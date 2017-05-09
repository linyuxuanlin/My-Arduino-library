#include <Wire.h>   
#include <LiquidCrystal_I2C.h>
int trig_pin = 3;
int echo_pin = 2;
long echotime; //in micro seconds
float distance; //in cm

LiquidCrystal_I2C lcd(0x27,20,4);  //设置IIC地址

void setup()
{
  lcd.init();  //初始化
  lcd.backlight();  //打开背光

  lcd.setCursor(5,1);
  lcd.print("by Lin");
  pinMode(trig_pin, OUTPUT); 
  pinMode(echo_pin, INPUT);
  digitalWrite(trig_pin, LOW);
}


void loop()
{
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  //get the result
  echotime= pulseIn(echo_pin, HIGH);
  distance= 0.0001*((float)echotime*340.0)/2.0;
  
  //send over Bluetooth 
    lcd.setCursor(1,0);  //设置第几列之后;第几行
  lcd.print(distance);
  lcd.setCursor(5,1);
  lcd.print("by Lin");
  
  delay(100);
}
