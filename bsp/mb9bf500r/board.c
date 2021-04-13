/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-02-24     Bernard      first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "mb9bf506r.h"
#include "core_cm3.h"

extern const uint32_t SystemFrequency;

/**
 * @addtogroup FM3
 */

/*@{*/

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
* This function will initial FM3 Easy Kit board.
 */
void rt_hw_board_init()
{
    /* init systick */
    SysTick_Config(SystemFrequency/RT_TICK_PER_SECOND);
}

/*@}*/
