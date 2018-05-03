/*!
    \file  usb_regs.h
    \brief USB FS&HS cell registers definition and handle macros
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#ifndef USB_REGS_H
#define USB_REGS_H

#include "usb_conf.h"

#define USBFS                     USBFS_BASE                              /*!< base address of USBFS registers */
#define USBHS                     USBHS_BASE                              /*!< base address of USBHS registers */

#ifdef USE_USBFS
    #define USBX    USBFS                                                 /*!< USB full speed mode */
#endif /* USE_USBFS */

#ifdef USE_USBHS
    #define USBX    USBHS                                                 /*!< USB high speed mode */
#endif /* USE_USBHS */

/* registers location definitions */
#define LOCATE_DIEPTFLEN(x)       (0x104U + 4U * ((x) - 1U))              /*!< locate device IN endpoint-x transfer length registers */
#define LOCATE_HCHCTL(x)          (0x500U + 0x20U * (x))                  /*!< locate host channel-x control registers */
#define LOCATE_HCHSTCTL(x)        (0x504U + 0x20U * (x))                  /*!< locate host channel-x split transaction control registers */
#define LOCATE_HCHINTF(x)         (0x508U + 0x20U * (x))                  /*!< locate host channel-x interrupt flag registers */
#define LOCATE_HCHINTEN(x)        (0x50CU + 0x20U * (x))                  /*!< locate host channel-x interrupt enable registers */
#define LOCATE_HCHLEN(x)          (0x510U + 0x20U * (x))                  /*!< locate host channel-x transfer length registers */
#define LOCATE_HCHDMAADDR(x)      (0x514U + 0x20U * (x))                  /*!< locate host channel-x DMA address registers */
#define LOCATE_DIEPCTL(x)         (0x900U + 0x20U * (x))                  /*!< locate device IN endpoint-x control registers */
#define LOCATE_DOEPCTL(x)         (0xB00U + 0x20U * (x))                  /*!< locate device OUT endpoint-x control registers */
#define LOCATE_DIEPINTF(x)        (0x908U + 0x20U * (x))                  /*!< locate device IN endpoint-x interrupt flag registers */
#define LOCATE_DOEPINTF(x)        (0xB08U + 0x20U * (x))                  /*!< locate device OUT endpoint-x interrupt flag registers */
#define LOCATE_DIEPLEN(x)         (0x910U + 0x20U * (x))                  /*!< locate device IN endpoint-x transfer length registers */
#define LOCATE_DOEPLEN(x)         (0xB10U + 0x20U * (x))                  /*!< locate device OUT endpoint-x transfer length registers */
#define LOCATE_DIEPxDMAADDR(x)    (0x914U + 0x20U * (x))                  /*!< locate device IN endpoint-x DMA address registers */
#define LOCATE_DOEPxDMAADDR(x)    (0xB14U + 0x20U * (x))                  /*!< locate device OUT endpoint-x DMA address registers */
#define LOCATE_DIEPxTFSTAT(x)     (0x918U + 0x20U * (x))                  /*!< locate Device IN endpoint-x transmit FIFO status register */
#define LOCATE_FIFO(x)            (((x) + 1U) << 12U)                     /*!< locate FIFO-x memory */

/* registers definitions */
#define USB_GOTGCS                REG32(((USBX) + 0x0000U))               /*!< global OTG control and status register */
#define USB_GOTGINTF              REG32(((USBX) + 0x0004U))               /*!< global OTG interrupt flag register */
#define USB_GAHBCS                REG32(((USBX) + 0x0008U))               /*!< global AHB control and status register */
#define USB_GUSBCS                REG32(((USBX) + 0x000CU))               /*!< global USB control and status register */
#define USB_GRSTCTL               REG32(((USBX) + 0x0010U))               /*!< global reset control register */
#define USB_GINTF                 REG32(((USBX) + 0x0014U))               /*!< global interrupt flag register */
#define USB_GINTEN                REG32(((USBX) + 0x0018U))               /*!< global interrupt enable register */
#define USB_GRSTATR               REG32(((USBX) + 0x001CU))               /*!< global receive status read register */
#define USB_GRSTATP               REG32(((USBX) + 0x0020U))               /*!< global receive status read and pop register */
#define USB_GRFLEN                REG32(((USBX) + 0x0024U))               /*!< global receive FIFO length register */
#define USB_HNPTFLEN              REG32(((USBX) + 0x0028U))               /*!< host non-periodic transmit FIFO length register */
#define USB_DIEP0TFLEN            REG32(((USBX) + 0x0028U))               /*!< device IN endpoint 0 transmit FIFO length register */
#define USB_HNPTFQSTAT            REG32(((USBX) + 0x002CU))               /*!< host non-periodic transmint FIFO/queue status register */
#define USB_GCCFG                 REG32(((USBX) + 0x0038U))               /*!< global core configuration register */
#define USB_CID                   REG32(((USBX) + 0x003CU))               /*!< core id register */
#define USB_HPTFLEN               REG32(((USBX) + 0x0100U))               /*!< host periodic transmit FIFO length register */
#define USB_DIEPxTFLEN(x)         REG32(((USBX) + LOCATE_DIEPTFLEN(x)))   /*!< device IN endpoint transmit FIFO length register */

#define USB_HCTL                  REG32(((USBX) + 0x0400U))               /*!< host control register */
#define USB_HFT                   REG32(((USBX) + 0x0404U))               /*!< host frame interval register */
#define USB_HFINFR                REG32(((USBX) + 0x0408U))               /*!< host frame information remaining register */
#define USB_HPTFQSTAT             REG32(((USBX) + 0x0410U))               /*!< host periodic transmit FIFO/queue status register */
#define USB_HACHINT               REG32(((USBX) + 0x0414U))               /*!< host all channels interrupt register */
#define USB_HACHINTEN             REG32(((USBX) + 0x0418U))               /*!< host all channels interrupt enable register */
#define USB_HPCS                  REG32(((USBX) + 0x0440U))               /*!< host port control and status register */
#define USB_HCHxCTL(x)            REG32(((USBX) + LOCATE_HCHCTL(x)))      /*!< host channel-x control register */
#define USB_HCHxSTCTL(x)          REG32(((USBX) + LOCATE_HCHSTCTL(x)))    /*!< host channel-x split transaction control register */
#define USB_HCHxINTF(x)           REG32(((USBX) + LOCATE_HCHINTF(x)))     /*!< host channel-x interrupt flag register */
#define USB_HCHxINTEN(x)          REG32(((USBX) + LOCATE_HCHINTEN(x)))    /*!< host channel-x interrupt enable register */
#define USB_HCHxLEN(x)            REG32(((USBX) + LOCATE_HCHLEN(x)))      /*!< host channel-x tranfer length register */
#define USB_HCHxDMAADDR(x)        REG32(((USBX) + LOCATE_HCHDMAADDR(x)))  /*!< host channel-x DMA address register */

