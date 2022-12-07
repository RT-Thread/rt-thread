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
#include <hal_timer.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sound/snd_core.h>
#include <sound/snd_pcm.h>
#include <sound/snd_dma.h>
#include <sound/dma_wrap.h>
#include <hal_dma.h>
#include <hal_cmd.h>

#include "sunxi-pcm.h"
#include "sunxi-spdif.h"

static const struct spdif_rate sample_rate_orig[] = {
    {22050,  0xB},
    {24000,  0x9},
    {32000,  0xC},
    {44100,  0xF},
    {48000,  0xD},
    {88200,  0x7},
    {96000,  0x5},
    {176400, 0x3},
    {192000, 0x1},
};

static const struct spdif_rate sample_rate_freq[] = {
    {22050,  0x4},
    {24000,  0x6},
    {32000,  0x3},
    {44100,  0x0},
    {48000,  0x2},
    {88200,  0x8},
    {96000,  0xA},
    {176400, 0xC},
    {192000, 0xE},
};

static int sunxi_spdif_get_audio_mode(struct snd_kcontrol *kcontrol,
        struct snd_ctl_info *info)
{
    unsigned int reg_val;
    unsigned long value = 0;

    snd_print("\n");
    if (kcontrol->type != SND_CTL_ELEM_TYPE_ENUMERATED) {
        snd_err("invalid kcontrol type = %d.\n", kcontrol->type);
        return -EINVAL;
    }

    if (kcontrol->private_data_type == SND_MODULE_PLATFORM) {
        struct snd_platform *platform = kcontrol->private_data;
        reg_val = snd_platform_read(platform, SUNXI_SPDIF_TXCFG);
        value = ((reg_val >> TXCFG_DATA_TYPE) & 0x1);
    } else {
        snd_err("invalid kcontrol data type = %d.\n",
                kcontrol->private_data_type);
        return -EINVAL;
    }

    snd_kcontrol_to_snd_ctl_info(kcontrol, info, value);

    return 0;
}

static int sunxi_spdif_set_audio_mode(struct snd_kcontrol *kcontrol,
                        unsigned long value)
{
    snd_print("\n");
    if (kcontrol->type != SND_CTL_ELEM_TYPE_ENUMERATED) {
        snd_err("invalid kcontrol type = %d.\n", kcontrol->type);
        return -EINVAL;
    }

    if (value >= kcontrol->items) {
        snd_err("invalid kcontrol items = %ld.\n", value);
        return -EINVAL;
    }

    if (kcontrol->private_data_type == SND_MODULE_PLATFORM) {
        struct snd_platform *platform = kcontrol->private_data;
        struct sunxi_spdif_info *sunxi_spdif = platform->private_data;
        snd_platform_update_bits(platform, SUNXI_SPDIF_TXCFG,
            (0x1 << TXCFG_CHAN_STA_EN), (value << TXCFG_CHAN_STA_EN));
        snd_platform_update_bits(platform, SUNXI_SPDIF_TXCFG,
            (0x1 << TXCFG_DATA_TYPE), (value << TXCFG_DATA_TYPE));
        snd_platform_update_bits(platform, SUNXI_SPDIF_TXCH_STA0,
            (0x1 << TXCHSTA0_AUDIO), (value << TXCHSTA0_AUDIO));
        snd_platform_update_bits(platform, SUNXI_SPDIF_RXCH_STA0,
            (0x1 << RXCHSTA0_AUDIO), (value << RXCHSTA0_AUDIO));
    } else {
        snd_err("invalid kcontrol data type = %d.\n",
                kcontrol->private_data_type);
    }
    snd_info("mask:0x%x, items:%d, value:0x%x\n",
            kcontrol->mask, kcontrol->items, value);

    return 0;
}

#ifdef CONFIG_SND_SUNXI_SPDIF_RX_IEC61937
static int sunxi_spdif_get_rx_data_type(struct snd_kcontrol *kcontrol,
        struct snd_ctl_info *info)
{
    unsigned int reg_val;
    unsigned long value = 0;

    snd_print("\n");
    if (kcontrol->type != SND_CTL_ELEM_TYPE_ENUMERATED) {
        snd_err("invalid kcontrol type = %d.\n", kcontrol->type);
        return -EINVAL;
    }

    if (kcontrol->private_data_type == SND_MODULE_PLATFORM) {
        struct snd_platform *platform = kcontrol->private_data;
        struct sunxi_spdif_info *sunxi_spdif = platform->private_data;
        reg_val = snd_platform_read(platform, SUNXI_SPDIF_EXP_CTL);
        value = ((reg_val >> RX_MODE_MAN) & 0x1);
    } else {
        snd_err("invalid kcontrol data type = %d.\n",
                kcontrol->private_data_type);
        return -EINVAL;
    }

    snd_kcontrol_to_snd_ctl_info(kcontrol, info, value);

