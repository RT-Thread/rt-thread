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
 * @file csi_test_mode.c
 * @brief camera sensor works in test mode and display on LVDS test.
 * @ingroup diag_camera
 */

#include <stdio.h>
#include "ipu/ipu_common.h"
#include "camera/camera_def.h"
#include "iomux_config.h"
#include "registers/regsipu.h"

extern int csi_dma_band_mode;
/*!
 * camera sensor works in test mode and display on LVDS.
 *
 * @return error information
 */
int32_t csi_test_mode(void)
{
    int32_t ipu_index = 1, count = 0;
    ips_dev_panel_t *panel;
    int32_t width = 640, height = 480;
    uint8_t revchar;

    /*step 1: enable panel */
    panel = search_panel("HannStar XGA LVDS");
    panel->panel_init(&ipu_index);

    /*step 2: setup IPU: from csi to display */
    ipu1_iomux_config();
    ipu_sw_reset(ipu_index, 1000);
    printf("Do you want to enable band mode (y or n)?\n");
    printf("Note in band mode the whole frame is split into pieces ");
    printf("and it is useful in memory limited system.\n");
    do {
        revchar = getchar();
    } while (revchar == (uint8_t) 0xFF);
    if ((revchar == 'Y' || revchar == 'y')) {
        csi_dma_band_mode = 1;
    } else {
        csi_dma_band_mode = 0;
    }
    ipu_capture_setup(ipu_index, CSI_TEST_MODE, width, height, width, height, panel);

    /*step 4: enable ipu display channel */
    ipu_enable_display(ipu_index);

    printf("Do you see the chessboard of test mode on LVDS panel(y or n)?\n");
    do {
        revchar = getchar();
    } while (revchar == (uint8_t) 0xFF);
    if (!(revchar == 'Y' || revchar == 'y')) {
        return TEST_FAILED;
    }

    printf("Press 'x/X' key on your computer to exit this test\n");
    while (1) {
        revchar = uart_getchar(g_debug_uart_port);
        if (revchar == 'X' || revchar == 'x')
            break;

        ipu_csi_test_mode_color(ipu_index, (count++) % 8);
        hal_delay_us(1000000);
    }

    ipu_capture_streamoff(ipu_index);
    return TEST_PASSED;
}
