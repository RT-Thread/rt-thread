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
 * FilePath: fes8336.c
 * Date: 2023-05-23 17:14:36
 * LastEditTime: 2023-05-23 17:14:36
 * Description:  This file is for providing functions to file es8336.c
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  wangzongqiang    2023/05/23     init
 */
#include <string.h>
#include <stdio.h>
#include "ftypes.h"
#include "fdrivers_port.h"
#include "fes8336.h"
#include "fiopad.h"

#include "fparameters.h"
#include "fi2c.h"
#include "fi2c_hw.h"
#include "fmio_hw.h"
#include "fmio.h"

#if defined(SOC_TARGET_E2000)
    #define ES8336_MIO FMIO14_ID
#elif defined(TARDIGRADE)
    #define ES8336_MIO FMIO14_ID
#endif

/*i2s slave address*/
#define ES8336_ADDR 0x10

static FIOPadCtrl iopad_ctrl;

/*es8336 register default value*/
static const struct  reg_default es8336_reg_defaults[] =
{
    {0x00, 0x03}, {0x01, 0x03}, {0x02, 0x00}, {0x03, 0x20},
    {0x04, 0x11}, {0x05, 0x00}, {0x06, 0x11}, {0x07, 0x00},
    {0x08, 0x00}, {0x09, 0x01}, {0x0a, 0x00}, {0x0b, 0x00},
    {0x0c, 0xf8}, {0x0d, 0x3f}, {0x0e, 0x00}, {0x0f, 0x00},
    {0x10, 0x01}, {0x11, 0xfc}, {0x12, 0x28}, {0x13, 0x00},
    {0x14, 0x00}, {0x15, 0x33}, {0x16, 0x00}, {0x17, 0x00},
    {0x18, 0x88}, {0x19, 0x06}, {0x1a, 0x22}, {0x1b, 0x03},
    {0x1c, 0x0f}, {0x1d, 0x00}, {0x1e, 0x80}, {0x1f, 0x80},
    {0x20, 0x00}, {0x21, 0x00}, {0x22, 0xc0}, {0x23, 0x00},
    {0x24, 0x01}, {0x25, 0x08}, {0x26, 0x10}, {0x27, 0xc0},
    {0x28, 0x00}, {0x29, 0x1c}, {0x2a, 0x00}, {0x2b, 0xb0},
    {0x2c, 0x32}, {0x2d, 0x03}, {0x2e, 0x00}, {0x2f, 0x11},
    {0x30, 0x10}, {0x31, 0x00}, {0x32, 0x00}, {0x33, 0xc0},
    {0x34, 0xc0}, {0x35, 0x1f}, {0x36, 0xf7}, {0x37, 0xfd},
    {0x38, 0xff}, {0x39, 0x1f}, {0x3a, 0xf7}, {0x3b, 0xfd},
    {0x3c, 0xff}, {0x3d, 0x1f}, {0x3e, 0xf7}, {0x3f, 0xfd},
    {0x40, 0xff}, {0x41, 0x1f}, {0x42, 0xf7}, {0x43, 0xfd},
    {0x44, 0xff}, {0x45, 0x1f}, {0x46, 0xf7}, {0x47, 0xfd},
    {0x48, 0xff}, {0x49, 0x1f}, {0x4a, 0xf7}, {0x4b, 0xfd},
    {0x4c, 0xff}, {0x4d, 0x00}, {0x4e, 0x00}, {0x4f, 0xff},
    {0x50, 0x00}, {0x51, 0x00}, {0x52, 0x00}, {0x53, 0x00},
};

static FI2c master_device;
static FMioCtrl es8336;

/**
 * @name: FEs8336WriteByte
 * @msg:  write one byte to es8336
 * @param Null
 * @return FES8336_SUCCESS or others
 */
static FError FEs8336WriteByte(u32 mem_addr, u8 value)
{
    FError ret = FES8336_SUCCESS;
    FI2c *instance_p = &master_device;
    ret = FI2cMasterWritePoll(instance_p, mem_addr, ONE_BYTE_OF_MEMORY, &value, 1);
    return ret;
}

