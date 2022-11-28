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
#include "pcm_generic.h"
#include "pcm_plugin_generic.h"
#include "plugin_ops.h"
#include "bswap.h"
#include <aw_list.h>
#include <aw_common.h>

struct _snd_pcm_rate {
    snd_pcm_generic_t gen;
    snd_pcm_uframes_t appl_ptr, hw_ptr, last_slave_hw_ptr;
    snd_pcm_uframes_t last_commit_ptr;
    snd_pcm_uframes_t orig_avail_min;
    snd_pcm_sw_params_t sw_params;
    snd_pcm_format_t sformat;
    unsigned int srate;
    snd_pcm_channel_area_t *pareas; /* areas for splitted period (rate pcm) */
    snd_pcm_channel_area_t *sareas; /* areas for splitted period (slave pcm) */
    snd_pcm_rate_info_t info;
    void *open_func;
    void *obj;
    snd_pcm_rate_ops_t ops;
    unsigned int get_idx;
    unsigned int put_idx;
    int16_t *src_buf;
    int16_t *dst_buf;
    int start_pending; /* start is triggered but not commited to slave */
    //snd_htimestamp_t trigger_tstamp;
    unsigned int plugin_version;
    unsigned int rate_min, rate_max;
};


static int snd_pcm_rate_hw_refine_cprepare(snd_pcm_t *pcm ATTRIBUTE_UNUSED, snd_pcm_hw_params_t *params)
{
    snd_pcm_rate_t *rate = pcm->private_data;
    int err;
    snd_interval_t access_mask = { .mask = SND_PCM_ACCBIT_SHM };
    snd_interval_t format_mask = { .mask = SND_PCM_FMTBIT_LINEAR };

    awalsa_debug("\n");

    err = _snd_pcm_hw_param_set_mask(params, SND_PCM_HW_PARAM_ACCESS,
                     &access_mask);
    if (err < 0)
        return err;
    err = _snd_pcm_hw_param_set_mask(params, SND_PCM_HW_PARAM_FORMAT,
                     &format_mask);
    if (err < 0)
        return err;
    if (rate->rate_min) {
        err = _snd_pcm_hw_param_set_min(params, SND_PCM_HW_PARAM_RATE,
                        rate->rate_min, 0);
        if (err < 0)
            return err;
    }
    if (rate->rate_max) {
        err = _snd_pcm_hw_param_set_max(params, SND_PCM_HW_PARAM_RATE,
                        rate->rate_max, 0);
        if (err < 0)
            return err;
    }
#if 0
    params->info &= ~(SND_PCM_INFO_MMAP | SND_PCM_INFO_MMAP_VALID);
#endif
    return 0;
}

static int snd_pcm_rate_hw_refine_sprepare(snd_pcm_t *pcm, snd_pcm_hw_params_t *sparams)
{
    snd_pcm_rate_t *rate = pcm->private_data;
    snd_interval_t saccess_mask = { .mask = SND_PCM_ACCBIT_MMAP };

    awalsa_debug("\n");

    _snd_pcm_hw_params_any(sparams);
    _snd_pcm_hw_param_set_mask(sparams, SND_PCM_HW_PARAM_ACCESS,
                   &saccess_mask);
    if (rate->sformat != SND_PCM_FORMAT_UNKNOWN) {
        _snd_pcm_hw_param_set(sparams, SND_PCM_HW_PARAM_FORMAT,
                      (unsigned long) rate->sformat, 0);
    }
    _snd_pcm_hw_param_set_minmax(sparams, SND_PCM_HW_PARAM_RATE,
                     rate->srate, 0, rate->srate + 1, -1);
    return 0;
}

static int snd_pcm_rate_hw_refine_schange(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
                      snd_pcm_hw_params_t *sparams)
{
    snd_pcm_rate_t *rate = pcm->private_data;
    snd_interval_t t, buffer_size;
    const snd_interval_t *srate, *crate;
    int err;
    unsigned int links = (SND_PCM_HW_PARBIT_CHANNELS |
                  SND_PCM_HW_PARBIT_PERIOD_TIME);

    awalsa_debug("\n");

    if (rate->sformat == SND_PCM_FORMAT_UNKNOWN)
        links |= (SND_PCM_HW_PARBIT_FORMAT |
              SND_PCM_HW_PARBIT_SAMPLE_BITS |
              SND_PCM_HW_PARBIT_FRAME_BITS);
    snd_range_copy(&buffer_size, hw_param_interval_c(params, SND_PCM_HW_PARAM_BUFFER_SIZE));
    snd_range_unfloor(&buffer_size);
    crate = hw_param_interval_c(params, SND_PCM_HW_PARAM_RATE);
    srate = hw_param_interval_c(sparams, SND_PCM_HW_PARAM_RATE);
    snd_range_muldiv(&buffer_size, srate, crate, &t);
    err = _snd_pcm_hw_param_set_range(sparams, SND_PCM_HW_PARAM_BUFFER_SIZE, &t);
    if (err < 0)
        return err;
    err = _snd_pcm_hw_params_refine(sparams, links, params);
    if (err < 0)
        return err;
    return 0;
}

static int snd_pcm_rate_hw_refine_cchange(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
                      snd_pcm_hw_params_t *sparams)
{
    snd_pcm_rate_t *rate = pcm->private_data;
    snd_interval_t t;
    const snd_interval_t *sbuffer_size, *buffer_size;
    const snd_interval_t *srate, *crate;
    int err;
    unsigned int links = (SND_PCM_HW_PARBIT_CHANNELS |
                  SND_PCM_HW_PARBIT_PERIOD_TIME);

    awalsa_debug("\n");

    if (rate->sformat == SND_PCM_FORMAT_UNKNOWN)
        links |= (SND_PCM_HW_PARBIT_FORMAT |
              SND_PCM_HW_PARBIT_SAMPLE_BITS |
              SND_PCM_HW_PARBIT_FRAME_BITS);
    sbuffer_size = hw_param_interval_c(sparams, SND_PCM_HW_PARAM_BUFFER_SIZE);
    crate = hw_param_interval_c(params, SND_PCM_HW_PARAM_RATE);
    srate = hw_param_interval_c(sparams, SND_PCM_HW_PARAM_RATE);
    snd_range_muldiv(sbuffer_size, crate, srate, &t);
    snd_range_floor(&t);
    err = _snd_pcm_hw_param_set_range(params, SND_PCM_HW_PARAM_BUFFER_SIZE, &t);
    if (err < 0)
        return err;
    buffer_size = hw_param_interval_c(params, SND_PCM_HW_PARAM_BUFFER_SIZE);
    /*
     * this condition probably needs more work:
     *   in case when the buffer_size is known and we are looking
     *   for best period_size, we should prefer situation when
     *   (buffer_size / period_size) * period_size == buffer_size
     */
    if (snd_range_single(buffer_size) && buffer_size->range.integer) {
        snd_interval_t *period_size;
        period_size = hw_param_interval(params, SND_PCM_HW_PARAM_PERIOD_SIZE);
        if (!snd_range_checkempty(period_size) &&
            period_size->range.openmin && period_size->range.openmax &&
            period_size->range.min + 1 == period_size->range.max) {
            if (period_size->range.min > 0 &&
                    (buffer_size->range.min / period_size->range.min)
                        * period_size->range.min
                        == buffer_size->range.min) {
                snd_range_set_value(period_size, period_size->range.min);
            } else if ((buffer_size->range.max / period_size->range.max)
                    * period_size->range.max
                    == buffer_size->range.max) {
                snd_range_set_value(period_size, period_size->range.max);
            }
        }
    }
#ifdef REFINE_DEBUG
    awalsa_info("REFINE (params):\n");
    snd_pcm_hw_params_dump(params);
    awalsa_info("REFINE (slave params):\n");
    snd_pcm_hw_params_dump(sparams);
#endif
    err = _snd_pcm_hw_params_refine(params, links, sparams);
#ifdef REFINE_DEBUG
    awalsa_info("********************\n");
    awalsa_info("REFINE (params) (%i):\n", err);
    snd_pcm_hw_params_dump(params);
    awalsa_info("REFINE (slave params):\n");
    snd_pcm_hw_params_dump(sparams);
#endif
    if (err < 0)
        return err;
    return 0;
}

