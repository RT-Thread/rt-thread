/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fes8336.h
 * Date: 2023-05-23 09:15:16
 * LastEditTime: 2023-05-23 17:15:16
 * Description:  This file is for es8336 defintion
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  wangzongqiang    2023/05/23     init
 */

#ifndef FES8336_H
#define FES8336_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* includes */

#include "ftypes.h"
#include "fi2c.h"
#include "fmio.h"
#include "fmio_hw.h"
#include "fparameters.h"


struct reg_default {
	unsigned int reg;
	unsigned int def;
};


typedef enum
{
    AUDIO_PCM_STREAM_WORD_LENGTH_16 = 0, /*the trams audio length word length*/
    AUDIO_PCM_STREAM_WORD_LENGTH_20,
    AUDIO_PCM_STREAM_WORD_LENGTH_24,
    AUDIO_PCM_STREAM_WORD_LENGTH_32,
    AUDIO_PCM_STREAM_WORD_LENGTH
} FEs8336PcmWordLength;

typedef enum
{
    AUDIO_PCM_STREAM_CAPTURE = 0,  /*es8336 work mode*/
    AUDIO_PCM_STREAM_PLAYBACK,
    AUDIO_PCM_STREAM_TYPE

} FEs8336WorkFormat;

typedef enum
{
    AUDIO_PCM_BIAS_LEVEL_OFF = 0,  /*the bias level of es8336, use the default value:AUDIO_PCM_BIAS_LEVEL_ON*/
    AUDIO_PCM_BIAS_LEVEL_STANDBY,
    AUDIO_PCM_BIAS_LEVEL_REPARE,
    AUDIO_PCM_BIAS_LEVEL_ON,
    AUDIO_PCM_BIAS_LEVEL
} FEs8336BiasLevel;

typedef enum
{
    ONE_BYTE_OF_MEMORY = 1,/*8 bits of memory address*/
    TWO_BYTES_OF_MEMORY,/*16 bits of memory address*/
    THREE_BYTES_OF_MEMORY,/*24 bits of memory address*/
    FOUR_BYTES_OF_MEMORY,/*32 bits of memory address*/
    ES836_BYTES_OF_MEMORY
} FEs8336SizeofRegister;

typedef struct 
{
    void *pram;
}FEs8336;

#define FES8336_SUCCESS FT_SUCCESS
/* ES8336 register space */
/*
 * RESET Control
 */
#define ES8336_RESET_REG00             0x00   /*register of reset*/
/*
 * Clock Managerment
 */
#define ES8336_CLKMGR_CLKSW_REG01      0x01  /* clock manager*/
#define ES8336_CLKMGR_CLKSEL_REG02     0x02  /* clock manager*/
#define ES8336_CLKMGR_ADCOSR_REG03     0x03  /*ADC delta sigma over sample rate*/
#define ES8336_CLKMGR_ADCDIV1_REG04    0x04  /*ADC clock divider*/
#define ES8336_CLKMGR_ADCDIV2_REG05    0x05  /*ADC internal divider*/
#define ES8336_CLKMGR_DACDIV1_REG06    0x06  /*DAC clock divider*/
#define ES8336_CLKMGR_DACDIV2_REG07    0x07  /*DAC internal divider*/
#define ES8336_CLKMGR_CPDIV_REG08      0x08  /*charge pump clock divider*/
/*
 * SDP Control
 */
#define ES8336_SDP_MS_BCKDIV_REG09     0x09 /*serial data port clk control*/
#define ES8336_SDP_ADCFMT_REG0A        0x0a /*ADC sdp config*/
#define ES8336_SDP_DACFMT_REG0B        0x0b /*DAC sdp config*/
/*
 * System Control
 */
#define ES8336_SYS_VMIDSEL_REG0C       0x0c /*vmidSel config*/
#define ES8336_SYS_PDN_REG0D           0x0d /*power down config*/
#define ES8336_SYS_LP1_REG0E           0x0e /*low power mode*/
#define ES8336_SYS_LP2_REG0F           0x0f /*low power mode of output*/
#define ES8336_SYS_VMIDLOW_REG10       0x10 /*DAC bias selection*/
#define ES8336_SYS_VSEL_REG11          0x11 /*system register */
#define ES8336_SYS_REF_REG12           0x12 /*system register*/
/*
 * HP Mixer
 */
