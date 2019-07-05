void setup() // Настройка
{
 //Устанавливаем скорость порта связи Arduino - ПК.
 Serial.begin(9600);
}
// Основная программа
void loop() 
{
  char char1;
 // если поступили данные.
 if (Serial.available() > 0) 
 {
  // считываем символ.  
  char1 = Serial.read();
  // отсылаем то, что получили, обратно на ПК.
  Serial.println(char1);
 }
}

