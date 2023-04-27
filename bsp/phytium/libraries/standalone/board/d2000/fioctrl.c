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
 * Description:  This files is for io-ctrl function implementation (io-mux/io-config/io-delay)
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/22   init commit
 */


/***************************** Include Files *********************************/
#include "fparameters.h"
#include "fio.h"
#include "fkernel.h"
#include "fassert.h"
#include "fdebug.h"

#include "fioctrl.h"
#include "fpinctrl.h"

/************************** Constant Definitions *****************************/
/* Bit[0] : 输入延迟功能使能  */
#define FIOCTRL_DELAY_EN(delay_beg)                      BIT(delay_beg)
#define FIOCTRL_INPUT_DELAY_OFF                          0

/* Bit[3:1] : 输入延迟精调档位选择 */
#define FIOCTRL_DELICATE_DELAY_MASK(delay_beg)             GENMASK((delay_beg + 3), (delay_beg + 1))
#define FIOCTRL_DELICATE_DELAY_GET(reg_val, delay_beg)     GET_REG32_BITS((reg_val), (delay_beg + 3), (delay_beg + 1))
#define FIOCTRL_DELICATE_DELAY_SET(val, delay_beg)         SET_REG32_BITS((val), (delay_beg + 3), (delay_beg + 1))

/* Bit[6:4] : 输入延迟粗调档位选择 */
#define FIOCTRL_ROUGH_DELAY_MASK(delay_beg)               GENMASK((delay_beg + 6), (delay_beg + 4))
#define FIOCTRL_ROUGH_DELAY_GET(reg_val, delay_beg)       GET_REG32_BITS((reg_val), (delay_beg + 6), (delay_beg + 4))
#define FIOCTRL_ROUGH_DELAY_SET(val, delay_beg)           SET_REG32_BITS((val), (delay_beg + 6), (delay_beg + 4))

/* Bit[7] : 保留 */
/* Bit[8] : 输出延迟功能使能 */

/* Bit[11:9] : 输出延迟精调档位选择 */
/* Bit [14:12] : 输出延迟粗调档位选择  */
/* Bit [15] : 保留 */

#define FIOCTRL_FUNC_BEG_OFF(reg_bit)   ((reg_bit) + 0)
#define FIOCTRL_FUNC_END_OFF(reg_bit)   ((reg_bit) + 1) /* bit[1:0] 复用功能占2个位 */
#define FIOCTRL_PULL_BEG_OFF(reg_bit)   ((reg_bit) + 2)
#define FIOCTRL_PULL_END_OFF(reg_bit)   ((reg_bit) + 3) /* bit[3:2] 上下拉功能占2个位 */

#define FIOCTRL_DELAY_IN_BEG_OFF(reg_bit)    ((reg_bit) + 0)
#define FIOCTRL_DELAY_IN_END_OFF(reg_bit)    ((reg_bit) + 7) /* bit[8:1] 输入延时占7个位 */
#define FIOCTRL_DELAY_OUT_BEG_OFF(reg_bit)   ((reg_bit) + 8)
#define FIOCTRL_DELAY_OUT_END_OFF(reg_bit)   ((reg_bit) + 15) /* bit[15:9] 输出延时占7个位 */

/* 芯片引脚控制寄存器的起止位置 */
#define FIOCTRL_REG_OFFSET_MIN                           0x200
#define FIOCTRL_REG_OFFSET_MAX                           0x22c

/* 芯片引脚延时寄存器的起止位置 */
#define FIOCTRL_DELAY_REG_OFFSET_MIN                     0x400
#define FIOCTRL_DELAY_REG_OFFSET_MAX                     0x404

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FIOCTRL_DEBUG_TAG "FIOCTRL"
#define FIOCTRL_ERROR(format, ...) FT_DEBUG_PRINT_E(FIOCTRL_DEBUG_TAG, format, ##__VA_ARGS__)
#define FIOCTRL_WARN(format, ...)  FT_DEBUG_PRINT_W(FIOCTRL_DEBUG_TAG, format, ##__VA_ARGS__)
#define FIOCTRL_INFO(format, ...)  FT_DEBUG_PRINT_I(FIOCTRL_DEBUG_TAG, format, ##__VA_ARGS__)
#define FIOCTRL_DEBUG(format, ...) FT_DEBUG_PRINT_D(FIOCTRL_DEBUG_TAG, format, ##__VA_ARGS__)

