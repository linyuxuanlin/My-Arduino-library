#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX
//**********************************************************
//Written by: www.whiteelectronics.pl
//contact: info@whiteelectronics.pl
//LCD: DMT32240M028_06WT - can by any DGUS LCD 2,8"-15" without any change
//UART1 
//A0 - analog input view on DGUS 0x10
//25 - digital input view on DGUS 0x21
//6 - PWM output data from DGUS 0x20
//**********************************************************

int iValue, iTmp;
byte bVal1, bVal2, bVal3;

void setup() {
  // initialize serial:
  mySerial.begin(115200);
//  pinMode(PIN_B5, INPUT_PULLUP);
//  pinMode(PIN_B6, INPUT_PULLUP);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  

 



  for (iTmp=0;iTmp<0x100;iTmp++)
    DGUS_SendVal(iTmp,0);
  



  iValue=0;
  bVal1=0;
  bVal2=0;
  bVal3=0;
  
}

void loop() 
{
    int iAnalog;
    int iTmp;

  for (iTmp=22;iTmp<38;iTmp++)
    InputChack(iTmp,iTmp,0,1);
  

  iAnalog=analogRead(A0); DGUS_SendVal(0x0080,iAnalog);
  delay(1);
  iAnalog=analogRead(A1); DGUS_SendVal(0x0081,iAnalog);
  delay(1);
  iAnalog=analogRead(A2); DGUS_SendVal(0x0082,iAnalog);
  delay(1);
  iAnalog=analogRead(A3); DGUS_SendVal(0x0083,iAnalog);
  delay(1);
  
  mySerialEvent();
}


void mySerialEvent() 
{
  int iLen;
  byte iData[255];
  int iTmp;
  int iAdr, iVal;
  if (mySerial.available()>3)
  {
      if(mySerial.read()==0x5A)
        if(mySerial.read()==0xA5)
        { 
          iLen=mySerial.read();
          iTmp=0;
          while (mySerial.available()<iLen) ; //Wait for all frame !!!! Blocking procedure

          while (iTmp<iLen) //Compile all frame
          { 
            iData[iTmp]=mySerial.read();
            iTmp++;
          }

          iAdr=(iData[1]<<8)+iData[2];
          iVal=(iData[4]<<8)+iData[5];

          for (iTmp=2;iTmp<14;iTmp++)
            if (iAdr==iTmp) analogWrite(iTmp,iVal&0xFF);  //PWM3 set at once

          for (iTmp=38;iTmp<53;iTmp++)
            if (iAdr==iTmp) digitalWrite(iTmp,iVal&0xFF);  //PWM3 set at once
          
           
        }   
  }
}

void DGUS_Beep(byte bTime) // Beep generate bTime*10ms 
{ 
  mySerial.write(0x5A);
  mySerial.write(0xA5);
  mySerial.write(0x03);
  mySerial.write(0x80);
  mySerial.write(0x02);
  mySerial.write(bTime); 
}

void DGUS_LED_Bright(byte bVal) //Screen backlite set 0-0x40
{
  if (bVal>0x40) bVal=0x40;
  mySerial.write(0x5A);
  mySerial.write(0xA5);
  mySerial.write(0x03);
  mySerial.write(0x80);
  mySerial.write(0x01);
  mySerial.write(bVal);
}

void DGUS_SendVal(int iAdr, int iVal)//Send iVal for VP= iAdr to DGUS
{ 
  byte bAdrL, bAdrH, bValL, bValH;
  bAdrL=iAdr&0xFF;
  bAdrH=(iAdr>>8)&0xFF;
  bValL=iVal&0xFF;
  bValH=(iVal>>8)&0xFF;
  
  mySerial.write(0x5A);
  mySerial.write(0xA5);
  mySerial.write(0x05);
  mySerial.write(0x82);
  mySerial.write(bAdrH);
  mySerial.write(bAdrL);
  mySerial.write(bValH);
  mySerial.write(bValL);
  
}

void InputChack(int Adr, int Pin, int On, int Off)
{
  if (digitalRead(Pin)==0) //Read digital and send to DGUS
    DGUS_SendVal(Adr,Off);
  else
    DGUS_SendVal(Adr,On);  


}

