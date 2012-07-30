#include <SimpleTimer.h>
#include <stdio.h>

// segment 
#define A  0
#define B  1
#define C  2
#define D  4
#define E  5
#define Fi 6
#define G  7
#define DP 3

// Pinagens
#define RESET_BUTTON_PIN A3
#define PLUS_BUTTON_PIN A4
#define MINUS_BUTTON_PIN A5
#define BUZZ_PIN A2

// Auxiliar de botoes (Reset Button / Plus Button / Minus Button)
#define RB 0
#define PB 1
#define MB 2

// Auxiliares 
#define APERTADO 1
#define NAO_APERTADO 0
#define iSTART 0
#define iCOUNT 1

// Configuracoes padroes
#define TEMPO_PADRAO_BOMBA 30
#define APERTO_BOTAO_DELAY 700
#define SETUP_SESSION_TIMEOUT 2
#define FIRE_REPEAT_TIME 311 // Numero impar para nao parar ativado


// Variaveis
	// Status Led
	const int ledPin =  13;
	int ledState = HIGH; 
	
  //botoes
  const int buttonPin[3] = { RESET_BUTTON_PIN, PLUS_BUTTON_PIN, MINUS_BUTTON_PIN }; 
	int  buttonState[3];
	int  buttonStateTime[3];
	int  lastButtonState[3] = {LOW, LOW, LOW};   // the previous reading from the input pin
	long lastDebounceTime[3] = {0 , 0, 0}; 

	// Global SimpleTimer Object
	SimpleTimer timer;

	// Global Secound Counter
	 int secs = 0;

  // Default timers
	int tempoBomba = TEMPO_PADRAO_BOMBA;
	int tempoBombaSetup = TEMPO_PADRAO_BOMBA;
	
  // Sessions
	int setup_session        = 0;
	int rb_state_time[2]     = {0,0};
	int pb_state_time[2]     = {0,0};
	int mb_state_time[2]     = {0,0};
	int disarm_state_time[2] = {0,0};
	int left_timmers[4] = {0,0,0, 0};
	
	// Leds
	int pins[2][8];
	int LIGADO = LOW;
	int DESLIGADO = HIGH;
	
	// Helpers
	long debounceDelay = 50;
	int reading[3];
	int defuse_button_rnd;
	int botao_cancela_estouro;
	int flagArmed;
	int flagBuzzer = 0;
	
	int flagw = 0;
//** Fim Variaveis



void status_bomba(int tmp = 0) {
	Serial.print("Tempo da bomba atual : ");
	Serial.print(tmp > 0 ? tmp : tempoBombaSetup);
	Serial.println(" minuto(s)");
}

/**
 * Funcao de  Setup
 */
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
	
	Serial.begin(9600);
	Serial.println("");
	
	flagArmed = false;

	// Set Buttons
	for (int i = 0; i < 3; i++) {
		pinMode(buttonPin[i], INPUT);
	}

	// Set Status Led
	pinMode(ledPin, OUTPUT);
	pinMode(BUZZ_PIN, OUTPUT);  

	// timed actions setup  
	timer.setInterval(1000 , count_secs);
	timer.setInterval(60000, StatusDislpay); // 1 por minuto
	left_timmers[0] = timer.setInterval(30 * 1000, blink);
	left_timmers[1] = timer.setInterval(10 * 1000, blink);
	left_timmers[2] = timer.setInterval(1  * 1000, blink);
	left_timmers[3] = timer.setTimer(   1  *  100, blinkFire,FIRE_REPEAT_TIME);

	zera_variaveis();
	timer.disable(left_timmers[3]);
	configura_botao_de_desarmar();

	Serial.println("Setup OK");
	status_bomba();
	Serial.println("On waiting wall...");
}

/**
 * Funcao responsavel por contar os segundos
 */
void count_secs() {
  secs += 1;
  int countdown_time = tempoBomba - secs;

	if(flagArmed) {
		if(countdown_time < 10) {
			if(!timer.isEnabled(left_timmers[2])) {
				timer.disable(left_timmers[1]);
				timer.enable(left_timmers[2]);
				Serial.println("Timer ativo 2 ");
			}
		} else {
			if(countdown_time < 3 * 60) {
				if(!timer.isEnabled(left_timmers[1])) {
					timer.disable(left_timmers[0]);
					timer.enable(left_timmers[1]);
					Serial.println("Timer ativo 1");
				}
			} else {
				if(countdown_time < 10 *60) {
					if(!timer.isEnabled(left_timmers[0])) {
						timer.enable(left_timmers[0]);
						Serial.println("Timer ativo 0");
					}
				}	
			}
		}
	}
}


