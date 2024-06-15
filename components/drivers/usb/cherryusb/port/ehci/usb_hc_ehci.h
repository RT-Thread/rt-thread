/*
 * Copyright 2020 The Apache Software Foundation
 * Copyright 2022 sakumisu
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USB_HC_EHCI_H
#define USB_HC_EHCI_H

#define EHCI_FULL_SPEED (0) /* Full-Speed (12Mbs) */
#define EHCI_LOW_SPEED  (1) /* Low-Speed (1.5Mbs) */
#define EHCI_HIGH_SPEED (2) /* High-Speed (480 Mb/s) */

/* Host Controller Capability Register Bit Definitions **********************/

/* Structural Parameters. Paragraph 2.2.3 */

#define EHCI_HCSPARAMS_NPORTS_SHIFT  (0) /* Bit 0-3: Number of physical downstream ports */
#define EHCI_HCSPARAMS_NPORTS_MASK   (15 << EHCI_HCSPARAMS_NPORTS_SHIFT)
#define EHCI_HCSPARAMS_PPC           (1 << 4) /* Bit 4: Port Power Control */
#define EHCI_HCSPARAMS_PRR           (1 << 7) /* Bit 7: Port Routing Rules */
#define EHCI_HCSPARAMS_NPCC_SHIFT    (8)      /* Bit 8-11: Number of Ports per Companion Controller */
#define EHCI_HCSPARAMS_NPCC_MASK     (15 << EHCI_HCSPARAMS_NPCC_SHIFT)
#define EHCI_HCSPARAMS_NCC_SHIFT     (12) /* Bit 12-15: Number of Companion Controllers */
#define EHCI_HCSPARAMS_NCC_MASK      (15 << EHCI_HCSPARAMS_NCC_SHIFT)
#define EHCI_HCSPARAMS_PIND          (1 << 16) /* Bit 16: Port Indicators */
#define EHCI_HCSPARAMS_DBGPORT_SHIFT (20)      /* Bit 20-23: Debug Port Number */
#define EHCI_HCSPARAMS_DBGPORT_MASK  (15 << EHCI_HCSPARAMS_DBGPORT_SHIFT)

/* Capability Parameters. Paragraph 2.2.4 */

#define EHCI_HCCPARAMS_64BIT      (1 << 0) /* Bit 0: 64-bit Addressing Capability */
#define EHCI_HCCPARAMS_PFLF       (1 << 1) /* Bit 1: Programmable Frame List Flag */
#define EHCI_HCCPARAMS_ASPC       (1 << 2) /* Bit 2: Asynchronous Schedule Park Capability */
#define EHCI_HCCPARAMS_IST_SHIFT  (4)      /* Bits 4-7: Isochronous Scheduling Threshold */
#define EHCI_HCCPARAMS_IST_MASK   (15 << EHCI_HCCPARAMS_IST_SHIFT)
#define EHCI_HCCPARAMS_EECP_SHIFT (8) /* Bits 8-15: EHCI Extended Capabilities Pointer */
#define EHCI_HCCPARAMS_EECP_MASK  (0xff << EHCI_HCCPARAMS_EECP_SHIFT)

/* Host Controller Operational Register Bit Definitions *********************/

/* USB Command. Paragraph 2.3.1 */

