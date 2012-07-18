int pin[5] = {13,22,23,24,25};
int cnt;

void setup() {
  for(cnt = 0; cnt < 5; cnt++) { 
    pinMode(pin[cnt], OUTPUT);
  }
    
  // Blink Led before start
  blink(pin[0], 7, 600);
  delay(1000);
  
  for(cnt = 0; cnt < 5; cnt++) 
    digitalWrite(pin[cnt], LOW); // desliga tudo
}

void loop() { 
  for(cnt = 0; cnt < 4; cnt++) {
    blink(pin[0], cnt+1, 1000);
    delay(1000);
    digitalWrite(pin[cnt+1], HIGH);
    delay(2500);
    digitalWrite(pin[cnt+1], LOW);
  }
  
}

//  blinks an LED
void blink(int whatPin, int howManyTimes, int milliSecs) {
  int i = 0;
  for ( i = 0; i < howManyTimes; i++) {
    digitalWrite(whatPin, HIGH);
    delay(milliSecs/2);
    digitalWrite(whatPin, LOW);
    delay(milliSecs/2);
  }
}
