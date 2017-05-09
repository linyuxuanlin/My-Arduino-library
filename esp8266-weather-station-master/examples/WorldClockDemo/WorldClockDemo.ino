/**The MIT License (MIT)

Copyright (c) 2015 by Daniel Eichhorn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

See more at http://blog.squix.ch
*/

#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <JsonListener.h>
#include "SSD1306.h"
#include "SSD1306Ui.h"
#include "Wire.h"
#include "WorldClockClient.h"
#include "icons.h"
#include "fonts.h"



/***************************
 * Begin Settings
 **************************/
// WIFI
const char* WIFI_SSID = "yourssid"; 
const char* WIFI_PWD = "yourpassw0rd";

// Setup
const int UPDATE_INTERVAL_SECS = 10 * 60; // Update every 10 minutes

// Display Settings
const int I2C_DISPLAY_ADDRESS = 0x3c;
const int SDA_PIN = D3;
const int SDC_PIN = D4;

// TimeClient settings


// Initialize the oled display for address 0x3c
// sda-pin=14 and sdc-pin=12
SSD1306   display(I2C_DISPLAY_ADDRESS, SDA_PIN, SDC_PIN);
SSD1306Ui ui     ( &display );

/***************************
 * End Settings
 **************************/
String timeZoneIds [] = {"America/New_York", "Europe/London", "Europe/Paris", "Australia/Sydney"};
WorldClockClient worldClockClient("de", "CH", "E, dd. MMMMM yyyy", 4, timeZoneIds);


// this array keeps function pointers to all frames
// frames are the single views that slide from right to left
bool (*frames[])(SSD1306 *display, SSD1306UiState* state, int x, int y) = { drawFrame1, drawFrame2, drawFrame3, drawFrame4};
int numberOfFrames = 4;

// flag changed in the ticker function every 10 minutes
bool readyForUpdate = false;

String lastUpdate = "--";

Ticker ticker;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  // initialize dispaly
  display.init();
  display.clear();
  display.display();

  //display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setContrast(255);

  WiFi.begin(WIFI_SSID, WIFI_PWD);
  
  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    display.clear();
    display.drawString(64, 10, "Connecting to WiFi");
    display.drawXbm(46, 30, 8, 8, counter % 3 == 0 ? ANIMATION_activeSymbole : ANIMATION_inactiveSymbole);
    display.drawXbm(60, 30, 8, 8, counter % 3 == 1 ? ANIMATION_activeSymbole : ANIMATION_inactiveSymbole);
    display.drawXbm(74, 30, 8, 8, counter % 3 == 2 ? ANIMATION_activeSymbole : ANIMATION_inactiveSymbole);
    display.display();
    
    counter++;
  }

  ui.setTargetFPS(30);

  ui.setActiveSymbole(ANIMATION_activeSymbole);
  ui.setInactiveSymbole(ANIMATION_inactiveSymbole);

  // You can change this to
  // TOP, LEFT, BOTTOM, RIGHT
  ui.setIndicatorPosition(BOTTOM);

  // Defines where the first frame is located in the bar.
  ui.setIndicatorDirection(LEFT_RIGHT);

  // You can change the transition that is used
  // SLIDE_LEFT, SLIDE_RIGHT, SLIDE_TOP, SLIDE_DOWN
  ui.setFrameAnimation(SLIDE_LEFT);

  // Add frames
  ui.setFrames(frames, numberOfFrames);

  // Inital UI takes care of initalising the display too.
  ui.init();

  Serial.println("");

  updateData(&display);

  ticker.attach(UPDATE_INTERVAL_SECS, setReadyForWeatherUpdate);

}

void loop() {

  if (readyForUpdate && ui.getUiState().frameState == FIXED) {
    updateData(&display);
  }

  int remainingTimeBudget = ui.update();

  if (remainingTimeBudget > 0) {
    // You can do some work here
    // Don't do stuff if you are below your
    // time budget.
    delay(remainingTimeBudget);
  }

}

void updateData(SSD1306 *display) {
  drawProgress(display, 50, "Updating Time...");
  worldClockClient.updateTime();
  drawProgress(display, 100, "Done...");
  readyForUpdate = false;
  delay(1000);
}

void drawProgress(SSD1306 *display, int percentage, String label) {
  display->clear();
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_10);
  display->drawString(64, 10, label);
  display->drawRect(10, 28, 108, 12);
  display->fillRect(12, 30, 104 * percentage / 100 , 9);
  display->display();
}

void drawClock(SSD1306 *display, int x, int y, int timeZoneIndex, String city, const char* icon) {
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(x + 60, y + 5, city);
  display->setFont(Crushed_Plain_36);
  display->drawXbm(x, y, 60, 60, icon); 
  display->drawString(x + 60, y + 15, worldClockClient.getHours(timeZoneIndex) + ":" + worldClockClient.getMinutes(timeZoneIndex));

}

bool drawFrame1(SSD1306 *display, SSD1306UiState* state, int x, int y) {
  drawClock(display, x, y, 0, "New York",  new_york_bits);
}

bool drawFrame2(SSD1306 *display, SSD1306UiState* state, int x, int y) {
  drawClock(display, x, y, 1, "London",  london_bits);
}

bool drawFrame3(SSD1306 *display, SSD1306UiState* state, int x, int y) {
  drawClock(display, x, y, 2, "Paris",  paris_bits);
}

bool drawFrame4(SSD1306 *display, SSD1306UiState* state, int x, int y) {
  drawClock(display, x, y, 3, "Sydney",  sydney_bits);
}


void setReadyForWeatherUpdate() {
  Serial.println("Setting readyForUpdate to true");
  readyForUpdate = true;
}


