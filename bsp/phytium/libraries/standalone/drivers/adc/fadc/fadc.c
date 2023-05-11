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
 * FilePath: fadc.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:28:45
 * Description: This file is for the minimum required function implementations for this driver.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/8/15   init commit
 */

#include <string.h>
#include "fgeneric_timer.h"
#include "fkernel.h"
#include "ftypes.h"
#include "ferror_code.h"
#include "fdebug.h"
#include "fadc.h"
#include "fadc_hw.h"
#include "fparameters.h"
#include "fassert.h"
#include "fsleep.h"

#define FADC_DEBUG_TAG "FT_ADC"
#define FADC_DEBUG(format, ...)     FT_DEBUG_PRINT_D(FADC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FADC_INFO(format, ...)      FT_DEBUG_PRINT_I(FADC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FADC_WARN(format, ...)      FT_DEBUG_PRINT_W(FADC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FADC_ERROR(format, ...)     FT_DEBUG_PRINT_E(FADC_DEBUG_TAG, format, ##__VA_ARGS__)

#define FADC_MAX_CLOCK_PRESC 16

#define FADC_MAX_THRESHOLD 0x400


/**
 * @name: FAdcPowerDownControl
 * @msg: Set power down signal
 * @param {FAdcCtrl} *pctrl, pointer to a FAdcCtrl structure that contains
 *                the configuration information for the specified adc module.
 * @param {u8} power_state, this parameter must be enable or disable.
 * @return err code information, FADC_SUCCESS indicates success，others indicates failed
 */
static FError FAdcPowerDownControl(FAdcCtrl *pctrl, u8 power_state)
{

    FASSERT(pctrl != NULL);
    FASSERT(FT_COMPONENT_IS_READY == pctrl->is_ready);
    u32 reg_val = 0;
    uintptr base_addr = pctrl->config.base_addr;
    reg_val = FADC_READ_REG32(base_addr, FADC_CTRL_REG_OFFSET);
    if (power_state == FADC_CTRL_PD_ENABLE)
    {
        reg_val |= FADC_CTRL_REG_PD_EN;
    }
    else
    {
        reg_val &= ~(FADC_CTRL_REG_PD_EN);
    }

    FADC_WRITE_REG32(base_addr, FADC_CTRL_REG_OFFSET, reg_val);

    return FADC_SUCCESS;
}

/**
 * @name: FAdcChannelEnable
 * @msg: enable channel, corresponding to fix channel mode or multi channel mode.
 * @param {FAdcCtrl} *pctrl, pointer to a FAdcCtrl structure that contains
 *                the configuration information for the specified adc module.
 * @param {FAdcChannel} channel, adc channel number.
 * @param {boolean} state, TRUE-enable, FALSE-disable
 * @return void
 */
void FAdcChannelEnable(FAdcCtrl *pctrl, FAdcChannel channel, boolean state)
{
    FASSERT(pctrl != NULL);
    FASSERT(FT_COMPONENT_IS_READY == pctrl->is_ready);
    FASSERT(channel < FADC_CHANNEL_NUM);
    u32 reg_val = 0;
    uintptr base_addr = pctrl->config.base_addr;
    reg_val = FADC_READ_REG32(base_addr, FADC_CTRL_REG_OFFSET);

    if (state == TRUE)
    {
        if (reg_val & FADC_CTRL_REG_FIX_CHANNEL)
        {
            reg_val &= ~(FADC_CTRL_REG_FIX_CHANNEL_NUM_MASK);
            reg_val |= FADC_CTRL_REG_FIX_CHANNEL_NUM(channel);
        }
        else
        {
            reg_val |= FADC_CTRL_REG_CHANNEL_EN(channel);
        }
    }
    else
    {
        /* fix channel mode, disable means stop convert */
        if (reg_val & FADC_CTRL_REG_FIX_CHANNEL)
        {
            reg_val &= ~(FADC_CTRL_REG_SOC_EN);

        }
        else
        {
            reg_val &= ~(FADC_CTRL_REG_CHANNEL_EN(channel));
        }
    }


    FADC_WRITE_REG32(base_addr, FADC_CTRL_REG_OFFSET, reg_val);

}

