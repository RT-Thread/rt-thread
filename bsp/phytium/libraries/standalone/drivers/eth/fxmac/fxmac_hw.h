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
 * FilePath: fxmac_hw.h
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:58
 * Description:  This file is hardware definition file. 
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/06/16    first release
 * 1.1  liuzhihong  2023/4/11     jumbo support
 */

#ifndef FXMAC_HW_H
#define FXMAC_HW_H

#include "fparameters.h"
#include "fio.h"
#include "ftypes.h"
#include "fkernel.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define FXMAC_RX_BUF_UNIT 64U /* Number of receive buffer bytes as a unit, this is HW setup */

#define FXMAC_MAX_RXBD 128U /* Size of RX buffer descriptor queues */
#define FXMAC_MAX_TXBD 128U /* Size of TX buffer descriptor queues */

#define FXMAC_MAX_HASH_BITS 64U /* Maximum value for hash bits. 2**6 */

/************************** Constant Definitions *****************************/

#define FXMAC_MAX_MAC_ADDR 4U /* Maxmum number of mac address supported */
#define FXMAC_MAX_TYPE_ID 4U  /* Maxmum number of type id supported */

#ifdef __aarch64__
#define FXMAC_BD_ALIGNMENT 64U /* Minimum buffer descriptor alignment on the local bus */
#else

#define FXMAC_BD_ALIGNMENT 4U /* Minimum buffer descriptor alignment on the local bus */
#endif
#define FXMAC_RX_BUF_ALIGNMENT 4U /* Minimum buffer alignment when using options that impose 
                                    alignment  restrictions on the buffer data on the local bus */

#define FXMAC_NWCTRL_OFFSET 0x00000000U  /* Network Control reg */
#define FXMAC_NWCFG_OFFSET 0x00000004U   /* Network Config reg */
#define FXMAC_NWSR_OFFSET 0x00000008U    /* Network Status reg */
#define FXMAC_DMACR_OFFSET 0x00000010U   /* DMA Control reg */
#define FXMAC_TXSR_OFFSET 0x00000014U    /* TX Status reg */
#define FXMAC_RXQBASE_OFFSET 0x00000018U /* RX Q Base address reg */
#define FXMAC_TXQBASE_OFFSET 0x0000001CU /* TX Q Base address reg */
#define FXMAC_RXSR_OFFSET 0x00000020U    /* RX Status reg */

#define FXMAC_ISR_OFFSET 0x00000024U /* Interrupt Status reg */
#define FXMAC_IER_OFFSET 0x00000028U /* Interrupt Enable reg */
#define FXMAC_IDR_OFFSET 0x0000002CU /* Interrupt Disable reg */
#define FXMAC_IMR_OFFSET 0x00000030U /* Interrupt Mask reg */

#define FXMAC_PHYMNTNC_OFFSET 0x00000034U /* Phy Maintaince reg */
#define FXMAC_RXPAUSE_OFFSET 0x00000038U  /* RX Pause Time reg */
#define FXMAC_TXPAUSE_OFFSET 0x0000003CU  /* TX Pause Time reg */

#define FXMAC_JUMBOMAXLEN_OFFSET 0x00000048U /* Jumbo max length reg */
#define FXMAC_GEM_HSMAC 0x0050               /* Hs mac config register*/
#define FXMAC_RXWATERMARK_OFFSET 0x0000007CU /* RX watermark reg */

#define FXMAC_HASHL_OFFSET 0x00000080U /* Hash Low address reg */
#define FXMAC_HASHH_OFFSET 0x00000084U /* Hash High address reg */

#define FXMAC_GEM_SA1B 0x0088          /* Specific1 Bottom */
#define FXMAC_GEM_SA1T 0x008C          /* Specific1 Top */
#define FXMAC_GEM_SA2B 0x0090          /* Specific2 Bottom */
#define FXMAC_GEM_SA2T 0x0094          /* Specific2 Top */
#define FXMAC_GEM_SA3B 0x0098          /* Specific3 Bottom */
#define FXMAC_GEM_SA3T 0x009C          /* Specific3 Top */
#define FXMAC_GEM_SA4B 0x00A0          /* Specific4 Bottom */
#define FXMAC_GEM_SA4T 0x00A4          /* Specific4 Top */

#define FXMAC_MATCH1_OFFSET 0x000000A8U /* Type ID1 Match reg */
#define FXMAC_MATCH2_OFFSET 0x000000ACU /* Type ID2 Match reg */
#define FXMAC_MATCH3_OFFSET 0x000000B0U /* Type ID3 Match reg */
#define FXMAC_MATCH4_OFFSET 0x000000B4U /* Type ID4 Match reg */

#define FXMAC_STRETCH_OFFSET 0x000000BCU      /* IPG Stretch reg */
#define FXMAC_REVISION_REG_OFFSET 0x000000FCU /*   identification number and module revision */

#define FXMAC_OCTTXL_OFFSET 0x00000100U /* Octects transmitted Low reg */
#define FXMAC_OCTTXH_OFFSET 0x00000104U /* Octects transmitted High reg */

