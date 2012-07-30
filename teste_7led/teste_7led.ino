/*
7 LED segments demo counter program from electronicsblog.net.
If You share/use this code elsewhere on the internet please mention this code source.
*/

// segment 
#define A  0
#define B  1
#define C  2
#define D  4
#define E  5
#define Fi 6
#define G  7
#define DP 3

int pins[2][8];
int LIGADO = LOW;
int DESLIGADO = HIGH;

// functions to display digits

void digit0 (int display = 0) {
	// for 0 needed to turn ON F A B C D E segments, so:
	digitalWrite(pins[display][A],  LIGADO);
	digitalWrite(pins[display][B],  LIGADO);
	digitalWrite(pins[display][C],  LIGADO);
	digitalWrite(pins[display][D],  LIGADO);
	digitalWrite(pins[display][E],  LIGADO);
	digitalWrite(pins[display][Fi], LIGADO);
	digitalWrite(pins[display][G],  DESLIGADO);
};

void digit1 (int display = 0) {
	digitalWrite(pins[display][A],  DESLIGADO);
	digitalWrite(pins[display][B],  LIGADO);
	digitalWrite(pins[display][C],  LIGADO);
	digitalWrite(pins[display][D],  DESLIGADO);
	digitalWrite(pins[display][E],  DESLIGADO);
	digitalWrite(pins[display][Fi], DESLIGADO);
	digitalWrite(pins[display][G],  DESLIGADO);
};

void digit2 (int display = 0) {
	digitalWrite(pins[display][A],  LIGADO);
	digitalWrite(pins[display][B],  LIGADO);
	digitalWrite(pins[display][C],  DESLIGADO);
	digitalWrite(pins[display][D],  LIGADO);
	digitalWrite(pins[display][E],  LIGADO);
	digitalWrite(pins[display][Fi], DESLIGADO);
	digitalWrite(pins[display][G],  LIGADO);
};

void digit3 (int display = 0) {
	digitalWrite(pins[display][A],  LIGADO);
	digitalWrite(pins[display][B],  LIGADO);
	digitalWrite(pins[display][C],  LIGADO);
	digitalWrite(pins[display][D],  LIGADO);
	digitalWrite(pins[display][E],  DESLIGADO);
	digitalWrite(pins[display][Fi], DESLIGADO);
	digitalWrite(pins[display][G],  LIGADO);
};

void digit4 (int display = 0) {
	digitalWrite(pins[display][A],  DESLIGADO);
	digitalWrite(pins[display][B],  LIGADO);
	digitalWrite(pins[display][C],  LIGADO);
	digitalWrite(pins[display][D],  DESLIGADO);
	digitalWrite(pins[display][E],  DESLIGADO);
	digitalWrite(pins[display][Fi], LIGADO);
	digitalWrite(pins[display][G],  LIGADO);
};

void digit5 (int display = 0) {
	digitalWrite(pins[display][A],  LIGADO);
	digitalWrite(pins[display][B],  DESLIGADO);
	digitalWrite(pins[display][C],  LIGADO);
	digitalWrite(pins[display][D],  LIGADO);
	digitalWrite(pins[display][E],  DESLIGADO);
	digitalWrite(pins[display][Fi], LIGADO);
	digitalWrite(pins[display][G],  LIGADO);
};

void digit6 (int display = 0) {
	digitalWrite(pins[display][A],  LIGADO);
	digitalWrite(pins[display][B],  DESLIGADO);
	digitalWrite(pins[display][C],  LIGADO);
	digitalWrite(pins[display][D],  LIGADO);
	digitalWrite(pins[display][E],  LIGADO);
	digitalWrite(pins[display][Fi], LIGADO);
	digitalWrite(pins[display][G],  LIGADO);
};

void digit7 (int display = 0) {
	digitalWrite(pins[display][A],  LIGADO);
	digitalWrite(pins[display][B],  LIGADO);
	digitalWrite(pins[display][C],  LIGADO);
	digitalWrite(pins[display][D],  DESLIGADO);
	digitalWrite(pins[display][E],  DESLIGADO);
	digitalWrite(pins[display][Fi], DESLIGADO);
	digitalWrite(pins[display][G],  DESLIGADO);
}

void digit8 (int display = 0) {
	digitalWrite(pins[display][A],  LIGADO);
	digitalWrite(pins[display][B],  LIGADO);
	digitalWrite(pins[display][C],  LIGADO);
	digitalWrite(pins[display][D],  LIGADO);
	digitalWrite(pins[display][E],  LIGADO);
	digitalWrite(pins[display][Fi], LIGADO);
	digitalWrite(pins[display][G],  LIGADO);
};

void digit9 (int display = 0) {
	digitalWrite(pins[display][A],  LIGADO);
	digitalWrite(pins[display][B],  LIGADO);
	digitalWrite(pins[display][C],  LIGADO);
	digitalWrite(pins[display][D],  LIGADO);
	digitalWrite(pins[display][E],  DESLIGADO);
	digitalWrite(pins[display][Fi], LIGADO);
	digitalWrite(pins[display][G],  LIGADO);
};

void dot (int display = 0, int status = DESLIGADO) {
	digitalWrite(pins[display][DP], status);
}

//function to display digit from inputed int
void showdigit (int dsp = 0, int digit = -1) {
	switch (digit) {
		case 0: digit0(dsp); break;
		case 1: digit1(dsp); break;
		case 2: digit2(dsp); break;
		case 3: digit3(dsp); break;
		case 4: digit4(dsp); break;
		case 5: digit5(dsp); break;
		case 6: digit6(dsp); break;
		case 7: digit7(dsp); break;
		case 8: digit8(dsp); break;
		case 9: digit9(dsp); break;
		default:
		break;
	};
}

void showdigit2(int digit) {
	char resposta[3];
	int a;
	sprintf(resposta, "%i", digit);
  if(strlen(resposta) == 1) {
		showdigit(0,0);
		showdigit(1,digit);	
  } else {
		a = digit/10;
		showdigit(0,a);	
		a = digit - (a * 10);
		showdigit(1,a);
  }
}

void setup() {	
	pins[0][G]  = 7;
	pins[0][A]  = 0;
	pins[0][B]  = 1;
	pins[0][E]  = 5;
	pins[0][D]  = 4;
	pins[0][C]  = 2;
	pins[0][DP] = 3;
	pins[0][Fi]  = 6;
	
	pins[1][G]  = 10;
	pins[1][A]  = 13;
	pins[1][B]  = A0;
	pins[1][E]  = 8;
	pins[1][D]  = 9;
	pins[1][C]  = 12;
	pins[1][DP] = A1;
	pins[1][Fi]  = 11;
	
	for(size_t i = 0; i < 2; i++)
	{
		for(size_t j = 0; j < 8; j++)
		{
			pinMode(pins[i][j], OUTPUT);
		}
	}
};

void loop () {
	for (int i=0;i<100;i++) { //counting from 0 to 9
		showdigit2(i);
		delay (1000); // 1000ms= 1s delay

		if (i%2) { 
			dot();
		} else {
			dot(0,LIGADO);
		};
	};
};