/**
 * Funcao responsavel por mostrar o status dos acontecimentos, 1 vez por mimuto
 */
void StatusDislpay() {
	if(flagArmed) {
		int countdown_time = tempoBomba - secs;
		Serial.print("* Status - Restam ");
		if(countdown_time > 0) {
			if(countdown_time < 60)
			{
				Serial.print(countdown_time);
				Serial.println(" segundos");
			} else {
				countdown_time = countdown_time / 60;
				Serial.print(countdown_time+1);
				Serial.println(" minutos");
				//showdigit2(countdown_time);
			}
			Serial.println("");
		}
	}
}

/**
 * Funcao responsavel por pegar um numero randomico e setar qual será o botao que ira
 * desarmar a bomba
 */
void configura_botao_de_desarmar() {
	String auxprint;
	int randaux = random(0,1000);
	randomSeed(secs);
	
	if(randaux%2 == 0) {
		botao_cancela_estouro = 0;
	} else {
		botao_cancela_estouro = 1;
	}

	Serial.print("Botao configurado pra ser o desligador: ");
	auxprint = botao_cancela_estouro ?  "Plus" : "Minus";
	Serial.println(auxprint);
}


/**
 * Funcao responsavel por controlar os Botoes (Leitura)
 */
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


/**
 * Funcao responsavel disparar o Buzzer
 */
void dispara() {
	char pontos[22];
	Serial.println("Disparando");
	digitalWrite(ledPin,HIGH);
	digitalWrite(BUZZ_PIN,HIGH);
	delay(500); sprintf(pontos,"[..                 ]"); Serial.println(pontos);
	delay(500); sprintf(pontos,"[....               ]"); Serial.println(pontos);
	delay(500); sprintf(pontos,"[........           ]"); Serial.println(pontos);
	delay(500); sprintf(pontos,"[............       ]"); Serial.println(pontos);
	delay(500); sprintf(pontos,"[...................]"); Serial.println(pontos);
	digitalWrite(BUZZ_PIN,LOW);
}


/**
 * Funcao responsavel por limpar as variaveis dos botoes
 */
void zera_variaveis() {
	for(size_t i = 0; i < 3; i++)
	{
		lastButtonState[i] = LOW;
		lastDebounceTime[i] = 0;
		buttonState[i] = LOW;
		timer.disable(left_timmers[i]);
	}
	digitalWrite(ledPin,LOW);
	delay(APERTO_BOTAO_DELAY);
}


/**
 * Funcao responsavel por limpar fazer a configuracao do equipamento
 */
void goto_setup() {
	music_setup(8);
	zera_variaveis();
	timer.disable(left_timmers[3]);
	configura_botao_de_desarmar();

  // Controla Sessao
	setup_session = secs;
	Serial.println("");
  Serial.println("Entering in setup mode");

	status_bomba();
	//showdigit2(tempoBombaSetup);

	// Fica no while de configuração até algumas condições de parada ser executado
	while(1) {
		timer.run();
		ctrlButtons();
		
		if(buttonState[PB] == APERTADO)
			tempoBombaSetup++;
		
		if(buttonState[MB] == APERTADO)
			tempoBombaSetup--;

		// Açoes iguais em todo aberto de botao
		if((buttonState[PB] == APERTADO) || (buttonState[MB] == APERTADO)) {
			blinkFino();
			zera_variaveis();
			setup_session = secs;
			Serial.print("Setup : ");
			Serial.println(tempoBombaSetup);
			//showdigit2(tempoBombaSetup);
		}

		// Reset Button
		if(buttonState[RB] == APERTADO) {
			if(rb_state_time[iSTART] == 0) {
				rb_state_time[iSTART] = secs;
				Serial.println("RBF");
			}
			rb_state_time[iCOUNT] = secs;
			if(rb_state_time[iSTART] < secs - SETUP_SESSION_TIMEOUT) {
				Serial.println("RESET Button FIRED");
				zera_variaveis();
				setup_session = secs;
				tempoBomba = tempoBombaSetup;
				status_bomba();
				break;
			}
		} else {
			rb_state_time[iSTART] = 0;
		}
	}
	aguarda_entre_sessoes();
}

void aguarda_entre_sessoes() {
	if(flagw) {
		for(size_t i = 0; i < 8; ++i)
		{
			blink();
		}
		delay(300);
		zera_variaveis();
	}
	
}

void music_setup(int rep) {
	for(size_t i = 0; i < rep; ++i)
	{
		digitalWrite(BUZZ_PIN,HIGH);
		delay(100);
		digitalWrite(BUZZ_PIN,LOW);
		delay(100);
		digitalWrite(BUZZ_PIN,HIGH);
		delay(100);
		digitalWrite(BUZZ_PIN,LOW);
		delay(300);
	}
	delay(1000);
}


