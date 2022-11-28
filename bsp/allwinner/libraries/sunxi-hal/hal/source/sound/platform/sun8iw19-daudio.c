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
#include <log.h>
#include <sound/snd_core.h>
#include <sound/snd_pcm.h>
#include <sound/snd_dma.h>
#include <sound/dma_wrap.h>
#include <hal_dma.h>

#include "sunxi-pcm.h"
#include "sunxi-daudio.h"
#include "../codecs/sun8iw19-codec.h"

static void sunxi_daudio_txctrl_enable(struct snd_platform *platform, bool enable)
{
    if (enable) {
        snd_platform_update_bits(platform, SUNXI_DAUDIO_CTL,
                    (1 << SDO0_EN) | (1 << CTL_TXEN),
                    (1 << SDO0_EN) | (1 << CTL_TXEN));
        snd_platform_update_bits(platform, SUNXI_DAUDIO_INTCTL,
                    (1 << TXDRQEN), (1 << TXDRQEN));
    } else {
        snd_platform_update_bits(platform, SUNXI_DAUDIO_INTCTL,
                    (1 << TXDRQEN), (0 << TXDRQEN));
        snd_platform_update_bits(platform, SUNXI_DAUDIO_CTL,
                    (1 << SDO0_EN) | (1 << CTL_TXEN),
                    (0 << SDO0_EN) | (0 << CTL_TXEN));
    }
}

static void sunxi_daudio_rxctrl_enable(struct snd_platform *platform, bool enable)
{
    if (enable) {
        snd_platform_update_bits(platform, SUNXI_DAUDIO_CTL,
                (1 << CTL_RXEN), (1 << CTL_RXEN));
        snd_platform_update_bits(platform, SUNXI_DAUDIO_INTCTL,
                (1 << RXDRQEN), (1 << RXDRQEN));
    } else {
        snd_platform_update_bits(platform, SUNXI_DAUDIO_INTCTL,
                (1 << RXDRQEN), (0 << RXDRQEN));
        snd_platform_update_bits(platform, SUNXI_DAUDIO_CTL,
                (1 << CTL_RXEN), (0 << CTL_RXEN));
    }
}

static int sunxi_daudio_global_enable(struct snd_platform *platform, bool enable)
{
    struct sunxi_daudio_info *sunxi_daudio = platform->private_data;
    /* uint32_t sr_level = 0; */
//      uint32_t __cpsr;

    /* sr_level = freert_write_lock_irqsave(&sunxi_daudio->gen_lock); */
//        __cpsr = hal_spin_lock_irqsave();
    if (enable) {
        if (sunxi_daudio->global_enable++ == 0)
            snd_platform_update_bits(platform,
                SUNXI_DAUDIO_CTL,
                (1<<GLOBAL_EN), (1<<GLOBAL_EN));
    } else {
        if (--sunxi_daudio->global_enable == 0)
            snd_platform_update_bits(platform,
                SUNXI_DAUDIO_CTL,
                (1<<GLOBAL_EN), (0<<GLOBAL_EN));
    }
    /* freert_write_unlock_irqsave(&sunxi_daudio->gen_lock, sr_level); */
//        hal_spin_unlock_irqrestore(__cpsr);

    return 0;
}

static int sunxi_daudio_startup(struct snd_pcm_substream *substream,
                struct snd_dai *dai)
{
    struct snd_platform *platform = dai->component;
    struct sunxi_daudio_info *sunxi_daudio = platform->private_data;
    struct sunxi_daudio_param *param = &sunxi_daudio->param;

    snd_print("\n");
    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
        dai->playback_dma_data = &sunxi_daudio->playback_dma_param;
    else
        dai->capture_dma_data = &sunxi_daudio->capture_dma_param;

    return 0;
}

static int sunxi_daudio_hw_params(struct snd_pcm_substream *substream,
        struct snd_pcm_hw_params *params, struct snd_dai *dai)
{
    struct snd_platform *platform = dai->component;
    struct sunxi_daudio_info *sunxi_daudio = platform->private_data;
    struct sunxi_daudio_param *param = &sunxi_daudio->param;
    int ret = 0;

    snd_print("\n");

    /* set cpu dai fmt */
    ret = snd_soc_dai_set_fmt(dai, param->audio_format
            | (param->signal_inversion << SND_SOC_DAIFMT_SIG_SHIFT)
            | (param->daudio_master << SND_SOC_DAIFMT_MASTER_SHIFT));
    if (ret < 0) {
        snd_err("cpu dai set fmt failed.\n");
        return -EINVAL;
    }

