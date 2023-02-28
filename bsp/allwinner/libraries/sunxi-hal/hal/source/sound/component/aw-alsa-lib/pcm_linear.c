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
#include "bswap.h"
#include "pcm_local.h"
#include "pcm_plugin_generic.h"

#include "plugin_ops.h"

typedef struct {
        /* This field need to be the first */
        snd_pcm_plugin_t plug;
        unsigned int use_getput;
        unsigned int conv_idx;
        unsigned int get_idx, put_idx;
        snd_pcm_format_t sformat;
} snd_pcm_linear_t;

int snd_pcm_linear_convert_index(snd_pcm_format_t src_format,
                 snd_pcm_format_t dst_format)
{
    int src_endian, dst_endian, sign, src_width, dst_width;

    sign = (snd_pcm_format_signed(src_format) !=
        snd_pcm_format_signed(dst_format));

    src_endian = snd_pcm_format_big_endian(src_format);
    dst_endian = snd_pcm_format_big_endian(dst_format);

    if (src_endian < 0)
        src_endian = 0;
    if (dst_endian < 0)
        dst_endian = 0;

    src_width = snd_pcm_format_width(src_format) / 8 - 1;
    dst_width = snd_pcm_format_width(dst_format) / 8 - 1;

    return src_width * 32 + src_endian * 16 + sign * 8 + dst_width * 2 + dst_endian;
}

int snd_pcm_linear_get_index(snd_pcm_format_t src_format, snd_pcm_format_t dst_format)
{
    int sign, width, pwidth, endian;
    sign = (snd_pcm_format_signed(src_format) !=
        snd_pcm_format_signed(dst_format));

    endian = snd_pcm_format_big_endian(src_format);

    if (endian < 0)
        endian = 0;
    pwidth = snd_pcm_format_physical_width(src_format);
    width = snd_pcm_format_width(src_format);
    if (pwidth == 24) {
        switch (width) {
        case 24:
            width = 0; break;
        case 20:
            width = 1; break;
        case 18:
        default:
            width = 2; break;
        }
        return width * 4 + endian * 2 + sign + 16;
    } else {
        width = width / 8 - 1;
        return width * 4 + endian * 2 + sign;
    }
}

int snd_pcm_linear_put_index(snd_pcm_format_t src_format, snd_pcm_format_t dst_format)
{
    int sign, width, pwidth, endian;
    sign = (snd_pcm_format_signed(src_format) !=
        snd_pcm_format_signed(dst_format));

    endian = snd_pcm_format_big_endian(dst_format);

    if (endian < 0)
        endian = 0;
    pwidth = snd_pcm_format_physical_width(dst_format);
    width = snd_pcm_format_width(dst_format);
    if (pwidth == 24) {
        switch (width) {
        case 24:
            width = 0; break;
        case 20:
            width = 1; break;
        case 18:
        default:
            width = 2; break;
        }
        return width * 4 + endian * 2 + sign + 16;
    } else {
        width = width / 8 - 1;
        return width * 4 + endian * 2 + sign;
    }
}

void snd_pcm_linear_convert(const snd_pcm_channel_area_t *dst_areas, snd_pcm_uframes_t dst_offset,
                const snd_pcm_channel_area_t *src_areas, snd_pcm_uframes_t src_offset,
                unsigned int channels, snd_pcm_uframes_t frames,
                unsigned int convidx)
{
#define CONV_LABELS
#include "plugin_ops.h"
#undef CONV_LABELS
    void *conv = conv_labels[convidx];
    unsigned int channel;
    for (channel = 0; channel < channels; ++channel) {
        const char *src;
        char *dst;
        int src_step, dst_step;
        snd_pcm_uframes_t frames1;
        const snd_pcm_channel_area_t *src_area = &src_areas[channel];
        const snd_pcm_channel_area_t *dst_area = &dst_areas[channel];
        src = snd_pcm_channel_area_addr(src_area, src_offset);
        dst = snd_pcm_channel_area_addr(dst_area, dst_offset);
        src_step = snd_pcm_channel_area_step(src_area);
        dst_step = snd_pcm_channel_area_step(dst_area);
        frames1 = frames;
        while (frames1-- > 0) {
            goto *conv;
#define CONV_END after
#include "plugin_ops.h"
#undef CONV_END
        after:
            src += src_step;
            dst += dst_step;
        }
    }
}

