#include <Servo.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int servoPin = 13, LED = 50, BUZZ = 52;
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'c','0','=','+'}
};
byte rowPins[ROWS] = {26, 27, 28, 29}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {22, 23, 24, 25}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo myservo;

String stateStr[] = {"Pass: ", "door is open", "locked", "new pass: ", "new time: "};
String input, password = "0000";
int timer = 10, wrongPassCnt = 0, state = 0, ttt = 10;
long t0 = millis();
bool isTimerOn = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  
  myservo.attach(servoPin);
  myservo.write(map(0, -180, 180, 0, 180));
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(stateStr[state]);

}

int getLeftTime() {
  if (!isTimerOn) {
    return 0;
  }
  return timer - (millis() - t0) / 1000;
}

void lockDoor() {
  digitalWrite(BUZZ, HIGH);
  myservo.write(map(0, -180, 180, 0, 180));
  digitalWrite(LED, LOW);
  isTimerOn = false;
  state = 0;
  input = "";
  printState();
  delay(100);
  digitalWrite(BUZZ, LOW);
}

void openDoor() {
  digitalWrite(BUZZ, HIGH);
  state = 1;
  myservo.write(map(180, -180, 180, 0, 180));
  digitalWrite(LED, HIGH);
  isTimerOn = true;
  t0 = millis();
  delay(100);
  digitalWrite(BUZZ, LOW);
}

void checkPassword() {
  lcd.clear();
  if (input == password) {
    wrongPassCnt = 0;
    lcd.setCursor(0, 0);
    lcd.print("correct");
    input = "";
    timer = ttt;
    delay(500);
    openDoor();
  } else {
    wrongPassCnt++;
    if (wrongPassCnt >= 4) {
      state = 2;
      input = "";
      t0 = millis();
      isTimerOn = true;
      timer = (wrongPassCnt - 3) * 5;
      lcd.setCursor(0, 1);
      lcd.print("system locked!");
    } else {
      lcd.print("wrong");
      lcd.setCursor(0, 1);
      lcd.print("left: " + String(4-wrongPassCnt));
      state = 0;
      input = "";
    }
  }
}

void printState() {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(stateStr[state] + input);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int leftTime = getLeftTime();
  if (leftTime < 0) {
    if (state == 2) {
      state = 0;
    } else {
      lockDoor(); 
    }
  }
  if (isTimerOn) {
    lcd.setCursor(0,0);
    lcd.print("Time: " + String(leftTime) + " ");  
  }
  char key = keypad.getKey();
  if (key && state != 2) {
    printState();
    lcd.print(key);
    if (key == '=') {
      if (state == 0 && !isTimerOn) {
        checkPassword();
      } else if (state == 3 && isTimerOn) {
        password = input;
        input = "";
        state = 1;
        printState();
      } else if (state == 4 && isTimerOn) {
        ttt = input.toInt();
        timer = ttt;
        input = "";
        state = 1;
        printState();
      }
    } else if (key == '+' && state == 1) {
      state = 3;
      printState();
    } else if (key == '-' && state == 1) {
      state = 4;
      printState();
    } else if (key == '*' && state == 1) {
      lockDoor();
    } else {
      input += key;
    }
  }
  
}
