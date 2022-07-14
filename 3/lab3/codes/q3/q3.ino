#include <LiquidCrystal.h>
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'o', '0', '=', '+'}
};
byte rowPins[ROWS] = {31, 33, 35, 37}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {23, 25, 27, 29}; //connect to the column pinouts of the keypad

const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String op1, op2;
char op;
boolean op_entered = false;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    lcd.print(key);
    if (key == 'o')
    {
      op1 = "";
      op2 = "";
      op_entered = false;
      lcd.clear();
      lcd.setCursor(0, 0);
    }
    else if (key == '=')
    {
      int a = op1.toInt();
      int b = op2.toInt();
      lcd.setCursor(0, 1);
      switch (op)
      {
        case '+':
          lcd.print(a + b);
          break;
        case '-':
          lcd.print(a - b);
          break;
        case '*':
          lcd.print(a * b);
          break;
        case '/':
          lcd.print((float)a / b);
          break;
      }
    }
    else if (!op_entered && (key == '+' || key == '-' || key == '*' || key == '/'))
    {
      op = key;
      op_entered = true;
    }
    else if (! op_entered)
    {
      op1 += key;
    }
    else
    {
      op2 += key;
    }
  }
}
