// Объявляем переменные для хранения состояния двух моторов.
int motor_L1, motor_L2;
int motor_R1, motor_R2;
// Функция инициализации уравления моторами.//////////////////////////////
void setup_motor_system(int L1, int  L2,  int  R1, int R2)
{
  // Заносим в переменные номера контактов (пинов) Arduino.
  motor_L1 = L1; motor_L2 = L2;
  // Для левых и правых моторов машинки.
  motor_R1 = R1; motor_R2 = R2;
  // Переводим указанные порты в состояние вывода данных.
  pinMode(motor_L1, OUTPUT);
  pinMode(motor_L2, OUTPUT);

  pinMode(motor_R1, OUTPUT);
  pinMode(motor_R2, OUTPUT);
}
// движение вперед./////////////////////////////////////////////////////////
void forward()
{
  // Если двигатель будет работать не в ту сторону,
  // поменять на нем контакты местами.
  digitalWrite(motor_L1, HIGH);
  digitalWrite(motor_L2, LOW);
  digitalWrite(motor_R1, HIGH);
  digitalWrite(motor_R2, LOW);
}
// Поворот налево с блокировкой левых колес.//////////////////////////////
void forward_left()
{
  // блокируем вращение левых колес.
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_L2, LOW);
  // правые колеса вращаются.
  digitalWrite(motor_R1, HIGH);
  digitalWrite(motor_R2, LOW);
}
// Поворот налево.////////////////////////////////////////////////////////
void left()
{
  // левые колеса вращаются назад
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_L2, HIGH);
  // правые колеса вращаются.
  digitalWrite(motor_R1, HIGH);
  digitalWrite(motor_R2, LOW);
}
// Поворот направо с блокировкой правых колес.///////////////////////////
void forward_right()
{
  // левые колеса вращаются.
  digitalWrite(motor_L1, HIGH);
  digitalWrite(motor_L2, LOW);
  // блокируем вращение правых колес.
  digitalWrite(motor_R1, LOW);
  digitalWrite(motor_R2, LOW);
}
///////////////////////////////////////////////////////////////////////
void right()
{
  // левые колеса вращаются.
  digitalWrite(motor_L1, HIGH);
  digitalWrite(motor_L2, LOW);
  //правые колеса вращаются назад.
  digitalWrite(motor_R1, LOW);
  digitalWrite(motor_R2, HIGH);
}
// Включаем движение назад.////////////////////////////////////////////
void backward()
{
  // Меняем направление вращения двигателей.
  digitalWrite(motor_L2, HIGH);
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_R2, HIGH);
  digitalWrite(motor_R1, LOW);
}
//////////////////////////////////////////////////////////////////
void backward_left()
{
  // Меняем направление вращения двигателей.
  digitalWrite(motor_L2, LOW);
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_R2, HIGH);
  digitalWrite(motor_R1, LOW);
}
///////////////////////////////////////////////////////////////
void backward_right()
{
  // Меняем направление вращения двигателей.
  digitalWrite(motor_L2, HIGH);
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_R2, LOW);
  digitalWrite(motor_R1, LOW);
}
// Остановка////////////////////////////////////////////////////
void _stop()
{
  // Блокируем все колеса.
  digitalWrite(motor_L2, LOW);
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_R2, LOW);
  digitalWrite(motor_R1, LOW);
}
