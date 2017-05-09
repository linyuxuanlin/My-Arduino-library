//by Lin
#include <Servo.h>
Servo myservo; 
void setup() {
  myservo.attach(3);//舵机连接Arduino的D9
}

void loop() {
  myservo.write(90); //让舵机回到中位
  delay(500);
  myservo.write(180);
}
 
