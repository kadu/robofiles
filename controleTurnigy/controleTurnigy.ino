#include <Servo.h>

//canais do receptor
unsigned long channel1 = 0;
unsigned long channel2 = 0; 
unsigned long channel3 = 0;
unsigned long channel4 = 0;
unsigned long channel5 = 0;
unsigned long channel6 = 0;
unsigned long channel7 = 0;
unsigned long channel8 = 0;
unsigned long channel9 = 0;

//Arma o Esc
#define val_to_arm_motors 20;
#define val_to_power_motors 1;

//Variável que fará a compensação de cada motor com relação aos demais
#define val_power_motor_right 2;
#define val_power_motor_left  2;
#define val_power_motor_front 2;
#define val_power_motor_back  2;        

int speed;

void setup()
{
    delay (3000);
    Serial.begin(9600);
    Serial.println("Speed    Angle    Channel1    Channel2    Channel3    Channel4    Channel5    Channel6    Channel7    Channel8    Channel9");
    pinMode (30, INPUT);
    pinMode (29, INPUT);
    pinMode (28, INPUT);
    pinMode (27, INPUT);
    pinMode (26, INPUT);
    pinMode (25, INPUT);
    pinMode (24, INPUT);
    pinMode (23, INPUT);
    pinMode (22, INPUT);
    
    delay(1000);
//    motorTraseiro.attach(6);
//    motorFrontal.attach(9);
//    motorDireita.attach(11);
//    motorEsquerda.attach(10);
//    arm();
}


void arm(){
  // arm the speed controller, modify as necessary for your ESC  
  speed = val_to_arm_motors;
  int angle = map(speed, 0, 100, 20, 180); //map(_speed, 110, 180, 0, 180);
  delay(2500); //delay 2,5 seconds,  some speed controllers may need longer
}


//retorna o sinal lido em todos os canais do Rádio Controle
void checkTransmitter()
{
  Serial.println("checando");
  channel9 = (pulseIn (30, HIGH, 100000))/10; 
  channel8 = (pulseIn (29, HIGH, 100000))/10; 
  channel7 = (pulseIn (28, HIGH, 100000))/10; 
  channel6 = (pulseIn (27, HIGH, 100000))/10; 
  channel5 = (pulseIn (26, HIGH, 100000))/10; 
  channel4 = (pulseIn (25, HIGH, 100000))/10; 
  channel3 = (pulseIn (24, HIGH, 100000))/10; 
  channel2 = (pulseIn (23, HIGH, 100000))/10; 
  channel1 = (pulseIn (22, HIGH, 100000))/10; 
}

/*
 1- Side Left  - esquerda
 2- Side Right - direita
 3- Side Front - frente
 4- Side Back  - traz
*/
void turnSide(int side, int speed)
{
  int angle = map(speed, 0, 100, 20, 180);
  Serial.print(speed);
  Serial.print("        ");
  Serial.print(angle);
  Serial.print("        ");
  Serial.print(channel1);
  Serial.print("        ");
  Serial.print(channel2);
  Serial.print("        ");
  Serial.print(channel3);
  Serial.print("        ");
  Serial.print(channel4);
  Serial.print("        ");
  Serial.print(channel5);
  Serial.print("        ");
  Serial.print(channel6);
  Serial.print("        ");
  Serial.print(channel7);
  Serial.print("        ");
  Serial.print(channel8);
  Serial.print("        ");
  Serial.print(channel9);
  Serial.println("");
}

void loop()
{
    checkTransmitter();//check the data being received by the transmitter.
    
    Serial.println ("*******************Comando: Subida/Descida ********************");//if we decrease altitude we should check for landing, and slow our decent when we get close to the ground.
    //Filtrando o canal 2, para que a leitura, seja sempre um divisível por 10 somado a 5. Faz com que a qualidade da leitura melhore e os motores fiquem mais estáveis.
    speed = (((channel2 - 90)/5)*5);

    //**************movimentos em diagonal**************
    
    //verifica diagonal frente->esquerda
    if((channel3 > 90 && channel3 < 130) && (channel1>90 && channel1<130))
      turnSide(6,speed);
      //verifica diagonal traz->esquerda
    else if ((channel3 > 90 && channel3 < 130)&&(channel1>=150 && channel1<200))
      turnSide(7,speed);
      //verifica diagonal frente->direita
    else if((channel1>90 && channel1<130)&&(channel3 >= 150 && channel3 < 200))
      turnSide(8,speed);
      //verifica diagonal traz->direita
    else if((channel1>90 && channel1<130) && (channel1>=150 && channel1<200))
      turnSide(9,speed);

    //**************movimentos laterais simples**************
    //virar para esquerda
    if(channel3 > 90 && channel3 < 130)
      turnSide(1,speed);
      //virar para a direita
    else if(channel3 >= 150 && channel3 < 200)
      turnSide(2,speed);
    //ir pra frente
    if(channel1>90 && channel1<130)
      turnSide(3,speed);
    //ir para traz
    else if(channel1>=150 && channel1< 200)
      turnSide(4,speed);

    // ********************Estabilizar*****************
    if(channel1>=130 && channel1<150 && channel3>=130 && channel3<150)
      turnSide(5,speed);   
}
