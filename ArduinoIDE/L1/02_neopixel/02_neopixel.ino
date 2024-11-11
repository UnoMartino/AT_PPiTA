#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        21

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 1


Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);


void setup() {
  // put your setup code here, to run once:
  pixels.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(0, 255, 0));
  pixels.show(); 
  
}
