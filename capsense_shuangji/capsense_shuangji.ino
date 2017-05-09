#include <CapacitiveSensor.h>
CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);  
const int ledPin = 13; 
int ledState = LOW;
void setup() {
Serial.begin(9600);
}

void loop() {
 unsigned int total1 =  cs_4_2.capacitiveSensor(30);
 if(total1 > 20 )
     {
      while(total1 > 20){
        for(int i = 0;i < 400;i++) {
          if(total1 > 20 ){
            while(total1 > 20){
              ledState = !ledState;
            break;
            }
          }

         delay(1);
   
        }
      }
     }
     if (ledState) {
    digitalWrite(ledPin ,HIGH);
  }
  else {
    digitalWrite(ledPin ,LOW);
  } 
}
