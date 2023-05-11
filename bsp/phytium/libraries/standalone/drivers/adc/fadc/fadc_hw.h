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
 * FilePath: fadc_hw.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:28:45
 * Description: This file is for adc register definition.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/4/15   init commit
 */

#ifndef FADC_HW_H
#define FADC_HW_H

#include "fkernel.h"
#include "ftypes.h"
#include "fio.h"
#include "fdebug.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* Generic ADC register definitions */

/* FADC register */
#define FADC_CTRL_REG_OFFSET                0x00
#define FADC_INTER_REG_OFFSET               0x04
#define FADC_STATE_REG_OFFSET               0x08
#define FADC_ERRCLR_REG_OFFSET              0x0c
#define FADC_LEVEL_REG_OFFSET(x)            (0x10+(x)*4)
#define FADC_INTRMASK_REG_OFFSET            0x30
#define FADC_INTR_REG_OFFSET                0x34
#define FADC_COV_RESULT_REG_OFFSET(x)       (0x38+(x)*4)
#define FADC_FINISH_CNT_REG_OFFSET(x)       (0x58+(x)*4)
#define FADC_HIS_LIMIT_REG_OFFSET(x)        (0x78+(x)*4)

#define FADC_CTRL_REG_PD_EN                 BIT(31)
#define FADC_CTRL_REG_FIX_CHANNEL_NUM_MASK  GENMASK(18, 16)
#define FADC_CTRL_REG_FIX_CHANNEL_NUM(x)    ((x)<<16)
#define FADC_CTRL_REG_CLK_DIV(x)            ((x)<<12)
#define FADC_CTRL_REG_CLK_DIV_MASK          GENMASK(15, 12)
#define FADC_CTRL_REG_CHANNEL_EN(x)         BIT((x)+4)
#define FADC_CTRL_REG_FIX_CHANNEL           BIT(3)
#define FADC_CTRL_REG_SINGLE_CONVERT_EN     BIT(2)
#define FADC_CTRL_REG_SINGLE_CONVERT        BIT(1)
#define FADC_CTRL_REG_SOC_EN                BIT(0)

#define FADC_STATE_REG_B_STA(x)             ((x)<<8)
#define FADC_STATE_REG_EOC_STA              BIT(7)
#define FADC_STATE_REG_S_STA(x)             ((x)<<4)
#define FADC_STATE_REG_SOC_STA              BIT(3)
#define FADC_STATE_REG_ERR_STA              BIT(2)
#define FADC_STATE_REG_COV_FINISH_STA       BIT(1)
#define FADC_STATE_REG_CTL_BUSY_STA         BIT(0)

#define FADC_LEVEL_REG_HIGH_LEVEL(x)        ((x)<<16)
#define FADC_LEVEL_REG_LOW_LEVEL(x)         ((x)<<0)

#define FADC_INTRMASK_REG_ERR_MASK          BIT(24)
#define FADC_INTRMASK_REG_ULIMIT_MASK(x)    BIT((x)*2+9)
#define FADC_INTRMASK_REG_DLIMIT_MASK(x)    BIT((x)*2+8)
#define FADC_INTRMASK_REG_COVFIN_MASK(x)    BIT((x))

#define FADC_INTR_REG_ERR               BIT(24)
#define FADC_INTR_REG_ULIMIT(x)         BIT((x)*2+9)
#define FADC_INTR_REG_DLIMIT(x)         BIT((x)*2+8)
#define FADC_INTR_REG_COVFIN(x)         BIT((x))
#define FADC_INTR_REG_COVFIN_MASK       GENMASK(7, 0)
#define FADC_INTR_REG_LIMIT_MASK        GENMASK(23, 8)

/* convert result range */
#define FADC_COV_RESULT_REG_MASK        GENMASK(9, 0)

#define FADC_HIS_LIMIT_REG_UMASK        GENMASK(25, 16)
#define FADC_HIS_LIMIT_REG_DMASK        GENMASK(9, 0)

/***************** Macros (Inline Functions) Definitions *********************/

/**
 * @name: FADC_READ_REG32
 * @msg:  读取FADC寄存器
 * @param {u32} addr 定时器的基地址
 * @param {u32} reg_offset   定时器的寄存器的偏移
 * @return {u32} 寄存器参数
 */
#define FADC_READ_REG32(addr, reg_offset) FtIn32(addr + (u32)(reg_offset))

/**
 * @name: FADC_WRITE_REG32
 * @msg:  写入FADC寄存器
 * @param {u32} addr 定时器的基地址
 * @param {u32} reg_offset   定时器的寄存器的偏移
 * @param {u32} reg_value    写入寄存器参数
 * @return {void}
 */
#define FADC_WRITE_REG32(addr, reg_offset, reg_value) FtOut32((addr) + (u32)(reg_offset), (u32)(reg_value))

#define FADC_SETBIT(base_addr, reg_offset, data) FtSetBit32((base_addr) + (u32)(reg_offset), (u32)(data))

#define FADC_CLEARBIT(base_addr, reg_offset, data) FtClearBit32((base_addr) + (u32)(reg_offset), (u32)(data))

/* debug register value for adc channel */
void FAdcDump(uintptr base_addr, u8 channel);

#ifdef __cplusplus
}
#endif

#endif