#define RED 22
#define BLUE 24
#define LED_PWR 25

void setup() {
  // intitialize the digital Pin as an output
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);
}

// the loop function runs over and over again
void loop() {

  for (int fadeValue = 0; fadeValue <= 360; fadeValue += 5) {

        // sets the relative value (range from -1 - 1):
    int RelativeBrightness = (1 - sin(radians(fadeValue))) * 255;

    // makes sure result is a positive number
    if(RelativeBrightness < 0) {
      RelativeBrightness *= -1;
    }

    analogWrite(BLUE, RelativeBrightness);

    // wait for 30 milliseconds to see the dimming effect

    delay(30);
  }

  for (int fadeValue = 0; fadeValue <= 360; fadeValue += 5) {

        // sets the relative value (range from -1 - 1):
    int RelativeBrightness = (1 - sin(radians(fadeValue))) * 255;

    // makes sure result is a positive number
    if(RelativeBrightness < 0) {
      RelativeBrightness *= -1;
    }

    analogWrite(RED, RelativeBrightness);

    // wait for 30 milliseconds to see the dimming effect

    delay(30);
  }

}