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
#include <ctype.h>
#include <getopt.h>
#include <sound/snd_core.h>
#include <sound/snd_pcm.h>
#include <sound/pcm_common.h>
#include <aw_common.h>
#include <unistd.h>
#include "ac108.h"

//test config
#define AC108_KCONTROL_TEST_EN
//add to
#undef AC108_IDLE_RESET_EN

//AC108 SDO2/TX2 Enable (SDO1 has be enabled default)
#define AC108_SDO2_EN           0
#define AC108_DMIC_EN           0   //0:ADC  1:DMIC
#undef AC108_IDLE_RESET_EN          //reset AC108 when in idle time
#define AC108_POWERON_RESET_EN      1   //AC108 poweron soft reset enable
//add to
#undef AC108_POWERON_RESET_EN

#define AC108_REGULATOR_NAME        "regulator_name"
#define AC108_RATES         (SNDRV_PCM_RATE_8000_96000 | SNDRV_PCM_RATE_KNOT)
#define AC108_FORMATS           (SNDRV_PCM_FMTBIT_S16_LE | \
                    SNDRV_PCM_FMTBIT_S20_3LE | \
                    SNDRV_PCM_FMTBIT_S24_LE | \
                    SNDRV_PCM_FMTBIT_S32_LE)

struct real_val_to_reg_val {
    unsigned int real_val;
    unsigned int reg_val;
};

struct pll_div {
    unsigned int freq_in;
    unsigned int freq_out;
    unsigned int m1;
    unsigned int m2;
    unsigned int n;
    unsigned int k1;
    unsigned int k2;
};

#if 0
static const unsigned char ac108_reg_addr_list[] = {
    CHIP_AUDIO_RST,

    //Power Control
    PWR_CTRL1,
    PWR_CTRL2,
    PWR_CTRL3,
    PWR_CTRL4,
    PWR_CTRL5,
    PWR_CTRL6,
    PWR_CTRL7,
    PWR_CTRL8,
    PWR_CTRL9,

    //PLL Configure Control
    PLL_CTRL1,
    PLL_CTRL2,
    PLL_CTRL3,
    PLL_CTRL4,
    PLL_CTRL5,
    PLL_CTRL6,
    PLL_CTRL7,
    PLL_LOCK_CTRL,

    //System Clock Control
    SYSCLK_CTRL,
    MOD_CLK_EN,
    MOD_RST_CTRL,
    DSM_CLK_CTRL,

    //I2S Common Control
    I2S_CTRL,
    I2S_BCLK_CTRL,
    I2S_LRCK_CTRL1,
    I2S_LRCK_CTRL2,
    I2S_FMT_CTRL1,
    I2S_FMT_CTRL2,
    I2S_FMT_CTRL3,

    //I2S TX1 Control
    I2S_TX1_CTRL1,
    I2S_TX1_CTRL2,
    I2S_TX1_CTRL3,
    I2S_TX1_CHMP_CTRL1,
    I2S_TX1_CHMP_CTRL2,
    I2S_TX1_CHMP_CTRL3,
    I2S_TX1_CHMP_CTRL4,

    //I2S TX2 Control
    I2S_TX2_CTRL1,
    I2S_TX2_CTRL2,
    I2S_TX2_CTRL3,
    I2S_TX2_CHMP_CTRL1,
    I2S_TX2_CHMP_CTRL2,
    I2S_TX2_CHMP_CTRL3,
    I2S_TX2_CHMP_CTRL4,

    //I2S RX1 Control
    I2S_RX1_CTRL1,
    I2S_RX1_CHMP_CTRL1,
    I2S_RX1_CHMP_CTRL2,
    I2S_RX1_CHMP_CTRL3,
    I2S_RX1_CHMP_CTRL4,

    //I2S Loopback Debug
    I2S_LPB_DEBUG,

    //ADC Common Control
    ADC_SPRC,
    ADC_DIG_EN,
    DMIC_EN,
    ADC_DSR,
    ADC_FIR,
    ADC_DDT_CTRL,

    //HPF Control
    HPF_EN,
    HPF_COEF_REGH1,
    HPF_COEF_REGH2,
    HPF_COEF_REGL1,
    HPF_COEF_REGL2,
    HPF_GAIN_REGH1,
    HPF_GAIN_REGH2,
    HPF_GAIN_REGL1,
    HPF_GAIN_REGL2,

    //ADC Digital Channel Volume Control
    ADC1_DVOL_CTRL,
    ADC2_DVOL_CTRL,
    ADC3_DVOL_CTRL,
    ADC4_DVOL_CTRL,

    //ADC Digital Mixer Source and Gain Control
    ADC1_DMIX_SRC,
    ADC2_DMIX_SRC,
    ADC3_DMIX_SRC,
    ADC4_DMIX_SRC,

    //ADC Digital Debug Control
    ADC_DIG_DEBUG,

    //I2S Pad Drive Control
    I2S_DAT_PADDRV_CTRL,
    I2S_CLK_PADDRV_CTRL,

    //Analog PGA Control
    ANA_PGA1_CTRL,
    ANA_PGA2_CTRL,
    ANA_PGA3_CTRL,
    ANA_PGA4_CTRL,

    //MIC Offset Control
    MIC_OFFSET_CTRL1,
    MIC_OFFSET_CTRL2,
    MIC1_OFFSET_STATU1,
    MIC1_OFFSET_STATU2,
    MIC2_OFFSET_STATU1,
    MIC2_OFFSET_STATU2,
    MIC3_OFFSET_STATU1,
    MIC3_OFFSET_STATU2,
    MIC4_OFFSET_STATU1,
    MIC4_OFFSET_STATU2,

    //ADC1 Analog Control
    ANA_ADC1_CTRL1,
    ANA_ADC1_CTRL2,
    ANA_ADC1_CTRL3,
    ANA_ADC1_CTRL4,
    ANA_ADC1_CTRL5,
    ANA_ADC1_CTRL6,
    ANA_ADC1_CTRL7,

    //ADC2 Analog Control
    ANA_ADC2_CTRL1,
    ANA_ADC2_CTRL2,
    ANA_ADC2_CTRL3,
    ANA_ADC2_CTRL4,
    ANA_ADC2_CTRL5,
    ANA_ADC2_CTRL6,
    ANA_ADC2_CTRL7,

    //ADC3 Analog Control
    ANA_ADC3_CTRL1,
    ANA_ADC3_CTRL2,
    ANA_ADC3_CTRL3,
    ANA_ADC3_CTRL4,
    ANA_ADC3_CTRL5,
    ANA_ADC3_CTRL6,
    ANA_ADC3_CTRL7,

    //ADC4 Analog Control
    ANA_ADC4_CTRL1,
    ANA_ADC4_CTRL2,
    ANA_ADC4_CTRL3,
    ANA_ADC4_CTRL4,
    ANA_ADC4_CTRL5,
    ANA_ADC4_CTRL6,
    ANA_ADC4_CTRL7,

    //GPIO Configure
    GPIO_CFG1,
    GPIO_CFG2,
    GPIO_DAT,
    GPIO_DRV,
    GPIO_PULL,
    GPIO_INT_CFG,
    GPIO_INT_EN,
    GPIO_INT_STATUS,

    //Misc
    BGTC_DAT,
    BGVC_DAT,
    PRNG_CLK_CTRL,
};
#endif

static const struct real_val_to_reg_val ac108_sample_rate[] = {
    {8000,  0},
    {11025, 1},
    {12000, 2},
    {16000, 3},
    {22050, 4},
    {24000, 5},
    {32000, 6},
    {44100, 7},
    {48000, 8},
    {96000, 9},
};

static const struct real_val_to_reg_val ac108_sample_resolution[] = {
    {8,  1},
    {12, 2},
    {16, 3},
    {20, 4},
    {24, 5},
    {28, 6},
    {32, 7},
};

static const struct real_val_to_reg_val ac108_bclk_div[] = {
    {0,   0},
    {1,   1},
    {2,   2},
    {4,   3},
    {6,   4},
    {8,   5},
    {12,  6},
    {16,  7},
    {24,  8},
    {32,  9},
    {48,  10},
    {64,  11},
    {96,  12},
    {128, 13},
    {176, 14},
    {192, 15},
};

