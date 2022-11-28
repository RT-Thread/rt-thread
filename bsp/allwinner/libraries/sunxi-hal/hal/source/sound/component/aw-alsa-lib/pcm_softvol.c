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
#include "pcm_local.h"
#include <aw-alsa-lib/pcm_plugin.h>
#include <aw-alsa-lib/pcm_config.h>
#include <aw-alsa-lib/control.h>
#include "pcm_plugin_generic.h"
#include <math.h>

typedef struct {
    /* This field need to be the first */
    snd_pcm_plugin_t plug;
    snd_pcm_format_t sformat;
    unsigned int cchannels;
    /*snd_ctl*/
    unsigned int cur_vol[2];
    unsigned int max_val;       /* max index  */
    unsigned int zero_dB_val;   /* index at 0 dB */
    double min_dB;
    double max_dB;
    unsigned int *dB_value;
    const snd_pcm_softvol_control_t *control;
} snd_pcm_softvol_t;

#define VOL_SCALE_SHIFT         16
#define VOL_SCALE_MASK          ((1 << VOL_SCALE_SHIFT) - 1)

#define PRESET_RESOLUTION       256
#define PRESET_MIN_DB           -51.0
#define ZERO_DB                  0.0
#define MAX_DB_UPPER_LIMIT      50

static const unsigned int preset_dB_value[PRESET_RESOLUTION] = {
    0x00b8, 0x00bd, 0x00c1, 0x00c5, 0x00ca, 0x00cf, 0x00d4, 0x00d9,
    0x00de, 0x00e3, 0x00e8, 0x00ed, 0x00f3, 0x00f9, 0x00fe, 0x0104,
    0x010a, 0x0111, 0x0117, 0x011e, 0x0124, 0x012b, 0x0132, 0x0139,
    0x0140, 0x0148, 0x0150, 0x0157, 0x015f, 0x0168, 0x0170, 0x0179,
    0x0181, 0x018a, 0x0194, 0x019d, 0x01a7, 0x01b0, 0x01bb, 0x01c5,
    0x01cf, 0x01da, 0x01e5, 0x01f1, 0x01fc, 0x0208, 0x0214, 0x0221,
    0x022d, 0x023a, 0x0248, 0x0255, 0x0263, 0x0271, 0x0280, 0x028f,
    0x029e, 0x02ae, 0x02be, 0x02ce, 0x02df, 0x02f0, 0x0301, 0x0313,
    0x0326, 0x0339, 0x034c, 0x035f, 0x0374, 0x0388, 0x039d, 0x03b3,
    0x03c9, 0x03df, 0x03f7, 0x040e, 0x0426, 0x043f, 0x0458, 0x0472,
    0x048d, 0x04a8, 0x04c4, 0x04e0, 0x04fd, 0x051b, 0x053a, 0x0559,
    0x0579, 0x0599, 0x05bb, 0x05dd, 0x0600, 0x0624, 0x0648, 0x066e,
    0x0694, 0x06bb, 0x06e3, 0x070c, 0x0737, 0x0762, 0x078e, 0x07bb,
    0x07e9, 0x0818, 0x0848, 0x087a, 0x08ac, 0x08e0, 0x0915, 0x094b,
    0x0982, 0x09bb, 0x09f5, 0x0a30, 0x0a6d, 0x0aab, 0x0aeb, 0x0b2c,
    0x0b6f, 0x0bb3, 0x0bf9, 0x0c40, 0x0c89, 0x0cd4, 0x0d21, 0x0d6f,
    0x0dbf, 0x0e11, 0x0e65, 0x0ebb, 0x0f12, 0x0f6c, 0x0fc8, 0x1026,
    0x1087, 0x10e9, 0x114e, 0x11b5, 0x121f, 0x128b, 0x12fa, 0x136b,
    0x13df, 0x1455, 0x14ce, 0x154a, 0x15c9, 0x164b, 0x16d0, 0x1758,
    0x17e4, 0x1872, 0x1904, 0x1999, 0x1a32, 0x1ace, 0x1b6e, 0x1c11,
    0x1cb9, 0x1d64, 0x1e13, 0x1ec7, 0x1f7e, 0x203a, 0x20fa, 0x21bf,
    0x2288, 0x2356, 0x2429, 0x2500, 0x25dd, 0x26bf, 0x27a6, 0x2892,
    0x2984, 0x2a7c, 0x2b79, 0x2c7c, 0x2d85, 0x2e95, 0x2fab, 0x30c7,
    0x31ea, 0x3313, 0x3444, 0x357c, 0x36bb, 0x3801, 0x394f, 0x3aa5,
    0x3c02, 0x3d68, 0x3ed6, 0x404d, 0x41cd, 0x4355, 0x44e6, 0x4681,
    0x4826, 0x49d4, 0x4b8c, 0x4d4f, 0x4f1c, 0x50f3, 0x52d6, 0x54c4,
    0x56be, 0x58c3, 0x5ad4, 0x5cf2, 0x5f1c, 0x6153, 0x6398, 0x65e9,
    0x6849, 0x6ab7, 0x6d33, 0x6fbf, 0x7259, 0x7503, 0x77bd, 0x7a87,
    0x7d61, 0x804d, 0x834a, 0x8659, 0x897a, 0x8cae, 0x8ff5, 0x934f,
    0x96bd, 0x9a40, 0x9dd8, 0xa185, 0xa548, 0xa922, 0xad13, 0xb11b,
    0xb53b, 0xb973, 0xbdc5, 0xc231, 0xc6b7, 0xcb58, 0xd014, 0xd4ed,
    0xd9e3, 0xdef6, 0xe428, 0xe978, 0xeee8, 0xf479, 0xfa2b, 0xffff,
};

