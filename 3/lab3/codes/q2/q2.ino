#include <LiquidCrystal.h>
#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'#', '0', '=', '+'}
};
byte rowPins[ROWS] = {31, 33, 35, 37};
byte colPins[COLS] = {23, 25, 27, 29};
const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte col = 0;
String password;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  lcd.setCursor(col, 0);
  char key = keypad.getKey();
  if (key) {
    if (key == '#') 
    {
      lcd.clear();
      col = 0;
      password = "";
    }
    else if (key == '*')
    {
      lcd.setCursor(0, 1);
      if (password == "9831140") {
        lcd.print("Correct password");
        password = "";
      } else {
        lcd.print("Wrong password");
        password = "";
      }
    } 
    else 
    {
      lcd.print(key);
      password += key;
      col++;
    }
  }
}
