/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-21
 */


/*  $NetBSD: lan9118reg.h,v 1.3 2010/09/27 12:29:03 kiyohara Exp $  */
/*
 * Copyright (c) 2008 KIYOHARA Takashi
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _LAN9118REG_H_
#define _LAN9118REG_H_


#define CONFIG_SMC911X_32_BIT

#define LAN9118_IOSIZE   0x100

#define LAN9118_ID_89218 0x218a
#define LAN9118_ID_9115  0x0115
#define LAN9118_ID_9116  0x0116
#define LAN9118_ID_9117  0x0117
#define LAN9118_ID_9118  0x0118
#define LAN9218_ID_9215  0x115a
#define LAN9218_ID_9216  0x116a
#define LAN9218_ID_9217  0x117a
#define LAN9218_ID_9218  0x118a

#define LAN9210_ID_9210  0x9210
#define LAN9210_ID_9211  0x9211
#define LAN9220_ID_9220  0x9220
#define LAN9220_ID_9221  0x9221

#define IS_LAN9118(id)  ((id) >= LAN9118_ID_9115 && (id) <= LAN9118_ID_9118)
#define IS_LAN9218(id)  ((id) >= LAN9218_ID_9215 && (id) <= LAN9218_ID_9218)

#define LAN9118_IPHY_ADDR   0x01    /* Internal PHY Address */


#define LAN9118_RXDFIFOP    0x00    /* RX Data FIFO Port */
#define LAN9118_RXDFIFOAP   0x04    /* RX Data FIFO Alias Ports */
#define LAN9118_TXDFIFOP    0x20    /* TX Data FIFO Port */
#define LAN9118_TXDFIFOAP   0x24    /* TX Data FIFO Alias Ports */
#define LAN9118_RXSFIFOP    0x40    /* RX Status FIFO Port */
#define LAN9118_RXSFIFOPEEK 0x44    /* RX Status FIFO PEEK */
#define LAN9118_TXSFIFOP    0x48    /* TX Status FIFO Port */
#define LAN9118_TXSFIFOPEEK 0x4c    /* TX Status FIFO PEEK */

