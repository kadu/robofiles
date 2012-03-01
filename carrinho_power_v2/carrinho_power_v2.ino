\#include <Ultrasonic.h>
#include <Servo.h>

#define ladoDireito  0
#define ladoEsquerdo 1
//sensor ultrasonico
#define usTrigger 52
#define usEcho    53

int distancia = 0;

//LEd Matrix
int pgled[10] = {36,37,38,39,40,41,42,43,44,45};

//Servo
Servo myservo;
int posicao         = 0;
int lado            = ladoDireito;   // flag pra marcar se esta subindo ou descendo
const int ServoPin  = 33;  // data do servo
//Motor
int motor_left[]    = {9,8};
int motor_right[]   = {11,10};
int motor1en        = 7 ;
int motor2en        = 12;
// Buzzer
const int buzzPin   = 22; // era 5

Ultrasonic ultrasonic(usTrigger,usEcho);
int mapa;

void setup() {
  Serial.begin(115200);
  pinMode(motor1en, OUTPUT);
  pinMode(motor2en, OUTPUT);
  for(int i=0;i < 2; i++){
    pinMode(motor_left[i],  OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
  for(int i=0; i<10; i++){
    pinMode(pgled[i],OUTPUT);
  }
  
  blink(buzzPin, 3, 700);
  myservo.attach(ServoPin);
  grillo(buzzPin,5);
  turnMotorsOnLine();
  delay(3000);
}

void loop() {
  distancia = ultrasonic.Ranging(CM);
  mapa = map(distancia,50,400,9,0);
  progress(mapa); 
  Serial.print("Distancia atual: ");
  Serial.print(distancia);
  Serial.println(" cm");
  Serial.println(mapa);
  
  vaiservo();
  if(distancia <= 45) {
    motor_stop();
    drive_backward();
    grillo(buzzPin,3);
    turn_left();
    delay(700);
    motor_stop();
    delay(1000);
  } 
  drive_forward();
  delay(600);
}

void vaiservo() {
  if(lado == ladoDireito) 
    posicao+=90;
  else
    posicao-=90;
    
  if((posicao==0)||(posicao==180))
    lado = !lado;  
  
  myservo.write(posicao);
  delay(100);
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

void grillo(const int Pin, int vezes) {
  int i;
  for(i = 0; i < vezes; i++) {
    tone(Pin,55,900);
    delay(250);
    noTone(Pin);
    delay(250);  
  }
};

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

void progress(int pos) {
  int i;
  if (pos > 10) 
    pos = 10;
  if(pos < 1)
    pos = 0;
  for(i = 0; i < 10; i++) {
    if(i<pos) {
      digitalWrite(pgled[i], HIGH);
    } else {
      digitalWrite(pgled[i], LOW);
    }
  }
}
