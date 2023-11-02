#include <AltSoftSerial.h>
#include <TinyGPS.h>

TinyGPS gps;  //Creates a new instance of the TinyGPS object
AltSoftSerial altSerial;

void setup()
{
  Serial.begin(9600);  
  altSerial.begin(9600);
  Serial.println();
}

void loop()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 500;)
  {
    while (altSerial.available())
    {
      char c = altSerial.read();
      //Serial.print(c);
      if (gps.encode(c)) 
        newData = true;  
    }
  }

  if (newData)      //If newData is true
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);  
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" ");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
  }
 
  Serial.println(failed);
 // if (chars == 0)
   // Serial.println("** No characters received from GPS: check wiring **");
}