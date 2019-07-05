// Переменные с номерами пинов, к которым подключены датчики.
int left_sensor_line = 9;
int right_sensor_line = 8;
void setup()
{
  // Перевод пинов в состояние ввода данных.
  pinMode(left_sensor_line, INPUT);
  pinMode(right_sensor_line, INPUT);
  // Устанавливаем скорость порта связи с ПК.
  Serial.begin(9600);
}
// Основная программа.
void loop()
{
    Serial.print("Left sensor =");
    Serial.println(digitalRead(left_sensor_line));
    Serial.print("Right sensor =");
    Serial.println(digitalRead(right_sensor_line));
    Serial.println("======================================");
    delay(500);
}

