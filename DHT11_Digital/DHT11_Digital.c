#include <reg52.h>
#include <intrins.h>  //use for _nop_()
#define uchar unsigned char
#define uint unsigned int
#define sint short int

unsigned char code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,
                        0xf8,0x80,0x90};
sbit P2_3 = P2^3;
sbit P2_2 = P2^2;
sbit P2_1 = P2^1;
sbit P2_0 = P2^0;
sbit DHT11_DATA=P2^7;    //DHT11数据线 
static int RH_H,RH_L,Temp_H,Temp_L,checksum;
//湿度整数位、小数位，温度整数位、小数位，校验和。
static sint RH_I1,RH_F1,T_I1,T_F1;
static sint RH_I0,RH_F0,T_I0,T_F0;
static uchar for1s=0;//顾名思义，为了一秒延时而设的变量
void scanDHT11();
sint recivedata();
void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	i = 2;
	while (--i);
}

void Delay20ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 36;
	j = 217;
	do
	{
		while (--j);
	} while (--i);
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
	//1.主机拉低数据位18ms以上发送读取信号
	
DHT11_DATA=0;
Delay20ms();
DHT11_DATA=1;
//2.延时20-40us，等待DHT11响应
Delay10us();
Delay10us();
Delay10us();
Delay10us();
Delay10us();
Delay10us();
//数据位被拉低则说明DHT11响应
if (DHT11_DATA == 0){
	//等到数据位再次被拉高
	while(DHT11_DATA==0);
	//等待拉低准备接收数据
	while(DHT11_DATA==1);
	//开始接收数据
	RH_H=recivedata();
	RH_L=recivedata();
	Temp_H=recivedata();
	Temp_L=recivedata();
	checksum=recivedata();
	RH_I1=(RH_H/10);
	RH_I0=(RH_H%10);
	RH_F1=(RH_L/10);
	RH_F0=(RH_L%10);
	T_I1=(Temp_H/10);
	T_I0=(Temp_H%10);
	T_F1=(Temp_L/10);
	T_F0=(Temp_L%10);
	
} 
}


sint recivedata(){
	uchar i;
	sint data_t;
	char bits;
	bits=0;
	for(i=0;i<8;i++){
		while(DHT11_DATA);//等待数据线拉高
		Delay10us();
		Delay10us();
		Delay10us();
		Delay10us();
		Delay10us();
		Delay10us();
		bits<<=1;
		data_t=DHT11_DATA;
		bits +=data_t;
}
return bits;
	
}
void main()
{
	EA=1;IT0=1;EX0=1;
	Timer0Init();
	while(1){
		dprint(T_I1,T_I0,T_F1,T_F0);
	}
}