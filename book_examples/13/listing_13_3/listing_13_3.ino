//Подключаем библиотеку I2C.
#include <Wire.h>
///////////////////////////////////////////////////////////
//Подключаю функции управления моторами
#include "motor.h"
//Подключаю функции HMC5883L
#include "compas.h"
//=======================================
void setup() {
  // Серийный порт для связи с ПК.
  Serial.begin(9600);
  //Запускаем связь по шине I2C.
  Wire.begin();
  //Компас
  compas_setup();      // инициализация HMC5883L
  //Для анализа окончания процесса будем использовать светодиод.
  pinMode(6, OUTPUT);
}
//=======================================
void loop() {
  float heading = get_Compass_ang();
  Serial.println(heading);
  digitalWrite(6, HIGH);
  delay(500);
  digitalWrite(6, 0);
}

