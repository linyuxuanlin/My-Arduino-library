#include <TN901.h>
TN901 tn;
void setup()
{
    Serial.begin(9600);
    tn.Init(7,9,8);
}

void loop()
{
   tn.Read();
   SerialValue();
   delay(200);
}

void SerialValue()
{
   Serial.print("OT: ");
   Serial.print(tn.OT, DEC);
   Serial.println(" C");
   Serial.print("ET: ");
   Serial.print(tn.ET, DEC);
   Serial.println(" C");
}