//FOUT =(FIN * N) / [(M1+1) * (M2+1)*(K1+1)*(K2+1)] ;
//M1[0,31],  M2[0,1],  N[0,1023],  K1[0,31],  K2[0,1]
static const struct pll_div ac108_pll_div[] = {
    {400000,   24576000, 0,  0, 983,  7,  1},   //<out: 24.575M>
    {512000,   24576000, 0,  0, 960,  9,  1},   //24576000/48
    {768000,   24576000, 0,  0, 640,  9,  1},   //24576000/32
    {800000,   24576000, 0,  0, 768,  24, 0},
    {1024000,  24576000, 0,  0, 480,  9,  1},   //24576000/24
    {1600000,  24576000, 0,  0, 384,  24, 0},
    {2048000,  24576000, 0,  0, 240,  9,  1},   //24576000/12
    {3072000,  24576000, 0,  0, 160,  9,  1},   //24576000/8
    {4096000,  24576000, 0,  0, 120,  9,  1},   //24576000/6
    {6000000,  24576000, 4,  0, 512,  24, 0},
    {12000000, 24576000, 9,  0, 512,  24, 0},
    {13000000, 24576000, 12, 0, 639,  12, 1},   //<out: 24.577M>
    {15360000, 24576000, 9,  0, 320,  9,  1},
    {16000000, 24576000, 9,  0, 384,  24, 0},
    {19200000, 24576000, 11, 0, 384,  24, 0},
    {19680000, 24576000, 15, 1, 999,  24, 0},   //<out: 24.575M>
    {24000000, 24576000, 9,  0, 256,  24, 0},

    {400000,   22579200, 0,  0, 1016, 8,  1},   //<out: 22.5778M>
    {512000,   22579200, 0,  0, 882,  9,  1},
    {768000,   22579200, 0,  0, 588,  9,  1},
    {800000,   22579200, 0,  0, 508,  8,  1},   //<out: 22.5778M>
    {1024000,  22579200, 0,  0, 441,  9,  1},
    {1600000,  22579200, 0,  0, 254,  8,  1},   //<out: 22.5778M>
    {2048000,  22579200, 1,  0, 441,  9,  1},
    {3072000,  22579200, 2,  0, 441,  9,  1},
    {4096000,  22579200, 3,  0, 441,  9,  1},
    {6000000,  22579200, 5,  0, 429,  18, 0},   //<out: 22.5789M>
    {12000000, 22579200, 11, 0, 429,  18, 0},   //<out: 22.5789M>
    {13000000, 22579200, 12, 0, 429,  18, 0},   //<out: 22.5789M>
    {15360000, 22579200, 14, 0, 441,  9,  1},
    {16000000, 22579200, 24, 0, 882,  24, 0},
    {19200000, 22579200, 4,  0, 147,  24, 0},
    {19680000, 22579200, 13, 1, 771,  23, 0},   //<out: 22.5793M>
    {24000000, 22579200, 24, 0, 588,  24, 0},

    {12288000, 24576000, 9,  0, 400,  9,  1},   //24576000/2
    {11289600, 22579200, 9,  0, 400,  9,  1},   //22579200/2

    {24576000/1,   24576000, 9,  0, 200, 9, 1}, //24576000
    {24576000/4,   24576000, 4,  0, 400, 9, 1}, //6144000
    {24576000/16,  24576000, 0,  0, 320, 9, 1}, //1536000
    {24576000/64,  24576000, 0,  0, 640, 4, 1}, //384000
    {24576000/96,  24576000, 0,  0, 960, 4, 1}, //256000
    {24576000/128, 24576000, 0,  0, 512, 1, 1}, //192000
    {24576000/176, 24576000, 0,  0, 880, 4, 0}, //140000
    {24576000/192, 24576000, 0,  0, 960, 4, 0}, //128000

    {22579200/1,   22579200, 9,  0, 200, 9, 1}, //22579200
    {22579200/4,   22579200, 4,  0, 400, 9, 1}, //5644800
    {22579200/16,  22579200, 0,  0, 320, 9, 1}, //1411200
    {22579200/64,  22579200, 0,  0, 640, 4, 1}, //352800
    {22579200/96,  22579200, 0,  0, 960, 4, 1}, //235200
    {22579200/128, 22579200, 0,  0, 512, 1, 1}, //176400
    {22579200/176, 22579200, 0,  0, 880, 4, 0}, //128290
    {22579200/192, 22579200, 0,  0, 960, 4, 0}, //117600

    {22579200/6,   22579200, 2,  0, 360, 9, 1}, //3763200
    {22579200/8,   22579200, 0,  0, 160, 9, 1}, //2822400
    {22579200/12,  22579200, 0,  0, 240, 9, 1}, //1881600
    {22579200/24,  22579200, 0,  0, 480, 9, 1}, //940800
    {22579200/32,  22579200, 0,  0, 640, 9, 1}, //705600
    {22579200/48,  22579200, 0,  0, 960, 9, 1}, //470400
};

static twi_status_t ac108_init_i2c_device(twi_port_t port)
{
    twi_status_t ret = 0;

    ret = hal_twi_init(port);
    if (ret != TWI_STATUS_OK) {
        snd_err("init i2c err ret=%d.\n", ret);
        return ret;
    }

    return TWI_STATUS_OK;
}

static twi_status_t ac108_deinit_i2c_device(twi_port_t port)
{
    twi_status_t ret = 0;

    ret = hal_twi_uninit(port);
    if (ret != TWI_STATUS_OK) {
        snd_err("init i2c err ret=%d.\n", ret);
        return ret;
    }

    return TWI_STATUS_OK;
}

static twi_status_t ac108_read(struct twi_device *twi_dev,
    unsigned char reg, unsigned char *rt_value)
{
    twi_status_t ret;

    hal_twi_control(twi_dev->bus, I2C_SLAVE, &twi_dev->addr);
    ret = hal_twi_read(twi_dev->bus, reg, rt_value, 1);
    if (ret != TWI_STATUS_OK) {
        snd_err("error = %d [REG-0x%02x]\n", ret, reg);
        return ret;
    }

    return TWI_STATUS_OK;
}

static int ac108_write(struct twi_device *twi_dev,
    unsigned char reg, unsigned char value)
{
    twi_status_t ret;
    twi_msg_t msg;
    unsigned char buf[2] = {reg, value};

    msg.flags = 0;
    msg.addr =  twi_dev->addr;
    msg.len = 2;
    msg.buf = buf;

    ret = hal_twi_control(twi_dev->bus, I2C_RDWR, &msg);
    if (ret != TWI_STATUS_OK) {
        snd_err("error = %d [REG-0x%02x]\n", ret, reg);
        return ret;
    }

    return TWI_STATUS_OK;
}

static int ac108_update_bits(struct twi_device *twi_dev,
    unsigned char reg, unsigned char mask, unsigned char value)
{
    unsigned char val_old = 0;
    unsigned char val_new = 0;

    ac108_read(twi_dev, reg, &val_old);
    val_new = (val_old & ~mask) | (value & mask);
    if (val_new != val_old)
        ac108_write(twi_dev, reg, val_new);

    return 0;
}

static int ac108_multi_chips_write(struct ac108_priv *ac108,
    unsigned char reg, unsigned char value)
{
    unsigned char i;

    for (i = 0; i < ac108->param.chip_num; i++)
        ac108_write(&(ac108->param.twi_dev[i]), reg, value);

    return 0;
}

static int ac108_multi_chips_update_bits(struct ac108_priv *ac108,
        unsigned char reg, unsigned char mask, unsigned char value)
{
    unsigned char i;

    for (i = 0; i < ac108->param.chip_num; i++)
        ac108_update_bits(&(ac108->param.twi_dev[i]), reg, mask, value);

    return 0;
}

#ifdef AC108_KCONTROL_TEST_EN
/* ac108 mixer controls define */
static const char * const adc_digital_src_mux[] = {
    "ADC1_Switch", "ADC2_Switch", "ADC3_Switch", "ADC4_Switch",
};

static const char * const adc12_dmic1_src_mux[] = {
    "ADC12_Switch", "DMIC1_Switch",
};

static const char * const adc34_dmic2_src_mux[] = {
    "ADC34_Switch", "DMIC2_Switch",
};

static const char * const i2s_tx1ch_map_mux[] = {
    "ADC1_Sample_Switch", "ADC2_Sample_Switch",
    "ADC3_Sample_Switch", "ADC4_Sample_Switch",
};

static int ac108_ctl_enum_value_get(struct snd_kcontrol *kcontrol,
                struct snd_ctl_info *info)
{
    unsigned int val = 0;

    if (kcontrol->type != SND_CTL_ELEM_TYPE_ENUMERATED) {
        snd_err("invalid kcontrol type = %d.\n", kcontrol->type);
        return -EINVAL;
    }

    if (kcontrol->private_data_type == SND_MODULE_CODEC) {
        struct snd_codec *codec = kcontrol->private_data;
        struct ac108_priv *ac108 = codec->private_data;
        struct ac108_param *param = &ac108->param;
        ac108_read(&param->twi_dev[0], kcontrol->reg, (unsigned char *)&val);
    } else {
        snd_err("%s invalid kcontrol data type = %d.\n", __func__,
                kcontrol->private_data_type);
    }

    snd_kcontrol_to_snd_ctl_info(kcontrol, info, val);

    return 0;
}

static int ac108_ctl_enum_value_set(struct snd_kcontrol *kcontrol, unsigned long val)
{
    if (kcontrol->type != SND_CTL_ELEM_TYPE_ENUMERATED) {
        snd_err("invalid kcontrol type = %d.\n", kcontrol->type);
        return -EINVAL;
    }

    if (val >= kcontrol->items) {
        snd_err("invalid kcontrol items = %ld.\n", val);
        return -EINVAL;
    }

    if (kcontrol->private_data_type == SND_MODULE_CODEC) {
        struct snd_codec *codec = kcontrol->private_data;
        struct ac108_priv *ac108 = codec->private_data;
        struct ac108_param *param = &ac108->param;
        ac108_update_bits(&param->twi_dev[0], kcontrol->reg,
                (kcontrol->mask << kcontrol->shift),
                ((unsigned int)val << kcontrol->shift));
    } else {
        snd_err("invalid kcontrol data type = %d.\n",
                kcontrol->private_data_type);
        return -EINVAL;
    }
    kcontrol->value = val & kcontrol->mask;

    snd_info("mask:0x%x, shift:%d, value:0x%x\n",
            kcontrol->mask, kcontrol->shift, kcontrol->value);

    return 0;
}

static int ac108_ctl_value_get(struct snd_kcontrol *kcontrol,
            struct snd_ctl_info *info)
{
    unsigned int val = 0;
    int mask = 0;

    if (kcontrol->type != SND_CTL_ELEM_TYPE_INTEGER) {
        snd_err("invalid kcontrol type = %d.\n", kcontrol->type);
        return -EINVAL;
    }

