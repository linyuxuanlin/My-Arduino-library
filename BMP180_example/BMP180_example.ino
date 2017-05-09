#include <SFE_BMP180.h>
#include <Wire.h>
 
SFE_BMP180 pressure;// 创建一个气压计对象
 
double baseline; // 基准气压
 
void setup()
{
  Serial.begin(9600);
  Serial.println("REBOOT");
 
  // 初始化传感器
  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    // 糟糕，气压计出问题了，多半是连线有问题
    Serial.println("BMP180 init fail (disconnected?)\n\n");
    while(1); // 暂停
  }
 
  //获得基准气压
  baseline = getP();
 
  Serial.print("baseline pressure: ");
  Serial.print(baseline);
  Serial.println(" hPa");  
}
 
void loop()
{
  double a,p,t;
  p = getP();// 获得一个气压值
  a = pressure.altitude(p,baseline);//获得基于基准气压的高度值
 
  Serial.print("relative altitude: ");
  if (a >= 0.0) Serial.print(" "); // 调整正数显示格式
  Serial.print(a,1);
  Serial.print(" meters ");  
 
  t = getT();// 获得一个温度值
  Serial.print("temperature: ");
  Serial.print(t,1);
  Serial.println(" degrees");  
 
 
  delay(500);//刷新率
}
 
 
double getP()
{
  char status;
  double T,P,p0,a;
  // You must first get a temperature measurement to perform a pressure reading.
  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.
  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);
    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Use '&T' to provide the address of T to the function.
    // Function returns 1 if successful, 0 if failure.
 
    status = pressure.getTemperature(T);
    if (status != 0)
    {
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.
      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);
        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Use '&P' to provide the address of P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.
        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          return P;
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
}
 
double getT()
{
  char status;
  double T,p0;
  status = pressure.startTemperature();
  if (status != 0)
  {
    delay(status);
    status = pressure.getTemperature(T);
    if (status != 0)
    {
      status = pressure.startPressure(3);
      return T;
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
}