    return 0;
}

static int sunxi_spdif_set_rx_data_type(struct snd_kcontrol *kcontrol,
                        unsigned long value)
{
    snd_print("\n");
    if (kcontrol->type != SND_CTL_ELEM_TYPE_ENUMERATED) {
        snd_err("invalid kcontrol type = %d.\n", kcontrol->type);
        return -EINVAL;
    }

    if (value >= kcontrol->items) {
        snd_err("invalid kcontrol items = %ld.\n", value);
        return -EINVAL;
    }

    if (kcontrol->private_data_type == SND_MODULE_PLATFORM) {
        struct snd_platform *platform = kcontrol->private_data;
        struct sunxi_spdif_info *sunxi_spdif = platform->private_data;
        snd_platform_update_bits(platform, SUNXI_SPDIF_EXP_CTL,
            (0x1 << RX_MODE), (0x0 << RX_MODE));
        snd_platform_update_bits(platform, SUNXI_SPDIF_EXP_CTL,
            (0x1 << RX_MODE_MAN), (value << RX_MODE_MAN));
    } else {
        snd_err("invalid kcontrol data type = %d.\n",
                kcontrol->private_data_type);
    }
    snd_info("mask:0x%x, items:%d, value:0x%x\n",
            kcontrol->mask, kcontrol->items, value);

    return 0;
}
#endif

static int sunxi_spdif_get_audio_hub_mode(struct snd_kcontrol *kcontrol,
        struct snd_ctl_info *info)
{
    unsigned int reg_val;
    unsigned long value = 0;

    snd_print("\n");
    if (kcontrol->type != SND_CTL_ELEM_TYPE_ENUMERATED) {
        snd_err("invalid kcontrol type = %d.\n", kcontrol->type);
        return -EINVAL;
    }

    if (kcontrol->private_data_type == SND_MODULE_PLATFORM) {
        struct snd_platform *platform = kcontrol->private_data;
        struct sunxi_spdif_info *sunxi_spdif = platform->private_data;
        reg_val = snd_platform_read(platform, SUNXI_SPDIF_FIFO_CTL);
        value = ((reg_val >> FIFO_CTL_HUBEN) & 0x1);
    } else {
        snd_err("invalid kcontrol data type = %d.\n",
                kcontrol->private_data_type);
        return -EINVAL;
    }

    snd_kcontrol_to_snd_ctl_info(kcontrol, info, value);

    return 0;
}

static int sunxi_spdif_set_audio_hub_mode(struct snd_kcontrol *kcontrol,
                        unsigned long value)
{
    snd_print("\n");
    if (kcontrol->type != SND_CTL_ELEM_TYPE_ENUMERATED) {
        snd_err("invalid kcontrol type = %d.\n", kcontrol->type);
        return -EINVAL;
    }

    if (value >= kcontrol->items) {
        snd_err("invalid kcontrol items = %ld.\n", value);
        return -EINVAL;
    }

    if (kcontrol->private_data_type == SND_MODULE_PLATFORM) {
        struct snd_platform *platform = kcontrol->private_data;
        struct sunxi_spdif_info *sunxi_spdif = platform->private_data;
        snd_platform_update_bits(platform, SUNXI_SPDIF_FIFO_CTL,
            (0x1 << FIFO_CTL_HUBEN), (value << FIFO_CTL_HUBEN));
        snd_platform_update_bits(platform, SUNXI_SPDIF_TXCFG,
            (0x1 << TXCFG_TXEN), (value << TXCFG_TXEN));
    } else {
        snd_err("invalid kcontrol data type = %d.\n",
                kcontrol->private_data_type);
    }
    snd_info("mask:0x%x, items:%d, value:0x%x\n",
            kcontrol->mask, kcontrol->items, value);

    return 0;
}

static const char * const sunxi_spdif_audio_format_function[] = {"PCM", "DTS"};

#ifdef CONFIG_SND_SUNXI_SPDIF_RX_IEC61937
static const char * const sunxi_spdif_rx_data_type[] = {"IEC-60958", "IEC-61937"};
#endif

static const char * const sunxi_spdif_audio_hub_mode[] = {"Disabled", "Enabled"};

