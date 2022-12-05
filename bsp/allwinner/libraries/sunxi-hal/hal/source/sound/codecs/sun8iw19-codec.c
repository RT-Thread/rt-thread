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
#include <stdlib.h>
#include <string.h>
#include <init.h>
#include <log.h>
#include <sound/snd_core.h>
#include <sound/snd_pcm.h>
#include <sound/pcm_common.h>
#include <aw_common.h>
#include <hal_gpio.h>
#include <sound/snd_dma.h>
#include <sound/dma_wrap.h>
#include <hal_dma.h>
#include "hal_clk.h"

#include "sunxi-codec.h"
#include "sun8iw19-codec.h"
/* #include "../platform/sun8iw19-daudio.h" */

struct snd_codec sunxi_audiocodec;

static struct sunxi_codec_param default_param = {
    .digital_vol    = 0x0,
    .lineout_vol    = 0x1f,
    .mic1gain   = 0x1f,
    .lineingain = 0x0,
    .gpio_spk   = GPIOH(4),
    .pa_msleep_time = 160,
    .pa_level   = 1,
    .adcdrc_cfg     = 0,
    .adchpf_cfg     = 1,
    .dacdrc_cfg     = 0,
    .dachpf_cfg     = 0,
};

static const struct sample_rate sample_rate_conv[] = {
    {44100, 0},
    {48000, 0},
    {8000, 5},
    {32000, 1},
    {22050, 2},
    {24000, 2},
    {16000, 3},
    {11025, 4},
    {12000, 4},
    {192000, 6},
    {96000, 7},
};

#ifdef SUNXI_ADC_DAUDIO_SYNC
struct snd_codec *adc_daudio_sync_codec;
static int substream_mode;
int adc_sync_flag;

int sunxi_codec_get_pcm_trigger_substream_mode(void)
{
    return substream_mode;
}

void sunxi_codec_set_pcm_trigger_substream_mode(int value)
{
    if (!((adc_sync_flag >> ADC_I2S_RUNNING) & 0x1)) {
        substream_mode = value;
    } else {
        pr_err("set the adc sync mode should be stop the record.\n");
    }
}

void sunxi_codec_set_pcm_adc_sync_flag(int value)
{
       adc_sync_flag = value;
}

int sunxi_codec_get_pcm_adc_sync_flag(void)
{
    return adc_sync_flag;
}

/* for adc and i2s rx sync */
void sunxi_cpudai_adc_drq_enable(bool enable)
{
    if (enable) {
        snd_codec_update_bits(adc_daudio_sync_codec, SUNXI_ADC_FIFOC,
                (1 << ADC_DRQ_EN), (1 << ADC_DRQ_EN));
    } else {
        snd_codec_update_bits(adc_daudio_sync_codec, SUNXI_ADC_FIFOC,
                (1 << ADC_DRQ_EN), (0 << ADC_DRQ_EN));
    }
}
#endif

