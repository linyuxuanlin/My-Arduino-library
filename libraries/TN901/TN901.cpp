/**
 * TN901 Library
 * 说明: 台湾燃太TN901传感器库
 * 版权: AngelIOT www.96121.org
 */

#include "TN901.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"



  //初始化TN901传感器
  void TN901::Init(int TN_Data,int TN_Clk,int TN_ACK)
  {
    //定义私有端口
    _dataPin=TN_Data;
    _clkPin=TN_Clk;
    _ackPin=TN_ACK;

    pinMode(_clkPin, INPUT);
    pinMode(_ackPin, OUTPUT);
    digitalWrite(_ackPin,HIGH);
  }
  
  //读取数据
  void TN901::Read()
  {
    digitalWrite(_ackPin,LOW);
    ReadData(0x4c);//目标温度的第一个字节为0x4c    
    if((Data[0]==0x4c)&&
       (Data[4]==0x0d))//每帧的最后一个字节为0x0d    
    {   
      GetData_OT();  
    } 
   
    delay(1); //等待1毫秒
          
    digitalWrite(_ackPin,LOW); 
    ReadData(0x66);//环境温度的第一个字节为0x66      
  
    if((Data[0]==0x66)&&
       (Data[4]==0x0d))//每帧的最后一个字节为0x0d    
    {   
      GetData_ET();
    }
  }


  //读取数据
  void TN901::ReadData(char flag)
  {
    char i,j,k;
    byte BitState = 0;          //每次发七帧
    for(k=0;k<7;k++)
    {
      for(j=0;j<5;j++)        //每帧5个字节
      {
        for(i=0;i<8;i++)
        {
          int temp= digitalRead(_clkPin);
          while(temp)
          {
            temp = digitalRead(_clkPin);
          } 
          temp= digitalRead(_clkPin);
          BitState= digitalRead(_dataPin);
          Data[j]= Data[j]<<1;
          Data[j]= Data[j]|BitState;
          
          while(!temp)
          {
            temp = digitalRead(_clkPin);
          }
        }
      }
     if(Data[0]==flag)  k=8;
    }

    digitalWrite(_ackPin,HIGH);
  }

  //计算环境温度 
  int TN901::GetData()   
  {   
    int Temp;   
    Temp=(Data[1]<<8)|Data[2];   
    Temp = int(((float)Temp/16 - 273.15)*100);      
    return Temp;
  }  

  //计算环境温度 
  void TN901::GetData_ET()   
  {      
    ET=(Data[1]<<8)|Data[2];   
    ET = int(((float)ET/16 - 273.15)*100);      
  }   

  //计算目标温度
  void TN901::GetData_OT()   
  {   
    OT=(Data[1]<<8)|Data[2];   
    OT = int(((float)OT/16 - 273.15)*100);      
  }  