static int snd_pcm_rate_hw_refine(snd_pcm_t *pcm,
                  snd_pcm_hw_params_t *params)
{
#if 0
    snd_pcm_rate_t *rate = pcm->private_data;
    snd_pcm_t *spcm = rate->gen.slave;
    return spcm->ops->hw_refine(spcm->op_arg, params);
#endif
    return snd_pcm_hw_refine_slave(pcm, params,
                       snd_pcm_rate_hw_refine_cprepare,
                       snd_pcm_rate_hw_refine_cchange,
                       snd_pcm_rate_hw_refine_sprepare,
                       snd_pcm_rate_hw_refine_schange,
                       snd_pcm_generic_hw_refine);
}

#if 0
static inline void _div64_32(u_int64_t *n, uint32_t d, uint32_t *rem)
{
    *rem = *n % d;
    *n /= d;
}

static inline unsigned int _muldiv32(unsigned int a, unsigned int b, unsigned int c)
{
    uint32_t rem;
    u_int64_t n = (u_int64_t) (a * b);

    _div64_32(&n, c, &rem);
    return n;
}
#endif

static int snd_pcm_rate_hw_params(snd_pcm_t *pcm, snd_pcm_hw_params_t * params)
{
    snd_pcm_rate_t *rate = pcm->private_data;
    snd_pcm_t *slave = rate->gen.slave;
    snd_pcm_rate_side_info_t *sinfo, *cinfo;
    unsigned int channels, cwidth, swidth, chn;
    int err = 0;

#if 0
    unsigned int sbuffer_size, speriod_size;
    snd_pcm_hw_params_t *slave_params;
    snd_pcm_hw_params_alloca(&slave_params);
    memcpy(slave_params, params, sizeof(snd_pcm_hw_params_t));

    snd_pcm_hw_param_change(slave_params, SND_PCM_HW_PARAM_ACCESS);
    err = snd_pcm_hw_params_set_access(slave, slave_params, SND_PCM_ACCESS_MMAP_INTERLEAVED);
    if (err < 0) {
        awalsa_err("snd_pcm_hw_params_set_access failed\n");
        return err;
    }
    if (slave->rate != pcm->rate)
        err = snd_pcm_hw_params_set_rate(slave, slave_params, slave->rate, NULL);
    if (err < 0) {
        awalsa_err("snd_pcm_hw_params_set_rate failed\n");
        return err;
    }
#else
    err = snd_pcm_hw_params_slave(pcm, params,
            snd_pcm_rate_hw_refine_cchange,
            snd_pcm_rate_hw_refine_sprepare,
            snd_pcm_rate_hw_refine_schange,
            snd_pcm_generic_hw_params);
    if (err < 0)
        return err;
#endif

    if (pcm->stream == SND_PCM_STREAM_PLAYBACK) {
        cinfo = &rate->info.in;
        sinfo = &rate->info.out;
    } else {
        sinfo = &rate->info.in;
        cinfo = &rate->info.out;
    }
    err = snd_pcm_hw_params_get_format(params, &cinfo->format);
    if (err < 0)
        return err;
    err = snd_pcm_hw_params_get_rate(params, &cinfo->rate, 0);
    if (err < 0)
        return err;
    err = snd_pcm_hw_params_get_period_size(params, &cinfo->period_size, 0);
    if (err < 0)
        return err;
    err = snd_pcm_hw_params_get_buffer_size(params, &cinfo->buffer_size);
    if (err < 0)
        return err;
    err = snd_pcm_hw_params_get_channels(params, &channels);
    if (err < 0)
        return err;

#if 0
    sbuffer_size = _muldiv32(cinfo->buffer_size, slave->rate, cinfo->rate);
    speriod_size = _muldiv32(cinfo->period_size, slave->rate, cinfo->rate);
    err = snd_pcm_hw_params_set_buffer_size(slave, slave_params, sbuffer_size);
    if (err < 0) {
        awalsa_err("snd_pcm_hw_params_set_buffer_size failed\n");
        return err;
    }

    err = snd_pcm_hw_params_set_period_size(slave, slave_params, speriod_size, NULL);
    if (err < 0) {
        awalsa_err("snd_pcm_hw_params_set_period_size failed\n");
        return err;
    }

    err = _snd_pcm_hw_params_internal(slave, slave_params);
    if (err < 0) {
        awalsa_err("failed to set slave params\n");
        return err;
    }

    /* TODO: temp solution */
    memcpy(params, slave_params, sizeof(snd_pcm_hw_params_t));
    snd_pcm_hw_param_change(params, SND_PCM_HW_PARAM_BUFFER_SIZE);
    snd_pcm_hw_params_set_buffer_size(pcm, params, cinfo->buffer_size);
    snd_pcm_hw_param_change(params, SND_PCM_HW_PARAM_PERIOD_SIZE);
    snd_pcm_hw_params_set_period_size(pcm, params, cinfo->period_size, NULL);
    if (sbuffer_size != slave->buffer_size) {
        cinfo->buffer_size = _muldiv32(slave->buffer_size, cinfo->rate, slave->rate);
        /*cinfo->buffer_size++;*/
        snd_pcm_hw_param_change(params, SND_PCM_HW_PARAM_BUFFER_SIZE);
        err = snd_pcm_hw_params_set_buffer_size(pcm, params, cinfo->buffer_size);
        if (err < 0) {
            awalsa_err("snd_pcm_hw_params_set_buffer_size failed\n");
            return err;
        }
    }
    if (speriod_size != slave->period_size) {
        cinfo->period_size = cinfo->buffer_size / (slave->buffer_size / slave->period_size);
        snd_pcm_hw_param_change(params, SND_PCM_HW_PARAM_PERIOD_SIZE);
        err = snd_pcm_hw_params_set_period_size(pcm, params, cinfo->period_size, NULL);
        if (err < 0) {
            awalsa_err("snd_pcm_hw_params_set_period_size failed\n");
            return err;
        }
    }
#endif

    rate->info.channels = channels;
    sinfo->format = slave->format;
    sinfo->rate = slave->rate;
    sinfo->buffer_size = slave->buffer_size;
    sinfo->period_size = slave->period_size;

    awalsa_debug("out rate %d  \n", sinfo->rate);
    awalsa_debug("in rate %d  \n", cinfo->rate);
    if (rate->pareas) {
        awalsa_err("rate plugin already in use");
        return -EBUSY;
    }
    err = rate->ops.init(rate->obj, &rate->info);
    if (err < 0)
        return err;

    awalsa_debug("\n");
    rate->pareas = malloc(2 * channels * sizeof(*rate->pareas));
    if (rate->pareas == NULL)
        goto error;

    cwidth = snd_pcm_format_physical_width(cinfo->format);
    swidth = snd_pcm_format_physical_width(sinfo->format);
    rate->pareas[0].addr = malloc(((cwidth * channels * cinfo->period_size) / 8) +
                      ((swidth * channels * sinfo->period_size) / 8));

    if (rate->pareas[0].addr == NULL)
        goto error;

    rate->sareas = rate->pareas + channels;
    rate->sareas[0].addr = (char *)rate->pareas[0].addr + ((cwidth * channels * cinfo->period_size) / 8);
    for (chn = 0; chn < channels; chn++) {
        rate->pareas[chn].addr = rate->pareas[0].addr + (cwidth * chn * cinfo->period_size) / 8;
        rate->pareas[chn].first = 0;
        rate->pareas[chn].step = cwidth;
        rate->sareas[chn].addr = rate->sareas[0].addr + (swidth * chn * sinfo->period_size) / 8;
        rate->sareas[chn].first = 0;
        rate->sareas[chn].step = swidth;
    }

    if (rate->ops.convert_s16 || rate->ops.convert_s16_fix) {
        rate->get_idx = snd_pcm_linear_get_index(rate->info.in.format, SND_PCM_FORMAT_S16_LE);
        rate->put_idx = snd_pcm_linear_put_index(SND_PCM_FORMAT_S16_LE, rate->info.out.format);
        if (rate->src_buf != NULL)
            free(rate->src_buf);
        rate->src_buf = malloc(channels * rate->info.in.period_size * 2);
        if (rate->dst_buf != NULL)
            free(rate->dst_buf);
        rate->dst_buf = malloc(channels * rate->info.out.period_size * 2);
        if (! rate->src_buf || ! rate->dst_buf)
            goto error;
    }

    return 0;

 error:
    if (rate->pareas) {
        free(rate->pareas[0].addr);
        free(rate->pareas);
        rate->pareas = NULL;
    }
    if (rate->ops.free)
        rate->ops.free(rate->obj);
    return -ENOMEM;
}

