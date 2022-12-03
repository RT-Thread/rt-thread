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
#include <string.h>
#include <sound/snd_core.h>
#include <sound/snd_pcm.h>
#include <sound/snd_misc.h>
#include <aw_common.h>
#include <sound/pcm_common.h>



struct pcm_format_data {
    unsigned char width;    /* bit width */
    unsigned char phys; /* physical bit width */
    signed char le; /* 0 = big-endian, 1 = little-endian, -1 = others */
    signed char signd;  /* 0 = unsigned, 1 = signed, -1 = others */
    unsigned char silence[8];   /* silence data to fill */
};

static struct pcm_format_data pcm_formats[(int)SND_PCM_FORMAT_LAST+1] = {
    [SND_PCM_FORMAT_S8] = {
        .width = 8, .phys = 8, .le = -1, .signd = 1,
        .silence = {},
    },
    [SND_PCM_FORMAT_U8] = {
        .width = 8, .phys = 8, .le = -1, .signd = 0,
        .silence = { 0x80 },
    },
    [SND_PCM_FORMAT_S16_LE] = {
        .width = 16, .phys = 16, .le = 1, .signd = 1,
        .silence = {},
    },
    [SND_PCM_FORMAT_S16_BE] = {
        .width = 16, .phys = 16, .le = 0, .signd = 1,
        .silence = {},
    },
    [SND_PCM_FORMAT_U16_LE] = {
        .width = 16, .phys = 16, .le = 1, .signd = 0,
        .silence = { 0x00, 0x80 },
    },
    [SND_PCM_FORMAT_U16_BE] = {
        .width = 16, .phys = 16, .le = 0, .signd = 0,
        .silence = { 0x80, 0x00 },
    },
    [SND_PCM_FORMAT_S24_LE] = {
        .width = 24, .phys = 32, .le = 1, .signd = 1,
        .silence = {},
    },
    [SND_PCM_FORMAT_S24_BE] = {
        .width = 24, .phys = 32, .le = 0, .signd = 1,
        .silence = {},
    },
    [SND_PCM_FORMAT_U24_LE] = {
        .width = 24, .phys = 32, .le = 1, .signd = 0,
        .silence = { 0x00, 0x00, 0x80 },
    },
    [SND_PCM_FORMAT_U24_BE] = {
        .width = 24, .phys = 32, .le = 0, .signd = 0,
        .silence = { 0x00, 0x80, 0x00, 0x00 },
    },
    [SND_PCM_FORMAT_S32_LE] = {
        .width = 32, .phys = 32, .le = 1, .signd = 1,
        .silence = {},
    },
    [SND_PCM_FORMAT_S32_BE] = {
        .width = 32, .phys = 32, .le = 0, .signd = 1,
        .silence = {},
    },
    [SND_PCM_FORMAT_U32_LE] = {
        .width = 32, .phys = 32, .le = 1, .signd = 0,
        .silence = { 0x00, 0x00, 0x00, 0x80 },
    },
    [SND_PCM_FORMAT_U32_BE] = {
        .width = 32, .phys = 32, .le = 0, .signd = 0,
        .silence = { 0x80, 0x00, 0x00, 0x00 },
    },
};


int snd_pcm_format_physical_width(snd_pcm_format_t format)
{
    int val;
    if ((int)format < 0 || (int)format > (int)SND_PCM_FORMAT_LAST)
        return -EINVAL;
    if ((val = pcm_formats[(int)format].phys) == 0)
        return -EINVAL;
    return val;
}


static unsigned int snd_pcm_rate_mask_sanitize(unsigned int rates)
{
    if (rates & SNDRV_PCM_RATE_CONTINUOUS)
        return SNDRV_PCM_RATE_CONTINUOUS;
    else if (rates & SNDRV_PCM_RATE_KNOT)
        return SNDRV_PCM_RATE_KNOT;
    return rates;
}

unsigned int snd_pcm_rate_mask_intersect(unsigned int rates_a, unsigned int rates_b)
{
    rates_a = snd_pcm_rate_mask_sanitize(rates_a);
        rates_b = snd_pcm_rate_mask_sanitize(rates_b);

        if (rates_a & SNDRV_PCM_RATE_CONTINUOUS)
                return rates_b;
        else if (rates_b & SNDRV_PCM_RATE_CONTINUOUS)
                return rates_a;
        else if (rates_a & SNDRV_PCM_RATE_KNOT)
                return rates_b;
        else if (rates_b & SNDRV_PCM_RATE_KNOT)
                return rates_a;
        return rates_a & rates_b;
}

static unsigned int rates[] = { 5512, 8000, 11025, 16000, 22050, 32000, 44100,
                                 48000, 64000, 88200, 96000, 176400, 192000 };

const struct snd_pcm_hw_constraint_list snd_pcm_known_rates = {
        .count = ARRAY_SIZE(rates),
        .list = rates,
};

int snd_pcm_limit_hw_rates(struct snd_pcm_runtime *runtime)
{
        int i;
        for (i = 0; i < (int)snd_pcm_known_rates.count; i++) {
                if (runtime->hw.rates & (1 << i)) {
                        runtime->hw.rate_min = snd_pcm_known_rates.list[i];
                        break;
                }
        }
        for (i = (int)snd_pcm_known_rates.count - 1; i >= 0; i--) {
                if (runtime->hw.rates & (1 << i)) {
                        runtime->hw.rate_max = snd_pcm_known_rates.list[i];
                        break;
                }
        }
        return 0;
}

int snd_pcm_format_set_silence(snd_pcm_format_t format, void *data, unsigned int samples)
{
    int width;
    unsigned char *dst, *pat;

    if (format < 0 || format > SND_PCM_FORMAT_LAST)
        return -EINVAL;
    if (samples == 0)
        return 0;
    width = pcm_formats[format].phys;
    pat = pcm_formats[format].silence;
    if (!width)
        return -EINVAL;
    /* signed or 1 byte data */
    if (pcm_formats[format].signd == 1 || width <= 8) {
        unsigned int bytes = samples * width / 8;
        memset(data, *pat, bytes);
    }

    /* non-zero samples, fill using a loop */
    width /= 8;
    dst = data;
#if 0
        while (samples--) {
                memcpy(dst, pat, width);
                dst += width;
        }
#else
        /* a bit optimization for constant width */
        switch (width) {
        case 2:
                while (samples--) {
                        memcpy(dst, pat, 2);
                        dst += 2;
                }
                break;
        case 3:
                while (samples--) {
                        memcpy(dst, pat, 3);
                        dst += 3;
                }
                break;
        case 4:
                while (samples--) {
                        memcpy(dst, pat, 4);
                        dst += 4;
                }
                break;
        case 8:
                while (samples--) {
                        memcpy(dst, pat, 8);
                        dst += 8;
                }
                break;
        }
#endif
    return 0;
}
