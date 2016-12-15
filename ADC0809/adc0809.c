#include<reg52.h>
#include <intrins.h>  //use for _nop_()
#define UCHAR unsigned char
#define uint unsigned int
#define sint short int
#define FOSC 11059200

#define F500KHz    (65536-FOSC/4/500000)
sbit datain=P2;
sbit OE=P2^4;
sbit EOC=P2^5;

sbit START=P2^6;
sbit P2_0 = P2^0;
sbit P2_1 = P2^1;
sbit P2_3 = P2^3;
sbit P2_2 = P2^2;
sbit led2=P1^1;
sbit led3=P1^2;
sbit led4=P1^3;
float V_F;
int V;
UCHAR I_0,F_0,F_1;
sfr T2MOD = 0xc9;                   //timer2 mode register
unsigned char code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,
                        0xf8,0x80,0x90};


void dprint(UCHAR num0,UCHAR num1,UCHAR num2,UCHAR num3){
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
    T2MOD = 0x02;                   //enable timer2 output clock
    RCAP2L = TL2 = F500KHz;        //initial timer2 low byte
    RCAP2H = TH2 = F500KHz >> 8;   //initial timer2 high byte
    TR2 = 1;                        //timer2 start running
    EA = 1;                         //open global interrupt switch

while(1){
	START=0;
	START=1;
	START=0;
	led2=0;
	while(EOC==0);
	led3=0;
	OE=1;
	V_F=P3*1.96078;
	led4=P3;
	V=V_F;
	F_0=V%10;
	V=(int)V/10;
	F_1=V%10;
	V=(int)V/10;
	I_0=V%10;

	dprint(0,I_0,F_1,F_0);
	led2=1;led3=1;
	
	OE=0;
}
	
}

	
	
	
