int VibPin = 4;
void setup() {
  // put your setup code here, to run once:
pinMode(VibPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

      digitalWrite(VibPin,HIGH);
      delay(500);
      
      digitalWrite(VibPin,LOW);
      delay(50);
     
}
