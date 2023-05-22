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
 * FilePath: fiopad_comm.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:25:29
 * Description:  This file is for io-pad function definition
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2021/11/5    init commit
 * 1.1   zhugengyu  2022/3/21    adopt to lastest tech spec.
 */


/***************************** Include Files *********************************/
#include "fparameters.h"
#include "fio.h"
#include "fkernel.h"
#include "fassert.h"
#include "fdebug.h"
#include "stdio.h"
#include "fpinctrl.h"

/************************** Constant Definitions *****************************/
/** @name IO PAD Control Register
 */
#define FIOPAD_X_REG0_BEG_OFFSET            0x0    /* 上下拉/驱动能力/复用功能配置 */
#define FIOPAD_X_REG0_END_OFFSET            0x24c

#define FIOPAD_X_REG1_BEG_OFFSET            0x1024 /* 输入/输出延时配置 */
#define FIOPAD_X_REG1_END_OFFSET            0x124c

/** @name X_reg0 Register
 */
#define FIOPAD_X_REG0_PULL_MASK        GENMASK(9, 8)    /* 上下拉配置 */
#define FIOPAD_X_REG0_PULL_GET(x)      GET_REG32_BITS((x), 9, 8)
#define FIOPAD_X_REG0_PULL_SET(x)      SET_REG32_BITS((x), 9, 8)

#define FIOPAD_X_REG0_DRIVE_MASK       GENMASK(7, 4)    /* 驱动能力配置 */
#define FIOPAD_X_REG0_DRIVE_GET(x)     GET_REG32_BITS((x), 7, 4)
#define FIOPAD_X_REG0_DRIVE_SET(x)     SET_REG32_BITS((x), 7, 4)

#define FIOPAD_X_REG0_FUNC_MASK        GENMASK(2, 0)   /* 引脚复用配置 */
#define FIOPAD_X_REG0_FUNC_GET(x)      GET_REG32_BITS((x), 2, 0)
#define FIOPAD_X_REG0_FUNC_SET(x)      SET_REG32_BITS((x), 2, 0)

/** @name X_reg1 Register
 */
#define FIOPAD_X_REG1_OUT_DELAY_EN                BIT(8)
#define FIOPAD_X_REG1_OUT_DELAY_DELICATE_MASK     GENMASK(11, 9)
#define FIOPAD_X_REG1_OUT_DELAY_DELICATE_GET(x)   GET_REG32_BITS((x), 11, 9) /* 延时精调  */
#define FIOPAD_X_REG1_OUT_DELAY_DELICATE_SET(x)   SET_REG32_BITS((x), 11, 9)
#define FIOPAD_X_REG1_OUT_DELAY_ROUGH_MASK        GENMASK(14, 12)
#define FIOPAD_X_REG1_OUT_DELAY_ROUGH_GET(x)      GET_REG32_BITS((x), 14, 12) /* 延时粗调 */
#define FIOPAD_X_REG1_OUT_DELAY_ROUGH_SET(x)      SET_REG32_BITS((x), 14, 12)

#define FIOPAD_X_REG1_IN_DELAY_EN                BIT(0)
#define FIOPAD_X_REG1_IN_DELAY_DELICATE_MASK     GENMASK(3, 1)
#define FIOPAD_X_REG1_IN_DELAY_DELICATE_GET(x)   GET_REG32_BITS((x), 3, 1) /* 延时精调 */
#define FIOPAD_X_REG1_IN_DELAY_DELICATE_SET(x)   SET_REG32_BITS((x), 3, 1)
#define FIOPAD_X_REG1_IN_DELAY_ROUGH_MASK        GENMASK(6, 4)
#define FIOPAD_X_REG1_IN_DELAY_ROUGH_GET(x)      GET_REG32_BITS((x), 6, 4) /* 延时粗调 */
#define FIOPAD_X_REG1_IN_DELAY_ROUGH_SET(x)      SET_REG32_BITS((x), 6, 4)

#define FIOPAD_DELAY_MAX                       15

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
static inline u32 FIOPadRead(FPinIndex pin)
{
    return FtIn32(FIOPAD_BASE_ADDR + pin.reg_off);
}

static inline void FIOPadWrite(FPinIndex pin, u32 reg_val)
{
    FtOut32(FIOPAD_BASE_ADDR + pin.reg_off, reg_val);
    return;
}

