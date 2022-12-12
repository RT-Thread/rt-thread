/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-07 13:25:10
 * @Description:  This files is for gmac register
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef GMAC_HW_H
#define GMAC_HW_H
#include "ft_types.h"
#include "ft_gmac.h"
/* Register Offset */

#define GMAC_CONTROL_OFFSET 0x00000000U                /* Configuration */
#define GMAC_FRAME_FILTER_OFFSET 0x00000004U           /* Frame Filter */
#define GMAC_HASH_HIGH_OFFSET 0x00000008U              /* Multicast Hash Table High */
#define GMAC_HASH_LOW_OFFSET 0x0000000cU               /* Multicast Hash Table Low */
#define GMAC_MII_ADDR_OFFSET 0x00000010U               /* MII Address */
#define GMAC_MII_DATA_OFFSET 0x00000014U               /* MII Data */
#define GMAC_FLOW_CTRL_OFFSET 0x00000018U              /* Flow Control */
#define GMAC_VLAN_TAG_OFFSET 0x0000001cU               /* VLAN Tag */
#define GMAC_VERSION_OFFSET 0x00000020U                /* GMAC CORE Version */
#define GMAC_INTERNAL_MODULE_STATUS_OFFSET 0x00000024U /*  给出各种内部块的状态以进行调试。 */
#define GMAC_LPI_CONTROL_STATUS_OFFSET 0x00000030U     /* 控制低功耗空闲（LPI）操作并提供内核的 LPI 状态。 */
#define GMAC_LPI_TIMER_CONTROL_OFFSET 0x00000034U      /* 控制 LPI 状态中的超时值。 */
#define GMAC_ISR_STATUS_OFFSET 0x00000038U             /* 中断状态。 */
#define GMAC_ISR_MASK_OFFSET 0x0000003CU               /* 生成中断的掩码 */
#define GMAC_MAC_ADDR0_UPPER16BIT_OFFSET 0x00000040U   /* 第一个 MAC 地址的高 16 位。 */
#define GMAC_MAC_ADDR0_LOWER16BIT_OFFSET 0x00000044U   /* 第一个 MAC 地址的低 32 位。。 */
#define GMAC_MAC_ADDR1_UPPER16BIT_OFFSET 0x00000048U   /* 第二个 MAC 地址的高 16 位。 */
#define GMAC_MAC_ADDR1_LOWER16BIT_OFFSET 0x0000004CU   /* 第二个 MAC 地址的低 32 位。。 */
#define GMAC_MAC_MAC_PHY_STATUS 0x000000D8U            /* MAC PHY 状态 */

#define DMA_BUS_MODE_OFFSET 0x00001000U         /* Bus Mode */
#define DMA_XMT_POLL_DEMAND_OFFSET 0x00001004U  /* Transmit Poll Demand */
#define DMA_RCV_POLL_DEMAND_OFFSET 0x00001008U  /* Received Poll Demand */
#define DMA_RCV_BASE_ADDR_OFFSET 0x0000100cU    /* Receive List Base */
#define DMA_TX_BASE_ADDR_OFFSET 0x00001010U     /* Transmit List Base */
#define DMA_STATUS_OFFSET 0x00001014U           /* Status Register */
#define DMA_OP_OFFSET 0x00001018U               /* Ctrl (Operational Mode) */
#define DMA_INTR_ENA_OFFSET 0x0000101cU         /* Interrupt Enable */
#define DMA_MISSED_FRAME_CTR_OFFSET 0x00001020U /* Missed Frame Counter */
#define DMA_RX_WATCHDOG_OFFSET 0x1024U          /* Receive Interrupt Watchdog */
#define DMA_AXI_BUS_MOD_OFFSET 0x1028U          /* 控制 AXI 主行为 */
#define DMA_AXI_BUS_STATUS_OFFSET 0x102CU       /* 控制 AXI 状态 */

/* MMC control */
#define MMC_CNTRL 0x0100U        /* MMC Control */
#define MMC_RX_INTR 0x0104U      /* MMC RX Interrupt */
#define MMC_TX_INTR 0x0108U      /* MMC TX Interrupt */
#define MMC_RX_INTR_MASK 0x010cU /* MMC Interrupt Mask */
#define MMC_TX_INTR_MASK 0x0110U /* MMC Interrupt Mask */
#define MMC_RX_IPC_INTR_MASK 0x0200U
#define MMC_RX_IPC_INTR 0x0208U

