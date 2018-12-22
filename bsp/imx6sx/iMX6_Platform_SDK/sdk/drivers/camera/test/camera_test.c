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
 * @file camera_test.c
 * @brief Main camera test.
 * @ingroup diag_camera
 */

#include <stdio.h>
#include "sdk.h"

const char g_camera_test_name[] = "Camera Test";

extern int32_t csi_sensor_capture(void);
extern int32_t sensor_capture(void);
extern int32_t adv7180_capture(void);
extern int32_t csi_test_mode(void);

typedef struct {
    const char *name;
     int32_t(*test) (void);
} camera_test_t;

static camera_test_t camera_tests[] = {
#if defined(BOARD_SMART_DEVICE)
    {"Sensor capture", sensor_capture},
#endif
#if defined(BOARD_EVB)||defined(BOARD_SABRE_AI)
    {"adv7180 capture", adv7180_capture},
#endif
#if defined(CHIP_MX6SL)
    {"Sensor capture", csi_sensor_capture},
#else
    {"test mode", csi_test_mode},
#endif
};

#if !defined(CHIP_MX6SL)
extern int csi_dma_band_mode;
#endif
test_return_t camera_test(void)
{
    int32_t retv = TEST_FAILED;
    int32_t i;
    int32_t test_num = sizeof(camera_tests) / sizeof(camera_test_t);
    uint8_t revchar;

    printf("\nStart camera test\n");

    do {
#if !defined(CHIP_MX6SL)
        csi_dma_band_mode = 0;
#endif
        for (i = 0; i < test_num; i++) {
            printf("\t%d - %s\n", i, camera_tests[i].name);
        }
        printf("\tx - to exit.\n");

        do {
            revchar = (uint8_t) getchar();
        } while (revchar == (uint8_t) 0xFF);
        if (revchar == 'x') {
            printf("\nCamera test exit.\n");
            break;
        }
        i = revchar - '0';

        if ((i >= 0) && (i < test_num)) {
            retv = camera_tests[i].test();
            if (retv == TEST_PASSED) {
                printf("\n%s test PASSED.\n\n", camera_tests[i].name);
            } else {
                printf("\n%s test FAILED.\n\n", camera_tests[i].name);
            }

        }
    } while (1);

    return retv;
}