static struct snd_kcontrol sunxi_spdif_controls[] = {
    SND_CTL_ENUM_EXT("spdif audio format function",
                ARRAY_SIZE(sunxi_spdif_audio_format_function),
                sunxi_spdif_audio_format_function,
                SND_CTL_ENUM_AUTO_MASK,
                sunxi_spdif_get_audio_mode,
                sunxi_spdif_set_audio_mode),
#ifdef CONFIG_SND_SUNXI_SPDIF_RX_IEC61937
    SND_CTL_ENUM_EXT("spdif rx data type",
                ARRAY_SIZE(sunxi_spdif_rx_data_type),
                sunxi_spdif_rx_data_type,
                SND_CTL_ENUM_AUTO_MASK,
                sunxi_spdif_get_rx_data_type,
                sunxi_spdif_set_rx_data_type),
#endif
    SND_CTL_ENUM_EXT("spdif audio hub mode",
                ARRAY_SIZE(sunxi_spdif_audio_hub_mode),
                sunxi_spdif_audio_hub_mode,
                SND_CTL_ENUM_AUTO_MASK,
                sunxi_spdif_get_audio_hub_mode,
                sunxi_spdif_set_audio_hub_mode),
    SND_CTL_KCONTROL("sunxi spdif loopback debug", SUNXI_SPDIF_CTL, CTL_LOOP_EN, 0x1),
};

/*
 * Configure DMA , Chan enable & Global enable
 */
static void sunxi_spdif_txctrl_enable(struct snd_platform *platform, bool enable)
{
//  struct sunxi_spdif_info *sunxi_spdif = platform->private_data;

    snd_print("\n");
    if (enable) {
        snd_platform_update_bits(platform, SUNXI_SPDIF_TXCFG,
                (0x1 << TXCFG_TXEN), (0x1 << TXCFG_TXEN));
        snd_platform_update_bits(platform, SUNXI_SPDIF_INT,
                (0x1 << INT_TXDRQEN), (0x1 << INT_TXDRQEN));
    } else {
        snd_platform_update_bits(platform, SUNXI_SPDIF_TXCFG,
                (0x1 << TXCFG_TXEN), (0x0 << TXCFG_TXEN));
        snd_platform_update_bits(platform, SUNXI_SPDIF_INT,
                (0x1 << INT_TXDRQEN), (0x0 << INT_TXDRQEN));
    }
}

static void sunxi_spdif_rxctrl_enable(struct snd_platform *platform, bool enable)
{
//  struct sunxi_spdif_info *sunxi_spdif = platform->private_data;

    snd_print("\n");
    if (enable) {
        snd_platform_update_bits(platform, SUNXI_SPDIF_RXCFG,
                (0x1 << RXCFG_CHSR_CP), (0x1 << RXCFG_CHSR_CP));

        snd_platform_update_bits(platform, SUNXI_SPDIF_INT,
                (0x1 << INT_RXDRQEN), (0x1 << INT_RXDRQEN));
        snd_platform_update_bits(platform, SUNXI_SPDIF_RXCFG,
                (0x1 << RXCFG_RXEN), (0x1 << RXCFG_RXEN));
    } else {
        snd_platform_update_bits(platform, SUNXI_SPDIF_RXCFG,
                (0x1 << RXCFG_RXEN), (0x0 << RXCFG_RXEN));
        snd_platform_update_bits(platform, SUNXI_SPDIF_INT,
                (0x1 << INT_RXDRQEN), (0x0 << INT_RXDRQEN));
    }
}

static void sunxi_spdif_init(struct snd_platform *platform)
{
//  struct sunxi_spdif_info *sunxi_spdif = platform->private_data;

    snd_print("\n");
    /* FIFO CTL register default setting */
    snd_platform_update_bits(platform, SUNXI_SPDIF_FIFO_CTL,
            (CTL_TXTL_MASK << FIFO_CTL_TXTL),
            (CTL_TXTL_DEFAULT << FIFO_CTL_TXTL));
    snd_platform_update_bits(platform, SUNXI_SPDIF_FIFO_CTL,
            (CTL_RXTL_MASK << FIFO_CTL_RXTL),
            (CTL_RXTL_DEFAULT << FIFO_CTL_RXTL));

    snd_platform_write(platform, SUNXI_SPDIF_TXCH_STA0, 0x2 << TXCHSTA0_CHNUM);
    snd_platform_write(platform, SUNXI_SPDIF_TXCH_STA0, 0x2 << RXCHSTA0_CHNUM);
}

static int sunxi_spdif_hw_params(struct snd_pcm_substream *substream,
        struct snd_pcm_hw_params *params, struct snd_dai *dai)
{
    struct snd_platform *platform = dai->component;
//  struct sunxi_spdif_info *sunxi_spdif = platform->private_data;
    unsigned int tx_input_mode = 0;
    unsigned int rx_output_mode = 0;
    unsigned int origin_freq_bit = 0, sample_freq_bit = 0;
    unsigned int reg_temp;
    unsigned int i;

    snd_print("\n");
    switch (params_format(params)) {
    case    SNDRV_PCM_FORMAT_S16_LE:
        reg_temp = 0;
        tx_input_mode = 1;
        rx_output_mode = 3;
        break;
/*
    case    SNDRV_PCM_FORMAT_S20_3LE:
        reg_temp = 1;
        tx_input_mode = 0;
        rx_output_mode = 0;
        break;
*/
    case    SNDRV_PCM_FORMAT_S24_LE:
    /* only for the compatible of tinyalsa */
    case    SNDRV_PCM_FORMAT_S32_LE:
        reg_temp = 2;
        tx_input_mode = 0;
        rx_output_mode = 0;
        break;
    default:
        snd_err("sunxi spdif params_format[%d] error!\n", params_format(params));
        return -EINVAL;
    }