#define USB_DCFG                  REG32(((USBX) + 0x0800U))               /*!< device configuration register */
#define USB_DCTL                  REG32(((USBX) + 0x0804U))               /*!< device control register */
#define USB_DSTAT                 REG32(((USBX) + 0x0808U))               /*!< device status register */
#define USB_DIEPINTEN             REG32(((USBX) + 0x0810U))               /*!< device IN endpoint common interrupt enable register */
#define USB_DOEPINTEN             REG32(((USBX) + 0x0814U))               /*!< device OUT endpoint common interrupt enable register */
#define USB_DAEPINT               REG32(((USBX) + 0x0818U))               /*!< device all endpoints interrupt register */
#define USB_DAEPINTEN             REG32(((USBX) + 0x081CU))               /*!< device all endpoints interrupt enable register */
#define USB_DVBUSDT               REG32(((USBX) + 0x0828U))               /*!< device vbus discharge time register */
#define USB_DVBUSPT               REG32(((USBX) + 0x082CU))               /*!< device vbus pulsing time register */
#define USB_DIEPFEINTEN           REG32(((USBX) + 0x0834U))               /*!< device IN endpoint FIFO empty interrupt enable register */
#define USB_DEP1INT               REG32(((USBX) + 0x0838U))               /*!< device endpoint 1 interrupt register */
#define USB_DEP1INTEN             REG32(((USBX) + 0x083CU))               /*!< device endpoint 1 interrupt enable register */
#define USB_DIEP1INTEN            REG32(((USBX) + 0x0844U))               /*!< device IN endpoint 1 interrupt enable register */
#define USB_DOEP1INTEN            REG32(((USBX) + 0x0884U))               /*!< device OUT endpoint 1 interrupt enable register */
#define USB_DIEP0CTL              REG32(((USBX) + 0x0900U))               /*!< device IN endpoint 0 control register */
#define USB_DIEP0LEN              REG32(((USBX) + 0x0910U))               /*!< device IN endpoint 0 transfer length register */
#define USB_DOEP0CTL              REG32(((USBX) + 0x0B00U))               /*!< device OUT endpoint 0 control register */
#define USB_DOEP0LEN              REG32(((USBX) + 0x0B10U))               /*!< device OUT endpoint 0 transfer length register */
#define USB_DIEPxCTL(x)           REG32(((USBX) + LOCATE_DIEPCTL(x)))     /*!< device IN endpoint-x control register */
#define USB_DOEPxCTL(x)           REG32(((USBX) + LOCATE_DOEPCTL(x)))     /*!< device OUT endpoint-x control register */
#define USB_DIEPxINTF(x)          REG32(((USBX) + LOCATE_DIEPINTF(x)))    /*!< device IN endpoint-x interrupt flag register */
#define USB_DOEPxINTF(x)          REG32(((USBX) + LOCATE_DOEPINTF(x)))    /*!< device OUT endpoint-x interrupt flag register */
#define USB_DIEPxLEN(x)           REG32(((USBX) + LOCATE_DIEPLEN(x)))     /*!< device IN endpoint-x transfer length register */
#define USB_DOEPxLEN(x)           REG32(((USBX) + LOCATE_DOEPLEN(x)))     /*!< device OUT endpoint-x transfer length register */
#define USB_DIEPxDMAADDR(x)       REG32(((USBX) + LOCATE_DIEPxDMAADDR(x)))/*!< device IN endpoint-x DMA address register */
#define USB_DOEPxDMAADDR(x)       REG32(((USBX) + LOCATE_DOEPxDMAADDR(x)))/*!< device OUT endpoint-x DMA address register */
#define USB_DIEPxTFSTAT(x)        REG32(((USBX) + LOCATE_DIEPxTFSTAT(x))) /*!< device IN endpoint-x transmit FIFO status register */

#define USB_PWRCLKCTL             REG32(((USBX) + 0x0E00U))               /*!< power and clock register */

#define USB_FIFO(x)               (&REG32(((USBX) + LOCATE_FIFO(x))))     /*!< FIFO memory */

/* global OTG control and status register bits definitions */
#define GOTGCS_BSV                BIT(19)             /*!< B-Session Valid */
#define GOTGCS_ASV                BIT(18)             /*!< A-session valid */
#define GOTGCS_DI                 BIT(17)             /*!< debounce interval */
#define GOTGCS_CIDPS              BIT(16)             /*!< id pin status */
#define GOTGCS_DHNPEN             BIT(11)             /*!< device HNP enable */
#define GOTGCS_HHNPEN             BIT(10)             /*!< host HNP enable */
#define GOTGCS_HNPREQ             BIT(9)              /*!< HNP request */
#define GOTGCS_HNPS               BIT(8)              /*!< HNP successes */
#define GOTGCS_SRPREQ             BIT(1)              /*!< SRP request */
#define GOTGCS_SRPS               BIT(0)              /*!< SRP successes */

/* global OTG interrupt flag register bits definitions */
#define GOTGINTF_DF               BIT(19)             /*!< debounce finish */
#define GOTGINTF_ADTO             BIT(18)             /*!< A-device timeout */
#define GOTGINTF_HNPDET           BIT(17)             /*!< host negotiation request detected */
#define GOTGINTF_HNPEND           BIT(9)              /*!< HNP end */
#define GOTGINTF_SRPEND           BIT(8)              /*!< SRP end */
#define GOTGINTF_SESEND           BIT(2)              /*!< session end */

/* global AHB control and status register bits definitions */
#define GAHBCS_PTXFTH             BIT(8)              /*!< periodic Tx FIFO threshold */
#define GAHBCS_TXFTH              BIT(7)              /*!< tx FIFO threshold */
#define GAHBCS_DMAEN              BIT(5)              /*!< DMA function Enable */
#define GAHBCS_BURST              BITS(1, 4)          /*!< the AHB burst type used by DMA */
#define GAHBCS_GINTEN             BIT(0)              /*!< global interrupt enable */

