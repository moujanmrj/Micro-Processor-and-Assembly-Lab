void setup() {
  // put your setup code here, to run once:
  pinMode(52, OUTPUT);
}

void loop() {
  digitalWrite(52, LOW);
  delay(1000);
  digitalWrite(52, HIGH);
  delay(1000);
}
