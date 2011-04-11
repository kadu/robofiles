// Modified by Worapoht K.
#include <SoftwareSerial.h>

int  val = 0; 
char code[10]; 
int bytesread = 0; 

#define rxPin 0
#define txPin 1
// RFID reader SOUT pin connected to Serial RX pin at 2400bps to pin8

void setup()
{ 
  Serial.begin(9600);  // Hardware serial for Monitor 2400bps
  Serial.println("Teste");
\
  pinMode(2,OUTPUT);       // Set digital pin 2 as OUTPUT to connect it to the RFID /ENABLE pin 
  digitalWrite(2, LOW);    // Activate the RFID reader 
}


void loop()
{ 
  SoftwareSerial RFID = SoftwareSerial(rxPin,txPin); 
  RFID.begin(2400);

  if((val = RFID.read()) == 10)
  {   // check for header 
    bytesread = 0; 
    while(bytesread<10)
    {  // read 10 digit code 
      val = RFID.read(); 
      if((val == 10)||(val == 13))
      {  // if header or stop bytes before the 10 digit reading 
        break;                       // stop reading 
      } 
      code[bytesread] = val;         // add the digit           
      bytesread++;                   // ready to read next digit  
    } 

    if(bytesread == 10)
    {  // if 10 digit read is complete 
      Serial.print("TAG code is: ");   // possibly a good TAG 
      Serial.println(code);            // print the TAG code 
    }
    bytesread = 0; 
    delay(500);                       // wait for a second
  } 
} 
