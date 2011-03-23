#include <IRremote.h>

int RECV_PIN = 53;
int led=13;
IRrecv irrecv(RECV_PIN);

decode_results results;
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(led,OUTPUT);
}
void bip() {
 digitalWrite(led,HIGH);
 delay(100);
 digitalWrite(led,LOW); 
}
void loop() {
  if (irrecv.decode(&results)) {
    //Serial.println(results.value);
    bip();
    irrecv.resume(); // Receive the next value
    switch(results.value) {
      case 16753245 : Serial.println("Power"); break;
      case 16736925 : Serial.println("Mode"); break;
      case 16769565 : Serial.println("Mute"); break;
      case 16720605 : Serial.println("Rew"); break;
      case 16712445 : Serial.println("FF"); break;
      case 16761405 : Serial.println("Play/Pause"); break;
      case 16769055 : Serial.println("Vol-"); break;
      case 16754775 : Serial.println("Vol+"); break;
      case 16748655 : Serial.println("EQ"); break;
      case 16738455 : Serial.println("0"); break;
      case 16750695 : Serial.println("100+"); break;
      case 16756815 : Serial.println("Back"); break;
      case 16724175 : Serial.println("1"); break;
      case 16718055 : Serial.println("2"); break;
      case 16743045 : Serial.println("3"); break;
      case 16716015 : Serial.println("4"); break;
      case 16726215 : Serial.println("5"); break;
      case 16734885 : Serial.println("6"); break;
      case 16728765 : Serial.println("7"); break;
      case 16730805 : Serial.println("8"); break;
      case 16732845 : Serial.println("9"); break;
      default :       Serial.print("Estranho"); Serial.println(results.value,DEC); break;
    }
  }
}


