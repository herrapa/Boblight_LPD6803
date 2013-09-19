//To use with Boblight plugin to XBMC
//RGB strip: LPD6803
//data: pin 11
//Clock: pin 13

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

#define numChannels 84

byte enableBoblight = 1;

byte enableRead = 0;
byte bytesRead = 0;
byte isDone = 0;
//byte numChannels = 84;
byte arr[numChannels]; //RGB array

void setup()
{
  Serial.begin(115200);
  
  mySerial.begin(9600);
  //mySerial.println("Hello, world?");
  
  ledSetup();
}

void loop() 
{
  if (enableBoblight)
  {
    while (Serial.available() > 0)
    {
      byte inByte = Serial.read();
      
      if (isDone)
      {
        if (inByte == 0x6A)
          {
            //Serial.println("= 6A");
            parseRGBSerialPacket();
            enableRead = 0;
            bytesRead = 0;
            isDone = 0;
          }
        else
          {
            //bad data
            //Serial.println("Bad data");
            enableRead = 0;
            bytesRead = 0;
            isDone = 0;
          }
      }
      if (enableRead)
      {
        //Serial.println("enableRead");
        arr[bytesRead] = inByte;
        
        if (bytesRead == (numChannels - 1))
        {
          isDone = 1;
        }
        
        bytesRead++;
      }
      
      if (inByte == 0x5A)
      {
        //Serial.println("inbyte = 0x5A");
        enableRead = 1;
      }
    }
  }
  
  if (mySerial.available())
  {
    byte r = mySerial.read();
    //Serial.println(r);
    switch (r)
    {
      case 'l': 
      enableBoblight = 0;
      parseRGBSWSPacket();
      break;
      case 's':
      enableBoblight = mySerial.read();
      break;
    }
  }
}
