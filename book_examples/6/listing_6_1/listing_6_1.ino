//Создадим переменные для хранения номеров используемых пинов/портов Arduino.
int In1, In2, In3, In4;
//Настройка
void setup() {
  // Присвоим переменным номера пинов Arduino.
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
  //Остановить все двигатели.
  digitalWrite(In1, LOW); //Правые двигатели на роботе.
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW); //Левые двигатели на роботе.
  digitalWrite(In4, LOW);
  delay(1000); // Ждем 1 сек.

  //Включить-выключить поочередно левые и правые двигатели
  digitalWrite(In1, HIGH); //Включили один правый двигатель на роботе.
  delay(1000); // Ждем 1 сек.
  digitalWrite(In1, LOW); //Выключили

  digitalWrite(In2, HIGH); //Включили другой правый двигатель на роботе.
  delay(1000); // Ждем 1 сек.
  digitalWrite(In2, LOW); //Выключили

  digitalWrite(In3, HIGH); //Включили один левый двигатель на роботе.
  delay(1000); // Ждем 1 сек.
  digitalWrite(In3, LOW); //Выключили

  digitalWrite(In4, HIGH); //Включили другой левый двигатель на роботе.
  delay(1000); // Ждем 1 сек.
  digitalWrite(In4, LOW); //Выключили
}




