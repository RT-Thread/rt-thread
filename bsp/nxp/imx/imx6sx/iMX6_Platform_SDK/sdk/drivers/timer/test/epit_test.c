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
 * @file epit_test.c
 * @brief EPIT unit tests source file.
 *
 * @ingroup diag_timer
 */

#include <stdio.h>
#include "timer/epit.h"
#include "timer/timer.h"
#include "epit_test.h"
#include "registers/regsepit.h"

static volatile uint8_t g_wait_for_irq;

/*!
 * Main unit test for the EPIT.
 * @return  0
 */
int32_t epit_test(void)
{
    uint8_t sel;

    printf("Start EPIT unit tests:");

    do {
        printf("\n  1 - for delay test.\n");
        printf("  2 - for tick test.\n");
        printf("  x - to exit.\n\n");

        do {
            sel = getchar();
        } while (sel == (uint8_t) NONE_CHAR);

        if (sel == 'x') {
            printf("\nTest exit.\n");
            break;
        }

        if (sel == '1')
            epit_delay_test();
        if (sel == '2')
            epit_tick_test();

    } while(1);

    return 0;
}

/*!
 * This test uses the system delay function that uses the EPIT counter.
 * The EPIT is configure into timer.c.
 * Whenever a second has passed, it displays the elapsed number of seconds.
 */
void epit_delay_test(void)
{
    uint32_t counter = 0;
    /* stops after xx seconds */
    uint32_t max_duration = 10;

    printf("This test displays the elapsed number of second.\n");
    printf("The test exists after %d seconds.\n",max_duration);

    while (counter != max_duration) {        
        hal_delay_us(1000000);
        counter++;
        printf("%ds\n",counter);
    };
}

/* epit instance for system tick */
static uint32_t epit_instance = HW_EPIT2;

/*! 
 * Tick timer interrupt handler.
 */
void tick_timer_interrupt_routine(void)
{
    g_wait_for_irq = 0;
    /* clear the compare event flag */
    epit_get_compare_event(epit_instance);
}

/*!
 * The EPIT is programmed to generate an interrupt every 10ms.
 * It emulates an system tick timer. A counter is increased at every tick.
 * Whenever a second has passed, it displays the counter value.
 */
void epit_tick_test(void)
{
    uint32_t counter = 0;
    /* stops after xx seconds */
    uint32_t max_duration = 10;
    uint32_t freq = 0;

    printf("EPIT is programmed to generate an interrupt every 10ms as a tick timer.\n");
    printf("The test exits after %d seconds.\n",max_duration);

    /* Initialize the EPIT timer used for tick timer. An interrupt
       is generated every 10ms */
    /* typical IPG_CLK is in MHz, so divide it to get a reference
       clock of 1MHz => 1us per count */
    freq = get_main_clock(IPG_CLK);
    epit_init(epit_instance, CLKSRC_IPG_CLK, freq/1000000,
              SET_AND_FORGET, 10000, WAIT_MODE_EN | STOP_MODE_EN);
    epit_setup_interrupt(epit_instance, tick_timer_interrupt_routine, TRUE);
    epit_counter_enable(epit_instance, 10000, IRQ_MODE);

    while ((counter/100) != max_duration) {
        g_wait_for_irq = 1;
        while (g_wait_for_irq == 1);
        counter++;

        if (!(counter%100)) 
            printf("Elapsed time %d seconds <=> %d ticks.\n", counter/100, counter);
    };

    epit_counter_disable(epit_instance);
}
