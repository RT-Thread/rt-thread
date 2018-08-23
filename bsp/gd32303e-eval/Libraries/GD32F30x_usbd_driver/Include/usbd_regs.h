/*!
    \file  usbd_regs.h
    \brief USB device registers
*/

/*
    Copyright (C) 2017 GigaDevice

    2017-02-10, V1.0.0, firmware for GD32F30x
*/

#ifndef USBD_REGS_H
#define USBD_REGS_H

#include "usbd_conf.h"

/* USB device registers base address */
#define USBD                           USBD_BASE
#define USBD_RAM                       (APB1_BUS_BASE + 0x00006000U)

/* registers definitions */
/* common registers */
#define USBD_CTL                       (REG32(USBD + 0x40U))  /*!< control register */
#define USBD_INTF                      (REG32(USBD + 0x44U))  /*!< interrupt flag register */
#define USBD_STAT                      (REG32(USBD + 0x48U))  /*!< status register */
#define USBD_DADDR                     (REG32(USBD + 0x4CU))  /*!< device address register */
#define USBD_BADDR                     (REG32(USBD + 0x50U))  /*!< buffer address register */

/* endpoint control and status register */
#define USBD_EPxCS(ep_id)              (REG32(USBD + (ep_id) * 4U))  /*!< endpoint x control and status register address */

/* LPM Registers */
#define USBD_LPMCS                     (REG32(USBD + 0x54U))  /*!< USBD LPM control and status register */

/* bits definitions */
/* USBD_CTL */
#define CTL_STIE                       BIT(15)  /*!< successful transfer interrupt enable mask */
#define CTL_PMOUIE                     BIT(14)  /*!< packet memory overrun/underrun interrupt enable mask */
#define CTL_ERRIE                      BIT(13)  /*!< error interrupt enable mask */
#define CTL_WKUPIE                     BIT(12)  /*!< wakeup interrupt enable mask */
#define CTL_SPSIE                      BIT(11)  /*!< suspend state interrupt enable mask */
#define CTL_RSTIE                      BIT(10)  /*!< reset interrupt enable mask */
#define CTL_SOFIE                      BIT(9)   /*!< start of frame interrupt enable mask */
#define CTL_ESOFIE                     BIT(8)   /*!< expected start of frame interrupt enable mask */
#define CTL_L1REQIE                    BIT(7)   /*!< LPM L1 state request interrupt enable */
#define CTL_L1RSREQ                    BIT(5)   /*!< LPM L1 resume request */
#define CTL_RSREQ                      BIT(4)   /*!< resume request */
#define CTL_SETSPS                     BIT(3)   /*!< set suspend state */
#define CTL_LOWM                       BIT(2)   /*!< low-power mode at suspend state */
#define CTL_CLOSE                      BIT(1)   /*!< goes to close state */
#define CTL_SETRST                     BIT(0)   /*!< set USB reset */

/* USBD_INTF */
#define INTF_STIF                      BIT(15)     /*!< successful transfer interrupt flag (read only bit) */
#define INTF_PMOUIF                    BIT(14)     /*!< packet memory overrun/underrun interrupt flag (clear-only bit) */
#define INTF_ERRIF                     BIT(13)     /*!< error interrupt flag (clear-only bit) */
#define INTF_WKUPIF                    BIT(12)     /*!< wakeup interrupt flag (clear-only bit) */
#define INTF_SPSIF                     BIT(11)     /*!< suspend state interrupt flag (clear-only bit) */
#define INTF_RSTIF                     BIT(10)     /*!< reset interrupt flag (clear-only bit) */
#define INTF_SOFIF                     BIT(9)      /*!< start of frame interrupt flag (clear-only bit) */
#define INTF_ESOFIF                    BIT(8)      /*!< expected start of frame interrupt flag(clear-only bit) */
#define INTF_L1REQ                     BIT(7)      /*!< LPM L1 transaction is successfully received and acknowledged */
#define INTF_DIR                       BIT(4)      /*!< direction of transaction (read-only bit) */
#define INTF_EPNUM                     BITS(0, 3)  /*!< endpoint number (read-only bit)  */

/* USBD_STAT */
#define STAT_RXDP                      BIT(15)       /*!< data plus line status */
#define STAT_RXDM                      BIT(14)       /*!< data minus line status */
#define STAT_LOCK                      BIT(13)       /*!< locked the USB */
#define STAT_SOFLN                     BITS(11, 12)  /*!< SOF lost number */
#define STAT_FCNT                      BITS(0, 10)   /*!< frame number count */

/* USBD_DADDR */
#define DADDR_USBEN                    BIT(7)      /*!< USB module enable */
#define DADDR_USBDAR                   BITS(0, 6)  /*!< USB device address */

