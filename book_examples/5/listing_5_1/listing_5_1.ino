//Создадим переменные для хранения номеров используемых пинов/портов Arduino.
int In1, In2, In3, In4;
//Настройка
void setup() {
  // Присвоим переменным номера пинов Arduino.
  In1 = 5;
  In2 = 4;
  In3 = 3;
  In4 = 2;
  //Переведем данные пины/порты в режим вывода.
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
}
//Тело программы
void loop() {
  //Отключим оба двигателя.
  digitalWrite(In1, LOW); //двигатель М2.
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW); //двигатель М1.
  digitalWrite(In4, LOW);
  delay(1000); // Ждем 1 сек.
  //Включим двигатель М2.
  digitalWrite(In1, LOW);  //двигатель М2.
  digitalWrite(In2, HIGH);
  delay(1000); // Ждем 1 сек.
  // Вращаем двигатель М2 в другую сторону.
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  delay(1000); // Ждем 1 сек.
   // Проделайте те же операции для двигателя M1 самостоятельно.
  // ....
}

