/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <string.h>

#include <rthw.h>
#include <rtthread.h>

#define DBG_TAG "vdec.h264"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "vdec-sun252i.h"
#include "h264_bitstream.h"
#include "h264_decoder.h"
#include "h264_dpb.h"
#include "h264_frame_pool.h"
#include "h264_hw.h"
#include "h264_syntax.h"

#define H264_DECODER_MIN_BITSTREAM_SIZE (256 * 1024)
#define H264_DECODER_TIMEOUT_MS          500

struct h264_packet
{
    rt_list_t list;
    void *data;
    rt_size_t length;
    rt_int64_t pts;
};

struct h264_decoder
{
    struct h264_sps sps;
    struct h264_pps pps;
    struct h264_frame_pool frames;
    struct h264_dpb dpb;
    struct h264_hw_buffers buffers;
    struct rt_completion completion;
    rt_list_t packets;
    void *bitstream;
    rt_ubase_t bitstream_dma;
    rt_size_t bitstream_size;
    enum vdec_format format;
    rt_uint32_t status;
    rt_uint8_t have_sps;
    rt_uint8_t have_pps;
    rt_uint8_t resources_ready;
    rt_bool_t ve_claimed;
    rt_uint8_t holding_frames;
    rt_uint8_t held_frames;
    rt_bool_t no_cache_ops;
};

static void h264_decoder_cache_sync(void *address, rt_size_t size)
{
#ifndef ARCH_MM_MMU
    rt_hw_cpu_dcache_clean_and_invalidate(address, size);
#else
    RT_UNUSED(address);
    RT_UNUSED(size);
#endif
}

static int h264_decoder_irq(void *data)
{
    struct h264_decoder *decoder = data;
    rt_uint32_t status;

    status = h264_hw_ack_status();
    if (status & (RT_BIT(0) | RT_BIT(1) | RT_BIT(2)))
    {
        decoder->status = status;
        rt_completion_done(&decoder->completion);
    }
    return 0;
}

static void h264_decoder_resources_deinit(struct h264_decoder *decoder)
{
    if (!decoder->resources_ready)
    {
        return;
    }
    h264_hw_buffers_deinit(&decoder->buffers);
    h264_frame_pool_deinit(&decoder->frames);
    rt_memset(&decoder->dpb, 0, sizeof(decoder->dpb));
    decoder->resources_ready = 0;
}

static int h264_decoder_resources_init(struct h264_decoder *decoder)
{
    rt_uint8_t frame_count;
    int result;

    if (!decoder->have_sps || !decoder->have_pps)
    {
        return -EAGAIN;
    }
    if (decoder->resources_ready)
    {
        return 0;
    }
    frame_count = decoder->sps.max_num_ref_frames + decoder->holding_frames + 1;
    if (frame_count < 3)
    {
        frame_count = 3;
    }
    if (frame_count > H264_FRAME_POOL_MAX)
    {
        frame_count = H264_FRAME_POOL_MAX;
    }
    result = h264_frame_pool_init(&decoder->frames, &decoder->sps, frame_count);
    if (result)
    {
        return result;
    }
    result = h264_dpb_init(&decoder->dpb, &decoder->frames, &decoder->sps);
    if (result)
    {
        h264_frame_pool_deinit(&decoder->frames);
        return result;
    }
    result = h264_hw_buffers_init(&decoder->buffers);
    if (result)
    {
        h264_frame_pool_deinit(&decoder->frames);
        rt_memset(&decoder->dpb, 0, sizeof(decoder->dpb));
        return result;
    }
    decoder->resources_ready = 1;
    return 0;
}

static void h264_decoder_packets_clear(struct h264_decoder *decoder)
{
    struct h264_packet *packet;
    struct h264_packet *next;

    rt_list_for_each_entry_safe(packet, next, &decoder->packets, list)
    {
        rt_list_remove(&packet->list);
        rt_free(packet->data);
        rt_free(packet);
    }
}

int h264_decoder_open(const struct h264_decoder_config *config,
                      struct h264_decoder **out)
{
    struct h264_decoder *decoder;
    rt_size_t bitstream_size;
    int result;

