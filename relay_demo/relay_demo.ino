//继电器测试程序
//HIGH为关,LOW为开
//by Lin
int relayPin = 8;  //in接D8
void setup()
{
  pinMode(relayPin, OUTPUT);  //设为输出
  Serial.begin(9600);  //串口启动
  digitalWrite(relayPin, HIGH);  //初始化,先设为关
}
void loop()
{
  //效果:LED关一秒,亮一秒
  digitalWrite(relayPin, HIGH);
  Serial.println("OFF");
  delay(1000);
  digitalWrite(relayPin, LOW);
  Serial.println("ON");
  delay(1000);
}
