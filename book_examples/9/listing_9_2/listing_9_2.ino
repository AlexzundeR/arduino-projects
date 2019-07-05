#include "motor.h"
unsigned long _time;
//====================================
int left_sensor_line = 9;
int right_sensor_line = 8;
//====================================
void setup()
{
  // Переменные – номера контактов (пинов) Arduino.
  // Для левых и правых моторов машинки.
  setup_motor_system(2, 3, 4, 5);
  _stop(); //Двигатели остановлены.
  // Сенсорные пины переводим в состояние ввода данных.
  pinMode(left_sensor_line, INPUT);
  pinMode(right_sensor_line, INPUT);
  _time = millis();
  // Устанавливаем скорость порта связи с ПК.
  Serial.begin(9600);
}
// Основная программа.
void loop()
{
  while (true)
  {
    bool ls = digitalRead(left_sensor_line);
    bool rs = digitalRead(right_sensor_line);
    //   Serial.println(ls);
    //   Serial.println(rs);
    //   Serial.println("======================================");
    //  delay(500);
    //Готов к приему.
    if ((!ls) && (!rs))
    {
      forward();
    }
    else
    {
      if (ls)
      {
        left();
      }
      else
      {
        right();
      }
    }
    delayMicroseconds(500);
    _stop();
    delayMicroseconds(100);
  }
}

