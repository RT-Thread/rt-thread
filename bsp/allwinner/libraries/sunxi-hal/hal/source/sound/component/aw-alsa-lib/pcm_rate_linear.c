/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the people's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
*
*
* THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
* PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
* THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
* OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <aw-alsa-lib/plugin/pcm_rate.h>
#include <aw-alsa-lib/pcm_config.h>
#include "pcm_local.h"
#include "plugin_ops.h"

#include "bswap.h"
#include <aw_list.h>
#include <aw_common.h>


/* LINEAR_DIV needs to be large enough to handle resampling from 192000 -> 8000 */
#define LINEAR_DIV_SHIFT 19
#define LINEAR_DIV (1<<LINEAR_DIV_SHIFT)

struct rate_linear {
    unsigned int get_idx;
    unsigned int put_idx;
    unsigned int pitch;
    unsigned int pitch_shift;   /* for expand interpolation */
    unsigned int channels;
    int16_t *old_sample;
    void (*func)(struct rate_linear *rate,
             const snd_pcm_channel_area_t *dst_areas,
             snd_pcm_uframes_t dst_offset, unsigned int dst_frames,
             const snd_pcm_channel_area_t *src_areas,
             snd_pcm_uframes_t src_offset, unsigned int src_frames);
};

static snd_pcm_uframes_t input_frames(void *obj, snd_pcm_uframes_t frames)
{
    struct rate_linear *rate = obj;
    if (frames == 0)
        return 0;
    /* Round toward zero */
    return muldiv_near(frames, LINEAR_DIV, rate->pitch);
}

static snd_pcm_uframes_t output_frames(void *obj, snd_pcm_uframes_t frames)
{
    struct rate_linear *rate = obj;
    if (frames == 0)
        return 0;
    /* Round toward zero */
    return muldiv_near(frames, rate->pitch, LINEAR_DIV);
}

static void linear_expand(struct rate_linear *rate,
              const snd_pcm_channel_area_t *dst_areas,
              snd_pcm_uframes_t dst_offset, unsigned int dst_frames,
              const snd_pcm_channel_area_t *src_areas,
              snd_pcm_uframes_t src_offset, unsigned int src_frames)
{
#define GET16_LABELS
#define PUT16_LABELS
#include "plugin_ops.h"
#undef GET16_LABELS
#undef PUT16_LABELS
    void *get = get16_labels[rate->get_idx];
    void *put = put16_labels[rate->put_idx];
    unsigned int get_threshold = rate->pitch;
    unsigned int channel;
    unsigned int src_frames1;
    unsigned int dst_frames1;
    int16_t sample = 0;
    unsigned int pos;

    for (channel = 0; channel < rate->channels; ++channel) {
        const snd_pcm_channel_area_t *src_area = &src_areas[channel];
        const snd_pcm_channel_area_t *dst_area = &dst_areas[channel];
        const char *src;
        char *dst;
        int src_step, dst_step;
        int16_t old_sample = 0;
        int16_t new_sample;
        int old_weight, new_weight;
        src = snd_pcm_channel_area_addr(src_area, src_offset);
        dst = snd_pcm_channel_area_addr(dst_area, dst_offset);
        src_step = snd_pcm_channel_area_step(src_area);
        dst_step = snd_pcm_channel_area_step(dst_area);
        src_frames1 = 0;
        dst_frames1 = 0;
        new_sample = rate->old_sample[channel];
        pos = get_threshold;
        while (dst_frames1 < dst_frames) {
            if (pos >= get_threshold) {
                pos -= get_threshold;
                old_sample = new_sample;
                if (src_frames1 < src_frames) {
                    goto *get;
#define GET16_END after_get
#include "plugin_ops.h"
#undef GET16_END
                after_get:
                    new_sample = sample;
                }
            }
            new_weight = (pos << (16 - rate->pitch_shift)) / (get_threshold >> rate->pitch_shift);
            old_weight = 0x10000 - new_weight;
            sample = (old_sample * old_weight + new_sample * new_weight) >> 16;
            goto *put;
#define PUT16_END after_put
#include "plugin_ops.h"
#undef PUT16_END
        after_put:
            dst += dst_step;
            dst_frames1++;
            pos += LINEAR_DIV;
            if (pos >= get_threshold) {
                src += src_step;
                src_frames1++;
            }
        }
        rate->old_sample[channel] = new_sample;
    }
}

