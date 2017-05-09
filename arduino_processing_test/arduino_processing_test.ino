int potpin = 0; //把电位计连在Arduino模拟端口0
//初始化 
void setup() 
{
  Serial.begin(9600);//启动串行通讯，波特率为9600b/s
}


void loop() 
{
  //读取电位计电压量的采样值，采样值范围为0~1023
  int sensorValue = analogRead(potpin);  
  //把范围为0~1023的采样值正比转换为范围0~255单字节数据
  int data= sensorValue/4;
  //把包含电压值信息的单字节数据通过串口发送到上位机    
  Serial.print(data); 
  delay(20);  //延时20ms
}