/** MAC 配置寄存器 **/
#define GMAC_CONTROL_2K 0x08000000U /* IEEE 802.3as 2K packets */
#define GMAC_CONTROL_CST 0x2000000U
#define GMAC_CONTROL_TC 0x01000000U         /* Transmit Conf. in RGMII/SGMII */
#define GMAC_CONTROL_WD 0x00800000U         /* Disable Watchdog on receive */
#define GMAC_CONTROL_JD 0x00400000U         /* Jabber disable */
#define GMAC_CONTROL_BE 0x00200000U         /* Frame Burst Enable */
#define GMAC_CONTROL_JE 0x00100000U         /* Jumbo frame */
#define GMAC_CONTROL_IFG(x) ((x & 7) << 17) /* 帧内间隔 ,000 96bit times 001 88bit times 010 80bit times … 111 40bit times*/
#define GMAC_CONTROL_DCRS 0x00010000U       /* Disable carrier sense */
#define GMAC_CONTROL_PS 0x00008000U         /* Port Select 0:GMII 1:MII */
#define GMAC_CONTROL_FES 0x00004000U        /* Speed 0:10 1:100 */
#define GMAC_CONTROL_DO 0x00002000U         /* Disable Rx Own */
#define GMAC_CONTROL_LM 0x00001000U         /* Loop-back mode */
#define GMAC_CONTROL_DM 0x00000800U         /* Duplex Mode . 1 is Duplex */
#define GMAC_CONTROL_IPC 0x00000400U        /* Checksum Offload */
#define GMAC_CONTROL_DR 0x00000200U         /* Disable Retry */
#define GMAC_CONTROL_LUD 0x00000100U        /* Link up/down */
#define GMAC_CONTROL_ACS 0x00000080U        /* Auto Pad/FCS Stripping */
#define GMAC_CONTROL_BL(x) ((x & 3) << 5)
#define GMAC_CONTROL_DC 0x00000010U /* Deferral Check */
#define GMAC_CONTROL_TE 0x00000008U /* Transmitter Enable */
#define GMAC_CONTROL_RE 0x00000004U /* Receiver Enable */
#define GMAC_CONTROL_INIT (GMAC_CONTROL_DO | GMAC_CONTROL_JD | GMAC_CONTROL_ACS | GMAC_CONTROL_IPC | GMAC_CONTROL_BE | GMAC_CONTROL_DM | GMAC_CONTROL_WD | GMAC_CONTROL_CST)

/** Frame Filter **/
#define GMAC_FRAME_FILTER_PR 0x00000001U
#define GMAC_FRAME_FILTER_HUC 0x00000002U
#define GMAC_FRAME_FILTER_HMC 0x00000004U
#define GMAC_FRAME_FILTER_DAIF 0x00000008U
#define GMAC_FRAME_FILTER_PM 0x00000010U
#define GMAC_FRAME_FILTER_DBF 0x00000020U
#define GMAC_FRAME_FILTER_PCF(x) ((x & 3) << 6)
#define GMAC_FRAME_FILTER_SAIF 0x00000100U
#define GMAC_FRAME_FILTER_SAF 0x00000200U
#define GMAC_FRAME_FILTER_HPF 0x00000400U
#define GMAC_FRAME_FILTER_RA 0x80000000U

/**  哈希表高位寄存器 **/
#define GMAC_HASH_HIGH_HTH 0xffffffffUL /* 该字段包含 Hash 表的高 32 位。 */

/** 哈希表低位寄存器 **/
#define GMAC_HASH_LOW_HTH 0xffffffffUL /* 该字段包含 Hash 表的低 32 位。 */

/** GMII 地址寄存器  **/
#define GMAC_MII_ADDR_GB 0x00000001
#define GMAC_MII_ADDR_GW 0x00000002
#define GMAC_MII_ADDR_CR(x) ((x & 0xf) << 2)
#define GMAC_MII_ADDR_GR(x) ((x & 0x1f) << 6)
#define GMAC_MII_ADDR_PA(x) ((x & 0x1f) << 11)

/** GMII 数据寄存器  **/
#define GMAC_MII_DATA_GD 0x0000ffffU

/**  流控寄存器 **/
#define GMAC_FLOW_FCB 0x00000001U
#define GMAC_FLOW_BPA GMAC_FLOW_FCB
#define GMAC_FLOW_TFE 0x00000002U
#define GMAC_FLOW_RFE 0x00000004U
#define GMAC_FLOW_UP 0x00000008U
#define GMAC_FLOW_PLT(x) ((x & 3) << 3)
#define GMAC_FLOW_DZPQ 0x00000080U
#define GMAC_FLOW_PT 0xffff0000U

/** VLAN 标记寄存器 **/
// #define GMAC_VLAN_TAG_VL 0x0000ffffU
#define GMAC_VLAN_TAG_VL(x) (x & 0xffffU)
#define GMAC_VLAN_TAG_ETV 0x00010000U

/** 版本寄存器 **/
#define GMAC_VERSION_UDV 0x00FF0000U /* 用户定义版本号 */
#define GMAC_VERSION_SDV 0x000000ffU /* 硬件定议版本号 */

/** LPI 控制和状态寄存器 **/
#define GMAC_LPI_CONTROL_STATUS_TLPIEN 0x00000001U
#define GMAC_LPI_CONTROL_STATUS_TLPIEX 0x00000002U
#define GMAC_LPI_CONTROL_STATUS_RLPIEN 0x00000004U
#define GMAC_LPI_CONTROL_STATUS_RLPIEX 0x00000008U
#define GMAC_LPI_CONTROL_STATUS_TLPIST 0x00000100U
#define GMAC_LPI_CONTROL_STATUS_RLPIST 0x00000200U
#define GMAC_LPI_CONTROL_STATUS_LPIEN 0x00010000U
#define GMAC_LPI_CONTROL_STATUS_PLS 0x00020000U
#define GMAC_LPI_CONTROL_STATUS_PLSEN 0x00040000U
#define GMAC_LPI_CONTROL_STATUS_LPITXA 0x00080000U