    for (i = 0; i < ARRAY_SIZE(sample_rate_orig); i++) {
        if (params_rate(params) == sample_rate_orig[i].samplerate) {
            origin_freq_bit = sample_rate_orig[i].rate_bit;
            break;
        }
    }

    for (i = 0; i < ARRAY_SIZE(sample_rate_freq); i++) {
        if (params_rate(params) == sample_rate_freq[i].samplerate) {
            sample_freq_bit = sample_rate_freq[i].rate_bit;
//          sunxi_spdif->rate = sample_rate_freq[i].samplerate;
            break;
        }
    }

    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
        snd_platform_update_bits(platform, SUNXI_SPDIF_TXCFG,
                (0x3 << TXCFG_SAMPLE_BIT),
                (reg_temp<<TXCFG_SAMPLE_BIT));

        snd_platform_update_bits(platform, SUNXI_SPDIF_FIFO_CTL,
                (0x1 << FIFO_CTL_TXIM),
                (tx_input_mode << FIFO_CTL_TXIM));

        if (params_channels(params) == 1) {
            snd_platform_update_bits(platform, SUNXI_SPDIF_TXCFG,
                    (0x1 << TXCFG_SINGLE_MOD),
                    (0x1 << TXCFG_SINGLE_MOD));
        } else {
            snd_platform_update_bits(platform, SUNXI_SPDIF_TXCFG,
                    (0x1 << TXCFG_SINGLE_MOD),
                    (0x0 << TXCFG_SINGLE_MOD));
        }

        /* samplerate conversion */
        snd_platform_update_bits(platform, SUNXI_SPDIF_TXCH_STA0,
                (0xF << TXCHSTA0_SAMFREQ),
                (sample_freq_bit << TXCHSTA0_SAMFREQ));
        snd_platform_update_bits(platform, SUNXI_SPDIF_TXCH_STA1,
                (0xF << TXCHSTA1_ORISAMFREQ),
                (origin_freq_bit << TXCHSTA1_ORISAMFREQ));
        switch (reg_temp) {
        case    0:
            snd_platform_update_bits(platform, SUNXI_SPDIF_TXCH_STA1,
                    (0xF << TXCHSTA1_MAXWORDLEN),
                    (0x2 << TXCHSTA1_MAXWORDLEN));
            break;
        case    1:
            snd_platform_update_bits(platform, SUNXI_SPDIF_TXCH_STA1,
                    (0xF << TXCHSTA1_MAXWORDLEN),
                    (0xC << TXCHSTA1_MAXWORDLEN));
            break;
        case    2:
            snd_platform_update_bits(platform, SUNXI_SPDIF_TXCH_STA1,
                    (0xF << TXCHSTA1_MAXWORDLEN),
                    (0xB << TXCHSTA1_MAXWORDLEN));
            break;
        default:
            snd_err("sunxi spdif unexpection error\n");
            return -EINVAL;
        }
    } else {
        /*
         * FIXME, not sync as spec says, just test 16bit & 24bit,
         * using 3 working ok
         */
        snd_platform_update_bits(platform, SUNXI_SPDIF_FIFO_CTL,
                (0x3 << FIFO_CTL_RXOM),
                (rx_output_mode << FIFO_CTL_RXOM));
        snd_platform_update_bits(platform, SUNXI_SPDIF_RXCH_STA0,
                (0xF<<RXCHSTA0_SAMFREQ),
                (sample_freq_bit << RXCHSTA0_SAMFREQ));
        snd_platform_update_bits(platform, SUNXI_SPDIF_RXCH_STA1,
                (0xF<<RXCHSTA1_ORISAMFREQ),
                (origin_freq_bit << RXCHSTA1_ORISAMFREQ));

        switch (reg_temp) {
        case    0:
            snd_platform_update_bits(platform, SUNXI_SPDIF_RXCH_STA1,
                    (0xF << RXCHSTA1_MAXWORDLEN),
                    (0x2 << RXCHSTA1_MAXWORDLEN));
            break;
        case    1:
            snd_platform_update_bits(platform, SUNXI_SPDIF_RXCH_STA1,
                    (0xF << RXCHSTA1_MAXWORDLEN),
                    (0xC << RXCHSTA1_MAXWORDLEN));
            break;
        case    2:
            snd_platform_update_bits(platform, SUNXI_SPDIF_RXCH_STA1,
                    (0xF << RXCHSTA1_MAXWORDLEN),
                    (0xB << RXCHSTA1_MAXWORDLEN));
            break;
        default:
            snd_err("sunxi spdif unexpection error\n");
            return -EINVAL;
        }
    }

    return 0;
}

