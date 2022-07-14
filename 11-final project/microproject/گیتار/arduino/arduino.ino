#include "pitches.h"

#define SOUNDER 11
#define DURATION 10

const int leds[] = {51, 52, 53};
int notes[3][5] = {
  {NOTE_G3, NOTE_GS3, NOTE_A4, NOTE_AS4, NOTE_B4},
  {NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_F3, NOTE_FS3},
  {NOTE_G2, NOTE_GS2, NOTE_A3, NOTE_AS3, NOTE_B3}
};

bool isPlaying[3] = {0};
int ways[3] = {0};
float scale;

void setup() {
  Serial.begin(9600);

  pinMode(leds[2], OUTPUT);
  pinMode(leds[1], OUTPUT);
  pinMode(leds[0], OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char key = Serial.read();
    Serial.println(key);

    switch (key) {
      case 'z':
        ways[2] = 0;
        break;
      case 'x':
        ways[2] = 1;
        break;
      case 'c':
        ways[2] = 2;
        break;
      case 'v':
        ways[2] = 3;
        break;
      case 'b':
        ways[2] = 4;
        break;
      case 'a':
        ways[1] = 0;
        break;
      case 's':
        ways[1] = 1;
        break;
      case 'd':
        ways[1] = 2;
        break;
      case 'f':
        ways[1] = 3;
        break;
      case 'g':
        ways[1] = 4;
        break;
      case 'q':
        ways[0] = 0;
        break;
      case 'w':
        ways[0] = 1;
        break;
      case 'e':
        ways[0] = 2;
        break;
      case 'r':
        ways[0] = 3;
        break;
      case 't':
        ways[0] = 4;
        break;
      case 'm':
        isPlaying[2] = !isPlaying[2];
        digitalWrite(leds[2], isPlaying[2] ? HIGH : LOW);
        break;
      case 'k':
        isPlaying[1] = !isPlaying[1];
        digitalWrite(leds[1], isPlaying[1] ? HIGH : LOW);
        break;
      case 'o':
        isPlaying[0] = !isPlaying[0];
        digitalWrite(leds[0], isPlaying[0] ? HIGH : LOW);
        break;
    };

  }

  if (isPlaying[2]) {
    scale = analogRead(A2) / 512.0;
    tone(SOUNDER, (int) (notes[2][ways[2]] * scale), DURATION);
    delay(DURATION);
  }
  if (isPlaying[1]) {
    scale = analogRead(A1) / 512.0;
    tone(SOUNDER, (int) (notes[1][ways[1]] * scale), DURATION);
    delay(DURATION);
  }
  if (isPlaying[0]) {
    scale = analogRead(A0) / 512.0;
    tone(SOUNDER, (int) (notes[0][ways[0]] * scale), DURATION);
    delay(DURATION);
  }
}
