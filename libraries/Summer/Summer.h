/*
||
|| @file Summer.h
|| @version 1.1
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

#ifndef SUMMER_H  
#define SUMMER_H 

#include "WProgram.h"

class Summer{
	public:
		Summer(uint8_t summerPin);
		void setTone(byte tone);
		void setTempo(unsigned int tempo);
		void beep(unsigned int toneFrequency);
		void playTone(unsigned int toneFrequency, byte beats);
	private:
		uint8_t pin;
		unsigned int tempo;
};

#endif 

/*
|| @changelog
|| | 1.0 2009-04-24 - Alexander Brevig : Fixed a bug in the constructor
|| | 1.0 2008-10-23 - Alexander Brevig : Initial Release
|| #
*/