/* optimized version for S16 format */
static void linear_expand_s16(struct rate_linear *rate,
                  const snd_pcm_channel_area_t *dst_areas,
                  snd_pcm_uframes_t dst_offset, unsigned int dst_frames,
                  const snd_pcm_channel_area_t *src_areas,
                  snd_pcm_uframes_t src_offset, unsigned int src_frames)
{
    unsigned int channel;
    unsigned int src_frames1;
    unsigned int dst_frames1;
    unsigned int get_threshold = rate->pitch;
    unsigned int pos;

    awalsa_debug("\n");
    for (channel = 0; channel < rate->channels; ++channel) {
        const snd_pcm_channel_area_t *src_area = &src_areas[channel];
        const snd_pcm_channel_area_t *dst_area = &dst_areas[channel];
        const int16_t *src;
        int16_t *dst;
        int src_step, dst_step;
        int16_t old_sample = 0;
        int16_t new_sample;
        int old_weight, new_weight;
        src = snd_pcm_channel_area_addr(src_area, src_offset);
        dst = snd_pcm_channel_area_addr(dst_area, dst_offset);
        src_step = snd_pcm_channel_area_step(src_area) >> 1;
        dst_step = snd_pcm_channel_area_step(dst_area) >> 1;
        src_frames1 = 0;
        dst_frames1 = 0;
        new_sample = rate->old_sample[channel];
        pos = get_threshold;
        while (dst_frames1 < dst_frames) {
            if (pos >= get_threshold) {
                pos -= get_threshold;
                old_sample = new_sample;
                if (src_frames1 < src_frames)
                    new_sample = *src;
            }
            new_weight = (pos << (16 - rate->pitch_shift)) / (get_threshold >> rate->pitch_shift);
            old_weight = 0x10000 - new_weight;
            *dst = (old_sample * old_weight + new_sample * new_weight) >> 16;
            dst += dst_step;
            dst_frames1++;
            pos += LINEAR_DIV;
            if (pos >= get_threshold) {
                src += src_step;
                src_frames1++;
            }
        }
        rate->old_sample[channel] = new_sample;
    }
}

static void linear_shrink(struct rate_linear *rate,
              const snd_pcm_channel_area_t *dst_areas,
              snd_pcm_uframes_t dst_offset, unsigned int dst_frames,
              const snd_pcm_channel_area_t *src_areas,
              snd_pcm_uframes_t src_offset, unsigned int src_frames)
{
#define GET16_LABELS
#define PUT16_LABELS
#include "plugin_ops.h"
#undef GET16_LABELS
#undef PUT16_LABELS
    void *get = get16_labels[rate->get_idx];
    void *put = put16_labels[rate->put_idx];
    unsigned int get_increment = rate->pitch;
    unsigned int channel;
    unsigned int src_frames1;
    unsigned int dst_frames1;
    int16_t sample = 0;
    unsigned int pos;

    for (channel = 0; channel < rate->channels; ++channel) {
        const snd_pcm_channel_area_t *src_area = &src_areas[channel];
        const snd_pcm_channel_area_t *dst_area = &dst_areas[channel];
        const char *src;
        char *dst;
        int src_step, dst_step;
        int16_t old_sample = 0;
        int16_t new_sample = 0;
        int old_weight, new_weight;
        pos = LINEAR_DIV - get_increment; /* Force first sample to be copied */
        src = snd_pcm_channel_area_addr(src_area, src_offset);
        dst = snd_pcm_channel_area_addr(dst_area, dst_offset);
        src_step = snd_pcm_channel_area_step(src_area);
        dst_step = snd_pcm_channel_area_step(dst_area);
        src_frames1 = 0;
        dst_frames1 = 0;
        while (src_frames1 < src_frames) {

            goto *get;
#define GET16_END after_get
#include "plugin_ops.h"
#undef GET16_END
        after_get:
            new_sample = sample;
            src += src_step;
            src_frames1++;
            pos += get_increment;
            if (pos >= LINEAR_DIV) {
                pos -= LINEAR_DIV;
                old_weight = (pos << (32 - LINEAR_DIV_SHIFT)) / (get_increment >> (LINEAR_DIV_SHIFT - 16));
                new_weight = 0x10000 - old_weight;
                sample = (old_sample * old_weight + new_sample * new_weight) >> 16;
                goto *put;
#define PUT16_END after_put
#include "plugin_ops.h"
#undef PUT16_END
            after_put:
                dst += dst_step;
                dst_frames1++;
                if (dst_frames1 > dst_frames) {
                    awalsa_err("dst_frames overflow");
                    break;
                }
            }
            old_sample = new_sample;
        }
    }
}

