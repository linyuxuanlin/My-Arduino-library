char BluetoothData; // the Bluetooth data received 

void setup() {

  Serial.begin(9600);
  

  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  

  digitalWrite(6,0);
  digitalWrite(7,0);

}

void loop() {

  if (Serial.available()){
  
    BluetoothData=Serial.read(); //Get next character from bluetooth
  
    if(BluetoothData=='W'){ // Red Button Pressed
      digitalWrite(7,1); //Turn digital out 4 to High
      digitalWrite(6,1); //Turn digital out 5 to Low

      if(BluetoothData=='A'){
       digitalWrite(7,0); 
       digitalWrite(6,1);
      }
    }
    if(BluetoothData=='S'){ // Yellow Button Pressed
    digitalWrite(7,0);
    digitalWrite(6,0);

    if(BluetoothData=='D'){
       digitalWrite(7,1); 
       digitalWrite(6,0);
      }
    }
    if(BluetoothData=='w'||BluetoothData=='s'||BluetoothData=='a'||BluetoothData=='d'){ // Red or Yellow Button Released
      digitalWrite(4,0);
      digitalWrite(5,0);
    }
    
  }
  
  delay(10);// wait 10 ms

}
