#include "REG51.h"
#include "oled.h"
#include "bmp.h"

 int main(void)
 {	u8 t;
		OLED_Init();			//初始化OLED  
		OLED_Clear()  	; 
	
		t='&';

	while(1) 
	{		
		OLED_Clear();

		OLED_ShowCHinese(108,0,1);//技
		OLED_ShowString(6,3,"0.96' OLED TEST",16);
		OLED_ShowChar(48,6,t,16);//显示ASCII字符	   	
		delay_ms(100);

	}	  
	
}