    switch (params_format(params)) {
    case SND_PCM_FORMAT_S16_LE:
        snd_platform_update_bits(platform,
            SUNXI_DAUDIO_FMT0,
            (SUNXI_DAUDIO_SR_MASK<<DAUDIO_SAMPLE_RESOLUTION),
            (SUNXI_DAUDIO_SR_16BIT<<DAUDIO_SAMPLE_RESOLUTION));
        if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
            snd_platform_update_bits(platform,
                SUNXI_DAUDIO_FIFOCTL,
                (SUNXI_DAUDIO_TXIM_MASK<<TXIM),
                (SUNXI_DAUDIO_TXIM_VALID_LSB<<TXIM));
        else
            snd_platform_update_bits(platform,
                SUNXI_DAUDIO_FIFOCTL,
                (SUNXI_DAUDIO_RXOM_MASK<<RXOM),
                (SUNXI_DAUDIO_RXOM_EXPH<<RXOM));
        break;
    case SND_PCM_FORMAT_S24_LE:
        snd_platform_update_bits(platform, SUNXI_DAUDIO_FMT0,
                (SUNXI_DAUDIO_SR_MASK<<DAUDIO_SAMPLE_RESOLUTION),
                (SUNXI_DAUDIO_SR_24BIT<<DAUDIO_SAMPLE_RESOLUTION));
        if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
            snd_platform_update_bits(platform,
                    SUNXI_DAUDIO_FIFOCTL,
                    (SUNXI_DAUDIO_TXIM_MASK<<TXIM),
                    (SUNXI_DAUDIO_TXIM_VALID_LSB<<TXIM));
        else
            snd_platform_update_bits(platform,
                    SUNXI_DAUDIO_FIFOCTL,
                    (SUNXI_DAUDIO_RXOM_MASK<<RXOM),
                    (SUNXI_DAUDIO_RXOM_EXP0<<RXOM));
        break;
    case SND_PCM_FORMAT_S32_LE:
        snd_platform_update_bits(platform, SUNXI_DAUDIO_FMT0,
                (SUNXI_DAUDIO_SR_MASK<<DAUDIO_SAMPLE_RESOLUTION),
                (SUNXI_DAUDIO_SR_32BIT<<DAUDIO_SAMPLE_RESOLUTION));
        if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
            snd_platform_update_bits(platform,
                    SUNXI_DAUDIO_FIFOCTL,
                    (SUNXI_DAUDIO_TXIM_MASK<<TXIM),
                    (SUNXI_DAUDIO_TXIM_VALID_LSB<<TXIM));
        else
            snd_platform_update_bits(platform,
                    SUNXI_DAUDIO_FIFOCTL,
                    (SUNXI_DAUDIO_RXOM_MASK<<RXOM),
                    (SUNXI_DAUDIO_RXOM_EXPH<<RXOM));
        break;
    default:
        snd_err("unrecognized format\n");
        return -EINVAL;
    }

    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
        snd_platform_update_bits(platform, SUNXI_DAUDIO_CHCFG,
                (SUNXI_DAUDIO_TX_SLOT_MASK<<TX_SLOT_NUM),
                ((params_channels(params)-1)<<TX_SLOT_NUM));
        snd_platform_write(platform,
            SUNXI_DAUDIO_TX0CHMAP0, SUNXI_DEFAULT_CHMAP0);
        snd_platform_write(platform,
            SUNXI_DAUDIO_TX0CHMAP1, SUNXI_DEFAULT_CHMAP1);
        snd_platform_update_bits(platform,
            SUNXI_DAUDIO_TX0CHSEL,
            (SUNXI_DAUDIO_TX_CHSEL_MASK<<TX_CHSEL),
            ((params_channels(params)-1)<<TX_CHSEL));
        snd_platform_update_bits(platform,
            SUNXI_DAUDIO_TX0CHSEL,
            (SUNXI_DAUDIO_TX_CHEN_MASK<<TX_CHEN),
            ((1<<params_channels(params))-1)<<TX_CHEN);
    } else {
        unsigned int SUNXI_DAUDIO_RXCHMAPX = 0;
        int index = 0;

        for (index = 0; index < 16; index++) {
            if (index >= 12)
                SUNXI_DAUDIO_RXCHMAPX = SUNXI_DAUDIO_RXCHMAP0;
            else if (index >= 8)
                SUNXI_DAUDIO_RXCHMAPX = SUNXI_DAUDIO_RXCHMAP1;
            else if (index >= 4)
                SUNXI_DAUDIO_RXCHMAPX = SUNXI_DAUDIO_RXCHMAP2;
            else
                SUNXI_DAUDIO_RXCHMAPX = SUNXI_DAUDIO_RXCHMAP3;
            snd_platform_update_bits(platform,
                SUNXI_DAUDIO_RXCHMAPX,
                DAUDIO_RXCHMAP(index),
                DAUDIO_RXCH_DEF_MAP(index));
        }
        snd_platform_update_bits(platform, SUNXI_DAUDIO_CHCFG,
                (SUNXI_DAUDIO_RX_SLOT_MASK<<RX_SLOT_NUM),
                ((params_channels(params)-1)<<RX_SLOT_NUM));
        snd_platform_update_bits(platform, SUNXI_DAUDIO_RXCHSEL,
                (SUNXI_DAUDIO_RX_CHSEL_MASK<<RX_CHSEL),
                ((params_channels(params)-1)<<RX_CHSEL));
    }

    return 0;
}

static int sunxi_daudio_set_sysclk(struct snd_dai *dai,
                int clk_id, unsigned int freq, int dir)
{
    struct snd_platform *platform = dai->component;
    struct sunxi_daudio_info *sunxi_daudio = platform->private_data;
    struct sunxi_daudio_param *param = &sunxi_daudio->param;

    if (hal_clk_set_rate(sunxi_daudio->pllclk, freq)) {
        snd_err("set pllclk rate %u failed\n", freq);
        return -EINVAL;
    }

    return 0;
}

static int sunxi_daudio_set_clkdiv(struct snd_dai *dai,
                int clk_id, int clk_div)
{
    struct snd_platform *platform = dai->component;
    struct sunxi_daudio_info *sunxi_daudio = platform->private_data;
    struct sunxi_daudio_param *param = &sunxi_daudio->param;
    unsigned int bclk_div, div_ratio;

    snd_print("\n");
    if (param->tdm_config)
        /* I2S/TDM two channel mode */
        div_ratio = clk_div/(2 * param->pcm_lrck_period);
    else
        /* PCM mode */
        div_ratio = clk_div / param->pcm_lrck_period;

    switch (div_ratio) {
    case    1:
        bclk_div = SUNXI_DAUDIO_BCLK_DIV_1;
        break;
    case    2:
        bclk_div = SUNXI_DAUDIO_BCLK_DIV_2;
        break;
    case    4:
        bclk_div = SUNXI_DAUDIO_BCLK_DIV_3;
        break;
    case    6:
        bclk_div = SUNXI_DAUDIO_BCLK_DIV_4;
        break;
    case    8:
        bclk_div = SUNXI_DAUDIO_BCLK_DIV_5;
        break;
    case    12:
        bclk_div = SUNXI_DAUDIO_BCLK_DIV_6;
        break;
    case    16:
        bclk_div = SUNXI_DAUDIO_BCLK_DIV_7;
        break;
    case    24:
        bclk_div = SUNXI_DAUDIO_BCLK_DIV_8;
        break;
    case    32:
        bclk_div = SUNXI_DAUDIO_BCLK_DIV_9;
        break;
    case    48:
        bclk_div = SUNXI_DAUDIO_BCLK_DIV_10;
        break;
    case    64:
        bclk_div = SUNXI_DAUDIO_BCLK_DIV_11;
        break;
    case    96:
        bclk_div = SUNXI_DAUDIO_BCLK_DIV_12;
        break;
    case    128:
        bclk_div = SUNXI_DAUDIO_BCLK_DIV_13;
        break;
    case    176:
        bclk_div = SUNXI_DAUDIO_BCLK_DIV_14;
        break;
    case    192:
        bclk_div = SUNXI_DAUDIO_BCLK_DIV_15;
        break;
    default:
        snd_err("unsupport clk_div\n");
        return -EINVAL;
    }
    /* setting bclk to driver external codec bit clk */
    snd_platform_update_bits(platform, SUNXI_DAUDIO_CLKDIV,
            (SUNXI_DAUDIO_BCLK_DIV_MASK<<BCLK_DIV),
            (bclk_div<<BCLK_DIV));

    return 0;
}

