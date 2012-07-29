#ifndef Soda_h
#define Soda_h

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class Soda {
private:
	const byte numeral[10];
	const int segmentPins[8];
public:
	void pins(int a, int b, int c, int d, int e, int f, int g, int dp);
	void setup();
	void write(int number);
}

#endif