/**
 * @name: FEs8336ReadByte
 * @msg:  read one byte to es8336
 * @param Null
 * @return FES8336_SUCCESS or others
 */
static FError FEs8336ReadByte(u32 mem_addr, u8 *value)
{
    FError ret = FES8336_SUCCESS;
    FI2c *instance_p = &master_device;
    ret = FI2cMasterReadPoll(instance_p, mem_addr, ONE_BYTE_OF_MEMORY, value, 1);
    return ret;
}


/**
 * @name: FEs8336Init
 * @msg:  init the es8336, include the mio and i2c params
 * @param Null
 * @return FES8336_SUCCESS or others
 */
FError FEs8336Init(void)
{
    FError ret = FES8336_SUCCESS;
    FMioCtrl *pctrl = &es8336;
    const FMioConfig *mioconfig_p ;
    FI2c *instance_p = &master_device;
    const FI2cConfig *i2cconfig_p;
    FI2cConfig i2cconfig;

    mioconfig_p = FMioLookupConfig(ES8336_MIO);
    if (NULL == mioconfig_p)
    {
        printf("Mio error inval parameters.\r\n");
        return FMIO_ERR_INVAL_PARM;
    }
    pctrl->config = *mioconfig_p;
    ret = FMioFuncInit(pctrl, FMIO_FUNC_SET_I2C);
    if (ret != FES8336_SUCCESS)
    {
        printf("ES8336_MIO MioInit error.\r\n");
        return ret;
    }
    /* get standard config of i2c */
    i2cconfig_p = FI2cLookupConfig(FI2C0_ID);
    /* Modify configuration */
    i2cconfig = *i2cconfig_p;
    i2cconfig.base_addr = FMioFuncGetAddress(pctrl, FMIO_FUNC_SET_I2C);
    i2cconfig.irq_num = FMioFuncGetIrqNum(pctrl, FMIO_FUNC_SET_I2C);
    i2cconfig.slave_addr = ES8336_ADDR;
    FI2cDeInitialize(instance_p);
    /* Initialization */
    ret = FI2cCfgInitialize(instance_p, &i2cconfig);
    if (ret != FES8336_SUCCESS)
    {
        return ret;
    }
    /*  callback function for FI2C_MASTER_INTR_EVT interrupt  */
    instance_p->master_evt_handlers[FI2C_EVT_MASTER_TRANS_ABORTED] = NULL;
    instance_p->master_evt_handlers[FI2C_EVT_MASTER_READ_DONE] = NULL;
    instance_p->master_evt_handlers[FI2C_EVT_MASTER_WRITE_DONE] = NULL;

    return ret;
}

/**
 * @name: FEs8336InitRegs
 * @msg:  init the es8336 regs
 * @return Null
 */
