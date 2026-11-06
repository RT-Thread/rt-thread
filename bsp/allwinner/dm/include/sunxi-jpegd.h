/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __SUNXI_JPEGD_H__
#define __SUNXI_JPEGD_H__

#include <rtthread.h>

/*
 * Buffers passed to the VE must be allocated by a VE codec device. This keeps
 * the CPU address and DMA address paired on both MMU and no-MMU systems.
 */
struct sunxi_jpegd_buffer
{
    void *virt_addr;
    rt_ubase_t phys_addr;
    rt_size_t size;
};

enum sunxi_jpegd_format
{
    SUNXI_JPEGD_FORMAT_NV12,
    SUNXI_JPEGD_FORMAT_YV12,
    SUNXI_JPEGD_FORMAT_MB32_420,
};

struct sunxi_jpegd_decode
{
    struct sunxi_jpegd_buffer *input;
    struct sunxi_jpegd_buffer *output;
    rt_size_t input_size;
    rt_tick_t timeout;

    rt_uint16_t width;
    rt_uint16_t height;
    rt_uint16_t stride;
    rt_uint16_t format;
    rt_size_t luma_size;
};

struct sunxi_jpegd_info
{
    struct sunxi_jpegd_buffer *input;
    rt_size_t input_size;

    rt_uint16_t width;
    rt_uint16_t height;
    rt_uint16_t stride;
    rt_uint16_t format;
    rt_size_t luma_size;
    rt_size_t output_size;
};

#define SUNXI_JPEGD_CMD_ALLOC_BUFFER \
    (RT_DEVICE_CTRL_BASE(Char) + 0)
#define SUNXI_JPEGD_CMD_FREE_BUFFER \
    (RT_DEVICE_CTRL_BASE(Char) + 1)
#define SUNXI_JPEGD_CMD_DECODE \
    (RT_DEVICE_CTRL_BASE(Char) + 2)
#define SUNXI_JPEGD_CMD_GET_VERSION \
    (RT_DEVICE_CTRL_BASE(Char) + 3)
#define SUNXI_JPEGD_CMD_GET_INFO \
    (RT_DEVICE_CTRL_BASE(Char) + 4)

#endif /* __SUNXI_JPEGD_H__ */
