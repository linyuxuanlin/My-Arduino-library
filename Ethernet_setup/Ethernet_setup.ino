#include<SPI.h>
#include<Ethernet.h>
byte mac[]={0xDE,0xAD,0xBE,0xEF,0xFE,0xED};

void setup() {
 Serial.begin(9600);
 if(Ethernet.begin(mac) ==  0){
  Serial.println("faild");
  for(;;);
  Serial.print("IP");
  for(byte thisByte = 0;thisByte<4;thisByte++){  
    Serial.print(Ethernet.localIP()[thisByte],DEC);
    Serial.print(".");    
  }
  Serial.println(); 
 }
}

void loop() {
  
}
