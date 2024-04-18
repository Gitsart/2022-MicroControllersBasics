#include <SoftwareSerial.h>
int a;
SoftwareSerial SIM900A(2,3);

String rMessage = "";

void setup()
{ pinMode(11,OUTPUT);
digitalWrite(11,HIGH);
SIM900A.begin(9600); // GSM Module Baud rate – communication speed
Serial.begin(9600); // Baud rate of Serial Monitor in the IDE app
Serial.println ("Text Messege Module Ready & Verified");
delay(100);
Serial.println ("Type s to send message or r to receive message");
}

void loop()
{
if (Serial.available()>0)
switch(Serial.read())
{
case 's':
SendMessage();
break;
case 'r':
RecieveMessage();
break;
}

//if (SIM900A.available()>0)
//Serial.write(SIM900A.read());
}

void SendMessage()
{
Serial.println ("Sending Message please wait….");
SIM900A.println("AT+CMGF=1"); //Text Mode initialisation
delay(1000);
Serial.println ("Set SMS Number");
SIM900A.println("AT+CMGS=\"+919207937537\"\r"); // Receiver's Mobile Number
delay(1000);
Serial.println ("Set SMS Content");
SIM900A.println("Bhai kya haal hain? (Brother how are you?) this messege has been sent through Arduino Uno not a mobile phone wink wink ");// Messsage content
delay(100);
Serial.println ("Done");
SIM900A.println((char)26);// delay(1000);
Serial.println ("Message sent succesfully");
}

void RecieveMessage()
{
Serial.println ("Receiving Messeges");
delay (1000);
SIM900A.println("AT+CNMI=2,2,0,0,0"); // Eeceiving Mode Enabled
delay(1000);
Serial.write ("Messege Received Sucessfully");

rMessage = "";

int retry = 0;

int isMessage = 0;

while(1){
  String sBuff;
  Serial.print("S Buff");
  sBuff = SIM900A.readString();
  Serial.print(sBuff);
  retry++;

  if(sBuff.indexOf("+CMT") > 0){
    isMessage = 1;
    break; 
  } else if(retry >5){
    break;
  }
}
if(isMessage == 1){
  Serial.println("Message recieved");
  digitalWrite(11,LOW);
} else {
  Serial.println("Message not recieved");
  
}


//
//while(SIM900A.available()){
//  char cBuff = SIM900A.read();
//  rMessage += cBuff;
//}

//Serial.print("Message Stored in variable is");
//Serial.print(rMessage);

}
