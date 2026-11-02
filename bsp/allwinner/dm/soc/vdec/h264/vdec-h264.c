/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>

#include <rtthread.h>
#include <rtdevice.h>

#include <vdec/vdec.h>

#include "h264_decoder.h"
#include "h264_frame_pool.h"
#include "vdec-sun252i.h"

#define DBG_TAG "vdec"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct vdec_stream
{
    struct h264_decoder *decoder;
    rt_bool_t eos;
};

int vdec_decode_image(enum vdec_codec codec, const void *data, size_t length,
                      enum vdec_format format, struct vdec_frame *frame)
{
    RT_UNUSED(codec);
    RT_UNUSED(data);
    RT_UNUSED(length);
    RT_UNUSED(format);
    RT_UNUSED(frame);

    return -ENOTSUP;
}

void vdec_frame_release(struct vdec_frame *frame)
{
    if (h264_decoder_owns_frame(frame))
    {
        h264_decoder_release_frame(frame);
        rt_memset(frame->plane, 0, sizeof(frame->plane));
    }
}

int vdec_stream_open(const struct vdec_stream_config *config,
                     struct vdec_stream **stream)
{
    struct h264_decoder_config h264_config;
    struct vdec_stream *new_stream;
    int result;

    if (!config || !stream || config->codec != VDEC_CODEC_H264 ||
        (config->format != VDEC_FORMAT_NV12 && config->format != VDEC_FORMAT_NV21))
    {
        return -ENOTSUP;
    }
    new_stream = rt_calloc(1, sizeof(*new_stream));
    if (!new_stream)
    {
        return -ENOMEM;
    }
    h264_config.format = config->format;
    h264_config.bitstream_size = config->buffer_size;
    h264_config.no_cache_ops = config->no_cache_ops;
    h264_config.holding_frames = config->holding_frames == VDEC_HOLD_NONE ? 0 :
                                       (config->holding_frames > 0 ?
                                        config->holding_frames : 3);
    if (h264_config.holding_frames > H264_FRAME_POOL_MAX - 2)
    {
        h264_config.holding_frames = H264_FRAME_POOL_MAX - 2;
    }
    result = h264_decoder_open(&h264_config, &new_stream->decoder);
    if (result)
    {
        rt_free(new_stream);
        return result;
    }
    *stream = new_stream;
    return 0;
}

int vdec_stream_feed(struct vdec_stream *stream, const void *data, size_t length,
                     int64_t pts, size_t *consumed)
{
    if (!stream)
    {
        return -EINVAL;
    }
    return h264_decoder_feed(stream->decoder, data, length, pts, consumed);
}

int vdec_stream_get_frame(struct vdec_stream *stream, struct vdec_frame *frame)
{
    int result;

    if (!stream || !frame)
    {
        return -EINVAL;
    }
    result = h264_decoder_get_frame(stream->decoder, frame);
    return result == -EAGAIN && stream->eos ? -ENODATA : result;
}

int vdec_stream_flush(struct vdec_stream *stream)
{
    if (!stream)
    {
        return -EINVAL;
    }
    stream->eos = RT_TRUE;
    return 0;
}

void vdec_stream_close(struct vdec_stream *stream)
{
    if (!stream)
    {
        return;
    }
    h264_decoder_close(stream->decoder);
    rt_free(stream);
}
