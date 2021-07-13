#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9,10); 
const uint64_t address = 0xE8E8F0F0E1LL; //0xF0F0F0F0E1LL;

//Struct data:
struct Data_Package {
  byte data1;
  byte data2;
  byte data3;
};  
  Data_Package data;

  void setup() 
{
  Serial.begin(115200);
  radio.begin();
  
 
  Serial.println("Receiver Started....");
  Serial.print("Connecting to ");
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();              //This sets the module as receiver
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

/*
  int recvData()
{
  if ( radio.available() ) 
  {
    radio.read(&data, sizeof(Data_Package));
    return 1;
    }
    return 0;
}

  void loop()
{
  if(recvData())
  {
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
}*/
