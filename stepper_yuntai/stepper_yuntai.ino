#include<Stepper.h>
int x = -90; //x轴固定步数,步数=度数*3,负的值是为比较方便理解
int y = 45; //y轴固定步数,步数=度数*3
int delaytime = 1000; //停下来的时间
const int stepsPerRevolution = 100;
Stepper Stepper1(stepsPerRevolution,  4, 5, 6, 7);
//下步进电机接线
Stepper Stepper2(stepsPerRevolution,  8, 9, 10, 11);
//上步进电机接线
void setup() {
  Serial.begin(9600);
  Stepper1.setSpeed(300);
  Stepper2.setSpeed(300);  //最大速度
  Serial.println("Hello world");
}

void loop() {

  //1
  Stepper1.step(x);
  Stepper2.step(y);
  delay(delaytime);

  //2
  Stepper1.step(-x);
  delay(delaytime);

  //3
  Stepper1.step(-x);
  delay(delaytime);
 
  //4
  Stepper2.step(-y);
  Stepper2.step(-y);
  delay(delaytime);

  //5
  Stepper1.step(x);
  delay(delaytime);

  //6
  Stepper1.step(x);
  delay(delaytime);

  //回到原点
  Stepper1.step(-x);
  Stepper2.step(y);
  delay(delaytime);
  delay(delaytime);//延时多一点
}