#define EHCI_USBCMD_RUN                 (1 << 0) /* Bit 0: Run/Stop */
#define EHCI_USBCMD_HCRESET             (1 << 1) /* Bit 1: Host Controller Reset */
#define EHCI_USBCMD_FLSIZE_SHIFT        (2)      /* Bits 2-3: Frame List Size */
#define EHCI_USBCMD_FLSIZE_MASK         (3 << EHCI_USBCMD_FLSIZE_SHIFT)
#define EHCI_USBCMD_FLSIZE_1024         (0 << EHCI_USBCMD_FLSIZE_SHIFT) /* 1024 elements (4096 bytes) */
#define EHCI_USBCMD_FLSIZE_512          (1 << EHCI_USBCMD_FLSIZE_SHIFT) /* 512 elements (2048 bytes) */
#define EHCI_USBCMD_FLSIZE_256          (2 << EHCI_USBCMD_FLSIZE_SHIFT) /* 256 elements (1024 bytes) */
#define EHCI_USBCMD_PSEN                (1 << 4)                        /* Bit 4: Periodic Schedule Enable */
#define EHCI_USBCMD_ASEN                (1 << 5)                        /* Bit 5: Asynchronous Schedule Enable */
#define EHCI_USBCMD_IAAD                (1 << 6)                        /* Bit 6: Interrupt on Async Advance Doorbell */
#define EHCI_USBCMD_LRESET              (1 << 7)                        /* Bit 7: Light Host Controller Reset */
#define EHCI_USBCMD_ASYNC_PARKCNT_SHIFT (8)                             /* Bits 8-9: Asynchronous Schedule Park Mode Count */
#define EHCI_USBCMD_ASYNC_PARKCNT_MASK  (3 << EHCI_USBCMD_ASYNC_PARKCNT_SHIFT)
#define EHCI_USBCMD_ASYNC_PARK          (1 << 11) /* Bit 11: Asynchronous Schedule Park Mode Enable */
#define EHCI_USBCMD_ITHRE_SHIFT         (16)      /* Bits 16-23: Interrupt Threshold Control */
#define EHCI_USBCMD_ITHRE_MASK          (0xff << EHCI_USBCMD_ITHRE_SHIFT)
#define EHCI_USBCMD_ITHRE_1MF           (0x01 << EHCI_USBCMD_ITHRE_SHIFT) /* 1 micro-frame */
#define EHCI_USBCMD_ITHRE_2MF           (0x02 << EHCI_USBCMD_ITHRE_SHIFT) /* 2 micro-frames */
#define EHCI_USBCMD_ITHRE_4MF           (0x04 << EHCI_USBCMD_ITHRE_SHIFT) /* 4 micro-frames */
#define EHCI_USBCMD_ITHRE_8MF           (0x08 << EHCI_USBCMD_ITHRE_SHIFT) /* 8 micro-frames (default, 1 ms) */
#define EHCI_USBCMD_ITHRE_16MF          (0x10 << EHCI_USBCMD_ITHRE_SHIFT) /* 16 micro-frames (2 ms) */
#define EHCI_USBCMD_ITHRE_32MF          (0x20 << EHCI_USBCMD_ITHRE_SHIFT) /* 32 micro-frames (4 ms) */
#define EHCI_USBCMD_ITHRE_64MF          (0x40 << EHCI_USBCMD_ITHRE_SHIFT) /* 64 micro-frames (8 ms) */

/* USB Status. Paragraph 2.3.2 */

#define EHCI_USBSTS_INT    (1 << 0)  /* Bit 0:  USB Interrupt */
#define EHCI_USBSTS_ERR    (1 << 1)  /* Bit 1:  USB Error Interrupt */
#define EHCI_USBSTS_PCD    (1 << 2)  /* Bit 2:  Port Change Detect */
#define EHCI_USBSTS_FLR    (1 << 3)  /* Bit 3:  Frame List Rollover */
#define EHCI_USBSTS_FATAL  (1 << 4)  /* Bit 4:  Host System Error */
#define EHCI_USBSTS_IAA    (1 << 5)  /* Bit 5:  Interrupt on Async Advance */
#define EHCI_USBSTS_HALTED (1 << 12) /* Bit 12: HC Halted */
#define EHCI_USBSTS_RECLAM (1 << 13) /* Bit 13: Reclamation */
#define EHCI_USBSTS_PSS    (1 << 14) /* Bit 14: Periodic Schedule Status */
#define EHCI_USBSTS_ASS    (1 << 15) /* Bit 15: Asynchronous Schedule Status */
                                     /* Bits 16-31: Reserved */

/* USB Interrupt Enable. Paragraph 2.3.3 */

#define EHCI_USBIE_INT     (1 << 0) /* Bit 0:  USB Interrupt */
#define EHCI_USBIE_ERR     (1 << 1) /* Bit 1:  USB Error Interrupt */
#define EHCI_USBIE_PCD     (1 << 2) /* Bit 2:  Port Change Detect */
#define EHCI_USBIE_FLROLL  (1 << 3) /* Bit 3:  Frame List Rollover */
#define EHCI_USBIE_FATAL   (1 << 4) /* Bit 4:  Host System Error */
#define EHCI_USBIE_IAA     (1 << 5) /* Bit 5:  Interrupt on Async Advance */
#define EHCI_USBIE_ALLINTS (0x3f)   /* Bits 0-5:  All interrupts */

/* USB Frame Index. Paragraph 2.3.4 */

#define EHCI_FRINDEX_MASK (0x3fff) /* Bits 0-13: Frame index */

