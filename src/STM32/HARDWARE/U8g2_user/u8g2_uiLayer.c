#include "u8g2_ui.h"
#ifdef u8g2Ui_layer_import

#include <stdlib.h>

void u8g2Ui_getClipPosSize(u8g2Ui_basic_t *p, u8g2Ui_posSize_t *posSize)
{
    if (!p)
        return;
    
    // 复制初始位置和大小
    *posSize = p->posSize;

    u8g2_long_t x0 = posSize->x;
    u8g2_long_t y0 = posSize->y;
    u8g2_long_t x1 = posSize->x + posSize->w;
    u8g2_long_t y1 = posSize->y + posSize->h;
    
    p = p->p_father;
    while (p)
    {
        if (x0 < p->posSize.x)
            x0 = p->posSize.x;
        if (y0 < p->posSize.y)
            y0 = p->posSize.y;
        if (x1 > p->posSize.x + p->posSize.w)
            x1 = p->posSize.x + p->posSize.w;
        if (y1 > p->posSize.y + p->posSize.h)
            y1 = p->posSize.y + p->posSize.h;
        
        p = p->p_father;
    }
    
    if(x0 < 0)
    {
        x0 = 0;
    }
    if(y0 < 0)
    {
        y0 = 0;
    }
    if(x1 < x0 || y1 < y0)
    {
        x1 = x0;
        y1 = y0;
    }

    // 更新计算后的位置和大小
    posSize->x = x0;
    posSize->y = y0;
    posSize->w = x1 - x0;
    posSize->h = y1 - y0;
}

void u8g2Ui_callDisplay(u8g2Ui_basic_t *p)
{
    if (!p || !p->display)
        return;
    u8g2Ui_posSize_t posSize;
    u8g2Ui_getClipPosSize(p, &posSize);
    int x = posSize.x;
    int y = posSize.y;
    int w = posSize.w;
    int h = posSize.h;
    if (x + w <= 0 || y + h <= 0)
        return;
    u8g2_t *u8g2 = u8g2Ui_getU8g2(p);
    u8g2_uint_t width = u8g2_GetDisplayWidth(u8g2);
    u8g2_uint_t height = u8g2_GetDisplayHeight(u8g2);
    if (w > width - x)
        w = width - x;
    if (h > height - y)
        h = height - y;
    uint8_t *_layerBuff = (uint8_t *)u8g2Ui_malloc(u8g2->tile_buf_height * width);
    if (!_layerBuff)
    {
        // todo: error
        return;
    }
    uint8_t *layerBuff = u8g2_GetBufferPtr(u8g2);
    u8g2_GetBufferPtr(u8g2) = _layerBuff;
    u8g2_ClearBuffer(u8g2);

    p->display(p);

    for (int _h = y < 0 ? -y : 0; _h < h; ++_h)
    {
#ifdef u8g2Ui_fastMode
        if (_h * 8 < u8g2->tile_curr_row)
            continue;
        if (_h * 8 > u8g2->tile_curr_row + u8g2->tile_buf_height)
            break;
#endif
        for (int _w = x < 0 ? -x : 0; _w < w; ++_w)
        {
#define GET_PIXEL(_X, _Y) ((uint8_t(*)[128])_layerBuff)[(_Y) / 8][(_X)] & (1 << (_Y) % 8)
#define SET_PIXEL(_X, _Y) ((uint8_t(*)[128])layerBuff)[(_Y) / 8][(_X)] |= (1 << ((_Y) % 8))
#define CLR_PIXEL(_X, _Y) ((uint8_t(*)[128])layerBuff)[(_Y) / 8][(_X)] &= (~(1 << (_Y) % 8))
            if (GET_PIXEL(_w, _h))
            {
                SET_PIXEL(_w + x, _h + y);
            }
            else
            {
                CLR_PIXEL(_w + x, _h + y);
            }
        }
    }
    u8g2Ui_free(_layerBuff);
    u8g2_GetBufferPtr(u8g2) = layerBuff;
}
#endif
