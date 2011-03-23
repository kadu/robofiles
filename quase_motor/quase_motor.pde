
// Use this code to test your motor with the Arduino board:
// if you need PWM, just use the PWM outputs on the Arduino
// and instead of analogWrite, you should use the analogWrite command
// —————————————————————————  Motors
int motor_left[] = {3,4};
int motor_right[] = {8, 9};
// ————————————————————————— Setup
void setup() {
  Serial.begin(9600);
  // Setup motors
  int i;
  for(i = 0; i < 2; i++){
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
}
// ————————————————————————— Loop
void loop() {
  drive_forward();
  delay(1000);
  motor_stop();
  Serial.println("1");
  drive_backward();
  delay(1000);
  motor_stop();
  Serial.println("2");
  turn_left();
  delay(1000);
  motor_stop();
  Serial.println("3");
  turn_right();
  delay(1000);
  motor_stop();
  Serial.println("4");
  motor_stop();
  delay(1000);
  motor_stop();
  Serial.println("5");
}
// ————————————————————————— Drive
void motor_stop(){
  analogWrite(motor_left[0], LOW);
  analogWrite(motor_left[1], LOW);
  analogWrite(motor_right[0], LOW);
  analogWrite(motor_right[1], LOW);
  delay(25);
}
void drive_forward(){
  analogWrite(motor_left[0], HIGH);
  analogWrite(motor_left[1], LOW);
  analogWrite(motor_right[0], HIGH);
  analogWrite(motor_right[1], LOW);
}
void drive_backward(){
  analogWrite(motor_left[0], LOW);
  analogWrite(motor_left[1], HIGH);
  analogWrite(motor_right[0], LOW);
  analogWrite(motor_right[1], HIGH);
}
void turn_left(){
  analogWrite(motor_left[0], LOW);
  analogWrite(motor_left[1], HIGH);
  analogWrite(motor_right[0], HIGH);
  analogWrite(motor_right[1], LOW);
}
void turn_right(){
  analogWrite(motor_left[0], HIGH);
  analogWrite(motor_left[1], LOW);
  analogWrite(motor_right[0], LOW);
  analogWrite(motor_right[1], HIGH);
}
