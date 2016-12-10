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
sbit DT=P2^6;
sbit P2_3 = P2^3;
sbit P2_2 = P2^2;
sbit P2_1 = P2^1;
sbit P2_0 = P2^0;
unsigned char code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,
                        0xf8,0x80,0x90,0xff,0xbf};
			
uchar tempH,tempL;
uchar I_1,I_0,F_1,F_0;
uchar fg=0;	/*		
void Delay15us();
void Delay50us();
void Delay500us();
void dprint(uchar num0,uchar num1,uchar num2,uchar num3);
void DSInit();
void sendchar(uchar char_);
uchar readdata();*/
void delay(unsigned char i)
{
 for(i;i>0;i--);
}
void Delay15us()		//@11.0592MHz
{
	unsigned char i;

	i = 4;
	while (--i);
}
void Delay50us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 20;
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
	
	P0=table[num1];
	P2_1=0;
	P2_1=1;
	
	P0=(table[num2]& 0x7f);
	P2_2=0;
	P2_2=1;
	
	P0=table[num3];
	P2_3=0;
	P2_3=1;
	
}
void DSInit(){
	DT=1;
	delay(8);
	DT=0;
	delay(70);
	DT=1;
	delay(5);
	led5=0;
	delay(5);
}
void sendchar(uchar char_){
	unsigned char i=0; //数据线从高电平拉至低电平，产生写起始信号。15us之内将所需写的位送到数据线上，
  for(i=8;i>0;i--) 
  {
   DT=0; 
   DT=char_&0x01; 
   delay(5);
   DT=1;
   char_>>=1;
	} 
	delay(4);

}
uchar readdata(){
	unsigned char i=0; //每个读周期最短的持续时间为60us，各个读周期之间必须有1us以上的高电平恢复期
	unsigned char data_in=0; 
	for (i=8;i>0;i--) {
	DT=1; 
	delay(1); 
	DT=0;
	data_in>>=1; 
	DT=1; 
	if(DT==1) 
	data_in|=0x80; 
	delay(4);

	} 
	return(data_in);
}
void main(){
	
	
	while(1){
		 DSInit();
		if(DT==0){ //若响应
		led6=0;
			//发送跳过rom搜索的命令
			sendchar(0xcc);
			//启动温度转换
			sendchar(0x44);
			delay(125);
			DSInit();
			sendchar(0xcc);
			//发送读取命令
			sendchar(0xbe);
			//开始接收
			tempH =readdata();
			tempL =readdata();
			//开始转换数据
			//fg=tempH>>7;
			if (tempH>0x7f){
				led7=0;
				tempH=~tempH;
				tempL=~tempL;
				tempH++;
				fg=1;
			}else fg=0;
			I_1=(tempL/16+tempH*16)/10;
			I_0=(tempL/16+tempH*16)%10;	
			F_1= (tempL&0x0f)*10/16; //小数第一位
		}
		led0=I_1;
		led1=I_0;
		led2=F_1;
		led3=tempH;
		led4=tempL;
		led6=1;led7=1;
		dprint(fg+10,I_1,I_0,F_1);
		//Delay500us();
		
	}
	
	
}