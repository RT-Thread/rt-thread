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
 * @file sensor_capture.c
 * @brief camera sensor capture and display test.
 * @ingroup diag_camera
 */

#if defined(BOARD_EVB) || defined(BOARD_SABRE_AI)

#include <stdio.h>
#include "ipu/ipu_common.h"
#include "camera/camera_def.h"
#include "video/adv7180_def.h"

int32_t adv7180_capture(void)
{
    int32_t ipu_index = 1;
    int adv7180_std, gated_mode, csi_interface;
    ips_dev_panel_t *panel;
    video_fmt_t *in_fmt;
    uint8_t revchar;
    int32_t ret = TEST_PASSED;

    printf("Please plug automotive port card and evb board onto the armadillo board.\n");
    ipu1_iomux_config();

    /*step 1: enable panel */
    panel = search_panel("HannStar XGA LVDS");
    panel->panel_init(&ipu_index);

    /*step 2: setup adv7180 */
    ret = adv7180_init();
    if (ret != TEST_PASSED)
        return ret;

    adv7180_std = adv7180_get_std();
    gated_mode = adv7180_is_interlaced_mode();

    if ((adv7180_std == ADV7180_NTSC) && (gated_mode == 1)) {
        csi_interface = CSI_BT656_NTSC_INTERLACED;  /*interlaced BT656 */
    } else if ((adv7180_std == ADV7180_PAL) && (gated_mode == 1)) {
        csi_interface = CSI_BT656_PAL_INTERLACED;   /*interlaced BT656 */
    } else {
        printf("Not supported BT656 input!\n");
        return TEST_FAILED;
    }
    in_fmt = &video_fmts[adv7180_std];

    printf("Do you want to enable deinterlace processing? y or n\n");
    do {
        revchar = (uint8_t) getchar();
    } while (revchar == (uint8_t) 0xFF);
    if (revchar == 'y' || revchar == 'Y') {
        csi_vdi_direct_path = 1;
    } else {
        csi_vdi_direct_path = 0;
    }

    /*step 3: setup IPU: from csi to display */
    ipu_sw_reset(ipu_index, 1000);

    ipu_capture_setup(ipu_index, csi_interface, in_fmt->raw_width, in_fmt->raw_height,
                      in_fmt->active_width, in_fmt->active_height, panel);
    ipu_enable_display(ipu_index);

    printf("Do you see the captured image (y or n)?\n");
    do {
        revchar = getchar();
    } while (revchar == (uint8_t) 0xFF);
    if (!(revchar == 'Y' || revchar == 'y'))
        return TEST_FAILED;

    return TEST_PASSED;
}
#endif
