// Подключаем библиотеку для работы с Serial через дискретные порты
#include <SoftwareSerial.h>
//Создаем последовательный порт на пинах 10 и 11
SoftwareSerial BTSerial(10, 11); // RX, TX
// Переменная для приема данных по Bluetooth
char bt_input;
// Настройка
void setup()
{
  // Устанавливаем скорость передачи данных по Bluetooth
  BTSerial.begin(9600);
  // Переключаем A0 в двоичный режим работы, на передачу
  pinMode(14, OUTPUT);//Только для HC-05
  // Переводим HC-05 в режим AT-команд
  digitalWrite(14, 1); //Только для HC-05
  // Присваиваем HC-05 новое имя - MaxiBot
  BTSerial.println("AT+NAME=MaxiBot");//Для НС-05
  //Для модуля из набора HC-06 и SPP-C
  // BTSerial.println("AT+NAMEMaxiBot");
  // Устанавливаем скорость передачи данных по кабелю
  Serial.begin(9600);
  // переводим HC-05 в нормальный режим работы
  digitalWrite(14, 0); //Только для HC-05
}
void loop()
{
  // Если пришли данные по Bluetooth
  if (BTSerial.available())
  {
    // Записываем, что пришло по Bluetooth в переменную bt_input
    bt_input = (char)BTSerial.read();
    Serial.println(bt_input);
  }
}

