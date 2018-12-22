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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vpu_test.h"
#include "sdk.h"
#include "vpu/vpu_debug.h"
#include "vpu/vpu_util.h"
#include "core/cortex_a9.h"
#include "core/mmu.h"

extern void print_media_fat_info(uint32_t);

#define DeviceNum 0

vpu_resource_t vpu_resource = { 0 };
struct decode *g_dec_instance[MAX_NUM_INSTANCE];
struct encode *g_enc_instance[MAX_NUM_INSTANCE];
int32_t g_disp_clr_index[MAX_NUM_INSTANCE];
int32_t g_multi_instance = 1;

static vpu_test_t vpu_tests[] = {
    {"VPU DECODER TEST", decode_test},
    {"VPU ENCODER TEST", encode_test},
};

int vpu_test(void)
{
    int32_t err = 0, i = 0;
    vpu_versioninfo ver;
    uint8_t revchar;
    int32_t test_num = sizeof(vpu_tests) / sizeof(vpu_test_t);

    /*instance attached to display interface */
    config_system_parameters();

    /* enable L1 cache for mx6dq and mx6sdl */
    arm_icache_enable();
    arm_dcache_invalidate();
    mmu_enable();
    arm_dcache_enable();

    set_card_access_mode(1, 0);

    /* FAT filesystem setup from SD card */
    if (FSInit(NULL, bufy, maxdevices, maxhandles, maxcaches) != SUCCESS) {
        err = -1;
        printf("Fail to initialize the filesystem\n");
    }
    /*init the drive */
    FSDriveInit(DeviceNum);
    SetCWDHandle(DeviceNum);

    g_current_active_instance = 0;

    /* initialize VPU */
    framebuf_init();

    err = VPU_Init();
    if (err) {
        err_msg("VPU Init Failure.\n");
        return -1;
    }

    err = VPU_GetVersionInfo(&ver);
    if (err) {
        err_msg("Cannot get version info\n");
        VPU_UnInit();
        return -1;
    }

    info_msg("VPU firmware version: %d.%d.%d\n", ver.fw_major, ver.fw_minor, ver.fw_release);

    do {
        for (i = 0; i < test_num; i++)
            printf("\t%d - %s\n", i, vpu_tests[i].name);
        printf("\tx - to exit.\n");
        revchar = 0xFF;

        revchar = 0xFF;
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
            err = vpu_tests[i].test(NULL);
            vpu_codec_io_deinit();
        }
    } while (1);

    VPU_UnInit();

    return 0;
}
