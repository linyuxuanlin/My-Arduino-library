#include <i2cmaster.h>  //调用IIC库

void setup() {
  Serial.begin(9600);  //设置串口波特率
  Serial.println("Setup...");  //启动提示

  i2c_init(); //初始化IIC总线
  PORTC = (1 << PORTC4) | (1 << PORTC5);//上拉使能
}
void loop() {
  int Dev24C02 = 0x5A << 1;
  int data_low = 0;
  int data_high = 0;
  int pec = 0;

  i2c_start_wait(Dev24C02 + I2C_WRITE);  //设置IIC地址
  i2c_write(0x07);

  //读数
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

  float celcius = tempData - 273.15;  //定义摄氏度
  Serial.print("Tempurature: ");   //输出到串口: "摄氏度:"
  Serial.println(celcius);  //输出到串口: 温度的数据
  delay(1000); //延时1秒
}