    if (kcontrol->private_data_type == SND_MODULE_CODEC) {
        struct snd_codec *codec = kcontrol->private_data;
        struct ac108_priv *ac108 = codec->private_data;
        struct ac108_param *param = &ac108->param;
        ac108_read(&param->twi_dev[0], kcontrol->reg, (unsigned char *)&val);
    } else {
        snd_err("%s invalid kcontrol data type = %d.\n", __func__,
                kcontrol->private_data_type);
    }

    snd_kcontrol_to_snd_ctl_info(kcontrol, info, val);

    return 0;
}

static int ac108_ctl_value_set(struct snd_kcontrol *kcontrol, unsigned long val)
{
    if (kcontrol->type != SND_CTL_ELEM_TYPE_INTEGER) {
        snd_err("invalid kcontrol type = %d.\n", kcontrol->type);
        return -EINVAL;
    }

    if (kcontrol->private_data_type == SND_MODULE_CODEC) {
        struct snd_codec *codec = kcontrol->private_data;
        struct ac108_priv *ac108 = codec->private_data;
        struct ac108_param *param = &ac108->param;
        ac108_update_bits(&param->twi_dev[0], kcontrol->reg,
                (kcontrol->mask << kcontrol->shift),
                ((unsigned int)val << kcontrol->shift));
    } else {
        snd_err("%s invalid kcontrol data type = %d.\n", __func__,
                kcontrol->private_data_type);
    }
    snd_info("mask:0x%x, shitf:%d, value:0x%x\n",
            kcontrol->mask, kcontrol->shift, val);
    return 0;
}

static struct snd_kcontrol ac108_codec_controls[] = {
    //ADC1 DIG MUX
    SND_CTL_ENUM_VALUE_EXT("ADC1 DIG MUX", ARRAY_SIZE(adc_digital_src_mux),
            adc_digital_src_mux, ADC_DSR, DIG_ADC1_SRS,
            SND_CTL_ENUM_AUTO_MASK,
            ac108_ctl_enum_value_get, ac108_ctl_enum_value_set),
    //ADC2 DIG MUX
    SND_CTL_ENUM_VALUE_EXT("ADC2 DIG MUX", ARRAY_SIZE(adc_digital_src_mux),
            adc_digital_src_mux, ADC_DSR, DIG_ADC2_SRS,
            SND_CTL_ENUM_AUTO_MASK,
            ac108_ctl_enum_value_get, ac108_ctl_enum_value_set),
    //ADC3 DIG MUX
    SND_CTL_ENUM_VALUE_EXT("ADC3 DIG MUX", ARRAY_SIZE(adc_digital_src_mux),
            adc_digital_src_mux, ADC_DSR, DIG_ADC3_SRS,
            SND_CTL_ENUM_AUTO_MASK,
            ac108_ctl_enum_value_get, ac108_ctl_enum_value_set),
    //ADC4 DIG MUX
    SND_CTL_ENUM_VALUE_EXT("ADC4 DIG MUX", ARRAY_SIZE(adc_digital_src_mux),
            adc_digital_src_mux, ADC_DSR, DIG_ADC4_SRS,
            SND_CTL_ENUM_AUTO_MASK,
            ac108_ctl_enum_value_get, ac108_ctl_enum_value_set),

    //ADC12 DMIC1 MUX
    SND_CTL_ENUM_VALUE_EXT("ADC12 DMIC1 MUX", ARRAY_SIZE(adc12_dmic1_src_mux),
            adc12_dmic1_src_mux, DMIC_EN, DMIC1_EN,
            SND_CTL_ENUM_AUTO_MASK,
            ac108_ctl_enum_value_get, ac108_ctl_enum_value_set),
    //ADC34 DMIC2 MUX
    SND_CTL_ENUM_VALUE_EXT("ADC34 DMIC2 MUX", ARRAY_SIZE(adc34_dmic2_src_mux),
            adc34_dmic2_src_mux, DMIC_EN, DMIC2_EN,
            SND_CTL_ENUM_AUTO_MASK,
            ac108_ctl_enum_value_get, ac108_ctl_enum_value_set),

    //ADC1 DIG MIXER
    SND_CTL_KCONTROL_VALUE_EXT("ADC1 DIG MIXER ADC1 DAT switch",
            ADC1_DMIX_SRC, ADC1_ADC1_DMXL_SRC, 1, 0,
            ac108_ctl_value_get, ac108_ctl_value_set),
    SND_CTL_KCONTROL_VALUE_EXT("ADC1 DIG MIXER ADC2 DAT switch",
            ADC1_DMIX_SRC, ADC1_ADC2_DMXL_SRC, 1, 0,
            ac108_ctl_value_get, ac108_ctl_value_set),
    SND_CTL_KCONTROL_VALUE_EXT("ADC1 DIG MIXER ADC3 DAT switch",
            ADC1_DMIX_SRC, ADC1_ADC3_DMXL_SRC, 1, 0,
            ac108_ctl_value_get, ac108_ctl_value_set),
    SND_CTL_KCONTROL_VALUE_EXT("ADC1 DIG MIXER ADC4 DAT switch",
            ADC1_DMIX_SRC, ADC1_ADC4_DMXL_SRC, 1, 0,
            ac108_ctl_value_get, ac108_ctl_value_set),
    //ADC2 DIG MIXER
    SND_CTL_KCONTROL_VALUE_EXT("ADC2 DIG MIXER ADC1 DAT switch",
            ADC2_DMIX_SRC, ADC2_ADC1_DMXL_SRC, 1, 0,
            ac108_ctl_value_get, ac108_ctl_value_set),
    SND_CTL_KCONTROL_VALUE_EXT("ADC2 DIG MIXER ADC2 DAT switch",
            ADC2_DMIX_SRC, ADC2_ADC2_DMXL_SRC, 1, 0,
            ac108_ctl_value_get, ac108_ctl_value_set),
    SND_CTL_KCONTROL_VALUE_EXT("ADC2 DIG MIXER ADC3 DAT switch",
            ADC2_DMIX_SRC, ADC2_ADC3_DMXL_SRC, 1, 0,
            ac108_ctl_value_get, ac108_ctl_value_set),
    SND_CTL_KCONTROL_VALUE_EXT("ADC2 DIG MIXER ADC4 DAT switch",
            ADC2_DMIX_SRC, ADC2_ADC4_DMXL_SRC, 1, 0,
            ac108_ctl_value_get, ac108_ctl_value_set),
    //ADC3 DIG MIXER
    SND_CTL_KCONTROL_VALUE_EXT("ADC3 DIG MIXER ADC1 DAT switch",
            ADC3_DMIX_SRC, ADC3_ADC1_DMXL_SRC, 1, 0,
            ac108_ctl_value_get, ac108_ctl_value_set),
    SND_CTL_KCONTROL_VALUE_EXT("ADC3 DIG MIXER ADC2 DAT switch",
            ADC3_DMIX_SRC, ADC3_ADC2_DMXL_SRC, 1, 0,
            ac108_ctl_value_get, ac108_ctl_value_set),
    SND_CTL_KCONTROL_VALUE_EXT("ADC3 DIG MIXER ADC3 DAT switch",
            ADC3_DMIX_SRC, ADC3_ADC3_DMXL_SRC, 1, 0,
            ac108_ctl_value_get, ac108_ctl_value_set),
    SND_CTL_KCONTROL_VALUE_EXT("ADC3 DIG MIXER ADC4 DAT switch",
            ADC3_DMIX_SRC, ADC3_ADC4_DMXL_SRC, 1, 0,
            ac108_ctl_value_get, ac108_ctl_value_set),
    //ADC4 DIG MIXER
    SND_CTL_KCONTROL_VALUE_EXT("ADC4 DIG MIXER ADC1 DAT switch",
            ADC4_DMIX_SRC, ADC4_ADC1_DMXL_SRC, 1, 0,
            ac108_ctl_value_get, ac108_ctl_value_set),
    SND_CTL_KCONTROL_VALUE_EXT("ADC4 DIG MIXER ADC2 DAT switch",
            ADC4_DMIX_SRC, ADC4_ADC2_DMXL_SRC, 1, 0,
            ac108_ctl_value_get, ac108_ctl_value_set),
    SND_CTL_KCONTROL_VALUE_EXT("ADC4 DIG MIXER ADC3 DAT switch",
            ADC4_DMIX_SRC, ADC4_ADC3_DMXL_SRC, 1, 0,
            ac108_ctl_value_get, ac108_ctl_value_set),
    SND_CTL_KCONTROL_VALUE_EXT("ADC4 DIG MIXER ADC4 DAT switch",
            ADC4_DMIX_SRC, ADC4_ADC4_DMXL_SRC, 1, 0,
            ac108_ctl_value_get, ac108_ctl_value_set),

    //I2S TX1 CH1 MUX
    SND_CTL_ENUM_VALUE_EXT("I2S TX1 CH1 MUX", ARRAY_SIZE(i2s_tx1ch_map_mux),
            i2s_tx1ch_map_mux, I2S_TX1_CHMP_CTRL1, TX1_CH1_MAP,
            SND_CTL_ENUM_AUTO_MASK,
            ac108_ctl_enum_value_get, ac108_ctl_enum_value_set),
    //I2S TX1 CH2 MUX
    SND_CTL_ENUM_VALUE_EXT("I2S TX1 CH2 MUX", ARRAY_SIZE(i2s_tx1ch_map_mux),
            i2s_tx1ch_map_mux, I2S_TX1_CHMP_CTRL1, TX1_CH2_MAP,
            SND_CTL_ENUM_AUTO_MASK,
            ac108_ctl_enum_value_get, ac108_ctl_enum_value_set),
    //I2S TX1 CH3 MUX
    SND_CTL_ENUM_VALUE_EXT("I2S TX1 CH3 MUX", ARRAY_SIZE(i2s_tx1ch_map_mux),
            i2s_tx1ch_map_mux, I2S_TX1_CHMP_CTRL1, TX1_CH3_MAP,
            SND_CTL_ENUM_AUTO_MASK,
            ac108_ctl_enum_value_get, ac108_ctl_enum_value_set),
    //I2S TX1 CH4 MUX
    SND_CTL_ENUM_VALUE_EXT("I2S TX1 CH4 MUX", ARRAY_SIZE(i2s_tx1ch_map_mux),
            i2s_tx1ch_map_mux, I2S_TX1_CHMP_CTRL1, TX1_CH4_MAP,
            SND_CTL_ENUM_AUTO_MASK,
            ac108_ctl_enum_value_get, ac108_ctl_enum_value_set),
};
#endif

