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

#include <stdio.h>
#include "ipu/ipu_common.h"
#include "camera/camera_def.h"
#include "iomux_config.h"
#include "registers/regsipu.h"

/*!
 * camera sensor display and capture test.
 *
 * @return error information
 */
int32_t sensor_capture(void)
{
    int32_t ipu_index = 1, read_value = 1;
    ips_dev_panel_t *panel;
    camera_profile_t *sensor;
    uint8_t revchar;
    int32_t ret = TEST_PASSED;

    /*step 1: enable panel */
    panel = search_panel("HannStar XGA LVDS");
    panel->panel_init(&ipu_index);

    /*step 2: setup IPU: from csi to display */
    ipu1_iomux_config();
    ipu_sw_reset(ipu_index, 1000);
    ipu_capture_setup(ipu_index, CSI_PARALLEL, 640, 480, 640, 480, panel);

    /*step 3: setup sensor */
    sensor = sensor_search();
    if (sensor == NULL)
        return TEST_FAILED;
    sensor_config(sensor);

    /*step 4: enable ipu display channel */
    ipu_enable_display(ipu_index);

    /*test 1: capture image from sensor */
    printf("Do you see the captured image (y or n)?\n");
    do {
        revchar = getchar();
    } while (revchar == (uint8_t) 0xFF);
    if (!(revchar == 'Y' || revchar == 'y')) {
        ret = TEST_FAILED;
        goto err;
    }

    /*test 2: sensor auto focus */
    if (sensor->auto_focus_enable) {
        printf("Do you want to test auto focus function? [y/n]\n");
        if (is_input_char('y', NULL)) {
            sensor_autofocus_init(sensor);
            while (is_input_char('y', NULL)) {
                sensor_af_trigger(sensor);
                printf("Do you see the viewfiner in the middle of camera?[y/n]\n");
                if (!is_input_char('y', NULL)) {
                    ret = TEST_FAILED;
                    goto err;
                }
                printf("Trigger more? [y/n]\n");
            }
        }
    }

    /*test 3: sensor standby */
    printf("Do you want to test standby mode? [y/n]\n");
    while (is_input_char('y', NULL)) {
        sensor_standby(read_value);
        if (read_value == 1) {
            printf("Do you see the still camera image? [y/n]\n");
            if (!is_input_char('y', NULL)) {
                ret = TEST_FAILED;
                goto err;
            }
        }
        read_value = 1 - read_value;
        printf("Trigger more? [y/n]\n");
    }

err:
    ipu_capture_streamoff(ipu_index);
    return ret;
}
