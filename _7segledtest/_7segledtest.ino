// bits representing segments A through G (and decimal point) for numerals 0-9 
const byte numeral[10] = {
//ABCDEFG /dp
B11111101, // 0
B01100001, // 1 
B11011011, // 2
B11110011, // 3 
B01100111, // 4 
B10110111, // 5 
B00111111, // 6 
B11100001, // 7 
B11111111, // 8 
B11100111, // 9
};

// pins for decimal point and each segment
//                          dp,G,F,E,D,C,B,A 
const int segmentPins[8] = { 5,9,8,7,6,4,3,2};

void setup() {
  Serial.begin(9600);
  	for(int i=0; i < 8; i++) {
		pinMode(segmentPins[i], OUTPUT); // set segment and DP pins to output 
	}
}


void loop()
{
	for(int i=0; i < 7; i++) {
  Serial.println(i);
		showDigit(i); delay(1000);
	}
	// the last value if i is 10 and this will turn the display off 
	delay(2000); // pause two seconds with the display off
}

// Displays a number from 0 through 9 on a 7-segment display
// any value not within the range of 0-9 turns the display off
void showDigit( int number) {
	boolean isBitSet;
	for(int segment = 1; segment < 8; segment++) {
		if( number < 0 || number > 9) {
			isBitSet = 0; // turn off all segments 
		} else {
			// isBitSet will be true if given bit is 1
			isBitSet = bitRead(numeral[number], segment); 
		}
		isBitSet = ! isBitSet; // remove this line if common cathode display
		digitalWrite( segmentPins[segment], isBitSet); 
	}
}