static int ac108_codec_startup(struct snd_pcm_substream *substream,
        struct snd_dai *dai)
{
    struct snd_codec *codec = dai->component;
    struct ac108_priv *ac108 = codec->private_data;
    struct ac108_param *param = &ac108->param;
    int ret = 0;

    snd_print("\n");

    return 0;
}

static int ac108_codec_set_pll(struct snd_dai *dai, int pll_id, int source,
            unsigned int freq_in, unsigned int freq_out)
{
    struct snd_codec *codec = dai->component;
    struct ac108_priv *ac108 = codec->private_data;
    struct ac108_param *param = &ac108->param;
    unsigned int i = 0;
    unsigned int m1 = 0;
    unsigned int m2 = 0;
    unsigned int n = 0;
    unsigned int k1 = 0;
    unsigned int k2 = 0;

    snd_print("\n");
    if (freq_out == 0) {
        snd_err("freq_out is 0.\n");
        return 0;
    }

    //default: freq_int == freq_out; pll_id = 0; source = 0;
    if (freq_in < 128000 || freq_in > 24576000) {
        snd_err("AC108 PLLCLK source input freq only support [128K,24M],while now %u\n\n", freq_in);
        return -EINVAL;
    } else if ((freq_in == 24576000 || freq_in == 22579200) &&
        pll_id == SYSCLK_SRC_MCLK) {
        //System Clock Source Select MCLK, SYSCLK Enable
        snd_print("AC108 don't need to use PLL\n\n");
        ac108_multi_chips_update_bits(ac108, SYSCLK_CTRL,
                0x1 << SYSCLK_SRC | 0x1 << SYSCLK_EN,
                0x0 << SYSCLK_SRC | 0x1 << SYSCLK_EN);
        return 0;   //Don't need to use PLL
    }

    //PLL Clock Source Select
    switch (pll_id) {
    case PLLCLK_SRC_MCLK:
        snd_print("AC108 PLLCLK input source select MCLK\n");
        ac108_multi_chips_update_bits(ac108, SYSCLK_CTRL, 0x3 << PLLCLK_SRC,
                    0x0 << PLLCLK_SRC);
    break;
    case PLLCLK_SRC_BCLK:
        snd_print("AC108 PLLCLK input source select BCLK\n");
        ac108_multi_chips_update_bits(ac108, SYSCLK_CTRL, 0x3 << PLLCLK_SRC,
                    0x1 << PLLCLK_SRC);
    break;
    case PLLCLK_SRC_GPIO2:
        snd_print("AC108 PLLCLK input source select GPIO2\n");
        ac108_multi_chips_update_bits(ac108, SYSCLK_CTRL, 0x3 << PLLCLK_SRC,
                    0x2 << PLLCLK_SRC);
    break;
    case PLLCLK_SRC_GPIO3:
        snd_print("AC108 PLLCLK input source select GPIO3\n");
        ac108_multi_chips_update_bits(ac108, SYSCLK_CTRL, 0x3 << PLLCLK_SRC,
                    0x3 << PLLCLK_SRC);
    break;
    default:
        snd_err("AC108 PLLCLK source config error:%d\n", pll_id);
    return -EINVAL;
    }

    //FOUT =(FIN * N) / [(M1+1) * (M2+1)*(K1+1)*(K2+1)] ;
    for (i = 0; i < ARRAY_SIZE(ac108_pll_div); i++) {
        if (ac108_pll_div[i].freq_in == freq_in &&
            ac108_pll_div[i].freq_out == freq_out) {
            m1 = ac108_pll_div[i].m1;
            m2 = ac108_pll_div[i].m2;
            n = ac108_pll_div[i].n;
            k1 = ac108_pll_div[i].k1;
            k2 = ac108_pll_div[i].k2;
            snd_print("AC108 PLL freq_in match:%u, freq_out:%u\n",
                freq_in, freq_out);
            break;
        }
    }

    if (i == ARRAY_SIZE(ac108_pll_div)) {
        snd_err("AC108 don't match PLLCLK freq_in and freq_out table\n");
        return -EINVAL;
    }

    //Config PLL DIV param M1/M2/N/K1/K2
    ac108_multi_chips_update_bits(ac108, PLL_CTRL2,
            0x1f << PLL_PREDIV1 | 0x1 << PLL_PREDIV2,
            m1 << PLL_PREDIV1 | m2 << PLL_PREDIV2);
    ac108_multi_chips_update_bits(ac108, PLL_CTRL3, 0x3 << PLL_LOOPDIV_MSB,
                (n >> 8) << PLL_LOOPDIV_MSB);
    ac108_multi_chips_update_bits(ac108, PLL_CTRL4, 0xff << PLL_LOOPDIV_LSB,
                (u8)n << PLL_LOOPDIV_LSB);
    ac108_multi_chips_update_bits(ac108, PLL_CTRL5,
                (0x1f << PLL_POSTDIV1) | (0x1 << PLL_POSTDIV2),
                k1 << PLL_POSTDIV1 | (k2 << PLL_POSTDIV2));

    //Config PLL module current
    //ac108_multi_chips_update_bits(ac108, PLL_CTRL1, 0x7<<PLL_IBIAS, 0x4<<PLL_IBIAS);
    //ac108_multi_chips_update_bits(ac108, PLL_CTRL6, 0x1f<<PLL_CP, 0xf<<PLL_CP);

    //PLL module enable
    //PLL CLK lock enable
    ac108_multi_chips_update_bits(ac108, PLL_LOCK_CTRL, 0x1 << PLL_LOCK_EN,
                0x1 << PLL_LOCK_EN);
    //PLL Common voltage Enable, PLL Enable
    //ac108_multi_chips_update_bits(ac108, PLL_CTRL1,
    //          0x1 << PLL_EN | 0x1 << PLL_COM_EN,
    //          0x1<<PLL_EN | 0x1<<PLL_COM_EN);

    //PLLCLK Enable, SYSCLK Enable
    //0x1<<SYSCLK_SRC
    ac108_multi_chips_update_bits(ac108, SYSCLK_CTRL,
                0x1 << PLLCLK_EN | 0x1 << SYSCLK_EN,
                0x1 << PLLCLK_EN | 0x1 << SYSCLK_EN);

    return 0;
}

static int ac108_codec_set_clkdiv(struct snd_dai *dai, int div_id, int div)
{
    struct snd_codec *codec = dai->component;
    struct ac108_priv *ac108 = codec->private_data;
    struct ac108_param *param = &ac108->param;
    unsigned int i = 0;
    unsigned int bclk_div = 0;
    unsigned int bclk_div_reg_val = 0;

    snd_print("\n");
    /* default: div_id = 0; */
    if (param->daudio_master == 4) {
        /*
         *daudio_master(val << 12):
         *  1: SND_SOC_DAIFMT_CBM_CFM(codec clk & FRM master)
         *  4: SND_SOC_DAIFMT_CBS_CFS(codec clk & FRM slave)
         */
        snd_print("AC108 work as Slave mode, don't need to config BCLK_DIV.\n");
        return 0;
    }

    /* SND_SOC_DAIFMT_I2S*/
    switch (param->daudio_format) {
    case SND_SOC_DAIFMT_DSP_A:
    case SND_SOC_DAIFMT_DSP_B:
        bclk_div = div / param->lrck_period;
        break;
    case SND_SOC_DAIFMT_I2S:
    case SND_SOC_DAIFMT_RIGHT_J:
    case SND_SOC_DAIFMT_LEFT_J:
    default:
        bclk_div = div / (2 * param->lrck_period);
        break;
    }

    for (i = 0; i < ARRAY_SIZE(ac108_bclk_div); i++) {
        if (ac108_bclk_div[i].real_val == bclk_div) {
            bclk_div_reg_val = ac108_bclk_div[i].reg_val;
            snd_print("AC108 set BCLK_DIV_[%u]\n", bclk_div);
            break;
        }
    }

    if (i == ARRAY_SIZE(ac108_bclk_div)) {
        snd_err("AC108 don't support BCLK_DIV_[%u]\n", bclk_div);
        return -EINVAL;
    }

    //AC108 set BCLK DIV
    ac108_multi_chips_update_bits(ac108, I2S_BCLK_CTRL, 0xf << BCLKDIV,
                bclk_div_reg_val << BCLKDIV);
    return 0;
}

