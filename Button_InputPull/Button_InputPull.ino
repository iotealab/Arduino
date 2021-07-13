int inputPin = 7;
#define pinLed 13
int sensorState = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Initialize Serial Monitor
 
  pinMode(inputPin,INPUT_PULLUP);
  pinMode(pinLed,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorState = digitalRead(inputPin);
   
  //Serial.print("Sensor or Input val: ");  
  Serial.println(sensorState);
   
  //Verifying the state using if conditional statement
  if (sensorState == 1) {
    digitalWrite(pinLed, HIGH);
    delay(1000);
  } else {
    //muteAlarm();
    digitalWrite(pinLed,LOW );
  }    
}