/* USBD_EPxCS */
#define EPxCS_RX_ST                    BIT(15)       /*!< endpoint reception successful transferred */
#define EPxCS_RX_DTG                   BIT(14)       /*!< endpoint reception data PID toggle */
#define EPxCS_RX_STA                   BITS(12, 13)  /*!< endpoint reception status bits */
#define EPxCS_SETUP                    BIT(11)       /*!< endpoint setup transaction completed */
#define EPxCS_CTL                      BITS(9, 10)   /*!< endpoint type control */
#define EPxCS_KCTL                     BIT(8)        /*!< endpoint kind control */
#define EPxCS_TX_ST                    BIT(7)        /*!< endpoint transmission successful transfer */
#define EPxCS_TX_DTG                   BIT(6)        /*!< endpoint transmission data toggle */
#define EPxCS_TX_STA                   BITS(4, 5)    /*!< endpoint transmission transfers status bits */
#define EPxCS_ADDR                     BITS(0, 3)    /*!< endpoint address */

/* USBD_LPMCS */
#define LPMCS_BLSTAT                   BITS(4, 7)    /*!< bLinkState value */
#define LPMCS_REMWK                    BIT(3)        /*!< bRemoteWake value */
#define LPMCS_LPMACK                   BIT(1)        /*!< LPM token acknowledge enable */
#define LPMCS_LPMEN                    BIT(0)        /*!< LPM support enable */

/* constants definitions */
/* endpoint control and status register mask (no toggle fields) */
#define EPCS_MASK                      (EPxCS_RX_ST|EPxCS_SETUP|EPxCS_CTL|EPxCS_KCTL|EPxCS_TX_ST|EPxCS_ADDR)

/* EPxCS_CTL[1:0] endpoint type control */
#define ENDP_TYPE(regval)              (EPxCS_CTL & ((regval) << 9U))

#define EP_BULK                        ENDP_TYPE(0U)  /* bulk transfers */
#define EP_CONTROL                     ENDP_TYPE(1U)  /* control transfers */
#define EP_ISO                         ENDP_TYPE(2U)  /* isochronous transfers */
#define EP_INTERRUPT                   ENDP_TYPE(3U)  /* interrupt transfers */
#define EP_CTL_MASK                    (~EPxCS_CTL & EPCS_MASK)

/* endpoint kind control mask */
#define EPKCTL_MASK                    (~EPxCS_KCTL & EPCS_MASK)

/* EPxCS_TX_STA[1:0] status for Tx transfer */
#define ENDP_TXSTAT(regval)            (EPxCS_TX_STA & ((regval) << 4U))

#define EPTX_DISABLED                  ENDP_TXSTAT(0U)  /* transmission state is disabled */
#define EPTX_STALL                     ENDP_TXSTAT(1U)  /* transmission state is STALL */
#define EPTX_NAK                       ENDP_TXSTAT(2U)  /* transmission state is NAK */
#define EPTX_VALID                     ENDP_TXSTAT(3U)  /* transmission state is enabled */
#define EPTX_DTGMASK                   (EPxCS_TX_STA | EPCS_MASK)

/* EPxCS_RX_STA[1:0] status for Rx transfer */
#define ENDP_RXSTAT(regval)            (EPxCS_RX_STA & ((regval) << 12U))

#define EPRX_DISABLED                  ENDP_RXSTAT(0U)  /* reception state is disabled */
#define EPRX_STALL                     ENDP_RXSTAT(1U)  /* reception state is STALL */
#define EPRX_NAK                       ENDP_RXSTAT(2U)  /* reception state is NAK */
#define EPRX_VALID                     ENDP_RXSTAT(3U)  /* reception state is enabled */
#define EPRX_DTGMASK                   (EPxCS_RX_STA | EPCS_MASK)

/* endpoint receive/transmission counter register bit definitions */
#define EPRCNT_BLKSIZ                  BIT(15)       /* reception data block size */
#define EPRCNT_BLKNUM                  BITS(10, 14)  /* reception data block number */
#define EPRCNT_CNT                     BITS(0, 9)    /* reception data count */

#define EPTCNT_CNT                     BITS(0, 9)    /* transmisson data count */

/* interrupt flag clear bits */
#define CLR_STIF                       (~INTF_STIF)
#define CLR_PMOUIF                     (~INTF_PMOUIF)
#define CLR_ERRIF                      (~INTF_ERRIF)
#define CLR_WKUPIF                     (~INTF_WKUPIF)
#define CLR_SPSIF                      (~INTF_SPSIF)
#define CLR_RSTIF                      (~INTF_RSTIF)
#define CLR_SOFIF                      (~INTF_SOFIF)
#define CLR_ESOFIF                     (~INTF_ESOFIF)
#define CLR_L1REQ                      (~INTF_L1REQ)