static int ac108_codec_set_fmt(struct snd_dai *dai, unsigned int fmt)
{
    struct snd_codec *codec = dai->component;
    struct ac108_priv *ac108 = codec->private_data;
    struct ac108_param *param = &ac108->param;
    unsigned int i = 0;
    unsigned char tx_offset = 0;
    unsigned char i2s_mode = 0;
    unsigned char lrck_polarity = 0;
    unsigned char brck_polarity = 0;

    snd_print("\n");
    //AC108 config Master/Slave mode
    switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
    case SND_SOC_DAIFMT_CBM_CFM:    //AC108 Master
        snd_print("AC108 set to work as Master\n");
        //BCLK & LRCK output
        ac108_update_bits(&param->twi_dev[0], I2S_CTRL, 0x3 << LRCK_IOEN,
                0x3 << LRCK_IOEN);
    break;
    case SND_SOC_DAIFMT_CBS_CFS:    //AC108 Slave
        snd_print("AC108 set to work as Slave\n");
        //BCLK & LRCK input
        ac108_update_bits(&param->twi_dev[0], I2S_CTRL, 0x3 << LRCK_IOEN,
                0x0 << LRCK_IOEN);
    break;
    default:
        snd_err("AC108 Master/Slave mode config error:%u\n\n",
            (fmt & SND_SOC_DAIFMT_MASTER_MASK) >> 12);
    return -EINVAL;
    }

    for (i = 0; i < param->chip_num; i++) {
        /*
         * multi_chips: only one chip set as Master,
         * and the others also need to set as Slave
         */
        ac108_update_bits(&param->twi_dev[i], I2S_CTRL, 0x3 << LRCK_IOEN,
                0x0 << LRCK_IOEN);
    }

    //AC108 config I2S/LJ/RJ/PCM format
    switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
    case SND_SOC_DAIFMT_I2S:
        snd_print("AC108 config I2S format\n");
        i2s_mode = LEFT_JUSTIFIED_FORMAT;
        tx_offset = 1;
    break;
    case SND_SOC_DAIFMT_RIGHT_J:
        snd_print("AC108 config RIGHT-JUSTIFIED format\n");
        i2s_mode = RIGHT_JUSTIFIED_FORMAT;
        tx_offset = 0;
    break;
    case SND_SOC_DAIFMT_LEFT_J:
        snd_print("AC108 config LEFT-JUSTIFIED format\n");
        i2s_mode = LEFT_JUSTIFIED_FORMAT;
        tx_offset = 0;
    break;
    case SND_SOC_DAIFMT_DSP_A:
        snd_print("AC108 config PCM-A format\n");
        i2s_mode = PCM_FORMAT;
        tx_offset = 1;
    break;
    case SND_SOC_DAIFMT_DSP_B:
        snd_print("AC108 config PCM-B format\n");
        i2s_mode = PCM_FORMAT;
        tx_offset = 0;
    break;
    default:
        snd_err("AC108 I2S format config error:%u\n\n",
            fmt & SND_SOC_DAIFMT_FORMAT_MASK);
    return -EINVAL;
    }

    ac108_multi_chips_update_bits(ac108, I2S_FMT_CTRL1,
        0x3 << MODE_SEL | 0x1 << TX2_OFFSET | 0x1 << TX1_OFFSET,
        i2s_mode<<MODE_SEL | tx_offset<<TX2_OFFSET | tx_offset << TX1_OFFSET);

    //AC108 config BCLK&LRCK polarity
    switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
    case SND_SOC_DAIFMT_NB_NF:
        snd_print("AC108 config: BCLK_normal,LRCK_normal.\n");
        brck_polarity = BCLK_NORMAL_DRIVE_N_SAMPLE_P;
        lrck_polarity = LRCK_LEFT_LOW_RIGHT_HIGH;
    break;
    case SND_SOC_DAIFMT_NB_IF:
        snd_print("AC108 config: BCLK_normal,LRCK_invert.\n");
        brck_polarity = BCLK_NORMAL_DRIVE_N_SAMPLE_P;
        lrck_polarity = LRCK_LEFT_HIGH_RIGHT_LOW;
    break;
    case SND_SOC_DAIFMT_IB_NF:
        snd_print("AC108 config: BCLK_invert,LRCK_normal.\n");
        brck_polarity = BCLK_INVERT_DRIVE_P_SAMPLE_N;
        lrck_polarity = LRCK_LEFT_LOW_RIGHT_HIGH;
    break;
    case SND_SOC_DAIFMT_IB_IF:
        snd_print("AC108 config: BCLK_invert,LRCK_invert.\n");
        brck_polarity = BCLK_INVERT_DRIVE_P_SAMPLE_N;
        lrck_polarity = LRCK_LEFT_HIGH_RIGHT_LOW;
        break;
    default:
        snd_err("AC108 config BCLK/LRCLK polarity error:%u\n",
            (fmt & SND_SOC_DAIFMT_INV_MASK) >> 8);
    return -EINVAL;
    }
    ac108_multi_chips_update_bits(ac108, I2S_BCLK_CTRL,  0x1<<BCLK_POLARITY,
                brck_polarity << BCLK_POLARITY);
    ac108_multi_chips_update_bits(ac108, I2S_LRCK_CTRL1, 0x1<<LRCK_POLARITY,
                lrck_polarity << LRCK_POLARITY);

    return 0;
}

static void ac108_codec_set_pga_gain(struct twi_device *twi_dev, struct ac108_param *param)
{
    unsigned int i;

    snd_print("\n");
    if (twi_dev->ref_chan.ref_channel != 0x0) {
        snd_info("ref_cfg.ref_channel:0x%x, set ref_pga_gain:%d\n",
             twi_dev->ref_chan.ref_channel, twi_dev->ref_chan.ref_pga);
        /* set the gain for referenced channels, always used for aec */
        for (i = 0; i < 4; i++) {
            if ((twi_dev->ref_chan.ref_channel >> i) & 0x1) {
                ac108_update_bits(twi_dev, ANA_PGA1_CTRL + i,
                    0x1F << ADC1_ANALOG_PGA,
                    twi_dev->ref_chan.ref_pga << ADC1_ANALOG_PGA);
            } else
                ac108_update_bits(twi_dev, ANA_PGA1_CTRL + i,
                    0x1F << ADC1_ANALOG_PGA,
                    param->pga_gain << ADC1_ANALOG_PGA);
        }
    } else {
        for (i = 0; i < 4; i++)
            ac108_update_bits(twi_dev, ANA_PGA1_CTRL + i,
                    0x1F << ADC1_ANALOG_PGA,
                    param->pga_gain << ADC1_ANALOG_PGA);
    }
}

