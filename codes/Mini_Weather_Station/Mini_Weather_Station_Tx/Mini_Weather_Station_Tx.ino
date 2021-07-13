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

//RF Library
#include <SPI.h>
#include "RF24.h"
#include "Wire.h"

//Struct data:
struct Data_Package {
  byte data1;
  byte data2;
  byte data3;
};  
  Data_Package data;

RF24 radio(9,10); //CE, CSN
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup() {
  // put your setup code here, to run once:
  //DHT22 Sensor
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
  //Rain Sensor
  pinMode(2, INPUT);
  //Begin NRF module
  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop() {
  // put your main code here, to run repeatedly:
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
    rainVal = map(rainVal,0,1023,0,255);
    isRaining = !(digitalRead(rain_dig_pin));
    if (isRaining){
      IsRain = "YES";
    }
     else{
       IsRain = "NO";
    }

    //Debugging Output value via serial monitor
 /*
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  //Rain Drop
    Serial.print("Raining ");
    Serial.print(IsRain);
    Serial.print("Moisture level:");
    Serial.println(rainVal);
  delay(500);
*/
  data.data1 = rainVal;
  data.data2 = h;
  data.data3 = t;
  
  radio.write(&data, sizeof(Data_Package));

  //Debugging NRF module values
    Serial.println(data.data1);
    Serial.println(data.data2);
    Serial.println(data.data3);
    delay(500);

}
