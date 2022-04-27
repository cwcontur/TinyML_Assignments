#include "model.cc"
#include <Arduino_LSM9DS1.h>

// global definitions for LEDs
#define RED 22
#define BLUE 24
#define LED_PWR 25

// global variables
const float accelerationThreshold = 2.5; // threshold of significant in G's
const int numSamples = 119;

int predictions = 0;
float avg;
int samplesRead = numSamples;
int numColumn = 0;
int sampleNumber = 1;

float features[numSamples];

Eloquent::ML::Port::Classifier model; 

void setup() {
    //capture new data
    Serial.begin(9600);

    // Initializes LEDs
    pinMode(BLUE, OUTPUT);
    pinMode(RED, OUTPUT);
    pinMode(LED_PWR, OUTPUT);

    // Turns LEDs off
    digitalWrite(RED, HIGH);
    digitalWrite(BLUE, HIGH);
    digitalWrite(LED_PWR, HIGH);

    while (!Serial);

    if (!IMU.begin()) {
      Serial.println("Failed to initialize IMU!");
      while (1);
    }
}

void loop() {

  float aX, aY, aZ, gX, gY, gZ;

  // wait for significant motion
  while (samplesRead == numSamples) {
    if (IMU.accelerationAvailable()) {
      // read the acceleration data
      IMU.readAcceleration(aX, aY, aZ);

      // sum up the absolutes
      float aSum = fabs(aX) + fabs(aY) + fabs(aZ);

      // check if it's above the threshold
      if (aSum >= accelerationThreshold) {
        // reset the sample read count
        samplesRead = 0;
        break;
      }
    }
  }
  
  float feature[numSamples][6];

  // check if the all the required samples have been read since
  // the last time the significant motion was detected
  while (samplesRead < numSamples) {

    // check if both new acceleration and gyroscope data is available
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
      // read the acceleration and gyroscope data
      IMU.readAcceleration(aX, aY, aZ);
      IMU.readGyroscope(gX, gY, gZ);

      samplesRead++;
      numColumn++;

      // keeps track of the number of columns in the data and resets count as needed
      if(numColumn == 119) {
        sampleNumber++;
        numColumn = 0;
      }

      // stores data
      feature[numColumn][0] = aX;
      feature[numColumn][1] = aY;
      feature[numColumn][2] = aZ;
      feature[numColumn][3] = gX;
      feature[numColumn][4] = gY;
      feature[numColumn][5] = gZ;

      // puts data through model after feature array is filled
      if (samplesRead == numSamples) {
        predictions++;
        // keeps track of time lapsed while predicting
        unsigned long start = micros();
        int result = model.predict(*feature); // puts data through model
        unsigned long end = micros();
        float elapsed = end - start;
        avg = avg + elapsed;
    
        // calculates the average time across 10 predictions
        if(predictions == 10){
          avg = avg/predictions;
          Serial.print("Average Prediction Time: ");
          Serial.print(avg);
          Serial.print(" microseconds\n");
          predictions = 0;
          avg = 0;
        }
        // changes LED to red or blue based on model prediction
        if(result == 0) {
          digitalWrite(RED, LOW);
          Serial.println("Wave Recorded");
          delay(2000);
          digitalWrite(RED, HIGH);
        } 
        else if (result == 1) {
          digitalWrite(BLUE, LOW);
          Serial.println("Fist Bump Recorded");
          delay(2000);
          digitalWrite(BLUE, HIGH);
        }
      }
    }
  }
}

