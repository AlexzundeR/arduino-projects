#include "ShiftRegister595.h"
//Порт, подключенный к ST_CP 74HC595
#define latchPin 5
//Порт, подключенный к SH_CP  74HC595
#define clockPin 4
//Порт, подключенный к DS 74HC595
#define dataPin 6
ShiftRegister595 shReg( latchPin , clockPin , dataPin );
void setup() {
  randomSeed(analogRead(0));
}
void loop() {
  for (int j = 0; j < 256; j++) 
  {
    shReg.write(random(0,255));
    shReg.write(random(0,255));
    shReg.write(j);
    delay(1000);
  }
}

