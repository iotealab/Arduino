//RF Library
#include <SPI.h>
#include "RF24.h"
#include "Wire.h"
//#include <nRF24L01.h>

//Struct data:
struct Data_Package {
  byte data1;
  byte data2;
  byte data3;
};  
  Data_Package data;

RF24 radio(9,10); //CE, CSN //4,5 for esp32
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();

}

void loop() {
  // put your main code here, to run repeatedly:
    if (radio.available()){
        while (radio.available()) { 
          // While there is data ready
        radio.read(&data, sizeof(Data_Package));

        //Debugging values via serial monitor
        Serial.print("rainVal data1: ");
        //data.data1 = data.data1*4;
        //data.data1 = map(data.data1,0,255,0,1023);
        Serial.println(data.data1);
        Serial.print("humid. data2: ");
        Serial.println(data.data2);
        Serial.print("temp. data3: ");
        Serial.println(data.data3);
        }
    }
}