#ifdef SUNXI_CODEC_DAP_ENABLE
static void adcdrc_config(struct snd_codec *codec)
{
    /* Left peak filter attack time */
    snd_codec_write(codec, SUNXI_ADC_DRC_LPFHAT, (0x000B77BF >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_ADC_DRC_LPFLAT, 0x000B77BF & 0xFFFF);
    /* Right peak filter attack time */
    snd_codec_write(codec, SUNXI_ADC_DRC_RPFHAT, (0x000B77BF >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_ADC_DRC_RPFLAT, 0x000B77BF & 0xFFFF);
    /* Left peak filter release time */
    snd_codec_write(codec, SUNXI_ADC_DRC_LPFHRT, (0x00FFE1F8 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_ADC_DRC_LPFLRT, 0x00FFE1F8 & 0xFFFF);
    /* Right peak filter release time */
    snd_codec_write(codec, SUNXI_ADC_DRC_RPFHRT, (0x00FFE1F8 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_ADC_DRC_RPFLRT, 0x00FFE1F8 & 0xFFFF);

    /* Left RMS filter attack time */
    snd_codec_write(codec, SUNXI_ADC_DRC_LPFHAT, (0x00012BAF >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_ADC_DRC_LPFLAT, 0x00012BAF & 0xFFFF);
    /* Right RMS filter attack time */
    snd_codec_write(codec, SUNXI_ADC_DRC_RPFHAT, (0x00012BAF >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_ADC_DRC_RPFLAT, 0x00012BAF & 0xFFFF);

    /* smooth filter attack time */
    snd_codec_write(codec, SUNXI_ADC_DRC_SFHAT, (0x00017665 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_ADC_DRC_SFLAT, 0x00017665 & 0xFFFF);
    /* gain smooth filter release time */
    snd_codec_write(codec, SUNXI_ADC_DRC_SFHRT, (0x00000F04 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_ADC_DRC_SFLRT, 0x00000F04 & 0xFFFF);

    /* OPL */
    snd_codec_write(codec, SUNXI_ADC_DRC_HOPL, (0xFBD8FBA7 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_ADC_DRC_LOPL, 0xFBD8FBA7 & 0xFFFF);
    /* OPC */
    snd_codec_write(codec, SUNXI_ADC_DRC_HOPC, (0xF95B2C3F >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_ADC_DRC_LOPC, 0xF95B2C3F & 0xFFFF);
    /* OPE */
    snd_codec_write(codec, SUNXI_ADC_DRC_HOPE, (0xF45F8D6E >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_ADC_DRC_LOPE, 0xF45F8D6E & 0xFFFF);
    /* LT */
    snd_codec_write(codec, SUNXI_ADC_DRC_HLT, (0x01A934F0 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_ADC_DRC_LLT, 0x01A934F0 & 0xFFFF);
    /* CT */
    snd_codec_write(codec, SUNXI_ADC_DRC_HCT, (0x06A4D3C0 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_ADC_DRC_LCT, 0x06A4D3C0 & 0xFFFF);
    /* ET */
    snd_codec_write(codec, SUNXI_ADC_DRC_HET, (0x0BA07291 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_ADC_DRC_LET, 0x0BA07291 & 0xFFFF);
    /* Ki */
    snd_codec_write(codec, SUNXI_ADC_DRC_HKI, (0x00051EB8 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_ADC_DRC_LKI, 0x00051EB8 & 0xFFFF);
    /* Kc */
    snd_codec_write(codec, SUNXI_ADC_DRC_HKC, (0x00800000 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_ADC_DRC_LKC, 0x00800000 & 0xFFFF);
    /* Kn */
    snd_codec_write(codec, SUNXI_ADC_DRC_HKN, (0x01000000 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_ADC_DRC_LKN, 0x01000000 & 0xFFFF);
    /* Ke */
    snd_codec_write(codec, SUNXI_ADC_DRC_HKE, (0x0000F45F >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_ADC_DRC_LKE, 0x0000F45F & 0xFFFF);
}

static void adcdrc_enable(struct snd_codec *codec, bool on)
{
    struct sunxi_codec_info *sunxi_codec = codec->private_data;

    if (on) {
        snd_codec_update_bits(codec, SUNXI_ADC_DAP_CTL,
            (0x1 << ADC_DRC0_EN), (0x1 << ADC_DRC0_EN));
    } else {
        snd_codec_update_bits(codec, SUNXI_ADC_DAP_CTL,
            (0x1 << ADC_DRC0_EN), (0x0 << ADC_DRC0_EN));
    }
}

static void adchpf_config(struct snd_codec *codec)
{
    /* HPF */
    snd_codec_write(codec, SUNXI_ADC_DRC_HHPFC, (0xFFFAC1 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_ADC_DRC_LHPFC, 0xFFFAC1 & 0xFFFF);
}

static void adchpf_enable(struct snd_codec *codec, bool on)
{
    struct sunxi_codec_info *sunxi_codec = codec->private_data;

    if (on) {
        snd_codec_update_bits(codec, SUNXI_ADC_DAP_CTL,
            (0x1 << ADC_HPF0_EN), (0x1 << ADC_HPF0_EN));
    } else {
        snd_codec_update_bits(codec, SUNXI_ADC_DAP_CTL,
            (0x1 << ADC_HPF0_EN), (0x0 << ADC_HPF0_EN));
    }
}

static void dacdrc_config(struct snd_codec *codec)
{
    /* Left peak filter attack time */
    snd_codec_write(codec, SUNXI_DAC_DRC_LPFHAT, (0x000B77BF >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_LPFLAT, 0x000B77BF & 0xFFFF);
    /* Right peak filter attack time */
    snd_codec_write(codec, SUNXI_DAC_DRC_RPFHAT, (0x000B77F0 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_RPFLAT, 0x000B77F0 & 0xFFFF);

    /* Left peak filter release time */
    snd_codec_write(codec, SUNXI_DAC_DRC_LPFHRT, (0x00FFE1F8 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_LPFLRT, 0x00FFE1F8 & 0xFFFF);
    /* Right peak filter release time */
    snd_codec_write(codec, SUNXI_DAC_DRC_RPFHRT, (0x00FFE1F8 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_RPFLRT, 0x00FFE1F8 & 0xFFFF);

    /* Left RMS filter attack time */
    snd_codec_write(codec, SUNXI_DAC_DRC_LRMSHAT, (0x00012BB0 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_LRMSLAT, 0x00012BB0 & 0xFFFF);
    /* Right RMS filter attack time */
    snd_codec_write(codec, SUNXI_DAC_DRC_RRMSHAT, (0x00012BB0 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_RRMSLAT, 0x00012BB0 & 0xFFFF);

    /* smooth filter attack time */
    snd_codec_write(codec, SUNXI_DAC_DRC_SFHAT, (0x00017665 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_SFLAT, 0x00017665 & 0xFFFF);
    /* gain smooth filter release time */
    snd_codec_write(codec, SUNXI_DAC_DRC_SFHRT, (0x00000F04 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_SFLRT, 0x00000F04 & 0xFFFF);

    /* OPL */
    snd_codec_write(codec, SUNXI_DAC_DRC_HOPL, (0xFF641741 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_LOPL, 0xFF641741 & 0xFFFF);
    /* OPC */
    snd_codec_write(codec, SUNXI_DAC_DRC_HOPC, (0xF9E8E88C >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_LOPC, 0xF9E8E88C & 0xFFFF);
    /* OPE */
    snd_codec_write(codec, SUNXI_DAC_DRC_HOPE, (0xF5DE3D14 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_LOPE, 0xF5DE3D14 & 0xFFFF);
    /* LT */
    snd_codec_write(codec, SUNXI_DAC_DRC_HLT, (0x0336110B >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_LLT, 0x0336110B & 0xFFFF);
    /* CT */
    snd_codec_write(codec, SUNXI_DAC_DRC_HCT, (0x08BF6C28 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_LCT, 0x08BF6C28 & 0xFFFF);
    /* ET */
    snd_codec_write(codec, SUNXI_DAC_DRC_HET, (0x0C9F9255 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_LET, 0x0C9F9255 & 0xFFFF);
    /* Ki */
    snd_codec_write(codec, SUNXI_DAC_DRC_HKI, (0x001A7B96 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_LKI, 0x001A7B96 & 0xFFFF);
    /* Kc */
    snd_codec_write(codec, SUNXI_DAC_DRC_HKC, (0x00FD70A5 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_LKC, 0x00FD70A5 & 0xFFFF);
    /* Kn */
    snd_codec_write(codec, SUNXI_DAC_DRC_HKN, (0x010AF8B0 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_LKN, 0x010AF8B0 & 0xFFFF);
    /* Ke */
    snd_codec_write(codec, SUNXI_DAC_DRC_HKE, (0x06286BA0 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_LKE, 0x06286BA0 & 0xFFFF);
    /* MXG */
    snd_codec_write(codec, SUNXI_DAC_DRC_MXGHS, (0x035269E0 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_MXGLS, 0x035269E0 & 0xFFFF);
    /* MNG */
    snd_codec_write(codec, SUNXI_DAC_DRC_MNGHS, (0xF95B2C3F >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_MNGLS, 0xF95B2C3F & 0xFFFF);
    /* EPS */
    snd_codec_write(codec, SUNXI_DAC_DRC_EPSHC, (0x00025600 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_EPSLC, 0x00025600 & 0xFFFF);
}

static void dacdrc_enable(struct snd_codec *codec, bool on)
{
    struct sunxi_codec_info *sunxi_codec = codec->private_data;

    if (on) {
        /* detect noise when ET enable */
        snd_codec_update_bits(codec, SUNXI_DAC_DRC_CTRL,
            (0x1 << DAC_DRC_NOISE_DET_EN),
            (0x1 << DAC_DRC_NOISE_DET_EN));

        /* 0x0:RMS filter; 0x1:Peak filter */
        snd_codec_update_bits(codec, SUNXI_DAC_DRC_CTRL,
            (0x1 << DAC_DRC_SIGNAL_SEL),
            (0x1 << DAC_DRC_SIGNAL_SEL));

        snd_codec_update_bits(codec, SUNXI_DAC_DRC_CTRL,
            (0x1 << DAC_DRC_GAIN_MAX_EN),
            (0x1 << DAC_DRC_GAIN_MAX_EN));

        snd_codec_update_bits(codec, SUNXI_DAC_DRC_CTRL,
            (0x1 << DAC_DRC_GAIN_MIN_EN),
            (0x1 << DAC_DRC_GAIN_MIN_EN));

        /* delay function enable */
        snd_codec_update_bits(codec, SUNXI_DAC_DRC_CTRL,
            (0x1 << DAC_DRC_DELAY_BUF_EN),
            (0x1 << DAC_DRC_DELAY_BUF_EN));

        snd_codec_update_bits(codec, SUNXI_DAC_DRC_CTRL,
            (0x1 << DAC_DRC_LT_EN),
            (0x1 << DAC_DRC_LT_EN));
        snd_codec_update_bits(codec, SUNXI_DAC_DRC_CTRL,
            (0x1 << DAC_DRC_ET_EN),
            (0x1 << DAC_DRC_ET_EN));

        snd_codec_update_bits(codec, SUNXI_DAC_DAP_CTL,
            (0x1 << DDAP_DRC_EN),
            (0x1 << DDAP_DRC_EN));
    } else {
        snd_codec_update_bits(codec, SUNXI_DAC_DAP_CTL,
            (0x1 << DDAP_DRC_EN),
            (0x0 << DDAP_DRC_EN));

        /* detect noise when ET enable */
        snd_codec_update_bits(codec, SUNXI_DAC_DRC_CTRL,
            (0x1 << DAC_DRC_NOISE_DET_EN),
            (0x0 << DAC_DRC_NOISE_DET_EN));

        /* 0x0:RMS filter; 0x1:Peak filter */
        snd_codec_update_bits(codec, SUNXI_DAC_DRC_CTRL,
            (0x1 << DAC_DRC_SIGNAL_SEL),
            (0x0 << DAC_DRC_SIGNAL_SEL));

        /* delay function enable */
        snd_codec_update_bits(codec, SUNXI_DAC_DRC_CTRL,
            (0x1 << DAC_DRC_DELAY_BUF_EN),
            (0x0 << DAC_DRC_DELAY_BUF_EN));

        snd_codec_update_bits(codec, SUNXI_DAC_DRC_CTRL,
            (0x1 << DAC_DRC_GAIN_MAX_EN),
            (0x0 << DAC_DRC_GAIN_MAX_EN));
        snd_codec_update_bits(codec, SUNXI_DAC_DRC_CTRL,
            (0x1 << DAC_DRC_GAIN_MIN_EN),
            (0x0 << DAC_DRC_GAIN_MIN_EN));

        snd_codec_update_bits(codec, SUNXI_DAC_DRC_CTRL,
            (0x1 << DAC_DRC_LT_EN),
            (0x0 << DAC_DRC_LT_EN));
        snd_codec_update_bits(codec, SUNXI_DAC_DRC_CTRL,
            (0x1 << DAC_DRC_ET_EN),
            (0x0 << DAC_DRC_ET_EN));
    }
}

static void dachpf_config(struct snd_codec *codec)
{
    /* HPF */
    snd_codec_write(codec, SUNXI_DAC_DRC_HHPFC, (0xFFFAC1 >> 16) & 0xFFFF);
    snd_codec_write(codec, SUNXI_DAC_DRC_LHPFC, 0xFFFAC1 & 0xFFFF);
}

static void dachpf_enable(struct snd_codec *codec, bool on)
{
    struct sunxi_codec_info *sunxi_codec = codec->private_data;

    if (on) {
        snd_codec_update_bits(codec, SUNXI_DAC_DAP_CTL,
            (0x1 << DDAP_HPF_EN),
            (0x1 << DDAP_HPF_EN));
    } else {
        snd_codec_update_bits(codec, SUNXI_DAC_DAP_CTL,
            (0x1 << DDAP_HPF_EN),
            (0x0 << DDAP_HPF_EN));
    }
}
#endif

/* for adc and i2s rx sync */
#ifdef SUNXI_ADC_DAUDIO_SYNC
static int sunxi_codec_get_substream_mode(struct snd_kcontrol *kcontrol,
        struct snd_ctl_info *info)
{
    unsigned int val = 0;
    uint32_t __cpsr;

        __cpsr = hal_spin_lock_irqsave();

    if (kcontrol->type != SND_CTL_ELEM_TYPE_ENUMERATED)
        return -EINVAL;

    if (kcontrol->private_data_type == SND_MODULE_CODEC)
        val = sunxi_codec_get_pcm_trigger_substream_mode();
    else
        return -EINVAL;

    snd_kcontrol_to_snd_ctl_info(kcontrol, info, val);
        hal_spin_unlock_irqrestore(__cpsr);

    return 0;

}

static int sunxi_codec_set_substream_mode(struct snd_kcontrol *kcontrol,
                        unsigned long value)
{
    uint32_t __cpsr;

        __cpsr = hal_spin_lock_irqsave();

    if (kcontrol->type != SND_CTL_ELEM_TYPE_ENUMERATED)
        return -EINVAL;

    if (value >= kcontrol->items)
        return -EINVAL;

    if (kcontrol->private_data_type == SND_MODULE_CODEC)
        sunxi_codec_set_pcm_trigger_substream_mode(value);

        hal_spin_unlock_irqrestore(__cpsr);
    snd_info("mask:0x%x, items:%d, value:0x%x\n",
            kcontrol->mask, kcontrol->items, value);

    return 0;
}

static const char * const sunxi_codec_substream_mode_function[] = {"ADC_ASYNC",
            "ADC_I2S_SYNC"};
#endif

static const char * const codec_format_function[] = {
            "hub_disable", "hub_enable"};

static const char * const codec_output_mode_select[] = {
            "DACL_SINGLE", "DACL_DIFFER"};

static const char * const codec_linein_switch[] = {
            "Off", "On"};


static struct snd_kcontrol sunxi_codec_controls[] = {
    SND_CTL_ENUM("codec hub mode",
        ARRAY_SIZE(codec_format_function), codec_format_function,
                    SUNXI_DAC_DPC, DAC_HUB_EN),
    SND_CTL_ENUM("Left LINEOUT Mux",
        ARRAY_SIZE(codec_output_mode_select), codec_output_mode_select,
                    SUNXI_DAC_ANA_CTL, LINEOUTLDIFFEN),
    SND_CTL_ENUM("Left Input Mixer LINEINL Switch",
        ARRAY_SIZE(codec_linein_switch), codec_linein_switch,
                    SUNXI_ADCL_ANA_CTL, LINEINLEN),
#ifdef SUNXI_ADC_DAUDIO_SYNC
    SND_CTL_ENUM_EXT("codec trigger substream mode",
                ARRAY_SIZE(sunxi_codec_substream_mode_function),
                sunxi_codec_substream_mode_function,
                SND_CTL_ENUM_AUTO_MASK,
                sunxi_codec_get_substream_mode,
                sunxi_codec_set_substream_mode),
#endif
    SND_CTL_KCONTROL("digital volume", SUNXI_DAC_DPC, DVOL, 0x3F),
    SND_CTL_KCONTROL("LINEIN gain volume", SUNXI_ADCL_ANA_CTL, LINEINLG, 0x1),
    SND_CTL_KCONTROL("MIC1 gain volume", SUNXI_ADCL_ANA_CTL, PGA_GAIN_CTRL, 0x1F),
    SND_CTL_KCONTROL("LINEOUT volume", SUNXI_DAC_ANA_CTL, LINEOUT_VOL, 0x1F),
};

static void sunxi_codec_init(struct snd_codec *codec)
{
    struct sunxi_codec_info *sunxi_codec = codec->private_data;
    struct sunxi_codec_param *param = &sunxi_codec->param;
    unsigned int ret;

    /* Enable ADCFDT to overcome niose at the beginning */
    snd_codec_update_bits(codec, SUNXI_ADC_FIFOC,
            (0x7 << ADCDFEN), (0x7 << ADCDFEN));

    /* init the mic pga and vol params */
    snd_codec_update_bits(codec, SUNXI_DAC_ANA_CTL,
            0x1F << LINEOUT_VOL,
            param->lineout_vol << LINEOUT_VOL);

    snd_codec_update_bits(codec, SUNXI_DAC_DPC,
            0x3F << DVOL,
            param->digital_vol << DVOL);

    snd_codec_update_bits(codec, SUNXI_ADCL_ANA_CTL,
            0x1F << PGA_GAIN_CTRL,
            param->mic1gain << PGA_GAIN_CTRL);

    snd_codec_update_bits(codec, SUNXI_ADCL_ANA_CTL,
            0x1 << LINEINLG,
            param->lineingain << LINEINLG);

    snd_codec_update_bits(codec, SUNXI_ADCL_ANA_CTL,
            0x3 << IOPLINE, 0x1 << IOPLINE);

#ifdef SUNXI_CODEC_DAP_ENABLE
    if (param->dacdrc_cfg || param->dachpf_cfg) {
        snd_codec_update_bits(codec, SUNXI_DAC_DAP_CTL,
                (0x1 << DDAP_EN), (0x1 << DDAP_EN));
    }

    if (param->adcdrc_cfg || param->adchpf_cfg) {
        snd_codec_update_bits(codec, SUNXI_ADC_DAP_CTL,
                (0x1 << ADC_DAP0_EN), (0x1 << ADC_DAP0_EN));
    }

    if (param->adcdrc_cfg) {
        adcdrc_config(codec);
        adcdrc_enable(codec, 1);
    }
    if (param->adchpf_cfg) {
        adchpf_config(codec);
        adchpf_enable(codec, 1);
    }
    if (param->dacdrc_cfg) {
        dacdrc_config(codec);
        dacdrc_enable(codec, 1);
    }
    if (param->dachpf_cfg) {
        dachpf_config(codec);
        dachpf_enable(codec, 1);
    }
#endif
}

static int sunxi_codec_dapm_control(struct snd_pcm_substream *substream,
                struct snd_dai *dai, int onoff)
{
    struct snd_codec *codec = dai->component;
    struct sunxi_codec_info *sunxi_codec = codec->private_data;
    struct sunxi_codec_param *param = &sunxi_codec->param;

    if (substream->dapm_state == onoff)
        return 0;
    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
        /*
         * Playback:
         * Playback --> DACL --> Left LINEOUT Mux --> LINEOUTL --> External Speaker
         *
         */
        if (onoff) {
            /* Playback on */
            /* analog DAC enable */
            snd_codec_update_bits(codec, SUNXI_DAC_ANA_CTL,
                    (0x1<<DACLEN), (0x1<<DACLEN));
            /* digital DAC enable */
            snd_codec_update_bits(codec, SUNXI_DAC_DPC,
                    (0x1<<EN_DAC), (0x1<<EN_DAC));
            hal_msleep(10);
            snd_codec_update_bits(codec, SUNXI_DAC_ANA_CTL,
                (0x1<<DACLMUTE), (0x1<<DACLMUTE));
            /* LINEOUT */
            snd_codec_update_bits(codec, SUNXI_DAC_ANA_CTL,
                (0x1<<LINEOUTL_EN), (0x1<<LINEOUTL_EN));

            if (param->gpio_spk > 0) {
                hal_gpio_set_direction(param->gpio_spk, 1);
                hal_gpio_set_data(param->gpio_spk, 1);
                hal_msleep(param->pa_msleep_time);
            }
        } else {
            /* Playback off */
            if (param->gpio_spk > 0) {
                hal_gpio_set_direction(param->gpio_spk, 0);
                hal_gpio_set_data(param->gpio_spk, 0);
            }
            /* LINEOUT */
            snd_codec_update_bits(codec, SUNXI_DAC_ANA_CTL,
                (0x1<<LINEOUTL_EN), (0x0<<LINEOUTL_EN));

            snd_codec_update_bits(codec, SUNXI_DAC_ANA_CTL,
                (0x1<<DACLMUTE), (0x0<<DACLMUTE));

            /* digital DAC */
            snd_codec_update_bits(codec, SUNXI_DAC_DPC,
                    (0x1<<EN_DAC), (0x0<<EN_DAC));
            /* analog DAC */
            snd_codec_update_bits(codec, SUNXI_DAC_ANA_CTL,
                    (0x1<<DACLEN), (0x0<<DACLEN));
        }
    } else {
        /*
         * Capture:
         * Capture <-- ADCL <-- Left Input Mixer <-- MIC1 PGA <-- MIC1 <-- MainMic Bias
         *
         */
        unsigned int channels = 0;
        channels = substream->runtime->channels;

        snd_print("channels = %u\n", channels);
        if (onoff) {
            /* Capture on */
            /* digital ADC enable */
            hal_msleep(100);
            snd_codec_update_bits(codec, SUNXI_ADC_FIFOC,
                    (0x1<<EN_AD), (0x1<<EN_AD));
            switch (channels) {
            case 1:
                /* analog ADCL enable */
                snd_codec_update_bits(codec, SUNXI_ADCL_ANA_CTL,
                        (0x1<<ADCLEN), (0x1<<ADCLEN));

                snd_codec_update_bits(codec, SUNXI_ADCL_ANA_CTL,
                    (0x1<<MIC1AMPEN), (0x1<<MIC1AMPEN));
                break;
            default:
                snd_err("unknown channels:%u\n", channels);
                return -1;
            }
            /* MainMic Bias */
            snd_codec_update_bits(codec, SUNXI_MICBIAS_ANA_CTL,
                    (0x1<<MMICBIASEN), (0x1<<MMICBIASEN));
        } else {
            /* Capture off */
            /* MainMic Bias */
            snd_codec_update_bits(codec, SUNXI_MICBIAS_ANA_CTL,
                    (0x1<<MMICBIASEN), (0x0<<MMICBIASEN));
            switch (channels) {
            case 1:
                /* MIC1 PGA */
                snd_codec_update_bits(codec, SUNXI_ADCL_ANA_CTL,
                    (0x1<<MIC1AMPEN), (0x0<<MIC1AMPEN));

                /* analog ADCL enable */
                snd_codec_update_bits(codec, SUNXI_ADCL_ANA_CTL,
                        (0x1<<ADCLEN), (0x0<<ADCLEN));
                break;
            default:
                snd_err("unknown channels:%u\n", channels);
                return -1;
            }
            /* digital ADC enable */
            snd_codec_update_bits(codec, SUNXI_ADC_FIFOC,
                    (0x1<<EN_AD), (0x0<<EN_AD));
        }
    }
    substream->dapm_state = onoff;
    return 0;
}

static int sunxi_codec_startup(struct snd_pcm_substream *substream,
        struct snd_dai *dai)
{
    struct snd_codec *codec = dai->component;
    struct sunxi_codec_info *sunxi_codec = codec->private_data;
//  struct sunxi_codec_param *param = codec->param;

    snd_print("\n");

    return 0;
}


static int sunxi_codec_hw_params(struct snd_pcm_substream *substream,
        struct snd_pcm_hw_params *params, struct snd_dai *dai)
{
    struct snd_codec *codec = dai->component;
    struct sunxi_codec_info *sunxi_codec = codec->private_data;
    struct sunxi_codec_param *codec_param = &sunxi_codec->param;
    int i = 0;

    snd_print("\n");
    switch (params_format(params)) {
    case    SND_PCM_FORMAT_S16_LE:
        if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
            snd_codec_update_bits(codec, SUNXI_DAC_FIFOC,
                (3 << FIFO_MODE), (3 << FIFO_MODE));
            snd_codec_update_bits(codec, SUNXI_DAC_FIFOC,
                (1 << TX_SAMPLE_BITS), (0 << TX_SAMPLE_BITS));
        } else {
            snd_codec_update_bits(codec, SUNXI_ADC_FIFOC,
                (1 << RX_FIFO_MODE), (1 << RX_FIFO_MODE));
            snd_codec_update_bits(codec, SUNXI_ADC_FIFOC,
                (1 << RX_SAMPLE_BITS), (0 << RX_SAMPLE_BITS));
        }
        break;
    case    SND_PCM_FORMAT_S24_LE:
        if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
            snd_codec_update_bits(codec, SUNXI_DAC_FIFOC,
                (3 << FIFO_MODE), (0 << FIFO_MODE));
            snd_codec_update_bits(codec, SUNXI_DAC_FIFOC,
                (1 << TX_SAMPLE_BITS), (1 << TX_SAMPLE_BITS));
        } else {
            snd_codec_update_bits(codec, SUNXI_ADC_FIFOC,
                (1 << RX_FIFO_MODE), (0 << RX_FIFO_MODE));
            snd_codec_update_bits(codec, SUNXI_ADC_FIFOC,
                (1 << RX_SAMPLE_BITS), (1 << RX_SAMPLE_BITS));
        }
        break;
    default:
        break;
    }

    for (i = 0; i < ARRAY_SIZE(sample_rate_conv); i++) {
        if (sample_rate_conv[i].samplerate == params_rate(params)) {
            if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
                snd_codec_update_bits(codec, SUNXI_DAC_FIFOC,
                    (0x7 << DAC_FS),
                    (sample_rate_conv[i].rate_bit << DAC_FS));
            } else {
                if (sample_rate_conv[i].samplerate > 48000)
                    return -EINVAL;
                snd_codec_update_bits(codec, SUNXI_ADC_FIFOC,
                    (0x7 << ADC_FS),
                    (sample_rate_conv[i].rate_bit<<ADC_FS));
            }
        }
    }

    /* reset the adchpf func setting for different sampling */
    if (substream->stream == SNDRV_PCM_STREAM_CAPTURE) {
        if (codec_param->adchpf_cfg) {
            if (params_rate(params) == 16000) {

                snd_codec_write(codec, SUNXI_ADC_DRC_HHPFC,
                        (0x00F623A5 >> 16) & 0xFFFF);

                snd_codec_write(codec, SUNXI_ADC_DRC_LHPFC,
                            0x00F623A5 & 0xFFFF);

            } else if (params_rate(params) == 44100) {

                snd_codec_write(codec, SUNXI_ADC_DRC_HHPFC,
                        (0x00FC60DB >> 16) & 0xFFFF);

                snd_codec_write(codec, SUNXI_ADC_DRC_LHPFC,
                            0x00FC60DB & 0xFFFF);
            } else {
                snd_codec_write(codec, SUNXI_ADC_DRC_HHPFC,
                        (0x00FCABB3 >> 16) & 0xFFFF);

                snd_codec_write(codec, SUNXI_ADC_DRC_LHPFC,
                            0x00FCABB3 & 0xFFFF);
            }
        }
    }

    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
        switch (params_channels(params)) {
        case 1:
            snd_codec_update_bits(codec, SUNXI_DAC_FIFOC,
                    (1<<DAC_MONO_EN), 1<<DAC_MONO_EN);
            break;
        case 2:
            snd_codec_update_bits(codec, SUNXI_DAC_FIFOC,
                    (1<<DAC_MONO_EN), (0<<DAC_MONO_EN));
            break;
        default:
            snd_err("cannot support the channels:%u.\n",
                params_channels(params));
            return -EINVAL;
        }
    } else {
        switch (params_channels(params)) {
        case 1:
            snd_codec_update_bits(codec, SUNXI_ADC_FIFOC,
                    (0xf<<ADC_CHAN_SEL), (1<<ADC_CHAN_SEL));
            break;
        default:
            snd_err("capture only  support 1 channel\n");
            return -EINVAL;
        }
    }

    return 0;
}

static int sunxi_codec_set_sysclk(struct snd_dai *dai,
        int clk_id, unsigned int freq, int dir)
{
    struct snd_codec *codec = dai->component;
    struct sunxi_codec_info *sunxi_codec = codec->private_data;

    snd_print("\n");
    if (hal_clk_set_rate(sunxi_codec->pllclk, freq)) {
        snd_err("set pllclk rate %u failed\n", freq);
        return -EINVAL;
    }

    return 0;
}

static void sunxi_codec_shutdown(struct snd_pcm_substream *substream,
        struct snd_dai *dai)
{
    struct snd_codec *codec = dai->component;
    struct sunxi_codec_info *sunxi_codec = codec->private_data;
    struct sunxi_codec_param *param = &sunxi_codec->param;

    snd_print("\n");
    /*
     * Playback:
     * Playback --> DACL --> DACL_SINGLE --> LINEOUTL --> External Speaker
     * Playback --> DACL --> DACL_DIFFER --> LINEOUTL --> External Speaker
     *
     * Capture:
     * Capture <-- ADCL <-- Left Input Mixer <-- MIC1 PGA <-- MIC1 <-- MainMic Bias
     * Capture <-- ADCL <-- Left Input Mixer <-- LINEINL PGA <-- LINEINL <-- MainMic Bias
     *
     */
    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
        if (param->gpio_spk > 0)
            hal_gpio_set_data(param->gpio_spk, 0);

        /* LINEOUT */
        snd_codec_update_bits(codec, SUNXI_DAC_ANA_CTL,
                (0x1<<LINEOUTL_EN), (0x0<<LINEOUTL_EN));

        snd_codec_update_bits(codec, SUNXI_DAC_ANA_CTL,
                (0x1<<DACLMUTE), (0x0<<DACLMUTE));

        /* digital DAC enable */
        snd_codec_update_bits(codec, SUNXI_DAC_DPC,
                (0x1<<EN_DAC), (0x0<<EN_DAC));

        /* analog DAC enable */
        snd_codec_update_bits(codec, SUNXI_DAC_ANA_CTL,
                (0x1<<DACLEN), (0x0<<DACLEN));
    } else {
        /* MainMic Bias */
        snd_codec_update_bits(codec, SUNXI_MICBIAS_ANA_CTL,
                (0x1<<MMICBIASEN), (0x0<MMICBIASEN));

        /* MIC PGA */
        snd_codec_update_bits(codec, SUNXI_ADCL_ANA_CTL,
                (0x1<<MIC1AMPEN), (0x0<<MIC1AMPEN));

        /* digital ADC enable */
        snd_codec_update_bits(codec, SUNXI_ADCL_ANA_CTL,
                (0x1<<EN_AD), (0x0<<EN_AD));

        /* analog ADCL enable */
        snd_codec_update_bits(codec, SUNXI_ADCL_ANA_CTL,
                (0x1<<ADCLEN), (0x0<<ADCLEN));
    }

    return;
}

static int sunxi_codec_prepare(struct snd_pcm_substream *substream,
        struct snd_dai *dai)
{
    struct snd_codec *codec = dai->component;

    snd_print("\n");

    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
        snd_codec_update_bits(codec, SUNXI_DAC_FIFOC,
            (1 << FIFO_FLUSH), (1 << FIFO_FLUSH));
        snd_codec_write(codec, SUNXI_DAC_FIFOS,
            (1 << DAC_TXE_INT | 1 << DAC_TXU_INT | 1 << DAC_TXO_INT));
        snd_codec_write(codec, SUNXI_DAC_CNT, 0);
    } else {
        snd_codec_update_bits(codec, SUNXI_ADC_FIFOC,
                (1 << ADC_FIFO_FLUSH), (1 << ADC_FIFO_FLUSH));
        snd_codec_write(codec, SUNXI_ADC_FIFOS,
                (1 << ADC_RXA_INT | 1 << ADC_RXO_INT));
        snd_codec_write(codec, SUNXI_ADC_CNT, 0);
    }

    return 0;
}

static int sunxi_codec_trigger(struct snd_pcm_substream *substream,
        int cmd, struct snd_dai *dai)
{
    struct snd_codec *codec = dai->component;
    struct sunxi_codec_info *sunxi_codec = codec->private_data;
    unsigned int sync_mode = 0;
    int adc_sync_flag = 0;
    uint32_t __cpsr;

    snd_print("\n");
    switch (cmd) {
    case SNDRV_PCM_TRIGGER_START:
    case SNDRV_PCM_TRIGGER_RESUME:
    case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
        if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
            snd_codec_update_bits(codec, SUNXI_DAC_FIFOC,
                (1 << DAC_DRQ_EN), (1 << DAC_DRQ_EN));
        }
        else if (substream->stream == SNDRV_PCM_STREAM_CAPTURE) {
#ifndef SUNXI_ADC_DAUDIO_SYNC
            snd_codec_update_bits(codec, SUNXI_ADC_FIFOC,
                (1 << ADC_DRQ_EN), (1 << ADC_DRQ_EN));
#else
            __cpsr = hal_spin_lock_irqsave();
            sync_mode = sunxi_codec_get_pcm_trigger_substream_mode();
            if (sync_mode) {
                adc_sync_flag = sunxi_codec_get_pcm_adc_sync_flag();
                adc_sync_flag |= (0x1 << ADC_CODEC_SYNC);
                if (adc_sync_flag & (0x1 << ADC_I2S_RUNNING)) {
                    sunxi_cpudai_adc_drq_enable(true);
                } else if ((adc_sync_flag & (0x1 << ADC_CODEC_SYNC)) &&
                        (adc_sync_flag & (0x1 << ADC_I2S_SYNC))) {
                    adc_sync_flag |= (0x1 << ADC_I2S_RUNNING);
                    sunxi_cpudai_adc_drq_enable(true);
                    sunxi_daudio_rx_drq_enable(true);
                }
                sunxi_codec_set_pcm_adc_sync_flag(adc_sync_flag);
            } else
                sunxi_cpudai_adc_drq_enable(true);
            hal_spin_unlock_irqrestore(__cpsr);
#endif
        }
        break;
    case SNDRV_PCM_TRIGGER_STOP:
    case SNDRV_PCM_TRIGGER_SUSPEND:
    case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
        if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
            snd_codec_update_bits(codec, SUNXI_DAC_FIFOC,
                (1 << DAC_DRQ_EN), (0 << DAC_DRQ_EN));
        }
        else if (substream->stream == SNDRV_PCM_STREAM_CAPTURE) {
#ifndef SUNXI_ADC_DAUDIO_SYNC
            snd_codec_update_bits(codec, SUNXI_ADC_FIFOC,
                (1 << ADC_DRQ_EN), (0 << ADC_DRQ_EN));
#else
            __cpsr = hal_spin_lock_irqsave();
            adc_sync_flag = sunxi_codec_get_pcm_adc_sync_flag();
            adc_sync_flag &= ~(0x1 << ADC_CODEC_SYNC);
            if (!((adc_sync_flag >> ADC_CODEC_SYNC) & 0x1) &&
                    (!((adc_sync_flag >> ADC_I2S_SYNC) & 0x1))) {
                adc_sync_flag &= ~(0x1 << ADC_I2S_RUNNING);
            }
            sunxi_codec_set_pcm_adc_sync_flag(adc_sync_flag);
            sunxi_cpudai_adc_drq_enable(false);
            hal_spin_unlock_irqrestore(__cpsr);
#endif
        }
        break;
    default:
        return -EINVAL;
    }

    return 0;
}

static struct snd_dai_ops sun8iw19_codec_dai_ops = {
    .startup    = sunxi_codec_startup,
    .hw_params  = sunxi_codec_hw_params,
    .shutdown   = sunxi_codec_shutdown,
    .set_sysclk = sunxi_codec_set_sysclk,
    .trigger    = sunxi_codec_trigger,
    .prepare    = sunxi_codec_prepare,
    .dapm_control   = sunxi_codec_dapm_control,
};

static struct snd_dai sun8iw19_codec_dai[] = {
    {
        .name   = "sun8iw19codec",
        .playback = {
            .stream_name = "Playback",
            .channels_min = 1,
            .channels_max = 2,
            .rates  = SNDRV_PCM_RATE_8000_192000
                | SNDRV_PCM_RATE_KNOT,
            .formats = SNDRV_PCM_FMTBIT_S16_LE
                | SNDRV_PCM_FMTBIT_S24_LE,
            .rate_min       = 8000,
            .rate_max       = 192000,
        },
        .capture = {
            .stream_name = "Capture",
            .channels_min = 1,
            .channels_max = 1,
            .rates = SNDRV_PCM_RATE_8000_48000
                | SNDRV_PCM_RATE_KNOT,
            .formats = SNDRV_PCM_FMTBIT_S16_LE
                | SNDRV_PCM_FMTBIT_S24_LE,
            .rate_min       = 8000,
            .rate_max       = 48000,
        },
        .ops = &sun8iw19_codec_dai_ops,
    },
};

static int sun8iw19_codec_probe(struct snd_codec *codec)
{
    struct sunxi_codec_info *sunxi_codec = NULL;

    if (!codec->codec_dai)
        return -1;

    sunxi_codec = snd_malloc(sizeof(struct sunxi_codec_info));
    if (!sunxi_codec) {
        snd_err("no memory\n");
        return -ENOMEM;
    }

    codec->private_data = (void *)sunxi_codec;

    snd_print("codec para init\n");
    /* get codec para from board config? */
    sunxi_codec->param = default_param;
    codec->codec_base_addr = (void *)SUNXI_CODEC_BASE_ADDR;
    codec->codec_dai->component = codec;

    sunxi_codec->pllclk = HAL_CLK_PLL_AUDIO;
    sunxi_codec->moduleclk = HAL_CLK_PERIPH_AUDIOCODEC_1X;

    hal_clk_set_parent(sunxi_codec->moduleclk, sunxi_codec->pllclk);
    hal_clock_enable(sunxi_codec->pllclk);
    hal_clock_enable(sunxi_codec->moduleclk);

    sunxi_codec_init(codec);
#ifdef SUNXI_ADC_DAUDIO_SYNC
    adc_daudio_sync_codec = codec;
#endif

    return 0;
}

static int sun8iw19_codec_remove(struct snd_codec *codec)
{
    struct sunxi_codec_info *sunxi_codec = codec->private_data;
    struct sunxi_codec_param *param = &sunxi_codec->param;

    if (param->adcdrc_cfg)
        adcdrc_enable(codec, 0);
    if (param->adchpf_cfg)
        adchpf_enable(codec, 0);
    if (param->dacdrc_cfg)
        dacdrc_enable(codec, 0);
    if (param->dachpf_cfg)
        dachpf_enable(codec, 0);

    hal_clock_disable(sunxi_codec->moduleclk);
    hal_clock_disable(sunxi_codec->pllclk);

    snd_free(sunxi_codec);
    codec->private_data = NULL;

    return 0;
}

struct snd_codec sunxi_audiocodec = {
    .name       = "audiocodec",
    .codec_dai  = sun8iw19_codec_dai,
    .codec_dai_num  = ARRAY_SIZE(sun8iw19_codec_dai),
    .private_data   = NULL,
    .probe      = sun8iw19_codec_probe,
    .remove     = sun8iw19_codec_remove,
    .controls       = sunxi_codec_controls,
    .num_controls   = ARRAY_SIZE(sunxi_codec_controls),
};