/**
 * @name: FAdcChannelThresholdSet
 * @msg: Set adc channel high_threshold and low_threshold.
 * you need use this function after FAdcConvertSet. If you want to use this function to
 * add other channel enable when the adc conversion is started, you need to restart the
 * adc convert start signal(adc_soc_en) after use to make the operation valid.
 * @param {FAdcCtrl} *pctrl, pointer to a FAdcCtrl structure that contains
 *                the configuration information for the specified adc module.
 * @param {FAdcChannel} channel, adc channel number.
 * @param {FAdcThresholdConfig} *threshold_config, pointer to adc channel threshold value struct.
 * @return err code information, FADC_SUCCESS indicates success，others indicates failed
 */
FError FAdcChannelThresholdSet(FAdcCtrl *pctrl, FAdcChannel channel, FAdcThresholdConfig *threshold_config)
{
    FASSERT(pctrl != NULL);
    FASSERT(FT_COMPONENT_IS_READY == pctrl->is_ready);
    FASSERT(channel < FADC_CHANNEL_NUM);

    u16 low_threshold = threshold_config->low_threshold;
    u16 high_threshold = threshold_config->high_threshold;

    FASSERT(high_threshold < FADC_MAX_THRESHOLD);
    FASSERT(low_threshold < high_threshold);

    uintptr base_addr = pctrl->config.base_addr;

    u32 threshold = (FADC_LEVEL_REG_HIGH_LEVEL(high_threshold)) |
                    (FADC_LEVEL_REG_LOW_LEVEL(low_threshold));
    FADC_WRITE_REG32(base_addr, (FADC_LEVEL_REG_OFFSET(channel)), threshold);

    return FADC_SUCCESS;
}

/**
 * @name: FAdcConvertSet
 * @msg: config adc convert parameters.
 * @param {FAdcCtrl} *pctrl, pointer to a FAdcCtrl structure that contains
 *                the configuration information for the specified adc module.
 * @param {FAdcConvertConfig} *convert_config, include convert mode，channel mode，
 *                            clock divider and convert_interval.
 * @return err code information, FADC_SUCCESS indicates success，others indicates failed
 */
FError FAdcConvertSet(FAdcCtrl *pctrl, FAdcConvertConfig *convert_config)
{
    FASSERT(pctrl != NULL);
    FASSERT(FT_COMPONENT_IS_READY == pctrl->is_ready);

    u32 reg_val = 0;
    uintptr base_addr = pctrl->config.base_addr;
    reg_val = FADC_READ_REG32(base_addr, FADC_CTRL_REG_OFFSET);

    /* clk_div config */
    u32 clk_div = convert_config->clk_div;
    FASSERT(clk_div < FADC_MAX_CLOCK_PRESC);
    if (clk_div % 2 == 1)
    {
        FADC_ERROR("Clk_div is not even.");
        return FADC_ERR_INVAL_PARM;
    }
    reg_val &= (~FADC_CTRL_REG_CLK_DIV_MASK);
    reg_val |= FADC_CTRL_REG_CLK_DIV(clk_div);

    /* config convert mode */
    FAdcConvertMode convert_mode = convert_config->convert_mode;
    FASSERT(convert_mode < FADC_CONVERT_MODE_NUM);
    if (convert_mode == FADC_SINGLE_CONVERT)
    {
        reg_val |= FADC_CTRL_REG_SINGLE_CONVERT;
    }
    else
    {
        reg_val &= ~(FADC_CTRL_REG_SINGLE_CONVERT);
    }

    /* config channel mode */
    FAdcChannelMode channel_mode = convert_config->channel_mode;
    FASSERT(channel_mode < FADC_CHANNEL_MODE_NUM);

    if (channel_mode == FADC_FIXED_CHANNEL)
    {
        reg_val |= FADC_CTRL_REG_FIX_CHANNEL;
    }
    else
    {
        reg_val &= ~(FADC_CTRL_REG_FIX_CHANNEL);
    }
    FADC_WRITE_REG32(base_addr, FADC_CTRL_REG_OFFSET, reg_val);

    /* config time interval between two converts */
    FADC_WRITE_REG32(base_addr, FADC_INTER_REG_OFFSET, convert_config->convert_interval);

    return FADC_SUCCESS;
}


