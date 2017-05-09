/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date     :  03-30-15
************************************************************************
 This application example code is in the public domain.

   control servo througt the IntoRobot Cloud

this example is writted for arduino Yun

*/
#include <Bridge.h>
#include <YunClient.h>
#include <IntoRobot.h>
#include <Servo.h> 

//intorobot topic
#define CMD_SERVO_ANGLE "channel/servo_0/cmd/angle"
#define DATA_SERVO_STATUS  "channel/servo_0/data/status"

const char *device_id = "your_device_id";         //device id, get from the IntoRobot Cloud
const char *access_token = "your_access_token";  //access token, get from the IntoRobot Cloud
YunClient yunClient;
IntorobotClass IntoRobot(device_id, access_token, yunClient);

Servo myservo;  // create servo object to control a servo 

void setup()
{
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    // Bridge startup
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    Bridge.begin();
    digitalWrite(13, LOW);
    Serial.println("Bridge Beginned");
    //until the arduino connnet to the IntoRobot Cloud
    while (!IntoRobot.connected())
    {
        IntoRobot.process();
    }

    // attaches the servo on pin 9 to the servo object 
    myservo.attach(9);  
    //subscribe the Servo Control topic
    IntoRobot.subscribe(CMD_SERVO_ANGLE, NULL, ServoAngleControlCb);
}

void loop()
{
    IntoRobot.process();
}

//the servo CallBack Function
void ServoAngleControlCb(uint8_t * payload, uint32_t len)
{
    String tmp="";
    
    for(int n=0; n<len; n++)
    {tmp+=(char)payload[n];}
    
    int pos = atoi(tmp.c_str());
    if( (pos>=0) && (pos<=180) )
    {
        myservo.write(pos);
        IntoRobot.publish(DATA_SERVO_STATUS, (uint8_t *)"1", 1);
    }
}


