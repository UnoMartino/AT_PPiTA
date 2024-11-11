#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        21

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

bool state = 0;

void setup() {
  // put your setup code here, to run once:
  pixels.begin();
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
    char text[100] = {0};
    int size = Serial.available();
    Serial.readBytes(text, size);


    char colorLetter = text[0];
    char colorValue[3];
    for(int i = 0; i < sizeof(colorValue);i++)
    {
      colorValue[i] = text[i + 1];
    }

    int colorValueInt = atoi(colorValue);
    
    switch (text[0]) {
      case 'R':
        pixels.setPixelColor(0, pixels.Color(colorValueInt,0, 0));
        break;
      
      case 'G':
        pixels.setPixelColor(0, pixels.Color(0, colorValueInt, 0));
        break;

      case 'B':
        pixels.setPixelColor(0, pixels.Color(0, 0, colorValueInt));
        break;
    }
    pixels.show(); 
    Serial.println(text);
  }

  delay(100);
}
