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
 * FilePath: fspim_hw.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 09:08:05
 * Description:  This file is for providing spim Hardware interaction api 
 *               and some predefined variables.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2021/12/3   init commit
 * 1.1   zhugengyu  2022/4/15   support test mode
 * 1.2   zhugengyu  2022/5/13   support spi dma
 * 1.3  liqiaozhong 2023/1/4    add data get func
 */


#ifndef  DRIVERS_FSPIM_M_HW_H
#define  DRIVERS_FSPIM_M_HW_H

#ifdef __cplusplus
extern "C"
{
#endif
/***************************** Include Files *********************************/

#include "fparameters.h"
#include "fkernel.h"
#include "fio.h"
#include "ftypes.h"
#include "fspim.h"

/************************** Constant Definitions *****************************/
/** @name Register Map
 *
 * Register offsets from the base address of an SD device.
 * @{
 */
/* offset map of SPI register */
#define FSPIM_CTRL_R0_OFFSET 0x00       /* Ctrl register 0 */
#define FSPIM_CTRL_R1_OFFSET 0x04       /* Ctrl register 1 */
#define FSPIM_SSIENR_OFFSET 0x08        /* SPI enable register */
#define FSPIM_MWCR_OFFSET 0x0c          /* Microwire ctrl register */
#define FSPIM_SER_OFFSET 0x10           /* Slave enable register */
#define FSPIM_BAUD_R_OFFSET 0x14        /* Baudrate set register */
#define FSPIM_TXFTL_R_OFFSET 0x18       /* Tx threshold register */
#define FSPIM_RXFTL_R_OFFSET 0x1c       /* Rx threshold register */
#define FSPIM_TXFLR_OFFSET 0x20         /* Tx level register */
#define FSPIM_RXFLR_OFFSET 0x24         /* Rx level register */
#define FSPIM_SR_OFFSET 0x28            /* Status register */
#define FSPIM_IMR_OFFSET 0x2c           /* Intr mask register */
#define FSPIM_ISR_OFFSET 0x30           /* Irq Status register */
#define FSPIM_RIS_R_OFFSET 0x34         /* Intr status register */
#define FSPIM_TXOI_CR_OFFSET 0x38       /* TX FIFO overflow intr clear register */
#define FSPIM_RXOI_CR_OFFSET 0x3c       /* RX FIFO overflow intr clear register */
#define FSPIM_RXUI_CR_OFFSET 0x40       /* TX FIFO underflow intr clear register */
#define FSPIM_MSTI_CR_OFFSET 0x44       /* Multi slave intr clear register */
#define FSPIM_ICR_OFFSET 0x48           /* Intr clear register */
#define FSPIM_DMA_CR_OFFSET 0x4c        /* DMA ctrl register */
#define FSPIM_DMA_TDLR_OFFSET 0x50      /* DMA TX Data level register */
#define FSPIM_DMA_RDLR_OFFSET 0x54      /* DMA RX Data level register */
#define FSPIM_IDR_OFFSET 0x58           /* Identification register */
#define FSPIM_DR_OFFSET 0x60            /* Data register */
#define FSPIM_RX_SAMPLE_DLY_OFFSET 0xfc /* RX Data delay register */
#define FSPIM_CS_OFFSET 0x100           /* Chip selection register */

/** @name FSPIM_CTRL_R0_OFFSET Register
 */

#define FSPIM_CTRL_R0_DFS_MASK       GENMASK(3, 0)
#define FSPIM_CTRL_R0_DFS(x)         (FSPIM_CTRL_R0_DFS_MASK & ((x) << 0)) /* 选择数据长度 */
#define FSPIM_CTRL_R0_FRF(x)         (GENMASK(5, 4) & ((x) << 4)) /* 选择传输模式 */
#define FSPIM_CTRL_R0_SCPHA(x)        ((x) << 6) /* 串行时钟相位 */
#define FSPIM_CTRL_R0_SCPHA_MASK      BIT(6)
enum
{
    FSPIM_SCPHA_SWITCH_DATA_MID = 0x0,
    FSPIM_SCPHA_SWITCH_DATA_BEG = 0x1
};
#define FSPIM_CTRL_R0_SCPOL(x)       ((x) << 7) /* 串行时钟极性 */
#define FSPIM_CTRL_R0_SCPOL_MASK     BIT(7)
enum
{
    FSPIM_SCPOL_INACTIVE_LOW = 0,
    FSPIM_SCPOL_INACTIVE_HIGH = 1
};
#define FSPIM_CTRL_R0_TMOD_MASK      GENMASK(9, 8)
#define FSPIM_CTRL_R0_TMOD(x)        (FSPIM_CTRL_R0_TMOD_MASK & ((x) << 8)) /* 传输模式控制位 */
#define FSPIM_CTRL_R0_TMOD_SHIFT     8
enum
{
    FSPIM_TMOD_RX_TX  = 0b00,
    FSPIM_TMOD_TX_ONLY = 0b01,
    FSPIM_TMOD_RX_ONLY = 0b10,
    FSPIM_TMOD_RD_EEPROM = 0b11
};
#define FSPIM_CTRL_R0_SLV_OE(x)      ((x) << 10) /* 从机发送逻辑使能位 */
#define FSPIM_CTRL_R0_SLV_OE_MASK    BIT(10)
enum
{
    FSPIM_SLAVE_TX_ENABLE = 0,
    FSPIM_SLAVE_TX_DISALE = 1
};
#define FSPIM_CTRL_R0_SLV_SRL(x)     ((x) << 11) /* 移位寄存器回环 */
enum
{
    FSPIM_SRL_NORAML = 0,
    FSPIM_SRL_TEST = 1
};
#define FSPIM_CTRL_R0_CFS(x)         (GENMASK(5, 12) & ((x) << 12)) /* 数据大小控制位，用于 Microwire 模式 */

/** @name FSPIM_CTRL_R1_OFFSET Register
 */
/* FSPIM_TMOD_RX_ONLY 或 FSPIM_TMOD_RD_EEPROM 该字段设置为 SPI 连续接收的数据量 */
#define FSPIM_CTRL_R1_NDF(x)         (GENMASK(15, 0) & ((x) << 0))
#define FSPIM_CTRL_R1_NDF_64KB       0b11

/** @name FSPIM_SSIENR_OFFSET Register
 */
#define FSPIM_SSIENR_SSI_EN(x)       ((x) << 0) /* SPI 使能启用和禁用所有 SPI 操作 */

/** @name FSPIM_MWCR_OFFSET Register
 */
#define FSPIM_MWCR_MW_MOD(x)         ((x) << 0) /* Microwire 传输模式 */
enum
{
    FSPIM_MWMODE_NO_CONT_TRANS  = 0, /* 非连续传输 */
    FSPIM_MWMODE_CONT_TRANS     = 1  /* 连续传输 */
};

#define FSPIM_MWCR_MDD(x)            ((x) << 1) /* Microwire 控制位 */
enum
{
    FSPIM_MWCR_RX_EXT = 0,  /* 从外部串行设备接收数据 */
    FSPIM_MWCR_TX_EXT       /* 数据发送到外部串行设备 */
};

#define FSPIM_MWCR_MHS(x)            ((x) << 2) /* Microwire 握手 */
enum
{
    FSPU_MWCR_DISABLE_HANDSHAKING = 0,
    FSPU_MWCR_ENABLE_HANDSHAKING = 1
};

/** @name FSPIM_SER_OFFSET Register
 */
#define FSPIM_SER(x)                 (GENMASK(3, 0) & ((x) << 0)) /* 从机选择信号启动标志 */
/* 寄存器中的每一个位都对应来自 SPI 主机的从选信号(ss_x_n]).当此寄
    存器中的某个位被置为 1 时,串行口传输开始时 */
enum
{
    FSPIM_SER_UNSELECT = 0x0,
    FSPIM_SER_SELECT = 0x1
};

/** @name FSPIM_BAUD_R_OFFSET Register
 */
#define FSPIM_BAUD_R_SCKDV(x)        (GENMASK(15, 0) & ((x) << 0)) /* SCKDV 为 2 ~ 65534 之间的任何偶数值 */
#define FSPIM_BAUD_R_SCKDV_MIN       2U
#define FSPIM_BAUD_R_SCKDV_MAX       65534U
#define FSPIM_BAUD_R_SCKDV_IS_VALID(x)  (0 == (x) % 2)

/** @name FSPIM_TXFTL_R_OFFSET Register
 */
#define FSPIM_TXFTL_R_TFT(x)         (GENMASK(2, 0) & ((x) << 0)) /* 发送 FIFO 阙值 */

/** @name FSPIM_RXFTL_R_OFFSET Register
 */
#define FSPIM_RXFTL_R_RFT(x)         (GENMASK(3, 0) & ((x) << 0)) /* 接收 FIFO 阙值 */

/** @name FSPIM_TXFLR_OFFSET Register
 */
#define FSPIM_TXFLR_TXTFL(x)         (GENMASK(3, 0) & ((x) << 0)) /* 发送 FIFO 等级 */

/** @name FSPIM_RXFLR_OFFSET Register
 */
#define FSPIM_RXFLR_RXTFL(x)         (GENMASK(3, 0) & ((x) << 0)) /* 接收 FIFO 等级 */

/** @name FSPIM_SR_OFFSET Register, RO
 */
#define FSPIM_SR_BUSY                BIT(0)  /* SPI 总线繁忙标志位 */
#define FSPIM_SR_TFNF                BIT(1)  /* 发送 FIFO 不满 */
#define FSPIM_SR_TFE                 BIT(2)  /* 发送 FIFO 为空 */
#define FSPIM_SR_RFNE                BIT(3)  /* 接收 FIFO 不为空 */
#define FSPIM_SR_RFF                 BIT(4)  /* 接收 FIFO 满 */
#define FSPIM_SR_TXE                 BIT(5)  /* 传输错误 */
#define FSPIM_SR_DCOL                BIT(6)  /* 传输数据冲突错误 */
#define FSPIM_SR_ALL_BITS            GENMASK(0, 6)

/** @name FSPIM_IMR_OFFSET Register
 */
#define FSPIM_IMR_TXEIS              BIT(0) /* 发送 FIFO 空中断 */
#define FSPIM_IMR_TXOIS              BIT(1) /* 发送 FIFO 上溢中断 */
#define FSPIM_IMR_RXUIS              BIT(2) /* 接收 FIFO 下溢中断 */
#define FSPIM_IMR_RXOIS              BIT(3) /* 接收 FIFO 上溢中断 */
#define FSPIM_IMR_RXFIS              BIT(4) /* 接收 FIFO 满中断 */
#define FSPIM_IMR_ALL_BITS           GENMASK(4, 0)

/** @name FSPIM_ISR_OFFSET Register
 */
#define FSPIM_ISR_TXEIS              BIT(0) /* 发送 FIFO 空中断状态 */
#define FSPIM_ISR_TXOIS              BIT(1) /* 发送 FIFO 上溢中断状态 */
#define FSPIM_ISR_RXUIS              BIT(2) /* 接收 FIFO 下溢中断状态 */
#define FSPIM_ISR_RXOIS              BIT(3) /* 接收 FIFO 上溢中断状态 */
#define FSPIM_ISR_RXFIS              BIT(4) /* 接收 FIFO 满中断状态 */
#define FSPIM_ISR_MSTIS              BIT(5) /* 多主机竞争中断状态 */

/** @name FSPIM_RIS_R_OFFSET Register
 */
#define FSPIM_RIS_R_TXEIR              BIT(0) /* 传输 FIFO 空生成中断状态 */
#define FSPIM_RIS_R_TXOIR              BIT(1) /* 传输 FIFO 上溢生成中断状态 */
#define FSPIM_RIS_R_RXUIR              BIT(2) /* 接收 FIFO 下溢生成中断状态 */
#define FSPIM_RIS_R_RXOIR              BIT(3) /* 接收 FIFO 上溢生成中断状态 */
#define FSPIM_RIS_R_RXFIR              BIT(4) /* 接收 FIFO 满生成中断状态 */
#define FSPIM_RIS_R_MSTIR              BIT(5) /* 多主机冲突生成中断状态 */
#define FSPIM_RIS_R_ALL_BITS           GENMASK(5, 0)

/** @name FSPIM_TXOI_CR_OFFSET Register
 */
#define FSPIM_TXOICR                   BIT(0) /* 清除传输 FIFO 溢出中断 */

/** @name FSPIM_RXOI_CR_OFFSET Register
 */
#define FSPIM_RXOICR                   BIT(0) /* 清除传输 FIFO 溢出中断 */

/** @name FSPIM_RXUI_CR_OFFSET Register
 */
#define FSPIM_RXUICR                   BIT(0) /* 清除传输 FIFO 下溢中断 */

/** @name FSPIM_MSTI_CR_OFFSET Register
 */
#define FSPIM_MSTICR                   BIT(0) /* 清除多主争用中断 */

/** @name FSPIM_ICR_OFFSET Register
 */
#define FSPIM_ICR                      BIT(0) /* 清除中断 */

/** @name FSPIM_DMA_CR_OFFSET Register
 */
#define FSPIM_DMA_CR_RDMAE             BIT(0) /* DMA 接收使能 */
#define FSPIM_DMA_CR_TDMAE             BIT(1) /* DMA 发送使能 */

/** @name FSPIM_DMA_TDLR_OFFSET Register
 */
#define FSPIM_DMATDL(x)                (GENMASK(2, 0) & ((x) << 0))     /* 发送数据等级 */

/** @name FSPIM_DMA_RDLR_OFFSET Register
 */
#define FSPIM_DMARDL(x)                (GENMASK(2, 0) & ((x) << 0))     /* 接收数据等级 */

/** @name FSPIM_IDR_OFFSET Register
 */
#define FSPIM_IDCODE(x)                (GENMASK(31, 0) & ((x) << 0))    /* 识别码。即外部设备标识代码 */

/** @name FSPIM_DR_OFFSET Register
 */
#define FSPIM_DR(x)                    (GENMASK(15, 0) & ((x) << 0))    /* 数据寄存器 */

/** @name FSPIM_RX_SAMPLE_DLY_OFFSET Register
 */
#define FSPIM_RSD(x)                   (GENMASK(7, 0) & ((x) << 0))     /* 接收数据延时 */

/** @name FSPIM_CS_OFFSET Register
 */
#define FSPIM_NUM_OF_CS                     4U
#define FSPIM_CHIP_SEL_EN(cs)               BIT((cs) + FSPIM_NUM_OF_CS) /* 1: enable chip selection */
#define FSPIM_CHIP_SEL(cs)                  BIT(cs)

#define FSPIM_DEFAULT_DFS              0x7
#define FSPIM_DEFAULT_FRF              0x0
#define FSPIM_DEFAULT_RSD              0x6
#define FSPIM_DEFAULT_CFS              0x0

#define FSPIM_MIN_FIFO_DEPTH           0
#define FSPIM_MAX_FIFO_DEPTH           256
#define FSPIM_TIMEOUT                  256

#define FSPIM_TX_DMA_LEVEL             0x10
#define FSPIM_RX_DMA_LEVEL             0xf
/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FSPIM_READ_REG32(addr, reg_offset) FtIn32((addr) + (u32)(reg_offset))
#define FSPIM_WRITE_REG32(addr, reg_offset, reg_value) FtOut32((addr) + (u32)(reg_offset), (u32)(reg_value))

/**
 * @name: FSpimSetCtrlR0
 * @msg: 设置CTRL_R0寄存器
 * @return {*}
 * @param {uintptr} base_addr
 * @param {u32} val
 */
static inline void FSpimSetCtrlR0(uintptr base_addr, u32 val)
{
    FSPIM_WRITE_REG32(base_addr, FSPIM_CTRL_R0_OFFSET, val);
}

/**
 * @name: FSpimGetCtrlR0
 * @msg: 获取CTRL_R0寄存器的值
 * @return {*}
 * @param {uintptr} base_addr
 */
static inline u32 FSpimGetCtrlR0(uintptr base_addr)
{
    return FSPIM_READ_REG32(base_addr, FSPIM_CTRL_R0_OFFSET);
}

/**
 * @name: FSpimSetCtrlR0
 * @msg: 设置CTRL_R1寄存器
 * @return {*}
 * @param {uintptr} base_addr
 * @param {u32} val
 */
static inline void FSpimSetCtrlR1(uintptr base_addr, u32 val)
{
    FSPIM_WRITE_REG32(base_addr, FSPIM_CTRL_R1_OFFSET, val);
}

/**
 * @name: FSpimSetTxFifoThreshold
 * @msg: 设置TX Fifo阈值
 * @return {*}
 * @param {uintptr} base_addr
 * @param {u32} val
 */
static inline void FSpimSetTxFifoThreshold(uintptr base_addr, u32 val)
{
    FSPIM_WRITE_REG32(base_addr, FSPIM_TXFTL_R_OFFSET, val);
}

/**
 * @name: FSpimGetTxFifoThreshold
 * @msg: 获取TX Fifo阈值
 * @return {*}
 * @param {uintptr} base_addr
 */
static inline u32 FSpimGetTxFifoThreshold(uintptr base_addr)
{
    return FSPIM_READ_REG32(base_addr, FSPIM_TXFTL_R_OFFSET);
}

/**
 * @name: FSpimSetRxFifoThreshold
 * @msg: 设置RX Fifo阈值
 * @return {*}
 * @param {uintptr} base_addr
 * @param {u32} val
 */
static inline void FSpimSetRxFifoThreshold(uintptr base_addr, u32 val)
{
    FSPIM_WRITE_REG32(base_addr, FSPIM_RXFTL_R_OFFSET, val);
}

/**
 * @name: FSpimGetRxFifoThreshold
 * @msg: 获取RX Fifo阈值
 * @return {*}
 * @param {uintptr} base_addr
 */
static inline u32 FSpimGetRxFifoThreshold(uintptr base_addr)
{
    return FSPIM_READ_REG32(base_addr, FSPIM_RXFTL_R_OFFSET);
}

/**
 * @name: FSpimGetTxFifoLevel
 * @msg: 获取当前TX Fifo等级
 * @return {*}
 * @param {uintptr} base_addr
 */
static inline u32 FSpimGetTxFifoLevel(uintptr base_addr)
{
    return FSPIM_READ_REG32(base_addr, FSPIM_TXFLR_OFFSET);
}

/**
 * @name: FSpimGetRxFifoLevel
 * @msg: 获取当前RX Fifo等级
 * @return {*}
 * @param {uintptr} base_addr
 */
static inline u32 FSpimGetRxFifoLevel(uintptr base_addr)
{
    return FSPIM_READ_REG32(base_addr, FSPIM_RXFLR_OFFSET);
}

/**
 * @name: FSpimGetTxDMALevel
 * @msg: 获取当前的TX DMA等级
 * @return {*}
 * @param {uintptr} base_addr
 */
static inline u32 FSpimGetTxDMALevel(uintptr base_addr)
{
    return FSPIM_READ_REG32(base_addr, FSPIM_DMA_TDLR_OFFSET);
}

/**
 * @name: FSpimGetRxDMALevel
 * @msg: 获取当前的RX DMA等级
 * @return {*}
 * @param {uintptr} base_addr
 */
static inline u32 FSpimGetRxDMALevel(uintptr base_addr)
{
    return FSPIM_READ_REG32(base_addr, FSPIM_DMA_RDLR_OFFSET);
}

/**
 * @name: FSpimSetTxDMALevel
 * @msg: 设置TX DMA等级
 * @return {*}
 * @param {uintptr} base_addr
 * @param {u32} level, TX DMA等级, 应该与FIFO阈值保持一致
 */
static inline void FSpimSetTxDMALevel(uintptr base_addr, u32 level)
{
    FSPIM_WRITE_REG32(base_addr, FSPIM_DMA_TDLR_OFFSET, level);
}

/**
 * @name: FSpimSetRxDMALevel
 * @msg: 设置RX DMA等级
 * @return {*}
 * @param {uintptr} base_addr
 * @param {u32} level, RX DMA等级, 应该与FIFO阈值保持一致
 */
static inline void FSpimSetRxDMALevel(uintptr base_addr, u32 level)
{
    FSPIM_WRITE_REG32(base_addr, FSPIM_DMA_RDLR_OFFSET, level);
}


/**
 * @name: FSpimGetEnable
 * @msg: 获取FSPIM控制器的使能状态
 * @return {*}
 * @param {uintptr} base_addr
 */
static inline boolean FSpimGetEnable(uintptr base_addr)
{
    return FSPIM_READ_REG32(base_addr, FSPIM_SSIENR_OFFSET);
}

/**
 * @name: FSpimSetEnable
 * @msg: 使能/去使能FSPIM控制器
 * @return {*}
 * @param {uintptr} base_addr
 * @param {boolean} enable
 */
static inline void FSpimSetEnable(uintptr base_addr, boolean enable)
{
    if (enable)
    {
        FSPIM_WRITE_REG32(base_addr, FSPIM_SSIENR_OFFSET, FSPIM_SSIENR_SSI_EN(1));
    }
    else
    {
        FSPIM_WRITE_REG32(base_addr, FSPIM_SSIENR_OFFSET, FSPIM_SSIENR_SSI_EN(0));
    }
}

/**
 * @name: FSpimMaskIrq
 * @msg: 屏蔽指定的中断位，去使能中断
 * @return {*}
 * @param {uintptr} base_addr
 * @param {u32} mask
 */
static inline void FSpimMaskIrq(uintptr base_addr, u32 mask)
{
    u32 curr_mask;
    curr_mask = FSPIM_READ_REG32(base_addr, FSPIM_IMR_OFFSET) & ~mask; /* = 0 中断不活动*/
    FSPIM_WRITE_REG32(base_addr, FSPIM_IMR_OFFSET, curr_mask);
}

/**
 * @name: FSpimUmaskIrq
 * @msg: 取消屏蔽指定的中断位，使能中断
 * @return {*}
 * @param {uintptr} base_addr
 * @param {u32} mask
 */
static inline void FSpimUmaskIrq(uintptr base_addr, u32 mask)
{
    u32 curr_mask;
    curr_mask = FSPIM_READ_REG32(base_addr, FSPIM_IMR_OFFSET) | mask; /* = 1 中断活动 */
    FSPIM_WRITE_REG32(base_addr, FSPIM_IMR_OFFSET, curr_mask);
}


/**
 * @name: FSpimGetMask
 * @msg: 获取当前的中断屏蔽位
 * @return {*}
 * @param {uintptr} base_addr
 */
static inline u32 FSpimGetMask(uintptr base_addr)
{
    return FSPIM_IMR_ALL_BITS & FSPIM_READ_REG32(base_addr, FSPIM_IMR_OFFSET);
}

/**
 * @name: FSpimGetTransMode
 * @msg: 获取当前的传输模式
 * @return {*}
 * @param {uintptr} base_addr
 */
static inline u32 FSpimGetTransMode(uintptr base_addr)
{
    return ((FSpimGetCtrlR0(base_addr) & FSPIM_CTRL_R0_TMOD_MASK) >> FSPIM_CTRL_R0_TMOD_SHIFT);
}

/**
 * @name: FSpimGetStatus
 * @msg: 获取当前的FSPIM控制器状态
 * @return {*}
 * @param {uintptr} base_addr
 */
static inline u32 FSpimGetStatus(uintptr base_addr)
{
    return FSPIM_READ_REG32(base_addr, FSPIM_SR_OFFSET);
}

/**
 * @name: FSpimWriteData
 * @msg: 写SPI数据
 * @return {*}
 * @param {uintptr} base_addr
 * @param {u16} dat
 */
static inline void FSpimWriteData(uintptr base_addr, u16 dat)
{
    FSPIM_WRITE_REG32(base_addr, FSPIM_DR_OFFSET, FSPIM_DR(dat));
}

/**
 * @name: FSpimReadData
 * @msg: 读SPI数据
 * @return {*}
 * @param {uintptr} base_addr
 */
static inline u16 FSpimReadData(uintptr base_addr)
{
    return (u16)(FSPIM_READ_REG32(base_addr, FSPIM_DR_OFFSET));
}

/************************** Function Prototypes ******************************/
/* 使能/去使能和从设备的连接 */
void FSpimSetSlaveEnable(uintptr base_addr, boolean enable);

/* 获取TX Fifo可以设置的最大深度 */
u32 FSpimGetTxFifoDepth(uintptr base_addr);

/* 获取RX Fifo可以设置的最大深度 */
u32 FSpimGetRxFifoDepth(uintptr base_addr);

/* 选择SPI从设备 */
void FSpimSelSlaveDev(uintptr base_addr, u32 slave_dev_id);

/* 设置SPI传输速度 */
FError FSpimSetSpeed(uintptr base_addr, u32 speed);

/* 读取SPI传输速度 */
u32 FSpimGetSpeed(uintptr base_addr);

/* 设置SPI传输模式 */
void FSpimSetTransMode(uintptr base_addr, u32 trans_mode);

/* 设置串行时钟相位 */
void FSpimSetCpha(uintptr base_addr, u32 cpha_mode);

/* 设置串行时钟相位 */
void FSpimSetCpol(uintptr base_addr, u32 cpol_mode);

/* 读取串行时钟相位 */
FSpimCphaType FSpimGetCpha(uintptr base_addr);

/* 读取串行时钟极性 */
FSpimCpolType FSpimGetCpol(uintptr base_addr);

#ifdef __cplusplus
}
#endif

#endif // !