/**
 * Function to control armed status
 */
void goto_armed() {
	music_setup(4);
	zera_variaveis();
	configura_botao_de_desarmar();
	status_bomba();
	tempoBomba = secs + tempoBombaSetup * 60 ;
	

  Serial.println("Entering in ARMED mode");

	// Fica no while de configuração até algumas condições de parada ser executado
	while(1) {
		timer.run();
		ctrlButtons();
		
		// Disarm button
		if(buttonState[botao_cancela_estouro ? PB : MB] == APERTADO) {
			if(disarm_state_time[iSTART] == 0) {
				disarm_state_time[iSTART] = secs;
				Serial.println("DISARM PRESSED");
			}
			disarm_state_time[iCOUNT] = secs;
			if(disarm_state_time[iSTART] < secs - SETUP_SESSION_TIMEOUT) {
				Serial.println("DISARMED");
				break;
			}
		} else {
			disarm_state_time[iSTART] = 0;
		}

		if(buttonState[!botao_cancela_estouro ? PB : MB] == APERTADO) {
			Serial.println("FIRE IN THE HOLE!!!");
			//dispara();
			timer.enable(left_timmers[3]);
			flagw = !flagw;
			break;
		}
		
		if(secs > tempoBomba) {
	    Serial.println("Time is UP");
			//dispara();
			timer.enable(left_timmers[3]);
			flagw = !flagw;
			break;
		}
	}
	//aguarda_entre_sessoes();
}

void blink() {
	Serial.println("blink");
	digitalWrite(ledPin,HIGH);
	digitalWrite(BUZZ_PIN,HIGH);
	delay(300);
	digitalWrite(ledPin,LOW);
	digitalWrite(BUZZ_PIN,LOW);
}

void blinkFino() {
	Serial.println("blink");
	digitalWrite(ledPin,HIGH);
	digitalWrite(BUZZ_PIN,HIGH);
	delay(100);
	digitalWrite(ledPin,LOW);
	digitalWrite(BUZZ_PIN,LOW);
}

void blinkFire() {
	digitalWrite(BUZZ_PIN,flagBuzzer ? HIGH : LOW);
	flagBuzzer = !flagBuzzer;
}


/**
 * Loop
 */
void loop() {
	flagArmed = false;
	timer.run();
	ctrlButtons();
	if(flagw) {
		Serial.println("On waiting wall...");
		if(timer.isEnabled(left_timmers[3]))
		{
			Serial.println("Poxa vida entrei no timer e esou ativo");
		} else {
			Serial.println("Esqueceram de me ativar :(");
		}
		digitalWrite(ledPin,HIGH);
		flagw = !flagw;
	}
	
	// Reset Button
	if(buttonState[RB] == APERTADO) {
		if(rb_state_time[iSTART] == 0) {
			rb_state_time[iSTART] = secs;
			Serial.println("RBF");
		}
		rb_state_time[iCOUNT] = secs;
		if(rb_state_time[iSTART] < secs - SETUP_SESSION_TIMEOUT) {
			Serial.println("RESET Button FIRED");
			//aguarda_entre_sessoes();
			goto_setup();	
			music_setup(2);
		}
	} else {
		rb_state_time[iSTART] = 0;
	}
	
	// Plus Button
	if(buttonState[PB] == APERTADO) {
		if(pb_state_time[iSTART] == 0) {
			pb_state_time[iSTART] = secs;
			Serial.println("PBF");
		}
		pb_state_time[iCOUNT] = secs;
		if(pb_state_time[iSTART] < secs - SETUP_SESSION_TIMEOUT) {
			Serial.println("PLUS Button FIRED");
			aguarda_entre_sessoes();
			flagArmed = true;
			goto_armed();
		}
	} else {
		pb_state_time[iSTART] = 0;
	}	
	
	// Minus Button
	if(buttonState[MB] == APERTADO) {
		if(mb_state_time[iSTART] == 0) {
			mb_state_time[iSTART] = secs;
			Serial.println("MBF");
		}
		mb_state_time[iCOUNT] = secs;
		if(mb_state_time[iSTART] < secs - SETUP_SESSION_TIMEOUT) {
			
			Serial.println("Minus Button FIRED waiting");
			aguarda_entre_sessoes();
			flagArmed = true;
			goto_armed();
		}
	} else {
		mb_state_time[iSTART] = 0;
	}
}

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
		//showdigit(0,0);
		//showdigit(1,digit);	
  } else {
		a = digit/10;
		//showdigit(0,a);	
		a = digit - (a * 10);
		//showdigit(1,a);
  }
}
