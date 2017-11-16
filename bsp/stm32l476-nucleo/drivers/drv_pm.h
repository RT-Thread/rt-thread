/*
 * File      : drv_pm.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author          Notes
 * 2012-08-20     heyuanjie87     the first version
 */

#ifndef  __DRV_PM_H__
#define  __DRV_PM_H__

#include <rtthread.h>

/* stm32l4 power management timer status */
#define PMTIMER_ENTER_NONE  0
#define PMTIMER_ENTER_SLEEP 1
#define PMTIMER_ENTER_TIMER 2
#define PMTIMER_ENTER_STOP  3

struct stm32l4_pm
{
    rt_uint16_t timer_status;
    rt_uint16_t timer_reload_value;
};

int stm32l4_pm_hw_init(void);

#endif /* __DRV_PM_H__ */
