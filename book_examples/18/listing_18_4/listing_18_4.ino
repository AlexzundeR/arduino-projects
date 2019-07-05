#include <Wire.h>
#include "Adafruit_PWMServoDriver.h"
#define maxservo 700
#define minservo 180
// Создаем объект "серводрайвер"
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int i;
void setup() {
  pwm.begin();
  pwm.setPWMFreq(70);  // Задаем частоту 
  //Устанавливаем сервомоторы в центральное положение.
for (i = 0; i < 4; i++)  pwm.setPWM(i, 0, (maxservo - minservo) / 2);
}
//=================================
void loop() {
  delay(1000);
  for (i = 0; i < 4; i++)   pwm.setPWM(i, 0, maxservo);
  delay(1000);
  for (i = 0; i < 4; i++)   pwm.setPWM(i, 0, minservo);
}


