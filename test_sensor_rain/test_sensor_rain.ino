//Rain Drop Sensor
  int rain_sensor = A1;
  int rain_dig_pin = 2;
  int rainVal;
  boolean isRaining = false;
  String IsRain;
 
  void setup(){
  Serial.begin(9600);
  pinMode(2, INPUT);
  }
  void loop(){
    rainVal = analogRead(rain_sensor);
    isRaining = !(digitalRead(rain_dig_pin));
    if (isRaining){
      IsRain = "YES";
    }
     else{
       IsRain = "NO";
    }
    Serial.print("Raining ");
    Serial.print(IsRain);
    Serial.print(" Moisture level:");
    Serial.println(rainVal);
    delay(200);
  }
