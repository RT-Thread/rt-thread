/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __SUNXI_JPEGE_H__
#define __SUNXI_JPEGE_H__

#include <sunxi-jpegd.h>

/*
 * The VE encoder consumes contiguous NV12 frames. Buffers must be allocated
 * by either jpegd or jpege so their CPU and DMA addresses remain paired.
 */
struct sunxi_jpege_encode
{
    struct sunxi_jpegd_buffer *input;
    struct sunxi_jpegd_buffer *output;
    rt_tick_t timeout;
    rt_size_t output_size;

    rt_uint16_t width;
    rt_uint16_t height;
    rt_uint16_t stride;
    rt_uint16_t format;
    rt_uint8_t quality;
};

#define SUNXI_JPEGE_CMD_ALLOC_BUFFER \
    SUNXI_JPEGD_CMD_ALLOC_BUFFER
#define SUNXI_JPEGE_CMD_FREE_BUFFER \
    SUNXI_JPEGD_CMD_FREE_BUFFER
#define SUNXI_JPEGE_CMD_ENCODE \
    (RT_DEVICE_CTRL_BASE(Char) + 2)
#define SUNXI_JPEGE_CMD_GET_VERSION \
    SUNXI_JPEGD_CMD_GET_VERSION

#endif /* __SUNXI_JPEGE_H__ */
