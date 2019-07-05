#include "Kalman.h"
// Библиотека для работы с протоколом I2C (порты A5/SCL и A4/SDA)
#include <Wire.h>
#include "motor.h"
#include "gyro_acsel.h"
// Пин информационного светодиода.
int  s_diod = 6;

//Переменные для хранения данных времени
// работы контроллера Arduino.
unsigned long time_data_request, time_in_system;
// Время, через которое производится опрос гироскопа-акселерометра.
const unsigned long time_step = 10;
double accXangle; // Угол, посчитанный по акселерометру.
double gyroXangle ; // Угол, посчитанный по гирокомпасу.
double gyroXrate; //Приращение угла по показаниям гироскопа.
double kalAngleX ;
// Результирующий угол после обработки фильтром Калмана.
Kalman kalmanX;
Kalman kalmanY;
//===============================================================
void setup()
{
  //Коэффициенты для фильтра Калмана.
  kalmanX.setQangle(0.001);
  kalmanX.setQbias(0.003);
  kalmanX.setRmeasure(0.03);
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
  kalmanX.setAngle(0); // Set starting angle
  kalmanY.setAngle(0);
  timer = micros();
}
//=====================================================================
// Основная программа.
void loop()
{
  int i = 0;
  while (true)
  {
    //Запрос данных от гироскопа MPU-6050
    Data_mpu6050();

    // Расчет угла по показаниям акселерометра.
    accXangle = (atan2(AcY, AcZ)) * RAD_TO_DEG;
    // Расчет приращения угла по гироскопу.
    gyroXrate = -((float)GyX / 131.0);
    // Расчет угла по показаниям гироскопа.
    // Обработка данных фильтром Калмана.
    kalAngleX = kalmanX.getAngle(accXangle, gyroXrate, (float)( micros() - timer) / 1000000.0);
    timer = micros();
    // Компенсируем наклон
    if (kalAngleX > 2.0)
    {
      forward();
    }
    else if (kalAngleX < -2.0)
    {
      backward();
    }
    else {
      _stop();
    }
   /* if (i == 100)
    {
      Serial.print("kalAngleX=");
      Serial.println( kalAngleX);
      i = 0;
    }
    i++; */
  }
}

