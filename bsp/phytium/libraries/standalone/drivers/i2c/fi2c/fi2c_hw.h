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
 * FilePath: fi2c_hw.h
 * Date: 2021-11-01 14:53:42
 * LastEditTime: 2022-02-18 08:36:32
 * Description:  This file is for I2C register definition
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  zhugengyu 2021/11/1  first commit
 * 1.1  liushengming 2022/02/18  add fi2c_slave mode
 */


#ifndef FI2C_HW_H
#define FI2C_HW_H

/* - 传入模块基地址，不能复杂结构体
- hardware interface of device || low-level driver function prototypes

- 包括驱动寄存器参数和low-level操作定义
1. 定义寄存器偏移
2. 对上提供该模块寄存器操作的接口
3. 一些简单外设提供直接操作接口
4. 可以定义一些状态的接口，用于响应驱动状态的变化 */

/***************************** Include Files *********************************/

#include "fparameters.h"
#include "fio.h"
#include "ferror_code.h"
#include "fkernel.h"

#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/

/** @name Register Map
 *
 * Register offsets from the base address of an I2C device.
 * @{
 */
#define FI2C_CON_OFFSET 0x00
#define FI2C_TAR_OFFSET 0x04
#define FI2C_SAR_OFFSET 0x08
#define FI2C_HS_MADDR_OFFSET 0x0C
#define FI2C_DATA_CMD_OFFSET 0x10
#define FI2C_SS_SCL_HCNT_OFFSET 0x14
#define FI2C_SS_SCL_LCNT_OFFSET 0x18
#define FI2C_FS_SCL_HCNT_OFFSET 0x1C
#define FI2C_FS_SCL_LCNT_OFFSET 0x20
#define FI2C_HS_SCL_HCNT_OFFSET 0x24
#define FI2C_HS_SCL_LCNT_OFFSET 0x28
#define FI2C_INTR_STAT_OFFSET 0x2C
#define FI2C_INTR_MASK_OFFSET 0x30
#define FI2C_RAW_INTR_STAT_OFFSET 0x34
#define FI2C_RX_TL_OFFSET 0x38
#define FI2C_TX_TL_OFFSET 0x3C
#define FI2C_CLR_INTR_OFFSET 0x40
#define FI2C_CLR_RX_UNDER_OFFSET 0x44
#define FI2C_CLR_RX_OVER_OFFSET 0x48
#define FI2C_CLR_TX_OVER_OFFSET 0x4C
#define FI2C_CLR_RD_REQ_OFFSET 0x50
#define FI2C_CLR_TX_ABRT_OFFSET 0x54
#define FI2C_CLR_RX_DONE_OFFSET 0x58
#define FI2C_CLR_ACTIVITY_OFFSET 0x5c
#define FI2C_CLR_STOP_DET_OFFSET 0x60
#define FI2C_CLR_START_DET_OFFSET 0x64
#define FI2C_CLR_GEN_CALL_OFFSET 0x68
#define FI2C_ENABLE_OFFSET 0x6C
#define FI2C_STATUS_OFFSET 0x70
#define FI2C_TXFLR_OFFSET 0x74
#define FI2C_RXFLR_OFFSET 0x78
#define FI2C_SDA_HOLD_OFFSET 0x7c
#define FI2C_TX_ABRT_SOURCE_OFFSET 0x80
#define FI2C_SLV_DATA_NACK_ONLY_OFFSET 0x84
#define FI2C_DMA_CR_OFFSET 0x88
#define FI2C_DMA_TDLR_OFFSET 0x8c
#define FI2C_DMA_RDLR_OFFSET 0x90
#define FI2C_SDA_SETUP_OFFSET 0x94
#define FI2C_ACK_GENERAL_CALL_OFFSET 0x98
#define FI2C_ENABLE_STATUS_OFFSET 0x9C
#define FI2C_FS_SPKLEN_OFFSET 0xa0
#define FI2C_HS_SPKLEN_OFFSET 0xa4
#define FI2C_COMP_PARAM_1_OFFSET 0xf4
#define FI2C_COMP_VERSION_OFFSET 0xf8
#define FI2C_COMP_TYPE_OFFSET 0xfc

/** @name FI2C_CON_OFFSET Register
 */
#define FI2C_CON_MASTER_MODE (0x1 << 0)
#define FI2C_CON_SLAVE_MODE (0x0 << 0)

#define FI2C_CON_SPEED_MASK GENMASK(2, 1)
#define FI2C_CON_STD_SPEED (0x1 << 1)
#define FI2C_CON_FAST_SPEED (0x2 << 1)
#define FI2C_CON_HIGH_SPEED (0x3 << 1)