static int snd_pcm_rate_hw_free(snd_pcm_t *pcm)
{
    snd_pcm_rate_t *rate = pcm->private_data;
    awalsa_debug("\n");
    if (rate->pareas) {
        free(rate->pareas[0].addr);
        free(rate->pareas);
        rate->pareas = NULL;
        rate->sareas = NULL;
    }
    if (rate->ops.free)
        rate->ops.free(rate->obj);
    free(rate->src_buf);
    free(rate->dst_buf);
    rate->src_buf = rate->dst_buf = NULL;
    return snd_pcm_hw_free(rate->gen.slave);
}

static void recalc(snd_pcm_t *pcm, snd_pcm_uframes_t *val)
{
    snd_pcm_rate_t *rate = pcm->private_data;
    snd_pcm_t *slave = rate->gen.slave;
    unsigned long div;

    awalsa_debug("\n");
    if (*val == pcm->buffer_size) {
        *val = slave->buffer_size;
    } else {
        div = *val / pcm->period_size;
        if (div * pcm->period_size == *val)
            *val = div * slave->period_size;
        else
            *val = muldiv_near(*val, slave->period_size, pcm->period_size);
    }
}

static int snd_pcm_rate_sw_params(snd_pcm_t *pcm, snd_pcm_sw_params_t * params)
{
    snd_pcm_rate_t *rate = pcm->private_data;
    snd_pcm_t *slave = rate->gen.slave;
    snd_pcm_sw_params_t *sparams;
    snd_pcm_uframes_t boundary1, boundary2, sboundary;
    int err;

    awalsa_debug("\n");
    sparams = &rate->sw_params;
    err = snd_pcm_sw_params_current(slave, sparams);
    if (err < 0)
        return err;
    sboundary = sparams->boundary;
    *sparams = *params;
    boundary1 = pcm->buffer_size;
    boundary2 = slave->buffer_size;
    while (boundary1 * 2 <= LONG_MAX - pcm->buffer_size &&
           boundary2 * 2 <= LONG_MAX - slave->buffer_size) {
        boundary1 *= 2;
        boundary2 *= 2;
    }
    params->boundary = boundary1;
    sparams->boundary = sboundary;

    if (rate->ops.adjust_pitch)
        rate->ops.adjust_pitch(rate->obj, &rate->info);

    recalc(pcm, &sparams->avail_min);
    rate->orig_avail_min = sparams->avail_min;
    recalc(pcm, &sparams->start_threshold);
    if (sparams->avail_min < 1) sparams->avail_min = 1;
    if (sparams->start_threshold <= slave->buffer_size) {
        if (sparams->start_threshold > (slave->buffer_size / sparams->avail_min) * sparams->avail_min)
            sparams->start_threshold = (slave->buffer_size / sparams->avail_min) * sparams->avail_min;
    }
    if (sparams->stop_threshold >= params->boundary) {
        sparams->stop_threshold = sparams->boundary;
    } else {
        recalc(pcm, &sparams->stop_threshold);
    }
    awalsa_debug("\n");
    /* no use */
    //recalc(pcm, &sparams->silence_threshold);
    if (sparams->silence_size >= params->boundary) {
        sparams->silence_size = sparams->boundary;
    } else {
        recalc(pcm, &sparams->silence_size);
    }
    awalsa_debug("\n");
    return snd_pcm_sw_params(slave, sparams);
}

static int snd_pcm_rate_init(snd_pcm_t *pcm)
{
    snd_pcm_rate_t *rate = pcm->private_data;

    awalsa_debug("\n");
    if (rate->ops.reset)
        rate->ops.reset(rate->obj);
    rate->last_commit_ptr = 0;
    rate->start_pending = 0;
    return 0;
}

static void convert_to_s16(snd_pcm_rate_t *rate, int16_t *buf,
               const snd_pcm_channel_area_t *areas,
               snd_pcm_uframes_t offset, unsigned int frames,
               unsigned int channels)
{
#ifndef DOC_HIDDEN
#define GET16_LABELS
#include "plugin_ops.h"
#undef GET16_LABELS
#endif /* DOC_HIDDEN */
    void *get = get16_labels[rate->get_idx];
    const char *src;
    int16_t sample = 0;
    const char *srcs[channels];
    int src_step[channels];
    unsigned int c;

    awalsa_debug("\n");
    for (c = 0; c < channels; c++) {
        srcs[c] = snd_pcm_channel_area_addr(areas + c, offset);
        src_step[c] = snd_pcm_channel_area_step(areas + c);
    }

    while (frames--) {
        for (c = 0; c < channels; c++) {
            src = srcs[c];
            goto *get;
#ifndef DOC_HIDDEN
#define GET16_END after_get
#include "plugin_ops.h"
#undef GET16_END
#endif /* DOC_HIDDEN */
        after_get:
            *buf++ = sample;
            srcs[c] += src_step[c];
        }
    }
}

static void convert_from_s16(snd_pcm_rate_t *rate, const int16_t *buf,
                 const snd_pcm_channel_area_t *areas,
                 snd_pcm_uframes_t offset, unsigned int frames,
                 unsigned int channels)
{
#ifndef DOC_HIDDEN
#define PUT16_LABELS
#include "plugin_ops.h"
#undef PUT16_LABELS
#endif /* DOC_HIDDEN */
    void *put = put16_labels[rate->put_idx];
    char *dst;
    int16_t sample;
    char *dsts[channels];
    int dst_step[channels];
    unsigned int c;

    awalsa_debug("\n");
    for (c = 0; c < channels; c++) {
        dsts[c] = snd_pcm_channel_area_addr(areas + c, offset);
        dst_step[c] = snd_pcm_channel_area_step(areas + c);
    }

    while (frames--) {
        for (c = 0; c < channels; c++) {
            dst = dsts[c];
            sample = *buf++;
            goto *put;
#ifndef DOC_HIDDEN
#define PUT16_END after_put
#include "plugin_ops.h"
#undef PUT16_END
#endif /* DOC_HIDDEN */
        after_put:
            dsts[c] += dst_step[c];
        }
    }
}

static void do_convert(const snd_pcm_channel_area_t *dst_areas,
               snd_pcm_uframes_t dst_offset, unsigned int dst_frames,
               const snd_pcm_channel_area_t *src_areas,
               snd_pcm_uframes_t src_offset, unsigned int src_frames,
               unsigned int channels,
               snd_pcm_rate_t *rate)
{
    awalsa_debug("\n");
    if (rate->ops.convert_s16) {
        const int16_t *src;
        int16_t *dst;
        if (! rate->src_buf)
            src = src_areas->addr + src_offset * 2 * channels;
        else {
            convert_to_s16(rate, rate->src_buf, src_areas, src_offset,
                       src_frames, channels);
            src = rate->src_buf;
        }
        if (! rate->dst_buf)
            dst = dst_areas->addr + dst_offset * 2 * channels;
        else
            dst = rate->dst_buf;
        rate->ops.convert_s16(rate->obj, dst, dst_frames, src, src_frames);
        if (dst == rate->dst_buf)
            convert_from_s16(rate, rate->dst_buf, dst_areas, dst_offset,
                     dst_frames, channels);
    } else {
        rate->ops.convert(rate->obj, dst_areas, dst_offset, dst_frames,
                   src_areas, src_offset, src_frames);
    }
}

#ifdef SND_PCM_RATE_FIX_PERIOD_SIZE
static void do_convert_fix(const snd_pcm_channel_area_t *dst_areas,
               snd_pcm_uframes_t dst_offset, unsigned int *dst_frames,
               const snd_pcm_channel_area_t *src_areas,
               snd_pcm_uframes_t src_offset, unsigned int *src_frames,
               unsigned int channels,
               snd_pcm_rate_t *rate)
{
    awalsa_debug("\n");
    if (rate->ops.convert_s16_fix) {
        const int16_t *src;
        int16_t *dst;
        if (! rate->src_buf)
            src = src_areas->addr + src_offset * 2 * channels;
        else {
            convert_to_s16(rate, rate->src_buf, src_areas, src_offset,
                       *src_frames, channels);
            src = rate->src_buf;
        }
        if (! rate->dst_buf)
            dst = dst_areas->addr + dst_offset * 2 * channels;
        else
            dst = rate->dst_buf;
        rate->ops.convert_s16_fix(rate->obj, dst, dst_frames, src, src_frames);
        if (dst == rate->dst_buf)
            convert_from_s16(rate, rate->dst_buf, dst_areas, dst_offset,
                     *dst_frames, channels);
    } else {
        awalsa_err("unsupport...\n");
    }
}

