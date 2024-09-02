#ifndef _U8G2_UI_
#define _U8G2_UI_

#include <stdlib.h>
#include <stdint.h>


#define u8g2Ui_malloc malloc
#define u8g2Ui_free free


typedef struct U8G2Ui_BASIC{
    struct U8G2Ui_BASIC * p_father;
    struct U8G2Ui_BASIC * p_next;
    struct U8G2Ui_BASIC * p_son;

    void (*init)(struct U8G2Ui_BASIC * p);
    void (*deInit)(void);
    void (*display)(void);  // todo
    uint8_t (*event)(void); // todo
    
} u8g2Ui_basic_t;

/* ----------------------------| u8g2_ui.c |---------------------------- */

typedef struct{
    u8g2Ui_basic_t basic;

} u8g2Ui_t;

u8g2Ui_t* new_u8g2Ui(void * p);
u8g2Ui_t* delete_u8g2Ui(void);



#endif
