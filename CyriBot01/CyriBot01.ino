/*
CodeArm STEM Robotics Kit
Project Name : ShoulderTest
Developed by : Liensy Robotics
Last Update : 20/11/2020
*/
 
#include <Servo.h>
 
//shield connections
int servoPin2 = 4; //shoulder pin
 
Servo servo2;  //Shoulder control
 
int servoAngle2 = 0;   // servo position in degrees
 
void setup()
{
  Serial.begin(9600);  
  servo2.attach(servoPin2);
}
 
void loop()

{
 servo2.write(90);          
 delay(1000); 
 servo2.write(180);
 delay(1000);
}