static inline void
snd_pcm_rate_write_areas1_fix(snd_pcm_t *pcm,
             const snd_pcm_channel_area_t *areas,
             snd_pcm_uframes_t offset,
             const snd_pcm_channel_area_t *slave_areas,
             snd_pcm_uframes_t slave_offset,
            snd_pcm_uframes_t *input_frames,
            snd_pcm_uframes_t *output_frames)
{
    snd_pcm_rate_t *rate = pcm->private_data;
    unsigned int src_frames = pcm->period_size;
    unsigned int dst_frames = rate->gen.slave->period_size;
    awalsa_debug("\n");

    if (input_frames != NULL)
        src_frames = *input_frames;
    if (output_frames != NULL)
        dst_frames = *output_frames;
    do_convert_fix(slave_areas, slave_offset, &dst_frames,
           areas, offset, &src_frames,
           pcm->channels, rate);
    #if 0
    if (src_frames != pcm->period_size) {
        awalsa_err("src_frames modify...%u->%u\n", pcm->period_size, src_frames);
    }
    if (dst_frames != rate->gen.slave->period_size) {
        awalsa_err("dst_frames modify...%u->%u\n", rate->gen.slave->period_size, dst_frames);
    }
    #endif
    if (input_frames != NULL)
        *input_frames = src_frames;
    if (output_frames != NULL)
        *output_frames = dst_frames;
}
#else
static inline void
snd_pcm_rate_write_areas1(snd_pcm_t *pcm,
             const snd_pcm_channel_area_t *areas,
             snd_pcm_uframes_t offset,
             const snd_pcm_channel_area_t *slave_areas,
             snd_pcm_uframes_t slave_offset)
{
    snd_pcm_rate_t *rate = pcm->private_data;
    awalsa_debug("\n");
    do_convert(slave_areas, slave_offset, rate->gen.slave->period_size,
           areas, offset, pcm->period_size,
           pcm->channels, rate);
}
#endif

static inline void
snd_pcm_rate_read_areas1(snd_pcm_t *pcm,
             const snd_pcm_channel_area_t *areas,
             snd_pcm_uframes_t offset,
             const snd_pcm_channel_area_t *slave_areas,
             snd_pcm_uframes_t slave_offset)
{
    snd_pcm_rate_t *rate = pcm->private_data;

    awalsa_debug("\n");
    do_convert(areas, offset, pcm->period_size,
           slave_areas, slave_offset, rate->gen.slave->period_size,
           pcm->channels, rate);
}

#ifdef SND_PCM_RATE_FIX_PERIOD_SIZE
static inline void snd_pcm_rate_sync_hwptr0(snd_pcm_t *pcm, snd_pcm_uframes_t slave_hw_ptr)
{
    snd_pcm_rate_t *rate = pcm->private_data;

    snd_pcm_sframes_t slave_hw_ptr_diff = slave_hw_ptr - rate->last_slave_hw_ptr;
    snd_pcm_sframes_t last_slave_hw_ptr_frac;

    awalsa_debug("\n");
    if (pcm->stream != SND_PCM_STREAM_PLAYBACK)
        return;

    /* TODO: slave_hw_ptr_diff += rate->gen.slave->boundary? */
    if (slave_hw_ptr_diff < 0)
        slave_hw_ptr_diff += rate->gen.slave->boundary; /* slave boundary wraparound */
    else if (slave_hw_ptr_diff == 0)
        return;
    last_slave_hw_ptr_frac = rate->last_slave_hw_ptr % rate->gen.slave->rate;

#if 0
    printf("hw_ptr=%u, last_slave_hw_ptr_frac=%u, slave_hw_ptr_diff=%u, %u, fractional 1=%u, 2=%u\n",
            rate->hw_ptr, last_slave_hw_ptr_frac, slave_hw_ptr_diff,
            (((last_slave_hw_ptr_frac + slave_hw_ptr_diff) / rate->gen.slave->rate) * pcm->rate),
            rate->ops.input_frames(rate->obj, last_slave_hw_ptr_frac),
            rate->ops.input_frames(rate->obj, (last_slave_hw_ptr_frac + slave_hw_ptr_diff) % rate->gen.slave->rate));
#endif
    rate->hw_ptr += (
            (((last_slave_hw_ptr_frac + slave_hw_ptr_diff) / rate->gen.slave->rate) * pcm->rate)-
            rate->ops.input_frames(rate->obj, last_slave_hw_ptr_frac) +
            rate->ops.input_frames(rate->obj, (last_slave_hw_ptr_frac + slave_hw_ptr_diff) % rate->gen.slave->rate));
    rate->last_slave_hw_ptr = slave_hw_ptr;

    rate->hw_ptr %= pcm->boundary;
}
#else
static inline void snd_pcm_rate_sync_hwptr0(snd_pcm_t *pcm, snd_pcm_uframes_t slave_hw_ptr)
{
    snd_pcm_rate_t *rate = pcm->private_data;

    snd_pcm_sframes_t slave_hw_ptr_diff = slave_hw_ptr - rate->last_slave_hw_ptr;
    snd_pcm_sframes_t last_slave_hw_ptr_frac;

    awalsa_debug("\n");
    if (pcm->stream != SND_PCM_STREAM_PLAYBACK)
        return;

    if (slave_hw_ptr_diff < 0)
        slave_hw_ptr_diff += rate->gen.slave->boundary; /* slave boundary wraparound */
    else if (slave_hw_ptr_diff == 0)
        return;
    last_slave_hw_ptr_frac = rate->last_slave_hw_ptr % rate->gen.slave->period_size;
    /* While handling fraction part fo slave period, rounded value will be
     * introduced by input_frames().
     * To eliminate rounding issue on rate->hw_ptr, subtract last rounded
     * value from rate->hw_ptr and add new rounded value of present
     * slave_hw_ptr fraction part to rate->hw_ptr. Hence,
     * rate->hw_ptr += [ (no. of updated slave periods * pcm rate period size) -
     *  fractional part of last_slave_hw_ptr rounded value +
     *  fractional part of updated slave hw ptr's rounded value ]
     */
#if 0
    printf("hw_ptr=%u, last_slave_hw_ptr_frac=%u, slave_hw_ptr_diff=%u, %u, fractional 1=%u, 2=%u\n",
            rate->hw_ptr, last_slave_hw_ptr_frac, slave_hw_ptr_diff,
            (((last_slave_hw_ptr_frac + slave_hw_ptr_diff) / rate->gen.slave->period_size) * pcm->period_size),
            rate->ops.input_frames(rate->obj, last_slave_hw_ptr_frac),
            rate->ops.input_frames(rate->obj, (last_slave_hw_ptr_frac + slave_hw_ptr_diff) % rate->gen.slave->period_size));
#endif
    rate->hw_ptr += (
            (((last_slave_hw_ptr_frac + slave_hw_ptr_diff) / rate->gen.slave->period_size) * pcm->period_size) -
            rate->ops.input_frames(rate->obj, last_slave_hw_ptr_frac) +
            rate->ops.input_frames(rate->obj, (last_slave_hw_ptr_frac + slave_hw_ptr_diff) % rate->gen.slave->period_size));
    rate->last_slave_hw_ptr = slave_hw_ptr;

    rate->hw_ptr %= pcm->boundary;
}
#endif

static inline void snd_pcm_rate_sync_hwptr(snd_pcm_t *pcm)
{
    snd_pcm_rate_t *rate = pcm->private_data;
    awalsa_debug("\n");
    snd_pcm_rate_sync_hwptr0(pcm, *rate->gen.slave->hw.ptr);
}

static int snd_pcm_rate_hwsync(snd_pcm_t *pcm)
{
    snd_pcm_rate_t *rate = pcm->private_data;

    awalsa_debug("\n");
    int err = snd_pcm_hwsync(rate->gen.slave);
    if (err < 0)
        return err;
    snd_pcm_rate_sync_hwptr(pcm);
    return 0;
}

static snd_pcm_uframes_t snd_pcm_rate_playback_internal_delay(snd_pcm_t *pcm)
{
    snd_pcm_rate_t *rate = pcm->private_data;

    awalsa_debug("\n");
    if (rate->appl_ptr < rate->last_commit_ptr) {
        return rate->appl_ptr - rate->last_commit_ptr + pcm->boundary;
    } else {
        return rate->appl_ptr - rate->last_commit_ptr;
    }
}

