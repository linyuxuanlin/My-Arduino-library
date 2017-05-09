#include <UTFT.h>
extern uint8_t SmallFont[];
UTFT myGLCD(ILI9481,38,39,40,41);
void setup() {
  randomSeed(analogRead(0));
  
// Setup the LCD
  myGLCD.InitLCD();
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
    myGLCD.clrScr();
}

void loop() {
  int buf[478];
  int x, x2;
  int y, y2;
  int r;

 myGLCD.fillScr(0, 0, 255);
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRoundRect(160, 70, 319, 169);
  
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.print("林", CENTER, 93);
  myGLCD.print("Restarting in a", CENTER, 119);
  myGLCD.print("few seconds...", CENTER, 132);
   myGLCD.setColor(0, 255, 0);
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.print("Runtime: (msecs)", CENTER, 290);
  myGLCD.printNumI(millis(), CENTER, 305);
  
  delay (10000);
  
 
myGLCD.clrScr();
 

 
}