    if (!config || !out || (config->format != VDEC_FORMAT_NV12 &&
                            config->format != VDEC_FORMAT_NV21))
    {
        return -EINVAL;
    }
    decoder = rt_calloc(1, sizeof(*decoder));
    if (!decoder)
    {
        return -ENOMEM;
    }
    rt_list_init(&decoder->packets);
    rt_completion_init(&decoder->completion);
    result = sunxi_vdec_hw_acquire(decoder, h264_decoder_irq, 0);
    if (result)
    {
        rt_free(decoder);
        return result;
    }
    decoder->ve_claimed = RT_TRUE;
    bitstream_size = config->bitstream_size;
    if (bitstream_size < H264_DECODER_MIN_BITSTREAM_SIZE)
    {
        bitstream_size = H264_DECODER_MIN_BITSTREAM_SIZE;
    }
    decoder->bitstream = sunxi_vdec_hw_dma_alloc(bitstream_size, &decoder->bitstream_dma);
    if (!decoder->bitstream)
    {
        h264_decoder_close(decoder);
        return -ENOMEM;
    }
    decoder->bitstream_size = bitstream_size;
    decoder->format = config->format;
    decoder->holding_frames = config->holding_frames;
    decoder->no_cache_ops = config->no_cache_ops;
    result = sunxi_vdec_hw_reset_decoder();
    if (result)
    {
        h264_decoder_close(decoder);
        return result;
    }
    *out = decoder;
    return 0;
}

void h264_decoder_close(struct h264_decoder *decoder)
{
    if (!decoder)
    {
        return;
    }
    if (decoder->ve_claimed)
    {
        sunxi_vdec_hw_release(decoder);
        decoder->ve_claimed = RT_FALSE;
    }
    if (decoder->held_frames)
    {
        LOG_W("closed with %u frames still held", decoder->held_frames);
    }
    h264_decoder_packets_clear(decoder);
    h264_decoder_resources_deinit(decoder);
    if (decoder->bitstream)
    {
        sunxi_vdec_hw_dma_free(decoder->bitstream);
    }
    rt_free(decoder);
}

int h264_decoder_feed(struct h264_decoder *decoder, const void *data, rt_size_t length,
                      rt_int64_t pts, rt_size_t *consumed)
{
    const rt_uint8_t *start = data;
    const rt_uint8_t *end = start + length;
    const rt_uint8_t *nalu;

    if (!decoder || !data || !length || !consumed)
    {
        return -EINVAL;
    }
    *consumed = 0;
    nalu = h264_annexb_find_start_code(start, end);
    if (nalu != start)
    {
        return -EINVAL;
    }
    while (nalu)
    {
        const rt_uint8_t *next = h264_annexb_find_start_code(nalu + 3, end);
        rt_size_t nalu_length = (next ? next : end) - nalu;
        int type = h264_annexb_nalu_type(nalu, nalu_length);

        if (type == 7)
        {
            struct h264_sps sps;

            if (h264_sps_parse(nalu, nalu_length, &sps) != 0)
            {
                return *consumed ? 0 : -ENOTSUP;
            }
            if (decoder->resources_ready &&
                rt_memcmp(&decoder->sps, &sps, sizeof(sps)) != 0)
            {
                return *consumed ? 0 : -ENOTSUP;
            }
            decoder->sps = sps;
            decoder->have_sps = 1;
        }
        else if (type == 8 && h264_pps_parse(nalu, nalu_length, &decoder->pps) == 0)
        {
            decoder->have_pps = 1;
        }
        else if (type == 1 || type == 5)
        {
            struct h264_packet *packet;

            if (nalu_length > decoder->bitstream_size)
            {
                return *consumed ? 0 : -ENOMEM;
            }
            packet = rt_calloc(1, sizeof(*packet));
            if (!packet)
            {
                return *consumed ? 0 : -ENOMEM;
            }
            packet->data = rt_malloc(nalu_length);
            if (!packet->data)
            {
                rt_free(packet);
                return *consumed ? 0 : -ENOMEM;
            }
            rt_memcpy(packet->data, nalu, nalu_length);
            packet->length = nalu_length;
            packet->pts = pts;
            rt_list_insert_before(&decoder->packets, &packet->list);
        }
        *consumed += nalu_length;
        nalu = next;
    }
    return *consumed ? 0 : -EAGAIN;
}

