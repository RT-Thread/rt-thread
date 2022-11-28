/* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.

 * Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
 * the the People's Republic of China and other countries.
 * All Allwinner Technology Co.,Ltd. trademarks are used with permission.

 * DISCLAIMER
 * THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
 * IF YOU NEED TO INTEGRATE THIRD PART'S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
 * IN ALLWINNER'SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
 * ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
 * ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
 * COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
 * YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PART'S TECHNOLOGY.


 * THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
 * PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
 * THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
 * OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __UDC_PLATFORM_H__
#define __UDC_PLATFORM_H__

#include <stdint.h>

#include <sunxi_hal_common.h>
#include <usb/ch9.h>

/* USB_POWER */
#define USB_POWER_ENABLESUSPENDM    (0x01)   /* RW */
#define USB_POWER_SUSPENDMODE       (0x02)   /* P: RO ; H: WO */ /*Read clear by the intr. register*/
#define USB_POWER_RESUME        (0x04)   /* RW */
#define USB_POWER_RESET         (0x08)   /* P: RO ; H: RW */
#define USB_POWER_HSMODE        (0x10)   /* RO */
#define USB_POWER_HSENAB        (0x20)   /* RW */
#define USB_POWER_SOFTCONN      (0x40)   /* RW */
#define USB_POWER_ISOUPDATE     (0x80)   /* RW */

/* USB_INTRTX */
#define USB_INTRTX_EP0          (0x01)   /*RO*/
#define USB_INTRTX_EP1          (0x02)   /*RO*/
#define USB_INTRTX_EP2          (0x04)   /*RO*/
#define USB_INTRTX_EP3          (0x08)   /*RO*/
#define USB_INTRTX_EP4          (0x10)   /*RO*/

/* USB_INTRRX */
#define USB_INTRRX_EP1          (0x02)   /*RO*/
#define USB_INTRRX_EP2          (0x04)   /*RO*/
#define USB_INTRRX_EP3          (0x08)   /*RO*/
#define USB_INTRRX_EP4          (0x10)   /*RO*/

/* USB_INTRTXE & USB_INTRRXE */
#define USB_INTRE_EPEN          (0x01)   /* RW */
#define USB_INTRE_EPDIS         (0x00)   /* RW */

/* USB_INTRUSB */
#define USB_INTRUSB_SUSPEND     (0x01)   /*RO*/
#define USB_INTRUSB_RESUME      (0x02)   /*RO*/
#define USB_INTRUSB_RESET       (0x04)   /*RO*/
#define USB_INTRUSB_BABBLE      (0x04)   /*RO*/
#define USB_INTRUSB_SOF         (0x08)   /*RO*/
#define USB_INTRUSB_CONN        (0x10)   /*RO*/
#define USB_INTRUSB_DISCON      (0x20)   /*RO*/
#define USB_INTRUSB_SESSREQ     (0x40)   /*RO*/
#define USB_INTRUSB_VBUSERROR       (0x80)   /*RO*/

/* USB_INTRUSBE */
#define USB_INTRUSBE_SUSPEND        (0x01)   /*RW*/
#define USB_INTRUSBE_RESUME     (0x02)   /*RW*/
#define USB_INTRUSBE_RESET      (0x04)   /*RW*/
#define USB_INTRUSBE_BABBLE     (0x04)   /*RW*/
#define USB_INTRUSBE_SOF        (0x08)   /*RW*/
#define USB_INTRUSBE_CONN       (0x10)   /*RW*/
#define USB_INTRUSBE_DISCON     (0x20)   /*RW*/
#define USB_INTRUSBE_SESSREQ        (0x40)   /*RW*/
#define USB_INTRUSBE_VBUSERROR      (0x80)   /*RW*/

/* USB_TESTMODE */
#define USB_TESTMODE_TESTSE0NAK     (0x01)  /* RW */
#define USB_TESTMODE_TESTJ      (0x02)  /* RW */
#define USB_TESTMODE_TESTK      (0x04)  /* RW */
#define USB_TESTMODE_TESTPACKET     (0x08)  /* RW */
#define USB_TESTMODE_FORCEHS        (0x10)  /* RW */
#define USB_TESTMODE_FORCEFS        (0x20)  /* RW */
#define USB_TESTMODE_FIFOACCESS     (0x40)  /* WO, AC */
#define USB_TESTMODE_FORCEHOST      (0x80)  /* RW */

