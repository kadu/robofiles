//  const int switchPin = 2;    // switch input
  const int motor1Pin = 3;    // H-bridge leg 1 (pin 2, 1A)
  const int motor2Pin = 4;    // H-bridge leg 2 (pin 7, 2A)
  const int enablePin = 9;    // H-bridge enable pin
  const int ledPin = 13;      // LED 

  void setup() {
    // set the switch as an input:
  //  pinMode(switchPin, INPUT); 

    // set all the other pins you're using as outputs:
    pinMode(motor1Pin, OUTPUT); 
    pinMode(motor2Pin, OUTPUT); 
    pinMode(enablePin, OUTPUT);
    pinMode(ledPin, OUTPUT);

    // set enablePin high so that motor can turn on:
    digitalWrite(enablePin, HIGH); 

    // blink the LED 3 times. This should happen only once.
    // if you see the LED blink three times, it means that the module
    // reset itself,. probably because the motor caused a brownout
    // or a short.
    blink(ledPin, 3, 100);
    digitalWrite(enablePin,HIGH);
  }

  void loop() {
    digitalWrite(motor1Pin,LOW);
    digitalWrite(motor2Pin,HIGH);
    delay(2500);
    blink(ledPin, 3, 100);
    digitalWrite(motor1Pin,HIGH);
    digitalWrite(motor2Pin,LOW);

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