/* 4G Segment Selector.
 * Paragraph 2.3.5,  Bits[64:32] of data structure addresses
 */

/* Frame List Base Address. Paragraph 2.3.6 */
#define EHCI_PERIODICLISTBASE_MASK (0xfffff000) /* Bits 12-31: Base Address (Low) */

/* Next Asynchronous List Address. Paragraph 2.3.7 */

#define EHCI_ASYNCLISTADDR_MASK (0xffffffe0) /* Bits 5-31: Link Pointer Low (LPL) */

/* Configured Flag Register. Paragraph 2.3.8 */

#define EHCI_CONFIGFLAG (1 << 0) /* Bit 0: Configure Flag */

/* Port Status/Control, Port 1-n. Paragraph 2.3.9 */

#define EHCI_PORTSC_CCS            (1 << 0) /* Bit 0: Current Connect Status */
#define EHCI_PORTSC_CSC            (1 << 1) /* Bit 1: Connect Status Change */
#define EHCI_PORTSC_PE             (1 << 2) /* Bit 2: Port Enable */
#define EHCI_PORTSC_PEC            (1 << 3) /* Bit 3: Port Enable/Disable Change */
#define EHCI_PORTSC_OCA            (1 << 4) /* Bit 4: Over-current Active */
#define EHCI_PORTSC_OCC            (1 << 5) /* Bit 5: Over-current Change */
#define EHCI_PORTSC_RESUME         (1 << 6) /* Bit 6: Force Port Resume */
#define EHCI_PORTSC_SUSPEND        (1 << 7) /* Bit 7: Suspend */
#define EHCI_PORTSC_RESET          (1 << 8) /* Bit 8: Port Reset */
#define EHCI_PORTSC_LSTATUS_SHIFT  (10)     /* Bits 10-11: Line Status */
#define EHCI_PORTSC_LSTATUS_MASK   (3 << EHCI_PORTSC_LSTATUS_SHIFT)
#define EHCI_PORTSC_LSTATUS_SE0    (0 << EHCI_PORTSC_LSTATUS_SHIFT) /* SE0 Not Low-speed device, perform EHCI reset */
#define EHCI_PORTSC_LSTATUS_KSTATE (1 << EHCI_PORTSC_LSTATUS_SHIFT) /* K-state Low-speed device, release ownership of port */
#define EHCI_PORTSC_LSTATUS_JSTATE (2 << EHCI_PORTSC_LSTATUS_SHIFT) /* J-state Not Low-speed device, perform EHCI reset */
#define EHCI_PORTSC_PP             (1 << 12)                        /* Bit 12: Port Power */
#define EHCI_PORTSC_OWNER          (1 << 13)                        /* Bit 13: Port Owner */
#define EHCI_PORTSC_PIC_SHIFT      (14)                             /* Bits 14-15: Port Indicator Control */
#define EHCI_PORTSC_PIC_MASK       (3 << EHCI_PORTSC_PIC_SHIFT)
#define EHCI_PORTSC_PIC_OFF        (0 << EHCI_PORTSC_PIC_SHIFT) /* Port indicators are off */
#define EHCI_PORTSC_PIC_AMBER      (1 << EHCI_PORTSC_PIC_SHIFT) /* Amber */
#define EHCI_PORTSC_PIC_GREEN      (2 << EHCI_PORTSC_PIC_SHIFT) /* Green */
#define EHCI_PORTSC_PTC_SHIFT      (16)                         /* Bits 16-19: Port Test Control */
#define EHCI_PORTSC_PTC_MASK       (15 << EHCI_PORTSC_PTC_SHIFT)
#define EHCI_PORTSC_PTC_DISABLED   (0 << EHCI_PORTSC_PTC_SHIFT) /* Test mode not enabled */
#define EHCI_PORTSC_PTC_JSTATE     (1 << EHCI_PORTSC_PTC_SHIFT) /* Test J_STATE */
#define EHCI_PORTSC_PTC_KSTATE     (2 << EHCI_PORTSC_PTC_SHIFT) /* Test K_STATE */
#define EHCI_PORTSC_PTC_SE0NAK     (3 << EHCI_PORTSC_PTC_SHIFT) /* Test SE0_NAK */
#define EHCI_PORTSC_PTC_PACKET     (4 << EHCI_PORTSC_PTC_SHIFT) /* Test Packet */
#define EHCI_PORTSC_PTC_ENABLE     (5 << EHCI_PORTSC_PTC_SHIFT) /* Test FORCE_ENABLE */
#define EHCI_PORTSC_WKCCNTE        (1 << 20)                    /* Bit 20: Wake on Connect Enable */
#define EHCI_PORTSC_WKDSCNNTE      (1 << 21)                    /* Bit 21: Wake on Disconnect Enable */
#define EHCI_PORTSC_WKOCE          (1 << 22)                    /* Bit 22: Wake on Over-current Enable */
                                                                /* Bits 23-31: Reserved */

