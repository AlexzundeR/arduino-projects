//Определение функции 
int sravnenie(int a, int b);
void setup() {
}
void loop() {
  int x=10;
  int y=25;
// Вызов функции sravnenie().
  int s=sravnenie(x,y);
}
// Определение функции sravnenie ().
// Указываем тип возвращаемого значения, имя функции и информацию о формальных аргументах.
int sravnenie(int a, int b) 
// Далее идет тело функции
{
  if(a<b) return b;
  else return a;
}

