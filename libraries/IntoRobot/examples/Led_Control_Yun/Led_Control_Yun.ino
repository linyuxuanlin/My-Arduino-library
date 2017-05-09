/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date     :  03-30-15
************************************************************************
 This application example code is in the public domain.

   control Led througt the IntoRobot Cloud

this example is writted for arduino Yun

*/
#include <Bridge.h>
#include <YunClient.h>
#include <IntoRobot.h>


//intorobot topic
#define CMD_LIGHTSWITCH "channel/smartLight_0/cmd/switch" 
#define DATA_LIGHTSTATE  "channel/smartLight_0/data/status"

const char *device_id = "your_device_id";         //device id, get from the IntoRobot Cloud
const char *access_token = "your_access_token";  //access token, get from the IntoRobot Cloud
YunClient yunClient;
IntorobotClass IntoRobot(device_id, access_token, yunClient);

#define LEDPIN  13  //the pin of led

void setup() 
{
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    
    // Bridge startup
    pinMode(LEDPIN, OUTPUT);
    digitalWrite(LEDPIN, HIGH);
    Bridge.begin();
    digitalWrite(LEDPIN, LOW);
    Serial.println("Bridge Beginned");
    
    //until the arduino connnet to the IntoRobot Cloud
    while(!IntoRobot.connected())
    {
        IntoRobot.process();
    }
    
    //subscribe the Led Control topic
    IntoRobot.subscribe(CMD_LIGHTSWITCH, NULL, LightSwitchCb);
}

void loop() 
{
    IntoRobot.process();
}

//the Led Control CallBack Function
void LightSwitchCb(uint8_t * payload, uint32_t len)
{
    if(!memcmp(payload,"1",1))
    {
        IntoRobot.publish(DATA_LIGHTSTATE, (uint8_t *)"1", 1);
        digitalWrite(LEDPIN, HIGH);// Turn ON the LED pins  
    }
    else if(!memcmp(payload,"0",1))
    {
        IntoRobot.publish(DATA_LIGHTSTATE, (uint8_t *)"0", 1);
        digitalWrite(LEDPIN, LOW);// Turn ON the LED pins  
    }

}

