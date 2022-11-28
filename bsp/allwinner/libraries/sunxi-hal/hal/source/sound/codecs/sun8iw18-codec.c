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
#include <sound/pcm_common.h>
#include <aw_common.h>
#include <hal_timer.h>
#include <sound/snd_dma.h>
#include <sound/dma_wrap.h>
#include <hal_dma.h>

#include "sunxi-codec.h"
#include "hal_clk.h"
#include "hal_gpio.h"
#include "sun8iw18-codec.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x)   (sizeof(x)/sizeof((x)[0]))
#endif

#define SUNXI_AUDIOCODEC_REG_DEBUG
#ifdef SUNXI_AUDIOCODEC_REG_DEBUG
struct snd_codec sun8iw18_codec;
#define REG_LABEL(constant)     {#constant, constant}
#define REG_LABEL_END           {NULL, 0}

struct audiocodec_label {
    const char *name;
    const unsigned int address;
    /*int value;*/
} reg_labels[] = {
    REG_LABEL(SUNXI_DAC_DPC),
        REG_LABEL(SUNXI_DAC_FIFO_CTL),
        REG_LABEL(SUNXI_DAC_FIFO_STA),
        REG_LABEL(SUNXI_DAC_CNT),
        REG_LABEL(SUNXI_DAC_DG),
        REG_LABEL(SUNXI_ADC_FIFO_CTL),
        REG_LABEL(SUNXI_ADC_FIFO_STA),
        REG_LABEL(SUNXI_ADC_CNT),
        REG_LABEL(SUNXI_ADC_DG),
        REG_LABEL(SUNXI_DAC_DAP_CTL),
        REG_LABEL(SUNXI_ADC_DAP_CTL),

        REG_LABEL(SUNXI_HP_CTL),
        REG_LABEL(SUNXI_MIX_DAC_CTL),
        REG_LABEL(SUNXI_LINEOUT_CTL0),
        REG_LABEL(SUNXI_LINEOUT_CTL1),
        REG_LABEL(SUNXI_MIC1_CTL),
        REG_LABEL(SUNXI_MIC2_MIC3_CTL),

        REG_LABEL(SUNXI_LADCMIX_SRC),
        REG_LABEL(SUNXI_RADCMIX_SRC),
        REG_LABEL(SUNXI_XADCMIX_SRC),
        REG_LABEL(SUNXI_ADC_CTL),
        REG_LABEL(SUNXI_MBIAS_CTL),
        REG_LABEL(SUNXI_APT_REG),

    REG_LABEL(SUNXI_OP_BIAS_CTL0),
        REG_LABEL(SUNXI_OP_BIAS_CTL1),
        REG_LABEL(SUNXI_ZC_VOL_CTL),
        REG_LABEL(SUNXI_BIAS_CAL_CTRL),
        REG_LABEL_END,
};

void sunxi_audiocodec_reg_dump(void)
{
    struct snd_codec *codec = &sun8iw18_codec;
    int i = 0;

    while (reg_labels[i].name != NULL) {
        printf("%-20s[0x%03x]: 0x%-10x\n",
            reg_labels[i].name,
            reg_labels[i].address,
            snd_codec_read(codec, reg_labels[i].address));
        i++;
    }

    return;
}
#else
void sunxi_audiocodec_reg_dump(void)
{
    return ;
}
#endif

static int sunxi_spk_gpio_get_data(struct snd_kcontrol *kcontrol,
                struct snd_ctl_info *info)
{
    struct snd_codec *codec = kcontrol->private_data;
    struct sunxi_codec_info *sunxi_codec = codec->private_data;

    if (sunxi_codec->param.gpio_spk > 0) {
        hal_gpio_get_data(sunxi_codec->param.gpio_spk,
                    (gpio_data_t *)&info->value);
        snd_print("get spk value:%u\n", info->value);
        info->id = kcontrol->id;
        info->name = kcontrol->name;
        info->min = kcontrol->min;
        info->max = kcontrol->max;
        return 0;
    }

    return -1;
}

static int sunxi_spk_gpio_set_data(struct snd_kcontrol *kcontrol, unsigned long val)
{
    struct snd_codec *codec = kcontrol->private_data;
    struct sunxi_codec_info *sunxi_codec = codec->private_data;
    if (val != GPIO_DATA_LOW && val != GPIO_DATA_HIGH)
        return -1;
    if (sunxi_codec->param.gpio_spk > 0) {
        hal_gpio_set_direction(sunxi_codec->param.gpio_spk, GPIO_DIRECTION_OUTPUT);
        hal_gpio_set_data(sunxi_codec->param.gpio_spk, (gpio_data_t)val);
        snd_print("set spk value:%u\n", val);
        return 0;
    }

    return -1;
}

static const char * const codec_format_function[] = {
            "hub_disable", "hub_enable"};

static struct snd_kcontrol sunxi_codec_controls[] = {
    SND_CTL_KCONTROL("digital volume", SUNXI_DAC_DPC, DVOL, 0x3F),
    SND_CTL_KCONTROL("MIC1 gain volume", SUNXI_MIC1_CTL, MIC1BOOST, 0x7),
    SND_CTL_KCONTROL("MIC2 gain volume", SUNXI_MIC2_MIC3_CTL, MIC2BOOST, 0x7),
    SND_CTL_KCONTROL("MIC3 gain volume", SUNXI_MIC2_MIC3_CTL, MIC3BOOST, 0x7),
    SND_CTL_KCONTROL("ADC gain volume", SUNXI_ADC_CTL, ADCG, 0x7),
    SND_CTL_KCONTROL("LINEOUT volume", SUNXI_LINEOUT_CTL1, LINEOUT_VOL, 0x1f),
    SND_CTL_KCONTROL_EXT("Spk PA Switch", 1, 0,
                    sunxi_spk_gpio_get_data,
                    sunxi_spk_gpio_set_data),

