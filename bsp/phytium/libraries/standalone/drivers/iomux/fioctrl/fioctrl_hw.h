/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
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
 * Date: 2021-04-29 10:21:53
 * LastEditTime: 2022-02-18 08:29:20
 * Description:  This files is for the ioctrl register related functions
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2023/7/30    first release
 */

#ifndef FIOPAD_HW_H
#define FIOPAD_HW_H

#include "fparameters.h"
#include "fkernel.h"

#ifdef __cplusplus
extern "C"
{
#endif

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


#ifdef __cplusplus
}

#endif
#endif