// Подключаем библиотеку, управляющую моторами.
#include "motor.h"
// Временные константы служат для точного задания времени на поворот, разворот, движение вперед
// в миллисекундах.
const int time_90=390;
const int time_180=750;
const int time_10cm=220;
// Номера портов, к которым подключены датчики препятствия.
const int  Front1=8, Front2=9, Right=7;

//=========================================
void setup()
{
  // Заносим в переменные номера контактов (пинов) Arduino.
 // Для левых и правых моторов машинки.
  setup_motor_system(2, 3, 4, 5);
  // Остановка.
  _stop();
  
  // Инициализируем порты датчиков препятствия.
  pinMode(Front1, INPUT);
  pinMode(Front2, INPUT);
  pinMode(Right, INPUT);
 
  // Устанавливаем скорость передачи данных по кабелю.
  // Порт компьютера
  //Serial.begin(9600);
}
// Основная программа.
void loop()
{
  boolean d_Front1, d_Front2, d_Right;
  d_Front1 = digitalRead(Front1); d_Front2 = digitalRead(Front2); d_Right = digitalRead(Right);

  // Если ни один датчик не сработал.
  if (d_Front1 && d_Front2 && d_Right)
  {
    forward_right();//подворот вправо.
    delay(time_90 / 9);
    forward(); // едем вперед.
    delay(time_10cm / 2);
  }
  else
  {
    //Если сработал один из передних датчиков и не сработал правый.
    if ((!d_Front1) || (!d_Front2))
    {
      //Если не сработал правый датчик.
      if (d_Right)
      {
        // поворачиваем направо на 90 градусов.
        right(); 
        delay(time_10cm);
      }
      else
      {
        // поворачиваем налево на 90 градусов.
        left();
        delay(time_10cm);
      }
    }
    else
    { // Если сработал правый датчик.
      forward_left();//подворот влево.
      delay(time_90 / 9);
      forward(); // едем вперед.
      delay(time_10cm / 2);
    }
  }
}

