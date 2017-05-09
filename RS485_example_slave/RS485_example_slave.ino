//作为从机:只负责输出数据
#include <SoftwareSerial.h>  //调用软串口
SoftwareSerial mySerial(10, 11);  //RO,DI的接线
void setup() {
  mySerial.begin (9600);  //设置RS485的波特率
  //Serial.begin(9600);  //设置串口的波特率
  pinMode(3, OUTPUT);  //DE,RE的接线
  digitalWrite(3, LOW);  //设置低电平以发送数据
}

void loop() {
  
  //Serial.println ("SENT");  //测试程序是否工作
  mySerial.println("hello world");  //输出数据
  delay(10);  //必须延时
}
