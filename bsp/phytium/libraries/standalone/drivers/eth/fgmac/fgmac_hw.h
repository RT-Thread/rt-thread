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
 * FilePath: fgmac_hw.h
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:58
 * Description:  This file is for manipulation of hardware registers .
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2021/07/13    first release
 */

#ifndef  FGMAC_HW_H
#define  FGMAC_HW_H

/* - 传入模块基地址，不能复杂结构体
- hardware interface of device || low-level driver function prototypes

- 包括驱动寄存器参数和low-level操作定义
1. 定义寄存器偏移
2. 对上提供该模块寄存器操作的接口
3. 一些简单外设提供直接操作接口
4. 可以定义一些状态的接口，用于响应驱动状态的变化

note: 本文件不能引用fooxx.h
*/

/***************************** Include Files *********************************/

#include "fkernel.h"
#include "fio.h"
#include "ftypes.h"

#ifdef __cplusplus
extern "C"
{
#endif
/************************** Constant Definitions *****************************/

/** @name Register Map
 *
 * Register offsets from the base address of an SD device.
 * @{
 */
/**** FGMAC CTRL ****/
#define FGMAC_CONF_OFFSET 0x00U                   /* MAC 配置寄存器 */
#define FGMAC_FRAME_FILTER_OFFSET 0x04U           /* Mac 帧过滤 */
#define FGMAC_HASH_HIGH_OFFSET 0x08U              /* 哈希表高位寄存器 */
#define FGMAC_HASH_LOW_OFFSET 0x0cU               /* 哈希表低位寄存器 */
#define FGMAC_GMII_ADDR_OFFSET 0x10U              /* GMII 地址寄存器 */
#define FGMAC_GMII_DATA_OFFSET 0x14U              /* GMII 数据寄存器 */
#define FGMAC_FLOW_CTRL_OFFSET 0x18U              /* 流控寄存器 */
#define FGMAC_VLAN_TAG_OFFSET 0x1cU               /* VLAN 标记寄存器 */
#define FGMAC_VERSION_OFFSET 0x20U                /* 版本寄存器 */
#define FGMAC_DEBUG_STATUS_OFFSET 0x24U           /* 调试寄存器 */
#define FGMAC_LPI_CTRL_STATUS_OFFSET 0x30U        /* LPI (低功耗空闲) 控制和状态寄存器 */
#define FGMAC_LPI_TIMER_CTRL_OFFSET 0x34U         /* LPI 定时器控制寄存器 */
#define FGMAC_INTR_STATUS_OFFSET 0x38U             /* 中断状态寄存器 */
#define FGMAC_INTR_MASK_OFFSET 0x3CU               /* 中断屏蔽寄存器 */
#define FGMAC_MAC_ADDR0_UPPER16BIT_OFFSET 0x40U   /* 第一个 MAC 地址的高 16 位。 */
#define FGMAC_MAC_ADDR0_LOWER32BIT_OFFSET 0x44U   /* 第一个 MAC 地址的低 32 位。。 */
#define FGMAC_MAC_ADDR1_UPPER16BIT_OFFSET 0x48U   /* 第二个 MAC 地址的高 16 位。 */
#define FGMAC_MAC_ADDR1_LOWER32BIT_OFFSET 0x4CU   /* 第二个 MAC 地址的低 32 位。。 */
#define FGMAC_MAC_PHY_STATUS 0xD8U                /* MAC PHY 状态 */

/**** FGMAC DMA CTRL ****/
#define FGMAC_DMA_BUS_MODE_OFFSET 0x1000U           /* 总线模式寄存器 */
#define FGMAC_DMA_TX_POLL_REQ_OFFSET 0x1004U        /* 发送轮询请求寄存器 */
#define FGMAC_DMA_RX_POLL_REQ_OFFSET 0x1008U        /* 接收轮询请求寄存器 */
#define FGMAC_DMA_RX_LIST_BASE_OFFSET 0x100cU       /* 接收描述符列表地址寄存器 */
#define FGMAC_DMA_TX_LIST_BASE_OFFSET 0x1010U       /* 发送描述符列表地址寄存器 */
#define FGMAC_DMA_STATUS_OFFSET 0x1014U             /* 状态寄存器 */
#define FGMAC_DMA_OP_OFFSET 0x1018U                 /* 操作模式寄存器 */
#define FGMAC_DMA_INTR_OFFSET 0x101cU            /* 中断使能寄存器 */
#define FGMAC_DMA_MISSED_FRAME_CNT_OFFSET 0x1020U   /* 丢帧和缓冲区溢出计数器寄存器 */
#define FGMAC_DMA_RX_WATCHDOG_OFFSET 0x1024U        /* 接收中断看门狗定时器寄存器 */
#define FGMAC_DMA_AXI_BUS_MOD_OFFSET 0x1028U        /* AXI 总线模式寄存器*/
#define FGMAC_DMA_AXI_BUS_STATUS_OFFSET 0x102CU     /* AXI 状态寄存器 */
#define FGMAC_DMA_HOST_TX_DESC_OFFSET 0x1048U       /* 当前主机发送描述符寄存器 */
#define FGMAC_DMA_HOST_RX_DESC_OFFSET 0x104CU       /* 当前主机接收描述符寄存器 */
#define FGMAC_DMA_HOST_TX_BUF_ADDR_OFFSET 0x1050U   /* 当前主机发送缓冲地址寄存器 */
#define FGMAC_DMA_HOST_RX_BUF_ADDR_OFFSET 0x1054U   /* 当前主机接收缓冲地址寄存器 */
#define FGMAC_DMA_HW_FUNC_OFFSET   0x1058U          /* 硬件功能寄存器 */

/** @name FGMAC_CONF_OFFSET Register
 */
#define FGMAC_CONF_RX_EN               BIT(2) /* 接收器启用 */
#define FGMAC_CONF_TX_EN               BIT(3) /* 发送器启用 */
#define FGMAC_CONF_DC               BIT(4) /* 延期检查 */
#define FGMAC_CONF_BL_MASK          GENMASK(6, 5) /* 后退限制 */
#define FGMAC_CONF_BL(x)            (FGMAC_CONF_BL_MASK & ((x) << 5))
#define FGMAC_CONF_ACS              BIT(7) /* 自动 PAD/ CRC 剥线 */
#define FGMAC_CONF_LINK_UPDOWN      BIT(8) /* 链接 up/down */
#define FGMAC_CONF_DISABLE_RETRY    BIT(9) /* 禁用重试 */
#define FGMAC_CONF_IPC              BIT(10) /* 校验和卸载 */
#define FGMAC_CONF_DUPLEX_MODE      BIT(11) /* 双工模式 */
#define FGMAC_CONF_LOOPBACK_MODE    BIT(12) /* 环回模式 */
#define FGMAC_CONF_DO               BIT(13) /* 不能自接收 */
#define FGMAC_CONF_FES              BIT(14) /* 速度选择 0: 10Mbps, 1: 100Mbps  d2000 ft2004手册有误*/
#define FGMAC_CONF_PORTSELECT       BIT(15) /* 端口选择 0: GMII（1000Mbps）1: MII(10/100Mbps) */
#define FGMAC_CONF_DCRS             BIT(16) /* 传输过程中禁用载波侦听 */
#define FGMAC_CONF_IFG_MASK         GENMASK(19, 17) /* 帧内间隔 */
#define FGMAC_CONF_IFG(x)           (FGMAC_CONF_IFG_MASK & ((x) << 17))
#define FGMAC_CONF_JE               BIT(20) /* 使用Jumbo帧 */
#define FGMAC_CONF_BE               BIT(21) /* 帧突发启用 */
#define FGMAC_CONF_JD               BIT(22) /* Jabber 禁用 */
#define FGMAC_CONF_WD               BIT(23) /* 看门狗禁用 */
#define FGMAC_CONF_TC               BIT(24) /* 在 RGMII 中传输配置 */
#define FGMAC_CONF_CST              BIT(25) /* 类型帧的 CRC 剥离 */

/* 使能类型帧的CRC剥离、禁用看门狗WD、禁用Jabber JD、帧突发启用BE、不能自接收DO(全双工保留)*/
#define FGMAC_CONF_INIT  (FGMAC_CONF_CST| FGMAC_CONF_WD| FGMAC_CONF_JD| FGMAC_CONF_BE| FGMAC_CONF_DO)

/** @name FGMAC_FRAME_FILTER_OFFSET Register
 */
#define FGMAC_FRAME_FILTER_PR           BIT(0)
#define FGMAC_FRAME_FILTER_HUC          BIT(1)  /* 哈希单播 */
#define FGMAC_FRAME_FILTER_HMC          BIT(2)  /* 哈希多播 */
#define FGMAC_FRAME_FILTER_DAIF         BIT(3)  /* 目的地址反向过滤 */
#define FGMAC_FRAME_FILTER_PM           BIT(4)  /* 通过所有多播 */
#define FGMAC_FRAME_FILTER_DBF          BIT(5)  /* 禁用广播帧 */
#define FGMAC_FRAME_FILTER_PCF_MASK     (GENMASK(7, 6))  /* 通过控制帧 */
#define FGMAC_FRAME_FILTER_PCF(x)       ((x) << 6)
#define FGMAC_FRAME_FILTER_SAIF         BIT(8)   /* 源地址反相过滤 */
#define FGMAC_FRAME_FILTER_SAF          BIT(9)   /* 源地址过滤使能 */
#define FGMAC_FRAME_FILTER_HPF          BIT(10)  /* hash 或 perfect 过滤器 */
#define FGMAC_FRAME_FILTER_RA           BIT(31)  /* 全部接收 */

/** @name FGMAC_HASH_HIGH_OFFSET Register
 */
#define FGMAC_HASH_HIGH_HTH_MASK        GENMASK(31, 0) /* 该字段包含 Hash 表的高 32 位。 */

/** @name FGMAC_HASH_LOW_OFFSET Register
 */
#define FGMAC_HASH_LOW_HTH_MASK         GENMASK(31, 0) /* 该字段包含 Hash 表的低 32 位。 */

/** @name FGMAC_GMII_ADDR_OFFSET Register
 */
#define FGMAC_MII_ADDR_GB               BIT(0) /* GMII 忙 */
#define FGMAC_MII_ADDR_GW               BIT(1) /* GMII 写 */
#define FGMAC_MII_ADDR_CR_MASK          GENMASK(5, 2) /* CSR 时钟范围 */
#define FGMAC_MII_ADDR_CR(x)            (FGMAC_MII_ADDR_CR_MASK & ((x) << 2))
#define FGMAC_MII_ADDR_GR_MASK          GENMASK(10, 6) /* GMII 寄存器 */
#define FGMAC_MII_ADDR_GR(x)            (FGMAC_MII_ADDR_GR_MASK & ((x) << 6))
#define FGMAC_MII_ADDR_PA_MASK          GENMASK(15, 11) /* 物理层地址 */
#define FGMAC_MII_ADDR_PA(x)            (FGMAC_MII_ADDR_PA_MASK & ((x) << 11))

/** @name FGMAC_GMII_DATA_OFFSET Register
 */
#define FGMAC_MII_DATA_GD_MASK          GENMASK(15, 0)

/** @name FGMAC_FLOW_CTRL_OFFSET Register
 */
#define FGMAC_FLOW_FCB                  BIT(0)
#define FGMAC_FLOW_BPA                  BIT(0)
#define FGMAC_FLOW_TFE                  BIT(1)
#define FGMAC_FLOW_RFE                  BIT(2) /* 接收流控制启用 */
#define FGMAC_FLOW_UP                   BIT(3) /* 单播暂停帧检测 */
#define FGMAC_FLOW_PLT_MASK             GENMASK(5, 4) /* 暂停低阈值 */
#define FGMAC_FLOW_PLT(x)               ((x) << 3)
#define FGMAC_FLOW_DZPQ                 BIT(7)
#define FGMAC_FLOW_PT_MASK              GENMASK(31, 16) /* 暂停时间 */

/** @name FGMAC_VLAN_TAG_OFFSET Register
 */
#define FGMAC_VLAN_TAG_VL_MASK          GENMASK(15, 0) /* 启用 12 位 VLAN 标记比较 */
#define FGMAC_VLAN_TAG_VL(x)            (FGMAC_VLAN_TAG_VL_MASK & ((x) << 15))
#define FGMAC_VLAN_TAG_ETV              BIT(16) /* 接收帧的 VLAN 标记标识符 */

/** @name FGMAC_VERSION_OFFSET Register
 */
#define FGMAC_VERSION_UDV_MASK          GENMASK(15, 8) /* 用户定义版本号 */
#define FGMAC_VERSION_SDV_MASK          GENMASK(7, 0) /* 硬件定议版本号 */

/** @name FGMAC_LPI_CTRL_STATUS_OFFSET Register
 */
#define FGMAC_LPI_CTRL_STATS_TLPIEN      BIT(0) /* 发送 LPI 进入 */
#define FGMAC_LPI_CTRL_STATS_TLPIEX      BIT(1) /* 发送 LPI 退出 */
#define FGMAC_LPI_CTRL_STATS_RLPIEN      BIT(2) /* 接收 LPI 进入 */
#define FGMAC_LPI_CTRL_STATS_RLPIEX      BIT(3) /* 接收 LPI 退出 */
#define FGMAC_LPI_CTRL_STATS_TLPIST      BIT(8) /* 发送 LPI 状态 */
#define FGMAC_LPI_CTRL_STATS_RLPIST      BIT(9)  /* 接收 LPI 状态 */
#define FGMAC_LPI_CTRL_STATS_LPIEN       BIT(16) /* LPI 使能 */
#define FGMAC_LPI_CTRL_STATS_PLS         BIT(17) /* PHY 链路状态 */
#define FGMAC_LPI_CTRL_STATS_PLSEN       BIT(18) /* 物理链路状态使能 */
#define FGMAC_LPI_CTRL_STATS_LPITXA      BIT(19) /* LPI 发送自动化 */

/** @name FGMAC_LPI_TIMER_CTRL_OFFSET Register
 */
#define FGMAC_LPI_TIMER_TWT_MASK        GENMASK(15, 0)
#define FGMAC_LPI_TIMER_LIT_MASK        GENMASK(25, 16)

/** @name FGMAC_INTR_STATUS_OFFSET Register
 */
#define FGMAC_ISR_STATUS_RSIS            BIT(0) /* RGMII/SMII Interrupt Status */
#define FGMAC_ISR_STATUS_PCSLSC          BIT(1) /* PCS 链路状态改变 */
#define FGMAC_ISR_STATUS_PCSANC          BIT(2) /* PCS 自协商完成 */
#define FGMAC_ISR_STATUS_PMTIS           BIT(3)
#define FGMAC_ISR_STATUS_MMCIS           BIT(4)
#define FGMAC_ISR_STATUS_MMCRIS          BIT(5)  /* MMC 接收中断状态 */
#define FGMAC_ISR_STATUS_MMCTIS          BIT(6)  /* MMC 发送中断状态 */
#define FGMAC_ISR_STATUS_MMCRCOIS        BIT(7)  /* 接收校验和卸载中断状态 */
#define FGMAC_ISR_STATUS_TIS             BIT(9)  /* 时间戳中断状态 */
#define FGMAC_ISR_STATUS_LPIIS           BIT(10) /* LPI 中断状态 */
#define FGMAC_ISR_STATUS_ALL_MASK        GENMASK(10, 0)

/** @name FGMAC_INTR_MASK_OFFSET Register
 */
#define FGMAC_ISR_MASK_RSIM             BIT(0) /* RGMII/SMII 中断屏蔽 */
#define FGMAC_ISR_MASK_PCSLSIM          BIT(1) /* PCS 链路状态中断屏蔽 */
#define FGMAC_ISR_MASK_PCSANCIM         BIT(2) /* PCS AN 完成中断屏蔽 */
#define FGMAC_ISR_MASK_PMTIM            BIT(3) /* PMT 中断屏蔽 */
#define FGMAC_ISR_MASK_TIM              BIT(9) /* 时间戳中断屏蔽 */
#define FGMAC_ISR_MASK_LPIIM            BIT(10) /* LPI 中断屏蔽 */
#define FGMAC_ISR_MASK_ALL_BITS         (GENMASK(3, 0) | GENMASK(10, 9))

#define FGMAC_8BIT_ADDR                 GENMASK(7, 0)

/** @name FGMAC_MAC_ADDR0_UPPER16BIT_OFFSET Register
 */
#define FGMAC_MAC_ADDR0_UPPER16BIT_A    GENMASK(15, 0) /* MAC 地址 0[47:32] */

/** @name FGMAC_MAC_ADDR0_LOWER32BIT_OFFSET Register
 */
#define FGMAC_MAC_ADDR0_LOWER32BIT_A  GENMASK(31, 0) /* MAC 地址 0[31:0] */

/** @name FGMAC_MAC_ADDR1_UPPER16BIT_OFFSET Register
 */
#define FGMAC_MAC_ADDR1_UPPER16BIT_A    GENMASK(15, 0) /* MAC 地址 1[47:32] */
#define FGMAC_MAC_ADDR1_UPPER16BIT_MBC  GENMASK(29, 24)
#define FGMAC_MAC_ADDR1_UPPER16BIT_SA   BIT(30)
#define FGMAC_MAC_ADDR1_UPPER16BIT_AE   BIT(31)

/** @name FGMAC_MAC_ADDR1_LOWER32BIT_OFFSET Register
 */
#define FGMAC_MAC_ADDR1_LOWER16BIT_A   GENMASK(31, 0) /* MAC 地址 1[31:0] */

/** @name FGMAC_MAC_PHY_STATUS Register
 */
#define FGMAC_RGSMIIIS_LNKMODE      BIT(0) /* 指示链路的当前操作模式 */
#define FGMAC_RGSMIIIS_LNKMODE_HALF  (0b0 << 0)
#define FGMAC_RGSMIIIS_LNKMODE_FULL  (0b1 << 0)
#define FGMAC_RGSMIIIS_SPEED         GENMASK(2, 1)
#define FGMAC_RGSMIIIS_SPEED_2_5MHZ  (0b00 << 1) /*  链路速度 2.5MHz */
#define FGMAC_RGSMIIIS_SPEED_25MHZ   (0b01 << 1) /*  25MHz */
#define FGMAC_RGSMIIIS_SPEED_125MHZ  (0b10 << 1) /*  125MHz */
#define FGMAC_RGSMIIIS_LNKSTS       BIT(3)
#define FGMAC_RGSMIIIS_LNKSTS_UP     (0b1 << 3)
#define FGMAC_RGSMIIIS_LNKSTS_DOWN   (0b0 << 3)
#define FGMAC_RGSMIIIS_JAB_TIMEOUT   BIT(4)
#define FGMAC_RGSMIIIS_FALSECARDET  BIT(5)

/****************FGMAC DMA Register*******************/
/* Bus mode register definitions */
/** @name FGMAC_DMA_BUS_MODE_OFFSET Register
 */
#define FGMAC_DMA_BUS_SWR           BIT(0) /* 软件复位 */
#define FGMAC_DMA_BUS_DA            BIT(1) /* 设置 8xPBL 模式 */
#define FGMAC_DMA_BUS_DSL_MASK      GENMASK(6, 2) /* 描述符跳跃长度 */
#define FGMAC_DMA_BUS_ATDS          BIT(7) /* 
#define FGMAC_DMA_BUS_PBL_MASK      GENMASK(13, 8) /* 可编程突发长度 */
#define FGMAC_DMA_BUS_PBL(x)        ((x) << 8)
enum
{
    FGMAC_DMA_BUS_PBL_1  = 1,
    FGMAC_DMA_BUS_PBL_2  = 2,
    FGMAC_DMA_BUS_PBL_4  = 4,
    FGMAC_DMA_BUS_PBL_8  = 8,
    FGMAC_DMA_BUS_PBL_16  = 16,
    FGMAC_DMA_BUS_PBL_32  = 32
};
#define FGMAC_DMA_BUS_PR_MASK GENMASK(15, 14) /* 加权循环仲裁中的优先级比率 */
#define FGMAC_DMA_BUS_PR(x)          ((x) << 14)
#define FGMAC_DMA_BUS_FB            BIT(16) /* 固定突发 */
#define FGMAC_DMA_BUS_RPBL_MASK     GENMASK(22, 17) /* RxDMA 事务中要传输的最大节拍数 */
#define FGMAC_DMA_BUS_RPBL(x)        ((x) << 17)
enum
{
    FGMAC_DMA_BUS_RPBL_1  = 1,
    FGMAC_DMA_BUS_RPBL_2  = 2,
    FGMAC_DMA_BUS_RPBL_4  = 4,
    FGMAC_DMA_BUS_RPBL_16  = 16,
    FGMAC_DMA_BUS_RPBL_32  = 32
};
#define FGMAC_DMA_BUS_USP           BIT(23)
#define FGMAC_DMA_BUS_8XPBL         BIT(24)
#define FGMAC_DMA_BUS_AAL           BIT(25)
#define FGMAC_DMA_BUS_MB            BIT(26) /* 混合突发 */
#define FGMAC_DMA_BUS_TXPR          BIT(27) /* 发送优先级 */
#define FGMAC_DMA_BUS_PRWG          GENMASK(29, 18) /* 通道优先权重 */

#define FGMAC_DMA_BUS_INIT          (FGMAC_DMA_BUS_FB | FGMAC_DMA_BUS_PBL(16) | FGMAC_DMA_BUS_RPBL(16))

/* 这些位控制 RxDMA 和 TxDMA 之间的加权循环仲裁中的优先级比率,
   FGMAC_DMA_BUS_DA=1时有效 */
#define FGMAC_DMA_BUS_PRIORXTX_41       (3 << 14) /* 4:1 */
#define FGMAC_DMA_BUS_PRIORXTX_31       (2 << 14) /* 3:1 */
#define FGMAC_DMA_BUS_PRIORXTX_21       (1 << 14) /* 2:1 */
#define FGMAC_DMA_BUS_PRIORXTX_11       (0 << 14) /* 1:1 */

/** @name FGMAC_DMA_TX_POLL_REQ_OFFSET Register
 */
#define FGMAC_DMA_XMT_POLL_DEMAND_TPD GENMASK(31, 0)

/** @name FGMAC_DMA_RX_POLL_REQ_OFFSET Register
 */
#define FGMAC_DMA_RCV_POLL_DEMAND_RPD GENMASK(31, 0)

/** @name FGMAC_DMA_RX_LIST_BASE_OFFSET Register
 */
#define FGMAC_DMA_RCV_BASE_ADDR_START_REC_LIST GENMASK(31, 4)

/** @name FGMAC_DMA_TX_LIST_BASE_OFFSET Register
 */
#define FGMAC_DMA_TX_BASE_ADDR_START_TRA_LIST GENMASK(31, 4)

/** @name FGMAC_DMA_STATUS_OFFSET Register
 */
#define FGMAC_DMA_STATUS_GLPII               BIT(30)   /* FGMAC LPI interrupt */
#define FGMAC_DMA_STATUS_TTI                 BIT(29)   /* 时间戳触发中断 */
#define FGMAC_DMA_STATUS_GPI                 BIT(28)   /* PMT interrupt */
#define FGMAC_DMA_STATUS_GMI                 BIT(27)  /* MMC interrupt */
#define FGMAC_DMA_STATUS_GLI                 BIT(26)  /* FGMAC Line interface int */
#define FGMAC_DMA_STATUS_EB_MASK             GENMASK(25, 23)     /* Error Bits Mask */
#define FGMAC_DMA_STATUS_TS_MASK             GENMASK(22, 20)     /* Transmit Process State */
#define FGMAC_DMA_STATUS_TS_STOPPED          (0b000 << 20)
#define FGMAC_DMA_STATUS_TS_GET_DESC         (0b001 << 20)
#define FGMAC_DMA_STATUS_TS_WAIT             (0b010 << 20)
#define FGMAC_DMA_STATUS_TS_QUEUE            (0b011 << 20)
#define FGMAC_DMA_STATUS_TS_PAUSE            (0b110 << 20)
#define FGMAC_DMA_STATUS_TS_CLOSE_DESC       (0b111 << 20)
#define FGMAC_DMA_STATUS_RS_MASK             GENMASK(19, 17) /* Receive Process State */
#define FGMAC_DMA_STATUS_NIS                 BIT(16)         /* Normal Interrupt Summary */
#define FGMAC_DMA_STATUS_AIS                 BIT(15)         /* Abnormal Interrupt Summary */
#define FGMAC_DMA_STATUS_ERI                 BIT(14)         /* Early Receive Interrupt */
#define FGMAC_DMA_STATUS_FBI                 BIT(13)         /* Fatal Bus Error Interrupt */
#define FGMAC_DMA_STATUS_ETI                 BIT(10)         /* Early Transmit Interrupt */
#define FGMAC_DMA_STATUS_RWT                 BIT(9)         /* Receive Watchdog Timeout */
#define FGMAC_DMA_STATUS_RPS                 BIT(8)         /* Receive Process Stopped */
#define FGMAC_DMA_STATUS_RU                  BIT(7)          /* Receive Buffer Unavailable */
#define FGMAC_DMA_STATUS_RI                  BIT(6)          /* Receive Interrupt */
#define FGMAC_DMA_STATUS_UNF                 BIT(5)         /* Transmit Underflow */
#define FGMAC_DMA_STATUS_OVF                 BIT(4)         /* Receive Overflow */
#define FGMAC_DMA_STATUS_TJT                 BIT(3)         /* Transmit Jabber Timeout */
#define FGMAC_DMA_STATUS_TU                  BIT(2)          /* Transmit Buffer Unavailable */
#define FGMAC_DMA_STATUS_TPS                 BIT(1)         /* Transmit Process Stopped */
#define FGMAC_DMA_STATUS_TI                  BIT(0)          /* Transmit Interrupt */

#define FGMAC_DMA_STATUS_CLR_ABLE            (GENMASK(5, 0) | GENMASK(10, 7)| FGMAC_DMA_STATUS_FBI | FGMAC_DMA_STATUS_AIS)  /* BIT [16 : 0] write 1 to clear */

/** @name FGMAC_DMA_OP_OFFSET Register
 */
#define FGMAC_DMA_OP_DT                      BIT(26)    /* No Dropping of TCP/IP csum Err Frame */
#define FGMAC_DMA_OP_RSF                     BIT(25)    /* Rx Store and Forward */
#define FGMAC_DMA_OP_DFF                     BIT(24)    /*   */
#define FGMAC_DMA_OP_RFA_2                   BIT(23)
#define FGMAC_DMA_OP_RFD_2                   BIT(22)
#define FGMAC_DMA_OP_TSF                     BIT(21)   /* Tx Store and Forward */
#define FGMAC_DMA_OP_FTF                     BIT(20)   /* Flush Tx FIFO */
#define FGMAC_DMA_OP_TTC_MASK                GENMASK(16, 14)
#define FGMAC_DMA_OP_TTC(x)                  ((x) << 14)   /* Tx Threshold Control */
enum
{
    FGMAC_DMA_OP_TTC_64 = 0b000,
    FGMAC_DMA_OP_TTC_128 = 0b001,
    FGMAC_DMA_OP_TTC_192 = 0b010,
    FGMAC_DMA_OP_TTC_256 = 0b011,
    FGMAC_DMA_OP_TTC_40  = 0b100,
    FGMAC_DMA_OP_TTC_32  = 0b101,
    FGMAC_DMA_OP_TTC_24  = 0b110,
    FGMAC_DMA_OP_TTC_16  = 0b111
};

#define FGMAC_DMA_OP_ST                      BIT(13)   /* Start/Stop Tx */
#define FGMAC_DMA_OP_RFD_MASK                GENMASK(12, 11)
#define FGMAC_DMA_OP_RFD(x)                  ((x) << 11) /* Threshold for DeActive Flow Control */
#define FGMAC_DMA_OP_RFA_MASK                GENMASK(10, 9) /* Threshold for Active Flow Control */
#define FGMAC_DMA_OP_EFC                     BIT(8)  /* Enable HW Flow control */
#define FGMAC_DMA_OP_FEF                     BIT(7)  /* Forward Error Frame */
#define FGMAC_DMA_OP_FUF                     BIT(6)  /* Forward Undersize Good Frame */
#define FGMAC_DMA_OP_RTC_MASK                GENMASK(4, 3)  /* Rx Threshold Control */
#define FGMAC_DMA_OP_OSF                     BIT(2)  /* Operate On Second Mode */
#define FGMAC_DMA_OP_SR                      BIT(1)  /* Start/Stop Rx */
#define FGMAC_DMA_OP_CLEAR_MASK              GENMASK(31, 0)
#define FGMAC_DMA_OP_INIT                    (FGMAC_DMA_OP_SR | FGMAC_DMA_OP_RSF)

/** @name FGMAC_DMA_INTR_OFFSET Register
 */
#define FGMAC_DMA_INTR_ENA_TIE               BIT(0) /* Transmit Interrupt */
#define FGMAC_DMA_INTR_ENA_TSE               BIT(1) /* 传输停止启用 */
#define FGMAC_DMA_INTR_ENA_TUE               BIT(2) /* Transmit Buffer Unavailable */
#define FGMAC_DMA_INTR_ENA_THE               BIT(3) /* 发送 Jabber 超时启用 */
#define FGMAC_DMA_INTR_ENA_OVE               BIT(4) /* 溢出中断使能 */
#define FGMAC_DMA_INTR_ENA_UNE               BIT(5) /* 下溢中断使能 */
#define FGMAC_DMA_INTR_ENA_RIE               BIT(6) /* Receive Interrupt */
#define FGMAC_DMA_INTR_ENA_RUE               BIT(7) /* 接收缓冲区不可用启用 */
#define FGMAC_DMA_INTR_ENA_RSE               BIT(8) /* 接收已停止启用 */
#define FGMAC_DMA_INTR_ENA_RWE               BIT(9) /* 接收看门狗超时使能  */
#define FGMAC_DMA_INTR_ENA_ETE               BIT(10) /* 早期发送中断使能  */
#define FGMAC_DMA_INTR_ENA_FBE               BIT(13) /* Fatal Bus Error */
#define FGMAC_DMA_INTR_ENA_ERE               BIT(14) /* Early Receive */
#define FGMAC_DMA_INTR_ENA_AIE               BIT(15) /* Abnormal Summary */
#define FGMAC_DMA_INTR_ENA_NIE               BIT(16) /* Normal Summary */
#define FGMAC_DMA_INTR_ENA_ALL_MASK          (GENMASK(10, 0) | GENMASK(16, 13))

/** @name FGMAC_DMA_MISSED_FRAME_CNT_OFFSET Register
 */
#define FGMAC_DMA_MISSED_FRAME_CTR_CMIS           GENMASK(15, 0) /* 由于主机接收缓冲区不可用而导致控制器丢失的帧数 */
#define FGMAC_DMA_MISSED_FRAME_CTR_OVMIS          BIT(16)
#define FGMAC_DMA_MISSED_FRAME_CTR_CFIFO          GENMASK(27, 17)
#define FGMAC_DMA_MISSED_FRAME_CTR_OVFIFO         BIT(28)

/** @name FGMAC_DMA_RX_WATCHDOG_OFFSET Register
 */
#define FGMAC_DMA_RX_WATCHDOG_RIWT                GENMASK(7, 0)

/** @name FGMAC_DMA_AXI_BUS_MOD_OFFSET Register
 */
#define FGMAC_DMA_AXI_BUS_MOD_UNDEF               BIT(0)  /* AXI 未定义的突发长度 */
#define FGMAC_DMA_AXI_BUS_MOD_BLEN4               BIT(1)  /* AXI 突发长度 4 */
#define FGMAC_DMA_AXI_BUS_MOD_BLEN8               BIT(2)  /* AXI 突发长度 8 */
#define FGMAC_DMA_AXI_BUS_MOD_BLEN16              BIT(3)  /* AXI 突发长度 16 */
#define FGMAC_DMA_AXI_BUS_MOD_BLEN32              BIT(4)  /* AXI 突发长度 32 */
#define FGMAC_DMA_AXI_BUS_MOD_BLEN64              BIT(5)  /* AXI 突发长度 64 */
#define FGMAC_DMA_AXI_BUS_MOD_BLEN128             BIT(6)  /* AXI 突发长度 128 */
#define FGMAC_DMA_AXI_BUS_MOD_BLEN256             BIT(7)  /* AXI 突发长度 256 */
#define FGMAC_DMA_AXI_BUS_MOD_AXI_AAL             BIT(12) /* 地址对齐的节拍 */
#define FGMAC_DMA_AXI_BUS_MOD_RD_OSR_LMT_MASK     GENMASK(19, 16)
#define FGMAC_DMA_AXI_BUS_MOD_RD_OSR_LMT(x)       ((x) << 16) /* XI 最大读取未决请求限制此值限 制 AXI 读取接口上的最大未完成请求。 */
#define FGMAC_DMA_AXI_BUS_MOD_WR_OSR_LMT_MASK     GENMASK(23, 20)
#define FGMAC_DMA_AXI_BUS_MOD_WR_OSR_LMT(x)       ((x) << 20) /* AXI 最大写入未决请求限制此值 限制 AXI 写入接口上的最大未完成请求。 */
#define FGMAC_DMA_AXI_BUS_MOD_UNLCK_ON_MGK_RWK    BIT(30)
#define FGMAC_DMA_AXI_BUS_MOD_EN_LPI              BIT(31)

#define FGMAC_DMA_DESC_ADDR_MASK                  GENMASK(31, 4)

#define FGMAC_MAC_ADDR_LEN                        6
#define FGMAC_RETRY_TIMES                         500
#define FGMAC_DELAY_US                            100
/**************************** Type Definitions *******************************/

typedef u8 FGmacMacAddr[FGMAC_MAC_ADDR_LEN];

enum
{
    FGMAC_CTRL_INTR = 0,
    FGMAC_DMA_INTR,

    FGMAC_MAX_INTR_TYPE
};

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
/* 读FGMAC控制器寄存器，以u32返回整个寄存器值 */
#define FGMAC_READ_REG32(addr, reg_offset) FtIn32((addr) + (u32)(reg_offset))

/* 写FGMAC控制器寄存器，以u32覆盖写入整个寄存器值 */
#define FGMAC_WRITE_REG32(addr, reg_offset, reg_value) FtOut32((addr) + (u32)(reg_offset), (u32)(reg_value))

/* 将FGMAC控制器寄存器的特定位置为1, 不改变其它位 */
#define FGMAC_SET_REG32(addr, reg_offset, set_bits) FtSetBit32((addr) + (u32)(reg_offset), (u32)(set_bits))

/* 将FGMAC控制器寄存器的特定位置为0, 不改变其它位 */
#define FGMAC_CLR_REG32(addr, reg_offset, clr_bits) FtClearBit32((addr) + (u32)(reg_offset), (u32)(clr_bits))

/* 在一个总长度为num的环内将索引idx增加1 */
#define FGMAC_DMA_INC_DESC(idx, num)                  (idx) = (((idx) + 1) % (num))

static inline void FGmacResumeDmaSend(uintptr base_addr)
{
    if (FGMAC_READ_REG32(base_addr, FGMAC_DMA_STATUS_OFFSET) & FGMAC_DMA_STATUS_TU)
    {
        FGMAC_SET_REG32(base_addr, FGMAC_DMA_STATUS_OFFSET, FGMAC_DMA_STATUS_TU); /* clear TBUS GMAC DMA flag */
        FGMAC_WRITE_REG32(base_addr, FGMAC_DMA_TX_POLL_REQ_OFFSET, 0xff); /* resume DMA transmission */
    }
    else
    {
        FGMAC_WRITE_REG32(base_addr, FGMAC_DMA_TX_POLL_REQ_OFFSET, 0xff); /* resume DMA transmission */
    }
}

static inline void FGmacResumeDmaRecv(uintptr base_addr)
{
    if (FGMAC_READ_REG32(base_addr, FGMAC_DMA_STATUS_OFFSET) & FGMAC_DMA_STATUS_RU)
    {
        FGMAC_SET_REG32(base_addr, FGMAC_DMA_STATUS_OFFSET, FGMAC_DMA_STATUS_RU); /* Clear RBUS GMAC DMA flag */
        FGMAC_WRITE_REG32(base_addr, FGMAC_DMA_RX_POLL_REQ_OFFSET, 0xff); /* Resume DMA transmission*/
    }
    else
    {
        FGMAC_WRITE_REG32(base_addr, FGMAC_DMA_RX_POLL_REQ_OFFSET, 0xff);
    }
}

static inline void FGmacStartDmaTrans(uintptr base_addr)
{
    FGMAC_SET_REG32(base_addr, FGMAC_DMA_OP_OFFSET, (FGMAC_DMA_OP_SR | FGMAC_DMA_OP_ST));     /* enable dma tx and rx */
    FGMAC_SET_REG32(base_addr, FGMAC_CONF_OFFSET, (FGMAC_CONF_RX_EN | FGMAC_CONF_TX_EN)); /* enable gmac tx and rx */

    /* clear Tx and Rx process stopped flags */
    FGMAC_WRITE_REG32(base_addr, FGMAC_DMA_INTR_OFFSET,
                      (FGMAC_DMA_INTR_ENA_RIE | FGMAC_DMA_INTR_ENA_AIE | FGMAC_DMA_INTR_ENA_NIE));
}

static inline void FGmacStopDmaTrans(uintptr base_addr)
{
    FGMAC_CLR_REG32(base_addr, FGMAC_DMA_OP_OFFSET, (FGMAC_DMA_OP_SR | FGMAC_DMA_OP_ST)); /* disable dma tx and rx */
    FGMAC_CLR_REG32(base_addr, FGMAC_CONF_OFFSET, (FGMAC_CONF_RX_EN | FGMAC_CONF_TX_EN)); /* disable gmac tx and rx */
}

static inline void FGmacResmuDmaUnderflow(uintptr base_addr)
{
    if (FGMAC_DMA_STATUS_UNF & FGMAC_READ_REG32(base_addr, FGMAC_DMA_STATUS_OFFSET))
    {
        FGMAC_SET_REG32(base_addr, FGMAC_DMA_STATUS_OFFSET, FGMAC_DMA_STATUS_UNF);  /* clear TBUS GMAC DMA flag */
        FGMAC_WRITE_REG32(base_addr, FGMAC_DMA_TX_POLL_REQ_OFFSET, 0xff); /* resume DMA transmission*/
    }
}

/************************** Function Prototypes ******************************/
/* 获取FGMAC控制器配置的MAC地址 */
void FGmacGetMacAddr(uintptr base_addr, FGmacMacAddr mac_addr);

/* 设置FGMAC控制器的MAC地址 */
void FGmacSetMacAddr(uintptr base_addr, const FGmacMacAddr mac_addr);

/* 触发FGMAC控制器软件复位 */
FError FGmacSoftwareReset(uintptr base_addr, int timeout);

FError FGmacFlushTxFifo(uintptr base_addr, int timeout);

void FGmacStopDmaTrans(uintptr base_addr);

/* wait fgmac mii not busy */
FError FGmacPhyWaitBusBusy(uintptr base_addr, int timeout);

#ifdef __cplusplus
}
#endif

#endif