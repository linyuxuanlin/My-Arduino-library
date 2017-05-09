#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>
#include <dht11.h>
String temp;
String wet;
dht11 ggyy;   // 注意现在 ggyy 代表 DHT11 传感器
char auth[] = "78f8c94c46a043a6bdcc846067363501";
const int pin = 4;
void setup() {
     Serial.begin(115200);
     Blynk.begin(auth);

}
  void sendUptime()
    {
     // shows the value temp on virtual pin 10
     Blynk.virtualWrite(2, wet); 
      Blynk.virtualWrite(1, temp); 
    }
    
void loop() {
  Blynk.run();
 ggyy.read(pin); 
 temp=(String("") + "Humidity = "+ ggyy.humidity + " %");
 wet=(String("")+", temperature = "+ ggyy.temperature +" C");
 

}