static int sunxi_spdif_set_sysclk(struct snd_dai *dai, int clk_id,
                        unsigned int freq, int dir)
{
    struct snd_platform *platform = dai->component;
    struct sunxi_spdif_info *sunxi_spdif = platform->private_data;

    snd_print("\n");
    if (hal_clk_set_rate(sunxi_spdif->pllclk, freq)) {
        snd_err("set pllclk %u failed\n", freq);
        return -EINVAL;
    }

    return 0;
}

static int sunxi_spdif_set_clkdiv(struct snd_dai *dai, int clk_id, int clk_div)
{
    struct snd_platform *platform = dai->component;
//  struct sunxi_spdif_info *sunxi_spdif = platform->private_data;
//  struct sunxi_spdif_param *param = &sunxi_spdif->param;

    snd_print("\n");
    /* fs = PLL/[(div+1)*64*2] */
    clk_div = clk_div >> 7;

    snd_platform_update_bits(platform, SUNXI_SPDIF_TXCFG,
            (0x1F << TXCFG_CLK_DIV_RATIO),
            ((clk_div - 1) << TXCFG_CLK_DIV_RATIO));

    return 0;
}

static int sunxi_spdif_startup(struct snd_pcm_substream *substream,
            struct snd_dai *dai)
{
    struct snd_platform *platform = dai->component;
    struct sunxi_spdif_info *sunxi_spdif = platform->private_data;

    snd_print("\n");
    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
        dai->playback_dma_data = &sunxi_spdif->playback_dma_param;
    } else {
        dai->capture_dma_data = &sunxi_spdif->capture_dma_param;
    }

    return 0;
}

static void sunxi_spdif_shutdown(struct snd_pcm_substream *substream,
            struct snd_dai *dai)
{
    snd_print("\n");
}

static int sunxi_spdif_trigger(struct snd_pcm_substream *substream,
                int cmd, struct snd_dai *dai)
{
    struct snd_platform *platform = dai->component;
    unsigned int ret;

    snd_print("\n");
    switch (cmd) {
    case    SNDRV_PCM_TRIGGER_START:
    case    SNDRV_PCM_TRIGGER_RESUME:
    case    SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
        if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
            sunxi_spdif_txctrl_enable(platform, true);
        } else {
            sunxi_spdif_rxctrl_enable(platform, true);
        }
        break;
    case    SNDRV_PCM_TRIGGER_STOP:
    case    SNDRV_PCM_TRIGGER_SUSPEND:
    case    SNDRV_PCM_TRIGGER_PAUSE_PUSH:
        if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
            sunxi_spdif_txctrl_enable(platform, false);
        } else {
            sunxi_spdif_rxctrl_enable(platform, false);
        }
        break;
    default:
        ret = -EINVAL;
        break;
    }

    return ret;
}

/*
 * Reset & Flush FIFO
 */
static int sunxi_spdif_prepare(struct snd_pcm_substream *substream,
            struct snd_dai *dai)
{
    struct snd_platform *platform = dai->component;
    unsigned int reg_val;

    snd_print("\n");
    snd_platform_update_bits(platform, SUNXI_SPDIF_CTL,
            (0x1 << CTL_GEN_EN), (0x0 << CTL_GEN_EN));

    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
        snd_platform_update_bits(platform, SUNXI_SPDIF_FIFO_CTL,
                (0x1 << FIFO_CTL_FTX), (0x1 << FIFO_CTL_FTX));
        snd_platform_write(platform, SUNXI_SPDIF_TXCNT, 0x0);
    } else {
        snd_platform_update_bits(platform, SUNXI_SPDIF_FIFO_CTL,
                (0x1 << FIFO_CTL_FRX), (0x1 << FIFO_CTL_FRX));
        snd_platform_write(platform, SUNXI_SPDIF_RXCNT, 0x0);
    }

    /* clear all interrupt status */
    reg_val = snd_platform_read(platform, SUNXI_SPDIF_INT_STA);
    snd_platform_write(platform, SUNXI_SPDIF_INT_STA, reg_val);

    /* need reset */
    snd_platform_update_bits(platform, SUNXI_SPDIF_CTL,
            (0x1 << CTL_RESET) | (0x1 << CTL_GEN_EN),
            (0x1 << CTL_RESET) | (0x1 << CTL_GEN_EN));
    return 0;
}

/* spdif module init status */
static int sunxi_spdif_dai_probe(struct snd_dai *dai)
{
    struct snd_platform *platform = dai->component;

    snd_print("\n");
    dai->playback_dma_data = 0;
    dai->capture_dma_data = 0;

    sunxi_spdif_init(platform);

    return 0;
}

