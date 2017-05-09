/*
name: RotaryEncoder example
version:  1.0
Author:  Lin <linyuxuanlin.github.io>
Date:    2016-10-2
Description:  旋转编码器例程
note: CLK(A) - D2
      DT (B) - D3
      SW     - D5
*/
 
#define ENCODER_A_PIN 2
#define ENCODER_B_PIN 3
#define SWITCH_PIN    4
long position;
 
void setup(){
  //初始化
  pinMode(ENCODER_A_PIN, INPUT);
  pinMode(ENCODER_B_PIN, INPUT);
  pinMode(SWITCH_PIN, INPUT);
  //硬件中断
  attachInterrupt(0, read_quadrature, CHANGE);
 
  //初始化串口
  Serial.begin(9600);
}
 
void loop(){
   if (digitalRead(SWITCH_PIN) == LOW){
     delay(10);
     if (digitalRead(SWITCH_PIN) == LOW){
       Serial.println("Switch Pressed");
     }
   }
   Serial.print("Position: ");
   Serial.println(position, DEC);
   delay(500);
}
 
void read_quadrature(){  
  // ENA脚下降沿中断触发
  if (digitalRead(ENCODER_A_PIN) == LOW){   
    //查询ENB的电平以确认是顺时针还是逆时针旋转
    if (digitalRead(ENCODER_B_PIN) == LOW)
      position++;
  }
  // ENA脚上升沿中断触发
  else{
    //查询ENB的电平以确认是顺时针还是逆时针旋转
    if (digitalRead(ENCODER_B_PIN) == LOW)
      position--;
  }
}