/* global USB control and status register bits definitions */
#define GUSBCS_FDM                BIT(30)             /*!< force device mode */
#define GUSBCS_FHM                BIT(29)             /*!< force host mode */
#define GUSBCS_ULPIEOI            BIT(21)             /*!< ULPI external over-current indicator */
#define GUSBCS_ULPIEVD            BIT(20)             /*!< ULPI external VBUS driver */
#define GUSBCS_UTT                BITS(10, 13)        /*!< USB turnaround time */
#define GUSBCS_HNPCEN             BIT(9)              /*!< HNP capability enable */
#define GUSBCS_SRPCEN             BIT(8)              /*!< SRP capability enable */
#define GUSBCS_EMBPHY             BIT(6)              /*!< embedded PHY selected */
#define GUSBCS_TOC                BITS(0, 2)          /*!< timeout calibration */

/* global reset control register bits definitions */
#define GRSTCTL_DMAIDL            BIT(31)             /*!< DMA idle state */
#define GRSTCTL_DMABSY            BIT(30)             /*!< DMA busy */
#define GRSTCTL_TXFNUM            BITS(6, 10)         /*!< tx FIFO number */
#define GRSTCTL_TXFF              BIT(5)              /*!< tx FIFO flush */
#define GRSTCTL_RXFF              BIT(4)              /*!< rx FIFO flush */
#define GRSTCTL_HFCRST            BIT(2)              /*!< host frame counter reset */
#define GRSTCTL_HCSRST            BIT(1)              /*!< HCLK soft reset */
#define GRSTCTL_CSRST             BIT(0)              /*!< core soft reset */

/* global interrupt flag register bits definitions */
#define GINTF_WKUPIF              BIT(31)             /*!< wakeup interrupt flag */
#define GINTF_SESIF               BIT(30)             /*!< session interrupt flag */
#define GINTF_DISCIF              BIT(29)             /*!< disconnect interrupt flag */
#define GINTF_IDPSC               BIT(28)             /*!< id pin status change */
#define GINTF_PTXFEIF             BIT(26)             /*!< periodic tx FIFO empty interrupt flag */
#define GINTF_HCIF                BIT(25)             /*!< host channels interrupt flag */
#define GINTF_HPIF                BIT(24)             /*!< host port interrupt flag */
#define GINTF_PXNCIF              BIT(21)             /*!< periodic transfer not complete interrupt flag */
#define GINTF_ISOONCIF            BIT(21)             /*!< isochronous OUT transfer not complete interrupt flag */
#define GINTF_ISOINCIF            BIT(20)             /*!< isochronous IN transfer not complete interrupt flag */
#define GINTF_OEPIF               BIT(19)             /*!< OUT endpoint interrupt flag */
#define GINTF_IEPIF               BIT(18)             /*!< IN endpoint interrupt flag */
#define GINTF_EOPFIF              BIT(15)             /*!< end of periodic frame interrupt flag */
#define GINTF_ISOOPDIF            BIT(14)             /*!< isochronous OUT packet dropped interrupt flag */
#define GINTF_ENUMFIF             BIT(13)             /*!< enumeration finished */
#define GINTF_RST                 BIT(12)             /*!< USB reset */
#define GINTF_SP                  BIT(11)             /*!< USB suspend */
#define GINTF_ESP                 BIT(10)             /*!< early suspend */
#define GINTF_GONAK               BIT(7)              /*!< global OUT NAK effective */
#define GINTF_GNPINAK             BIT(6)              /*!< global IN non-periodic NAK effective */
#define GINTF_NPTXFEIF            BIT(5)              /*!< non-periodic tx FIFO empty interrupt flag */
#define GINTF_RXFNEIF             BIT(4)              /*!< rx FIFO non-empty interrupt flag */
#define GINTF_SOF                 BIT(3)              /*!< start of frame */
#define GINTF_OTGIF               BIT(2)              /*!< OTG interrupt flag */
#define GINTF_MFIF                BIT(1)              /*!< mode fault interrupt flag */
#define GINTF_COPM                BIT(0)              /*!< current operation mode */

/* global interrupt enable register bits definitions */
#define GINTEN_WKUPIE             BIT(31)             /*!< wakeup interrupt enable */
#define GINTEN_SESIE              BIT(30)             /*!< session interrupt enable */
#define GINTEN_DISCIE             BIT(29)             /*!< disconnect interrupt enable */
#define GINTEN_IDPSCIE            BIT(28)             /*!< id pin status change interrupt enable */
#define GINTEN_PTXFEIE            BIT(26)             /*!< periodic tx FIFO empty interrupt enable */
#define GINTEN_HCIE               BIT(25)             /*!< host channels interrupt enable */
#define GINTEN_HPIE               BIT(24)             /*!< host port interrupt enable */
#define GINTEN_IPXIE              BIT(21)             /*!< periodic transfer not complete interrupt enable */
#define GINTEN_ISOONCIE           BIT(21)             /*!< isochronous OUT transfer not complete interrupt enable */
#define GINTEN_ISOINCIE           BIT(20)             /*!< isochronous IN transfer not complete interrupt enable */
#define GINTEN_OEPIE              BIT(19)             /*!< OUT endpoints interrupt enable */
#define GINTEN_IEPIE              BIT(18)             /*!< IN endpoints interrupt enable */
#define GINTEN_EOPFIE             BIT(15)             /*!< end of periodic frame interrupt enable */
#define GINTEN_ISOOPDIE           BIT(14)             /*!< isochronous OUT packet dropped interrupt enable */
#define GINTEN_ENUMFIE            BIT(13)             /*!< enumeration finish enable */
#define GINTEN_RSTIE              BIT(12)             /*!< USB reset interrupt enable */
#define GINTEN_SPIE               BIT(11)             /*!< USB suspend interrupt enable */
#define GINTEN_ESPIE              BIT(10)             /*!< early suspend interrupt enable */
#define GINTEN_GONAKIE            BIT(7)              /*!< global OUT NAK effective interrupt enable */
#define GINTEN_GNPINAKIE          BIT(6)              /*!< global non-periodic IN NAK effective interrupt enable */
#define GINTEN_NPTXFEIE           BIT(5)              /*!< non-periodic Tx FIFO empty interrupt enable */
#define GINTEN_RXFNEIE            BIT(4)              /*!< receive FIFO non-empty interrupt enable */
#define GINTEN_SOFIE              BIT(3)              /*!< start of frame interrupt enable */
#define GINTEN_OTGIE              BIT(2)              /*!< OTG interrupt enable */
#define GINTEN_MFIE               BIT(1)              /*!< mode fault interrupt enable */

