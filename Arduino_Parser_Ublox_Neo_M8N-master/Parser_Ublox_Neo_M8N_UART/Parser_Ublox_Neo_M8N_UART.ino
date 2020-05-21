/* Andrea Toscano
Universita' degli Studi di Milano

Sample script - Reading some info from U-Blox Neo M8N GPS/GLONASS
*/
#include <SoftwareSerial.h>
#include "Ublox.h"
#define SERIAL_BAUD 115200
#define GPS_BAUD 9600
#define N_FLOATS 4
SoftwareSerial ss(4, 3);
Ublox M8_Gps;
// Altitude - Latitude - Longitude - N Satellites
float gpsArray[N_FLOATS] = {0, 0, 0, 0};

void setup() {
   Serial.begin(SERIAL_BAUD);
   ss.begin(GPS_BAUD);
   pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
   if(!ss.available())
		return;

  while(ss.available()){
        char c = ss.read();
         if (M8_Gps.encode(c)) {
          gpsArray[0] = M8_Gps.altitude;
          gpsArray[1] = M8_Gps.latitude;
          gpsArray[2] = M8_Gps.longitude; 
          gpsArray[3] = M8_Gps.sats_in_use;
        }
  }
  for(byte i = 0; i < N_FLOATS; i++) {
    Serial.print(gpsArray[i], 6);Serial.print(" ");
  }
  Serial.println("");
}