#define FXMAC_TXCNT_OFFSET 0x00000108U      /* Error-free Frmaes transmitted counter */
#define FXMAC_TXBCCNT_OFFSET 0x0000010CU    /* Error-free Broadcast Frames counter*/
#define FXMAC_TXMCCNT_OFFSET 0x00000110U    /* Error-free Multicast Frame counter */
#define FXMAC_TXPAUSECNT_OFFSET 0x00000114U /* Pause Frames Transmitted Counter */
#define FXMAC_TX64CNT_OFFSET 0x00000118U    /* Error-free 64 byte Frames Transmitted counter */
#define FXMAC_TX65CNT_OFFSET 0x0000011CU    /* Error-free 65-127 byte Frames Transmitted counter */
#define FXMAC_TX128CNT_OFFSET 0x00000120U   /* Error-free 128-255 byte Frames Transmitted counter*/
#define FXMAC_TX256CNT_OFFSET 0x00000124U   /* Error-free 256-511 byte Frames transmitted counter */
#define FXMAC_TX512CNT_OFFSET 0x00000128U   /* Error-free 512-1023 byte Frames transmitted counter */
#define FXMAC_TX1024CNT_OFFSET 0x0000012CU  /* Error-free 1024-1518 byte Frames transmitted counter */
#define FXMAC_TX1519CNT_OFFSET 0x00000130U  /* Error-free larger than 1519 byte Frames transmitted counter */
#define FXMAC_TXURUNCNT_OFFSET 0x00000134U  /* TX under run error counter */

#define FXMAC_SNGLCOLLCNT_OFFSET 0x00000138U   /* Single Collision Frame Counter */
#define FXMAC_MULTICOLLCNT_OFFSET 0x0000013CU  /* Multiple Collision Frame Counter */
#define FXMAC_EXCESSCOLLCNT_OFFSET 0x00000140U /* Excessive Collision Frame Counter */
#define FXMAC_LATECOLLCNT_OFFSET 0x00000144U   /* Late Collision Frame Counter */
#define FXMAC_TXDEFERCNT_OFFSET 0x00000148U    /* Deferred Transmission Frame Counter */
#define FXMAC_TXCSENSECNT_OFFSET 0x0000014CU   /* Transmit Carrier Sense Error Counter */

#define FXMAC_OCTRXL_OFFSET 0x00000150U /* Octects Received register Low */
#define FXMAC_OCTRXH_OFFSET 0x00000154U /* Octects Received register High */

#define FXMAC_RXCNT_OFFSET 0x00000158U       /* Error-free Frames Received Counter */
#define FXMAC_RXBROADCNT_OFFSET 0x0000015CU  /* Error-free Broadcast Frames Received Counter */
#define FXMAC_RXMULTICNT_OFFSET 0x00000160U  /* Error-free Multicast Frames Received Counter */
#define FXMAC_RXPAUSECNT_OFFSET 0x00000164U  /* Pause Frames Received Counter */
#define FXMAC_RX64CNT_OFFSET 0x00000168U     /* Error-free 64 byte Frames Received Counter */
#define FXMAC_RX65CNT_OFFSET 0x0000016CU     /* Error-free 65-127 byte Frames Received Counter */
#define FXMAC_RX128CNT_OFFSET 0x00000170U    /* Error-free 128-255 byte Frames Received Counter */
#define FXMAC_RX256CNT_OFFSET 0x00000174U    /* Error-free 256-512 byte Frames Received Counter */
#define FXMAC_RX512CNT_OFFSET 0x00000178U    /* Error-free 512-1023 byte Frames Received Counter */
#define FXMAC_RX1024CNT_OFFSET 0x0000017CU   /* Error-free 1024-1518 byte Frames Received Counter */
#define FXMAC_RX1519CNT_OFFSET 0x00000180U   /* Error-free 1519-max byte Frames Received Counter */
#define FXMAC_RXUNDRCNT_OFFSET 0x00000184U   /* Undersize Frames Received Counter */
#define FXMAC_RXOVRCNT_OFFSET 0x00000188U    /* Oversize Frames Received Counter */
#define FXMAC_RXJABCNT_OFFSET 0x0000018CU    /* Jabbers Received Counter */
#define FXMAC_RXFCSCNT_OFFSET 0x00000190U    /* Frame Check Sequence Error Counter */
#define FXMAC_RXLENGTHCNT_OFFSET 0x00000194U /* Length Field Error Counter */
#define FXMAC_RXSYMBCNT_OFFSET 0x00000198U   /* Symbol Error Counter */
#define FXMAC_RXALIGNCNT_OFFSET 0x0000019CU  /* Alignment Error Counter */
#define FXMAC_RXRESERRCNT_OFFSET 0x000001A0U /* Receive Resource Error Counter */
#define FXMAC_RXORCNT_OFFSET 0x000001A4U     /* Receive Overrun Counter */
#define FXMAC_RXIPCCNT_OFFSET 0x000001A8U    /* IP header Checksum Error Counter */
#define FXMAC_RXTCPCCNT_OFFSET 0x000001ACU   /* TCP Checksum Error Counter */
#define FXMAC_RXUDPCCNT_OFFSET 0x000001B0U   /* UDP Checksum Error Counter */
#define FXMAC_LAST_OFFSET 0x000001B4U        /* Last statistic counter offset, for clearing */

#define FXMAC_1588_SEC_OFFSET 0x000001D0U       /* 1588 second counter */
#define FXMAC_1588_NANOSEC_OFFSET 0x000001D4U   /* 1588 nanosecond counter */
#define FXMAC_1588_ADJ_OFFSET 0x000001D8U       /* 1588 nanosecond adjustment counter */
#define FXMAC_1588_INC_OFFSET 0x000001DCU       /* 1588 nanosecond increment counter */
#define FXMAC_PTP_TXSEC_OFFSET 0x000001E0U      /* 1588 PTP transmit second counter */
#define FXMAC_PTP_TXNANOSEC_OFFSET 0x000001E4U  /* 1588 PTP transmit nanosecond counter */
#define FXMAC_PTP_RXSEC_OFFSET 0x000001E8U      /* 1588 PTP receive second counter */
#define FXMAC_PTP_RXNANOSEC_OFFSET 0x000001ECU  /* 1588 PTP receive nanosecond counter */
#define FXMAC_PTPP_TXSEC_OFFSET 0x000001F0U     /* 1588 PTP peer transmit second counter */
#define FXMAC_PTPP_TXNANOSEC_OFFSET 0x000001F4U /* 1588 PTP peer transmit nanosecond counter */
#define FXMAC_PTPP_RXSEC_OFFSET 0x000001F8U     /* 1588 PTP peer receive second counter */
#define FXMAC_PTPP_RXNANOSEC_OFFSET 0x000001FCU /* 1588 PTP peer receive nanosecond counter */

