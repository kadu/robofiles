/*
||
|| @file Summer.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Display the intuitive way of using a Summer when using this Hardware Abstraction class
|| #
||
|| @license
|| | Copyright (c) 2009 Alexander Brevig. All rights reserved.
|| | This code is subject to AlphaLicence.txt
|| | www.alphabeta.alexanderbrevig.com/AlphaLicense.txt
|| #
||
*/

#include <Summer.h>

Summer summer = Summer(9);

void setup() {
  summer.setTempo(300);
}

void loop() {
  summer.playTone(440,1); //A4
  summer.playTone(880,2); //A5
}
