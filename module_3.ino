void setup() {
  Serial.begin(9600);
}

void loop() {
  int value;
  value = analogRead(A0);
  delay(100);

  int midiValue;
  midiValue = map(value, 0, 1023, 0, 127);
  Serial.println(midiValue);
}
