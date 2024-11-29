#include <stdio.h>
#include <stdlib.h>

#include "sys.h"
#include "tim.h"
#include "usart.h"
#include "delay.h"
#include "gpio.h"

#include "u8g2_ui.h"

void PaintingFrame(u8g2Ui_basic_t *p, u8g2Ui_posSize_t *posSize)
{
    if (!p)
    {
        // todo
        return;
    }
    u8g2_t *u8g2 = u8g2Ui_getU8g2(p);
    if (!u8g2)
    {
        // todo
        return;
    }
	if(1) // todo: 测试
	{
		u8g2_DrawStr(u8g2,0,10,"Hello World");
		u8g2_DrawLine(u8g2, 0, 0, 128, 64);
		u8g2_DrawLine(u8g2, 0, 0, 64, 64);
	}
}

int main(void)
{
	u8g2Ui_t *u8g2Ui = new_u8g2Ui();
	u8g2_t *u8g2 = u8g2Ui_getU8g2(u8g2Ui);

	
	u8g2Ui_paintingFrame_t * u8g2Ui_paintingFrame = new_u8g2Ui_paintingFrame(u8g2Ui, PaintingFrame);
	u8g2Ui_paintingFrame_t * u8g2Ui_paintingFrame2 = new_u8g2Ui_paintingFrame(u8g2Ui_paintingFrame, PaintingFrame);

	u8g2Ui_setPosSize_x(u8g2Ui_paintingFrame2,10);
	u8g2Ui_setPosSize_y(u8g2Ui_paintingFrame2,10);

	delay_init(); // 延时函数初始化
	gpio_init();  // 初始化与外设连接的硬件接口

	u8g2Ui_init(u8g2Ui);

	while (1)
	{
		u8g2Ui_run(u8g2Ui);
		LED;
	}
}