/* System Control and Status Registers */
#define LAN9118_ID_REV                      0x50    /* Chip ID and Revision */
#define LAN9118_ID_REV_ID(x)                (((x) >> 16) & 0xffff)
#define LAN9118_ID_REV_REV(x)               ((x) & 0xffff)
#define LAN9118_IRQ_CFG                     0x54    /* Main Interrupt Configuration */
#define LAN9118_IRQ_CFG_INT_DEAS(t)         ((t) << 24) /* Intr Deassert Interval */
#define LAN9118_IRQ_CFG_INT_DEAS_CLR        (1 << 14)   /* Intr Deass Intrval clr */
#define LAN9118_IRQ_CFG_INT_DEAS_STS        (1 << 13)   /* Intr Deassert Status */
#define LAN9118_IRQ_CFG_IRQ_INT             (1 << 12)   /* Master Interrupt */
#define LAN9118_IRQ_CFG_IRQ_EN              (1 << 8)    /* IRQ Enable */
#define LAN9118_IRQ_CFG_IRQ_POL             (1 << 4)    /* IRQ Polarity */
#define LAN9118_IRQ_CFG_IRQ_TYPE            (1 << 0)    /* IRQ Buffer Type */
#define LAN9118_INT_STS                     0x58    /* Interrupt Status */
#define LAN9118_INT_EN                      0x5c    /* Interrupt Enable Register */
#define LAN9118_INT_SW_INT                  (1 << 31) /* Software Interrupt */
#define LAN9118_INT_TXSTOP_INT              (1 << 25) /* TX Stopped */
#define LAN9118_INT_RXSTOP_INT              (1 << 24) /* RX Stopped */
#define LAN9118_INT_RXDFH_INT               (1 << 23) /* RX Drppd Frm Cnt Halfway */
#define LAN9118_INT_TX_IOC                  (1 << 21) /* TX IOC Interrupt */
#define LAN9118_INT_RXD_INT                 (1 << 20) /* RX DMA Interrupt */
#define LAN9118_INT_GPT_INT                 (1 << 19) /* GP Timer */
#define LAN9118_INT_PHY_INT                 (1 << 18) /* PHY */
#define LAN9118_INT_PME_INT                 (1 << 17) /* Power Management Event */
#define LAN9118_INT_TXSO                    (1 << 16) /* TX Status FIFO Overflow */
#define LAN9118_INT_RWT                     (1 << 15) /* Rcv Watchdog Time-out */
#define LAN9118_INT_RXE                     (1 << 14) /* Receive Error */
#define LAN9118_INT_TXE                     (1 << 13) /* Transmitter Error */
#define LAN9118_INT_TDFO                    (1 << 10) /* TX Data FIFO Overrun */
#define LAN9118_INT_TDFA                    (1 << 9)  /* TX Data FIFO Available */
#define LAN9118_INT_TSFF                    (1 << 8)  /* TX Status FIFO Full */
#define LAN9118_INT_TSFL                    (1 << 7)  /* TX Status FIFO Level */
#define LAN9118_INT_RXDF_INT                (1 << 6)  /* RX Dropped Frame Intr */
#define LAN9118_INT_RSFF                    (1 << 4)  /* RX Status FIFO Full */
#define LAN9118_INT_RSFL                    (1 << 3)  /* RX Status FIFO Level */
#define LAN9118_INT_GPIOX_INT(x)            (1 << (x)) /* GPIO[2:0] */
/*              0x60       Reserved for future use */
#define LAN9118_BYTE_TEST                   0x64    /* Read-only byte order testing reg */
#define LAN9118_BYTE_TEST_VALUE             0x87654321
#define LAN9118_FIFO_INT                    0x68    /* FIFO Level Interrupt */
#define LAN9118_FIFO_INT_TXDAL(x)           ((x) << 24) /* TX Data Available Lvl */
#define LAN9118_FIFO_INT_TXSL(x)            ((x) << 16) /* TX Status Level */
#define LAN9118_FIFO_INT_RXSL(x)            ((x) << 0)  /* RX Status Level */
#define LAN9118_RX_CFG                      0x6c    /* Receive Configuration */
#define LAN9118_RX_CFG_RXEA_4B              (0 << 30) /* RX End Alignment: 4 Byte */
#define LAN9118_RX_CFG_RXEA_16B             (1 << 30) /*                  16 Byte */
#define LAN9118_RX_CFG_RXEA_32B             (2 << 30) /*                  32 Byte */
#define LAN9118_RX_CFG_RX_DMA_CNT(x)        ((x) << 16) /* RX DMA Count */
#define LAN9118_RX_CFG_RX_DUMP              (1 << 15)   /* Force RX Discard */
#define LAN9118_RX_CFG_RXDOFF(x)            ((x) << 8)  /* RX Data Offset */
#define LAN9118_TX_CFG                      0x70    /* Transmit Configuration */
#define LAN9118_TX_CFG_TXS_DUMP             (1 << 15) /* Force TX Status Discard */
#define LAN9118_TX_CFG_TXD_DUMP             (1 << 14) /* Force TX Data Discard */
#define LAN9118_TX_CFG_TXSAO                (1 << 2)  /* TX Status Allow Overrun */
#define LAN9118_TX_CFG_TX_ON                (1 << 1)  /* Transmitter Enable */
#define LAN9118_TX_CFG_STOP_TX              (1 << 0)  /* Stop Transmitter */
#define LAN9118_HW_CFG                      0x74    /* Hardware Configuration */
#define LAN9118_HW_CFG_MBO                  (1 << 20)/* Must Be One */
#define LAN9118_HW_CFG_TX_FIF_MASK          (0xf << 16) /* TX FIFO Size */
#define LAN9118_HW_CFG_TX_FIF_SZ(sz)        ((sz) << 16)
#define LAN9118_HW_CFG_PHY_CLK_SEL_MASK     (3 << 5) /* PHY Clock Select */
#define LAN9118_HW_CFG_PHY_CLK_SEL_IPHY     (0 << 5) /*   Internal PHY */
#define LAN9118_HW_CFG_PHY_CLK_SEL_EMII     (1 << 5) /*   External MII Port */
#define LAN9118_HW_CFG_PHY_CLK_SEL_CD       (2 << 5) /*   Clock Disabled */
#define LAN9118_HW_CFG_SMI_SEL              (1 << 4) /* Serial Mgmt Interface Sel */
#define LAN9118_HW_CFG_EXT_PHY_DET          (1 << 3) /* External PHY Detect */
#define LAN9118_HW_CFG_EXT_PHY_EN           (1 << 2) /* External PHY Enable */
#define LAN9118_HW_CFG_SRST_TO              (1 << 1) /* Soft Reset Timeout */
#define LAN9118_HW_CFG_SRST                 (1 << 0) /* Soft Reset */
#define LAN9118_RX_DP_CTL                   0x78    /* RX Datapath Control */
#define LAN9118_RX_DP_CTL_RX_FFWD           (1 << 31)/* RX Data FIFO Fast Forward */
#define LAN9118_RX_FIFO_INF                 0x7c    /* Receive FIFO Information */
#define LAN9118_RX_FIFO_INF_RXSUSED(x)      (((x) >> 16) & 0xff) /*Sts Used Space*/
#define LAN9118_RX_FIFO_INF_RXDUSED(x)      ((x) & 0xffff)  /*Data FIFO Used Space*/
#define LAN9118_TX_FIFO_INF                 0x80    /* Transmit FIFO Information */
#define LAN9118_TX_FIFO_INF_TXSUSED(x)      (((x) >> 16) & 0xff) /*Sts Used Space*/
#define LAN9118_TX_FIFO_INF_TDFREE(x)       ((x) & 0xffff) /*Data FIFO Free Space*/
#define LAN9118_PMT_CTRL                    0x84    /* Power Management Control */
#define LAN9118_PMT_CTRL_PM_MODE_MASK       (3 << 12)
#define LAN9118_PMT_CTRL_PM_MODE_D0         (0 << 12)
#define LAN9118_PMT_CTRL_PM_MODE_D1         (1 << 12)
#define LAN9118_PMT_CTRL_PM_MODE_D2         (2 << 12)
#define LAN9118_PMT_CTRL_PHY_RST            (1 << 10) /* PHY Reset */
#define LAN9118_PMT_CTRL_WOL_EN             (1 << 9)  /* Wake-On-LAN Enable */
#define LAN9118_PMT_CTRL_ED_EN              (1 << 8)  /* Energy-Detect Enable */
#define LAN9118_PMT_CTRL_PME_TYPE           (1 << 6)  /* PME Buffer Type */
#define LAN9118_PMT_CTRL_WUPS_NWUED         (0 << 4) /* WAKE-UP Status: No Event */
#define LAN9118_PMT_CTRL_WUPS_ED            (1 << 4) /* WAKE-UP Status: Energy */
#define LAN9118_PMT_CTRL_WUPS_WUD           (2 << 4) /* WAKE-UP Status: Wake-up */
#define LAN9118_PMT_CTRL_PME_IND            (1 << 3)  /* PME indication */
#define LAN9118_PMT_CTRL_PME_POL            (1 << 2)  /* PME Polarity */
#define LAN9118_PMT_CTRL_PME_EN             (1 << 1)  /* PME Enable */
#define LAN9118_PMT_CTRL_READY              (1 << 0)  /* Device Ready */
#define LAN9118_GPIO_CFG                    0x88    /* General Purpose IO Configuration */
#define LAN9118_GPIO_CFG_LEDX_EN(x)         (1 << ((x) + 28))  /* LED[3:1] enable */
#define LAN9118_GPIO_CFG_GPIO_INT_POL(p)    (1 << ((p) + 24)) /* Intr Polarity */
#define LAN9118_GPIO_CFG_EEPR_EN            (7 << 20)          /* EEPROM Enable */
#define LAN9118_GPIO_CFG_GPIOBUFN(n)        (1 << ((n) + 16))  /* Buffer Type */
#define LAN9118_GPIO_CFG_GPDIRN(n)          (1 << ((n) + 8))   /* Direction */
#define LAN9118_GPIO_CFG_GPODN(n)           (1 << (n)) /* GPIO Data (3,4 is WO) */
#define LAN9118_GPT_CFG                     0x8c    /* General Purpose Timer Config */
#define LAN9118_GPT_CNT                     0x90    /* General Purpose Timer Count */
/*              0x94       Reserved for future use */
#define LAN9118_WORD_SWAP                   0x98    /* WORD SWAP Register */
#define LAN9118_FREE_RUN                    0x9c    /* Free Run Counter */
#define LAN9118_RX_DROP                     0xa0    /* RX Drop Frame Counter */
#define LAN9118_MAC_CSR_CMD                 0xa4    /* MAC CSR Synchronizer Command */
#define LAN9118_MAC_CSR_CMD_BUSY            (1 << 31)
#define LAN9118_MAC_CSR_CMD_W               (0 << 30)
#define LAN9118_MAC_CSR_CMD_R               (1 << 30)
#define LAN9118_MAC_CSR_CMD_ADDRESS(a)      ((a) & 0xff)
#define LAN9118_MAC_CSR_DATA                0xa8    /* MAC CSR Synchronizer Data */
#define LAN9118_AFC_CFG                     0xac    /* Automatic Flow Control Config */
#define LAN9118_AFC_CFG_AFC_HI(x)           ((x) << 16)
#define LAN9118_AFC_CFG_AFC_LO(x)           ((x) << 8)
#define LAN9118_AFC_CFG_BACK_DUR(x)         ((x) << 4)
#define LAN9118_AFC_CFG_FCMULT              (1 << 3) /* Flow Control on Multicast */
#define LAN9118_AFC_CFG_FCBRD               (1 << 2) /* Flow Control on Broadcast */
#define LAN9118_AFC_CFG_FCADD               (1 << 1) /* Flow Control on Addr Dec */
#define LAN9118_AFC_CFG_FCANY               (1 << 0) /* Flow Control on Any Frame */
#define LAN9118_E2P_CMD                     0xb0    /* EEPROM command */
#define LAN9118_E2P_CMD_EPCB                (1 << 31) /* EPC Busy */
#define LAN9118_E2P_CMD_EPCC_READ           (0 << 28) /* EPC Command: READ */
#define LAN9118_E2P_CMD_EPCC_EWDS           (1 << 28) /*              EWDS */
#define LAN9118_E2P_CMD_EPCC_EWEN           (2 << 28) /*              EWEN */
#define LAN9118_E2P_CMD_EPCC_WRITE          (3 << 28) /*              WRITE */
#define LAN9118_E2P_CMD_EPCC_WRAL           (4 << 28) /*              WRAL */
#define LAN9118_E2P_CMD_EPCC_ERASE          (5 << 28) /*              ERASE */
#define LAN9118_E2P_CMD_EPCC_ERAL           (6 << 28) /*              ERAL */
#define LAN9118_E2P_CMD_EPCC_RELOAD         (7 << 28) /*              Reload */
#define LAN9118_E2P_CMD_EPCTO               (1 << 9)  /* EPC Time-out */
#define LAN9118_E2P_CMD_MACAL               (1 << 8)  /* MAC Address Loaded */
#define LAN9118_E2P_CMD_EPCA(a)             ((a) & 0xff) /* EPC Address */
#define LAN9118_E2P_DATA                    0xb4    /* EEPROM Data */
/*              0xb8 - 0xfc Reserved for future use */