void snd_pcm_linear_getput(const snd_pcm_channel_area_t *dst_areas, snd_pcm_uframes_t dst_offset,
               const snd_pcm_channel_area_t *src_areas, snd_pcm_uframes_t src_offset,
               unsigned int channels, snd_pcm_uframes_t frames,
               unsigned int get_idx, unsigned int put_idx)
{
#define CONV24_LABELS
#include "plugin_ops.h"
#undef CONV24_LABELS
    void *get = get32_labels[get_idx];
    void *put = put32_labels[put_idx];
    unsigned int channel;
    u_int32_t sample = 0;
    for (channel = 0; channel < channels; ++channel) {
        const char *src;
        char *dst;
        int src_step, dst_step;
        snd_pcm_uframes_t frames1;
        const snd_pcm_channel_area_t *src_area = &src_areas[channel];
        const snd_pcm_channel_area_t *dst_area = &dst_areas[channel];
        src = snd_pcm_channel_area_addr(src_area, src_offset);
        dst = snd_pcm_channel_area_addr(dst_area, dst_offset);
        src_step = snd_pcm_channel_area_step(src_area);
        dst_step = snd_pcm_channel_area_step(dst_area);
        frames1 = frames;
        while (frames1-- > 0) {
            goto *get;
#define CONV24_END after
#include "plugin_ops.h"
#undef CONV24_END
        after:
            src += src_step;
            dst += dst_step;
        }
    }
}

static snd_pcm_uframes_t
snd_pcm_linear_write_areas(snd_pcm_t *pcm,
               const snd_pcm_channel_area_t *areas,
               snd_pcm_uframes_t offset,
               snd_pcm_uframes_t size,
               const snd_pcm_channel_area_t *slave_areas,
               snd_pcm_uframes_t slave_offset,
               snd_pcm_uframes_t *slave_sizep)
{
    snd_pcm_linear_t *linear = pcm->private_data;
    if (size > *slave_sizep)
        size = *slave_sizep;
    if (linear->use_getput)
        snd_pcm_linear_getput(slave_areas, slave_offset,
                      areas, offset,
                      pcm->channels, size,
                      linear->get_idx, linear->put_idx);
    else
        snd_pcm_linear_convert(slave_areas, slave_offset,
                       areas, offset,
                       pcm->channels, size, linear->conv_idx);
    *slave_sizep = size;
    return size;
}

static snd_pcm_uframes_t
snd_pcm_linear_read_areas(snd_pcm_t *pcm,
              const snd_pcm_channel_area_t *areas,
              snd_pcm_uframes_t offset,
              snd_pcm_uframes_t size,
              const snd_pcm_channel_area_t *slave_areas,
              snd_pcm_uframes_t slave_offset,
              snd_pcm_uframes_t *slave_sizep)
{
    snd_pcm_linear_t *linear = pcm->private_data;
    if (size > *slave_sizep)
        size = *slave_sizep;
    if (linear->use_getput)
        snd_pcm_linear_getput(areas, offset,
                      slave_areas, slave_offset,
                      pcm->channels, size,
                      linear->get_idx, linear->put_idx);
    else
        snd_pcm_linear_convert(areas, offset,
                       slave_areas, slave_offset,
                       pcm->channels, size, linear->conv_idx);
    *slave_sizep = size;
    return size;
}

static int snd_pcm_linear_hw_refine(snd_pcm_t *pcm, snd_pcm_hw_params_t *params)
{
    snd_pcm_linear_t *linear = pcm->private_data;
    snd_pcm_t *slave = linear->plug.gen.slave;
    int ret;

    awalsa_debug("\n");
    ret = slave->ops->hw_refine(slave->op_arg, params);
    if (ret < 0)
        return ret;

    return ret;
}

static int snd_pcm_linear_hw_params(snd_pcm_t *pcm, snd_pcm_hw_params_t *params)
{
    snd_pcm_linear_t *linear = pcm->private_data;
    snd_pcm_t *slave = linear->plug.gen.slave;
    int err;
    snd_pcm_hw_params_t *slave_params;
    snd_pcm_format_t format;

    snd_pcm_hw_params_alloca(&slave_params);
    memcpy(slave_params, params, sizeof(snd_pcm_hw_params_t));

    snd_pcm_hw_params_set_format(slave, slave_params, linear->sformat);

    err = _snd_pcm_hw_params_internal(slave, slave_params);
    if (err < 0) {
        awalsa_err("failed to set slave hw params\n");
        return err;
    }

    snd_pcm_hw_params_get_format(params, &format);
    linear->use_getput = (snd_pcm_format_physical_width(format) == 24 ||
                snd_pcm_format_physical_width(linear->sformat) == 24);
    if (linear->use_getput) {
        if (pcm->stream == SND_PCM_STREAM_PLAYBACK) {
            linear->get_idx = snd_pcm_linear_get_index(format, SND_PCM_FORMAT_S32);
            linear->put_idx = snd_pcm_linear_put_index(SND_PCM_FORMAT_S32, linear->sformat);
        } else {
            linear->get_idx = snd_pcm_linear_get_index(format, SND_PCM_FORMAT_S32);
            linear->put_idx = snd_pcm_linear_put_index(SND_PCM_FORMAT_S32, linear->sformat);
        }
        /*awalsa_info("get_idx=%u, put_idx=%u\n", linear->get_idx, linear->put_idx);*/
    } else {
        if (pcm->stream == SND_PCM_STREAM_PLAYBACK)
            linear->conv_idx = snd_pcm_linear_convert_index(format , linear->sformat);
        else
            linear->conv_idx = snd_pcm_linear_convert_index(linear->sformat , format);
        /*awalsa_info("conv_idx=%u\n", linear->conv_idx);*/
    }

    /*TODO*/
    memcpy(params, slave_params, sizeof(snd_pcm_hw_params_t));

    return 0;
}

