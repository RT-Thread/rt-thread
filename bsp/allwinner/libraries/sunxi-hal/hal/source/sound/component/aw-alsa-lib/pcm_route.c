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
#include <math.h>
#include <aw-alsa-lib/plugin/pcm_route.h>
#include "bswap.h"
#include "pcm_local.h"
#include "pcm_plugin_generic.h"

#include "plugin_ops.h"

/* The best possible hack to support missing optimization in gcc 2.7.2.3 */
#if SND_PCM_PLUGIN_ROUTE_RESOLUTION & (SND_PCM_PLUGIN_ROUTE_RESOLUTION - 1) != 0
#define div(a) a /= SND_PCM_PLUGIN_ROUTE_RESOLUTION
#elif SND_PCM_PLUGIN_ROUTE_RESOLUTION == 16
#define div(a) a >>= 4
#else
#error "Add some code here"
#endif

typedef struct {
    int channel;
    int as_int;
#if SND_PCM_PLUGIN_ROUTE_FLOAT
    float as_float;
#endif
} snd_pcm_route_ttable_src_t;

typedef struct snd_pcm_route_ttable_dst snd_pcm_route_ttable_dst_t;

typedef struct {
    enum {UINT64, FLOAT} sum_idx;
    unsigned int get_idx;
    unsigned int put_idx;
    unsigned int conv_idx;
    int use_getput;
    unsigned int src_size;
    snd_pcm_format_t dst_sfmt;
    unsigned int nsrcs;
    unsigned int ndsts;
    snd_pcm_route_ttable_dst_t *dsts;
} snd_pcm_route_params_t;

typedef void (*route_f)(const snd_pcm_channel_area_t *dst_area,
            snd_pcm_uframes_t dst_offset,
            const snd_pcm_channel_area_t *src_areas,
            snd_pcm_uframes_t src_offset,
            unsigned int src_channels,
            snd_pcm_uframes_t frames,
            const snd_pcm_route_ttable_dst_t *ttable,
            const snd_pcm_route_params_t *params);

struct snd_pcm_route_ttable_dst {
    int att;    /* Attenuated */
    unsigned int nsrcs;
    snd_pcm_route_ttable_src_t* srcs;
    route_f func;
};

typedef union {
    int32_t as_sint32;
    int64_t as_sint64;
#if SND_PCM_PLUGIN_ROUTE_FLOAT
    float as_float;
#endif
} sum_t;

typedef struct {
    /* This field need to be the first */
    snd_pcm_plugin_t plug;
    snd_pcm_format_t sformat;
    int schannels;
    snd_pcm_route_params_t params;
    snd_pcm_chmap_t *chmap;
} snd_pcm_route_t;


static void snd_pcm_route_convert1_zero(const snd_pcm_channel_area_t *dst_area,
                    snd_pcm_uframes_t dst_offset,
                    const snd_pcm_channel_area_t *src_areas,
                    snd_pcm_uframes_t src_offset,
                    unsigned int src_channels,
                    snd_pcm_uframes_t frames,
                    const snd_pcm_route_ttable_dst_t* ttable,
                    const snd_pcm_route_params_t *params)
{
    snd_pcm_area_silence(dst_area, dst_offset, frames, params->dst_sfmt);
}

static void snd_pcm_route_convert1_one(const snd_pcm_channel_area_t *dst_area,
                       snd_pcm_uframes_t dst_offset,
                       const snd_pcm_channel_area_t *src_areas,
                       snd_pcm_uframes_t src_offset,
                       unsigned int src_channels,
                       snd_pcm_uframes_t frames,
                       const snd_pcm_route_ttable_dst_t* ttable,
                       const snd_pcm_route_params_t *params)
{
#define CONV_LABELS
#include "plugin_ops.h"
#undef CONV_LABELS
    void *conv;
    const snd_pcm_channel_area_t *src_area = 0;
    unsigned int srcidx;
    const char *src;
    char *dst;
    int src_step, dst_step;
    for (srcidx = 0; srcidx < ttable->nsrcs && srcidx < src_channels; ++srcidx) {
        unsigned int channel = ttable->srcs[srcidx].channel;
        if (channel >= src_channels)
            continue;
        src_area = &src_areas[channel];
        if (src_area->addr != NULL)
            break;
    }
    if (srcidx == ttable->nsrcs || srcidx == src_channels) {
        snd_pcm_route_convert1_zero(dst_area, dst_offset,
                        src_areas, src_offset,
                        src_channels,
                        frames, ttable, params);
        return;
    }

    conv = conv_labels[params->conv_idx];
    src = snd_pcm_channel_area_addr(src_area, src_offset);
    dst = snd_pcm_channel_area_addr(dst_area, dst_offset);
    src_step = snd_pcm_channel_area_step(src_area);
    dst_step = snd_pcm_channel_area_step(dst_area);
    while (frames-- > 0) {
        goto *conv;
#define CONV_END after
#include "plugin_ops.h"
#undef CONV_END
    after:
        src += src_step;
        dst += dst_step;
    }
}

