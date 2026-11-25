/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>

#include "h264_dpb.h"

int h264_dpb_init(struct h264_dpb *dpb, struct h264_frame_pool *pool,
                  const struct h264_sps *sps)
{
    if (!dpb || !sps || (sps->pic_order_cnt_type != 0 &&
                         sps->pic_order_cnt_type != 2))
    {
        return -ENOTSUP;
    }
    if (sps->pic_order_cnt_type == 0 &&
        (sps->log2_max_pic_order_cnt_lsb < 4 ||
         sps->log2_max_pic_order_cnt_lsb > 16))
    {
        return -ENOTSUP;
    }
    dpb->pool = pool;
    dpb->previous_poc_msb = 0;
    dpb->previous_poc_lsb = 0;
    dpb->max_poc_lsb = sps->pic_order_cnt_type == 0 ?
                       1U << sps->log2_max_pic_order_cnt_lsb : 0;
    dpb->previous_frame_num = 0;
    dpb->previous_frame_num_offset = 0;
    dpb->max_frame_num = 1U << sps->log2_max_frame_num;
    dpb->max_ref_frames = sps->max_num_ref_frames;
    return 0;
}

int h264_dpb_picture_poc(struct h264_dpb *dpb, const struct h264_sps *sps,
                         const struct h264_slice *slice, rt_int32_t *poc)
{
    rt_int32_t poc_msb;

    if (!dpb || !sps || !slice || !poc)
    {
        return -ENOTSUP;
    }
    if (sps->pic_order_cnt_type == 2)
    {
        rt_uint32_t frame_num_offset;

        if (slice->idr_pic)
        {
            frame_num_offset = 0;
        }
        else if (dpb->previous_frame_num > slice->frame_num)
        {
            frame_num_offset = dpb->previous_frame_num_offset + dpb->max_frame_num;
        }
        else
        {
            frame_num_offset = dpb->previous_frame_num_offset;
        }
        *poc = 2 * (rt_int32_t)(frame_num_offset + slice->frame_num) -
               (slice->nal_ref_idc ? 0 : 1);
        if (slice->nal_ref_idc)
        {
            dpb->previous_frame_num = slice->frame_num;
            dpb->previous_frame_num_offset = frame_num_offset;
        }
        return 0;
    }
    if (sps->pic_order_cnt_type != 0 || !dpb->max_poc_lsb)
    {
        return -ENOTSUP;
    }
    if (slice->idr_pic)
    {
        dpb->previous_poc_msb = 0;
        dpb->previous_poc_lsb = 0;
    }
    if (slice->pic_order_cnt_lsb < dpb->previous_poc_lsb &&
        dpb->previous_poc_lsb - slice->pic_order_cnt_lsb >= dpb->max_poc_lsb / 2)
    {
        poc_msb = dpb->previous_poc_msb + dpb->max_poc_lsb;
    }
    else if (slice->pic_order_cnt_lsb > dpb->previous_poc_lsb &&
             slice->pic_order_cnt_lsb - dpb->previous_poc_lsb > dpb->max_poc_lsb / 2)
    {
        poc_msb = dpb->previous_poc_msb - dpb->max_poc_lsb;
    }
    else
    {
        poc_msb = dpb->previous_poc_msb;
    }
    *poc = poc_msb + slice->pic_order_cnt_lsb;
    if (slice->nal_ref_idc)
    {
        dpb->previous_poc_msb = poc_msb;
        dpb->previous_poc_lsb = slice->pic_order_cnt_lsb;
    }
    return 0;
}

void h264_dpb_finish_picture(struct h264_dpb *dpb, struct h264_frame *frame,
                             const struct h264_slice *slice, rt_int32_t poc)
{
    rt_uint8_t index;
    rt_uint8_t references = 0;
    struct h264_frame *oldest = RT_NULL;

    if (!dpb || !frame || !slice)
    {
        return;
    }
    frame->poc = poc;
    frame->frame_num = slice->frame_num;
    frame->decoding = 0;
    frame->decode_ref = !!slice->nal_ref_idc;
    if (!dpb->pool || !frame->decode_ref)
    {
        return;
    }
    if (!dpb->max_ref_frames)
    {
        frame->decode_ref = 0;
        return;
    }
    if (slice->idr_pic)
    {
        for (index = 0; index < dpb->pool->count; index++)
        {
            if (&dpb->pool->frames[index] != frame)
            {
                dpb->pool->frames[index].decode_ref = 0;
            }
        }
        return;
    }
    for (index = 0; index < dpb->pool->count; index++)
    {
        struct h264_frame *candidate = &dpb->pool->frames[index];

        if (candidate->decode_ref)
        {
            references++;
            if (candidate != frame && (!oldest || candidate->poc < oldest->poc))
            {
                oldest = candidate;
            }
        }
    }
    if (references > dpb->max_ref_frames && oldest)
    {
        oldest->decode_ref = 0;
    }
}

rt_uint8_t h264_dpb_ref_list(const struct h264_dpb *dpb, rt_uint32_t current_frame_num,
                             struct h264_frame **frames, rt_uint8_t max_count)
{
    rt_uint8_t count = 0;
    rt_uint8_t index;

    if (!dpb || !dpb->pool || !frames)
    {
        return 0;
    }
    for (index = 0; index < dpb->pool->count && count < max_count; index++)
    {
        struct h264_frame *frame = &dpb->pool->frames[index];

        if (frame->decode_ref)
        {
            rt_uint8_t position = count;
            rt_uint32_t distance = (current_frame_num + dpb->max_frame_num -
                                    frame->frame_num) % dpb->max_frame_num;

            while (position > 0)
            {
                struct h264_frame *previous = frames[position - 1];
                rt_uint32_t previous_distance =
                    (current_frame_num + dpb->max_frame_num - previous->frame_num) %
                    dpb->max_frame_num;

                if (previous_distance <= distance)
                {
                    break;
                }
                frames[position] = previous;
                position--;
            }
            frames[position] = frame;
            count++;
        }
    }
    return count;
}
