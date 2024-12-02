#include <stdio.h>
#include <stdlib.h>

#include "sys.h"
#include "tim.h"
#include "usart.h"
#include "delay.h"
#include "gpio.h"

#include "u8g2_ui.h"

void PaintingFrame(u8g2_t *u8g2, u8g2_uint_t w, u8g2_uint_t h)
{
    if (!u8g2)
    {
        // todo
        return;
    }
	// 绘制矩形
	u8g2_DrawFrame(u8g2, 0, 0, w, h);
}

int main(void)
{
	u8g2Ui_t *u8g2Ui = new_u8g2Ui();
	
	u8g2Ui_paintingFrame_t * u8g2Ui_paintingFrame = new_u8g2Ui_paintingFrame(u8g2Ui, PaintingFrame);
	u8g2Ui_paintingFrame_t * u8g2Ui_paintingFrame2 = new_u8g2Ui_paintingFrame(u8g2Ui_paintingFrame, PaintingFrame);

	u8g2Ui_setPosSize_w(u8g2Ui_paintingFrame,64);
	u8g2Ui_setPosSize_w(u8g2Ui_paintingFrame2,10);
	u8g2Ui_setPosSize_h(u8g2Ui_paintingFrame2,10);

	delay_init(); // 延时函数初始化
	gpio_init();  // 初始化与外设连接的硬件接口

	u8g2Ui_init(u8g2Ui);

	while (1)
	{
		u8g2Ui_setPosSize_x(u8g2Ui_paintingFrame2,-5);
		u8g2Ui_setPosSize_y(u8g2Ui_paintingFrame2,-5);
		u8g2Ui_run(u8g2Ui);
		LED;
	}
}
