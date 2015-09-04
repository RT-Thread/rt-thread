/*
 * File      : clock.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-04-25     Yi.qiu       first version
 */

#include <rtthread.h>
#include "dm36x.h"


/**
 * @brief System Clock Configuration
 */
void rt_hw_clock_init(void)
{
	//LOCKTIME = 0xFFFFFFFF;	//u-boot already init system clock
	//rt_hw_set_mpll_clock(MPL_SDIV, MPL_PDIV, MPL_MIDV);
	//rt_hw_set_upll_clock(UPL_SDIV, UPL_PDIV, UPL_MDIV);
	//rt_hw_set_divider(HDIVN, PDIVN);
}