static void snd_pcm_route_convert1_one_getput(const snd_pcm_channel_area_t *dst_area,
                          snd_pcm_uframes_t dst_offset,
                          const snd_pcm_channel_area_t *src_areas,
                          snd_pcm_uframes_t src_offset,
                          unsigned int src_channels,
                          snd_pcm_uframes_t frames,
                          const snd_pcm_route_ttable_dst_t* ttable,
                          const snd_pcm_route_params_t *params)
{
#define CONV24_LABELS
#include "plugin_ops.h"
#undef CONV24_LABELS
    void *get, *put;
    const snd_pcm_channel_area_t *src_area = 0;
    unsigned int srcidx;
    const char *src;
    char *dst;
    int src_step, dst_step;
    u_int32_t sample = 0;
    for (srcidx = 0; srcidx < ttable->nsrcs && srcidx < src_channels; ++srcidx) {
        unsigned int channel = ttable->srcs[srcidx].channel;
        if (channel >= src_channels)
            continue;
        src_area = &src_areas[channel];
        if (src_area->addr != NULL)
            break;
    }
    if (srcidx == ttable->nsrcs || srcidx == src_channels) {
        snd_pcm_route_convert1_zero(dst_area, dst_offset,
                        src_areas, src_offset,
                        src_channels,
                        frames, ttable, params);
        return;
    }

    get = get32_labels[params->get_idx];
    put = put32_labels[params->put_idx];
    src = snd_pcm_channel_area_addr(src_area, src_offset);
    dst = snd_pcm_channel_area_addr(dst_area, dst_offset);
    src_step = snd_pcm_channel_area_step(src_area);
    dst_step = snd_pcm_channel_area_step(dst_area);
    while (frames-- > 0) {
        goto *get;
#define CONV24_END after
#include "plugin_ops.h"
#undef CONV24_END
    after:
        src += src_step;
        dst += dst_step;
    }
}

