/****************************************************************************
*
*    The MIT License (MIT)
*
*    Copyright 2012 - 2020 Vivante Corporation, Santa Clara, California.
*    All Rights Reserved.
*
*    Permission is hereby granted, free of charge, to any person obtaining
*    a copy of this software and associated documentation files (the
*    'Software'), to deal in the Software without restriction, including
*    without limitation the rights to use, copy, modify, merge, publish,
*    distribute, sub license, and/or sell copies of the Software, and to
*    permit persons to whom the Software is furnished to do so, subject
*    to the following conditions:
*
*    The above copyright notice and this permission notice (including the
*    next paragraph) shall be included in all copies or substantial
*    portions of the Software.
*
*    THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
*    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
*    IN NO EVENT SHALL VIVANTE AND/OR ITS SUPPLIERS BE LIABLE FOR ANY
*    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
*    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
*    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
*****************************************************************************/

#include <string.h>

#include "vg_lite.h"

static void _memcpy(void *dst, void *src, int size) {
    int i;
    for (i = 0; i < size; i++) {
        ((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
    }
}

/* Get the plane memory pointer and strides info. */
static uint32_t get_buffer_planes(vg_lite_buffer_t *buffer,
                              uint8_t **memory,
                              uint32_t *strides)
{
    uint32_t count = 1;

    switch (buffer->format) {
        case VG_LITE_RGBA8888:
        case VG_LITE_BGRA8888:
        case VG_LITE_RGBX8888:
        case VG_LITE_BGRX8888:
        case VG_LITE_RGB565:
        case VG_LITE_BGR565:
        case VG_LITE_RGBA4444:
        case VG_LITE_BGRA4444:
        case VG_LITE_BGRA5551:
        case VG_LITE_A8:
        case VG_LITE_L8:
        case VG_LITE_A4:
        case VG_LITE_INDEX_1:
        case VG_LITE_INDEX_2:
        case VG_LITE_INDEX_4:
        case VG_LITE_INDEX_8:
        case VG_LITE_YUYV:
        case VG_LITE_YUY2:
        case VG_LITE_RGBA2222:
            count = 1;
            memory[0] = (uint8_t *)buffer->memory;
            memory[1] = memory[2] = ((uint8_t*)0);
            strides[0] = buffer->stride;
            strides[1] = strides[2] = 0;
            break;

        case VG_LITE_NV12:
        case VG_LITE_NV16:
            count = 2;
            memory[0] = (uint8_t *)buffer->memory;
            memory[1] = (uint8_t *)buffer->yuv.uv_memory;
            memory[2] = 0;
            strides[0] = buffer->stride;
            strides[1] = buffer->yuv.uv_stride;
            strides[2] = 0;
            break;

        case VG_LITE_AYUY2:
            count = 2;
            memory[0] = (uint8_t *)buffer->memory;
            memory[1] = 0;
            memory[2] = (uint8_t *)buffer->yuv.v_memory;
            strides[0] = buffer->stride;
            strides[1] = 0;
            strides[2] = buffer->yuv.alpha_stride;
            break;

        case VG_LITE_ANV12:
            count = 3;
            memory[0] = (uint8_t *)buffer->memory;
            memory[1] = (uint8_t *)buffer->yuv.uv_memory;
            memory[2] = (uint8_t *)buffer->yuv.v_memory;
            strides[0] = buffer->stride;
            strides[1] = buffer->yuv.uv_stride;
            strides[2] = buffer->yuv.alpha_stride;
            break;

        case VG_LITE_YV12:
        case VG_LITE_YV24:
        case VG_LITE_YV16:
            count = 3;
            memory[0] = (uint8_t *)buffer->memory;
            memory[1] = (uint8_t *)buffer->yuv.uv_memory;
            memory[2] = (uint8_t *)buffer->yuv.v_memory;
            strides[0] = buffer->stride;
            strides[1] = buffer->yuv.uv_stride;
            strides[2] = buffer->yuv.v_stride;
            break;

        case VG_LITE_YUY2_TILED:
        case VG_LITE_NV12_TILED:
        case VG_LITE_ANV12_TILED:
        case VG_LITE_AYUY2_TILED:
        default:
            count = 0;

            break;
    }
    return count;
}

vg_lite_error_t vg_lite_buffer_upload(vg_lite_buffer_t  *buffer,
                                      uint8_t           *data[3],
                                      uint32_t           stride[3])
{
    vg_lite_error_t error = VG_LITE_SUCCESS;
    int32_t plane_count;
    uint8_t  *buffer_memory[3] = {((uint8_t*)0)};
    uint32_t  buffer_strides[3] = {0};
    uint8_t  *pdata;
    int32_t i, j;

    /* Get buffer memory info. */
    plane_count = get_buffer_planes(buffer, buffer_memory, buffer_strides);

    if (plane_count > 0 && plane_count <= 3) {
        /* Copy the data to buffer. */
        for (i = 0; i < plane_count;  i++) {
            pdata = data[i];
            for (j = 0; j < buffer->height; j++) {
                _memcpy(buffer_memory[i], pdata, buffer_strides[i]);
                buffer_memory[i] += buffer_strides[i];
                pdata += stride[i];
            }
        }
    }
    else {
        error = VG_LITE_INVALID_ARGUMENT;
    }

    return error;
}
