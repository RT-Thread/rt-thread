/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-07     Tanek        first implementation
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "project.h"
#include "board.h"
#include <drivers/pm.h>

#define USER_WAKEUP_PIN       PIN_WK_UP

static void (*_wakeup_hook)(void);

void bsp_register_wakeup(void (*hook)(void))
{
    RT_ASSERT(hook != RT_NULL);

    _wakeup_hook = hook;
}

static void _wakeup_callback(void *args)
{
    (void)args;
    rt_pm_exit();
    if (_wakeup_hook)
        _wakeup_hook();
}

/*
 * This function is executed when GPIO interrupt is triggered.
 */
void SwInterruptIsr()
{
    Cy_GPIO_ClearInterrupt(SW2_P0_4_0_PORT, SW2_P0_4_0_NUM);
    _wakeup_callback(NULL);
    NVIC_ClearPendingIRQ(SysInt_SW_cfg.intrSrc);
}

static int rt_hw_wakeup_init(void)
{
    /* Initialize and enable GPIO interrupt */
    /* SysInt_SW_cfg structure is defined in cyfitter_sysint_cfg.c based on
       parameters entered in the Interrupts tab of CYDWR. */
    Cy_SysInt_Init(&SysInt_SW_cfg, SwInterruptIsr);
    NVIC_ClearPendingIRQ(SysInt_SW_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_SW_cfg.intrSrc);
    
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_wakeup_init);
