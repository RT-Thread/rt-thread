/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DRV_OV7670_H__
#define __DRV_OV7670_H__

#include <rtdevice.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OV7670_DEVICE_NAME              "ov7670"
#define OV7670_WIDTH                    320U
#define OV7670_HEIGHT                   240U
#define OV7670_BYTES_PER_PIXEL          2U
#define OV7670_FRAME_SIZE               (OV7670_WIDTH * OV7670_HEIGHT * \
                                         OV7670_BYTES_PER_PIXEL)

#define OV7670_CTRL_GET_INFO            (RT_DEVICE_CTRL_BASE(Miscellaneous) + 1)

enum ov7670_pixel_format
{
    OV7670_PIXEL_FORMAT_RGB565 = 0,
};

struct ov7670_info
{
    rt_uint16_t width;
    rt_uint16_t height;
    rt_uint32_t frame_size;
    rt_uint32_t pixel_format;
    rt_uint32_t xclk_hz;
    rt_uint8_t pid;
    rt_uint8_t ver;
};

#ifdef __cplusplus
}
#endif

#endif /* __DRV_OV7670_H__ */
