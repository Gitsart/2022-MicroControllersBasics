#include <dht.h>
#define SensorPin A0 // Defines pin number to which the soil moisture sensor is connected
#define dataPin D8 // Defines pin number to which the temperature sensor is connected
dht DHT; // Creats a DHT object

void setup() 
{
  pinMode(D1,OUTPUT); //Fan
  pinMode(D2,OUTPUT); // Ultrasound emitter
  pinMode(D4,OUTPUT); // Pump
  Serial.begin(9600);
}
void loop() 
{
  digitalWrite (D2,HIGH); // The ultrasonic bug reppellent is High.
  digitalWrite (D1,LOW);
  digitalWrite (D4,LOW);
  float sensorValue = analogRead(SensorPin);
  Serial.print("Soil Moisture=");
 Serial.print(sensorValue);
  if (sensorValue>700)
  { 
    digitalWrite(D4,HIGH);
    Serial.println("Pumping Water");
    delay(3000);
    Serial.println("Pumping Stopped");
  } 
  int readData = DHT.read11(dataPin); // DHT11

  float t = DHT.temperature; // Gets the values of the temperature
  float h = DHT.humidity; // Gets the values of the humidity

  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.print(" ");
  Serial.print("C | ");
  Serial.print("Humidity = ");
  Serial.print(h);
  Serial.println(" % ");
  Serial.println("");
  if(t>33)
  {
    digitalWrite(D1,HIGH);
    delay(3000);
  }

  delay (2000);
}
