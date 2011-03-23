#include <IRremote.h>
#include <IRremoteInt.h>

/* Map a YK-001 IR Control */
#define rc_Power       16753245
#define rc_Mode        16736925
#define rc_Mute        16769565
#define rc_Rew         16720605
#define rc_FF          16712445
#define rc_Play_Pause  16761405
#define rc_Vol_minus   16769055
#define rc_Vol_plus    16754775
#define rc_EQ          16748655
#define rc_number0     16738455
#define rc_100plus     16750695
#define rc_Back        16756815
#define rc_number1     16724175
#define rc_number2     16718055
#define rc_number3     16743045
#define rc_number4     16716015
#define rc_number5     16726215
#define rc_number6     16734885
#define rc_number7     16728765
#define rc_number8     16730805
#define rc_number9     16732845

// —————————————————————————  Motors
int motor_left[]  = {6,7};
int motor_right[] = {3,2};
int motor1en      = 10;
int motor2en      = 11;

// variaveis para o Controle remoto (IR)
int RECV_PIN = 53;
int led=13;
int last_received;
IRrecv irrecv(RECV_PIN);
decode_results results;

// Setup
void setup(){
  Serial.begin(115200);

  irrecv.enableIRIn(); // inicia o reciver IR
  pinMode(led,OUTPUT); 
  
  // Setup motors
  pinMode(motor1en,OUTPUT); 
  pinMode(motor2en,OUTPUT); 
  for(int i = 0; i < 2; i++){
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
  digitalWrite(motor1en, HIGH); 
  digitalWrite(motor2en, HIGH);
  
  Serial.println("Inicializado");
  motor_stop();
}

// Bib - Pisca o Led
void bip() {
 digitalWrite(led,HIGH);
 delay(100);
 digitalWrite(led,LOW); 
}



// Loop
void loop() {
  if (irrecv.decode(&results)) {
    bip();           // Indica que recebeu algo
    irrecv.resume(); // Recebe o proximo valor
    if(results.value != 4294967295)
      last_received = results.value;
      
    switch(last_received) {
      case rc_Vol_minus : 
	Serial.println("Vol-  - Carrinho dando ré"); 
        drive_backward();
        delay(600);
        motor_stop();
	break;
      case rc_Vol_plus  : 
	Serial.println("Vol+  - Carrinho indo pra frente"); 
        drive_forward();
        delay(600);
        motor_stop();
	break;
      case rc_Rew       : 
	Serial.println("Rew   - Carrinho virando para a esquerda"); 
        turn_left();
        delay(600);
        motor_stop();
	break;
      case rc_FF        : 
	Serial.println("FF    - Carrinho virando para a direita"); 
        turn_right();
        delay(600);
        motor_stop();
	break;   
      case rc_Power     : 
	Serial.println("Power - Carrinho Maluco, girando no proprio eixo"); 
	break; 
      case rc_Mute      :
      	Serial.println("Mute - Para Motor"); 
        motor_stop();
        break;
      case 4294967295   : 
	Serial.println("Repetindo"); break;
      default           : 
	Serial.print("Estranho : "); 
	Serial.println(results.value,DEC); 
        motor_stop();
	break;
    }
  } 
}

// Funcoes do Motor
// ————————————————————————— Drive
void motor_stop(){
  Serial.println("StopA");
  digitalWrite(motor_left[0], HIGH);
  digitalWrite(motor_left[1], HIGH);
  digitalWrite(motor_right[0], HIGH);
  digitalWrite(motor_right[1], HIGH);
  
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], LOW);
  
}
void drive_forward(){
  digitalWrite(motor_left[0], HIGH);
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_right[0], HIGH);
  digitalWrite(motor_right[1], LOW);
}
void drive_backward(){
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], HIGH);
  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], HIGH);
}
void turn_left(){
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], HIGH);
  digitalWrite(motor_right[0], HIGH);
  digitalWrite(motor_right[1], LOW);
}
void turn_right(){
  digitalWrite(motor_left[0], HIGH);
  digitalWrite(motor_left[1], LOW);
  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], HIGH);
}