static int sunxi_daudio_init_fmt(struct snd_platform *platform, unsigned int fmt)
{
    unsigned int offset, mode;
    unsigned int lrck_polarity, brck_polarity;

    switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
    case    SND_SOC_DAIFMT_CBM_CFM:
        snd_platform_update_bits(platform, SUNXI_DAUDIO_CTL,
                (SUNXI_DAUDIO_LRCK_OUT_MASK<<LRCK_OUT),
                (SUNXI_DAUDIO_LRCK_OUT_DISABLE<<LRCK_OUT));
        break;
    case    SND_SOC_DAIFMT_CBS_CFS:
        snd_platform_update_bits(platform, SUNXI_DAUDIO_CTL,
                (SUNXI_DAUDIO_LRCK_OUT_MASK<<LRCK_OUT),
                (SUNXI_DAUDIO_LRCK_OUT_ENABLE<<LRCK_OUT));
        break;
    default:
        snd_err("unknown maser/slave format\n");
        return -EINVAL;
    }

    switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
    case    SND_SOC_DAIFMT_I2S:
        offset = SUNXI_DAUDIO_TX_OFFSET_1;
        mode = SUNXI_DAUDIO_MODE_CTL_I2S;
        break;
    case    SND_SOC_DAIFMT_RIGHT_J:
        offset = SUNXI_DAUDIO_TX_OFFSET_0;
        mode = SUNXI_DAUDIO_MODE_CTL_RIGHT;
        break;
    case    SND_SOC_DAIFMT_LEFT_J:
        offset = SUNXI_DAUDIO_TX_OFFSET_0;
        mode = SUNXI_DAUDIO_MODE_CTL_LEFT;
        break;
    case    SND_SOC_DAIFMT_DSP_A:
        offset = SUNXI_DAUDIO_TX_OFFSET_1;
        mode = SUNXI_DAUDIO_MODE_CTL_PCM;
        break;
    case    SND_SOC_DAIFMT_DSP_B:
        offset = SUNXI_DAUDIO_TX_OFFSET_0;
        mode = SUNXI_DAUDIO_MODE_CTL_PCM;
        break;
    default:
        snd_err("format setting failed\n");
        return -EINVAL;
    }

    snd_platform_update_bits(platform, SUNXI_DAUDIO_CTL,
            (SUNXI_DAUDIO_MODE_CTL_MASK<<MODE_SEL),
            (mode<<MODE_SEL));
    snd_platform_update_bits(platform, SUNXI_DAUDIO_TX0CHSEL,
            (SUNXI_DAUDIO_TX_OFFSET_MASK<<TX_OFFSET),
            (offset<<TX_OFFSET));
    snd_platform_update_bits(platform, SUNXI_DAUDIO_RXCHSEL,
            (SUNXI_DAUDIO_RX_OFFSET_MASK<<RX_OFFSET),
            (offset<<RX_OFFSET));

    switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
    case SND_SOC_DAIFMT_NB_NF:
        lrck_polarity = SUNXI_DAUDIO_LRCK_POLARITY_NOR;
        brck_polarity = SUNXI_DAUDIO_BCLK_POLARITY_NOR;
        break;
    case SND_SOC_DAIFMT_NB_IF:
        lrck_polarity = SUNXI_DAUDIO_LRCK_POLARITY_INV;
        brck_polarity = SUNXI_DAUDIO_BCLK_POLARITY_NOR;
        break;
    case SND_SOC_DAIFMT_IB_NF:
        lrck_polarity = SUNXI_DAUDIO_LRCK_POLARITY_NOR;
        brck_polarity = SUNXI_DAUDIO_BCLK_POLARITY_INV;
        break;
    case SND_SOC_DAIFMT_IB_IF:
        lrck_polarity = SUNXI_DAUDIO_LRCK_POLARITY_INV;
        brck_polarity = SUNXI_DAUDIO_BCLK_POLARITY_INV;
        break;
    default:
        snd_err("invert clk setting failed\n");
        return -EINVAL;
    }

    snd_platform_update_bits(platform, SUNXI_DAUDIO_FMT0,
            (1<<LRCK_POLARITY), (lrck_polarity<<LRCK_POLARITY));
    snd_platform_update_bits(platform, SUNXI_DAUDIO_FMT0,
            (1<<BRCK_POLARITY), (brck_polarity<<BRCK_POLARITY));

    return 0;
}

static int sunxi_daudio_set_fmt(struct snd_dai *dai, unsigned int fmt)
{
    struct snd_platform *platform = dai->component;
    struct sunxi_daudio_info *sunxi_daudio = platform->private_data;
    struct sunxi_daudio_param *param = &sunxi_daudio->param;

    sunxi_daudio_init_fmt(platform, fmt);

    return 0;
}

static int sunxi_daudio_prepare(struct snd_pcm_substream *substream,
                struct snd_dai *dai)
{
    struct snd_platform *platform = dai->component;
    struct sunxi_daudio_info *sunxi_daudio = platform->private_data;
    struct sunxi_daudio_param *param = &sunxi_daudio->param;
    unsigned int i;

    snd_print("\n");
    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
        for (i = 0 ; i < SUNXI_DAUDIO_FTX_TIMES ; i++) {
            snd_platform_update_bits(platform,
                SUNXI_DAUDIO_FIFOCTL,
                (1 << FIFO_CTL_FTX), (1 << FIFO_CTL_FTX));
            hal_usleep(1000);
        }
        snd_platform_write(platform, SUNXI_DAUDIO_TXCNT, 0);
        if (sunxi_daudio->hub_mode && !sunxi_daudio->playback_en) {
            snd_platform_update_bits(platform,
                    SUNXI_DAUDIO_CTL,
                    (1 << SDO0_EN) | (1 << CTL_TXEN),
                    (1 << SDO0_EN) | (1 << CTL_TXEN));
            sunxi_daudio_global_enable(platform, true);
            sunxi_daudio->playback_en = 1;
        }
    } else {
        snd_platform_update_bits(platform, SUNXI_DAUDIO_FIFOCTL,
                (1<<FIFO_CTL_FRX), (1<<FIFO_CTL_FRX));
        snd_platform_write(platform, SUNXI_DAUDIO_RXCNT, 0);
    }

    return 0;
}