static void snd_pcm_route_convert1_many(const snd_pcm_channel_area_t *dst_area,
                    snd_pcm_uframes_t dst_offset,
                    const snd_pcm_channel_area_t *src_areas,
                    snd_pcm_uframes_t src_offset,
                    unsigned int src_channels,
                    snd_pcm_uframes_t frames,
                    const snd_pcm_route_ttable_dst_t* ttable,
                    const snd_pcm_route_params_t *params)
{
#define GET32_LABELS
#define PUT32_LABELS
#include "plugin_ops.h"
#undef GET32_LABELS
#undef PUT32_LABELS
    static void *const zero_labels[2] = {
        &&zero_int64,
#if SND_PCM_PLUGIN_ROUTE_FLOAT
        &&zero_float
#endif
    };
    /* sum_type att */
    static void *const add_labels[2 * 2] = {
        &&add_int64_noatt, &&add_int64_att,
#if SND_PCM_PLUGIN_ROUTE_FLOAT
        &&add_float_noatt, &&add_float_att
#endif
    };
    /* sum_type att */
    static void *const norm_labels[2 * 2] = {
        &&norm_int64_noatt,
        &&norm_int64_att,
#if SND_PCM_PLUGIN_ROUTE_FLOAT
        &&norm_float,
        &&norm_float,
#endif
    };
    void *zero, *get32, *add, *norm, *put32;
    int nsrcs = ttable->nsrcs;
    char *dst;
    int dst_step;
    const char *srcs[nsrcs];
    int src_steps[nsrcs];
    snd_pcm_route_ttable_src_t src_tt[nsrcs];
    int32_t sample = 0;
    int srcidx, srcidx1 = 0;
    const char *src = 0;
    for (srcidx = 0; srcidx < nsrcs && (unsigned)srcidx < src_channels; ++srcidx) {
        const snd_pcm_channel_area_t *src_area;
        unsigned int channel = ttable->srcs[srcidx].channel;
        if (channel >= src_channels)
            continue;
        src_area = &src_areas[channel];
        srcs[srcidx1] = snd_pcm_channel_area_addr(src_area, src_offset);
        src_steps[srcidx1] = snd_pcm_channel_area_step(src_area);
        src_tt[srcidx1] = ttable->srcs[srcidx];
        srcidx1++;
    }
    nsrcs = srcidx1;
    if (nsrcs == 0) {
        snd_pcm_route_convert1_zero(dst_area, dst_offset,
                        src_areas, src_offset,
                        src_channels,
                        frames, ttable, params);
        return;
    } else if (nsrcs == 1 && src_tt[0].as_int == SND_PCM_PLUGIN_ROUTE_RESOLUTION) {
        if (params->use_getput)
            snd_pcm_route_convert1_one_getput(dst_area, dst_offset,
                              src_areas, src_offset,
                              src_channels,
                              frames, ttable, params);
        else
            snd_pcm_route_convert1_one(dst_area, dst_offset,
                           src_areas, src_offset,
                           src_channels,
                           frames, ttable, params);
        return;
    }

    zero = zero_labels[params->sum_idx];
    get32 = get32_labels[params->get_idx];
    add = add_labels[params->sum_idx * 2 + ttable->att];
    norm = norm_labels[params->sum_idx * 2 + ttable->att];
    put32 = put32_labels[params->put_idx];
    dst = snd_pcm_channel_area_addr(dst_area, dst_offset);
    dst_step = snd_pcm_channel_area_step(dst_area);

    while (frames-- > 0) {
        snd_pcm_route_ttable_src_t *ttp = src_tt;
        sum_t sum;

        /* Zero sum */
        goto *zero;
    zero_int64:
        sum.as_sint64 = 0;
        goto zero_end;
#if SND_PCM_PLUGIN_ROUTE_FLOAT
    zero_float:
        sum.as_float = 0.0;
        goto zero_end;
#endif
    zero_end:
        for (srcidx = 0; srcidx < nsrcs; ++srcidx) {
            src = srcs[srcidx];

            /* Get sample */
            goto *get32;
#define GET32_END after_get
#include "plugin_ops.h"
#undef GET32_END
        after_get:

            /* Sum */
            goto *add;
        add_int64_att:
            sum.as_sint64 += (int64_t) sample * ttp->as_int;
            goto after_sum;
        add_int64_noatt:
            if (ttp->as_int)
                sum.as_sint64 += sample;
            goto after_sum;
#if SND_PCM_PLUGIN_ROUTE_FLOAT
        add_float_att:
            sum.as_float += sample * ttp->as_float;
            goto after_sum;
        add_float_noatt:
            if (ttp->as_int)
                sum.as_float += sample;
            goto after_sum;
#endif
        after_sum:
            srcs[srcidx] += src_steps[srcidx];
            ttp++;
        }

        /* Normalization */
        goto *norm;
    norm_int64_att:
        div(sum.as_sint64);
        /* fallthru */
    norm_int64_noatt:
        if (sum.as_sint64 > (int64_t)0x7fffffff)
            sample = 0x7fffffff;    /* maximum positive value */
        else if (sum.as_sint64 < -(int64_t)0x80000000)
            sample = 0x80000000;    /* maximum negative value */
        else
            sample = sum.as_sint64;
        goto after_norm;

#if SND_PCM_PLUGIN_ROUTE_FLOAT
    norm_float:
        sum.as_float = rint(sum.as_float);
        if (sum.as_float > (int64_t)0x7fffffff)
            sample = 0x7fffffff;    /* maximum positive value */
        else if (sum.as_float < -(int64_t)0x80000000)
            sample = 0x80000000;    /* maximum negative value */
        else
            sample = sum.as_float;
        goto after_norm;
#endif
    after_norm:

        /* Put sample */
        goto *put32;
#define PUT32_END after_put32
#include "plugin_ops.h"
#undef PUT32_END
    after_put32:

        dst += dst_step;
    }
}

static void snd_pcm_route_convert(const snd_pcm_channel_area_t *dst_areas,
                  snd_pcm_uframes_t dst_offset,
                  const snd_pcm_channel_area_t *src_areas,
                  snd_pcm_uframes_t src_offset,
                  unsigned int src_channels,
                  unsigned int dst_channels,
                  snd_pcm_uframes_t frames,
                  snd_pcm_route_params_t *params)
{
    unsigned int dst_channel;
    snd_pcm_route_ttable_dst_t *dstp;
    const snd_pcm_channel_area_t *dst_area;

    dstp = params->dsts;
    dst_area = dst_areas;
    for (dst_channel = 0; dst_channel < dst_channels; ++dst_channel) {
        if (dst_channel >= params->ndsts)
            snd_pcm_route_convert1_zero(dst_area, dst_offset,
                            src_areas, src_offset,
                            src_channels,
                            frames, dstp, params);
        else
            dstp->func(dst_area, dst_offset,
                   src_areas, src_offset,
                   src_channels,
                   frames, dstp, params);
        dstp++;
        dst_area++;
    }
}

static snd_pcm_uframes_t
snd_pcm_route_write_areas(snd_pcm_t *pcm,
              const snd_pcm_channel_area_t *areas,
              snd_pcm_uframes_t offset,
              snd_pcm_uframes_t size,
              const snd_pcm_channel_area_t *slave_areas,
              snd_pcm_uframes_t slave_offset,
              snd_pcm_uframes_t *slave_sizep)
{
    snd_pcm_route_t *route = pcm->private_data;
    snd_pcm_t *slave = route->plug.gen.slave;
    if (size > *slave_sizep)
        size = *slave_sizep;
    snd_pcm_route_convert(slave_areas, slave_offset,
                  areas, offset,
                  pcm->channels,
                  slave->channels,
                  size, &route->params);
    *slave_sizep = size;
    return size;
}

