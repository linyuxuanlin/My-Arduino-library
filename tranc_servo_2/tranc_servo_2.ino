#include <TraceApp.h>
#include <Servo.h>
TraceApp obj(Serial, 9600);   //实例化检测对象
Servo myservo;
int pos=90 ;
int i;
int j;
int data=90;
void setup()
{
  myservo.attach(2);
  myservo.write(90);
  obj.begin();      //初始化,注意:后面不需要再用Serial.begin()!
  myservo.write(pos);
}

void loop()
{
  obj.routine();    //尽可能让这一句频繁运行

  if (obj.valid())  //检测的物体是否有效
  {

    Serial.println(obj.getT()); //物体大小

   

    
    if (obj.getX() >= 150 ) {
      pos = 90 + (((obj.getX()) - 150));
while(i>=pos){
  i=data;
  i++;
  myservo.write(i);
  delay(10);
}
data=pos;
      
     

    }
    else {
      pos = 90 - ((150 - (obj.getX())));
      
while(i<=pos){
  j=data;
  j--;
  myservo.write(i);
  delay(10);
}
data=pos;
      
      
    }

  }





}


