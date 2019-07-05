// константы
#define  dirpin 4
#define  steppin 5
#define MS1 11
#define MS2 3
#define Enable 2
#define Sleep 12
//====================
void setup()
{
  pinMode(dirpin, OUTPUT);
  pinMode(steppin, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(Enable, OUTPUT);
  pinMode(Sleep, OUTPUT);
  // Отключаем обмотки двигателя.
  digitalWrite(Enable, HIGH);
  //= Разбудим драйвер.
  digitalWrite(Sleep, LOW);
  //= Зададим минимальную величину шага.
  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, HIGH);
  //= Ждем шага.
  digitalWrite(steppin, LOW);
  //Задали направление.
  digitalWrite(dirpin, LOW);
  // Подключаем обмотки двигателя.
  digitalWrite(Enable, LOW);
}
//==========================================
void loop()
{
  int i;
  // Устанавливаем направление.
  digitalWrite(dirpin, LOW); 
  delay(100);
  // итерации повторяются для 4000 микрошагов.
  for (i = 0; i < 4000; i++) 
  { //Делаем шаг.
    digitalWrite(steppin, HIGH);
    delayMicroseconds(500);
    digitalWrite(steppin, LOW);
    delayMicroseconds(50);
  }
  digitalWrite(dirpin, HIGH); // Смена направления.
  delay(100);
  // итерации повторяются для 4000 микрошагов.
  for (i = 0; i < 4000; i++)
  { //Делаем шаг.
    digitalWrite(steppin, HIGH);
    delayMicroseconds(500);
    digitalWrite(steppin, LOW);
    delayMicroseconds(50);
  }
}