/* for adc and i2s rx sync */
#ifdef SUNXI_ADC_DAUDIO_SYNC
struct snd_platform *adc_daudio_sync_platform;

void sunxi_daudio_rx_drq_enable(bool enable)
{
    sunxi_daudio_rxctrl_enable(adc_daudio_sync_platform, enable);
    sunxi_daudio_global_enable(adc_daudio_sync_platform, enable);
}
#endif

static int sunxi_daudio_trigger(struct snd_pcm_substream *substream,
                int cmd, struct snd_dai *dai)
{
    struct snd_platform *platform = dai->component;
    struct sunxi_daudio_info *sunxi_daudio = platform->private_data;
    struct sunxi_daudio_param *param = &sunxi_daudio->param;
#ifdef SUNXI_ADC_DAUDIO_SYNC
    unsigned int sync_mode = 0;
    int adc_sync_flag = 0;
    uint32_t __cpsr;
#endif

    snd_print("\n");
    switch (cmd) {
    case SNDRV_PCM_TRIGGER_START:
    case SNDRV_PCM_TRIGGER_RESUME:
    case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
        if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
            sunxi_daudio_txctrl_enable(platform, true);
            if (!sunxi_daudio->playback_en) {
                /* Global enable I2S/TDM module */
                sunxi_daudio_global_enable(platform, true);
                sunxi_daudio->playback_en = 1;
            }
        } else {
#ifdef SUNXI_ADC_DAUDIO_SYNC
            if (sunxi_daudio->param.tdm_num == 0) {
                __cpsr = hal_spin_lock_irqsave();
                sync_mode = sunxi_codec_get_pcm_trigger_substream_mode();
                if (sync_mode) {
                    adc_sync_flag = sunxi_codec_get_pcm_adc_sync_flag();
                    adc_sync_flag |= (0x1 << ADC_I2S_SYNC);
                    if (adc_sync_flag & (0x1 << ADC_I2S_RUNNING)) {
                        sunxi_daudio_rx_drq_enable(true);
                    } else if ((adc_sync_flag & (0x1 << ADC_CODEC_SYNC)) &&
                        (adc_sync_flag & (0x1 << ADC_I2S_SYNC))) {
                        adc_sync_flag |= (0x1 << ADC_I2S_RUNNING);
                        sunxi_cpudai_adc_drq_enable(true);
                        sunxi_daudio_rx_drq_enable(true);
                    }
                    sunxi_codec_set_pcm_adc_sync_flag(adc_sync_flag);
                } else {
                    sunxi_daudio_rx_drq_enable(true);
                }
                hal_spin_unlock_irqrestore(__cpsr);
            } else
#endif
            {
                sunxi_daudio_rxctrl_enable(platform, true);
                /* Global enable I2S/TDM module */
                sunxi_daudio_global_enable(platform, true);
            }
        }
        break;
    case SNDRV_PCM_TRIGGER_STOP:
    case SNDRV_PCM_TRIGGER_SUSPEND:
    case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
        if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
            sunxi_daudio_txctrl_enable(platform, false);
            if (sunxi_daudio->playback_en) {
                /* Global enable I2S/TDM module */
                sunxi_daudio_global_enable(platform, false);
                sunxi_daudio->playback_en = 0;
            }
        } else {
#ifdef SUNXI_ADC_DAUDIO_SYNC
            if (sunxi_daudio->param.tdm_num == 0) {
                __cpsr = hal_spin_lock_irqsave();
                adc_sync_flag = sunxi_codec_get_pcm_adc_sync_flag();
                adc_sync_flag &= ~(0x1 << ADC_I2S_SYNC);
                if (!((adc_sync_flag >> ADC_CODEC_SYNC) & 0x1) &&
                    (!((adc_sync_flag >> ADC_I2S_SYNC) & 0x1))) {
                    adc_sync_flag &= ~(0x1 << ADC_I2S_RUNNING);
                }
                sunxi_codec_set_pcm_adc_sync_flag(adc_sync_flag);
                sunxi_daudio_rx_drq_enable(false);
                hal_spin_unlock_irqrestore(__cpsr);
            } else
#endif
            {
                sunxi_daudio_rxctrl_enable(platform, false);
                /* Global enable I2S/TDM module */
                sunxi_daudio_global_enable(platform, false);
            }
        }
        break;
    default:
        return -EINVAL;
    }

    return 0;
}

static void sunxi_daudio_shutdown(struct snd_pcm_substream *substream,
                struct snd_dai *dai)
{
    struct snd_platform *platform = dai->component;
    struct sunxi_daudio_info *sunxi_daudio = platform->private_data;
    struct sunxi_daudio_param *param = &sunxi_daudio->param;

    snd_print("\n");
    if ((substream->stream == SNDRV_PCM_STREAM_PLAYBACK) &&
        (sunxi_daudio->hub_mode)) {
        snd_platform_update_bits(platform,
                SUNXI_DAUDIO_CTL,
                (1 << SDO0_EN) | (1 << CTL_TXEN),
                (0 << SDO0_EN) | (0 << CTL_TXEN));
        if (sunxi_daudio->playback_en) {
            sunxi_daudio_global_enable(platform, false);
            sunxi_daudio->playback_en = 0;
        }
        return;
    }
}

static struct snd_dai_ops sunxi_daudio_dai_ops = {
    .startup = sunxi_daudio_startup,
    .set_sysclk = sunxi_daudio_set_sysclk,
    .set_clkdiv = sunxi_daudio_set_clkdiv,
    .set_fmt = sunxi_daudio_set_fmt,
    .hw_params = sunxi_daudio_hw_params,
    .prepare = sunxi_daudio_prepare,
    .trigger = sunxi_daudio_trigger,
    .shutdown = sunxi_daudio_shutdown,
};

