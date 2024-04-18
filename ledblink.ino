

void setup()
{

  pinMode(2,OUTPUT);
   pinMode(3,OUTPUT);
    pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
   pinMode(8,OUTPUT);

}

void loop()

{

  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  delay(200);
  
  digitalWrite(3, HIGH);
  delay(500);
  digitalWrite(3, LOW);
  delay(200);
  
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(4, LOW);
  delay(200);

    digitalWrite(5, HIGH);
  delay(500);
  digitalWrite(5, LOW);
  delay(200);

    digitalWrite(8, HIGH);
  delay(500);
  digitalWrite(8, LOW);
  delay(200);
}
