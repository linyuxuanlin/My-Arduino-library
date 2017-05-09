#include <PS2X_lib.h>
const int in1 =30;
const int in2 =31;
const int in3 =32;
const int in4 =33;
const int in5 =34;
const int in6 =35;
const int in7 =36;
const int in8 =37;
const int en1 =6;
const int en2 =7;
const int en3 =4;
const int en4 =5;
const int led =41;
#define PS2_DAT        5   
#define PS2_CMD        4
#define PS2_SEL        3
#define PS2_CLK        2
//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false
int error = 0;
byte type = 0;
byte vibrate = 0;
PS2X ps2x; 
void setup() {
  digitalWrite(led,HIGH);
  Serial.begin(57600);
  delay(300);
  digitalWrite(led,LOW);
  pinMode( in1 ,OUTPUT);
  pinMode( in2 ,OUTPUT);
  pinMode( in3 ,OUTPUT);
  pinMode( in4 ,OUTPUT);
  pinMode( in5 ,OUTPUT);
  pinMode( in6 ,OUTPUT);
  pinMode( in7 ,OUTPUT);
  pinMode( in8 ,OUTPUT);
  pinMode( led ,OUTPUT);
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  if(error == 0){
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
  if (pressures)
    Serial.println("true ");
  else
    Serial.println("false");
  Serial.print("rumble = ");
  if (rumble)
    Serial.println("true)");
  else
    Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }  
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  
//  Serial.print(ps2x.Analog(1), HEX);
  
  type = ps2x.readType(); 
  switch(type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
  case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
   }  

}

