#include <Ultrasonic.h>
Ultrasonic ultrasonic(52,53);
//LEd Matrix
int pgled[10] = {36,37,38,39,40,41,42,43,44,45};
int distancia;
int mapa;
void setup() {
  Serial.begin(115200);
  Serial.println("testing...");
  for(int i=0; i<10; i++){
    pinMode(pgled[i],OUTPUT);
  }
}

void loop() {
  distancia = ultrasonic.Ranging(CM);
  mapa = map(distancia,10,60,9,0);
  progress(mapa);
  Serial.print(distancia);
  Serial.print("cm - mapa = ");
  Serial.println(mapa);
  delay(400);
}

void progress(int pos) {
  int i;
  if (pos > 10) 
    pos = 10;
  for(i = 0; i < 10; i++) {
    if(i<pos) {
      digitalWrite(pgled[i], HIGH);
    } else {
      digitalWrite(pgled[i], LOW);
    }
  }
}

