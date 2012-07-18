#include <SPI.h>
#include <Ethernet.h>

/*
  SD card file dump
 
 This example shows how to read a file from the SD card using the
 SD library and send it over the serial port.
 	
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 
 created  22 December 2010
 
 This example code is in the public domain.
 	 
 */

#include <SD.h>
#include <IniFile.h>

// On the Ethernet Shield, CS is pin 4. Note that even if it's not
// used as the CS pin, the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD library
// functions will not work.
const int chipSelect = 4;
char *fileName = "/net.ini";
const int macLen = 18;
char mac[macLen];

void setup()
{
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  pinMode(53, OUTPUT);
  
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");  
  IniFile ini(fileName);
  if(ini.isOpen()) {
    Serial.println("Arquivo .ini encontrado");
    if(ini.getValue("mac","network", mac, macLen)) {
      Serial.print("network section has an entry mac with value ");
      Serial.write((const uint8_t*)mac, macLen); // not null terminated!
      Serial.println();
    }
  }
}

void loop()
{
}