typedef union {
    int i;
    short s[2];
} val_t;
static inline int MULTI_DIV_32x16(int a, unsigned short b)

{
    val_t v, x, y;
    v.i = a;
    y.i = 0;
    x.i = (unsigned short)v.s[0];
    x.i *= b;
    y.s[0] = x.s[1];
    y.i += (int)v.s[1] * b;

    return y.i;
}

/* unused, only support little endian */
#ifndef bswap_32
#define bswap_32(a) (a)
#endif

#ifndef bswap_16
#define bswap_16(a) (a)
#endif

static inline int MULTI_DIV_int(int a, unsigned int b, int swap)
{
    unsigned int gain = (b >> VOL_SCALE_SHIFT);
    int fraction;
    a = swap ? (int)bswap_32(a) : a;
    fraction = MULTI_DIV_32x16(a, b & VOL_SCALE_MASK);
    if (gain) {
        long long amp = (long long)a * gain + fraction;
        if (amp > (int)0x7fffffff)
            amp = (int)0x7fffffff;
        else if (amp < (int)0x80000000)
            amp = (int)0x80000000;
        return swap ? (int)bswap_32((int)amp) : (int)amp;
    }
    return swap ? (int)bswap_32(fraction) : fraction;
}

static inline short MULTI_DIV_short(short a, unsigned int b, int swap)
{
    unsigned int gain = b >> VOL_SCALE_SHIFT;
    int fraction;
    a = swap ? (short)bswap_16(a) : a;
    fraction = (int)(a * (b & VOL_SCALE_MASK)) >> VOL_SCALE_SHIFT;
    if (gain) {
        int amp = a * gain + fraction;
        if (abs(amp) > 0x7fff)
            amp = (a<0) ? (short)0x8000 : (short)0x7fff;
        return swap ? (short)bswap_16((short)amp) : (short)amp;
    }
    return swap ? (short)bswap_16((short)fraction) : (short)fraction;
}

#define CONVERT_AREA(TYPE, swap) do {   \
    unsigned int ch, fr; \
    TYPE *src, *dst; \
    for (ch = 0; ch < channels; ch++) { \
        src_area = &src_areas[ch]; \
        dst_area = &dst_areas[ch]; \
        src = snd_pcm_channel_area_addr(src_area, src_offset); \
        dst = snd_pcm_channel_area_addr(dst_area, dst_offset); \
        src_step = snd_pcm_channel_area_step(src_area) / sizeof(TYPE); \
        dst_step = snd_pcm_channel_area_step(dst_area) / sizeof(TYPE); \
        GET_VOL_SCALE; \
        fr = frames; \
        if (! vol_scale) { \
            while (fr--) { \
                *dst = 0; \
                dst += dst_step; \
            } \
        } else if (vol_scale == 0xffff) { \
            while (fr--) { \
                *dst = *src; \
                src += src_step; \
                dst += dst_step; \
            } \
        } else { \
            while (fr--) { \
                *dst = (TYPE) MULTI_DIV_##TYPE(*src, vol_scale, swap); \
                src += src_step; \
                dst += dst_step; \
            } \
        } \
    } \
} while (0)

