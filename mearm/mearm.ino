/*
  name:mearm
  version:  1.0
  Author:  Lin <824676271@qq.com>
  Date:    2016-10-1
  Description:  MeArm机械臂
  note: basic
*/
#include <Servo.h>
Servo servo1, servo2, servo3, servo4 ;

int up = 2;
int down = 3;
int grab = 4;
int x = 0;
int y = 1;

int val0;
int val1;
int i;
boolean grabstate = 0  ;

void setup() {
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);
  servo4.attach(12);
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(grab, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(up) == 0) {
    servo3.write(80);
    delay(5);
  }
  if (digitalRead(down) == 0) {
    servo3.write(180);
    delay(5);
  }
  if (digitalRead(grab) == 0) {
    servo4.write(180);
    delay(5);
  }
  if (digitalRead(grab) == 1) {
    servo4.write(0);
  }
  val1 = analogRead(x);
  val1 = map(val1, 0, 1023, 90, 0);
  val0 = analogRead(y);
  val0 = map(val0, 0, 1023, 0, 179);
  servo1.write(val0);
  servo2.write(val1);
  state();
}

void state(){
  Serial.print(val0);
   Serial.print(",");
   Serial.println(val1);
   delay(200);
}