#define EHCI_PORTSC_ALLINTS (EHCI_PORTSC_CSC | EHCI_PORTSC_PEC | \
                             EHCI_PORTSC_OCC | EHCI_PORTSC_RESUME)

/* Queue Head. Paragraph 3.6 */

/* Queue Head Horizontal Link Pointer: Queue Head DWord 0. Table 3-19 */

#define QH_HLP_END 0x1

#define QH_HLP_ITD(x)  (((uint32_t)(x) & ~0x1F) | 0x0) /* Isochronous Transfer Descriptor */
#define QH_HLP_QH(x)   (((uint32_t)(x) & ~0x1F) | 0x2) /* Queue Head */
#define QH_HLP_SITD(x) (((uint32_t)(x) & ~0x1F) | 0x4) /* Split Transaction Isochronous Transfer Descriptor */
#define QH_HLP_FSTN(x) (((uint32_t)(x) & ~0x1F) | 0x6) /* Frame Span Traversal Node */

/* Endpoint Characteristics: Queue Head DWord 1. Table 3-19 */

#define QH_EPCHAR_DEVADDR_SHIFT (0) /* Bitx 0-6: Device Address */
#define QH_EPCHAR_DEVADDR_MASK  (0x7f << QH_EPCHAR_DEVADDR_SHIFT)
#define QH_EPCHAR_I             (1 << 7) /* Bit 7: Inactivate on Next Transaction */
#define QH_EPCHAR_ENDPT_SHIFT   (8)      /* Bitx 8-11: Endpoint Number */
#define QH_EPCHAR_ENDPT_MASK    (15 << QH_EPCHAR_ENDPT_SHIFT)
#define QH_EPCHAR_EPS_SHIFT     (12) /* Bitx 12-13: Endpoint Speed */
#define QH_EPCHAR_EPS_MASK      (3 << QH_EPCHAR_EPS_SHIFT)
#define QH_EPCHAR_EPS_FULL      (0 << QH_EPCHAR_EPS_SHIFT) /* Full-Speed (12Mbs) */
#define QH_EPCHAR_EPS_LOW       (1 << QH_EPCHAR_EPS_SHIFT) /* Low-Speed (1.5Mbs) */
#define QH_EPCHAR_EPS_HIGH      (2 << QH_EPCHAR_EPS_SHIFT) /* High-Speed (480 Mb/s) */
#define QH_EPCHAR_DTC           (1 << 14)                  /* Bit 14: Data Toggle Control */
#define QH_EPCHAR_H             (1 << 15)                  /* Bit 15: Head of Reclamation List Flag */
#define QH_EPCHAR_MAXPKT_SHIFT  (16)                       /* Bitx 16-26: Maximum Packet Length */
#define QH_EPCHAR_MAXPKT_MASK   (0x7ff << QH_EPCHAR_MAXPKT_SHIFT)
#define QH_EPCHAR_C             (1 << 27) /* Bit 27: Control Endpoint Flag */
#define QH_EPCHAR_RL_SHIFT      (28)      /* Bitx 28-31: Nak Count Reload */
#define QH_EPCHAR_RL_MASK       (15 << QH_EPCHAR_RL_SHIFT)

/* Endpoint Capabilities: Queue Head DWord 2. Table 3-20 */

