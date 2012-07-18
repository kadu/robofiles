#include <Servo.h>

#define ladoDireito  0
#define ladoEsquerdo 1

//Motor
int motor_left[]    = {9,8};
int motor_right[]   = {11,10};
int motor1en        = 7 ;
int motor2en        = 12;

void setup() {
  Serial.begin(115200);
  pinMode(motor1en, OUTPUT);
  pinMode(motor2en, OUTPUT);
  for(int i=0;i < 2; i++){
    pinMode(motor_left[i],  OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
  
  turnMotorsOnLine();
  delay(3000);
  Serial.println("Final de Setup");
}

void loop() {  
    Serial.println("loop");
    drive_backward();
    delay(3000);
    turn_left();
    delay(1200);
    motor_stop();
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
