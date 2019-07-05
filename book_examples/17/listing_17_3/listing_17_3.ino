// Библиотека для работы с протоколом I2C (порты A5/SCL и A4/SDA)
#include <Wire.h>
#include "motor.h"
#include "gyro_acsel.h"
// Пин информационного светодиода.
int  s_diod = 6;
//начальное смещение нуля баланса.
double balancing_zerro = 2.4;
//===============================================================
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
  digitalWrite(s_diod, LOW);
  delay(200);
  digitalWrite(s_diod, HIGH);
  _stop();
  timer = micros();
}
//=====================================================================
// Основная программа.
void loop()
{
  int i=0;
  timer = micros();
  while (true)
  {
    // Компенсируем наклон.
    if (GyXsum > 1.0)
    {
      forward();
    }
    else if (GyXsum < -1.0)
    {
      backward();
    }
    else {
      _stop();
    }
    //Запрос данных от гироскопа MPU-6050
    Data_mpu6050();

    //Расчет угла по показаниям акселерометра
    // с учетом корректировки точки равновесия balancing_zerro.
    AcYsum = (atan2(AcY, AcZ)) * RAD_TO_DEG+balancing_zerro;
    // Измерение наклона по Х.
    // Использование Комплементарного фильтра,
    // alfa - коэффициент фильтра.
    double alfa = 0.001;
    GyXsum = (1 - alfa) * (GyXsum + ((double)GyX * (double)(micros() - timer)) / 131000000.0) + alfa * AcYsum;
    //Для перевода угловой скорости в угол нужно знать время!
    timer = micros();
    /* if (i == 100)
    {
      Serial.print("GyXsum =");
      Serial.println(GyXsum);
      i = 0;
    }
    i++;
    */
  }
}


