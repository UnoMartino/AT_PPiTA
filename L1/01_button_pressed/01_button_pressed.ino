bool state = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(0, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  bool button = digitalRead(0);
  if (!button) {
    if (state == 0) {
      state = 1;
      Serial.println("button pressed");
    }
  }
  else {
    state = 0;
  }

}
