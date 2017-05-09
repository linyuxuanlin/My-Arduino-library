const byte A = 2; 
const byte B = 3;
const byte C = 4;
const byte D = 5;
const byte E = 6;
const byte F = 7;
const byte O = 8;
const byte X = 0;
const byte Y = 1;
void setup() { 
Serial.begin(9600); 
pinMode(B, INPUT); 
digitalWrite(B, HIGH); 
pinMode(A, INPUT); 
digitalWrite(A, HIGH); 
pinMode(C, INPUT); 
digitalWrite(C, HIGH); 
pinMode(D, INPUT); 
digitalWrite(D, HIGH); 
pinMode(E, INPUT); 
digitalWrite(E, HIGH); 
pinMode(F, INPUT); 
digitalWrite(F, HIGH); 
pinMode(O, INPUT); 
digitalWrite(O, HIGH); }

void loop() { 
  
Serial.print("A:"); 
Serial.print(digitalRead(A)); 
Serial.print(" "); 
Serial.print("B:"); 
Serial.print(digitalRead(B)); 
Serial.print(" "); 
Serial.print("C:"); 
Serial.print(digitalRead(C)); 
Serial.print(" "); 
Serial.print("D:");
Serial.print(digitalRead(D)); 
Serial.print(" "); 
Serial.print("E:"); 
Serial.print(digitalRead(E));
Serial.print(" "); 
Serial.print("F:"); 
Serial.print(digitalRead(F));  
Serial.print(" ");
Serial.print("O:"); 
Serial.print(digitalRead(O)); 
Serial.print(" ");  
Serial.print("X:"); 
Serial.print(analogRead(X)); 
Serial.print(" "); 
Serial.print("Y:"); 
Serial.print(analogRead(Y)); 
Serial.print(" "); 
Serial.println(); 
delay(100);}
