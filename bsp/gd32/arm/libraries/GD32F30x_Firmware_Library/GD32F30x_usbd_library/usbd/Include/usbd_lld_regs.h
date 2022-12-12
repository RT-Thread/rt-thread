/*!
    \file    usbd_lld_regs.h
    \brief   USB device low level registers

    \version 2020-08-01, V3.0.0, firmware for GD32F30x
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#ifndef __USBD_LLD_REGS_H
#define __USBD_LLD_REGS_H

#include "usbd_conf.h"

/* USB device registers base address */
#define USBD                           USBD_BASE
#define USBD_RAM                       USBD_RAM_BASE

/* registers definitions */
/* common registers */
#define USBD_CTL                       (REG32(USBD + 0x40U))          /*!< control register */
#define USBD_INTF                      (REG32(USBD + 0x44U))          /*!< interrupt flag register */
#define USBD_STAT                      (REG32(USBD + 0x48U))          /*!< status register */
#define USBD_DADDR                     (REG32(USBD + 0x4CU))          /*!< device address register */
#define USBD_BADDR                     (REG32(USBD + 0x50U))          /*!< buffer address register */
#define USBD_LPMCS                     (REG32(USBD + 0x54U))          /*!< USBD LPM control and status register */

/* endpoint control and status register */
#define USBD_EPxCS(ep_num)             (REG32(USBD + (ep_num) * 4U))  /*!< endpoint x control and status register address */

/* bits definitions */
/* USBD_CTL */
#define CTL_STIE                       BIT(15)          /*!< successful transfer interrupt enable mask */
#define CTL_PMOUIE                     BIT(14)          /*!< packet memory overrun/underrun interrupt enable mask */
#define CTL_ERRIE                      BIT(13)          /*!< error interrupt enable mask */
#define CTL_WKUPIE                     BIT(12)          /*!< wakeup interrupt enable mask */
#define CTL_SPSIE                      BIT(11)          /*!< suspend state interrupt enable mask */
#define CTL_RSTIE                      BIT(10)          /*!< reset interrupt enable mask */
#define CTL_SOFIE                      BIT(9)           /*!< start of frame interrupt enable mask */
#define CTL_ESOFIE                     BIT(8)           /*!< expected start of frame interrupt enable mask */
#define CTL_L1REQIE                    BIT(7)           /*!< LPM L1 state request interrupt enable */
#define CTL_L1RSREQ                    BIT(5)           /*!< LPM L1 resume request */
#define CTL_RSREQ                      BIT(4)           /*!< resume request */
#define CTL_SETSPS                     BIT(3)           /*!< set suspend state */
#define CTL_LOWM                       BIT(2)           /*!< low-power mode at suspend state */
#define CTL_CLOSE                      BIT(1)           /*!< goes to close state */
#define CTL_SETRST                     BIT(0)           /*!< set USB reset */

#ifdef LPM_ENABLED
#define USBD_INTEN                     BITS(7, 15)      /*!< USBD interrupt enable bits */
#else
#define USBD_INTEN                     BITS(8, 15)      /*!< USBD interrupt enable bits */
#endif
/* USBD_INTF */
#define INTF_STIF                      BIT(15)          /*!< successful transfer interrupt flag (read only bit) */
#define INTF_PMOUIF                    BIT(14)          /*!< packet memory overrun/underrun interrupt flag (clear-only bit) */
#define INTF_ERRIF                     BIT(13)          /*!< error interrupt flag (clear-only bit) */
#define INTF_WKUPIF                    BIT(12)          /*!< wakeup interrupt flag (clear-only bit) */
#define INTF_SPSIF                     BIT(11)          /*!< suspend state interrupt flag (clear-only bit) */
#define INTF_RSTIF                     BIT(10)          /*!< reset interrupt flag (clear-only bit) */
#define INTF_SOFIF                     BIT(9)           /*!< start of frame interrupt flag (clear-only bit) */
#define INTF_ESOFIF                    BIT(8)           /*!< expected start of frame interrupt flag(clear-only bit) */
#define INTF_L1REQ                     BIT(7)           /*!< LPM L1 transaction is successfully received and acknowledged */
#define INTF_DIR                       BIT(4)           /*!< direction of transaction (read-only bit) */
#define INTF_EPNUM                     BITS(0, 3)       /*!< endpoint number (read-only bit)  */

/* USBD_STAT */
#define STAT_RXDP                      BIT(15)          /*!< data plus line status */
#define STAT_RXDM                      BIT(14)          /*!< data minus line status */
#define STAT_LOCK                      BIT(13)          /*!< locked the USB */
#define STAT_SOFLN                     BITS(11, 12)     /*!< SOF lost number */
#define STAT_FCNT                      BITS(0, 10)      /*!< frame number count */

/* USBD_DADDR */
#define DADDR_USBEN                    BIT(7)           /*!< USB module enable */
#define DADDR_USBADDR                  BITS(0, 6)       /*!< USB device address */