void FEs8336InitRegs(void)
{
    FEs8336WriteByte(ES8336_RESET_REG00, 0x3f);
    FDriverUdelay(500); /*ensure reset success*/
    FEs8336WriteByte(ES8336_RESET_REG00, 0x00);
    FEs8336WriteByte(ES8336_SYS_VMIDSEL_REG0C, 0xFF);/*vmisel config */
    FDriverUdelay(30);
    FEs8336WriteByte(ES8336_CLKMGR_CLKSEL_REG02, 0x08);
    FEs8336WriteByte(ES8336_CLKMGR_ADCOSR_REG03, 0x20);
    FEs8336WriteByte(ES8336_CLKMGR_ADCDIV1_REG04, 0x11);
    FEs8336WriteByte(ES8336_CLKMGR_ADCDIV2_REG05, 0x00);
    FEs8336WriteByte(ES8336_CLKMGR_DACDIV1_REG06, 0x11);
    FEs8336WriteByte(ES8336_CLKMGR_DACDIV2_REG07, 0x00);
    FEs8336WriteByte(ES8336_CLKMGR_CPDIV_REG08, 0x00);
    FEs8336WriteByte(ES8336_SDP_MS_BCKDIV_REG09, 0x04);
    FEs8336WriteByte(ES8336_CLKMGR_CLKSW_REG01, 0x7F);
    FEs8336WriteByte(ES8336_CAL_TYPE_REG1C, 0x0F);
    FEs8336WriteByte(ES8336_CAL_HPLIV_REG1E, 0x90);
    FEs8336WriteByte(ES8336_CAL_HPRIV_REG1F, 0x90);
    FEs8336WriteByte(ES8336_ADC_VOLUME_REG27, 0x00);
    FEs8336WriteByte(ES8336_ADC_PDN_LINSEL_REG22, 0xc0);
    FEs8336WriteByte(ES8336_ADC_D2SEPGA_REG24, 0x00);
    FEs8336WriteByte(ES8336_ADC_DMIC_REG25, 0x08);
    FEs8336WriteByte(ES8336_DAC_SET1_REG30, 0x00);
    FEs8336WriteByte(ES8336_DAC_SET2_REG31, 0x20);
    FEs8336WriteByte(ES8336_DAC_SET3_REG32, 0x00);
    FEs8336WriteByte(ES8336_DAC_VOLL_REG33, 0x00);
    FEs8336WriteByte(ES8336_DAC_VOLR_REG34, 0x00);
    FEs8336WriteByte(ES8336_SDP_ADCFMT_REG0A, 0x00);
    FEs8336WriteByte(ES8336_SDP_DACFMT_REG0B, 0x00);
    FEs8336WriteByte(ES8336_SYS_VMIDLOW_REG10, 0x11);
    FEs8336WriteByte(ES8336_SYS_VSEL_REG11, 0xFC);
    FEs8336WriteByte(ES8336_SYS_REF_REG12, 0x28);
    FEs8336WriteByte(ES8336_SYS_LP1_REG0E, 0x04);
    FEs8336WriteByte(ES8336_SYS_LP2_REG0F, 0x0C);
    FEs8336WriteByte(ES8336_DAC_PDN_REG2F, 0x11);
    FEs8336WriteByte(ES8336_HPMIX_SEL_REG13, 0x00);
    FEs8336WriteByte(ES8336_HPMIX_SWITCH_REG14, 0x88);
    FEs8336WriteByte(ES8336_HPMIX_PDN_REG15, 0x00);
    FEs8336WriteByte(ES8336_HPMIX_VOL_REG16, 0xBB);
    FEs8336WriteByte(ES8336_CPHP_PDN2_REG1A, 0x10);
    FEs8336WriteByte(ES8336_CPHP_LDOCTL_REG1B, 0x30);
    FEs8336WriteByte(ES8336_CPHP_PDN1_REG19, 0x02);
    FEs8336WriteByte(ES8336_CPHP_ICAL_VOL_REG18, 0x00);
    FEs8336WriteByte(ES8336_GPIO_SEL_REG4D, 0x02);
    FEs8336WriteByte(ES8336_GPIO_DEBUNCE_INT_REG4E, 0x02);
    FEs8336WriteByte(ES8336_TESTMODE_REG50, 0xA0);
    FEs8336WriteByte(ES8336_TEST1_REG51, 0x00);
    FEs8336WriteByte(ES8336_TEST2_REG52, 0x00);
    FEs8336WriteByte(ES8336_SYS_PDN_REG0D, 0x00);
    FEs8336WriteByte(ES8336_RESET_REG00, 0xC0);
    FDriverUdelay(50);
    FEs8336WriteByte(ES8336_ADC_PGAGAIN_REG23, 0x60);
    FEs8336WriteByte(ES8336_ADC_D2SEPGA_REG24, 0x01);
    /* adc ds mode, HPF enable */
    FEs8336WriteByte(ES8336_ADC_DMIC_REG25, 0x08);
    FEs8336WriteByte(ES8336_ADC_ALC1_REG29, 0xcd);
    FEs8336WriteByte(ES8336_ADC_ALC2_REG2A, 0x08);
    FEs8336WriteByte(ES8336_ADC_ALC3_REG2B, 0xa0);
    FEs8336WriteByte(ES8336_ADC_ALC4_REG2C, 0x05);
    FEs8336WriteByte(ES8336_ADC_ALC5_REG2D, 0x06);
    FEs8336WriteByte(ES8336_ADC_ALC6_REG2E, 0x61);
    return ;
}

