
#include<reg52.h>
#include <intrins.h>  //use for _nop_()
#define uchar unsigned char
#define uint unsigned int
#define sint short int
sbit datain=P2;
sbit OE=P2^4;
sbit EOC=P2^5;

sbit START=P2^6;
sbit CLK=P2^7;
sbit P2_3 = P2^3;
sbit P2_2 = P2^2;
sbit P2_1 = P2^1;
sbit P2_0 = P2^0;
int V;
uchar I_0,F_0,F_1;
unsigned char code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,
                        0xf8,0x80,0x90};
void Timer0Init(void)		//50微秒@11.0592MHz
{
//	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x02;		//设置定时器模式
	TL0 = 0xD2;		//设置定时初值
	TH0 = 0xD2;		//设置定时重载值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}

void dprint(uchar num0,uchar num1,uchar num2,uchar num3){
//it works.
	P0=table[num0];
	P2_0=0;
	P2_0=1;
	
	P0=(table[num1]& 0x7f);
	P2_1=0;
	P2_1=1;
	
	P0=table[num2];
	P2_2=0;
	P2_2=1;
	
	P0=table[num3];
	P2_3=0;
	P2_3=1;
	
}
void main(){
	Timer0Init();
	P1=0x00;
	EA=1;
	ET0=1;
	CLK=1;
	START=1;
	EOC=1;
	OE=1;
	//START=0;
	//START=1;
	//START=0;

	while(1){
		START=0;
		START=1;
		START=0;
		while(EOC==0);
		OE=1;
		V=(int)(P1/255)*500;
		F_0=V%10;
		V=(int)V/10;
		F_1=V%10;
		V=(int)V/10;
		I_0=V%10;
		dprint(0,I_0,F_1,F_0);
		OE=0;
		
	
}}
void timer0() interrupt 1{
		CLK=~CLK;
	}
	
	
	
