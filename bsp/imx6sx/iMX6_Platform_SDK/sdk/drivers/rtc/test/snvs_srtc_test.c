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
#include "rtc/srtc.h"
#include "snvs_srtc_test.h"

static int32_t onetime_tick = 0;

void srtc_one_time_tick_callback(void * arg)
{
    onetime_tick = 1;
}

void srtc_one_time_timer_test(void)
{
    int loop = 0xFFFFFFFF;

    onetime_tick = 0;

    srtc_init();
    
    srtc_setup_onetime_timer(1, srtc_one_time_tick_callback, 0);

    while(loop--)
    {
        if(onetime_tick)
            break;
    }

    if(onetime_tick == 0)
        printf( "SNVS SRTC Timer Test Failed!!\n");
    else
        printf( "SNVS SRTC Timer Test Passed!!\n");

    srtc_deinit();
}

/*!
 * Main unit test for the SRTC.
 * @return  0
 */
int32_t snvs_srtc_test(void)
{
    uint8_t sel;

    printf("Start SNVS SRTC unit tests:");

    do {

        printf("\n  1 - for one time timer test.\n");
        printf("  x - to exit.\n\n");

        do {
            sel = getchar();
        } while (sel == (uint8_t) 0xFF);

        if (sel == 'x') {
            printf("\nTest exit.\n");
            break;
        }

        if (sel == '1')
            srtc_one_time_timer_test();
    } while(1);

    return 0;
}