#define ES8336_HPMIX_SEL_REG13         0x13
#define ES8336_HPMIX_SWITCH_REG14      0x14 /*RDAC and LDAC signal*/
#define ES8336_HPMIX_PDN_REG15         0x15 /*LHP and RHP config*/
#define ES8336_HPMIX_VOL_REG16         0x16 /*the gain of dB*/
/*
 * Charge Pump Headphone driver
 */
#define ES8336_CPHP_OUTEN_REG17        0x17 /*LHP AND RHP output config*/
#define ES8336_CPHP_ICAL_VOL_REG18     0x18 /*the gain of dB of HPL*/
#define ES8336_CPHP_PDN1_REG19         0x19 /*HP config*/
#define ES8336_CPHP_PDN2_REG1A         0x1a /*CP config*/
#define ES8336_CPHP_LDOCTL_REG1B       0x1b /*voltage of hp*/
/*
 * Calibration
 */
#define ES8336_CAL_TYPE_REG1C         0x1c /*HPL and HPR config*/
#define ES8336_CAL_SET_REG1D          0x1d /*ica and mcal config*/
#define ES8336_CAL_HPLIV_REG1E        0x1e /*HPL ical config*/
#define ES8336_CAL_HPRIV_REG1F        0x1f /*HPL ical config*/
#define ES8336_CAL_HPLMV_REG20        0x20 /*HPL mcal config*/
#define ES8336_CAL_HPRMV_REG21        0x21 /*HPL mcal config*/
/*
 * ADC Control
 */
#define ES8336_ADC_PDN_LINSEL_REG22   0x22 /*PGA input select*/
#define ES8336_ADC_PGAGAIN_REG23      0x23 /*left PGA gain*/
#define ES8336_ADC_D2SEPGA_REG24      0x24 /*DF2SE config*/
#define ES8336_ADC_DMIC_REG25         0x25 /*ADC config*/
#define ES8336_ADC_MUTE_REG26         0x26 /*ADC mute config*/
#define ES8336_ADC_VOLUME_REG27       0x27 /*ADC volume config*/
#define ES8336_ADC_VOLUME_REG28       0x28 /*ADC volume config*/
#define ES8336_ADC_ALC1_REG29         0x29 /*ALC config and ALC PGA max gain*/
#define ES8336_ADC_ALC2_REG2A         0x2a /*ALC config and ALC PGA min gain*/
#define ES8336_ADC_ALC3_REG2B         0x2b /*ALC config*/
#define ES8336_ADC_ALC4_REG2C         0x2c /*ALC decay and attack config*/
#define ES8336_ADC_ALC5_REG2D         0x2d /*windows size for peak detector*/
#define ES8336_ADC_ALC6_REG2E         0x2e /* ALC noise gate config*/
/*
 * DAC Control
 */
#define ES8336_DAC_PDN_REG2F          0x2f /*DAC control of power down*/
#define ES8336_DAC_SET1_REG30         0x30 /*DAC data select and mute*/
#define ES8336_DAC_SET2_REG31         0x31 /*DAC config and control*/
#define ES8336_DAC_SET3_REG32         0x32 /*DAC fs mode and mute config*/
#define ES8336_DAC_VOLL_REG33         0x33 /*DAC volumel of left*/
#define ES8336_DAC_VOLR_REG34         0x34 /*DAC volumel of right*/
/*
 * GPIO
 */
#define ES8336_GPIO_SEL_REG4D         0x4D /*gpio select*/
#define ES8336_GPIO_DEBUNCE_INT_REG4E 0x4E /*button and insert debounce*/
#define ES8336_GPIO_FLAG              0x4F /*GM config*/
/*
 * TEST MODE
 */
#define ES8336_TESTMODE_REG50         0x50 /*test register*/
#define ES8336_TEST1_REG51            0x51
#define ES8336_TEST2_REG52            0x52
#define ES8336_TEST3_REG53            0x53

