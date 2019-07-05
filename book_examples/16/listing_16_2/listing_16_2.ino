#include <SoftwareSerial.h>
#include "DFPlayer_Mini_Mp3.h"
// Библиотека для работы с протоколом I2C (порты A5/SCL и A4/SDA)
#include <Wire.h>
// Подключаем библиотеку управления сервомоторами.
#include <Servo.h>
// Подключаем библиотеку, управляющую моторами.
#include "motor.h"
// Подключаем библиотеку, управляющую дальномером.
#include "sonar.h"
//Подключение библиотеки управления гироскопом.
#include "gyro_acsel.h"
// Создание последовательного соединения.
SoftwareSerial DFPSerial(15, 16);
// Создаем сервомотор поворта головы.
Servo neck;
// Константы - постоянные значения для уточнения углов.
#define left_ang 180
#define front_ang 135
#define right_ang 70
#define robot_length 30
#define servo_pin 14
// Создаем переменные для хранения трех дистанций - слева, впереди, справа.
int Dist_left, Dist_front, Dist_right;
// Функция осмотра препятствий роботом,
// ее тело ниже основной программы.
void look();
// Инициализация.
void setup () {
  //запуск гироскопа.
  giroscop_setup();
  // Инициализируем дальномер Trig = 13, Echo = 12.
  Sonar_init(13, 12);
  // Переменные — номера контактов (пинов) Arduino.
  // Для левых и правых моторов машинки.
  setup_motor_system(2, 3, 5, 4);
  _stop(); //Двигатели остановлены.
  DFPSerial.begin (9600);
  // Привязка созданного последовательного соединения
  // к DFPayer.
  mp3_set_serial (DFPSerial);
  //Расчет компенсации утечки нуля гироскопа.
  Calc_CompensatorZ(3000);
  mp3_set_volume (10);
}
// Основная программа.
void loop ()
{
  _stop();
  mp3_play (1);
  delay(2000);
  look();
  // Если проход достаточно широк.
  if((Dist_right>robot_length/2)&&(Dist_left>robot_length/2))
  {
    if (Dist_front > robot_length)
    {
      mp3_play (2);
      delay(2000);
      forward_t(650000); //в микросекундах.
    }
    else
    {
      if (Dist_right > Dist_left)
      {
        mp3_play (3);
        delay(2000);
        Angle(-90);
      }
      else
      {
        mp3_play (4);
        delay(2000);
        Angle(90);
      }
    }
  }
  else //проход узок
  {
    do
    {
      backward_t(550000); //в микросекундах
      look();
    }
    while ((Dist_right<robot_length/2)||(Dist_left<robot_length/2));
    mp3_play (5);
    delay(2000);
    Angle(180);
  }
}
//==============================================================
void look()
{
  // Инициализируем сервомотор, управление портом servo_pin.
  neck.attach(servo_pin);
  // Поворачиваем голову налево.
  neck.write(left_ang);
  // Ждем, так как поворот занимает небольшое время.
  delay(550);
  // Записываем расстояние до препятствия слева.
  Dist_left = Sonar(50);
  // Поворачиваем голову прямо вперед.
  neck.write(front_ang);
  // Ждем, так как поворот занимает небольшое время.
  delay(550);
  // Записываем расстояние до препятствия впереди.
  Dist_front =  Sonar(50);
  // Поворачиваем голову направо.
  neck.write(right_ang);
  // Ждем, так как поворот занимает небольшое время.
  delay(550);
  // Записываем расстояние до препятствия впереди.
  Dist_right = Sonar(50);
  neck.detach();
}