/* USB_DEVCTL */
#define USB_DEVCTL_SESSION      (0x01)   /* RW */
#define USB_DEVCTL_HOSTREQ      (0x02)   /* RW */
#define USB_DEVCTL_HOSTMODE     (0x04)   /* RO */
#define USB_DEVCTL_VBUS         (0x18)   /* RO */
#define USB_DEVCTL_LSDEV        (0x20)   /* RO */
#define USB_DEVCTL_FSDEV        (0x40)   /* RO */
#define USB_DEVCTL_BDEVICE      (0x80)   /* RO */

#define USB_DEVCTL_ABOVE_VBUS_VALID (0x18)
#define USB_DEVCTL_ABOVE_A_VALID    (0x10)
#define USB_DEVCTL_ABOVE_SESSION_END    (0x01)
#define USB_DEVCTL_BELOW_SESSION_END    (0x00)

/* USB_VEND0 */
#define USB_VEND0_DRQ_SEL       (1)
#define USB_VEND0_BUS_SEL       (0)

/* USB_CSR0 */
#define USB_CSR0_RXPKTRDY       (0x0001)   /* RO */
#define USB_CSR0_TXPKTRDY       (0x0002)   /* RW, AC */
#define USB_CSR0_SENTSTALL      (0x0004)   /* RC */
#define USB_CSR0_DATAEND        (0x0008)   /* WO, AC */
#define USB_CSR0_SETUPEND       (0x0010)   /* RO */
#define USB_CSR0_SENDSTALL      (0x0020)   /* WO, AC */
#define USB_CSR0_SERVICEDRXPKTRDY   (0x0040)   /* WO, AC */
#define USB_CSR0_SERVICEDSETUPEND   (0x0080)   /* WO, AC */
#define USB_CSR0_FLUSHFIFO      (0x0100)   /* WO, AC */
/* in Host mode */
#define USB_CSR0_RXSTALL        (0x0004)
#define USB_CSR0_SETUPPKT       (0x0008)
#define USB_CSR0_ERROR          (0x0010)
#define USB_CSR0_REQPKT         (0x0020)
#define USB_CSR0_STATUSPKT      (0x0040)
#define USB_CSR0_NAKTIMEOUT     (0x0080)
#define USB_CSR0_FLUSHFIFO      (0x0100)
#define USB_CSR0_DISPING        (0x0800)

/* USB_TXMAXP */
#define USB_TXMAXP_MAXPAYLOAD_MASK  (0x07FF)
#define USB_TXMAXP_HIGHSPEED_MASK   (0xF800)

/* USB_TXCSR */
#define USB_TXCSR_TXPKTRDY      (0x0001)   /* RW */
#define USB_TXCSR_FIFONOTEMPTY      (0x0002)   /* RO */
#define USB_TXCSR_UNDERRUN      (0x0004)   /* RW */
#define USB_TXCSR_FLUSHFIFO     (0x0008)   /* WO */
#define USB_TXCSR_SENDSTALL     (0x0010)   /* RW */
#define USB_TXCSR_SENTSTALL     (0x0020)   /* RC */
#define USB_TXCSR_CLRDATATOG        (0x0040)   /* WO */
#define USB_TXCSR_INCOMPTX      (0x0080)   /* RC */
#define USB_TXCSR_SETTXPKTRDY_TWICE (0x0100)   /* RC */
#define USB_TXCSR_DMAREQMODE        (0x0400)   /* RW */
#define USB_TXCSR_FRCDATATOG        (0x0800)   /* RW */
#define USB_TXCSR_DMAREQENAB        (0x1000)   /* RW */
#define USB_TXCSR_MODE          (0x2000)   /* RW */
#define USB_TXCSR_ISO           (0x4000)   /* RW */
#define USB_TXCSR_AUTOSET       (0x8000)   /* RW */
/* in Host mode */
#define USB_TXCSR_ERROR         (0x0004)
#define USB_TXCSR_RXSTALL       (0x0020)
#define USB_TXCSR_NAKTIMEOUT        (0x0080)

