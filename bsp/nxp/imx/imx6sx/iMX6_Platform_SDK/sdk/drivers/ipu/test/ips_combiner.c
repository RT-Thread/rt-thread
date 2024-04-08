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
 * @file ips_combiner.c
 * @brief IPU combiner test.
 * @ingroup diag_ipu
 */

#include <string.h>
#include <stdio.h>

#include "ips_test.h"

int32_t ips_combiner_test(ips_dev_panel_t * panel)
{
    uint32_t ipu_index = 1;     // use ipu 1
    uint32_t fg_width = 600, fg_height = 100;
    uint32_t fg_xp, fg_yp;
    uint8_t alpha = 0;
    uint8_t revchar;

    printf("\n-- Combiner Test ---\n");
    /*reset IPU */
    ipu_sw_reset(ipu_index, 1000);

    /*setup IPU dual display channel, enable partial plane */
    fg_xp = (panel->width - fg_width) / 2;
    fg_yp = panel->height - 300;
    ipu_dual_display_setup(ipu_index, panel, INTERLEAVED_RGB565, fg_width, fg_height, fg_xp, fg_yp,
                           alpha);

    /*enable ipu display channel */
    ipu_enable_display(ipu_index);

    /*load background image */
    load_centralized_image(CH23_EBA0, panel);
    /*load foreground image */
    load_foreground_image(CH27_EBA0, fg_width, fg_height);

    printf("Transparency:\tPress '+' to increase / '-' to decrease\n");
    printf("Position:\tPress 'L' to move left / 'R' to right / 'D' to down / 'U' to up\n");
    printf("Other key to exit.\n");
    while (1) {
        do {
            revchar = getchar();
        } while (revchar == (uint8_t) 0xFF);
        if (revchar == '+' || revchar == '=') {
            if (alpha > 245)
                alpha = 255;
            else
                alpha += 10;
        } else if (revchar == '-' || revchar == '_') {
            if (alpha <= 10)
                alpha = 0;
            else
                alpha -= 10;
        } else if (revchar == 'r' || revchar == 'R') {
            if (fg_xp > (panel->width - 20 - fg_width))
                fg_xp = panel->width - fg_width;
            else
                fg_xp += 20;
        } else if (revchar == 'l' || revchar == 'L') {
            if (fg_xp <= 20)
                fg_xp = 0;
            else
                fg_xp -= 20;
        } else if (revchar == 'd' || revchar == 'D') {
            if (fg_yp > (panel->height - 20 - fg_height))
                fg_yp = panel->height - fg_height;
            else
                fg_yp += 20;
        } else if (revchar == 'u' || revchar == 'U') {
            if (fg_yp <= 20)
                fg_yp = 0;
            else
                fg_yp -= 20;
        } else
            break;

        ipu_dp_config(ipu_index, NO_CSC, 1, fg_xp, fg_yp, alpha);
    }

    return TRUE;
}
