#include <SimpleTimer.h>
#include <stdio.h>

// Global SimpleTimer Object
SimpleTimer timer;

// Global Secound Counter
int secs = 0;

void botao_de_desarmar() {
	randomSeed(secs);
	defbutton = random(0,1000);
	botao_estouro = random(0,1000);
	Serial.print("Randon = ");
	Serial.println(defbutton);
	Serial.println(botao_estouro);
	if(defbutton%2 == 0) {
		defbutton = 0;
	} else {
		defbutton = 1;
	}
	
	Serial.print("Botao configurado pra ser o desligador: ");
	String bot = defbutton ?  "Plus" : "Minus";
	Serial.println(bot);
}



// print current arduino "uptime" on the serial port
void DigitalClockDisplay() {
  int h,m,s;
  s = millis() / 1000;
  m = s / 60;
  h = s / 3600;
  s = s - m * 60;
  m = m - h * 60;
  secs += 1;
/*
	Serial.print(h);
  printDigits(m);
  printDigits(s); */
}

//
// utility function for digital clock display:
// prints preceding colon and leading 0
//
void printDigits(int digits) {
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void setup() {
  Serial.begin(9600);
	defbutton = 239;
	botao_estouro = 239;
  
  // Set Buttons
  for (int i = 0; i < 3; i++) 
    pinMode(buttonPin[i], INPUT);
    
  // Set Status Led
  pinMode(ledPin, OUTPUT);  

  // timed actions setup  
  timer.setInterval(1000, DigitalClockDisplay);
	botao_de_desarmar();

	Serial.println("Setup OK");
}

void ctrlButtons() {
	// Button Control
  for (int i = 0; i < 3; i++) {
    reading[i] = digitalRead(buttonPin[i]);
    if (reading[i] != lastButtonState[i]) {    
      lastDebounceTime[i] = millis();
    }
    
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      buttonState[i] = reading[i];
    }
    
    // save state
    lastButtonState[i] = reading[i];
  }
}

void dispara() {
	Serial.println("Dispara");
	digitalWrite(ledPin,HIGH);
	delay(1000);
	digitalWrite(ledPin,LOW);
}

void zera() {
	for(size_t i = 0; i < 3; i++)
	{
		lastButtonState[i] = LOW;   // the previous reading from the input pin
		lastDebounceTime[i] = 0;
		buttonState[i] = LOW;
	}
}

void debuga() {
	Serial.println("Debug...");
	Serial.print("Bomba dispara em ");
	Serial.print(tempoBombaSetup);
	Serial.println(" minutos");
	sprintf(saida, " reset %i - plus %i - minus %i - secs %i - tmpbomba %i", buttonState[0], buttonState[1], buttonState[2], secs, tempoBomba);
  Serial.println(saida);
	Serial.println(defbutton);
	Serial.println(botao_estouro);
}

void goto_setup() {
	zera();
	
	
	botao_de_desarmar();

	setup_session = secs;
  Serial.println("Entering in setup mode");

	Serial.println("While do setup");
	flagMostraRelogio = true;
	while(1) {
		timer.run();
		ctrlButtons();
		
		if(buttonState[PB] == APERTADO) {
			setup_session = secs;
			tempoBombaSetup++;
      Serial.println("Plus pressed");
			delay(APERTO_BOTAO_DELAY);
			debuga();
			zera();
		}
		
		if(buttonState[MB] == APERTADO) {
			setup_session = secs;
			tempoBombaSetup--;
      Serial.println("Minus pressed");
			delay(APERTO_BOTAO_DELAY);
			debuga();
			zera();
		}
		
    if(buttonState[RB] == APERTADO) {
      Serial.println("Reset pressed");
      setup_session = secs - 15; 
			delay(APERTO_BOTAO_DELAY);
			zera();
			break;     
    }

		if(secs > setup_session + 10) {
			Serial.println("Config exit");
			Serial.print("Bomb will fired on ");
			Serial.print(tempoBombaSetup);
      Serial.println(" mins");      
			tempoBomba = tempoBombaSetup; // Save new bomb time
			zera();
      break;
		} 

	}
	tempo();
	Serial.println("Exit setup");
	flagMostraRelogio = false;
}


void goto_limbo() {
  Serial.println("On limbo...");
	delay(3000); // 3 secs
	Serial.println("Exit limbo...");
}

void desliga() {
  digitalWrite(ledPin,LOW);
}

void tempo() {
	for(size_t i = 0; i < 3; ++i)
	{
		digitalWrite(ledPin,HIGH);
		delay(1000);
		digitalWrite(ledPin,LOW);
		delay(1000);
	}
	delay(500);
}

void loop() {
  timer.run();
	ctrlButtons();
	
	if(buttonState[RB] == APERTADO) {
    Serial.println("RESET Button FIRED");
		dispara();
		goto_setup();
	}

  if(buttonState[PB] == APERTADO) {
    Serial.println("Plus Button FIRED");
		debuga();
    if (defbutton) {
      desliga();
    } else {
      secs = tempoBomba;
    }
  }
  
  if(buttonState[MB] == APERTADO) {
    Serial.println("Minus Button FIRED");
		debuga();
    if (!defbutton) {
      desliga();
    } else {
      secs = tempoBomba;
    }
  }
	
		
	if(secs >= tempoBomba*100) {
    Serial.println("Time is UP");
    dispara();
    flagDispara = !flagDispara;
		goto_limbo();
		goto_limbo();
	}
}