void loop() {
  if(error == 1) //skip loop if no controller found
    return; 
  
  if(type == 2){ //Guitar Hero Controller
    ps2x.read_gamepad();          //read controller 
   
    if(ps2x.ButtonPressed(GREEN_FRET)){
      Serial.println("Green Fret Pressed");

      digitalWrite(led,HIGH);
    }
    else{digitalWrite(led,LOW);}
    if(ps2x.ButtonPressed(RED_FRET))
      Serial.println("Red Fret Pressed");
    if(ps2x.ButtonPressed(YELLOW_FRET))
      Serial.println("Yellow Fret Pressed");
    if(ps2x.ButtonPressed(BLUE_FRET))
      Serial.println("Blue Fret Pressed");
    if(ps2x.ButtonPressed(ORANGE_FRET))
      Serial.println("Orange Fret Pressed"); 

    if(ps2x.ButtonPressed(STAR_POWER))
      Serial.println("Star Power Command");
    
    if(ps2x.Button(UP_STRUM))          //will be TRUE as long as button is pressed
      Serial.println("Up Strum");
    if(ps2x.Button(DOWN_STRUM))
      Serial.println("DOWN Strum");
 
    if(ps2x.Button(PSB_START)){         //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    }
    if(ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");
    
    if(ps2x.Button(ORANGE_FRET)) {     // print stick value IF TRUE
      Serial.print("Wammy Bar Position:");
      Serial.println(ps2x.Analog(WHAMMY_BAR), DEC); 
    } 
  }
  else { //DualShock Controller
    ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed
    
    if(ps2x.Button(PSB_START))         //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");      

    if(ps2x.Button(PSB_PAD_UP)) { 
      go();//will be TRUE as long as button is pressed
      Serial.print("Up held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
    }
    if(ps2x.Button(PSB_PAD_RIGHT)){
      right();
      Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    }
    if(ps2x.Button(PSB_PAD_LEFT)){
      left();
      Serial.print("LEFT held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    }
    if(ps2x.Button(PSB_PAD_DOWN)){
      back();
      Serial.print("DOWN held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }   
    if(ps2x.Button(PSB_PAD_UP)) { 
      if(ps2x.ButtonPressed(RED_FRET)){
       RIGHT();
      }
    }
    if(ps2x.Button(PSB_PAD_UP)) { 
      if(ps2x.ButtonPressed(ORANGE_FRET)){
       LEFT();  
      }
    }
    if(ps2x.Button(PSB_PAD_DOWN)){
      if(ps2x.ButtonPressed(RED_FRET)){
        BACKRIGHT();
      }
    }
    if(ps2x.Button(PSB_PAD_DOWN)){
      if(ps2x.ButtonPressed(ORANGE_FRET)){
        BACKLEFT();
      }
    }
    vibrate = ps2x.Analog(PSAB_CROSS);  //this will set the large motor vibrate speed based on how hard you press the blue (X) button
    if (ps2x.NewButtonState()) {        //will be TRUE if any button changes state (on to off, or off to on)
      if(ps2x.Button(PSB_L3))
        Serial.println("L3 pressed");
      if(ps2x.Button(PSB_R3))
        Serial.println("R3 pressed");
      if(ps2x.Button(PSB_L2))
        Serial.println("L2 pressed");
      if(ps2x.Button(PSB_R2))
        Serial.println("R2 pressed");
      if(ps2x.Button(PSB_TRIANGLE))
        Serial.println("Triangle pressed");        
    }

    if(ps2x.ButtonPressed(PSB_CIRCLE))               //will be TRUE if button was JUST pressed
      Serial.println("Circle just pressed");
    if(ps2x.NewButtonState(PSB_CROSS))               //will be TRUE if button was JUST pressed OR released
      Serial.println("X just changed");
    if(ps2x.ButtonReleased(PSB_SQUARE))              //will be TRUE if button was JUST released
      Serial.println("Square just released");     

    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) { //print stick values if either is TRUE
      Serial.print("Stick Values:");
      Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_LX), DEC); 
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_RY), DEC); 
      Serial.print(",");
      Serial.println(ps2x.Analog(PSS_RX), DEC); 
    }     
  }
  delay(50);  


}
void go(){
 digitalWrite( in1 , HIGH);
 digitalWrite( in3 , HIGH);
 digitalWrite( in5 , HIGH);
 digitalWrite( in7 , HIGH);
 digitalWrite( in2 , LOW );
 digitalWrite( in4 , LOW );
 digitalWrite( in6 , LOW );
 digitalWrite( in8 , LOW );
}
void back(){
 digitalWrite( in1 , LOW );
 digitalWrite( in3 , LOW );
 digitalWrite( in5 , LOW );
 digitalWrite( in7 , LOW );
 digitalWrite( in2 , HIGH);
 digitalWrite( in4 , HIGH);
 digitalWrite( in6 , HIGH);
 digitalWrite( in8 , HIGH);
}
void left(){
 digitalWrite( in1 , HIGH);
 digitalWrite( in3 , HIGH);
 digitalWrite( in5 , HIGH);
 digitalWrite( in7 , HIGH);
 digitalWrite( in2 , LOW );
 digitalWrite( in4 , LOW );
 digitalWrite( in6 , LOW );
 digitalWrite( in8 , LOW );
}
void right(){
 digitalWrite( in1 , HIGH);
 digitalWrite( in3 , HIGH);
 digitalWrite( in5 , HIGH);
 digitalWrite( in7 , HIGH);
 digitalWrite( in2 , LOW );
 digitalWrite( in4 , LOW );
 digitalWrite( in6 , LOW );
 digitalWrite( in8 , LOW );
}
void LEFT(){
 digitalWrite( in1 , HIGH);
 digitalWrite( in3 , HIGH);
 digitalWrite( in5 , HIGH);
 digitalWrite( in7 , HIGH);
 digitalWrite( in2 , LOW );
 digitalWrite( in4 , LOW );
 digitalWrite( in6 , LOW );
 digitalWrite( in8 , LOW );
}
void RIGHT(){
 digitalWrite( in1 , HIGH);
 digitalWrite( in3 , HIGH);
 digitalWrite( in5 , HIGH);
 digitalWrite( in7 , HIGH);
 digitalWrite( in2 , LOW );
 digitalWrite( in4 , LOW );
 digitalWrite( in6 , LOW );
 digitalWrite( in8 , LOW );
}
void BACKLEFT(){
 digitalWrite( in1 , HIGH);
 digitalWrite( in3 , HIGH);
 digitalWrite( in5 , HIGH);
 digitalWrite( in7 , HIGH);
 digitalWrite( in2 , LOW );
 digitalWrite( in4 , LOW );
 digitalWrite( in6 , LOW );
 digitalWrite( in8 , LOW );
}
void BACKRIGHT(){
 digitalWrite( in1 , HIGH);
 digitalWrite( in3 , HIGH);
 digitalWrite( in5 , HIGH);
 digitalWrite( in7 , HIGH);
 digitalWrite( in2 , LOW );
 digitalWrite( in4 , LOW );
 digitalWrite( in6 , LOW );
 digitalWrite( in8 , LOW );
}
