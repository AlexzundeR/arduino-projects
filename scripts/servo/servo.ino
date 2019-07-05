#include <Servo.h>

Servo neck;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);

  neck.attach(14);
}

void loop() {

  return;
  digitalWrite(13, HIGH);

  int i;
  for (i = 10; i<=170; i=i+10){
    neck.write(i);
    delay(100);
  }

  for(i=170;i>=10; i=i-10){
    neck.write(i);
    delay(100);
  }

  digitalWrite(13, LOW);
}