#define QH_EPCAPS_SSMASK_SHIFT  (0) /* Bitx 0-7: Interrupt Schedule Mask (Frame S-mask) */
#define QH_EPCAPS_SSMASK_MASK   (0xff << QH_EPCAPS_SSMASK_SHIFT)
#define QH_EPCAPS_SSMASK(n)     ((n) << QH_EPCAPS_SSMASK_SHIFT)
#define QH_EPCAPS_SCMASK_SHIFT  (8) /* Bitx 8-15: Split Completion Mask (Frame C-Mask) */
#define QH_EPCAPS_SCMASK_MASK   (0xff << QH_EPCAPS_SCMASK_SHIFT)
#define QH_EPCAPS_SCMASK(n)     ((n) << QH_EPCAPS_SCMASK_SHIFT)
#define QH_EPCAPS_HUBADDR_SHIFT (16) /* Bitx 16-22: Hub Address */
#define QH_EPCAPS_HUBADDR_MASK  (0x7f << QH_EPCAPS_HUBADDR_SHIFT)
#define QH_EPCAPS_HUBADDR(n)    ((n) << QH_EPCAPS_HUBADDR_SHIFT)
#define QH_EPCAPS_PORT_SHIFT    (23) /* Bit 23-29: Port Number */
#define QH_EPCAPS_PORT_MASK     (0x7f << QH_EPCAPS_PORT_SHIFT)
#define QH_EPCAPS_PORT(n)       ((n) << QH_EPCAPS_PORT_SHIFT)
#define QH_EPCAPS_MULT_SHIFT    (30) /* Bit 30-31: High-Bandwidth Pipe Multiplier */
#define QH_EPCAPS_MULT_MASK     (3 << QH_EPCAPS_MULT_SHIFT)
#define QH_EPCAPS_MULT(n)       ((n) << QH_EPCAPS_MULT_SHIFT)

/* qTD Token. Paragraph 3.5.3 */

#define QTD_LIST_END 1

#define QTD_TOKEN_STATUS_SHIFT       (0) /* Bits 0-7: Status */
#define QTD_TOKEN_STATUS_MASK        (0xff << QTD_TOKEN_STATUS_SHIFT)
#define QTD_TOKEN_STATUS_PINGSTATE   (1 << 0) /* Bit 0 Ping State  */
#define QTD_TOKEN_STATUS_ERR         (1 << 0) /* Bit 0 Error */
#define QTD_TOKEN_STATUS_SPLITXSTATE (1 << 1) /* Bit 1 Split Transaction State */
#define QTD_TOKEN_STATUS_MMF         (1 << 2) /* Bit 2 Missed Micro-Frame */
#define QTD_TOKEN_STATUS_XACTERR     (1 << 3) /* Bit 3 Transaction Error */
#define QTD_TOKEN_STATUS_BABBLE      (1 << 4) /* Bit 4 Babble Detected */
#define QTD_TOKEN_STATUS_DBERR       (1 << 5) /* Bit 5 Data Buffer Error */
#define QTD_TOKEN_STATUS_HALTED      (1 << 6) /* Bit 6 Halted */
#define QTD_TOKEN_STATUS_ACTIVE      (1 << 7) /* Bit 7 Active */
#define QTD_TOKEN_STATUS_ERRORS      (0x78 << QTD_TOKEN_STATUS_SHIFT)
#define QTD_TOKEN_PID_SHIFT          (8) /* Bits 8-9: PID Code */
#define QTD_TOKEN_PID_MASK           (3 << QTD_TOKEN_PID_SHIFT)
#define QTD_TOKEN_PID_OUT            (0 << QTD_TOKEN_PID_SHIFT) /* OUT Token generates token (E1H) */
#define QTD_TOKEN_PID_IN             (1 << QTD_TOKEN_PID_SHIFT) /* IN Token generates token (69H) */
#define QTD_TOKEN_PID_SETUP          (2 << QTD_TOKEN_PID_SHIFT) /* SETUP Token generates token (2DH) */
#define QTD_TOKEN_CERR_SHIFT         (10)                       /* Bits 10-11: Error Counter */
#define QTD_TOKEN_CERR_MASK          (3 << QTD_TOKEN_CERR_SHIFT)
#define QTD_TOKEN_CPAGE_SHIFT        (12) /* Bits 12-14: Current Page */
#define QTD_TOKEN_CPAGE_MASK         (7 << QTD_TOKEN_CPAGE_SHIFT)
#define QTD_TOKEN_IOC                (1 << 15) /* Bit 15: Interrupt On Complete */
#define QTD_TOKEN_NBYTES_SHIFT       (16)      /* Bits 16-30: Total Bytes to Transfer */
#define QTD_TOKEN_NBYTES_MASK        (0x7fff << QTD_TOKEN_NBYTES_SHIFT)
#define QTD_TOKEN_TOGGLE             (1 << 31) /* Bit 31: Data Toggle */

/* Isochronous (High-Speed) Transfer Descriptor (iTD). Paragraph 3.3 */

