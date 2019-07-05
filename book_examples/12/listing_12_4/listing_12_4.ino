// Подключаем библиотеку, управляющую моторами.
#include "motor.h"
// Временные константы служат для точного задания времени на поворот, разворот, движение вперед
// в миллисекундах.
const int time_90=190;
const int time_10=20;
const int time_180=380;
const int time_10cm=100;
// Номера портов, к которым подключены датчики препятствия.
const int  Front1=8, Front2=9, Right=7;

void avtoroute()
{
  boolean d_Front1, d_Front2, d_Right;
  d_Front1=digitalRead(Front1); d_Front2=digitalRead(Front2); d_Right=digitalRead(Right);
  // Ищем правую сторону.
  // Если ни один датчик не сработал.
  if(d_Front1&&d_Front2&&d_Right)
  {
    forward_right();//подворот вправо.
    delay(3);//time_10cm/5);
    forward(); // едем вперед.
    delayMicroseconds(500);
  }
  else
  {
    //Если сработал один из передних датчиков. 
    if(((!d_Front1)||(!d_Front2))&&d_Right)
    {      
      // поворачиваем направо на 90 градусов.
      right(); 
      //delay(time_10);
      delayMicroseconds(500);
    }
    else
    //Если сработал один из передних датчиков и правый. 
    if(((!d_Front1)||(!d_Front2))&&(!d_Right))
    {
      // поворачиваем налево на 90 градусов.
      left(); 
      //delay(time_10);
      delayMicroseconds(500);
    }
    else
    { // Отклоняемся от правой стороны
      // Если сработал правый датчик.
      forward_left();//подворот влево.
      delay(3);//time_90/5);
      forward(); // едем вперед.
      delayMicroseconds(500);
    }
  }
// Регулировка скорости робота.
//  _stop();
//  delayMicroseconds(100);
  
}

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
    avtoroute();
}

