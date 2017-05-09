#include "HX711.h"

#include "Arduino.h"

//int DOUT;//������������
//int SCK;//����ʱ������

//float scale;//�������ϵ��
//long offset;//���岹��ֵ
//int times;//����ɼ�����

Hx711::Hx711(int IO_DOUT,int IO_SCK)//���캯��
{
	DOUT = IO_DOUT;
	SCK = IO_SCK;
	pinMode(SCK, OUTPUT);//����IO�ڹ�����ʽ
	pinMode(DOUT, INPUT);

}

void Hx711::setScale(float IO_scale)//���ñ���ϵ��
{
	scale = IO_scale;
}

void Hx711::setOffset(long IO_offset)//���ò���ֵ
{
	offset = IO_offset;
}

long Hx711::getValue()//�ɼ�һ��ADCֵ
{
	unsigned long Count;
	unsigned char i;
	digitalWrite(SCK,LOW);
	Count = 0;
	while(digitalRead(DOUT) == 1);//�͵�ƽʱ���ݿ������
	for(i=0;i<24;i++)//ѭ����ȡ����
	{
		digitalWrite(SCK,HIGH);
		Count = Count<<1;
		digitalWrite(SCK,LOW);
		if(digitalRead(DOUT) == 1) Count++;//���λ��1
	}
	digitalWrite(SCK,HIGH);
	Count = Count^0x800000;//���λ��0
	digitalWrite(SCK,LOW);//128����
	return Count;
}

long Hx711::getAverageValue(char IO_times)//�ɼ�ADCƽ��ֵ
{
	long sum=0;
	char i;
	for(i=0;i<IO_times;i++)
	{
		sum += getValue();
	}
	return sum/IO_times;

}

float Hx711::getWeight(char IO_times)//�ó�����ֵ
{
	long temp;
	temp = getAverageValue(IO_times) - offset;
	return (float)temp/scale;
}

