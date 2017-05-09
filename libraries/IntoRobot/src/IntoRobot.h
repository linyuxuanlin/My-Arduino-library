/**
 ******************************************************************************
 * @file     : intorobot.h
 * @author   : robin
 * @version  : V1.0.0
 * @date     : 6-December-2014
 * @brief    :    
 ******************************************************************************
  Copyright (c) 2013-2014 IntoRobot Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
 */
#ifndef   INTOROBOT_H_
#define   INTOROBOT_H_

#include "MqttClient.h"
#define INTOROBOT_DEBUG

typedef void (*CB)(uint8_t*, uint32_t);

extern volatile uint8_t INTOROBOT_CLOUD_CONNECT;
extern volatile uint8_t INTOROBOT_CLOUD_CONNECTED;

#define MAX_CALLBACK_NUM    10

struct _callbacknode
{
    void (*callback)(uint8_t*, uint32_t);
    uint8_t qos;
    const char *topic;
    const char *device_id;
};

struct _callbacklist
{
    struct _callbacknode callbacknode[MAX_CALLBACK_NUM];
    int total_callbacks;
};

class IntorobotClass
{
    private: 
        MqttClientClass ApiMqttClient;

        void fill_mqtt_topic(String &fulltopic, const char *topic, const char *device_id);
        void resubscribe(void);

    public:
        IntorobotClass(const char *device_id, const char *access_token, Client& mqttclient);
        bool connected(void);
        void connect(void);
        void disconnect(void);
        uint8_t publish(const char *topic, char *payload);
        uint8_t publish(const char* topic, uint8_t* payload, unsigned int plength);
        uint8_t publish(const char* topic, uint8_t* payload, unsigned int plength, uint8_t retained);
        uint8_t publish(const char* topic, uint8_t* payload, unsigned int plength, uint8_t qos, uint8_t retained);
        uint8_t subscribe(const char* topic, const char *device_id, void (*callback)(uint8_t*, uint32_t));
        uint8_t subscribe(const char* topic, const char *device_id, void (*callback)(uint8_t*, uint32_t), uint8_t qos);
        uint8_t unsubscribe(const char *topic, const char *device_id);
        int deviceInfo(char *product_id, char *device_id, char *access_token);
        void process(void);
};
	
#ifdef __cplusplus
extern "C" {
#endif

//subscribe topic info
CB getsubcallback(char * fulltopic);
void addsubcallback(char *topic, char *device_id, void (*callback)(uint8_t*, uint32_t), uint8_t qos);
void delsubcallback(char * topic, char *device_id);
void ApiMqttClientCallBack(char *topic, uint8_t *payload, uint32_t length);

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /*INTOROBOT_H_*/

