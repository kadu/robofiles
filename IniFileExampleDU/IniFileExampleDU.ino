#include <SD.h>
//#include <IniFile.h>

#include <SPI.h>
#include <Ethernet.h>
#include <IniFile.h>

// The select pin used for the SD card
#define SD_SELECT 4
#define ETHERNET_SELECT 53

void setup()
{
  // Configure all of the SPI select pins as outputs and make SPI
  // devices inactive, otherwise the earlier init routines may fail
  // for devices which have not yet been configured.
  pinMode(SD_SELECT, OUTPUT);
  digitalWrite(SD_SELECT, HIGH); // disable SD card
  
  pinMode(ETHERNET_SELECT, OUTPUT);
  digitalWrite(ETHERNET_SELECT, HIGH); // disable Ethernet

  const int macLen = 18;
  char mac[macLen];
  int i;

  const char *filename = "net.ini";
  Serial.begin(9600);
  IniFile ini(filename);
  if (ini.isOpen()) {
    Serial.println("Ini file exists");
    if (ini.getValue("mac", "network", mac, macLen)) {
      Serial.print("network section has an entry mac with value ");
      Serial.write((const uint8_t*)mac, macLen); // not null terminated!
      Serial.println();
    }
    else
      Serial.println("Could not read mac from network section");
  }
  else {
    Serial.print("Ini file ");
    Serial.print(filename);
    Serial.println(" does not exist");
  }
}


void loop()
{


}
