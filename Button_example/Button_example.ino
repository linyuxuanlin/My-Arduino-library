/*
name: Button example
Description: 按扭的例程
IDE version:  1.6
Author:  Lin <linyuxuanlin.github.io>
Date:    2016-10-3
note: 按下按钮，LED亮；松开，LED灭
*/

int Button = 2;
int LEDpin = 13;
 
void setup() {
  pinMode(Button, INPUT_PULLUP); //上拉使之默认接高电平,省去电阻
  pinMode(LEDpin, OUTPUT);  //设置13号IO口为输出状态
}
 
void loop() {
  int ButtonState = digitalRead(Button); //设置变量存储状态值
  if(ButtonState==0) 
  {
  digitalWrite(LEDpin,HIGH);        //如果读到的状态为0，说明按键已经按下，点亮LED
  }
  else
  {
  digitalWrite(LEDpin,LOW);      // 反之，熄灭LED
  }   
}
