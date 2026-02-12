#include "stdbool.h"
#include "stdint.h"
//#include "main.h"


#ifndef __EIF_IOM_H__
#define __EIF_IOM_H__

void eif_pull_up_wakeup_io(void);

void eif_pull_down_wakeup_io(void);

void eif_pull_up_reset_io(void);

void eif_pull_down_reset_io(void);

uint8_t eif_get_status_io_value(void);

void eif_gpio_init(void);

void eif_gpio_DeInit(void);

void eif_gpio_ReInit(void);

void EXTI_NZ8801_STAIRQ_Config(void);

void EXTI_NZ8801_STAIRQ_Default(void);

#endif //__EIF_IOM_H__




