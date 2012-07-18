/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);  
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  digitalWrite(6,HIGH);
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  delay(5000);              // wait for a second
  digitalWrite(7, HIGH);
  digitalWrite(6,LOW);
  digitalWrite(9,LOW);
  
  // set the LED off
  delay(1500);              // wait for a second
  digitalWrite(8, HIGH);
  digitalWrite(7,LOW);
  digitalWrite(10,HIGH);
  delay(3500);              // wait for a second
}