/* for slave mode */
#define FI2C_CON_SLAVE_ADR_7BIT (0x0 << 3)
#define FI2C_CON_SLAVE_ADR_10BIT (0x1 << 3)

/* for master mode */
#define FI2C_CON_MASTER_ADR_7BIT (0x0 << 4)
#define FI2C_CON_MASTER_ADR_10BIT (0x1 << 4)

#define FI2C_CON_RESTART_EN (0x1 << 5)
#define FI2C_CON_SLAVE_DISABLE (0x1 << 6)

/** @name FI2C_TAR_OFFSET Register
 */
#define FI2C_IC_TAR_MASK GENMASK(9, 0)
#define FI2C_GC_OR_START (0x1 << 10)
#define FI2C_SPECIAL (0x1 << 11)
#define FI2C_TAR_ADR_7BIT (0x0 << 12)
#define FI2C_TAR_ADR_10BIT (0x1 << 12)

/** @name FI2C_SAR_OFFSET Register
 */
#define FI2C_IC_SAR_MASK GENMASK(9, 0) //Slave addr when in slave mode

/** @name FI2C_HS_MADDR_OFFSET Register
 */
#define FI2C_IC_HS_MAR GENMASK(2, 0) //I2C High Speed模式主机编码

/** @name FI2C_DATA_CMD_OFFSET Register
 */
#define FI2C_DATA_MASK GENMASK(7, 0)
#define FI2C_DATA_CMD_READ (0x1 << 8)
#define FI2C_DATA_CMD_WRITE (0x0 << 8)
#define FI2C_DATA_CMD_STOP (0x1 << 9)
#define FI2C_DATA_CMD_RESTART (0x1 << 10)

/** @name FI2C_INTR_STAT_OFFSET Register
 *  @name FI2C_INTR_MASK_OFFSET Register
 *  @name FI2C_RAW_INTR_STAT_OFFSET Register
 */
#define FI2C_INTR_RX_UNDER (0x1 << 0)   /* 接收缓冲区为空 */
#define FI2C_INTR_RX_OVER (0x1 << 1)    /* 接收缓冲区大小达到 IC_RX_BUFFER_DEPTH ，且还继续从外部接收数据 */
#define FI2C_INTR_RX_FULL (0x1 << 2)    /* 接收缓冲区大于等于 IC_RX_TL 中设定的门限值（RX_TL) */
#define FI2C_INTR_TX_OVER (0x1 << 3)    /* 发送缓冲区大小达到 IC_TX_BUFFER_DEPTH，并且还在尝试写数据 */
#define FI2C_INTR_TX_EMPTY (0x1 << 4)   /* 发送缓冲区小于等于 IC_TX_TL 寄存器中设定的门限值 */
#define FI2C_INTR_RD_REQ (0x1 << 5)     /* 读请求标志 */
#define FI2C_INTR_TX_ABRT (0x1 << 6)    /* I2C 不能完成FIFO内容的传输 */
#define FI2C_INTR_RX_DONE (0x1 << 7)    /* Slave工作模式下，规定时间内没有Master的回应，通信结束 */
#define FI2C_INTR_ACTIVITY (0x1 << 8)   /* I2C 控制器的活动状态 */
#define FI2C_INTR_STOP_DET (0x1 << 9)   /* I2C 总线接口上是否产生了 STOP */
#define FI2C_INTR_START_DET (0x1 << 10) /* I2C 总线接口上是否产生了 START 或 RESTART */
#define FI2C_INTR_GEN_CALL (0x1 << 11)  /* I2C 总线接口上接收并识别到General Call格式 */

#define FI2C_INTR_ALL_MASK 0x8FF

#define FI2C_INTR_MASTER_WR_MASK (FI2C_INTR_TX_EMPTY | FI2C_INTR_TX_ABRT)
#define FI2C_INTR_MASTER_RD_MASK (FI2C_INTR_MASTER_WR_MASK | FI2C_INTR_RX_FULL)

#define FI2C_INTR_SLAVE_DEF_MASK (FI2C_INTR_RX_FULL | FI2C_INTR_STOP_DET | \
                                  FI2C_INTR_RD_REQ | FI2C_INTR_RX_DONE |   \
                                  FI2C_INTR_RX_UNDER | FI2C_INTR_TX_ABRT |\
                                  FI2C_INTR_START_DET)

/** @name FI2C_RX_TL_OFFSET Register
 */
#define FI2C_RX_TL_MASK GENMASK(7, 0)

/** @name FI2C_TX_TL_OFFSET Register
 */
#define FI2C_TX_TL_MASK GENMASK(7, 0)

/** @name FI2C_IC_ENABLE_OFFSET Register
 */
