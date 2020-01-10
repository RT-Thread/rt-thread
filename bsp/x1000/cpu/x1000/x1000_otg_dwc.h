/*
 * File      : x1000_otg_dwc.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-02-03     Urey         the first version
 */

#ifndef _X1000_OTG_DWC_H_
#define _X1000_OTG_DWC_H_

/* Globle Regs define */
#define GOTG_CTL        (OTG_BASE + 0x00)
#define GOTG_INTR       (OTG_BASE + 0x04)
#define GAHB_CFG        (OTG_BASE + 0x08)
#define GUSB_CFG        (OTG_BASE + 0x0c)
#define GRST_CTL        (OTG_BASE + 0x10)
#define GINT_STS        (OTG_BASE + 0x14)
#define GINT_MASK       (OTG_BASE + 0x18)
#define GRXSTS_READ     (OTG_BASE + 0x1c)
#define GRXSTS_POP      (OTG_BASE + 0x20)
#define GRXFIFO_SIZE        (OTG_BASE + 0x24)
#define GNPTXFIFO_SIZE      (OTG_BASE + 0x28)
#define GDTXFIFO_SIZE       (OTG_BASE + 0x104)
#define GHW_CFG1        (OTG_BASE + 0x44)
#define GHW_CFG2        (OTG_BASE + 0x48)
#define GHW_CFG3        (OTG_BASE + 0x4c)
#define GHW_CFG4        (OTG_BASE + 0x50)
#define GDFIFO_CFG      (OTG_BASE + 0x5c)
#define PCGC_CTL        (OTG_BASE + 0xe00)

/* Fifo number 1 ~ 15 */
#define GDEIP_TXF(n)    (OTG_BASE + (0x104 + ((n-1) * 0x4)))

#define REG_GOTG_CTL        REG32(GOTG_CTL)
#define REG_GOTG_INTR       REG32(GOTG_INTR)
#define REG_GAHB_CFG        REG32(GAHB_CFG)
#define REG_GUSB_CFG        REG32(GUSB_CFG)
#define REG_GRST_CTL        REG32(GRST_CTL)
#define REG_GINT_STS        REG32(GINT_STS)
#define REG_GINT_MASK       REG32(GINT_MASK)
#define REG_GRXSTS_READ     REG32(GRXSTS_READ)
#define REG_GRXSTS_POP      REG32(GRXSTS_POP)
#define REG_GRXFIFO_SIZE    REG32(GRXFIFO_SIZE)
#define REG_GNPTXFIFO_SIZE  REG32(GNPTXFIFO_SIZE)
#define REG_GDTXFIFO_SIZE   REG32(GDTXFIFO_SIZE)
#define REG_GHW_CFG1        REG32(GHW_CFG1)
#define REG_GHW_CFG2        REG32(GHW_CFG2)
#define REG_GHW_CFG3        REG32(GHW_CFG3)
#define REG_GHW_CFG4        REG32(GHW_CFG4)
#define REG_GDFIFO_CFG      REG32(GDFIFO_CFG)
#define REG_GDIEP_TXF(n)    REG32(GDEIP_TXF(n))
#define REG_PCGC_CTL        REG32(PCGC_CTL)
/* Device Regs define */
#define EP_FIFO(n)      (OTG_BASE + (n+1)*0x1000) // FiX ME
#define REG_EP_FIFO(n)      REG32(EP_FIFO(n))


#define OTG_DCFG        (OTG_BASE + 0x800)
#define OTG_DCTL        (OTG_BASE + 0x804)
#define OTG_DSTS        (OTG_BASE + 0x808)
#define DIEP_MASK       (OTG_BASE + 0x810)
#define DOEP_MASK       (OTG_BASE + 0x814)
#define OTG_DAINT       (OTG_BASE + 0x818)
#define DAINT_MASK      (OTG_BASE + 0x81c)

#define DIEP_EMPMSK     (OTG_BASE + 0x834)


