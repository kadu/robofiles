#include <stdio.h>

unsigned long channel[5];
//Motor
int motor_left[]    = {9,8};
int motor_right[]   = {11,10};
int motor1en        = 7 ;
int motor2en        = 12;


void setup() {
  Serial.begin(9600);
  Serial.print("Setup");
  for(int i=0; i<5; i++)
    channel[i] = 0;
  //Controle
  pinMode (22, INPUT);
  pinMode (24, INPUT);
  pinMode (26, INPUT);
  pinMode (28, INPUT);
  
  //Motor
  pinMode(motor1en, OUTPUT);
  pinMode(motor2en, OUTPUT);
  for(int i=0;i < 2; i++){
    pinMode(motor_left[i],  OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
  Serial.println(" completed!");
}

void loop() {
  channel[0] = (pulseIn (22, HIGH, 100000));
  channel[1] = (pulseIn (24, HIGH, 100000)); 
  channel[2] = (pulseIn (26, HIGH, 100000)); 
  channel[3] = (pulseIn (28, HIGH, 100000));
  if(channel[0]!=0)
    for(int i=0; i<4; i++)    
      channel[i] = map(channel[i],1040,1880,0,100);
      
  Serial.print("    channel 1  "); Serial.print(channel[0]); //esquerda/direita (mao esquerda)
  Serial.print("    channel 2  "); Serial.print(channel[1]); //cima baixo (mao esquerda)
  Serial.print("    channel 3  "); Serial.print(channel[2]); //acelerador
  Serial.print("    channel 4  "); Serial.print(channel[3]); //esquerda/direita (mao direita)
  Serial.println("");
  
  delay(1000);
}


// Funcoes do Motor
void turnMotorsOnLine(void) {
  digitalWrite(motor1en, HIGH); 
  digitalWrite(motor2en, HIGH);
}
void turnMotorsOffLine(void) {
  digitalWrite(motor1en, LOW); 
  digitalWrite(motor2en, LOW);
}
void motor_stop(){
  digitalWrite(motor_left[0], HIGH);
  digitalWrite(motor_left[1], HIGH);
  digitalWrite(motor_right[0], HIGH);
  digitalWrite(motor_right[1], HIGH);
  
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], LOW); 
}
void drive_forward(){
  digitalWrite(motor_left[0], HIGH);
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_right[0], HIGH);
  digitalWrite(motor_right[1], LOW);
}
void drive_backward(){
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], HIGH);
  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], HIGH);
}
void  turn_left(){
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], HIGH);
  digitalWrite(motor_right[0], HIGH);
  digitalWrite(motor_right[1], LOW);
}
void turn_right(){
  digitalWrite(motor_left[0], HIGH);
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], HIGH);
};
