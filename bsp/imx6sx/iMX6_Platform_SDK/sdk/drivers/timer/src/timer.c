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
 * @file timer.c
 * @brief Basic timer functions
 *
 * @ingroup diag_timer
 */

#include <assert.h>
#include "sdk.h"
#include "timer/epit.h"
#include "timer/timer.h"
#include "registers/regsarmglobaltimer.h"
#include "core/ccm_pll.h"

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

static void time_init_global_timer();

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

uint32_t g_microsecondTimerMultiple;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void hal_delay_us(uint32_t usecs)
{
    uint32_t instance = g_system_timer_port;
    if (usecs == 0) {
        return;
    }

    /* enable the counter first */
    epit_counter_enable(instance, usecs, POLLING_MODE);
    
    /* wait for the compare event */
    while (!epit_get_compare_event(instance)) ;
    
    /* disable the counter to save power */
    epit_counter_disable(instance);
}

void system_time_init(void)
{
    uint32_t freq;
    // Init microsecond tick counter.
    time_init_global_timer();
    
    /* EPIT1 is used for the delay function */
    /* Initialize the EPIT timer used for system time functions */
    /* typical IPG_CLK is in MHz, so divide it to get a reference
       clock of 1MHz => 1us per count */
    freq = get_main_clock(IPG_CLK);
    epit_init(g_system_timer_port, CLKSRC_IPG_CLK, freq / 1000000,
              SET_AND_FORGET, 1000, WAIT_MODE_EN | STOP_MODE_EN);
}

//! Init the ARM global timer to a microsecond-frequency clock.
void time_init_global_timer()
{
    // The ARM private peripheral clock is half the CPU clock.
    uint32_t periphClock = get_main_clock(CPU_CLK) / 2;
    uint32_t prescaler = (periphClock / 1000000) - 1;
    
    // Divide down the prescaler until it fits into 8 bits. We add up the number of ticks
    // it takes to equal a microsecond interval.
    g_microsecondTimerMultiple = 1;
    while (prescaler > 0xff)
    {
        prescaler /= 2;
        ++g_microsecondTimerMultiple;
    }
    
    // Make sure the timer is off.
    HW_ARMGLOBALTIMER_CONTROL.B.TIMER_ENABLE = 0;
    
    // Clear counter.
    HW_ARMGLOBALTIMER_COUNTERn_WR(0, 0);
    HW_ARMGLOBALTIMER_COUNTERn_WR(1, 0);
    
    // Set prescaler and clear other flags.
    HW_ARMGLOBALTIMER_CONTROL_WR(BF_ARMGLOBALTIMER_CONTROL_PRESCALER(prescaler));
    
    // Now turn on the timer.
    HW_ARMGLOBALTIMER_CONTROL.B.TIMER_ENABLE = 1;
}

uint64_t time_get_microseconds()
{
    // First read upper.
    uint32_t upper = HW_ARMGLOBALTIMER_COUNTERn_RD(1);
    uint32_t lower;
    
    while (true)
    {
        // Read lower.
        lower = HW_ARMGLOBALTIMER_COUNTERn_RD(0);
        
        // Read upper again.
        uint32_t newUpper = HW_ARMGLOBALTIMER_COUNTERn_RD(1);
        
        // If the first and second read of the upper bits are the same, then return.
        if (newUpper == upper)
        {
            return (((uint64_t)upper << 32) | (uint64_t)lower) / g_microsecondTimerMultiple;
        }
        
        // Otherwise, start over again.
        upper = newUpper;
    }
    
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////

