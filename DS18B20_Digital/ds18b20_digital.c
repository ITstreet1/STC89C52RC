#include<reg52.h>
#include <intrins.h>  //use for _nop_()
#define uchar unsigned char
#define uint unsigned int
#define sint short int
sbit led0=P1^0;
sbit led1=P1^1;
sbit led2=P1^2;
sbit led3=P1^3;
sbit led4=P1^4;
sbit led5=P1^5;
sbit led6=P1^6;
sbit led7=P1^7;

sbit P2_3 = P2^3;
sbit P2_2 = P2^2;
sbit P2_1 = P2^1;
sbit P2_0 = P2^0;
uchar I_1,I_0,F_1,F_0;
unsigned char code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,
                        0xf8,0x80,0x90,0xff,0xbf};
sbit DQ=P2^6; //数据传输线接单片机的相应的引脚 
unsigned char tempL=0; //设全局变量
unsigned char tempH=0; 
unsigned int sdata;//测量到的温度的整数部分
unsigned char xiaoshu1;//小数第一位
unsigned char xiaoshu2;//小数第二位
unsigned char xiaoshu;//两位小数
char  fg=1;        //温度正负标志





//延时时间是time=i*8+10us

void delay(unsigned char i)
{
 for(i;i>0;i--);
}


//***********************************************************

//                     延时子程序

//************************************************************
void delay1ms()
{
 unsigned char i;
 for(i=124;i>0;i--);  //延时124*8+10=1002us
}



//*****************************初始化程序 *********************************//

void Init_DS18B20(void) 
{

 DQ=1; //DQ先置高 
 delay(8); //稍延时
 DQ=0; //发送复位脉冲 
 delay(80); //延时（>480us) 
 DQ=1; //拉高数据线 
 delay(5); //等待（15~60us)
 delay(20); 
} 


//**********读一个字节************//

ReadOneChar(void)  
{
unsigned char i=0; 
unsigned char dat=0; 
for (i=8;i>0;i--) //一个字节有8位 
{
 DQ=1; 
 delay(1); 
 DQ=0;
 dat>>=1; 
 DQ=1; 
 if(DQ) 
 dat|=0x80; 
 delay(4);
} 
return(dat);
} 



//*********************** **写一个字节**************************//

void WriteOneChar(unsigned char dat) 
{ 
  unsigned char i=0; 
  for(i=8;i>0;i--) 
  {
   DQ=0;
   DQ=dat&0x01; 
   delay(5); 
   DQ=1; 
   dat>>=1;
  } 
  delay(4);
} 


//读温度值（低位放tempL;高位放tempH;）
void ReadTemperature(void) 
{ 
 Init_DS18B20(); //初始化
 WriteOneChar(0xcc); //跳过读序列号的操作
 WriteOneChar(0x44); //启动温度转换
 delay(125); 
 Init_DS18B20(); 
 WriteOneChar(0xcc); //跳过读序列号的操作 
 WriteOneChar(0xbe);  
 tempL=ReadOneChar(); 
 tempH=ReadOneChar(); 
  
		if(tempH>0x7f)      //最高位为1时温度是负
		{
		 tempL=~tempL;         //补码转换，取反加一
		 tempH=~tempH+1;       
		 fg=1;      
       }else fg=0;
		sdata = tempL/16+tempH*16;      //整数部分
		xiaoshu1 = (tempL&0x0f)*10/16; //小数第一位
		xiaoshu2 = (tempL&0x0f)*100/16%10;//小数第二位
		//xiaoshu=xiaoshu1*10+xiaoshu2; //小数两位
		I_0=sdata%10;
		I_1=sdata/10;
		F_1=xiaoshu1;
		}
void dprint(uchar num0,uchar num1,uchar num2,uchar num3){
//it works.
	P0=table[num0];
	P2_0=0;
	delay1ms();
	P2_0=1;
	
	P0=table[num1];
	P2_1=0;
	delay1ms();
	P2_1=1;
	
	P0=(table[num2]& 0x7f);
	P2_2=0;
	delay1ms();
	P2_2=1;
	
	P0=table[num3];
	P2_3=0;
	delay1ms();
	P2_3=1;
	
}

void main(){
	
	
	while(1){
		ReadTemperature();
		led0=I_1;
		led1=I_0;
		led2=F_1;
		led3=tempH;
		led4=tempL;

		dprint(fg+10,I_1,I_0,F_1);
		//Delay500us();
		
	}
	
	
}