/*
PWM LED呼吸灯
16/11/30
抛弃原来错误的方法
采用定时器中断
*/
/*中断号 0,2为外部中断 1,3为定时器中断 4为串口中断 
即：
0	INT0
1	T0
2	INT1
3	T1
4	serial 

TCON:D7-D0			D3
	TF1 TR1 TF0	TR0	IE1	IT1	IE0	IT0
IE	:D7-D0			
	EA			ES	ET1	EX1	ET0	EX0
TMOD:D7-D0
	GATE	C/T M1	M0|	GATE	C/T	M1	M0
			T1		  |			T0

*/
#define uint unsigned int
#define uchar unsigned char
#include<reg52.h>
sbit led0=P1^0;
sbit led1=P1^1;
sbit led2=P1^2;
sbit led3=P1^3;
sbit led4=P1^4;
sbit led5=P1^5;
sbit led6=P1^6;
sbit led7=P1^7;
static count=0;
static count_CB=0;
static time_PWM=0;
void Timer0Init(void)		//5微秒@11.0592MHz
{
	//AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xFB;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}
void delay(uint sec){
	
	while(sec--);

}

void timer0() interrupt 1{
	
	//因为定时器在溢出后寄存器中的初值寄存器自动归零，
	//所以需要重新赋值才能有想要的延时	
	TL0 = 0xFB;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
		count++;
		count_CB++;
	if (count==time_PWM ){
		P1=~P1;}
	if (count==500){
		P1=~P1;
		count=0;
	}
	if(count_CB == 25)//如果过了25*20us则改变亮度
	{
		count_CB = 0;
		time_PWM ++;
	}
	if (time_PWM == 499){
		time_PWM=1;

	}
}


void main()
{
	
	Timer0Init();
	//初始化定时器
	EA=1;
	//允许中中断
	ET0=1;
	//允许定时器中断
	led0=0;
	led2=0;
	led4=0;led6=0;
	while(1);
	
	
}