/* It's used in OTG_MULT_PROC_INTRPT = 1
#define DEACH_INT       (OTG_BASE + 0x838)
#define DEACH_INTMASK       (OTG_BASE + 0x83c)
#define DIEP0_INTMASK       (OTG_BASE + 0x840)
#define DIEP1_INTMASK       (OTG_BASE + 0x844)
#define DOEP0_INTMASK       (OTG_BASE + 0x880)
#define DOEP1_INTMASK       (OTG_BASE + 0x884)
*/

#define DIEP_CTL(n)     (OTG_BASE + (0x900 + (n)*0x20))
#define DOEP_CTL(n)     (OTG_BASE + (0xb00 + (n)*0x20))

#define DIEP_INT(n)     (OTG_BASE + (0x908 + (n)*0x20))
#define DOEP_INT(n)     (OTG_BASE + (0xb08 + (n)*0x20))

#define DIEP_SIZE(n)        (OTG_BASE + (0x910 + (n)*0x20))
#define DOEP_SIZE(n)        (OTG_BASE + (0xb10 + (n)*0x20))

#define DIEP_TXFSTS(n)      (OTG_BASE + (0x918 + (n)*0x20))

#define DIEP_DMA(n)         (OTG_BASE + (0x914 + (n)*0x20))
#define DOEP_DMA(n)         (OTG_BASE + (0xb14 + (n)*0x20))

#define REG_OTG_DCFG        REG32(OTG_DCFG)
#define REG_OTG_DCTL        REG32(OTG_DCTL)
#define REG_OTG_DSTS        REG32(OTG_DSTS)
#define REG_DIEP_MASK       REG32(DIEP_MASK)
#define REG_DOEP_MASK       REG32(DOEP_MASK)
#define REG_OTG_DAINT       REG32(OTG_DAINT)
#define REG_DAINT_MASK      REG32(DAINT_MASK)
#define REG_DIEP_EMPMSK     REG32(DIEP_EMPMSK)

#define REG_DIEP_CTL(n)     REG32(DIEP_CTL(n))
#define REG_DOEP_CTL(n)     REG32(DOEP_CTL(n))

#define REG_DIEP_INT(n)     REG32(DIEP_INT(n))
#define REG_DOEP_INT(n)     REG32(DOEP_INT(n))

#define REG_DIEP_SIZE(n)    REG32(DIEP_SIZE(n))
#define REG_DOEP_SIZE(n)    REG32(DOEP_SIZE(n))

#define REG_DIEP_TXFSTS(n)  REG32(DIEP_TXFSTS(n))

#define REG_DIEP_DMA(n)     REG32(DIEP_DMA(n))
#define REG_DOEP_DMA(n)     REG32(DOEP_DMA(n))

/* Regs macro define */
/*************************************************/
#define AHBCFG_TXFE_LVL     BIT7
#define AHBCFG_DMA_ENA      BIT5
#define AHBCFG_GLOBLE_INTRMASK  BIT0
#define USBCFG_FORCE_DEVICE BIT30
#define USBCFG_TRDTIME_MASK (0xf << 10)
#define USBCFG_TRDTIME_9    (9 << 10)
#define USBCFG_TRDTIME_6    (6 << 10)

/* GRSTCTL */
#define RSTCTL_AHB_IDLE     BIT31
#define RSTCTL_TXFNUM_ALL   (0x10 << 6)
#define RSTCTL_TXFIFO_FLUSH BIT5
#define RSTCTL_RXFIFO_FLUSH BIT4
#define RSTCTL_INTK_FLUSH   BIT3
#define RSTCTL_FRMCNT_RST   BIT2
#define RSTCTL_CORE_RST     BIT0