static snd_pcm_uframes_t
snd_pcm_route_read_areas(snd_pcm_t *pcm,
             const snd_pcm_channel_area_t *areas,
             snd_pcm_uframes_t offset,
             snd_pcm_uframes_t size,
             const snd_pcm_channel_area_t *slave_areas,
             snd_pcm_uframes_t slave_offset,
             snd_pcm_uframes_t *slave_sizep)
{
    snd_pcm_route_t *route = pcm->private_data;
    snd_pcm_t *slave = route->plug.gen.slave;
    if (size > *slave_sizep)
        size = *slave_sizep;
    snd_pcm_route_convert(areas, offset,
                  slave_areas, slave_offset,
                  slave->channels,
                  pcm->channels,
                  size, &route->params);
    *slave_sizep = size;
    return size;
}

int snd_pcm_route_determine_ttable(
        const snd_pcm_route_ttable_config_t *tt_config,
        unsigned int *tt_csize, unsigned int *tt_ssize)
{
    int csize = 0, ssize = 0;
    int i;

    assert(tt_config && tt_csize && tt_ssize);
    i = 0;
    while (1) {
        if (snd_pcm_route_is_ttable_config_end(&tt_config[i]))
            break;
        int cchannel = tt_config[i].cchannel;
        int schannel = tt_config[i].schannel;
        if (cchannel + 1 > csize)
            csize = cchannel + 1;
        if (schannel + 1 > ssize)
            ssize = schannel + 1;
        i++;
    }

    if (csize == 0 || ssize == 0) {
        awalsa_debug("Invalid null ttable configuration\n");
        return -EINVAL;
    }
    *tt_csize = csize;
    *tt_ssize = ssize;
    return 0;
}

int snd_pcm_route_load_ttable(
        const snd_pcm_route_ttable_config_t *tt_config,
        snd_pcm_route_ttable_entry_t *ttable,
        unsigned int tt_csize, unsigned int tt_ssize,
        unsigned int *tt_cused, unsigned int *tt_sused, int schannels)
{
    int cused = -1;
    int sused = -1;
    int i;
    unsigned int k;

    for (k = 0; k < tt_csize * tt_ssize; ++k)
        ttable[k] = 0.0;

    i = 0;
    while (1) {
        if (snd_pcm_route_is_ttable_config_end(&tt_config[i]))
            break;

        int cchannel = tt_config[i].cchannel;
        int schannel = tt_config[i].schannel;
        snd_pcm_route_ttable_entry_t value = tt_config[i].route_value;

        if (cchannel < 0 || (unsigned int) cchannel > tt_csize) {
            awalsa_err("invalid client channel: %d\n", cchannel);
            return -EINVAL;
        }
        if (schannel < 0 || (unsigned int) schannel > tt_ssize ||
                (schannels > 0 && schannel >= schannels)) {
            awalsa_err("invalid slave channel: %d\n", schannel);
            return -EINVAL;
        }
        ttable[cchannel * tt_ssize + schannel] = value;
        if (schannel > sused)
            sused = schannel;
        if (cchannel > cused)
            cused = cchannel;
        i++;
    }

    *tt_sused = sused + 1;
    *tt_cused = cused + 1;
    return 0;
}

static int route_chmap_init(snd_pcm_t *pcm)
{
    int set_map = 0;
    snd_pcm_chmap_t *current;
    snd_pcm_route_t *route = pcm->private_data;
    if (!route->chmap)
        return 0;
    if (__snd_pcm_state(pcm) != SND_PCM_STATE_PREPARED)
        return 0;

    /* Check if we really need to set the chmap or not.
       This is important in case set_chmap is not implemented. */
    current = snd_pcm_get_chmap(route->plug.gen.slave);
    if (!current)
        return -ENOSYS;
    if (current->channels != route->chmap->channels)
        set_map = 1;
    else
        set_map = memcmp(current->pos, route->chmap->pos,
                 current->channels);
    free(current);
    if (!set_map)
        return 0;

    return snd_pcm_set_chmap(route->plug.gen.slave, route->chmap);
}

static int snd_pcm_route_close(snd_pcm_t *pcm)
{
    snd_pcm_route_t *route = pcm->private_data;
    snd_pcm_route_params_t *params = &route->params;
    unsigned int dst_channel;

    awalsa_debug("\n");
    if (params->dsts) {
        for (dst_channel = 0; dst_channel < params->ndsts; ++dst_channel) {
            free(params->dsts[dst_channel].srcs);
        }
        free(params->dsts);
    }
    free(route->chmap);
    return snd_pcm_generic_close(pcm);
}

static int snd_pcm_route_hw_refine_cprepare(snd_pcm_t *pcm ATTRIBUTE_UNUSED, snd_pcm_hw_params_t *params)
{
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
    err = _snd_pcm_hw_param_set_min(params, SND_PCM_HW_PARAM_CHANNELS, 1, 0);
    if (err < 0)
        return err;
#if 0
    params->info &= ~(SND_PCM_INFO_MMAP | SND_PCM_INFO_MMAP_VALID);
#endif
    return 0;
}

