/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * @file epit.c
 * @brief EPIT driver source file.
 *
 * @ingroup diag_timer
 */

#include "timer/epit.h"
#include "timer/timer.h"
#include "core/interrupt.h"
#include "core/ccm_pll.h"
#include "registers/regsepit.h"

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void epit_reload_counter(uint32_t instance, uint32_t load_val)
{
    // set the load register especially if RLD=reload_mode=SET_AND_FORGET=1 
    HW_EPIT_LR_WR(instance, load_val);
}

uint32_t epit_get_counter_value(uint32_t instance)
{
    return HW_EPIT_CNR_RD(instance);
}

void epit_set_compare_event(uint32_t instance, uint32_t compare_val)
{
    HW_EPIT_CMPR_WR(instance, compare_val);
}

uint32_t epit_get_compare_event(uint32_t instance)
{
    uint32_t status_register;

    // get the status 
    status_register = HW_EPIT_SR_RD(instance);
    
    // clear it if found set 
    if (status_register & BM_EPIT_SR_OCIF)
    {
        HW_EPIT_SR_SET(instance, BM_EPIT_SR_OCIF);
    }

    // return the read value before the bit was cleared 
    return status_register & BM_EPIT_SR_OCIF;
}

void epit_counter_disable(uint32_t instance)
{
    /* temporary workaround for the discovered issue when disabling the
     * counter during end of count/reload/set compare flag ??.
     * Set to the max value so that it ensures that the counter couldn't
     * reach 0 when it is disabled.
     */
    HW_EPIT_LR_WR(instance, 0xFFFFFFFF);

    // disable the counter 
    HW_EPIT_CR_CLR(instance, BM_EPIT_CR_EN);

    // ensure to leave the counter in a proper state
    // by disabling the output compare interrupt
    HW_EPIT_CR_CLR(instance, BM_EPIT_CR_OCIEN);
    
    // and clearing possible remaining compare event 
    HW_EPIT_SR_SET(instance, BM_EPIT_SR_OCIF);
}

void epit_counter_enable(uint32_t instance, uint32_t load_val, uint32_t irq_mode)
{
    // set the load register especially if RLD=reload_mode=SET_AND_FORGET=1
    // and if the value is different from 0 which is the lowest counter value
    if (load_val != 0)
    {
        HW_EPIT_LR_WR(instance, load_val);
    }

    // ensure to start the counter in a proper state
    // by clearing possible remaining compare event
    HW_EPIT_SR_SET(instance, BM_EPIT_SR_OCIF);

    // set the mode when the output compare event occur: IRQ or polling 
    if (irq_mode == IRQ_MODE)
    {
        HW_EPIT_CR_SET(instance, BM_EPIT_CR_OCIEN);
    }
    else
    {
        // polling 
        HW_EPIT_CR_CLR(instance, BM_EPIT_CR_OCIEN);
    }

    // finally, enable the counter 
    HW_EPIT_CR_SET(instance, BM_EPIT_CR_EN);
}

void epit_setup_interrupt(uint32_t instance, void (*irq_subroutine)(void), bool enableIt)
{
    uint32_t irq_id = EPIT_IRQS(instance);

    if (enableIt)
    {    
        // register the IRQ sub-routine 
        register_interrupt_routine(irq_id, irq_subroutine);
        
        // enable the IRQ 
        enable_interrupt(irq_id, CPU_0, 0);
    }
    else
    {
        // disable the IRQ 
        disable_interrupt(irq_id, CPU_0);
    }
}

void epit_init(uint32_t instance, uint32_t clock_src, uint32_t prescaler,
               uint32_t reload_mode, uint32_t load_val, uint32_t low_power_mode)
{
    uint32_t control_reg_tmp = 0;
    uint32_t base = REGS_EPIT_BASE(instance);

    // enable the source clocks to the EPIT port 
    clock_gating_config(base, CLOCK_ON);

    // start with a known state by disabling and reseting the module 
    HW_EPIT_CR_WR(instance, BM_EPIT_CR_SWR);
    
    // wait for the reset to complete 
    while ((HW_EPIT_CR(instance).B.SWR) != 0) ;

    // set the reference source clock for the counter 
    control_reg_tmp |= BF_EPIT_CR_CLKSRC(clock_src);

    // set the counter clock prescaler value - 0 to 4095 
    control_reg_tmp |= BF_EPIT_CR_PRESCALAR(prescaler-1);

    // set the reload mode 
    if (reload_mode == SET_AND_FORGET)
    {
        control_reg_tmp |= BM_EPIT_CR_RLD;
    }

    // set behavior for low power mode 
    if (low_power_mode & WAIT_MODE_EN)
    {
        control_reg_tmp |= BM_EPIT_CR_WAITEN;
    }
    if (low_power_mode & STOP_MODE_EN)
    {
        control_reg_tmp |= BM_EPIT_CR_STOPEN;
    }

    // make the counter start from a known value when enabled, this is loaded from
    // EPITLR register if RLD=reload_mode=1 or 0xFFFFFFFF if RLD=reload_mode=0
    control_reg_tmp |= BM_EPIT_CR_IOVW | BM_EPIT_CR_ENMOD;

    // finally write the control register 
    HW_EPIT_CR_WR(instance, control_reg_tmp);

    // initialize the load register especially if RLD=reload_mode=SET_AND_FORGET=1 
    // and if the value is different from 0 which is the lowest counter value
    if (load_val != 0)
    {
        HW_EPIT_LR_WR(instance, load_val);
    }
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
