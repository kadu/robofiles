unsigned long channel1 = 0;
unsigned long channel2 = 0; 
unsigned long channel3 = 0;
unsigned long channel4 = 0;
unsigned long channel5 = 0;
unsigned long channel6 = 0;
unsigned long channel7 = 0;
unsigned long channel8 = 0;
unsigned long channel9 = 0;
int x = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup");

  pinMode (30, INPUT);
  pinMode (29, INPUT);
  pinMode (28, INPUT);
  pinMode (27, INPUT);
  pinMode (26, INPUT);
  pinMode (25, INPUT);
  pinMode (24, INPUT);
  pinMode (23, INPUT);
  pinMode (22, INPUT);
  Serial.println("Pinos setados");
  Serial.println("Valores padrao");
  Serial.println("+---------------------------------------+");
  Serial.println("| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |");
  Serial.println("+---------------------------------------+");
}

void imprime() {
  String linha = "|";
  linha += channel1; linha += " |";
  linha += channel2; linha += " |";
  linha += channel3; linha += " |";
  linha += channel4; linha += " |";
  linha += channel5; linha += " |";
  linha += channel6; linha += " |";
  linha += channel7; linha += " |";
  linha += channel8; linha += " |";
  linha += channel9; linha += " |";
  Serial.println(linha);
}

void loop() {
  int i = 1;
  x++;
  Serial.print(x);
  Serial.print("  ");
//  Serial.println("loop");
  channel9 = (pulseIn (30, HIGH, 100000))/i; 
  channel8 = (pulseIn (29, HIGH, 100000))/i; 
  channel7 = (pulseIn (28, HIGH, 100000))/i; 
  channel6 = (pulseIn (27, HIGH, 100000))/i; 
  channel5 = (pulseIn (26, HIGH, 100000))/i; 
  channel4 = (pulseIn (25, HIGH, 100000))/i; 
  channel3 = (pulseIn (24, HIGH, 100000))/i; 
  channel2 = (pulseIn (23, HIGH, 100000))/i; 
  channel1 = (pulseIn (22, HIGH, 100000))/i;
  imprime();  
  delay(1000);
}