/**  LPI 定时器控制寄存器 **/
#define GMAC_LPI_TIMER_TWT 0x0000ffffU
#define GMAC_LPI_TIMER_LIT 0x3FF0000U

/** 中断状态寄存器 **/
#define GMAC_ISR_STATUS_RSIS 0x00000001U
#define GMAC_ISR_STATUS_PCSLSC 0x00000002U
#define GMAC_ISR_STATUS_PCSANC 0x00000004U
#define GMAC_ISR_STATUS_PMTIS 0x00000008U
#define GMAC_ISR_STATUS_MMCIS 0x00000010U
#define GMAC_ISR_STATUS_MMCRIS 0x00000020U
#define GMAC_ISR_STATUS_MMCTIS 0x00000040U
#define GMAC_ISR_STATUS_MMCRCOIS 0x00000080U
#define GMAC_ISR_STATUS_TIS 0x00000200U
#define GMAC_ISR_STATUS_LPIIS 0x00000400U

/** 中断屏蔽寄存器  **/
#define GMAC_ISR_MASK_RSIM 0x00000001U /* RGMII/SMII 中断屏蔽 */
#define GMAC_ISR_MASK_PCSLSIM 0x00000002U
#define GMAC_ISR_MASK_PCSANCIM 0x00000004U
#define GMAC_ISR_MASK_PMTIM 0x00000008U
#define GMAC_ISR_MASK_TIM 0x00000020U
#define GMAC_ISR_MASK_LPIIM 0x00000040U

/**  MAC 地址 0 高寄存器 **/
#define GMAC_MAC_ADDR0_UPPER16BIT_A 0x0000ffffU

/** MAC 地址 0 低寄存器 **/
#define GMAC_MAC_ADDR0_LOWERER16BIT_A 0xffffffffU

/**  MAC 地址 1 高寄存器 **/
#define GMAC_MAC_ADDR1_UPPER16BIT_A 0x0000ffffU
#define GMAC_MAC_ADDR1_UPPER16BIT_MBC 0x3f000000U
#define GMAC_MAC_ADDR1_UPPER16BIT_SA 0x40000000U
#define GMAC_MAC_ADDR1_UPPER16BIT_AE 0x80000000U

/** MAC 地址 1 低寄存器 **/
#define GMAC_MAC_ADDR1_LOWER16BIT_A 0xffffffffU

/*  GMAC DMA 寄存器 */
/** 总线模式寄存器 **/
#define DMA_BUS_PRWG 0x030000000U
#define DMA_BUS_TXPR 0x08000000U
#define DMA_BUS_MB 0x04000000U
#define DMA_BUS_AAL 0x02000000U
#define DMA_BUS_8xPBL 0x01000000U
#define DMA_BUS_USP 0x00800000U
#define DMA_BUS_RPBL(x) ((x & 0x3f) << 17)
#define DMA_BUS_FB 0x00010000U          /* Fixed Burst */
#define DMA_BUS_PR(x) ((x & 0x3) << 14) /* 00: 1:1 ,01: 2:1 ,10: 3:1 ,11: 4:1 */
#define DMA_BUS_PBL(x) ((x & 0x3f) << 8)
#define DMA_BUS_ATDS 0x00000080U
#define DMA_BUS_DSL 0x0000007CU /* Descriptor Skip Length */
#define DMA_BUS_DA 0x00000002U  /* DMA Arbitration Scheme,Rx High Pro */
#define DMA_BUS_SWR 0x00000001U /* Software Reset */

#define DMA_BUS_INIT (DMA_BUS_FB | DMA_BUS_PBL(16) | DMA_BUS_RPBL(16))

/** 发送轮询请求寄存器 **/
#define DMA_XMT_POLL_DEMAND_TPD 0xffffffffU

/** 发送轮询请求寄存器 **/
#define DMA_RCV_POLL_DEMAND_RPD 0xffffffffU

/** 接收描述符列表地址寄存器  **/
#define DMA_RCV_BASE_ADDR_START_REC_LIST 0xfffffff0U

/** 发送描述符列表地址寄存器 **/
#define DMA_TX_BASE_ADDR_START_TRA_LIST 0xfffffff0U

/**
  * @brief  Bit definition of TDES0 register: DMA Tx descriptor status register
  */
#define BIT(bitnum) (1 << (bitnum % 32))
#define GENMASK(h, l) \
  (((~0UL) - (1UL << (l)) + 1) & (~0UL >> (32 - 1 - (h))))

