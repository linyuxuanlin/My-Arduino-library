//master:recieve
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  Serial.println ("setup...");
}

void loop() {
  while (mySerial.available() ) {
    byte c = mySerial.read();
    Serial.write(c);
    delay(10);
  }
}