/* endpoint receive/transmission counter register bit offset */
#define BLKSIZE_OFFSET                 (0x01U)
#define BLKNUM_OFFSET                  (0x05U)
#define RXCNT_OFFSET                   (0x0AU)

#define TXCNT_OFFSET                   (0x0AU)

#define BLKSIZE32_MASK                 (0x1fU)
#define BLKSIZE2_MASK                  (0x01U)

#define BLKSIZE32_OFFSETMASK           (0x05U)
#define BLKSIZE2_OFFSETMASK            (0x01U)

/* double buffer endpoint direction */
typedef enum
{
    DBUF_EP_IN,   /* double buffer IN direction */
    DBUF_EP_OUT,  /* double buffer OUT direction */
    DBUF_EP_ERR,  /* double buffer errer direction */
}dbuf_ep_dir_enum;

/* endpoints address */
/* first bit is direction(0 for Rx and 1 for Tx) */
#define EP0_OUT                        ((uint8_t)0x00)  /* OUT endpoint 0 address */
#define EP0_IN                         ((uint8_t)0x80)  /* IN endpoint 0 address */
#define EP1_OUT                        ((uint8_t)0x01)  /* OUT endpoint 1 address */
#define EP1_IN                         ((uint8_t)0x81)  /* IN endpoint 1 address */
#define EP2_OUT                        ((uint8_t)0x02)  /* OUT endpoint 2 address */
#define EP2_IN                         ((uint8_t)0x82)  /* IN endpoint 2 address */
#define EP3_OUT                        ((uint8_t)0x03)  /* OUT endpoint 3 address */
#define EP3_IN                         ((uint8_t)0x83)  /* IN endpoint 3 address */
#define EP4_OUT                        ((uint8_t)0x04)  /* OUT endpoint 4 address */
#define EP4_IN                         ((uint8_t)0x84)  /* IN endpoint 4 address */
#define EP5_OUT                        ((uint8_t)0x05)  /* OUT endpoint 5 address */
#define EP5_IN                         ((uint8_t)0x85)  /* IN endpoint 5 address */
#define EP6_OUT                        ((uint8_t)0x06)  /* OUT endpoint 6 address */
#define EP6_IN                         ((uint8_t)0x86)  /* IN endpoint 6 address */
#define EP7_OUT                        ((uint8_t)0x07)  /* OUT endpoint 7 address */
#define EP7_IN                         ((uint8_t)0x87)  /* IN endpoint 7 address */

/* endpoints_Identifier */
#define EP0                            ((uint8_t)0)  /* endpoint 0 ID */
#define EP1                            ((uint8_t)1)  /* endpoint 1 ID */
#define EP2                            ((uint8_t)2)  /* endpoint 2 ID */
#define EP3                            ((uint8_t)3)  /* endpoint 3 ID */
#define EP4                            ((uint8_t)4)  /* endpoint 4 ID */
#define EP5                            ((uint8_t)5)  /* endpoint 5 ID */
#define EP6                            ((uint8_t)6)  /* endpoint 6 ID */
#define EP7                            ((uint8_t)7)  /* endpoint 7 ID */

/* USBD operation macros */

/* set register value */
#define USBD_REG_SET(reg, regvalue)    ((reg) = (uint16_t)(regvalue))

/* get register value */
#define USBD_REG_GET(reg)              ((uint16_t)(reg))

#define _EP_ADDR_SET(ep_num, addr)     USBD_REG_SET(USBD_EPxCS(ep_num), (USBD_REG_GET(USBD_EPxCS(ep_num)) & EPCS_MASK) | addr)

/* Tx or Rx transfer status setting (bits EPTX_STA[1:0]) */
#define USBD_ENDP_TX_STATUS_SET(ep_num, state) do {\
    register uint16_t _regval;       \
    _regval = USBD_REG_GET(USBD_EPxCS(ep_num)) & (uint16_t)EPTX_DTGMASK;\
    USBD_REG_SET(USBD_EPxCS(ep_num), ((_regval) ^ (state)));    \
} while(0)

#define USBD_ENDP_RX_STATUS_SET(ep_num, state) do {\
    register uint16_t _regval;   \
    _regval = USBD_REG_GET(USBD_EPxCS(ep_num)) & (uint16_t)EPRX_DTGMASK;\
    USBD_REG_SET(USBD_EPxCS(ep_num), ((_regval) ^ (state))); \
} while(0)

