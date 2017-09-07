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
 * @file ips_test.c
 * @brief Main IPU test.
 * @ingroup diag_ipu
 */

#include <stdio.h>
#include "ips_test.h"
#include "iomux_config.h"
#include "registers/regsipu.h"

static ipu_test_t ipu_tests[] = {
    {"IPU SINGLE DISPLAY TEST", ips_display_test},
    {"IPU COMBINE DISPLAY TEST", ips_combiner_test},
    {"IPU ROTATE TEST", ips_rotate_test},
    {"IPU RESIZE TEST", ips_resize_test},
    {"IPU CSC TEST", ips_csc_test},
};

int32_t ipu_test(void)
{
    int32_t retv = TRUE;
    ips_dev_panel_t *panel;
    uint8_t revchar;
    int32_t test_num = sizeof(ipu_tests) / sizeof(ipu_test_t);
    int32_t i, ipu_index = 1;

    printf("\nStart IPU test\n");
    printf("Note that the Display test is using the Hannstar LVDS panel pluged into LVDS0\n");
    ipu1_iomux_config();

    /*enable panel */
    panel = search_panel("HannStar XGA LVDS");
    panel->panel_init(&ipu_index);

    do {
        for (i = 0; i < test_num; i++)
            printf("\t%d - %s\n", i, ipu_tests[i].name);
        printf("\tx - to exit.\n");

        do {
            revchar = getchar();
        } while (revchar == (uint8_t) 0xFF);
        if (revchar == 'x') {
            printf("\nTest exit.\n");
            break;
        }

        i = revchar - '0';
        if ((i >= 0) && (i < test_num)) {
            printf("\n");
            retv = ipu_tests[i].test(panel);
            if (retv == TRUE)
                printf("\n%s test PASSED.\n\n", ipu_tests[i].name);
            else
                printf("\n%s test FAILED.\n\n", ipu_tests[i].name);
        }
    } while (1);

    return retv;
}