static int snd_pcm_route_hw_refine_sprepare(snd_pcm_t *pcm, snd_pcm_hw_params_t *sparams)
{
    snd_pcm_route_t *route = pcm->private_data;
    snd_interval_t saccess_mask = { .mask = SND_PCM_ACCBIT_MMAP };

    awalsa_debug("\n");
    _snd_pcm_hw_params_any(sparams);
    _snd_pcm_hw_param_set_mask(sparams, SND_PCM_HW_PARAM_ACCESS,
                   &saccess_mask);
    if (route->sformat != SND_PCM_FORMAT_UNKNOWN) {
        _snd_pcm_hw_param_set(sparams, SND_PCM_HW_PARAM_FORMAT,
                      (unsigned long) route->sformat, 0);
    }
    if (route->schannels >= 0) {
        _snd_pcm_hw_param_set(sparams, SND_PCM_HW_PARAM_CHANNELS,
                      (unsigned int) route->schannels, 0);
    }
    return 0;
}

static int snd_pcm_route_hw_refine_schange(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
                        snd_pcm_hw_params_t *sparams)
{
    snd_pcm_route_t *route = pcm->private_data;
    int err;
    unsigned int links = (SND_PCM_HW_PARBIT_RATE |
                  SND_PCM_HW_PARBIT_PERIODS |
                  SND_PCM_HW_PARBIT_PERIOD_SIZE |
                  SND_PCM_HW_PARBIT_PERIOD_TIME |
                  SND_PCM_HW_PARBIT_BUFFER_SIZE |
                  SND_PCM_HW_PARBIT_BUFFER_TIME);

    awalsa_debug("\n");
    if (route->sformat == SND_PCM_FORMAT_UNKNOWN)
        links |= (SND_PCM_HW_PARBIT_FORMAT |
              SND_PCM_HW_PARBIT_SAMPLE_BITS);
    if (route->schannels < 0)
        links |= SND_PCM_HW_PARBIT_CHANNELS;
    err = _snd_pcm_hw_params_refine(sparams, links, params);
    if (err < 0)
        return err;
    return 0;
}

static int snd_pcm_route_hw_refine_cchange(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
                        snd_pcm_hw_params_t *sparams)
{
    snd_pcm_route_t *route = pcm->private_data;
    int err;
    unsigned int links = (SND_PCM_HW_PARBIT_RATE |
                  SND_PCM_HW_PARBIT_PERIODS |
                  SND_PCM_HW_PARBIT_PERIOD_SIZE |
                  SND_PCM_HW_PARBIT_PERIOD_TIME |
                  SND_PCM_HW_PARBIT_BUFFER_SIZE |
                  SND_PCM_HW_PARBIT_BUFFER_TIME);

    awalsa_debug("\n");
    if (route->sformat == SND_PCM_FORMAT_UNKNOWN)
        links |= (SND_PCM_HW_PARBIT_FORMAT |
              SND_PCM_HW_PARBIT_SAMPLE_BITS);
    if (route->schannels < 0)
        links |= SND_PCM_HW_PARBIT_CHANNELS;
    err = _snd_pcm_hw_params_refine(params, links, sparams);
    if (err < 0)
        return err;
    return 0;
}

static int snd_pcm_route_hw_refine(snd_pcm_t *pcm, snd_pcm_hw_params_t *params)
{
#if 0
    snd_pcm_route_t *route = pcm->private_data;
    snd_pcm_t *slave = route->plug.gen.slave;
    int ret;

    awalsa_debug("\n");
    ret = slave->ops->hw_refine(slave->op_arg, params);
    if (ret < 0)
        return ret;

    return 0;
#else
    awalsa_debug("\n");
    return snd_pcm_hw_refine_slave(pcm, params,
                       snd_pcm_route_hw_refine_cprepare,
                       snd_pcm_route_hw_refine_cchange,
                       snd_pcm_route_hw_refine_sprepare,
                       snd_pcm_route_hw_refine_schange,
                       snd_pcm_generic_hw_refine);
#endif
}