/* USB_RXMAXP */
#define USB_RXMAXP_MAXPAYLOAD_MASK  (0x07FF)
#define USB_RXMAXP_HIGHSPEED_MASK   (0xF800)

/* USB_RXCSR */
#define USB_RXCSR_RXPKTRDY      (0x0001)   /* RC */
#define USB_RXCSR_FIFOFULL      (0x0002)   /* RO, AC */
#define USB_RXCSR_OVERRUN       (0x0004)   /* RC */
#define USB_RXCSR_DATAERROR     (0x0008)   /* RO */
#define USB_RXCSR_FLUSHFIFO     (0x0010)   /* WO, AC */
#define USB_RXCSR_SENDSTALL     (0x0020)   /* RW */
#define USB_RXCSR_SENTSTALL     (0x0040)   /* RC */
#define USB_RXCSR_CLRDATATOG        (0x0080)   /* WO */
#define USB_RXCSR_INCOMPRX      (0x0100)   /* RC */
#define USB_RXCSR_KEEPERRCTATUS     (0x0200)   /* RC */
#define USB_RXCSR_DMAREQMODE        (0x0800)   /* RW */
#define USB_RXCSR_DISNYET       (0x1000)   /* RW */
#define USB_RXCSR_PIDERROR      (0x1000)   /* RO */
#define USB_RXCSR_DMAREQENAB        (0x2000)   /* RW */
#define USB_RXCSR_ISO           (0x4000)   /* RW */
#define USB_RXCSR_AUTOCLEAR     (0x8000)   /* RW */
/* in Host mode */
#define USB_RXCSR_ERROR         (0x0004)
#define USB_RXCSR_NAKTIMEOUT        (0x0008)
#define USB_RXCSR_REQPKT        (0x0020)
#define USB_RXCSR_RXSTALL       (0x0040)
#define USB_RXCSR_SETPEQPKT_TWICE   (0x0400)
#define USB_RXCSR_AUTOREQ       (0x4000)

/* USB_TXTYPE */
#define USB_TXTYPE_EPNUM_MASK       (0x0f)
#define USB_TXTYPE_ISO          (0x10)
#define USB_TXTYPE_BULK         (0x20)
#define USB_TXTYPE_INTR         (0x30)
#define USB_TXTYPE_PROTOCOL_MASK    (0x30)

/* USB_RXTYPE */
#define USB_RXTYPE_EPNUM_MASK       (0x0f)
#define USB_RXTYPE_ISO          (0x10)
#define USB_RXTYPE_BULK         (0x20)
#define USB_RXTYPE_INTR         (0x30)
#define USB_RXTYPE_PROTOCOL_MASK    (0x30)

/* USB_PWRUPCNT */
#define USB_PWRUPCNT_MASK       (0x0f)

/* USB_FIFOSZ */
#define USB_FIFOSZ_SIZE_MASK        (0x0F)
#define USB_FIFOSZ_DPB          (0x10)
#define USB_FIFOSZ_SIZE_8       (0x00)
#define USB_FIFOSZ_SIZE_16      (0x01)
#define USB_FIFOSZ_SIZE_32      (0x02)
#define USB_FIFOSZ_SIZE_64      (0x03)
#define USB_FIFOSZ_SIZE_128     (0x04)
#define USB_FIFOSZ_SIZE_256     (0x05)
#define USB_FIFOSZ_SIZE_512     (0x06)
#define USB_FIFOSZ_SIZE_1024        (0x07)
#define USB_FIFOSZ_SIZE_2048        (0x08)
#define USB_FIFOSZ_SIZE_4096        (0x09)

/* USB_FIFOADD */
#define USB_FIFOADD_MASK        (0x1FFF)

/* USB_RXFIFOADD */
#define USB_RXFIFOADD_DATAERRINTREN (0x8000)
#define USB_RXFIFOADD_OVERRUNINTREN (0x4000)

/* USB_FIFO2ADD */
#define USB_FIFO2ADD_MASK       (0x1FFF)
#define USB_FIFO2ADD_EN         (0x8000)

