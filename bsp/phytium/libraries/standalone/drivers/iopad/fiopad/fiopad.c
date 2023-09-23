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
 * FilePath: fiopad.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:25:29
 * Description:  This file is for iopad function
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhangyan    2023/7/4    init commit
 */

/***************************** Include Files *********************************/
#include "fparameters.h"
#include <string.h>
#include "fio.h"
#include "fkernel.h"
#include "fassert.h"
#include "fdebug.h"
#include "stdio.h"
#include "fpinctrl.h"
#include "fiopad_hw.h"
#include "fiopad.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

#define FIOPAD_DEBUG_TAG "FIOPAD"
#define FIOPAD_ERROR(format, ...)   FT_DEBUG_PRINT_E(FIOPAD_DEBUG_TAG, format, ##__VA_ARGS__)
#define FIOPAD_WARN(format, ...)    FT_DEBUG_PRINT_W(FIOPAD_DEBUG_TAG, format, ##__VA_ARGS__)
#define FIOPAD_INFO(format, ...)    FT_DEBUG_PRINT_I(FIOPAD_DEBUG_TAG, format, ##__VA_ARGS__)
#define FIOPAD_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FIOPAD_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/

/**
 * @name: FIOPadCfgInitialize
 * @msg:  Initializes a specific instance such that it is ready to be used
 * @param {FIOPadCtrl} *pctrl, instance of FIOPAD controller
 * @param {FIOPadConfig} input_config_p, Configuration parameters of IOPAD
 * @return err code information, FPWM_SUCCESS indicates success，others indicates failed
 */
FError FIOPadCfgInitialize(FIOPadCtrl *instance_p, const FIOPadConfig *input_config_p)
{
    FASSERT(instance_p != NULL);
    FASSERT(input_config_p != NULL);

    FError ret = FIOPAD_SUCCESS;
    /*
    * If the device is started, disallow the initialize and return a Status
    * indicating it is started.  This allows the user to de-initialize the device
    * and reinitialize, but prevents a user from inadvertently
    * initializing.
    */
    if (FT_COMPONENT_IS_READY == instance_p->is_ready)
    {
        FIOPAD_WARN("Device is already initialized.");
    }

    /*Set default values and configuration data */
    FIOPadDeInitialize(instance_p);

    instance_p->config = *input_config_p;

    instance_p->is_ready = FT_COMPONENT_IS_READY;

    return ret;
}

/**
 * @name: FPinGetFunc
 * @msg: get the current multiplexing function of IO pins
 * @param {FIOPadCtrl} *instance_p, instance of FIOPAD controller
 * @param {u32} pin_reg_off, pin reg offset
 * @return {FIOPadFunc} current multiplexing function
 */
FIOPadFunc FIOPadGetFunc(FIOPadCtrl *instance_p, const u32 pin_reg_off)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FIOPAD_ASSERT_REG0_OFF(pin_reg_off);
    uintptr base_addr = instance_p->config.base_address;
    u32 func = FIOPAD_REG0_FUNC_GET(FIOPAD_READ_REG32(base_addr, pin_reg_off));
    FIOPAD_ASSERT_FUNC(func);

    return (FIOPadFunc)func;
}

/**
 * @name: FPinSetFunc
 * @msg: set the multiplexing function of IO pins
 * @param {FIOPadCtrl} *instance_p, instance of FIOPAD controller
 * @param {u32} pin_reg_off, pin reg offset
 * @param {FIOPadFunc} func, specific multiplexing function
 * @return err code information, FIOPAD_SUCCESS indicates success，others indicates failed
 */
FError FIOPadSetFunc(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadFunc func)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FIOPAD_ASSERT_REG0_OFF(pin_reg_off);
    FIOPAD_ASSERT_FUNC(func);
    u32 ret = FIOPAD_SUCCESS;
    uintptr base_addr = instance_p->config.base_address;
    u32 reg_val = FIOPAD_READ_REG32(base_addr, pin_reg_off);
    u32 test_val = 0;

    reg_val &= ~FIOPAD_REG0_FUNC_MASK;
    reg_val |= FIOPAD_REG0_FUNC_SET(func);

    FIOPAD_WRITE_REG32(base_addr, pin_reg_off, reg_val);

    test_val = FIOPAD_READ_REG32(base_addr, pin_reg_off);

    if (reg_val != test_val)
    {
        FIOPAD_ERROR("ERROR: FIOPad write is failed ,pin is %x\n, 0x%x != 0x%x",
                     pin_reg_off, reg_val, test_val);
    }

    return ret;
}

