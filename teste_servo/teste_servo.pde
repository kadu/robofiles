// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.
#include <Ultrasonic.h>
#include <Servo.h> 
#define ladoDireito 0
#define ladoEsquerdo 1

Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
Ultrasonic ultrasonic(52,53);

int pos = 0;    // variable to store the servo position 
int lado = ladoDireito;
int cmt;

void setup() { 
  Serial.begin(115200);
  Serial.println("Vai comecar");
  myservo.attach(33);  // attaches the servo on pin 9 to the servo object 
} 

void loop() {
  if(lado == ladoDireito) 
    pos+=45;
  else
    pos-=45;
    
  if((pos==0)||(pos==180))
    lado = !lado;  
  
  
  Serial.print(ultrasonic.Ranging(CM));
  Serial.println("cm");
  myservo.write(pos);
  delay(60);
}
