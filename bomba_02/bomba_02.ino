#include <stdio.h>

const int buttonPin[3] = { 22, 23, 24 }; 
const int ledPin =  13;

int ledState = HIGH; 
int buttonState[3];
int lastButtonState[3] = {LOW, LOW, LOW};   // the previous reading from the input pin

long lastDebounceTime[3] = {0 , 0, 0}; 
long debounceDelay = 50;

char saida[20];

int reading[3];

void setup() {
  for (int i = 0; i < 3; i++) 
    pinMode(buttonPin[i], INPUT);
    
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
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

  sprintf(saida, "%i - %i - %i", buttonState[0], buttonState[1], buttonState[2]);
  Serial.println(saida);
}