#define FIOCTRL_ASSERT_REG_OFF(pin) FASSERT_MSG(((pin.reg_off >= FIOCTRL_REG_OFFSET_MIN) && (pin.reg_off <= FIOCTRL_REG_OFFSET_MAX)), "invalid pin register off @%d", (pin.reg_off))
#define FIOCTRL_ASSERT_FUNC(func) FASSERT_MSG((func < FPIN_NUM_OF_FUNC), "invalid func as %d", (func))
#define FIOCTRL_ASSERT_PULL(pull) FASSERT_MSG((pull < FPIN_NUM_OF_PULL), "invalid pull as %d", (pull))

#define FIOCTRL_ASSERT_DELAY_REG_OFF(pin) FASSERT_MSG(((pin.reg_off >= FIOCTRL_DELAY_REG_OFFSET_MIN) && (pin.reg_off <= FIOCTRL_DELAY_REG_OFFSET_MAX)), "invalid delay pin register off @%d", (pin.reg_off))
#define FIOCTRL_ASSERT_DELAY(delay) FASSERT_MSG(((delay) < FPIN_NUM_OF_DELAY), "invalid delay as %d", (delay));
/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/*****************************************************************************/

/**
 * @name: FPinGetFunc
 * @msg: 获取IO引脚当前的复用功能
 * @return {FPinFunc} 当前的复用功能
 * @param {FPinIndex} pin IO引脚索引
 * @note 参考编程手册，使用 FIOCTRL_INDEX 宏定义index的值
 */
FPinFunc FPinGetFunc(const FPinIndex pin)
{
    FIOCTRL_ASSERT_REG_OFF(pin);

    u32 func_beg = FIOCTRL_FUNC_BEG_OFF(pin.reg_bit);
    u32 func_end = FIOCTRL_FUNC_END_OFF(pin.reg_bit);
    u32 reg_val = FtIn32(FIOCTRL_REG_BASE_ADDR + pin.reg_off);
    u32 func = GET_REG32_BITS(reg_val, func_end, func_beg);
    FIOCTRL_ASSERT_FUNC(func);

    return (FPinFunc)GET_REG32_BITS(reg_val, func_end, func_beg);
}

/**
 * @name: FPinSetFunc
 * @msg: 设置IO引脚复用功能
 * @return {*}
 * @param {FPinIndex} pin IO引脚索引
 * @param {FPinFunc} func IO复用功能
 * @note 参考编程手册，使用 FIOCTRL_INDEX 宏定义index的值
 */
void FPinSetFunc(const FPinIndex pin, FPinFunc func)
{
    FIOCTRL_ASSERT_REG_OFF(pin);
    FIOCTRL_ASSERT_FUNC(func);

    u32 func_beg = FIOCTRL_FUNC_BEG_OFF(pin.reg_bit);
    u32 func_end = FIOCTRL_FUNC_END_OFF(pin.reg_bit);
    u32 reg_val = FtIn32(FIOCTRL_REG_BASE_ADDR + pin.reg_off);

    reg_val &= ~GENMASK(func_end, func_beg);
    reg_val |= SET_REG32_BITS(func, func_end, func_beg);

    FtOut32(FIOCTRL_REG_BASE_ADDR + pin.reg_off, reg_val);
    return;
}

/**
 * @name: FPinGetPull
 * @msg: 获取IO引脚当前的上下拉设置
 * @return {*}
 * @param {FPinIndex} pin IO引脚索引
 * @note 参考编程手册，使用 FIOCTRL_INDEX 宏定义index的值
 */
