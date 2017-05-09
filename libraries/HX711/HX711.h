#ifndef HX711_h
#define HX711_h

#include "Arduino.h"

class Hx711
{
private:
	int DOUT;//������������
	int SCK;//����ʱ������

	float scale;//�������ϵ��
	long offset;//���岹��ֵ
public:
	Hx711(int IO_DOUT,int IO_SCK);//���캯��
	void setScale(float IO_scale);//���ñ���ϵ��
	void setOffset(long IO_offset);//���ò���ֵ

	long getValue();//�ɼ�һ��ADCֵ
	long getAverageValue(char IO_times);//�ɼ�ADCƽ��ֵ
	float getWeight(char IO_times);//�ó�����ֵ
};

#endif