/* optimized version for S16 format */
static void linear_shrink_s16(struct rate_linear *rate,
                  const snd_pcm_channel_area_t *dst_areas,
                  snd_pcm_uframes_t dst_offset, unsigned int dst_frames,
                  const snd_pcm_channel_area_t *src_areas,
                  snd_pcm_uframes_t src_offset, unsigned int src_frames)
{
    unsigned int get_increment = rate->pitch;
    unsigned int channel;
    unsigned int src_frames1;
    unsigned int dst_frames1;
    unsigned int pos = 0;

    for (channel = 0; channel < rate->channels; ++channel) {
        const snd_pcm_channel_area_t *src_area = &src_areas[channel];
        const snd_pcm_channel_area_t *dst_area = &dst_areas[channel];
        const int16_t *src;
        int16_t *dst;
        int src_step, dst_step;
        int16_t old_sample = 0;
        int16_t new_sample = 0;
        int old_weight, new_weight;
        pos = LINEAR_DIV - get_increment; /* Force first sample to be copied */
        src = snd_pcm_channel_area_addr(src_area, src_offset);
        dst = snd_pcm_channel_area_addr(dst_area, dst_offset);
        src_step = snd_pcm_channel_area_step(src_area) >> 1;
        dst_step = snd_pcm_channel_area_step(dst_area) >> 1 ;
        src_frames1 = 0;
        dst_frames1 = 0;
        while (src_frames1 < src_frames) {

            new_sample = *src;
            src += src_step;
            src_frames1++;
            pos += get_increment;
            if (pos >= LINEAR_DIV) {
                pos -= LINEAR_DIV;
                old_weight = (pos << (32 - LINEAR_DIV_SHIFT)) / (get_increment >> (LINEAR_DIV_SHIFT - 16));
                new_weight = 0x10000 - old_weight;
                *dst = (old_sample * old_weight + new_sample * new_weight) >> 16;
                dst += dst_step;
                dst_frames1++;
                if (dst_frames1 > dst_frames) {
                    awalsa_err("dst_frames overflow");
                    break;
                }
            }
            old_sample = new_sample;
        }
    }
}

static void linear_convert(void *obj,
               const snd_pcm_channel_area_t *dst_areas,
               snd_pcm_uframes_t dst_offset, unsigned int dst_frames,
               const snd_pcm_channel_area_t *src_areas,
               snd_pcm_uframes_t src_offset, unsigned int src_frames)
{
    struct rate_linear *rate = obj;
    rate->func(rate, dst_areas, dst_offset, dst_frames,
           src_areas, src_offset, src_frames);
}

static void linear_free(void *obj)
{
    struct rate_linear *rate = obj;

    free(rate->old_sample);
    rate->old_sample = NULL;
}