#define FXMAC_PCS_CONTROL_OFFSET 0x00000200U /* All PCS registers */

#define FXMAC_PCS_STATUS_OFFSET  0x00000204U /* All PCS status */

#define FXMAC_PCS_AN_LP_OFFSET 0x00000214U  /* All PCS link partner's base page */

#define FXMAC_DESIGNCFG_DEBUG1_OFFSET 0x00000280U /* Design Configuration Register 1 */

#define FXMAC_DESIGNCFG_DEBUG2_OFFSET 0x00000284U /* Design Configuration Register 2 */

#define FXMAC_INTQ1_STS_OFFSET 0x00000400U /* Interrupt Q1 Status reg */

#define FXMAC_TXQ1BASE_OFFSET 0x00000440U /* TX Q1 Base address reg */
#define FXMAC_RXQ1BASE_OFFSET 0x00000480U /* RX Q1 Base address reg */

#define FXMAC_RXBUFQ1_SIZE_OFFSET 0x000004a0U /* Receive Buffer Size */
#define FXMAC_RXBUFQX_SIZE_OFFSET(x) (FXMAC_RXBUFQ1_SIZE_OFFSET + (x << 2))
#define FXMAC_RXBUFQX_SIZE_MASK GENMASK(7, 0)

#define FXMAC_MSBBUF_TXQBASE_OFFSET 0x000004C8U /* MSB Buffer TX Q Base reg */
#define FXMAC_MSBBUF_RXQBASE_OFFSET 0x000004D4U /* MSB Buffer RX Q Base reg */
#define FXMAC_TXQSEGALLOC_QLOWER_OFFSET 0x000005A0U /* Transmit SRAM segment distribution */
#define FXMAC_INTQ1_IER_OFFSET 0x00000600U      /* Interrupt Q1 Enable reg */
#define FXMAC_INTQX_IER_SIZE_OFFSET(x) (FXMAC_INTQ1_IER_OFFSET + (x << 2))

#define FXMAC_INTQ1_IDR_OFFSET 0x00000620U /* Interrupt Q1 Disable reg */
#define FXMAC_INTQX_IDR_SIZE_OFFSET(x) (FXMAC_INTQ1_IDR_OFFSET + (x << 2))

#define FXMAC_INTQ1_IMR_OFFSET 0x00000640U /* Interrupt Q1 Mask reg */

#define FXMAC_GEM_USX_CONTROL_OFFSET 0x0A80 /* High speed PCS control register */
#define FXMAC_TEST_CONTROL_OFFSET 0X0A84    /* USXGMII Test Control Register */
#define FXMAC_GEM_USX_STATUS_OFFSET 0x0A88    /* USXGMII Status Register */

#define FXMAC_GEM_SRC_SEL_LN 0x1C04
#define FXMAC_GEM_DIV_SEL0_LN 0x1C08
#define FXMAC_GEM_DIV_SEL1_LN 0x1C0C
#define FXMAC_GEM_PMA_XCVR_POWER_STATE 0x1C10
#define FXMAC_GEM_SPEED_MODE 0x1C14
#define FXMAC_GEM_MII_SELECT 0x1C18
#define FXMAC_GEM_SEL_MII_ON_RGMII 0x1C1C
#define FXMAC_GEM_TX_CLK_SEL0 0x1C20
#define FXMAC_GEM_TX_CLK_SEL1 0x1C24
#define FXMAC_GEM_TX_CLK_SEL2 0x1C28
#define FXMAC_GEM_TX_CLK_SEL3 0x1C2C
#define FXMAC_GEM_RX_CLK_SEL0 0x1C30
#define FXMAC_GEM_RX_CLK_SEL1 0x1C34
#define FXMAC_GEM_CLK_250M_DIV10_DIV100_SEL 0x1C38
#define FXMAC_GEM_TX_CLK_SEL5 0x1C3C
#define FXMAC_GEM_TX_CLK_SEL6 0x1C40
#define FXMAC_GEM_RX_CLK_SEL4 0x1C44
#define FXMAC_GEM_RX_CLK_SEL5 0x1C48
#define FXMAC_GEM_TX_CLK_SEL3_0 0x1C70
#define FXMAC_GEM_TX_CLK_SEL4_0 0x1C74
#define FXMAC_GEM_RX_CLK_SEL3_0 0x1C78
#define FXMAC_GEM_RX_CLK_SEL4_0 0x1C7C
#define FXMAC_GEM_RGMII_TX_CLK_SEL0 0x1C80
#define FXMAC_GEM_RGMII_TX_CLK_SEL1 0x1C84
#define FXMAC_GEM_MODE_SEL_OFFSET 0xDC00
#define FXMAC_LOOPBACK_SEL_OFFSET 0xDC04

/**
 * @name interrupts bit definitions
 * Bits definitions are same in FXMAC_ISR_OFFSET,
 * FXMAC_IER_OFFSET, FXMAC_IDR_OFFSET, and FXMAC_IMR_OFFSET
 * @{
 */