#define DMA_TDES0_DEFERRED BIT(0)
#define DMA_TDES0_UNDERFLOW_ERROR BIT(1)
#define DMA_TDES0_EXCESSIVE_DEFERRAL BIT(2)
#define DMA_TDES0_COLLISION_COUNT_MASK GENMASK(6, 3)
#define DMA_TDES0_VLAN_FRAME BIT(7)
#define DMA_TDES0_EXCESSIVE_COLLISIONS BIT(8)
#define DMA_TDES0_LATE_COLLISION BIT(9)
#define DMA_TDES0_NO_CARRIER BIT(10)
#define DMA_TDES0_LOSS_CARRIER BIT(11)
#define DMA_TDES0_PAYLOAD_ERROR BIT(12)
#define DMA_TDES0_FRAME_FLUSHED BIT(13)
#define DMA_TDES0_JABBER_TIMEOUT BIT(14)
#define DMA_TDES0_ERROR_SUMMARY BIT(15)
#define DMA_TDES0_IP_HEADER_ERROR BIT(16)
#define DMA_TDES0_TIME_STAMP_STATUS BIT(17)
#define DMA_TDES0_OWN ((u32)BIT(31)) /* silence sparse */
/* TDES1 */
#define DMA_TDES1_BUFFER1_SIZE_MASK GENMASK(10, 0)
#define DMA_TDES1_BUFFER2_SIZE_MASK GENMASK(21, 11)
#define DMA_TDES1_BUFFER2_SIZE_SHIFT 11
#define DMA_TDES1_TIME_STAMP_ENABLE BIT(22)
#define DMA_TDES1_DISABLE_PADDING BIT(23)
#define DMA_TDES1_SECOND_ADDRESS_CHAINED BIT(24)
#define DMA_TDES1_END_RING BIT(25)
#define DMA_TDES1_CRC_DISABLE BIT(26)
#define DMA_TDES1_CHECKSUM_INSERTION_MASK GENMASK(28, 27)
#define DMA_TDES1_CHECKSUM_INSERTION_SHIFT 27
#define DMA_TDES1_FIRST_SEGMENT BIT(29)
#define DMA_TDES1_LAST_SEGMENT BIT(30)
#define DMA_TDES1_INTERRUPT BIT(31)

/*  Bit definition of RDES0 register: DMA Rx descriptor status register */
/* RDES0 */
#define DMA_RDES0_PAYLOAD_CSUM_ERR BIT(0)
#define DMA_RDES0_CRC_ERROR BIT(1)
#define DMA_RDES0_DRIBBLING BIT(2)
#define DMA_RDES0_MII_ERROR BIT(3)
#define DMA_RDES0_RECEIVE_WATCHDOG BIT(4)
#define DMA_RDES0_FRAME_TYPE BIT(5)
#define DMA_RDES0_COLLISION BIT(6)
#define DMA_RDES0_IPC_CSUM_ERROR BIT(7)
#define DMA_RDES0_LAST_DESCRIPTOR BIT(8)
#define DMA_RDES0_FIRST_DESCRIPTOR BIT(9)
#define DMA_RDES0_VLAN_TAG BIT(10)
#define DMA_RDES0_OVERFLOW_ERROR BIT(11)
#define DMA_RDES0_LENGTH_ERROR BIT(12)
#define DMA_RDES0_SA_FILTER_FAIL BIT(13)
#define DMA_RDES0_DESCRIPTOR_ERROR BIT(14)
#define DMA_RDES0_ERROR_SUMMARY BIT(15)
#define DMA_RDES0_FRAME_LEN_MASK (0x3FFF << 16) /*GENMASK(29, 16)*/
#define DMA_RDES0_FRAME_LEN_SHIFT 16
#define DMA_RDES0_DA_FILTER_FAIL BIT(30)
#define DMA_RDES0_OWN BIT(31)
/* RDES1 */
#define DMA_RDES1_BUFFER1_SIZE_MASK GENMASK(10, 0)
#define DMA_RDES1_BUFFER2_SIZE_MASK GENMASK(21, 11)
#define DMA_RDES1_BUFFER2_SIZE_SHIFT 11
#define DMA_RDES1_SECOND_ADDRESS_CHAINED BIT(24)
#define DMA_RDES1_END_RING BIT(25)
#define DMA_RDES1_DISABLE_IC BIT(31)

/** DMA Status register defines **/
#define DMA_STATUS_GLPII 0x40000000       /* GMAC LPI interrupt */
#define DMA_STATUS_GPI 0x10000000         /* PMT interrupt */
#define DMA_STATUS_GMI 0x08000000         /* MMC interrupt */
#define DMA_STATUS_GLI 0x04000000         /* GMAC Line interface int */
#define DMA_STATUS_EB_MASK 0x00380000     /* Error Bits Mask */
#define DMA_STATUS_EB_TX_ABORT 0x00080000 /* Error Bits - TX Abort */
#define DMA_STATUS_EB_RX_ABORT 0x00100000 /* Error Bits - RX Abort */
#define DMA_STATUS_TS_MASK 0x00700000     /* Transmit Process State */
#define DMA_STATUS_RS_MASK 0x000e0000     /* Receive Process State */
#define DMA_STATUS_NIS 0x00010000         /* Normal Interrupt Summary */
#define DMA_STATUS_AIS 0x00008000         /* Abnormal Interrupt Summary */
#define DMA_STATUS_ERI 0x00004000         /* Early Receive Interrupt */
#define DMA_STATUS_FBI 0x00002000         /* Fatal Bus Error Interrupt */
#define DMA_STATUS_ETI 0x00000400         /* Early Transmit Interrupt */
#define DMA_STATUS_RWT 0x00000200         /* Receive Watchdog Timeout */
#define DMA_STATUS_RPS 0x00000100         /* Receive Process Stopped */
#define DMA_STATUS_RU 0x00000080          /* Receive Buffer Unavailable */
#define DMA_STATUS_RI 0x00000040          /* Receive Interrupt */
#define DMA_STATUS_UNF 0x00000020         /* Transmit Underflow */
#define DMA_STATUS_OVF 0x00000010         /* Receive Overflow */
#define DMA_STATUS_TJT 0x00000008         /* Transmit Jabber Timeout */
#define DMA_STATUS_TU 0x00000004          /* Transmit Buffer Unavailable */
#define DMA_STATUS_TPS 0x00000002         /* Transmit Process Stopped */
#define DMA_STATUS_TI 0x00000001          /* Transmit Interrupt */
#define DMA_STATUS_INIT 0xFFFFFFFF

