//Подключаем библиотеку I2C.
#include <Wire.h>
///////////////////////////////////////////////////////////
// адрес i2c компаса.
#define address 0x1E
void setup() {
  // Серийный порт для связи с ПК.
  Serial.begin(9600);
  //Запускаем связь по шине I2C.
  Wire.begin();
  //Для анализа окончания процесса будем использовать светодиод.
  pinMode(6, OUTPUT);
}
//=======================================
void loop() {
  int x, y, z; //triple axis data
  Wire.beginTransmission(address);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  Wire.requestFrom(address, 6);
  if (6 <= Wire.available()) {
    x = Wire.read() << 8;    x |= Wire.read();
    z = Wire.read() << 8;    z |= Wire.read();
    y = Wire.read() << 8;    y |= Wire.read();
  }
  Serial.print("x: ");  Serial.print(x);
  Serial.print("  y: ");  Serial.print(y);
  Serial.print("  z: ");  Serial.println(z);
  delay(500);
} 

