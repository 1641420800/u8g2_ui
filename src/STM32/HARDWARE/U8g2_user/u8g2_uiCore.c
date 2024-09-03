#include "u8g2_ui.h"

void u8g2_ui_run_display(u8g2Ui_basic_t* p)
{
    while(p)
    {
        p->display(p);
        if(p->p_son) u8g2_ui_run_display(p->p_son);
        p = p->p_next;
    }
}

void u8g2_ui_init_call(u8g2Ui_basic_t* p)
{
    while(p)
    {
        p->init(p);
        if(p->p_son) u8g2_ui_init_call(p->p_son);
        p = p->p_next;
    }
}

void u8g2_ui_run(u8g2Ui_t* p)
{
    u8g2_ClearBuffer(&p->u8g2);
    u8g2_ui_run_display(&p->basic);
    u8g2_SendBuffer(&p->u8g2);
}

void u8g2_ui_init(u8g2Ui_t* p)
{
    u8g2_ui_init_call(&p->basic);
}

void u8g2_ui_delete(void* p)
{
    u8g2Ui_basic_t* u8g2Ui_basic = (u8g2Ui_basic_t*)p;
    if(!u8g2Ui_basic) return;
    if(u8g2Ui_basic->p_father) {
        if(u8g2_uiList_unbind(p)) return;
    }
    u8g2Ui_basic_t* u8g2Ui_basic_temp;
    u8g2Ui_basic_t** u8g2Ui_basic_temp2;
    while(u8g2Ui_basic->p_son)
    {
        u8g2Ui_basic_temp = u8g2Ui_basic->p_son;
        while (u8g2Ui_basic_temp->p_son || u8g2Ui_basic_temp->p_next)
        {
            if(u8g2Ui_basic_temp->p_son)
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

