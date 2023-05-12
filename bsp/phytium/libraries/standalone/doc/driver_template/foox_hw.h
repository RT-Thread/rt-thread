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
 * FilePath: foox_hw.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:24:52
 * Description:  This file is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */


#ifndef  DRIVERS_XXXX_FOOXX_HW_H
#define  DRIVERS_XXXX_FOOXX_HW_H


/* - 传入模块基地址，不能复杂结构体
- hardware interface of device || low-level driver function prototypes

- 包括驱动寄存器参数和low-level操作定义
1. 定义寄存器偏移
2. 对上提供该模块寄存器操作的接口
3. 一些简单外设提供直接操作接口
4. 可以定义一些状态的接口，用于响应驱动状态的变化

note: 本文件不能引用fooxx.h
*/

#ifdef __cplusplus
extern "C"
{
#endif
/***************************** Include Files *********************************/

#include "fparameters.h"
#include "fio.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/** @name Register Map
 *
 * Register offsets from the base address of an SD device.
 * @{
 */

#define FOOXX_XX_OFFSET

/** @name FOOXX_XX_OFFSET Register
 */

#define FOOXX_XX_STATE


#define FOOXX_READ_REG32(addr, reg_offset) FtIn32((addr) + (u32)(reg_offset))
#define FOOXX_WRITE_REG32(addr, reg_offset, reg_value) FtOut32((addr) + (u32)(reg_offset), (u32)(reg_value))


/************************** Function Prototypes ******************************/
void FooxHwWrite(uintptr base, char byte);

char FooxHwRead(uintptr base);

#ifdef __cplusplus
}
#endif

