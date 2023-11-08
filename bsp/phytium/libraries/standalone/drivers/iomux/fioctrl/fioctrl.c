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
 * FilePath: fioctrl.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:25:29
 * Description:  This file is for implmentation ioctrl functions
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2023/7/31    init commit
 */

/***************************** Include Files *********************************/

#include <string.h>
#include "fparameters.h"
#include "fio.h"
#include "fkernel.h"
#include "fassert.h"
#include "fdrivers_port.h"

#include "fioctrl_hw.h"
#include "fioctrl.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

#define FIOCTRL_DEBUG_TAG "FIOCTRL"
#define FIOCTRL_ERROR(format, ...) FT_DEBUG_PRINT_E(FIOCTRL_DEBUG_TAG, format, ##__VA_ARGS__)
#define FIOCTRL_WARN(format, ...)  FT_DEBUG_PRINT_W(FIOCTRL_DEBUG_TAG, format, ##__VA_ARGS__)
#define FIOCTRL_INFO(format, ...)  FT_DEBUG_PRINT_I(FIOCTRL_DEBUG_TAG, format, ##__VA_ARGS__)
#define FIOCTRL_DEBUG(format, ...) FT_DEBUG_PRINT_D(FIOCTRL_DEBUG_TAG, format, ##__VA_ARGS__)

#define FIOCTRL_ASSERT_REG_OFF(pin) FASSERT_MSG(((pin.reg_off >= FIOCTRL_REG_OFFSET_MIN) && (pin.reg_off <= FIOCTRL_REG_OFFSET_MAX)), "invalid pin register off @%d", (pin.reg_off))
#define FIOCTRL_ASSERT_FUNC(func) FASSERT_MSG((func < FIOCTRL_NUM_OF_FUNC), "invalid func as %d", (func))
#define FIOCTRL_ASSERT_PULL(pull) FASSERT_MSG((pull < FIOCTRL_NUM_OF_PULL), "invalid pull as %d", (pull))

#define FIOCTRL_ASSERT_DELAY_REG_OFF(pin) FASSERT_MSG(((pin.reg_off >= FIOCTRL_DELAY_REG_OFFSET_MIN) && (pin.reg_off <= FIOCTRL_DELAY_REG_OFFSET_MAX)), "invalid delay pin register off @%d", (pin.reg_off))
#define FIOCTRL_ASSERT_DELAY(delay) FASSERT_MSG(((delay) < FIOCTRL_NUM_OF_DELAY), "invalid delay as %d", (delay));

/************************** Function Prototypes ******************************/

/*****************************************************************************/


/**
 * @name: FIOCtrlCfgInitialize
 * @msg:  Initializes a specific instance such that it is ready to be used
 * @param {FIOCtrl} *pctrl, instance of FIOCTRL controller
 * @param {FIOCtrlConfig} input_config_p, Configuration parameters of IOCTRL
 * @return err code information, FIOCTRL_SUCCESS indicates success，others indicates failed
 */
FError FIOCtrlCfgInitialize(FIOCtrl *instance_p, const FIOCtrlConfig *input_config_p)
{
    FASSERT(instance_p != NULL);
    FASSERT(input_config_p != NULL);

    FError ret = FIOCTRL_SUCCESS;
    /*
    * If the device is started, disallow the initialize and return a Status
    * indicating it is started.  This allows the user to de-initialize the device
    * and reinitialize, but prevents a user from inadvertently
    * initializing.
    */
    if (FT_COMPONENT_IS_READY == instance_p->is_ready)
    {
        FIOCTRL_WARN("Device is already initialized.");
    }

    /*Set default values and configuration data */
    memset(instance_p, 0U, sizeof(*instance_p));

    instance_p->config = *input_config_p;

    instance_p->is_ready = FT_COMPONENT_IS_READY;

    return ret;
}

/**
 * @name: FIOCtrlDeInitialize
 * @msg:  DeInitializes a specific instance
 * @param {FIOCtrl} *pctrl, instance of FIOCTRL controller
 * @param {FIOCtrlConfig} input_config_p, Configuration parameters of IOCTRL
 * @return err code information, FIOCTRL_SUCCESS indicates success，others indicates failed
 */
void FIOCtrlDeInitialize(FIOCtrl *instance_p)
{
    FASSERT(instance_p != NULL);
    memset(instance_p, 0U, sizeof(*instance_p));
}

/**
 * @name: FIOCtrlGetFunc
 * @msg: get the current multiplexing function of IO pins
 * @param {FIOCtrl} *instance_p, instance of FIOCTRL controller
 * @param {FIOCtrlPinIndex} pin, pin reg offset
 * @return {FIOCtrlFunc} current multiplexing function
 */
