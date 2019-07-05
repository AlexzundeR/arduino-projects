// Подключаем библиотеку управления сервомоторами.
#include <Servo.h>
// Подключаем библиотеку управляющую моторами.
#include "motor.h"
// Подключаем библиотеку управляющую дальномером.
#include "sonar.h"

// Создаем сервомотор поворота головы.
Servo neck;

// Константы - постоянные значения для уточнения углов.
// поворота головы.
// Эти значения нужно уточнить для вашего робота!
const int left_ang = 180;
const int front_ang = 90;
const int right_ang = 0;
// Временные константы служат для точного задания времени на поворот,
//  разворот, движение вперед в миллисекундах.
// Эти значения нужно уточнить для вашего робота!
const int time_turn_90 = 390;
const int time_turn_180 = 750;
const int time_move_30cm = 220;
// Длина робота.
// Эти значения нужно уточнить для вашего робота!
const int robot_length = 18;
// Эти значения нужно уточнить для вашего робота!
//Максимальная скорость не может превышать 255.
const int max_speed = 255;
//Минимальная скорость, ниже которой колеса уже не вращаются.
const int min_speed = 155;

const int sonar_between_delay = 350;

void setup()
{
  Serial.begin(9600);
   // Инициализируем дальномер Trig = 13, Echo = 12.
  Sonar_init(13, 12);
  // Инициализируем сервомотор, управление 9 портом.
  neck.attach(14);
  // Переменные – номера контактов (пинов) Arduino.
  // Для левых и правых моторов машинки.
  setup_motor_system(2, 3, 5, 4);
  _stop(); //Двигатели остановлены.
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
  delay(sonar_between_delay);
  // Записываем расстояние до препятствия слева.
  Dist_left = Sonar(400);
  // Поворачиваем голову прямо вперед.
  neck.write(front_ang);
  // Ждем, так как поворот занимает небольшое время.
  delay(sonar_between_delay);
  // Записываем расстояние до препятствия впереди.
  Dist_front =  Sonar(400);
  // Поворачиваем голову направо.
  neck.write(right_ang);
  // Ждем, так как поворот занимает небольшое время.
  delay(sonar_between_delay);
  // Записываем расстояние до препятствия впереди.
  Dist_right = Sonar(400);
  //Заранее даем команду повернуть голову влево,
  //это уменьшит время остановок робота на анализ местности.
  neck.write(left_ang);

  Serial.print("Front:");
  Serial.println(Dist_front);
  Serial.print("Left:");
  Serial.println(Dist_left);
  Serial.print("Right:");
  Serial.println(Dist_right);

  // Если габариты робота позволяют движение вперед и развороты.
  if ((Dist_right > ((robot_length / 2) - 2)) && (Dist_left > ((robot_length / 2) - 2)))
  {
    Serial.println("Let's go");
    if (Dist_front > robot_length) //Если можно двигаться вперед
    {
      Serial.println("Forward");
      forward(); // едем вперед 30см.
      delay(time_move_30cm);
    }
    else if (Dist_right > Dist_left)
    {
      Serial.println("Right");
      right(); // поворачиваем направо на 90 градусов.
      delay(time_turn_90);
    }
    else
    {
      Serial.println("Left");
      left(); // поворачиваем направо на 90 градусов.
      delay(time_turn_90);
    }
  }
  else
  {
    Serial.println("Go back to turn left");
    do {
      //Отъезжаем назад от препятствия.
      backward();
      delay(time_move_30cm / 2);
      _stop();
      neck.write(left_ang);
      // Ждем, так как поворот занимает небольшое время.
      delay(350);
      // Записываем расстояние до препятствия слева.
      Dist_left = Sonar(400);
      neck.write(right_ang);
      // Ждем, так как поворот занимает небольшое время.
      delay(350);
      // Записываем расстояние до препятствия впереди.
      Dist_right = Sonar(400);
      //Заранее даем команду повернуть голову влево,
      //это уменьшит время остановок робота на анализ местности.
      neck.write(left_ang);
      // Цикл повторяется, пока есть препятствия для разворота.
    } while ((Dist_right < ((robot_length / 2) - 2)) || (Dist_left < ((robot_length / 2) - 2)));
    //разворачиваем робота.
    left(); delay(time_turn_180);
  }
}