/**
 * @name: FAdcInterruptEnable
 * @msg: enable channel interrupt.
 * @param {FAdcCtrl} *pctrl, pointer to a FAdcCtrl structure that contains
 *                the configuration information for the specified adc module.
 * @param {FAdcChannel} channel, adc channel number.
 * @param {FAdcIntrEvtType} event_type, interrupt event type
 * @return err code information, FADC_SUCCESS indicates success，others indicates failed
 */
FError FAdcInterruptEnable(FAdcCtrl *pctrl, FAdcChannel channel, FAdcIntrEventType event_type)
{
    FASSERT(pctrl != NULL);
    FASSERT(FT_COMPONENT_IS_READY == pctrl->is_ready);

    uintptr base_addr = pctrl->config.base_addr;
    u32 reg_val = 0;
    reg_val = FADC_READ_REG32(base_addr, FADC_INTRMASK_REG_OFFSET);
    switch (event_type)
    {
        case FADC_INTR_EVENT_COVFIN: /* enable channel convert complete irq */
            reg_val &= ~(FADC_INTRMASK_REG_COVFIN_MASK(channel));
            break;

        case FADC_INTR_EVENT_DLIMIT:
            reg_val &= ~(FADC_INTRMASK_REG_DLIMIT_MASK(channel));
            break;

        case FADC_INTR_EVENT_ULIMIT:
            reg_val &= ~(FADC_INTRMASK_REG_ULIMIT_MASK(channel));
            break;

        case FADC_INTR_EVENT_ERROR:
            reg_val &= ~(FADC_INTRMASK_REG_ERR_MASK);
            break;

        default:
            break;
    }

    FADC_WRITE_REG32(base_addr, FADC_INTRMASK_REG_OFFSET, reg_val);

    return FADC_SUCCESS;
}

/**
 * @name: FAdcInterruptDisable
 * @msg: disable channel interrupt.
 * @param {FAdcCtrl} *pctrl, pointer to a FAdcCtrl structure that contains
 *                the configuration information for the specified adc module.
 * @param {FAdcChannel} channel, adc channel number.
 * @param {FAdcIntrEvtType} event_type, interrupt event type
 * @return err code information, FADC_SUCCESS indicates success，others indicates failed
 */
FError FAdcInterruptDisable(FAdcCtrl *pctrl, FAdcChannel channel, FAdcIntrEventType event_type)
{
    FASSERT(pctrl != NULL);
    FASSERT(FT_COMPONENT_IS_READY == pctrl->is_ready);
    FASSERT(channel < FADC_CHANNEL_NUM);

    uintptr base_addr = pctrl->config.base_addr;
    u32 reg_val = 0;
    reg_val = FADC_READ_REG32(base_addr, FADC_INTRMASK_REG_OFFSET);
    switch (event_type)
    {
        case FADC_INTR_EVENT_COVFIN: /* enable channel convert complete irq */
            reg_val |= (FADC_INTRMASK_REG_COVFIN_MASK(channel));
            break;

        case FADC_INTR_EVENT_DLIMIT:
            reg_val |= (FADC_INTRMASK_REG_DLIMIT_MASK(channel));
            break;

        case FADC_INTR_EVENT_ULIMIT:
            reg_val |= (FADC_INTRMASK_REG_ULIMIT_MASK(channel));
            break;

        case FADC_INTR_EVENT_ERROR:
            reg_val |= (FADC_INTRMASK_REG_ERR_MASK);
            break;

        default:
            break;
    }

    FADC_WRITE_REG32(base_addr, FADC_INTRMASK_REG_OFFSET, reg_val);

    return FADC_SUCCESS;
}

/**
 * @name: FAdcConvertStart
 * @msg: Start adc convert.
 * @param {FAdcCtrl} *pctrl, pointer to a FAdcCtrl structure that contains
 *                the configuration information for the specified adc module.
 * @return
 */
void FAdcConvertStart(FAdcCtrl *pctrl)
{
    FASSERT(pctrl != NULL);
    FASSERT(FT_COMPONENT_IS_READY == pctrl->is_ready);
    u32 reg_val = 0;
    uintptr base_addr = pctrl->config.base_addr;
    reg_val = FADC_READ_REG32(base_addr, FADC_CTRL_REG_OFFSET);
    reg_val |= FADC_CTRL_REG_SOC_EN;
    FADC_WRITE_REG32(base_addr, FADC_CTRL_REG_OFFSET, reg_val);

}