/* global receive status debug read register bits definitions */
#define GRSTATR_RPCKST            BITS(17, 20)        /*!< received packet status */
#define GRSTATR_DPID              BITS(15, 16)        /*!< data PID */
#define GRSTATR_BCOUNT            BITS(4, 14)         /*!< byte count */
#define GRSTATR_CNUM              BITS(0, 3)          /*!< channel number */

/* global status read and pop register bits definitions */
#define GRSTATP_RPCKST            BITS(17, 20)        /*!< received packet status */
#define GRSTATP_DPID              BITS(15, 16)        /*!< data PID */
#define GRSTATP_BCOUNT            BITS(4, 14)         /*!< byte count */
#define GRSTATP_EPNUM             BITS(0, 3)          /*!< endpoint number */

/* global receive FIFO length register bits definitions */
#define GRFLEN_RXFD               BITS(0, 15)         /*!< rx FIFO depth */

/* host non-periodic transmit FIFO length register bits definitions */
#define HNPTFLEN_HNPTXFD          BITS(16, 31)        /*!< non-periodic Tx FIFO depth */
#define HNPTFLEN_HNPTXRSAR        BITS(0, 15)         /*!< non-periodic Tx RAM start address */

/* IN endpoint 0 transmit FIFO length register bits definitions */
#define DIEP0TFLEN_IEP0TXFD       BITS(16, 31)        /*!< IN Endpoint 0 Tx FIFO depth */
#define DIEP0TFLEN_IEP0TXRSAR     BITS(0, 15)         /*!< IN Endpoint 0 TX RAM start address */

/* host non-periodic transmit FIFO/queue status register bits definitions */
#define HNPTFQSTAT_NPTXRQTOP      BITS(24, 30)        /*!< top entry of the non-periodic Tx request queue */
#define HNPTFQSTAT_NPTXRQS        BITS(16, 23)        /*!< non-periodic Tx request queue space */
#define HNPTFQSTAT_NPTXFS         BITS(0, 15)         /*!< non-periodic Tx FIFO space */
#define HNPTFQSTAT_CNUM           BITS(27, 30)        /*!< channel number*/
#define HNPTFQSTAT_EPNUM          BITS(27, 30)        /*!< endpoint number */
#define HNPTFQSTAT_TYPE           BITS(25, 26)        /*!< token type */
#define HNPTFQSTAT_TMF            BIT(24)             /*!< terminate flag */

/* global core configuration register bits definitions */
#define GCCFG_VBUSIG              BIT(21)             /*!< vbus ignored */
#define GCCFG_SOFOEN              BIT(20)             /*!< SOF output enable */
#define GCCFG_VBUSBCEN            BIT(19)             /*!< the VBUS B-device comparer enable */
#define GCCFG_VBUSACEN            BIT(18)             /*!< the VBUS A-device comparer enable */
#define GCCFG_PWRON               BIT(16)             /*!< power on */

/* core ID register bits definitions */
#define CID_CID                   BITS(0, 31)         /*!< core ID */

/* host periodic transmit FIFO length register bits definitions */
#define HPTFLEN_HPTXFD            BITS(16, 31)        /*!< host periodic Tx FIFO depth */
#define HPTFLEN_HPTXFSAR          BITS(0, 15)         /*!< host periodic Tx RAM start address */

/* device IN endpoint transmit FIFO length register bits definitions */
#define DIEPTFLEN_IEPTXFD         BITS(16, 31)        /*!< IN endpoint Tx FIFO x depth */
#define DIEPTFLEN_IEPTXRSAR       BITS(0, 15)         /*!< IN endpoint FIFOx Tx x RAM start address */

/* host control register bits definitions */
#define HCTL_SPDFSLS              BIT(2)              /*!< speed limited to FS and LS */
#define HCTL_CLKSEL               BITS(0, 1)          /*!< clock select for USB clock */

/* host frame interval register bits definitions */
#define HFT_FRI                   BITS(0, 15)         /*!< frame interval */

/* host frame information remaining register bits definitions */
#define HFINFR_FRT                BITS(16, 31)        /*!< frame remaining time */
#define HFINFR_FRNUM              BITS(0, 15)         /*!< frame number */

/* host periodic transmit FIFO/queue status register bits definitions */
#define HPTFQSTAT_PTXREQT         BITS(24, 31)        /*!< top entry of the periodic Tx request queue */
#define HPTFQSTAT_PTXREQS         BITS(16, 23)        /*!< periodic Tx request queue space */
#define HPTFQSTAT_PTXFS           BITS(0, 15)         /*!< periodic Tx FIFO space */
#define HPTFQSTAT_OEFRM           BIT(31)             /*!< odd/eveb frame */
#define HPTFQSTAT_CNUM            BITS(27, 30)        /*!< channel number */
#define HPTFQSTAT_EPNUM           BITS(27, 30)        /*!< endpoint number */
#define HPTFQSTAT_TYPE            BITS(25, 26)        /*!< token type */
#define HPTFQSTAT_TMF             BIT(24)             /*!< terminate flag */

/* host all channels interrupt register bits definitions */
#define HACHINT_HACHINT           BITS(0, 11)         /*!< host all channel interrupts */

/* host all channels interrupt enable register bits definitions */
#define HACHINTEN_CINTEN          BITS(0, 11)         /*!< channel interrupt enable */

/* host port control and status register bits definitions */
#define HPCS_PS                   BITS(17, 18)        /*!< port speed */
#define HPCS_PP                   BIT(12)             /*!< port power */
#define HPCS_PLST                 BITS(10, 11)        /*!< port line status */
#define HPCS_PRST                 BIT(8)              /*!< port reset */
#define HPCS_PSP                  BIT(7)              /*!< port suspend */
#define HPCS_PREM                 BIT(6)              /*!< port resume */
#define HPCS_PEDC                 BIT(3)              /*!< port enable/disable change */
#define HPCS_PE                   BIT(2)              /*!< port enable */
#define HPCS_PCD                  BIT(1)              /*!< port connect detected */
#define HPCS_PCST                 BIT(0)              /*!< port connect status */

