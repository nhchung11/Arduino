#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte diachi[6] = "12345";

void setup() 
{
  Serial.begin(9600);
  
  if (!radio.begin()) 
  {
    Serial.println("Module không khởi động được...!!");
    while (1) {}
  } 
  
  radio.openReadingPipe(1, diachi);
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(80);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
  
  if (!radio.available())
  {
    Serial.println("Chưa kết nối được với TX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  } 
}

void loop() 
{
  if (radio.available()) 
  {
    char nhan[30] = ""; //30 là số kí tự trong mảng
    radio.read(&nhan, sizeof(nhan));
    Serial.println(nhan);
  }
}