/**
 * @name: FAdcConvertStop
 * @msg: Stop adc convert.
 * @param {FAdcCtrl} *pctrl, pointer to a FAdcCtrl structure that contains
 *                the configuration information for the specified adc module.
 * @return
 */
void FAdcConvertStop(FAdcCtrl *pctrl)
{
    FASSERT(pctrl != NULL);
    FASSERT(FT_COMPONENT_IS_READY == pctrl->is_ready);
    u32 reg_val = 0;
    uintptr base_addr = pctrl->config.base_addr;
    reg_val = FADC_READ_REG32(base_addr, FADC_CTRL_REG_OFFSET);
    reg_val &= (~FADC_CTRL_REG_SOC_EN);
    FADC_WRITE_REG32(base_addr, FADC_CTRL_REG_OFFSET, reg_val);

}

/**
 * @name: FAdcInit
 * @msg: init adc variable configuration.
 * @param {FAdcCtrl} *pctrl, pointer to a FAdcCtrl structure that contains
 *                the configuration information for the specified adc module.
 * @param {FAdcConvertConfig} *convert_config, pointer to adc convert configuration
 * @return err code information, FADC_SUCCESS indicates success，others indicates failed
 */
FError FAdcVariableConfig(FAdcCtrl *pctrl, FAdcConvertConfig *convert_config)
{
    FASSERT(pctrl != NULL);
    FASSERT(convert_config != NULL);

    FError ret = FADC_SUCCESS;

    /* disable power down signal */
    ret = FAdcPowerDownControl(pctrl, FADC_CTRL_PD_DISABLE);
    if (ret != FADC_SUCCESS)
    {
        FADC_ERROR("FAdcPowerDownControl failed.");
        return FADC_ERR_CMD_FAILED;
    }

    /* set time interval between two converts */
    ret = FAdcConvertSet(pctrl, convert_config);
    if (ret != FADC_SUCCESS)
    {
        FADC_ERROR("FAdcConvertSet failed.");
        return FADC_ERR_CMD_FAILED;
    }

    return ret;
}

/**
 * @name: FAdcSingleConvertEnable
 * @msg: Enable single convert signal, when convert mode is set to single conversion.
 * @param {FAdcCtrl} *pctrl, pointer to a FAdcCtrl structure that contains
 *                the configuration information for the specified adc module.
 * @return err code information, FADC_SUCCESS indicates success，others indicates failed
 */
static FError FAdcSingleConvertEnable(FAdcCtrl *pctrl)
{
    FASSERT(pctrl != NULL);
    FASSERT(FT_COMPONENT_IS_READY == pctrl->is_ready);
    u32 reg_val = 0;
    uintptr base_addr = pctrl->config.base_addr;
    reg_val = FADC_READ_REG32(base_addr, FADC_CTRL_REG_OFFSET);
    reg_val |= FADC_CTRL_REG_SINGLE_CONVERT_EN;
    FADC_WRITE_REG32(base_addr, FADC_CTRL_REG_OFFSET, reg_val);

    return FADC_SUCCESS;
}

/**
 * @name: FAdcReadConvertResult
 * @msg: read adc channel convert result value.
 * @param {FAdcCtrl} *pctrl, pointer to a FAdcCtrl structure that contains
 *                the configuration information for the specified adc module.
 * @param {FAdcChannel} channel, adc channel number.
 * @param {u16} *val, pointer to adc convert result value.
 * @return err code information, FADC_SUCCESS indicates success，others indicates failed.
 */
FError FAdcReadConvertResult(FAdcCtrl *pctrl, FAdcChannel channel, u16 *val)
{
    FASSERT(pctrl != NULL);
    FASSERT(channel < FADC_CHANNEL_NUM);
    FASSERT(FT_COMPONENT_IS_READY == pctrl->is_ready);
    int timeout = FADC_READ_DELAY;
    uintptr base_addr = pctrl->config.base_addr;

    u32 reg_val = FADC_READ_REG32(base_addr, FADC_CTRL_REG_OFFSET);
    /* single conversion */
    if (reg_val & FADC_CTRL_REG_SINGLE_CONVERT)
    {
        FAdcSingleConvertEnable(pctrl);
    }

    do
    {
        fsleep_millisec(10);
    }
    while ((!pctrl->convert_complete[channel]) && (0 <= --timeout));

    if (0 >= timeout)
    {
        FADC_ERROR("Timeout when reading adc-data, the conversion is not finished.");
        *val = 0;
        return FADC_ERR_TIMEOUT;
    }

    FADC_CONVERT_UNCOMPLETE(pctrl->convert_complete[channel]);
    *val = pctrl->value[channel];

    return FADC_SUCCESS;
}

