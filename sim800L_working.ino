#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(D7, D8); //SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
  
  Serial.println("Sending SMS...");   

  mySerial.print("AT+CMGF=1\r");    
  updateSerial();
  mySerial.print("AT+CMGS=\"+917306033200\"\r");  //Your phone number don't forget to include your country code, example +212123456789"
  updateSerial();
  mySerial.print("CHILD MONITORING SYSTEM : Child not in range");       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  updateSerial();
  mySerial.print((char)26);// (required according to the datasheet)
  updateSerial();
  Serial.println();
  Serial.println("Text Sent.");
  delay(500);
}

void loop()
{
  updateSerial();
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
