#include "u8g2_ui.h"

void u8g2Ui_init(struct U8G2Ui_BASIC *p)
{
    if (!p)
        return;
    u8g2Ui_t *u8g2Ui = (u8g2Ui_t *)p;
    oled_u8g2_init(&u8g2Ui->u8g2);
}
void u8g2Ui_deInit(struct U8G2Ui_BASIC *p)
{
    if (!p)
        return;
}
void u8g2Ui_display(struct U8G2Ui_BASIC *p)
{
    if (!p)
        return;
    u8g2Ui_t *u8g2Ui = (u8g2Ui_t *)p;
    u8g2_SetMaxClipWindow(&u8g2Ui->u8g2);
}
uint8_t u8g2Ui_event(struct U8G2Ui_BASIC *p, u8g2Ui_eType_t EType, int EValue)
{
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
    u8g2Ui->basic.init = u8g2Ui_init;
    u8g2Ui->basic.deInit = u8g2Ui_deInit;
    u8g2Ui->basic.display = u8g2Ui_display;
    u8g2Ui->basic.event = u8g2Ui_event;

    u8g2Ui->basic.posSize.x = 0;
    u8g2Ui->basic.posSize.y = 0;
    u8g2Ui->basic.posSize.w = u8g2_GetDisplayWidth(&u8g2Ui->u8g2);
    u8g2Ui->basic.posSize.h = u8g2_GetDisplayHeight(&u8g2Ui->u8g2);

    u8g2Ui->basic.p_father = NULL;
    u8g2Ui->basic.p_next = NULL;
    u8g2Ui->basic.p_son = NULL;

    return u8g2Ui;
}
