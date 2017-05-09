/**
 * TN901 Library
 * 说明: 台湾燃太TN901传感器库
 * 版权: AngelIOT www.96121.org
 */

#ifndef TH901_H
#define TH901_H


#include <inttypes.h>

#define TN901_OTADDRESS 0x4c
#define TN901_ETADDRESS 0x66
#define TN901_ENDADDRESS 0x0d


class TN901
{
  public:
    short ET;
    short OT;
    void Init(int TN_Data,int TN_Clk,int TN_ACK);
    void Read();
    void ReadData(char flag);
    int  GetData();
    void  GetData_OT();
    void  GetData_ET();
  private:
    int _dataPin;
    int _clkPin;
    int _ackPin;
    unsigned char  Data[5]; 
};

#endif