/* -------------------- USB PHY Registers -------------------- */
#define USB_PHY_BASE_OFFSET     (0x400)

/* USB_ISCR */
#define USB_ISCR_VBUS_VALID_FROM_DATA   (0x40000000)
#define USB_ISCR_VBUS_VALID_FROM_VBUS   (0x20000000)
#define USB_ISCR_EXT_ID_STATUS      (0x10000000)
#define USB_ISCR_EXT_DM_STATUS      (0x08000000)
#define USB_ISCR_EXT_DP_STATUS      (0x04000000)
#define USB_ISCR_MERGED_VBUS_STATUS (0x02000000)
#define USB_ISCR_MERGED_ID_STATUS   (0x01000000)
#define USB_ISCR_ID_PULLUP_EN       (0x00020000)
#define USB_ISCR_DPDM_PULLUP_EN     (0x00010000)
#define USB_ISCR_FORCE_ID_LOW       (0x8000)
#define USB_ISCR_FORCE_ID_HIGH      (0xc000)
#define USB_ISCR_FORCE_ID_DISABLED  (0x0)
#define USB_ISCR_FORCE_ID_MASK      (0xc000)
#define USB_ISCR_FORCE_VBUS_LOW     (0x2000)
#define USB_ISCR_FORCE_VBUS_HIGH    (0x3000)
#define USB_ISCR_FORCE_VBUS_DISABLED    (0x0)
#define USB_ISCR_FORCE_VBUS_MASK    (0x3000)
#define USB_ISCR_VBUS_VALID_SRC_DPDM    (0X0800)
#define USB_ISCR_VBUS_VALID_SRC_ALL (0X0c00)
#define USB_ISCR_VBUS_VALID_SRC_MASK    (0X0c00)
#define USB_ISCR_HOSC_EN        (0X0080)
#define USB_ISCR_VBUS_CHANGE_DETECT (0X0040)
#define USB_ISCR_ID_CHANGE_DETECT   (0X0020)
#define USB_ISCR_DPDM_CHANGE_DETECT (0X0010)
#define USB_ISCR_IRQ_ENABLE     (0X0008)
#define USB_ISCR_VBUS_CHANGE_DETECT_EN  (0X0004)
#define USB_ISCR_ID_CHANGE_DETECT_EN    (0X0002)
#define USB_ISCR_DPDM_CHANGE_DETECT_EN  (0X0001)

/* USB_PHY_CTL 28nm */
#define USB_PHYCTL28NM_SIDDQ        (0X0008)
#define USB_PHYCTL28NM_VBUSVLDEXT   (0X0020)

/* USB_PHY_SEL */
#define USB_PHYSEL_OTG_SEL      (0x0001)

/* Register operations */
#define DRV_WriteReg(addr, data)    hal_writew(data, addr)
#define DRV_Reg(addr)           hal_readw(addr)
#define DRV_WriteReg32(addr, data)  hal_writel(data, addr)
#define DRV_Reg32(addr)         hal_readl(addr)
#define DRV_WriteReg8(addr, data)   hal_writeb(data, addr)
#define DRV_Reg8(addr)          hal_readb(addr)
#define USB_DRV_WriteReg(addr, data)    hal_writew(data, addr)
#define USB_DRV_Reg(addr)       hal_readw(addr)
#define USB_DRV_WriteReg32(addr, data)  hal_writel(data, addr)
#define USB_DRV_Reg32(addr)     hal_readl(addr)
#define USB_DRV_WriteReg8(addr, data)   hal_writeb(data, addr)
#define USB_DRV_Reg8(addr)      hal_readb(addr)

#define USB_DRV_ClearBits(addr,data) { \
    uint16_t temp; \
    temp = DRV_Reg(addr); \
    temp &=~(data); \
    DRV_WriteReg(addr,temp); \
}

#define USB_DRV_SetBits(addr,data) { \
    uint16_t temp; \
    temp = DRV_Reg(addr); \
    temp |= (data); \
    DRV_WriteReg(addr,temp); \
}

