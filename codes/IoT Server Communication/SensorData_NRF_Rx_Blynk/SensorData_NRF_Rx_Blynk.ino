#define BLYNK_PRINT Serial

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

//#include <WiFi.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

char auth[] = "K01p0jyz_Im7ML6Xo3HKlcaTQmBt_ZzW";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "CyrilSpot"; //YourNetworkName
char pass[] = "iotealab"; //NetworkPassword

// Hardware Serial on Mega, Leonardo, Micro...
#define EspSerial Serial


// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

BlynkTimer timer;
 
RF24 radio(9,10); //Use Pin 9,10 for Arduino if you wish
const uint64_t address = 0xF0F0F0F0E1LL;
 
struct MyData 
{
  int counter;
  float temperature;
  float humidity;
  float raindrop;
  float moistamt;
};
MyData data;
 
//WiFiClient client;
 void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, millis() / 1000);
}
  void getTemp()
{
 

  Blynk.virtualWrite(V0, data.counter);
  Serial.println("Data Received:");
  Serial.print("Packet No. = ");
  Serial.println(data.counter);

  Blynk.virtualWrite(V1, data.temperature);
  Serial.print("Temperature = ");
  Serial.print(data.temperature);
  Serial.println("*C");

  Blynk.virtualWrite(V2, data.raindrop);
  Serial.print("RainDrop = ");
  Serial.print(data.raindrop);
  Serial.println("%");

  Blynk.virtualWrite(V3, data.moistamt);
  Serial.print("Approx. SoilMoisture = ");
  Serial.print(data.moistamt);
  Serial.println("amt");

  Blynk.virtualWrite(V4, data.humidity);
  Serial.print("Humidity = ");
  Serial.print(data.humidity);
  Serial.println("%");
 
}

void setup() 
{
  Serial.begin(115200);
  radio.begin();
  
  Serial.println("Receiver Started....");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.println();
  
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();              //This sets the module as receiver
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8442);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
  timer.setInterval(6000L, getTemp);
}

void loop()
{
  if ( radio.available() ) 
  {
    radio.read(&data, sizeof(MyData));
  
  Serial.println();
 
  }
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