/** DMA 操作模式寄存器 **/
#define DMA_OP_DT 0x04000000U           /* No Dropping of TCP/IP csum Err Frame */
#define DMA_OP_RSF 0x02000000U          /* Rx Store and Forward */
#define DMA_OP_DFF 0x01000000U          /*   */
#define DMA_OP_TSF 0x000200000U         /* Tx Store and Forward */
#define DMA_OP_FTF 0x000100000U         /* Flush Tx FIFO */
#define DMA_OP_TTC(x) ((x & 7) << 14)   /* Tx Threshold Control  ,• 000 64 , 001 128 , 010 192 ,011 256 ,100 40 , 101 32 , 110 24 , 111 16*/
#define DMA_OP_ST 0x000002000U          /* Start/Stop Tx */
#define DMA_OP_RFD(x) ((x & 0x3) << 11) /* Threshold for DeActive Flow Control */
#define DMA_OP_RFA 0x000000600U         /* Threshold for Active Flow Control */
#define DMA_OP_EFC 0x000000100U         /* Enable HW Flow control */
#define DMA_OP_FEF 0x000000080U         /* Forward Error Frame */
#define DMA_OP_FUF 0x000000040U         /* Forward Undersize Good Frame */
#define DMA_OP_RTC 0x000000018U         /* Rx Threshold Control */
#define DMA_OP_OSF 0x000000004U         /* Operate On Second Mode */
#define DMA_OP_SR 0x00000002U           /* Start/Stop Rx */
#define DMA_OP_CLEAR_MASK ((u32)0xF8DE3F23U)
#define DMA_OP_INIT (DMA_OP_SR | DMA_OP_RSF)

/** 中断使能寄存器 **/
#define DMA_INTR_ENA_TIE 0x00000001U /* Transmit Interrupt */
#define DMA_INTR_ENA_TSE 0x00000002U /* 传输停止启用 */
#define DMA_INTR_ENA_TUE 0x00000004U /* Transmit Buffer Unavailable */
#define DMA_INTR_ENA_THE 0x00000008U /* 发送 Jabber 超时启用 */
#define DMA_INTR_ENA_OVE 0x00000010U /* 溢出中断使能 */
#define DMA_INTR_ENA_UNE 0x00000020U /* 下溢中断使能 */
#define DMA_INTR_ENA_RIE 0x00000040U /* Receive Interrupt */
#define DMA_INTR_ENA_RUE 0x00000080U /* 接收缓冲区不可用启用 */
#define DMA_INTR_ENA_RSE 0x00000100U /* 接收已停止启用 */
#define DMA_INTR_ENA_RWE 0x00000200U /* 接收看门狗超时使能  */
#define DMA_INTR_ENA_ETE 0x00000400U /* 早期发送中断使能  */
#define DMA_INTR_ENA_FBE 0x00002000U /* Fatal Bus Error */
#define DMA_INTR_ENA_ERE 0x00004000U /* Early Receive */
#define DMA_INTR_ENA_AIE 0x00008000  /* Abnormal Summary */
#define DMA_INTR_ENA_NIE 0x00010000  /* Normal Summary */

#define DMA_INTR_DEFAULT (DMA_INTR_ENA_TIE | DMA_INTR_ENA_TSE | DMA_INTR_ENA_TUE | DMA_INTR_ENA_THE | DMA_INTR_ENA_OVE | DMA_INTR_ENA_UNE | DMA_INTR_ENA_RIE | DMA_INTR_ENA_RUE | DMA_INTR_ENA_RSE | DMA_INTR_ENA_RWE | DMA_INTR_ENA_ETE | DMA_INTR_ENA_FBE | DMA_INTR_ENA_ERE | DMA_INTR_ENA_AIE | DMA_INTR_ENA_NIE)

/** 丢帧和缓冲区溢出计数器寄存器 **/
#define DMA_MISSED_FRAME_CTR_CMIS 0x0000FFFFUDMA_MISSED_FRAME
#define DMA_MISSED_FRAME_CTR_OVMIS 0x00010000U
#define DMA_MISSED_FRAME_CTR_CFIFO 0x0ffe0000U
#define DMA_MISSED_FRAME_CTR_OVFIFO 0x10000000U

