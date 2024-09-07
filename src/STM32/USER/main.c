#include <stdio.h>
#include <stdlib.h>

#include "sys.h"
#include "tim.h"
#include "usart.h"
#include "delay.h"
#include "gpio.h"

#include "u8g2_ui.h"


int main(void)
{
	u8g2Ui_t * u8g2Ui = new_u8g2Ui();
	u8g2_t * u8g2 = u8g2Ui_getU8g2(u8g2Ui);

	u8g2Ui_basic_t * u8g2Ui_basic = &u8g2Ui->basic;
	for(int i = 0; i < 5; i++)
	{
		u8g2Ui_text_t * u8g2Ui_text = new_u8g2Ui_textBuff(u8g2Ui_basic, 32);
		u8g2Ui_text_set_text(u8g2Ui_text, "Hello %d", i);
		u8g2Ui_setPosSize_x(u8g2Ui_text,i&1?-10:10);
		u8g2Ui_setPosSize_y(u8g2Ui_text,10);
		u8g2Ui_basic = &u8g2Ui_text->basic;
	}
	u8g2Ui_setPosSize_w(u8g2Ui->basic.p_son,64);
	
	
	delay_init();						// 延时函数初始化	  
	gpio_init();						// 初始化与外设连接的硬件接口
	
	u8g2Ui_init(u8g2Ui);
	
	while(1)
	{
		u8g2Ui_run(u8g2Ui);
		LED;
	}
}
