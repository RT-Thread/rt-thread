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
 * FilePath: fmio_hw.h
 * Date: 2022-06-20 21:05:34
 * LastEditTime: 2022-06-20 21:05:34
 * Description:  This file is for mio hardware define
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  liushengming  2022/06/20  init
 */
#ifndef FMIO_HW_H
#define FMIO_HW_H

#include "fparameters.h"
#include "fio.h"
#include "fkernel.h"
#include "fdrivers_port.h"
#include "ferror_code.h"

#ifdef __cplusplus
extern "C"
{
#endif


/************************** Constant Definitions *****************************/

/** @name Register Map
 *
 * Register offsets from the base address of MIO device.
 *
 */
#define FMIO_BASE_SET_ADDR(x) FMIO_BASE_ADDR(x)+0x1000

#define FMIO_FUNC_OFFSET 0x00
#define FMIO_SEL_STATE_OFFSET  0x04
#define FMIO_VER_OFFSET  0x100

/* creg_mio_func_sel */
#define FMIO_FUNC_SEL_MASK  GENMASK(1,0)
#define FMIO_FUNC_SET(n)    (FMIO_FUNC_SEL_MASK & (n))
enum
{
    FMIO_FUNC_SET_I2C = 0b00,
    FMIO_FUNC_SET_UART = 0b01,
#if defined(TARDIGRADE)
    FMIO_FUNC_SET_PWM = 0b10,
#endif
    FMIO_NUM_OF_MIO_FUNC
};

#define FMIO_FUNC_STATE_MASK GENMASK(1, 0)
#define FMIO_VERSION_MASK    GENMASK(31, 0)

/***************** Macros (Inline Functions) Definitions *********************/
/**
 * @name: FMIO_READ_REG32
 * @msg:  读取MIO寄存器
 * @param {u32} addr MIO的基地址
 * @param {u32} reg_offset   MIO的寄存器的偏移
 * @return {u32} 寄存器参数
 */
#define FMIO_READ_REG32(addr, reg_offset) FtIn32(addr + (u32)reg_offset)

/**
 * @name: FMIO_WRITE_REG32
 * @msg:  写入MIO寄存器
 * @param {u32} addr MIO的基地址
 * @param {u32} reg_offset   MIO的寄存器的偏移
 * @param {u32} reg_value    写入寄存器参数
 * @return {void}
 */
#define FMIO_WRITE_REG32(addr, reg_offset, reg_value) FtOut32(addr + (u32)reg_offset, (u32)reg_value)

/**
 * @name: FMioWriteFunc
 * @msg: 设置MIO的功能
 * @return {*}
 * @param {uintptr} addr
 * @param {u32} val
 */
static inline void FMioWriteFunc(uintptr addr, u32 val)
{
    FMIO_WRITE_REG32(addr, FMIO_FUNC_OFFSET, val);
}

/**
 * @name: FMioReadStatus
 * @msg: 获取MIO的设置
 * @return {u32} register value
 * @param {uintptr} addr
 */
static inline u32 FMioReadStatus(uintptr addr)
{
    return FMIO_READ_REG32(addr, FMIO_SEL_STATE_OFFSET) & FMIO_FUNC_STATE_MASK;
}

/**
 * @name: FMioReadVersion
 * @msg: 获取MIO的版本信息
 * @return {u32} register value
 * @param {uintptr} addr
 */
static inline u32 FMioReadVersion(uintptr addr)
{
    return FMIO_READ_REG32(addr, FMIO_VER_OFFSET) & FMIO_VERSION_MASK;
}

/************************** Function Prototypes ******************************/
/*设置Mio功能*/
FError FMioSelectFunc(uintptr addr, u32 mio_type);

/*获取Mio状态*/
u32 FMioGetFunc(uintptr addr);

/*获取版本信息，默认32'h1*/
u32 FMioGetVersion(uintptr addr);

#ifdef __cplusplus
}
#endif

#endif