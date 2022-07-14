#include "pitches.h"
#include "themes.h"
#include "themes (1).h"
#include "themes (2).h"
#include "themes (3).h"
#include "custom.h"
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {25, 26, 27, 28}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {22, 23, 24}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int* melodies[] = {melody1, melody2, melody3, melody4, melody5};
int* noteDurationsArr[] = {noteDurations1, noteDurations2, noteDurations3, noteDurations4, noteDurations5};
int melodySizes[] = {sizeof(melody1)/sizeof(int), sizeof(melody2)/sizeof(int), sizeof(melody3)/sizeof(int), sizeof(melody4)/sizeof(int), sizeof(melody5)/sizeof(int)};
float scale = 1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();
  
  if (key){
    if (key >= '1' && key <= '5') {
      int num = key - '1';
      for (int thisNote = 0; thisNote < melodySizes[num]; thisNote++) {
        scale = analogRead(A15)/512.0;
        int noteDuration = 300 / noteDurationsArr[num][thisNote];
        tone(8, (int)(melodies[num][thisNote] * scale), noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(8);
      }
    }
  }
  
}
