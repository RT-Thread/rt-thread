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
 * $Date: 2019-09-11 14:32:22 -0500 (Wed, 11 Sep 2019) $
 * $Revision: 46047 $
 *
 **************************************************************************** */

/* **** Includes **** */
#include "mxc_config.h"
#include "mxc_assert.h"
#include "mxc_sys.h"
#include "tmr.h"

/* **** Definitions **** */

/* **** Globals **** */

/* **** Functions **** */

/* ************************************************************************** */
int TMR_Init(mxc_tmr_regs_t *tmr, tmr_pres_t pres, const sys_cfg_tmr_t* sys_cfg)
{
    MXC_ASSERT(tmr);
    
    int err;
    // System settigns
    if((err=SYS_TMR_Init(tmr, sys_cfg)) !=E_NO_ERROR)
    {
        return err;
    }
    
    // Disable timer and clear settings
    tmr->cn = 0;
    
    // Clear interrupt flag
    tmr->intr = MXC_F_TMR_INTR_IRQ_CLR;
    
    // Set the prescaler
    tmr->cn = pres;

    return err;
}

int TMR_Shutdown(mxc_tmr_regs_t *tmr)
{
    MXC_ASSERT(tmr);
    
    int err;
    // System settigns
    if((err=SYS_TMR_Shutdown(tmr)) !=E_NO_ERROR)
    {
        return err;
    }
    
    // Disable timer and clear settings
    tmr->cn = 0;
    
    return err;
}

/* ************************************************************************** */
void TMR_Enable(mxc_tmr_regs_t* tmr)
{
    MXC_ASSERT(tmr);

    tmr->cn |= MXC_F_TMR_CN_TEN;
}

/* ************************************************************************** */
void TMR_Disable(mxc_tmr_regs_t* tmr)
{
    MXC_ASSERT(tmr);

    tmr->cn &= ~(MXC_F_TMR_CN_TEN);
}

/* ************************************************************************** */
int TMR_Config(mxc_tmr_regs_t *tmr, const tmr_cfg_t *cfg)
{
    MXC_ASSERT(tmr);
    
    // Configure the timer
    tmr->cn = (tmr->cn & ~(MXC_F_TMR_CN_TMODE | MXC_F_TMR_CN_TPOL)) |
              ((cfg->mode << MXC_F_TMR_CN_TMODE_POS) & MXC_F_TMR_CN_TMODE) |
              ((cfg->pol << MXC_F_TMR_CN_TPOL_POS) & MXC_F_TMR_CN_TPOL);
              
    tmr->cnt = 0x1;
    tmr->cmp = cfg->cmp_cnt;

    return E_NO_ERROR;
}

/* ************************************************************************** */
int TMR_PWMConfig(mxc_tmr_regs_t *tmr, const tmr_pwm_cfg_t *cfg)
{
    if (cfg->duty_cnt > cfg->per_cnt) {
        return E_BAD_PARAM;
    }
    
    // Configure the timer
    tmr->cn = (tmr->cn & ~(MXC_F_TMR_CN_TMODE | MXC_F_TMR_CN_TPOL)) |
              MXC_S_TMR_CN_TMODE_PWM | ((cfg->pol << MXC_F_TMR_CN_TPOL_POS) & MXC_F_TMR_CN_TPOL);
              
    tmr->cnt = 0x1;
    tmr->cmp = cfg->per_cnt;
    tmr->pwm = cfg->duty_cnt;
    
    return E_NO_ERROR;
}

/* ************************************************************************** */
int TMR_PWMSetDuty(mxc_tmr_regs_t *tmr, uint32_t duty)
{
    uint32_t cnt;
    
    // Make sure the new Duty count is less than the period count
    if (duty > tmr->cmp) {
        return E_BAD_PARAM;
    }
    
    cnt = tmr->cnt; // make sure order of volatile access is known.
    // Avoid glitching the output
    if (duty >= tmr->pwm) {
        // Wait for the count to be in the range of 1 to tmr->pwm
        while (cnt > tmr->pwm) {
            cnt = tmr->cnt; // update the volatile access variable
        }
    } else {
        // Wait for the count to pass tmr->pwm
        while (cnt < tmr->pwm) {
            cnt = tmr->cnt; // update the volatile access variable
        }
    }
    tmr->pwm = duty;
    
    return E_NO_ERROR;
}

/* ************************************************************************** */
int TMR_PWMSetPeriod(mxc_tmr_regs_t *tmr, uint32_t per)
{
    // Make sure the new Duty count is less than the period count
    if (tmr->pwm > per) {
        return E_BAD_PARAM;
    }
    
    // Wait for the count to be less than the new dut_cnt
    while (tmr->cnt >= per) {}
    tmr->cmp = per;
    
    return E_NO_ERROR;
}


