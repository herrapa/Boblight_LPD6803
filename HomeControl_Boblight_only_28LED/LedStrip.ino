
#include <FastSPI_LED.h>

#define NUM_LEDS 28

//data: pin 11
//Clock: pin 13
// Sometimes chipsets wire in a backwards sort of way
struct CRGB { unsigned char b; unsigned char r; unsigned char g; };

struct CRGB *leds;

#define PIN 4

//file for LED functions

void ledSetup()
{
  FastSPI_LED.setLeds(NUM_LEDS);
  FastSPI_LED.setChipset(CFastSPI_LED::SPI_LPD6803);

  //FastSPI_LED.setPin(PIN);
  
  FastSPI_LED.init();
  FastSPI_LED.start();

  leds = (struct CRGB*)FastSPI_LED.getRGBData(); 
  delay(500);
  for (int i=0; i < NUM_LEDS; i++)
     {
       leds[i].r = 0;
       leds[i].g = 0;
       leds[i].b = 0;      
    }
  FastSPI_LED.show();
  delay(50);
  
}

void parseRGBSerialPacket()
{
  for (int i = 0; i < 28; i++)
  {
    byte r = arr[i * 3];
    byte g = arr[i * 3 + 1];
    byte b = arr[i * 3 + 2];
    leds[i].r = r;
    leds[i].g = g;
    leds[i].b = b; 
  }
  
  FastSPI_LED.show();
    //delay(5);
}

void parseRGBSWSPacket()
{
  byte rgb[3];
      for (int i = 0; i < 3; i++)
      {
        rgb[i] =  mySerial.read();
      }
      for (int i=0; i < NUM_LEDS; i++)
     {
       leds[i].r = rgb[0];
       leds[i].g = rgb[1];
       leds[i].b = rgb[2];      
    }
  FastSPI_LED.show();
}
