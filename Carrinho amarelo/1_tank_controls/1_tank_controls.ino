// Tank controls: dirigir o carrinho pelo Serial com W A S D.
//
// Arduino Nano, Ponte-H L298N, conjunto de 3 pilhas 3.7V, jumpers ENA/ENB,
// 4 conjuntos de motor + roda, e todos os respectivos fios de ligação.
//
// Usar monitor serial em modo não canônico (tecla enviada imediatamente, sem esperar ENTER).
// Cada tecla liga os motores por TEMPO_LIGADO_MS. Sem tecla nova, o carrinho para.

const int IN1 = 3;
const int IN2 = 4;
const int IN3 = 5;
const int IN4 = 6;

const unsigned long TEMPO_LIGADO_MS = 100;

unsigned long iucm = 0;  // instante do último comando aos motores

void motores(int esquerdo, int direito) {
  digitalWrite(IN1, direito > 0);
  digitalWrite(IN2, direito < 0);
  digitalWrite(IN3, esquerdo > 0);
  digitalWrite(IN4, esquerdo < 0);
  iucm = millis();
}

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    switch (Serial.read()) {
      case 'w': motores( 1,  1); break;
      case 's': motores(-1, -1); break;
      case 'a': motores(-1,  1); break;
      case 'd': motores( 1, -1); break;
    }
  }

  if (millis() - iucm >= TEMPO_LIGADO_MS) {
    motores(0, 0);  // nenhuma tecla nova a tempo: para
  }
}
