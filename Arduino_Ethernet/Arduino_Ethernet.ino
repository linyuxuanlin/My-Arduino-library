/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 *
 * This example shows how to use Arduino Ethernet shield (W5100)
 * to connect your project to Blynk.
 * Feel free to apply it to any other example. It's simple!
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "78f8c94c46a043a6bdcc846067363501";

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth);
  // You can also specify server.
  // For more options, see BoardsAndShields/Arduino_Ethernet_Manual example
  //Blynk.begin(auth, "your_server.com", 8442);
  //Blynk.begin(auth, IPAddress(192,168,1,100), 8888);
}

void loop()
{
  Blynk.run();
}