extern int snd_pcm_linear_get_index(snd_pcm_format_t src_format, snd_pcm_format_t dst_format);
extern int snd_pcm_linear_put_index(snd_pcm_format_t src_format, snd_pcm_format_t dst_format);
static int linear_init(void *obj, snd_pcm_rate_info_t *info)
{
    struct rate_linear *rate = obj;

    awalsa_debug("\n");
    rate->get_idx = snd_pcm_linear_get_index(info->in.format, SND_PCM_FORMAT_S16_LE);
    rate->put_idx = snd_pcm_linear_put_index(SND_PCM_FORMAT_S16_LE, info->out.format);
    if (info->in.rate < info->out.rate) {
        if (info->in.format == info->out.format && info->in.format == SND_PCM_FORMAT_S16_LE)
            rate->func = linear_expand_s16;
        else
            rate->func = linear_expand;
        /* pitch is get_threshold */
    } else {
        if (info->in.format == info->out.format && info->in.format == SND_PCM_FORMAT_S16_LE)
            rate->func = linear_shrink_s16;
        else
            rate->func = linear_shrink;
        /* pitch is get_increment */
    }
    rate->pitch = (((u_int64_t)info->out.rate * LINEAR_DIV) +
               (info->in.rate / 2)) / info->in.rate;
    rate->channels = info->channels;

    free(rate->old_sample);
    awalsa_debug("rate->channels %d , sizeof(*rate->old_sample)is %d  \n", rate->channels, sizeof(*rate->old_sample));
    rate->old_sample = malloc(sizeof(*rate->old_sample) * rate->channels);
    if (! rate->old_sample)
        return -ENOMEM;

    return 0;
}

static int linear_adjust_pitch(void *obj, snd_pcm_rate_info_t *info)
{
    struct rate_linear *rate = obj;
    snd_pcm_uframes_t cframes;

    awalsa_debug("\n");
    rate->pitch = (((u_int64_t)info->out.period_size * LINEAR_DIV) +
            (info->in.period_size/2) ) / info->in.period_size;

    cframes = input_frames(rate, info->out.period_size);
    awalsa_debug("out.period_size = %d\n", info->out.period_size);
    while (cframes != info->in.period_size) {
        snd_pcm_uframes_t cframes_new;
        if (cframes > info->in.period_size)
            rate->pitch++;
        else
            rate->pitch--;
        cframes_new = input_frames(rate, info->out.period_size);
        if ((cframes > info->in.period_size && cframes_new < info->in.period_size) ||
            (cframes < info->in.period_size && cframes_new > info->in.period_size)) {
            awalsa_err("invalid pcm period_size %ld -> %ld",
                   info->in.period_size, info->out.period_size);
            return -EIO;
        }
        cframes = cframes_new;
    }
    awalsa_debug("\n");
    if (rate->pitch >= LINEAR_DIV) {
        /* shift for expand linear interpolation */
        rate->pitch_shift = 0;
        while ((rate->pitch >> rate->pitch_shift) >= (1 << 16))
            rate->pitch_shift++;
    }
    return 0;
}

static void linear_reset(void *obj)
{
    struct rate_linear *rate = obj;

    /* for expand */
    if (rate->old_sample)
        memset(rate->old_sample, 0, sizeof(*rate->old_sample) * rate->channels);
}

static void linear_close(void *obj)
{
    free(obj);
}

static int get_supported_rates(ATTRIBUTE_UNUSED void *rate,
                   unsigned int *rate_min, unsigned int *rate_max)
{
    *rate_min = SND_PCM_PLUGIN_RATE_MIN;
    *rate_max = SND_PCM_PLUGIN_RATE_MAX;
    return 0;
}

static const snd_pcm_rate_ops_t linear_ops = {
    .close = linear_close,
    .init = linear_init,
    .free = linear_free,
    .reset = linear_reset,
    .adjust_pitch = linear_adjust_pitch,
    .convert = linear_convert,
    .input_frames = input_frames,
    .output_frames = output_frames,
    .version = SND_PCM_RATE_PLUGIN_VERSION,
    .get_supported_rates = get_supported_rates,
};

int SND_PCM_RATE_PLUGIN_ENTRY(linear) (ATTRIBUTE_UNUSED unsigned int version,
                       void **objp, snd_pcm_rate_ops_t *ops)
{
    struct rate_linear *rate;

    rate = calloc(1, sizeof(*rate));
    if (! rate)
        return -ENOMEM;

    *objp = rate;
    *ops = linear_ops;
    return 0;
}
