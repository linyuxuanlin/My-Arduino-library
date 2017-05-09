int led = 13;
void setup() {
  pinMode(led,OUTPUT);
digitalWrite(led,LOW);

Serial.begin(9600);
}

void loop() {
  if(Serial.available())
{ char i = Serial.read();
if(i=='A')
{
Serial.print("A");
digitalWrite(led,HIGH);
}
} 
Serial.print("wuliejian\n");
delay(2000);
}