static void snd_pcm_linear_dump(snd_pcm_t *pcm)
{
    snd_pcm_linear_t *linear = pcm->private_data;
    printf("Linear conversion PCM (%s)\n", snd_pcm_format_name(linear->sformat));
    if (pcm->setup) {
        printf("Its setup is:\n");
        snd_pcm_dump_setup(pcm);
    }
    printf("Slave: ");
    snd_pcm_dump_setup(linear->plug.gen.slave);
}

static const snd_pcm_ops_t snd_pcm_linear_ops = {
    .close = snd_pcm_generic_close,
    /*.info = snd_pcm_generic_info,*/
    .hw_refine = snd_pcm_linear_hw_refine,
    .hw_params = snd_pcm_linear_hw_params,
    .hw_free = snd_pcm_generic_hw_free,
    .sw_params = snd_pcm_generic_sw_params,
    .channel_info = snd_pcm_generic_channel_info,
    .dump = snd_pcm_linear_dump,
    /*.nonblock = snd_pcm_generic_nonblock,*/
    /*.async = snd_pcm_generic_async,*/
    .mmap = snd_pcm_generic_mmap,
    .munmap = snd_pcm_generic_munmap,
    .query_chmaps = snd_pcm_generic_query_chmaps,
    .get_chmap = snd_pcm_generic_get_chmap,
    .set_chmap = snd_pcm_generic_set_chmap,
};

int snd_pcm_linear_open(snd_pcm_t **pcmp, const char *name, snd_pcm_format_t sformat, snd_pcm_t *slave, int close_slave)
{
    snd_pcm_t *pcm;
    snd_pcm_linear_t *linear;
    int err;

    awalsa_debug("\n");
    assert(pcmp && slave);
    if (snd_pcm_format_linear(sformat) != 1)
        return -EINVAL;
    linear = calloc(1, sizeof(snd_pcm_linear_t));
    if (!linear)
        return -ENOMEM;
    snd_pcm_plugin_init(&linear->plug);
    linear->sformat = sformat;
    linear->plug.read = snd_pcm_linear_read_areas;
    linear->plug.write = snd_pcm_linear_write_areas;
    linear->plug.undo_read = snd_pcm_plugin_undo_read_generic;
    linear->plug.undo_write = snd_pcm_plugin_undo_write_generic;
    linear->plug.gen.slave = slave;
    linear->plug.gen.close_slave = close_slave;

    awalsa_debug("\n");
    err = snd_pcm_new(&pcm, SND_PCM_TYPE_LINEAR, name, slave->stream, slave->mode);
    if (err < 0) {
        free(linear);
        return err;
    }
    pcm->ops = &snd_pcm_linear_ops;
    pcm->fast_ops = &snd_pcm_plugin_fast_ops;
    pcm->private_data = linear;
    snd_pcm_set_hw_ptr(pcm, &linear->plug.hw_ptr, 0, 0);
    snd_pcm_set_appl_ptr(pcm, &linear->plug.appl_ptr, 0, 0);
    *pcmp = pcm;

    return 0;
}


#if 0
int _snd_pcm_linear_open(snd_pcm_t **pcmp, const snd_pcm_config_t *pcm_config,
        snd_pcm_stream_t stream, int mode)
{
    int err;
    const snd_pcm_linear_config_t *linear_config = (const snd_pcm_linear_config_t *)(pcm_config->config);
    const snd_pcm_config_t *sconf = NULL;
    snd_pcm_t *spcm;
    snd_pcm_format_t sformat = SND_PCM_FORMAT_UNKNOWN;


    err = snd_pcm_linear_open(pcmp, name, sformat, spcm, 1);
    if (err < 0)
        snd_pcm_close(spcm);
    return err;
}
#endif