static int sunxi_spdif_dai_remove(struct snd_dai *dai)
{
    snd_print("\n");
    return 0;
}

static struct snd_dai_ops sunxi_spdif_dai_ops = {
    .hw_params = sunxi_spdif_hw_params,
    .set_clkdiv = sunxi_spdif_set_clkdiv,
    .set_sysclk = sunxi_spdif_set_sysclk,
    .startup = sunxi_spdif_startup,
    .shutdown = sunxi_spdif_shutdown,
    .trigger = sunxi_spdif_trigger,
    .prepare = sunxi_spdif_prepare,
};

static struct snd_dai sunxi_spdif_dai = {
    .id     = 1,
    .name       = "sunxi-spdif-cpudai",
    .playback = {
        .stream_name    = "Playback",
        .channels_min   = 1,
        .channels_max   = 2,
        .rates      = SUNXI_SPDIF_RATES,
        .formats    = SNDRV_PCM_FMTBIT_S16_LE
                | SNDRV_PCM_FMTBIT_S24_LE
                | SNDRV_PCM_FMTBIT_S32_LE,
        .rate_min   = 8000,
        .rate_max   = 192000,
    },
    .capture = {
        .stream_name    = "Capture",
        .channels_min   = 2,
        .channels_max   = 2,
        .rates      = SUNXI_SPDIF_RATES,
        .formats    = SNDRV_PCM_FMTBIT_S16_LE
                | SNDRV_PCM_FMTBIT_S24_LE
                | SNDRV_PCM_FMTBIT_S32_LE,
        .rate_min   = 8000,
        .rate_max   = 192000,
    },
    .probe = sunxi_spdif_dai_probe,
    .remove = sunxi_spdif_dai_remove,
    .ops = &sunxi_spdif_dai_ops,
};

static int sunxi_spdif_clk_init(struct snd_platform *platform)
{
    struct sunxi_spdif_info *sunxi_spdif = platform->private_data;
    hal_reset_type_t reset_type = HAL_SUNXI_RESET;
    hal_clk_type_t clk_type = HAL_SUNXI_CCU;
    int ret;

    snd_print("\n");
    sunxi_spdif->pllclk = hal_clock_get(clk_type, SUNXI_SPDIF_CLK_PLL_AUDIO);
    sunxi_spdif->moduleclk = hal_clock_get(clk_type, SUNXI_SPDIF_CLK_SPDIF);
    sunxi_spdif->busclk = hal_clock_get(clk_type, SUNXI_SPDIF_CLK_BUS);
    sunxi_spdif->rstclk = hal_reset_control_get(reset_type, SUNXI_SPDIF_CLK_RST);
#ifdef CONFIG_SND_SUNXI_SPDIF_RX_IEC61937
    sunxi_spdif->pllclk1 = hal_clock_get(clk_type, SUNXI_SPDIF_CLK_PLL_AUDIO1);
    sunxi_spdif->pllclk1_div = hal_clock_get(clk_type, SUNXI_SPDIF_CLK_PLL_AUDIO1_DIV);
    sunxi_spdif->moduleclk_rx = hal_clock_get(clk_type, SUNXI_SPDIF_CLK_SPDIF_RX);
#endif

    ret = hal_clk_set_parent(sunxi_spdif->moduleclk, sunxi_spdif->pllclk);
    if (ret != HAL_CLK_STATUS_OK) {
        snd_err("sunxi_spdif clk_set_parent failed.\n");
        goto err_spdif_moduleclk_set_parent;
    }
#ifdef CONFIG_SND_SUNXI_SPDIF_RX_IEC61937
    ret = hal_clk_set_parent(sunxi_spdif->moduleclk_rx, sunxi_spdif->pllclk1_div);
    if (ret != HAL_CLK_STATUS_OK) {
        snd_err("sunxi_spdif clk_set_parent failed.\n");
        goto err_spdif_moduleclk_set_parent;
    }
#endif

    ret = hal_reset_control_deassert(sunxi_spdif->rstclk);
    if (ret != HAL_CLK_STATUS_OK) {
        snd_err("spdif clk_deassert rstclk failed.\n");
        goto err_spdif_pllclk_enable;
    }

    ret = hal_clock_enable(sunxi_spdif->busclk);
    if (ret != HAL_CLK_STATUS_OK) {
        snd_err("spdif clk_enable busclk failed.\n");
        goto err_spdif_pllclk_enable;
    }
    ret = hal_clock_enable(sunxi_spdif->pllclk);
    if (ret != HAL_CLK_STATUS_OK) {
        snd_err("spdif clk_enable pllclk failed.\n");
        goto err_spdif_pllclk_enable;
    }
    ret = hal_clock_enable(sunxi_spdif->moduleclk);
    if (ret != HAL_CLK_STATUS_OK) {
        snd_err("spdif clk_enable moduleclk failed.\n");
        goto err_spdif_moduleclk_enable;
    }
#ifdef CONFIG_SND_SUNXI_SPDIF_RX_IEC61937
    ret = hal_clock_enable(sunxi_spdif->pllclk1);
    if (ret != HAL_CLK_STATUS_OK) {
        snd_err("spdif clk_enable pllclk1 failed.\n");
        goto err_spdif_pllclk_enable;
    }
    ret = hal_clock_enable(sunxi_spdif->pllclk1_div);
    if (ret != HAL_CLK_STATUS_OK) {
        snd_err("spdif clk_enable pllclk1 div failed.\n");
        goto err_spdif_pllclk_enable;
    }
    ret = hal_clock_enable(sunxi_spdif->moduleclk_rx);
    if (ret != HAL_CLK_STATUS_OK) {
        snd_err("spdif clk_enable moduleclk rx failed.\n");
        goto err_spdif_moduleclk_enable;
    }
#endif

    return 0;

err_spdif_moduleclk_enable:
    hal_clock_disable(sunxi_spdif->pllclk);
err_spdif_pllclk_enable:
err_spdif_moduleclk_set_parent:
    snd_free(sunxi_spdif);
    return ret;
}