/**
 * @name: FIOPadGetPull
 * @msg: get the current up_down_pull configuration of IO pins
 * @param {FIOPadCtrl} *instance_p, instance of FIOPAD controller
 * @param {u32} pin_reg_off, pin reg offset
 * @return {FIOPadPull}  current up_down_pull configuration
 */
FIOPadPull FIOPadGetPull(FIOPadCtrl *instance_p, const u32 pin_reg_off)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FIOPAD_ASSERT_REG0_OFF(pin_reg_off);
    uintptr base_addr = instance_p->config.base_address;
    u32 pull = FIOPAD_REG0_PULL_GET(FIOPAD_READ_REG32(base_addr, pin_reg_off));
    FIOPAD_ASSERT_PULL(pull);

    return (FIOPadPull)pull;
}

/**
 * @name: FIOPadSetPull
 * @msg: set the up_down_pull configuration of IO pins
 * @param {FIOPadCtrl} *instance_p, instance of FIOPAD controller
 * @param {u32} pin_reg_off, pin reg offset
 * @param {FIOPadPull} func, up_down_pull configuration
 * @return err code information, FIOPAD_SUCCESS indicates success，others indicates failed
 */
FError FIOPadSetPull(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadPull pull)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FIOPAD_ASSERT_REG0_OFF(pin_reg_off);
    FIOPAD_ASSERT_PULL(pull);
    u32 ret = FIOPAD_SUCCESS;
    uintptr base_addr = instance_p->config.base_address;
    u32 reg_val = FIOPAD_READ_REG32(base_addr, pin_reg_off);

    reg_val &= ~FIOPAD_REG0_PULL_MASK;
    reg_val |= FIOPAD_REG0_PULL_SET(pull);

    FIOPAD_WRITE_REG32(base_addr, pin_reg_off, reg_val);

    return ret;
}

/**
 * @name: FIOPadGetDriver
 * @msg: get the current driver strength of IO pins
 * @param {FIOPadCtrl} *instance_p, instance of FIOPAD controller
 * @param {u32} pin_reg_off, pin reg offset
 * @return {FIOPadDrive}  current driver strength
 */
FIOPadDrive FIOPadGetDriver(FIOPadCtrl *instance_p, const u32 pin_reg_off)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FIOPAD_ASSERT_REG0_OFF(pin_reg_off);
    uintptr base_addr = instance_p->config.base_address;
    u32 drive = FIOPAD_REG0_DRIVE_GET(FIOPAD_READ_REG32(base_addr, pin_reg_off));
    FIOPAD_ASSERT_DRIVE(drive);

    return (FIOPadDrive)drive;
}

/**
 * @name: FIOPadSetDriver
 * @msg: set the driver strength of IO pins
 * @param {FIOPadCtrl} *instance_p, instance of FIOPAD controller
 * @param {u32} pin_reg_off, pin reg offset
 * @param {FIOPadDrive} func, driver strength
 * @return err code information, FIOPAD_SUCCESS indicates success，others indicates failed
 */
FError FIOPadSetDriver(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadDrive drive)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FIOPAD_ASSERT_REG0_OFF(pin_reg_off);
    FIOPAD_ASSERT_DRIVE(drive);
    u32 ret = FIOPAD_SUCCESS;
    uintptr base_addr = instance_p->config.base_address;
    u32 reg_val = FIOPAD_READ_REG32(base_addr, pin_reg_off);

    reg_val &= ~FIOPAD_REG0_DRIVE_MASK;
    reg_val |= FIOPAD_REG0_DRIVE_SET(drive);

    FIOPAD_WRITE_REG32(base_addr, pin_reg_off, reg_val);

    return ret;
}

/**
 * @name: FIOPadSetConfig
 * @msg: set the func, up_down_pull,  driver strength of IO pins
 * @param {FIOPadCtrl} *instance_p, instance of FIOPAD controller
 * @param {u32} pin_reg_off, pin reg offset
 * @param {FIOPadFunc} func, specific multiplexing function
 * @param {FIOPadPull} pull, up_down_pull configurations
 * @param {FIOPadDrive} driver, driver strength
 * @return err code information, FIOPAD_SUCCESS indicates success，others indicates failed
 */
