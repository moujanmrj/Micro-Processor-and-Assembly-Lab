#include <LiquidCrystal.h>
#include <Keypad.h>

const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

boolean flag = false;
char incomingByte;
int col = 0;
int row = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
}
void loop() {
  if (Serial.available() > 0 && !flag) {
    incomingByte = Serial.read();
    flag = true;
    col = 0;
    row = 0;
  }

  lcd.clear();
  lcd.setCursor(col, row);
  lcd.print(incomingByte);
  col++;
  if (col == 16) {
    col = 0;
  }
  row = 1 - row;
  delay(300);
}
