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
#include <stdio.h>
#include "sdk.h"
#include "wdog/watchdog.h"

/************************************************** Static Function ***********************************************/
static void watchdog_reset(void)
{
    watchdog_reg_p base = (watchdog_reg_p) WDOG1_BASE_ADDR;
    char stop_feeding;
    uint8_t ch;
    int i = 0;

    printf("\n---- Running WatchDog test. Type 'y' to continue.\n");

    do {
        ch = getchar();
    } while (ch == (uint8_t) 0xFF);

    if ((ch != 'Y') && (ch != 'y')) {
        printf("\nTest exit.\n");
        return;
    }

    printf("Power reset...\n");

    /* Init Watchdog */
    base->wcr = WCR_WDA | WCR_SRS | WCR_WT | WCR_WDBG;

    printf
        ("watch dog is running,and system will reset in 2 seconds if you stop feeding dog.Stop feeding dog ?(Y or N)\n");
    /*enable watchdog */
    base->wcr |= WCR_WDE;
    /* Infinite loop */
    while (1) {
        stop_feeding = getchar();
        if (stop_feeding!='Y' && stop_feeding!='y') {
            if (i % 2 == 0)
                base->wsr = 0x5555;
            else
                base->wsr = 0xAAAA;
            i++;
        } else {
            printf("reboot\n");
            while (1) ;
        }
    }
}

/************************************************** Global Function ***********************************************/

int wdog_test(void)
{
    int retv = FALSE;

    watchdog_reset();

    return retv;
}
