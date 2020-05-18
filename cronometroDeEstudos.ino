#include <LiquidCrystal.h>      // usando a biblioteca LiquidCrystal

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7; // definicao dos pinos do Display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                // configurando os pinos
int thisChar = 0 ;

const int pinoBotaoVerde = 12;         //PINO DIGITAL UTILIZADO PELO PUSH BUTTON GREEN
const int pinoBotaoVermelho = 11;           //PINO DIGITAL UTILIZADO PELO PUSH BUTTON RED
const int buzzer = 2;                  //PINO DIGITAL UTILIZADO PELO LED

int segundo, minuto;
unsigned long  salvarTempo;
int ultimoTempo;
unsigned long proximoSegundo;
int segundoTotal;
int tempoDoTemporizador;

boolean desativar = false;

void setup()
{
  lcd.begin(16, 2);                        // definindo o LCD - 16 colunas e 2 linhas

  pinMode(pinoBotaoVerde, INPUT_PULLUP);
  pinMode(pinoBotaoVermelho, INPUT_PULLUP);
  //DEFINE O PINO COMO ENTRADA / "_PULLUP" É PARA ATIVAR O RESISTOR INTERNO
  //DO ARDUINO PARA GARANTIR QUE NÃO EXISTA FLUTUAÇÃO ENTRE 0 (LOW) E 1 (HIGH)

  pinMode(buzzer, OUTPUT);                   //DEFINE O PINO COMO SAÍDA
  digitalWrite(buzzer, LOW);                 //BUZZER INICIA DESLIGADO

  ultimoTempo = 0;
  minuto = 0;
  segundo = 0;

  lcd.setCursor(3, 0);
  lcd.print("Iniciando");
  lcd.setCursor(3, 1);
  lcd.print("Atividade");
  delay (2000);
  lcd.clear();
}

void loop()
{
  Menu();
  desativar = false;

  while (digitalRead(pinoBotaoVerde) == HIGH && digitalRead(pinoBotaoVermelho) == HIGH) {

  }

  if (digitalRead(pinoBotaoVerde) == LOW) {       //SE A LEITURA DO PINO FOR IGUAL A LOW, FAZ
    tempoDoTemporizador = 4;
    Buzzer();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Intervalo 5 min");
    delay(800);
    while (desativar == false) {
      desativar = Temporizador(desativar);
    }

  } else if (digitalRead(pinoBotaoVermelho) == LOW) {  //SE A LEITURA DO PINO FOR IGUAL A LOW, FAZ
    tempoDoTemporizador = 24;
    Buzzer();
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Atividade 25 min");
    delay(800);
    while (desativar == false) {
      desativar = Temporizador(desativar);
    }

  } else {
  }

  delay(1000);
}