static void ac108_codec_hw_init(struct twi_device *twi_dev, struct ac108_param *param)
{
    /*** Chip reset ***/
    /*0x00=0x12: reset all registers to their default state*/
    //ac108_write(twi_dev, CHIP_AUDIO_RST, 0x12);

#if !AC108_DMIC_EN
    /*** Analog voltage enable ***/
    /*0x06=0x01: Enable Analog LDO*/
    ac108_write(twi_dev, PWR_CTRL6, 0x01);
    /*
     * 0x07=0x9b: VREF faststart Enable,
     * Enable VREF @ 3.4V (5V) or 3.1V (3.3V)
     * (needed for Analog LDO and MICBIAS)
     */
    ac108_write(twi_dev, PWR_CTRL7, 0x9b);
    /*
     * 0x09=0x81: VREFP faststart Enable, Enable VREFP_FASTSTART_ENABLE
     * (needed by all audio input channels)
     */
    ac108_write(twi_dev, PWR_CTRL9, 0x81);
    /*
     * DSM low power mode enable, Control bias current for
     * DSM integrator opamps
     */
    ac108_write(twi_dev, ANA_ADC3_CTRL7, 0x0b);
#endif
    /*** SYSCLK Config ***/
    /*SYSCLK Enable*/
    ac108_update_bits(twi_dev, SYSCLK_CTRL, 0x1 << SYSCLK_EN, 0x1 << SYSCLK_EN);
    /*
     * 0x21=0x93: Module clock enable<I2S, ADC digital,
     * MIC offset Calibration, ADC analog>
     */
    ac108_write(twi_dev, MOD_CLK_EN, 0x93);
    /*
     * 0x22=0x93: Module reset de-asserted
     * <I2S, ADC digital, MIC offset Calibration, ADC analog>
     */
    ac108_write(twi_dev, MOD_RST_CTRL, 0x93);
    /*** I2S Common Config ***/
    /*SDO1 enable, SDO2 Enable*/
    ac108_update_bits(twi_dev, I2S_CTRL, ((0x1 << SDO1_EN) | (0x1 << SDO2_EN)),
            ((0x1 << SDO1_EN) | (!!AC108_SDO2_EN << SDO2_EN)));
    /*SDO drive data and SDI sample data at the different BCLK edge*/
    ac108_update_bits(twi_dev, I2S_BCLK_CTRL, (0x1 << EDGE_TRANSFER),
            (0x0 << EDGE_TRANSFER));
    ac108_update_bits(twi_dev, I2S_LRCK_CTRL1, 0x3 << LRCK_PERIODH,
            (((param->lrck_period - 1) >> 8) << LRCK_PERIODH));

    /*
     * config LRCK period:
     * 16bit * 8ch = 128,
     * 32bit * 8ch = 256,
     * 32bit *16ch = 512
     */
    ac108_write(twi_dev, I2S_LRCK_CTRL2, (param->lrck_period - 1) & 0xFF);
    /*
     * Encoding mode enable, Turn to hi-z state (TDM)
     * when not transferring slot
     */
    ac108_update_bits(twi_dev, I2S_FMT_CTRL1,
        0x1 << ENCD_SEL | 0x1 << TX_SLOT_HIZ | 0x1 << TX_STATE,
        !!AC108_ENCODING_EN << ENCD_SEL | 0x0 << TX_SLOT_HIZ | 0x1 << TX_STATE);
    /* 8/12/16/20/24/28/32bit Slot Width */
    ac108_update_bits(twi_dev, I2S_FMT_CTRL2, 0x7 << SLOT_WIDTH_SEL,
            (param->slot_width / 4 - 1) << SLOT_WIDTH_SEL);
    /*
     * 0x36=0x70: TX MSB first, TX2 Mute, Transfer 0 after
     * each sample in each slot(sample resolution < slot width),
     * LRCK = 1 BCLK width (short frame), Linear PCM Data Mode
     */
    ac108_write(twi_dev, I2S_FMT_CTRL3, AC108_SDO2_EN ? 0x60 : 0x70);

    /*0x3C=0xe4: TX1 CHn Map to CHn adc sample, n=[1,4]*/
    ac108_write(twi_dev, I2S_TX1_CHMP_CTRL1, 0xe4);
    /*0x3D=0xe4: TX1 CHn Map to CH(n-4) adc sample, n=[5,8]*/
    ac108_write(twi_dev, I2S_TX1_CHMP_CTRL2, 0xe4);
    /*0x3E=0xe4: TX1 CHn Map to CH(n-8) adc sample, n=[9,12]*/
    ac108_write(twi_dev, I2S_TX1_CHMP_CTRL3, 0xe4);
    /*0x3F=0xe4: TX1 CHn Map to CH(n-12) adc sample, n=[13,16]*/
    ac108_write(twi_dev, I2S_TX1_CHMP_CTRL4, 0xe4);

#if AC108_SDO2_EN
    /*
     * 0x44=0x4e: TX2 CH1/2 Map to CH3/4 adc sample,
     * TX2 CH3/4 Map to CH1/2 adc sample
     */
    ac108_write(twi_dev, I2S_TX2_CHMP_CTRL1, 0x4e);
    /*0x45=0xe4: TX2 CHn Map to CH(n-4) adc sample, n=[5,8]*/
    ac108_write(twi_dev, I2S_TX2_CHMP_CTRL2, 0xe4);
    /*0x46=0xe4: TX2 CHn Map to CH(n-8) adc sample, n=[9,12]*/
    ac108_write(twi_dev, I2S_TX2_CHMP_CTRL3, 0xe4);
    /*0x47=0xe4: TX2 CHn Map to CH(n-12) adc sample, n=[13,16]*/
    ac108_write(twi_dev, I2S_TX2_CHMP_CTRL4, 0xe4);
#endif

    /*** ADC DIG part Config***/
    /*0x60=0x03: ADC Sample Rate 16KHz*/
    //ac108_write(ADC_SPRC, 0x03);
    /*0x61=0x1f: Digital part globe enable, ADCs digital part enable*/
    ac108_write(twi_dev, ADC_DIG_EN, 0x1f);
    /*0xBB=0x0f: Gating ADCs CLK de-asserted (ADCs CLK Enable)*/
    ac108_write(twi_dev, ANA_ADC4_CTRL7, 0x0f);

    if (twi_dev->debug_mode) {
        /*0x66=0x00: Digital ADCs channel HPF disable*/
        ac108_write(twi_dev, HPF_EN, 0x00);
        /*
         * 0X7F=0x00: ADC pattern select: 0:ADC normal, 1:0x5A5A5A,
         * 2:0x123456, 3:0x00, 4~7:I2S RX data
         */
        ac108_write(twi_dev, ADC_DIG_DEBUG, twi_dev->debug_mode & 0x7);
    }

#if !AC108_DMIC_EN
    /*** ADCs analog PGA gain Config***/
    ac108_codec_set_pga_gain(twi_dev, param);

    /*** enable AAF/ADC/PGA  and UnMute Config ***/
    /*
     * 0xA0=0x07: ADC1 AAF & ADC enable, ADC1 PGA enable,
     * ADC1 MICBIAS enable and UnMute
     */
    ac108_write(twi_dev, ANA_ADC1_CTRL1, 0x07);
    /*
     * 0xA7=0x07: ADC2 AAF & ADC enable, ADC2 PGA enable,
     * ADC2 MICBIAS enable and UnMute
     */
    ac108_write(twi_dev, ANA_ADC2_CTRL1, 0x07);
    /*
     * 0xAE=0x07: ADC3 AAF & ADC enable, ADC3 PGA enable,
     * ADC3 MICBIAS enable and UnMute
     */
    ac108_write(twi_dev, ANA_ADC3_CTRL1, 0x07);
    /*
     * 0xB5=0x07: ADC4 AAF & ADC enable, ADC4 PGA enable,
     * ADC4 MICBIAS enable and UnMute
     */
    ac108_write(twi_dev, ANA_ADC4_CTRL1, 0x07);

    /*
     * delay 50ms to let VREF/VRP faststart powerup stable,
     * then disable faststart
     */
    usleep(50 * 1000);
    /* VREF faststart disable */
    ac108_update_bits(twi_dev, PWR_CTRL7, 0x1 << VREF_FASTSTART_ENABLE,
            0x0 << VREF_FASTSTART_ENABLE);
    /*VREFP faststart disable*/
    ac108_update_bits(twi_dev, PWR_CTRL9, 0x1 << VREFP_FASTSTART_ENABLE,
            0x0 << VREFP_FASTSTART_ENABLE);
#else
    /*** DMIC module Enable ***/
    /*DMIC1/2 Enable, while ADC DIG source select DMIC1/2*/
    ac108_write(twi_dev, DMIC_EN, 0x03);
    /*GPIO1 as DMIC1_DAT, GPIO2 as DMIC_CLK*/
    ac108_write(twi_dev, GPIO_CFG1, 0xee);
    /*GPIO3 as DMIC2_DAT*/
    ac108_write(twi_dev, GPIO_CFG2, 0x7e);
#endif
}

static int ac108_codec_hw_params(struct snd_pcm_substream *substream,
        struct snd_pcm_hw_params *params, struct snd_dai *dai)
{
    struct snd_codec *codec = dai->component;
    struct ac108_priv *ac108 = codec->private_data;
    struct ac108_param *param = &ac108->param;
    int i = 0;
    int ret = 0;
    unsigned char reg_val = 0;
    unsigned short channels = 0;
    unsigned short channels_en = 0;
    unsigned short sample_resolution = 0;

    snd_print("\n");
    /* set codec dai fmt */
    ret = snd_soc_dai_set_fmt(dai, param->daudio_format
            | (param->signal_inversion << SND_SOC_DAIFMT_SIG_SHIFT)
            | (param->daudio_master << SND_SOC_DAIFMT_MASTER_SHIFT));
    if (ret < 0) {
        snd_err("codec_dai set pll failed\n");
        return -EINVAL;
    }

    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
        snd_print("AC108 not need playback.\n");
        return 0;
    }

    //AC108 hw init
    for (i = 0; i < param->chip_num; i++)
        ac108_codec_hw_init(&param->twi_dev[i], param);

    //AC108 set sample rate
    for (i = 0; i < ARRAY_SIZE(ac108_sample_rate); i++) {
        if (ac108_sample_rate[i].real_val ==
            params_rate(params) / (AC108_ENCODING_EN ? AC108_ENCODING_CH_NUMS / 2 : 1)) {
            ac108_multi_chips_update_bits(ac108, ADC_SPRC,
                0xf << ADC_FS_I2S1,
                ac108_sample_rate[i].reg_val << ADC_FS_I2S1);
            break;
        }
    }

    //AC108 set channels
#if !AC108_SDO2_EN
    channels = params_channels(params) *
            (AC108_ENCODING_EN ? AC108_ENCODING_CH_NUMS/2 : 1);
    for (i = 0; i < (channels + 3) / 4; i++) {
        channels_en = (channels >= 4 * (i + 1)) ? 0x000f << (4 * i) :
                ((1 << (channels % 4)) - 1) << (4 * i);
        ac108_write(&param->twi_dev[i], I2S_TX1_CTRL1, channels - 1);
        ac108_write(&param->twi_dev[i], I2S_TX1_CTRL2, (unsigned char )channels_en);
        ac108_write(&param->twi_dev[i], I2S_TX1_CTRL3, channels_en >> 8);
    }

    for (; i < param->chip_num; i++) {
        ac108_write(&param->twi_dev[i], I2S_TX1_CTRL1, 0);
        ac108_write(&param->twi_dev[i], I2S_TX1_CTRL2, 0);
        ac108_write(&param->twi_dev[i], I2S_TX1_CTRL3, 0);
    }
#else
    channels = params_channels(params);
    for (i = 0; i < (channels + 3) / 4; i++) {
        //(2 >= 4*(i+1)) ? 0x000f<<(4*i) : ((1<<(2%4))-1)<<(4*i);
        channels_en = 0x03;
        ac108_write(&param->twi_dev[i], I2S_TX1_CTRL1, 2 - 1);
        ac108_write(&param->twi_dev[i], I2S_TX1_CTRL2, (u8)channels_en);
        ac108_write(&param->twi_dev[i], I2S_TX1_CTRL3, channels_en >> 8);
    }
    for (; i < param->chip_num; i++) {
        ac108_write(&param->twi_dev[i], I2S_TX1_CTRL1, 0);
        ac108_write(&param->twi_dev[i], I2S_TX1_CTRL2, 0);
        ac108_write(&param->twi_dev[i], I2S_TX1_CTRL3, 0);
    }

    for (i = 0; i < (channels + 3) / 4; i++) {
        //(2 >= 4*(i+1)) ? 0x000f<<(4*i) : ((1<<(2%4))-1)<<(4*i);
        channels_en = 0x03;
        ac108_write(&param->twi_dev[i], I2S_TX2_CTRL1, 2 - 1);
        ac108_write(&param->twi_dev[i], I2S_TX2_CTRL2, (u8)channels_en);
        ac108_write(&param->twi_dev[i], I2S_TX2_CTRL3, channels_en >> 8);
    }
    for (; i < param->chip_num; i++) {
        ac108_write(&param->twi_dev[i], I2S_TX2_CTRL1, 0);
        ac108_write(&param->twi_dev[i], I2S_TX2_CTRL2, 0);
        ac108_write(&param->twi_dev[i], I2S_TX2_CTRL3, 0);
    }