/* iTD Next Link Pointer. Paragraph 3.3.1 */

#define ITD_NLP_ITD(x)  (((uint32_t)(x) & ~0x1F) | 0x0)
#define ITD_NLP_QH(x)   (((uint32_t)(x) & ~0x1F) | 0x2)
#define ITD_NLP_SITD(x) (((uint32_t)(x) & ~0x1F) | 0x4)
#define ITD_NLP_FSTN(x) (((uint32_t)(x) & ~0x1F) | 0x6)

/* iTD Transaction Status and Control List. Paragraph 3.3.2 */
#define ITD_TSCL_XOFFS_SHIFT    (0) /* Bits 0-11: Transaction X offset */
#define ITD_TSCL_XOFFS_MASK     (0xfff << ITD_TSCL_XOFFS_SHIFT)
#define ITD_TSCL_PG_SHIFT       (12) /* Bits 12-14: Page select */
#define ITD_TSCL_PG_MASK        (7 << ITD_TSCL_PG_SHIFT)
#define ITD_TSCL_IOC            (1 << 15) /* Bit 15:  Interrupt On Comp */
#define ITD_TSCL_LENGTH_SHIFT   (16)      /* Bits 16-27:  Transaction length */
#define ITD_TSCL_LENGTH_MASK    (0xfff << ITD_TSCL_LENGTH_SHIFT)
#define ITD_TSCL_STATUS_SHIFT   (28) /* Bits 28-31:  Transaction status */
#define ITD_TSCL_STATUS_MASK    (15 << ITD_TSCL_STATUS_SHIFT)
#define ITD_TSCL_STATUS_XACTERR (1 << 28) /* Bit 28: Transaction error */
#define ITD_TSCL_STATUS_BABBLE  (1 << 29) /* Bit 29: Babble Detected */
#define ITD_TSCL_STATUS_DBERROR (1 << 30) /* Bit 30: Data Buffer Error */
#define ITD_TSCL_STATUS_ACTIVE  (1 << 31) /* Bit 31: Active error */

/* iTD Buffer Page Pointer List. Paragraph 3.3.4 */

/* iTD Buffer Pointer Page 0. Table 3-4 */

#define ITD_BUFPTR0_DEVADDR_SHIFT (0) /* Bits 0-6: Device Address */
#define ITD_BUFPTR0_DEVADDR_MASK  (0x7f << ITD_BUFPTR0_DEVADDR_SHIFT)
#define ITD_BUFPTR0_ENDPT_SHIFT   (8) /* Bits 8-11: Endpoint Number */
#define ITD_BUFPTR0_ENDPT_MASK    (15 << ITD_BUFPTR0_ENDPT_SHIFT)

/* iTD Buffer Pointer Page 1. Table 3-5 */

#define ITD_BUFPTR1_MAXPKT_SHIFT (0) /* Bits 0-10: Maximum Packet Size */
#define ITD_BUFPTR1_MAXPKT_MASK  (0x7ff << ITD_BUFPTR1_MAXPKT_SHIFT)
#define ITD_BUFPTR1_DIRIN        (1 << 11) /* Bit 11: Direction 1=IN */
#define ITD_BUFPTR1_DIROUT       (0)       /* Bit 11: Direction 0=OUT */

/* iTD Buffer Pointer Page 2. Table 3-6 */

#define ITD_BUFPTR2_MULTI_SHIFT (0) /* Bits 0-1: Multi */
#define ITD_BUFPTR2_MULTI_MASK  (3 << ITD_BUFPTR2_MULTI_SHIFT)
#define ITD_BUFPTR2_MULTI_1     (1 << ITD_BUFPTR2_MULTI_SHIFT) /* One transaction per micro-frame */
#define ITD_BUFPTR2_MULTI_2     (2 << ITD_BUFPTR2_MULTI_SHIFT) /* Two transactions per micro-frame */
#define ITD_BUFPTR2_MULTI_3     (3 << ITD_BUFPTR2_MULTI_SHIFT) /* Three transactions per micro-frame */

/* Registers ****************************************************************/

/* Host Controller Capability Registers.
 * This register block must be positioned at a well known address.
 */

struct ehci_hccr {
    volatile uint8_t caplength;        /* 0x00: Capability Register Length */
    volatile uint8_t reserved;         /* 0x01: reserved */
    volatile uint16_t hciversion;      /* 0x02: Interface Version Number */
    volatile uint32_t hcsparams;       /* 0x04: Structural Parameters */
    volatile uint32_t hccparams;       /* 0x08: Capability Parameters */
    volatile uint8_t hcspportroute[8]; /* 0x0c: Companion Port Route Description */
};

