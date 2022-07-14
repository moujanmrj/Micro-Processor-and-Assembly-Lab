#include <Servo.h>

Servo servo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(9, 1000, 2000);

}

int ServoMap(int x){
  return map(x, -180, 180, 1000, 2000);
}

String incoming = "";

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    incoming = Serial.readString();
    Serial.println(-1 * incoming.toInt());
    servo.writeMicroseconds(ServoMap(-1 * incoming.toInt()));
  }

}