/* host channel-x control register bits definitions */
#define HCHCTL_CEN                BIT(31)             /*!< channel enable */
#define HCHCTL_CDIS               BIT(30)             /*!< channel disable */
#define HCHCTL_ODDFRM             BIT(29)             /*!< odd frame */
#define HCHCTL_DAR                BITS(22, 28)        /*!< device address */
#define HCHCTL_MPC                BITS(20, 21)        /*!< multiple packet count */
#define HCHCTL_EPTYPE             BITS(18, 19)        /*!< endpoint type */
#define HCHCTL_LSD                BIT(17)             /*!< low-speed device */
#define HCHCTL_EPDIR              BIT(15)             /*!< endpoint direction */
#define HCHCTL_EPNUM              BITS(11, 14)        /*!< endpoint number */
#define HCHCTL_MPL                BITS(0, 10)         /*!< maximum packet length */

/* host channel-x split transaction register bits definitions */
#define HCHSTCTL_SPLEN            BIT(31)             /*!< enable high-speed split transaction */
#define HCHSTCTL_CSPLT            BIT(16)             /*!< complete-split enable */
#define HCHSTCTL_ISOPCE           BITS(14, 15)        /*!< isochronous OUT payload continuation encoding */
#define HCHSTCTL_HADDR            BITS(7, 13)         /*!< HUB address */
#define HCHSTCTL_PADDR            BITS(0, 6)          /*!< port address */

/* host channel-x interrupt flag register bits definitions */
#define HCHINTF_DTER              BIT(10)             /*!< data toggle error */
#define HCHINTF_REQOVR            BIT(9)              /*!< request queue overrun */
#define HCHINTF_BBER              BIT(8)              /*!< babble error */
#define HCHINTF_USBER             BIT(7)              /*!< USB bus Error */
#define HCHINTF_NYET              BIT(6)              /*!< NYET */
#define HCHINTF_ACK               BIT(5)              /*!< ACK */
#define HCHINTF_NAK               BIT(4)              /*!< NAK */
#define HCHINTF_STALL             BIT(3)              /*!< STALL */
#define HCHINTF_DMAER             BIT(2)              /*!< DMA error */
#define HCHINTF_CH                BIT(1)              /*!< channel halted */
#define HCHINTF_TF                BIT(0)              /*!< transfer finished */

/* host channel-x interrupt enable register bits definitions */
#define HCHINTEN_DTERIE           BIT(10)             /*!< data toggle error interrupt enable */
#define HCHINTEN_REQOVRIE         BIT(9)              /*!< request queue overrun interrupt enable */
#define HCHINTEN_BBERIE           BIT(8)              /*!< babble error interrupt enable */
#define HCHINTEN_USBERIE          BIT(7)              /*!< USB bus error interrupt enable */
#define HCHINTEN_NYETIE           BIT(6)              /*!< NYET interrupt enable */
#define HCHINTEN_ACKIE            BIT(5)              /*!< ACK interrupt enable */
#define HCHINTEN_NAKIE            BIT(4)              /*!< NAK interrupt enable */
#define HCHINTEN_STALLIE          BIT(3)              /*!< STALL interrupt enable */
#define HCHINTEN_DMAERIE          BIT(2)              /*!< DMA error interrupt enable */
#define HCHINTEN_CHIE             BIT(1)              /*!< channel halted interrupt enable */
#define HCHINTEN_TFIE             BIT(0)              /*!< transfer finished interrupt enable */

/* host channel-x transfer length register bits definitions */
#define HCHLEN_PING               BIT(31)             /*!< PING token request */
#define HCHLEN_DPID               BITS(29, 30)        /*!< data PID */
#define HCHLEN_PCNT               BITS(19, 28)        /*!< packet count */
#define HCHLEN_TLEN               BITS(0, 18)         /*!< transfer length */

/* host channel-x DMA address register bits definitions */
#define HCHDMAADDR_DMAADDR        BITS(0, 31)         /*!< DMA address */

/* device control and status registers */
/* device configuration registers bits definitions */
#define DCFG_EOPFT                BITS(11, 12)        /*!< end of periodic frame time */
#define DCFG_DAR                  BITS(4, 10)         /*!< device address */
#define DCFG_NZLSOH               BIT(2)              /*!< non-zero-length status OUT handshake */
#define DCFG_DS                   BITS(0, 1)          /*!< device speed */

/* device control registers bits definitions */
#define DCTL_POIF                 BIT(11)             /*!< power-on initialization finished */
#define DCTL_CGONAK               BIT(10)             /*!< clear global OUT NAK */
#define DCTL_SGONAK               BIT(9)              /*!< set global OUT NAK */
#define DCTL_CGINAK               BIT(8)              /*!< clear global IN NAK */
#define DCTL_SGINAK               BIT(7)              /*!< set global IN NAK */
#define DCTL_GONS                 BIT(3)              /*!< global OUT NAK status */
#define DCTL_GINS                 BIT(2)              /*!< global IN NAK status */
#define DCTL_SD                   BIT(1)              /*!< soft disconnect */
#define DCTL_RWKUP                BIT(0)              /*!< remote wakeup */

/* device status registers bits definitions */
#define DSTAT_FNRSOF              BITS(8, 21)         /*!< the frame number of the received SOF. */
#define DSTAT_ES                  BITS(1, 2)          /*!< enumerated speed */
#define DSTAT_SPST                BIT(0)              /*!< suspend status */

/* device IN endpoint common interrupt enable registers bits definitions */
#define DIEPINTEN_NAKEN           BIT(13)             /*!< NAK handshake sent by USBHS interrupt enable bit */
#define DIEPINTEN_TXFEEN          BIT(7)              /*!< transmit FIFO empty interrupt enable bit */
#define DIEPINTEN_IEPNEEN         BIT(6)              /*!< IN endpoint NAK effective interrupt enable bit */
#define DIEPINTEN_EPTXFUDEN       BIT(4)              /*!< endpoint Tx FIFO underrun interrupt enable bit */
#define DIEPINTEN_CITOEN          BIT(3)              /*!< control In Timeout interrupt enable bit */
#define DIEPINTEN_EPDISEN         BIT(1)              /*!< endpoint disabled interrupt enable bit */
#define DIEPINTEN_TFEN            BIT(0)              /*!< transfer finished interrupt enable bit */ 

/* device OUT endpoint common interrupt enable registers bits definitions */
#define DOEPINTEN_NYETEN          BIT(14)             /*!< NYET handshake is sent interrupt enable bit */
#define DOEPINTEN_BTBSTPEN        BIT(6)              /*!< back-to-back SETUP packets interrupt enable bit */
#define DOEPINTEN_EPRXFOVREN      BIT(4)              /*!< endpoint Rx FIFO overrun interrupt enable bit */
#define DOEPINTEN_STPFEN          BIT(3)              /*!< SETUP phase finished interrupt enable bit */
#define DOEPINTEN_EPDISEN         BIT(1)              /*!< endpoint disabled interrupt enable bit */
#define DOEPINTEN_TFEN            BIT(0)              /*!< transfer finished interrupt enable bit */