/* MAC Control and Status Registers */
#define LAN9118_MAC_CR              0x1 /* MAC Control Register */
#define LAN9118_MAC_CR_RXALL        (1 << 31) /* Receive All Mode */
#define LAN9118_MAC_CR_RCVOWN       (1 << 23) /* Disable Receive Own */
#define LAN9118_MAC_CR_LOOPBK       (1 << 21) /* Loopback operation Mode */
#define LAN9118_MAC_CR_FDPX         (1 << 20) /* Full Duplex Mode */
#define LAN9118_MAC_CR_MCPAS        (1 << 19) /* Pass All Multicast */
#define LAN9118_MAC_CR_PRMS         (1 << 18) /* Promiscuous Mode */
#define LAN9118_MAC_CR_INVFILT      (1 << 17) /* Inverse filtering */
#define LAN9118_MAC_CR_PASSBAD      (1 << 16) /* Pass Bad Frames */
#define LAN9118_MAC_CR_HO           (1 << 15) /* Hash Only Filtering mode */
#define LAN9118_MAC_CR_HPFILT       (1 << 13) /* Hash/Perfect Flt Mode */
#define LAN9118_MAC_CR_LCOLL        (1 << 12) /* Late Collision Control */
#define LAN9118_MAC_CR_BCAST        (1 << 11) /* Disable Broardcast Frms */
#define LAN9118_MAC_CR_DISRTY       (1 << 10) /* Disable Retry */
#define LAN9118_MAC_CR_PADSTR       (1 << 8)  /* Automatic Pad String */
#define LAN9118_MAC_CR_BOLMT        (1 << 7)  /* BackOff Limit */
#define LAN9118_MAC_CR_DFCHK        (1 << 5)  /* Deferral Check */
#define LAN9118_MAC_CR_TXEN         (1 << 3)  /* Transmitter enable */
#define LAN9118_MAC_CR_RXEN         (1 << 2)  /* Receiver enable */
#define LAN9118_ADDRH               0x2 /* MAC Address High */
#define LAN9118_ADDRL               0x3 /* MAC Address Low */
#define LAN9118_HASHH               0x4 /* Multicast Hash Table High */
#define LAN9118_HASHL               0x5 /* Multicast Hash Table Low */
#define LAN9118_MII_ACC             0x6 /* MII Access */
#define LAN9118_MII_ACC_PHYA(a)     ((a) << 11) /* PHY Address */
#define LAN9118_MII_ACC_MIIRINDA(i) ((i) << 6)  /* MII Register Index */
#define LAN9118_MII_ACC_MIIWNR      (1 << 1)    /* MII Write */
#define LAN9118_MII_ACC_MIIBZY      (1 << 0)    /* MII Busy */
#define LAN9118_MII_DATA            0x7 /* MII Data */
#define LAN9118_FLOW                0x8 /* Flow Control */
#define LAN9118_FLOW_FCPT(t)        ((t) << 16) /* Pause Time */
#define LAN9118_FLOW_FCPASS         (1 << 2)    /* Pass Control Frame */
#define LAN9118_FLOW_FCEN           (1 << 1)    /* Flow Control Enable */
#define LAN9118_FLOW_FCBUSY         (1 << 0)    /* Flow Control Busy */
#define LAN9118_VLAN1               0x9 /* VLAN1 Tag */
#define LAN9118_VLAN2               0xa /* VLAN2 Tag */
#define LAN9118_WUFF                0xb /* Wake-up Frame Filter */
#define LAN9118_WUCSR               0xc /* Wake-up Control and Status */

