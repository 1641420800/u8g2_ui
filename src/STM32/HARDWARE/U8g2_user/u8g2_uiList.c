#include "u8g2_ui.h"

uint8_t u8g2Ui_list_bind(struct U8G2Ui_BASIC *p_father, struct U8G2Ui_BASIC *p)
{
    if (!p_father || !p)
        return 1;
    if (p->p_father != NULL)
        return 1;
    p->p_father = p_father;
    p->p_next = p_father->p_son;
    p_father->p_son = p;
    return 0;
}

uint8_t u8g2Ui_list_unbind(struct U8G2Ui_BASIC *p)
{
    if (!p || !p->p_father)
        return 1;

    struct U8G2Ui_BASIC *p_father = p->p_father;

    if (p_father->p_son == p)
    {
        p_father->p_son = p->p_next;
    }
    else
    {
        struct U8G2Ui_BASIC *p_son = p_father->p_son;
        while (p_son && p_son->p_next)
        {
            if (p_son->p_next == p)
            {
                p_son->p_next = p->p_next;
                p->p_father = NULL;
                return 0;
            }
            else
            {
                p_son = p_son->p_next;
            }
        }
    }
    return 1;
}