static void sunxi_spdif_gpio_init(bool enable)
{
    snd_print("\n");
    if (enable) {
        /* CLK */
//      hal_gpio_pinmux_set_function(g_spdif_gpio.clk.gpio,
//                  g_spdif_gpio.clk.mux);
        /* OUT */
        hal_gpio_pinmux_set_function(g_spdif_gpio.out.gpio,
                    g_spdif_gpio.out.mux);
        /* IN */
        hal_gpio_pinmux_set_function(g_spdif_gpio.in.gpio,
                    g_spdif_gpio.in.mux);
    } else {
        /* CLK */
//      hal_gpio_pinmux_set_function(g_spdif_gpio.clk.gpio,
//                  GPIO_MUXSEL_DISABLED);
        /* OUT */
        hal_gpio_pinmux_set_function(g_spdif_gpio.out.gpio,
                    GPIO_MUXSEL_DISABLED);
        /* IN */
        hal_gpio_pinmux_set_function(g_spdif_gpio.in.gpio,
                    GPIO_MUXSEL_DISABLED);
    }
}

static int sunxi_spdif_platform_probe(struct snd_platform *platform)
{
    struct sunxi_spdif_info *sunxi_spdif;

    snd_print("\n");
    sunxi_spdif = snd_malloc(sizeof(struct sunxi_spdif_info));
    if (!sunxi_spdif) {
        snd_err("no memory\n");
        return -ENOMEM;
    }
    platform->private_data = (void *)sunxi_spdif;
    platform->cpu_dai->component = platform;

    /* mem base */
    platform->mem_base = (void *)SUNXI_SPDIF_MEMBASE;

    /* clk */
    sunxi_spdif_clk_init(platform);

    /* pinctrl */
    sunxi_spdif_gpio_init(true);

    /* dma config */
    sunxi_spdif->playback_dma_param.dst_maxburst = 8;
    sunxi_spdif->playback_dma_param.src_maxburst = 8;
    sunxi_spdif->playback_dma_param.dma_addr =
            (dma_addr_t)platform->mem_base + SUNXI_SPDIF_TXFIFO;
    sunxi_spdif->playback_dma_param.dma_drq_type_num = DRQDST_SPDIF;

    sunxi_spdif->capture_dma_param.src_maxburst = 8;
    sunxi_spdif->capture_dma_param.dst_maxburst = 8;
    sunxi_spdif->capture_dma_param.dma_addr =
            (dma_addr_t)platform->mem_base + SUNXI_SPDIF_RXFIFO;
    sunxi_spdif->capture_dma_param.dma_drq_type_num = DRQSRC_SPDIF;

    return 0;
}

static int sunxi_spdif_platform_remove(struct snd_platform *platform)
{
    struct sunxi_spdif_info *sunxi_spdif;

    snd_print("\n");
    sunxi_spdif = platform->private_data;
    if (!sunxi_spdif)
        return 0;

    hal_clock_disable(sunxi_spdif->busclk);
    hal_clock_disable(sunxi_spdif->moduleclk);
    hal_clock_disable(sunxi_spdif->pllclk);
    hal_clock_put(sunxi_spdif->busclk);
    hal_clock_put(sunxi_spdif->moduleclk);
    hal_clock_put(sunxi_spdif->pllclk);
#ifdef CONFIG_SND_SUNXI_SPDIF_RX_IEC61937
    hal_clock_disable(sunxi_spdif->moduleclk_rx);
    hal_clock_disable(sunxi_spdif->pllclk1_div);
    hal_clock_disable(sunxi_spdif->pllclk1);
    hal_clock_put(sunxi_spdif->moduleclk_rx);
    hal_clock_put(sunxi_spdif->pllclk1_div);
    hal_clock_put(sunxi_spdif->pllclk1);
#endif
    hal_reset_control_assert(sunxi_spdif->rstclk);
    hal_reset_control_put(sunxi_spdif->rstclk);

    sunxi_spdif_gpio_init(false);

    snd_free(sunxi_spdif);
    platform->private_data = NULL;
    return 0;
}