    SND_CTL_KCONTROL("Left Input Mixer DACL Switch", SUNXI_LADCMIX_SRC, LADC_DACL, 1),
    SND_CTL_KCONTROL("Left Input Mixer MIC1 Boost Switch", SUNXI_LADCMIX_SRC, LADC_MIC1_STAGE, 1),
    SND_CTL_KCONTROL("Left Input Mixer MIC2 Boost Switch", SUNXI_LADCMIX_SRC, LADC_MIC2_STAGE, 1),
    SND_CTL_KCONTROL("Left Input Mixer MIC3 Boost Switch", SUNXI_LADCMIX_SRC, LADC_MIC3_STAGE, 1),
    SND_CTL_KCONTROL("Right Input Mixer DACL Switch", SUNXI_RADCMIX_SRC, RADC_DACL, 1),
    SND_CTL_KCONTROL("Right Input Mixer MIC1 Boost Switch", SUNXI_RADCMIX_SRC, RADC_MIC1_STAGE, 1),
    SND_CTL_KCONTROL("Right Input Mixer MIC2 Boost Switch", SUNXI_RADCMIX_SRC, RADC_MIC2_STAGE, 1),
    SND_CTL_KCONTROL("Right Input Mixer MIC3 Boost Switch", SUNXI_RADCMIX_SRC, RADC_MIC3_STAGE, 1),
    SND_CTL_KCONTROL("Xadc Input Mixer DACL Switch", SUNXI_XADCMIX_SRC, XADC_DACL, 1),
    SND_CTL_KCONTROL("Xadc Input Mixer MIC1 Boost Switch", SUNXI_XADCMIX_SRC, XADC_MIC1_STAGE, 1),
    SND_CTL_KCONTROL("Xadc Input Mixer MIC2 Boost Switch", SUNXI_XADCMIX_SRC, XADC_MIC2_STAGE, 1),
    SND_CTL_KCONTROL("Xadc Input Mixer MIC3 Boost Switch", SUNXI_XADCMIX_SRC, XADC_MIC3_STAGE, 1),

    SND_CTL_KCONTROL("Left LINEOUT Mux", SUNXI_LINEOUT_CTL0, LINEOUTL_SRC, 1),
    SND_CTL_KCONTROL("Right LINEOUT Mux", SUNXI_LINEOUT_CTL0, LINEOUTR_SRC, 1),
    SND_CTL_ENUM("sunxi codec audio hub mode",
        ARRAY_SIZE(codec_format_function), codec_format_function,
        SUNXI_DAC_DPC, DAC_HUB_EN),
    SND_CTL_KCONTROL_USER("Soft Volume Master", 255, 0, 255),
};

