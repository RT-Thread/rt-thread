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
 * FilePath: fgdma_hw.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:24:52
 * Description:  This file is for gdma register related defintion
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2021/11/5    init commit
 * 1.1   zhugengyu  2022/5/16    modify according to tech manual.
 */

#ifndef FGDMA_HW_H
#define FGDMA_HW_H

#include "fparameters.h"
#include "fio.h"
#include "fkernel.h"

#ifdef __cplusplus
extern "C"
{
#endif
/***************************** Include Files *********************************/

/************************** Constant Definitions *****************************/

/** @name Register Map
 *
 * Register offsets from the base address of an GDMA device.
 * @{
 */
#define FGDMA_CTL_OFFSET            0x0U    /* 全局控制类寄存器 */
#define FGDMA_INTR_STATE_OFFSET     0x4U    /* 中断状态寄存器 */
#define FGDMA_INTR_CTRL_OFFSET      0x8U    /* 中断使能控制寄存器 */
#define FGDMA_LP_OFFSET             0xCU    /* 每一位对应一个通道时钟开启和关断 */
#define FGDMA_QOS_CFG_OFFSET        0x10U   /* 读写请求的 QoS 配置 */

/* Channel register */
#define FGDMA_CHX_OFFSET(x)             ((x) * 0x60U)
#define FGDMA_CHX_CTL_OFFSET(x)         (0x20 + FGDMA_CHX_OFFSET(x)) /* 软复位信号与使能控制信号 */
#define FGDMA_CHX_MODE_OFFSET(x)        (0x24 + FGDMA_CHX_OFFSET(x)) /* 模式寄存器 */
#define FGDMA_CHX_INT_CTRL_OFFSET(x)    (0x28 + FGDMA_CHX_OFFSET(x)) /* 中断输出控制寄存器 */
#define FGDMA_CHX_INT_STATE_OFFSET(x)   (0x2C + FGDMA_CHX_OFFSET(x)) /* 状态寄存器 */
#define FGDMA_CHX_LVI_OFFSET(x)         (0x30 + FGDMA_CHX_OFFSET(x)) /* 链表模式下 BDL 有效条目 */
#define FGDMA_CHX_TS_OFFSET(x)          (0x34 + FGDMA_CHX_OFFSET(x)) /* 直接操作模式下总 Byte 数据量 */
#define FGDMA_CHX_UPSADDR_OFFSET(x)     (0x38 + FGDMA_CHX_OFFSET(x)) /* 源地址寄存器(高32位) */
#define FGDMA_CHX_LWSADDR_OFFSET(x)     (0x3C + FGDMA_CHX_OFFSET(x)) /* 源地址寄存器(低32位) */
#define FGDMA_CHX_UPDADDR_OFFSET(x)     (0x40 + FGDMA_CHX_OFFSET(x)) /* 目的地址寄存器(高32位) */
#define FGDMA_CHX_LWDADDR_OFFSET(x)     (0x44 + FGDMA_CHX_OFFSET(x)) /* 目的地址寄存器(低32位) */
#define FGDMA_CHX_XFER_CFG_OFFSET(x)    (0x48 + FGDMA_CHX_OFFSET(x)) /* 读写请求 Burst 信息 */
#define FGDMA_CHX_LCP_OFFSET(x)         (0x4C + FGDMA_CHX_OFFSET(x)) /* 当前操作了多少个 BDL 列表 */
#define FGDMA_CHX_SECCTL_OFFSET(x)      (0x50 + FGDMA_CHX_OFFSET(x)) /* 安全控制寄存器 */
#define FGDMA_CHX_SEC_ATST_OFFSET(x)    (0x54 + FGDMA_CHX_OFFSET(x)) /* Secssid 和 Atst信号控制寄存器 */
#define FGDMA_CHX_NSID_STRMID_OFFSET(x) (0x58 + FGDMA_CHX_OFFSET(x)) /* NSAID 和 StreamID 控制寄存器 */
#define FGDMA_CHX_AW_CFG_OFFSET(x)      (0x5C + FGDMA_CHX_OFFSET(x)) /* 控制 AXI AW 通道配置寄存器 */
#define FGDMA_CHX_AR_CFG_OFFSET(x)      (0x60 + FGDMA_CHX_OFFSET(x)) /* 控制 AXI AR 通道配置寄存器 */
#define FGDMA_CHX_SECRSP_OFFSET(x)      (0x64 + FGDMA_CHX_OFFSET(x)) /* 通道 Response 安全控制寄存器 */

/** @name FGDMA_CTL_OFFSET Register
 */
#define FGDMA_CTL_OT_MASK               GENMASK(11, 8)
#define FGDMA_CTL_OT_SET(ot)            SET_REG32_BITS(ot, 11, 8) /* dma 传输outstanding 控制，实际数量为该寄存器值+1 */
#define FGDMA_CTL_RD_ARB                BIT(5) /* dma 读请求仲裁模式: 0：轮询模式，1：采用Qos判断模式 */
#define FGDMA_CTL_WR_ARB                BIT(4) /* dma 写请求仲裁模式: 0：轮询模式，1：采用Qos判断模式 */
#define FGDMA_CTL_SOFT_RESET            BIT(1) /* dma 软件复位信号，1表示进行复位，写0退出 */
#define FGDMA_CTL_ENABLE                BIT(0) /* dma 使能信号，1表示使能，写0表示disable */

/** @name FGDMA_INTR_STATE_OFFSET Register
 */
#define FGDMA_CHX_INTR_STATE(x)         BIT(x) /* channel-x 中断状态标志位 */

/** @name FGDMA_INTR_CTRL_OFFSET Register
 */
#define FGDMA_CHX_INTR_MASK(x)          BIT(x)  /* channel-x 中断使能控制，1 表示使能，0 表示不使能 */
#define FGDMA_CHX_INTR_GLOBAL_MASK      BIT(31) /* 全局中断输出 mask 控制信号，1表示允许中断输出，0 表示不允许 */

/** @name FGDMA_LP_OFFSET Register
 */
#define FGDMA_CHX_LP_CTL(x)             BIT(x)  /* channel-x 时钟开启和关断，1 表示关断，默认开启 */

/** @name FGDMA_QOS_CFG_OFFSET Register
 */
#define FGDMA_QOS_CFG_ARGOS_MASK        GENMASK(7, 4)
#define FGDMA_QOS_CFG_ARGOS_SET(qos)    SET_REG32_BITS((qos), 7, 4) /* 读请求的 QoS 配置 */
#define FGDMA_QOS_CFG_AWQOS_MASK        GENMASK(3, 0)
#define FGDMA_QOS_CFG_AWQOS_SET(qos)    SET_REG32_BITS((qos), 3, 0) /* 写请求的 QoS 配置 */

/** @name FGDMA_CHX_CTL_OFFSET Register
 */
#define FGDMA_CHX_CTL_SOFT_RESET        BIT(4) /* 软复位信号，1 表示进行软复位，写 0 退出 */
#define FGDMA_CHX_CTL_ENABLE            BIT(0) /* 使能控制信号，1 表示使能该通道，0 表示不使能 */

/** @name FGDMA_CHX_MODE_OFFSET Register
 */
#define FGDMA_CHX_MODE_RD_QOS_MASK          GENMASK(23, 20)
#define FGDMA_CHX_MODE_RD_QOS_SET(qos)      SET_REG32_BITS((qos), 23, 20) /* CHX 读请求 Qos 配置 */
#define FGDMA_CHX_MODE_RD_QOS_GET(qos)      GET_REG32_BITS((qos), 23, 20)
/* 是否用 cd_rd_qos 的值替换该通道的去请求 QoSS，1 表示替换, 0 不替换 */
#define FGDMA_CHX_MODE_RD_QOS_EN            BIT(16)

#define FGDMA_CHX_MODE_WR_QOS_MASK          GENMASK(15, 12)
#define FGDMA_CHX_MODE_WR_QOS_SET(qos)      SET_REG32_BITS((qos), 15, 12) /* CHX 写请求 Qos 配置 */
#define FGDMA_CHX_MODE_WR_QOS_GET(qos)      GET_REG32_BITS((qos), 15, 12)
/* 是否用 cx_wr_qos 中的值替换该通道写请求的 QoS：1 表示替换, 0 不替换 */
#define FGDMA_CHX_MODE_WR_QOS_EN            BIT(8)

/* 是否用CHX qos cfg 中的值替换该读请求的 Qos：1 表示替换 ，0 不替换 */
#define FGDMA_CHX_MODE_BDL_ROLL_EN          BIT(4)
#define FGDMA_CHX_MODE_BDL_EN               BIT(0)  /* 配置当前采用direct 或者BDL 链表模式, 0 采用Direct 模式, 1 采用BDL 模式 */

/** @name FGDMA_CHX_INT_CTRL_OFFSET Register
 */
#define FGDMA_CHX_INT_CTRL_TRANS_END_ENABLE     BIT(3)  /* CHX 所以数据传输完成中断输出控制，1表示允许输出，0表示不允许 */
#define FGDMA_CHX_INT_CTRL_BDL_END_ENABLE       BIT(2)  /* CHX bdl 条目数据传输完成中断输出控制，1表示允许输出，0表示不允许  */
#define FGDMA_CHX_INT_CTRL_FIFO_FULL_ENABLE     BIT(1)  /* CHX ARM满中断 1表示允许输出，0表示不允许 */
#define FGDMA_CHX_INT_CTRL_FIFO_EMPTY_ENABLE    BIT(0)  /* CHX ARM空中断 1表示允许输出，0表示不允许 */

/** @name FGDMA_CHX_INT_STATE_OFFSET Register
 */
#define FGDMA_CHX_INT_STATE_BUSY                BIT(4)  /* CHX 处于数据传输中，写1 清0 */
#define FGDMA_CHX_INT_STATE_TRANS_END           BIT(3)  /* CHX 处于传输完成状态，direct 模式时，表示所有数据传输完成，BDL 模式表示当前所有BDL条目传输完成： 写1清0 */
#define FGDMA_CHX_INT_STATE_BDL_END             BIT(2)  /* CHX 在BDL模式下，表示当前一个BDL 条目数据传输完成；Direct 模式下该位始终为0 ，  写1清0 */
#define FGDMA_CHX_INT_STATE_FIFO_FULL           BIT(1)  /* CHX FIFO 满状态，写1清0 */
#define FGDMA_CHX_INT_STATE_FIFO_EMPTY          BIT(0)  /* CHX FIFO 空状态，写1清0 */
#define FGDMA_CHX_INT_STATE_ALL                 GENMASK(4, 0)

/** @name FGDMA_CHX_LVI_OFFSET Register
 */
#define FGDMA_CHX_LVI_SET(lvi)        SET_REG32_BITS((lvi - 1), 31, 0) /* CHX last vaild index, 即链表末模式下BDL有效条目，实际有效条目=该寄存器值+1 */

/** @name FGDMA_CHX_TS_OFFSET Register
 */
#define FGDMA_CHX_TS_SET(ts)          SET_REG32_BITS((ts), 31, 0) /* CHX 在direct 模式下操作的的总Byte数量 */

/** @name FGDMA_CHX_UPSADDR_OFFSET Register
 */
#define FGDMA_CHX_UPSADDR_SET(addr)   SET_REG32_BITS((addr), 31, 0) /* CHX 源地址高32bits */

/** @name FGDMA_CHX_LWSADDR_OFFSET Register
 */
#define FGDMA_CHX_LWSADDR_SET(addr)   SET_REG32_BITS((addr), 31, 0) /* CHX 源地址低32bits */

/** @name FGDMA_CHX_UPDADDR_OFFSET Register
 */
#define FGDMA_CHX_UPDADDR_SET(addr)   SET_REG32_BITS((addr), 31, 0) /* CHX 目标地址高32bits */

/** @name FGDMA_CHX_LWDADDR_OFFSET Register
 */
#define FGDMA_CHX_LWDADDR_SET(addr)   SET_REG32_BITS((addr), 31, 0) /* CHX 目标地址低32bits */

/** @name FGDMA_CHX_XFER_CFG_OFFSET Register
 */
#define FGDMA_CHX_XFER_CFG_AR_LEN_SET(len)      SET_REG32_BITS((len), 31, 24) /* CHX 读请求 Burst length 大小 */
#define FGDMA_CHX_XFER_CFG_AR_SIZE_SET(size)    SET_REG32_BITS((size), 22, 20) /* CHX 读请求 Burst size 大小， 支持 1、2、8、16 Byte */
#define FGDMA_CHX_XFER_CFG_AR_BRUST_SET(type)   SET_REG32_BITS((type), 17, 16) /* CHX 读请求 Brust 类型： 0：fix ，1：incr */
#define FGDMA_CHX_XFER_CFG_AW_LEN_SET(len)      SET_REG32_BITS((len), 15, 8) /* CHX 写请求 Burst length 大小 */
#define FGDMA_CHX_XFER_CFG_AW_SIZE_SET(size)    SET_REG32_BITS((size), 6, 4) /* CHX 写请求 Burst size 大小， 支持 1、2、8、16 Byte */
#define FGDMA_CHX_XFER_CFG_AW_BRUST_SET(type)   SET_REG32_BITS((type), 1, 0) /* CHX 写请求 Brust 类型： 0：fix ，1：incr */

#define FGDMA_INCR                      1U
#define FGDMA_FIX                       0U

#define FGDMA_BURST_LEN                 7U /* burst lenth = FGDMA_BURST_LEN + 1，写入寄存器的最大合法值为7，burst length最大值为8 */

/** @name FGDMA_CHX_LCP_OFFSET Register
 */
#define FGDMA_CHX_LCP_GET(reg_val)   GET_REG32_BITS((reg_val), 31, 0) /* 当前操作的BDL列表数  */

/** @name FGDMA_CHX_SECCTL_OFFSET Register
 */
#define FGDMA_CHX_SECCTL_SET(val)    GET_REG32_BITS((val), 31, 0) /* CHX 安全控制寄存器，仅安全状态可访问 */

/** @name FGDMA_CHX_SEC_ATST_OFFSET Register
 */
#define FGDMA_CHX_SEC_ATST_SET(val)  SET_REG32_BITS((val), 31, 0)

/** @name FGDMA_CHX_NSID_STRMID_OFFSET Register
 */
#define FGDMA_CHX_NSID_STRMID_SET(val)  SET_REG32_BITS((val), 31, 0)

/** @name FGDMA_CHX_AW_CFG_OFFSET Register
 */
#define FGDMA_CHX_AW_CFG_AWCACHE_SET(val)        SET_REG32_BITS((val), 3, 0)  /* CHX dma arcache */
#define FGDMA_CHX_AW_CFG_AWREGION_MASK_SET(val)  SET_REG32_BITS((val), 7, 4) /* CHX dma arregion */
#define FGDMA_CHX_AW_CFG_AWPROT_SET(val)         SET_REG32_BITS((val), 9, 8)
#define FGDMA_CHX_AW_CFG_AWDOMAIN_SET(val)       SET_REG32_BITS((val), 13, 12) /* chx ardomain */
#define FGDMA_CHX_AW_CFG_AWSNOOP_SET(val)        SET_REG32_BITS((val), 18, 16)
#define FGDMA_CHX_AW_CFG_AWBAR_SET(val)          SET_REG32_BITS((val), 21, 20)

/** @name FGDMA_CHX_AR_CFG_OFFSET Register
 */
#define FGDMA_CHX_AR_CFG_AWCACHE_SET(val)        SET_REG32_BITS((val), 3, 0)  /* CHX dma arcache */
#define FGDMA_CHX_AR_CFG_AWREGION_MASK_SET(val)  SET_REG32_BITS((val), 7, 4) /* CHX dma arregion */
#define FGDMA_CHX_AR_CFG_AWPROT_SET(val)         SET_REG32_BITS((val), 9, 8)
#define FGDMA_CHX_AR_CFG_AWDOMAIN_SET(val)       SET_REG32_BITS((val), 13, 12) /* chx ardomain */
#define FGDMA_CHX_AR_CFG_AWSNOOP_SET(val)        SET_REG32_BITS((val), 19, 16)
#define FGDMA_CHX_AR_CFG_AWBAR_SET(val)          SET_REG32_BITS((val), 21, 20)

/** @name FGDMA_CHX_SECRSP_OFFSET Register
 */
#define FGDMA_CHX_SECRSP                         BIT(0) /* response 安全控制位 */

#define FGDMA_OUTSTANDING                        0xfU  /* 实际outstanding数目为0xf + 1 */

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FGDMA_READREG(base_addr, reg_offset) \
    FtIn32((base_addr) + (u32)(reg_offset))

#define FGDMA_WRITEREG(base_addr, reg_offset, data) \
    FtOut32((base_addr) + (u32)(reg_offset), (u32)(data))

/**
 * @name: FGdmaDisable
 * @msg: 去使能GDMA控制器
 * @return {void} 无
 * @param {uintptr} base_addr, GDMA控制器基地址
 */
static inline void FGdmaDisable(uintptr base_addr)
{
    u32 reg_val = FGDMA_READREG(base_addr, FGDMA_CTL_OFFSET);
    reg_val &= ~FGDMA_CTL_ENABLE;
    FGDMA_WRITEREG(base_addr, FGDMA_CTL_OFFSET, reg_val);
}

/**
 * @name: FGdmaEnable
 * @msg: 使能GDMA控制器
 * @return {void} 无
 * @param {uintptr} base_addr, GDMA控制器基地址
 */
static inline void FGdmaEnable(uintptr base_addr)
{
    u32 reg_val = FGDMA_READREG(base_addr, FGDMA_CTL_OFFSET);
    reg_val |= FGDMA_CTL_ENABLE;
    FGDMA_WRITEREG(base_addr, FGDMA_CTL_OFFSET, reg_val);
}

/**
 * @name: FGdmaSoftwareReset
 * @msg: 完成GDMA控制器软复位
 * @return {void} 无
 * @param {uintptr} base_addr, GDMA控制器基地址
 */
static inline void FGdmaSoftwareReset(uintptr base_addr)
{
    int delay = 100;
    u32 reg_val = FGDMA_READREG(base_addr, FGDMA_CTL_OFFSET);
    reg_val |= FGDMA_CTL_SOFT_RESET;
    FGDMA_WRITEREG(base_addr, FGDMA_CTL_OFFSET, reg_val);

    while (--delay > 0)
        ;

    reg_val = FGDMA_READREG(base_addr, FGDMA_CTL_OFFSET);
    reg_val &= ~FGDMA_CTL_SOFT_RESET;
    FGDMA_WRITEREG(base_addr, FGDMA_CTL_OFFSET, reg_val);
}

/**
 * @name: FGdmaIrqEnable
 * @msg: 开启GDMA控制器中断
 * @return {void} 无
 * @param {uintptr} base_addr, GDMA控制器基地址
 */
static inline void FGdmaIrqEnable(uintptr base_addr)
{
    u32 reg_val = FGDMA_READREG(base_addr, FGDMA_INTR_CTRL_OFFSET);
    reg_val |= FGDMA_CHX_INTR_GLOBAL_MASK;
    FGDMA_WRITEREG(base_addr, FGDMA_INTR_CTRL_OFFSET, reg_val);
}

/**
 * @name: FGdmaIrqDisable
 * @msg: 关闭GDMA控制器中断
 * @return {void} 无
 * @param {uintptr} base_addr, GDMA控制器基地址
 */
static inline void FGdmaIrqDisable(uintptr base_addr)
{
    u32 reg_val = FGDMA_READREG(base_addr, FGDMA_INTR_CTRL_OFFSET);
    reg_val &= ~FGDMA_CHX_INTR_GLOBAL_MASK;
    FGDMA_WRITEREG(base_addr, FGDMA_INTR_CTRL_OFFSET, reg_val);
}

/**
 * @name: FGdmaChanDisable
 * @msg: 去使能GDMA通道
 * @return {void} 无
 * @param {uintptr} base_addr, GDMA控制器基地址
 * @param {u32} chan, GDMA通道号
 */
static inline void FGdmaChanDisable(uintptr base_addr, u32 chan)
{
    u32 reg_val = FGDMA_READREG(base_addr, FGDMA_CHX_CTL_OFFSET(chan));
    reg_val &= ~FGDMA_CHX_CTL_ENABLE; /* 禁用通道 */
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_CTL_OFFSET(chan), reg_val);
}