#define FXMAC_IXR_PTPPSTX_MASK BIT(25)  /* PTP Pdelay_resp TXed */
#define FXMAC_IXR_PTPPDRTX_MASK BIT(24) /* PTP Pdelay_req TXed */
#define FXMAC_IXR_PTPPSRX_MASK BIT(23)  /* PTP Pdelay_resp RXed */
#define FXMAC_IXR_PTPPDRRX_MASK BIT(22) /* PTP Pdelay_req RXed */

#define FXMAC_IXR_PTPSTX_MASK BIT(21)  /* PTP Sync TXed */
#define FXMAC_IXR_PTPDRTX_MASK BIT(20) /* PTP Delay_req TXed */
#define FXMAC_IXR_PTPSRX_MASK BIT(19)  /* PTP Sync RXed */
#define FXMAC_IXR_PTPDRRX_MASK BIT(18) /* PTP Delay_req RXed */

#define FXMAC_IXR_PAUSETX_MASK BIT(14)    /* Pause frame transmitted */
#define FXMAC_IXR_PAUSEZERO_MASK BIT(13)  /* Pause time has reached zero */
#define FXMAC_IXR_PAUSENZERO_MASK BIT(12) /* Pause frame received */
#define FXMAC_IXR_HRESPNOK_MASK BIT(11)   /* hresp not ok */
#define FXMAC_IXR_RXOVR_MASK BIT(10)      /* Receive overrun occurred */
#define FXMAC_IXR_LINKCHANGE_MASK BIT(9)   /* link status change */
#define FXMAC_IXR_TXCOMPL_MASK BIT(7)     /* Frame transmitted ok */
#define FXMAC_IXR_TXEXH_MASK BIT(6)       /* Transmit err occurred or no buffers*/
#define FXMAC_IXR_RETRY_MASK BIT(5)       /* Retry limit exceeded */
#define FXMAC_IXR_URUN_MASK BIT(4)        /* Transmit underrun */
#define FXMAC_IXR_TXUSED_MASK BIT(3)      /* Tx buffer used bit read */
#define FXMAC_IXR_RXUSED_MASK BIT(2)      /* Rx buffer used bit read */
#define FXMAC_IXR_RXCOMPL_MASK BIT(1)     /* Frame received ok */
#define FXMAC_IXR_MGMNT_MASK BIT(0)       /* PHY management complete */
#define FXMAC_IXR_ALL_MASK GENMASK(31, 0) /* Everything! */

#define FXMAC_IXR_TX_ERR_MASK ((u32)FXMAC_IXR_TXEXH_MASK | \
                               (u32)FXMAC_IXR_RETRY_MASK | \
                               (u32)FXMAC_IXR_URUN_MASK)

#define FXMAC_IXR_RX_ERR_MASK ((u32)FXMAC_IXR_HRESPNOK_MASK | \
                               (u32)FXMAC_IXR_RXUSED_MASK |   \
                               (u32)FXMAC_IXR_RXOVR_MASK)

#define FXMAC_INTR_MASK               \
     ((u32)FXMAC_IXR_LINKCHANGE_MASK |  \
     (u32)FXMAC_IXR_TX_ERR_MASK |       \
     (u32)FXMAC_IXR_RX_ERR_MASK |       \
     (u32)FXMAC_IXR_RXCOMPL_MASK |      \
     (u32)FXMAC_IXR_TXCOMPL_MASK)

/** @name network control register bit definitions
 * @{
 */
#define FXMAC_NWCTRL_ENABLE_HS_MAC_MASK BIT(31)

#define FXMAC_NWCTRL_TWO_PT_FIVE_GIG_MASK BIT(29) /* 2.5G operation selected */

#define FXMAC_NWCTRL_FLUSH_DPRAM_MASK BIT(18) /* Flush a packet from Rx SRAM */
#define FXMAC_NWCTRL_ZEROPAUSETX_MASK BIT(11) /* Transmit zero quantum pause frame */
#define FXMAC_NWCTRL_PAUSETX_MASK BIT(11)     /* Transmit pause frame */
#define FXMAC_NWCTRL_HALTTX_MASK BIT(10)      /* Halt transmission after current frame */
#define FXMAC_NWCTRL_STARTTX_MASK BIT(9)      /* Start tx (tx_go) */

#define FXMAC_NWCTRL_STATWEN_MASK BIT(7) /* Enable writing to stat counters */
#define FXMAC_NWCTRL_STATINC_MASK BIT(6) /* Increment statistic registers */
#define FXMAC_NWCTRL_STATCLR_MASK BIT(5) /* Clear statistic registers */
#define FXMAC_NWCTRL_MDEN_MASK BIT(4)    /* Enable MDIO port */
#define FXMAC_NWCTRL_TXEN_MASK BIT(3)    /* Enable transmit */
#define FXMAC_NWCTRL_RXEN_MASK BIT(2)    /* Enable receive */
#define FXMAC_NWCTRL_LOOPBACK_LOCAL_MASK BIT(1) /* Loopback local */



/** @name network configuration register bit definitions
 * @{
 */
#define FXMAC_NWCFG_BADPREAMBEN_MASK BIT(29)       /* disable rejection of non-standard preamble */
#define FXMAC_NWCFG_IPDSTRETCH_MASK BIT(28)        /* enable transmit IPG */
#define FXMAC_NWCFG_SGMII_MODE_ENABLE_MASK BIT(27) /* SGMII mode enable */
#define FXMAC_NWCFG_FCSIGNORE_MASK BIT(26)         /* disable rejection of FCS error */
#define FXMAC_NWCFG_HDRXEN_MASK BIT(25)            /* RX half duplex */
#define FXMAC_NWCFG_RXCHKSUMEN_MASK BIT(24)        /* enable RX checksum offload */
#define FXMAC_NWCFG_PAUSECOPYDI_MASK BIT(23)       /* Do not copy pause Frames to memory */

