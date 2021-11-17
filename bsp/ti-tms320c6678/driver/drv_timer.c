/*
 * Copyright (c) 2021, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-16     Dystopia     the first version
 */

#include "drv_timer.h"
#include "KeyStone_common.h"

#include <rthw.h>
#include <rtthread.h>

/**
 *  @b Description
 *  @n
 *      The function initial system timer.
 * 		Use local timer (==DNUM of a core) to generate a clock on TIMO0,interrupts are generated as well
 *
 *  @param[]
 *
 *  @retval
 *		NULL
 */
void hw_system_timer_init(void)
{
	// initial system timer interrupt
    // map local timer interrupt to INT14
    gpCGEM_regs->INTMUX3 = (CSL_GEM_TINTLN<<CSL_CGEM_INTMUX3_INTSEL14_SHIFT);
    // enable INT14
    CPU_interrupt_enable(1<<14);

    return ;
}

void hw_system_timer_start(void)
{
    Timer64_Config tmrCfg;

    //select output on TIMO0 from local timer.
    gpBootCfgRegs->TOUTSEL = (DNUM*2)<<CSL_BOOTCFG_TOUTSEL_TOUTSEL0_SHIFT;

    /* configure the timer to generate clocks and interrupts */
    tmrCfg.timer_num= DNUM;
    tmrCfg.timerMode= TIMER_PERIODIC_CLOCK;
    tmrCfg.period= (unsigned long long) RT_TICK_PER_SECOND*gDSP_Core_Speed_Hz/6000;
    tmrCfg.reload_period= 0; //not used for this case

    // initial timer
    Timer64_Init(&tmrCfg);
}