#endif

    //AC108 set sample resorution
    switch (params_format(params)) {
    case SND_PCM_FORMAT_S16_LE:
        sample_resolution = 16;
    break;
    case SND_PCM_FORMAT_S24_LE:
        sample_resolution = 24;
    break;
    case SND_PCM_FORMAT_S32_LE:
        sample_resolution = 32;
    break;
    default:
        snd_err("AC108 don't supported the sample resolution: %u\n",
            params_format(params));
    return -EINVAL;
    }

#if 0
    //AC108_ENCODING_EN
    //TX Encoding mode, SR add 4bits to mark channel number
    if ((sample_resolution <= 24) && (sample_resolution != 16))
        sample_resolution += 4;
#endif
    for (i = 0; i < ARRAY_SIZE(ac108_sample_resolution); i++) {
        if (ac108_sample_resolution[i].real_val == sample_resolution) {
            ac108_multi_chips_update_bits(ac108, I2S_FMT_CTRL2,
                0x7 << SAMPLE_RESOLUTION,
                ac108_sample_resolution[i].reg_val << SAMPLE_RESOLUTION);
            break;
        }
    }

    ac108_read(&param->twi_dev[0], SYSCLK_CTRL, &reg_val);
    if (reg_val & 0x80) {
        //PLLCLK Enable
        //PLL Common voltage Enable, PLL Enable
        ac108_multi_chips_update_bits(ac108, PLL_CTRL1,
                0x1 << PLL_EN | 0x1 << PLL_COM_EN,
                0x1 << PLL_EN | 0x1 << PLL_COM_EN);
        if (!(reg_val & 0x08)) {
            //SYSCLK select MCLK
            //GPIO4 output Clock 24MHz from DPLL
            ac108_multi_chips_update_bits(ac108, GPIO_CFG2,
                0xf << GPIO4_SELECT, 0x9 << GPIO4_SELECT);
        }
    }

    return 0;
}

static int ac108_codec_set_sysclk(struct snd_dai *dai,
        int clk_id, unsigned int freq, int dir)
{
    struct snd_codec *codec = dai->component;
    struct ac108_priv *ac108 = codec->private_data;
    struct ac108_param *param = &ac108->param;

    snd_print("\n");
    //default: clk_id = 0;
    switch (clk_id) {
    case SYSCLK_SRC_MCLK:
        snd_print("AC108 SYSCLK source select MCLK.\n");
        //System Clock Source Select MCLK
        ac108_multi_chips_update_bits(ac108,
                SYSCLK_CTRL, 0x1 << SYSCLK_SRC,
                0x0 << SYSCLK_SRC);
    break;
    case SYSCLK_SRC_PLL:
        snd_print("AC108 SYSCLK source select PLL.\n");
        //System Clock Source Select PLL
        ac108_multi_chips_update_bits(ac108,
                SYSCLK_CTRL, 0x1 << SYSCLK_SRC,
                0x1 << SYSCLK_SRC);
    break;
    default:
        snd_err("AC108 SYSCLK source config error:%d\n\n", clk_id);
    return -EINVAL;
    }

    //SYSCLK Enable
    ac108_multi_chips_update_bits(ac108,
                SYSCLK_CTRL, 0x1 << SYSCLK_EN,
                0x1 << SYSCLK_EN);
    //AC108 TX enable, Globle enable
    ac108_multi_chips_update_bits(ac108, I2S_CTRL,
                0x1 << TXEN | 0x1 << GEN,
                0x1 << TXEN | 0x1 << GEN);
    return 0;
}

static int ac108_codec_prepare(struct snd_pcm_substream *substream,
        struct snd_dai *dai)
{
    struct snd_codec *codec = dai->component;
    struct ac108_priv *ac108 = codec->private_data;
    struct ac108_param *param = &ac108->param;

    snd_print("\n");
    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
        snd_print("ac108 playback prepare.\n");
    } else {
        snd_print("ac108 capture prepare.\n");
    }
    return 0;
}

void ac108_reg_show(void);
static int ac108_codec_trigger(struct snd_pcm_substream *substream,
        int cmd, struct snd_dai *dai)
{
    struct snd_codec *codec = dai->component;
    struct ac108_priv *ac108 = codec->private_data;
    struct ac108_param *param = &ac108->param;

    snd_print("\n");
    switch (cmd) {
    case SNDRV_PCM_TRIGGER_START:
    case SNDRV_PCM_TRIGGER_RESUME:
    case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
        if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
            snd_print("ac108 playback trigger start.\n");
        } else {
            snd_print("ac108 capture trigger start\n");
        }
        break;
    case SNDRV_PCM_TRIGGER_STOP:
    case SNDRV_PCM_TRIGGER_SUSPEND:
    case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
        if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
            snd_print("ac108 playback trigger stop.\n");
        } else {
            snd_print("ac108 capture trigger stop\n");
        }
        break;
    default:
        return -EINVAL;
    }
    return 0;
}

static int ac108_codec_hw_free(struct snd_pcm_substream *substream,
        struct snd_dai *dai)
{
    struct snd_codec *codec = dai->component;
    struct ac108_priv *ac108 = codec->private_data;
    struct ac108_param *param = &ac108->param;

    snd_print("\n");
    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
        snd_print("AC108 playback hw_free.\n");
        return 0;
    }

    //AC108 I2S Globle disable
    ac108_multi_chips_update_bits(ac108, I2S_CTRL,
                0x1 << GEN, 0x0 << GEN);

#ifdef AC108_IDLE_RESET_EN
    snd_print("AC108 reset all register to their default value\n");
    ac108_multi_chips_write(ac108, CHIP_AUDIO_RST, 0x12);
#else
    //repair PLL version no sync problem && Encoding no DAT
    ac108_multi_chips_update_bits(ac108, PLL_CTRL1,
                0x1 << PLL_EN | 0x1 << PLL_COM_EN,
                0x0 << PLL_EN | 0x0 << PLL_COM_EN);
    ac108_multi_chips_update_bits(ac108, MOD_CLK_EN,
                0x1 << I2S | 0x1 << ADC_DIGITAL,
                0x0<<I2S | 0x0<<ADC_DIGITAL);
    ac108_multi_chips_update_bits(ac108, MOD_RST_CTRL,
                0x1 << I2S | 0x1 << ADC_DIGITAL,
                0x0 << I2S | 0x0 << ADC_DIGITAL);
#endif
    return 0;
}

static void ac108_codec_shutdown(struct snd_pcm_substream *substream,
        struct snd_dai *dai)
{
    struct snd_codec *codec = dai->component;
    struct ac108_priv *ac108 = codec->private_data;
    struct ac108_param *param = &ac108->param;
    int ret = 0;
    unsigned int i = 0;

    snd_print("\n");
    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
        snd_print("AC108 playback shutdown.\n");
    } else {
        snd_print("AC108 capture shutdown.\n");
    }

    return;
}

static struct snd_dai_ops ac108_codec_dai_ops = {
    .startup    = ac108_codec_startup,
    .set_sysclk = ac108_codec_set_sysclk,
    .set_pll    = ac108_codec_set_pll,
    .set_clkdiv = ac108_codec_set_clkdiv,
    .set_fmt    = ac108_codec_set_fmt,
    .hw_params  = ac108_codec_hw_params,
    .prepare    = ac108_codec_prepare,
    .trigger    = ac108_codec_trigger,
    .hw_free    = ac108_codec_hw_free,
    .shutdown   = ac108_codec_shutdown,
};

static struct snd_dai ac108_codec_dai[] = {
    {
        .name       = "ac108-codecdai",
        .playback   = {
            .stream_name    = "Playback",
            .channels_min   = 1,
            .channels_max   = 8,
            .rates      = SNDRV_PCM_RATE_8000_192000
                    | SNDRV_PCM_RATE_KNOT,
            .formats    = SNDRV_PCM_FMTBIT_S16_LE
                    | SNDRV_PCM_FMTBIT_S24_LE
                    | SNDRV_PCM_FMTBIT_S32_LE,
            .rate_min   = 8000,
            .rate_max   = 48000,
        },
        .capture    = {
            .stream_name    = "Capture",
            .channels_min   = 1,
            .channels_max   = 8,
            .rates      = SNDRV_PCM_RATE_8000_48000
                    | SNDRV_PCM_RATE_KNOT,
            .formats    = SNDRV_PCM_FMTBIT_S16_LE
                    | SNDRV_PCM_FMTBIT_S24_LE,
            .rate_min   = 8000,
            .rate_max   = 48000,
        },
        .ops        = &ac108_codec_dai_ops,
    },
};

static int ac108_codec_probe(struct snd_codec *codec)
{
    unsigned char read_data = 0x0;

    struct ac108_priv *ac108 = NULL;
    unsigned int i = 0;
    twi_status_t ret = 0;
    unsigned char reset_cmd[2] = {0x0, 0x12};
    struct ac108_param default_param = {
        .chip_num = AC108_CHIP_NUM,
        .twi_dev = AC108_CHIP_CFG,
        .pga_gain = AC108_PGA_GAIN,
        .daudio_master = AC108_DAUDIO_MASTER,
        .daudio_format = AC108_DAUDIO_FORMAT,
        .signal_inversion = AC108_DAUDIO_SIG_INV,
        .lrck_period = AC108_LRCK_PERIOD,
        .slot_width = AC108_SLOT_WIDTH,
    };

    if (!codec->codec_dai) {
        snd_err("codec->codec_dai is null.\n");
        return -EFAULT;
    }

    ac108 = snd_malloc(sizeof(struct ac108_priv));
    if (!ac108) {
        snd_err("no memory\n");
        return -ENOMEM;
    }

    snd_print("codec para init.\n");
    codec->private_data = (void *)ac108;
    ac108->param = default_param;
    ac108->codec = codec;
    codec->codec_dai->component = codec;

    snd_print("init ac108 i2c port.\n");
    ret = ac108_init_i2c_device(ac108->param.twi_dev[i].bus);
    if (ret != TWI_STATUS_OK) {
        snd_err("init i2c err\n");
        ret = -EFAULT;
        goto err_twi_init;
    }

    for (i = 0; i < ac108->param.chip_num; i++) {
        hal_twi_control(ac108->param.twi_dev[i].bus, I2C_SLAVE, &default_param.twi_dev[i].addr);
    }
    snd_print("ac108 codec register finished.\n");

    return 0;

err_twi_init:
    snd_free(ac108);
    return ret;
}