#define GET_VOL_SCALE \
    switch (ch) { \
    case 0: \
    case 2: \
        vol_scale = (channels == ch + 1) ? vol_c : vol[0]; \
        break; \
    case 4: \
    case 5: \
        vol_scale = vol_c; \
        break; \
    default: \
        vol_scale = vol[ch & 1]; \
        break; \
    }

static void softvol_convert_stereo_vol(snd_pcm_softvol_t *svol,
                       const snd_pcm_channel_area_t *dst_areas,
                       snd_pcm_uframes_t dst_offset,
                       const snd_pcm_channel_area_t *src_areas,
                       snd_pcm_uframes_t src_offset,
                       unsigned int channels,
                       snd_pcm_uframes_t frames)
{
    const snd_pcm_channel_area_t *dst_area, *src_area;
    unsigned int src_step, dst_step;
    unsigned int vol_scale, vol[2], vol_c;

#if 0
    /* for test */
    snd_pcm_areas_copy(dst_areas, dst_offset, src_areas, src_offset,
               channels, frames, svol->sformat);
    return;
#endif
    if (svol->cur_vol[0] == 0 && svol->cur_vol[1] == 0) {
        snd_pcm_areas_silence(dst_areas, dst_offset, channels, frames,
                      svol->sformat);
        return;
    } else if (svol->zero_dB_val && svol->cur_vol[0] == svol->zero_dB_val &&
           svol->cur_vol[1] == svol->zero_dB_val) {
        snd_pcm_areas_copy(dst_areas, dst_offset, src_areas, src_offset,
                   channels, frames, svol->sformat);
        return;
    }

    if (svol->max_val == 1) {
        vol[0] = svol->cur_vol[0] ? 0xffff : 0;
        vol[1] = svol->cur_vol[1] ? 0xffff : 0;
        vol_c = vol[0] | vol[1];
    } else {
        vol[0] = svol->dB_value[svol->cur_vol[0]];
        vol[1] = svol->dB_value[svol->cur_vol[1]];
        vol_c = svol->dB_value[(svol->cur_vol[0] + svol->cur_vol[1]) / 2];
    }
    switch (svol->sformat) {
    case SND_PCM_FORMAT_S16_LE:
    case SND_PCM_FORMAT_S16_BE:
        /* 16bit samples */
        CONVERT_AREA(short,
                 !snd_pcm_format_little_endian(svol->sformat));
        break;
    case SND_PCM_FORMAT_S32_LE:
    case SND_PCM_FORMAT_S32_BE:
        /* 32bit samples */
        CONVERT_AREA(int,
                 !snd_pcm_format_little_endian(svol->sformat));
        break;
#if 0
    case SND_PCM_FORMAT_S24_3LE:
        CONVERT_AREA_S24_3LE();
#endif
        break;
    default:
        break;
    }
}

