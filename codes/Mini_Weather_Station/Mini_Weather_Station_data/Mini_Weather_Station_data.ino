//Mini weather station: Integrating Rain drop/DHT22 sensors
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
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);



void setup() {
  // put your setup code here, to run once:
  //DHT22
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
  //Rain Sensor
  pinMode(2, INPUT);
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
    isRaining = !(digitalRead(rain_dig_pin));
    if (isRaining){
      IsRain = "YES";
    }
     else{
       IsRain = "NO";
    }

    //Debugging Output value via serial monitor
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  delay(500);
  //Rain Drop
    Serial.print("Raining ");
    Serial.print(IsRain);
    Serial.print(" Moisture level:");
    Serial.println(rainVal);
  delay(500);

}