/* PHY Registers */
#define LAN9118_MCSR                0x11    /* Mode Control/Status Register */
#define LAN9118_MCSR_EDPWRDOWN      (1 << 13) /* Energy Detect Power Down */
#define LAN9118_MCSR_ENERGYON       (1 << 1)
#define LAN9118_SMR                 0x12    /* Special Modes Register */
#define LAN9118_SMR_PHYAD           (0x01)
#define LAN9118_SCSI                0x1b    /* Special Control/Status Indications */
#define LAN9118_SCSI_VCOOFF_LP      (1 << 10)
#define LAN9118_SCSI_XPOL           (1 << 4)  /* Polarity state */
#define LAN9118_ISR                 0x1d    /* Interrupt Source Register */
#define LAN9118_IMR                 0x1e    /* Interrupt Mask Register */
#define LAN9118_I_ENERGYON          (1 << 7)
#define LAN9118_I_AUTONEGOCOMPL     (1 << 6)
#define LAN9118_I_REMOTEFAULT       (1 << 5)
#define LAN9118_I_LINKDOWN          (1 << 4)
#define LAN9118_I_AUTONEGOLPACK     (1 << 3) /* AutoNego LP Acknowledge */
#define LAN9118_I_PDF               (1 << 2) /* Parallel Detection Fault */
#define LAN9118_I_AUTONEGOPR        (1 << 1) /* AutoNego Page Received */
#define LAN9118_PHYSCSR             0x1f    /* PHY Special Control/Status Reg */
#define LAN9118_PHYSCSR_AUTODONE    (1 << 12) /* AutoNego done indication */
#define LAN9118_PHYSCSR_SI_10       (1 << 2)  /* Speed Indication */
#define LAN9118_PHYSCSR_SI_100      (2 << 2)
#define LAN9118_PHYSCSR_SI_FDX      (4 << 2)


