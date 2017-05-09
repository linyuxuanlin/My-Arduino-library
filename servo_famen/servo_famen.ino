#include <Servo.h>
Servo myservo; 
void setup() {
  pinMode(4,INPUT);
  myservo.attach(3);
  myservo.write(90);
  Serial.begin(9600);
}

void loop() {
 int a =digitalRead(4);
 if(a==1){
  myservo.write(0);
 }
 else{
  myservo.write(90);
  delay(2000);
 }
 delay(200);
 Serial.println(a);
 
}
