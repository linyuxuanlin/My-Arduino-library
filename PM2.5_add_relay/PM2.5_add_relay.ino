/*
name: SHARP GP2Y10 & RELAY
version:  1.0
Author:  Lin <824676271@qq.com>
Date:    2016-08-19
Description:  空气质量检测,控制继电器
note: none
*/
int voutPin = 0; // A0
int ledPin = 2; // D2
int relayPin = 8;  //继电器in接D8
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
int x = 150 ; //闸值,超过:继电器吸合,反之
void setup()
{
  pinMode(relayPin, OUTPUT);  //设为输出
  Serial.begin(9600);  //串口启动
  pinMode(ledPin, OUTPUT);
  digitalWrite(relayPin, LOW);  //初始化,先设为关
}
void loop() {
  digitalWrite(ledPin, LOW); // 点亮LED
  delayMicroseconds(samplingTime);
  voMeasured = analogRead(voutPin); // 度数
  delayMicroseconds(deltaTime);
  digitalWrite(ledPin, HIGH); //关LED
  delayMicroseconds(sleepTime);
  calcVoltage = (float)voMeasured * (5.0 / 1024.0);
  dustDensity = 1000 * 0.17 * calcVoltage - 0.1;
  Serial.print(" - Dust Density: ");
  if ( calcVoltage > 3.5 )
  {
    Serial.print(">");  // unit: ug/m3
  }
  Serial.print(dustDensity);
  Serial.println(" ug/m3");

  if (dustDensity > x) {
    digitalWrite(relayPin, HIGH);
    Serial.println("ON");
  }
  else{
    digitalWrite(relayPin, LOW);
    Serial.println("OFF");   
  }
  delay(1000);

}
