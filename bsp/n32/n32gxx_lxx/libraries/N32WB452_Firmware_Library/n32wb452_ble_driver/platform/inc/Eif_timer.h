#include "stdbool.h"
#include "stdint.h"

#ifndef __EIF_TIMER_H_
#define __EIF_TIMER_H_

void eif_timer_isr(void);
void eif_timer_init(void);

void eif_set_timeout(uint32_t to);

uint32_t eif_get_time(void);

void eif_enable_timer(bool enable);



#endif //__EIF_TIMER_H_

