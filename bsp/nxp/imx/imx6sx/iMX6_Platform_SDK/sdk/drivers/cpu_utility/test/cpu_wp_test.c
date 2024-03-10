/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
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

/*----------------------------------------------------------------------------
		File Includes
----------------------------------------------------------------------------*/
#include "sdk.h"
#include "timer/epit.h"
#include "core/cortex_a9.h"
#include "core/mmu.h"
#include "pmu/pmu_driver.h"
#include "cpu_utility/cpu_utility.h"
#include "registers/regsepit.h"

void my_memcpy(char *dst, char *src, int size)
{
    asm volatile ("push {r3-r6}");
    asm volatile ("loop:");
    asm volatile ("ldmia r1!, {r3-r6}");
    asm volatile ("stmia r0!, {r3-r6}");
    asm volatile ("subs r2, r2, #16");
    asm volatile ("bne loop");
    asm volatile ("pop {r3-r6}");
}

uint32_t memcpy_perf_record(int size)
{
#ifdef CHIP_MX6SL
    char *dst = (char *)0x94000000;
    char *src = (char *)0x98000000;
#else
    char *dst = (char *)0x24000000;
    char *src = (char *)0x28000000;
#endif
    uint32_t time_counter;
    uint32_t epit_instance = HW_EPIT2, epit_freq = 0;

    epit_freq = get_main_clock(IPG_CLK);
    epit_init(epit_instance, CLKSRC_IPG_CLK, epit_freq / 1000000,
              SET_AND_FORGET, 10000, WAIT_MODE_EN | STOP_MODE_EN);
    epit_setup_interrupt(epit_instance, NULL, FALSE);
    epit_counter_enable(epit_instance, 0xFFFFFFFF, 0);   //polling mode

    my_memcpy(dst, src, size);

    time_counter = epit_get_counter_value(epit_instance);
    epit_counter_disable(epit_instance); //polling mode

    time_counter = (0xFFFFFFFF - time_counter) / 1000;  //ms

    return time_counter;
}

int cpu_wp_test(void)
{
    int i = 0;
    uint32_t cpu_freq;
    int time_elapsed = 0;
    int size = 0x1000000;

    if (arm_dcache_state_query() == 1) {
        arm_dcache_flush();
        arm_dcache_invalidate();
        mmu_disable();
        arm_dcache_disable();
    }

    while (i < CPU_WORKPOINT_OUTOFRANGE) {
        cpu_freq = cpu_workpoint_set(i);
        time_elapsed = memcpy_perf_record(size);
        printf(" Copying %dMB data takes %d ms when cpu running at %dMHz\n", size / (1024 * 1024),
               time_elapsed, cpu_freq);
        hal_delay_us(3000);
        i++;
    }
    
    // Restore to default workpoint.
    cpu_workpoint_set(CPU_WORKPOINT_800MHZ);

    return 0;
}

