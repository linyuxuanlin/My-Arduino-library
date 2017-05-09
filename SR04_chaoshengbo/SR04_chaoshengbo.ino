const int TrigPin = 8; 
const int EchoPin = 7; 
float distance; 
void setup() 
{   // 初始化串口通信及连接SR04的引脚
        Serial.begin(9600); 
        pinMode(TrigPin, OUTPUT); 
    // 要检测引脚上输入的脉冲宽度，需要先设置为输入状态
        pinMode(EchoPin, INPUT); 
    Serial.println("Ultrasonic sensor:");
} 
void loop() 
{ 
    // 产生一个10us的高脉冲去触发TrigPin 
        digitalWrite(TrigPin, LOW); 
        delayMicroseconds(2); 
        digitalWrite(TrigPin, HIGH); 
        delayMicroseconds(10);
        digitalWrite(TrigPin, LOW); 
   
        distance = pulseIn(EchoPin, HIGH) / 58.00;
        Serial.print(distance/100); 
        Serial.print("m"); 
        Serial.println(); 
        delay(100); 
}
