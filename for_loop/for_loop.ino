void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i<=10; i++){ //Using '<=' makes it count till 10 
    Serial.print(i);
    Serial.println("Hello World");
    delay(1000);
  }
}
