#include "model.cc"
#include <Arduino_LSM9DS1.h>

// global definitions for LEDs
int red_light_pin= 11;
int green_light_pin = 10;
int blue_light_pin = 9;
float avg;
int predictions = 0;

// tune as per your needs
#define SAMPLES 64
#define GAIN (1.0f/50)
#define SOUND_THRESHOLD 2000

float features[SAMPLES];

Eloquent::ML::Port::Classifier model; 

void setup() {
    //capture new data
    Serial.begin(9600);

    // Initializes LEDs
    pinMode(red_light_pin, OUTPUT);
    pinMode(green_light_pin, OUTPUT);
    pinMode(blue_light_pin, OUTPUT);

    while (!Serial);

    if (!IMU.begin()) {
      Serial.println("Failed to initialize IMU!");
      while (1);
    }
}

void loop() {

  if (recordAudioSample()) {
      predictions++;

      // Serial.println(clf.predictLabel(*features)) 
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
        RGB_color(0, 255, 00); // Green       
        Serial.println("Go Recorded");
        delay(2000);
        RGB_color(0, 0, 0);
      } 
      else if (result == 1) {
        RGB_color(255, 0, 0); // Red
        Serial.println("Stop Recorded");
        delay(2000);
        RGB_color(0, 0, 0);
      }
      else if (result == 2) {
        RGB_color(0, 0, 255); // Blue
        Serial.println("Up Recorded");
        delay(2000);
        RGB_color(0, 0, 0); 
      }
      else if (result == 3) {
        RGB_color(255, 161, 0); // Orange
        Serial.println("Down Recorded");
        delay(2000);
        RGB_color(0, 0, 0);
      }
  }

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
  {
   analogWrite(red_light_pin, red_light_value);
   analogWrite(green_light_pin, green_light_value);
   analogWrite(blue_light_pin, blue_light_value);
 }

/**
 * PDM callback to update mic object
 */
void onAudio() {
    mic.update();
}

/**
 * Read given number of samples from mic
 */
bool recordSample() {

    if (mic.hasData() && mic.data() > SOUND_THRESHOLD) {

        for (int i = 0; i < SAMPLES; i++) {
            while (!mic.hasData())
                delay(1);

            features[i] = mic.pop() * GAIN;
        }

        return true;
        delay(1000);
    }

    return false;
    delay(20);
}

