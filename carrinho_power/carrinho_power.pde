#include <Servo.h>
#include <SoftwareSerial.h>
#include <Ultrasonic.h>
Ultrasonic ultrasonic(52,53);

// Servo
Servo myservo;
int pos = 0; // posicao do servo
int ctrlpos = 0; // 0 sobe 1 desce
int controle = 0;

// Constantes para a pinagem Motor
int motor_left[]    = {9,8};
int motor_right[]   = {11,10};
int motor1en        = 7 ;
int motor2en        = 12;

// Sensor de Batida
const int SensorPin = 6;

//Conta loop
int contaloop = 0;

// RFID
int  val = 0; 
char code[10]; 
int bytesread = 0; 

#define rxPin 0
#define txPin 1
#define rfidStdout 2 

// Status
const int ledPin = 3;

// Buzz
const int buzzPin = 5;

int stat = 0;

// Setup
void setup() { 
  
  Serial.begin(9600);
  pinMode(SensorPin  ,INPUT); 

  
  pinMode(motor1en,OUTPUT); 
  pinMode(motor2en,OUTPUT); 
  pinMode(ledPin  ,OUTPUT); 
  
  for(int i = 0; i < 2; i++){
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
//  turnMotorsOnLine(); // Liga motores
  
  //rfid
  pinMode(rfidStdout,OUTPUT);       // Set digital pin 2 as OUTPUT to connect it to the RFID /ENABLE pin 
  digitalWrite(rfidStdout, LOW);    // Activate the RFID reader 

  blink(buzzPin, 3, 700);
  
  // Servo
  myservo.attach(42);
}

void loop() {
  contaloop++;
  if(contaloop==1)
    esperaChave();
  
  turnMotorsOnLine();
  vaiservo();
  stat = ultrasonic.Ranging(CM);
  Serial.print("Distancia atual: ");
  Serial.print(stat);
  Serial.println(" cm");
  if (stat <= 20) {
    motor_stop(); Serial.println("Para Motor");
    drive_backward(); Serial.println("Anda pra tras");
    grillo(buzzPin,5);
    
    turn_left(); Serial.println("Vira a esquerda");
    delay(1000);
    while(pegaValor(SensorPin) == HIGH) {
      delay(2000);
      Serial.print("Esperando");
    }
    Serial.println("");
    turnMotorsOffLine();
    esperaChave();
  } else {
    Serial.println("Anda meu filho");
    drive_forward();
  }
  delay(100);
}

void vaiservo() {
  if(ctrlpos) {
    pos += 5;
  } else {
    pos += 5;
  }
  
  if (controle = 35) {
    ctrlpos != ctrlpos;
    controle = 0;
  }
  
  myservo.write(pos);  
}

int pegaValor(int Sensor) {
  int resultado;
  resultado = digitalRead(Sensor);
  Serial.println(resultado,DEC);
  return(resultado);
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
  Serial.println("StopA");
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

void grillo(const int Pin, int vezes) {
  int i;
  for(i = 0; i < vezes; i++) {
    tone(Pin,55,900);
    delay(250);
    noTone(Pin);
    delay(250);  
  }
};

void esperaChave(void) {
  Serial.println("Espera chave 000");
  SoftwareSerial RFID = SoftwareSerial(rxPin,txPin); 
  RFID.begin(2400);
  Serial.println("Espera chave 001");

  if((val = RFID.read()) == 10)
  {   // check for header 
  Serial.println("Espera chave 002");
    bytesread = 0; 
    while(bytesread<10)
    {  // read 10 digit code 
    Serial.println("Espera chave 003");
      val = RFID.read(); 
      if((val == 10)||(val == 13))
      {  // if header or stop bytes before the 10 digit reading 
        break;                       // stop reading 
      } 
      Serial.println("Espera chave 004");
      code[bytesread] = val;         // add the digit           
      bytesread++;                   // ready to read next digit  
    } 
    Serial.println("Espera chave 005");

    if(bytesread == 10)
    {  // if 10 digit read is complete 
      Serial.print("TAG code is: ");   // possibly a good TAG 
      Serial.println(code);            // print the TAG code 
    }
    Serial.println("Espera chave 006");
    bytesread = 0; 
    delay(500);                       // wait for a second
  } 
  Serial.println("Espera chave 007");
};