#define FI2C_ENABLE_CONTROLLER (0x1 << 0)
#define FI2C_DISABLE_CONTROLLER (0x0 << 0)

/** @name FI2C_STATUS_OFFSET Register
 */
#define FI2C_STATUS_ACTIVITY (0x1 << 0)
#define FI2C_STATUS_TFNF (0x1 << 1)
#define FI2C_STATUS_TFE (0x1 << 2)
#define FI2C_STATUS_RFNE (0x1 << 3)
#define FI2C_STATUS_RFF (0x1 << 4)
#define FI2C_STATUS_MST_ACTIVITY (0x1 << 5)
#define FI2C_STATUS_SLV_ACTIVITY (0x1 << 6)

/** @name FI2C_ENABLE_OFFSET Register
 */
#define FI2C_IC_ENABLE (0x1 << 0)
#define FI2C_IC_DISABLE (0x0 << 0)
#define FI2C_IC_ENABLE_MASK (0x1 << 0)

#define FI2C_SLV_DISABLED_WHILE_BUSY (0x1 << 1)
#define FI2C_SLV_RX_DATA_LOST (0x1 << 2)

/* High and low times in different speed modes (in ns) */
#define FI2C_MIN_SS_SCL_HIGHTIME 4000
#define FI2C_MIN_SS_SCL_LOWTIME 4700
#define FI2C_MIN_FS_SCL_HIGHTIME 600
#define FI2C_MIN_FS_SCL_LOWTIME 1300
#define FI2C_MIN_FP_SCL_HIGHTIME 500
#define FI2C_MIN_FP_SCL_LOWTIME 500
#define FI2C_MIN_HS_SCL_HIGHTIME 60
#define FI2C_MIN_HS_SCL_LOWTIME 160
#define FI2C_DEFAULT_SDA_HOLD_TIME 300

#define FI2C_READ_REG32(addr, reg_offset) FtIn32((addr) + (u32)(reg_offset))
#define FI2C_WRITE_REG32(addr, reg_offset, reg_value) FtOut32((addr) + (u32)(reg_offset), (u32)(reg_value))

#define FI2C_IIC_FIFO_MAX_LV 8

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/
enum
{
    FI2C_STANDARD_SPEED = 0,
    FI2C_FAST_SPEED,

    FI2C_SPEED_MODE_MAX
};
/***************** Macros (Inline Functions) Definitions *********************/
#define FI2C_GET_INTRRUPT_MASK(addr) FI2C_READ_REG32((addr), FI2C_INTR_MASK_OFFSET)

#define FI2C_SET_INTRRUPT_MASK(addr, mask) FI2C_WRITE_REG32((addr), FI2C_INTR_MASK_OFFSET, (mask))

#define FI2C_CLEAR_INTR_STATUS(addr) FI2C_READ_REG32((addr), FI2C_CLR_INTR_OFFSET)

#define FI2C_GET_STATUS(addr) FI2C_READ_REG32((addr), FI2C_STATUS_OFFSET)

#define FI2C_READ_DATA(addr) (u8)(FI2C_DATA_MASK & FI2C_READ_REG32(addr, FI2C_DATA_CMD_OFFSET))

#define FI2C_WRITE_DATA(addr, dat) FI2C_WRITE_REG32((addr), FI2C_DATA_CMD_OFFSET, (dat))

#define FI2C_SET_RX_TL(addr, level) FI2C_WRITE_REG32((addr), FI2C_RX_TL_OFFSET, (level))

#define FI2C_SET_TX_TL(addr, level) FI2C_WRITE_REG32((addr), FI2C_TX_TL_OFFSET, (level))

#define FI2C_READ_INTR_STAT(addr) FI2C_READ_REG32((addr), FI2C_INTR_STAT_OFFSET)

#define FI2C_READ_RAW_INTR_STAT(addr) FI2C_READ_REG32((addr), FI2C_RAW_INTR_STAT_OFFSET)

inline static u32 FI2cGetEnable(uintptr addr)
{
    return FI2C_READ_REG32(addr, FI2C_ENABLE_STATUS_OFFSET);
}

/************************** Function Prototypes ******************************/
FError FI2cSetEnable(uintptr addr, boolean enable);
FError FI2cSetSpeed(uintptr addr, u32 speed_rate);
FError FI2cWaitStatus(uintptr addr, u32 stat_bit);
FError FI2cWaitBusBusy(uintptr addr);
FError FI2cSetTar(uintptr addr, u32 tar_addr);
FError FI2cSetSar(uintptr addr, u32 sar_addr);
FError FI2cFlushRxFifo(uintptr addr);
u32 FI2cClearIntrBits(uintptr addr, u32 *last_err_p);

#ifdef __cplusplus
}
#endif

#endif