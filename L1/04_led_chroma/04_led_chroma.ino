#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        21

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

unsigned int hue = 0;

void setup() {
  pixels.begin();
  pinMode(0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  pixels.setPixelColor(0, pixels.ColorHSV(hue));
  pixels.show(); 
  if (hue < 65535){ hue += 10; }
  else { hue = 0; }
  
}
