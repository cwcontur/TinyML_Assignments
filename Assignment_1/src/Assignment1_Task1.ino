#define BLUE 24
#define LED_PWR 25

void setup() {
  // intitialize the digital Pin as an output
  pinMode(BLUE, OUTPUT);
}

// the loop function runs over and over again
void loop() {

  for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5) {

    // sets the value (range from 0 to 255):

    analogWrite(BLUE, fadeValue);

    // wait for 30 milliseconds to see the dimming effect

    delay(30);
  }

  for (int fadeValue = 255; fadeValue >= 0; fadeValue -= 5) {

    // sets the value (range from 0 to 255):

    analogWrite(BLUE, fadeValue);

    // wait for 30 milliseconds to see the dimming effect

    delay(30);
  }
}