int h264_decoder_get_frame(struct h264_decoder *decoder, struct vdec_frame *frame)
{
    struct h264_packet *packet;
    struct h264_slice slice;
    struct h264_frame *output;
    struct h264_frame *refs[32];
    rt_int32_t poc;
    rt_uint8_t ref_count;
    rt_uint32_t start_code_length;
    int result;

    if (!decoder || !frame)
    {
        return -EINVAL;
    }
    if (rt_list_isempty(&decoder->packets))
    {
        return -EAGAIN;
    }
    packet = rt_list_first_entry(&decoder->packets, struct h264_packet, list);
    if (!decoder->have_sps || !decoder->have_pps)
    {
        return -EAGAIN;
    }
    result = h264_decoder_resources_init(decoder);
    if (result)
    {
        return result;
    }
    result = h264_slice_parse(packet->data, packet->length, &decoder->sps, &decoder->pps,
                              &slice);
    if (result)
    {
        LOG_E("slice parse failed: %d", result);
        goto out_packet;
    }
    if (slice.first_mb_in_slice != 0 || slice.slice_type == H264_SLICE_B)
    {
        result = -ENOTSUP;
        goto out_packet;
    }
    result = h264_dpb_picture_poc(&decoder->dpb, &decoder->sps, &slice, &poc);
    if (result)
    {
        goto out_packet;
    }
    ref_count = h264_dpb_ref_list(&decoder->dpb, slice.frame_num, refs,
                                  RT_ARRAY_SIZE(refs));
    output = h264_frame_pool_acquire(&decoder->frames);
    if (!output)
    {
        return -EBUSY;
    }
    output->poc = poc;
    rt_memcpy(decoder->bitstream, packet->data, packet->length);
    h264_decoder_cache_sync(decoder->bitstream, packet->length);
    start_code_length = ((rt_uint8_t *)packet->data)[2] == 1 ? 3 : 4;
    decoder->status = 0;
    h264_hw_enable();
    result = h264_hw_program_frames(&decoder->buffers, &decoder->frames, output, refs,
                                    ref_count, slice.slice_type == H264_SLICE_B ? refs : RT_NULL,
                                    slice.slice_type == H264_SLICE_B ? ref_count : 0);
    if (result)
    {
        LOG_E("frame register setup failed: %d", result);
    }
    else
    {
        result = h264_hw_program_slice(&decoder->sps, &decoder->pps, &slice,
                    decoder->bitstream_dma, packet->length,
                    (start_code_length + 1) * 8 + slice.header_bits, RT_TRUE,
                    decoder->format == VDEC_FORMAT_NV21);
        if (result)
        {
            LOG_E("slice register setup failed: %d", result);
        }
    }
    if (!result)
    {
        rt_completion_init(&decoder->completion);
        h264_hw_start_slice();
        if (rt_completion_wait(&decoder->completion,
                               rt_tick_from_millisecond(H264_DECODER_TIMEOUT_MS)) != RT_EOK)
        {
            decoder->status = h264_hw_ack_status();
            if (decoder->status & RT_BIT(0))
            {
                LOG_W("VE completed without an interrupt, status=%08x", decoder->status);
            }
            else if (decoder->status & (RT_BIT(1) | RT_BIT(2)))
            {
                result = -EIO;
            }
            else
            {
                result = -ETIMEDOUT;
            }
        }
        else if (decoder->status & (RT_BIT(1) | RT_BIT(2)))
        {
            LOG_E("VE reported decode error: status=%08x", decoder->status);
            result = -EIO;
        }
    }
    if (result)
    {
        h264_frame_pool_cancel(output);
        goto out_packet;
    }
    h264_dpb_finish_picture(&decoder->dpb, output, &slice, poc);
    if (!decoder->no_cache_ops)
    {
        h264_decoder_cache_sync(output->data, output->size);
    }
    h264_frame_pool_publish(output, packet->pts);
    output = h264_frame_pool_next(&decoder->frames);
    if (!output)
    {
        result = -EAGAIN;
        goto out_packet;
    }
    result = h264_frame_pool_prepare_display(output);
    if (!result)
    {
        result = sunxi_vdec_hw_convert_tiled(output->dma,
            output->dma + output->stride * RT_ALIGN(output->height, 32),
            output->display_dma, output->stride,
            RT_ALIGN(output->height, 32));
    }
    if (result)
    {
        LOG_E("tiled-to-NV12 conversion failed: %d", result);
        h264_frame_pool_release(output);
        goto out_packet;
    }
    if (!decoder->no_cache_ops)
    {
        h264_decoder_cache_sync(output->display, output->size);
    }
    rt_memset(frame, 0, sizeof(*frame));
    frame->format = decoder->format;
    frame->width = output->width;
    frame->height = output->height;
    frame->plane[0] = output->display;
    frame->plane[1] = (rt_uint8_t *)output->display + output->stride * RT_ALIGN(output->height, 32);
    frame->stride[0] = output->stride;
    frame->stride[1] = output->stride;
    frame->pts = output->pts;
    output->owner = decoder;
    decoder->held_frames++;
    frame->priv = output;
out_packet:
    rt_list_remove(&packet->list);
    rt_free(packet->data);
    rt_free(packet);
    return result;
}

rt_bool_t h264_decoder_owns_frame(const struct vdec_frame *frame)
{
    const struct h264_frame *native_frame;

    if (!frame || !frame->priv)
    {
        return RT_FALSE;
    }
    native_frame = frame->priv;
    return native_frame->magic == H264_FRAME_MAGIC;
}

void h264_decoder_release_frame(struct vdec_frame *frame)
{
    if (h264_decoder_owns_frame(frame))
    {
        struct h264_frame *native_frame = frame->priv;

        if (native_frame->owner && native_frame->owner->held_frames)
        {
            native_frame->owner->held_frames--;
        }
        h264_frame_pool_release(native_frame);
        frame->priv = RT_NULL;
    }
}
