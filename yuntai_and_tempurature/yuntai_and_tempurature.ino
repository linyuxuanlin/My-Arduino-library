#include <i2cmaster.h>  //调用IIC库
#include <SoftwareSerial.h>  //调用软串口
#include<Stepper.h>

int x = -90; //x轴固定步数,步数=度数*3,负的值是为比较方便理解
int y = 45; //y轴固定步数,步数=度数*3
int delaytime = 1000; //停下来的时间
const int stepsPerRevolution = 100;
Stepper Stepper1(stepsPerRevolution,  4, 5, 6, 7);
//下步进电机接线
Stepper Stepper2(stepsPerRevolution,  8, 9, 10, 11);
//上步进电机接线
SoftwareSerial mySerial(2, 3);  //RO,DI的接线
void setup() {
  Serial.begin(9600);  //设置串口波特率
  mySerial.begin (9600);  //设置RS485的波特率
  pinMode(12, OUTPUT);  //DE,RE的接线
  digitalWrite(12, LOW);  //设置低电平以发送数据
  i2c_init(); //初始化IIC总线
  PORTC = (1 << PORTC4) | (1 << PORTC5);//上拉使能
  Stepper1.setSpeed(300);
  Stepper2.setSpeed(300);  //最大速度
  Serial.println("Setup...");  //启动提示
  mySerial.println("hello world");  //启动提示
}

void loop() {
  delay(2000);
  //1
  Stepper1.step(x);
  Stepper2.step(y);
  Serial.print("first point:");
  mySerial.print("first point:");
  tempurature();

  //2
  Stepper1.step(-x);
  Serial.print("second point:");
  mySerial.print("second point:");
  tempurature();

  //3
  Stepper1.step(-x);
  Serial.print("third point:");
  mySerial.print("third point:");
  tempurature();

  //4
  Stepper2.step(-y);
  Stepper2.step(-y);
  Serial.print("fourth point:");
  mySerial.print("fourth point:");
  tempurature();

  //5
  Stepper1.step(x);
  Serial.print("fifth point:");
  mySerial.print("fifth point:");
  tempurature();

  //6
  Stepper1.step(x);
  Serial.print("sixth point:");
  mySerial.print("sixth point:");
  tempurature();

  //回到原点
  Stepper1.step(-x);
  Stepper2.step(y);
  Serial.println("origin");
  mySerial.println("origin");
  delay(3000);//延时一些时间
}

void tempurature() {
  int Dev24C02 = 0x5A << 1;
  int data_low = 0;
  int data_high = 0;
  int pec = 0;
  i2c_start_wait(Dev24C02 + I2C_WRITE);  //设置IIC地址
  i2c_write(0x07);
  i2c_rep_start(Dev24C02 + I2C_READ);
  data_low = i2c_readAck(); //Read 1 byte and then send ack
  data_high = i2c_readAck(); //Read 1 byte and then send ack
  pec = i2c_readNak();
  i2c_stop();

  //这将一起转换高低字节,渲染出温度.MSB是一个错误位,忽略温度
  double tempFactor = 0.02; // 每LSB为0.02度(MLX90614的测量分辨率)
  double tempData = 0x0000; // 使数据归零
  int frac; // 小数点后的数据

  // 掩盖高字节的错误位，然后移动让它留下8位，并增加了低字节。
  tempData = (double)(((data_high & 0x007F) << 8) + data_low);
  tempData = (tempData * tempFactor) - 0.01;
  float i = tempData - 273.15;  //定义温度储存的变量
  Serial.print("tempurature:");   //输出到串口: "摄氏度:"
  mySerial.print("tempurature:");
  Serial.println(i);  //输出到串口: 温度的数据
  mySerial.println(i);  //输出数据
  delay(1000); //延时1秒
}

