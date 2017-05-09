#include <dht11.h>
dht11 ggyy;   // 注意现在 ggyy 代表 DHT11 传感器
const int pin = 4;  // 
void setup( ) {
  Serial.begin(115200);
}
void loop( ) {
  ggyy.read(pin);  // 读取 DHT11 传感器
  Serial.print(String("") + "Humidity = "+ ggyy.humidity + " %");
  Serial.println(String("")+", temperature = "+ ggyy.temperature +" C");
  delay(2222);  // 规定至少要等 2 秒再次读 dht11
}
