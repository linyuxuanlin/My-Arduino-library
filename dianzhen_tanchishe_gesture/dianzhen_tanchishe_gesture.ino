/*
  name:Snake game made with the Gesture Sensor
  version:  1.0
  Author:  Lin <824676271@qq.com>
  Date:    2016-08-18
  Description:  红外手势贪吃蛇
  note: 首先,把 LedControl 和 SparkFun_APDS9960 的库通通丢进libraries里
*/

/*
  接线:
  MAX7219控制的8x8点阵
  Din-D12
  CLK-D11
  CS -D10
  红外手势传感器
  SDA -A4
  SCL -A5
  INT -D2
*/

#include <LedControl.h>
#include <Wire.h>
#include <SparkFun_APDS9960.h>
LedControl lc = LedControl(12, 11, 10, 1);
#define APDS9960_INT    2
SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;
String direction;
int snakeX[36];
int snakeY[36];
int speed = 1000; //延迟,数值越大贪吃蛇速度回越慢
int snakeSize;
int foodX;
int foodY;
boolean inGame = false;
void setup() {
  attachInterrupt(0, interruptRoutine, FALLING);
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  if ( apds.enableGestureSensor(true) ) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }
  lc.shutdown(0, false);
  lc.setIntensity(0, 2); //亮度(0-15),太亮了会伤眼睛哦
  lc.clearDisplay(0); //清屏
  Serial.begin(9600);
  newGame(); //开始新游戏
}
void loop() {
  if (inGame) { //检查是否已经在游戏中
    lc.clearDisplay(0); //清屏
    switch ( apds.readGesture() ) {
      //
      case DIR_UP:
        Serial.println("UP");
        direction = "right";//为什么?因为我想要把屏幕转90度
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
        direction = "left";
        break;
      case DIR_LEFT:
        Serial.println("LEFT");
        direction = "up";
        break;
      case DIR_RIGHT:
        Serial.println("RIGHT");
        direction = "down";
        break;
      default:
        Serial.println("NONE");
    }
    move(direction); //朝挥手的方向移动蛇
    checkIfHitFood(); //检测是否吃到食物
    checkIfHitSelf(); //检查是否吃到自己
    drawSnake(); //在点阵平上画蛇
    drawFood(); //在点阵平上画食物
    if (digitalRead(APDS9960_INT) == 0) {
      apds.init();
      apds.enableGestureSensor(true);
    }
    isr_flag = 0;
    delay(speed); //稍稍延时
  }
}

int simple(int num) {
  return (num * 9 / 1024);
}

void move(String dir) {
  for (int i = snakeSize - 1; i > 0; i--) { 
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  if (dir == "up") {
    if (snakeY[0] == 0) {    
      snakeY[0] = 7;
    } else {
      snakeY[0]--;
    }
  } else if (dir == "down") {
    if (snakeY[0] == 7) {       
      snakeY[0] = 0;
    } else {
      snakeY[0]++;
    }
  } else if (dir == "left") {
    if (snakeX[0] == 0) { 
      snakeX[0] = 7;
    } else {
      snakeX[0]--;
    }
  } else if (dir == "right") {
    if (snakeX[0] == 7) { 
      snakeX[0] = 0;
    } else {
      snakeX[0]++;
    }
  }
}

void drawSnake() {
  for (int i = 0; i < snakeSize; i++) {
    lc.setLed(0, snakeY[i], snakeX[i], true);
  }
}

void drawFood() {
  lc.setLed(0, foodY, foodX, true);
  delay(50); //一点小延时让食物区别于蛇身
  lc.setLed(0, foodY, foodX, false);
}

//This method sets a new location of the food randomly.
void newFood() {
  int newFoodX = random(0, 8);
  int newFoodY = random(0, 8);
  while (isSnake(newFoodX, newFoodY)) { 
    newFoodX = random(0, 8);
    newFoodY = random(0, 8);
  }
  foodX = newFoodX;
  foodY = newFoodY;
}

void checkIfHitFood() {
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    snakeSize++; 
    newFood(); 
  }
}

void checkIfHitSelf() {
  for (int i = 1; i < snakeSize - 1; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      gameOver(); //Call the gameOver() method.
    }
  }
}

boolean isSnake(int x, int y) {
  for (int i = 0; i < snakeSize - 1; i++) {
    if ((x == snakeX[i]) && (y == snakeY[i])) {
      return true;
    }
  }
  return false;
}


void newGame() {
  for (int i = 0; i < 36; i++) { 
    snakeX[i] = -1;
    snakeY[i] = -1;
  }
  snakeX[0] = 4; 
  snakeY[0] = 8; 
  direction = "up"; 
  snakeSize = 1; 
  newFood(); 
  inGame = true; 
  }
  
void interruptRoutine() {
  isr_flag = 1;
}

void gameOver() {
  inGame = false; 
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      lc.setLed(0, y, x, true);
      delay(20);
      lc.setLed(0, y, x, false);
    }
  }
  newGame(); 
}
