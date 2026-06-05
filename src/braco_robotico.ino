/*
 * ============================================================
 * BRAÇO ROBÓTICO DE COLETA DE AMOSTRAS — Docking & Retrieval
 * Maker Lab — Projeto de Robótica Espacial - 4ESPY
 * ============================================================
 *
 * Descrição:
 *   Controle de braço robótico com 2 servomotores e LED de status
 *   via Monitor Serial. Simula operação em microgravidade para
 *   captura de amostras espaciais.

    Integrantes:

      Debora da Silva Amaral - RM550412, 
      Eduardo Pielich Sanchez - RM99767, 
      Gabriel Machado Carrara Pimentel - RM99880, 
      Livia Namba Seraphim - RM97819, 
      Vitor Hugo Gonçalves Rodrigues - RM97758
 *
 * Hardware:
 *   - Arduino Uno
 *   - Servo 1 (articulação / ombro) — pino digital 9
 *   - Servo 2 (garra / efetuador)   — pino digital 10
 *   - LED de status                 — pino digital 13 (com resistor 220Ω)
 *   - Fonte: 5V–6V (bancada/simulador)
 *
 * Comandos via Monitor Serial (9600 baud):
 *   U  → Up    : Sobe o braço  (Servo1 vai para 150°)
 *   D  → Down  : Desce o braço (Servo1 vai para  30°)
 *   O  → Open  : Abre a garra  (Servo2 vai para 120°)
 *   C  → Close : Fecha a garra (Servo2 vai para  10°)
 *   H  → Home  : Posição inicial (Servo1=90°, Servo2=90°)
 *   S  → Status: Imprime ângulos atuais no Serial
 * ============================================================
 */

#include <Servo.h>

const int PIN_SERVO_BRACO = 9;  
const int PIN_SERVO_GARRA = 10; 
const int PIN_LED_STATUS  = 13;  

const int BRACO_MIN  = 10;   
const int BRACO_MAX  = 170;  
const int BRACO_HOME = 90;   

const int GARRA_ABERTA   = 120; 
const int GARRA_FECHADA  = 10;  
const int GARRA_HOME     = 90;  

const int BRACO_UP   = 150;
const int BRACO_DOWN = 30;  

const int DELAY_POR_GRAU = 8; 

Servo servoBraco;
Servo servoGarra;

int anguloBraco = BRACO_HOME;
int anguloGarra = GARRA_HOME;
bool ledState   = false;

void setup() {
  Serial.begin(9600);

  servoBraco.attach(PIN_SERVO_BRACO);
  servoGarra.attach(PIN_SERVO_GARRA);

  pinMode(PIN_LED_STATUS, OUTPUT);

  moverSuave(servoBraco, anguloBraco, BRACO_HOME);
  moverSuave(servoGarra, anguloGarra, GARRA_HOME);
  anguloBraco = BRACO_HOME;
  anguloGarra = GARRA_HOME;

  piscarLED(3); 

  Serial.println("============================================");
  Serial.println(" BRACO ROBOTICO — Docking & Retrieval v1.0");
  Serial.println("============================================");
  Serial.println("Comandos disponiveis:");
  Serial.println("  U -> Up    : Sobe o braco");
  Serial.println("  D -> Down  : Desce o braco");
  Serial.println("  O -> Open  : Abre a garra");
  Serial.println("  C -> Close : Fecha a garra");
  Serial.println("  H -> Home  : Posicao inicial");
  Serial.println("  S -> Status: Exibe angulos atuais");
  Serial.println("============================================");
  Serial.println("Sistema pronto. Aguardando comando...");
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = (char)Serial.read();
    cmd = toupper(cmd); 

    if (cmd == ' ' || cmd == '\n' || cmd == '\r') return;

    piscarLED(1); 

    switch (cmd) {

      case 'U': 
        Serial.print(">> UP: movendo braco para ");
        Serial.print(BRACO_UP);
        Serial.println(" graus...");
        moverSuave(servoBraco, anguloBraco, BRACO_UP);
        anguloBraco = BRACO_UP;
        Serial.println("   [OK] Braco em posicao UP.");
        break;

      case 'D': 
        Serial.print(">> DOWN: movendo braco para ");
        Serial.print(BRACO_DOWN);
        Serial.println(" graus...");
        moverSuave(servoBraco, anguloBraco, BRACO_DOWN);
        anguloBraco = BRACO_DOWN;
        Serial.println("   [OK] Braco em posicao DOWN.");
        break;

      case 'O': 
        Serial.print(">> OPEN: abrindo garra para ");
        Serial.print(GARRA_ABERTA);
        Serial.println(" graus...");
        moverSuave(servoGarra, anguloGarra, GARRA_ABERTA);
        anguloGarra = GARRA_ABERTA;
        Serial.println("   [OK] Garra aberta.");
        break;

      case 'C': 
        Serial.print(">> CLOSE: fechando garra para ");
        Serial.print(GARRA_FECHADA);
        Serial.println(" graus...");
        moverSuave(servoGarra, anguloGarra, GARRA_FECHADA);
        anguloGarra = GARRA_FECHADA;
        Serial.println("   [OK] Garra fechada. Amostra capturada!");
        break;

      case 'H': 
        Serial.println(">> HOME: retornando a posicao inicial...");
        moverSuave(servoBraco, anguloBraco, BRACO_HOME);
        moverSuave(servoGarra, anguloGarra, GARRA_HOME);
        anguloBraco = BRACO_HOME;
        anguloGarra = GARRA_HOME;
        piscarLED(3);
        Serial.println("   [OK] Posicao HOME restaurada.");
        break;

      case 'S': 
        imprimirStatus();
        break;

      default:
        Serial.print("?? Comando desconhecido: '");
        Serial.print(cmd);
        Serial.println("' — use U, D, O, C, H ou S.");
    }
  }
}

void moverSuave(Servo& servo, int origem, int destino) {
  int passo = (destino > origem) ? 1 : -1;
  for (int pos = origem; pos != destino; pos += passo) {
    servo.write(pos);
    delay(DELAY_POR_GRAU);
  }
  servo.write(destino); 
}

void piscarLED(int vezes) {
  for (int i = 0; i < vezes; i++) {
    digitalWrite(PIN_LED_STATUS, HIGH);
    delay(120);
    digitalWrite(PIN_LED_STATUS, LOW);
    delay(120);
  }
}

void imprimirStatus() {
  Serial.println("── STATUS DO BRACO ──────────────────");
  Serial.print("   Servo Braco (pino 9)  : ");
  Serial.print(anguloBraco);
  Serial.println(" graus");
  Serial.print("   Servo Garra (pino 10) : ");
  Serial.print(anguloGarra);
  Serial.println(" graus");
  Serial.println("─────────────────────────────────────");
}
