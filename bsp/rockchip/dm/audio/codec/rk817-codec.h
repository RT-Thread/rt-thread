/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#ifndef __RK817_CODEC_H__
#define __RK817_CODEC_H__

#include "rk8xx.h"

#define RK817_CODEC_PLAYBACK    1
#define RK817_CODEC_CAPTURE     2
#define RK817_CODEC_ALL         3

#define RK817_DAC_VOL_MIN       3
#define RK817_DAC_VOL_MAX       255
#define RK817_DEFAULT_HP_VOL    0x03
#define RK817_DEFAULT_SPK_VOL   0x0a

#define ADC_DIG_CLK_MASK        (0xf << 4)
#define ADC_DIG_CLK_EN          (0xe << 4)
#define ADC_DIG_CLK_DIS         (0x0 << 4)
#define DAC_DIG_CLK_MASK        (0xf << 0)
#define DAC_DIG_CLK_EN          (0xe << 0)
#define DAC_DIG_CLK_DIS         (0x0 << 0)

#define I2STX_EN_MASK           RT_BIT(4)
#define I2STX_EN                RT_BIT(4)
#define I2STX_DIS               0

#define RK817_I2S_MODE_MASK     RT_BIT(0)
#define RK817_I2S_MODE_SLV      0
#define RK817_I2S_MODE_MST      RT_BIT(0)

#define DACSRT_MASK             0x7
#define DACMT_ENABLE            RT_BIT(0)
#define DACMT_DISABLE           0

#define VDW_RX_16BITS           0x0f
#define VDW_TX_16BITS           0x0f

#define PWD_DACBIAS_MASK        RT_BIT(3)
#define PWD_DACBIAS_DOWN        RT_BIT(3)
#define PWD_DACBIAS_ON          0
#define PWD_DACD_MASK           RT_BIT(2)
#define PWD_DACD_DOWN           RT_BIT(2)
#define PWD_DACD_ON             0
#define PWD_DACL_MASK           RT_BIT(1)
#define PWD_DACL_DOWN           RT_BIT(1)
#define PWD_DACL_ON             0
#define PWD_DACR_MASK           RT_BIT(0)
#define PWD_DACR_DOWN           RT_BIT(0)
#define PWD_DACR_ON             0

#define PLL_PW_DOWN             RT_BIT(0)
#define PLL_PW_UP               0

#define HP_PATH                 3
#define OFF                     0

struct rk817_codec_config
{
    rt_uint32_t samplerate;
    rt_uint16_t samplebits;
    rt_uint32_t mclk_rate;
};

struct rk817_codec;

rt_err_t rk817_codec_bind_rk8xx(struct rk817_codec **out_codec, struct rk8xx *rk8xx);
rt_err_t rk817_codec_hw_params(struct rk817_codec *codec, const struct rk817_codec_config *cfg);
rt_err_t rk817_codec_start(struct rk817_codec *codec);
rt_err_t rk817_codec_stop(struct rk817_codec *codec);
rt_err_t rk817_codec_set_volume(struct rk817_codec *codec, rt_uint8_t volume);
struct rk817_codec *rk817_codec_find(struct rt_ofw_node *np);
struct rk8xx *rk817_codec_rk8xx_from_np(struct rt_ofw_node *np);

#endif /* __RK817_CODEC_H__ */
