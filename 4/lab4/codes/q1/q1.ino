#include <Servo.h>

Servo servo; 

int degree;   
void setup() {
  servo.attach(9,1000,2000);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  for (degree = 0; degree <= 90; degree ++) {
    servo.write(degree+90);
    delay(50);
  }
  for (degree = 90; degree >= 0; degree --) {
    servo.write(degree+90);
    delay(50);
  }
}