FPinPull FPinGetPull(const FPinIndex pin)
{
    FIOCTRL_ASSERT_REG_OFF(pin);

    u32 pull_beg = FIOCTRL_PULL_BEG_OFF(pin.reg_bit);
    u32 pull_end = FIOCTRL_PULL_END_OFF(pin.reg_bit);
    u32 reg_val = FtIn32(FIOCTRL_REG_BASE_ADDR + pin.reg_off);
    u32 pull = GET_REG32_BITS(reg_val, pull_end, pull_beg);

    FIOCTRL_ASSERT_PULL(pull);
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
    FIOCTRL_ASSERT_REG_OFF(pin);
    FIOCTRL_ASSERT_PULL(pull);

    u32 pull_beg = FIOCTRL_PULL_BEG_OFF(pin.reg_bit);
    u32 pull_end = FIOCTRL_PULL_END_OFF(pin.reg_bit);
    u32 reg_val = FtIn32(FIOCTRL_REG_BASE_ADDR + pin.reg_off);

    reg_val &= ~GENMASK(pull_end, pull_beg);
    reg_val |= SET_REG32_BITS(pull, pull_end, pull_beg);

    FtOut32(FIOCTRL_REG_BASE_ADDR + pin.reg_off, reg_val);
    return;
}

/**
 * @name: FPinGetConfig
 * @msg: 获取IO引脚的复用、上下拉和驱动能力设置
 * @return {*}
 * @param {FPinIndex} pin IO引脚索引
 * @param {FPinFunc} *func IO复用功能
 * @param {FPinPull} *pull pull 上下拉设置
 */
void FPinGetConfig(const FPinIndex pin, FPinFunc *func, FPinPull *pull)
{
    FIOCTRL_ASSERT_REG_OFF(pin);

    u32 func_beg = FIOCTRL_FUNC_BEG_OFF(pin.reg_bit);
    u32 func_end = FIOCTRL_FUNC_END_OFF(pin.reg_bit);
    u32 pull_beg = FIOCTRL_PULL_BEG_OFF(pin.reg_bit);
    u32 pull_end = FIOCTRL_PULL_END_OFF(pin.reg_bit);
    u32 reg_val = FtIn32(FIOCTRL_REG_BASE_ADDR + pin.reg_off);

    if (func)
    {
        *func = GET_REG32_BITS(reg_val, func_end, func_beg);
    }

    if (pull)
    {
        *pull = GET_REG32_BITS(reg_val, pull_end, pull_beg);
    }

    return;
}

/**
 * @name: FPinSetConfig
 * @msg: 设置IO引脚的复用、上下拉和驱动能力
 * @return {*}
 * @param {FPinIndex} pin IO引脚索引
 * @param {FPinFunc} func IO复用功能
 * @param {FPinPull} pull pull 上下拉设置
 */
