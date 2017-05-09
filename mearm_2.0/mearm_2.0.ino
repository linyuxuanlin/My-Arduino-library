/*
  name:mearm
  version:  2.0
  Author:  Lin <824676271@qq.com>
  Date:    2016-10-2
  Description:  MeArm机械臂
  note: 改进控制
*/
#include <Servo.h>
Servo servo1, servo2, servo3, servo4 ;

int up = 2;
int down = 3;
int grab = 4;
int x = 0;
int y = 1;
int valx;
int valy;
int i;
boolean grabstate = 0  ;

void setup() {
  servo1.attach(9, 555, 2390);
  servo2.attach(10,555,1460);
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
  valy = 90;
}
void spinx() {
  
  if ( analogRead(x) >= 640 && analogRead(x) <= 896) {
    valx--;
    delay(8);
  }
  if ( analogRead(x) <= 384 && analogRead(x) >= 128) {
    valx++;
    delay(8);
  }
  if ( analogRead(x) >= 896) {
    valx--;
    delay(5);
  }
  if ( analogRead(x) <= 128 ) {
    valx++;
    delay(5);
  }
  servo2.write(valx);
}
void spiny() {
  if ( analogRead(y) >= 640 && analogRead(x) <= 896) {
    valy++;
    delay(8);
  }
  if ( analogRead(y) <= 384 && analogRead(y) >= 128) {
    valy--;
    delay(8);
  }
    if ( analogRead(x) >= 896) {
    valx++;
    delay(5);
  }
  if ( analogRead(x) <= 128 ) {
    valx--;
    delay(5);
  }
  servo1.write(valy);
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

  spinx();
  spiny();
  

}

void state() {
  Serial.print(valx);
  Serial.print(",");
  Serial.println(valy);
  delay(200);
}

