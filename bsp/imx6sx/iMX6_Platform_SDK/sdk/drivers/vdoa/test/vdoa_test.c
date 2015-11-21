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
#include <stdlib.h>
#include <string.h>

#include "vdoa/vdoa.h"
#include "sdk.h"
#include "registers/regsvdoa.h"
#include <filesystem/fsapi.h>
#include "usdhc/usdhc_ifc.h"

extern void hdmi_1080P60_video_output(int32_t ipu_index, int32_t ipu_di);
extern void print_media_fat_info(uint32_t);

#define DeviceNum 0

#define IMG_WIDTH	1920 
#define IMG_HEIGHT	832

void vdoa_test(void)
{
    uint8_t *buffer = malloc(IMG_WIDTH * IMG_HEIGHT * 1.5 + 0x1000);
	/*the VDOA file is extracted from VPU decoder in tiled frame mode*/
	uint8_t readfile[] = "vdoa_in.yuv";
    int count, err;
    int fin = 0;

    if (buffer == NULL)
        return;

    hdmi_1080P60_video_output(1, 0);
    if (FSInit(NULL, bufy, maxdevices, maxhandles, maxcaches) != SUCCESS) {
        err = -1;
        return;
    }

    FSDriveInit(DeviceNum);
    SetCWDHandle(DeviceNum);

    print_media_fat_info(DeviceNum);

    if ((fin = Fopen(readfile, (uint8_t *) "r")) < 0) {
        printf("cannot open file %s!\n", readfile);
        return;
    }

    buffer = (uint8_t *) (((uint32_t) buffer + 0xFFF) & 0xFFFFF000);

    set_card_access_mode(1, 0);
    
    count = Fread(fin, (uint8_t *) buffer, IMG_WIDTH * IMG_HEIGHT * 1.5);

    vdoa_clear_interrupt();
    vdoa_setup(IMG_WIDTH, IMG_HEIGHT, IMG_WIDTH, IMG_WIDTH, 0, 0, 16, 0);
    vdoa_start((uint32_t) buffer, IMG_WIDTH * IMG_HEIGHT, IPU2_CH23_EBA0, IMG_WIDTH * 1088);

    while (!vdoa_check_tx_eot()) ;
    Fclose(fin);
}
