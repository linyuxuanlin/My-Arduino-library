int iValue, iTmp;
byte bVal1, bVal2, bVal3;
void setup() {
  Serial1.begin(115200);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  pinMode(28, INPUT_PULLUP);
  pinMode(29, INPUT_PULLUP);
  pinMode(30, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);
  pinMode(34, INPUT_PULLUP);
  pinMode(35, INPUT_PULLUP);
  pinMode(36, INPUT_PULLUP);
  pinMode(37, INPUT_PULLUP);
  pinMode(38, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(49, OUTPUT);
  pinMode(50, OUTPUT);
  pinMode(51, OUTPUT);
  pinMode(52, OUTPUT);
  pinMode(53, OUTPUT);
  for (iTmp = 0; iTmp < 0x100; iTmp++) {
    DGUS_SendVal(iTmp, 0);
  }
  iValue = 0;
  bVal1 = 0;
  bVal2 = 0;
  bVal3 = 0;

}

void loop()
{
  int iAnalog;
  int iTmp;

  for (iTmp = 22; iTmp < 38; iTmp++)
    InputChack(iTmp, iTmp, 0, 1);


  iAnalog = analogRead(A0); DGUS_SendVal(0x0080, iAnalog);
  delay(1);
  iAnalog = analogRead(A1); DGUS_SendVal(0x0081, iAnalog);
  delay(1);
  iAnalog = analogRead(A2); DGUS_SendVal(0x0082, iAnalog);
  delay(1);
  iAnalog = analogRead(A3); DGUS_SendVal(0x0083, iAnalog);
  delay(1);
  iAnalog = analogRead(A4); DGUS_SendVal(0x0084, iAnalog);
  delay(1);
  iAnalog = analogRead(A5); DGUS_SendVal(0x0085, iAnalog);
  delay(1);
  iAnalog = analogRead(A6); DGUS_SendVal(0x0086, iAnalog);
  delay(1);
  iAnalog = analogRead(A7); DGUS_SendVal(0x0087, iAnalog);
  delay(1);
  iAnalog = analogRead(A8); DGUS_SendVal(0x0088, iAnalog);
  delay(1);
  iAnalog = analogRead(A9); DGUS_SendVal(0x0089, iAnalog);
  delay(1);
  iAnalog = analogRead(A10); DGUS_SendVal(0x008A, iAnalog);
  delay(1);
  iAnalog = analogRead(A11); DGUS_SendVal(0x008B, iAnalog);
  delay(1);
  iAnalog = analogRead(A12); DGUS_SendVal(0x008C, iAnalog);
  delay(1);
  iAnalog = analogRead(A13); DGUS_SendVal(0x008D, iAnalog);
  delay(1);
  iAnalog = analogRead(A14); DGUS_SendVal(0x008E, iAnalog);
  delay(1);
  iAnalog = analogRead(A15); DGUS_SendVal(0x008F, iAnalog);



  serial1Event();
}


void serial1Event()
{
  int iLen;
  byte iData[255];
  int iTmp;
  int iAdr, iVal;
  if (Serial1.available() > 3)
  {
    if (Serial1.read() == 0x5A)
      if (Serial1.read() == 0xA5)
      {
        iLen = Serial1.read();
        iTmp = 0;
        while (Serial1.available() < iLen) ; //Wait for all frame !!!! Blocking procedure

        while (iTmp < iLen) //Compile all frame
        {
          iData[iTmp] = Serial1.read();
          iTmp++;
        }

        iAdr = (iData[1] << 8) + iData[2];
        iVal = (iData[4] << 8) + iData[5];

        for (iTmp = 2; iTmp < 14; iTmp++)
          if (iAdr == iTmp) analogWrite(iTmp, iVal & 0xFF); //PWM3 set at once

        for (iTmp = 38; iTmp < 53; iTmp++)
          if (iAdr == iTmp) digitalWrite(iTmp, iVal & 0xFF); //PWM3 set at once


      }
  }
}

void DGUS_Beep(byte bTime) // Beep generate bTime*10ms
{
  Serial1.write(0x5A);
  Serial1.write(0xA5);
  Serial1.write(0x03);
  Serial1.write(0x80);
  Serial1.write(0x02);
  Serial1.write(bTime);
}

void DGUS_LED_Bright(byte bVal) //Screen backlite set 0-0x40
{
  if (bVal > 0x40) bVal = 0x40;
  Serial1.write(0x5A);
  Serial1.write(0xA5);
  Serial1.write(0x03);
  Serial1.write(0x80);
  Serial1.write(0x01);
  Serial1.write(bVal);
}

void DGUS_SendVal(int iAdr, int iVal)//Send iVal for VP= iAdr to DGUS
{
  byte bAdrL, bAdrH, bValL, bValH;
  bAdrL = iAdr & 0xFF;
  bAdrH = (iAdr >> 8) & 0xFF;
  bValL = iVal & 0xFF;
  bValH = (iVal >> 8) & 0xFF;
  Serial1.write(0x5A);
  Serial1.write(0xA5);
  Serial1.write(0x05);
  Serial1.write(0x82);
  Serial1.write(bAdrH);
  Serial1.write(bAdrL);
  Serial1.write(bValH);
  Serial1.write(bValL);
}
void InputChack(int Adr, int Pin, int On, int Off)
{
  if (digitalRead(Pin) == 0) //Read digital and send to DGUS
    DGUS_SendVal(Adr, Off);
  else
    DGUS_SendVal(Adr, On);
}

