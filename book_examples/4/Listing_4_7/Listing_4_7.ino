void setup() // Настройка.
{
 // Переводим 13 порт в состояние вывода информации.
 pinMode(13, OUTPUT);  
}
// Основная программа.
void loop() 
{
  unsigned long time_1;
  unsigned long time_2;
  unsigned long time_3;
time_1 = millis();   //Начальное значение – количество миллисекунд
// от включения программы.
time_2=time_1+1000; // +1 секунду.
time_3=time_1+2000; // +2 секунды.
  while(time_1<time_2)
  {
    digitalWrite(13, 1);   // Включает светодиод на плате.
    time_1 = millis(); //Текущее время в time_1. 
  }
  while(time_1<time_3)
  {
    digitalWrite(13, 0);   // Выключает светодиод на плате.
    time_1 = millis(); //Текущее время в time_1.
  }
}

