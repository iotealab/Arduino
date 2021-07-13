#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


char auth[] = "smnG1qugEOHAgXH_n04MwBvS3ZmWY9Bq"; 

char ssid[] = "CyrilSpot";
char pass[] = "iotealab";

int LED = 2;


void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);
    pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
}
