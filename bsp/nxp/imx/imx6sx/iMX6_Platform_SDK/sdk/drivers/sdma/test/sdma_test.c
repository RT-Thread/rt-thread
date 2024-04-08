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
#include "sdma_test.h"

static sdma_test_t sdma_tests[] = {
    {"Memory to memory", mem_2_mem_test},
    {"eCSPI1 loopback - shared memory", ecspi_shp_test},
#if (!defined(BOARD_SMART_DEVICE)) && (!defined(BOARD_EVK))    //Since mx6x SD board uses UART1 as debug uart.
    {"UART1 loopback  - shared memory", uart_shp_test},
#endif
    {"UART5 loopback  - perihperal", uart_app_test},
    {"UART5 loopback with interrupt supported", uart_app_interrupt_test},
};

int sdma_test(void)
{
    int retv = FALSE, idx;
    uint8_t sel;

    printf("\n---- Running SDMA test, type 'x' to exit.\n");

    do {
        printf("Please select script type:\n");
        for (idx = 0; idx < (sizeof(sdma_tests) / sizeof(sdma_test_t)); idx++) {
            printf("\t%d - %s\n", idx, sdma_tests[idx].name);
        }
        printf("\tx - to exit.\n");

        do {
            sel = getchar();
        } while (sel == (uint8_t) 0xFF);

        if (sel == 'x') {
            printf("\nTest exit.\n");
            break;
        }

        idx = sel - '0';

        if ((idx >= 0) && (idx < (sizeof(sdma_tests) / sizeof(sdma_test_t)))) {
            printf("\n");
            retv = sdma_tests[idx].test();
            if (retv == TRUE) {
                printf("\n%s test PASSED.\n", sdma_tests[idx].name);
            } else {
                printf("\n%s test FAILED.\n", sdma_tests[idx].name);
            }

        }
    } while (1);

    return retv;
}
