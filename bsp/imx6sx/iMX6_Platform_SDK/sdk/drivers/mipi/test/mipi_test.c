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

/*!
 * @file mipi_test.c
 * @brief Main mipi test.
 * @ingroup diag_mipi
 */

#include <stdio.h>
#include "sdk.h"

extern int32_t mipi_csi2_test(void);
extern int32_t mipi_dsi_test(void);

typedef struct {
    const char *name;
     int32_t(*test) (void);
} mipi_test_t;

static mipi_test_t mipi_tests[] = {
    {"mipi csi-2", mipi_csi2_test},
    {"mipi dsi test", mipi_dsi_test},
};

int32_t mipi_test(void)
{
    int32_t retv = TRUE, i;
    int32_t test_num = sizeof(mipi_tests) / sizeof(mipi_test_t);
    uint8_t revchar;

    printf("\nStart mipi test\n");

    do {
        for (i = 0; i < test_num; i++) {
            printf("\t%d - %s\n", i, mipi_tests[i].name);
        }
        printf("\tx - to exit.\n");

        do {
            revchar = (uint8_t) getchar();
        } while (revchar == (uint8_t) 0xFF);
        if (revchar == 'x') {
            printf("\nmipi test exit.\n");
            break;
        }
        i = revchar - '0';

        if ((i >= 0) && (i < test_num)) {
            retv = mipi_tests[i].test();
            if (retv == TEST_PASSED) {
                printf("\n%s test PASSED.\n", mipi_tests[i].name);
            } else {
                printf("\n%s test FAILED.\n", mipi_tests[i].name);
            }

        }
    } while (1);

    return retv;
}