/**
 * @name: FEs8336Reset
 * @msg:  reset the es8336
 * @return Null
 */
void FEs8336Reset(void)
{
    u8 value = 0;
    value = FEs8336ReadByte(ES8336_RESET_REG00, &value);
    FEs8336WriteByte(ES8336_RESET_REG00, 0x3F);
    FDriverUdelay(100);
    FEs8336WriteByte(ES8336_RESET_REG00, 0x03);
}

/**
 * @name: FEs8336RegsProbe
 * @msg:  probe the es8336 regs
 * @return Null
 */
void FEs8336RegsProbe(void)
{
    u8 value = 0;
    FEs8336Reset();
    FEs8336InitRegs();
    FEs8336WriteByte(ES8336_GPIO_SEL_REG4D, 0x02);
    /* max debance time, enable interrupt, low active */
    FEs8336WriteByte(ES8336_GPIO_DEBUNCE_INT_REG4E, 0xf3);
    /* es8336_set_bias_level(codec, SND_SOC_BIAS_OFF); */
    FEs8336WriteByte(ES8336_CPHP_OUTEN_REG17, 0x00);
    FEs8336WriteByte(ES8336_DAC_PDN_REG2F, 0x11);
    FEs8336WriteByte(ES8336_CPHP_LDOCTL_REG1B, 0x03);
    FEs8336WriteByte(ES8336_CPHP_PDN2_REG1A, 0x22);
    FEs8336WriteByte(ES8336_CPHP_PDN1_REG19, 0x06);
    FEs8336WriteByte(ES8336_HPMIX_SWITCH_REG14, 0x00);
    FEs8336WriteByte(ES8336_HPMIX_PDN_REG15, 0x33);
    FEs8336WriteByte(ES8336_HPMIX_VOL_REG16, 0x00);
    FEs8336WriteByte(ES8336_SYS_LP1_REG0E, 0xFF);
    FEs8336WriteByte(ES8336_SYS_LP2_REG0F, 0xFF);
    FEs8336WriteByte(ES8336_CLKMGR_CLKSW_REG01, 0xF3);
    FEs8336WriteByte(ES8336_ADC_PDN_LINSEL_REG22, 0xD0);

    return ;
}

/**
 * @name: FEs8336Startup
 * @msg:  start up the es8336
 * @param (FEs8336WorkFormat} format ,the workmode of  PCM
 * @return FES8336_SUCCESS
 */

FError FEs8336Startup(FEs8336WorkFormat format)
{
    FError ret = FES8336_SUCCESS;
    FEs8336WriteByte(ES8336_RESET_REG00, 0xC0);
    FEs8336WriteByte(ES8336_SYS_PDN_REG0D, 0x00);

    if (format == AUDIO_PCM_STREAM_PLAYBACK)
    {
        FEs8336WriteByte(ES8336_CLKMGR_CLKSW_REG01, 0x77);
        FEs8336WriteByte(ES8336_SYS_LP1_REG0E, 0x3F);
        FEs8336WriteByte(ES8336_SYS_LP2_REG0F, 0x1F);
        FEs8336WriteByte(ES8336_HPMIX_SWITCH_REG14, 0x88);
        FEs8336WriteByte(ES8336_HPMIX_PDN_REG15, 0x00);
        FEs8336WriteByte(ES8336_HPMIX_VOL_REG16, 0xBB);
        FEs8336WriteByte(ES8336_CPHP_PDN2_REG1A, 0x10);
        FEs8336WriteByte(ES8336_CPHP_LDOCTL_REG1B, 0x30);
        FEs8336WriteByte(ES8336_CPHP_PDN1_REG19, 0x02);
        FEs8336WriteByte(ES8336_DAC_PDN_REG2F, 0x00);
        FEs8336WriteByte(ES8336_CPHP_OUTEN_REG17, 0x66);
        FEs8336WriteByte(ES8336_RESET_REG00, 0xc0);
        FEs8336WriteByte(ES8336_DAC_VOLL_REG33, 0x0);
        FEs8336WriteByte(ES8336_DAC_VOLR_REG34, 0x28);
        FEs8336WriteByte(ES8336_ADC_PDN_LINSEL_REG22, 0xf0);
    }
    else
    {
        FEs8336WriteByte(ES8336_CLKMGR_CLKSW_REG01, 0x7f);
        FEs8336WriteByte(ES8336_ADC_PDN_LINSEL_REG22, 0x30);
    }

    return ret;
}

