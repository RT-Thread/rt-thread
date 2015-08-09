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
#include "camera/camera_def.h"
#include "lcdif/lcdif_common.h"

/*!
 * camera sensor display and capture test.
 *
 * @return error information
 */
int32_t csi_sensor_capture(void)
{
    camera_profile_t *sensor;
    uint8_t revchar;
    int32_t ret = TEST_PASSED;

    /*step 1: setup CSI: from csi --> pxp --> display */
    lcdif_display_setup();
    pxp_csc_process();
    csi_setup();

    /*step 2: setup sensor */
    sensor = sensor_search();
    if (sensor == NULL)
        return TEST_FAILED;
    sensor_config(sensor);

    /*step 3: clear RxFIFO and stream on sensor */
    csi_streamon();

    printf("Do you see the captured image (y or n)?\n");
    do {
        revchar = getchar();
    } while (revchar == (uint8_t) 0xFF);
    if (!(revchar == 'Y' || revchar == 'y')) {
        ret = TEST_FAILED;
        goto err;
    }

  err:
    /* step4: before exiting test, make sensor to standby and disable pxp */
    pxp_disable();
    csi_streamoff();
    return ret;
}
