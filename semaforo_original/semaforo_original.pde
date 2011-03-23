// code for traffic light /
const int BTN_PIN = 2; 
const int TRAFFIC_RED_PIN = 24; 
const int TRAFFIC_YELLOW_PIN = 23;
const int TRAFFIC_GREEN_PIN = 22; 
const int PEDESTRIAN_RED_PIN = 29; 
const int PEDESTRIAN_GREEN_PIN = 28; 

int ledPin[]={ TRAFFIC_RED_PIN, TRAFFIC_YELLOW_PIN, TRAFFIC_GREEN_PIN, PEDESTRIAN_RED_PIN, PEDESTRIAN_GREEN_PIN, };

int length = sizeof ledPin/sizeof *ledPin; 
void setup() { 
  for(int i=0;i<length;i++) 
    pinMode(ledPin[i], OUTPUT); 
  pinMode(BTN_PIN,INPUT); 
  } 

void loop() { 
  //int switchValue = digitalRead(2); 
  haltTraffic(); 
  delay(10000); 
  changeGreen(); 
  for(int i=0;i<50;i++){ 
    if(digitalRead(BTN_PIN)==HIGH) 
      break; 
    delay(400); 
  } 
} 

void haltTraffic(){ 
  changeRed(); 
  digitalWrite(TRAFFIC_RED_PIN, HIGH); 
  delay(1000); 
  digitalWrite(PEDESTRIAN_RED_PIN, LOW); 
  digitalWrite(PEDESTRIAN_GREEN_PIN, HIGH); 
} 

void changeRed(){ 
  // private digitalWrite(TRAFFIC_GREEN_PIN, LOW); 
  digitalWrite(TRAFFIC_YELLOW_PIN, HIGH); 
  delay(5000); digitalWrite(TRAFFIC_YELLOW_PIN, LOW); 
} 

void changeGreen(){
  digitalWrite(PEDESTRIAN_GREEN_PIN, LOW); 
  for(int i=0;i<10;i++){ 
    digitalWrite(PEDESTRIAN_RED_PIN, LOW); 
    delay(500); 
    digitalWrite(PEDESTRIAN_RED_PIN, HIGH); 
    delay(500); 
  } 
  delay(1500); 
  digitalWrite(TRAFFIC_RED_PIN, LOW); 
  digitalWrite(TRAFFIC_GREEN_PIN, HIGH); 
}
