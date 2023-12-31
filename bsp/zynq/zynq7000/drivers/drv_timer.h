#ifndef DRV_TIMER_H__
#define DRV_TIMER_H__

#include "xparameters.h"

int rt_hw_timer_init(void);

#define TIMER_IRPT_INTR XPAR_SCUTIMER_INTR

#endif