static int snd_pcm_route_hw_params(snd_pcm_t *pcm, snd_pcm_hw_params_t * params)
{
    snd_pcm_route_t *route = pcm->private_data;
    snd_pcm_t *slave = route->plug.gen.slave;
    snd_pcm_format_t src_format, dst_format;
    int err;
#if 0
    snd_pcm_hw_params_t *slave_params;
    unsigned int cchannels;

    awalsa_debug("\n");

    snd_pcm_hw_params_get_channels(params, &cchannels);
    snd_pcm_hw_params_alloca(&slave_params);
    memcpy(slave_params, params, sizeof(snd_pcm_hw_params_t));

    snd_pcm_hw_param_change(slave_params, SND_PCM_HW_PARAM_ACCESS);
    err = snd_pcm_hw_params_set_access(slave, slave_params, SND_PCM_ACCESS_MMAP_INTERLEAVED);
    if (err < 0) {
        awalsa_err("snd_pcm_hw_params_set_access failed\n");
        return err;
    }
    snd_pcm_hw_param_change(slave_params, SND_PCM_HW_PARAM_CHANNELS);
    err = snd_pcm_hw_params_set_channels(slave, slave_params, route->schannels);
    if (err < 0) {
        awalsa_err("snd_pcm_hw_params_set_channels failed\n");
        return err;
    }

    /* TODO: whether pcm route can change format? */
#if 0
    snd_pcm_hw_param_change(slave_params, SND_PCM_HW_PARAM_FORMAT);
    err = snd_pcm_hw_params_set_format(slave, slave_params, route->sformat);
    if (err < 0) {
        awalsa_err("snd_pcm_hw_params_set_format failed\n");
        return err;
    }
#endif

    err = _snd_pcm_hw_params_internal(slave, slave_params);
    if (err < 0) {
        awalsa_err("failed to set slave hw params\n");
        return err;
    }

    memcpy(params, slave_params, sizeof(snd_pcm_hw_params_t));
    snd_pcm_hw_param_change(params, SND_PCM_HW_PARAM_CHANNELS);
    err = snd_pcm_hw_params_set_channels(pcm, params, cchannels);
    if (err < 0) {
        awalsa_err("snd_pcm_hw_params_set_channels failed\n");
        return err;
    }
#else

    awalsa_debug("\n");
    err = snd_pcm_hw_params_slave(pcm, params,
                      snd_pcm_route_hw_refine_cchange,
                      snd_pcm_route_hw_refine_sprepare,
                      snd_pcm_route_hw_refine_schange,
                      snd_pcm_generic_hw_params);
    if (err < 0)
        return err;
#endif

    if (pcm->stream == SND_PCM_STREAM_PLAYBACK) {
        err = snd_pcm_hw_params_get_format(params, &src_format);
        dst_format = slave->format;
    } else {
        src_format = slave->format;
        err = snd_pcm_hw_params_get_format(params, &dst_format);
    }
    if (err < 0)
        return err;
    /* 3 bytes formats? */
    route->params.use_getput =
        (snd_pcm_format_physical_width(src_format) + 7) / 3 == 3 ||
        (snd_pcm_format_physical_width(dst_format) + 7) / 3 == 3;
    route->params.get_idx = snd_pcm_linear_get_index(src_format, SND_PCM_FORMAT_S32_LE);
    route->params.put_idx = snd_pcm_linear_put_index(SND_PCM_FORMAT_S32_LE, dst_format);
    route->params.conv_idx = snd_pcm_linear_convert_index(src_format, dst_format);
    route->params.src_size = snd_pcm_format_width(src_format) / 8;
    route->params.dst_sfmt = dst_format;
#if SND_PCM_PLUGIN_ROUTE_FLOAT
    route->params.sum_idx = FLOAT;
#else
    route->params.sum_idx = UINT64;
#endif
    return 0;
}

static snd_pcm_chmap_t *snd_pcm_route_get_chmap(snd_pcm_t *pcm)
{
    snd_pcm_route_t *route = pcm->private_data;
    snd_pcm_chmap_t *map, *slave_map;
    unsigned int src, dst, nsrcs;

    awalsa_debug("\n");
    slave_map = snd_pcm_generic_get_chmap(pcm);
    if (!slave_map)
        return NULL;
    nsrcs = route->params.nsrcs;
    map = calloc(4, nsrcs + 1);
    if (!map) {
        free(slave_map);
        return NULL;
    }
    map->channels = nsrcs;
    for (src = 0; src < nsrcs; src++)
        map->pos[src] = SND_CHMAP_NA;
    for (dst = 0; dst < route->params.ndsts; dst++) {
        snd_pcm_route_ttable_dst_t *d = &route->params.dsts[dst];
        for (src = 0; src < d->nsrcs; src++) {
            unsigned int c = d->srcs[src].channel;
            if (c < nsrcs && map->pos[c] == SND_CHMAP_NA)
                map->pos[c] = slave_map->pos[dst];
        }
    }
    free(slave_map);
    return map;
}

static snd_pcm_chmap_query_t **snd_pcm_route_query_chmaps(snd_pcm_t *pcm)
{
    snd_pcm_chmap_query_t **maps;
    awalsa_debug("\n");
    snd_pcm_chmap_t *map = snd_pcm_route_get_chmap(pcm);
    if (!map)
        return NULL;
    maps = _snd_pcm_make_single_query_chmaps(map);
    free(map);
    return maps;
}