/**
 * @name: FAdcReadFinishCnt
 * @msg: read adc channel convert finish count.
 * @param {FAdcCtrl} *pctrl, pointer to a FAdcCtrl structure that contains
 *                the configuration information for the specified adc module.
 * @param {FAdcChannel} channel, adc channel number.
 * @param {u32} *count, pointer to adc convert finish count.
 * @return err code information, FADC_SUCCESS indicates success，others indicates failed.
 */
FError FAdcReadFinishCnt(FAdcCtrl *pctrl, FAdcChannel channel, u32 *count)
{
    FASSERT(pctrl != NULL);
    FASSERT(FT_COMPONENT_IS_READY == pctrl->is_ready);

    uintptr base_addr = pctrl->config.base_addr;
    *count = FADC_READ_REG32(base_addr, FADC_FINISH_CNT_REG_OFFSET(channel));
    return FADC_SUCCESS;
}

/**
 * @name: FAdcReadHisLimit
 * @msg: read adc channel history limit value, include upper limit and lower limit.
 * @param {FAdcCtrl} *pctrl, pointer to a FAdcCtrl structure that contains
 *                the configuration information for the specified adc module.
 * @param {FAdcChannel} channel, adc channel number.
 * @param {u16} *u_his_limit, pointer to adc convert history upper limit value.
 * @param {u16} *d_his_limit, pointer to adc convert history lower limit value.
 * @return err code information, FADC_SUCCESS indicates success，others indicates failed.
 */
FError FAdcReadHisLimit(FAdcCtrl *pctrl, FAdcChannel channel, u16 *u_his_limit, u16 *d_his_limit)
{
    FASSERT(pctrl != NULL);
    FASSERT(FT_COMPONENT_IS_READY == pctrl->is_ready);
    u32 reg_val = 0;
    uintptr base_addr = pctrl->config.base_addr;

    reg_val = FADC_READ_REG32(base_addr, FADC_HIS_LIMIT_REG_OFFSET(channel));

    *u_his_limit = (reg_val & FADC_HIS_LIMIT_REG_UMASK) >> 16;
    *d_his_limit = (reg_val & FADC_HIS_LIMIT_REG_DMASK) ;

    return FADC_SUCCESS;
}

/**
 * @name: FAdcDeInitialize
 * @msg: DeInitialization function for the device instance
 * @param {FAdcCtrl} *pctrl, instance of FADC controller
 * @return {*}
 */
void FAdcDeInitialize(FAdcCtrl *pctrl)
{
    FASSERT(pctrl);

    pctrl->is_ready = 0;
    memset(pctrl, 0, sizeof(*pctrl));

    return;
}

/**
 * @name: FAdcCfgInitialize
 * @msg:  Initializes a specific instance such that it is ready to be used.
 * @param {FAdcCtrl} *pctrl, instance of FADC controller
 * @param {FAdcConfig} *input_config_p, Default configuration parameters of FADC
 * @return err code information, FADC_SUCCESS indicates success，others indicates failed
 */
FError FAdcCfgInitialize(FAdcCtrl *pctrl, const FAdcConfig *input_config_p)
{
    FASSERT(pctrl && input_config_p);

    FError ret = FADC_SUCCESS;
    /*
    * If the device is started, disallow the initialize and return a Status
    * indicating it is started.  This allows the user to de-initialize the device
    * and reinitialize, but prevents a user from inadvertently
    * initializing.
    */
    if (FT_COMPONENT_IS_READY == pctrl->is_ready)
    {
        FADC_WARN("The device was already initialized!");
    }

    /*Set default values and configuration data */
    FAdcDeInitialize(pctrl);

    pctrl->config = *input_config_p;

    pctrl->is_ready = FT_COMPONENT_IS_READY;

    return ret;
}