/* device all endpoints interrupt registers bits definitions */
#define DAEPINT_OEPITB            BITS(16, 21)        /*!< device all OUT endpoint interrupt bits */
#define DAEPINT_IEPITB            BITS(0, 5)          /*!< device all IN endpoint interrupt bits */

/* device all endpoints interrupt enable registers bits definitions */
#define DAEPINTEN_OEPIE           BITS(16, 21)        /*!< OUT endpoint interrupt enable */
#define DAEPINTEN_IEPIE           BITS(0, 3)          /*!< IN endpoint interrupt enable */

/* device Vbus discharge time registers bits definitions */
#define DVBUSDT_DVBUSDT           BITS(0, 15)         /*!< device VBUS discharge time */

/* device Vbus pulsing time registers bits definitions */
#define DVBUSPT_DVBUSPT           BITS(0, 11)         /*!< device VBUS pulsing time */

/* device IN endpoint FIFO empty interrupt enable register bits definitions */
#define DIEPFEINTEN_IEPTXFEIE     BITS(0, 5)          /*!< IN endpoint Tx FIFO empty interrupt enable bits */

/* device endpoint 1 interrupt register bits definitions */
#define DEP1INT_OEP1INT           BIT(17)             /*!< OUT Endpoint 1 interrupt */
#define DEP1INT_IEP1INT           BIT(1)              /*!< IN Endpoint 1 interrupt */

/* device endpoint 1 interrupt register enable bits definitions */
#define DEP1INTEN_OEP1INTEN       BIT(17)             /*!< OUT Endpoint 1 interrupt enable */
#define DEP1INTEN_IEP1INTEN       BIT(1)              /*!< IN Endpoint 1 interrupt enable */

/* device IN endpoint 1 interrupt enable register bits definitions */
#define DIEP1INTEN_NAKEN          BIT(13)             /*!< NAK handshake sent by USBHS interrupt enable bit */
#define DIEP1INTEN_IEPNEEN        BIT(6)              /*!< IN endpoint NAK effective interrupt enable bit */
#define DIEP1INTEN_EPTXFUDEN      BIT(4)              /*!< endpoint Tx FIFO underrun interrupt enable bit */
#define DIEP1INTEN_CITOEN         BIT(3)              /*!< control In Timeout interrupt enable bit */
#define DIEP1INTEN_EPDISEN        BIT(1)              /*!< endpoint disabled interrupt enable bit */
#define DIEP1INTEN_TFEN           BIT(0)              /*!< transfer finished interrupt enable bit */

/* device OUT endpoint 1 interrupt enable register bits definitions */
#define DOEP1INTEN_NYETEN         BIT(14)             /*!< NYET handshake is sent interrupt enable bit */
#define DOEP1INTEN_BTBSTPEN       BIT(6)              /*!< back-to-back SETUP packets interrupt enable bit */
#define DOEP1INTEN_EPRXOVREN      BIT(4)              /*!< endpoint Rx FIFO over run interrupt enable bit */
#define DOEP1INTEN_STPFEN         BIT(3)              /*!< SETUP phase finished interrupt enable bit */
#define DOEP1INTEN_EPDISEN        BIT(1)              /*!< endpoint disabled interrupt enable bit */
#define DOEP1INTEN_TFEN           BIT(0)              /*!< back-to-back SETUP packets interrupt enable bit */

/* device IN endpoint 0 control register bits definitions */
#define DIEP0CTL_EPEN             BIT(31)             /*!< endpoint enable */
#define DIEP0CTL_EPD              BIT(30)             /*!< endpoint disable */
#define DIEP0CTL_SNAK             BIT(27)             /*!< set NAK */
#define DIEP0CTL_CNAK             BIT(26)             /*!< clear NAK */
#define DIEP0CTL_TXFNUM           BITS(22, 25)        /*!< tx FIFO number */
#define DIEP0CTL_STALL            BIT(21)             /*!< STALL handshake */
#define DIEP0CTL_EPTYPE           BITS(18, 19)        /*!< endpoint type */
#define DIEP0CTL_NAKS             BIT(17)             /*!< NAK status */
#define DIEP0CTL_EPACT            BIT(15)             /*!< endpoint active */
#define DIEP0CTL_MPL              BITS(0, 1)          /*!< maximum packet length */

/* device IN endpoint x control register bits definitions */
#define DIEPCTL_EPEN              BIT(31)             /*!< endpoint enable */
#define DIEPCTL_EPD               BIT(30)             /*!< endpoint disable */
#define DIEPCTL_SODDFRM           BIT(29)             /*!< set odd frame */
#define DIEPCTL_SD1PID            BIT(29)             /*!< set DATA1 PID */
#define DIEPCTL_SEVNFRM           BIT(28)             /*!< set even frame */
#define DIEPCTL_SD0PID            BIT(28)             /*!< set DATA0 PID */
#define DIEPCTL_SNAK              BIT(27)             /*!< set NAK */
#define DIEPCTL_CNAK              BIT(26)             /*!< clear NAK */
#define DIEPCTL_TXFNUM            BITS(22, 25)        /*!< tx FIFO number */
#define DIEPCTL_STALL             BIT(21)             /*!< STALL handshake */
#define DIEPCTL_EPTYPE            BITS(18, 19)        /*!< endpoint type */
#define DIEPCTL_NAKS              BIT(17)             /*!< NAK status */
#define DIEPCTL_EOFRM             BIT(16)             /*!< even/odd frame */
#define DIEPCTL_DPID              BIT(16)             /*!< endpoint data PID */
#define DIEPCTL_EPACT             BIT(15)             /*!< endpoint active */
#define DIEPCTL_MPL               BITS(0, 10)         /*!< maximum packet length */