static int snd_pcm_rate_delay(snd_pcm_t *pcm, snd_pcm_sframes_t *delayp)
{
    snd_pcm_rate_t *rate = pcm->private_data;
    snd_pcm_sframes_t slave_delay;
    int err;

    awalsa_debug("\n");
    snd_pcm_rate_hwsync(pcm);

    err = snd_pcm_delay(rate->gen.slave, &slave_delay);
    if (err < 0) {
        return err;
    }

    if (pcm->stream == SND_PCM_STREAM_PLAYBACK) {
        *delayp = rate->ops.input_frames(rate->obj, slave_delay)
                + snd_pcm_rate_playback_internal_delay(pcm);
    } else {
        *delayp = rate->ops.output_frames(rate->obj, slave_delay)
                + snd_pcm_mmap_capture_hw_avail(pcm);
    }
    return 0;
}

static int snd_pcm_rate_prepare(snd_pcm_t *pcm)
{
    snd_pcm_rate_t *rate = pcm->private_data;
    int err;

    awalsa_debug("\n");
    err = snd_pcm_prepare(rate->gen.slave);
    if (err < 0)
        return err;
    *pcm->hw.ptr = 0;
    *pcm->appl.ptr = 0;
    rate->last_slave_hw_ptr = 0;
    err = snd_pcm_rate_init(pcm);
    if (err < 0)
        return err;
    return 0;
}

static int snd_pcm_rate_reset(snd_pcm_t *pcm)
{
    snd_pcm_rate_t *rate = pcm->private_data;
    int err;
    awalsa_debug("\n");
    err = snd_pcm_reset(rate->gen.slave);
    if (err < 0)
        return err;
    *pcm->hw.ptr = 0;
    *pcm->appl.ptr = 0;
    rate->last_slave_hw_ptr = 0;
    err = snd_pcm_rate_init(pcm);
    if (err < 0)
        return err;
    return 0;
}
#if 0
static snd_pcm_sframes_t snd_pcm_rate_rewindable(snd_pcm_t *pcm ATTRIBUTE_UNUSED)
{
    return 0;
}

static snd_pcm_sframes_t snd_pcm_rate_forwardable(snd_pcm_t *pcm ATTRIBUTE_UNUSED)
{
    return 0;
}

static snd_pcm_sframes_t snd_pcm_rate_rewind(snd_pcm_t *pcm ATTRIBUTE_UNUSED,
                                             snd_pcm_uframes_t frames ATTRIBUTE_UNUSED)
{
        return 0;
}

static snd_pcm_sframes_t snd_pcm_rate_forward(snd_pcm_t *pcm ATTRIBUTE_UNUSED,
                                              snd_pcm_uframes_t frames ATTRIBUTE_UNUSED)
{
        return 0;
}
#endif

#ifdef SND_PCM_RATE_FIX_PERIOD_SIZE
static int snd_pcm_rate_commit_area(snd_pcm_t *pcm, snd_pcm_rate_t *rate,
                    snd_pcm_uframes_t appl_offset,
                    snd_pcm_uframes_t size,
                    snd_pcm_uframes_t slave_size,
                    snd_pcm_uframes_t *input_frames,
                    snd_pcm_uframes_t *output_frames)
#else
static int snd_pcm_rate_commit_area(snd_pcm_t *pcm, snd_pcm_rate_t *rate,
                    snd_pcm_uframes_t appl_offset,
                    snd_pcm_uframes_t size,
                    snd_pcm_uframes_t slave_size)
#endif
{
    snd_pcm_uframes_t cont = pcm->buffer_size - appl_offset;
    const snd_pcm_channel_area_t *areas;
    const snd_pcm_channel_area_t *slave_areas;
    snd_pcm_uframes_t slave_offset, xfer;
    snd_pcm_uframes_t slave_frames = ULONG_MAX;
    snd_pcm_sframes_t result;

    areas = snd_pcm_mmap_areas(pcm);
    awalsa_debug("cont=%u, size=%u, slave_size=%u\n", cont, size, slave_size);
    /* 剩余空间大于要写入的数据 */
    if (cont >= size) {
        result = snd_pcm_mmap_begin(rate->gen.slave, &slave_areas, &slave_offset, &slave_frames);
        if (result < 0)
            return result;
        if (slave_frames < slave_size) {
            awalsa_debug("slave_frames=%u\n", slave_frames);
            /* 数据写入到rate->sareas中 */
#ifdef SND_PCM_RATE_FIX_PERIOD_SIZE
            snd_pcm_rate_write_areas1_fix(pcm, areas, appl_offset, rate->sareas, 0, NULL, &slave_size);
            if (output_frames != NULL)
                *output_frames = slave_size;
#else
            snd_pcm_rate_write_areas1(pcm, areas, appl_offset, rate->sareas, 0);
#endif
            goto __partial;
        }
        /* 剩余空间大于slave period size,直接把数据写入slave_areas中 */
#ifdef SND_PCM_RATE_FIX_PERIOD_SIZE
        snd_pcm_rate_write_areas1_fix(pcm, areas, appl_offset, slave_areas, slave_offset, NULL, &slave_size);
        if (output_frames != NULL)
            *output_frames = slave_size;
#else
        snd_pcm_rate_write_areas1(pcm, areas, appl_offset,
                      slave_areas, slave_offset);
#endif
        result = snd_pcm_mmap_commit(rate->gen.slave, slave_offset, slave_size);
        if (result < (snd_pcm_sframes_t)slave_size) {
            awalsa_debug("result=%d, slave_size=%u\n", result, slave_size);
            if (result < 0)
                return result;
            result = snd_pcm_rewind(rate->gen.slave, result);
            if (result < 0)
                return result;
            return 0;
        }
    } else {
        /* 剩余空间小于要写入的数据,先把剩余空间填充完 */
        snd_pcm_areas_copy(rate->pareas, 0,
                   areas, appl_offset,
                   pcm->channels, cont,
                   pcm->format);
        /* 再填充剩余部分size-cont, 均写到rate->pareas中 */
        snd_pcm_areas_copy(rate->pareas, cont,
                   areas, 0,
                   pcm->channels, size - cont,
                   pcm->format);

        /* convert并写入到rate->sareas中 */
#ifdef SND_PCM_RATE_FIX_PERIOD_SIZE
        snd_pcm_rate_write_areas1_fix(pcm, rate->pareas, 0, rate->sareas, 0, &size, &slave_size);
        if (input_frames != NULL)
            *input_frames = size;
        if (output_frames != NULL)
            *output_frames = slave_size;
#else
        snd_pcm_rate_write_areas1(pcm, rate->pareas, 0, rate->sareas, 0);
#endif

        /* ok, commit first fragment */
        result = snd_pcm_mmap_begin(rate->gen.slave, &slave_areas, &slave_offset, &slave_frames);
        if (result < 0)
            return result;
          __partial:
        awalsa_debug("slave_size=%u, slave_frames=%u\n", slave_size, slave_frames);
        xfer = 0;
        cont = slave_frames;
        if (cont > slave_size)
            cont = slave_size;
        /* 将rate->sareas写入到slave areas中，cont小于等于slave_size */
        snd_pcm_areas_copy(slave_areas, slave_offset,
                   rate->sareas, 0,
                   pcm->channels, cont,
                   rate->gen.slave->format);
        result = snd_pcm_mmap_commit(rate->gen.slave, slave_offset, cont);
        if (result < (snd_pcm_sframes_t)cont) {
            if (result < 0)
                return result;
            result = snd_pcm_rewind(rate->gen.slave, result);
            if (result < 0)
                return result;
            return 0;
        }
        xfer = cont;

        /* 如果已经传输了slave_size的数据，则完成 */
        if (xfer == slave_size)
            goto commit_done;

        /* 传输剩余部分slave_size-cont,  */
        /* commit second fragment */
        cont = slave_size - cont;
        slave_frames = cont;
        result = snd_pcm_mmap_begin(rate->gen.slave, &slave_areas, &slave_offset, &slave_frames);
        awalsa_debug("cont=%u, slave_frames=%u\n", cont, slave_frames);
        if (result < 0)
            return result;
#if 0
        if (slave_offset) {
            awalsa_err("non-zero slave_offset %ld", slave_offset);
            return -EIO;
        }
#endif
        snd_pcm_areas_copy(slave_areas, slave_offset,
                   rate->sareas, xfer,
                   pcm->channels, cont,
                   rate->gen.slave->format);
        result = snd_pcm_mmap_commit(rate->gen.slave, slave_offset, cont);
        if (result < (snd_pcm_sframes_t)cont) {
            if (result < 0)
                return result;
            result = snd_pcm_rewind(rate->gen.slave, result + xfer);
            if (result < 0)
                return result;
            return 0;
        }
    }
 commit_done:
    if (rate->start_pending) {
        /* we have pending start-trigger.  let's issue it now */
        snd_pcm_start(rate->gen.slave);
        rate->start_pending = 0;
    }
    return 1;
}

