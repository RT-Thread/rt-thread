/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __VDEC_H264_HW_H__
#define __VDEC_H264_HW_H__

#include <rtthread.h>

#include "h264_syntax.h"
#include "h264_frame_pool.h"

struct h264_hw_buffers
{
    void *deblock;
    rt_ubase_t deblock_dma;
    void *intra;
    rt_ubase_t intra_dma;
    void *pic_info;
    rt_ubase_t pic_info_dma;
    void *neighbor;
    rt_ubase_t neighbor_dma;
    rt_ubase_t neighbor_aligned_dma;
};

int h264_hw_buffers_init(struct h264_hw_buffers *buffers);
void h264_hw_buffers_deinit(struct h264_hw_buffers *buffers);
void h264_hw_enable(void);
int h264_hw_program_frames(const struct h264_hw_buffers *buffers,
                           const struct h264_frame_pool *pool,
                           const struct h264_frame *output,
                           struct h264_frame *const *ref_list0, rt_uint8_t ref_count0,
                           struct h264_frame *const *ref_list1, rt_uint8_t ref_count1);

/* Program the parser and slice registers for one contiguous Annex-B NAL unit. */
int h264_hw_program_slice(const struct h264_sps *sps, const struct h264_pps *pps,
                          const struct h264_slice *slice, rt_ubase_t bitstream_dma,
                          rt_size_t bitstream_size, rt_uint32_t bit_offset,
                          rt_bool_t first_slice, rt_bool_t nv21);
void h264_hw_start_slice(void);
rt_uint32_t h264_hw_read_status(void);
rt_uint32_t h264_hw_ack_status(void);

#endif /* __VDEC_H264_HW_H__ */
