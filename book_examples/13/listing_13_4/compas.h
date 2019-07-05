#include <EEPROM.h>

#define address 0x1E
//Подключаю функции управления мотороами
//#include "motors.h"
float  dX, dY, dZ, scaleX, scaleY;
//////////////////////////////////////////////////////////////////////////////////
void write_int_to_eeprom(int ny, int data) //Младший адрес и переменная
{
  byte temp = data;// младший байт;
  EEPROM.write(ny, temp);
  temp = data >> 8;
  EEPROM.write(ny + 1, temp);
}
//////////////////////////////////////////////////////////////////////////////////
int read_int_from_eeprom(int ny) //Младший адрес и переменная
{
  int  temp = EEPROM.read(ny + 1) << 8; //старший байт
  temp |= EEPROM.read(ny); //младший байт
  return temp ;
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void compas_read(int &x, int &z, int &y)
{
  int xx, yy, zz;
  Wire.beginTransmission(address);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  Wire.requestFrom(address, 6);
  if (6 <= Wire.available())
  {
    xx = Wire.read() << 8;    xx |= Wire.read();
    zz = Wire.read() << 8;    zz |= Wire.read();
    yy = Wire.read() << 8;    yy |= Wire.read();
  }
  x  = xx; y = yy; z = zz;
}
//////////////////////////////////////////////////////////////////////////////////
void compas_max_min_to_eeprom()
{
  const int time_micro_stop = 150;
  int minx, zerroYminX, miny, zerroXminY, minz;
  int maxx, zerroYmaxX, maxy, zerroXmaxY, maxz;
  int x,y,z;
  for(int i=0;i<1;i++)
  {
  compas_read(x, z, y);
  minx = maxx = x;
  miny = maxy = y;
  minz = maxz = z;
  int j=0;
  do {
    int x, y, z; //triple axis data
    compas_read(x, z, y);
    if (x < minx) {
      minx = x;
      zerroYminX = y;
    }
    if (y < miny) {
      miny = y;
      zerroXminY = x;
    }
    if (z < minz) {
      minz = z;
    }

    if (x > maxx) {
      maxx = x;
      zerroYmaxX = y;
    }
    if (y > maxy) {
      maxy = y;
      zerroXmaxY = x;
    }
    if (z > maxz) {
      maxz = z;
    }
    left();
    delay(15);
    _stop();
    delay(150);
       j++;
  }while (j<700); // В течении минуты крутим робота

  // Записываем значения в EEPROM
  write_int_to_eeprom(i * 20, minx);
  delay(1);
  write_int_to_eeprom(i * 20 + 2, maxx);
  delay(1);
  write_int_to_eeprom(i * 20 + 4, miny);
  delay(1);
  write_int_to_eeprom(i * 20 + 6, maxy);
  delay(1);
  write_int_to_eeprom(i * 20 + 8, minz);
  delay(1);
  write_int_to_eeprom(i * 20 + 10, maxz);
  delay(1);
  write_int_to_eeprom(i * 20 + 12, zerroYminX);
  delay(1);
  write_int_to_eeprom(i * 20 + 14, zerroXminY);
  delay(1);
  write_int_to_eeprom(i * 20 + 16, zerroYmaxX);
  delay(1);
  write_int_to_eeprom(i * 20 + 18, zerroXmaxY);
  delay(1);
}
  write_int_to_eeprom(1000, zerroXmaxY);

}
//////////////////////////////////////////////////////////////////////////////////
void compas_setup_a() {
  Wire.beginTransmission(address);
  //Число замеров=8, скорость записи 75Гц.
  Wire.write(0x00); // A register
  Wire.write(B01111000); //
  Wire.endTransmission();
  //Максимальная чуствительность
  Wire.beginTransmission(address);
  Wire.write(0x01); // B register
  Wire.write(B00000000);
  Wire.endTransmission();
  //режим непрерывного измерения на скорости 3400кГц.
  Wire.beginTransmission(address);
  Wire.write(0x02); //Mode register
  Wire.write(B10000000);
  Wire.endTransmission();
  scaleX=1;
  scaleY=1;
  // Расчитываем корректировки по данным их еепром
  //раскоментировать после пересчета
  dX = 0;//float(read_int_from_eeprom(0) + read_int_from_eeprom(2)) / 2.0;
  dY = 0;//float(read_int_from_eeprom(4) + read_int_from_eeprom(6)) / 2.0;
  dZ = 0;// float(read_int_from_eeprom(8) + read_int_from_eeprom(10)) / 2.0;
  //scaleX = 1.0 / float(read_int_from_eeprom(2) - read_int_from_eeprom(0));
  //scaleY  = 1.0 / float(read_int_from_eeprom(6) - read_int_from_eeprom(4));
}
//////////////////////////////////////////////////////////////////////////////////
void compas_setup() {
  Wire.beginTransmission(address);
  //Число замеров=8, скорость записи 75Гц.
  Wire.write(0x00); // A register
  Wire.write(B01111000); //
  Wire.endTransmission();
  //Максимальная чуствительность
  Wire.beginTransmission(address);
  Wire.write(0x01); // B register
  Wire.write(B00000000);
  Wire.endTransmission();
  //режим непрерывного измерения на скорости 3400кГц.
  Wire.beginTransmission(address);
  Wire.write(0x02); //Mode register
  Wire.write(B10000000);
  Wire.endTransmission();
  scaleX=1;
  scaleY=1;
  // Расчитываем корректировки по данным их еепром
  //раскоментировать после пересчета
  dX = float(read_int_from_eeprom(0) + read_int_from_eeprom(2)) / 2.0;
  dY = float(read_int_from_eeprom(4) + read_int_from_eeprom(6)) / 2.0;
  dZ = float(read_int_from_eeprom(8) + read_int_from_eeprom(10)) / 2.0;
  //scaleX = 1.0 / float(read_int_from_eeprom(2) - read_int_from_eeprom(0));
  //scaleY  = 1.0 / float(read_int_from_eeprom(6) - read_int_from_eeprom(4));
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
float get_Compass_ang() {
  //раскоментировать после пересчета
  int x, y, z; //triple axis data
  Wire.beginTransmission(address);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  Wire.requestFrom(address, 6);
  if (6 <= Wire.available()) {
    x = Wire.read() << 8;    x |= Wire.read();
    z = Wire.read() << 8;    z |= Wire.read();
    y = Wire.read() << 8;    y |= Wire.read();
    //return atan2( (float(y) - dY) * scaleY, (float(x) - dX) * scaleX ) * RAD_TO_DEG;
        return atan2( (float(y) - dY), (float(x) - dX)) * RAD_TO_DEG;
  }
}

//////////////////////////////////////////////////////////////////////////////////
void compas_extremum_to_eeprom()
{
 compas_max_min_to_eeprom();
}

