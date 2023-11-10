#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <TinyGPS.h>
TinyGPS gps;

RF24 radio(7, 8); // CE, CSN
const byte diachi[6] = "12345"; //Mảng kí tự dạng chuỗi có 6 kí tự

void setup()
{
  Serial.begin(9600);
  if (!radio.begin()) 
  {
    Serial.println("Module không khởi động được...!!");
    while (1) {}
  } 
  
  radio.openWritingPipe(diachi);
  radio.setPALevel(RF24_PA_MIN); 
  radio.setChannel(80); 
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening(); //Cài đặt module là TX
  
  if (!radio.available())
  {
    Serial.println("Chưa kết nối được với RX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  }  
}

void loop()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    radio.write(&flat, sizeof(flat));
    radio.write(&flon, sizeof(flon));
  }
  else
  {
    const char* message = "No GPS";
    radio.write(message, strlen(message));
    Serial.println("No GPS");
  }
}