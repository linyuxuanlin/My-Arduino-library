#include<Stepper.h>


const int stepsPerRevolution = 210;


Stepper myStepper(stepsPerRevolution, 4, 5);//接线

void setup()
{
  // 设置转速，单位r/min
  myStepper.setSpeed(200);//最大速度


}

void loop()
{

  myStepper.step(15);//步数=度数*3
 

  

}

