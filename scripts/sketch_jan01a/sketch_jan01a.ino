
int In1, In2, In3, In4;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);

  In1 = 2;
  In2 = 3;
  In3 = 4; 
  In4 = 5;

  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);

}

void loop() {
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);

  delay(1000);

  digitalWrite(In1, HIGH);
    delay(1000);
  digitalWrite(In1, LOW);

  digitalWrite(In2, HIGH);
    delay(1000);
  digitalWrite(In2, LOW);

  digitalWrite(In3, HIGH);
    delay(1000);
  digitalWrite(In3, LOW);

  digitalWrite(In4, HIGH);
    delay(1000);
  digitalWrite(In4, LOW);
}
