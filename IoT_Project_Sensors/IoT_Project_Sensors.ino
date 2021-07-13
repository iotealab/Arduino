//Declaration of all sensors
//Soil Moisture
  int moist_sensor = A0;
  int moist_output_value;

  //Rain Drop Sensor
  int rain_sensor = A1;
  int rain_dig_pin = 2;
  int rainVal;
  boolean isRaining = false;
  String IsRain;

  //Dallas Temperature sensor
  // Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 4 on the Arduino
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

//DHT22
#include "DHT.h"
#define DHTPIN 5     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Reading from the moist sensor: ");
  delay(2000);
  //Serial.begin(9600);
  pinMode(2, INPUT);

  // start serial port
  //Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();

  //Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
  }

void loop() {
  // put your main code here, to run repeatedly:
  moist_output_value=analogRead(moist_sensor);
  moist_output_value = map(moist_output_value, 550, 0, 0, 100);
  Serial.print("Moisture");
  Serial.print(moist_output_value);
  Serial.print("%");
  //delay(1000); 

  rainVal = analogRead(rain_sensor);
    isRaining = !(digitalRead(rain_dig_pin));
    if (isRaining){
      IsRain = "YES";
    }
     else{
       IsRain = "NO";
    }
    Serial.print("Raining ");
    Serial.print(IsRain);
    Serial.print("Moisture level:");
    Serial.println(rainVal);
    delay(200);

   // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  float tempC = sensors.getTempCByIndex(0);
  // Check if reading was successful
  if(tempC != DEVICE_DISCONNECTED_C) 
  {
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
  } 
  else
  {
    Serial.println("Error: Could not read temperature data");
  }

  // Wait a few seconds between measurements.
  //delay(2000); //Tentavive timing though
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  
}