FIOCtrlFunc FIOCtrlGetFunc(FIOCtrl *instance_p, const FIOCtrlPinIndex pin)
{
    FASSERT(instance_p != NULL);
    FIOCTRL_ASSERT_REG_OFF(pin);

    u32 func_beg = FIOCTRL_FUNC_BEG_OFF(pin.reg_bit);
    u32 func_end = FIOCTRL_FUNC_END_OFF(pin.reg_bit);
    uintptr base_addr = instance_p->config.base_address;
    u32 reg_val = FtIn32(base_addr + pin.reg_off);
    u32 func = GET_REG32_BITS(reg_val, func_end, func_beg);
    FIOCTRL_ASSERT_FUNC(func);

    return (FIOCtrlFunc)GET_REG32_BITS(reg_val, func_end, func_beg);    
}

/**
 * @name: FIOCtrlSetFunc
 * @msg: set the multiplexing function of IO pins
 * @param {FIOCtrl} *instance_p, instance of FIOCTRL controller
 * @param {FIOCtrlPinIndex} pin, pin reg offset
 * @param {FIOCtrlFunc} func, specific multiplexing function
 * @return err code information, FIOCTRL_SUCCESS indicates success，others indicates failed
 */
FError FIOCtrlSetFunc(FIOCtrl *instance_p, const FIOCtrlPinIndex pin, FIOCtrlFunc func)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FIOCTRL_ASSERT_REG_OFF(pin);
    FIOCTRL_ASSERT_FUNC(func);

    u32 func_beg = FIOCTRL_FUNC_BEG_OFF(pin.reg_bit);
    u32 func_end = FIOCTRL_FUNC_END_OFF(pin.reg_bit);
    uintptr base_addr = instance_p->config.base_address;
    u32 reg_val = FtIn32(base_addr + pin.reg_off);

    reg_val &= ~GENMASK(func_end, func_beg);
    reg_val |= SET_REG32_BITS(func, func_end, func_beg);

    FtOut32(base_addr + pin.reg_off, reg_val);
    return FIOCTRL_SUCCESS;    
}

/**
 * @name: FIOCtrlGetPull
 * @msg: get the current up_down_pull configuration of IO pins
 * @param {FIOCtrl} *instance_p, instance of FIOCTRL controller
 * @param {FIOCtrlPinIndex} pin, pin reg offset
 * @return {FIOCtrlPull}  current up_down_pull configuration
 */
FIOCtrlPull FIOCtrlGetPull(FIOCtrl *instance_p, const FIOCtrlPinIndex pin)
{
    FASSERT(instance_p != NULL);
    FIOCTRL_ASSERT_REG_OFF(pin);

    u32 pull_beg = FIOCTRL_PULL_BEG_OFF(pin.reg_bit);
    u32 pull_end = FIOCTRL_PULL_END_OFF(pin.reg_bit);
    uintptr base_addr = instance_p->config.base_address;
    u32 reg_val = FtIn32(base_addr + pin.reg_off);
    u32 pull = GET_REG32_BITS(reg_val, pull_end, pull_beg);

    FIOCTRL_ASSERT_PULL(pull);
    return (FIOCtrlPull)pull;
}

/**
 * @name: FIOCtrlSetPull
 * @msg: get the current up_down_pull configuration of IO pins
 * @param {FIOCtrl} *instance_p, instance of FIOCTRL controller
 * @param {FIOCtrlPinIndex} pin, pin reg offset
 * @return {FIOCtrlPull}  current up_down_pull configuration
 */
FError FIOCtrlSetPull(FIOCtrl *instance_p, const FIOCtrlPinIndex pin, FIOCtrlPull pull)
{
    FASSERT(instance_p != NULL);
    FIOCTRL_ASSERT_REG_OFF(pin);
    FIOCTRL_ASSERT_PULL(pull);

    u32 pull_beg = FIOCTRL_PULL_BEG_OFF(pin.reg_bit);
    u32 pull_end = FIOCTRL_PULL_END_OFF(pin.reg_bit);
    uintptr base_addr = instance_p->config.base_address;
    u32 reg_val = FtIn32(base_addr + pin.reg_off);

    reg_val &= ~GENMASK(pull_end, pull_beg);
    reg_val |= SET_REG32_BITS(pull, pull_end, pull_beg);

    FtOut32(base_addr + pin.reg_off, reg_val);
    return FIOCTRL_SUCCESS;    
}

