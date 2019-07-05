// Библиотека для работы с протоколом I2C (порты A5/SCL и A4/SDA)
#include <Wire.h>
const int MPU_addr = 0x68; // упрощенный
               // I2C-адрес нашего гироскопа/акселерометра MPU-6050.
// переменные для хранения данных, возвращаемых прибором.
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
//==============================================
void setup()
{
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  // Производим запись в регистр энергосбережения MPU-6050
  Wire.write(0x6B);    
  Wire.write(0);     // устанавливаем его в ноль.
  Wire.endTransmission(true);
  Serial.begin(9600);
}
//================ НАЧАЛО ====================
void loop()
{
  Wire.beginTransmission(MPU_addr);
  //Готовим для чтения регистры с адреса 0x3B.
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  // Запрос состояния 14 регистров.
  Wire.requestFrom(MPU_addr, 14, true);
  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcX = Wire.read() << 8 | Wire.read();
  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcY = Wire.read() << 8 | Wire.read();
  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  AcZ = Wire.read() << 8 | Wire.read();
  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  Tmp = Wire.read() << 8 | Wire.read();
  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyX = Wire.read() << 8 | Wire.read();
  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyY = Wire.read() << 8 | Wire.read();
  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  GyZ = Wire.read() << 8 | Wire.read();
  // Вывод в порт данных, полученных от прибора.
  Serial.print("  AcX="); Serial.print(AcX);
  Serial.print("  AcY="); Serial.print(AcY);
  Serial.print("  AcZ="); Serial.println(AcZ);
  Serial.print("  GyX="); Serial.print(GyX);
  Serial.print("  GyY="); Serial.print(GyY);
  Serial.print("  GyZ="); Serial.println(GyZ);
  delay(1000);
}

