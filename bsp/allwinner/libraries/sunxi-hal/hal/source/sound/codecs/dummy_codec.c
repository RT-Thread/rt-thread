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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sound/snd_core.h>
#include <sound/snd_pcm.h>

static struct snd_dai_ops dummy_codec_dai_ops = {
    .hw_params  = NULL,
    .shutdown   = NULL,
    .startup    = NULL,
    .trigger    = NULL,
    .prepare    = NULL,
};

static struct snd_dai dummy_codec_dai[] = {
    {
        .name       = "dummy-codecdai",
        .playback   = {
            .stream_name    = "Playback",
            .channels_min   = 1,
            .channels_max   = 16,
            .rates      = SNDRV_PCM_RATE_8000_192000
                    | SNDRV_PCM_RATE_KNOT,
            .formats    = SNDRV_PCM_FMTBIT_S16_LE
                    | SNDRV_PCM_FMTBIT_S24_LE
                    | SNDRV_PCM_FMTBIT_S32_LE,
            .rate_min       = 8000,
            .rate_max       = 192000,
        },
        .capture    = {
            .stream_name    = "Capture",
            .channels_min   = 1,
            .channels_max   = 16,
            .rates      = SNDRV_PCM_RATE_8000_192000
                    | SNDRV_PCM_RATE_KNOT,
            .formats    = SNDRV_PCM_FMTBIT_S16_LE
                    | SNDRV_PCM_FMTBIT_S24_LE
                    | SNDRV_PCM_FMTBIT_S32_LE,
            .rate_min       = 8000,
            .rate_max       = 192000,
        },
        .ops        = &dummy_codec_dai_ops,
    },
};

struct snd_codec dummy_codec = {
    .name       = "dummy_codec",
    .codec_dai  = dummy_codec_dai,
    .codec_dai_num  = ARRAY_SIZE(dummy_codec_dai),
    .private_data   = NULL,
    .probe          = NULL,
    .remove         = NULL,
};

static struct snd_dai dmic_codec_dai[] = {
    {
        .name       = "dmic-codecdai",
        .capture    = {
            .stream_name    = "Capture",
            .channels_min   = 1,
            .channels_max   = 8,
            .rates      = SNDRV_PCM_RATE_8000_48000
                    | SNDRV_PCM_RATE_KNOT,
            .formats    = SNDRV_PCM_FMTBIT_S16_LE
                    | SNDRV_PCM_FMTBIT_S24_LE
                    | SNDRV_PCM_FMTBIT_S32_LE,
            .rate_min       = 8000,
            .rate_max       = 48000,
        },
        .ops        = &dummy_codec_dai_ops,
    },
};

struct snd_codec dmic_codec = {
    .name       = "dmic_codec",
    .capture_only = 1,
    .codec_dai  = dmic_codec_dai,
    .codec_dai_num  = ARRAY_SIZE(dmic_codec_dai),
    .private_data   = NULL,
    .probe          = NULL,
    .remove         = NULL,
    .read           = NULL,
    .write          = NULL,
};

static struct snd_dai spdif_codec_dai[] = {
    {
        .name       = "spdif-codecdai",
        .playback   = {
            .stream_name    = "Playback",
            .channels_min   = 1,
            .channels_max   = 2,
            .rates      = SNDRV_PCM_RATE_8000_192000
                    | SNDRV_PCM_RATE_KNOT,
            .formats    = SNDRV_PCM_FMTBIT_S16_LE
                    | SNDRV_PCM_FMTBIT_S24_LE
                    | SNDRV_PCM_FMTBIT_S32_LE,
            .rate_min       = 8000,
            .rate_max       = 192000,
        },
        .capture    = {
            .stream_name    = "Capture",
            .channels_min   = 1,
            .channels_max   = 2,
            .rates      = SNDRV_PCM_RATE_8000_192000
                    | SNDRV_PCM_RATE_KNOT,
            .formats    = SNDRV_PCM_FMTBIT_S16_LE
                    | SNDRV_PCM_FMTBIT_S24_LE
                    | SNDRV_PCM_FMTBIT_S32_LE,
            .rate_min       = 8000,
            .rate_max       = 192000,
        },
        .ops        = &dummy_codec_dai_ops,
    },
};

struct snd_codec spdif_codec = {
    .name       = "spdif_codec",
    .codec_dai  = spdif_codec_dai,
    .codec_dai_num  = ARRAY_SIZE(spdif_codec_dai),
    .private_data   = NULL,
    .probe          = NULL,
    .remove         = NULL,
    .read           = NULL,
    .write          = NULL,
};
