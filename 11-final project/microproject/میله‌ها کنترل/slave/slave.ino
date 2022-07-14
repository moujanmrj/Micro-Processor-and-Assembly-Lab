#include<SPI.h>

int dataReady = 53;

void setup(){
    Serial.begin(9600);
    SPI.begin();
    pinMode(dataReady, INPUT_PULLUP);
    pinMode(51, INPUT);
    pinMode(52, INPUT);
    SPCR |= _BV(SPE);
    SPI.attachInterrupt(); 
}

void loop() {

}

ISR (SPI_STC_vect){
    int x = (int) SPDR;
    Serial.println(SPDR);
    if(x > 30){
      tone(7,300,100);
    }
}
