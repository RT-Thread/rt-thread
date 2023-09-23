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
 * FilePath: fiopad_hw.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:29:05
 * Description:  This files is for the iopad register related definition
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhangyan   2023/7/3    first release
 */

#ifndef FIOPAD_HW_H
#define FIOPAD_HW_H

#include "fparameters.h"
#include "fkernel.h"
#include "fiopad.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** @name X_reg0 Register
 */
#define FIOPAD_REG0_PULL_MASK        GENMASK(9, 8)    /* 上下拉配置 */
#define FIOPAD_REG0_PULL_GET(x)      GET_REG32_BITS((x), 9, 8)
#define FIOPAD_REG0_PULL_SET(x)      SET_REG32_BITS((x), 9, 8)

#define FIOPAD_REG0_DRIVE_MASK       GENMASK(7, 4)    /* 驱动能力配置 */
#define FIOPAD_REG0_DRIVE_GET(x)     GET_REG32_BITS((x), 7, 4)
#define FIOPAD_REG0_DRIVE_SET(x)     SET_REG32_BITS((x), 7, 4)

#define FIOPAD_REG0_FUNC_MASK        GENMASK(2, 0)   /* 引脚复用配置 */
#define FIOPAD_REG0_FUNC_GET(x)      GET_REG32_BITS((x), 2, 0)
#define FIOPAD_REG0_FUNC_SET(x)      SET_REG32_BITS((x), 2, 0)

/** @name X_reg1 Register
 */
#define FIOPAD_REG1_OUT_DELAY_EN                BIT(8)
#define FIOPAD_REG1_OUT_DELAY_DELICATE_MASK     GENMASK(11, 9)
#define FIOPAD_REG1_OUT_DELAY_DELICATE_GET(x)   GET_REG32_BITS((x), 11, 9) /* 延时精调  */
#define FIOPAD_REG1_OUT_DELAY_DELICATE_SET(x)   SET_REG32_BITS((x), 11, 9)
#define FIOPAD_REG1_OUT_DELAY_ROUGH_MASK        GENMASK(14, 12)
#define FIOPAD_REG1_OUT_DELAY_ROUGH_GET(x)      GET_REG32_BITS((x), 14, 12) /* 延时粗调 */
#define FIOPAD_REG1_OUT_DELAY_ROUGH_SET(x)      SET_REG32_BITS((x), 14, 12)

#define FIOPAD_REG1_IN_DELAY_EN                BIT(0)
#define FIOPAD_REG1_IN_DELAY_DELICATE_MASK     GENMASK(3, 1)
#define FIOPAD_REG1_IN_DELAY_DELICATE_GET(x)   GET_REG32_BITS((x), 3, 1) /* 延时精调 */
#define FIOPAD_REG1_IN_DELAY_DELICATE_SET(x)   SET_REG32_BITS((x), 3, 1)
#define FIOPAD_REG1_IN_DELAY_ROUGH_MASK        GENMASK(6, 4)
#define FIOPAD_REG1_IN_DELAY_ROUGH_GET(x)      GET_REG32_BITS((x), 6, 4) /* 延时粗调 */
#define FIOPAD_REG1_IN_DELAY_ROUGH_SET(x)      SET_REG32_BITS((x), 6, 4)

#define FIOPAD_ASSERT_REG0_OFF(pin)      FASSERT_MSG((FIOPAD_REG0_END_OFFSET >= pin), "invalid reg0 offset @0x%x\r\n", (pin))
#define FIOPAD_ASSERT_FUNC(func)         FASSERT_MSG((func < FIOPAD_NUM_OF_FUNC), "invalid func as %d\r\n", (func))
#define FIOPAD_ASSERT_PULL(pull)         FASSERT_MSG((pull < FIOPAD_NUM_OF_PULL), "invalid pull as %d\r\n", (pull))
#define FIOPAD_ASSERT_DRIVE(drive)       FASSERT_MSG((drive < FIOPAD_NUM_OF_DRIVE), "invalid pull as %d\r\n", (drive))

#define FIOPAD_ASSERT_REG1_OFF(pin)      FASSERT_MSG(((FIOPAD_REG1_BEG_OFFSET <= pin) && (FIOPAD_REG1_END_OFFSET >= pin)), "invalid reg1 offset @0x%x\r\n", (pin))
#define FIOPAD_ASSERT_DELAY(delay)       FASSERT_MSG((delay < FIOPAD_NUM_OF_DELAY), "invalid delay as %d\r\n", (delay))

#define FIOPAD_DELAY_MAX                       15

/* 读FPWM寄存器 */
#define FIOPAD_READ_REG32(addr, reg_offset) FtIn32((addr) + (u32)reg_offset)

/* 写FPWM寄存器 */
#define FIOPAD_WRITE_REG32(addr, reg_offset, reg_value) FtOut32((addr) + (u32)reg_offset, (u32)reg_value)

/* print information of all iopad */
void FIOPadDump(uintptr base_addr);

#ifdef __cplusplus
}

#endif
#endif