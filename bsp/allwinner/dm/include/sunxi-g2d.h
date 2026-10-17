/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __SUNXI_G2D_H__
#define __SUNXI_G2D_H__

#include <rtthread.h>

struct sunxi_g2d_buffer
{
    void *virt_addr;
    rt_ubase_t phys_addr;
    rt_size_t size;
};

/*
 * A G2D-200 RCQ block starts with an array of these 16-byte headers.
 * The register data addressed by a header must live in the same DMA buffer.
 */
struct sunxi_g2d_rcq_header
{
    rt_uint32_t data_address;
    rt_uint32_t data_length_high;
    rt_uint32_t control;
    rt_uint32_t register_offset;
};

struct sunxi_g2d_rcq_submit
{
    struct sunxi_g2d_buffer *buffer;
    rt_uint32_t header_offset;
    rt_uint16_t header_count;
    rt_tick_t timeout;
};

enum sunxi_g2d_format
{
    SUNXI_G2D_FORMAT_ARGB8888,
    SUNXI_G2D_FORMAT_ABGR8888,
    SUNXI_G2D_FORMAT_RGBA8888,
    SUNXI_G2D_FORMAT_BGRA8888,
    SUNXI_G2D_FORMAT_XRGB8888,
    SUNXI_G2D_FORMAT_XBGR8888,
    SUNXI_G2D_FORMAT_RGB888,
    SUNXI_G2D_FORMAT_BGR888,
    SUNXI_G2D_FORMAT_RGB565,
    SUNXI_G2D_FORMAT_BGR565,
    SUNXI_G2D_FORMAT_ARGB4444,
    SUNXI_G2D_FORMAT_ARGB1555,
    SUNXI_G2D_FORMAT_NV12,
    SUNXI_G2D_FORMAT_NV21,
    SUNXI_G2D_FORMAT_I420,
    SUNXI_G2D_FORMAT_YUYV,
    SUNXI_G2D_FORMAT_MAX,
};

enum sunxi_g2d_rotation
{
    SUNXI_G2D_ROTATE_0,
    SUNXI_G2D_ROTATE_90,
    SUNXI_G2D_ROTATE_180,
    SUNXI_G2D_ROTATE_270,
};

enum sunxi_g2d_alpha_mode
{
    SUNXI_G2D_ALPHA_PIXEL,
    SUNXI_G2D_ALPHA_GLOBAL,
    SUNXI_G2D_ALPHA_MIXED,
};

enum sunxi_g2d_blend_mode
{
    SUNXI_G2D_BLEND_CLEAR,
    SUNXI_G2D_BLEND_SRC,
    SUNXI_G2D_BLEND_DST,
    SUNXI_G2D_BLEND_SRC_OVER,
    SUNXI_G2D_BLEND_DST_OVER,
    SUNXI_G2D_BLEND_SRC_IN,
    SUNXI_G2D_BLEND_DST_IN,
    SUNXI_G2D_BLEND_SRC_OUT,
    SUNXI_G2D_BLEND_DST_OUT,
    SUNXI_G2D_BLEND_SRC_ATOP,
    SUNXI_G2D_BLEND_DST_ATOP,
    SUNXI_G2D_BLEND_XOR,
};

#define SUNXI_G2D_FLIP_H                    RT_BIT(0)
#define SUNXI_G2D_FLIP_V                    RT_BIT(1)
#define SUNXI_G2D_SRC_PREMULTIPLIED         RT_BIT(2)
#define SUNXI_G2D_DST_PREMULTIPLIED         RT_BIT(3)
#define SUNXI_G2D_NO_CACHE_OPS              RT_BIT(4)
#define SUNXI_G2D_YUV_FULL_RANGE            RT_BIT(5)
#define SUNXI_G2D_YUV_BT709                 RT_BIT(6)

struct sunxi_g2d_image
{
    struct sunxi_g2d_buffer *buffer;
    rt_uint16_t width;
    rt_uint16_t height;
    rt_uint16_t pitch;
    enum sunxi_g2d_format format;
};

struct sunxi_g2d_rect
{
    rt_uint16_t x;
    rt_uint16_t y;
    rt_uint16_t width;
    rt_uint16_t height;
};

/* One physical plane. Buffers must be allocated or imported through g2d0. */
struct sunxi_g2d_plane
{
    struct sunxi_g2d_buffer *buffer;
    rt_size_t offset;
    rt_uint32_t pitch;
};

struct sunxi_g2d_surface
{
    enum sunxi_g2d_format format;
    rt_uint16_t width;
    rt_uint16_t height;
    struct sunxi_g2d_plane plane[3];
};

struct sunxi_g2d_blend
{
    enum sunxi_g2d_blend_mode mode;
    enum sunxi_g2d_alpha_mode foreground_alpha_mode;
    rt_uint8_t foreground_alpha;
    enum sunxi_g2d_alpha_mode background_alpha_mode;
    rt_uint8_t background_alpha;
    rt_bool_t color_key;
    rt_uint32_t color_key_min;
    rt_uint32_t color_key_max;
};

enum sunxi_g2d_operation_type
{
    SUNXI_G2D_OPERATION_FILL,
    SUNXI_G2D_OPERATION_BLIT,
    SUNXI_G2D_OPERATION_BLEND,
};

/* Generic operation for graphics planes and compositor attributes. */
struct sunxi_g2d_operation
{
    enum sunxi_g2d_operation_type type;
    rt_uint32_t flags;
    rt_uint32_t color;
    struct sunxi_g2d_surface destination;
    struct sunxi_g2d_rect destination_rect;
    struct sunxi_g2d_surface source;
    struct sunxi_g2d_rect source_rect;
    enum sunxi_g2d_rotation rotation;
    struct sunxi_g2d_surface background;
    struct sunxi_g2d_rect background_rect;
    struct sunxi_g2d_blend blend;
    rt_tick_t timeout;
};

struct sunxi_g2d_fill
{
    struct sunxi_g2d_image *destination;
    struct sunxi_g2d_rect rect;
    rt_uint32_t color;
    rt_tick_t timeout;
};

struct sunxi_g2d_blit
{
    struct sunxi_g2d_image *source;
    struct sunxi_g2d_rect source_rect;
    struct sunxi_g2d_image *destination;
    struct sunxi_g2d_rect destination_rect;
    rt_tick_t timeout;
};

#define SUNXI_G2D_CMD_ALLOC_BUFFER \
    (RT_DEVICE_CTRL_BASE(Miscellaneous) + 0)
#define SUNXI_G2D_CMD_FREE_BUFFER \
    (RT_DEVICE_CTRL_BASE(Miscellaneous) + 1)
#define SUNXI_G2D_CMD_SUBMIT_RCQ \
    (RT_DEVICE_CTRL_BASE(Miscellaneous) + 2)
#define SUNXI_G2D_CMD_GET_VERSION \
    (RT_DEVICE_CTRL_BASE(Miscellaneous) + 3)
#define SUNXI_G2D_CMD_FILL \
    (RT_DEVICE_CTRL_BASE(Miscellaneous) + 4)
#define SUNXI_G2D_CMD_BLIT \
    (RT_DEVICE_CTRL_BASE(Miscellaneous) + 5)
#define SUNXI_G2D_CMD_COMPOSE \
    (RT_DEVICE_CTRL_BASE(Miscellaneous) + 6)
#define SUNXI_G2D_CMD_IMPORT_BUFFER \
    (RT_DEVICE_CTRL_BASE(Miscellaneous) + 7)

#endif /* __SUNXI_G2D_H__ */
