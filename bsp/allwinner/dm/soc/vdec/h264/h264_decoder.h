/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __VDEC_H264_DECODER_H__
#define __VDEC_H264_DECODER_H__

#include <vdec/vdec.h>

struct h264_decoder;

struct h264_decoder_config
{
    enum vdec_format format;
    rt_size_t bitstream_size;
    rt_uint8_t holding_frames;
    rt_bool_t no_cache_ops;
};

int h264_decoder_open(const struct h264_decoder_config *config,
                      struct h264_decoder **decoder);
void h264_decoder_close(struct h264_decoder *decoder);
int h264_decoder_feed(struct h264_decoder *decoder, const void *data, rt_size_t length,
                      rt_int64_t pts, rt_size_t *consumed);
int h264_decoder_get_frame(struct h264_decoder *decoder, struct vdec_frame *frame);
rt_bool_t h264_decoder_owns_frame(const struct vdec_frame *frame);
void h264_decoder_release_frame(struct vdec_frame *frame);

#endif /* __VDEC_H264_DECODER_H__ */