#define FIOPAD_ASSERT_REG0_OFF(pin)      FASSERT_MSG((FIOPAD_X_REG0_END_OFFSET >= pin.reg_off), "invalid reg0 offset @0x%x\r\n", (pin.reg_off))
#define FIOPAD_ASSERT_FUNC(func)         FASSERT_MSG((func < FPIN_NUM_OF_FUNC), "invalid func as %d\r\n", (func))
#define FIOPAD_ASSERT_PULL(pull)         FASSERT_MSG((pull < FPIN_NUM_OF_PULL), "invalid pull as %d\r\n", (pull))
#define FIOPAD_ASSERT_DRIVE(drive)       FASSERT_MSG((drive < FPIN_NUM_OF_DRIVE), "invalid pull as %d\r\n", (drive))

#define FIOPAD_ASSERT_REG1_OFF(pin)      FASSERT_MSG(((FIOPAD_X_REG1_BEG_OFFSET <= pin.reg_off) && (FIOPAD_X_REG1_END_OFFSET >= pin.reg_off)), "invalid reg1 offset @0x%x\r\n", (pin.reg_off))
#define FIOPAD_ASSERT_DELAY(delay)       FASSERT_MSG((delay < FPIN_NUM_OF_DELAY), "invalid delay as %d\r\n", (delay))

#define FIOPAD_DEBUG_TAG "FIOPAD"
#define FIOPAD_ERROR(format, ...)   FT_DEBUG_PRINT_E(FIOPAD_DEBUG_TAG, format, ##__VA_ARGS__)
#define FIOPAD_WARN(format, ...)    FT_DEBUG_PRINT_W(FIOPAD_DEBUG_TAG, format, ##__VA_ARGS__)
#define FIOPAD_INFO(format, ...)    FT_DEBUG_PRINT_I(FIOPAD_DEBUG_TAG, format, ##__VA_ARGS__)
#define FIOPAD_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FIOPAD_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/
/**
 * @name: FPinGetFunc
 * @msg: 获取IO引脚当前的复用功能
 * @return {FPinFunc} 当前的复用功能
 * @param {FPinIndex} pin IO引脚索引
 * @note 参考编程手册，使用 FIOPAD_INDEX 宏定义index的值
 */
FPinFunc FPinGetFunc(const FPinIndex pin)
{
    FIOPAD_ASSERT_REG0_OFF(pin);
    u32 func = FIOPAD_X_REG0_FUNC_GET(FIOPadRead(pin));
    FIOPAD_ASSERT_FUNC(func);
    return (FPinFunc)func;
}

/**
 * @name: FPinSetFunc
 * @msg: 设置IO引脚复用功能
 * @return {*}
 * @param {FPinIndex} pin IO引脚索引
 * @param {FPinFunc} func IO复用功能
 * @note 参考编程手册，使用 FIOPAD_INDEX 宏定义index的值
 */
void FPinSetFunc(const FPinIndex pin, FPinFunc func)
{
    FIOPAD_ASSERT_REG0_OFF(pin);
    FIOPAD_ASSERT_FUNC(func);
    u32 reg_val = FIOPadRead(pin);
    u32 test_val = 0;

    reg_val &= ~FIOPAD_X_REG0_FUNC_MASK;
    reg_val |= FIOPAD_X_REG0_FUNC_SET(func);

    FIOPadWrite(pin, reg_val);

    test_val = FIOPadRead(pin);

    if (reg_val != test_val)
    {
        FIOPAD_ERROR("ERROR: FIOPad write is failed ,pin is %x\n, 0x%x != 0x%x",
                     pin.reg_off, reg_val, test_val);
    }

    return;
}

/**
 * @name: FPinGetDrive
 * @msg: 获取IO引脚的驱动能力
 * @return {FPinDrive} 引脚的当前的驱动能力
 * @param {FPinIndex} pin IO引脚索引
 */
FPinDrive FPinGetDrive(const FPinIndex pin)
{
    FIOPAD_ASSERT_REG0_OFF(pin);
    u32 drive = FIOPAD_X_REG0_DRIVE_GET(FIOPadRead(pin));
    FIOPAD_ASSERT_DRIVE(drive);
    return (FPinDrive)drive;
}

/**
 * @name: FPinSetDrive
 * @msg: 设置IO引脚的驱动能力
 * @return {*}
 * @param {FPinIndex} pin, IO引脚索引
 * @param {FPinDrive} drive, 引脚驱动能力设置
 */
void FPinSetDrive(const FPinIndex pin, FPinDrive drive)
{
    FIOPAD_ASSERT_REG0_OFF(pin);
    FIOPAD_ASSERT_DRIVE(drive);
    u32 reg_val = FIOPadRead(pin);

    reg_val &= ~FIOPAD_X_REG0_DRIVE_MASK;
    reg_val |= FIOPAD_X_REG0_DRIVE_SET(drive);

    FIOPadWrite(pin, reg_val);
    return;
}