static void snd_pcm_route_dump(snd_pcm_t *pcm)
{
    snd_pcm_route_t *route = pcm->private_data;
    unsigned int dst;

    if (route->sformat == SND_PCM_FORMAT_UNKNOWN)
        printf("Route conversion PCM\n");
    else
        printf("Route conversion PCM (sformat=%s)\n",
            snd_pcm_format_name(route->sformat));
    printf("  Transformation table:\n");
    for (dst = 0; dst < route->params.ndsts; dst++) {
        snd_pcm_route_ttable_dst_t *d = &route->params.dsts[dst];
        unsigned int src;
        printf("    %d <- ", dst);
        if (d->nsrcs == 0) {
            printf("none\n");
            continue;
        }
        src = 0;
        while (1) {
            snd_pcm_route_ttable_src_t *s = &d->srcs[src];
            if (d->att)
#if SND_PCM_PLUGIN_ROUTE_FLOAT
                printf("%d*%g", s->channel, s->as_float);
#else
                printf("%d*%g", s->channel, (double)s->as_int / (double)SND_PCM_PLUGIN_ROUTE_RESOLUTION);
#endif
            else
                printf("%d", s->channel);
            src++;
            if (src == d->nsrcs)
                break;
            printf(" + ");
        }
        printf("\n");
    }
    if (pcm->setup) {
        printf("Its setup is:\n");
        snd_pcm_dump_setup(pcm);
    }
    printf("Slave: ");
    snd_pcm_dump(route->plug.gen.slave);
}

static const snd_pcm_ops_t snd_pcm_route_ops = {
    .close = snd_pcm_route_close,
    .hw_refine = snd_pcm_route_hw_refine,
    .hw_params = snd_pcm_route_hw_params,
    .hw_free = snd_pcm_generic_hw_free,
    .sw_params = snd_pcm_generic_sw_params,
    .channel_info = snd_pcm_generic_channel_info,
    .dump = snd_pcm_route_dump,
    .mmap = snd_pcm_generic_mmap,
    .munmap = snd_pcm_generic_munmap,
    .query_chmaps = snd_pcm_route_query_chmaps,
    .get_chmap = snd_pcm_route_get_chmap,
    .set_chmap = NULL, /* NYI */
};

static int route_load_ttable(snd_pcm_route_params_t *params, snd_pcm_stream_t stream,
                 unsigned int tt_ssize,
                 snd_pcm_route_ttable_entry_t *ttable,
                 unsigned int tt_cused, unsigned int tt_sused)
{
    unsigned int src_channel, dst_channel;
    snd_pcm_route_ttable_dst_t *dptr;
    unsigned int sused, dused, smul, dmul;
    if (stream == SND_PCM_STREAM_PLAYBACK) {
        sused = tt_cused;
        dused = tt_sused;
        smul = tt_ssize;
        dmul = 1;
    } else {
        sused = tt_sused;
        dused = tt_cused;
        smul = 1;
        dmul = tt_ssize;
    }
    params->ndsts = dused;
    params->nsrcs = sused;
    dptr = calloc(dused, sizeof(*params->dsts));
    if (!dptr)
        return -ENOMEM;
    params->dsts = dptr;
    for (dst_channel = 0; dst_channel < dused; ++dst_channel) {
        snd_pcm_route_ttable_entry_t t = 0;
        int att = 0;
        int nsrcs = 0;
        snd_pcm_route_ttable_src_t srcs[sused];
        for (src_channel = 0; src_channel < sused; ++src_channel) {
            snd_pcm_route_ttable_entry_t v;
            v = ttable[src_channel * smul + dst_channel * dmul];
            if (v != 0) {
                srcs[nsrcs].channel = src_channel;
#if SND_PCM_PLUGIN_ROUTE_FLOAT
                /* Also in user space for non attenuated */
                srcs[nsrcs].as_int = (v == SND_PCM_PLUGIN_ROUTE_FULL ? SND_PCM_PLUGIN_ROUTE_RESOLUTION : 0);
                srcs[nsrcs].as_float = v;
#else
                assert(v >= 0 && v <= SND_PCM_PLUGIN_ROUTE_FULL);
                srcs[nsrcs].as_int = v;
#endif
                if (v != SND_PCM_PLUGIN_ROUTE_FULL)
                    att = 1;
                t += v;
                nsrcs++;
            }
        }
#if 0
        assert(t <= SND_PCM_PLUGIN_ROUTE_FULL);
#endif
        dptr->att = att;
        dptr->nsrcs = nsrcs;
        if (nsrcs == 0)
            dptr->func = snd_pcm_route_convert1_zero;
        else
            dptr->func = snd_pcm_route_convert1_many;
        if (nsrcs > 0) {
            dptr->srcs = calloc((unsigned int) nsrcs, sizeof(*srcs));
            if (!dptr->srcs)
                return -ENOMEM;
            memcpy(dptr->srcs, srcs, sizeof(*srcs) * nsrcs);
        } else
            dptr->srcs = 0;
        dptr++;
    }
    return 0;
}

