/*
  const int motor1Pin = 6;    // H-bridge leg 1 (pin 2, 1A)
  const int motor2Pin = 7;    // H-bridge leg 2 (pin 7, 2A)
  const int enablePin = 10;    // H-bridge enable pin
  
  const int motor3Pin = 2;    // H-bridge leg 1 (pin 2, 1A)
  const int motor4Pin = 3;    // H-bridge leg 2 (pin 7, 2A)
  const int enable2Pin = 11;    // H-bridge enable pin
  */


int motor_left[]  = {6,7};
int motor_right[] = {3,2};
int motor1en      = 10;
int motor2en      = 11;  
int contador;
  
  
  
  const int ledPin = 13;      // LED 

  void setup() {
    // set all the other pins you're using as outputs:
    Serial.begin(115200);

    pinMode(motor1en,OUTPUT); 
    pinMode(motor2en,OUTPUT); 
    for(int i = 0; i < 2; i++){
      pinMode(motor_left[i], OUTPUT);
      pinMode(motor_right[i], OUTPUT);
    }
    
    Serial.println("Comecando em 10 secs");
    


    // blink the LED 3 times. This should happen only once.
    // if you see the LED blink three times, it means that the module
    // reset itself,. probably because the motor caused a brownout
    // or a short.
    blink(ledPin, 7, 1000);
    blink(ledPin, 7,  425);  
    liga();
  }
  
  
  void loop() {

    blink(ledPin,2, 900);
    drive_forward();
    delay(4000);
    blink(ledPin,2, 1000);
    motor_stop();
    
    delay(1000);
    blink(ledPin,2, 900);
    drive_backward();
    
    delay(3000);motor_stop();
    blink(ledPin,2, 900);
    turn_left();
    
    delay(560);motor_stop();
    blink(ledPin,2, 900);
    drive_forward();
    
    delay(10000);motor_stop();
    blink(ledPin,2, 900);
    turn_left();
  
    delay(560);motor_stop();
    blink(ledPin,2, 900);
    
    motor_stop();
    
    
    /*
    drive_forward();
    delay(1000);  
    turn_left();
    delay(560);
    motor_stop();
    blink(ledPin, 5, 100);
    turn_right();
    delay(560);
    motor_stop();    */
    
    
    desliga();
    delay(20000);
    
    
    /*contador = 1; 
    while(contador < 3) {      
      blink(ledPin, 3, 100);
      delay(1000); drive_forward();
      delay(1000); turn_left();
      delay(1000); drive_forward();
      delay(1000); turn_right();
      delay(1000); drive_forward();
      delay(1000); turn_right();
      delay(1000); drive_forward();
      delay(1000); turn_right();
      delay(1000); drive_forward();
      delay(1000); turn_left();
      delay(1000); motor_stop();
      delay(1000); drive_backward();      
      delay(5000);
      blink(ledPin, 5, 400); 
      contador++;
    } */
  }

  /*
    blinks an LED
   */
  void blink(int whatPin, int howManyTimes, int milliSecs) {
    int i = 0;
    for ( i = 0; i < howManyTimes; i++) {
      digitalWrite(whatPin, HIGH);
      delay(milliSecs/2);
      digitalWrite(whatPin, LOW);
      delay(milliSecs/2);
    }
  }
  
void liga(void) {
  digitalWrite(motor1en, HIGH); 
  digitalWrite(motor2en, HIGH);
}
void desliga(void) {
  digitalWrite(motor1en, LOW); 
  digitalWrite(motor2en, LOW);
}

// Funcoes do Motor
// ————————————————————————— Drive
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

void  turn_right(){
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], HIGH);
  digitalWrite(motor_right[0], HIGH);
  digitalWrite(motor_right[1], LOW);
}
void turn_left(){
  digitalWrite(motor_left[0], HIGH);
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], HIGH);
};
