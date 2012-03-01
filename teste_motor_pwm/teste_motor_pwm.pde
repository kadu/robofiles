//Motor
int motor_left[]    = {9,8};
int motor_right[]   = {11,10};
int motor1en        = 7 ;
int motor2en        = 12;
int veloc;

void setup() {
  Serial.begin(115200);
  pinMode(motor1en, OUTPUT);
  pinMode(motor2en, OUTPUT);
  for(int i=0;i < 2; i++){
    pinMode(motor_left[i],  OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
  delay(5000);
  turnMotorsOnLine();
}

void loop() {
  Serial.println("loop");
  motor_stop();
  delay(1000);
  for(veloc = 60; veloc <= 255; veloc+=10) {
    Serial.print("Velocidade ");
    Serial.println(veloc);
    acertaVeloc(veloc+14,veloc);
    delay(3000);
    motor_stop();
    delay(700);
  }
  delay(10000);
}

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
void drive_forward(int velocidade){
  if(velocidade == 0) {
    digitalWrite(motor_left[0], HIGH);
    digitalWrite(motor_left[1], LOW);
    digitalWrite(motor_right[0], HIGH);
    digitalWrite(motor_right[1], LOW);
  } else {
    analogWrite(motor_left[0], velocidade);
    analogWrite(motor_left[1], LOW);
    analogWrite(motor_right[0], velocidade);
    analogWrite(motor_right[1], LOW);
  }
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

void acertaVeloc(int velocR, int velocL) {
  analogWrite(motor_left[0], velocL);
  analogWrite(motor_left[1], LOW);
  analogWrite(motor_right[0], velocR);
  analogWrite(motor_right[1], LOW);
}

