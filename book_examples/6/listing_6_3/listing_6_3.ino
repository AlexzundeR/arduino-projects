//Создадим переменные для хранения номеров используемых пинов/портов Arduino.
int In1, In2, In3, In4, InZ;
//Настройка
void setup() {
  // Присвоим переменным номера пинов Arduino.
  InZ = 6;
  pinMode(InZ, OUTPUT);
  In1 = 2;
  In2 = 3;
  In3 = 4;
  In4 = 5;

  //Переведем данные пины/порты в режим вывода.
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
}
//Тело программы
void loop() {
  for (int i = 0; i < 10; i++)
  {
    tone(InZ, 1000);
    delay(100);
    noTone(InZ);
    delay(100);
  }
  delay(1000);
}

