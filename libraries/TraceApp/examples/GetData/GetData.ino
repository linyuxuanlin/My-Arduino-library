/*******************************************
一个个人小项目，配套APP下载以及相关教程见
http://pengzhihui.xyz/2016/05/05/trace/
*******************************************/

#include <TraceApp.h>

TraceApp obj(Serial, 115200);   //实例化检测对象

void setup()
{
  obj.begin();      //初始化,注意:后面不需要再用Serial.begin()!
}

void loop()
{
  obj.routine();    //尽可能让这一句频繁运行

  if (obj.valid())  //检测的物体是否有效
  {
    Serial.print("Obj detected at:");
    Serial.print(obj.getX());  //x坐标
    Serial.print(",");
    Serial.print(obj.getY());  //y坐标
    Serial.print("  with size of:");
    Serial.println(obj.getT()); //物体大小
  }
  else
    Serial.println("No obj or too many detected");

  delay(100);
}