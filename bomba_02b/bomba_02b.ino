#include <SimpleTimer.h>
#include <stdio.h>

// Pinagens
#define RESET_BUTTON_PIN 22
#define PLUS_BUTTON_PIN 23
#define MINUS_BUTTON_PIN 24

// Auxiliar de botoes (Reset Button / Plus Button / Minus Button)
#define RB 0
#define PB 1
#define MB 2

// Auxiliares 
#define APERTADO 1
#define NAO_APERTADO 0

// Configuracoes padroes
#define TEMPO_PADRAO_BOMBA 2
#define APERTO_BOTAO_DELAY 700
#define SETUP_SESSION_TIMEOUT 4


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
//	int tempoBomba = TEMPO_PADRAO_BOMBA * 60;
	int tempoBomba = 120;
	int tempoBombaSetup = TEMPO_PADRAO_BOMBA;
	
  // Sessions
	int setup_session = 0;
	
	// Helpers
	long debounceDelay = 50;
	int reading[3];
	int defuse_button_rnd;
	int botao_cancela_estouro;

//** Fim Variaveis


/**
 * Funcao de  Setup
 */
void setup() {
	Serial.begin(9600);

	// Set Buttons
	for (int i = 0; i < 3; i++) {
		pinMode(buttonPin[i], INPUT);
	}

	// Set Status Led
	pinMode(ledPin, OUTPUT);  

	// timed actions setup  
	timer.setInterval(1000, count_secs);
	timer.setInterval(60000, StatusDislpay); // 1 por minuto
	configura_botao_de_desarmar();

	Serial.println("Setup OK");
}


/**
 * Funcao responsavel por contar os segundos
 */
void count_secs() {
  secs += 1;
	Serial.print("Secs = "); Serial.print(secs); 
	Serial.print("  Tempo bomba = "); Serial.println(tempoBomba);
}


/**
 * Funcao responsavel por mostrar o status dos acontecimentos, 1 vez por mimuto
 */
void StatusDislpay() {
	int countdown_time = tempoBomba - secs;
	Serial.print("* Status - Restam ");
	if(countdown_time < 60)
	{
		Serial.print(countdown_time);
		Serial.println(" segundos");
	} else {
		countdown_time = countdown_time / 60;
		Serial.print(countdown_time);
		Serial.println(" minutos");
	}
	
	Serial.println("");
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
 * Funcao responsavel Disparar o Buzzer
 */
void dispara() {
	char pontos[22];
	Serial.println("Disparando");
	digitalWrite(ledPin,HIGH);
	delay(500); sprintf(pontos,"[..                 ]"); Serial.println(pontos);
	delay(500); sprintf(pontos,"[....               ]"); Serial.println(pontos);
	delay(500); sprintf(pontos,"[........           ]"); Serial.println(pontos);
	delay(500); sprintf(pontos,"[............       ]"); Serial.println(pontos);
	delay(500); sprintf(pontos,"[...................]"); Serial.println(pontos);
	digitalWrite(ledPin,LOW);
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
	}
	delay(APERTO_BOTAO_DELAY);
}


/**
 * Funcao responsavel por limpar fazer a configuracao do equipamento
 */
void goto_setup() {
	zera_variaveis();
	configura_botao_de_desarmar();

  // Controla Sessao
	setup_session = secs;
  Serial.println("Entering in setup mode");

	// Fica no while de configuração até algumas condições de parada ser executado
	while(1) {
		timer.run();
		ctrlButtons();
		
		if(buttonState[PB] == APERTADO)
			tempoBombaSetup++;
		
		if(buttonState[MB] == APERTADO)
			tempoBombaSetup--;

		// Açoes iguais em todo aberto de botao
		if((buttonState[PB] == APERTADO) || (buttonState[MB] == APERTADO) || (buttonState[RB] == APERTADO)) {
			zera_variaveis();
			setup_session = secs;
			Serial.print("Setup : ");
			Serial.println(tempoBombaSetup);
		}
		
		// Reset
    if(buttonState[RB] == APERTADO) {
      setup_session = secs - 15; 
			break;     
    }

		// Controle da sessao
		if(secs > setup_session + SETUP_SESSION_TIMEOUT) {
			tempoBomba = secs + tempoBombaSetup * 60 ;
			
			Serial.print("Bomb will fired on ");
			Serial.print(tempoBombaSetup);
      Serial.println(" mins");      
			zera_variaveis();
      break;
		} 

	}
	aguarda_entre_sessoes();
}

void aguarda_entre_sessoes() {
	for(size_t i = 0; i < 8; ++i)
	{
		digitalWrite(ledPin,HIGH);
		delay(300);
		digitalWrite(ledPin,LOW);
		delay(300);
	}
	delay(300);
}

/**
 * Funcao que para a bomba por um tempo
 */
void goto_limbo() {
  Serial.println("On limbo...");
	delay(5000); // 3 secs
	Serial.println("Exit limbo...");
}

/**
 * Loop
 */
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
    if (botao_cancela_estouro) {
      goto_limbo();
    } else {
      secs = tempoBomba;
    }
  }
  
  if(buttonState[MB] == APERTADO) {
    Serial.println("Minus Button FIRED");
    if (!botao_cancela_estouro) {
      goto_limbo();
    } else {
      secs = tempoBomba;
    }
  }
	
		
	if(secs > tempoBomba) {
    Serial.println("Time is UP");
    dispara();
		goto_limbo();
	}
}