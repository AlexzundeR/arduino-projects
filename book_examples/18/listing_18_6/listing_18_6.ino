// Библиотека для работы с протоколом I2C (порты A5/SCL и A4/SDA)
#include <Wire.h>
///////////////////////////////////////////////////////////
// константа с адресом i2c датчика
#define sensor_address 44
///////////////////////////////////////////////////////////
//== Функция опроса датчика с 44 адресом i2c ==========
int Data_from_i2c_arduino()
{
  int  illuminating_intensity;
  // Запрос 2 байтов.
  Wire.requestFrom(sensor_address, 2, true);
  illuminating_intensity = Wire.read() | Wire.read() << 8;
  return illuminating_intensity;
}
//=====================================================
void setup()
{
  Wire.begin();
  Serial.begin(9600);
}
//==== Основная программа.=====
void loop()
{
  int i_i = Data_from_i2c_arduino();
  Serial.print("illuminating_intensity = "); Serial.println(i_i);
  delay(1000);
}

