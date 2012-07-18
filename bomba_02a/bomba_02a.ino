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
#include <stdio.h>

// Buttons
#define RESET_BUTTON 22
#define PLUS_BUTTON 23
#define MINUS_BUTTON 24
#define RB 0
#define PB 1
#define MB 2
#define APERTADO 1
#define NAO_APERTADO 0

const int buttonPin[3] = { RESET_BUTTON, PLUS_BUTTON, MINUS_BUTTON }; 

// Status Led
const int ledPin =  13;

// Helpers
int ledState = HIGH; 
int buttonState[3];
int buttonStateTime[3];
int lastButtonState[3] = {LOW, LOW, LOW};   // the previous reading from the input pin
long lastDebounceTime[3] = {0 , 0, 0}; 
long debounceDelay = 50;
char saida[20];
int reading[3];

int tempoBomba = 1800; // 30mins
int tempoBombaSetup = 1800;

int setup_session = 0;


// Global SimpleTimer Object
SimpleTimer timer;

// Global Secound Counter
int secs = 0;

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
  //Serial.println();
  
	secs += 1;
  sprintf(saida, " %i - %i - %i", buttonState[0], buttonState[1], buttonState[2]);
  Serial.println(saida);    
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

void setup() {
  Serial.begin(9600);
  
  // Set Buttons
  for (int i = 0; i < 3; i++) 
    pinMode(buttonPin[i], INPUT);
    
  // Set Status Led
  pinMode(ledPin, OUTPUT);  

  // welcome message
  Serial.println("SimpleTimer Example");
  Serial.println("One timer is triggered every 15 seconds");
  Serial.println("Another timer is set to trigger only once after 10 seconds");
  Serial.println("Another timer is set to trigger 10 times");
  Serial.println();

  // timed actions setup
  timer.setInterval(15000, RepeatTask);
  timer.setTimeout(10000, OnceOnlyTask);
  timer.setInterval(1000, DigitalClockDisplay);
  timer.setTimer(1200, TenTimesTask, 10);
}

void ctrlButtons() {
	// Button Control
  for (int i = 0; i < 3; i++) {
    reading[i] = digitalRead(buttonPin[i]);
    if (reading[i] != lastButtonState[i]) {    
      lastDebounceTime[i] = millis();
    }
    
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      buttonState[i] = reading[i];
    }
    
    // save state
    lastButtonState[i] = reading[i];
  }
}

void dispara() {
	digitalWrite(ledPin,HIGH);
	delay(5000);
	digitalWrite(ledPin,LOW);
}

void goto_setup() {
	setup_session = secs;
	
	while(1) {
		ctrlButtons();
		
		if(buttonState[PB] == APERTADO) {
			setup_session = 0;
			tempoBombaSetup+=60;
		}
		
		if(buttonState[MB] == APERTADO) {
			setup_session = 0;
			tempoBombaSetup-=60;
		}
		Serial.println(tempoBombaSetup/60);
		
		if(setup_session + 10 >= secs) {
			break;
			Serial.println('Saindo da configuracao');
			Serial.print('Bomba aramada para ');
			Serial.println(tempoBomba);
			tempoBomba = tempoBombaSetup;
		}
			
	}
}


void goto_limbo() {
	delay(300000); // 5 secs
}

void loop() {
	int defbutton = random(1,2);
	
  // this is where the "polling" occurs
  timer.run();
	ctrlButtons();
	
	if(buttonState[RB] == APERTADO) {
		tempoBomba == secs;
	}
	
	if(buttonState[defbutton] == APERTADO) {
		//desliga_bomba();
		goto_limbo();
		goto_setup();
	}
		
	if(secs == tempoBomba) {
		dispara();
		goto_limbo();
		goto_setup();
	}
}
