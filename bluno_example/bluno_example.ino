void setup() {
    Serial.begin(9600);               //initial the Serial
}

void loop()
{
    if(Serial.available())
    {
        Serial.write(Serial.read());    //send what has been received
    }
}


