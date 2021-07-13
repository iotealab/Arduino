
int pinBuzzer = 6;
#define pinLed 13

void setup() {
  // put your setup code here, to run once:
 pinMode(pinBuzzer,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  buzzAlarm();
  delay(500);
  muteAlarm();
  delay(500);
}

void buzzAlarm() {
  //LED ON
  digitalWrite(pinLed, HIGH);
   
  //Using frequency of 1500 hz.
  tone(pinBuzzer,1500);
  delay(1000); //One second
   
  muteAlarm();
}
 
void muteAlarm() {
  //LED OFF
  digitalWrite(pinLed,LOW );
  
  //Buzzer OFF
  noTone(pinBuzzer);
}
