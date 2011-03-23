/*
||
|| @file Summer.cpp
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Provide an easy way of making summers
|| #
||
|| @license
|| | Copyright (c) 2009 Alexander Brevig. All rights reserved.
|| | This code is subject to AlphaLicence.txt
|| | www.alphabeta.alexanderbrevig.com/AlphaLicense.txt
|| #
||
*/

//include the class definition
#include "Summer.h"

/*
|| <<constructor>>
|| Parameter pin:int8_t sets the pin that the summer is connected to
*/
Summer::Summer(uint8_t summerPin){
	this->pin=summerPin;
	this->tempo=200;
	pinMode(this->pin,OUTPUT);
}

/*
|| Set a tone using PWM
*/
void Summer::setTone(byte tone){
	if(tone>0){
		analogWrite(this->pin,tone);
	}else digitalWrite(this->pin,0);
}

/*
|| Set the current tempo
*/
void Summer::setTempo(unsigned int tempo){
	this->tempo=tempo;
}

/*
|| Beep with given freq, for given beats at given tempo
*/
void Summer::beep(unsigned int toneFrequency) {
  playTone(toneFrequency,1);
}

/*
|| Beep with given freq, for given beats at given tempo
*/
void Summer::playTone(unsigned int toneFrequency, byte beats) {
  beats*=tempo;
  int tone = (1000000 / toneFrequency)/2; //recalculate frequency to pause value between pulses
  for (long i = 0; i < beats * 1000L; i += tone * 2) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(pin, LOW);
    delayMicroseconds(tone);
  }
}

/*
|| @changelog
|| | 2008-10-23 - Alexander Brevig : Initial Release
|| #
*/