#define FXMAC_NWCFG_DWIDTH_64_MASK BIT(21)         /* 64 bit Data bus width */
#define FXMAC_NWCFG_BUS_WIDTH_32_MASK (0U << 21)
#define FXMAC_NWCFG_BUS_WIDTH_64_MASK (1U << 21)
#define FXMAC_NWCFG_BUS_WIDTH_128_MASK (2U << 21)

#define FXMAC_NWCFG_CLOCK_DIV224_MASK (7U << 18)
#define FXMAC_NWCFG_CLOCK_DIV128_MASK (6U << 18)
#define FXMAC_NWCFG_CLOCK_DIV96_MASK (5U << 18)
#define FXMAC_NWCFG_CLOCK_DIV64_MASK (4U << 18)
#define FXMAC_NWCFG_CLOCK_DIV48_MASK (3U << 18)
#define FXMAC_NWCFG_CLOCK_DIV32_MASK (2U << 18)
#define FXMAC_NWCFG_CLOCK_DIV16_MASK (1U << 18)
#define FXMAC_NWCFG_CLOCK_DIV8_MASK (0U << 18)
#define FXMAC_NWCFG_RESET_MASK BIT(19)      /* reset value of mdc_clock_division*/
#define FXMAC_NWCFG_MDC_SHIFT_MASK 18U             /* shift bits for MDC */
#define FXMAC_NWCFG_MDCCLKDIV_MASK GENMASK(20, 18) /* MDC Mask PCLK divisor */

#define FXMAC_NWCFG_FCS_REMOVE_MASK BIT(17)      /* FCS remove - setting this bit will cause received frames to be written to memory without their frame check sequence (last 4 bytes). */
#define FXMAC_NWCFG_LENGTH_FIELD_ERROR_FRAME_DISCARD_MASK BIT(16)    /* RX length error discard */
#define FXMAC_NWCFG_RXOFFS_MASK GENMASK(15)  /* RX buffer offset */
#define FXMAC_NWCFG_PAUSE_ENABLE_MASK BIT(13)    /* Pause enable - when set, transmission will pause if a non-zero 802.3 classic pause frame is received and PFC has not been negotiated. */
#define FXMAC_NWCFG_RETRYTESTEN_MASK BIT(12) /* Retry test */
#define FXMAC_NWCFG_PCSSEL_MASK BIT(11)     /* PCS Select */
#define FXMAC_NWCFG_1000_MASK BIT(10)       /* Gigabit mode enable */
#define FXMAC_NWCFG_XTADDMACHEN_MASK BIT(9) /* External address match enable */
#define FXMAC_NWCFG_1536RXEN_MASK BIT(8)    /* Enable 1536 byte frames reception */
#define FXMAC_NWCFG_UCASTHASHEN_MASK BIT(7) /* Receive unicast hash frames */
#define FXMAC_NWCFG_MCASTHASHEN_MASK BIT(6) /* Receive multicast hash frames */
#define FXMAC_NWCFG_BCASTDI_MASK BIT(5)     /* Do not receive broadcast frames */
#define FXMAC_NWCFG_COPYALLEN_MASK BIT(4)   /* Copy all frames */
#define FXMAC_NWCFG_JUMBO_MASK BIT(3)       /* Jumbo frames */
#define FXMAC_NWCFG_NVLANDISC_MASK BIT(2)   /* Receive only VLAN frames */
#define FXMAC_NWCFG_FDEN_MASK BIT(1)        /* full duplex */
#define FXMAC_NWCFG_100_MASK BIT(0)         /* 100 Mbps */


/* Receive buffer descriptor status words bit positions.
 * Receive buffer descriptor consists of two 32-bit registers,
 * the first - word0 contains a 32-bit word aligned address pointing to the
 * address of the buffer. The lower two bits make up the wrap bit indicating
 * the last descriptor and the ownership bit to indicate it has been used by
 * the xmac.
 * The following register - word1, contains status information regarding why
 * the frame was received (the filter match condition) as well as other
 * useful info.
 * @{
 */
#define FXMAC_RXBUF_BCAST_MASK BIT(31)            /* Broadcast frame */
#define FXMAC_RXBUF_MULTIHASH_MASK BIT(30)        /* Multicast hashed frame */
#define FXMAC_RXBUF_UNIHASH_MASK BIT(29)          /* Unicast hashed frame */
#define FXMAC_RXBUF_EXH_MASK BIT(27)              /* buffer exhausted */
#define FXMAC_RXBUF_AMATCH_MASK GENMASK(26, 25)   /* Specific address \
matched */
#define FXMAC_RXBUF_IDFOUND_MASK BIT(24)          /* Type ID matched */
#define FXMAC_RXBUF_IDMATCH_MASK GENMASK(23, 22)  /* ID matched mask */
#define FXMAC_RXBUF_VLAN_MASK BIT(21)             /* VLAN tagged */
#define FXMAC_RXBUF_PRI_MASK BIT(20)              /* Priority tagged */
#define FXMAC_RXBUF_VPRI_MASK GENMASK(19, 17)     /* Vlan priority */
#define FXMAC_RXBUF_CFI_MASK BIT(16)              /* CFI frame */
#define FXMAC_RXBUF_EOF_MASK BIT(15)              /* End of frame. */
#define FXMAC_RXBUF_SOF_MASK BIT(14)              /* Start of frame. */
#define FXMAC_RXBUF_FCS_STATUS_MASK BIT(13)       /* Status of fcs. */
#define FXMAC_RXBUF_LEN_MASK GENMASK(12, 0)       /* Mask for length field */
#define FXMAC_RXBUF_LEN_JUMBO_MASK GENMASK(13, 0) /* Mask for jumbo length */