/**
 * @name: FEs8336ShutDown
 * @msg:  shut down the es8336
 * @param (FEs8336WorkFormat} work_mode ,the type of workmode of PCM
 * @return FES8336_SUCCESS
 */
FError FEs8336ShutDown(FEs8336WorkFormat work_mode)
{
    FError ret = FES8336_SUCCESS;
    u8 value = 0;
    if (work_mode == AUDIO_PCM_STREAM_PLAYBACK)
    {
        FEs8336WriteByte(ES8336_CPHP_OUTEN_REG17, 0x00);
        FEs8336WriteByte(ES8336_DAC_PDN_REG2F, 0x11);
        FEs8336WriteByte(ES8336_CPHP_LDOCTL_REG1B, 0x03);
        FEs8336WriteByte(ES8336_CPHP_PDN2_REG1A, 0x22);
        FEs8336WriteByte(ES8336_CPHP_PDN1_REG19, 0x06);
        FEs8336WriteByte(ES8336_HPMIX_SWITCH_REG14, 0x00);
        FEs8336WriteByte(ES8336_HPMIX_PDN_REG15, 0x33);
        FEs8336WriteByte(ES8336_HPMIX_VOL_REG16, 0x00);
        FEs8336WriteByte(ES8336_SYS_PDN_REG0D, 0x00);
        FEs8336WriteByte(ES8336_SYS_LP1_REG0E, 0xFF);
        FEs8336ReadByte(ES8336_CLKMGR_CLKSW_REG01, &value);
        value &= (~ES8336_CLKMGR_DAC_ANALOG_EN) ;
        FEs8336WriteByte(ES8336_CLKMGR_CLKSW_REG01, value);
    }
    else
    {
        FEs8336WriteByte(ES8336_SYS_LP1_REG0E, 0xC0);
        FEs8336ReadByte(ES8336_CLKMGR_CLKSW_REG01, &value);
        value &= (~ES8336_CLKMGR_ADC_MCLK_EN);
        value &= (~ES8336_CLKMGR_ADC_ANALOG_EN);
        FEs8336WriteByte(ES8336_CLKMGR_CLKSW_REG01, value);

    }
    return ret;
}

/**
 * @name: FEs8336MuteDown
 * @msg:  mute down the es8336
 * @param (u32} mute ,mute or not mute the es8336
 * @return FES8336_SUCCESS
 */
FError FEs8336MuteDown(u32 mute)
{
    FError ret = FES8336_SUCCESS;
    u8 value = 0;
    if (mute)
    {
        FEs8336WriteByte(ES8336_DAC_SET1_REG30, 0x20);
    }
    FEs8336WriteByte(ES8336_DAC_SET1_REG30, 0x00);
    return ret;
}

/**
 * @name: FEs8336SetVolumel
 * @msg:  set the vilumel of es8336
 * @param (FEs8336WorkFormat} work_mode ,the type of workmode of PCM
 * @param (u32} value ,the volumel value
 * @return FES8336_SUCCESS
 */
FError FEs8336SetVolumel(FEs8336WorkFormat work_mode, u32 value)
{
    FError ret = FES8336_SUCCESS;
    if (work_mode == AUDIO_PCM_STREAM_PLAYBACK)
    {
        FEs8336WriteByte(ES8336_DAC_VOLL_REG33, value);
        FEs8336WriteByte(ES8336_DAC_VOLR_REG34, value);
    }
    else
    {
        FEs8336WriteByte(ES8336_ADC_VOLUME_REG27, value);
        FEs8336WriteByte(ES8336_ADC_VOLUME_REG28, value);
    }
    return ret;
}

