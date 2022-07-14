#include <SPI.h>

char* MESSAGE0 = "Moujan\r";
char* MESSAGE1 = "Farhan\r";

#define SS0_PIN 44
#define SS1_PIN 45

void setup() {
  Serial.begin(9600);
  Serial.println("Starting master");

  pinMode(SS0_PIN, OUTPUT);
  digitalWrite(SS0_PIN, HIGH);

  pinMode(SS1_PIN, OUTPUT);
  digitalWrite(SS1_PIN, HIGH);
  
  SPI.begin();
}


void loop() {
  digitalWrite(SS0_PIN, LOW);
  delay(10);
  for (char* ch = MESSAGE0; *ch; ++ch) {
    Serial.print(*ch);
    SPI.transfer(*ch);
    delay(5);
  }
  digitalWrite(SS0_PIN, HIGH);
  delay(1000);

  digitalWrite(SS1_PIN, LOW);
  delay(10);
  for (char* ch = MESSAGE1; *ch; ++ch) {
    Serial.print(*ch);
    SPI.transfer(*ch);
    delay(5);
  }
  digitalWrite(SS1_PIN, HIGH);
  delay(1000);
}
