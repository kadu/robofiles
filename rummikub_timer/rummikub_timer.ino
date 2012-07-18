#include <glcd.h>
#include "fonts/allFonts.h"         // system and arial14 fonts are used
#include "bitmaps/allBitmaps.h"       // all images in the bitmap dir 

gText countdownArea =  gText(GLCD.CenterX, GLCD.CenterY,1,1,Arial_14); // text area for countdown digits
int backlight = 7;

void setup() {
  pinMode(backlight, OUTPUT);
  analogWrite(backlight, 150);
  // Initialize the GLCD 
  GLCD.Init();
  GLCD.SelectFont(Arial_14);
  GLCD.DrawBitmap(r1,0,0);
  delay(500); GLCD.ClearScreen();
}

void loop() {
  mainmenu();
  GLCD.CursorToXY(0, 14); GLCD.Puts("0.1");
  //GLCD.print(millis()/1000);
}

void countdown(int count){
  while(count--){  // do countdown  
    countdownArea.ClearArea(); 
    countdownArea.print(count);
    delay(1000);  
  }  
}

void mainmenu() {
  GLCD.ClearScreen();
  gText text = gText(textAreaFULL);
  text.SelectFont(Arial_14);
  text.println("linha 1");
  text.println("linha 2");
  text.println("======[ linha 3 ]======");
  text.println("linha 4");
  text.println("linha 5");
  text.println("linha 6");
  
  delay(10000);  
}
