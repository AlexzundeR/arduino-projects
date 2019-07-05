//Подключение библиотеки I2C шины.
#include <Wire.h>
//Подключение библиотеки удаленного управления.
#include "IRremote.h"
//Подключение библиотеки управления моторами.
#include "motor.h"
//Подключение библиотеки управления гироскопом.
#include "gyro_acsel.h"
// Порт для IR-приемника.
int RECV_PIN = 7;
// Создание IR-приемника.
IRrecv irrecv(RECV_PIN);
//Переменная для результатов IR-приемника.
decode_results results;
int diod_pin = 6;
//========================================
void setup()
{
  //запуск гироскопа.
  giroscop_setup();
  // Переменные – номера контактов (пинов) Arduino.
  // Для левых и правых моторов машинки.
  setup_motor_system(2, 3, 4, 5);
  _stop(); //Двигатели остановлены.
  // Запуск IR-приемника.
  //Расчет компенсации утечки нуля гироскопа.
  // Робот стоит на месте 3 секунды
  Calc_CompensatorZ(3000);
  //переводим пин светодиода в режим вывода.
  pinMode(diod_pin, OUTPUT);
  irrecv.enableIRIn();
  Serial.begin(9600);
}
// Основная программа.
void loop()
{
  if (irrecv.decode(&results))
  {
    Serial.println(results.value, HEX);
    switch (results.value) {
      // 1
      case 0xC101E57B:
        //Включаем светодиод.
        digitalWrite(diod_pin, 1);
        Angle(10);
        //Гасим светодиод.
        digitalWrite(diod_pin, 0);
        break;
      // 2
      case 0x97483BFB:
        //Включаем светодиод.
        digitalWrite(diod_pin, 1);
        Angle(20);
        //Гасим светодиод.
        digitalWrite(diod_pin, 0);
        break;
      // 3
      case 0xF0C41643:
        //Включаем светодиод.
        digitalWrite(diod_pin, 1);
        Angle(30);
        //Гасим светодиод.
        digitalWrite(diod_pin, 0);
        break;
      // 4
      case 0x9716BE3F:
        //Включаем светодиод.
        digitalWrite(diod_pin, 1);
        Angle(40);
        //Гасим светодиод.
        digitalWrite(diod_pin, 0);
        break;
      // 5
      case 0x3D9AE3F7:
        //Включаем светодиод.
        digitalWrite(diod_pin, 1);
        Angle(50);
        //Гасим светодиод.
        digitalWrite(diod_pin, 0);
        break;
      // 6
      case 0x6182021B:
        //Включаем светодиод.
        digitalWrite(diod_pin, 1);
        Angle(60);
        //Гасим светодиод.
        digitalWrite(diod_pin, 0);
        break;
      // Вперед 10 сек
      case 0x511DBB:
        //Включаем светодиод.
        digitalWrite(diod_pin, 1);
        forward_t(10000000);
        //Гасим светодиод.
        digitalWrite(diod_pin, 0);
        break;
      // Назад 10 сек
      case 0xA3C8EDDB:
        //Включаем светодиод.
        digitalWrite(diod_pin, 1);
        backward_t(10000000);
        //Гасим светодиод.
        digitalWrite(diod_pin, 0);
        break;
      case 0xD7E84B1B:
        //Включаем светодиод.
        digitalWrite(diod_pin, 1);
        Angle_t(100000000);
        //Гасим светодиод.
        digitalWrite(diod_pin, 0);
        break;
    }
    irrecv.resume();
  }
  time_gyro(0.5);
 }

