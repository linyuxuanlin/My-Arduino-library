#include "IRremote.h"
IRsend irsend; 


void setup()
{

  Serial.begin(9600);
  pinMode(2,INPUT);
  pinMode(4,INPUT);
  pinMode(13,OUTPUT);
} 
void loop() 
{
  if(digitalRead(2)==LOW){
    digitalWrite(13,HIGH);
 irsend.sendNEC(0x1B7BDF98, 32); // channel 0  红外发射码前需要加上“0x”
  }
  else{
    digitalWrite(13,LOW);
  }
  
  if(digitalRead(4)==LOW){
    digitalWrite(13,HIGH);
 irsend.sendNEC(0x8E102B22, 32); // channel 0  红外发射码前需要加上“0x”
  }
  else{
    digitalWrite(13,LOW);
  }
  
 delay(200);
}
