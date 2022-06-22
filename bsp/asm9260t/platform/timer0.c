/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-04-29     ArdaFu       first version
 */

#include "timer0.h"
#include "asm9260t.h"
#include "rtthread.h"
void hw_timer0_init(void)
{
    uint32_t pclk;

    // enable timer0's clock, reset timer0
    outl((1<<4), REG_SET(HW_AHBCLKCTRL1));
    outl((1<<4), REG_CLR(HW_PRESETCTRL1));
    outl((1<<4), REG_SET(HW_PRESETCTRL1));

    outl((1<<0), REG_CLR(HW_TIMER0_TCR));

    outl((3<<0), REG_CLR(HW_TIMER0_CTCR));

    outl((3<<0), REG_CLR(HW_TIMER0_DIR));

    outl(0, REG_CLR(HW_TIMER0_PR));
    outl(0, REG_CLR(HW_TIMER0_PC));

    outl((7<<0), REG_CLR(HW_TIMER0_MCR));
    outl((3<<0), REG_SET(HW_TIMER0_MCR));

    pclk = (inl(HW_SYSPLLCTRL)&0x1FF)*1000000u/4u;
    outl(pclk/RT_TICK_PER_SECOND, HW_TIMER0_MR0);

    outl((1<<4), REG_SET(HW_TIMER0_TCR));
    outl((1<<4), REG_CLR(HW_TIMER0_TCR));
    outl((1<<0), REG_SET(HW_TIMER0_TCR));
}