/* Tx or Rx transfer status getting (bits EPxCS_RX_STA[1:0]) */
#define USBD_ENDP_TX_STATUS_GET(ep_num) (USBD_REG_GET(USBD_EPxCS(ep_num)) & EPxCS_TX_STA)
#define USBD_ENDP_RX_STATUS_GET(ep_num) (USBD_REG_GET(USBD_EPxCS(ep_num)) & EPxCS_RX_STA)

/* Rx and Tx transfer status setting (bits EPxCS_RX_STA[1:0] & EPxCS_TX_STA[1:0]) */
#define USBD_ENDP_RX_TX_STATUS_SET(ep_num, state_rx, state_tx) do {\
    register uint16_t _regval;   \
    _regval = USBD_REG_GET(USBD_EPxCS(ep_num)) & (uint16_t)(EPRX_DTGMASK | EPxCS_TX_STA) ;\
    USBD_REG_SET(USBD_EPxCS(ep_num), (((_regval) ^ (state_rx)) ^ (state_tx)));    \
} while(0)

/* set and clear endpoint kind (bit EPxCS_KCTL) */
#define USBD_ENDP_KIND_SET(ep_num)      (USBD_REG_SET(USBD_EPxCS(ep_num), ((USBD_REG_GET(USBD_EPxCS(ep_num)) | EPxCS_KCTL) & EPCS_MASK)))
#define USBD_ENDP_KIND_CLEAR(ep_num)    (USBD_REG_SET(USBD_EPxCS(ep_num), (USBD_REG_GET(USBD_EPxCS(ep_num)) & EPKCTL_MASK)))

/* set and clear directly STATUS_OUT state of endpoint */
#define USBD_STATUS_OUT_SET(ep_num)     USBD_ENDP_KIND_SET(ep_num)
#define USBD_STATUS_OUT_CLEAR(ep_num)   USBD_ENDP_KIND_CLEAR(ep_num)

/* clear bit EPxCS_RX_ST/EPxCS_TX_ST in the endpoint control and status register */
#define USBD_ENDP_RX_STAT_CLEAR(ep_num) (USBD_REG_SET(USBD_EPxCS(ep_num), USBD_REG_GET(USBD_EPxCS(ep_num)) & 0x7FFFU & (uint16_t)EPCS_MASK))
#define USBD_ENDP_TX_STAT_CLEAR(ep_num) (USBD_REG_SET(USBD_EPxCS(ep_num), USBD_REG_GET(USBD_EPxCS(ep_num)) & 0xFF7FU & (uint16_t)EPCS_MASK))

/* toggle EPxCS_RX_DTG or EPxCS_TX_DTG bit in the endpoint control and status register */
#define USBD_DTG_RX_TOGGLE(ep_num)      (USBD_REG_SET(USBD_EPxCS(ep_num), EPxCS_RX_DTG | (USBD_REG_GET(USBD_EPxCS(ep_num)) & EPCS_MASK)))
#define USBD_DTG_TX_TOGGLE(ep_num)      (USBD_REG_SET(USBD_EPxCS(ep_num), EPxCS_TX_DTG | (USBD_REG_GET(USBD_EPxCS(ep_num)) & EPCS_MASK)))

/* clear EPxCS_RX_DTG or EPxCS_TX_DTG bit in the endpoint control and status register */
#define USBD_DTG_RX_CLEAR(ep_num)       do {\
    if ((USBD_REG_GET(USBD_EPxCS(ep_num)) & EPxCS_RX_DTG) != 0U) {\
        USBD_DTG_RX_TOGGLE(ep_num);\
    } else {\
    }\
} while(0)

#define USBD_DTG_TX_CLEAR(ep_num)       do {\
    if ((USBD_REG_GET(USBD_EPxCS(ep_num)) & EPxCS_TX_DTG) != 0U) {\
        USBD_DTG_TX_TOGGLE(ep_num);\
    } else {\
    }\
} while(0)

/* set and clear directly double buffered feature of endpoint */
#define USBD_ENDP_DOUBLE_BUF_SET(ep_num)   USBD_ENDP_KIND_SET(ep_num)
#define USBD_ENDP_DOUBLE_BUF_CLEAR(ep_num) USBD_ENDP_KIND_CLEAR(ep_num)

/* toggle SW_BUF bit in the double buffered endpoint */
#define USBD_SWBUF_TX_TOGGLE(ep_num)    USBD_DTG_RX_TOGGLE(ep_num)
#define USBD_SWBUF_RX_TOGGLE(ep_num)    USBD_DTG_TX_TOGGLE(ep_num)

#endif /* USBD_REGS_H */
