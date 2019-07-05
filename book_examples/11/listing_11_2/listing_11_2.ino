// Подключаем библиотеку управления сервомоторами.
#include <Servo.h>
// Подключаем библиотеку, управляющую моторами.
#include "motor.h"
// Подключаем библиотеку, управляющую дальномером.
#include "sonar.h"

// Создаем сервомотор поворота головы.
Servo neck;
// Константы - постоянные значения для уточнения углов.
const int left_ang = 168;
const int front_ang = 98;
const int right_ang = 28;
// Временные константы служат для точного задания времени на поворот, 
//разворот, движение вперед
// в миллисекундах.
const int time_90 = 390;
const int time_180 = 750;
const int time_10cm = 220;

void setup()
{
  // Инициализируем дальномер Trig = 13, Echo = 12.
  Sonar_init(13, 12);
  // Инициализируем сервомотор, управление 9 портом.
  neck.attach(14);
  // Переменные – номера контактов (пинов) Arduino.
  // Для левых и правых моторов машинки.
  setup_motor_system(2, 3, 4, 5);
  _stop(); //Двигатели остановлены.
  Serial.begin(9600);
}
// Основная программа.
void loop()
{
  _stop();
  // Создаем переменные для хранения трех дистанций - слева, впереди, справа.
  int Dist_left, Dist_front, Dist_right;
  // Поворачиваем голову налево.
  neck.write(left_ang);
  // Ждем, так как поворот занимает небольшое время.
  delay(1500);
  // Записываем расстояние до препятствия слева.
  Dist_left = Sonar(400);
  Serial.print("Dist_left="); // оформляем вывод.
  // выводим дистанцию.
  Serial.print(Dist_left);
  Serial.println(" cm."); // оформляем вывод.
  // приостанавливаем программу.
  delay(500);
  // Поворачиваем голову прямо вперед.
  neck.write(front_ang);
  // Ждем, так как поворот занимает небольшое время.
  delay(1500);
  // Записываем расстояние до препятствия впереди.
  Dist_front = Sonar(400);
  Serial.print("Dist_front="); // оформляем вывод.
  // выводим дистанцию.
  Serial.print(Dist_front);
  Serial.println(" cm."); // оформляем вывод.
  // приостанавливаем программу.
  delay(500);
  // Поворачиваем голову направо.
  neck.write(right_ang);
  // Ждем, так как поворот занимает небольшое время.
  delay(1500);
  // Записываем расстояние до препятствия впереди.
  Dist_right = Sonar(400);
  Serial.print("Dist_right="); // оформляем вывод.
  // выводим дистанцию.
  Serial.print(Dist_right);
  Serial.println(" cm."); // оформляем вывод.
  // приостанавливаем программу.
  delay(500);
  neck.write(front_ang);
  // оформляем вывод.
  Serial.println(" ------------------------."); 
  // Если расстояние до препятствия слева наибольшее.
  if ((Dist_left > Dist_front) && (Dist_left > Dist_right))
  {
    // оформляем вывод.
Serial.println("(Dist_left>Dist_front)&&(Dist_left>Dist_right)POVOROT LEFT");
    // приостанавливаем программу.
    delay(500);
    left(); // поворачиваем налево 0,5 секунд.
    delay(time_90);
    if (Dist_left > 10)
    {
      // оформляем вывод.
      Serial.println(" Dist_left>10 VPERED 0.5 SEC"); 
      // приостанавливаем программу.
      delay(500);
      forward(); // едем вперед 0,5 секунды.
      delay(time_10cm);
    }
  }
  else
  {
    if (Dist_right > Dist_front)
    {
      // оформляем вывод.
      Serial.println(" Dist_right>Dist_front POVOROT RIGHT"); 
      // приостанавливаем программу.
      delay(500);
      right(); // поворачиваем направо 0,5 секунд.
      delay(time_90);
      if (Dist_right > 10)
      {
        // оформляем вывод.
        Serial.println(" Dist_right>10 VPERED 0.5 SEC"); 
        // приостанавливаем программу.
        delay(500);
        forward(); // едем вперед 0,5 секунды.
        delay(time_10cm);
      }
    }
    else
    {
      if (Dist_front > 10)
      {
        // оформляем вывод.
        Serial.println(" Dist_front>10 VPERED 0.5 SEC");         
        // приостанавливаем программу.
        delay(500);
        forward(); // едем вперед 0,5 секунды.
        delay(time_10cm);
      }
      else
      {
        // оформляем вывод.
        Serial.println(" right **********RAZVOROT*************"); 
        // приостанавливаем программу.
        delay(500);
        right(); // разворачиваемся.
        delay(time_180);
      }
    }
  }
}