/**
 * @name: FGdmaChanEnable
 * @msg: 使能GDMA通道
 * @return {void} 无
 * @param {uintptr} base_addr, GDMA控制器基地址
 * @param {u32} chan, GDMA通道号
 */
static inline void FGdmaChanEnable(uintptr base_addr, u32 chan)
{
    u32 reg_val = FGDMA_READREG(base_addr, FGDMA_CHX_CTL_OFFSET(chan));
    reg_val |= FGDMA_CHX_CTL_ENABLE; /* 使能通道 */
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_CTL_OFFSET(chan), reg_val);
}

/**
 * @name: FGdmaChanIrqDisable
 * @msg: 关闭GDMA通道中断
 * @return {void} 无
 * @param {uintptr} base_addr, GDMA控制器基地址
 * @param {u32} chan, GDMA通道号
 */
static inline void FGdmaChanIrqDisable(uintptr base_addr, u32 chan)
{
    u32 reg_val = FGDMA_READREG(base_addr, FGDMA_INTR_CTRL_OFFSET);
    reg_val &= ~FGDMA_CHX_INTR_MASK(chan); /* 禁用通道中断 */
    FGDMA_WRITEREG(base_addr, FGDMA_INTR_CTRL_OFFSET, reg_val);
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_INT_CTRL_OFFSET(chan), 0x0U); /* 禁用通道所有中断位 */
}

