boolean Temporizador (boolean desativado) {

  lcd.clear();
  lcd.setCursor(5, 1);
  lcd.print("-");
  lcd.print(tempoDoTemporizador + 1);
  lcd.print(":00-");
  delay(1000);

  minuto = tempoDoTemporizador;
  segundoTotal = 59;
  salvarTempo = millis();

  lcd.clear();

  while (true) {

    proximoSegundo = salvarTempo + 1000;

    segundo = segundoTotal - ultimoTempo;
    lcd.setCursor(5, 1);
    lcd.print("-");
    lcd.print(minuto);
    lcd.print(":");
    lcd.print(segundo);
    lcd.print("-");

    if (segundo <= 0) {
      delay(1000);
      minuto = minuto - 1;

      if (minuto == 0 && segundo <= 0) {
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Acabou o tempo!");
        Buzzer();
        Buzzer();
        delay(1000);
        return true;
      }

      segundoTotal = 60;
      ultimoTempo = 0;
    }

    if (millis() >= proximoSegundo) {
      ++ultimoTempo;
      salvarTempo = proximoSegundo;
    }
    if (digitalRead(pinoBotaoVermelho) == LOW) {
      return true;
    }
  }
}
