#include "u8g2_ui.h"

void u8g2_ui_run_display(u8g2Ui_basic_t *p)
{
    while (p)
    {
        if (p->display)
            p->display(p);
        if (p->p_son)
            u8g2_ui_run_display(p->p_son);
        p = p->p_next;
    }
}

void u8g2_ui_init_call(u8g2Ui_basic_t *p)
{
    while (p)
    {
        if (p->init)
            p->init(p);
        if (p->p_son)
            u8g2_ui_init_call(p->p_son);
        p = p->p_next;
    }
}

void u8g2Ui_run(u8g2Ui_t *p)
{
    u8g2_ClearBuffer(&p->u8g2);
    u8g2_ui_run_display(&p->basic);
    u8g2_SendBuffer(&p->u8g2);
}

void u8g2Ui_init(u8g2Ui_t *p)
{
    u8g2_ui_init_call(&p->basic);
}

void u8g2Ui_delete(void *p)
{
    u8g2Ui_basic_t *u8g2Ui_basic = (u8g2Ui_basic_t *)p;
    if (!u8g2Ui_basic)
        return;
    if (u8g2Ui_basic->p_father)
    {
        if (u8g2Ui_list_unbind(p))
            return;
    }
    u8g2Ui_basic_t *u8g2Ui_basic_temp;
    u8g2Ui_basic_t **u8g2Ui_basic_temp2;
    while (u8g2Ui_basic->p_son)
    {
        u8g2Ui_basic_temp = u8g2Ui_basic->p_son;
        while (u8g2Ui_basic_temp->p_son || u8g2Ui_basic_temp->p_next)
        {
            if (u8g2Ui_basic_temp->p_son)
            {
                u8g2Ui_basic_temp = u8g2Ui_basic_temp->p_son;
                u8g2Ui_basic_temp2 = &u8g2Ui_basic_temp->p_son;
            }
            else
            {
                u8g2Ui_basic_temp = u8g2Ui_basic_temp->p_next;
                u8g2Ui_basic_temp2 = &u8g2Ui_basic_temp->p_next;
            }
        }
        *u8g2Ui_basic_temp2 = NULL;
        u8g2Ui_basic_temp->event(u8g2Ui_basic_temp, Ui_eType_delete, 0);
        u8g2Ui_basic_temp->deInit(u8g2Ui_basic_temp);
        u8g2Ui_free(u8g2Ui_basic_temp);
    }
    u8g2Ui_basic->event(u8g2Ui_basic, Ui_eType_delete, 0);
    u8g2Ui_basic->deInit(u8g2Ui_basic);
    u8g2Ui_free(p);
}

void u8g2Ui_getClipPosSize(u8g2Ui_basic_t *p, u8g2Ui_posSize_t *posSize)
{
    if (!p)
        return;
    u8g2Ui_posSize_t _posSize = p->posSize;
    p = p->p_father;
    while (p)
    {
        _posSize.x += p->posSize.x;
        _posSize.y += p->posSize.y;
        p = p->p_father;
    }
    *posSize = _posSize;
}
void u8g2Ui_clipWindow(u8g2Ui_basic_t *p)
{
    if (!p)
        return;
    u8g2_t *u8g2 = u8g2Ui_getU8g2(p);
    if (!u8g2)
        return;
    u8g2Ui_posSize_t _posSize = p->posSize;
    p = p->p_father;
    while (p)
    {
        _posSize.x += p->posSize.x;
        _posSize.y += p->posSize.y;
        u8g2_long_t x0 = _posSize.x + _posSize.w;
        u8g2_long_t y0 = _posSize.y + _posSize.h;
        u8g2_long_t x1 = p->posSize.x + p->posSize.w;
        u8g2_long_t y1 = p->posSize.y + p->posSize.h;
        _posSize.w = (x0 < x1 ? x0 : x1) - _posSize.x;
        _posSize.h = (y0 < y1 ? y0 : y1) - _posSize.y;
        p = p->p_father;
    }
    if (_posSize.x < 0)
        _posSize.x = 0;
    if (_posSize.y < 0)
        _posSize.y = 0;
    u8g2_SetClipWindow(u8g2, _posSize.x, _posSize.y, _posSize.x + _posSize.w, _posSize.y + _posSize.h);
}

void u8g2Ui_getPosSize(void *p, u8g2Ui_posSize_t *posSize)
{
	u8g2Ui_basic_t * _p = p;
	if(!_p || !posSize)
	{
		return;
	}
	*posSize = _p->posSize;
}
void u8g2Ui_setPosSize(void *p, u8g2Ui_posSize_t *posSize)
{
	u8g2Ui_basic_t * _p = p;
	if(!_p || !posSize)
	{
		return;
	}
	_p->posSize = *posSize;
}
u8g2_long_t u8g2Ui_getPosSize_x(void *p)
{
	u8g2Ui_posSize_t posSize = {0};
	u8g2Ui_getPosSize(p, &posSize);
	return posSize.x;
}
void u8g2Ui_setPosSize_x(void *p, u8g2_long_t x)
{
	u8g2Ui_posSize_t posSize = {0};
	u8g2Ui_getPosSize(p, &posSize);
	posSize.x = x;
	u8g2Ui_setPosSize(p, &posSize);
}
u8g2_long_t u8g2Ui_getPosSize_y(void *p)
{
	u8g2Ui_posSize_t posSize = {0};
	u8g2Ui_getPosSize(p, &posSize);
	return posSize.y;
}
void u8g2Ui_setPosSize_y(void *p, u8g2_long_t y)
{
	u8g2Ui_posSize_t posSize = {0};
	u8g2Ui_getPosSize(p, &posSize);
	posSize.y = y;
	u8g2Ui_setPosSize(p, &posSize);
}
u8g2_uint_t u8g2Ui_getPosSize_h(void *p)
{
	u8g2Ui_posSize_t posSize = {0};
	u8g2Ui_getPosSize(p, &posSize);
	return posSize.h;
}
void u8g2Ui_setPosSize_h(void *p, u8g2_uint_t h)
{
	u8g2Ui_posSize_t posSize = {0};
	u8g2Ui_getPosSize(p, &posSize);
	posSize.h = h;
	u8g2Ui_setPosSize(p, &posSize);
}
u8g2_uint_t u8g2Ui_getPosSize_w(void *p)
{
	u8g2Ui_posSize_t posSize = {0};
	u8g2Ui_getPosSize(p, &posSize);
	return posSize.w;
}
void u8g2Ui_setPosSize_w(void *p, u8g2_uint_t w)
{
	u8g2Ui_posSize_t posSize = {0};
	u8g2Ui_getPosSize(p, &posSize);
	posSize.w = w;
	u8g2Ui_setPosSize(p, &posSize);
}
