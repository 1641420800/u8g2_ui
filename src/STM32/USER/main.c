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
	u8g2Ui_t *u8g2Ui = new_u8g2Ui();
	u8g2_t *u8g2 = u8g2Ui_getU8g2(u8g2Ui);

	
	u8g2Ui_starrySky_t * u8g2Ui_starrySky = new_u8g2Ui_starrySky(u8g2Ui, 40);

	delay_init(); // 延时函数初始化
	gpio_init();  // 初始化与外设连接的硬件接口

	u8g2Ui_init(u8g2Ui);

	while (1)
	{
		u8g2Ui_run(u8g2Ui);
		LED;
	}
}
