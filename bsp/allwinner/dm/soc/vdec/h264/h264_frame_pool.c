/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <string.h>

#include <rtthread.h>

#include "vdec-sun252i.h"
#include "h264_frame_pool.h"
#include "h264_syntax.h"

int h264_frame_pool_init(struct h264_frame_pool *pool, const struct h264_sps *sps,
                         rt_uint8_t count)
{
    rt_uint16_t width;
    rt_uint16_t height;
    rt_uint16_t stride;
    rt_uint16_t aligned_height;
    rt_uint16_t chroma_width;
    rt_uint16_t chroma_height;
    rt_size_t size;
    rt_size_t mv_col_field_size;
    rt_uint8_t index;

    if (!pool || !sps || !sps->width || !sps->height || !count ||
        count > H264_FRAME_POOL_MAX)
    {
        return -EINVAL;
    }
    width = sps->width;
    height = sps->height;
    /* VE reference pictures are tiled in 32x32 blocks, unlike linear NV12. */
    stride = RT_ALIGN(width, 32);
    aligned_height = RT_ALIGN(height, 32);
    chroma_width = RT_ALIGN((width + 1) / 2, 16);
    chroma_height = RT_ALIGN((height + 1) / 2, 32);
    size = (rt_size_t)stride * aligned_height +
           2U * (rt_size_t)chroma_width * chroma_height;
    mv_col_field_size = ((width + 15) / 16) * ((height + 15) / 16) * 16;
    if (!sps->direct_8x8_inference)
    {
        mv_col_field_size *= 2;
    }
    if (!sps->frame_mbs_only)
    {
        mv_col_field_size *= 2;
    }
    rt_memset(pool, 0, sizeof(*pool));
    pool->width = width;
    pool->height = height;
    pool->stride = stride;
    pool->width_in_mbs = (width + 15) / 16;
    pool->height_in_mbs = (height + 15) / 16;
    pool->count = count;

    for (index = 0; index < count; index++)
    {
        struct h264_frame *frame = &pool->frames[index];

        frame->magic = H264_FRAME_MAGIC;
        frame->data = sunxi_vdec_hw_dma_alloc(size, &frame->dma);
        if (!frame->data)
        {
            h264_frame_pool_deinit(pool);
            return -ENOMEM;
        }
        frame->size = size;
        frame->mv_col = sunxi_vdec_hw_dma_alloc(mv_col_field_size * 2,
                                                 &frame->mv_col_dma);
        if (!frame->mv_col)
        {
            h264_frame_pool_deinit(pool);
            return -ENOMEM;
        }
        frame->mv_col_field_size = mv_col_field_size;
        frame->width = width;
        frame->height = height;
        frame->stride = stride;
        frame->index = index;
        frame->pts = -1;
        rt_memset(frame->data, 0, size);
        rt_memset(frame->mv_col, 0, mv_col_field_size * 2);
    }
    return 0;
}

void h264_frame_pool_reset(struct h264_frame_pool *pool)
{
    rt_uint8_t index;

    if (!pool)
    {
        return;
    }
    for (index = 0; index < pool->count; index++)
    {
        pool->frames[index].decode_ref = 0;
        pool->frames[index].display_ref = 0;
        pool->frames[index].decoding = 0;
        pool->frames[index].ready = 0;
        pool->frames[index].pts = -1;
    }
}

void h264_frame_pool_deinit(struct h264_frame_pool *pool)
{
    rt_uint8_t index;

    if (!pool)
    {
        return;
    }
    for (index = 0; index < pool->count; index++)
    {
        if (pool->frames[index].data)
        {
            sunxi_vdec_hw_dma_free(pool->frames[index].data);
            pool->frames[index].data = RT_NULL;
        }
        if (pool->frames[index].display)
        {
            sunxi_vdec_hw_dma_free(pool->frames[index].display);
            pool->frames[index].display = RT_NULL;
        }
        if (pool->frames[index].mv_col)
        {
            sunxi_vdec_hw_dma_free(pool->frames[index].mv_col);
            pool->frames[index].mv_col = RT_NULL;
        }
    }
    rt_memset(pool, 0, sizeof(*pool));
}

struct h264_frame *h264_frame_pool_acquire(struct h264_frame_pool *pool)
{
    rt_uint8_t index;

    if (!pool)
    {
        return RT_NULL;
    }
    for (index = 0; index < pool->count; index++)
    {
        struct h264_frame *frame = &pool->frames[index];

        if (!frame->decoding && !frame->decode_ref && !frame->display_ref)
        {
            frame->decoding = 1;
            return frame;
        }
    }
    return RT_NULL;
}

void h264_frame_pool_cancel(struct h264_frame *frame)
{
    if (frame)
    {
        frame->decoding = 0;
    }
}

void h264_frame_pool_publish(struct h264_frame *frame, rt_int64_t pts)
{
    if (!frame)
    {
        return;
    }
    frame->display_ref = 1;
    frame->ready = 1;
    frame->pts = pts;
}

struct h264_frame *h264_frame_pool_next(struct h264_frame_pool *pool)
{
    rt_uint8_t index;
    struct h264_frame *result = RT_NULL;

    if (!pool)
    {
        return RT_NULL;
    }
    for (index = 0; index < pool->count; index++)
    {
        struct h264_frame *frame = &pool->frames[index];

        if (frame->ready && (!result || frame->poc < result->poc))
        {
            result = frame;
        }
    }
    if (result)
    {
        result->ready = 0;
    }
    return result;
}

int h264_frame_pool_prepare_display(struct h264_frame *frame)
{
    if (!frame)
    {
        return -EINVAL;
    }
    if (!frame->display)
    {
        frame->display = sunxi_vdec_hw_dma_alloc(frame->size, &frame->display_dma);
        if (!frame->display)
        {
            return -ENOMEM;
        }
    }
    return 0;
}

void h264_frame_pool_release(struct h264_frame *frame)
{
    if (frame)
    {
        frame->display_ref = 0;
        if (frame->display)
        {
            sunxi_vdec_hw_dma_free(frame->display);
            frame->display = RT_NULL;
            frame->display_dma = 0;
        }
    }
}
