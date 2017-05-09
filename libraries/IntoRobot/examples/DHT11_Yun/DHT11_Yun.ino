/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date     :  03-30-15
************************************************************************
 This application example code is in the public domain.

   read temperature and humidity , send to the IntoRobot Cloud

this example is writted for arduino Yun

*/
#include <Bridge.h>
#include <YunClient.h>
#include <IntoRobot.h>
#include "DHT.h"

//intorobot topic
#define DATA_TMMPERATURE "channel/humiture_0/data/temperature"
#define DATA_HUMIDITY  "channel/humiture_0/data/humidity"

const char *device_id = "your_device_id";         //device id, get from the IntoRobot Cloud
const char *access_token = "your_access_token";  //access token, get from the IntoRobot Cloud
YunClient yunClient;
IntorobotClass IntoRobot(device_id, access_token, yunClient);

#define DHTPIN 2        // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 
DHT dht(DHTPIN, DHTTYPE);

long starttime;
int postInterval = 5 * 1000;

void setup()
{
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    //dht begin
    dht.begin();
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
}

void loop()
{
    char tmp[16];

    IntoRobot.process();
    if ((millis() - starttime) > postInterval)
    {
        starttime = millis();
        float t = dht.readTemperature();
        float h = dht.readHumidity();
        memset(tmp, 0, sizeof(tmp)); // temperature
        dtostrf(t, 4, 2, tmp);
        IntoRobot.publish(DATA_TMMPERATURE, (uint8_t *)tmp, strlen(tmp));
        memset(tmp, 0, sizeof(tmp)); // humidity
        dtostrf(h, 4, 2, tmp);
        IntoRobot.publish(DATA_HUMIDITY, (uint8_t *)tmp, strlen(tmp));
    }
}