/* GINTMSK */
#define GINTMSK_RSUME_DETE  BIT31
#define GINTMSK_CONID_STSCHG    BIT28
#define GINTMSK_RESET_DETE  BIT23
#define GINTMSK_FETCH_SUSPEND   BIT22
#define GINTMSK_OEP_INTR    BIT19
#define GINTMSK_IEP_INTR    BIT18
#define GINTMSK_EP_MISMATCH BIT17
#define GINTMSK_ENUM_DONE   BIT13
#define GINTMSK_USB_RESET   BIT12
#define GINTMSK_USB_SUSPEND BIT11
#define GINTMSK_USB_EARLYSUSPEND    BIT10
#define GINTMSK_I2C_INT     BIT9
#define GINTMSK_ULPK_CKINT  BIT8
#define GINTMSK_GOUTNAK_EFF BIT7
#define GINTMSK_GINNAK_EFF  BIT6
#define GINTMSK_NPTXFIFO_EMPTY  BIT5
#define GINTMSK_RXFIFO_NEMPTY   BIT4
#define GINTMSK_START_FRAM  BIT3
#define GINTMSK_OTG_INTR    BIT2
#define GINTMSK_MODE_MISMATCH   BIT1

/* GINTSTS */
#define GINTSTS_RSUME_DETE  BIT31
#define GINTSTS_CONID_STSCHG    BIT28
#define GINTSTS_RESET_DETE  BIT23
#define GINTSTS_FETCH_SUSPEND   BIT22
#define GINTSTS_OEP_INTR    BIT19
#define GINTSTS_IEP_INTR    BIT18
#define GINTSTS_EP_MISMATCH BIT17
#define GINTSTS_ENUM_DONE   BIT13
#define GINTSTS_USB_RESET   BIT12
#define GINTSTS_USB_SUSPEND BIT11
#define GINTSTS_USB_EARLYSUSPEND    BIT10
#define GINTSTS_I2C_INT     BIT9
#define GINTSTS_ULPK_CKINT  BIT8
#define GINTSTS_GOUTNAK_EFF BIT7
#define GINTSTS_GINNAK_EFF  BIT6
#define GINTSTS_NPTXFIFO_EMPTY  BIT5
#define GINTSTS_RXFIFO_NEMPTY   BIT4
#define GINTSTS_START_FRAM  BIT3
#define GINTSTS_OTG_INTR    BIT2
#define GINTSTS_MODE_MISMATCH   BIT1

/* DCTL */
#define DCTL_CGOUTNAK       BIT10
#define DCTL_CLR_GNPINNAK   BIT8
#define DCTL_SGNPINNAK      BIT7
#define DCTL_SOFT_DISCONN   BIT1
#define DCTL_SGOUTNAK       BIT9
/* DCFG */
#define DCFG_DEV_ADDR_MASK  (0x7f << 4)
#define DCFG_DEV_ADDR_BIT   4
#define DCFG_DEV_DESC_DMA   (1 << 23)
/* DSTS */
#define DSTS_ERRATIC_ERROR          BIT3
#define DSTS_ENUM_SPEED_MASK        (0x3 << 1)
#define DSTS_ENUM_SPEED_BIT         BIT1
#define DSTS_ENUM_SPEED_HIGH        (0x0 << 1)
#define DSTS_ENUM_SPEED_FULL_30OR60 (0x1 << 1)
#define DSTS_ENUM_SPEED_LOW         (0x2 << 1)
#define DSTS_ENUM_SPEED_FULL_48     (0x3 << 1)

/* GRXSTSR/GRXSTSP */
#define GRXSTSP_PKSTS_MASK      (0xf << 17)
#define GRXSTSP_PKSTS_GOUT_NAK      (0x1 << 17)
#define GRXSTSP_PKSTS_GOUT_RECV     (0x2 << 17)
#define GRXSTSP_PKSTS_TX_COMP       (0x3 << 17)
#define GRXSTSP_PKSTS_SETUP_COMP    (0x4 << 17)
#define GRXSTSP_PKSTS_SETUP_RECV    (0x6 << 17)
#define GRXSTSP_BYTE_CNT_MASK       (0x7ff << 4)
#define GRXSTSP_BYTE_CNT_BIT        4
#define GRXSTSP_EPNUM_MASK      (0xf)
#define GRXSTSP_EPNUM_BIT       BIT0


/* DIOEPCTL */
// ep0
#define DEP_EP0_MAXPKET_SIZE    64
#define DEP_EP0_MPS_64      (0x0)
#define DEP_EP0_MPS_32      (0x1)
#define DEP_EP0_MPS_16      (0x2)
#define DEP_EP0_MPS_8       (0x3)