static void adchpf_config(struct snd_codec *codec)
{
    snd_codec_write(codec, AC_ADC_DRC_HHPFC, (0xFFFAC1 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_ADC_DRC_LHPFC, 0xFFE644 & 0xFFFF);
}

static void adchpf_enable(struct snd_codec *codec, bool on)
{
    if (on) {
        snd_codec_update_bits(codec, SUNXI_ADC_DAP_CTL,
            (0x1 << ADC_HPF0_EN | 0x1 << ADC_HPF1_EN),
            (0x1 << ADC_HPF0_EN | 0x1 << ADC_HPF1_EN));
        snd_codec_update_bits(codec, SUNXI_ADC_DAP_CTL,
            (0x1 << ADC_DAP0_EN | 0x1 << ADC_DAP1_EN),
            (0x1 << ADC_DAP0_EN | 0x1 << ADC_DAP1_EN));
    } else {
        snd_codec_update_bits(codec, SUNXI_ADC_DAP_CTL,
            (0x1 << ADC_HPF0_EN | 0x1 << ADC_HPF1_EN),
            (0x0 << ADC_HPF0_EN | 0x0 << ADC_HPF1_EN));
        snd_codec_update_bits(codec, SUNXI_ADC_DAP_CTL,
            (0x1 << ADC_DAP0_EN | 0x1 << ADC_DAP1_EN),
            (0x0 << ADC_DAP0_EN | 0x0 << ADC_DAP1_EN));
    }
}

static void adcdrc_config(struct snd_codec *codec)
{
    /* Left peak filter attack time */
    snd_codec_write(codec, AC_ADC_DRC_LPFHAT, (0x000B77BF >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_ADC_DRC_LPFLAT, 0x000B77BF & 0xFFFF);
    /* Right peak filter attack time */
    snd_codec_write(codec, AC_ADC_DRC_RPFHAT, (0x000B77BF >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_ADC_DRC_RPFLAT, 0x000B77BF & 0xFFFF);
    /* Left peak filter release time */
    snd_codec_write(codec, AC_ADC_DRC_LPFHRT, (0x00FFE1F8 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_ADC_DRC_LPFLRT, 0x00FFE1F8 & 0xFFFF);
    /* Right peak filter release time */
    snd_codec_write(codec, AC_ADC_DRC_RPFHRT, (0x00FFE1F8 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_ADC_DRC_RPFLRT, 0x00FFE1F8 & 0xFFFF);

    /* Left RMS filter attack time */
    snd_codec_write(codec, AC_ADC_DRC_LPFHAT, (0x00012BAF >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_ADC_DRC_LPFLAT, 0x00012BAF & 0xFFFF);
    /* Right RMS filter attack time */
    snd_codec_write(codec, AC_ADC_DRC_RPFHAT, (0x00012BAF >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_ADC_DRC_RPFLAT, 0x00012BAF & 0xFFFF);

    /* smooth filter attack time */
    snd_codec_write(codec, AC_ADC_DRC_SFHAT, (0x00025600 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_ADC_DRC_SFLAT, 0x00025600 & 0xFFFF);
    /* gain smooth filter release time */
    snd_codec_write(codec, AC_ADC_DRC_SFHRT, (0x00000F04 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_ADC_DRC_SFLRT, 0x00000F04 & 0xFFFF);

    /* OPL */
    snd_codec_write(codec, AC_ADC_DRC_HOPL, (0xFBD8FBA7 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_ADC_DRC_LOPL, 0xFBD8FBA7 & 0xFFFF);
    /* OPC */
    snd_codec_write(codec, AC_ADC_DRC_HOPC, (0xF95B2C3F >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_ADC_DRC_LOPC, 0xF95B2C3F & 0xFFFF);
    /* OPE */
    snd_codec_write(codec, AC_ADC_DRC_HOPE, (0xF45F8D6E >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_ADC_DRC_LOPE, 0xF45F8D6E & 0xFFFF);
    /* LT */
    snd_codec_write(codec, AC_ADC_DRC_HLT, (0x01A934F0 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_ADC_DRC_LLT, 0x01A934F0 & 0xFFFF);
    /* CT */
    snd_codec_write(codec, AC_ADC_DRC_HCT, (0x06A4D3C0 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_ADC_DRC_LCT, 0x06A4D3C0 & 0xFFFF);
    /* ET */
    snd_codec_write(codec, AC_ADC_DRC_HET, (0x0BA07291 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_ADC_DRC_LET, 0x0BA07291 & 0xFFFF);
    /* Ki */
    snd_codec_write(codec, AC_ADC_DRC_HKI, (0x00051EB8 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_ADC_DRC_LKI, 0x00051EB8 & 0xFFFF);
    /* Kc */
    snd_codec_write(codec, AC_ADC_DRC_HKC, (0x00800000 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_ADC_DRC_LKC, 0x00800000 & 0xFFFF);
    /* Kn */
    snd_codec_write(codec, AC_ADC_DRC_HKN, (0x01000000 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_ADC_DRC_LKN, 0x01000000 & 0xFFFF);
    /* Ke */
    snd_codec_write(codec, AC_ADC_DRC_HKE, (0x0000F45F >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_ADC_DRC_LKE, 0x0000F45F & 0xFFFF);
}

static void adcdrc_enable(struct snd_codec *codec, bool on)
{
    if (on) {
        snd_codec_update_bits(codec, SUNXI_ADC_DAP_CTL,
            (0x1 << ADC_DRC0_EN | 0x1 << ADC_DRC1_EN),
            (0x1 << ADC_DRC0_EN | 0x1 << ADC_DRC1_EN));
        snd_codec_update_bits(codec, SUNXI_ADC_DAP_CTL,
            (0x1 << ADC_DAP0_EN | 0x1 << ADC_DAP1_EN),
            (0x1 << ADC_DAP0_EN | 0x1 << ADC_DAP1_EN));
    } else {
        snd_codec_update_bits(codec, SUNXI_ADC_DAP_CTL,
            (0x1 << ADC_DAP0_EN | 0x1 << ADC_DAP1_EN),
            (0x0 << ADC_DAP0_EN | 0x0 << ADC_DAP1_EN));
        snd_codec_update_bits(codec, SUNXI_ADC_DAP_CTL,
            (0x1 << ADC_DRC0_EN | 0x1 << ADC_DRC1_EN),
            (0x0 << ADC_DRC0_EN | 0x0 << ADC_DRC1_EN));
    }
}

static void dachpf_config(struct snd_codec *codec)
{
    /* HPF */
    snd_codec_write(codec, AC_DAC_DRC_HHPFC, (0xFFFAC1 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_DAC_DRC_LHPFC, 0xFFFAC1 & 0xFFFF);
}

static void dachpf_enable(struct snd_codec *codec, bool on)
{
    if (on) {
        snd_codec_update_bits(codec, SUNXI_DAC_DAP_CTL,
            (0x1 << DDAP_HPF_EN),
            (0x1 << DDAP_HPF_EN));

        snd_codec_update_bits(codec, SUNXI_DAC_DAP_CTL,
            (0x1 << DDAP_EN),
            (0x1 << DDAP_EN));
    } else {
        snd_codec_update_bits(codec, SUNXI_DAC_DAP_CTL,
            (0x1 << DDAP_EN),
            (0x0 << DDAP_EN));

        snd_codec_update_bits(codec, SUNXI_DAC_DAP_CTL,
            (0x1 << DDAP_HPF_EN),
            (0x0 << DDAP_HPF_EN));
    }
}

static void dacdrc_config(struct snd_codec *codec)
{
    /* Left peak filter attack time */
    snd_codec_write(codec, AC_DAC_DRC_LPFHAT, (0x000B77BF >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_DAC_DRC_LPFLAT, 0x000B77BF & 0xFFFF);
    /* Right peak filter attack time */
    snd_codec_write(codec, AC_DAC_DRC_RPFHAT, (0x000B77BF >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_DAC_DRC_RPFLAT, 0x000B77BF & 0xFFFF);
    /* Left peak filter release time */
    snd_codec_write(codec, AC_DAC_DRC_LPFHRT, (0x00FFE1F8 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_DAC_DRC_LPFLRT, 0x00FFE1F8 & 0xFFFF);
    /* Right peak filter release time */
    snd_codec_write(codec, AC_DAC_DRC_RPFHRT, (0x00FFE1F8 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_DAC_DRC_RPFLRT, 0x00FFE1F8 & 0xFFFF);

    /* Left RMS filter attack time */
    snd_codec_write(codec, AC_DAC_DRC_LPFHAT, (0x00012BAF >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_DAC_DRC_LPFLAT, 0x00012BAF & 0xFFFF);
    /* Right RMS filter attack time */
    snd_codec_write(codec, AC_DAC_DRC_RPFHAT, (0x00012BAF >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_DAC_DRC_RPFLAT, 0x00012BAF & 0xFFFF);

    /* smooth filter attack time */
    snd_codec_write(codec, AC_DAC_DRC_SFHAT, (0x00025600 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_DAC_DRC_SFLAT, 0x00025600 & 0xFFFF);
    /* gain smooth filter release time */
    snd_codec_write(codec, AC_DAC_DRC_SFHRT, (0x00000F04 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_DAC_DRC_SFLRT, 0x00000F04 & 0xFFFF);

    /* OPL */
    snd_codec_write(codec, AC_DAC_DRC_HOPL, (0xFBD8FBA7 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_DAC_DRC_LOPL, 0xFBD8FBA7 & 0xFFFF);
    /* OPC */
    snd_codec_write(codec, AC_DAC_DRC_HOPC, (0xF95B2C3F >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_DAC_DRC_LOPC, 0xF95B2C3F & 0xFFFF);
    /* OPE */
    snd_codec_write(codec, AC_DAC_DRC_HOPE, (0xF45F8D6E >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_DAC_DRC_LOPE, 0xF45F8D6E & 0xFFFF);
    /* LT */
    snd_codec_write(codec, AC_DAC_DRC_HLT, (0x01A934F0 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_DAC_DRC_LLT, 0x01A934F0 & 0xFFFF);
    /* CT */
    snd_codec_write(codec, AC_DAC_DRC_HCT, (0x06A4D3C0 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_DAC_DRC_LCT, 0x06A4D3C0 & 0xFFFF);
    /* ET */
    snd_codec_write(codec, AC_DAC_DRC_HET, (0x0BA07291 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_DAC_DRC_LET, 0x0BA07291 & 0xFFFF);
    /* Ki */
    snd_codec_write(codec, AC_DAC_DRC_HKI, (0x00051EB8 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_DAC_DRC_LKI, 0x00051EB8 & 0xFFFF);
    /* Kc */
    snd_codec_write(codec, AC_DAC_DRC_HKC, (0x00800000 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_DAC_DRC_LKC, 0x00800000 & 0xFFFF);
    /* Kn */
    snd_codec_write(codec, AC_DAC_DRC_HKN, (0x01000000 >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_DAC_DRC_LKN, 0x01000000 & 0xFFFF);
    /* Ke */
    snd_codec_write(codec, AC_DAC_DRC_HKE, (0x0000F45F >> 16) & 0xFFFF);
    snd_codec_write(codec, AC_DAC_DRC_LKE, 0x0000F45F & 0xFFFF);
}

static void dacdrc_enable(struct snd_codec *codec, bool on)
{
    if (on) {
        /* detect noise when ET enable */
        snd_codec_update_bits(codec, AC_DAC_DRC_CTL,
            (0x1 << DAC_DRC_CTL_CONTROL_DRC_EN),
            (0x1 << DAC_DRC_CTL_CONTROL_DRC_EN));
        /* 0x0:RMS filter; 0x1:Peak filter */
        snd_codec_update_bits(codec, AC_DAC_DRC_CTL,
            (0x1 << DAC_DRC_CTL_SIGNAL_FUN_SEL),
            (0x1 << DAC_DRC_CTL_SIGNAL_FUN_SEL));
        /* delay function enable */
        snd_codec_update_bits(codec, AC_DAC_DRC_CTL,
            (0x1 << DAC_DRC_CTL_DEL_FUN_EN),
            (0x0 << DAC_DRC_CTL_DEL_FUN_EN));

        snd_codec_update_bits(codec, AC_DAC_DRC_CTL,
            (0x1 << DAC_DRC_CTL_DRC_LT_EN),
            (0x1 << DAC_DRC_CTL_DRC_LT_EN));
        snd_codec_update_bits(codec, AC_DAC_DRC_CTL,
            (0x1 << DAC_DRC_CTL_DRC_ET_EN),
            (0x1 << DAC_DRC_CTL_DRC_ET_EN));

        snd_codec_update_bits(codec, SUNXI_DAC_DAP_CTL,
            (0x1 << DDAP_DRC_EN),
            (0x1 << DDAP_DRC_EN));

        snd_codec_update_bits(codec, SUNXI_DAC_DAP_CTL,
            (0x1 << DDAP_EN),
            (0x1 << DDAP_EN));
    } else {
        snd_codec_update_bits(codec, SUNXI_DAC_DAP_CTL,
            (0x1 << DDAP_EN),
            (0x0 << DDAP_EN));

        snd_codec_update_bits(codec, SUNXI_DAC_DAP_CTL,
            (0x1 << DDAP_DRC_EN),
            (0x0 << DDAP_DRC_EN));

        /* detect noise when ET enable */
        snd_codec_update_bits(codec, AC_DAC_DRC_CTL,
            (0x1 << DAC_DRC_CTL_CONTROL_DRC_EN),
            (0x0 << DAC_DRC_CTL_CONTROL_DRC_EN));
        /* 0x0:RMS filter; 0x1:Peak filter */
        snd_codec_update_bits(codec, AC_DAC_DRC_CTL,
            (0x1 << DAC_DRC_CTL_SIGNAL_FUN_SEL),
            (0x1 << DAC_DRC_CTL_SIGNAL_FUN_SEL));
        /* delay function enable */
        snd_codec_update_bits(codec, AC_DAC_DRC_CTL,
            (0x1 << DAC_DRC_CTL_DEL_FUN_EN),
            (0x0 << DAC_DRC_CTL_DEL_FUN_EN));

        snd_codec_update_bits(codec, AC_DAC_DRC_CTL,
            (0x1 << DAC_DRC_CTL_DRC_LT_EN),
            (0x0 << DAC_DRC_CTL_DRC_LT_EN));
        snd_codec_update_bits(codec, AC_DAC_DRC_CTL,
            (0x1 << DAC_DRC_CTL_DRC_ET_EN),
            (0x0 << DAC_DRC_CTL_DRC_ET_EN));
    }
}

static int sunxi_codec_init(struct snd_codec *codec)
{
    struct sunxi_codec_info *sunxi_codec = codec->private_data;
    struct sunxi_codec_param *param = &sunxi_codec->param;

    /* Disable DRC function for playback */
    snd_codec_write(codec, SUNXI_DAC_DAP_CTL, 0);
    /* Disable HPF(high passed filter) */
    snd_codec_update_bits(codec, SUNXI_DAC_DPC,
                        (1 << HPF_EN), (0x0 << HPF_EN));
    /* Enable ADCFDT to overcome niose at the beginning */
    snd_codec_update_bits(codec, SUNXI_ADC_FIFO_CTL,
                        (7 << ADCDFEN), (7 << ADCDFEN));
    /* set digital volume */
    snd_codec_update_bits(codec, SUNXI_DAC_DPC,
            (0x3f << DVOL), (param->digital_vol << DVOL));
    /* set LINEOUT volume */
    snd_codec_update_bits(codec, SUNXI_LINEOUT_CTL1,
            (0x1f << LINEOUT_VOL),
            (param->lineout_vol << LINEOUT_VOL));
    /* set MIC2,3 Boost AMP disable */
    snd_codec_write(codec, SUNXI_MIC2_MIC3_CTL, 0x44);
    /* set LADC Mixer mute */
    snd_codec_write(codec, SUNXI_LADCMIX_SRC, 0x0);
    /* MIC1 AMP gain */
    snd_codec_update_bits(codec, SUNXI_MIC1_CTL,
                        0x7 << MIC1BOOST,
                        param->mic1gain << MIC1BOOST);
    /* MIC2,MIC3 AMP gain */
    snd_codec_update_bits(codec, SUNXI_MIC2_MIC3_CTL,
                        0x7 << MIC2BOOST,
                        param->mic2gain << MIC2BOOST);
    snd_codec_update_bits(codec, SUNXI_MIC2_MIC3_CTL,
                        0x7 << MIC3BOOST,
                        param->mic3gain << MIC3BOOST);
    /* adc gain */
    snd_codec_update_bits(codec, SUNXI_ADC_CTL,
                        0x1f << ADCG,
                        param->adcgain << ADCG);

    /* LINEOUT Mux */
    snd_codec_update_bits(codec, SUNXI_LINEOUT_CTL0,
            (0x1<<LINEOUTL_SRC), (0x0<<LINEOUTL_SRC));
    snd_codec_update_bits(codec, SUNXI_LINEOUT_CTL0,
            (0x1<<LINEOUTR_SRC), (0x1<<LINEOUTR_SRC));

    /* Left Input Mixer */
    snd_codec_update_bits(codec, SUNXI_LADCMIX_SRC,
            (0x1<<LADC_MIC1_STAGE), (0x1<<LADC_MIC1_STAGE));
    /* Right Input Mixer */
    snd_codec_update_bits(codec, SUNXI_RADCMIX_SRC,
            (0x1<<RADC_MIC2_STAGE), (0x1<<RADC_MIC2_STAGE));
    /* X Input Mixer */
    snd_codec_update_bits(codec, SUNXI_XADCMIX_SRC,
            (0x1<<XADC_MIC3_STAGE), (0x1<<XADC_MIC3_STAGE));

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

    return 0;
}

static int sun8iw18_codec_probe(struct snd_codec *codec)
{
    struct sunxi_codec_info *sunxi_codec = NULL;
    struct sunxi_codec_param default_param = {
        .digital_vol    = 0x0,
        .lineout_vol    = 0x0a,
        .mic1gain   = 0x4,
        .mic2gain   = 0x4,
        .mic3gain   = 0x0,
        .adcgain    = 0x3,
        .gpio_spk   = GPIOH(9),
        .gpio_spk_power = GPIOH(2),
        .pa_msleep_time = 50,
        .adcdrc_cfg     = 0,
        .adchpf_cfg     = 1,
        .dacdrc_cfg     = 0,
        .dachpf_cfg     = 0,
    };

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
    sunxi_codec->pllclkx4 = HAL_CLK_PLL_AUDIOX4;
    sunxi_codec->moduleclk = HAL_CLK_PERIPH_AUDIOCODEC_1X;

    hal_clk_set_parent(sunxi_codec->moduleclk, sunxi_codec->pllclkx4);
    hal_clock_enable(sunxi_codec->pllclk);
    hal_clock_enable(sunxi_codec->pllclkx4);
    hal_clock_enable(sunxi_codec->moduleclk);

    sunxi_codec_init(codec);

    return 0;
}

static int sun8iw18_codec_remove(struct snd_codec *codec)
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
    hal_clock_disable(sunxi_codec->pllclkx4);
    hal_clock_disable(sunxi_codec->pllclk);

    snd_free(sunxi_codec);
    codec->private_data = NULL;

    return 0;
}

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

static int sunxi_codec_hw_params(struct snd_pcm_substream *substream,
        struct snd_pcm_hw_params *params, struct snd_dai *dai)
{
    struct snd_codec *codec = dai->component;
    int i = 0;

    snd_print("\n");
    switch (params_format(params)) {
    case    SND_PCM_FORMAT_S16_LE:
        if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
            snd_codec_update_bits(codec, SUNXI_DAC_FIFO_CTL,
                (3<<FIFO_MODE), (3<<FIFO_MODE));
            snd_codec_update_bits(codec, SUNXI_DAC_FIFO_CTL,
                (1<<TX_SAMPLE_BITS), (0<<TX_SAMPLE_BITS));
        } else {
            snd_codec_update_bits(codec, SUNXI_ADC_FIFO_CTL,
                (1<<RX_FIFO_MODE), (1<<RX_FIFO_MODE));
            snd_codec_update_bits(codec, SUNXI_ADC_FIFO_CTL,
                (1<<RX_SAMPLE_BITS), (0<<RX_SAMPLE_BITS));
        }
        break;
    case    SND_PCM_FORMAT_S32_LE:
        /* only for the compatible of tinyalsa */
    case    SND_PCM_FORMAT_S24_LE:
        if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
            snd_codec_update_bits(codec, SUNXI_DAC_FIFO_CTL,
                (3<<FIFO_MODE), (0<<FIFO_MODE));
            snd_codec_update_bits(codec, SUNXI_DAC_FIFO_CTL,
                (1<<TX_SAMPLE_BITS), (1<<TX_SAMPLE_BITS));
        } else {
            snd_codec_update_bits(codec, SUNXI_ADC_FIFO_CTL,
                (1<<RX_FIFO_MODE), (0<<RX_FIFO_MODE));
            snd_codec_update_bits(codec, SUNXI_ADC_FIFO_CTL,
                (1<<RX_SAMPLE_BITS), (1<<RX_SAMPLE_BITS));
        }
        break;
    default:
        snd_err("params_format[%d] error!\n", params_format(params));
        return -EINVAL;
    }

    for (i = 0; i < ARRAY_SIZE(sample_rate_conv); i++) {
        if (sample_rate_conv[i].samplerate == params_rate(params)) {
            if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
                snd_codec_update_bits(codec, SUNXI_DAC_FIFO_CTL,
                    (0x7<<DAC_FS),
                    (sample_rate_conv[i].rate_bit<<DAC_FS));
            } else {
                if (sample_rate_conv[i].samplerate > 48000)
                    return -EINVAL;
                snd_codec_update_bits(codec, SUNXI_ADC_FIFO_CTL,
                    (0x7<<ADC_FS),
                    (sample_rate_conv[i].rate_bit<<ADC_FS));
            }
        }
    }
    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
        switch (params_channels(params)) {
        case 1:
            snd_codec_update_bits(codec, SUNXI_DAC_FIFO_CTL,
                    (1<<DAC_MONO_EN), 1<<DAC_MONO_EN);
            break;
        case 2:
            snd_codec_update_bits(codec, SUNXI_DAC_FIFO_CTL,
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
            snd_codec_update_bits(codec, SUNXI_ADC_FIFO_CTL,
                    (0xf<<ADC_CHAN_SEL), (1<<ADC_CHAN_SEL));
            break;
        case 2:
            snd_codec_update_bits(codec, SUNXI_ADC_FIFO_CTL,
                    (0xf<<ADC_CHAN_SEL), (3<<ADC_CHAN_SEL));
            break;
        case 3:
            snd_codec_update_bits(codec, SUNXI_ADC_FIFO_CTL,
                    (0xf<<ADC_CHAN_SEL), (7<<ADC_CHAN_SEL));
            break;
        case 4:
            snd_codec_update_bits(codec, SUNXI_ADC_FIFO_CTL,
                    (0xf<<ADC_CHAN_SEL), (0xf<<ADC_CHAN_SEL));
            break;
        default:
            snd_err("cannot support the channels:%u.\n",
                params_channels(params));
            return -EINVAL;
        }
    }
    return 0;
}

static void sunxi_codec_shutdown(struct snd_pcm_substream *substream,
        struct snd_dai *dai)
{

    return;
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
            snd_codec_update_bits(codec, SUNXI_MIX_DAC_CTL,
                    (0x1<<DACALEN), (0x1<<DACALEN));
            /* digital DAC enable */
            snd_codec_update_bits(codec, SUNXI_DAC_DPC,
                    (0x1<<EN_DAC), (0x1<<EN_DAC));
            /* delay 10ms to avoid digitabl DAC square wave */
            hal_msleep(10);
            /* LINEOUT */
            snd_codec_update_bits(codec, SUNXI_LINEOUT_CTL0,
                (0x1<<LINEOUTL_EN), (0x1<<LINEOUTL_EN));
            snd_codec_update_bits(codec, SUNXI_LINEOUT_CTL0,
                (0x1<<LINEOUTR_EN), (0x1<<LINEOUTR_EN));
            if (param->gpio_spk > 0) {
                hal_gpio_set_direction(param->gpio_spk,
                        GPIO_DIRECTION_OUTPUT);
                hal_gpio_set_data(param->gpio_spk,
                        GPIO_DATA_HIGH);
            }
            if (param->gpio_spk_power > 0) {
                hal_gpio_set_direction(param->gpio_spk_power,
                        GPIO_DIRECTION_OUTPUT);
                hal_gpio_set_data(param->gpio_spk_power,
                        GPIO_DATA_HIGH);
            }
            /* delay to wait PA stable */
            hal_msleep(param->pa_msleep_time);
        } else {
            /* Playback off */
            if (param->gpio_spk > 0) {
                hal_gpio_set_direction(param->gpio_spk,
                        GPIO_DIRECTION_OUTPUT);
                hal_gpio_set_data(param->gpio_spk,
                        GPIO_DATA_LOW);
            }
            if (param->gpio_spk_power > 0) {
                hal_gpio_set_direction(param->gpio_spk_power,
                        GPIO_DIRECTION_OUTPUT);
                hal_gpio_set_data(param->gpio_spk_power,
                        GPIO_DATA_LOW);
            }
            hal_msleep(param->pa_msleep_time);
            /* LINEOUT */
            snd_codec_update_bits(codec, SUNXI_LINEOUT_CTL0,
                (0x1<<LINEOUTL_EN), (0x0<<LINEOUTL_EN));
            snd_codec_update_bits(codec, SUNXI_LINEOUT_CTL0,
                (0x1<<LINEOUTR_EN), (0x0<<LINEOUTR_EN));
            /* digital DAC */
            snd_codec_update_bits(codec, SUNXI_DAC_DPC,
                    (0x1<<EN_DAC), (0x0<<EN_DAC));
            /* analog DAC */
            snd_codec_update_bits(codec, SUNXI_MIX_DAC_CTL,
                    (0x1<<DACALEN), (0x0<<DACALEN));
        }
    } else {
        /*
         * Capture:
         * Capture <-- ADCL <-- Left Input Mixer <-- MIC1 PGA <-- MIC1 <-- MainMic Bias
         * Capture <-- ADCR <-- Right Input Mixer <-- MIC2 PGA <-- MIC2 <-- MainMic Bias
         * Capture <-- ADCX <-- Xadc Input Mixer <-- MIC3 PGA <-- MIC3 <-- MainMic Bias
         *
         */
        unsigned int channels = 0;
        channels = substream->runtime->channels;

        snd_print("channels = %u\n", channels);
        if (onoff) {
            /* Capture on */
            /* digital ADC enable */
#ifndef CONFIG_SND_MULTI_SOUNDCARD
            snd_codec_update_bits(codec, SUNXI_ADC_FIFO_CTL,
                    (0x1<<EN_AD), (0x1<<EN_AD));
#endif
            switch (channels) {
            case 4:
            case 3:
                /* analog ADCX enable */
                snd_codec_update_bits(codec, SUNXI_ADC_CTL,
                        (0x1<<ADCXEN), (0x1<<ADCXEN));
            case 2:
                /* analog ADCR enable */
                snd_codec_update_bits(codec, SUNXI_ADC_CTL,
                        (0x1<<ADCREN), (0x1<<ADCREN));
            case 1:
                /* analog ADCL enable */
                snd_codec_update_bits(codec, SUNXI_ADC_CTL,
                        (0x1<<ADCLEN), (0x1<<ADCLEN));
                break;
            default:
                snd_err("unknown channels:%u\n", channels);
                return -1;
            }
            switch (channels) {
            case 4:
            case 3:
                /* MIC3 PGA */
                snd_codec_update_bits(codec, SUNXI_MIC2_MIC3_CTL,
                    (0x1<<MIC3AMPEN), (0x1<<MIC3AMPEN));
            case 2:
                /* MIC2 PGA */
                snd_codec_update_bits(codec, SUNXI_MIC2_MIC3_CTL,
                    (0x1<<MIC2AMPEN), (0x1<<MIC2AMPEN));
            case 1:
                /* MIC1 PGA */
                snd_codec_update_bits(codec, SUNXI_MIC1_CTL,
                    (0x1<<MIC1AMPEN), (0x1<<MIC1AMPEN));
                break;
            default:
                snd_err("unknown channels:%u\n", channels);
                return -1;
            }
            /* MainMic Bias */
            snd_codec_update_bits(codec, SUNXI_MBIAS_CTL,
                    (0x1<<MMICBIASEN), (0x1<<MMICBIASEN));
        } else {
            /* Capture off */
            /* MainMic Bias */
            snd_codec_update_bits(codec, SUNXI_MBIAS_CTL,
                    (0x1<<MMICBIASEN), (0x0<<MMICBIASEN));
            switch (channels) {
            case 4:
            case 3:
                /* MIC3 PGA */
                snd_codec_update_bits(codec, SUNXI_MIC2_MIC3_CTL,
                    (0x1<<MIC3AMPEN), (0x0<<MIC3AMPEN));
            case 2:
                /* MIC2 PGA */
                snd_codec_update_bits(codec, SUNXI_MIC2_MIC3_CTL,
                    (0x1<<MIC2AMPEN), (0x0<<MIC2AMPEN));
            case 1:
                /* MIC1 PGA */
                snd_codec_update_bits(codec, SUNXI_MIC1_CTL,
                    (0x1<<MIC1AMPEN), (0x0<<MIC1AMPEN));
                break;
            default:
                snd_err("unknown channels:%u\n", channels);
                return -1;
            }
            switch (channels) {
            case 4:
            case 3:
                /* analog ADCX enable */
                snd_codec_update_bits(codec, SUNXI_ADC_CTL,
                        (0x1<<ADCXEN), (0x0<<ADCXEN));
            case 2:
                /* analog ADCR enable */
                snd_codec_update_bits(codec, SUNXI_ADC_CTL,
                        (0x1<<ADCREN), (0x0<<ADCREN));
            case 1:
                /* analog ADCL enable */
                snd_codec_update_bits(codec, SUNXI_ADC_CTL,
                        (0x1<<ADCLEN), (0x0<<ADCLEN));
                break;
            default:
                snd_err("unknown channels:%u\n", channels);
                return -1;
            }
#ifndef CONFIG_SND_MULTI_SOUNDCARD
            /* digital ADC enable */
            snd_codec_update_bits(codec, SUNXI_ADC_FIFO_CTL,
                    (0x1<<EN_AD), (0x0<<EN_AD));
#endif
        }
    }
    substream->dapm_state = onoff;
    return 0;
}

static int sunxi_codec_startup(struct snd_pcm_substream *substream,
        struct snd_dai *dai)
{
    snd_print("\n");

    return 0;
}

static int sunxi_codec_trigger(struct snd_pcm_substream *substream,
        int cmd, struct snd_dai *dai)
{
    struct snd_codec *codec = dai->component;

    snd_print("cmd=%d\n", cmd);
    switch (cmd) {
    case    SNDRV_PCM_TRIGGER_START:
    case    SNDRV_PCM_TRIGGER_RESUME:
    case    SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
        if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
            snd_codec_update_bits(codec,
                    SUNXI_DAC_FIFO_CTL,
                    (1<<DAC_DRQ_EN), (1<<DAC_DRQ_EN));
        else {
#ifndef CONFIG_SND_MULTI_SOUNDCARD
            snd_codec_update_bits(codec,
                    SUNXI_ADC_FIFO_CTL,
                    (1 << ADC_DRQ_EN), (1 << ADC_DRQ_EN));
#endif
        }
        break;
    case    SNDRV_PCM_TRIGGER_STOP:
    case    SNDRV_PCM_TRIGGER_SUSPEND:
    case    SNDRV_PCM_TRIGGER_PAUSE_PUSH:
        if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
            snd_codec_update_bits(codec,
                    SUNXI_DAC_FIFO_CTL,
                    (1 << DAC_DRQ_EN), (0 << DAC_DRQ_EN));
        else {
#ifndef CONFIG_SND_MULTI_SOUNDCARD
            snd_codec_update_bits(codec,
                    SUNXI_ADC_FIFO_CTL,
                    (1 << ADC_DRQ_EN), (0 << ADC_DRQ_EN));
#endif
        }
        break;
    default:
        return -EINVAL;
    }
    return 0;
}

static int sunxi_codec_prepare(struct snd_pcm_substream *substream,
        struct snd_dai *dai)
{
    struct snd_codec *codec = dai->component;

    snd_print("\n");
    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
        snd_codec_update_bits(codec, SUNXI_DAC_FIFO_CTL,
                (1<<FIFO_FLUSH), (1<<FIFO_FLUSH));
        snd_codec_write(codec, SUNXI_DAC_FIFO_STA,
            (1 << DAC_TXE_INT | 1 << DAC_TXU_INT | 1 << DAC_TXO_INT));
        snd_codec_write(codec, SUNXI_DAC_CNT, 0);
    } else {
        snd_codec_update_bits(codec, SUNXI_ADC_FIFO_CTL,
            (1<<ADC_FIFO_FLUSH), (1<<ADC_FIFO_FLUSH));
        snd_codec_write(codec, SUNXI_ADC_FIFO_STA,
            (1 << ADC_RXA_INT | 1 << ADC_RXO_INT));
        snd_codec_write(codec, SUNXI_ADC_CNT, 0);
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

static struct snd_dai_ops sun8iw18_codec_dai_ops = {
    .hw_params  = sunxi_codec_hw_params,
    .shutdown   = sunxi_codec_shutdown,
    .startup    = sunxi_codec_startup,
    .trigger    = sunxi_codec_trigger,
    .prepare    = sunxi_codec_prepare,
    .set_sysclk     = sunxi_codec_set_sysclk,
    .dapm_control   = sunxi_codec_dapm_control,
};

static struct snd_dai sun8iw18_codec_dai[] = {
    {
        .name       = "AC-codecdai",
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
            .channels_max   = 4,
            .rates      = SNDRV_PCM_RATE_8000_48000
                    | SNDRV_PCM_RATE_KNOT,
            .formats    = SNDRV_PCM_FMTBIT_S16_LE
                    | SNDRV_PCM_FMTBIT_S24_LE,
            .rate_min       = 8000,
            .rate_max       = 48000,
        },
        .ops        = &sun8iw18_codec_dai_ops,
    },
};



struct snd_codec sun8iw18_codec = {
    .name       = "audiocodec",
    .codec_dai  = sun8iw18_codec_dai,
    .codec_dai_num  = ARRAY_SIZE(sun8iw18_codec_dai),
    .private_data   = NULL,
    .probe      = sun8iw18_codec_probe,
    .remove     = sun8iw18_codec_remove,
    .read           = sunxi_codec_read,
    .write          = sunxi_codec_write,
    .controls       = sunxi_codec_controls,
    .num_controls   = ARRAY_SIZE(sunxi_codec_controls),
};

#if 0
extern struct snd_platform gAudioCodecPlatform;
struct snd_card gAudioCodec = {
    .name       = "AudioCodec",
    .codec      = &sun8iw18_codec,
    .platform   = &gAudioCodecPlatform,
};
#endif