#define USB_DRV_SetData(addr, bitmask, value) { \
    uint16_t temp;  \
    temp = (~(bitmask)) & DRV_Reg(addr); \
    temp |= ((value) & (bitmask)); \
    DRV_WriteReg(addr,temp); \
}

#define USB_DRV_ClearBits32(addr,data) { \
    uint32_t temp; \
    temp = DRV_Reg32(addr); \
    temp &=~(data); \
    DRV_WriteReg32(addr,temp); \
}

#define USB_DRV_SetBits32(addr,data) { \
    uint32_t temp; \
    temp = DRV_Reg32(addr); \
    temp |= (data); \
    DRV_WriteReg32(addr,temp); \
}

#define USB_DRV_SetData32(addr, bitmask, value) { \
    uint32_t temp; \
    temp = (~(bitmask)) & DRV_Reg32(addr); \
    temp |= ((value) & (bitmask)); \
    DRV_WriteReg32(addr,temp); \
}

#define USB_DRV_ClearBits8(addr,data) { \
    uint8_t temp; \
    temp = DRV_Reg8(addr); \
    temp &=~(data); \
    DRV_WriteReg8(addr,temp); \
}

#define USB_DRV_SetBits8(addr,data) { \
    uint8_t temp; \
    temp = DRV_Reg8(addr); \
    temp |= (data); \
    DRV_WriteReg8(addr,temp); \
}

#define USB_DRV_SetData8(addr, bitmask, value) { \
    uint8_t temp; \
    temp = (~(bitmask)) & DRV_Reg8(addr); \
    temp |= ((value) & (bitmask)); \
    DRV_WriteReg8(addr,temp); \
}

typedef struct {
    /* common registers */
    /* fifo */
    uint32_t    fifo0;      /* USBEndpoint0FIFORegister */
    uint32_t    fifo1;      /* USBEndpoint1FIFORegister */
    uint8_t     revered1[56];   /* 0x0000 + N*4 */
    uint8_t     power;      /* 0x0040 */
    uint8_t     devctl;     /* 0x0041 */
    uint8_t     index;      /* 0x0042 */
    uint8_t     vend0;      /* 0x0043 */
    uint16_t    intrtx;     /* 0x0044 */
    uint16_t    intrrx;     /* 0x0046 */
    uint16_t    intrtxe;    /* 0x0048 */
    uint16_t    intrrxe;    /* 0x004a */
    uint32_t    intrusb;    /* 0x004c */
    uint32_t    intrusbe;   /* 0x0050 */
    uint32_t    frame;      /* 0x0054 */
    uint32_t    reserved1[9];
    uint32_t    testmode;   /* 0x007c */
    /* indexed registers */
    uint16_t    txmap;      /* 0x0080 */
    uint16_t    txcsr;      /* 0x0082 */
    uint16_t    rxmap;      /* 0x0084 */
    uint16_t    rxcsr;      /* 0x0086 */
    uint32_t    rxcount;    /* 0x0088 */
    uint8_t     txtype;     /* 0x008c */
    uint8_t     txinterval; /* 0x008d */
    uint8_t     rxtype;     /* 0x008e */
    uint8_t     rxinterval; /* 0x008f */
    /* OTG, dynamic FIFO, version & vendor registers */
    uint16_t    txfifosz;   /* 0x0090 */
    uint16_t    txfifoadd;  /* 0x0092 */
    uint16_t    rxfifosz;   /* 0x0094 */
    uint16_t    rxfifoadd;  /* 0x0096 */
    uint8_t     faddr;      /* 0x0098 */
} UDC_REGISTER_T;

typedef struct {
    uint32_t    iscr;       /* 0x0400 */
    uint32_t    phyctrl40nm;    /* 0x0404 */
    uint32_t    phybist;    /* 0x0408 */
    uint32_t    reserved1;
    uint32_t    phyctrl28nm;    /* 0x0410 */
    uint32_t    phytest;    /* 0x0414 */
    uint32_t    phytune;    /* 0x0418 */
    uint32_t    reserved2;
    uint32_t    physel;     /* 0x0420 */
    uint32_t    physta;     /* 0x0424 */
} USBPHY_REGISTER_T;

#endif /*__UDC_PLATFORM_H__*/
