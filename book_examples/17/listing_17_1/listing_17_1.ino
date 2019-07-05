// Библиотека для работы с протоколом I2C (порты A5/SCL и A4/SDA)
#include <Wire.h>
#include "motor.h"
#include "gyro_acsel.h"
// Пин информационного светодиода.
int  s_diod = 6;
//=====================================================================
void setup()
{
  // Заносим в переменные номера контактов (пинов) Arduino.
  // Для левых и правых моторов машинки.
  setup_motor_system(2, 3, 4, 5);
  // Двигатели остановлены.
  _stop();
  giroscop_setup();
  Serial.begin(9600);
  pinMode(s_diod, OUTPUT);
  _stop();
  for (int i = 0; i < 5; i++)
  {
    delay(100); digitalWrite(s_diod, HIGH);
    delay(100); digitalWrite(s_diod, LOW);
  }
  digitalWrite(s_diod, HIGH);
  GyXsum = 0;
}
//=========================================================
// Основная программа.
void loop()
{
  const long compensatorX = -257;
  //Запрос данных от гироскопа MPU-6050
  Data_mpu6050();
  GyXsum = GyXsum + (long)GyX - compensatorX;
  if (GyXsum > 10)
  {
    forward();
  }
  else
  {
    if (GyXsum < -10) backward(); else _stop();
  }
}