void FPinGetConfig(const FPinIndex pin, FPinFunc *func, FPinPull *pull, FPinDrive *drive)
{
    FIOPAD_ASSERT_REG0_OFF(pin);
    u32 reg_val = FIOPadRead(pin);

    if (func)
    {
        *func = FIOPAD_X_REG0_FUNC_GET(reg_val);
    }

    if (pull)
    {
        *pull = FIOPAD_X_REG0_PULL_GET(reg_val);
    }

    if (drive)
    {
        *drive = FIOPAD_X_REG0_DRIVE_GET(reg_val);
    }

    return;
}

void FPinSetConfig(const FPinIndex pin, FPinFunc func, FPinPull pull, FPinDrive drive)
{
    FIOPAD_ASSERT_REG0_OFF(pin);
    u32 reg_val = FIOPadRead(pin);

    reg_val &= ~FIOPAD_X_REG0_FUNC_MASK;
    reg_val |= FIOPAD_X_REG0_FUNC_SET(func);

    reg_val &= ~FIOPAD_X_REG0_PULL_MASK;
    reg_val |= FIOPAD_X_REG0_PULL_SET(pull);

    reg_val &= ~FIOPAD_X_REG0_DRIVE_MASK;
    reg_val |= FIOPAD_X_REG0_DRIVE_SET(drive);

    FIOPadWrite(pin, reg_val);
    return;
}

/**
 * @name: FPinGetPull
 * @msg: 获取IO引脚当前的上下拉设置
 * @return {*}
 * @param {FPinIndex} pin IO引脚索引
 * @note 参考编程手册，使用 FIOPAD_INDEX 宏定义index的值
 */
FPinPull FPinGetPull(const FPinIndex pin)
{
    FIOPAD_ASSERT_REG0_OFF(pin);
    u32 pull = FIOPAD_X_REG0_PULL_GET(FIOPadRead(pin));
    FIOPAD_ASSERT_PULL(pull);
    return (FPinPull)pull;
}

/**
 * @name: FPinSetPull
 * @msg: 设置IO引脚当前的上下拉
 * @return {*}
 * @param {FPinIndex} pin IO引脚索引
 * @param {FPinPull} pull 上下拉设置
 */
void FPinSetPull(const FPinIndex pin, FPinPull pull)
{
    FIOPAD_ASSERT_REG0_OFF(pin);
    FIOPAD_ASSERT_PULL(pull);

    u32 reg_val = FIOPadRead(pin);

    reg_val &= ~FIOPAD_X_REG0_PULL_MASK;
    reg_val |= FIOPAD_X_REG0_PULL_SET(pull);

    FIOPadWrite(pin, reg_val);
    return;
}

/**
 * @name: FPinGetDelay
 * @msg: 获取IO引脚当前的延时设置
 * @return {FPinDelay} 当前的延时设置
 * @param {FPinIndex} pin IO引脚延时设置索引
 * @param {FPinDelayDir} dir 输入/输出延时
 * @param {FPinDelayType} type 精调/粗调延时
 */
