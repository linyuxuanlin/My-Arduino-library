int led1=3;
int led2=4;
int tonepin=5;
void setup() {
  // put your setup code here, to run once:
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(tonepin,OUTPUT);
digitalWrite(led1,HIGH);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
int a=analogRead(A0);
//Serial.println(a);
/*
if(a>=130&&a<=230)
{pinMode(led2,LOW);
tone(tonepin,1000);
pinMode(led1,HIGH);
delay(400);
pinMode(led1,HIGH);
delay(400);
}
*/
if(a>150)
{
  digitalWrite(tonepin,LOW);
  
  digitalWrite(led1,HIGH);
  
  
}
else{
  digitalWrite(tonepin,HIGH);
  digitalWrite(led1,LOW);
  
  }
  delay(100);
}

