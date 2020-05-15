/* Programa de Teste de LCD
   Blog Eletrogate - https://blog.eletrogate.com/guia-completo-do-display-lcd-arduino/
   Arduino Nano - LCD 16/2 azul - IDE 1.8.5
   Gustavo Murta   11/abril/2018
   Biblioteca LiquidCrystal https://github.com/arduino-libraries/LiquidCrystal
*/
 
#include <LiquidCrystal.h>      // usando a biblioteca LiquidCrystal
 
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7; // definicao dos pinos do Display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                // configurando os pinos
int thisChar = 0 ;

const int pinoBotaoGreen = 12;         //PINO DIGITAL UTILIZADO PELO PUSH BUTTON GREEN
const int pinoBotaoRed = 11;           //PINO DIGITAL UTILIZADO PELO PUSH BUTTON RED
const int buzzer = 2;                  //PINO DIGITAL UTILIZADO PELO LED

int segundo, minuto;
unsigned long UtlTime;

boolean desativar = false;

void setup()
{
  lcd.begin(16, 2);                        // definindo o LCD - 16 colunas e 2 linhas
pinMode(pinoBotaoGreen, INPUT_PULLUP);     //DEFINE O PINO COMO ENTRADA / "_PULLUP" É PARA ATIVAR O RESISTOR INTERNO
                                           //DO ARDUINO PARA GARANTIR QUE NÃO EXISTA FLUTUAÇÃO ENTRE 0 (LOW) E 1 (HIGH)
pinMode(pinoBotaoRed, INPUT_PULLUP);
pinMode(buzzer, OUTPUT);                   //DEFINE O PINO COMO SAÍDA
digitalWrite(buzzer, LOW);                 //BUZZER INICIA DESLIGADO

 UtlTime = 0;
  minuto = 0;
  lcd.begin(16, 2);

  lcd.setCursor(3, 0);
  lcd.print("Iniciando");
  lcd.setCursor(3, 1);
  lcd.print("Atividade");
  delay (2000);
  lcd.clear();

 Menu (); // MENU DE ENTRADA
}

 void Menu ()                     // imprimindo mensagem
{
  lcd.setCursor(0, 0);            // selecionando coluna 0 e linha 0
  lcd.print("Menu principal:");
  delay(1500);
  lcd.clear();                       // limpa a tela
  delay(1000);                       // atraso de 1 segundo// print da mensagem
  lcd.setCursor(0, 0);               // selecionando coluna 16 e linha 1
  lcd.print("-Verde atividade");
  lcd.setCursor(0, 1);
  lcd.print("-Vermelho intervalo");
  delay(1000);                       // atraso de 350 ms
}

void Flash ()
{
  lcd.noDisplay();                // desliga display
  delay(1000);                    // atraso de meio segundo
  lcd.display();                  // liga display
  delay(1000);                    // atraso de meio segundo
  lcd.clear();                    // limpa a tela
  delay(1000);                    // atraso de 1 segundo
}
 
void AutoScroll ()                // teste de rolagem de mensagem
{
  lcd.setCursor(16, 1);           // selecionando coluna 16 e linha 1
  lcd.autoscroll();               // configura rolagem automatica de mensagem
  for (thisChar = 0; thisChar < 10; thisChar++)     // imprime de 0 a 9
  {
    lcd.print(thisChar);          // imprime o numero
    delay(350);                   // atraso de 350 ms
  }
  lcd.noAutoscroll();             // desliga rolagem autoamtica
  lcd.clear();                    // limpa a tela
  delay(1000);                    // atraso de 1 segundo
}

boolean Tempo (boolean desativado) {
if (millis() - UtlTime < 0)
  {
    UtlTime = millis();
  }
  else
  {
    segundo = int((millis() - UtlTime) / 1000);
  }
  if (segundo > 59) {
    segundo = 0;
    minuto--;
    UtlTime = millis();
    if (minuto < 1 && segundo == 0) {
      lcd.clear();
   //   do {
      minuto = 0;
      segundo = 0;
      lcd.setCursor(0, 0);
      lcd.print("Acabou o tempo");
      return true;
    //  } while (minuto < 1 && segundo == 0);
    }
  }

  lcd.setCursor(5, 1);
  lcd.print("-");
  lcd.print(minuto);
  lcd.print(":");
  int resultadoSegundo = 60 - segundo;
  lcd.print(resultadoSegundo);
  lcd.print("-");
}

void loop()
{
 // Flash ();         // piscando a mensagem
 // AutoScroll ();    // teste de rolagem de mensagem
 boolean resultado = false;
 
  if(digitalRead(pinoBotaoGreen) == LOW){         //SE A LEITURA DO PINO FOR IGUAL A LOW, FAZ
      //digitalWrite(buzzer, HIGH);               //LIGA O BUZZER
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Atividade 25 min");
      while (resultado == false){
        Tempo (desativar);
        resultado = desativar;
      }
  } else if(digitalRead(pinoBotaoRed) == LOW){    //SE A LEITURA DO PINO FOR IGUAL A LOW, FAZ
   // digitalWrite(buzzer, HIGH);                 //LIGA O BUZZER
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("Intervalo 5 min");
    } else{                                       //SENÃO, FAZ
    digitalWrite(buzzer, LOW);                    //DESLIGA O BUZZER
  }

  Menu ();
}

 
