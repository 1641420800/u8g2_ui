#ifndef _U8G2_UI_
#define _U8G2_UI_

#include <stdlib.h>
#include <stdint.h>

#include "u8g2.h"
#include "IIC_OLED.h"

#define u8g2Ui_malloc malloc
#define u8g2Ui_free free

#define u8g2Ui_fastMode

#define u8g2Ui_layer_import
#define u8g2Ui_text_import
#define u8g2Ui_paintingFrame_import


#define TYPE_CAST(p,Type) ((void*)((p) ? (((u8g2Ui_basic_t*)p)->type) == (Type) ? (p) : NULL : NULL))
typedef enum
{
    Ui_Type_ui_basic,
    Ui_Type_ui,
    Ui_Type_ui_text,
    Ui_Type_ui_paintingFrame,
} u8g2Ui_Type_t;

typedef enum
{
    Ui_eType_click,
    Ui_eType_delete,
    Ui_eType_getContentH,
    Ui_eType_getContentW,

    // 公共事件
    Ui_eType_setX,
    Ui_eType_setY,
    Ui_eType_setW,
    Ui_eType_setH,
    Ui_eType_setFont,
    Ui_eType_getX,
    Ui_eType_getY,
    Ui_eType_getW,
    Ui_eType_getH,
    Ui_eType_getFont,
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

    u8g2Ui_Type_t type;
    u8g2Ui_posSize_t posSize;
	const uint8_t *font;

    void (*init)(struct U8G2Ui_BASIC *p);
    void (*deInit)(struct U8G2Ui_BASIC *p);
    void (*display)(struct U8G2Ui_BASIC *p);
    uint8_t (*event)(struct U8G2Ui_BASIC *p, u8g2Ui_eType_t EType, int EValue);
    uint8_t (*userEvent)(struct U8G2Ui_BASIC *p, u8g2Ui_eType_t EType, int EValue);

} u8g2Ui_basic_t;
/*
void u8g2Ui_init(struct U8G2Ui_BASIC *p)
{
    u8g2Ui_text_t * _p = TYPE_CAST(p, Ui_Type_ui_basic);
    if (!_p)
    {
        // todo
        return;
    }
}
void u8g2Ui_deInit(struct U8G2Ui_BASIC *p)
{
    u8g2Ui_text_t * _p = TYPE_CAST(p, Ui_Type_ui_basic);
    if (!_p)
    {
        // todo
        return;
    }
}
void u8g2Ui_display(struct U8G2Ui_BASIC *p)
{
    u8g2Ui_text_t * _p = TYPE_CAST(p, Ui_Type_ui_basic);
    if (!_p)
    {
        // todo
        return;
    }
}
uint8_t u8g2Ui_event(struct U8G2Ui_BASIC *p, u8g2Ui_eType_t EType, int EValue)
{
    u8g2Ui_text_t * _p = TYPE_CAST(p, Ui_Type_ui_basic);
    if (!_p)
    {
        // todo
        return 0;
    }
    return u8g2Ui_basicEvent(p,EType,EValue);
}
*/
/* ----------------------------| u8g2_uiList.c |---------------------------- */

uint8_t u8g2Ui_list_bind(struct U8G2Ui_BASIC *p_father, struct U8G2Ui_BASIC *p);
uint8_t u8g2Ui_list_unbind(struct U8G2Ui_BASIC *p);

/* ----------------------------| u8g2_ui.c |---------------------------- */

typedef struct
{
    u8g2Ui_basic_t basic;
    u8g2_t u8g2;
} u8g2Ui_t;

u8g2Ui_t *new_u8g2Ui(void);
u8g2_t *u8g2Ui_getU8g2(void *p);

/* ----------------------------| u8g2_uiLayer.c |---------------------------- */
#ifdef u8g2Ui_layer_import

#endif
/* ----------------------------| u8g2_uiText.c |---------------------------- */
#ifdef u8g2Ui_text_import

typedef struct
{
    u8g2Ui_basic_t basic;
    char *text;
    uint16_t textLen;
    uint8_t isMultiline;
    uint8_t isVisible;
} u8g2Ui_text_t;

u8g2Ui_text_t *new_u8g2Ui_text(void *p, char *text);
u8g2Ui_text_t *new_u8g2Ui_textBuff(void *p, uint16_t textLen);

char *u8g2Ui_text_get_text(void *p);
void u8g2Ui_text_set_text(void *p, const char *text, ...);
uint8_t u8g2Ui_text_get_isMultiline(void *p);
void u8g2Ui_text_set_isMultiline(void *p, uint8_t isMultiline);
uint8_t u8g2Ui_text_get_isVisible(void *p);
void u8g2Ui_text_set_isVisible(void *p, uint8_t isVisible);
u8g2_uint_t u8g2Ui_text_get_contentH(void *p);
u8g2_uint_t u8g2Ui_text_get_contentW(void *p);


#endif
/* ----------------------------| u8g2_uiPaintingFrame.c |---------------------------- */
#ifdef u8g2Ui_paintingFrame_import

typedef void(*PaintingFrame_cb)(u8g2Ui_basic_t * p, u8g2Ui_posSize_t * posSize);
typedef struct
{
    u8g2Ui_basic_t basic;
    PaintingFrame_cb cb;
} u8g2Ui_paintingFrame_t;


u8g2Ui_paintingFrame_t *new_u8g2Ui_paintingFrame(void *p, PaintingFrame_cb cb);
PaintingFrame_cb u8g2Ui_paintingFrame_get_cb(void *p);
void u8g2Ui_paintingFrame_set_cb(void *p, PaintingFrame_cb cb);

#endif
/* ----------------------------| u8g2_uiCore.c |---------------------------- */

void u8g2Ui_basic_init(u8g2Ui_basic_t *basic,void (*init)(struct U8G2Ui_BASIC *p),void (*deInit)(struct U8G2Ui_BASIC *p),void (*display)(struct U8G2Ui_BASIC *p),uint8_t (*event)(struct U8G2Ui_BASIC *p, u8g2Ui_eType_t EType, int EValue),u8g2Ui_Type_t type);
void u8g2Ui_init(u8g2Ui_t *p);
void u8g2Ui_run(u8g2Ui_t *p);
void u8g2Ui_delete(void *p);
void u8g2Ui_getClipPosSize(u8g2Ui_basic_t *p, u8g2Ui_posSize_t *posSize);
void u8g2Ui_clipWindow(u8g2Ui_basic_t *p);
void u8g2Ui_getPosSize(void *p, u8g2Ui_posSize_t *posSize);
void u8g2Ui_setPosSize(void *p, u8g2Ui_posSize_t *posSize);
u8g2_long_t u8g2Ui_getPosSize_x(void *p);
void u8g2Ui_setPosSize_x(void *p, u8g2_long_t x);
u8g2_long_t u8g2Ui_getPosSize_y(void *p);
void u8g2Ui_setPosSize_y(void *p, u8g2_long_t y);
u8g2_uint_t u8g2Ui_getPosSize_h(void *p);
void u8g2Ui_setPosSize_h(void *p, u8g2_uint_t h);
u8g2_uint_t u8g2Ui_getPosSize_w(void *p);
void u8g2Ui_setPosSize_w(void *p, u8g2_uint_t w);
const uint8_t *u8g2Ui_getFont(void *p);
void u8g2Ui_setFont(void *p, const uint8_t *font);
uint8_t u8g2Ui_basicEvent(struct U8G2Ui_BASIC *p, u8g2Ui_eType_t EType, int EValue);


#endif
