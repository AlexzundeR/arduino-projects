    // Подключаем библиотеку для создания дополнительных последовательных (Serial) портов 
    #include <SoftwareSerial.h> 

    //Создаем последовательный порт на пинах 13-чтение и 2-передача
    SoftwareSerial BTSerial(10, 11); // RX, TX
    // Переменная для приема данных по Bluetooth
    char bt_input;

    void setup()
    {
     // Устанавливаем скорость передачи данных для НС-05 (Bluetooth модуль)
     BTSerial.begin(38400);
     // Переключаем A0 в двоичный режим работы, на передачу
//delay(10);
     // Присваиваем HC-05 новое имя - MaxiBot
     //BTSerial.println("AT+ROLE1");
     //BTSerial.println("AT+NAMESEREBRO");
    // BTSerial.println("AT+BAUD6");
    BTSerial.println("AT+HELP");
     //BTSerial.println("AT+ROLE");
    //BTSerial.println("AT+NAMEROBOPES");
     // Устанавливаем скорость передачи данных по кабелю
     // Порт компьютера
      Serial.begin(57600);
     // переводим HC-05 в нормальный режим работы
   
     
    }
    void loop()
    {
      // Если пришли данные по Bluetooth
      while (BTSerial.available())
      {
        // Записываем, что пришло от Bluetooth в переменную bt_input
        bt_input = (char)BTSerial.read();
        Serial.print(bt_input);
      }
     // BTSerial.println("AT+RESET");
      //delay(100);
      //Serial.println("");
    }

