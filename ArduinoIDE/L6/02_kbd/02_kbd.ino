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

  Keyboard.write();
}


void loop() {


}
