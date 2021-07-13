//Declaration of pin
  #define DHTPIN 5
//Rain Drop Sensor
  int rain_sensor = A1;
  int rain_dig_pin = 2;
//initializing variables
  int rainVal;
  boolean isRaining = false;
  String IsRain;

//Importation of libraries
#include "DHT.h"
//DHT Object initialization
#define DHTTYPE DHT22 //DHT22
DHT dht(DHTPIN, DHTTYPE);

//Source Code/Program for Sensor Node
#include <SPI.h>
#include <Wire.h>

#include <nRF24L01.h>
#include <RF24.h>
 
RF24 radio(9,10); // CE, CSN on Blue Pill PB0, PA4
const uint64_t address = 0xF0F0F0F0E1LL;
int counter = 0;

struct MyData 
{
  int counter;
  float temperature;
  float humidity;
  float raindrop;
  float moistamt;
};
MyData data;
 
void setup() 
{
Serial.begin(115200);
radio.begin();                  //Starting the Wireless communication
radio.openWritingPipe(address); //Setting the address where we will send the data
radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
radio.stopListening();          //This sets the module as transmitter
 Serial.println(F("DHTxx test!"));
 dht.begin();
  //Rain Sensor
  pinMode(2, INPUT);
 
}
 
void loop()
{
  //DHT22
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  //Rain Drop
    rainVal = analogRead(rain_sensor);
    rainVal = map(rainVal,0,1023,100,0);
    isRaining = !(digitalRead(rain_dig_pin));
    if (isRaining){
      IsRain = "YES";
    }
     else{
       IsRain = "NO";
    }

  data.counter = counter;
  data.temperature = t; 
  data.raindrop = rainVal;  
  data.moistamt = 0; //No sensor connected here 
  data.humidity = h;
  
  Serial.print("Packet No. = ");
  Serial.println(data.counter);
  
  Serial.print("Temperature = ");
  Serial.print(data.temperature);
  Serial.println("*C");
 
  Serial.print("RainDrop = ");
  Serial.print(data.raindrop);
  Serial.println("%");
 
  Serial.print("Approx. SoilMoisture = ");
  Serial.print(data.moistamt);
  Serial.println("amt");
 
  Serial.print("Humidity = "); //
  Serial.print(data.humidity);
  Serial.println("%");
 
  Serial.println();
  
  radio.write(&data, sizeof(MyData));
  
  Serial.println("Data Packet Sent");
  Serial.println("");
  
  counter++;
  delay(5000);
}