/**
 * @name: FEs8336SetFormat
 * @msg:  set the es8336 word lenth
 * @param (u32} length ,the es8336 word lenth
 * @param (FEs8336WorkFormat} format ,the type of workmode of PCM
 * @return FES8336_SUCCESS
 */
FError FEs8336SetFormat(FEs8336PcmWordLength length, FEs8336WorkFormat format)
{
    FError ret = FES8336_SUCCESS;
    u8 value = 0;
    u8 reg_value;
    switch (length)
    {
        case AUDIO_PCM_STREAM_WORD_LENGTH_16:
            value = ES8336_DACWL_16;
            break;
        case AUDIO_PCM_STREAM_WORD_LENGTH_20:
            value = ES8336_DACWL_20;
            break;
        case AUDIO_PCM_STREAM_WORD_LENGTH_24:
            value = ES8336_DACWL_24;
            break;
        case AUDIO_PCM_STREAM_WORD_LENGTH_32:
            value = ES8336_DACWL_32;
            break;
        default:
            value = ES8336_DACWL_32;
            break;
    }
    FEs8336ReadByte(ES8336_SDP_ADCFMT_REG0A, &reg_value);
    FEs8336WriteByte(ES8336_SDP_ADCFMT_REG0A, reg_value | value);
    if (format == AUDIO_PCM_STREAM_PLAYBACK)
    {
        FEs8336ReadByte(ES8336_SDP_DACFMT_REG0B, &reg_value);
        FEs8336WriteByte(ES8336_SDP_DACFMT_REG0B, reg_value | value);
        FEs8336WriteByte(ES8336_DAC_SET1_REG30, 0x00);
    }
    else
    {
        FEs8336WriteByte(ES8336_SDP_DACFMT_REG0B, 0x0c);
        FEs8336WriteByte(ES8336_DAC_SET1_REG30, 0x00);
        FEs8336WriteByte(ES8336_DAC_VOLL_REG33, 0x0);
        FEs8336WriteByte(ES8336_DAC_VOLR_REG34, 0x28);
    }

    return ret;
}

/**
 * @name: FEs8336SetBiasLevel
 * @msg:  set the es8336 bias level
 * @param (u32} format ,the es8336 word lenth
 * @param (FEs8336WorkFormat} type ,the type of workmode of PCM
 * @return FES8336_SUCCESS
 */
FError FEs8336SetBiasLevel(FEs8336BiasLevel level)
{
    FError ret = FES8336_SUCCESS;
    switch (level)
    {
        case AUDIO_PCM_BIAS_LEVEL_ON:
            break;
        case AUDIO_PCM_BIAS_LEVEL_REPARE:
            break;
        case AUDIO_PCM_BIAS_LEVEL_STANDBY:
            break;
        case AUDIO_PCM_BIAS_LEVEL_OFF:
            FEs8336WriteByte(ES8336_CPHP_OUTEN_REG17, 0x00);
            FEs8336WriteByte(ES8336_DAC_PDN_REG2F, 0x11);
            FEs8336WriteByte(ES8336_CPHP_LDOCTL_REG1B, 0x03);
            FEs8336WriteByte(ES8336_CPHP_PDN2_REG1A, 0x22);
            FEs8336WriteByte(ES8336_CPHP_PDN1_REG19, 0x06);
            FEs8336WriteByte(ES8336_HPMIX_SWITCH_REG14, 0x00);
            FEs8336WriteByte(ES8336_HPMIX_PDN_REG15, 0x33);
            FEs8336WriteByte(ES8336_HPMIX_VOL_REG16, 0x00);
            FEs8336WriteByte(ES8336_ADC_PDN_LINSEL_REG22, 0xC0);
            FEs8336WriteByte(ES8336_SYS_LP1_REG0E, 0x3F);

            FEs8336WriteByte(ES8336_SYS_LP2_REG0F, 0x1F);
            FEs8336WriteByte(ES8336_RESET_REG00, 0x00);
            break;
    }
    return ret;
}

