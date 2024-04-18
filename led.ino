

void setup() {
 
 pinMode(8,INPUT);
 pinMode(13,OUTPUT);
 Serial.begin(9600);

}

void loop() {
if (digitalRead(8)==HIGH)
 {
  Serial.println(1);
  digitalWrite(13,HIGH);
 }
 else 
  {
    Serial.println(0);
    digitalWrite(13,LOW);
  }
}