/**
 * @name: FGdmaChanIrqEnable
 * @msg: 打开GDMA通道中断
 * @return {void} 无
 * @param {uintptr} base_addr, GDMA控制器基地址
 * @param {u32} chan, GDMA通道号
 * @param {u32} umask, 使能的通道中断位
 */
static inline void FGdmaChanIrqEnable(uintptr base_addr, u32 chan, u32 umask)
{
    u32 reg_val = FGDMA_READREG(base_addr, FGDMA_INTR_CTRL_OFFSET);
    reg_val |= FGDMA_CHX_INTR_MASK(chan); /* 使能通道中断 */
    FGDMA_WRITEREG(base_addr, FGDMA_INTR_CTRL_OFFSET, reg_val);
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_INT_CTRL_OFFSET(chan), umask); /* 使能通道指定中断位 */
}

/**
 * @name: FGdmaChanReset
 * @msg: 完成GDMA通道软复位
 * @return {void} 无
 * @param {uintptr} base_addr, GDMA控制器基地址
 * @param {u32} chan, GDMA通道号
 */
static inline void FGdmaChanReset(uintptr base_addr, u32 chan)
{
    int delay = 100;
    u32 reg_val = FGDMA_READREG(base_addr, FGDMA_CHX_CTL_OFFSET(chan));
    reg_val |= FGDMA_CHX_CTL_SOFT_RESET;
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_CTL_OFFSET(chan), reg_val);

    while (--delay > 0)
        ;

    reg_val = FGDMA_READREG(base_addr, FGDMA_CHX_CTL_OFFSET(chan));
    reg_val &= ~FGDMA_CHX_CTL_SOFT_RESET;
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_CTL_OFFSET(chan), reg_val);
}

