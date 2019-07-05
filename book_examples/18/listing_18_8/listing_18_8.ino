// Библиотека для работы с протоколом I2C (порты A5/SCL и A4/SDA).
#include <Wire.h>
// Подключаем библиотеку дополнительных последовательных (Serial) портов.
#include <SoftwareSerial.h>
//Создаем последовательный порт на пинах 13 - чтение и 2 - передача.
SoftwareSerial BTSerial(10, 11); // RX, TX
// Переменная для приема данных по Bluetooth.
char bt_input;
///////////////////////////////////////////////////////////
//Подключаю функции управления моторами.
#include "motors.h"
//////////////////////////////////////////////////////////
//Подключаю функции HMC5883L.
#include "compas.h"
//////////////////////////////////////////////////////////
//Подключаю функции MPU-6050.
#include "gyro_acsel.h"
///////////////////////////////////////////////////////////
void setup()
{
  BTSerial.begin(9600);
  // Заносим в переменные номера контактов (пинов) Arduino.
  // Для левых и правых моторов.
  setup_motor_system(2, 3, 4, 5);
  // Двигатели остановлены.
  _stop();
  giroscop_setup();
  //Компас.
  compas_setup();      // инициализация HMC5883L
  delay(150);
  Ang_ = 0;
  //Расчет компенсации утечки нуля гироскопа.
  Calc_CompensatorZ(1000);
  // Запуск таймера для гироскопа.
  timer = micros();
}
//==================================
void loop()
{
  while (1)
  {
    if (BTSerial.available())
    {
      // Читаем команды и заносим их в переменную.
      bt_input = (char)BTSerial.read();
      // Отправляем команду в порт, чтобы можно было ее проверить.
      //Serial.println(bt_input);
      switch (bt_input) {
        // Вперед
        case 'F':
          forward_t(1000000);
          break;
        // Назад
        case 'B':
          backward_t(1000000);
          break;
        // Влево
        case 'L':
          Angle(90);
          break;
        // Вправо
        case 'R':
          Angle(-90);
          break;
        // Разворот
        case 'O':
          Angle(180);
          break;
        // Стоп
        case 'S':
          _stop();
        case 'X':
          //switch_rejim = 1;
          break;
        case 'x':
          //switch_rejim = 0;
          break;
        case 'D':
          _stop(); //switch_rejim = 0;
          break;
      }
    }
    time_gyro(1);
  }
}






