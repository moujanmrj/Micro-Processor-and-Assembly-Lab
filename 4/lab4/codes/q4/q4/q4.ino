#include <Servo.h>

Servo servo;  

void setup() {
  servo.attach(9);  
  Serial.begin(9600);
}

void loop() {
  int degree; 
  degree = analogRead(A0);
  degree = map(degree, 0, 1023, 0, 180);
  servo.write(degree);
  Serial.println(degree);
  delay(1000);
}
