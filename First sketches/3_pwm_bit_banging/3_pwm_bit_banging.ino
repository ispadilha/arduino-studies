const int BOTAO = 2;
const int BUZZER = 7;
const int LED = 8;

const int DUTY_CYCLE = 20;

void setup() {
  Serial.begin(115200);
  Serial.println("inicio");

  pinMode(BOTAO, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(BUZZER, LOW);
  digitalWrite(LED, LOW);
}

void loop() {
  int estadoBotao = digitalRead(BOTAO);

  if (estadoBotao == LOW) {
    digitalWrite(BUZZER, LOW);
    digitalWrite(LED, LOW);
  } else {
    digitalWrite(LED, HIGH);
    digitalWrite(BUZZER, HIGH);
    delayMicroseconds(DUTY_CYCLE);
    digitalWrite(LED, LOW);
    digitalWrite(BUZZER, LOW);
    delayMicroseconds(1000 - DUTY_CYCLE);
  }
}