#undef GET_VOL_SCALE
#define GET_VOL_SCALE
static void softvol_convert_mono_vol(snd_pcm_softvol_t *svol,
                     const snd_pcm_channel_area_t *dst_areas,
                     snd_pcm_uframes_t dst_offset,
                     const snd_pcm_channel_area_t *src_areas,
                     snd_pcm_uframes_t src_offset,
                     unsigned int channels,
                     snd_pcm_uframes_t frames)
{
    const snd_pcm_channel_area_t *dst_area, *src_area;
    unsigned int src_step, dst_step;
    unsigned int vol_scale;

#if 0
    /* for test */
    snd_pcm_areas_copy(dst_areas, dst_offset, src_areas, src_offset,
               channels, frames, svol->sformat);
    return;
#else
    if (svol->cur_vol[0] == 0) {
        snd_pcm_areas_silence(dst_areas, dst_offset, channels, frames,
                      svol->sformat);
        return;
    } else if (svol->zero_dB_val && svol->cur_vol[0] == svol->zero_dB_val) {
        snd_pcm_areas_copy(dst_areas, dst_offset, src_areas, src_offset,
                   channels, frames, svol->sformat);
        return;
    }
#endif

    if (svol->max_val == 1)
        vol_scale = svol->cur_vol[0] ? 0xffff : 0;
    else
        vol_scale = svol->dB_value[svol->cur_vol[0]];
    switch (svol->sformat) {
    case SND_PCM_FORMAT_S16_LE:
    case SND_PCM_FORMAT_S16_BE:
        /* 16bit samples */
        CONVERT_AREA(short,
                 !snd_pcm_format_little_endian(svol->sformat));
        break;
    case SND_PCM_FORMAT_S32_LE:
    case SND_PCM_FORMAT_S32_BE:
        /* 32bit samples */
        CONVERT_AREA(int,
                 !snd_pcm_format_little_endian(svol->sformat));
        break;
#if 0
    case SND_PCM_FORMAT_S24_3LE:
        CONVERT_AREA_S24_3LE();
#endif
        break;
    default:
        break;
    }
}

static void get_current_volume(snd_pcm_softvol_t *svol)
{
    unsigned int i;
    snd_ctl_info_t info;
    int ret;

    ret = snd_ctl_get(svol->control->card_name,
                svol->control->control_name,
                &info);
    if (ret < 0) {
        awalsa_err("get ctl elem[%s] failed\n", svol->control->control_name);
        return;
    }
    for (i = 0; i < svol->cchannels && i < 2; i++) {
        svol->cur_vol[i] = (unsigned int)info.value;
    }
}

static snd_pcm_uframes_t
snd_pcm_softvol_read_areas(snd_pcm_t *pcm,
            const snd_pcm_channel_area_t *areas,
            snd_pcm_uframes_t offset,
            snd_pcm_uframes_t size,
            const snd_pcm_channel_area_t *slave_areas,
            snd_pcm_uframes_t slave_offset,
            snd_pcm_uframes_t *slave_sizep)
{
    snd_pcm_softvol_t *svol = pcm->private_data;
    if (size > *slave_sizep)
        size = *slave_sizep;
    get_current_volume(svol);
    if (svol->cchannels == 1)
        softvol_convert_mono_vol(svol, areas, offset, slave_areas,
                slave_offset, pcm->channels, size);
    else
        softvol_convert_stereo_vol(svol, areas, offset, slave_areas,
                slave_offset, pcm->channels, size);
    *slave_sizep = size;
    return size;
}

static snd_pcm_uframes_t
snd_pcm_softvol_write_areas(snd_pcm_t *pcm,
            const snd_pcm_channel_area_t *areas,
            snd_pcm_uframes_t offset,
            snd_pcm_uframes_t size,
            const snd_pcm_channel_area_t *slave_areas,
            snd_pcm_uframes_t slave_offset,
            snd_pcm_uframes_t *slave_sizep)
{
    snd_pcm_softvol_t *svol = pcm->private_data;
    if (size > *slave_sizep)
        size = *slave_sizep;
    /*awalsa_info("cchannels=%d, offset=%u, size:%u, slave_offset=%u, slave_size=%u\n",*/
            /*svol->cchannels, offset, size, slave_offset, *slave_sizep);*/
    get_current_volume(svol);

    if (svol->cchannels == 1)
        softvol_convert_mono_vol(svol, slave_areas, slave_offset,
                areas, offset, pcm->channels, size);
    else
        softvol_convert_stereo_vol(svol, slave_areas, slave_offset,
                areas, offset, pcm->channels, size);
    *slave_sizep = size;
    return size;
}

static void softvol_free(snd_pcm_softvol_t *svol)
{
    if (svol->plug.gen.close_slave)
        snd_pcm_close(svol->plug.gen.slave);
    if (svol->dB_value && svol->dB_value != preset_dB_value)
        snd_free(svol->dB_value);
    snd_free(svol);
}

