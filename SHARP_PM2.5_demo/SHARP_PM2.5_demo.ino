/*
name: SHARP GP2Y10 demo
version:  1.0
Author:  Lin <824676271@qq.com>
Date:    2016-08-19
Description:  空气质量检测
note: 输出单位ug/m3
*/
int voutPin = 0; // A0
int ledPin = 2; // D2
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
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
  delay(1000);

}
