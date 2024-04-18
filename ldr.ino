#define LED D0 
const int ldrPin = A0;

void setup() {

Serial.begin(9600);

pinMode(LED, OUTPUT);

pinMode(ldrPin, INPUT);

}

void loop() {

int ldrStatus = analogRead(ldrPin);

  if (ldrStatus <=35                                                                                                                ) {
  Serial.print(ldrStatus);
  digitalWrite(LED, HIGH);
  Serial.println("LDR is DARK, LED is ON");
  
  }
  else {
digitalWrite(LED, LOW);
  Serial.println("LED is OFF");
  }
delay(1000);
}