/** 接收中断看门狗定时器寄存器 **/
#define DMA_RX_WATCHDOG_RIWT 0x0000000fU

/** AXI_BUS_MOD **/
#define DMA_AXI_BUS_MOD_UNDEF 0x00000001U               /* AXI 未定义的突发长度 */
#define DMA_AXI_BUS_MOD_BLEN4 0x00000002U               /* AXI 突发长度 4 */
#define DMA_AXI_BUS_MOD_BLEN8 0x00000004U               /* AXI 突发长度 8 */
#define DMA_AXI_BUS_MOD_BLEN16 0x00000008U              /* AXI 突发长度 16 */
#define DMA_AXI_BUS_MOD_BLEN32 0x00000010U              /* AXI 突发长度 32 */
#define DMA_AXI_BUS_MOD_BLEN64 0x00000020U              /* AXI 突发长度 64 */
#define DMA_AXI_BUS_MOD_BLEN128 0x00000040U             /* AXI 突发长度 128 */
#define DMA_AXI_BUS_MOD_BLEN256 0x00000080U             /* AXI 突发长度 256 */
#define DMA_AXI_BUS_MOD_AXI_AAL 0x00001000U             /* 地址对齐的节拍 */
#define DMA_AXI_BUS_MOD_RD_OSR_LMT(x) ((x & 0xf) << 16) /* XI 最大读取未决请求限制此值限 制 AXI 读取接口上的最大未完成请求。 */
#define DMA_AXI_BUS_MOD_WR_OSR_LMT(x) ((x & 0xf) << 20) /* AXI 最大写入未决请求限制此值 限制 AXI 写入接口上的最大未完成请求。 */
#define DMA_AXI_BUS_MOD_UNLCK_ON_MGK_RWK 0x40000000U
#define DMA_AXI_BUS_MOD_EN_LPI 0x80000000U

/** MMC Control  **/
#define MMC_DEFAULT_MASK 0xffffffff

/* Common PHY Registers (AR8035) */

#define PHY_BCR_OFFSET ((u16)0x00)     /* Transceiver Basic Control Register   */
#define PHY_BSR_OFFSET ((u16)0x01)     /* Transceiver Basic Status Register    */
#define PHY_ID1_REG_OFFSET ((u16)0x02) /* PHY ID1 Identifier */
#define PHY_ID2_REG_OFFSET ((u16)0x03) /* PHY ID2 Identifier */
#define PHY_AUTO_NEGOTIATION_ADVERTISEMENT_OFFSET ((u16)0x04)
#define PHY_EXTENDED_CONTROL_REGISTER_OFFSET ((u16)0x9)
#define PHY_SPECIFIC_STATUS_OFFSET ((u16)0x11)
#define PHY_INTERRUPT_ENABLE_OFFSET ((u16)0x12)
#define PHY_INTERRUPT_STATUS_OFFSET ((u16)0x13)
#define PHY_DEBUG_ADDR_OFFSET ((u16)0x1D)
#define PHY_DEBUG_DATA_OFFSET ((u16)0x1E)

/* MII control register bit  */

#define PHY_BCR_1000 0x0040       /* 1 = 1000mb when \
                PHY_BCR_100 is also 1 */
#define PHY_BCR_COLL_TEST 0x0080  /* collision test */
#define PHY_BCR_FDX 0x0100        /* FDX =1, half duplex =0 */
#define PHY_BCR_RESTART 0x0200    /* restart auto negotiation */
#define PHY_BCR_ISOLATE 0x0400    /* isolate PHY from MII */
#define PHY_BCR_POWER_DOWN 0x0800 /* power down */
#define PHY_BCR_AUTO_EN 0x1000    /* auto-negotiation enable */
#define PHY_BCR_100 0x2000        /* 0 = 10mb, 1 = 100mb */
#define PHY_BCR_LOOPBACK 0x4000   /* 0 = normal, 1 = loopback */
#define PHY_BCR_RESET 0x8000      /* 0 = normal, 1 = PHY reset */
#define PHY_BCR_NORM_EN 0x0000    /* just enable the PHY */
#define PHY_BCR_DEF_0_MASK 0xca7f /* they must return zero */
#define PHY_BCR_RES_MASK 0x003f   /* reserved bits,return zero */

#define PHY_ANAR_10TX_HD ((u16)0x0020)
#define PHY_ANAR_10TX_FD ((u16)0x0040)
#define PHY_ANAR_100TX_HD ((u16)0x0080)
#define PHY_ANAR_100TX_FD ((u16)0x0100)
#define PHY_ANAR_100T_4 ((u16)0x0200)
#define PHY_ANAR_PAUSE ((u16)0x0400)
#define PHY_ANAR_ASM_PAUSE ((u16)0x0800)
#define PHY_ANAR_REMORT_FAULT ((u16)0x2000)
#define PHY_ANAR_NEXT_PAGE ((u16)0x8000)
#define PHY_ANAR_PAUSE_MASK ((u16)0x0c00)

#define PHY_BSR_EXTENDED_STATUS ((u16)0x100)

#define PHY_EXTENDED_CONTROL_1000T_FD ((u16)0x200)
#define PHY_EXTENDED_CONTROL_1000T_HD ((u16)0x100)

