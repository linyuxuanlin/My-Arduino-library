#include <MotorDC.h>
 
MotorDC motorDC(9,8);
 
void setup()
{
  Serial.begin(9600);
  Serial.println("Motor DC Library");
}
 
void loop()
{
  // PWM 0 to 255
  motorDC.setSpeed(63);
  delay(10000);
  // PWM -255 to 0
  motorDC.setSpeed(-63);
  delay(10000);

}

