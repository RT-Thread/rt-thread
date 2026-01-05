#ifndef __DRV_BASE__
#define __DRV_BASE__
#include "board.h"

 void n32_gpio_rcc_enable(GPIO_Module *gpio_grp);

 
 void n32_time_rcc_config(TIM_Module *htim);

void gpio_remap_JTAGOFF_SWDON(GPIO_Module *gpio_grp, uint16_t pin);
#endif
