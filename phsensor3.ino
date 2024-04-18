#include <OneWire.h>

#include <DallasTemperature.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial nodemcu(5,6);
#define ONE_WIRE_BUS 13

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);
float Celsius = 0;
float Fahrenheit = 0;
char dd=0;
#define SensorPin A1          // the pH meter Analog output is connected with the Arduino’s Analog
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
float voltage;
float ntu;
int buf[10],temp;
char *my_str[]={"used_to_drinking"} ;
void setup()
{ 
  
 Serial.begin(115200); 
  nodemcu.begin(115200);                                                                                                                                                                                                                                                                                                               
  pinMode(13,OUTPUT);  
  sensors.begin();  
  Serial.println("Ready");    //Test the serial monitor
}
void loop()
{ 
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();
  voltage=0;
  for(int i=0;i<800;i++)
  { 
    voltage += ((float)analogRead(A0)/ 1023.0)*5;
 }
 voltage=voltage/850;
 voltage=round_to_dp(voltage,2);
 if(voltage<2.5)
 {
  ntu=3000;
  }
  else
  {    ntu=-1220.4*sq(voltage)+5742.3*voltage-5353.8;
    }
 
  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
  avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=3.5*phValue+5; 
  //convert the millivolt into pH value
  Serial.println ();
  Serial.println("pH:");  
  Serial.println(phValue);
  sensors.requestTemperatures();

  Celsius = sensors.getTempCByIndex(0);
  Fahrenheit = sensors.toFahrenheit(Celsius);
  Serial.print(Celsius);
  Serial.print(" C  ");
  Serial.print(Fahrenheit);
  Serial.println(" F");
  Serial.println ("sensor output(v):");
  Serial.println (voltage);
  Serial.println ("NTU:");
  Serial.println(ntu);
  Serial.println ();
  if(phValue>=6&&phValue<=8)
  {
    if(voltage>2.5 )
    {
      for(int i=0;i<1;i++)
     Serial.println(my_str[i]);
    }
  }
  else
  dd="nowater";
    
   
  //str =String("ph: ")+String(phValue)+String("c: ")+String(Celsius)+String("ntu: ")+String(ntu);
  //serial.println(str);
  data["ph"] = phValue;
  data["ntu"] = ntu; 
  data["temp"]=Celsius; 
  data["status"]= my_str;

  //Send data to NodeMCU
  data.printTo(nodemcu);
  jsonBuffer.clear();
  delay(1000);
}
   float round_to_dp(float in_value,int decimal_place)
{
  float multiplier =powf(10.0f,decimal_place);
in_value=roundf(in_value* multiplier)/multiplier;
return in_value;
  } 
 
