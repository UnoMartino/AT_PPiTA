#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, 10, 9);



void setup() {
  // put your setup code here, to run once:
  pinMode(13, INPUT);
  pinMode(14, INPUT);
  pinMode(15, INPUT);

  Serial.begin(9600);
  u8g2.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  int valueX = analogRead(13);
  int valueY = analogRead(14);
  int button = analogRead(15);

  u8g2.clearBuffer();
	
  int roundX = map(valueX, 0, 4096, -58, 58);
  int roundY = map(valueY, 0, 4096, -58, 58);

  
  Serial.println("Button: " + String(button));
  Serial.println();

  u8g2.drawFrame(4, 6, 120, 20);

  if (roundX > 0) {
    u8g2.drawBox(64, 8, roundX, 16);
    Serial.println("X: " + String(roundX));
  }
  else if (roundX < 0) {
    u8g2.drawBox(64 + roundX, 8, - roundX, 16);
    Serial.println("X: " + String(roundX));
  }


  // u8g2.drawBox(6, 12, roundX, 16);

  u8g2.drawFrame(4, 28, 120, 20);

  if (roundY > 0) {
    u8g2.drawBox(64, 30, roundY, 16);
    Serial.println("Y: " + String(roundY));

  }
  else if (roundY < 0) {
    u8g2.drawBox(64 + roundY, 30, - roundY, 16);
    Serial.println("Y: " + String(roundY));

  }

  // u8g2.drawBox(6, 34, roundY, 16);

  u8g2.setFont(u8g2_font_helvR10_tf);

  u8g2.setCursor(4, 62);
  u8g2.print("X: " + String(roundX));

  u8g2.setCursor(48, 62);
  u8g2.print("Y: " + String(roundY));

  u8g2.setCursor(92, 62);
  if (button < 20) {
    u8g2.print("B: 1");
  }
  else {
    u8g2.print("B: 0");
  }
  
  u8g2.sendBuffer();  

  delay(10);

}
