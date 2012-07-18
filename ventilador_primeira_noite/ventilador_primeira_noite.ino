int pin[5] = {13,22,23,24,25};
int cnt;
float TEMPOON;
float TEMPOOFF;
float umminuto = 60000; // Um minuto


void setup() {
  for(cnt = 0; cnt < 5; cnt++) { 
    pinMode(pin[cnt], OUTPUT);
  }
  TEMPOON = 8 * umminuto;
  TEMPOOFF = 22 * umminuto;
    
  // Blink Led before start
  blink(pin[0], 15, 600);
  delay(2500);
  
  for(cnt = 0; cnt < 5; cnt++) 
    digitalWrite(pin[cnt], LOW); // desliga tudo
}

void loop() { 
  // Liga ventilador
  blink(pin[0], 30, 100);
  digitalWrite(pin[3], LOW);  
  delay(TEMPOON);


  // Desliga Ventilador
  blink(pin[0], 5, 100);
  digitalWrite(pin[3], HIGH); 
  delay(TEMPOOFF);  
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