int snd_platform_spdif_register(struct snd_platform *platform, int unused)
{
    int ret;

    snd_print("\n");
    platform->name = snd_malloc(SPDIF_NAME_LEN);
    if (!platform->name) {
        snd_err("no memory\n");
        return -ENOMEM;
    }
    snprintf(platform->name, SPDIF_NAME_LEN, "spdif-cpudai");
    platform->ops = &sunxi_pcm_ops;
    platform->pcm_new = sunxi_pcm_new;
    platform->pcm_free = sunxi_pcm_free;

    platform->cpu_dai = snd_malloc(sizeof(struct snd_dai));
    if (!platform->cpu_dai) {
        snd_err("cpu_dai malloc failed.\n");
        ret = -ENOMEM;
        goto err_cpu_dai_malloc;
    }
    memcpy(platform->cpu_dai, &sunxi_spdif_dai, sizeof(struct snd_dai));

    platform->probe = sunxi_spdif_platform_probe;
    platform->remove = sunxi_spdif_platform_remove;

    platform->num_controls = ARRAY_SIZE(sunxi_spdif_controls);
    platform->controls = snd_malloc(sizeof(struct snd_kcontrol) * platform->num_controls);
    if (!platform->controls) {
        snd_err("controls malloc failed.\n");
        ret = -ENOMEM;
        goto err_control_malloc;
    }
    memcpy(platform->controls, sunxi_spdif_controls,
            sizeof(struct snd_kcontrol) * platform->num_controls);

    return 0;

err_control_malloc:
    snd_free(platform->cpu_dai);
err_cpu_dai_malloc:
    snd_free(platform->name);
    platform->name = NULL;
    return ret;
}

#ifdef SUNXI_SPDIF_DEBUG_REG
#define REG_LABEL(constant)     {#constant, constant}
#define REG_LABEL_END           {NULL, 0}

static struct spdif_label {
    const char *name;
    const unsigned int address;
    /*int value;*/
} reg_labels[] = {
    REG_LABEL(SUNXI_SPDIF_CTL),
    REG_LABEL(SUNXI_SPDIF_TXCFG),
    REG_LABEL(SUNXI_SPDIF_RXCFG),
    REG_LABEL(SUNXI_SPDIF_INT_STA),
    REG_LABEL(SUNXI_SPDIF_RXFIFO),
    REG_LABEL(SUNXI_SPDIF_FIFO_CTL),
    REG_LABEL(SUNXI_SPDIF_FIFO_STA),
    REG_LABEL(SUNXI_SPDIF_INT),
    REG_LABEL(SUNXI_SPDIF_TXFIFO),
    REG_LABEL(SUNXI_SPDIF_TXCNT),
    REG_LABEL(SUNXI_SPDIF_RXCNT),
    REG_LABEL(SUNXI_SPDIF_TXCH_STA0),
    REG_LABEL(SUNXI_SPDIF_TXCH_STA1),
    REG_LABEL(SUNXI_SPDIF_RXCH_STA0),
    REG_LABEL(SUNXI_SPDIF_RXCH_STA1),
#ifdef CONFIG_SND_SUNXI_SPDIF_RX_IEC61937
    REG_LABEL(SUNXI_SPDIF_EXP_CTL),
    REG_LABEL(SUNXI_SPDIF_EXP_ISTA),
    REG_LABEL(SUNXI_SPDIF_EXP_INFO0),
    REG_LABEL(SUNXI_SPDIF_EXP_INFO1),
    REG_LABEL(SUNXI_SPDIF_EXP_DBG0),
    REG_LABEL(SUNXI_SPDIF_EXP_DBG1),
    REG_LABEL(SUNXI_SPDIF_EXP_VER),
#endif
    REG_LABEL_END,
};

/* for debug */
#include <console.h>
int cmd_spdif_dump(void)
{
    int spdif_num = 0;
    void *membase;
    int i = 0;

    membase = (void *)SUNXI_SPDIF_MEMBASE;

    while (reg_labels[i].name != NULL) {
        printf("%-20s[0x%03x]: 0x%-10x\n",
            reg_labels[i].name,
            reg_labels[i].address,
            snd_readl(membase + reg_labels[i].address));
        i++;
    }
}
FINSH_FUNCTION_EXPORT_CMD(cmd_spdif_dump, spdif, spdif dump reg);
#endif /* SUNXI_SPDIF_DEBUG_REG */
