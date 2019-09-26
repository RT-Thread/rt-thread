/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-08-25     Bernard      first version
 */

#include <rtthread.h>
#include <rthw.h>

#include "AT91SAM7S.h"

/**
 * @addtogroup AT91SAM7
 */
/*@{*/

void rt_hw_trap_irq()
{
	rt_isr_handler_t hander = (rt_isr_handler_t)AT91C_AIC_IVR;

	hander(AT91C_AIC_ISR);

	/* end of interrupt */
	AT91C_AIC_EOICR = 0;
}

void rt_hw_trap_fiq()
{
    rt_kprintf("fast interrupt request\n");
}

/*@}*/
