#include <glcd.h>
#include <glcd_Config.h>

#include "fonts/allFonts.h"
#include "bitmaps/allBitmaps.h"

gText countdownArea =  gText(GLCD.CenterX, GLCD.CenterY,1,1,Arial_14); // text area for countdown digits

void setup() {
  GLCD.Init();
  GLCD.DrawBitmap(ArduinoIcon64x64,32,0);
  delay(2000);
  countdown(3);
  GLCD.SelectFont(System5x7, BLACK); 
}

void  loop() {
  GLCD.ClearScreen();
  GLCD.DrawBitmap(teste02,0,0);
  delay(10000);
  GLCD.ClearScreen();
  GLCD.DrawBitmap(olho_kadu01,0,0);
  delay(10000);
}

void countdown(int count){
  while(count--){  // do countdown  
    countdownArea.ClearArea(); 
    countdownArea.print(count);
    delay(1000);  
  }  
}