static int snd_pcm_softvol_close(snd_pcm_t *pcm)
{
    snd_pcm_softvol_t *svol = pcm->private_data;
    softvol_free(svol);
    return 0;
}

static int snd_pcm_softvol_hw_refine_cprepare(snd_pcm_t *pcm,
                          snd_pcm_hw_params_t *params)
{
    int err;
    snd_pcm_softvol_t *svol = pcm->private_data;
    snd_interval_t access_mask = { .mask = SND_PCM_ACCBIT_SHM };
    snd_interval_t format_mask = {
        .mask =
            (1ULL << SND_PCM_FORMAT_S16_LE) |
            (1ULL << SND_PCM_FORMAT_S16_BE) |
            (1ULL << SND_PCM_FORMAT_S32_LE) |
            (1ULL << SND_PCM_FORMAT_S32_BE)
    };

    awalsa_debug("\n");
    if (svol->sformat != SND_PCM_FORMAT_UNKNOWN) {
        snd_mask_none(&format_mask);
        snd_mask_set(&format_mask, (unsigned long)svol->sformat);
    }
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

static int snd_pcm_softvol_hw_refine_sprepare(snd_pcm_t *pcm, snd_pcm_hw_params_t *sparams)
{
    snd_pcm_softvol_t *svol = pcm->private_data;
    snd_interval_t saccess_mask = { .mask = SND_PCM_ACCBIT_MMAP };
    awalsa_debug("\n");
    _snd_pcm_hw_params_any(sparams);
    _snd_pcm_hw_param_set_mask(sparams, SND_PCM_HW_PARAM_ACCESS,
                   &saccess_mask);
    if (svol->sformat != SND_PCM_FORMAT_UNKNOWN) {
        _snd_pcm_hw_param_set(sparams, SND_PCM_HW_PARAM_FORMAT,
                (unsigned long)svol->sformat, 0);
    }
    return 0;
}

/*
 * refine the access mask
 */
static int check_access_mask(snd_pcm_hw_params_t *src,
                 snd_pcm_hw_params_t *dst)
{
    const snd_interval_t *mask;
    snd_interval_t smask;

    mask = hw_param_interval_c(src, SND_PCM_HW_PARAM_ACCESS);
    snd_mask_none(&smask);
    if (snd_mask_test(mask, (unsigned long)SND_PCM_ACCESS_RW_INTERLEAVED) ||
        snd_mask_test(mask, (unsigned long)SND_PCM_ACCESS_MMAP_INTERLEAVED)) {
        snd_mask_set(&smask, (unsigned long)SND_PCM_ACCESS_RW_INTERLEAVED);
        snd_mask_set(&smask, (unsigned long)SND_PCM_ACCESS_MMAP_INTERLEAVED);
    }
    if (snd_mask_test(mask, (unsigned long)SND_PCM_ACCESS_RW_NONINTERLEAVED) ||
        snd_mask_test(mask, (unsigned long)SND_PCM_ACCESS_MMAP_NONINTERLEAVED))  {
        snd_mask_set(&smask, (unsigned long)SND_PCM_ACCESS_RW_NONINTERLEAVED);
        snd_mask_set(&smask, (unsigned long)SND_PCM_ACCESS_MMAP_NONINTERLEAVED);
    }
    if (snd_mask_test(mask, (unsigned long)SND_PCM_ACCESS_MMAP_COMPLEX))
        snd_mask_set(&smask, (unsigned long)SND_PCM_ACCESS_MMAP_COMPLEX);

    return _snd_pcm_hw_param_set_mask(dst, SND_PCM_HW_PARAM_ACCESS, &smask);
}

static int snd_pcm_softvol_hw_refine_schange(snd_pcm_t *pcm,
                         snd_pcm_hw_params_t *params,
                         snd_pcm_hw_params_t *sparams)
{
    snd_pcm_softvol_t *svol = pcm->private_data;
    int err;
    unsigned int links = (SND_PCM_HW_PARBIT_CHANNELS |
                  SND_PCM_HW_PARBIT_RATE |
                  SND_PCM_HW_PARBIT_PERIODS |
                  SND_PCM_HW_PARBIT_PERIOD_SIZE |
                  SND_PCM_HW_PARBIT_PERIOD_TIME |
                  SND_PCM_HW_PARBIT_BUFFER_SIZE |
                  SND_PCM_HW_PARBIT_BUFFER_TIME);

    awalsa_debug("\n");
    if (svol->sformat == SND_PCM_FORMAT_UNKNOWN)
        links |= (SND_PCM_HW_PARBIT_FORMAT |
              SND_PCM_HW_PARBIT_SAMPLE_BITS);
    err = _snd_pcm_hw_params_refine(sparams, links, params);
    if (err < 0)
        return err;

    err = check_access_mask(params, sparams);
    if (err < 0)
        return err;

    return 0;
}

static int snd_pcm_softvol_hw_refine_cchange(snd_pcm_t *pcm,
                         snd_pcm_hw_params_t *params,
                        snd_pcm_hw_params_t *sparams)
{
    snd_pcm_softvol_t *svol = pcm->private_data;
    int err;
    unsigned int links = (SND_PCM_HW_PARBIT_CHANNELS |
                  SND_PCM_HW_PARBIT_RATE |
                  SND_PCM_HW_PARBIT_PERIODS |
                  SND_PCM_HW_PARBIT_PERIOD_SIZE |
                  SND_PCM_HW_PARBIT_PERIOD_TIME |
                  SND_PCM_HW_PARBIT_BUFFER_SIZE |
                  SND_PCM_HW_PARBIT_BUFFER_TIME);

    awalsa_debug("\n");
    if (svol->sformat == SND_PCM_FORMAT_UNKNOWN)
        links |= (SND_PCM_HW_PARBIT_FORMAT |
              SND_PCM_HW_PARBIT_SAMPLE_BITS);
    err = _snd_pcm_hw_params_refine(params, links, sparams);
    if (err < 0)
        return err;

    err = check_access_mask(sparams, params);
    if (err < 0)
        return err;

    return 0;
}

static int snd_pcm_softvol_hw_refine(snd_pcm_t *pcm, snd_pcm_hw_params_t *params)
{
    return snd_pcm_hw_refine_slave(pcm, params,
                       snd_pcm_softvol_hw_refine_cprepare,
                       snd_pcm_softvol_hw_refine_cchange,
                       snd_pcm_softvol_hw_refine_sprepare,
                       snd_pcm_softvol_hw_refine_schange,
                       snd_pcm_generic_hw_refine);
}

static int snd_pcm_softvol_hw_params(snd_pcm_t *pcm, snd_pcm_hw_params_t * params)
{
    snd_pcm_softvol_t *svol = pcm->private_data;
    snd_pcm_t *slave = svol->plug.gen.slave;
#if 0
    snd_pcm_format_t src_format, dst_format;
    int err;
    snd_pcm_hw_params_t *slave_params;

    awalsa_debug("\n");

    snd_pcm_hw_params_alloca(&slave_params);
    memcpy(slave_params, params, sizeof(snd_pcm_hw_params_t));

    snd_pcm_hw_param_change(slave_params, SND_PCM_HW_PARAM_ACCESS);
    err = snd_pcm_hw_params_set_access(slave, slave_params, SND_PCM_ACCESS_MMAP_INTERLEAVED);
    if (err < 0) {
        awalsa_err("snd_pcm_hw_params_set_access failed\n");
        return err;
    }

    err = _snd_pcm_hw_params_internal(slave, slave_params);
    if (err < 0) {
        awalsa_err("failed to set slave hw params\n");
        return err;
    }
    /*TODO*/
    memcpy(params, slave_params, sizeof(snd_pcm_hw_params_t));
#else
    awalsa_debug("\n");
    int err = snd_pcm_hw_params_slave(pcm, params,
                      snd_pcm_softvol_hw_refine_cchange,
                      snd_pcm_softvol_hw_refine_sprepare,
                      snd_pcm_softvol_hw_refine_schange,
                      snd_pcm_generic_hw_params);
    if (err < 0)
        return err;
#endif

    if (slave->format != SND_PCM_FORMAT_S16_LE &&
        slave->format != SND_PCM_FORMAT_S16_BE &&
#if 0
        slave->format != SND_PCM_FORMAT_S24_3LE &&
#endif
        slave->format != SND_PCM_FORMAT_S32_LE &&
        slave->format != SND_PCM_FORMAT_S32_BE) {
        awalsa_err("softvol supports only S16_LE, S16_BE, S24_3LE, S32_LE "
               " or S32_BE");
        return -EINVAL;
    }
    svol->sformat = slave->format;
    return 0;
}

static void snd_pcm_softvol_dump(snd_pcm_t *pcm)
{
    snd_pcm_softvol_t *svol = pcm->private_data;

    printf("Soft volume PCM\n");
    printf("Control: %s\n", svol->control->control_name);
    if (svol->max_val == 1) {
        printf("boolean\n");
    } else {
        printf("min_dB: %g\n", svol->min_dB);
        printf("max_dB: %g\n", svol->max_dB);
        printf("resolution: %d\n", svol->max_val + 1);
    }
    if (pcm->setup) {
        printf("Its setup is:\n");
        snd_pcm_dump_setup(pcm);
    }
    printf("Slave: ");
    snd_pcm_dump(svol->plug.gen.slave);
}

static const snd_pcm_ops_t snd_pcm_softvol_ops = {
    .close = snd_pcm_softvol_close,
    /*.info = snd_pcm_generic_info,*/
    .hw_refine = snd_pcm_softvol_hw_refine,
    .hw_params = snd_pcm_softvol_hw_params,
    .hw_free = snd_pcm_generic_hw_free,
    .sw_params = snd_pcm_generic_sw_params,
    .channel_info = snd_pcm_generic_channel_info,
    .dump = snd_pcm_softvol_dump,
    /*.nonblock = snd_pcm_generic_nonblock,*/
    /*.async = snd_pcm_generic_async,*/
    .mmap = snd_pcm_generic_mmap,
    .munmap = snd_pcm_generic_munmap,
    .query_chmaps = snd_pcm_generic_query_chmaps,
    .get_chmap = snd_pcm_generic_get_chmap,
    .set_chmap = snd_pcm_generic_set_chmap,
};

static int softvol_load_control(snd_pcm_t *pcm, snd_pcm_softvol_t *svol,
                int cchannels, double min_dB, double max_dB,
                int resolution)
{
    int ret;
    unsigned int i;
    snd_ctl_info_t info;

    svol->max_val = resolution - 1;
    svol->min_dB = min_dB;
    svol->max_dB = max_dB;

    if (svol->max_val == 1 || svol->max_dB == ZERO_DB)
        svol->zero_dB_val = svol->max_val;
    else if (svol->max_dB < 0)
        svol->zero_dB_val = 0;
    else
        svol->zero_dB_val = (min_dB / (min_dB - max_dB)) *
                    svol->max_val;
    awalsa_debug("\n");
    ret = snd_ctl_get(svol->control->card_name, svol->control->control_name, &info);
    if (ret < 0) {
        memset(&info, 0, sizeof(snd_ctl_info_t));
        info.name = svol->control->control_name;
        info.value = svol->max_val;
        info.count = cchannels;
        info.min = 0;
        info.max = svol->max_val;
        ret = snd_ctl_add(svol->control->card_name, &info);
        if (ret < 0) {
            awalsa_err("create snd ctl failed\n");
            return -1;
        }
    } else {
        /* check kcontrol range */
        if (info.max != svol->max_val ||
            info.min != 0 ||
            info.count != cchannels) {
            awalsa_err("exist kcontrol(%s) max:%d,min:%d,count:%d\n"
                "but now range is max:%d, min:%d, count:%d\n",
                info.name, info.max, info.min, info.count,
                svol->max_val, 0, cchannels);
            return -1;
        }
    }
    awalsa_debug("\n");

    if (min_dB == PRESET_MIN_DB && max_dB == ZERO_DB &&
            resolution == PRESET_RESOLUTION)
        svol->dB_value = (unsigned int *)preset_dB_value;
    else {
        svol->dB_value = calloc(resolution, sizeof(unsigned int));
        if (! svol->dB_value) {
            awalsa_err("cannot allocate dB table\n");
            return -ENOMEM;
        }
        svol->min_dB = min_dB;
        svol->max_dB = max_dB;
        for (i = 0; i <= svol->max_val; i++) {
            double db = svol->min_dB +
                (i * (svol->max_dB - svol->min_dB)) /
                svol->max_val;
            double v = (pow(10.0, db / 20.0) *
            (double)(1 << VOL_SCALE_SHIFT));

            svol->dB_value[i] = (unsigned int)v;
        }
        if (svol->zero_dB_val)
            svol->dB_value[svol->zero_dB_val] = 65535;
    }
    return ret;
}

int _snd_pcm_softvol_open(snd_pcm_t **pcmp, const snd_pcm_config_t *pcm_config,
        snd_pcm_stream_t stream, int mode)
{
    int ret;
    const snd_pcm_softvol_config_t *svol_config = (const snd_pcm_softvol_config_t *)(pcm_config->config);
    const snd_pcm_config_t *sconf = NULL;
    snd_pcm_t *pcm = NULL, *spcm = NULL;
    snd_pcm_softvol_t *svol = NULL;
    snd_pcm_format_t sformat = SND_PCM_FORMAT_UNKNOWN;
    int resolution = PRESET_RESOLUTION;
    double min_dB = PRESET_MIN_DB;
    double max_dB = ZERO_DB;
    int cchannels = 1;

    awalsa_debug("\n");
    sconf = snd_pcm_config_get_config(svol_config->slave.pcm);
    if (!sconf) {
        awalsa_err("can't find softvol slave pcm\n");
        return -EINVAL;
    }

    if (svol_config->resolution != 0)
        resolution = svol_config->resolution;
    if (svol_config->min_dB != 0)
        min_dB = svol_config->min_dB;
    if (svol_config->max_dB != 0)
        max_dB = svol_config->max_dB;
    if (svol_config->control.count != 0)
        cchannels = svol_config->control.count;
    awalsa_debug("resolution=%d, min_dB=%0.6f, max_dB=%0.6f, cchannels=%d\n",
            resolution, min_dB, max_dB, cchannels);

    ret = snd_pcm_open_config(&spcm, sconf, stream, mode);
    if (ret < 0) {
        awalsa_err("unable to open slave\n");
        goto err;
    }

    awalsa_debug("\n");

    svol = snd_malloc(sizeof(snd_pcm_softvol_t));
    if (!svol) {
        awalsa_err("no memory\n");
        ret = -ENOMEM;
        goto err;
    }

    snd_pcm_plugin_init(&svol->plug);
    svol->control = &svol_config->control;
    svol->sformat = sformat;
    svol->cchannels = cchannels;
    svol->plug.read = snd_pcm_softvol_read_areas;
    svol->plug.write = snd_pcm_softvol_write_areas;
    svol->plug.undo_read = snd_pcm_plugin_undo_read_generic;
    svol->plug.undo_write = snd_pcm_plugin_undo_write_generic;
    svol->plug.gen.slave = spcm;
    svol->plug.gen.close_slave = 1;

    /* load control  */
    ret = softvol_load_control(spcm, svol, cchannels, min_dB, max_dB, resolution);
    if (ret < 0) {
        awalsa_err("load control failed\n");
        goto err;
    }

    awalsa_debug("\n");
    ret = snd_pcm_new(&pcm, SND_PCM_TYPE_SOFTVOL, pcm_config->name, spcm->stream, spcm->mode);
    /*ret = snd_pcm_new(&pcm, SND_PCM_TYPE_SOFTVOL, pcm_config->name, spcm->stream, mode);*/
    if (ret < 0) {
        awalsa_err("failed to new softvol pcm\n");
        goto err;
    }

    awalsa_debug("\n");
    pcm->ops = &snd_pcm_softvol_ops;
    pcm->fast_ops = &snd_pcm_plugin_fast_ops;
    pcm->private_data = svol;

    pcm->mmap_shadow = 1;
    snd_pcm_set_hw_ptr(pcm, &svol->plug.hw_ptr, 0, 0);
    snd_pcm_set_appl_ptr(pcm, &svol->plug.appl_ptr, 0, 0);
    awalsa_debug("\n");

    *pcmp = pcm;
    return 0;
err:
    if (svol)
        softvol_free(svol);
    if (pcm)
        snd_pcm_free(pcm);
    return ret;
}
