//Порт, подключенный к ST_CP 74HC595
#define latchPin 5
//Порт, подключенный к SH_CP  74HC595
#define clockPin 4
//Порт, подключенный к DS 74HC595
#define dataPin 6
//================================= 
 void setup() {
  //устанавливаем режим порта выхода
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
//================================= 
void loop() {
  for (int j = 0; j <= 255; j++) {
    //устанавливаем LOW на latchPin 
    //пока не окончена передача байта.
    digitalWrite(latchPin, LOW);
     //MSBFIRST (Most Significant Bit First) - слева.
     //LSBFIRST (Least Significant Bit First) — справа.
    shiftOut(dataPin, clockPin, LSBFIRST, j);  
    //устанавливаем HIGH на latchPin, 
    //чтобы проинформировать регистр, что передача окончена.
    digitalWrite(latchPin, HIGH);
    delay(1000);
  }
}

