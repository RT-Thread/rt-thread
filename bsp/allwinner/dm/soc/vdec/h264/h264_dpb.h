/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __VDEC_H264_DPB_H__
#define __VDEC_H264_DPB_H__

#include <rtthread.h>

#include "h264_frame_pool.h"
#include "h264_syntax.h"

struct h264_dpb
{
    struct h264_frame_pool *pool;
    rt_int32_t previous_poc_msb;
    rt_uint32_t previous_poc_lsb;
    rt_uint32_t max_poc_lsb;
    rt_uint32_t previous_frame_num;
    rt_uint32_t previous_frame_num_offset;
    rt_uint32_t max_frame_num;
    rt_uint8_t max_ref_frames;
};

int h264_dpb_init(struct h264_dpb *dpb, struct h264_frame_pool *pool,
                  const struct h264_sps *sps);
int h264_dpb_picture_poc(struct h264_dpb *dpb, const struct h264_sps *sps,
                         const struct h264_slice *slice, rt_int32_t *poc);
void h264_dpb_finish_picture(struct h264_dpb *dpb, struct h264_frame *frame,
                             const struct h264_slice *slice, rt_int32_t poc);
rt_uint8_t h264_dpb_ref_list(const struct h264_dpb *dpb, rt_uint32_t current_frame_num,
                             struct h264_frame **frames, rt_uint8_t max_count);

#endif /* __VDEC_H264_DPB_H__ */