static int sunxi_daudio_mclk_setting(struct snd_platform *platform)
{
    struct sunxi_daudio_info *sunxi_daudio = platform->private_data;
    struct sunxi_daudio_param *param = &sunxi_daudio->param;
    uint16_t mclk_div;

    if (!param->mclk_div) {
        snd_platform_update_bits(platform, SUNXI_DAUDIO_CLKDIV,
                    (1 << MCLKOUT_EN), (0 << MCLKOUT_EN));
        return 0;
    }

    switch (param->mclk_div) {
    case 1:
        mclk_div = SUNXI_DAUDIO_MCLK_DIV_1;
        break;
    case 2:
        mclk_div = SUNXI_DAUDIO_MCLK_DIV_2;
        break;
    case 4:
        mclk_div = SUNXI_DAUDIO_MCLK_DIV_3;
        break;
    case 6:
        mclk_div = SUNXI_DAUDIO_MCLK_DIV_4;
        break;
    case 8:
        mclk_div = SUNXI_DAUDIO_MCLK_DIV_5;
        break;
    case 12:
        mclk_div = SUNXI_DAUDIO_MCLK_DIV_6;
        break;
    case 16:
        mclk_div = SUNXI_DAUDIO_MCLK_DIV_7;
        break;
    case 24:
        mclk_div = SUNXI_DAUDIO_MCLK_DIV_8;
        break;
    case 32:
        mclk_div = SUNXI_DAUDIO_MCLK_DIV_9;
        break;
    case    48:
        mclk_div = SUNXI_DAUDIO_MCLK_DIV_10;
        break;
    case    64:
        mclk_div = SUNXI_DAUDIO_MCLK_DIV_11;
        break;
    case    96:
        mclk_div = SUNXI_DAUDIO_MCLK_DIV_12;
        break;
    case    128:
        mclk_div = SUNXI_DAUDIO_MCLK_DIV_13;
        break;
    case    176:
        mclk_div = SUNXI_DAUDIO_MCLK_DIV_14;
        break;
    case    192:
        mclk_div = SUNXI_DAUDIO_MCLK_DIV_15;
        break;
    default:
        snd_err("unsupport  mclk_div\n");
        return -EINVAL;
    }

    snd_platform_update_bits(platform, SUNXI_DAUDIO_CLKDIV,
            (SUNXI_DAUDIO_MCLK_DIV_MASK<<MCLK_DIV),
            (mclk_div<<MCLK_DIV));
    snd_platform_update_bits(platform, SUNXI_DAUDIO_CLKDIV,
                (1<<MCLKOUT_EN), (1<<MCLKOUT_EN));

    return 0;
}

static int sunxi_daudio_init(struct snd_platform *platform)
{
    struct sunxi_daudio_info *sunxi_daudio = platform->private_data;
    struct sunxi_daudio_param *param = &sunxi_daudio->param;

    snd_platform_update_bits(platform, SUNXI_DAUDIO_FMT0,
                (1 << LRCK_WIDTH),
                (param->frametype << LRCK_WIDTH));
    snd_platform_update_bits(platform, SUNXI_DAUDIO_FMT0,
                (SUNXI_DAUDIO_LRCK_PERIOD_MASK) << LRCK_PERIOD,
                ((param->pcm_lrck_period - 1) << LRCK_PERIOD));
    snd_platform_update_bits(platform, SUNXI_DAUDIO_FMT0,
                (SUNXI_DAUDIO_SLOT_WIDTH_MASK) << SLOT_WIDTH,
                (((param->slot_width_select >> 2) - 1) << SLOT_WIDTH));

    snd_platform_update_bits(platform, SUNXI_DAUDIO_FMT1,
                (0x1 << TX_MLS),
                (param->msb_lsb_first << TX_MLS));
    snd_platform_update_bits(platform, SUNXI_DAUDIO_FMT1,
                (0x1 << RX_MLS),
                (param->msb_lsb_first << RX_MLS));
    snd_platform_update_bits(platform, SUNXI_DAUDIO_FMT1,
                (0x3 << SEXT),
                (param->sign_extend << SEXT));
    snd_platform_update_bits(platform, SUNXI_DAUDIO_FMT1,
                (0x3 << TX_PDM),
                (param->tx_data_mode << TX_PDM));
    snd_platform_update_bits(platform, SUNXI_DAUDIO_FMT1,
                (0x3 << RX_PDM),
                (param->rx_data_mode << RX_PDM));

    return sunxi_daudio_mclk_setting(platform);
}

static int sunxi_daudio_dai_probe(struct snd_dai *dai)
{
    struct snd_platform *platform = dai->component;

    snd_print("\n");
    dai->playback_dma_data = 0;
    dai->capture_dma_data = 0;

    sunxi_daudio_init(platform);

    return 0;
}

static struct snd_dai sunxi_daudio_dai = {
    .id     = 1,
    .name       = "sunxi-daudio-cpudai",
    .playback   = {
        .stream_name    = "Playback",
        .channels_min   = 1,
        .channels_max   = 8,
        .rates      = SUNXI_DAUDIO_RATES,
        .formats    = SNDRV_PCM_FMTBIT_S16_LE
                | SNDRV_PCM_FMTBIT_S24_LE
                | SNDRV_PCM_FMTBIT_S32_LE,
        .rate_min   = 8000,
        .rate_max   = 192000,
    },
    .capture    = {
        .stream_name    = "Capture",
        .channels_min   = 1,
        .channels_max   = 8,
        .rates      = SUNXI_DAUDIO_RATES,
        .formats    = SNDRV_PCM_FMTBIT_S16_LE
                | SNDRV_PCM_FMTBIT_S24_LE
                | SNDRV_PCM_FMTBIT_S32_LE,
        .rate_min   = 8000,
        .rate_max   = 192000,
    },
    .probe      = sunxi_daudio_dai_probe,
    .ops        = &sunxi_daudio_dai_ops,
};

#ifdef SUNXI_DAUDIO_HUB_ENABLE
static int sunxi_daudio_get_hub_mode(struct snd_kcontrol *kcontrol,
                struct snd_ctl_info *info)
{
    unsigned int reg_val;
    unsigned long value = 0;

    if (kcontrol->type != SND_CTL_ELEM_TYPE_ENUMERATED) {
        snd_err("invalid kcontrol type = %d.\n", kcontrol->type);
        return -EINVAL;
    }

    if (kcontrol->private_data_type == SND_MODULE_PLATFORM) {
        struct snd_platform *platform = kcontrol->private_data;
        struct sunxi_daudio_info *sunxi_daudio = platform->private_data;
        reg_val = snd_platform_read(platform, SUNXI_DAUDIO_FIFOCTL);
        value = ((reg_val & (1 << HUB_EN)) ? 1 : 0);
    } else {
        snd_err("invalid kcontrol data type = %d.\n",
                kcontrol->private_data_type);
        return -EINVAL;
    }

