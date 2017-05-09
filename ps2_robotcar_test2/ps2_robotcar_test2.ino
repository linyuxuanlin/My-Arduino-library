#include <PS2X_lib.h>  //for v1.6
#include <Servo.h>

#define PS2_DAT        7  //14    
#define PS2_CMD        5  //15
#define PS2_SEL        4  //16
#define PS2_CLK        6  //17

Servo servo_pin_5;
Servo servo_pin_6;
Servo servo_pin_7;
Servo servo_pin_8;
Servo servo_pin_9;

//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false
PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning
//you must always either restart your Arduino after you connect the controller,
//or call config_gamepad(pins) again after connecting the controller.

int error = 0;
byte type = 0;
byte vibrate = 0;

void setup() {
  delay(300);
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  servo_pin_9.attach(39);
  servo_pin_6.attach(43);
  servo_pin_8.attach(40);
  servo_pin_7.attach(41);
  servo_pin_5.attach(44);
  pinMode( 30 , OUTPUT);
  pinMode( 31 , OUTPUT);
  pinMode( 32 , OUTPUT);
  pinMode( 33 , OUTPUT);
  pinMode( 34 , OUTPUT);
  pinMode( 35 , OUTPUT);
  pinMode( 36 , OUTPUT);
  pinMode( 37 , OUTPUT);
  pinMode( 2  , OUTPUT);
}


void loop() {
  if (error == 1) //skip loop if no controller found
    return;

  if (type == 2) {
    ps2x.read_gamepad();
    if (ps2x.Button(PSB_TRIANGLE)) {
      servo_pin_9. write( 28 );
      delay( 300 );
      servo_pin_8.write( 90 );
      servo_pin_6.write( 90 );
      servo_pin_6.write( 95 );
      delay( 300 );
      servo_pin_5.write( 70 );
      servo_pin_5.write( 75 );
      delay( 300 );
      servo_pin_7.write( 140 );
    }
    if (ps2x.Button(PSB_CROSS)) {
      servo_pin_9.write( 100 );
      delay( 300 );
      servo_pin_6.write( 90 );
      delay( 100 );
      servo_pin_5.write( 130 );
      delay( 100 );
      servo_pin_7.write( 150 );      
    }
    if(ps2x.Button(PSB_PAD_UP)) { 
      digitalWrite( 30 , LOW );
      digitalWrite( 31 , HIGH );
      digitalWrite( 32 , HIGH );
      digitalWrite( 33 , LOW );
      digitalWrite( 34 , LOW );
      digitalWrite( 35 , HIGH );
      digitalWrite( 36 , HIGH );
      digitalWrite( 37 , LOW );      
    }
  }
}
