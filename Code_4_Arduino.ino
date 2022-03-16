#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(12,11); //Rx, Tx

#define echoPin 10
#define trigPin 9
#define buzz 8
const int max_dist=30;
long duration; 
int distance; 

void setup() {
  pinMode(buzz, OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600); //baudrate speed
  mySerial.begin(9600); //NodeMCU serial
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print(distance);
  Serial.print(" ");
  if(distance<max_dist){
    digitalWrite(buzz, HIGH);
    tone(buzz, 1000);

// trigger sensor --> sending data to esp8266 NodeMCU
    Serial.println("Arduino UNO: I sensed something!");
    
    mySerial.write(115); //code: sendSms
    delay(1000);
    
  } else {
    noTone(buzz);
    
  }
  
  delay(100);
}
