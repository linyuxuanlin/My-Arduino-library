#define C0  -1
#define C 262  
#define D 294  
#define E 330  
#define F 349  
#define G 392  
#define A 440  
#define B 494  
#define CP 523  
#define DP 587  
#define EP 659  
#define FP 698  
#define GP 784  
#define AP 880  
#define BP 988
int length;   
int scale[]={

  
  
  G,A,B,CP,B,CP,G,A,A,
  G,F,E,E,E,G,D,
  G,A,B,CP,B,CP,G,A,A,
  A,A,G,CP,CP,CP,DP,
  G,A,B,CP,B,CP,EP,AP,GP,FP,EP,EP,DP,C0, 
  A,B,CP,CP,CP,DP,CP,C0,CP,B,CP,DP,DP,CP,B,CP,
  
};        //生日歌曲谱
float durt[]=
{
  
  2,2,2,2,1,2,1,2,2+2,
  2,2,2,2,2,1,2+1,
  2,2,2,2,1,2,1,2,2+2,
  2,2,2,2,2,1,1+2,
  2,2,2,2,1,2,3,3,3,2,2+2,2,4,2,
  2,2,3,1,2,1,2,1,1,2,2,3,1,2,1,4,
  
};                                                        //音长
int tonepin=6;   //用8号引脚
void setup()
{
  pinMode(tonepin,OUTPUT);
  length=sizeof(scale)/sizeof(scale[0]);   //计算长度
}
void loop()
{
   //tone(tonepin,300);
  /*
  for(int i =300;i<900;i+=100){
  
   tone(tonepin,i);
   delay(100);
   
  }
  */
  
  
  for(int x=0;x<length;x++)
  {
    tone(tonepin,scale[x]);
    delay(500*durt[x]/2);   //这里用来根据节拍调节延时，500这个指数可以自己调整
    noTone(tonepin);
  }
  delay(2000);
  
}