/* TX Command 'A' Format */
#define LAN9118_TXC_A_IC        (1 << 31) /* Interrupt on Completion */
#define LAN9118_TXC_A_BEA_4B    (0 << 24) /* Buffer End Alignment: 4B */
#define LAN9118_TXC_A_BEA_16B   (1 << 24) /*                      16B */
#define LAN9118_TXC_A_BEA_32B   (2 << 24) /*                      32B */
#define LAN9118_TXC_A_DSO(x)    ((x) << 16) /*Data Start Offset: bytes*/
#define LAN9118_TXC_A_FS        (1 << 13) /* First Segment */
#define LAN9118_TXC_A_LS        (1 << 12) /* Last Segment */
#define LAN9118_TXC_A_BS(x)     ((x) << 0) /* Buffer Size */

/* TX Command 'B' Format */
#define LAN9118_TXC_B_PT(x)     ((x) << 16) /* Packet Tag */
#define LAN9118_TXC_B_ACRCD     (1 << 13)  /* Add CRC Disable */
#define LAN9118_TXC_B_DEFP      (1 << 12)  /* Dis Ether Frame Padding */
#define LAN9118_TXC_B_PL(x)     ((x) << 0) /* Packet Length */

/* TX Status Format */
#define LAN9118_TXS_PKTTAG(x)   (((x) >> 16) & 0xff) /* Packet Tag */
#define LAN9118_TXS_ES          (1 << 15)   /* Error Status */
#define LAN9118_TXS_LOC         (1 << 11)   /* Loss Of Carrier */
#define LAN9118_TXS_NC          (1 << 10)   /* No Carrier */
#define LAN9118_TXS_LCOL        (1 << 9)    /* Late Collision */
#define LAN9118_TXS_ECOL        (1 << 8)    /* Excessive Collision*/
#define LAN9118_TXS_COLCNT(x)   (((x) >> 3) & 0xf) /* Collision Count */
#define LAN9118_TXS_ED          (1 << 2)    /* Excessive Deferral */
#define LAN9118_TXS_DEFERRED    (1 << 0)    /* Deferred */

