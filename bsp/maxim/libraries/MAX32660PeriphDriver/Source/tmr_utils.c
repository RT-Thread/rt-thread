/* *****************************************************************************
 * Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2018-10-17 14:16:30 -0500 (Wed, 17 Oct 2018) $
 * $Revision: 38560 $
 *
 **************************************************************************** */

/* **** Includes **** */
#include <stddef.h>
#include "mxc_assert.h"
#include "tmr.h"
#include "tmr_utils.h"

/* **** Definitions **** */

/* **** Globals **** */

/* **** Functions **** */

/* ************************************************************************** */
void TMR_Delay(mxc_tmr_regs_t *tmr, unsigned long us, const sys_cfg_tmr_t *sys_cfg)
{
    // Return immediately if delay is 0
    if (!us) {
        return;
    }
    
    TMR_TO_Start(tmr, us, sys_cfg);
    
    while (TMR_TO_Check(tmr) != E_TIME_OUT) {}
}

/* ************************************************************************** */
void TMR_TO_Start(mxc_tmr_regs_t *tmr, unsigned long us, const sys_cfg_tmr_t *sys_cfg)
{
    uint64_t ticks;
    int clk_shift = 0;
    
    ticks = (uint64_t)us * (uint64_t)PeripheralClock / (uint64_t)1000000;
    while (ticks > 0xFFFFFFFFUL) {
        ticks >>= 1;
        ++clk_shift;
    }
    tmr_pres_t prescale = (tmr_pres_t)(clk_shift << MXC_F_TMR_CN_PRES_POS);

    TMR_Init(tmr, prescale, sys_cfg);
    
    // Initialize the timer in one-shot mode
    tmr_cfg_t cfg;
    cfg.mode = TMR_MODE_ONESHOT;
    cfg.cmp_cnt = ticks;
    cfg.pol = 0;
    
    TMR_Disable(tmr);
    TMR_Config(tmr, &cfg);
    
    TMR_IntClear(tmr);
    TMR_Enable(tmr);
}

/* ************************************************************************** */
int TMR_TO_Check(mxc_tmr_regs_t *tmr)
{
    if (TMR_IntStatus(tmr)) {
        return E_TIME_OUT;
    }
    return E_NO_ERROR;
}

/* ************************************************************************** */
void TMR_TO_Stop(mxc_tmr_regs_t *tmr)
{
    TMR_Disable(tmr);
    TMR_SetCount(tmr, 0x0);
}

/* ************************************************************************** */
void TMR_TO_Clear(mxc_tmr_regs_t *tmr)
{
    TMR_IntClear(tmr);
    TMR_SetCount(tmr, 0x0);
}

/* ************************************************************************** */
unsigned int TMR_TO_Elapsed(mxc_tmr_regs_t *tmr)
{
    uint32_t elapsed;
    tmr_unit_t units;
    
    TMR_GetTime(tmr, TMR_GetCount(tmr), &elapsed, &units);
    
    switch (units) {
        case TMR_UNIT_NANOSEC:
        default:
            return (elapsed / 1000);
        case TMR_UNIT_MICROSEC:
            return (elapsed);
        case TMR_UNIT_MILLISEC:
            return (elapsed * 1000);
        case TMR_UNIT_SEC:
            return (elapsed * 1000000);
    }
}

/* ************************************************************************** */
unsigned int TMR_TO_Remaining(mxc_tmr_regs_t *tmr)
{
    uint32_t remaining_ticks, remaining_time;
    tmr_unit_t units;
    
    remaining_ticks = TMR_GetCompare(tmr) - TMR_GetCount(tmr);
    TMR_GetTime(tmr, remaining_ticks, &remaining_time, &units);
    
    switch (units) {
        case TMR_UNIT_NANOSEC:
        default:
            return (remaining_time / 1000);
        case TMR_UNIT_MICROSEC:
            return (remaining_time);
        case TMR_UNIT_MILLISEC:
            return (remaining_time * 1000);
        case TMR_UNIT_SEC:
            return (remaining_time * 1000000);
    }
}

/* ************************************************************************** */
void TMR_SW_Start(mxc_tmr_regs_t *tmr, const sys_cfg_tmr_t *sys_cfg)
{
    TMR_TO_Start(tmr, 0xFFFFFFFF, sys_cfg);
}

/* ************************************************************************** */
unsigned int TMR_SW_Stop(mxc_tmr_regs_t *tmr)
{
    unsigned int elapsed = TMR_TO_Elapsed(tmr);
    TMR_TO_Stop(tmr);
    return elapsed;
}
