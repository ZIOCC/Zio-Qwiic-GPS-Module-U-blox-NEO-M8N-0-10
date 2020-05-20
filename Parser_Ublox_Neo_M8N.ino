/* Andrea Toscano
Universita' degli Studi di Milano

Sample script - Reading some info from U-Blox Neo M8N GPS/GLONASS
*/
#include <Wire.h>
#include "Ublox.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SC16IS752.h"
#define SERIAL_BAUD 9600
#define GPS_BAUD 9600
#define N_FLOATS 4
#define Address 0x4D

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

Ublox M8_Gps;
SC16IS752 SC16IS752;
// Altitude - Latitude - Longitude - N Satellites
float gpsArray[N_FLOATS] = {0, 0, 0, 0};
char Buffer[100];
uint8_t i=0,num=0;
void setup() {
    SC16IS752.begin(Address,true);
    SC16IS752.setup(CHANA,BAUD_9600,UART_8N1);
    
    SC16IS752.setGPIODir(0xFF);
   Serial.begin(SERIAL_BAUD);
   pinMode(13, OUTPUT);
//   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
//   display.clearDisplay();
 
}

void loop() {
 if(SC16IS752.checkRxLevel(CHANA)>0)
 {
 num=SC16IS752.readUART_Array(CHANA,Buffer);
    for(i=0;i<num;i++)
    {
      char c=Buffer[i];
     if (M8_Gps.encode(c)) {
            gpsArray[0] = M8_Gps.altitude;
            gpsArray[1] = M8_Gps.latitude;
            gpsArray[2] = M8_Gps.longitude; 
            gpsArray[3] = M8_Gps.sats_in_use;
       }
      }
      for(i=0;i<num;i++)
      {
        Buffer[i]=0;
      }
  }
if(gpsArray[3]>0)
{
  for(byte i = 0; i < N_FLOATS; i++) {
    Serial.print(gpsArray[i], 6);Serial.print(" ");
  }
//  display.setTextSize(2);
//  display.setTextColor(WHITE);
//  display.setCursor(0,0);
//  display.clearDisplay();
//  display.print("Star:");
//  display.print(gpsArray[3]);
//  display.display();
  for(byte i = 0; i < N_FLOATS; i++)
  {
    gpsArray[i]=0;
    }
  digitalWrite(13,HIGH);
  Serial.println("");
}

}

