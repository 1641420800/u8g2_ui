#include "u8g2_ui.h"
#ifdef u8g2Ui_starrySky_import
#include <stdlib.h>

void u8g2Ui_starrySky_init(struct U8G2Ui_BASIC *p)
{
    u8g2Ui_starrySky_t *_p = TYPE_CAST(p, Ui_Type_ui_starrySky);
    if (!_p)
    {
        // todo
        return;
    }
    u8g2_stars_t *stars = (u8g2_stars_t *)u8g2Ui_malloc(sizeof(u8g2_stars_t) * _p->maximumQuantity);
    if (!stars)
    {
        // todo
        _p->stars = NULL;
        return;
    }
    srand(_p->maximumQuantity);
    _p->stars = stars;
}
void u8g2Ui_starrySky_deInit(struct U8G2Ui_BASIC *p)
{
    u8g2Ui_starrySky_t *_p = TYPE_CAST(p, Ui_Type_ui_starrySky);
    if (!_p)
    {
        // todo
        return;
    }
    if (_p->stars)
    {
        u8g2Ui_free(_p->stars);
    }
    _p->stars = NULL;
}
void u8g2Ui_starrySky_display(struct U8G2Ui_BASIC *p)
{
    u8g2Ui_starrySky_t *_p = TYPE_CAST(p, Ui_Type_ui_starrySky);
    if (!_p || !_p->stars)
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
    u8g2Ui_posSize_t posSize;
    u8g2Ui_getClipPosSize(p, &posSize);
    u8g2Ui_clipWindow(p);
    u8g2_SetFont(u8g2, u8g2_font_8x13_mf);
    posSize.y += u8g2_GetAscent(u8g2);

#ifdef u8g2Ui_fastMode
    if (u8g2->tile_curr_row == 0)
    {
#endif
        for (uint16_t i = 0; i < _p->maximumQuantity; i++)
        {
            if (!_p->stars[i].effective)
            {
                if (rand() % 100 < 20) // 一定概率生产 会影响密度
                {
                    _p->stars[i].effective = 1;
                    // 假设一个方向
                    _p->stars[i].y = rand() % posSize.h;
                    _p->stars[i].x = 0;
                    _p->stars[i].siz = rand() % 4;
                }
            }
            else
            {
                // 假设一个方向
                _p->stars[i].x += _p->stars[i].siz + 1;
                if (_p->stars[i].x > posSize.w)
                {
                    _p->stars[i].effective = 0;
                }
            }
        }
#ifdef u8g2Ui_fastMode
    }
#endif
    for (uint16_t i = 0; i < _p->maximumQuantity; i++)
    {
        if (_p->stars[i].effective)
        {
            u8g2_DrawDisc(u8g2, posSize.x + _p->stars[i].x, posSize.y + _p->stars[i].y, _p->stars[i].siz + 1, U8G2_DRAW_ALL);
        }
    }
}
uint8_t u8g2Ui_starrySky_event(struct U8G2Ui_BASIC *p, u8g2Ui_eType_t EType, int EValue)
{
    u8g2Ui_starrySky_t *_p = TYPE_CAST(p, Ui_Type_ui_starrySky);
    if (!_p)
    {
        // todo
        return 0;
    }
    return 0;
}

u8g2Ui_starrySky_t *new_u8g2Ui_starrySky(void *p, size_t maximumQuantity)
{
    if (!p || !maximumQuantity)
    {
        // todo
        return NULL;
    }
    u8g2Ui_starrySky_t *u8g2Ui_starrySky = (u8g2Ui_starrySky_t *)u8g2Ui_malloc(sizeof(u8g2Ui_starrySky_t));
    if (!u8g2Ui_starrySky)
    {
        // todo
        return NULL;
    }

    u8g2Ui_basic_init(
        &u8g2Ui_starrySky->basic,
        u8g2Ui_starrySky_init,
        u8g2Ui_starrySky_deInit,
        u8g2Ui_starrySky_display,
        u8g2Ui_starrySky_event,
        Ui_Type_ui_starrySky);

    u8g2Ui_starrySky->basic.posSize.h = 64;
    u8g2Ui_starrySky->basic.posSize.w = 128;

    u8g2Ui_starrySky->stars = NULL;
    u8g2Ui_starrySky->maximumQuantity = maximumQuantity;

    u8g2Ui_list_bind(p, &u8g2Ui_starrySky->basic);

    return u8g2Ui_starrySky;
}

#endif
