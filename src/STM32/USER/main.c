#include <stdio.h>
#include <stdlib.h>

#include "sys.h"
#include "tim.h"
#include "usart.h"
#include "delay.h"
#include "gpio.h"

#include "IIC_OLED.h"


void oled_display(u8g2_t * u8g2)
{
	u8g2_DrawStr(u8g2,0,20,"Hello");
}


int main(void)
{
	u8g2_t u8g2;
	delay_init();	   		// 延时函数初始化	  
	gpio_init();		  		// 初始化与外设连接的硬件接口
	
	oled_u8g2_init(&u8g2);	// 初始化OLED
	// u8g2_SetFont(&u8g2,u8g2_font_10x20_mf);
	u8g2_SetFont(&u8g2,u8g2_font_8x13_mf);
	
	while(1)
	{
		u8g2_ClearBuffer(&u8g2);
		oled_display(&u8g2);
		u8g2_SendBuffer(&u8g2);
		LED;
	}
}
