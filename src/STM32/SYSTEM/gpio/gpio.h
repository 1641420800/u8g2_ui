#ifndef __GPIO_H
#define __GPIO_H	 
#include "sys.h"

#define LED PCout(13) = !PCin(13)

#define KEY_1 PBout(12)
#define KEY_2 PBout(13)
#define KEY_3 PBout(14)

void gpio_init(void);//≥ı ºªØ

				    
#endif
