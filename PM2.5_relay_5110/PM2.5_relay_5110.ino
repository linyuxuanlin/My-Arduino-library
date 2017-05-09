/*
name: PM 2.5 + relay control + 5110 LCD
version:  1.0
Author:  Lin <824676271@qq.com>
Date:    2016-08-19
Description:  智能插座初代
note: 必须用1.6.5才能编译通过
      闸值为 x = 150
*/

/*
接线：
LCD5110：
clk  = D7     //clock
din  = D6,   // data-in
dc    = D5,   // data select
reset = D2,   //reset
sce   = D3;  // enable
继电器：
Din = D8
Sharp灰尘传感器：
1 (V-LED) = 150欧电阻接5V，220uF电容接地
2 (LED-GND) = GND
3 (LED) = D4（注意这里，和之前的不一样）
4 (S-GND) = GND
5 (Vo)  = A0
6 (Vcc) = 5V
*/

#include <SPI.h>
#include<Wire.h>
#include <MultiLCD.h>//LCD5110库
LCD_PCD8544 lcd;
int voutPin = 0;
int ledPin = 4;
int relayPin = 8;
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
int x = 150 ; //闸值,超过:继电器吸合,反之
void setup() {
  lcd.begin(); //初始化LCD
  lcd.clear();
  pinMode(relayPin, OUTPUT);  //继电器设为输出
  Serial.begin(9600);  //串口启动
  pinMode(ledPin, OUTPUT);
  digitalWrite(relayPin, LOW);  //继电器初始化,先设为张开
  lcd.setCursor(0, 0);
  lcd.print(" Dust Density: ");

}
void loop() {
  digitalWrite(ledPin, LOW);
  delayMicroseconds(samplingTime);
  voMeasured = analogRead(voutPin);
  delayMicroseconds(deltaTime);
  digitalWrite(ledPin, HIGH); //关LED
  delayMicroseconds(sleepTime);
  calcVoltage = (float)voMeasured * (5.0 / 1024.0);
  dustDensity = 1000 * 0.17 * calcVoltage - 0.1;
  Serial.print(" Dust Density: ");

  if ( calcVoltage > 3.5 )
  {
    Serial.print(">");  
    lcd.setCursor(2, 2);
    lcd.print("> ");
  }
  else {
    lcd.setCursor(2, 2);
    lcd.print("  ");
  }
  Serial.print(dustDensity);
  lcd.setCursor(12, 2);
  lcd.print(dustDensity);
  Serial.println(" ug/m3");
  lcd.setCursor(52, 2);
  lcd.print("ug/m3");

  if (dustDensity > x) {
    digitalWrite(relayPin, HIGH);
    Serial.println("ON");
    lcd.setCursor(16, 4);
    lcd.print("relay ON ");
  }
  else {
    digitalWrite(relayPin, LOW);
    Serial.println("OFF");
    lcd.setCursor(16, 4);
    lcd.print("relay OFF");
  }
  delay(1000);

}