/* ************************************************************************** */
uint32_t TMR_GetCompare(mxc_tmr_regs_t* tmr)
{
    return tmr->cmp;
}

/* ************************************************************************** */
uint32_t TMR_GetCapture(mxc_tmr_regs_t* tmr)
{
    return tmr->pwm;
}

/* ************************************************************************* */
uint32_t TMR_GetCount(mxc_tmr_regs_t* tmr)
{
    return tmr->cnt;
}

/* ************************************************************************* */
void TMR_IntClear(mxc_tmr_regs_t* tmr)
{
    tmr->intr = MXC_F_TMR_INTR_IRQ_CLR;
}

/* ************************************************************************* */
uint32_t TMR_IntStatus(mxc_tmr_regs_t* tmr)
{
    return tmr->intr;
}

/* ************************************************************************* */
void TMR_SetCompare(mxc_tmr_regs_t *tmr, uint32_t cmp_cnt)
{
    tmr->cmp = cmp_cnt;
}

/* ************************************************************************* */
void TMR_SetCount(mxc_tmr_regs_t *tmr, uint32_t cnt)
{
    tmr->cnt = cnt;
}

/* ************************************************************************* */
int TMR_GetTicks(mxc_tmr_regs_t *tmr, uint32_t time, tmr_unit_t units, uint32_t *ticks)
{
    uint32_t unit_div0, unit_div1;
    uint32_t timerClock;
    uint32_t prescale;
    uint64_t temp_ticks;
    
    timerClock = SYS_TMR_GetFreq(tmr);
    prescale = ((tmr->cn & MXC_F_TMR_CN_PRES) >> MXC_F_TMR_CN_PRES_POS) 
        | (((tmr->cn & MXC_F_TMR_CN_PRES3) >> (MXC_F_TMR_CN_PRES3_POS))<<3);
    
    switch (units) {
        case TMR_UNIT_NANOSEC:
            unit_div0 = 1000000;
            unit_div1 = 1000;
            break;
        case TMR_UNIT_MICROSEC:
            unit_div0 = 1000;
            unit_div1 = 1000;
            break;
        case TMR_UNIT_MILLISEC:
            unit_div0 = 1;
            unit_div1 = 1000;
            break;
        case TMR_UNIT_SEC:
            unit_div0 = 1;
            unit_div1 = 1;
            break;
        default:
            return E_BAD_PARAM;
    }
    
    temp_ticks = (uint64_t)time * (timerClock / unit_div0) / (unit_div1 * (1 << (prescale & 0xF)));
    
    //make sure ticks is within a 32 bit value
    if (!(temp_ticks & 0xffffffff00000000)  && (temp_ticks & 0xffffffff)) {
        *ticks = temp_ticks;
        return E_NO_ERROR;
    }
    
    return E_INVALID;
}

/* ************************************************************************* */
int TMR_GetTime(mxc_tmr_regs_t *tmr, uint32_t ticks, uint32_t *time, tmr_unit_t *units)
{
    uint64_t temp_time = 0;
    uint32_t timerClock = SYS_TMR_GetFreq(tmr);
    uint32_t prescale = ((tmr->cn & MXC_F_TMR_CN_PRES) >> MXC_F_TMR_CN_PRES_POS) 
        | (((tmr->cn & MXC_F_TMR_CN_PRES3) >> (MXC_F_TMR_CN_PRES3_POS))<<3);
    
    temp_time = (uint64_t)ticks * 1000 * (1 << (prescale & 0xF)) / (timerClock / 1000000);
    if (!(temp_time & 0xffffffff00000000)) {
        *time = temp_time;
        *units = TMR_UNIT_NANOSEC;
        return E_NO_ERROR;
    }
    
    temp_time = (uint64_t)ticks * 1000 * (1 << (prescale & 0xF)) / (timerClock / 1000);
    if (!(temp_time & 0xffffffff00000000)) {
        *time = temp_time;
        *units = TMR_UNIT_MICROSEC;
        return E_NO_ERROR;
    }
    
    temp_time = (uint64_t)ticks * 1000 * (1 << (prescale & 0xF)) / timerClock;
    if (!(temp_time & 0xffffffff00000000)) {
        *time = temp_time;
        *units = TMR_UNIT_MILLISEC;
        return E_NO_ERROR;
    }
    
    temp_time = (uint64_t)ticks * (1 << (prescale & 0xF)) / timerClock;
    if (!(temp_time & 0xffffffff00000000)) {
        *time = temp_time;
        *units = TMR_UNIT_SEC;
        return E_NO_ERROR;
    }
    
    return E_INVALID;
}