#ifdef SND_PCM_RATE_FIX_PERIOD_SIZE
static int snd_pcm_rate_commit_next_period(snd_pcm_t *pcm, snd_pcm_uframes_t appl_offset, snd_pcm_uframes_t *output_frames)
{
    snd_pcm_rate_t *rate = pcm->private_data;

    awalsa_debug("\n");
    return snd_pcm_rate_commit_area(pcm, rate, appl_offset, pcm->period_size,
                    rate->gen.slave->period_size, NULL, output_frames);
}
#else
static int snd_pcm_rate_commit_next_period(snd_pcm_t *pcm, snd_pcm_uframes_t appl_offset)
{
    snd_pcm_rate_t *rate = pcm->private_data;

    awalsa_debug("\n");
    return snd_pcm_rate_commit_area(pcm, rate, appl_offset, pcm->period_size,
                    rate->gen.slave->period_size);
}
#endif

static int snd_pcm_rate_grab_next_period(snd_pcm_t *pcm, snd_pcm_uframes_t hw_offset)
{
    snd_pcm_rate_t *rate = pcm->private_data;
    snd_pcm_uframes_t cont = pcm->buffer_size - hw_offset;
    const snd_pcm_channel_area_t *areas;
    const snd_pcm_channel_area_t *slave_areas;
    snd_pcm_uframes_t slave_offset, xfer;
    snd_pcm_uframes_t slave_frames = ULONG_MAX;
    snd_pcm_sframes_t result;

    awalsa_debug("\n");
    areas = snd_pcm_mmap_areas(pcm);
    if (cont >= pcm->period_size) {
        result = snd_pcm_mmap_begin(rate->gen.slave, &slave_areas, &slave_offset, &slave_frames);
        if (result < 0)
            return result;
        if (slave_frames < rate->gen.slave->period_size)
            goto __partial;
        snd_pcm_rate_read_areas1(pcm, areas, hw_offset,
                     slave_areas, slave_offset);
        result = snd_pcm_mmap_commit(rate->gen.slave, slave_offset, rate->gen.slave->period_size);
        if (result < (snd_pcm_sframes_t)rate->gen.slave->period_size) {
            if (result < 0)
                return result;
            result = snd_pcm_rewind(rate->gen.slave, result);
            if (result < 0)
                return result;
            return 0;
        }
    } else {
        /* ok, grab first fragment */
        result = snd_pcm_mmap_begin(rate->gen.slave, &slave_areas, &slave_offset, &slave_frames);
        if (result < 0)
            return result;
          __partial:
        xfer = 0;
        cont = slave_frames;
        if (cont > rate->gen.slave->period_size)
            cont = rate->gen.slave->period_size;
        snd_pcm_areas_copy(rate->sareas, 0,
                   slave_areas, slave_offset,
                   pcm->channels, cont,
                   rate->gen.slave->format);
        result = snd_pcm_mmap_commit(rate->gen.slave, slave_offset, cont);
        if (result < (snd_pcm_sframes_t)cont) {
            if (result < 0)
                return result;
            result = snd_pcm_rewind(rate->gen.slave, result);
            if (result < 0)
                return result;
            return 0;
        }
        xfer = cont;

        if (xfer == rate->gen.slave->period_size)
            goto __transfer;

        /* grab second fragment */
        cont = rate->gen.slave->period_size - cont;
        slave_frames = cont;
        result = snd_pcm_mmap_begin(rate->gen.slave, &slave_areas, &slave_offset, &slave_frames);
        if (result < 0)
            return result;
#if 0
        if (slave_offset) {
            awalsa_err("non-zero slave_offset %ld", slave_offset);
            return -EIO;
        }
#endif
        snd_pcm_areas_copy(rate->sareas, xfer,
                           slave_areas, slave_offset,
                   pcm->channels, cont,
                   rate->gen.slave->format);
        result = snd_pcm_mmap_commit(rate->gen.slave, slave_offset, cont);
        if (result < (snd_pcm_sframes_t)cont) {
            if (result < 0)
                return result;
            result = snd_pcm_rewind(rate->gen.slave, result + xfer);
            if (result < 0)
                return result;
            return 0;
        }

        __transfer:
        cont = pcm->buffer_size - hw_offset;
        if (cont >= pcm->period_size) {
            snd_pcm_rate_read_areas1(pcm, areas, hw_offset,
                         rate->sareas, 0);
        } else {
            snd_pcm_rate_read_areas1(pcm,
                         rate->pareas, 0,
                         rate->sareas, 0);
            snd_pcm_areas_copy(areas, hw_offset,
                       rate->pareas, 0,
                       pcm->channels, cont,
                       pcm->format);
            snd_pcm_areas_copy(areas, 0,
                       rate->pareas, cont,
                       pcm->channels, pcm->period_size - cont,
                       pcm->format);
        }
    }
    return 1;
}

static int snd_pcm_rate_sync_playback_area(snd_pcm_t *pcm, snd_pcm_uframes_t appl_ptr)
{
    snd_pcm_rate_t *rate = pcm->private_data;
    snd_pcm_t *slave = rate->gen.slave;
    snd_pcm_uframes_t xfer;
    snd_pcm_sframes_t slave_size;
    int err;

    awalsa_debug("slave->running_areas %d \n", slave->running_areas);
    awalsa_debug("pcm->running_areas %d \n", pcm->running_areas);

    slave_size = snd_pcm_avail_update(slave);
    if (slave_size < 0)
        return slave_size;

    if (appl_ptr < rate->last_commit_ptr)
        xfer = appl_ptr - rate->last_commit_ptr + pcm->boundary;
    else
        xfer = appl_ptr - rate->last_commit_ptr;
    /* 传输的数据要大于等于period_size，并且slave可用空间大于period_size时，才执行commit_next_period */
    /* TODO: maybe slave_size >= (rate->gen.slave->period_size-1) */
    while (xfer >= pcm->period_size &&
           (snd_pcm_uframes_t)slave_size >= rate->gen.slave->period_size) {
#ifdef SND_PCM_RATE_FIX_PERIOD_SIZE
        snd_pcm_uframes_t write_frames = 0;
        err = snd_pcm_rate_commit_next_period(pcm, rate->last_commit_ptr % pcm->buffer_size, &write_frames);
#else
        err = snd_pcm_rate_commit_next_period(pcm, rate->last_commit_ptr % pcm->buffer_size);
#endif
        if (err == 0)
            break;
        if (err < 0)
            return err;
        xfer -= pcm->period_size;
#ifdef SND_PCM_RATE_FIX_PERIOD_SIZE
        slave_size -= write_frames;
#else
        slave_size -= rate->gen.slave->period_size;
#endif
        rate->last_commit_ptr += pcm->period_size;
        if (rate->last_commit_ptr >= pcm->boundary)
            rate->last_commit_ptr = 0;
    }
    return 0;
}

static snd_pcm_sframes_t snd_pcm_rate_mmap_commit(snd_pcm_t *pcm,
                          snd_pcm_uframes_t offset ATTRIBUTE_UNUSED,
                          snd_pcm_uframes_t size)
{
    snd_pcm_rate_t *rate = pcm->private_data;
    int err;

    awalsa_debug("\n");
    if (size == 0)
        return 0;
    if (pcm->stream == SND_PCM_STREAM_PLAYBACK) {
        err = snd_pcm_rate_sync_playback_area(pcm, rate->appl_ptr + size);
        if (err < 0)
            return err;
    }
    snd_pcm_mmap_appl_forward(pcm, size);
    return size;
}