/* device OUT endpoint 0 control register bits definitions */
#define DOEP0CTL_EPEN             BIT(31)             /*!< endpoint enable */
#define DOEP0CTL_EPD              BIT(30)             /*!< endpoint disable */
#define DOEP0CTL_SNAK             BIT(27)             /*!< set NAK */
#define DOEP0CTL_CNAK             BIT(26)             /*!< clear NAK */
#define DOEP0CTL_STALL            BIT(21)             /*!< STALL handshake */
#define DOEP0CTL_SNOOP            BIT(20)             /*!< snoop mode */
#define DOEP0CTL_EPTYPE           BITS(18, 19)        /*!< endpoint type */
#define DOEP0CTL_NAKS             BIT(17)             /*!< NAK status */
#define DOEP0CTL_EPACT            BIT(15)             /*!< endpoint active */
#define DOEP0CTL_MPL              BITS(0, 1)          /*!< maximum packet length */

/* device OUT endpoint-x control register bits definitions */
#define DOEPCTL_EPEN              BIT(31)             /*!< endpoint enable */
#define DOEPCTL_EPD               BIT(30)             /*!< endpoint disable */
#define DOEPCTL_SODDFRM           BIT(29)             /*!< set odd frame */
#define DOEPCTL_SD1PID            BIT(29)             /*!< set DATA1 PID */
#define DOEPCTL_SEVNFRM           BIT(28)             /*!< set even frame */
#define DOEPCTL_SD0PID            BIT(28)             /*!< set DATA0 PID */
#define DOEPCTL_SNAK              BIT(27)             /*!< set NAK */
#define DOEPCTL_CNAK              BIT(26)             /*!< clear NAK */
#define DOEPCTL_STALL             BIT(21)             /*!< STALL handshake */
#define DOEPCTL_SNOOP             BIT(20)             /*!< snoop mode */
#define DOEPCTL_EPTYPE            BITS(18, 19)        /*!< endpoint type */
#define DOEPCTL_NAKS              BIT(17)             /*!< NAK status */
#define DOEPCTL_EOFRM             BIT(16)             /*!< even/odd frame */
#define DOEPCTL_DPID              BIT(16)             /*!< endpoint data PID */
#define DOEPCTL_EPACT             BIT(15)             /*!< endpoint active */
#define DOEPCTL_MPL               BITS(0, 10)         /*!< maximum packet length */

/* device IN endpoint-x interrupt flag register bits definitions */
#define DIEPINTF_NAK              BIT(13)             /*!< NAK handshake sent by USBHS */
#define DIEPINTF_TXFE             BIT(7)              /*!< transmit FIFO empty */
#define DIEPINTF_IEPNE            BIT(6)              /*!< IN endpoint NAK effective */
#define DIEPINTF_EPTXFUD          BIT(4)              /*!< endpoint Tx FIFO underrun */
#define DIEPINTF_CITO             BIT(3)              /*!< control In Timeout interrupt */
#define DIEPINTF_EPDIS            BIT(1)              /*!< endpoint disabled */
#define DIEPINTF_TF               BIT(0)              /*!< transfer finished */

/* device OUT endpoint-x interrupt flag register bits definitions */
#define DOEPINTF_NYET             BIT(14)             /*!< NYET handshake is sent */
#define DOEPINTF_BTBSTP           BIT(6)              /*!< back-to-back SETUP packets */
#define DOEPINTF_EPRXFOVR         BIT(4)              /*!< endpoint Rx FIFO overrun */
#define DOEPINTF_STPF             BIT(3)              /*!< SETUP phase finished */
#define DOEPINTF_EPDIS            BIT(1)              /*!< endpoint disabled */
#define DOEPINTF_TF               BIT(0)              /*!< transfer finished */

/* device IN endpoint 0 transfer length register bits definitions */
#define DIEP0LEN_PCNT             BITS(19, 20)        /*!< packet count */
#define DIEP0LEN_TLEN             BITS(0, 6)          /*!< transfer length */

/* device OUT endpoint 0 transfer length register bits definitions */
#define DOEP0LEN_STPCNT           BITS(29, 30)        /*!< SETUP packet count */
#define DOEP0LEN_PCNT             BIT(19)             /*!< packet count */
#define DOEP0LEN_TLEN             BITS(0, 6)          /*!< transfer length */

/* device IN endpoint-x transfer length register bits definitions */
#define DIEPLEN_MCNT              BITS(29, 30)        /*!< multi count */
#define DIEPLEN_PCNT              BITS(19, 28)        /*!< packet count */
#define DIEPLEN_TLEN              BITS(0, 18)         /*!< transfer length */

/* device OUT endpoint-x transfer length register bits definitions */
#define DOEPLEN_RXDPID            BITS(29, 30)        /*!< received data PID */
#define DOEPLEN_STPCNT            BITS(29, 30)        /*!< SETUP packet count */
#define DOEPLEN_PCNT              BITS(19, 28)        /*!< packet count */
#define DOEPLEN_TLEN              BITS(0, 18)         /*!< transfer length */

/* device IN endpoint-x DMA address register bits definitions */
#define DIEPDMAADDR_DMAADDR       BITS(0, 31)         /*!< DMA address */

/* device OUT endpoint-x DMA address register bits definitions */
#define DOEPDMAADDR_DMAADDR       BITS(0, 31)         /*!< DMA address */

/* device IN endpoint-x transmit FIFO status register bits definitions */
#define DIEPTFSTAT_IEPTFS         BITS(0, 15)         /*!< IN endpoint¡¯s Tx FIFO space remaining */

/* USB power and clock registers bits definition */
#define PWRCLKCTL_SHCLK           BIT(1)              /*!< stop HCLK */
#define PWRCLKCTL_SUCLK           BIT(0)              /*!< stop the USB clock */

/* register options defines */
#define DCFG_DEVSPEED(regval)     (DCFG_DS & ((regval) << 0U))      /*!< device speed configuration */

#define USB_SPEED_EXP_HIGH        DCFG_DEVSPEED(0U)                 /*!< device external PHY high speed */
#define USB_SPEED_EXP_FULL        DCFG_DEVSPEED(1U)                 /*!< device external PHY full speed */
#define USB_SPEED_INP_FULL        DCFG_DEVSPEED(3U)                 /*!< device internal PHY full speed */

#define GAHBCS_TFEL(regval)       (GAHBCS_TXFTH & ((regval) << 7U)) /*!< device speed configuration */

#define TXFIFO_EMPTY_HALF         GAHBCS_TFEL(0U)                   /*!< Tx FIFO half empty */
#define TXFIFO_EMPTY              GAHBCS_TFEL(1U)                   /*!< Tx FIFO completely empty */

#define GAHBCS_DMAINCR(regval)    (GAHBCS_BURST & ((regval) << 1U)) /*!< AHB burst type used by DMA*/