FPinDelay FPinGetDelay(const FPinIndex pin, FPinDelayDir dir, FPinDelayType type)
{
    FIOPAD_ASSERT_REG1_OFF(pin);
    const u32 reg_val = FIOPadRead(pin);
    u8 delay = 0;

    if (FPIN_OUTPUT_DELAY == dir)
    {
        if (FPIN_DELAY_FINE_TUNING == type)
        {
            delay = FIOPAD_X_REG1_OUT_DELAY_DELICATE_GET(reg_val);
        }
        else if (FPIN_DELAY_COARSE_TUNING == type)
        {
            delay = FIOPAD_X_REG1_OUT_DELAY_ROUGH_GET(reg_val);
        }
        else
        {
            FASSERT(0);
        }
    }
    else if (FPIN_INPUT_DELAY == dir)
    {
        if (FPIN_DELAY_FINE_TUNING == type)
        {
            delay = FIOPAD_X_REG1_IN_DELAY_DELICATE_GET(reg_val);
        }
        else if (FPIN_DELAY_COARSE_TUNING == type)
        {
            delay = FIOPAD_X_REG1_IN_DELAY_ROUGH_GET(reg_val);
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
    return (FPinDelay)delay;
}

/**
 * @name: FPinGetDelayEn
 * @msg: 获取IO引脚当前的延时使能标志位
 * @return {*}
 * @param {FPinIndex} pin IO引脚延时设置索引
 * @param {FPinDelayDir} dir 输入/输出延时
 */
boolean FPinGetDelayEn(const FPinIndex pin, FPinDelayDir dir)
{
    FIOPAD_ASSERT_REG1_OFF(pin);
    const u32 reg_val = FIOPadRead(pin);
    boolean enabled = FALSE;

    if (FPIN_OUTPUT_DELAY == dir)
    {
        if (FIOPAD_X_REG1_OUT_DELAY_EN & reg_val)
        {
            enabled = TRUE;
        }
        else
        {
            enabled = FALSE;
        }
    }
    else if (FPIN_INPUT_DELAY == dir)
    {
        if (FIOPAD_X_REG1_IN_DELAY_EN & reg_val)
        {
            enabled = TRUE;
        }
        else
        {
            enabled = FALSE;
        }
    }
    else
    {
        FASSERT(0);
    }

    return enabled;
}

/**
 * @name: FPinSetDelay
 * @msg: 设置IO引脚延时
 * @return {*}
 * @param {FPinIndex} pin IO引脚延时设置索引
 * @param {FPinDelayDir} dir 输入/输出延时
 * @param {FPinDelayType} type 精调/粗调延时
 * @param {FPinDelay} delay 延时设置
 */
void FPinSetDelay(const FPinIndex pin, FPinDelayDir dir, FPinDelayType type, FPinDelay delay)
{
    FIOPAD_ASSERT_REG1_OFF(pin);
    FIOPAD_ASSERT_DELAY(delay);
    u32 reg_val = FIOPadRead(pin);

    if (FPIN_OUTPUT_DELAY == dir)
    {
        if (FPIN_DELAY_FINE_TUNING == type)
        {
            reg_val &= ~FIOPAD_X_REG1_OUT_DELAY_DELICATE_MASK;
            reg_val |= FIOPAD_X_REG1_OUT_DELAY_DELICATE_SET(delay);
        }
        else if (FPIN_DELAY_COARSE_TUNING == type)
        {
            reg_val &= ~FIOPAD_X_REG1_OUT_DELAY_ROUGH_MASK;
            reg_val |= FIOPAD_X_REG1_OUT_DELAY_ROUGH_SET(delay);
        }
        else
        {
            FASSERT(0);
        }
    }
    else if (FPIN_INPUT_DELAY == dir)
    {
        if (FPIN_DELAY_FINE_TUNING == type)
        {
            reg_val &= ~FIOPAD_X_REG1_IN_DELAY_DELICATE_MASK;
            reg_val |= FIOPAD_X_REG1_IN_DELAY_DELICATE_SET(delay);
        }
        else if (FPIN_DELAY_COARSE_TUNING == type)
        {
            reg_val &= ~FIOPAD_X_REG1_IN_DELAY_ROUGH_MASK;
            reg_val |= FIOPAD_X_REG1_IN_DELAY_ROUGH_SET(delay);
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

    FIOPadWrite(pin, reg_val);
    return;
}

/**
 * @name: FPinSetDelayEn
 * @msg: 使能/去使能IO引脚延时
 * @return {*}
 * @param {FPinIndex} pin IO引脚延时设置索引
 * @param {FPinDelayDir} dir 输入/输出延时
 * @param {boolean} enable TRUE: 使能, FALSE: 去使能
 */
void FPinSetDelayEn(const FPinIndex pin, FPinDelayDir dir, boolean enable)
{
    FIOPAD_ASSERT_REG1_OFF(pin);
    u32 reg_val = FIOPadRead(pin);

    if (FPIN_OUTPUT_DELAY == dir)
    {
        if (enable)
        {
            reg_val |= FIOPAD_X_REG1_OUT_DELAY_EN;
        }
        else
        {
            reg_val &= ~FIOPAD_X_REG1_OUT_DELAY_EN;
        }
    }
    else if (FPIN_INPUT_DELAY == dir)
    {
        if (enable)
        {
            reg_val |= FIOPAD_X_REG1_IN_DELAY_EN;
        }
        else
        {
            reg_val &= ~FIOPAD_X_REG1_IN_DELAY_EN;
        }
    }
    else
    {
        FASSERT(0);
    }

    FIOPadWrite(pin, reg_val);
    return;
}


/**
 * @name: FPinSetDelayConfig
 * @msg: Update and enable common IO pin delay config
 * @return {NONE}
 * @param {FPinIndex} pin, IO pin index
 * @param {FPinDelayIOType} in_out_type, Select the input and output types ，
 * @param {FPinDelay} roungh_delay, delay rough setting
 * @param {FPinDelay} delicate_delay, delay delicate setting
 * @param {boolean} enable, enable delay
 */
void FPinSetDelayConfig(const FPinIndex pin, FPinDelayIOType in_out_type, FPinDelay roungh_delay, FPinDelay delicate_delay, boolean enable)
{
    FIOPAD_ASSERT_REG1_OFF(pin);
    u32 reg_val = FIOPadRead(pin);

    if (in_out_type == FPIN_DELAY_IN_TYPE)
    {
        reg_val = FIOPadRead(pin);

        /* update delicate input delay */
        reg_val &= ~FIOPAD_X_REG1_IN_DELAY_DELICATE_MASK;
        reg_val |= FIOPAD_X_REG1_IN_DELAY_DELICATE_SET(delicate_delay);

        /* update rough input delay */
        reg_val &= ~FIOPAD_X_REG1_IN_DELAY_ROUGH_MASK;
        reg_val |= FIOPAD_X_REG1_IN_DELAY_ROUGH_SET(roungh_delay);

        /* enable input delay */
        if (enable)
        {
            reg_val |= FIOPAD_X_REG1_IN_DELAY_EN;
        }
        else
        {
            reg_val &= ~FIOPAD_X_REG1_IN_DELAY_EN;
        }
    }
    else
    {
        /* update delicate output delay */
        reg_val &= ~FIOPAD_X_REG1_OUT_DELAY_DELICATE_MASK;
        reg_val |= FIOPAD_X_REG1_OUT_DELAY_DELICATE_SET(delicate_delay);

        /* update rough output delay */
        reg_val &= ~FIOPAD_X_REG1_OUT_DELAY_ROUGH_MASK;
        reg_val |= FIOPAD_X_REG1_OUT_DELAY_ROUGH_SET(roungh_delay);

        /* enable output delay */
        if (enable)
        {
            reg_val |= FIOPAD_X_REG1_OUT_DELAY_EN;
        }
        else
        {
            reg_val &= ~FIOPAD_X_REG1_OUT_DELAY_EN;
        }
    }

    FIOPadWrite(pin, reg_val);
    return;
}

/**
 * @name: FPinGetDelayConfig
 * @msg: Get current common IO pin delay config
 * @return {NONE}
 * @param {FPinIndex} pin, IO pin index
 * @param {FPinDelay} *in_roungh_delay, input delay rough setting (输入粗调)
 * @param {FPinDelay} *in_delicate_delay, input delay delicate setting (输入精调)
 * @param {FPinDelay} *out_roungh_delay, output delay rough setting (输出粗调)
 * @param {FPinDelay} *out_delicate_delay, output delay delicate setting (输出精调)
 */
void FPinGetDelayConfig(const FPinIndex pin, FPinDelay *in_roungh_delay, FPinDelay *in_delicate_delay,
                        FPinDelay *out_roungh_delay, FPinDelay *out_delicate_delay)
{
    FIOPAD_ASSERT_REG1_OFF(pin);
    u32 reg_val = FIOPadRead(pin);

    if (out_delicate_delay)
    {
        *out_delicate_delay = FIOPAD_X_REG1_OUT_DELAY_DELICATE_GET(reg_val);
    }

    if (out_roungh_delay)
    {
        *out_roungh_delay = FIOPAD_X_REG1_OUT_DELAY_ROUGH_GET(reg_val);
    }

    if (in_delicate_delay)
    {
        *in_delicate_delay = FIOPAD_X_REG1_IN_DELAY_DELICATE_GET(reg_val);
    }

    if (in_roungh_delay)
    {
        *in_roungh_delay = FIOPAD_X_REG1_IN_DELAY_ROUGH_GET(reg_val);
    }

    return;
}

/**
 * @name: FIOPadDumpPadFunc
 * @msg: print information of all iopad
 * @return {*}
 */
void FIOPadDumpPadFunc(void)
{
    uintptr beg_off = FIOPAD_0_FUNC_OFFSET;
    uintptr end_off = FIOPAD_147_FUNC_OFFSET;
    uintptr off;
    FPinIndex pin;
    const char *pull_state[FPIN_NUM_OF_PULL] = {"none", "down", "up"};

    FIOPAD_DEBUG("Pad Func Info...");
    for (off = beg_off; off <= end_off; off += 4U)
    {
        pin.reg_off = off;
        FIOPAD_DEBUG("  [0x%x] func: %d, ds: %d, pull: %s ",
                     pin.reg_off,
                     FPinGetFunc(pin),
                     FPinGetDrive(pin),
                     pull_state[FPinGetPull(pin)]);
    }
}