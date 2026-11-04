// Testes usando Arduino Nano, Ponte-H L298N, conjunto de 3 pilhas 3.7V,
// 4 conjuntos de motor + roda, e todos os respectivos fios de ligação
//
// Como usar:
//   1. Apoiar o carrinho de forma que as quatro rodas fiquem no ar.
//      (OU diminuir o "TEMPO_LIGADO_MS"), é só um cuidado pra não bater/cair, etc.
//   2. Carregar este sketch e abrir o Monitor Serial no baud especificado em Serial.begin().
//   3. Digitar um comando e enviar:
//        1 = canal A (OUT1/OUT2, lado direito),  sentido 1 -> só IN1 em 5 V
//        2 = canal A (OUT1/OUT2, lado direito),  sentido 2 -> só IN2 em 5 V
//        3 = canal B (OUT3/OUT4, lado esquerdo), sentido 1 -> só IN3 em 5 V
//        4 = canal B (OUT3/OUT4, lado esquerdo), sentido 2 -> só IN4 em 5 V
//        f = andar para frente
//        t = andar para trás
//        0 = parar
//
// Cada comando fica ligado por "TEMPO_LIGADO_MS"
// (mandar mais tempo se precisar para medir com o multímetro).
//
// Como interpretar:
//   - Se um comando nao faz nada girar, suspeitar do fio do pino que deveria
//     estar em 5 V naquele comando.
//   - Se um comando faz os DOIS lados girarem, esse pino está em curto com
//     o vizinho.
//   - Com o multímetro (ponta preta no GND), o pino IN que deveria estar em
//     5 V tem que mostrar ~5 V na própria ponte.
//
// Os jumpers ENA e ENB da ponte precisam continuar no lugar.

const int IN1 = 3;
const int IN2 = 4;
const int IN3 = 5;
const int IN4 = 6;

const unsigned long TEMPO_LIGADO_MS = 100;

bool ligado = false;
unsigned long inicio = 0;

void aplicar(int v1, int v2, int v3, int v4) {
  digitalWrite(IN1, v1);
  digitalWrite(IN2, v2);
  digitalWrite(IN3, v3);
  digitalWrite(IN4, v4);

  ligado = (v1 == HIGH || v2 == HIGH || v3 == HIGH || v4 == HIGH);
  inicio = millis();

  Serial.print("   esperado na ponte:  IN1=");
  Serial.print(v1 == HIGH ? "5V" : "0V");
  Serial.print("  IN2=");
  Serial.print(v2 == HIGH ? "5V" : "0V");
  Serial.print("  IN3=");
  Serial.print(v3 == HIGH ? "5V" : "0V");
  Serial.print("  IN4=");
  Serial.println(v4 == HIGH ? "5V" : "0V");
}

void mostrarMenu() {
  Serial.println();
  Serial.println("Comandos:");
  Serial.println("  1 = canal A (OUT1/OUT2, lado direito),  sentido 1");
  Serial.println("  2 = canal A (OUT1/OUT2, lado direito),  sentido 2");
  Serial.println("  3 = canal B (OUT3/OUT4, lado esquerdo), sentido 1");
  Serial.println("  4 = canal B (OUT3/OUT4, lado esquerdo), sentido 2");
  Serial.println("  f = andar para frente");
  Serial.println("  t = andar para trás");
  Serial.println("  0 = parar");
}

void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.println();
  Serial.println("Início dos testes - parado");
  aplicar(LOW, LOW, LOW, LOW);
  mostrarMenu();
}

void loop() {
  if (ligado && millis() - inicio >= TEMPO_LIGADO_MS) {
    Serial.println("parou (tempo esgotado)");
    aplicar(LOW, LOW, LOW, LOW);
  }

  if (Serial.available() == 0) {
    return;
  }

  char c = Serial.read();

  switch (c) {
    case '1':
      Serial.println("Comando recebido: 1");
      Serial.println("(Canal A - lado direito, sentido 1)");
      aplicar(HIGH, LOW, LOW, LOW);
      break;
    case '2':
      Serial.println("Comando recebido: 2");
      Serial.println("(Canal A - lado direito, sentido 2)");
      aplicar(LOW, HIGH, LOW, LOW);
      break;
    case '3':
      Serial.println("Comando recebido: 3");
      Serial.println("(Canal B - lado esquerdo, sentido 1)");
      aplicar(LOW, LOW, HIGH, LOW);
      break;
    case '4':
      Serial.println("Comando recebido: 4");
      Serial.println("(Canal B - lado esquerdo, sentido 2)");
      aplicar(LOW, LOW, LOW, HIGH);
      break;
    case 'f':
    case 'F':
      Serial.println("Comando recebido: F");
      Serial.println("(andar para frente)");
      aplicar(HIGH, LOW, HIGH, LOW);
      break;
    case 't':
    case 'T':
      Serial.println("Comando recebido: T");
      Serial.println("(andar para trás)");
      aplicar(LOW, HIGH, LOW, HIGH);
      break;
    case '0':
      Serial.println("Comando recebido: 0");
      Serial.println("(parar)");
      aplicar(LOW, LOW, LOW, LOW);
      break;
    case '\n':
    case '\r':
    case ' ':
      break;  // ignora Enter e espacos
    default:
      mostrarMenu();
      break;
  }
}
