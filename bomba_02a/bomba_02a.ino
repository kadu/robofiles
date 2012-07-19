
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

int flagDispara = 0;   // 0 - desliga /   1 - Liga


// Global SimpleTimer Object
SimpleTimer timer;

// Global Secound Counter
int secs = 0;

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

  // timed actions setup  
  timer.setInterval(1000, DigitalClockDisplay);
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
  Serial.println('Entering in setup mode');
	
	while(1) {
		ctrlButtons();
		
		if(buttonState[PB] == APERTADO) {
			setup_session = 0;
			tempoBombaSetup+=60;
      Serial.println('Plus pressed');
		}
		
		if(buttonState[MB] == APERTADO) {
			setup_session = 0;
			tempoBombaSetup-=60;
      Serial.println('Minus pressed');
		}
		Serial.println(tempoBombaSetup/60);
		
    if(buttonState[RB] == APERTADO) {
      Serial.println('Reset pressed');
      setup_session = secs - 15;      
    }

		if(setup_session + 10 >= secs) {
			Serial.println('Config exit');
			Serial.print('Bomb will fired on ');
			Serial.print(tempoBomba);
      Serial.println('mins');      
			tempoBomba = tempoBombaSetup; // Save new bomb time
      break;
		}
	}
}


void goto_limbo() {
  Serial.println('On limbo...');
	delay(300000); // 5 secs
}

void desliga() {
  a
}

void loop() {
	int defbutton = random(0,1);  // 0 - PB   - 1 - MB
	
  // this is where the "polling" occurs
  timer.run();
	ctrlButtons();
	
	if(buttonState[RB] == APERTADO) {
    Serial.println('RESET Button FIRED');
		tempoBomba == secs;
	}

  if((buttonState[PB] == APERTADO) {
    Serial.println('Plus Button FIRED');
    if (defbutton) {
      desliga();
    } else {
      secs = tempoBomba;
    }
  }
  
  if((buttonState[MB] == APERTADO) {
    Serial.println('Minus Button FIRED');
    if (!defbutton) {
      desliga();
    } else {
      secs = tempoBomba;
    }
  }

		
	if(secs == tempoBomba) {
    Serial.println('Time is UP');
    if (flagDispara) {
      dispara();
      flagDispara = !flagDispara;
    }		
		goto_limbo();
		goto_setup();
	}
}
