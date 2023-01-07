/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <string.h>
#include <stdio.h>
#include <bl808_mjpeg.h>
#include "bl_cam.h"

#define MJPEG_DEFAULT_ADDR      0x80400000

int bl_cam_mjpeg_buffer_info_get(uint32_t *mjpeg_addr, uint32_t *mjpeg_size)
{
    int ret = 0;
    uint32_t tmpVal;

    *mjpeg_addr = BL_RD_REG(MJPEG_BASE, MJPEG_JPEG_FRAME_ADDR);
    if (*mjpeg_addr == MJPEG_DEFAULT_ADDR) {
        *mjpeg_addr = 0;
        ret = -1;
        goto exit;
    }

    tmpVal = BL_RD_REG(MJPEG_BASE, MJPEG_CONTROL_1);
    tmpVal = BL_GET_REG_BITS_VAL(tmpVal, MJPEG_REG_W_XLEN);
    /*get memory brust size 0 sigle; 1 INCR4; 2 INCR8; 3 INCR16*/
    *mjpeg_size = BL_RD_REG(MJPEG_BASE, MJPEG_JPEG_STORE_MEMORY);
    *mjpeg_size = *mjpeg_size << (3 + tmpVal + (tmpVal > 0 ? 1 : 0));

exit:
    return ret;
}

int bl_cam_mjpeg_get(uint8_t **ptr, uint32_t *len)
{
    int ret = 0;
    MJPEG_Frame_Info mjpeg_info;
    MJPEG_Get_Frame_Info(&mjpeg_info);

    if (mjpeg_info.validFrames > 0) {
        *ptr = (uint8_t *)(uintptr_t)mjpeg_info.curFrameAddr;
        *len = mjpeg_info.curFrameBytes;
    } else {
        ret = -1;
    }
    return ret;
}

int bl_cam_mjpeg_pop(void)
{
    MJPEG_Pop_Frame();
    return 0;
}