static int ac108_codec_remove(struct snd_codec *codec)
{
    struct ac108_priv *ac108 = codec->private_data;
    struct ac108_param *param = &ac108->param;
    unsigned int i = 0;
    int ret = 0;

    snd_print("deinit ac108 i2c port.\n");
    ret = ac108_deinit_i2c_device(param->twi_dev[i].bus);
    if (ret != TWI_STATUS_OK) {
        snd_err("i2c deinit port %d failed.\n",
        param->twi_dev[i].bus);
    }
    snd_free(ac108);
    codec->private_data = NULL;

    return 0;
}

struct snd_codec ac108_codec = {
    .name       = "ac108-codec",
    .codec_dai  = ac108_codec_dai,
    .codec_dai_num  = ARRAY_SIZE(ac108_codec_dai),
    .private_data   = NULL,
    .probe      = ac108_codec_probe,
    .remove     = ac108_codec_remove,
#ifdef AC108_KCONTROL_TEST_EN
    .controls   = ac108_codec_controls,
    .num_controls   = ARRAY_SIZE(ac108_codec_controls),
#endif
};

/* for ac108 debug */
void ac108_reg_dump_usage(void)
{
    printf("\n\n=========ac108 debug===========\n");
    printf("Usage: ac108_reg [option]\n");
    printf("\t-l,    ac108 dev list\n");
    printf("\t-h,    tools help\n");
    printf("\t-d,    ac108 dev addr(hex)\n");
    printf("\t-r,    ac108 reg addr(hex)\n");
    printf("\t-n,    ac108 reg read num(hex)\n");
    printf("\t-s,    ac108 show all regs\n");
    printf("\t-w,    ac108 write reg val(hex)\n");
    printf("\n");
}

void ac108_chip_list(void)
{
    unsigned int chip_num = AC108_CHIP_NUM;
    struct twi_device twi_dev[] = AC108_CHIP_CFG;
    int i = 0;

    printf("\n\n=========ac108 show ===========\n");
    printf("\tac108 dev num:\t%d\n", chip_num);
    for (i = 0; i < chip_num; i++)
        printf("\t%d i2c%d-0x%02x\n", i, twi_dev[i].bus, twi_dev[i].addr);
    printf("===============================\n");
}

void ac108_reg_show(void)
{
    unsigned int chip_num = AC108_CHIP_NUM;
    struct twi_device twi_dev[] = AC108_CHIP_CFG;
    unsigned char read_command;
    unsigned char read_data[1] = {0x0};
    twi_status_t ret = 0;
    unsigned int i = 0;
    unsigned int j = 0;

    for (i = 0; i < chip_num; i++) {
        printf("\n=========ac108 chip [i2c%d-0x%02x] ===========\n",
                twi_dev[i].bus, twi_dev[i].addr);
        for (j = 0; j <= AC108_REG_MAX; j++) {
            if (j % 8 == 0)
                printf("\n");
            read_command = 0x0 + j;
            ret = ac108_read(&twi_dev[i], read_command, read_data);
            if (ret != TWI_STATUS_OK) {
                snd_err("[i2c%d-0x%02x] read [REG-0x%02x,val-0x%02x] ret = %d.\n",
                    twi_dev[i].bus, twi_dev[i].addr,
                    read_command, read_data[0], ret);
            }
            printf("[0x%02x]: 0x%02x  ", read_command, read_data[0]);
        }
        printf("\n=========================================\n");
    }
}

int cmd_ac108_reg(int argc, char ** argv)
{
    twi_status_t ret = -1;
    unsigned int i;
    const struct option long_option[] = {
        {"help", 0, NULL, 'h'},
        {"list", 0, NULL, 'l'},
        {"addr", 1, NULL, 'd'},
        {"reg", 1, NULL, 'r'},
        {"num", 1, NULL, 'n'},
        {"show", 0, NULL, 's'},
        {"write", 1, NULL, 'w'},
        {NULL, 0, NULL, 0},
    };
    unsigned int chip_num = AC108_CHIP_NUM;
    struct twi_device twi_dev[] = AC108_CHIP_CFG;
    unsigned char reset_cmd[2] = {0x0, 0x12};
    unsigned char write_cmd[2] = {0x0, 0x0};
    unsigned char read_cmd[1] = {0x0};
    unsigned char read_data[1] = {0x0};
    unsigned int num = 1;
    unsigned int twi_addr = 0x3b;
    bool wr_flag = 0;

    while (1) {
        int c;

        if ((c = getopt_long(argc, argv, "hlsd:r:n:w:", long_option, NULL)) < 0)
            break;
        switch (c) {
        case 'h':
            ac108_reg_dump_usage();
            goto ac108_reg_exit;
        case 'l':
            ac108_chip_list();
            goto ac108_reg_exit;
        case 's':
            ac108_reg_show();
            goto ac108_reg_exit;
        case 'd':
            if (isdigit(*optarg)) {
                sscanf(optarg, "0x%x", &twi_addr);
                //twi_addr = atoi(optarg);
                printf("\ntwi_addr slave address is 0x%02x.\n", twi_addr);
            } else
                fprintf(stderr, "twi addr is not a digital value.\n");
            break;
        case 'r':
            if (isdigit(*optarg)) {
                sscanf(optarg, "0x%hhx", &read_cmd[0]);
                //read_cmd[0] = atoi(optarg);
                write_cmd[0] = read_cmd[0];
                printf("\nreg is 0x%02x.\n", read_cmd[0]);
            } else
                fprintf(stderr, "reg is not a digital value.\n");
            break;
        case 'n':
            if (isdigit(*optarg)) {
                sscanf(optarg, "0x%x", &num);
                //num = atoi(optarg);
                printf("\nnum is %d.\n", num);
            } else
                fprintf(stderr, "num is not a digital value.\n");
            break;
        case 'w':
            if (isdigit(*optarg)) {
                wr_flag = 1;
                sscanf(optarg, "0x%hhx", &write_cmd[1]);
                //write_cmd[1] = atoi(optarg);
                printf("\nwrite val is 0x%02x.\n", write_cmd[1]);
            } else
                fprintf(stderr, "write val is not a digital value.\n");
            break;
        default:
            fprintf(stderr, "Invalid switch or option needs an argument.\n");
            break;
        }
    }

    //checkout i2c port and addr.
    for (i = 0; i < chip_num; i++) {
        if (twi_addr == twi_dev[i].addr)
            break;
    }
    if (i >= chip_num) {
        fprintf(stderr, "the addr is error.\n");
        goto ac108_reg_exit;
    }
    if ((read_cmd[0] > AC108_REG_MAX) ||
        (write_cmd[0] > AC108_REG_MAX)) {
        fprintf(stderr, "the reg is over 0x%02x error.\n", AC108_REG_MAX);
        goto ac108_reg_exit;
    }

    if (wr_flag) {
        ret = ac108_write(&twi_dev[i], write_cmd[0], write_cmd[1]);
        if (ret != TWI_STATUS_OK) {
            snd_err("write error [REG-0x%02x,val-0x%02x] ret = %d.\n",
                write_cmd[0], write_cmd[1], ret);
        }
        ret = ac108_read(&twi_dev[i], read_cmd[0], read_data);
        if (ret != TWI_STATUS_OK) {
            snd_err("write error [I2C%d-0x%0x] REG=0x%02x, val=0x%02x] ret = %d.\n",
                twi_dev[i].bus, twi_dev[i].addr, read_cmd[0], read_data[0], ret);
            goto ac108_reg_exit;
        }
        if (read_data[0] == write_cmd[1]) {
            printf("write success, [I2C%d-0x%0x] REG=0x%02x, val=0x%02x] ret = %d.\n",
                twi_dev[i].bus, twi_dev[i].addr, read_cmd[0], read_data[0], ret);
        } else {
            printf("write val:0x%02x failed, [I2C%d-0x%0x] REG=0x%02x, val=0x%02x] ret = %d.\n",
                write_cmd[1], twi_dev[i].bus, twi_dev[i].addr, read_cmd[0], read_data[0], ret);
        }
    } else {
        for (i = 0; i < num; i++) {
            ret = ac108_read(&twi_dev[i], read_cmd[0], read_data);
            if (ret != TWI_STATUS_OK) {
                snd_err("read error [I2C%d-0x%0x] REG=0x%02x, val=0x%02x] ret = %d.\n",
                    twi_dev[i].bus, twi_dev[i].addr, read_cmd[0], read_data[0], ret);
                goto ac108_reg_exit;
            } else {
                printf("read success. [I2C%d-0x%0x] REG=0x%02x, val=0x%02x].\n",
                    twi_dev[i].bus, twi_dev[i].addr, read_cmd[0], read_data[0]);
            }
        }
    }

ac108_reg_exit:
    return 0;
}
FINSH_FUNCTION_EXPORT_CMD(cmd_ac108_reg, ac108_reg, ac108 regs dump);