#define FXMAC_RXBUF_WRAP_MASK BIT(1)        /* Wrap bit, last BD */
#define FXMAC_RXBUF_NEW_MASK BIT(0)         /* Used bit.. */
#define FXMAC_RXBUF_ADD_MASK GENMASK(31, 2) /* Mask for address */

/*
 * @}
 */

/* Transmit buffer descriptor status words bit positions.
 * Transmit buffer descriptor consists of two 32-bit registers,
 * the first - word0 contains a 32-bit address pointing to the location of
 * the transmit data.
 * The following register - word1, consists of various information to control
 * the xmac transmit process.  After transmit, this is updated with status
 * information, whether the frame was transmitted OK or why it had failed.
 * @{
 */
#define FXMAC_TXBUF_USED_MASK BIT(31)       /* Used bit. */
#define FXMAC_TXBUF_WRAP_MASK BIT(30)       /* Wrap bit, last descriptor */
#define FXMAC_TXBUF_RETRY_MASK BIT(29)      /* Retry limit exceeded */
#define FXMAC_TXBUF_URUN_MASK BIT(28)       /* Transmit underrun occurred */
#define FXMAC_TXBUF_EXH_MASK BIT(27)        /* Buffers exhausted */
#define FXMAC_TXBUF_TCP_MASK BIT(26)        /* Late collision. */
#define FXMAC_TXBUF_NOCRC_MASK BIT(16)      /* No CRC */
#define FXMAC_TXBUF_LAST_MASK BIT(15)       /* Last buffer */
#define FXMAC_TXBUF_LEN_MASK GENMASK(13, 0) /* Mask for length field */
/*
 * @}
 */


/**
 * @name receive status register bit definitions
 * @{
 */
#define FXMAC_RXSR_HRESPNOK_MASK BIT(3) /* Receive hresp not OK */
#define FXMAC_RXSR_RXOVR_MASK BIT(2)    /* Receive overrun */
#define FXMAC_RXSR_FRAMERX_MASK BIT(1)  /* Frame received OK */
#define FXMAC_RXSR_BUFFNA_MASK BIT(0)   /* RX buffer used bit set */

#define FXMAC_RXSR_ERROR_MASK ((u32)FXMAC_RXSR_HRESPNOK_MASK | \
                               (u32)FXMAC_RXSR_RXOVR_MASK |    \
                               (u32)FXMAC_RXSR_BUFFNA_MASK)

#define FXMAC_SR_ALL_MASK GENMASK(31, 0) /* Mask for full register */

/** @name DMA control register bit definitions
 * @{
 */
#define FXMAC_DMACR_ADDR_WIDTH_64 BIT(30)       /* 64 bit address bus */
#define FXMAC_DMACR_TXEXTEND_MASK BIT(29)       /* Tx Extended desc mode */
#define FXMAC_DMACR_RXEXTEND_MASK BIT(28)       /* Rx Extended desc mode */
#define FXMAC_DMACR_ORCE_DISCARD_ON_ERR_MASK BIT(24) /* Auto Discard RX frames during lack of resource. */
#define FXMAC_DMACR_RXBUF_MASK GENMASK(23, 16)  /* Mask bit for RX buffer size */
#define FXMAC_DMACR_RXBUF_SHIFT 16U             /* Shift bit for RX buffer size */
#define FXMAC_DMACR_TCPCKSUM_MASK BIT(11)       /* enable/disable TX checksum offload */
#define FXMAC_DMACR_TXSIZE_MASK BIT(10)         /* TX buffer memory size bit[10] */
#define FXMAC_DMACR_RXSIZE_MASK GENMASK(9, 8)   /* RX buffer memory size bit[9:8] */
#define FXMAC_DMACR_ENDIAN_MASK BIT(7)          /* endian configuration */
#define FXMAC_DMACR_SWAP_MANAGEMENT_MASK BIT(6) /*  When clear, selects little endian mode */
#define FXMAC_DMACR_BLENGTH_MASK GENMASK(4, 0)  /* buffer burst length */
#define FXMAC_DMACR_SINGLE_AHB_AXI_BURST BIT(0) /* single AHB_AXI bursts */
#define FXMAC_DMACR_INCR4_AHB_AXI_BURST BIT(2)  /* 4 bytes AHB_AXI bursts */
#define FXMAC_DMACR_INCR8_AHB_AXI_BURST BIT(3)  /* 8 bytes AHB_AXI bursts */
#define FXMAC_DMACR_INCR16_AHB_AXI_BURST BIT(4) /* 16 bytes AHB_AXI bursts */

/* This register indicates module identification number and module revision. */

#define FXMAC_REVISION_MODULE_MASK GENMASK(15, 0) /* Module revision */
#define FXMAC_IDENTIFICATION_MASK GENMASK(27, 16) /* Module identification number */
#define FXMAC_FIX_NUM_MASK GENMASK(31, 28)        /*  Fix number - incremented for fix releases */

/** @name network status register bit definitaions
 * @{
 */
#define FXMAC_NWSR_MDIOIDLE_MASK BIT(2) /* PHY management idle */
#define FXMAC_NWSR_MDIO_MASK BIT(1)     /* Status of mdio_in */
#define FXMAC_NWSR_PCS_LINK_STATE_MASK  BIT(0)

