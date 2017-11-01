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
 * @file snvs_rtc_test.c
 * @brief SNVS RTC unit tests source file.
 *
 * @ingroup diag_timer
 */

#include <stdio.h>
#include "sdk.h"
#include "rtc/rtc.h"
#include "snvs_rtc_test.h"

static int32_t onetime_tick = 0;
static int32_t periodic_tick = 0;

void one_time_tick_callback(void * arg)
{
    onetime_tick = 1;
}

void periodic_tick_callback(void * arg)
{
    periodic_tick ++;
    if(periodic_tick > 10)
        rtc_deinit();
}

void one_time_timer_test(void)
{
    int loop = 0xFFFFFF;

    onetime_tick = 0;

    rtc_init();
    
    rtc_setup_onetime_timer(10, one_time_tick_callback, 0);

    while(loop--)
    {
        if(onetime_tick)
            break;
    }

    if(onetime_tick == 0)
        printf( "SNVS RTC Timer Test Failed!!\n");
    else
        printf( "SNVS RTC Timer Test Passed!!\n");

    rtc_deinit();
}

void periodic_timer_test(void)
{
    int loop = 0xFFFFFF;

    periodic_tick = 0;

    rtc_init();
    
    rtc_setup_periodic_timer(2, periodic_tick_callback, 0);

    while(loop--)
    {
        if(periodic_tick > 10)
            break;
    }

    if(periodic_tick == 0)
        printf( "SNVS RTC Periodic Test Failed!!\n");
    else
        printf( "SNVS RTC Periodic Test Passed with %d periodic interrupts!!\n", periodic_tick);

    rtc_deinit();
}

/*!
 * Main unit test for the RTC.
 * @return  0
 */
int32_t snvs_rtc_test(void)
{
    uint8_t sel;

    printf("Start SNVS RTC unit tests:");

    do {

        printf("\n  1 - for one time timer test.\n");
        printf("  2 - for periodic timer test.\n");
        printf("  x - to exit.\n\n");

        do {
            sel = getchar();
        } while (sel == (uint8_t) 0xFF);

        if (sel == 'x') {
            printf("\nTest exit.\n");
            break;
        }

        if (sel == '1')
            one_time_timer_test();
        if (sel == '2')
            periodic_timer_test();

    } while(1);

    return 0;
}