/**
 * @name: FGdmaReadStatus
 * @msg: 获取GDMA控制器中断状态
 * @return {u32} 中断状态位
 * @param {uintptr} base_addr, GDMA控制器基地址
 */
static inline u32 FGdmaReadStatus(uintptr base_addr)
{
    return FGDMA_READREG(base_addr, FGDMA_INTR_STATE_OFFSET);
}

/**
 * @name: FGdmaReadChanStatus
 * @msg: 获取GDMA通道中断状态
 * @return {u32} 中断状态位
 * @param {uintptr} base_addr, GDMA控制器基地址
 * @param {u32} chan, 通道号
 */
static inline u32 FGdmaReadChanStatus(uintptr base_addr, u32 chan)
{
    return FGDMA_READREG(base_addr, FGDMA_CHX_INT_STATE_OFFSET(chan));
}

/**
 * @name: FGdmaClearChanStatus
 * @msg: 清除GDMA通道中断状态
 * @return {void} 无
 * @param {uintptr} base_addr, GDMA控制器基地址
 * @param {u32} chan, 通道号
 * @param {u32} status, 待清除的中断状态
 */
static inline void FGdmaClearChanStatus(uintptr base_addr, u32 chan, u32 status)
{
    FGDMA_WRITEREG(base_addr, FGDMA_CHX_INT_STATE_OFFSET(chan), status); /* 写1清0 */
}

/**
 * @name: FGdmaSetChanClock
 * @msg: 打开/关闭GDMA通道时钟
 * @return {void} 无
 * @param {uintptr} base_addr, GDMA控制器基地址
 * @param {u32} chan, 通道号
 * @param {boolean} enable，TRUE: 打开时钟, FALSE: 关闭时钟
 */
static inline void FGdmaSetChanClock(uintptr base_addr, u32 chan, boolean enable)
{
    u32 reg_val = FGDMA_READREG(base_addr, FGDMA_LP_OFFSET);
    if (enable)
    {
        reg_val &= ~FGDMA_CHX_LP_CTL(chan);    /* 写0开启通道时钟 */
    }
    else
    {
        reg_val |= FGDMA_CHX_LP_CTL(chan);    /* 写1关断通道时钟 */
    }
    FGDMA_WRITEREG(base_addr, FGDMA_LP_OFFSET, reg_val);

    return;
}

/************************** Function Prototypes ******************************/


#ifdef __cplusplus
}
#endif

#endif