/*
LCD5110接法：
clk  = D7     //clock
din  = D6,   // data-in
dc    = D5,   // data select
reset = D2,   //reset
sce   = D3;  // enable
*/
#include <SPI.h>
#include<Wire.h>
#include <MultiLCD.h>//LCD5110库
LCD_PCD8544 lcd;
void setup() {
  //初始化LCD
  lcd.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  //光标位置(列，行)
  lcd.print("  Hello World ");
}

void loop() {
  lcd.setCursor(8, 3);
  lcd.print("  by Lin ");
}




