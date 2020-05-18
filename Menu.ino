void Menu ()                     // imprimindo mensagem
{
  lcd.clear();
  lcd.setCursor(0, 0);            // selecionando coluna 0 e linha 0
  lcd.print("Menu principal:");
  delay(1500);
  lcd.clear();                       // limpa a tela
  delay(500);                       // atraso de 1 segundo// print da mensagem
  lcd.setCursor(0, 0);
  lcd.print("-Verde intervalo");
  lcd.setCursor(0, 1);
  lcd.print("-Verm. atividade");
  delay(500);
}
