#include <Wire.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
#define ADDR 0b1010000

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'7','8','9', '/'},
  {'4','5','6', '*'},
  {'1','2','3', '-'},
  {'C','0','=', '+'}
};
byte rowPins[ROWS] = {26, 27, 28, 29}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {22, 23, 24, 25}; //connect to the column pinouts of the keypad
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

const int LEDs[4] = {53, 52, 51, 50};
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


String stateStr[] = {"IDLE", "Working...", "HOLD", "new time: "};
int timer[4] = {5, 5, 5, 5}, curTimer = timer[0], saveTimer = 0;
String input;
int state = 0, _step = 0, changeTimeStep = 0;
long t0 = millis();
bool isTimerOn = false;

void saveSettings(int _curTimer)
{
  eeprom_write(0, _step);
  eeprom_write(1, state);
  for (int i = 0; i < 4; i++) {
     eeprom_write(i+2, timer[i]);
  }
  eeprom_write(6, _curTimer);
  eeprom_write(7, isTimerOn ? 1 : 0);
}
void loadSettings()
{
  _step = eeprom_read(0);
  if (_step == 255) {
    return;
  }
  state = eeprom_read(1);
  for (int i = 0; i < 4; i++) {
    timer[i] = eeprom_read(2+i);
  }
  curTimer = eeprom_read(6);
  
  isTimerOn = eeprom_read(7);
}
void eeprom_write(byte dataAddress, byte data){
  Wire.beginTransmission(ADDR);
  Wire.write(dataAddress);
  Wire.write(data);
  Serial.println(data);
  Wire.endTransmission();
}
byte eeprom_read(byte dataAddress){
  byte data = NULL;
  Wire.beginTransmission(ADDR);
  Wire.write(dataAddress);
  Wire.endTransmission();
  Wire.requestFrom(ADDR, 1);
  delay(1);
  if(Wire.available()){
    data = Wire.read();
  Serial.println(data);
  }
  return data;
}


int getLeftTime() {
  if (!isTimerOn) {
    return 0;
  }
  return curTimer - (millis() - t0) / 1000;
}

void printState() {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(stateStr[state] + input);
}

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 4; i++) {
    pinMode(LEDs[i], OUTPUT);
  }
  
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(16, 2);
  lcd.clear();
  //saveSettings(5);
  loadSettings();
  printState();
}


void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 4; i++) {
    if (i == _step && (state == 1 || state == 2))
      digitalWrite(LEDs[i], HIGH);
    else
      digitalWrite(LEDs[i], LOW);
  }
  int leftTime = getLeftTime();
  if (isTimerOn && leftTime < 0) {
    if (_step == 3) {
      for (int i = 0; i < 4; i++) {
        digitalWrite(LEDs[i], HIGH);
      }
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    FINISHED    ");
      isTimerOn = false;
      state = 0;
      delay(2000);
      lcd.clear();
      for (int i = 0; i < 4; i++) {
          digitalWrite(LEDs[i], LOW);
      }
      lcd.setCursor(0, 1);
      lcd.print(stateStr[0]);
      _step = (_step + 1) % 4;
    } else {
      _step = (_step + 1) % 4;
      t0 = millis();
      curTimer = timer[_step];
    }
    
  }else if (isTimerOn) {
    lcd.setCursor(0,0);
    lcd.print("Time: " + String(leftTime) + " ");  
  }
  char key = keypad.getKey();
  if (key) {
    printState();
    if (key == '*') {
      if (state == 0) { //IDLE
        t0 = millis();
        curTimer = timer[_step];
        state = 1;  
        isTimerOn = true;
        digitalWrite(LEDs[_step], HIGH);
        printState();
      } else if (state == 1) { //Working...
        state = 2;
        curTimer = leftTime;
        isTimerOn = false;
        printState();
      } else if (state == 2) { //HOLD
        state = 1;
        t0 = millis();
        isTimerOn = true;
        printState();
      }
    } else if (key == '=' && state == 3) {
      state = 0;
      timer[changeTimeStep] = input.toInt();
      input = "";
      printState();
    } else if (key >= '1' && key <= '4' && state == 0) {
      changeTimeStep = key - '1';
      state = 3;
      input = "";
      printState();
    } else if (state == 3) {
      input += key;
      printState();
    }
  }

  if ( millis() - saveTimer > 200)
  {
    if (isTimerOn) {
      saveSettings(leftTime); 
    } else {
      saveSettings(curTimer); 
    }
    saveTimer = millis();
  }
}