/** @name PHY Maintenance bit definitions
 * @{
 */
#define FXMAC_PHYMNTNC_OP_MASK (BIT(17) | BIT(30)) /* operation mask bits */
#define FXMAC_PHYMNTNC_OP_R_MASK BIT(29)           /* read operation */
#define FXMAC_PHYMNTNC_OP_W_MASK BIT(28)           /* write operation */
#define FXMAC_PHYMNTNC_ADDR_MASK GENMASK(27, 23)   /* Address bits */
#define FXMAC_PHYMNTNC_REG_MASK GENMASK(22, 18)    /* register bits */
#define FXMAC_PHYMNTNC_DATA_MASK GENMASK(11, 0)    /* data bits */
#define FXMAC_PHYMNTNC_PHAD_SHFT_MSK 23U           /* Shift bits for PHYAD */
#define FXMAC_PHYMNTNC_PREG_SHFT_MSK 18U           /* Shift bits for PHREG */

/** @name transmit status register bit definitions
 * @{
 */
#define FXMAC_TXSR_HRESPNOK_MASK BIT(8) /* Transmit hresp not OK */
#define FXMAC_TXSR_URUN_MASK BIT(6)     /* Transmit underrun */
#define FXMAC_TXSR_TXCOMPL_MASK BIT(5)  /* Transmit completed OK */
#define FXMAC_TXSR_BUFEXH_MASK BIT(4)   /* Transmit buffs exhausted mid frame */
#define FXMAC_TXSR_TXGO_MASK BIT(3)     /* Status of go flag */
#define FXMAC_TXSR_RXOVR_MASK BIT(2)    /* Retry limit exceeded */
#define FXMAC_TXSR_FRAMERX_MASK BIT(1)  /* Collision tx frame */
#define FXMAC_TXSR_USEDREAD_MASK BIT(0) /* TX buffer used bit set */

#define FXMAC_TXSR_ERROR_MASK ((u32)FXMAC_TXSR_HRESPNOK_MASK | \
                               (u32)FXMAC_TXSR_URUN_MASK |     \
                               (u32)FXMAC_TXSR_BUFEXH_MASK |   \
                               (u32)FXMAC_TXSR_RXOVR_MASK |    \
                               (u32)FXMAC_TXSR_FRAMERX_MASK |  \
                               (u32)FXMAC_TXSR_USEDREAD_MASK)
/** @name transmit SRAM segment allocation by queue 0 to 7  register bit definitions
 * @{
 */                                
#define FXMAC_TXQSEGALLOC_QLOWER_MASK BIT(2)  /* 16 segments are distributed to queue 0*/
#define FXMAC_TXQSEGALLOC_QLOWER_CLEAN_MASK 0x0U
/**
 * @name Interrupt Q1 status register bit definitions
 * @{
 */
#define FXMAC_INTQ1SR_TXCOMPL_MASK BIT(7) /* Transmit completed OK */
#define FXMAC_INTQ1SR_TXERR_MASK BIT(6)   /* Transmit AMBA Error */

#define FXMAC_INTQ1_IXR_ALL_MASK ((u32)FXMAC_INTQ1SR_TXCOMPL_MASK | \
                                  (u32)FXMAC_INTQ1SR_TXERR_MASK)

/**
 * @name Interrupt QUEUE status register bit definitions
 * @{
 */
#define FXMAC_INTQUESR_TXCOMPL_MASK BIT(7) /* Transmit completed OK */
#define FXMAC_INTQUESR_TXERR_MASK BIT(6)   /* Transmit AMBA Error */
#define FXMAC_INTQUESR_RCOMP_MASK BIT(1)
#define FXMAC_INTQUESR_RXUBR_MASK BIT(2)

#define FXMAC_INTQUE_IXR_ALL_MASK ((u32)FXMAC_INTQUESR_TXCOMPL_MASK | \
                                   (u32)FXMAC_INTQUESR_TXERR_MASK)

#define FXMAC_QUEUE_REGISTER_OFFSET(base_addr, queue_id) ((u32)base_addr + (queue_id - 1) * 4)

/* Design Configuration Register 1 - The GEM has many parameterisation options to configure the IP during compilation stage. */

#define FXMAC_DESIGNCFG_DEBUG1_BUS_WIDTH_MASK GENMASK(27, 25)
#define FXMAC_DESIGNCFG_DEBUG1_BUS_IRQCOR_MASK BIT(23)

/*GEM hs mac config register bitfields*/
#define FXMAC_GEM_HSMACSPEED_OFFSET 0
#define FXMAC_GEM_HSMACSPEED_SIZE 3
#define FXMAC_GEM_HSMACSPEED_MASK 0x7

/* Transmit buffer descriptor status words offset
 * @{
 */
#define FXMAC_BD_ADDR_OFFSET 0x00000000U /* word 0/addr of BDs */
#define FXMAC_BD_STAT_OFFSET 4           /* word 1/status of BDs, 4 bytes */
#define FXMAC_BD_ADDR_HI_OFFSET BIT(3)   /* word 2/addr of BDs */

/** @name MAC address register word 1 mask
 * @{
 */
#define FXMAC_GEM_SAB_MASK GENMASK(15, 0) /* Address bits[47:32] bit[31:0] are in BOTTOM */