/* RX Status Format */
#define LAN9118_RXS_FILTFAIL    (1 << 30) /* Filtering Fail */
#define LAN9118_RXS_PKTLEN(x)   (((x) >> 16) & 0x3fff) /* Packet Len */
#define LAN9118_RXS_ES          (1 << 15) /* Error Status */
#define LAN9118_RXS_BCF         (1 << 13) /* Broadcast Frame */
#define LAN9118_RXS_LENERR      (1 << 12) /* Length Error */
#define LAN9118_RXS_RUNTF       (1 << 11) /* Runt Frame */
#define LAN9118_RXS_MCF         (1 << 10) /* Multicast Frame */
#define LAN9118_RXS_FTL         (1 << 7)  /* Frame Too Long */
#define LAN9118_RXS_COLS        (1 << 6)  /* Collision Seen */
#define LAN9118_RXS_FT          (1 << 5)  /* Frame Type */
#define LAN9118_RXS_RWTO        (1 << 4)  /* Rcv Watchdog time-out */
#define LAN9118_RXS_MIIERR      (1 << 3)  /* MII Error */
#define LAN9118_RXS_DBIT        (1 << 2)  /* Drabbling Bit */
#define LAN9118_RXS_CRCERR      (1 << 1)  /* CRC Error */

/* Basic mode control register. */
#define LAN9118_BMCR_ANRESTART      0x0200  /* Auto negotiation restart  */
#define LAN9118_BMCR_ANENABLE       0x1000  /* Enable auto negotiation   */
#define LAN9118_BMCR_RESET          0x8000  /* Reset the DP83840     */
#define LAN9118_BMSR_LSTATUS        0x0004  /* Link status    */

/* Generic MII registers. */
#define LAN9118_MII_BMCR            0x00  /* Basic mode control register */
#define LAN9118_MII_BMSR            0x01  /* Basic mode status register  */
#define LAN9118_MII_ADVERTISE       0x04  /* Advertisement control register */

#define LAN9118_GPT_CFG_TIMER_EN    0x20000000  /* R/W */

#define LAN9118_RX_STS_PKT_LEN      0x3FFF0000
#define LAN9118_TX_STS_UNDERRUN     0x00000002

#define LAN9118_HW_CFG_SF           0x00100000  /* R/W */

#define LAN9118_INT_STS_RSFL        0x00000008  /* R/WC */
#define LAN9118_INT_EN_RDFL_EN      0x00000020  /* R/W */
#define LAN9118_MAC_CR_HBDIS        0x10000000

#endif  /* _LAN9118REG_H_ */
