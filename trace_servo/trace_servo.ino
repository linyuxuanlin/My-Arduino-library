#include <TraceApp.h>
#include <Servo.h>
TraceApp obj(Serial, 9600);   //实例化检测对象
Servo myservo1;
Servo myservo2;
int pos ;
int kos ;

void setup()
{
  myservo1.attach(2);
  myservo1.write(90);
  myservo2.attach(3, 802, 2400);
  myservo2.write(90);
  obj.begin();      //初始化,注意:后面不需要再用Serial.begin()!
}

void loop()
{
  obj.routine();    //尽可能让这一句频繁运行

  if (obj.valid())  //检测的物体是否有效
  {
  

myservo1.write(obj.getX()/2+10);
myservo2.write(obj.getY()/1.6-60);
    
   
    delay(20);

  }

}









