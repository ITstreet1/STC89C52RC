
#include<reg52.h>
#include <intrins.h>  //use for _nop_()
#define uchar unsigned char
#define uint unsigned int
#define sint short int

sbit DT=2^6;
sbit P2_3 = P2^3;
sbit P2_2 = P2^2;
sbit P2_1 = P2^1;
sbit P2_0 = P2^0;
unsigned char code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,
                        0xf8,0x80,0x90};
			
uchar tempH,tempL;
uchar I_1,I_0,F_1,F_0;
bit fg=1;			
void Delay15us()		//@11.0592MHz
{
	unsigned char i;

	i = 4;
	while (--i);
}
void Delay500us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
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
void DSInit(){
	DT=1;
	delay15us();
	DT=0;
	delay500us();
	DQ=1;
	delay15us();
	delay15us();
	
	
}
void sendchar(uchar char_){
	
	
	
}
uchar readdata(){
	
	
	
	
}
void main(){
	
	
	while(1){
		void DSInit();
		if(DQ==0){ //若响应
			//发送跳过rom搜索的命令
			sendchar(0xcc);
			//启动温度转换
			sendchar(0x44);
			DSInit();
			sendchar(0xcc);
			//发送读取命令
			sendchar(0xbe);
			//开始接收
			tempH =readdata();
			tempL = readdata();
			//开始转换数据
			fg=
			if ()
			
		}
		
		
		
	}
	
	
}