#define DMA_INCR0                 GAHBCS_DMAINCR(0U)                /*!< single burst type used by DMA*/
#define DMA_INCR1                 GAHBCS_DMAINCR(1U)                /*!< 4-beat incrementing burst type used by DMA*/
#define DMA_INCR4                 GAHBCS_DMAINCR(3U)                /*!< 8-beat incrementing burst type used by DMA*/
#define DMA_INCR8                 GAHBCS_DMAINCR(5U)                /*!< 16-beat incrementing burst type used by DMA*/
#define DMA_INCR16                GAHBCS_DMAINCR(7U)                /*!< 32-beat incrementing burst type used by DMA*/

#define DCFG_PFRI(regval)         (DCFG_EOPFT & ((regval) << 11U))  /*!< end of periodic frame time configuration */

#define FRAME_INTERVAL_80         DCFG_PFRI(0U)                     /*!< 80% of the frame time */
#define FRAME_INTERVAL_85         DCFG_PFRI(1U)                     /*!< 85% of the frame time */
#define FRAME_INTERVAL_90         DCFG_PFRI(2U)                     /*!< 90% of the frame time */
#define FRAME_INTERVAL_95         DCFG_PFRI(3U)                     /*!< 95% of the frame time */

#define DEP0CTL_MPL(regval)       (DOEP0CTL_MPL & ((regval) << 0U))   /*!< maximum packet length configuration */

#define EP0MPL_64                 DEP0CTL_MPL(0U)                   /*!< maximum packet length 64 bytes */
#define EP0MPL_32                 DEP0CTL_MPL(1U)                   /*!< maximum packet length 32 bytes */
#define EP0MPL_16                 DEP0CTL_MPL(2U)                   /*!< maximum packet length 16 bytes */
#define EP0MPL_8                  DEP0CTL_MPL(3U)                   /*!< maximum packet length 8 bytes */

/* endpoints address */

/* first bit is direction(0 for Rx and 1 for Tx) */
#define EP0_OUT                   ((uint8_t)0x00U)                  /*!< endpoint out 0 */
#define EP0_IN                    ((uint8_t)0x80U)                  /*!< endpoint in 0 */
#define EP1_OUT                   ((uint8_t)0x01U)                  /*!< endpoint out 1 */
#define EP1_IN                    ((uint8_t)0x81U)                  /*!< endpoint in 1 */
#define EP2_OUT                   ((uint8_t)0x02U)                  /*!< endpoint out 2 */
#define EP2_IN                    ((uint8_t)0x82U)                  /*!< endpoint in 2 */
#define EP3_OUT                   ((uint8_t)0x03U)                  /*!< endpoint out 3 */
#define EP3_IN                    ((uint8_t)0x83U)                  /*!< endpoint in 3 */

/* enable global interrupt */
#define USB_GLOBAL_INT_ENABLE()       (USB_GAHBCS |= GAHBCS_GINTEN)

/* disable global interrupt */
#define USB_GLOBAL_INT_DISABLE()      (USB_GAHBCS &= ~GAHBCS_GINTEN)

/* get current operation mode */
#define USB_CURRENT_MODE_GET()        (USB_GINTF & GINTF_COPM)

/* read global interrupt flag */
#define USB_CORE_INTR_READ(x) \
do { \
  uint32_t global_intf = USB_GINTF; \
  (x) = global_intf & USB_GINTEN; \
} while(0)

/* read global interrupt flag */
#define USB_DAOEP_INTR_READ(x) \
do { \
  uint32_t dev_all_ep_inten = USB_DAEPINTEN; \
  uint32_t dev_all_ep_int = USB_DAEPINT; \
  uint32_t out_ep_intb = DAEPINT_OEPITB;  \
  (x) = (dev_all_ep_inten & dev_all_ep_int & out_ep_intb) >> 16; \
} while(0)

/* read out endpoint-x interrupt flag */
#define USB_DOEP_INTR_READ(x, EpID) \
do { \
    uint32_t out_epintf = USB_DOEPxINTF(EpID); \
    (x) = out_epintf & USB_DOEPINTEN; \
} while(0) 

/* read all in endpoint interrupt flag */
#define USB_DAIEP_INTR_READ(x) \
do { \
  uint32_t dev_all_ep_inten = USB_DAEPINTEN; \
  uint32_t dev_all_ep_int = USB_DAEPINT; \
  uint32_t in_ep_intb = DAEPINT_IEPITB;  \
  (x) = dev_all_ep_inten & dev_all_ep_int & in_ep_intb; \
} while(0)


/* read in endpoint-x interrupt flag */
#define USB_DIEP_INTR_READ(x, EpID) \
do { \
    uint32_t dev_ep_intf = USB_DIEPxINTF(EpID); \
    uint32_t dev_ep_fifoempty_intf = (((USB_DIEPFEINTEN >> (EpID)) & 0x1U) << 7U); \
    uint32_t dev_inep_inten = USB_DIEPINTEN; \
    (x) = dev_ep_intf & (dev_ep_fifoempty_intf | dev_inep_inten); \
} while(0)

/* generate remote wakup signal */
#define USB_REMOTE_WAKEUP_SET()       (USB_DCTL |= DCTL_RWKUP)

/* no remote wakup signal generate */
#define USB_REMOTE_WAKEUP_RESET()     (USB_DCTL &= ~DCTL_RWKUP)

/* generate soft disconnect */
#define USB_SOFT_DISCONNECT_ENABLE()  (USB_DCTL |= DCTL_SD)

/* no soft disconnect generate */
#define USB_SOFT_DISCONNECT_DISABLE() (USB_DCTL &= ~DCTL_SD)

/* set device address */
#define USB_SET_DEVADDR(DevAddr)      (USB_DCFG |= (DevAddr) << 4U)

/* check whether frame is even */
#define USB_EVEN_FRAME()              (!(USB_HFINFR & 0x01U))

/* read port status */
#define USB_PORT_READ()               (USB_HPCS & (~HPCS_PE) & (~HPCS_PCD) & (~HPCS_PEDC))

/* usb clock initialize */
#define USB_FSLSCLOCK_INIT(ClockFreq) (USB_HCTL &= ~HCTL_CLKSEL | (ClockFreq))

/* get usb current speed */
#define USB_CURRENT_SPEED_GET()       ((USB_HPCS & HPCS_PS) >> 17)

/* get usb current frame */
#define USB_CURRENT_FRAME_GET()       (USB_HFINFR & 0xFFFFU)

#endif /* USB_REGS_H */
