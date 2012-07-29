/*
7 LED segments demo counter program from electronicsblog.net.
If You share/use this code elsewhere on the internet please mention this code source.
*/

// segment | Arduino board PIN number

#define G 7
#define A 0
#define B 1
#define E 5
#define D 4
#define C 2
#define DP 3

int F = 6;
int VAI = LOW;

// functions to display digits

void digit0 () {
// for 0 needed to turn ON F A B C D E segments, so:

digitalWrite(A, VAI);
digitalWrite(B, VAI);
digitalWrite(C, VAI);
digitalWrite(D, VAI);
digitalWrite(E, VAI);
digitalWrite(F, VAI);
digitalWrite(G, HIGH);

};

void digit1 () {

digitalWrite(A,HIGH);
digitalWrite(B, VAI);
digitalWrite(C, VAI);
digitalWrite(D, HIGH);
digitalWrite(E, HIGH);
digitalWrite(F, HIGH);
digitalWrite(G, HIGH);
};

void digit2 () {

digitalWrite(A,VAI);
digitalWrite(B, VAI);
digitalWrite(C, HIGH);
digitalWrite(D, VAI);
digitalWrite(E, VAI);
digitalWrite(F, HIGH);
digitalWrite(G, VAI);
};

void digit3 () {

digitalWrite(A, VAI);
digitalWrite(B, VAI);
digitalWrite(C, VAI);
digitalWrite(D, VAI);
digitalWrite(E, HIGH);
digitalWrite(F, HIGH);
digitalWrite(G, VAI);
};

void digit4 () {

digitalWrite(A,HIGH);
digitalWrite(B, VAI);
digitalWrite(C, VAI);
digitalWrite(D, HIGH);
digitalWrite(E, HIGH);
digitalWrite(F, VAI);
digitalWrite(G, VAI);
};

void digit5 () {

digitalWrite(A,VAI);
digitalWrite(B, HIGH);
digitalWrite(C, VAI);
digitalWrite(D, VAI);
digitalWrite(E, HIGH);
digitalWrite(F, VAI);
digitalWrite(G, VAI);
};

void digit6 () {

digitalWrite(A,VAI);
digitalWrite(B, HIGH);
digitalWrite(C, VAI);
digitalWrite(D, VAI);
digitalWrite(E, VAI);
digitalWrite(F, VAI);
digitalWrite(G, VAI);
};

void digit7 () {

digitalWrite(A,VAI);
digitalWrite(B, VAI);
digitalWrite(C, VAI);
digitalWrite(D, HIGH);
digitalWrite(E, HIGH);
digitalWrite(F, HIGH);
digitalWrite(G, HIGH);
}

void digit8 () {

digitalWrite(A, VAI);
digitalWrite(B, VAI);
digitalWrite(C, VAI);
digitalWrite(D, VAI);
digitalWrite(E, VAI);
digitalWrite(F, VAI);
digitalWrite(G, VAI);

};

void digit9 () {

digitalWrite(A,VAI);
digitalWrite(B, VAI);
digitalWrite(C, VAI);
digitalWrite(D, VAI);
digitalWrite(E, HIGH);
digitalWrite(F, VAI);
digitalWrite(G, VAI);

};

//function to display digit from inputed int

void showdigit (int digit)

{

switch (digit) {

case 0:
digit0 ();
break;

case 1:
digit1 ();
break;

case 2:
digit2 ();
break;

case 3:
digit3 ();
break;

case 4:
digit4 ();
break;

case 5:
digit5 ();
break;

case 6:
digit6 ();
break;

case 7:
digit7 ();
break;

case 8:
digit8 ();
break;

case 9:
digit9 ();
break;

default:

break;

};

}

void setup()

{

pinMode(A, OUTPUT);
pinMode(B, OUTPUT);
pinMode(C, OUTPUT);
pinMode(D, OUTPUT);
pinMode(E, OUTPUT);
pinMode(F, OUTPUT);
pinMode(G, OUTPUT);
pinMode(DP, OUTPUT);

};
void loop ()

{

for (int i=0;i<10;i++) { //counting from 0 to 9

showdigit(i);

delay (1000); // 1000ms= 1s delay

if (i%2) { digitalWrite(DP, HIGH); }

else {digitalWrite(DP, LOW); };

};


};
