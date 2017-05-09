#include <MotorDC.h>
 
MotorDC motorDC(9,8);
 
void setup()
{
  Serial.begin(9600);
  Serial.println("Motor DC Library");
}
 
void loop()
{
 
  motorDC.setSpeed(255);
  
}

