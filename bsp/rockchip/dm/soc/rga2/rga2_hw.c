/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#include "rga2_internal.h"
#include "rga2_reg.h"

struct rga2_format_info
{
    rt_uint8_t hw_format;
    rt_uint8_t bytes_per_pixel;
    rt_uint8_t rb_swap;
};

static rt_err_t rga2_get_format(rt_uint16_t format,
        struct rga2_format_info *info)
{
    static const struct rga2_format_info formats[] =
    {
        [RGA2_FORMAT_RGBA8888] = { 0, 4, 0 },
        [RGA2_FORMAT_BGRA8888] = { 0, 4, 1 },
        [RGA2_FORMAT_RGBX8888] = { 1, 4, 0 },
        [RGA2_FORMAT_BGRX8888] = { 1, 4, 1 },
        [RGA2_FORMAT_RGB888]   = { 2, 3, 0 },
        [RGA2_FORMAT_BGR888]   = { 2, 3, 1 },
        [RGA2_FORMAT_RGB565]   = { 4, 2, 0 },
        [RGA2_FORMAT_BGR565]   = { 4, 2, 1 },
    };

    if (format >= sizeof(formats) / sizeof(formats[0]))
    {
        return -RT_EINVAL;
    }

    *info = formats[format];
    return RT_EOK;
}

static rt_uint32_t rga2_scale_factor(rt_uint16_t source,
        rt_uint16_t destination)
{
    if (source == destination)
    {
        return 0;
    }

    if (source > destination)
    {
        /* Average down-scaling uses a 16.16 destination/source ratio. */
        return ((rt_uint32_t)destination << 16) / source;
    }

    /* Up-scaling uses a 16.16 source/destination ratio in the high half. */
    return (((rt_uint32_t)source << 16) / destination) << 16;
}

static rt_uint32_t rga2_destination_address(const struct rga2_req *req,
        rt_uint32_t stride, rt_uint8_t bytes_per_pixel)
{
    const struct rga2_rect *rect = &req->dst.rect;
    rt_uint32_t left_top = (rt_uint32_t)req->dst.address +
            rect->y * stride + rect->x * bytes_per_pixel;
    rt_uint32_t right_top = left_top +
            (rect->width - 1) * bytes_per_pixel;
    rt_uint32_t left_bottom = left_top +
            (rect->height - 1) * stride;
    rt_uint32_t right_bottom = left_bottom +
            (rect->width - 1) * bytes_per_pixel;
    rt_uint32_t mirror_x = req->rotate >= RGA2_ROTATE_180;
    rt_uint32_t mirror_y = mirror_x;

    mirror_x ^= !!(req->mirror & RGA2_MIRROR_X);
    mirror_y ^= !!(req->mirror & RGA2_MIRROR_Y);

    if (!(req->rotate & 1))
    {
        return mirror_y ? (mirror_x ? right_bottom : left_bottom) :
                (mirror_x ? right_top : left_top);
    }

    return mirror_y ? (mirror_x ? left_bottom : right_bottom) :
            (mirror_x ? left_top : right_top);
}

rt_err_t rockchip_rga2_build_command(const struct rga2_req *req,
        rt_uint32_t command[RGA2_COMMAND_WORDS])
{
    struct rga2_format_info src_format = { 0 };
    struct rga2_format_info dst_format;
    rt_uint16_t scale_width;
    rt_uint16_t scale_height;
    rt_uint32_t src_stride = 0;
    rt_uint32_t dst_stride;
    rt_uint32_t src_info = 0;

    rt_memset(command, 0, RGA2_COMMAND_WORDS * sizeof(*command));

    if (rga2_get_format(req->dst.format, &dst_format) != RT_EOK)
    {
        return -RT_EINVAL;
    }

    dst_stride = RT_ALIGN(req->dst.stride, 4);
    command[RGA2_MODE_CTRL / 4] = req->render_mode;
    command[RGA2_DST_INFO / 4] = dst_format.hw_format |
            ((rt_uint32_t)dst_format.rb_swap << 4);
    command[RGA2_DST_BASE0 / 4] = rga2_destination_address(req,
            dst_stride, dst_format.bytes_per_pixel);
    command[RGA2_DST_VIR_INFO / 4] = dst_stride >> 2;
    command[RGA2_DST_ACT_INFO / 4] = (req->dst.rect.width - 1) |
            ((rt_uint32_t)(req->dst.rect.height - 1) << 16);

    if (req->render_mode == RGA2_MODE_COLOR_FILL)
    {
        command[RGA2_SRC_BG_COLOR / 4] = req->color;
        return RT_EOK;
    }

    if (rga2_get_format(req->src.format, &src_format) != RT_EOK)
    {
        return -RT_EINVAL;
    }

    src_stride = RT_ALIGN(req->src.stride, 4);
    scale_width = (req->rotate & 1) ? req->dst.rect.height :
            req->dst.rect.width;
    scale_height = (req->rotate & 1) ? req->dst.rect.width :
            req->dst.rect.height;

    src_info = src_format.hw_format |
            ((rt_uint32_t)src_format.rb_swap << 4) |
            ((rt_uint32_t)req->rotate << 10) |
            ((rt_uint32_t)(req->mirror & 3) << 12);
    if (req->src.rect.width > scale_width)
    {
        src_info |= 1U << 14;
    }
    else if (req->src.rect.width < scale_width)
    {
        src_info |= 2U << 14;
    }
    if (req->src.rect.height > scale_height)
    {
        src_info |= 1U << 16;
    }
    else if (req->src.rect.height < scale_height)
    {
        src_info |= 2U << 16;
    }

    command[RGA2_SRC_INFO / 4] = src_info;
    command[RGA2_SRC_BASE0 / 4] = (rt_uint32_t)req->src.address +
            req->src.rect.y * src_stride +
            req->src.rect.x * src_format.bytes_per_pixel;
    command[RGA2_SRC_VIR_INFO / 4] = src_stride >> 2;
    command[RGA2_SRC_ACT_INFO / 4] = (req->src.rect.width - 1) |
            ((rt_uint32_t)(req->src.rect.height - 1) << 16);
    command[RGA2_SRC_X_FACTOR / 4] = rga2_scale_factor(
            req->src.rect.width, scale_width);
    command[RGA2_SRC_Y_FACTOR / 4] = rga2_scale_factor(
            req->src.rect.height, scale_height);

    return RT_EOK;
}
