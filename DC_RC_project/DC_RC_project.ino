Transmitter Code
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
#include<SPI.h>
#include<RF24.h>
#include<nRF24L01.h>
RF24 radio(7,8); // CE, CSN
const byte address[6] = "00001";
#define outputA 6
#define outputB 4
int counter = 0;
int aState;
int aLastState;
 
void setup() {
pinMode (outputA,INPUT);
pinMode (outputB,INPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();//pinMode (en, OUTPUT);
Serial.begin (9600);
//lcd.begin(16,2);
// Reads the initial state of the outputA
aLastState = digitalRead(outputA);
//Serial.begin(9600);
}
 
void loop() {
aState = digitalRead(outputA); // Reads the "current" state of the outputA
// If the previous and the current state of the outputA are different, that means a Pulse has occured
if (aState != aLastState){
// If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
if (digitalRead(outputB) != aState) {
counter ++;
 
} else {
counter --;
//analogWrite(en, 255);
 
}
Serial.print("Position: ");
Serial.println(counter);
radio.write(&counter, sizeof(counter));
//Serial.println("datasent");
 
}
aLastState = aState; // Updates the previous state of the outputA with the current state
 
}
Receiver Code
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
81
82
83
84
85
86
87
88
89
90
91
92
93
#include<LiquidCrystal.h>
LiquidCrystal lcd(14,15,16,17,18,19);
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
 
#define M1 5
#define M2 9
RF24 radio(7,8); // CE, CSN
const byte address[6] = "00001";
 
void setup() {
 
pinMode (M1, OUTPUT);
pinMode (M2, OUTPUT);
//pinMode (en, OUTPUT);
Serial.begin (9600);
radio.begin();
radio.openReadingPipe(0, address);
radio.setPALevel(RF24_PA_MIN);
radio.startListening();
lcd.begin(16,2);
lcd.print("Project-Maanasa");
//lcd.clear();
}
 
void loop() {
  if (radio.available())
  { lcd.clear();
    int r;
    radio.read(&r, sizeof(r));
   // Serial.println(r);
    lcd.setCursor(0,0);
    lcd.print("Position:");
    lcd.setCursor(10,0);
    lcd.print(r);
   if(r<=50)
{ //Serial.println("r>0");
    int mapva= map(r,0,50,0,255);
      analogWrite(M1,mapva);
      analogWrite(M2,0);
  float s=((float)mapva/(float)255)*100;
 Serial.print("speed percentage: ");
 Serial.println(s);
 lcd.setCursor(0,1);
 lcd.print("Speed:");
 lcd.setCursor(8,1);
 lcd.print(s);
 lcd.setCursor(13,1);
 lcd.print("%");
      if(r>50)
  {
    analogWrite(M1,255);
    analogWrite(M2,0);
    Serial.println("speed percentage:100");
     lcd.setCursor(0,1);
    lcd.print("Speed: 100.00%");
  }
 
}
 else if((r>-51)&&(r<0))
 { 
  int mapval=map(r,-50,-1,0,255);
    analogWrite(M2,mapval);
    analogWrite(M1,0);
  float s=((-1)*(float)mapval/(float)255)*100;
 Serial.print("speed percentage: ");
 Serial.println(s);
  lcd.print("Speed:");
 lcd.setCursor(8,1);
 lcd.print(s);
  lcd.setCursor(13,1);
 lcd.print("%");
 
   if(r<=-51)
   {
    analogWrite(M1,0);
    analogWrite(M2,0);
    Serial.println("speed percentage:0");
    lcd.setCursor(0,1);
    lcd.print("Speed:0.00%");
   }
 }
 else 
 {
  digitalWrite(M1, LOW);
digitalWrite(M2, LOW);
 }
//analogWrite(en, 255);
delay(100);
 
  }
  }
