//Soil Moisture
  int moist_sensor = A0;
  int moist_output_value; 
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Reading from the moist sensor: ");
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  moist_output_value=analogRead(moist_sensor);
  moist_output_value = map(moist_output_value, 550, 0, 0, 100);
  Serial.print("Moisture");
  Serial.print(moist_output_value);
  Serial.println("%");
  delay(1000); 
}
