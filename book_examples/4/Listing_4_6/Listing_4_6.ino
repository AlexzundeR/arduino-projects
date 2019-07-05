int time_pick; // Переменная для хранения времени свечения светодиода.
void setup() // Настройка
{
 //Устанавливаем скорость порта связи Arduino - ПК.
 Serial.begin(9600);
 // Переводим 13 порт в состояние вывода информации
 pinMode(13, OUTPUT);  
 time_pick=200; //Период свечения светодиода.
}
// Основная программа.
void loop() 
{
  char char1;
 // если поступили данные.
 if (Serial.available() > 0) 
 {
  // считываем символ.  
  char1 = Serial.read();
    switch (char1) {
    case '1':
      time_pick=1000;
      break;
    case '2':
      time_pick=500;
      break;
    default:
      time_pick=100;
  }
 }
   digitalWrite(13, 1);   // Включает светодиод на плате.
  delay(time_pick);           // Ждет 
  digitalWrite(13, 0);   // Выключает светодиод.
  delay(time_pick);           // Ждет 
}

