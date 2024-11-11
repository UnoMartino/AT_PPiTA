void setup() {
  // put your setup code here, to run once:
  pinMode(13, INPUT);
  pinMode(14, INPUT);
  pinMode(15, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int valueX = analogRead(13);
  int valueY = analogRead(14);
  bool button = !digitalRead(15);
  Serial.println("X: " + String(valueX));
  Serial.println("Y: " + String(valueY));
  Serial.println("Button: " + String(button));
  delay(100);
}
