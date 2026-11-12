// Passeio com PWM: o carrinho anda, desacelera conforme detecta aproximação
// a um obstáculo, para, gira no lugar por um tempo sorteado, e recomeça.
//
// Arduino Nano, Ponte-H L298N (com jumpers ENA/ENB no lugar),
// conjunto de 3 pilhas 3.7V, 4 conjuntos de motor + roda, e sensor ultrassônico HC-SR04.

// Ponte H: usando analogWrite(), os 4 pinos precisam ter PWM (pinos 3, 5, 6, 9, 10 ou 11)
const int IN1 = 3; // direito, para frente
const int IN2 = 5; // direito, para trás
const int IN3 = 6; // esquerdo, para frente
const int IN4 = 9; // esquerdo, para trás

const int TRIG_PIN = A5;
const int ECHO_PIN = A4;

// Velocidade (PWM, de 0 a 255) por faixa de distância
const int FAIXAS = 6;
const int ATE_CM[FAIXAS]     = { 10,  25,  50, 100, 200, 300};
const int VELOCIDADE[FAIXAS] = {  0,  50, 60, 70, 80, 90};

const int VELOCIDADE_MAX = 100;
const unsigned long GIRO_MAX_MS = 3000;
const unsigned long PAUSA_MS = 2000;
const unsigned long INTERVALO_MEDICAO_MS = 100;
const unsigned long TIMEOUT_US = 30000; // espera máxima pelo eco (~5 m)

void acionarMotores(int in1, int in2, int in3, int in4) {
  analogWrite(IN1, in1);
  analogWrite(IN2, in2);
  analogWrite(IN3, in3);
  analogWrite(IN4, in4);
}

int medirCm() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duracao = pulseIn(ECHO_PIN, HIGH, TIMEOUT_US);
  if (duracao == 0) duracao = TIMEOUT_US; // sem eco a tempo: livre até o limite (~5 m)

  // O número 0,0343 representa aproximadamente a velocidade do som
  // em centímetros por microssegundo.
  // Dividimos por dois porque o som percorre o caminho de ida e volta.
  return duracao * 0.0343 / 2;
}

int definirVelocidade(int cm) {
  for (int i = 0; i < FAIXAS; i++) {
    if (cm <= ATE_CM[i]) return VELOCIDADE[i];
  }
  return VELOCIDADE_MAX;
}

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  randomSeed(analogRead(A0)); // A0 solto: o ruído faz o sorteio mudar a cada vez que liga
  delay(PAUSA_MS);
}

void loop() {
  int cm = medirCm();
  int velocidade = definirVelocidade(cm);

  Serial.print(cm);
  Serial.print(" cm -> velocidade ");
  Serial.println(velocidade);

  if (velocidade > 0) {
    acionarMotores(velocidade, 0, velocidade, 0);
    delay(INTERVALO_MEDICAO_MS);
  } else {
    acionarMotores(0, 0, 0, 0);
    delay(PAUSA_MS);

    bool direita = random(2);
    unsigned long tempo = random(GIRO_MAX_MS + 1);
    Serial.print(direita ? "girando para a direita por " : "girando para a esquerda por ");
    Serial.print(tempo);
    Serial.println(" ms");

    if (direita) {
      acionarMotores(0, VELOCIDADE_MAX, VELOCIDADE_MAX, 0);
    } else {
      acionarMotores(VELOCIDADE_MAX, 0, 0, VELOCIDADE_MAX);
    }
    delay(tempo);
    acionarMotores(0, 0, 0, 0);
    delay(PAUSA_MS);
  }
}
