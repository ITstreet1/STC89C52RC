#include <reg52.h>
#include <intrins.h>  //use for _nop_()
#define uchar unsigned char
#define uint unsigned int

unsigned char code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,
                        0xf8,0x80,0x90};
sbit P2_3 = P2^3;
sbit P2_2 = P2^2;
sbit P2_1 = P2^1;
sbit P2_0 = P2^0;
sbit DHT11_DATA=P2^7;    //DHT11数据线 
static tempH,tempL;
	uchar for1s=0;
void Delay500us()		//@11.0592MHz
{
	unsigned char i;
	_nop_();
	i = 227;
	while (--i);
}


void Timer0Init(void)		//50毫秒@11.0592MHz
{
//	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x00;		//设置定时初值
	TH0 = 0x4C;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}

void INT0_DHT11 () interrupt 1{

	TL0 = 0x00;		//设置定时初值
	TH0 = 0x4C;		//设置定时初值
	for1s++;
	if (for1s>20){
		scanDHT11();
		for1s=0;
	}
	
}
void dprint(uchar num0,uchar num1,uchar num2,uchar num3){
//it works.
	P0=table[num0];
	P2_0=0;
	P2_0=1;
	
	P0=table[num1];
	P2_1=0;
	P2_1=1;
	
	P0=table[num2];
	P2_2=0;
	P2_2=1;
	
	P0=table[num3];
	P2_3=0;
	P2_3=1;
	
}

void scanDHT11(){
/*
1.主机拉低数据位18ms以上发送读取信号
2.延时20-40us，并将数据位设置为高电平，等待DHT11响应
3.DHT11拉低80us，此为dht11响应信号
4.DHT11拉低80us，开始发送信号
5.

*/
	
	
	
	
}
void main()
{
	EA=1;IT0=1;EX0=1;
	Timer0Init();
	while(1){
		dprint(1,2,3,4);
	}
}