//=Подключение библиотеки i2c
#include <Wire.h>
//================================================
// константа с адресом i2c датчика
#define sensor_address 44
//================================================
uint8_t wire_array[2];// Массив данных для передачи по wire.
// Функция, которая выполняется, когда приходит запрос от мастера.
void requestEvent()
{
  //Передача массива из 2 байтов.
  Wire.write(wire_array, 2);
}
void setup()
{
  // Инициализация в качестве подчиненного с i2c адресом 44.
  Wire.begin(sensor_address);
  // Ссылка на функцию, выполняемую при запросе данных.
  Wire.onRequest(requestEvent);
}
//=============================
void loop()
{
  int analogData = analogRead(A0);
  //Заполнение массива
  wire_array[0] = (uint8_t)((0xFF00 & analogData) >> 8);
  wire_array[1] = (uint8_t)(0x00FF & analogData);
}


