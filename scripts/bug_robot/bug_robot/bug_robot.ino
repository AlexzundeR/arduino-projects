
int ENA, ENB, BARIER;
int speed, freq, drive_power;
void setup() {
  ENA=6;
  ENB=9;
  BARIER=0;

  freq = 15;
  speed = 6;
  drive_power = 255;
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Переменные – номера контактов (пинов) Arduino.
  // Для левых и правых моторов машинки.
  setup_motor_system(2, 3, 4, 5);
  _stop(); //Двигатели остановлены.

  pinMode(BARIER, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  //forward();
  //for (int i =0; i<255; i+=10){
  //  analogWrite(ENA,i);
  //  analogWrite(ENB,i);
  //  delay(300);

  //  Serial.print("Now speed = "+ i);
  //}

  analogWrite(ENA,drive_power);
  analogWrite(ENB,drive_power);
  
  while(hasBarier()){
    Serial.print("Move backward");
    for (int i=0;i<2;i++){
      backward();
      applySpeed();
    }
    for (int i=0;i<2;i++){
      left();
      applySpeed();
    }
  }
  // put your main code here, to run repeatedly:
  forward();
  Serial.print("Move forward");

  applySpeed();
}

void applySpeed(){
  delay(freq*speed);
  _stop();
  delay(freq*(10-speed));
}

bool hasBarier(){
  return !digitalRead(BARIER);
}

// Объявляем переменные для хранения состояния двух моторов.
int motor_L1, motor_L2;
int motor_R1, motor_R2;
//===============================================
// Функция инициализации управления моторами.
void setup_motor_system(int L1, int  L2, int  R1, int R2)
{
  // Заносятся в переменные номера контактов (пинов) Arduino.
  motor_L1 = L1; motor_L2 = L2;
  // Для левых и правых моторов робота.
  motor_R1 = R1; motor_R2 = R2;
  // Переводятся указанные порты в состояние вывода данных.
  pinMode(motor_L1, OUTPUT);
  pinMode(motor_L2, OUTPUT);
  pinMode(motor_R1, OUTPUT);
  pinMode(motor_R2, OUTPUT);
}
//===============================================
// движение вперед.
void forward()
{
  // Если двигатель будет работать не в ту сторону,
  // поменять на нем контакты местами.
  digitalWrite(motor_L1, HIGH);
  digitalWrite(motor_L2, LOW);
  digitalWrite(motor_R1, HIGH);
  digitalWrite(motor_R2, LOW);
}

//===============================================
// Поворот налево с блокировкой левых колес.
void forward_left()
{
  // блокировка вращения левых колес.
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_L2, LOW);
  // правые колеса вращаются.
  digitalWrite(motor_R1, HIGH);
  digitalWrite(motor_R2, LOW);
}
//===============================================
// Поворот направо с блокировкой правых колес.
void forward_right()
{
  // левые колеса вращаются.
  digitalWrite(motor_L1, HIGH);
  digitalWrite(motor_L2, LOW);
  // блокировка вращения правых колес.
  digitalWrite(motor_R1, LOW);
  digitalWrite(motor_R2, LOW);
}
// Поворот налево на месте.
void left()
{
  // левые колеса вращаются назад.
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_L2, HIGH);
  // правые колеса вращаются вперед.
  digitalWrite(motor_R1, HIGH);
  digitalWrite(motor_R2, LOW);
}
//===============================================
// Поворот направо на месте.
void right()
{
  // левые колеса вращаются вперед.
  digitalWrite(motor_L1, HIGH);
  digitalWrite(motor_L2, LOW);
  // правые колеса вращаются назад.
  digitalWrite(motor_R1, LOW);
  digitalWrite(motor_R2, HIGH);
}


// Включаем движение назад.
void backward()
{
  // Смена направления вращения двигателей.
  digitalWrite(motor_L2, HIGH);
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_R2, HIGH);
  digitalWrite(motor_R1, LOW);
}
//===============================================
// Включаем движение назад.
void backward_left()
{
  // Смена направления вращения двигателей.
  digitalWrite(motor_L2, LOW);
  digitalWrite(motor_L1, HIGH);
  digitalWrite(motor_R2, HIGH);
  digitalWrite(motor_R1, LOW);
}
//===============================================
// Включаем движение назад.
void backward_right()
{
  // Смена направления вращения двигателей.
  digitalWrite(motor_L2, HIGH);
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_R2, LOW);
  digitalWrite(motor_R1, HIGH);
}
//===============================================

void _stop()
{
  // Блокировка всех колес.
  digitalWrite(motor_L2, LOW);
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_R2, LOW);
  digitalWrite(motor_R1, LOW);
}
