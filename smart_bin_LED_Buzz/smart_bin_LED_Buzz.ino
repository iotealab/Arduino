#include <Servo.h>
Servo servo;

// ---------------------------------------------------------------- //
// Arduino Ultrasoninc Sensor HC-SR04
// Re-writed by Cyril @ioTEA_lab
// Using Arduino IDE 1.8.7
// Using HC-SR04 Module
// Tested on 7 July, 2021
// ---------------------------------------------------------------- //

int redLED = 5;
int greenLED = 13;
int yellLED = 7;
int buzzPin = 8;
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(yellLED, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  servo.attach(4);
  digitalWrite(yellLED,HIGH);
  //delay(1000);
  digitalWrite(yellLED,LOW);
}
void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  if (distance<20)
  {
    digitalWrite(greenLED,HIGH);
    digitalWrite(redLED,LOW);
    tone(buzzPin,1500);
    servo.write(170);
    delay (2000);
  }
  else {
    digitalWrite(greenLED,LOW);
    digitalWrite(redLED,HIGH);
    noTone(buzzPin);
    servo.write(90);
    delay (1000);
  }
}
