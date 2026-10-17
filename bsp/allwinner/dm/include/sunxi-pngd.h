/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __SUNXI_PNGD_H__
#define __SUNXI_PNGD_H__

#include <sunxi-jpegd.h>

/*
 * The PNG decoder consumes a complete PNG stream and writes RGBA8888 pixels.
 * Both buffers must be allocated by one of the VE codec devices.
 */
enum sunxi_pngd_format
{
    SUNXI_PNGD_FORMAT_RGBA8888,
};

struct sunxi_pngd_info
{
    struct sunxi_jpegd_buffer *input;
    rt_size_t input_size;

    rt_uint32_t width;
    rt_uint32_t height;
    rt_uint32_t stride;
    rt_uint32_t format;
    rt_size_t output_size;
};

struct sunxi_pngd_decode
{
    struct sunxi_jpegd_buffer *input;
    struct sunxi_jpegd_buffer *output;
    rt_size_t input_size;
    rt_tick_t timeout;

    rt_uint32_t width;
    rt_uint32_t height;
    rt_uint32_t stride;
    rt_uint32_t format;
};

#define SUNXI_PNGD_CMD_ALLOC_BUFFER \
    SUNXI_JPEGD_CMD_ALLOC_BUFFER
#define SUNXI_PNGD_CMD_FREE_BUFFER \
    SUNXI_JPEGD_CMD_FREE_BUFFER
#define SUNXI_PNGD_CMD_DECODE \
    (RT_DEVICE_CTRL_BASE(Char) + 2)
#define SUNXI_PNGD_CMD_GET_VERSION \
    SUNXI_JPEGD_CMD_GET_VERSION
#define SUNXI_PNGD_CMD_GET_INFO \
    (RT_DEVICE_CTRL_BASE(Char) + 4)

#endif /* __SUNXI_PNGD_H__ */
