#include <Servo.h>
int trig_pin = 8;
int echo_pin = 9;
long echotime;
float distance;
Servo myservo;

void setup() {
  myservo.attach(2);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  digitalWrite(trig_pin, LOW);
}

void loop() {
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  echotime = pulseIn(echo_pin, HIGH);
  distance = 0.0001 * ((float)echotime * 340.0) / 2.0;
myservo.write(distance);
  if (distance < 10) {
    myservo.write(10);
    delay(100);
  }
  else {
    myservo.write(90); delay(500);
  }

  delay(100);
}
