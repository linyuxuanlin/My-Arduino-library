
#include <TN901.h> //TN901的库
TN901 tn;                 //创建TN901的对象
 
#include <Arduino.h> 
#include <Wire.h>
#include <MicroLCD.h> //OLED的库
LCD_SSD1306 lcd; /* for SSD1306 OLED module */
static const PROGMEM uint8_t tick[16 * 16 / 8] =
{0x00,0x80,0xC0,0xE0,0xC0,0x80,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0x78,0x30,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x1F,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00}; //显示勾
static const PROGMEM uint8_t cross[16 * 16 / 8] =
{0x00,0x0C,0x1C,0x3C,0x78,0xF0,0xE0,0xC0,0xE0,0xF0,0x78,0x3C,0x1C,0x0C,0x00,0x00,0x00,0x30,0x38,0x3C,0x1E,0x0F,0x07,0x03,0x07,0x0F,0x1E,0x3C,0x38,0x30,0x00,0x00}; //显示叉
 

 

 
void setup()
{
    pinMode(A0,INPUT); //设置距离传感器的端口
    tn.Init(8,2,7);  //tn901初始化
    lcd.begin(); //oled启动
  //lcd.setFont(FONT_SIZE_LARGE); //设置字体尺寸
    lcd.setCursor(0, 3); 
    
}
 
void loop()
{
  static int temp;  
  int t;
  boolean mode=false; //true - BODY; false - ROOM
  tn.Read(); //读取TN901的温度
  mode=!digitalRead(A0);  //检测距离传感器是否接近人体
  if(mode)  //如果接近人体
  {
       t=tn.OT+180; //tn.OT读取人体温度
       if(temp<t)temp=t;
  }
  else temp=tn.ET-400; //tn.ET,读取环境温度
   LCD_Value(temp,mode); //oled上显示人体温度或环境温度
   delay(200); //延时，以便TN901刷新
}
 
void LCD_Value(int temp,boolean mode)
{
  lcd.setCursor(30, 3); 
  lcd.print((float)temp/100);
  lcd.print(" C");
  //if(mode) lcd.draw( tick, 54, 48, 16, 16);
  //else     lcd.draw(cross, 54, 48, 16, 16);
}
 

