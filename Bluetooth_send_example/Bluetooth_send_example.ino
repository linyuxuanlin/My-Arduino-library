int i=0;
String inString = "";
String LED = "";
String LEDabc = "";
void setup() {
  Serial.begin(9600);
}
void loop() {
while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {inString += (char)inChar;}
    else {LED +=(char)inChar;}
    if (inChar == '\n') {
      i=inString.toInt();
      LEDabc=LED;
      inString = "";
      LED= ""; 
    }
  }
   if (LEDabc=="A\n"){
   analogWrite(3,i);
 }
   if (LEDabc=="B\n"){
   analogWrite(5,i);
 }
   if (LEDabc=="C\n"){
   analogWrite(6,i);
 }
}
