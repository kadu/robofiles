 int motor_direito_frente = 9;
int motor_esquerdo_frente = 5;
int motor_direito_atras = 10;
int motor_esquerdo_atras = 6;
int pisca_led = 13;
int toque = 0; //sensor do toque;
int valor0 = 0; // valor do sensor de toque;  

int contador = 0; // Contador de Batidas

void anda()
{
  analogWrite(motor_direito_frente, 255);
  analogWrite(motor_direito_atras, 0);
  analogWrite(motor_esquerdo_frente, 255);
  analogWrite(motor_esquerdo_atras, 0);
}

void parado()
{
  analogWrite(motor_direito_frente, 0);
  analogWrite(motor_direito_atras, 0);
  analogWrite(motor_esquerdo_frente, 0);
  analogWrite(motor_esquerdo_atras, 0);
}

void direito()
{
  analogWrite(motor_direito_frente, 0);
  analogWrite(motor_direito_atras, 0);
  analogWrite(motor_esquerdo_frente, 255);
  analogWrite(motor_esquerdo_atras, 0);
}

void esquerdo()
{
  analogWrite(motor_direito_frente, 255);
  analogWrite(motor_direito_atras, 0);
  analogWrite(motor_esquerdo_frente, 0);
  analogWrite(motor_esquerdo_atras, 0);
}

void atras()
{
  analogWrite(motor_direito_frente, 0);
  analogWrite(motor_direito_atras, 255);
  analogWrite(motor_esquerdo_frente, 0);
  analogWrite(motor_esquerdo_atras, 255);
}

void rotacao_direito()
{
  analogWrite(motor_direito_frente, 0);
  analogWrite(motor_direito_atras, 255);
  analogWrite(motor_esquerdo_frente, 255);
  analogWrite(motor_esquerdo_atras, 0);
}

void rotacao_esquerdo()
{
  analogWrite(motor_direito_frente, 255);
  analogWrite(motor_direito_atras, 0);
  analogWrite(motor_esquerdo_frente, 0);
  analogWrite(motor_esquerdo_atras, 255);
}

void setup()
{
  pinMode(motor_direito_frente, OUTPUT);
  pinMode(motor_esquerdo_frente, OUTPUT);
  pinMode(motor_direito_atras, OUTPUT);
  pinMode(motor_esquerdo_atras, OUTPUT);
  pinMode(pisca_led, OUTPUT);
  pinMode(toque, INPUT);
  Serial.begin(9600);
}


void loop()
{
  valor0 = analogRead(toque);
  Serial.print("O valor do Toque e igual a");
  Serial.println(valor0);
  delay(25); // Depois mudar para ser mais rapido, so teste
  if(valor0 <= 50)
  {  // bateu
    contador++;
    if(contador == 1) {
        // Vira pra Esquerda
        parado();
        delay(1);
        atras();
        delay(2000);
        rotacao_esquerdo();
        delay(1000);//calcular para rodar 90°graus
        parado();
        delay(1);
    } else {
      // vira 180
      contador = 0;
        parado();
        delay(1);
        atras();
        delay(2000);
        rotacao_esquerdo();
        delay(1000);//calcular para rodar 90°graus
        rotacao_esquerdo();
        delay(1000);//calcular para rodar 90°graus
        parado();
        delay(1);      
    }
  }
  else
  {
    anda();
    delay(100);
    parado();
    delay(1);
  }

}