/**
 * @name: FIOCtrlGetConfig
 * @msg: set the func, up_down_pull of IO pins
 * @param {FIOCtrl} *instance_p, instance of FIOCTRL controller
 * @param {FIOCtrlPinIndex} pin, pin reg offset
 * @param {FIOCtrlFunc} *func, multiplexing function
 * @param {FIOCtrlPull} *pull, up_down_pull configurations
 * @return err code information, FIOCTRL_SUCCESS indicates success，others indicates failed
 */
FError FIOCtrlGetConfig(FIOCtrl *instance_p, const FIOCtrlPinIndex pin, FIOCtrlFunc *func, FIOCtrlPull *pull)
{
    FASSERT(instance_p != NULL);
    FIOCTRL_ASSERT_REG_OFF(pin);

    u32 func_beg = FIOCTRL_FUNC_BEG_OFF(pin.reg_bit);
    u32 func_end = FIOCTRL_FUNC_END_OFF(pin.reg_bit);
    u32 pull_beg = FIOCTRL_PULL_BEG_OFF(pin.reg_bit);
    u32 pull_end = FIOCTRL_PULL_END_OFF(pin.reg_bit);
    uintptr base_addr = instance_p->config.base_address;
    u32 reg_val = FtIn32(base_addr + pin.reg_off);

    if (func)
    {
        *func = GET_REG32_BITS(reg_val, func_end, func_beg);
    }

    if (pull)
    {
        *pull = GET_REG32_BITS(reg_val, pull_end, pull_beg);
    }

    return FIOCTRL_SUCCESS;    
}

/**
 * @name: FIOCtrlSetConfig
 * @msg: set the func, up_down_pull of IO pins
 * @param {FIOCtrl} *instance_p, instance of FIOCTRL controller
 * @param {FIOCtrlPinIndex} pin, pin reg offset
 * @param {FIOCtrlFunc} func, specific multiplexing function
 * @param {FIOCtrlPull} pull, up_down_pull configurations
 * @return err code information, FIOCTRL_SUCCESS indicates success，others indicates failed
 */
FError FIOCtrlSetConfig(FIOCtrl *instance_p, const FIOCtrlPinIndex pin, FIOCtrlFunc func, FIOCtrlPull pull)
{
    FASSERT(instance_p != NULL);
    FIOCTRL_ASSERT_REG_OFF(pin);
    u32 func_beg = FIOCTRL_FUNC_BEG_OFF(pin.reg_bit);
    u32 func_end = FIOCTRL_FUNC_END_OFF(pin.reg_bit);
    u32 pull_beg = FIOCTRL_PULL_BEG_OFF(pin.reg_bit);
    u32 pull_end = FIOCTRL_PULL_END_OFF(pin.reg_bit);
    uintptr base_addr = instance_p->config.base_address;
    u32 reg_val = FtIn32(base_addr + pin.reg_off);

    reg_val &= ~GENMASK(func_end, func_beg);
    reg_val |= SET_REG32_BITS(func, func_end, func_beg);

    reg_val &= ~GENMASK(pull_end, pull_beg);
    reg_val |= SET_REG32_BITS(pull, pull_end, pull_beg);

    FtOut32(base_addr + pin.reg_off, reg_val);
    return FIOCTRL_SUCCESS;    
}

/**
 * @name: FIOCtrlGetDelay
 * @msg: get the current delay configuration of IO pins
 * @param {FIOCtrl} *instance_p, instance of FIOCTRL controller
 * @param {FIOCtrlPinIndex} pin, pin reg offset
 * @param {FIOCtrlDelayDir} dir, the delay direction
 * @param {FIOCtrlDelayType} type, the delay type
 * @return {FIOCtrlDelay}  current delay value
 */
FIOCtrlDelay FIOCtrlGetDelay(FIOCtrl *instance_p, const FIOCtrlPinIndex pin, FIOCtrlDelayDir dir, FIOCtrlDelayType type)
{
    FASSERT(instance_p != NULL);
    FIOCTRL_ASSERT_DELAY_REG_OFF(pin);
    u8 delay = 0;
    uintptr base_addr = instance_p->config.base_address;
    const u32 reg_val = FtIn32(base_addr + pin.reg_off);
    u32 delay_beg = 0, delay_end = 0;

    if (FIOCTRL_OUTPUT_DELAY == dir)
    {
        delay_beg = FIOCTRL_DELAY_OUT_BEG_OFF(pin.reg_off);
    }
    else if (FIOCTRL_INPUT_DELAY == dir)
    {
        delay_beg = FIOCTRL_DELAY_IN_BEG_OFF(pin.reg_off);
    }
    else
    {
        FASSERT(0);
    }

    if (FIOCTRL_DELAY_FINE_TUNING == type)
    {
        delay = FIOCTRL_DELICATE_DELAY_GET(reg_val, delay_beg);
    }
    else if (FIOCTRL_DELAY_COARSE_TUNING == type)
    {
        delay = FIOCTRL_ROUGH_DELAY_GET(reg_val, delay_beg);
    }
    else
    {
        FASSERT(0);
    }

    FIOCTRL_ASSERT_DELAY(delay);
    return (FIOCtrlDelay)delay;    
}

