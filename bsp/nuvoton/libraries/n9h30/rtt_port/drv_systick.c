/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-11-11      Wayne            First version
*
******************************************************************************/

#include "rtthread.h"
#include "NuMicro.h"
#include "drv_sys.h"
#include "nu_timer.h"

#define USE_TIMER   4

/* Concatenate */
#define _CONCAT2_(x, y)             x##y
#define _CONCAT3_(x, y, z)          x##y##z
#define CONCAT2(x, y)               _CONCAT2_(x, y)
#define CONCAT3(x, y, z)            _CONCAT3_(x,y,z)

/* Concatenate the macros of timer instance for driver usage. */
#define SYSTICK_IRQ           CONCAT2(IRQ_TMR, USE_TIMER )

#define SYSTICK_CLKEN         CONCAT3(TIMER, USE_TIMER, CKEN)

#define SYSTICK_RST           CONCAT3(TIMER, USE_TIMER, RST)

static void nu_systick_isr(int vector, void *param)
{
    rt_tick_increase();
    TIMER_ClearIntFlag(USE_TIMER);
}

void rt_hw_systick_init(void)
{
    nu_sys_ipclk_enable(SYSTICK_CLKEN);

    nu_sys_ip_reset(SYSTICK_RST);

    // Set timer frequency
    TIMER_Open(USE_TIMER, TIMER_PERIODIC_MODE, RT_TICK_PER_SECOND);

    // Enable timer interrupt
    TIMER_EnableInt(USE_TIMER);

    rt_hw_interrupt_install(SYSTICK_IRQ, nu_systick_isr, RT_NULL, "systick");
    rt_hw_interrupt_set_priority(SYSTICK_IRQ, IRQ_LEVEL_1);
    rt_hw_interrupt_umask(SYSTICK_IRQ);

    TIMER_Start(USE_TIMER);
} /* rt_hw_systick_init */

void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint32_t ticks;
    rt_uint32_t told, tnow, tcnt = 0;
    rt_uint32_t cmp = TIMER_GetCompareData(USE_TIMER);

    ticks = us * cmp / (1000000 / RT_TICK_PER_SECOND);
    told = TIMER_GetCounter(USE_TIMER);
    while (1)
    {
        /* Timer counter is increment. */
        tnow = TIMER_GetCounter(USE_TIMER);
        if (tnow != told)
        {
            /* 0 -- old === now -------- cmp */
            if (tnow > told)
            {
                tcnt += tnow - told;
            }
            else
            {
                /* 0 == now --- old ======== cmp */
                tcnt += cmp - told + tnow;
            }
            told = tnow;

            /* Timeout */
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }

} /* rt_hw_us_delay  */
