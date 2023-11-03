#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
// Max size of this struct is 32 bytes - NRF24L01 buffer limit
struct Data_Package {
  int count = 0;
};

Data_Package data; // Create a variable with the above structure

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.begin(9600);
  // ss.begin(GPSBaud);
}   

void loop() {
  data.count += 1;
  radio.write(&data, sizeof(Data_Package));
  delay(1000);
}