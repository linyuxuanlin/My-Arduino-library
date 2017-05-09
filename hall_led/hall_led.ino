/*
name: hall sensor & piezo
Description: none 
IDE version:  1.6
Author:  Lin <linyuxuanlin.github.io>
Date:    2017-3-9
*/
int readpin = 2;
int led=13;
int piezo=3;
void setup ()
{
  pinMode (readpin, INPUT) ;
  pinMode (led, OUTPUT) ;
  pinMode (piezo, OUTPUT) ;
  Serial.begin(9600);
}
void loop ()
{
  int incoming = digitalRead(readpin) ;
  //Serial.println(incoming);
  if (incoming == 0) {
    Serial.println("sth detected");
    digitalWrite(13,HIGH);
    digitalWrite(3,LOW);  
  }
   if (incoming == 1) {
    Serial.println("nothing detected");
    digitalWrite(13,LOW);
    digitalWrite(3,HIGH);
  }
   delay(100);
}
