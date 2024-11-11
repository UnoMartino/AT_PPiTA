void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
    char text[100] = {0};
    int size = Serial.available();
    Serial.readBytes(text, size);

    Serial.println(text);
  }

  delay(100);
}
