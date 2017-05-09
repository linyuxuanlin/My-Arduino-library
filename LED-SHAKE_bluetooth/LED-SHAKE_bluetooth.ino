String str="keuwl persistence of vision demo"; //string to display via persistance of vision
int pos=0; //current position in str
unsigned long data; // data describing first half of current character
unsigned long data2; // data describing second half of current character
char BluetoothData; // the data received from bluetooth serial link
int interval=5;// interval between columns in ms - determine speed of effect

//Conversion table (each value represents half of a 8x8 grid character)
unsigned long data_table[]={0,0,3755933696,0,459520,198400,337605648,268156,1241467174,50,135406914,2183716,1497709056,21025,197632,0, // !"#$%&'
  1094582272,0,1044447232,0,2132025856,8724,1040713728,2056,1621098496,0,134742016,2056,1616904192,0,204521472,3, //()*+,-./
  1094795582,62,1082081792,0,1230070082,70,1229537570,54,2131891224,16,1229539599,49,1229539646,48,225509633,3, //01234567
  1229539638,54,1229539590,62,909508608,0,1991639040,0,571738112,65,336860160,5140,337789184,8,162595074,6, //89:;<=>?
  2778284604,1010973093,151587198,126,1229539711,54,1094795582,34,1631666559,62,1095321983,65,17369471,1,1364279614,50, //@ABCDEFG
  134744191,127,8323072,0,20922689,1,571738239,65,1077952639,64,67240319,8323330,538706559,127,1094795582,15937, //HIJKLMNO
  151587199,6,1363231038,16446,151587199,118,1229539622,50,25100545,1,1077952575,63,541073439,31,1044398143,4145216, //PQRSTUVW
  135537217,4268564,2013528577,66052,1230070081,4277061,2180972544,0,806093568,192,4286644224,0,16909312,1026,2155905152,32896, //XYZ[\]^_
  67240192,0,1414812704,120,810043518,0,675562552,0,1212696624,126,1414812728,24,175900672,0,2762253336,120, //'abcdefg
  1879574654,0,4209152,0,8028160,0,1143476350,0,1077952000,0,2013529212,7865348,2013529212,0,1145324600, //hijklmno
  56,405021948,0,4262597132,128,67372156,8,609506376,0,1078476288,0,1077952572,124,541073436,28,943734844,3948608, //pqrstuvw
  672147524,68,2694881308,124,1280599108,68,1094060032,0,8323072,0,910229504,8}; //xyz{|}


void setup() {

  //接线:LED:5~12
  
  for(int i=5;i<=12;i++) pinMode(i, OUTPUT);

  //initialise serial communication
  Serial.begin(9600);

}

void loop() {

  //See if any data on bluetooth serial link, if so update string or speed
  if (Serial.available()){
    BluetoothData=Serial.read(); //Get next character from bluetooth
    if (BluetoothData=='~') interval=Serial.parseInt(); //Update interval with integer value after '~'
    if (BluetoothData>31&&BluetoothData<126){
      str=""; //clear previous string
      pos=0;
      while (BluetoothData!=13&&BluetoothData!=10){ //Sting terminated on <LF> or <CR>
        BluetoothData=Serial.read(); //Get next character from bluetooth
        if (BluetoothData>31&&BluetoothData<126) str+=BluetoothData;  //add character to string   
      }
      if (str.length()<1)str=" "; //make sure something in string
    }
  }

  //get data for current character 
  data=data_table[(int(str.charAt(pos))-32)*2]; //Left half of character
  data2=data_table[(int(str.charAt(pos))-32)*2+1]; //Right half of character
  
  //loop through and display character columns one at a time
  for (int j=0;j<32;j=j+8){
    for (int i=0;i<=8;i++) digitalWrite(5+i, bitRead(data,j+i));
    delay(interval); //delay between columns
  }
  for (int j=0;j<32;j=j+8){
    for (int i=0;i<=8;i++) digitalWrite(5+i, bitRead(data2,j+i));
    delay(interval);
  }
  
  //point to next charcater
  pos++;  if (pos>=str.length()) pos=0;
  
}