/* Host Controller Operational Registers.
 * This register block is positioned at an offset of 'caplength' from the
 * beginning of the Host Controller Capability Registers.
 */

struct ehci_hcor {
    volatile uint32_t usbcmd;           /* 0x00: USB Command */
    volatile uint32_t usbsts;           /* 0x04: USB Status */
    volatile uint32_t usbintr;          /* 0x08: USB Interrupt Enable */
    volatile uint32_t frindex;          /* 0x0c: USB Frame Index */
    volatile uint32_t ctrldssegment;    /* 0x10: 4G Segment Selector */
    volatile uint32_t periodiclistbase; /* 0x14: Frame List Base Address */
    volatile uint32_t asynclistaddr;    /* 0x18: Next Asynchronous List Address */
#ifndef CONFIG_USB_EHCI_HCOR_RESERVED_DISABLE
    uint32_t reserved[9];
#endif
    volatile uint32_t configflag; /* 0x40: Configured Flag Register */
    volatile uint32_t portsc[15]; /* 0x44: Port Status/Control */
};

/* USB2 Debug Port Register Interface.
 *  This register block is normally found via the PCI capabalities.
 * In non-PCI implementions, you need apriori information about the
 * location of these registers.
 */

struct ehci_debug {
    uint32_t psc;     /* 0x00: Debug Port Control/Status Register */
    uint32_t pids;    /* 0x04: Debug USB PIDs Register */
    uint32_t data[2]; /* 0x08: Debug Data buffer Registers */
    uint32_t addr;    /* 0x10: Device Address Register */
};

/* Data Structures **********************************************************/

/* Queue Element Transfer Descriptor (qTD). Paragraph 3.5 */

struct ehci_qtd {
    uint32_t next_qtd;     /* 0x00-0x03: Next qTD Pointer */
    uint32_t alt_next_qtd; /* 0x04-0x07: Alternate Next qTD Pointer */
    uint32_t token;        /* 0x08-0x0b: qTD Token */
    uint32_t bpl[5];       /* 0x0c-0x1c: Buffer Page Pointer List */
};

#define SIZEOF_EHCI_QTD (32) /* 8*sizeof(uint32_t) */

/* Queue Head. Paragraph 3.6 */

struct ehci_qh {
    uint32_t hlp;            /* 0x00-0x03: Queue Head Horizontal Link Pointer */
    uint32_t epchar;         /* 0x04-0x07: Endpoint Characteristics */
    uint32_t epcap;          /* 0x08-0x0b: Endpoint Capabilities */
    uint32_t curr_qtd;       /* 0x0c-0x0f: Current qTD Pointer */
    struct ehci_qtd overlay; /* 0x10-0x2c: Transfer overlay */
};

#define SIZEOF_EHCI_QH (48) /* 4*sizeof(uint32_t) + 32 */

/* Isochronous (High-Speed) Transfer Descriptor (iTD).
 * Paragraph 3.3.  Must be aligned to 32-byte boundaries.
 */

struct ehci_itd {
    uint32_t nlp;     /* 0x00-0x03: Next link pointer */
    uint32_t tscl[8]; /* 0x04-0x23: Transaction Status and Control List */
    uint32_t bpl[7];  /* 0x24-0x3c: Buffer Page Pointer List */
};

#define SIZEOF_EHCI_ITD (64) /* 16*sizeof(uint32_t) */

/* Split Transaction Isochronous Transfer Descriptor (siTD). Paragraph 3.4 */

struct ehci_sitd {
    uint32_t nlp;    /* 0x00-0x03: Next link pointer */
    uint32_t epchar; /* 0x04-0x07: Endpoint and Transaction Translator Characteristics */
    uint32_t mfsc;   /* 0x08-0x0b: Micro-frame Schedule Control */
    uint32_t tsc;    /* 0x0c-0x0f: Transfer Status and Control */
    uint32_t bpl[2]; /* 0x10-0x17: Buffer Pointer List */
    uint32_t blp;    /* 0x18-0x1b: Back link pointer */
};

#define SIZEOF_EHCI_SITD (28) /* 7*sizeof(uint32_t) */

#endif /* USB_HC_EHCI_H */
