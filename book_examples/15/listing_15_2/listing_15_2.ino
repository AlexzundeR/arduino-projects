//Подключение библиотеки I2C шины.
#include <Wire.h>
//Подключение библиотеки удаленного управления.
#include "IRremote.h"
//Побключение библиотеки управления моторами.
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
int keg_colour = 8;
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
  Calc_CompensatorZ(3000);
  //переводим пин светодиода в режим вывода.
  pinMode(diod_pin, OUTPUT);
  // Пин датчика цвета кегли в режим ввода.
  pinMode(keg_colour, INPUT);
  //Serial.begin(9600);
  digitalWrite(diod_pin, 1);
  delay(500);
  digitalWrite(diod_pin, 0);
  irrecv.enableIRIn();
}
// Основная программа.
void loop()
{
  bool start = false;
  while (!start)
  {
    if (irrecv.decode(&results))
    {
      //Если нажата кнопка "вперед" - стартуем
      if (results.value == 0x511DBB)
      {
        start = true;
        digitalWrite(diod_pin, 1);
      }
      irrecv.resume();
    }
  }
  while (start)
  {
    //Если сработал датчик
    // Датчик когда срабатывает - сбрасывается в ноль,
    // иначе он установлен в единицу.
    if (!digitalRead(keg_colour)) //есть белая кегля
    {
      //Время движения к кегле и
      //от кегли определяется экспериментом.
      forward_t(300000); // в мик.сек.
      _stop();
      backward_t(300000);
      _stop();
    }
    Angle(45);
    if (irrecv.decode(&results))
    {
      //Если нажата кнопка "стоп" - останавливаемся
      if (results.value == 0xD7E84B1B)
      {
        start = false;
        digitalWrite(diod_pin, 0);
      }
      irrecv.resume();
    }
  }
}

