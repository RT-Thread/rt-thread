/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __SPACEMIT_ES8326_H__
#define __SPACEMIT_ES8326_H__

#include <drivers/misc.h>

#define ES8326_RESET                 0x00
#define ES8326_CLK_CTL               0x01
#define ES8326_CLK_INV               0x02
#define ES8326_CLK_RESAMPLE          0x03
#define ES8326_CLK_DIV1              0x04
#define ES8326_CLK_DIV2              0x05
#define ES8326_CLK_DLL               0x06
#define ES8326_CLK_MUX               0x07
#define ES8326_CLK_ADC_SEL           0x08
#define ES8326_CLK_DAC_SEL           0x09
#define ES8326_CLK_ADC_OSR           0x0a
#define ES8326_CLK_DAC_OSR           0x0b
#define ES8326_CLK_DIV_CPC           0x0c
#define ES8326_CLK_DIV_BCLK          0x0d
#define ES8326_CLK_TRI               0x0e
#define ES8326_CLK_VMIDS1            0x10
#define ES8326_CLK_VMIDS2            0x11
#define ES8326_CLK_CAL_TIME          0x12
#define ES8326_FMT                   0x13
#define ES8326_DAC_MUTE              0x14
#define ES8326_ADC_MUTE              0x15
#define ES8326_ANA_PDN               0x16
#define ES8326_VMIDSEL               0x18
#define ES8326_ANA_LP                0x19
#define ES8326_ANA_MICBIAS           0x1b
#define ES8326_ANA_VSEL              0x1c
#define ES8326_VMIDLOW               0x22
#define ES8326_PGAGAIN               0x23
#define ES8326_HP_DRIVER             0x24
#define ES8326_DAC2HPMIX             0x25
#define ES8326_HP_VOL                0x26
#define ES8326_HP_CAL                0x27
#define ES8326_HP_DRIVER_REF         0x28
#define ES8326_ADC1_SRC              0x2a
#define ES8326_ADC2_SRC              0x2b
#define ES8326_HP_OFFSET_CAL         0x4a
#define ES8326_HPL_OFFSET_INI        0x4b
#define ES8326_HPR_OFFSET_INI        0x4c
#define ES8326_DAC_DSM               0x4d
#define ES8326_DAC_RAMPRATE          0x4e
#define ES8326_DAC_VPPSCALE          0x4f
#define ES8326_DAC_VOL               0x50
#define ES8326_DAC_CROSSTALK         0x55
#define ES8326_HPJACK_TIMER          0x56
#define ES8326_HPDET_TYPE            0x57
#define ES8326_INT_SOURCE            0x58
#define ES8326_INTOUT_IO             0x59
#define ES8326_SDINOUT1_IO           0x5a
#define ES8326_SDINOUT23_IO          0x5b
#define ES8326_HP_MISC               0xf7
#define ES8326_PULLUP_CTL            0xf9
#define ES8326_HPDET_STA             0xfb
#define ES8326_CSM_MUTE_STA          0xfc
#define ES8326_CHIP_ID1              0xfd
#define ES8326_CHIP_ID2              0xfe
#define ES8326_CHIP_VERSION          0xff

#define ES8326_CSM_ON                RT_BIT(7)
#define ES8326_CLK_ON                0x7e
#define ES8326_S16_LE                (3 << 2)
#define ES8326_DATA_LEN_MASK         (7 << 2)
#define ES8326_MUTE_MASK             (3 << 0)
#define ES8326_MUTE                  (3 << 0)
#define ES8326_MIC_SEL_MASK          (3 << 4)
#define ES8326_MIC1_SEL              RT_BIT(4)
#define ES8326_HP_OFF                0
#define ES8326_HP_ON                 0x77
#define ES8326_HP_DET_SRC_PIN9       RT_BIT(4)
#define ES8326_HP_TYPE_AUTO          RT_BIT(0)
#define ES8326_INT_SRC_PIN9          RT_BIT(3)
#define ES8326_IO_INPUT              0
#define ES8326_IO_DMIC_CLK           9
#define ES8326_SDINOUT1_SHIFT        4
#define ES8326_HPINSERT_FLAG         RT_BIT(1)
#define ES8326_VERSION_B             3

#define ES8326_ADC_AMIC              0x22
#define ES8326_ADC_DMIC              0x44

#endif /* __SPACEMIT_ES8326_H__ */
