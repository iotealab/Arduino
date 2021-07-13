//Receiver Code: 
#include <SPI.h>
#include "RF24.h"
//Servo Servo_motor_x,Servo_motor_y,Servo_motor_z;
//LCD

RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
//Struct data to be received
struct Data_Package {
  byte data0;
  byte data1;
  byte data2;
  byte data3;
};  

Data_Package data;
//LCD Initialization
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); //20,4
//Since I am using I2C A4, A5 are SDA and SCL
//Remember to read your I2C address for your LCD :"0x27"


void setup()
{
Serial.begin(9600);

radio.begin();
radio.openReadingPipe(1,pipe);
radio.startListening();
//LCD
  //LCD
  lcd.init();// initialize the lcd 
  lcd.backlight();
  lcd.print("Mini Weather Station");
}

void loop()
{
if (radio.available()){
        while (radio.available()) { 
          // While there is data ready
        radio.read(&data, sizeof(Data_Package));
        
        Serial.print("data0: ");
        Serial.println(data.data0);
        Serial.print("data1: ");
        Serial.println(data.data1);
        Serial.print("data2: ");
        Serial.println(data.data2);
        Serial.print("data3: ");
        Serial.println(data.data3);

        //LCD

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Rain:");
  lcd.print(data.data0);
  lcd.setCursor(8,0);
  lcd.print("Moist:");
  lcd.print(data.data3);

  lcd.setCursor(0,1);
  lcd.print("Temp:");
  lcd.print(data.data2);
  lcd.setCursor(8,1);
  lcd.print("Humid:");
  lcd.print(data.data1);

    }
  }
}
