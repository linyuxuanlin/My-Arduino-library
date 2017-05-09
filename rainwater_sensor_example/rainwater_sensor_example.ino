void setup() {
  pinMode(2,INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(digitalRead(2));
  delay(500);
} 

//无水 1
//有水 0