/* USBD_EPxCS */
#define EPxCS_RX_ST                    BIT(15)          /*!< endpoint reception successful transferred */
#define EPxCS_RX_DTG                   BIT(14)          /*!< endpoint reception data PID toggle */
#define EPxCS_RX_STA                   BITS(12, 13)     /*!< endpoint reception status bits */
#define EPxCS_SETUP                    BIT(11)          /*!< endpoint setup transaction completed */
#define EPxCS_CTL                      BITS(9, 10)      /*!< endpoint type control */
#define EPxCS_KCTL                     BIT(8)           /*!< endpoint kind control */
#define EPxCS_TX_ST                    BIT(7)           /*!< endpoint transmission successful transfer */
#define EPxCS_TX_DTG                   BIT(6)           /*!< endpoint transmission data toggle */
#define EPxCS_TX_STA                   BITS(4, 5)       /*!< endpoint transmission transfers status bits */
#define EPxCS_AR                       BITS(0, 3)       /*!< endpoint address */

/* USBD_LPMCS */
#define LPMCS_BLSTAT                   BITS(4, 7)       /*!< bLinkState value */
#define LPMCS_REMWK                    BIT(3)           /*!< bRemoteWake value */
#define LPMCS_LPMACK                   BIT(1)           /*!< LPM token acknowledge enable */
#define LPMCS_LPMEN                    BIT(0)           /*!< LPM support enable */

/* constants definitions */
/* endpoint control and status register mask (no toggle fields) */
#define EPCS_MASK                      (EPxCS_RX_ST | EPxCS_SETUP | \
                                        EPxCS_CTL | EPxCS_KCTL | EPxCS_TX_ST | EPxCS_AR)

/* EPxCS_CTL[1:0] endpoint type control */
#define ENDP_TYPE(regval)              (EPxCS_CTL & ((regval) << 9U))

#define EP_BULK                        ENDP_TYPE(0U)    /* bulk transfers */
#define EP_CONTROL                     ENDP_TYPE(1U)    /* control transfers */
#define EP_ISO                         ENDP_TYPE(2U)    /* isochronous transfers */
#define EP_INTERRUPT                   ENDP_TYPE(3U)    /* interrupt transfers */
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
#define EPRCNT_BLKSIZ                  BIT(15)          /* reception data block size */
#define EPRCNT_BLKNUM                  BITS(10, 14)     /* reception data block number */
#define EPRCNT_CNT                     BITS(0, 9)       /* reception data count */

#define EPTCNT_CNT                     BITS(0, 9)       /* transmisson data count */

/* interrupt flag clear bits */
#define CLR(x)                         (USBD_INTF = ~INTF_##x)

/* endpoint receive/transmission counter register bit offset */
#define BLKSIZE_OFFSET                 (0x01U)
#define BLKNUM_OFFSET                  (0x05U)
#define RXCNT_OFFSET                   (0x0AU)

#define TXCNT_OFFSET                   (0x0AU)

#define BLKSIZE32_MASK                 (0x1fU)
#define BLKSIZE2_MASK                  (0x01U)

#define BLKSIZE32_OFFSETMASK           (0x05U)
#define BLKSIZE2_OFFSETMASK            (0x01U)

/* USBD operation macros */

/* Tx or Rx transfer status setting (bits EPTX_STA[1:0]) */

#define USBD_EP_TX_STAT_SET(ep, stat) do {\
    USBD_EPxCS(ep) = (USBD_EPxCS(ep) & (uint16_t)EPTX_DTGMASK) ^ (stat); \
} while(0)

#define USBD_EP_RX_STAT_SET(ep, stat) do {\
    USBD_EPxCS(ep) = (USBD_EPxCS(ep) & (uint16_t)EPRX_DTGMASK) ^ (stat); \
} while(0)

/* clear bit EPxCS_RX_ST/EPxCS_TX_ST in the endpoint control and status register */

#define USBD_EP_TX_ST_CLEAR(ep) do {\
    USBD_EPxCS(ep) &= ~EPxCS_TX_ST & (uint16_t)EPCS_MASK; \
} while(0)

#define USBD_EP_RX_ST_CLEAR(ep) do {\
    USBD_EPxCS(ep) &= ~EPxCS_RX_ST & (uint16_t)EPCS_MASK; \
} while(0)

/* toggle EPxCS_RX_DTG or EPxCS_TX_DTG bit in the endpoint control and status register */

#define USBD_TX_DTG_TOGGLE(ep) do {\
    USBD_EPxCS(ep) = EPxCS_TX_DTG | (USBD_EPxCS(ep) & EPCS_MASK); \
} while(0)

#define USBD_RX_DTG_TOGGLE(ep) do {\
    USBD_EPxCS(ep) = EPxCS_RX_DTG | (USBD_EPxCS(ep) & EPCS_MASK); \
} while(0)

/* clear EPxCS_RX_DTG or EPxCS_TX_DTG bit in the endpoint control and status register */

#define USBD_TX_DTG_CLEAR(ep) do {\
    if ((USBD_EPxCS(ep_num) & EPxCS_TX_DTG) != 0U) {\
        USBD_TX_DTG_TOGGLE(ep);\
    } \
} while(0)

#define USBD_RX_DTG_CLEAR(ep) do {\
    if ((USBD_EPxCS(ep_num) & EPxCS_RX_DTG) != 0U) {\
        USBD_RX_DTG_TOGGLE(ep);\
    } \
} while(0)

#define USBD_EP_DBL_BUF_SET(ep) (USBD_EPxCS(ep) = (USBD_EPxCS(ep) | EPxCS_KCTL) & EPCS_MASK)

#endif /* __USBD_LLD_REGS_H */