void FPinSetConfig(const FPinIndex pin, FPinFunc func, FPinPull pull)
{
    FIOCTRL_ASSERT_REG_OFF(pin);
    u32 func_beg = FIOCTRL_FUNC_BEG_OFF(pin.reg_bit);
    u32 func_end = FIOCTRL_FUNC_END_OFF(pin.reg_bit);
    u32 pull_beg = FIOCTRL_PULL_BEG_OFF(pin.reg_bit);
    u32 pull_end = FIOCTRL_PULL_END_OFF(pin.reg_bit);
    u32 reg_val = FtIn32(FIOCTRL_REG_BASE_ADDR + pin.reg_off);

    reg_val &= ~GENMASK(func_end, func_beg);
    reg_val |= SET_REG32_BITS(func, func_end, func_beg);

    reg_val &= ~GENMASK(pull_end, pull_beg);
    reg_val |= SET_REG32_BITS(pull, pull_end, pull_beg);

    FtOut32(FIOCTRL_REG_BASE_ADDR + pin.reg_off, reg_val);
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
    FIOCTRL_ASSERT_DELAY_REG_OFF(pin);
    u8 delay = 0;
    const u32 reg_val = FtIn32(FIOCTRL_REG_BASE_ADDR + pin.reg_off);
    u32 delay_beg = 0, delay_end = 0;

    if (FPIN_OUTPUT_DELAY == dir)
    {
        delay_beg = FIOCTRL_DELAY_OUT_BEG_OFF(pin.reg_off);
    }
    else if (FPIN_INPUT_DELAY == dir)
    {
        delay_beg = FIOCTRL_DELAY_IN_BEG_OFF(pin.reg_off);
    }
    else
    {
        FASSERT(0);
    }

    if (FPIN_DELAY_FINE_TUNING == type)
    {
        delay = FIOCTRL_DELICATE_DELAY_GET(reg_val, delay_beg);
    }
    else if (FPIN_DELAY_COARSE_TUNING == type)
    {
        delay = FIOCTRL_ROUGH_DELAY_GET(reg_val, delay_beg);
    }
    else
    {
        FASSERT(0);
    }

    FIOCTRL_ASSERT_DELAY(delay);
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
    FIOCTRL_ASSERT_DELAY_REG_OFF(pin);
    boolean enabled = FALSE;
    const u32 reg_val = FtIn32(FIOCTRL_REG_BASE_ADDR + pin.reg_off);
    u32 delay_beg = 0, delay_end = 0;

    if (FPIN_OUTPUT_DELAY == dir)
    {
        delay_beg = FIOCTRL_DELAY_OUT_BEG_OFF(pin.reg_off);
    }
    else if (FPIN_INPUT_DELAY == dir)
    {
        delay_beg = FIOCTRL_DELAY_IN_BEG_OFF(pin.reg_off);
    }
    else
    {
        FASSERT(0);
    }

    if (FIOCTRL_DELAY_EN(delay_beg) & reg_val)
    {
        enabled = TRUE;
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
 * @param {FPinDelay} delay 延时档位设置 0 ~ 8 档可用
 */
void FPinSetDelay(const FPinIndex pin, FPinDelayDir dir, FPinDelayType type, FPinDelay delay)
{
    FIOCTRL_ASSERT_DELAY_REG_OFF(pin);
    FIOCTRL_ASSERT_DELAY(delay);
    u32 reg_val = FtIn32(FIOCTRL_REG_BASE_ADDR + pin.reg_off);
    u32 delay_beg = 0, delay_end = 0;

    if (FPIN_OUTPUT_DELAY == dir)
    {
        delay_beg = FIOCTRL_DELAY_OUT_BEG_OFF(pin.reg_off);
    }
    else if (FPIN_INPUT_DELAY == dir)
    {
        delay_beg = FIOCTRL_DELAY_IN_BEG_OFF(pin.reg_off);
    }
    else
    {
        FASSERT(0);
    }

    if (FPIN_DELAY_FINE_TUNING == type)
    {
        reg_val &= ~FIOCTRL_DELICATE_DELAY_MASK(delay_beg);
        delay = FIOCTRL_DELICATE_DELAY_GET(reg_val, delay_beg);
    }
    else if (FPIN_DELAY_COARSE_TUNING == type)
    {
        reg_val &= ~FIOCTRL_ROUGH_DELAY_MASK(delay_beg);
        delay = FIOCTRL_ROUGH_DELAY_GET(reg_val, delay_beg);
    }
    else
    {
        FASSERT(0);
    }

    FtOut32(FIOCTRL_REG_BASE_ADDR + pin.reg_off, reg_val);
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
    FIOCTRL_ASSERT_DELAY_REG_OFF(pin);
    u32 reg_val = FtIn32(FIOCTRL_REG_BASE_ADDR + pin.reg_off);
    u32 delay_beg = 0, delay_end = 0;

    if (FPIN_OUTPUT_DELAY == dir)
    {
        delay_beg = FIOCTRL_DELAY_OUT_BEG_OFF(pin.reg_off);
    }
    else if (FPIN_INPUT_DELAY == dir)
    {
        delay_beg = FIOCTRL_DELAY_IN_BEG_OFF(pin.reg_off);
    }
    else
    {
        FASSERT(0);
    }

    reg_val &= ~FIOCTRL_DELAY_EN(delay_beg);
    if (enable)
    {
        reg_val |= FIOCTRL_DELAY_EN(delay_beg);
    }

    FtOut32(FIOCTRL_REG_BASE_ADDR + pin.reg_off, reg_val);
    return;
}