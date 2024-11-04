#include "USB.h"
#include "USBHIDMouse.h"
#include "USBHIDKeyboard.h"
USBHIDMouse Mouse;
USBHIDKeyboard Keyboard;

void interruptButton() {
  Serial.println("Button");
}

void setup() {  // initialize the buttons' inputs:
  pinMode(10, INPUT);
  pinMode(9, INPUT);
  pinMode(8, INPUT_PULLUP);

  attachInterrupt(15, interruptButton, FALLING);

  Serial.begin(115200);
  // initialize mouse control:
  Mouse.begin();
  Keyboard.begin();
  USB.begin();
}

int speed = 5;
bool state = 0;


void loop() {

  int valueX = analogRead(10);
  int valueY = analogRead(9);
  bool button = !digitalRead(8);

  int roundX = map(valueX, 0, 4096, -speed, speed);
  int roundY = map(valueY, 0, 4096, -speed, speed);

  if (roundX < -1) {
    Mouse.move(roundX, 0);
  } 
  if (roundX > 1) {
    Mouse.move(roundX, 0);
  }
  if (roundY < -1) {
    Mouse.move(0, roundY);
  } 
  if (roundY > 1) {
    Mouse.move(0, roundY);
  }

  delay(5);
}
