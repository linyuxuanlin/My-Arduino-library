//此程序只适合sony的ps2手柄
//by Lin
#include <PS2X_lib.h>
//接线
#define PS2_DAT        5
#define PS2_CMD        4
#define PS2_SEL        3
#define PS2_CLK        2
#define pressures   true  //按压力度,改 false 取消
#define rumble      true  //手柄震动,改 false 取消
PS2X ps2x;  //创建类
int error = 0;
byte type = 0;
byte vibrate = 0;
void (* resetFunc) (void) = 0; //重启的函数

void setup() {
  Serial.begin(115200);
  delay(500);  //必须先延时让接收器期待
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  if (error == 0) {
    Serial.print("发现手柄,配置成功");

  }
  else if (error == 1)
    Serial.println("未发现手柄,检查接线");

  else if (error == 2)
    Serial.println("发现手柄但是没有连接权限");

  else if (error == 3)
    Serial.println("手柄拒绝打开压力传感器");

}

void loop() {
  //如果调用震动,就需要延时
  if (error == 1) { //如果没有发现手柄,就重启接收器
    resetFunc();
  }


  ps2x.read_gamepad(false, vibrate); //读取,并设置手柄以'vibrate'的速度震动
  vibrate = ps2x.Analog(PSAB_CROSS); //检测按下X的力度,并转化为震动强度(都为0-255)

  if (ps2x.Button(PSB_START)) //一旦按下就触发,可多次
    Serial.println("Start 被按下");
  if (ps2x.Button(PSB_SELECT))
    Serial.println("Select 被按下");
  if (ps2x.Button(PSB_PAD_UP)) {
    Serial.print("上 被按下,力度: ");
    Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
  }
  if (ps2x.Button(PSB_PAD_RIGHT)) {
    Serial.print("右 被按下,力度: ");
    Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
  }
  if (ps2x.Button(PSB_PAD_LEFT)) {
    Serial.print("左 被按下,力度: ");
    Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
  }
  if (ps2x.Button(PSB_PAD_DOWN)) {
    Serial.print("下 被按下,力度: ");
    Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
  }

  if (ps2x.NewButtonState()) { //设置只能改变状态后再重新触发,以设置只能单次
    if (ps2x.Button(PSB_L2))
      Serial.println("L2 被按");
    if (ps2x.Button(PSB_R2))
      Serial.println("R2 被按");

  }

  if (ps2x.Button(PSB_TRIANGLE)) //按下就触发,多次
    Serial.println("三角形 被按");
  if (ps2x.ButtonPressed(PSB_CIRCLE)) //按下后会触发
    Serial.println("圆形 刚刚被按");
  if (ps2x.NewButtonState(PSB_CROSS)) //当按键状态改变的时候触发,按下松开,触发两次
    Serial.println("叉 刚刚改变状态");
  if (ps2x.ButtonReleased(PSB_SQUARE)) //松开后会触发
    Serial.println("正方形 刚刚松开");

  if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) { //如果L1或R1被按下,显示摇杆位置
    Serial.print("摇杆位置:");
    Serial.print(ps2x.Analog(PSS_LY), DEC); //左Y轴
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_LX), DEC); //左X轴
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_RY), DEC); //右Y轴
    Serial.print(",");
    Serial.println(ps2x.Analog(PSS_RX), DEC); //右X轴

  }
  delay(50);  //延时一小会
}