/* USXGMII control register */
#define FXMAC_GEM_USX_HS_MAC_SPEED_100M (0x0 << 14) /* 100M operation */
#define FXMAC_GEM_USX_HS_MAC_SPEED_1G (0x1 << 14)   /* 1G operation */
#define FXMAC_GEM_USX_HS_MAC_SPEED_2_5G (0x2 << 14) /* 2.5G operation */
#define FXMAC_GEM_USX_HS_MAC_SPEED_5G  (0x3 << 14)  /* 5G operation */
#define FXMAC_GEM_USX_HS_MAC_SPEED_10G (0x4 << 14)  /* 10G operation */
#define FXMAC_GEM_USX_SERDES_RATE_5G    (0x0 << 12)
#define FXMAC_GEM_USX_SERDES_RATE_10G    (0x1 << 12)
#define FXMAC_GEM_USX_TX_SCR_BYPASS BIT(8)          /* RX Scrambler Bypass. Set high to bypass the receive descrambler. */
#define FXMAC_GEM_USX_RX_SCR_BYPASS BIT(9)          /* TX Scrambler Bypass. Set high to bypass the transmit scrambler. */
#define FXMAC_GEM_USX_RX_SYNC_RESET BIT(2)          /* RX Reset. Set high to reset the receive datapath. When low the receive datapath is enabled. */
#define FXMAC_GEM_USX_TX_DATAPATH_EN BIT(1)         /* TX Datapath Enable. */
#define FXMAC_GEM_USX_SIGNAL_OK BIT(0)              /* Enable the USXGMII/BASE-R receive PCS. */

/*  All PCS registers */

#define FXMAC_PCS_CONTROL_ENABLE_AUTO_NEG BIT(12) /* Enable auto-negotiation - when set active high, autonegotiation operation is enabled.  */


/* FXMAC_PCS_STATUS_OFFSET */
#define FXMAC_PCS_STATUS_LINK_STATUS_OFFSET 2
#define FXMAC_PCS_STATUS_LINK_STATUS    BIT(FXMAC_PCS_STATUS_LINK_STATUS_OFFSET)   /* Link status - indicates the status of the physical connection to the link partner. When set to logic 1 the link is up, and when set to logic 0, the link is down. */

/* FXMAC_PCS_AN_LP_OFFSET */

#define FXMAC_PCS_AN_LP_SPEED_OFFSET   10
#define FXMAC_PCS_AN_LP_SPEED    (0x3U << FXMAC_PCS_AN_LP_SPEED_OFFSET) /* SGMII 11 : Reserved 10 : 1000 Mbps 01 : 100Mbps 00 : 10 Mbps */
#define FXMAC_PCS_AN_LP_DUPLEX_OFFSET  12
#define FXMAC_PCS_AN_LP_DUPLEX   (0x3U << FXMAC_PCS_AN_LP_DUPLEX_OFFSET) /* SGMII Bit 13: Reserved. read as 0. Bit 12 : 0 : half-duplex. 1: Full Duplex." */
#define FXMAC_PCS_LINK_PARTNER_NEXT_PAGE_STATUS (1U<<15) /* In sgmii mode, 0 is link down . 1 is link up */


/* USXGMII Status Register */

#define FXMAC_GEM_USX_STATUS_BLOCK_LOCK BIT(0)  /* Block Lock. A value of one indicates that the PCS has achieved block synchronization. */


/***************** Macros (Inline Functions) Definitions *********************/

#define FXMAC_READREG32(addr, reg_offset) FtIn32(addr + (u32)reg_offset)
#define FXMAC_WRITEREG32(addr, reg_offset, reg_value) FtOut32(addr + (u32)reg_offset, (u32)reg_value)


#define FXMAC_SetBit32(addr, reg_offset, reg_value) FtSetBit32(addr + (u32)reg_offset, (u32)reg_value)
#define FXMAC_ClearBit32(addr, reg_offset, reg_value) FtClearBit32(addr + (u32)reg_offset, (u32)reg_value)

/****************************************************************************/
/**
 *
 * Enable interrupts specified in <i>Mask</i>. The corresponding interrupt for
 * each bit set to 1 in <i>Mask</i>, will be enabled.
 *
 * @param instance_p is a pointer to the instance to be worked on.
 * @param Mask contains a bit mask of interrupts to enable. The mask can
 *        be formed using a set of bitwise or'd values.
 *
 * @note
 * The state of the transmitter and receiver are not modified by this function.
 * C-style signature
 *     void FXMAC_INT_ENABLE(FXmac *instance_p, u32 Mask)
 *
 *****************************************************************************/
#define FXMAC_INT_ENABLE(instance_p, Mask)              \
    FXMAC_WRITEREG32((instance_p)->config.base_address, \
                     FXMAC_IER_OFFSET,                  \
                     ((Mask)&FXMAC_IXR_ALL_MASK));

/****************************************************************************/
/**
 *
 * Enable interrupts specified in <i>Mask</i>. The corresponding interrupt for
 * each bit set to 1 in <i>Mask</i>, will be enabled.
 *
 * @param instance_p is a pointer to the instance to be worked on.
 * @param Mask contains a bit mask of interrupts to enable. The mask can
 *        be formed using a set of bitwise or'd values.
 *
 * @note
 * The state of the transmitter and receiver are not modified by this function.
 * C-style signature
 *     void FXMAC_INT_Q1ENABLE(FXmac *instance_p, u32 Mask)
 *
 *****************************************************************************/
#define FXMAC_INT_Q1ENABLE(instance_p, Mask)            \
    FXMAC_WRITEREG32((instance_p)->config.base_address, \
                     FXMAC_INTQ1_IER_OFFSET,            \
                     ((Mask)&FXMAC_INTQ1_IXR_ALL_MASK));


#ifdef __cplusplus
}
#endif

#endif // !