/**
 * @name: FIOCtrlSetDelay
 * @msg: set the current delay configuration of IO pins
 * @param {FIOCtrl} *instance_p, instance of FIOCTRL controller
 * @param {FIOCtrlPinIndex} pin, pin reg offset
 * @param {FIOCtrlDelayDir} dir, the delay direction
 * @param {FIOCtrlDelayType} type, the delay type
 * @param {FIOCtrlDelay} delay, delay value
 * @return err code information, FIOCTRL_SUCCESS indicates success，others indicates failed
 */
FError FIOCtrlSetDelay(FIOCtrl *instance_p, const FIOCtrlPinIndex pin, FIOCtrlDelayDir dir, FIOCtrlDelayType type, FIOCtrlDelay delay)
{
    FASSERT(instance_p != NULL);
    FIOCTRL_ASSERT_DELAY_REG_OFF(pin);
    FIOCTRL_ASSERT_DELAY(delay);
    uintptr base_addr = instance_p->config.base_address;
    u32 reg_val = FtIn32(base_addr + pin.reg_off);
    u32 delay_beg = 0, delay_end = 0;

    if (FIOCTRL_OUTPUT_DELAY == dir)
    {
        delay_beg = FIOCTRL_DELAY_OUT_BEG_OFF(pin.reg_off);
    }
    else if (FIOCTRL_INPUT_DELAY == dir)
    {
        delay_beg = FIOCTRL_DELAY_IN_BEG_OFF(pin.reg_off);
    }
    else
    {
        return FIOCTRL_INVAL_PARAM;
    }

    if (FIOCTRL_DELAY_FINE_TUNING == type)
    {
        reg_val &= ~FIOCTRL_DELICATE_DELAY_MASK(delay_beg);
        delay = FIOCTRL_DELICATE_DELAY_GET(reg_val, delay_beg);
    }
    else if (FIOCTRL_DELAY_COARSE_TUNING == type)
    {
        reg_val &= ~FIOCTRL_ROUGH_DELAY_MASK(delay_beg);
        delay = FIOCTRL_ROUGH_DELAY_GET(reg_val, delay_beg);
    }
    else
    {
        return FIOCTRL_INVAL_PARAM;
    }

    FtOut32(base_addr + pin.reg_off, reg_val);
    return FIOCTRL_SUCCESS;    
}

/**
 * @name: FIOCtrlSetDelayEn
 * @msg: Enable/disable IO pin delay
 * @param {FIOCtrl} *instance_p, instance of FIOCTRL controller
 * @param {FIOCtrlPinIndex} pin, pin reg offset
 * @param {FIOCtrlDelayDir} dir, the delay direction
 * @param {boolean} enable TRUE: enable, FALSE: disable
 * @return err code information, FIOCTRL_SUCCESS indicates success，others indicates failed
 */
FError FIOCtrlSetDelayEn(FIOCtrl *instance_p, const FIOCtrlPinIndex pin, FIOCtrlDelayDir dir, boolean enable)
{
    FASSERT(instance_p != NULL);
    FIOCTRL_ASSERT_DELAY_REG_OFF(pin);
    uintptr base_addr = instance_p->config.base_address;
    u32 reg_val = FtIn32(base_addr + pin.reg_off);
    u32 delay_beg = 0, delay_end = 0;

    if (FIOCTRL_OUTPUT_DELAY == dir)
    {
        delay_beg = FIOCTRL_DELAY_OUT_BEG_OFF(pin.reg_off);
    }
    else if (FIOCTRL_INPUT_DELAY == dir)
    {
        delay_beg = FIOCTRL_DELAY_IN_BEG_OFF(pin.reg_off);
    }
    else
    {
        return FIOCTRL_INVAL_PARAM;
    }

    reg_val &= ~FIOCTRL_DELAY_EN(delay_beg);
    if (enable)
    {
        reg_val |= FIOCTRL_DELAY_EN(delay_beg);
    }

    FtOut32(base_addr + pin.reg_off, reg_val);
    return FIOCTRL_SUCCESS;    
}