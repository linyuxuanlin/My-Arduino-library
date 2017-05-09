int trig_pin = 4;
int echo_pin = 3;
long echotime; //in micro seconds
float distance; //in cm

void setup() {
  Serial.begin (9600);
  pinMode(trig_pin, OUTPUT); 
  pinMode(echo_pin, INPUT);
  digitalWrite(trig_pin, LOW); //Start with trigger LOW
}

void loop() {
  
  //trigger a pulse-echo measurement
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  //get the result
  echotime= pulseIn(echo_pin, HIGH);
  distance= 0.0001*((float)echotime*340.0)/2.0;
  Serial.println(distance);
  delay(100);
}
