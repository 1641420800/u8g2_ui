#ifndef _U8G2_UI_
#define _U8G2_UI_

#include <stdlib.h>
#include <stdint.h>

#include "u8g2.h"
#include "IIC_OLED.h"

#define u8g2Ui_malloc malloc
#define u8g2Ui_free free

typedef enum
{
    Ui_eType_click,
    Ui_eType_delete,
} u8g2Ui_eType_t;

typedef struct
{
    u8g2_long_t x;
    u8g2_long_t y;
    u8g2_uint_t w;
    u8g2_uint_t h;
} u8g2Ui_posSize_t;

typedef struct U8G2Ui_BASIC
{
    struct U8G2Ui_BASIC *p_next;
    struct U8G2Ui_BASIC *p_father;
    struct U8G2Ui_BASIC *p_son;

    u8g2Ui_posSize_t posSize;

    void (*init)(struct U8G2Ui_BASIC *p);
    void (*deInit)(struct U8G2Ui_BASIC *p);
    void (*display)(struct U8G2Ui_BASIC *p);
    uint8_t (*event)(struct U8G2Ui_BASIC *p, u8g2Ui_eType_t EType, int EValue);

} u8g2Ui_basic_t;

/* ----------------------------| u8g2_uiList.c |---------------------------- */

uint8_t u8g2_uiList_bind(struct U8G2Ui_BASIC *p_father, struct U8G2Ui_BASIC *p);
uint8_t u8g2_uiList_unbind(struct U8G2Ui_BASIC *p);

/* ----------------------------| u8g2_ui.c |---------------------------- */

typedef struct
{
    u8g2Ui_basic_t basic;
    u8g2_t u8g2;
} u8g2Ui_t;

u8g2Ui_t *new_u8g2Ui(void);

/* ----------------------------| u8g2_uiCore.c |---------------------------- */

void u8g2_ui_init(u8g2Ui_t* p);
void u8g2_ui_run(u8g2Ui_t *p);
void u8g2_ui_delete(void *p);

#endif
