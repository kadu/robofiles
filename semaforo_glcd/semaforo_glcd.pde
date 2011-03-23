#include <glcd.h>
#include <glcd_Config.h>
#include "fonts/allFonts.h"
#include "bitmaps/allBitmaps.h"

const int carro_Verde       = 9;
const int carro_Amarelo     = 10;
const int carro_Vermelho    = 11;

const int pedestre_Verde    = 12;
const int pedestre_Vermelho = 13;
const int pedestre_botao    = 52;

int sensorValue;

gText countdownArea =  gText(GLCD.CenterX, GLCD.CenterY,1,1,Arial_14); // text area for countdown digits

void setup() {
  Serial.begin(9600);
  Serial.println("Inicializando..."); 
  pinMode(carro_Verde      , OUTPUT);
  pinMode(carro_Amarelo    , OUTPUT);
  pinMode(carro_Vermelho   , OUTPUT);
  pinMode(pedestre_Verde   , OUTPUT);
  pinMode(pedestre_Vermelho, OUTPUT);
  pinMode(pedestre_botao   , INPUT); 

  // Iniciando GLCD e mostrando as imagens no inicio  
  GLCD.Init();
  GLCD.DrawBitmap(ArduinoIcon64x64,32,0);
  countdown(3);
  GLCD.DrawBitmap(teste02,0,0);
  delay(500);
  GLCD.ClearScreen();
  GLCD.DrawBitmap(olho_kadu01,0,0);
  GLCD.SelectFont(System5x7, BLACK);
  
  //delay(500);
  //GLCD.println("Inicializando...");
  inicia_semaforo();
}

void  loop() {
  haltTraffic(); 
  delay(10000); 
  changeGreen();
  for(int i=0;i<50;i++){ 
    if(digitalRead(pedestre_botao)==HIGH) 
      break; 
    delay(400); 
  }
}

void haltTraffic(){ 
  digitalWrite(carro_Verde      , LOW); 
  changeRed(); 
  digitalWrite(carro_Vermelho   , HIGH); 
  delay(1000); 
  digitalWrite(pedestre_Vermelho, LOW); 
  digitalWrite(pedestre_Verde   , HIGH); 
} 

void changeRed(){ 
  digitalWrite(carro_Amarelo, HIGH); 
  delay(5000); 
  digitalWrite(carro_Amarelo, LOW);
 GLCD.DrawBitmap(p_verde,0,0); 
} 

void changeGreen(){ 
  digitalWrite(pedestre_Verde, LOW); 
  for(int i=0;i<4;i++){ 
    digitalWrite(pedestre_Vermelho, LOW); 
    GLCD.DrawBitmap(p_vermelho,0,0);
    delay(500); 
    digitalWrite(pedestre_Vermelho, HIGH);
    GLCD.ClearScreen();
    delay(500); 
  } 
  delay(1500); 
  digitalWrite(carro_Vermelho, LOW);
 GLCD.DrawBitmap(p_vermelho,0,0); 
  digitalWrite(carro_Verde, HIGH); 
}

void inicia_semaforo() {
  // Pisca 10 vezes, mostrando que vai começar a funcionar o semaforo
  for(int i = 0; i < 10; i++) {  
    digitalWrite(carro_Amarelo    , HIGH);
    digitalWrite(pedestre_Verde   , HIGH);
    digitalWrite(pedestre_Vermelho, HIGH);
    delay(500);
    digitalWrite(carro_Amarelo    ,LOW);
    digitalWrite(pedestre_Verde   ,LOW);
    digitalWrite(pedestre_Vermelho,LOW);
    delay(500);  
  }

  digitalWrite(carro_Verde      , LOW);
  digitalWrite(carro_Amarelo    , LOW);
  digitalWrite(carro_Vermelho   , LOW);
  digitalWrite(pedestre_Vermelho, LOW);
  digitalWrite(pedestre_Verde   , LOW);
  GLCD.ClearScreen();
}


void countdown(int count){
  while(count--){  // do countdown  
    countdownArea.ClearArea(); 
    countdownArea.print(count);
    delay(1000);  
  }  
}



