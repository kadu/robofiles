/*
 * SimpleTimerAlarmExample.pde
 *
 * Based on usage example for Time + TimeAlarm libraries
 *
 * A timer is called every 15 seconds
 * Another timer is called once only after 10 seconds
 * A third timer is called 10 times.
 *
 */

#include <SimpleTimer.h>

// There must be one global SimpleTimer object.
// More SimpleTimer objects can be created and run,
// although there is little point in doing so.
SimpleTimer timer;
int ledPin = 13;
int state = 0;
int para;
// function to be called repeatedly
void RepeatTask() {
  Serial.println("15 second timer");        
}

// function to be called just once
void OnceOnlyTask() {
  Serial.println("This timer only triggers once");  
}

// function to be called exactly 10 times
void TenTimesTask() {
  static int k = 0;
  k++;
  Serial.print("called ");
  Serial.print(k);
  Serial.println(" / 10 times.");
}

// print current arduino "uptime" on the serial port
void DigitalClockDisplay() {
  int h,m,s;
  s = millis() / 1000;
  m = s / 60;
  h = s / 3600;
  s = s - m * 60;
  m = m - h * 60;
  Serial.print(h);
  printDigits(m);
  printDigits(s);
  Serial.println();
}

//
// utility function for digital clock display:
// prints preceding colon and leading 0
//
void printDigits(int digits) {
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void left_5mins() {
	timer.enable(para);	
}

void left_1min() {
	timer.disable(para);
}

void left_15secs() {
	digitalWrite(ledPin,HIGH);
	delay(300);
	digitalWrite(ledPin,LOW);
	
//	digitalWrite(ledPin,state ? HIGH : LOW);
//	state = !state;
}

void setup() {
  Serial.begin(9600);

  // welcome message
  Serial.println("SimpleTimer Example");
  Serial.println("One timer is triggered every 15 seconds");
  Serial.println("Another timer is set to trigger only once after 10 seconds");
  Serial.println("Another timer is set to trigger 10 times");
  Serial.println();

  // timed actions setup
  //timer.setInterval(15000, RepeatTask);
  //timer.setTimeout(10000, OnceOnlyTask);
  timer.setInterval(1000, DigitalClockDisplay);
	para = timer.setInterval(3000,left_15secs);
	timer.setTimeout(7000, left_1min);
	timer.setTimeout(15000, left_5mins);
//	timer.setInterval(1000,left_15secs);
  //timer.setTimer(1200, TenTimesTask, 10);
}

void loop() {
  // this is where the "polling" occurs
  timer.run();
}