/**
 * \brief Creates a new Route & Volume PCM
 * \param pcmp Returns created PCM handle
 * \param name Name of PCM
 * \param sformat Slave format
 * \param schannels Slave channels
 * \param ttable Attenuation table
 * \param tt_ssize Attenuation table - slave size
 * \param tt_cused Attenuation table - client used count
 * \param tt_sused Attenuation table - slave used count
 * \param slave Slave PCM handle
 * \param close_slave When set, the slave PCM handle is closed with copy PCM
 * \retval zero on success otherwise a negative error code
 * \warning Using of this function might be dangerous in the sense
 *          of compatibility reasons. The prototype might be freely
 *          changed in future.
 */
int snd_pcm_route_open(snd_pcm_t **pcmp, const char *name,
               snd_pcm_format_t sformat, int schannels,
               snd_pcm_route_ttable_entry_t *ttable,
               unsigned int tt_ssize,
               unsigned int tt_cused, unsigned int tt_sused,
               snd_pcm_t *slave, int close_slave)
{
    snd_pcm_t *pcm;
    snd_pcm_route_t *route;
    int err;
    assert(pcmp && slave && ttable);

    if (sformat != SND_PCM_FORMAT_UNKNOWN && snd_pcm_format_linear(sformat) != 1)
        return -EINVAL;

    route = calloc(1, sizeof(snd_pcm_route_t));
    if (!route) {
        return -ENOMEM;
    }
    snd_pcm_plugin_init(&route->plug);
    route->sformat = sformat;
    route->schannels = schannels;
    route->plug.read = snd_pcm_route_read_areas;
    route->plug.write = snd_pcm_route_write_areas;
    route->plug.undo_read = snd_pcm_plugin_undo_read_generic;
    route->plug.undo_write = snd_pcm_plugin_undo_write_generic;
    route->plug.gen.slave = slave;
    route->plug.gen.close_slave = close_slave;
    route->plug.init = route_chmap_init;

    err = snd_pcm_new(&pcm, SND_PCM_TYPE_ROUTE, name, slave->stream, slave->mode);
    if (err < 0) {
        free(route);
        return err;
    }
    pcm->ops = &snd_pcm_route_ops;
    pcm->fast_ops = &snd_pcm_plugin_fast_ops;
    pcm->private_data = route;
    snd_pcm_set_hw_ptr(pcm, &route->plug.hw_ptr, -1, 0);
    snd_pcm_set_appl_ptr(pcm, &route->plug.appl_ptr, -1, 0);
    err = route_load_ttable(&route->params, pcm->stream, tt_ssize, ttable, tt_cused, tt_sused);
    if (err < 0) {
        snd_pcm_close(pcm);
        return err;
    }
    *pcmp = pcm;

    return 0;
}

int _snd_pcm_route_open(snd_pcm_t **pcmp, const snd_pcm_config_t *pcm_config,
        snd_pcm_stream_t stream, int mode)
{
    const snd_pcm_route_config_t *route_config =
        (const snd_pcm_route_config_t *)(pcm_config->config);
    const snd_pcm_route_ttable_config_t *tt_config = route_config->ttable;
    const char *name = pcm_config->name;

    int ret = 0;
    snd_pcm_t *spcm = NULL;
    const snd_pcm_config_t *sconf = NULL;
    snd_pcm_format_t sformat = SND_PCM_FORMAT_UNKNOWN;
    int schannels = -1;
    snd_pcm_route_ttable_entry_t *ttable = NULL;
    unsigned int csize, ssize;
    unsigned int cused, sused;

    /* TODO: whether it is the correct way to get slave channels? */
    schannels = route_config->slave.channels;

    sconf = snd_pcm_config_get_config(route_config->slave.pcm);
    if (!sconf) {
        awalsa_err("can't find pcm slave:%s\n", route_config->slave.pcm);
        ret = -EINVAL;
        goto err_out;
    }
    ret = snd_pcm_open_config(&spcm, sconf, stream, mode);
    if (ret < 0) {
        awalsa_err("unable to open slave\n");
        goto err_out;
    }

    ret = snd_pcm_route_determine_ttable(tt_config, &csize, &ssize);
    if (ret < 0) {
        awalsa_err("failed to determine ttable\n");
        goto err_close_spcm;
    }
    ttable = malloc(csize * ssize * sizeof(snd_pcm_route_ttable_entry_t));
    if (!ttable) {
        awalsa_err("no memory\n");
        ret = -ENOMEM;
        goto err_close_spcm;
    }
    ret = snd_pcm_route_load_ttable(tt_config, ttable, csize, ssize,
            &cused, &sused, schannels);
    if (ret < 0) {
        awalsa_err("failed to load ttable\n");
        goto err_free_ttable;
    }

    ret = snd_pcm_route_open(pcmp, name, sformat, schannels,
            ttable, ssize, cused, sused, spcm, 1);
    free(ttable);
    if (ret < 0) {
        awalsa_err("snd_pcm_route_open failed\n");
        goto err_close_spcm;
    }

    return 0;

err_free_ttable:
    free(ttable);
err_close_spcm:
    snd_pcm_close(spcm);
err_out:
    return ret;
}
