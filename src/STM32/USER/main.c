#include <stdio.h>
#include <stdlib.h>

#include "sys.h"
#include "tim.h"
#include "usart.h"
#include "delay.h"
#include "gpio.h"

#include "u8g2_ui.h"

void PaintingFrame(u8g2Ui_basic_t * p, u8g2Ui_posSize_t * posSize)
{
	
	
	u8g2_t * u8g2 = u8g2Ui_getU8g2(p);
	u8g2_DrawUTF8(u8g2,10,15,"test");
	
	layer(u8g2,LayerXOR,u8g2_DrawRBox(u8g2,5,1,42,15,7));

}

int main(void)
{
	u8g2Ui_t *u8g2Ui = new_u8g2Ui();
	u8g2_t *u8g2 = u8g2Ui_getU8g2(u8g2Ui);

	
	u8g2Ui_paintingFrame_t * u8g2Ui_paintingFrame = new_u8g2Ui_paintingFrame(u8g2Ui, PaintingFrame);

	delay_init(); // 延时函数初始化
	gpio_init();  // 初始化与外设连接的硬件接口

	u8g2Ui_init(u8g2Ui);

	while (1)
	{
		u8g2Ui_run(u8g2Ui);
		LED;
	}
}
