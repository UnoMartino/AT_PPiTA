#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        21

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

bool state = 0;
int color = 0;

void setup() {
  pixels.begin();
  pinMode(0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  bool button = digitalRead(0);

  // Read button press and change color
  if (!button) {
    if (state == 0) {
      state = 1;

      if (color<3) {
        color++;
      }
      else {
        color = 0;
      }
    }
  }
  else {
    state = 0;
  }

  // LED handler
  pixels.clear();
  switch (color) {
    case 0:
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      break;
    case 1:
      pixels.setPixelColor(0, pixels.Color(255, 0, 0));
      break;
    case 2:
      pixels.setPixelColor(0, pixels.Color(0, 255, 0));
      break;
    case 3:
      pixels.setPixelColor(0, pixels.Color(0, 0, 255));
      break;
  }
  pixels.show(); 

}