FError FIOPadSetConfig(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadFunc func, FIOPadPull pull, FIOPadDrive drive)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FIOPAD_ASSERT_REG0_OFF(pin_reg_off);
    FIOPAD_ASSERT_FUNC(func);
    FIOPAD_ASSERT_PULL(pull);
    FIOPAD_ASSERT_DRIVE(drive);
    u32 ret = FIOPAD_SUCCESS;
    uintptr base_addr = instance_p->config.base_address;
    u32 reg_val = FIOPAD_READ_REG32(base_addr, pin_reg_off);
    
    reg_val &= ~FIOPAD_REG0_FUNC_MASK;
    reg_val |= FIOPAD_REG0_FUNC_SET(func);

    reg_val &= ~FIOPAD_REG0_PULL_MASK;
    reg_val |= FIOPAD_REG0_PULL_SET(pull);

    reg_val &= ~FIOPAD_REG0_DRIVE_MASK;
    reg_val |= FIOPAD_REG0_DRIVE_SET(drive);

    FIOPAD_WRITE_REG32(base_addr, pin_reg_off, reg_val);
    reg_val = FIOPAD_READ_REG32(base_addr, pin_reg_off);

    return ret;
}

/**
 * @name: FIOPadGetConfig
 * @msg: set the func, up_down_pull,  driver strength of IO pins
 * @param {FIOPadCtrl} *instance_p, instance of FIOPAD controller
 * @param {u32} pin_reg_off, pin reg offset
 * @param {FIOPadFunc} *func, multiplexing function
 * @param {FIOPadPull} *pull, up_down_pull configurations
 * @param {FIOPadDrive} *driver, driver strength
 * @return err code information, FIOPAD_SUCCESS indicates success，others indicates failed
 */
FError FIOPadGetConfig(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadFunc *func, FIOPadPull *pull, FIOPadDrive *drive)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FIOPAD_ASSERT_REG0_OFF(pin_reg_off);
    u32 ret = FIOPAD_SUCCESS;
    uintptr base_addr = instance_p->config.base_address;
    u32 reg_val = FIOPAD_READ_REG32(base_addr, pin_reg_off);

    *func = FIOPAD_REG0_FUNC_GET(reg_val);
    *pull = FIOPAD_REG0_PULL_GET(reg_val);
    *drive = FIOPAD_REG0_DRIVE_GET(reg_val);

    return ret;
}

/**
 * @name: FIOPadGetDelay
 * @msg: get the current delay configuration of IO pins
 * @param {FIOPadCtrl} *instance_p, instance of FIOPAD controller
 * @param {u32} pin_reg_off, pin reg offset
 * @param {FIOPadDelayDir} dir, the delay direction
 * @param {FIOPadDelayType} type, the delay type
 * @return {FIOPadDelay}  current delay value
 */
FIOPadDelay FIOPadGetDelay(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadDelayDir dir, FIOPadDelayType type)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FIOPAD_ASSERT_REG1_OFF(pin_reg_off);
    uintptr base_addr = instance_p->config.base_address;
    const u32 reg_val = FIOPAD_READ_REG32(base_addr, pin_reg_off);
    u8 delay = 0;

    if (FIOPAD_OUTPUT_DELAY == dir)
    {
        if (FIOPAD_DELAY_FINE_TUNING == type)
        {
            delay = FIOPAD_REG1_OUT_DELAY_DELICATE_GET(reg_val);
        }
        else if (FIOPAD_DELAY_COARSE_TUNING == type)
        {
            delay = FIOPAD_REG1_OUT_DELAY_ROUGH_GET(reg_val);
        }
        else
        {
            FASSERT(0);
        }
    }
    else if (FIOPAD_INPUT_DELAY == dir)
    {
        if (FIOPAD_DELAY_FINE_TUNING == type)
        {
            delay = FIOPAD_REG1_IN_DELAY_DELICATE_GET(reg_val);
        }
        else if (FIOPAD_DELAY_COARSE_TUNING == type)
        {
            delay = FIOPAD_REG1_IN_DELAY_ROUGH_GET(reg_val);
        }
        else
        {
            FASSERT(0);
        }
    }
    else
    {
        FASSERT(0);
    }

    FIOPAD_ASSERT_DELAY(delay);

    return (FIOPadDelay)delay;
}

