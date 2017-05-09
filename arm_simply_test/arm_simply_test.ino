#include <Servo.h>

Servo servo_pin_4;
Servo servo_pin_5;

void setup()
{
pinMode( 11 , INPUT);
pinMode( 12 , INPUT);
servo_pin_4.attach(4);
servo_pin_5.attach(5);
}

void loop()
{
if (digitalRead( 12))
{
servo_pin_4.write( 80 );
}
else
{
servo_pin_4.write( 90 );
}
if (digitalRead( 11))
{
servo_pin_5.write( 90 );
}
}


