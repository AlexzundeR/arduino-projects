#include <SoftwareSerial.h>
#include "DFPlayer_Mini_Mp3.h"
// Создание последовательного соединения.
SoftwareSerial DFPSerial(15, 16);
// Инициализация.
void setup () {
  DFPSerial.begin (9600);
  // Привязка созданного последовательного соединения
  // к DFPayer.
  mp3_set_serial (DFPSerial);  
  delay(1);  //
  mp3_set_volume (15);
}
// Основная программа.
void loop ()
{
//6 секунд играть 001.mp3 .
  mp3_play (1);
  delay (6000);
//6 секунд играть 002.mp3 .
  mp3_play (2);
  delay (6000);
//6 секунд играть 003.mp3 .
  mp3_play (3);
  delay (6000);
//6 секунд играть 004.mp3 .
  mp3_play (4);
  delay (6000);
//6 секунд играть 005.mp3 .
  mp3_play (5);
  delay (6000);
  for (int i = 0; i < 4; i++)
  {
    // играть предыдущий файл.
    mp3_prev ();
    delay (6000);
  }
  for (int i = 0; i < 4; i++)
  {
    // играть следующий файл.
    mp3_next ();
    delay (6000);
  }
}