#define PHY_RESET ((u16)0x8000U)                   /* PHY Reset */
#define PHY_LOOPBACK ((u16)0x4000U)                /* Select loop-back mode */
#define PHY_FULLDUPLEX_1000M ((u16)0x2140U)        /* Set the full-duplex mode at 1000 Mb/s */
#define PHY_HALFDUPLEX_1000M ((u16)0x2040U)        /* Set the half-duplex mode at 1000 Mb/s */
#define PHY_FULLDUPLEX_100M ((u16)0x2100U)         /* Set the full-duplex mode at 100 Mb/s */
#define PHY_HALFDUPLEX_100M ((u16)0x2000U)         /* Set the half-duplex mode at 100 Mb/s */
#define PHY_FULLDUPLEX_10M ((u16)0x0100U)          /* Set the full-duplex mode at 10 Mb/s  */
#define PHY_HALFDUPLEX_10M ((u16)0x0000U)          /* Set the half-duplex mode at 10 Mb/s  */
#define PHY_AUTONEGOTIATION ((u16)0x1000U)         /* Enable auto-negotiation function     */
#define PHY_RESTART_AUTONEGOTIATION ((u16)0x0200U) /* Restart auto-negotiation function    */
#define PHY_POWERDOWN ((u16)0x0800U)               /* Select the power down mode           */
#define PHY_ISOLATE ((u16)0x0400U)                 /* Isolate PHY from MII                 */

#define PHY_AUTONEGO_COMPLETE ((u16)0x0020U) /* Auto-Negotiation process completed   */
#define PHY_LINKED_STATUS ((u16)0x0004U)     /* Valid link established               */
#define PHY_JABBER_DETECTION ((u16)0x0002U)  /* Jabber condition detected            */

#define PHY_SPECIFIC_STATUS_DUPLEX ((u16)0x2000) /* 0 is Half-duplex ,1 is Full-duplex */
#define PHY_SPECIFIC_STATUS_SPEED ((u16)0xc000)  /* 0 is 10Mbps ,1 is 100Mbps , 2 is 1000Mbps */

#define PHY_INTERRUPT_ENABLE_WAKE_ON_LAN 0x00000001U            /* Wake on LAN  interrupt enable,0  Interrupt disable , 1 Interrupt enable */
#define PHY_INTERRUPT_ENABLE_POLARITY_CHANGED 0x00000002U       /* Polarity Changed  interrupt enable,0  Interrupt disable , 1 Interrupt enable */
#define PHY_INTERRUPT_ENABLE_WIRESPEED_DOWNGRADE 0x00000020U    /* Wirespeed downgrade Interrupt ,0  Interrupt disable , 1 Interrupt enable*/
#define PHY_INTERRUPT_ENABLE_LINK_SUCCESS 0x00000400U           /* Link success interrupt ,0  Interrupt disable , 1 Interrupt enable*/
#define PHY_INTERRUPT_ENABLE_LINK_FAIL 0x00000800U              /* Link fail interrupt, 0  Interrupt disable , 1 Interrupt enable */
#define PHY_INTERRUPT_ENABLE_PAGE_RECEIVED 0x00001000U          /*  Page Received, 0  Interrupt disable , 1 Interrupt enable */
#define PHY_INTERRUPT_ENABLE_DUPLEX_CHANGED 0x00002000U         /*  Duplex Changed, 0  Interrupt disable , 1 Interrupt enable*/
#define PHY_INTERRUPT_ENABLE_SPEED_CHANGED 0x00004000U          /* Speed Changed , 0  Interrupt disable , 1 Interrupt enable */
#define PHY_INTERRUPT_ENABLE_AUTO_NEGOTIATION_ERROR 0x00008000U /*  Auto-Negotiation Error , 0  Interrupt disable , 1 Interrupt enable */

#define PHY_INTERRUPT_STATUS_WAKE_ON_LAN 0x00000001U            /* Wake on LAN  ,0  No Wake-on-LAN packet is received , 1  Wake-on-LAN packet is received  */
#define PHY_INTERRUPT_STATUS_POLARITY_CHANGED 0x00000002U       /* Polarity Changed  ,0  Polarity changed , 1 Polarity not changed */
#define PHY_INTERRUPT_STATUS_WIRESPEED_DOWNGRADE 0x00000020U    /* Wirespeed downgrade Interrupt ,0 No Smartspeed interrupt detected  , 1 Smartspeed interrupt detected */
#define PHY_INTERRUPT_STATUS_LINK_SUCCESS 0x00000400U           /* Link success interrupt ,0  Link up not happened , 1  Link up happened.*/
#define PHY_INTERRUPT_STATUS_LINK_FAIL 0x00000800U              /* Link fail interrupt, 0  Link down not happened , 1  Link down happened. */
#define PHY_INTERRUPT_STATUS_PAGE_RECEIVED 0x00001000U          /*  Page Received, 0  Page not received  , 1 Page received */
#define PHY_INTERRUPT_STATUS_DUPLEX_CHANGED 0x00002000U         /*  Duplex Changed, 0  Duplex not changed , 1 Duplex changed*/
#define PHY_INTERRUPT_STATUS_SPEED_CHANGED 0x00004000U          /* Speed Changed , 0  Speed not changed , 1 Speed changed  */
#define PHY_INTERRUPT_STATUS_AUTO_NEGOTIATION_ERROR 0x00008000U /*  Auto-Negotiation Error , 0  No Auto-Negotiation Error , 1 Auto-Negotiation Error */

