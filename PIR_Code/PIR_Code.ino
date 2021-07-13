int PIR = 7;
void setup() {
  // put your setup code here, to run once:
  pinMode(PIR,INPUT);
  pinMode(13,OUTPUT);
  pinMode(9,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = digitalRead(PIR);
  if (val == HIGH){
    digitalWrite(13,HIGH);
    tone (9,500);
  }
  else{
    digitalWrite(13,LOW);
    noTone(9);
  }

}
