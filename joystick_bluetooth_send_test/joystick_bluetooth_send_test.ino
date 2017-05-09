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
digitalWrite(O, HIGH); 
 
}

void loop() {
 if(digitalRead(A)==LOW){
  Serial.println("A"); 
 }else{Serial.print(" ");}
 if(digitalRead(B)==LOW){
  Serial.println("B"); 
 }
 if(digitalRead(C)==LOW){
  Serial.println("C"); 
 }
 if(digitalRead(D)==LOW){
  Serial.println("D"); 
 }
}