/**
 * @name: FGmac_InitializeHw
 * @msg:  初始化Mac层与Phy层参数 。
 * @param {FGmac_Config_t} *Config 包含Mac层 与Phy层，配置参数。
 * @return {s32} Common_status 参数。
 */
s32 FGmac_InitializeHw(FGmac_Config_t *Config);

/**
 * @name: FGmac_ReadPHYRegister
 * @msg:  读取Phy 中的寄存器
 * @param {FGmac_Config_t} *Config 提供读取的基地址，与Phy读取过程中需要的相关参数。
 * @param {u16} PHYReg  需要读取Phy 芯片的寄存器地址。
 * @param {u32} *RegValue 读取出来的寄存器参数
 * @return {s32} Common_status 参数。
 */
s32 FGmac_ReadPHYRegister(FGmac_Config_t *Config, u16 PHYReg, u32 *RegValue);

/**
 * @name: Gmac_WritePHYRegister
 * @msg:  向Phy 中的特定寄存器写入参数。
 * @param {FGmac_Config_t} *Config 提供读取的基地址，与Phy读取过程中需要的相关参数。
 * @param {u16} PHYReg 需要读取Phy 芯片的寄存器地址。
 * @param {u32} RegValue 需要写入的寄存器参数
 * @return {s32}  Common_status 参数。
 */
s32 Gmac_WritePHYRegister(FGmac_Config_t *Config, u16 PHYReg, u32 RegValue);

/**
 * @name: FGmac_TransmissionEnable
 * @msg:  使能  Gmac 开始发送功能
 * @param {FGmac_Config_t} *Config  提供Mac的基地址。
 * @return {None}
 */
void FGmac_TransmissionEnable(FGmac_Config_t *Config);

/**
 * @name: FGmac_TransmissionDisable
 * @msg:  禁止  Gmac 开始发送功能
 * @param {FGmac_Config_t} *Config 提供Mac的基地址。
 * @return {None}
 */
void FGmac_TransmissionDisable(FGmac_Config_t *Config);

/**
 * @name: FGmac_ReceptionEnable
 * @msg:  使能  Gmac 开始接收功能
 * @param {FGmac_Config_t} *Config 提供Mac的基地址。
 * @return {None}
 */
void FGmac_ReceptionEnable(FGmac_Config_t *Config);

/**
 * @name: FGmac_ReceptionDisable
 * @msg:  禁止 Gmac 开始接收功能
 * @param {FGmac_Config_t}  *Config 提供Mac的基地址。
 * @return {None}
 */
void FGmac_ReceptionDisable(FGmac_Config_t *Config);

/**
 * @name: FGmac_DMAReceptionTransmissionEnable
 * @msg:  使能  Gmac  开始DMA描述符接收与写入功能
 * @param {FGmac_Config_t} *Config 提供Mac的基地址。
 * @return {*}
 */
void FGmac_DMAReceptionTransmissionEnable(FGmac_Config_t *Config);

/**
 * @name: FGmac_ReceptionTransmissionEnable
 * @msg: 使能  Gmac 开始接收与发送功能
 * @param {FGmac_Config_t} *Config 提供Mac的基地址。
 * @return {*}
 */
void FGmac_ReceptionTransmissionEnable(FGmac_Config_t *Config);

/**
 * @name: FGmac_FlushTransmitFIFO
 * @msg:  刷新 Gmac 发送 FIFO
 * @param {FGmac_Config_t} *Config 提供Mac的基地址。
 * @return {*}
 */
void FGmac_FlushTransmitFIFO(FGmac_Config_t *Config);

/**
 * @name: FGmac_DMATransmissionEnable
 * @msg:  使能 DMA描述符发送功能
 * @param {FGmac_Config_t} *Config 提供Mac的基地址。
 * @return {*}
 */
void FGmac_DMATransmissionEnable(FGmac_Config_t *Config);
/**
 * @name: FGmac_DMATransmissionDisable
 * @msg:  关闭 DMA描述符发送功能
 * @param {FGmac_Config_t} *Config 提供Mac的基地址。
 * @return {*}
 */
void FGmac_DMATransmissionDisable(FGmac_Config_t *Config);
/**
 * @name: FGmac_DMAReceptionEnable
 * @msg:  使能 DMA描述符接收功能
 * @param {FGmac_Config_t} *Config 提供Mac的基地址。
 * @return {*}
 */
void FGmac_DMAReceptionEnable(FGmac_Config_t *Config);
/**
 * @name: FGmac_DMAReceptionEnable
 * @msg:  使能 DMA描述符接收功能
 * @param {FGmac_Config_t} *Config 提供Mac的基地址。
 * @return {*}
 */
void FGmac_DMAReceptionDisable(FGmac_Config_t *Config);
#endif // !
