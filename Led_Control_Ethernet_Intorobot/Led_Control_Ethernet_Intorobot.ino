

/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date     :  03-30-15
************************************************************************
 This application example code is in the public domain.

   control Led througt the IntoRobot Cloud

this example is writted for arduino with Ethernet shield

*/
#include <SPI.h>
#include <Ethernet.h>
#include <IntoRobot.h>


// Update these with values suitable for your network.
byte mac[] = {  0x1A, 0xFE, 0x34, 0xDA, 0xBA, 0x0B };

//intorobot topic
#define CMD_LIGHTSWITCH "channel/smartLight_0/cmd/switch" 
#define DATA_LIGHTSTATE  "channel/smartLight_0/data/status"

const char *device_id = "111001000000000000000641";         //device id, get from the IntoRobot Cloud
const char *access_token = "36080c370503bc47b92474ab6eb4c80d";  //access token, get from the IntoRobot Cloud
EthernetClient ethClient;
IntorobotClass IntoRobot(device_id, access_token, ethClient);

#define LEDPIN  7  //the pin of led

void setup() 
{
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    
    // start the Ethernet connection:
    if (Ethernet.begin(mac) == 0) 
    {
        //Serial.println("Failed to configure Ethernet using DHCP");
        while(1);
    }
    Serial.println("ethernet connected...");

    //until the arduino connnet to the IntoRobot Cloud
    while(!IntoRobot.connected())
    {
        IntoRobot.process();
    }
    pinMode(LEDPIN, OUTPUT);  
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

