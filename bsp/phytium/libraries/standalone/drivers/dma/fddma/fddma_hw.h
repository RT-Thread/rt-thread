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
 * FilePath: fddma_hw.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:24:52
 * Description:  This files is for register definition
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/5/13    init commit
 */

#ifndef  FDDMA_HW_H
#define  FDDMA_HW_H

/***************************** Include Files *********************************/

#include "fassert.h"
#include "ftypes.h"
#include "fio.h"
#include "fkernel.h"

#ifdef __cplusplus
extern "C"
{
#endif


/************************** Constant Definitions *****************************/
/** @name Register Map
 *
 * Register offsets from the base address of an GPIO device.
 * @{
 */
#define FDDMA_CTL_OFFSET                        0x0 /* 全局控制类寄存器 */
#define FDDMA_CHAN_0_3_CFG_OFFSET               0x4 /* DMA通道0~3选择配置寄存器 */
#define FDDMA_STA_OFFSET                        0x8 /* 中断状态寄存器 */
#define FDDMA_MASK_INTR_OFFSET                  0xC /* 中断掩码寄存器 */
/* AXI读写相关的配置硬件暂未开放 */
#define FDDMA_UP_AXI_AW_CFG_OFFSET              0x10 /* 上行AXI写通道配置寄存器 */
#define FDDMA_UP_AXI_AR_CFG_OFFSET              0x14 /* 上行AXI读通道配置寄存器 */
#define FDDMA_DOWN_AXI_AW_CFG_OFFSET            0x18 /* 下行AXI写通道配置寄存器 */
#define FDDMA_DOWN_AXI_AR_CFG_OFFSET            0x1C /* 下行AXI读通道配置寄存器 */

#define FDDMA_CHAN_BIND_OFFSET                  0x20 /* DMA通道绑定寄存器 */
#define FDDMA_GCAP_OFFSET                       0x24 /* DMA通道数寄存器（只读） */
#define FDDMA_CHAN_4_7_CFG_OFFSET               0x28 /* DMA通道4~7选择配置寄存器 */

#define FDDMA_CHAN_OFFSET(chan)                 (0x40 * (chan))
#define FDDMA_CHAN_DDR_UP_ADDR_OFFSET(chan)     (0x40 + FDDMA_CHAN_OFFSET(chan)) /* 内存中源/目的地址高32位 */
#define FDDMA_CHAN_DDR_LOW_ADDR_OFFSET(chan)    (0x44 + FDDMA_CHAN_OFFSET(chan)) /* 内存中源/目的地址低32位 */
#define FDDMA_CHAN_DEV_ADDR_OFFSET(chan)        (0x48 + FDDMA_CHAN_OFFSET(chan)) /* 设备中源/目的地址32位 */
#define FDDMA_CHAN_TS_OFFSET(chan)              (0x4C + FDDMA_CHAN_OFFSET(chan)) /* 需要传输的总数据字节数 */
#define FDDMA_CHAN_CRT_UP_ADDR_OFFSET(chan)     (0x50 + FDDMA_CHAN_OFFSET(chan)) /* 当前内存需要读写数据的高32位 */
#define FDDMA_CHAN_CRT_LOW_ADDR_OFFSET(chan)    (0x54 + FDDMA_CHAN_OFFSET(chan)) /* 当前内存需要读写数据的低32位 */
#define FDDMA_CHAN_CTL_OFFSET(chan)             (0x58 + FDDMA_CHAN_OFFSET(chan)) /* 通道控制寄存器 */
#define FDDMA_CHAN_STS_OFFSET(chan)             (0x5C + FDDMA_CHAN_OFFSET(chan)) /* 通道状态寄存器 */
#define FDDMA_CHAN_TIMEOUT_CNT_OFFSET(chan)     (0x60 + FDDMA_CHAN_OFFSET(chan)) /* 超时等待阈值 */

/** @name FDDMA_CTL_OFFSET Register
 */
#define FDDMA_CTL_SRST                          BIT(1) /* 1: 全局软复位 */
#define FDDMA_CTL_ENABLE                        BIT(0) /* 1: 全局使能控制 */

/** @name FDDMA_CHAN_0_3_CFG_OFFSET Register
 */
#define FDDMA_CHAN_0_3_SEL_EN(chan)             BIT((chan) * 8 + 7)      /* 1: 通道chan信号源选择有效 */
#define FDDMA_CHAN_0_3_SEL(chan, sel)           ((sel) <<  ((chan) * 8)) /* 通道chan信号源选择sel项 */
#define FDDMA_CHAN_0_3_SEL_MASK(chan)           (GENMASK(7, 0) << ((chan) * 8))

/** @name FDDMA_STA_OFFSET Register
 */
#define FDDMA_STA_CHAN_REQ_DONE(chan)           BIT((chan) * 4) /* 通道chan的block请求完成时置1，写1后清0 */

/** @name FDDMA_MASK_INTR_OFFSET Register
 */
#define FDDMA_MASK_EN_GLOBAL_INTR               BIT(31)   /* 全局中断使能输出控制位 */
#define FDDMA_MASK_EN_CHAN_INTR(chan)           BIT(chan) /* 通道chan的中断输出控制位 */

/** @name FDDMA_CHAN_BIND_OFFSET Register
 */
#define FDDMA_CHAN_BIND(chan)                   BIT(chan) /* 1: 通道已绑定了外设DMA请求信号线 */

/** @name FDDMA_CHAN_4_7_CFG_OFFSET Register
 */
#define FDDMA_CHAN_4_7_SEL_EN(chan)             BIT(((chan) - 4) * 8 + 7) /* 1: 通道chan信号源选择有效 */
#define FDDMA_CHAN_4_7_SEL(chan, sel)           ((sel) <<  (((chan) - 4) * 8)) /* 通道chan信号源选择sel项 */
#define FDDMA_CHAN_4_7_SEL_MASK(chan)           (GENMASK(7, 0) << (((chan) - 4) * 8))

/** @name FDDMA_CHAN_CTL_OFFSET Register
 */
#define FDDMA_CHAN_CTL_RX_MODE                  BIT(2)  /* 1：接收外设 dma_rx_req, 0：接收外设 dma_tx_req */
#define FDDMA_CHAN_CTL_SRST                     BIT(1)  /* 1: 复位通道 */
#define FDDMA_CHAN_CTL_EN                       BIT(0)  /* 1: 使能通道 */

/** @name FDDMA_CHAN_STS_OFFSET Register
 */
#define FDDMA_CHAN_STS_FIFO_EMPTY               BIT(1)  /* 1: FIFO空状态 */
#define FDDMA_CHAN_STS_FIFO_FULL                BIT(0)  /* 1: FIFO满状态 */

/** @name FDDMA_CHAN_TIMEOUT_CNT_OFFSET Register
 */
#define FDDMA_CHAN_TIMEOUT_EN                   BIT(32)  /* 1: 使能超时机制 */
#define FDDMA_CHAN_TIMEOUT_CNT_SET(cnt)         SET_REG32_BITS((cnt), 27, 0)  /* 超时阈值 */
#define FDDMA_CHAN_TIMEOUT_CNT_MASK             GENMASK(27, 0)
/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
/**
 * @name: FDdmaReadReg
 * @msg: 读DDMA寄存器
 * @return {u32} 获取的寄存器值
 * @param {uintptr} base_addr, DDMA寄存器基地址
 * @param {u32} reg_off, DDMA寄存器偏移量
 */
static inline u32 FDdmaReadReg(uintptr base_addr, u32 reg_off)
{
    return FtIn32(base_addr + reg_off);
}

/**
 * @name: FDdmaWriteReg
 * @msg: 写DDMA寄存器
 * @return {无}
 * @param {uintptr} base_addr, DDMA寄存器基地址
 * @param {u32} reg_off, DDMA寄存器偏移量
 * @param {u32} reg_val, 设置的寄存器值
 */
static inline void FDdmaWriteReg(uintptr base_addr, u32 reg_off, u32 reg_val)
{
    FtOut32(base_addr + reg_off, reg_val);
    return;
}

/**
 * @name: FDdmaReadStatus
 * @msg: 获取DDMA中断状态
 * @return {u32} 中断状态
 * @param {uintptr} base_addr, DDMA寄存器基地址
 */
static inline u32 FDdmaReadStatus(uintptr base_addr)
{
    return FDdmaReadReg(base_addr, FDDMA_STA_OFFSET);
}

/**
 * @name: FDdmaReadChanStatus
 * @msg: 获取DDMA通道中断状态
 * @return {u32} 中断状态
 * @param {uintptr} base_addr, DDMA寄存器基地址
 * @param {u32} chan, DDMA通道号
 */
static inline u32 FDdmaReadChanStatus(uintptr base_addr, u32 chan)
{
    return FDdmaReadReg(base_addr, FDDMA_CHAN_STS_OFFSET(chan));
}

/************************** Function Prototypes ******************************/
/* 复位DDMA控制器 */
void FDdmaSoftwareReset(uintptr base_addr);

/* 去使能DDMA控制器 */
void FDdmaDisable(uintptr base_addr);

/* 使能DDMA控制器 */
void FDdmaEnable(uintptr base_addr);

/* 重置DDMA通道 */
void FDdmaResetChan(uintptr base_addr, u32 chan);

/* 去使能DDMA通道 */
FError FDdmaDisableChan(uintptr base_addr, u32 chan);

/* 使能DDMA通道 */
void FDdmaEnableChan(uintptr base_addr, u32 chan);

/* 关闭DDMA全局中断 */
void FDdmaDisableGlobalIrq(uintptr base_addr);

/* 打开DDMA全局中断 */
void FDdmaEnableGlobalIrq(uintptr base_addr);

/* 关闭DDMA通道中断 */
void FDdmaDisableChanIrq(uintptr base_addr, u32 chan);

/* 打开DDMA通道中断 */
void FDdmaEnableChanIrq(uintptr base_addr, u32 chan);

/* 清除DDMA通道中断状态 */
void FDdmaClearChanIrq(uintptr base_addr, u32 chan);

/* 检查通道是否在工作中 */
boolean FDdmaIsChanRunning(uintptr base_addr, u32 chan);

/* 将DDMA通道与外设绑定 */
void FDdmaSetChanSelection(uintptr base_addr, u32 chan, u32 slave_id);

/* 修改通道的绑定状态 */
void FDdmaSetChanBind(uintptr base_addr, u32 chan, boolean bind);

/* 设置通道的方向 */
void FDdmaSetChanDirection(uintptr base_addr, u32 chan, boolean is_rx);

/* 设置通道超时 */
void FDdmaSetChanTimeout(uintptr base_addr, u32 chan, u32 timeout);

#ifdef __cplusplus
}
#endif

#endif