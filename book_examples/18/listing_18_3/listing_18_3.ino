void setup()
{
// Переводим порты с 8 по 12 в состояние вывода
// это адресные порты
  //DDRB = B00111111;
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  //Порт 13 не занимать!!
  //А0 служит для получения аналогового сигнала
  // от мультиплексоров
  pinMode(A0, INPUT);
  //Подключаем порт для вывода информации на ПК
  Serial.begin(9600);
}
//================================
void loop()
{
  int  j, temp;
  uint8_t j_cor;
  //Задаем стартовые значения.
  for (j = 0; j < 18; j++)
  {
    j_cor = j;
    PORTB = j_cor; //Пишем адрес на мультиплексор
    temp = analogRead(A0);
    Serial.print("["); Serial.print(j); Serial.print("]="); Serial.println(temp);
  }
  Serial.println("------------------------------------------------");
  delay(1000);
}

