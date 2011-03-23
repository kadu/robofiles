int ledPin = 13;     
int irPin = 0;       
int val = 0;  
        

void setup() {
 pinMode(ledPin, OUTPUT); 
 Serial.begin(9600);        
}

void loop() {
 val = analogRead(irPin);
 Serial.println(val);
// Serial.print(10,BYTE);
// Serial.print(13,BYTE);
 delay(200);
}