    snd_kcontrol_to_snd_ctl_info(kcontrol, info, value);

    return 0;
}

static int sunxi_daudio_set_hub_mode(struct snd_kcontrol *kcontrol,
                unsigned long value)
{
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
        struct sunxi_daudio_info *sunxi_daudio = platform->private_data;
        snd_platform_update_bits(platform, SUNXI_DAUDIO_FIFOCTL,
                (1 << HUB_EN), (value << HUB_EN));
        sunxi_daudio->hub_mode = value;
    } else {
        snd_err("invalid kcontrol data type = %d.\n",
                kcontrol->private_data_type);
    }
    snd_info("mask:0x%x, items:%d, value:0x%x\n",
            kcontrol->mask, kcontrol->items, value);

    return 0;
}

static const char * const daudio_format_function[] = {
            "hub_disable", "hub_enable"};
#endif

/* pcm Audio Mode Select */
static struct snd_kcontrol sunxi_daudio_controls[] = {
#ifdef SUNXI_DAUDIO_HUB_ENABLE
    SND_CTL_ENUM_EXT("sunxi daudio audio hub mode",
        ARRAY_SIZE(daudio_format_function), daudio_format_function,
        SND_CTL_ENUM_AUTO_MASK,
        sunxi_daudio_get_hub_mode, sunxi_daudio_set_hub_mode),
#endif
    SND_CTL_KCONTROL("sunxi daudio loopback debug", SUNXI_DAUDIO_CTL, LOOP_EN, 0x1),
};

/****************************************************************************/
#ifndef sunxi_slave_id
#define sunxi_slave_id(d, s) (((d)<<16) | (s))
#endif

/* playback: period_size=2048*(16*2/8)=8K buffer_size=8K*8=64K */
/* capture:  period_size=2048*(16*4/8)=16K buffer_size=16K*8=128K */
static const struct snd_pcm_hardware sunxi_pcm_hardware[2] = {
    {   /* SNDRV_PCM_STREAM_PLAYBACK */
        .info           = SNDRV_PCM_INFO_INTERLEAVED
                    | SNDRV_PCM_INFO_BLOCK_TRANSFER
                    | SNDRV_PCM_INFO_MMAP
                    | SNDRV_PCM_INFO_MMAP_VALID
                    | SNDRV_PCM_INFO_PAUSE
                    | SNDRV_PCM_INFO_RESUME,
        .buffer_bytes_max   = 1024 * 128,
        .period_bytes_min   = 256,
        .period_bytes_max   = 1024 * 64,
        .periods_min        = 2,
        .periods_max        = 16,
    },
    {   /* SNDRV_PCM_STREAM_CAPTURE */
        .info           = SNDRV_PCM_INFO_INTERLEAVED
                    | SNDRV_PCM_INFO_BLOCK_TRANSFER
                    | SNDRV_PCM_INFO_MMAP
                    | SNDRV_PCM_INFO_MMAP_VALID
                    | SNDRV_PCM_INFO_PAUSE
                    | SNDRV_PCM_INFO_RESUME,
        .buffer_bytes_max   = 1024 * 128,
        .period_bytes_min   = 256,
        .period_bytes_max   = 1024 * 64,
        .periods_min        = 2,
        .periods_max        = 16,
    },
};

static int sunxi_pcm_preallocate_dma_buffer(struct snd_pcm *pcm, int stream)
{
    const struct snd_pcm_hardware *hw = NULL;
    struct snd_codec *codec = pcm->card->codec;
    struct snd_dma_buffer *buf = &pcm->streams[stream]->dma_buffer;
    size_t size = 0;

    snd_print("prealloc dma buffer\n");
    if (codec->hw)
        hw = &codec->hw[stream];
    else
        hw = &sunxi_pcm_hardware[stream];

    size = hw->buffer_bytes_max;
    buf->addr = dma_alloc_coherent(size);
    if (!buf->addr) {
        snd_print("dma_alloc_coherent failed!->%s\n", __func__);
        return -ENOMEM;
    }
    buf->bytes = size;

    return 0;
}

int sunxi_daudio_pcm_new(struct snd_pcm *pcm)
{
    int ret;

    snd_print("\n");
    if (pcm->streams[SNDRV_PCM_STREAM_PLAYBACK]) {
        ret = sunxi_pcm_preallocate_dma_buffer(pcm,
                        SNDRV_PCM_STREAM_PLAYBACK);
        if (ret != 0)
            goto err;
    }
    if (pcm->streams[SNDRV_PCM_STREAM_CAPTURE]) {
        ret = sunxi_pcm_preallocate_dma_buffer(pcm,
                        SNDRV_PCM_STREAM_CAPTURE);
        if (ret != 0)
            goto err;
    }
err:
    return 0;
}

void sunxi_daudio_pcm_free(struct snd_pcm *pcm)
{
    struct snd_pcm_substream *substream;
    struct snd_dma_buffer *buf;
    int stream;

    snd_print("\n");
    for (stream = 0; stream < 2; stream++) {
        substream = pcm->streams[stream];
        if (!substream)
            continue;
        buf = &substream->dma_buffer;
        if (!buf->addr)
            continue;
        snd_print("dma free.\n");
        dma_free_coherent(buf->addr);
        buf->addr = NULL;
    }

    return;
}

static int sunxi_pcm_open(struct snd_pcm_substream *substream)
{
    int ret;
    const struct snd_pcm_hardware *hw = NULL;
    struct snd_codec *codec = substream->pcm->card->codec;

    if (codec->hw)
        hw = &codec->hw[substream->stream];
    else
        hw = &sunxi_pcm_hardware[substream->stream];
    snd_set_runtime_hwparams(substream, hw);
    snd_print("request dma channel\n");
    /* request dma channel */
    ret = snd_dmaengine_pcm_open_request_chan(substream);
    if (ret != 0)
        snd_err("dmaengine pcm open failed with err %d\n", ret);

    return ret;
}

static int sunxi_pcm_close(struct snd_pcm_substream *substream)
{
    snd_print("\n");

    return snd_dmaengine_pcm_close_release_chan(substream);
}

