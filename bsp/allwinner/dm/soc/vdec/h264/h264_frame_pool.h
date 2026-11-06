/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __VDEC_H264_FRAME_POOL_H__
#define __VDEC_H264_FRAME_POOL_H__

#include <rtthread.h>

#define H264_FRAME_POOL_MAX 18
#define H264_FRAME_MAGIC    0x48323634U

struct h264_decoder;
struct h264_sps;

struct h264_frame
{
    rt_uint32_t magic;
    struct h264_decoder *owner;
    void *data;
    rt_ubase_t dma;
    void *display;
    rt_ubase_t display_dma;
    rt_size_t size;
    void *mv_col;
    rt_ubase_t mv_col_dma;
    rt_size_t mv_col_field_size;
    rt_uint16_t width;
    rt_uint16_t height;
    rt_uint16_t stride;
    rt_uint8_t index;
    rt_uint8_t decoding;
    rt_uint8_t decode_ref;
    rt_uint8_t display_ref;
    rt_uint8_t ready;
    rt_uint32_t frame_num;
    rt_int32_t poc;
    rt_int64_t pts;
};

struct h264_frame_pool
{
    struct h264_frame frames[H264_FRAME_POOL_MAX];
    rt_uint16_t width;
    rt_uint16_t height;
    rt_uint16_t stride;
    rt_uint16_t width_in_mbs;
    rt_uint16_t height_in_mbs;
    rt_uint8_t count;
};

int h264_frame_pool_init(struct h264_frame_pool *pool, const struct h264_sps *sps,
                         rt_uint8_t count);
void h264_frame_pool_reset(struct h264_frame_pool *pool);
void h264_frame_pool_deinit(struct h264_frame_pool *pool);
struct h264_frame *h264_frame_pool_acquire(struct h264_frame_pool *pool);
void h264_frame_pool_cancel(struct h264_frame *frame);
void h264_frame_pool_publish(struct h264_frame *frame, rt_int64_t pts);
struct h264_frame *h264_frame_pool_next(struct h264_frame_pool *pool);
int h264_frame_pool_prepare_display(struct h264_frame *frame);
void h264_frame_pool_release(struct h264_frame *frame);

#endif /* __VDEC_H264_FRAME_POOL_H__ */
