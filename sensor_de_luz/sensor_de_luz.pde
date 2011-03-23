int ledPin = 13;     
int lightPin = 0;       
int val = 0;  
int value1 = 575;        

void setup() {
 pinMode(ledPin, OUTPUT); 
 Serial.begin(9600);        
}

void loop() {
 val = analogRead(lightPin);
 Serial.println(val);
// Serial.print(10,BYTE);
// Serial.print(13,BYTE);
 
 if(val<value1){
   digitalWrite(ledPin, HIGH);
 } else {
   (digitalWrite(ledPin, LOW));
 }
 delay(200);
}