static int sunxi_pcm_hw_params(struct snd_pcm_substream *substream,
    struct snd_pcm_hw_params *params)
{
    int ret;
    struct snd_card *card = substream->pcm->card;
    struct snd_dai *cpu_dai = card->platform->cpu_dai;
    struct dmaengine_pcm_runtime_data *prtd = substream->runtime->private_data;
    struct dma_chan *chan = snd_dmaengine_pcm_get_chan(substream);
    struct dma_slave_config slave_config = {0};
    struct sunxi_dma_params *dmap;
    struct snd_platform *platform = cpu_dai->component;

    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
        dmap = cpu_dai->playback_dma_data;
    else
        dmap = cpu_dai->capture_dma_data;

    ret = snd_hwparams_to_dma_slave_config(substream, params, &slave_config);
    if (ret != 0) {
        snd_err("hw params config failed with err %d\n", ret);
        return ret;
    }
    slave_config.dst_maxburst = dmap->dst_maxburst;
    slave_config.src_maxburst = dmap->src_maxburst;
    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
        slave_config.dst_addr = (uint32_t)dmap->dma_addr;
        slave_config.src_addr_width = slave_config.dst_addr_width;
        slave_config.slave_id = sunxi_slave_id(dmap->dma_drq_type_num,
                                    0);
    } else {
        slave_config.src_addr = (uint32_t)dmap->dma_addr;
        slave_config.dst_addr_width = slave_config.src_addr_width;
        slave_config.slave_id = sunxi_slave_id(0,
                        dmap->dma_drq_type_num);
    }
#if 0
    snd_err("direction: %d, src_addr:%p, dst_addr:%p\n"
        "src_buswidth:%d, dst_buswidth: %d\n"
        "src_maxburst:%d, dst_maxburst: %d\n"
        "slave_id: %d\n", slave_config.direction,
        slave_config.src_addr, slave_config.dst_addr,
        slave_config.src_addr_width, slave_config.dst_addr_width,
        slave_config.src_maxburst, slave_config.dst_maxburst,
        slave_config.slave_id);
#endif
    ret = dmaengine_slave_config(chan, &slave_config);
    if (ret != 0) {
        snd_err("dmaengine_slave_config failed with err %d\n", ret);
        return ret;
    }

    snd_pcm_set_runtime_buffer(substream, &substream->dma_buffer);

    return 0;
}

static int sunxi_pcm_hw_free(struct snd_pcm_substream *substream)
{
    snd_print("\n");
    snd_pcm_set_runtime_buffer(substream, NULL);

    return 0;
}

static int sunxi_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
    snd_print(" stream:%u, cmd:%u\n", substream->stream, cmd);
    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
        switch (cmd) {
        case SNDRV_PCM_TRIGGER_START:
        case SNDRV_PCM_TRIGGER_RESUME:
        case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
            snd_dmaengine_pcm_trigger(substream,
                    SNDRV_PCM_TRIGGER_START);
            break;
        case SNDRV_PCM_TRIGGER_SUSPEND:
        case SNDRV_PCM_TRIGGER_STOP:
        case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
            snd_dmaengine_pcm_trigger(substream,
                    SNDRV_PCM_TRIGGER_STOP);
            break;
        }
    } else {
        switch (cmd) {
        case SNDRV_PCM_TRIGGER_START:
        case SNDRV_PCM_TRIGGER_RESUME:
        case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
            snd_dmaengine_pcm_trigger(substream,
                    SNDRV_PCM_TRIGGER_START);
            break;
        case SNDRV_PCM_TRIGGER_SUSPEND:
        case SNDRV_PCM_TRIGGER_STOP:
        case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
            snd_dmaengine_pcm_trigger(substream,
                    SNDRV_PCM_TRIGGER_STOP);
            break;
        }
    }

    return 0;
}

struct snd_pcm_ops sunxi_daudio_pcm_ops = {
    .open       = sunxi_pcm_open,
    .close      = sunxi_pcm_close,
    .hw_params  = sunxi_pcm_hw_params,
    .hw_free    = sunxi_pcm_hw_free,
    .trigger    = sunxi_pcm_trigger,
    .pointer    = snd_dmaengine_pcm_pointer,
};

