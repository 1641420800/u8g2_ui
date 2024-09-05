#include "u8g2_ui.h"

void u8g2Ui_Init(struct U8G2Ui_BASIC *p)
{
    if (!p && p->type == Ui_Type_ui)
        return;
    u8g2Ui_t *u8g2Ui = (u8g2Ui_t *)p;
    oled_u8g2_init(&u8g2Ui->u8g2);
    u8g2Ui->basic.posSize.w = u8g2_GetDisplayWidth(&u8g2Ui->u8g2);
    u8g2Ui->basic.posSize.h = u8g2_GetDisplayHeight(&u8g2Ui->u8g2);
}
void u8g2Ui_deInit(struct U8G2Ui_BASIC *p)
{
    if (!p && p->type == Ui_Type_ui)
        return;
}
void u8g2Ui_display(struct U8G2Ui_BASIC *p)
{
    if (!p && p->type == Ui_Type_ui)
        return;
    u8g2Ui_clipWindow(p);
}
uint8_t u8g2Ui_event(struct U8G2Ui_BASIC *p, u8g2Ui_eType_t EType, int EValue)
{
    if (!p && p->type == Ui_Type_ui)
        return 0;
    return 0;
}

u8g2Ui_t *new_u8g2Ui(void)
{
    u8g2Ui_t *u8g2Ui = (u8g2Ui_t *)u8g2Ui_malloc(sizeof(u8g2Ui_t));
    if (!u8g2Ui)
    {
        // todo
        return NULL;
    }
    u8g2Ui->basic.init = u8g2Ui_Init;
    u8g2Ui->basic.deInit = u8g2Ui_deInit;
    u8g2Ui->basic.display = u8g2Ui_display;
    u8g2Ui->basic.event = u8g2Ui_event;
    u8g2Ui->basic.type = Ui_Type_ui;
    u8g2Ui->basic.p_father = NULL;
    u8g2Ui->basic.p_next = NULL;
    u8g2Ui->basic.p_son = NULL;

    u8g2Ui->basic.posSize.x = 0;
    u8g2Ui->basic.posSize.y = 0;
    u8g2Ui->basic.posSize.w = 0;
    u8g2Ui->basic.posSize.h = 0;

    return u8g2Ui;
}

u8g2_t *u8g2Ui_getU8g2(void *p)
{
    if (!p)
        return NULL;
    u8g2Ui_t *_p = (u8g2Ui_t *)p;
    while (_p->basic.p_father)
        _p = (u8g2Ui_t *)_p->basic.p_father;
    if (_p->basic.type != Ui_Type_ui)
    {
        // todo
        return NULL;
    }
    return &(_p->u8g2);
}
