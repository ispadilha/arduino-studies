const int BOTAO = 2;
const int BUZZER = 5;
const int LED = 6;
// pwm pins: 3, 5, 6, 9, 10, or 11

void setup() {
  Serial.begin(115200);
  Serial.println("inicio");

  pinMode(BOTAO, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);

  analogWrite(BUZZER, 0);
  analogWrite(LED, 0);
}

void loop() {
  int estadoBotao = digitalRead(BOTAO);

  if (estadoBotao == LOW) {
    analogWrite(BUZZER, 0);
    analogWrite(LED, 0);
  } else {
    analogWrite(LED, 20);
    analogWrite(BUZZER, 20);
  }
}