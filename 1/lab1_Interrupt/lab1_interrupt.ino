volatile boolean flag1 = false;
volatile boolean flag2 = false;
int num = strlen("moujan");

void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  pinMode(18, INPUT);
  pinMode(19, INPUT);
  pinMode(20, INPUT);
  attachInterrupt(digitalPinToInterrupt(18), button1, RISING);
  attachInterrupt(digitalPinToInterrupt(19), button2, RISING);
  attachInterrupt(digitalPinToInterrupt(20), button3, RISING);
}

void button1() {
  flag1 = true;
}

void button2() {
  flag2 = true;
}

void button3() {
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}


void loop() {
  if (flag1) {
    digitalWrite(0, HIGH);
    delay(200);
    digitalWrite(1, HIGH);
    delay(200);
    digitalWrite(2, HIGH);
    delay(200);
    digitalWrite(3, HIGH);
    delay(200);
    digitalWrite(4, HIGH);
    delay(200);
    digitalWrite(5, HIGH);
    delay(200);
    digitalWrite(6, HIGH);
    delay(200);
    digitalWrite(7, HIGH);
    delay(200);
    flag1 = false;
  }

  if (flag2) {
    for (int i = 0; i < num; i++) {
      digitalWrite(0, HIGH);
      digitalWrite(1, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
      delay(200);
      digitalWrite(0, LOW);
      digitalWrite(1, LOW);
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      delay(200);

    }
    digitalWrite(0, HIGH);
    digitalWrite(1, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    flag2 = false;
  }
}
