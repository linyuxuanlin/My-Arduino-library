/*
  name:mearm
  version:  3.0
  Author:  Lin <824676271@qq.com>
  Date:    2016-10-2
  Description:  MeArm机械臂
  note: ps2控制,未完成
*/
#include <Servo.h>
#include <PS2X_lib.h>
Servo servo1, servo2, servo3, servo4 ;
#define PS2_DAT        5
#define PS2_CMD        4
#define PS2_SEL        3
#define PS2_CLK        2
#define pressures   false  //按压力度,改 false 取消
#define rumble      false  //手柄震动,改 false 取消
int leftx = 90;
int lefty = 90;
int rightx = 90;
int righty = 90;
PS2X ps2x;  //创建类
int error = 0;
byte type = 0;
byte vibrate = 0;
void (* resetFunc) (void) = 0; //重启的函数

void setup() {
  servo1.attach(9, 555, 2390);
  servo2.attach(10, 555, 1460);
  servo3.attach(11, 1370, 2300);
  servo4.attach(12, 544, 2400);
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  Serial.begin(115200);
  delay(500);  //必须先延时让接收器期待
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  if (error == 0) {
    Serial.print("发现手柄,配置成功");

  }
  else if (error == 1)
    Serial.println("未发现手柄,检查接线");

  else if (error == 2)
    Serial.println("发现手柄但是没有连接权限");

  else if (error == 3)
    Serial.println("手柄拒绝打开压力传感器");
}

void lx() {
  if ( ps2x.Analog(PSS_LX) >= 190)  {
    leftx--;
    delay(8);
  }
  if ( ps2x.Analog(PSS_LX) <= 65 ){
    leftx++;
    delay(8);
  }
  else{leftx=leftx;}
  servo2.write(leftx);
}

void ly() {
  if ( ps2x.Analog(PSS_LY) >= 190 ) {
    lefty++;
    delay(8);
  }
  if ( ps2x.Analog(PSS_LY) <= 65 ) {
    lefty--;
    delay(8);
  }
else{lefty=lefty;}
  servo1.write(lefty);
}

void rx() {
  if ( ps2x.Analog(PSS_RX) >= 190 ) {
    rightx++;
    delay(8);
  }
  if ( ps2x.Analog(PSS_RX) <= 65) {
    rightx--;
    delay(8);
  }
  else{rightx=rightx;}
  servo3.write(rightx);
}

void ry() {
  if ( ps2x.Analog(PSS_RY) >= 190 ) {
    righty++;
    delay(8);
  }
  if ( ps2x.Analog(PSS_RY) <= 65 ) {
    righty--;
    delay(8);
  }
  else{righty=righty;}
  servo4.write(righty);
}

void loop() {
  if (error == 1) { //如果没有发现手柄,就重启接收器
    resetFunc();
  }
  
    if (error == 0) {
  
    lx();
    ly();
    rx();
    ry();
    }

  delay(100);
}