static snd_pcm_sframes_t snd_pcm_rate_avail_update(snd_pcm_t *pcm)
{
    snd_pcm_rate_t *rate = pcm->private_data;
    snd_pcm_t *slave = rate->gen.slave;
    snd_pcm_uframes_t slave_size;

    awalsa_debug("\n");
    slave_size = snd_pcm_avail_update(slave);
    if (pcm->stream == SND_PCM_STREAM_CAPTURE)
        goto _capture;
    snd_pcm_rate_sync_hwptr(pcm);
    snd_pcm_rate_sync_playback_area(pcm, rate->appl_ptr);
    return snd_pcm_mmap_avail(pcm);
 _capture: {
    snd_pcm_uframes_t xfer, hw_offset, size;

    xfer = snd_pcm_mmap_capture_avail(pcm);
    size = pcm->buffer_size - xfer;
    hw_offset = snd_pcm_mmap_hw_offset(pcm);
    while (size >= pcm->period_size &&
           slave_size >= rate->gen.slave->period_size) {
        int err = snd_pcm_rate_grab_next_period(pcm, hw_offset);
        if (err < 0)
            return err;
        if (err == 0)
            return (snd_pcm_sframes_t)xfer;
        xfer += pcm->period_size;
        size -= pcm->period_size;
        slave_size -= rate->gen.slave->period_size;
        hw_offset += pcm->period_size;
        hw_offset %= pcm->buffer_size;
        snd_pcm_mmap_hw_forward(pcm, pcm->period_size);
    }
    return (snd_pcm_sframes_t)xfer;
 }
}

/* locking */
static int snd_pcm_rate_drain(snd_pcm_t *pcm)
{
    snd_pcm_rate_t *rate = pcm->private_data;

    awalsa_debug("\n");
    if (pcm->stream == SND_PCM_STREAM_PLAYBACK) {
        /* commit the remaining fraction (if any) */
        snd_pcm_uframes_t size, ofs, saved_avail_min;
        snd_pcm_sw_params_t sw_params;

        snd_pcm_lock(pcm);
        /* temporarily set avail_min to one */
        sw_params = rate->sw_params;
        saved_avail_min = sw_params.avail_min;
        sw_params.avail_min = 1;
        snd_pcm_sw_params(rate->gen.slave, &sw_params);

        size = rate->appl_ptr - rate->last_commit_ptr;
        ofs = rate->last_commit_ptr % pcm->buffer_size;
        while (size > 0) {
            snd_pcm_uframes_t psize, spsize;
            int err;

            awalsa_debug("\n");
            err = __snd_pcm_wait_in_lock(rate->gen.slave, -1);
            if (err < 0)
                break;
            if (size > pcm->period_size) {
                psize = pcm->period_size;
                spsize = rate->gen.slave->period_size;
            } else {
                psize = size;
                spsize = rate->ops.output_frames(rate->obj, size);
                if (! spsize)
                    break;
            }
            awalsa_debug("ofs=%u, psize=%u, spsize=%u\n", ofs, psize, spsize);
#ifdef SND_PCM_RATE_FIX_PERIOD_SIZE
            snd_pcm_uframes_t input_frames, output_frames;
            /* set actual src_frames=psize */
            input_frames = psize;
            snd_pcm_rate_commit_area(pcm, rate, ofs,
                         psize, spsize, &input_frames, &output_frames);
            awalsa_debug("input_frames=%u, output_frames=%u\n", input_frames, output_frames);
#else
            snd_pcm_rate_commit_area(pcm, rate, ofs,
                         psize, spsize);
#endif
            ofs = (ofs + psize) % pcm->buffer_size;
            size -= psize;
        }
        sw_params.avail_min = saved_avail_min;
        snd_pcm_sw_params(rate->gen.slave, &sw_params);
        snd_pcm_unlock(pcm);
    }
    awalsa_debug("\n");
    return snd_pcm_drain(rate->gen.slave);
}

static snd_pcm_state_t snd_pcm_rate_state(snd_pcm_t *pcm)
{
    snd_pcm_rate_t *rate = pcm->private_data;
    awalsa_debug("\n");
    if (rate->start_pending) /* pseudo-state */
        return SND_PCM_STATE_RUNNING;
    return snd_pcm_state(rate->gen.slave);
}


static int snd_pcm_rate_start(snd_pcm_t *pcm)
{
    snd_pcm_rate_t *rate = pcm->private_data;
    snd_pcm_sframes_t avail;

    awalsa_debug("\n");
    if (pcm->stream == SND_PCM_STREAM_CAPTURE)
        return snd_pcm_start(rate->gen.slave);

    if (snd_pcm_state(rate->gen.slave) != SND_PCM_STATE_PREPARED)
        return -EBADFD;

    //gettimestamp(&rate->trigger_tstamp, pcm->tstamp_type);

    avail = snd_pcm_mmap_playback_hw_avail(rate->gen.slave);
    if (avail < 0) /* can't happen on healthy drivers */
        return -EBADFD;

    if (avail == 0) {
        /* postpone the trigger since we have no data committed yet */
        rate->start_pending = 1;
        return 0;
    }
    rate->start_pending = 0;
    return snd_pcm_start(rate->gen.slave);
}

static int snd_pcm_rate_close(snd_pcm_t *pcm)
{
    snd_pcm_rate_t *rate = pcm->private_data;

    awalsa_debug("\n");
    if (rate->ops.close)
        rate->ops.close(rate->obj);
    //  snd_dlobj_cache_put(rate->open_func);
    return snd_pcm_generic_close(pcm);
}

static void snd_pcm_rate_dump(snd_pcm_t *pcm)
{
    snd_pcm_rate_t *rate = pcm->private_data;
    if (rate->sformat == SND_PCM_FORMAT_UNKNOWN)
        printf("Rate conversion PCM (%d)\n", rate->srate);
    else
        printf("Rate conversion PCM (%d, sformat=%s)\n",
            rate->srate,
            snd_pcm_format_name(rate->sformat));
    if (rate->ops.dump)
        rate->ops.dump(rate->obj);
    printf("Protocol version: %x\n", rate->plugin_version);
    if (pcm->setup) {
        printf("Its setup is:\n");
        snd_pcm_dump_setup(pcm);
    }
    printf("Slave: ");
    snd_pcm_dump(rate->gen.slave);
}

static const snd_pcm_fast_ops_t snd_pcm_rate_fast_ops = {
    .state = snd_pcm_rate_state,
    .hwsync = snd_pcm_rate_hwsync,
    .delay = snd_pcm_rate_delay,
    .prepare = snd_pcm_rate_prepare,
    .reset = snd_pcm_rate_reset,
    .start = snd_pcm_rate_start,
    .drop = snd_pcm_generic_drop,
    .drain = snd_pcm_rate_drain,
    .pause = snd_pcm_generic_pause,
    //.forwardable = snd_pcm_rate_forwardable,
    //.forward = snd_pcm_rate_forward,
    .resume = snd_pcm_generic_resume,
    .writei = snd_pcm_mmap_writei,
    //.writen = snd_pcm_mmap_writen,
    .readi = snd_pcm_mmap_readi,
    //.readn = snd_pcm_mmap_readn,
    .avail_update = snd_pcm_rate_avail_update,
    .mmap_commit = snd_pcm_rate_mmap_commit,
    .may_wait_for_avail_min = snd_pcm_plugin_may_wait_for_avail_min,
    .wait = snd_pcm_plugin_wait,
};

static const snd_pcm_ops_t snd_pcm_rate_ops = {
    .close = snd_pcm_rate_close,
    .hw_refine = snd_pcm_rate_hw_refine,
    .hw_params = snd_pcm_rate_hw_params,
    .hw_free = snd_pcm_rate_hw_free,
    .sw_params = snd_pcm_rate_sw_params,
    .channel_info = snd_pcm_generic_channel_info,
    .dump = snd_pcm_rate_dump,
    .mmap = snd_pcm_generic_mmap,
    .munmap = snd_pcm_generic_munmap,
};


