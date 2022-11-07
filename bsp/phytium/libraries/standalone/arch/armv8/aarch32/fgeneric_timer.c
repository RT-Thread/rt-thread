/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: generic_timer.c
 * Date: 2022-02-10 14:53:41
 * LastEditTime: 2022-02-17 17:30:07
 * Description:  This files is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */


#include "fparameters.h"
#include "fgeneric_timer.h"
#include "faarch32.h"
#include "sdkconfig.h"

#ifndef SDK_CONFIG_H__
    #warning "Please include sdkconfig.h"
#endif

#ifdef CONFIG_USE_SYS_TICK
    #include "fassert.h"
    #include "finterrupt.h"

    static volatile u32 genericTick;
    static GenericTimerTickHandler usr_tick_handler = NULL;
#endif

#define AARCH32_CNTP_CTL_ENABLE_MASK (1ul << 0)
#define AARCH32_CNTP_CTL_INTERRUPT_MASK (1ul << 1)

void GenericTimerStart(void)
{
    u32 ctrl = aarch32_cntp_ctl_get();

    if (!(ctrl & AARCH32_CNTP_CTL_ENABLE_MASK))
    {
        ctrl |= AARCH32_CNTP_CTL_ENABLE_MASK;
        aarch32_cntp_ctl_set(ctrl);
    }
}

void GenericTimerStop(void)
{
    u32 ctrl = aarch32_cntp_ctl_get();
    if ((ctrl & AARCH32_CNTP_CTL_ENABLE_MASK))
    {
        ctrl &= ~AARCH32_CNTP_CTL_ENABLE_MASK;
        aarch32_cntp_ctl_set(ctrl);
    }
}

void GenericTimerInterruptEnable(void)
{
    u32 ctrl = aarch32_cntp_ctl_get();
    if (ctrl & AARCH32_CNTP_CTL_INTERRUPT_MASK)
    {
        ctrl &= ~AARCH32_CNTP_CTL_INTERRUPT_MASK;
        aarch32_cntp_ctl_set(ctrl);
    }
}

void GenericTimerInterruptDisable(void)
{
    u64 ctrl = aarch32_cntp_ctl_get();
    if (!(ctrl & AARCH32_CNTP_CTL_INTERRUPT_MASK))
    {
        ctrl |= AARCH32_CNTP_CTL_INTERRUPT_MASK;
        aarch32_cntp_ctl_set(ctrl);
    }
}

u32 GenericTimerFrequecy(void)
{
    u32 rate = aarch32_cntfrq_get();
    return (rate != 0) ? rate : 1000000;
}

u64 GenericTimerRead(void)
{
    return aarch32_cntpct_get();
}

void GenericTimerCompare(u32 interval)
{
    aarch32_cntp_tval_set(interval);
}

#ifdef CONFIG_USE_SYS_TICK
static void GenericTimerClearTickIntr(u32 tickRateHz)
{
    GenericTimerCompare(GenericTimerFrequecy() / tickRateHz);
}

static void GenericTimerTickIntrHandler(s32 vector, void *param)
{
    u32 tickRateHz = (u32)param;
    (void)vector;
    genericTick++;                         /* tick */
    GenericTimerClearTickIntr(tickRateHz); /* clear tick intrrupt */

    if (usr_tick_handler) /* execute user handler */
        usr_tick_handler();
}
#endif

void GenericTimerSetupSystick(u32 tickRateHz, GenericTimerTickHandler tickHandler, u32 intrPrority)
{
#ifdef CONFIG_USE_SYS_TICK
    u32 cntFrq;

    /* disable timer and get system frequency */
    GenericTimerStop();
    cntFrq = GenericTimerFrequecy();

    /* set tick rate */
    GenericTimerCompare(cntFrq / tickRateHz);
    GenericTimerInterruptEnable();

    /* set generic timer intrrupt */
    InterruptSetPriority(GENERIC_TIMER_NS_IRQ_NUM, intrPrority);

    /* install tick handler */
    usr_tick_handler = tickHandler;
    InterruptInstall(GENERIC_TIMER_NS_IRQ_NUM, GenericTimerTickIntrHandler,
                     (void *)tickRateHz, "GenericTimerTick");

    /* enable intrrupt */
    InterruptUmask(GENERIC_TIMER_NS_IRQ_NUM);
    GenericTimerStart();
#endif
}

u32 GenericGetTick(void)
{
#ifdef CONFIG_USE_SYS_TICK
    return genericTick;
#else
    return 0xffU;
#endif
}