#define ES8336_IFACE            ES8336_SDP_MS_BCKDIV_REG09
#define ES8336_ADC_IFACE        ES8336_SDP_ADCFMT_REG0A
#define ES8336_DAC_IFACE        ES8336_SDP_DACFMT_REG0B

#define ES8336_REGNUM      84


/* REGISTER 0x01 CLOCK MANAGER */
#define ES8336_CLKMGR_MCLK_DIV_MASK (0x1<<7)
#define ES8336_CLKMGR_MCLK_DIV_NML  (0x0<<7)
#define ES8336_CLKMGR_MCLK_DIV_1    (0x1<<7)
#define ES8336_CLKMGR_ADC_MCLK_MASK (0x1<<3)
#define ES8336_CLKMGR_ADC_MCLK_EN   (0x1<<3)
#define ES8336_CLKMGR_ADC_MCLK_DIS  (0x0<<3)
#define ES8336_CLKMGR_DAC_MCLK_MASK (0x1<<2)
#define ES8336_CLKMGR_DAC_MCLK_EN   (0x1<<2)
#define ES8336_CLKMGR_DAC_MCLK_DIS  (0x0<<2)
#define ES8336_CLKMGR_ADC_ANALOG_MASK   (0x1<<1)
#define ES8336_CLKMGR_ADC_ANALOG_EN (0x1<<1)
#define ES8336_CLKMGR_ADC_ANALOG_DIS    (0x0<<1)
#define ES8336_CLKMGR_DAC_ANALOG_MASK   (0x1<<0)
#define ES8336_CLKMGR_DAC_ANALOG_EN (0x1<<0)
#define ES8336_CLKMGR_DAC_ANALOG_DIS    (0x0<<0)

/* REGISTER 0x0A */
#define ES8336_ADCWL_MASK   (0x7 << 2)
#define ES8336_ADCWL_32     (0x4 << 2)
#define ES8336_ADCWL_24     (0x0 << 2)
#define ES8336_ADCWL_20     (0x1 << 2)
#define ES8336_ADCWL_18     (0x2 << 2)
#define ES8336_ADCWL_16     (0x3 << 2)
#define ES8336_ADCFMT_MASK  (0x3 << 0)
#define ES8336_ADCFMT_I2S   (0x0 << 0)
#define ES8336_ADCWL_LEFT   (0x1 << 0)
#define ES8336_ADCWL_RIGHT  (0x2 << 0)
#define ES8336_ADCWL_PCM    (0x3 << 0)

/* REGISTER 0x0B */
#define ES8336_DACWL_MASK   (0x7 << 2)
#define ES8336_DACWL_32     (0x4 << 2)
#define ES8336_DACWL_24     (0x0 << 2)
#define ES8336_DACWL_20     (0x1 << 2)
#define ES8336_DACWL_18     (0x2 << 2)
#define ES8336_DACWL_16     (0x3 << 2)
#define ES8336_DACFMT_MASK  (0x3 << 0)
#define ES8336_DACFMT_I2S   (0x0 << 0)
#define ES8336_DACWL_LEFT   (0x1 << 0)
#define ES8336_DACWL_RIGHT  (0x2 << 0)
#define ES8336_DACWL_PCM    (0x3 << 0)

/*init the es8336, include the mio and i2c params*/
FError FEs8336Init(void);

/*reset the es8336*/
void FEs8336Reset(void);

/*probe the es8336 regs*/
void FEs8336RegsProbe(void);

/*shut down the es8336*/
FError FEs8336ShutDown(FEs8336WorkFormat work_mode);

/*mute down the es8336*/
FError FEs8336MuteDown(u32 mute);

/*set the es8336 bias level*/
FError FEs8336SetBiasLevel(FEs8336BiasLevel level);

/*set the es8336 word lenth*/
FError FEs8336SetFormat(FEs8336PcmWordLength length, FEs8336WorkFormat format);

void FEs8336InitRegs(void);

FError FEs8336SetVolumel(FEs8336WorkFormat work_mode, u32 value);
/*start up the es8336*/
FError FEs8336Startup(FEs8336WorkFormat format);

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

