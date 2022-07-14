#include<SPI.h>
#include <Servo.h>

int firstSlave = 36;
int secondSlave = 34;
int tempPin = A0;
int val;
Servo servo1; 
Servo servo2;
Servo servo3;

void setup(){
    servo1.attach(40,1000,2000); //1
    servo2.attach(41,1000,2000); //2
    servo3.attach(39,1000,2000); //3
    SPI.begin();
    pinMode(firstSlave, OUTPUT);
    pinMode(secondSlave, OUTPUT);
    digitalWrite(firstSlave, HIGH);
    digitalWrite(secondSlave, HIGH);
}

void loop(){
    val = analogRead(tempPin);
    float cel = (val/1024.0)*500;
    if (cel>30){
      servo1.writeMicroseconds(2000);
      servo2.writeMicroseconds(2000);
      servo3.writeMicroseconds(2000);
    }else if (cel<20){
      servo1.writeMicroseconds(1000);
      servo2.writeMicroseconds(1000);
      servo3.writeMicroseconds(1000);    
    }else{
      servo1.writeMicroseconds(1500);
      servo2.writeMicroseconds(1500);
      servo3.writeMicroseconds(1500);
    }
    sendData(cel, firstSlave);
    sendData(cel, secondSlave);
}

void sendData(int data, int targetSlave){
    digitalWrite(targetSlave, LOW);
    delay(50);
    SPI.transfer((byte)data);
    digitalWrite(targetSlave, HIGH);
    delay(50);
}
