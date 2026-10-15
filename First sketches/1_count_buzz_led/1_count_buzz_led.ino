const int BOTAO = 2;
const int BUZZER = 7;
const int LED = 8;

int count = 0;

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
    count++;
    Serial.println(count);
    delay(100);
  }
}