#if 0
static int rate_open_func(snd_pcm_rate_t *rate, const char *type, int verbose)
{
    char open_name[64], open_conf_name[64], lib_name[128], *lib = NULL;
    snd_pcm_rate_open_func_t open_func;
    snd_pcm_rate_open_conf_func_t open_conf_func;
    int err;

    snprintf(open_name, sizeof(open_name), "_snd_pcm_rate_%s_open", type);
#if 0
    snprintf(open_conf_name, sizeof(open_conf_name), "_snd_pcm_rate_%s_open_conf", type);
    if (!is_builtin_plugin(type)) {
        snprintf(lib_name, sizeof(lib_name),
                 "%s/libasound_module_rate_%s.so", ALSA_PLUGIN_DIR, type);
        lib = lib_name;
    }

    rate->rate_min = SND_PCM_PLUGIN_RATE_MIN;
    rate->rate_max = SND_PCM_PLUGIN_RATE_MAX;
    rate->plugin_version = SND_PCM_RATE_PLUGIN_VERSION;

    open_conf_func = snd_dlobj_cache_get(lib, open_conf_name, NULL, verbose && converter_conf != NULL);
    if (open_conf_func) {
        err = open_conf_func(SND_PCM_RATE_PLUGIN_VERSION,
                     &rate->obj, &rate->ops, converter_conf);
        if (!err) {
            rate->plugin_version = rate->ops.version;
            if (rate->ops.get_supported_rates)
                rate->ops.get_supported_rates(rate->obj,
                                  &rate->rate_min,
                                  &rate->rate_max);
            rate->open_func = open_conf_func;
            return 0;
        } else {
            snd_dlobj_cache_put(open_conf_func);
            return err;
        }
    }
#endif
    open_func = snd_dlobj_cache_get(lib, open_name, NULL, verbose);
    if (!open_func)
        return -ENOENT;

    rate->open_func = open_func;

    err = open_func(SND_PCM_RATE_PLUGIN_VERSION, &rate->obj, &rate->ops);
    if (!err) {
        rate->plugin_version = rate->ops.version;
        if (rate->ops.get_supported_rates)
            rate->ops.get_supported_rates(rate->obj,
                              &rate->rate_min,
                              &rate->rate_max);
        return 0;
    }

    /* try to open with the old protocol version */
    rate->plugin_version = SND_PCM_RATE_PLUGIN_VERSION_OLD;
    err = open_func(SND_PCM_RATE_PLUGIN_VERSION_OLD,
            &rate->obj, &rate->ops);
    if (err) {
        snd_dlobj_cache_put(open_func);
        rate->open_func = NULL;
    }
    return err;
}
#endif


int snd_pcm_rate_open(snd_pcm_t **pcmp, const char *name,
              snd_pcm_format_t sformat, unsigned int srate,
              const char *converter,
              snd_pcm_t *slave, int close_slave)
{
    snd_pcm_t *pcm;
    snd_pcm_rate_t *rate;
    int err;
#ifndef PIC
    snd_pcm_rate_open_func_t open_func;
    extern int SND_PCM_RATE_PLUGIN_ENTRY(linear) (unsigned int version, void **objp, snd_pcm_rate_ops_t *ops);
    extern int SND_PCM_RATE_PLUGIN_ENTRY(speexrate) (unsigned int version, void **objp, snd_pcm_rate_ops_t *ops);
#if 0
    extern int SND_PCM_RATE_PLUGIN_ENTRY(awrate) (unsigned int version, void **objp, snd_pcm_rate_ops_t *ops);
#endif
#endif

    awalsa_debug("\n");
    assert(pcmp && slave);
    if (sformat != SND_PCM_FORMAT_UNKNOWN &&
        snd_pcm_format_linear(sformat) != 1)
        return -EINVAL;

    rate = calloc(1, sizeof(snd_pcm_rate_t));
    if (!rate) {
        return -ENOMEM;
    }
    rate->gen.slave = slave;
    rate->gen.slave->rate = srate;
    rate->gen.close_slave = close_slave;
    rate->srate = srate;
    rate->sformat = sformat;
    rate->rate_min = SND_PCM_PLUGIN_RATE_MIN;
    rate->rate_max= SND_PCM_PLUGIN_RATE_MAX;

    err = snd_pcm_new(&pcm, SND_PCM_TYPE_RATE, name, slave->stream, slave->mode);
    if (err < 0) {
        free(rate);
        return err;
    }

#if 0
    err = -ENOENT;
    if (!converter) {
        const char *const *types;
        for (types = default_rate_plugins; *types; types++) {
            err = rate_open_func(rate, *types, NULL, 0);
            if (!err) {
                type = *types;
                break;
            }
        }
    } else if (!snd_config_get_string(converter, &type))
        err = rate_open_func(rate, type, NULL, 1);
    else if (is_string_array(converter)) {
        snd_config_iterator_t i, next;
        snd_config_for_each(i, next, converter) {
            snd_config_t *n = snd_config_iterator_entry(i);
            if (snd_config_get_string(n, &type) < 0)
                break;
            err = rate_open_func(rate, type, NULL, 0);
            if (!err)
                break;
        }
    } else if (snd_config_get_type(converter) == SND_CONFIG_TYPE_COMPOUND) {
        snd_config_iterator_t i, next;
        snd_config_for_each(i, next, converter) {
            snd_config_t *n = snd_config_iterator_entry(i);
            const char *id;
            if (snd_config_get_id(n, &id) < 0)
                continue;
            if (strcmp(id, "name") != 0)
                continue;
            snd_config_get_string(n, &type);
            break;
        }
        if (!type) {
            awalsa_err("No name given for rate converter");
            snd_pcm_free(pcm);
            free(rate);
            return -EINVAL;
        }
        err = rate_open_func(rate, type, converter, 1);
    } else {
        awalsa_err("Invalid type for rate converter");
        snd_pcm_free(pcm);
        free(rate);
        return -EINVAL;
    }
    if (err < 0) {
        awalsa_err("Cannot find rate converter");
        snd_pcm_free(pcm);
        free(rate);
        return -ENOENT;
    }
#else
    if( 0 == strcmp(converter, "linear"))
        open_func = SND_PCM_RATE_PLUGIN_ENTRY(linear);
    else if ( 0 == strcmp(converter, "speexrate"))
        open_func = SND_PCM_RATE_PLUGIN_ENTRY(speexrate);
#if 0
    else if ( 0 == strcmp(converter, "awrate") )
        open_func = SND_PCM_RATE_PLUGIN_ENTRY(awrate);
#endif
    else {
        awalsa_err("can not find rate plugin %s\n", converter);
        snd_pcm_free(pcm);
        free(rate);
        err = -EINVAL;
        return err;
    }
    err = open_func(SND_PCM_RATE_PLUGIN_VERSION, &rate->obj, &rate->ops);
    if (err < 0) {
        snd_pcm_free(pcm);
        free(rate);
        return err;
    }
#endif

    if (! rate->ops.init || ! (rate->ops.convert || rate->ops.convert_s16
        || rate->ops.convert_s16_fix) || ! rate->ops.input_frames ||
        ! rate->ops.output_frames) {
        awalsa_err("Inproper rate plugin %s initialization", converter);
        snd_pcm_free(pcm);
        free(rate);
        return err;
    }

    pcm->ops = &snd_pcm_rate_ops;
    pcm->fast_ops = &snd_pcm_rate_fast_ops;
    pcm->private_data = rate;
    //pcm->poll_fd = slave->poll_fd;
    //pcm->poll_events = slave->poll_events;
    pcm->mmap_rw = 1;
    //pcm->tstamp_type = slave->tstamp_type;
    snd_pcm_set_hw_ptr(pcm, &rate->hw_ptr, -1, 0);
    snd_pcm_set_appl_ptr(pcm, &rate->appl_ptr, -1, 0);
    *pcmp = pcm;

    return 0;
}


int _snd_pcm_rate_open(snd_pcm_t **pcmp, const snd_pcm_config_t *pcm_config,
               snd_pcm_stream_t stream, int mode)
{
    const snd_pcm_rate_config_t *rate_config =
    (const snd_pcm_rate_config_t *)(pcm_config->config);
    snd_pcm_t *spcm;
    int ret = -1;
    const snd_pcm_config_t *sconf = NULL;
    awalsa_debug("\n");
    if (stream != SND_PCM_STREAM_PLAYBACK) {
        awalsa_err("The rate plugin supports only playback stream");
        return -EINVAL;
    }
    sconf = snd_pcm_config_get_config(rate_config->slave.pcm);
    if (!sconf) {
        awalsa_err("can't find pcm slave:%s\n", rate_config->slave.pcm);
        return -EINVAL;
    }
    if (rate_config->slave.format != SND_PCM_FORMAT_UNKNOWN &&
        snd_pcm_format_linear(rate_config->slave.format) != 1) {
        awalsa_err("slave format is not linear");
        return -EINVAL;
    }
    ret = snd_pcm_open_config(&spcm, sconf, stream, mode);
    if (ret < 0)
        return ret;
    ret = snd_pcm_rate_open(pcmp, pcm_config->name, rate_config->slave.format, (unsigned int) rate_config->slave.rate,
                rate_config->converter, spcm, 1);
    if (ret < 0)
        snd_pcm_close(spcm);
    return ret;
}
