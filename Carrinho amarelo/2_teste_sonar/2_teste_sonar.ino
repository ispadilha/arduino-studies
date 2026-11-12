// Teste de sensor ultrassônico HC-SR04

const int TRIG_PIN = 11;
const int ECHO_PIN = 12;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);
  
  // Garante que o Trig comece em LOW
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(10);
}

void loop() {
  // Envia um pulso de 10 microssegundos
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Mede o tempo de retorno do sinal, com timeout de 30.000 microssegundos (30 ms)
  unsigned long duracao = pulseIn(ECHO_PIN, HIGH, 30000UL);

  if (duracao == 0) {
    Serial.println("Nenhum objeto detectado!");
  } else {
    // Converte o tempo em distância (centímetros)
    // O número 0,0343 representa aproximadamente a velocidade do som
    // em centímetros por microssegundo.
    // Dividimos por dois porque o som percorre o caminho de ida e volta.
    float distancia = duracao * 0.0343 / 2;

    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");
  }

  delay(1000);
}