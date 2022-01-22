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

#define USE_TIMER   5

/* Concatenate */
#define _CONCAT2_(x, y)       x##y
#define CONCAT2(x, y)         _CONCAT2_(x, y)

/* Concatenate the macros of timer instance for driver usage. */
#define SYSTICK               CONCAT2(TIMER, USE_TIMER)
#define SYSTICK_IRQ           CONCAT2(IRQ_TIMER, USE_TIMER)

static void nu_systick_isr(int vector, void *param)
{
    rt_tick_increase();
    ETIMER_ClearIntFlag(USE_TIMER);
}

void rt_hw_systick_init(void)
{
    nu_sys_ipclk_enable(TIMER5CKEN);

    nu_sys_ip_reset(TIMER5RST);

    // Set timer frequency
    ETIMER_Open(USE_TIMER, ETIMER_PERIODIC_MODE, RT_TICK_PER_SECOND);

    // Enable timer interrupt
    ETIMER_EnableInt(USE_TIMER);

    rt_hw_interrupt_install(SYSTICK_IRQ, nu_systick_isr, RT_NULL, "systick");
    rt_hw_interrupt_set_priority(SYSTICK_IRQ, IRQ_LEVEL_1);
    rt_hw_interrupt_umask(SYSTICK_IRQ);

    ETIMER_Start(USE_TIMER);
} /* rt_hw_systick_init */

void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint32_t ticks;
    rt_uint32_t told, tnow, tcnt = 0;
    rt_uint32_t cmp = ETIMER_GetCompareData(USE_TIMER);

    ticks = us * cmp / (1000000 / RT_TICK_PER_SECOND);
    told = ETIMER_GetCounter(USE_TIMER);
    while (1)
    {
        /* Timer counter is increment. */
        tnow = ETIMER_GetCounter(USE_TIMER);
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
} /* rt_hw_us_delay */