#define DEP_ENA_BIT     BIT31
#define DEP_DISENA_BIT      BIT30
#define DEP_SET_NAK         BIT27
#define DEP_CLEAR_NAK       BIT26
#define DEP_SET_STALL       BIT21
#define DEP_TYPE_MASK       (0x3 << 18)
#define DEP_TYPE_CNTL       (0x0 << 18)
#define DEP_TYPE_ISO        (0x1 << 18)
#define DEP_TYPE_BULK       (0x2 << 18)
#define DEP_TYPE_INTR       (0x3 << 18)
#define USB_ACTIVE_EP       BIT15
#define DEP_PKTSIZE_MASK    0x7ff
#define DEP_FS_PKTSIZE      64
#define DEP_HS_PKTSIZE      512

/* DIOEPINT */
#define DEP_NYET_INT        BIT14
#define DEP_NAK_INT     BIT13
#define DEP_BABBLE_ERR_INT  BIT12
#define DEP_PKT_DROP_STATUS BIT11
#define DEP_BNA_INT     BIT9
#define DEP_TXFIFO_UNDRN    BIT8        // Only for INEP
#define DEP_OUTPKT_ERR      BIT8        // Only for OUTEP
#define DEP_TXFIFO_EMPTY    BIT7
#define DEP_INEP_NAKEFF     BIT6        // Only for INEP
#define DEP_B2B_SETUP_RECV  BIT6        // Only for OUTEP0
#define DEP_INTOKEN_EPMISATCH   BIT5        // Only for INEP
#define DEP_STATUS_PHASE_RECV   BIT5        // Only for OUTEP0
#define DEP_INTOKEN_RECV_TXFIFO_EMPTY   BIT4    // Only for INEP
#define DEP_OUTTOKEN_RECV_EPDIS BIT4        // Only for OUTEP
#define DEP_TIME_OUT        BIT3        // Only for INEP
#define DEP_SETUP_PHASE_DONE    BIT3        // Only for OUTEP0
#define DEP_AHB_ERR     BIT2
#define DEP_EPDIS_INT       BIT1
#define DEP_XFER_COMP       BIT0        // Used by INEP and OUTEP

/* DOEPSIZ0 */
#define DOEPSIZE0_SUPCNT_1  (0x1 << 29)
#define DOEPSIZE0_SUPCNT_2  (0x2 << 29)
#define DOEPSIZE0_SUPCNT_3  (0x3 << 29)
#define DOEPSIZE0_PKTCNT_BIT    BIT19


#define DEP_RXFIFO_SIZE     1064
#define DEP_NPTXFIFO_SIZE   1024
#define DEP_DTXFIFO_SIZE    768


#define DWC_GAHBCFG_INT_DMA_BURST_SINGLE    0
#define DWC_GAHBCFG_INT_DMA_BURST_INCR      1
#define DWC_GAHBCFG_INT_DMA_BURST_INCR4     3
#define DWC_GAHBCFG_INT_DMA_BURST_INCR8     5
#define DWC_GAHBCFG_INT_DMA_BURST_INCR16    7

#define DWC_GAHBCFG_EXT_DMA_BURST_1word     0x0
#define DWC_GAHBCFG_EXT_DMA_BURST_4word     0x1
#define DWC_GAHBCFG_EXT_DMA_BURST_8word     0x2
#define DWC_GAHBCFG_EXT_DMA_BURST_16word    0x3
#define DWC_GAHBCFG_EXT_DMA_BURST_32word    0x4
#define DWC_GAHBCFG_EXT_DMA_BURST_64word    0x5
#define DWC_GAHBCFG_EXT_DMA_BURST_128word   0x6
#define DWC_GAHBCFG_EXT_DMA_BURST_256word   0x7

#define DEP_NUM         2

#if 0
#define UTMI_PHY_WIDTH      8
#else
#define UTMI_PHY_WIDTH      16
#endif

#endif /* _X1000_OTG_DWC_H_ */
