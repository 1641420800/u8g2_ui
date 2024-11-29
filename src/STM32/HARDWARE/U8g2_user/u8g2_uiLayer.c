#include "u8g2_ui.h"
#ifdef u8g2Ui_layer_import

#include <stdlib.h>

void u8g2Ui_callDisplay(u8g2Ui_basic_t *p)
{
    if(!p) return;
	int x = p->posSize.x;
	int y = p->posSize.y;
	int w = p->posSize.w;
	int h = p->posSize.h;
	if(x + w <= 0 || y + h <= 0) return;
	u8g2_t * u8g2 = u8g2Ui_getU8g2(p);
	u8g2_uint_t width = u8g2_GetDisplayWidth(u8g2);
	u8g2_uint_t height = u8g2_GetDisplayHeight(u8g2);
	if(w > width - x) w = width - x;
	if(h > height - y) h = height - y;
	uint8_t *_layerBuff = (uint8_t *)u8g2Ui_malloc(u8g2->tile_buf_height * width);
    if (!_layerBuff)
    {
		// todo: error
        return;
    }
	uint8_t *layerBuff = u8g2_GetBufferPtr(u8g2);
    u8g2_GetBufferPtr(u8g2) = _layerBuff;
	u8g2_ClearBuffer(u8g2);
    if (p->display)
    {
        p->display(p);
    }
    for(int _h = y < 0 ? -y : 0; _h < h; ++_h)
	{
#ifdef u8g2Ui_fastMode
		if(_h * 8 < u8g2->tile_curr_row) continue;
		if(_h * 8 > u8g2->tile_curr_row + u8g2->tile_buf_height) break;
#endif
		for(int _w = x < 0 ? -x : 0; _w < w; ++_w)
		{
			#define GET_PIXEL(_X,_Y) ((uint8_t(*)[128])_layerBuff)[(_Y) / 8][(_X)] & (1 << (_Y) % 8)
			#define SET_PIXEL(_X,_Y) ((uint8_t(*)[128])layerBuff)[(_Y) / 8][(_X)] |= (1 << ((_Y) % 8))
			#define CLR_PIXEL(_X,_Y) ((uint8_t(*)[128])layerBuff)[(_Y) / 8][(_X)] &= (~(1 << (_Y) % 8))
			if(GET_PIXEL(_w, _h))
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


uint8_t *layerBuff = NULL;
u8g2_t *layerU8g2 = NULL;
void u8g2Ui_startLayer(u8g2_t *u8g2)
{
    if (!u8g2)
        return;
    uint8_t *_layerBuff = (uint8_t *)u8g2Ui_malloc(u8g2->tile_buf_height * 128);
    if (!_layerBuff)
    {
        u8g2 = NULL;
        return;
    }
    layerBuff = u8g2_GetBufferPtr(u8g2);
    u8g2_GetBufferPtr(u8g2) = _layerBuff;
    u8g2_ClearBuffer(u8g2);
    layerU8g2 = u8g2;
}

void u8g2Ui_endLayer(Layer_t layer)
{
    if(!layerU8g2)
        return;
    uint8_t *_layerBuff = u8g2_GetBufferPtr(layerU8g2);

    switch (layer)
    {
    case LayerAND:
        for (int i = 0; i < layerU8g2->tile_buf_height * 128; ++i)
        {
            layerBuff[i] &= _layerBuff[i];
        }
        break;
    case LayerOR:
        for (int i = 0; i < layerU8g2->tile_buf_height * 128; ++i)
        {
            layerBuff[i] |= _layerBuff[i];
        }
        break;
    case LayerXOR:
        for (int i = 0; i < layerU8g2->tile_buf_height * 128; ++i)
        {
            layerBuff[i] ^= _layerBuff[i];
        }
        break;
    case LayerXNOR:
        for (int i = 0; i < layerU8g2->tile_buf_height * 128; ++i)
        {
            layerBuff[i] = (layerBuff[i] & _layerBuff[i]) | (~layerBuff[i] & ~_layerBuff[i]);
        }
        break;
    }
    u8g2_GetBufferPtr(layerU8g2) = layerBuff;
    u8g2Ui_free(_layerBuff);
    layerBuff = NULL;
    layerU8g2 = NULL;
}

#endif
