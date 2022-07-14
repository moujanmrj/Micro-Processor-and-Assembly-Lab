int num = strlen("moujan");
void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  pinMode(18, INPUT);
  pinMode(19, INPUT);
  pinMode(20, INPUT);

  digitalWrite(0, LOW); 
  digitalWrite(1, LOW);    
  digitalWrite(2, LOW);    
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

void loop() {
   if (digitalRead(10) == 1){
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
  }
   if (digitalRead(11)== 1){  
    for (int i=0; i < num; i++){                      
        digitalWrite(0, HIGH);   
        digitalWrite(1, HIGH); 
        digitalWrite(2, HIGH); 
        digitalWrite(3, HIGH); 
        digitalWrite(4, HIGH); 
        digitalWrite(5, HIGH); 
        digitalWrite(6, HIGH); 
        delay(200); 
        digitalWrite(0, LOW); 
        digitalWrite(1, LOW);    
        digitalWrite(2, LOW);    
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        delay(200); 
    }
    digitalWrite(0, HIGH);   
    digitalWrite(1, HIGH); 
    digitalWrite(2, HIGH); 
    digitalWrite(3, HIGH); 
    digitalWrite(4, HIGH); 
    digitalWrite(5, HIGH); 
    digitalWrite(6, HIGH); 
    delay(200); 
  }
   if (digitalRead(12) == 1){
    digitalWrite(0, LOW); 
    digitalWrite(1, LOW);    
    digitalWrite(2, LOW);    
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    delay(200);
  }
}
