/*
  Semaforo c/ Pedestre (Esquemas by Fritzing)
  
*/

const int scVerde    = 22;
const int scAmarelo  = 23;
const int scVermelho = 24;
const int spVerde    = 28;
const int spVermelho = 29;

int  ledState       = LOW;   
long previousMillis = 0;
long interval       = 5000;
int  ctrlLuz        = 0;

void setup() {
  Serial.begin(9600);
  pinMode(scVerde,OUTPUT);
  pinMode(scAmarelo,OUTPUT);
  pinMode(scVermelho,OUTPUT);
  pinMode(spVerde,OUTPUT);
  pinMode(spVermelho,OUTPUT);
  pinMode(2, INPUT);  // Botao
}

void loop() {

  unsigned long currentMillis = millis(); 
  int sensorValue = digitalRead(2); 
  if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;       
    switch(ctrlLuz) {
      case 0 : // Verde
        digitalWrite(scVermelho,LOW);
        digitalWrite(scVerde,HIGH);
        digitalWrite(spVerde,LOW);
        digitalWrite(spVermelho,HIGH);
        ctrlLuz++;
        interval = 15000;
        break;
      case 1 : // amarelo
        digitalWrite(scVerde,LOW);
        digitalWrite(scAmarelo,HIGH);
        digitalWrite(spVerde,LOW);
        digitalWrite(spVermelho,HIGH);
        ctrlLuz++;
        interval = 1000;
        break;
      case 2 : // Vermelho
        digitalWrite(scAmarelo,LOW);
        digitalWrite(scVermelho,HIGH);
        digitalWrite(spVermelho,LOW);
        digitalWrite(spVerde,HIGH);
        interval = 7000;      
        ctrlLuz = 0;
        break;
    }
  }
  
  if((sensorValue == 1) && (ctrlLuz == 1)) {
    interval = 2000;
    Serial.print("Sensor ");
    Serial.println(sensorValue, DEC);
  }
}
