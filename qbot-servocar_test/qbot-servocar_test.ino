
#include <Servo.h>
Servo servo1;
Servo servo2;
int l = 0; 
int r = 0;
int time =700;
void setup() {
  servo1.attach(3); 
  servo2.attach(2);
  Serial.begin(9600);
  
  stop();
  delay(500);
   
  Serial.println("hello");
  
  
}

void loop() {

  
  

  char val = Serial.read();
  

  if (val=='W'){
    go();
    
     Serial.println("W");
    delay(time);
    stop();
  }
  if (val=='S'){
    back();
    delay(time);
    stop();
    Serial.println("S");
  }
  if (val=='A'){
    left();
    delay(time);
    stop();
    Serial.println("A");
  }
  if (val=='D'){
    right();
    delay(time);
    stop();
    Serial.println("D");
  }
  
 
}
void go(){
  servo1.write(180);
  servo2.write(0);
}
void back(){
  servo1.write(0);
  servo2.write(180);
}
void right(){
  servo1.write(90);
  servo2.write(0);
}
void left(){
  servo1.write(90);
  servo2.write(180);
}
void stop(){
   servo1.write(0);
  servo2.write(90);
}