/**
 * @name: FIOPadSetDelay
 * @msg: set the current delay configuration of IO pins
 * @param {FIOPadCtrl} *instance_p, instance of FIOPAD controller
 * @param {u32} pin_reg_off, pin reg offset
 * @param {FIOPadDelayDir} dir, the delay direction
 * @param {FIOPadDelayType} type, the delay type
 * @param {FIOPadDelay} delay, delay value
 * @return err code information, FIOPAD_SUCCESS indicates success，others indicates failed
 */
FError FIOPadSetDelay(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadDelayDir dir, FIOPadDelayType type, FIOPadDelay delay)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FIOPAD_ASSERT_REG1_OFF(pin_reg_off);
    FIOPAD_ASSERT_DELAY(delay);
    u32 ret = FIOPAD_SUCCESS;
    uintptr base_addr = instance_p->config.base_address;
    u32 reg_val = FIOPAD_READ_REG32(base_addr, pin_reg_off);

    if (FIOPAD_OUTPUT_DELAY == dir)
    {
        if (FIOPAD_DELAY_FINE_TUNING == type)
        {
            reg_val &= ~FIOPAD_REG1_OUT_DELAY_DELICATE_MASK;
            reg_val |= FIOPAD_REG1_OUT_DELAY_DELICATE_SET(delay);
        }
        else if (FIOPAD_DELAY_COARSE_TUNING == type)
        {
            reg_val &= ~FIOPAD_REG1_OUT_DELAY_ROUGH_MASK;
            reg_val |= FIOPAD_REG1_OUT_DELAY_ROUGH_SET(delay);
        }
        else
        {
            FASSERT(0);
        }
    }
    else if (FIOPAD_INPUT_DELAY == dir)
    {
        if (FIOPAD_DELAY_FINE_TUNING == type)
        {
            reg_val &= ~FIOPAD_REG1_IN_DELAY_DELICATE_MASK;
            reg_val |= FIOPAD_REG1_IN_DELAY_DELICATE_SET(delay);
        }
        else if (FIOPAD_DELAY_COARSE_TUNING == type)
        {
            reg_val &= ~FIOPAD_REG1_IN_DELAY_ROUGH_MASK;
            reg_val |= FIOPAD_REG1_IN_DELAY_ROUGH_SET(delay);
        }
        else
        {
            FASSERT(0);
        }
    }
    else
    {
        FASSERT(0);
    }

    FIOPAD_WRITE_REG32(base_addr, pin_reg_off, reg_val);

    return ret;
}

/**
 * @name: FPinSetDelayEn
 * @msg: Enable/disable IO pin delay
 * @param {FIOPadCtrl} *instance_p, instance of FIOPAD controller
 * @param {u32} pin_reg_off, pin reg offset
 * @param {FIOPadDelayDir} dir, the delay direction
 * @param {boolean} enable TRUE: enable, FALSE: disable
 * @return err code information, FIOPAD_SUCCESS indicates success，others indicates failed
 */
FError FIOPadSetDelayEn(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadDelayDir dir, boolean enable)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FIOPAD_ASSERT_REG1_OFF(pin_reg_off);
    u32 ret = FIOPAD_SUCCESS;
    uintptr base_addr = instance_p->config.base_address;
    u32 reg_val = FIOPAD_READ_REG32(base_addr, pin_reg_off);

    if (FIOPAD_OUTPUT_DELAY == dir)
    {
        if (enable)
        {
            reg_val |= FIOPAD_REG1_OUT_DELAY_EN;
        }
        else
        {
            reg_val &= ~FIOPAD_REG1_OUT_DELAY_EN;
        }
    }
    else if (FIOPAD_INPUT_DELAY == dir)
    {
        if (enable)
        {
            reg_val |= FIOPAD_REG1_IN_DELAY_EN;
        }
        else
        {
            reg_val &= ~FIOPAD_REG1_IN_DELAY_EN;
        }
    }
    else
    {
        FASSERT(0);
    }

    FIOPAD_WRITE_REG32(base_addr, pin_reg_off, reg_val);

    return ret;
}

/**
 * @name: FIOPadDeInitialize
 * @msg: DeInitialization function for the device instance
 * @param {FIOPadCtrl} *pctrl, instance of FIOPAD controller
 * @return {*}
 */
FError FIOPadDeInitialize(FIOPadCtrl *instance_p)
{
    FASSERT(instance_p);
    FError ret = FIOPAD_SUCCESS;
    instance_p->is_ready = 0;
    memset(instance_p, 0, sizeof(*instance_p));
    
    return ret;
}