/****************************************************************************/
static int sunxi_daudio_platform_probe(struct snd_platform *platform)
{
    int ret = 0;
    int i = 0;
    int tdm_num = platform->type - SND_PLATFORM_TYPE_DAUDIO0;
    struct sunxi_daudio_info *sunxi_daudio = NULL;

    snd_print("\n");
    sunxi_daudio = snd_malloc(sizeof(struct sunxi_daudio_info));
    if (!sunxi_daudio) {
        snd_err("no memory\n");
        return -ENOMEM;
    }

    platform->private_data = (void *)sunxi_daudio;
    platform->cpu_dai->component = platform;
    sunxi_daudio->platform = platform;

    /* parser para */
    sunxi_daudio->param = daudio_param[tdm_num];
    if (tdm_num > DAUDIO_NUM_MAX) {
        snd_err("tdm_num:%u overflow.\n", sunxi_daudio->param.tdm_num);
        ret = -EFAULT;
        goto err_daudio_get_param;
    }

    /* clk */
    sunxi_daudio->pllclk = HAL_CLK_PLL_AUDIO;
    switch (sunxi_daudio->param.tdm_num) {
    case 0:
        sunxi_daudio->moduleclk = HAL_CLK_PERIPH_I2S0;
        break;
    case 1:
        sunxi_daudio->moduleclk = HAL_CLK_PERIPH_I2S1;
        break;
    default:
        snd_err("tdm_num:%u overflow\n", sunxi_daudio->param.tdm_num);
        ret = -EFAULT;
        goto err_daudio_get_moduleclk;
    }

    sunxi_daudio->pllclk = HAL_CLK_PLL_AUDIO;

    ret = hal_clk_set_parent(sunxi_daudio->moduleclk, sunxi_daudio->pllclk);
    if (ret != HAL_CLK_STATUS_OK) {
        snd_err("daudio[%d] clk_set_parent failed.\n",
                    sunxi_daudio->param.tdm_num);
        goto err_daudio_moduleclk_set_parent;
    }

    ret = hal_clock_enable(sunxi_daudio->pllclk);
    if (ret != HAL_CLK_STATUS_OK) {
        snd_err("daudio%d clk_enable pllclk failed.\n",
            sunxi_daudio->param.tdm_num);
        goto err_daudio_pllclk_enable;
    }
    ret = hal_clock_enable(sunxi_daudio->moduleclk);
    if (ret != HAL_CLK_STATUS_OK) {
        snd_err("daudio%d clk_enable moduleclk failed.\n",
            sunxi_daudio->param.tdm_num);
        goto err_daudio_moduleclk_enable;
    }

    /* mem base */
    platform->mem_base = (void *)SUNXI_DAUDIO_BASE + (0x1000 * sunxi_daudio->param.tdm_num);

    /* pinctrl */
    switch (sunxi_daudio->param.tdm_num) {
    case 0:
        sunxi_daudio->pinctrl = daudio0_pinctrl;
        sunxi_daudio->pinctrl_num = ARRAY_SIZE(daudio0_pinctrl);
        break;
    case 1:
        sunxi_daudio->pinctrl = daudio1_pinctrl;
        sunxi_daudio->pinctrl_num = ARRAY_SIZE(daudio1_pinctrl);
        break;
    default:
        sunxi_daudio->pinctrl = daudio0_pinctrl;
        sunxi_daudio->pinctrl_num = sizeof(daudio0_pinctrl)/
                        sizeof(struct daudio_pinctrl);
        break;
    }

    snd_print("daudio%d pinctrl_num = %d.\n", sunxi_daudio->param.tdm_num,
            sunxi_daudio->pinctrl_num);
    for (i = 0; i < sunxi_daudio->pinctrl_num; i++) {
        ret = hal_gpio_pinmux_set_function(sunxi_daudio->pinctrl[i].gpio_pin,
                        sunxi_daudio->pinctrl[i].mux);
        if (ret != 0) {
            snd_err("daudio%d pinmux[%d] set failed.\n",
                    sunxi_daudio->param.tdm_num,
                    sunxi_daudio->pinctrl[i].gpio_pin);
        }
        ret = hal_gpio_set_driving_level(sunxi_daudio->pinctrl[i].gpio_pin,
                    sunxi_daudio->pinctrl[i].driv_level);
        if (ret != 0) {
            snd_err("daudio%d driv_level = %d set failed.\n",
                    sunxi_daudio->param.tdm_num,
                    sunxi_daudio->pinctrl[i].driv_level);
        }
    }

    /* init some params */
    sunxi_daudio->hub_mode = 0;
    sunxi_daudio->playback_en = 0;
    sunxi_daudio->capture_en = 0;

    /* dma config */
    sunxi_daudio->playback_dma_param.src_maxburst = 4;
    sunxi_daudio->playback_dma_param.dst_maxburst = 4;
    sunxi_daudio->playback_dma_param.dma_addr =
            platform->mem_base + SUNXI_DAUDIO_TXFIFO;
    sunxi_daudio->capture_dma_param.src_maxburst = 4;
    sunxi_daudio->capture_dma_param.dst_maxburst = 4;
    sunxi_daudio->capture_dma_param.dma_addr =
            platform->mem_base + SUNXI_DAUDIO_RXFIFO;

    switch (sunxi_daudio->param.tdm_num) {
    case 0:
        SUNXI_DAUDIO_DRQDST(sunxi_daudio, 0);
        SUNXI_DAUDIO_DRQSRC(sunxi_daudio, 0);
        break;
    case 1:
        SUNXI_DAUDIO_DRQDST(sunxi_daudio, 1);
        SUNXI_DAUDIO_DRQSRC(sunxi_daudio, 1);
        break;
    default:
        snd_err("tdm_num:%u overflow\n", sunxi_daudio->param.tdm_num);
        ret = -EFAULT;
        goto err_daudio_tdm_num_over;
    }

#ifdef SUNXI_ADC_DAUDIO_SYNC
    adc_daudio_sync_platform = platform;
#endif
    return 0;

err_daudio_tdm_num_over:
    hal_clock_disable(sunxi_daudio->moduleclk);
err_daudio_moduleclk_enable:
    hal_clock_disable(sunxi_daudio->pllclk);
err_daudio_pllclk_enable:
err_daudio_moduleclk_set_parent:
err_daudio_get_moduleclk:
err_daudio_get_param:
    snd_free(sunxi_daudio);
    return ret;
}

static int sunxi_daudio_platform_remove(struct snd_platform *platform)
{
    struct sunxi_daudio_info *info = NULL;

    snd_print("\n");
    info = platform->private_data;
    if (!info)
        return 0;
    snd_free(info);
    platform->private_data = NULL;

    return 0;
}

int snd_platform_daudio_register(struct snd_platform *platform, int num)
{
    int ret = 0;

    if (num >= DAUDIO_NUM_MAX) {
        snd_err("num=%d, but the number of daudio is %d\n",
            num, DAUDIO_NUM_MAX);
        return -1;
    }

    platform->name = snd_malloc(DAUDIO_NAME_LEN);
    if (!platform->name) {
        snd_err("no memory\n");
        return -ENOMEM;
    }

    printf(platform->name, DAUDIO_NAME_LEN, "daudio%d-cpudai", num);
    snd_print("platform->name:%s\n", platform->name);

    platform->ops = &sunxi_daudio_pcm_ops;
    platform->pcm_new = sunxi_daudio_pcm_new;
    platform->pcm_free = sunxi_daudio_pcm_free;
    platform->cpu_dai = snd_malloc(sizeof(struct snd_dai));
    if (!platform->cpu_dai) {
        snd_err("cpu_dai malloc failed.\n");
        ret = -ENOMEM;
        goto err_cpu_dai_malloc;
    }
    memcpy(platform->cpu_dai, &sunxi_daudio_dai, sizeof(struct snd_dai));

    platform->probe = sunxi_daudio_platform_probe;
    platform->remove = sunxi_daudio_platform_remove;

    platform->num_controls = ARRAY_SIZE(sunxi_daudio_controls);
    platform->controls = snd_malloc(sizeof(struct snd_kcontrol) * platform->num_controls);
    if (!platform->controls) {
        snd_err("controls malloc failed.\n");
        ret = -ENOMEM;
        goto err_control_malloc;
    }
    memcpy(platform->controls, sunxi_daudio_controls,
            sizeof(struct snd_kcontrol) * platform->num_controls);

    return 0;

err_control_malloc:
    snd_free(platform->cpu_dai);
err_cpu_dai_malloc:
    snd_free(platform->name);
    return ret;
}
