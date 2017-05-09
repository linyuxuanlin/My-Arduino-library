String colors[]={"R0G0B0","R0G150B0"}; //App Light colours for LOW and HIGH
String receive_chars="abcdefghijkl"; //so app knows which data goes where
int interval=100; //Gives the serial link and app a chance to process data
float voltage; //Assumes 0-1023 range over 5V

void setup() {
 //Initiate Digital pins as Inputs
  for(int i=2;i<=13;i++) pinMode(i, INPUT); 
 
 //Initiate Serial for Bluetooth Communication
  Serial.begin(9600); 
}

void loop() {
  
  //Read Digital Pins and Send results over Bluetooth
    for(int i=2;i<=13;i++){
      Serial.print("*"+String(receive_chars.charAt(i-2))+colors[digitalRead(i)]+"*");
    }

  //Graph - Read Analogue Pins and Send Results over Bluetooth
    Serial.print("*G"); //using 'G' as receive char for graph in app
    for(int i=0;i<=5;i++){
      voltage=analogRead(i)*0.0048828;
      Serial.print(String(voltage)+",");
    }
    Serial.print("*");
    
  //Pause before taking next measurement
    delay(10); 
}
