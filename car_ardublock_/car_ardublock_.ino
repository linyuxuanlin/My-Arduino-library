void setup()
{
	Serial.begin(9600);
	pinMode( 30 , OUTPUT);
	pinMode( 31 , OUTPUT);
	pinMode( 32 , OUTPUT);
	pinMode( 33 , OUTPUT);
	pinMode( 34 , OUTPUT);
	pinMode( 35 , OUTPUT);
	pinMode( 36 , OUTPUT);
	pinMode( 37 , OUTPUT);
  
}

void loop()
{
  char val = Serial.read();
  if (-1 != val) {
  if ('W' == val){
	
		digitalWrite( 30 , LOW );
		digitalWrite( 31 , HIGH );
		digitalWrite( 32 , HIGH );
		digitalWrite( 33 , LOW );
		digitalWrite( 34 , LOW );
		digitalWrite( 35 , HIGH );
		digitalWrite( 36 , HIGH );
		digitalWrite( 37 , LOW );
	}



   if ('S' == val){
 
    digitalWrite( 30 , HIGH );
    digitalWrite( 31 , LOW );
    digitalWrite( 32 , LOW );
    digitalWrite( 33 , HIGH );
    digitalWrite( 34 , HIGH );
    digitalWrite( 35 , LOW );
    digitalWrite( 36 , LOW );
    digitalWrite( 37 , HIGH );
  }



    if ('A' == val){
  
    digitalWrite( 30 , HIGH );
    digitalWrite( 31 , LOW );
    digitalWrite( 32 , LOW );
    digitalWrite( 33 , HIGH );
    digitalWrite( 34 , LOW );
    digitalWrite( 35 , HIGH );
    digitalWrite( 36 , HIGH );
    digitalWrite( 37 , LOW );
  }


  
    if ('D' == val){
  
    digitalWrite( 30 , LOW );
    digitalWrite( 31 , HIGH );
    digitalWrite( 32 , HIGH );
    digitalWrite( 33 , LOW );
    digitalWrite( 34 , HIGH );
    digitalWrite( 35 , LOW );
    digitalWrite( 36 , LOW );
    digitalWrite( 37 , HIGH );
  }


     if ('F' == val){
 
    digitalWrite( 30 , LOW );
    digitalWrite( 31 , LOW );
    digitalWrite( 32 , LOW );
    digitalWrite( 33 , LOW );
    digitalWrite( 34 , LOW );
    digitalWrite( 35 , LOW );
    digitalWrite( 36 , LOW );
    digitalWrite( 37 , LOW );
  }

  }
}



