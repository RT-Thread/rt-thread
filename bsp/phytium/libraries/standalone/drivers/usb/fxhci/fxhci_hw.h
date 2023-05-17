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
 * FilePath: fxhci_hw.h
 * Date: 2022-02-11 13:33:12
 * LastEditTime: 2022-02-18 09:13:47
 * Description:  This files is for definition of XHCI hardware register interface
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

#ifndef  FXHCI_HW_H
#define  FXHCI_HW_H

/***************************** Include Files *********************************/
#include "fio.h"
#include "fassert.h"
#include "fkernel.h"

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
/***************** eXtensible Host Controller Capability Registers ***********************/
#define FXHCI_REG_CAP_CAPLENGTH         0x00    /* specify the limits, restrictions and capabilities */
#define FXHCI_REG_CAP_HCIVERSION        0x02    /* Interface Version Number */
#define FXHCI_REG_CAP_HCSPARAMS1        0x04    /* Host Controller Structural Parameters 1 */
#define FXHCI_REG_CAP_HCSPARAMS2        0x08    /* Host Controller Structural Parameters 2 */
#define FXHCI_REG_CAP_HCSPARAMS3        0x0C    /* Host Controller Structural Parameters 3 */
#define FXHCI_REG_CAP_HCCPARAMS         0x10    /* Capability Parameters 1 */
#define FXHCI_REG_CAP_DBOFF             0x14    /* Doorbell Offset Register */
#define FXHCI_REG_CAP_RTSOFF            0x18    /* Runtime Register Space Offset Register */

/***************** Host Controller Operational Registers ***********************/
#define FXHCI_REG_OP_USBCMD             0x00    /* USB Command Register */
#define FXHCI_REG_OP_USBSTS             0x04    /* USB Status Register */
#define FXHCI_REG_OP_PAGESIZE           0x08    /* Page Size Register */
#define FXHCI_REG_OP_DNCTRL             0x14    /* Device Notification Control Register */
#define FXHCI_REG_OP_CRCR               0x18    /* Command Ring Control Register */
#define FXHCI_REG_OP_DCBAAP             0x30    /* Device Context Base Address Array Pointer Register */
#define FXHCI_REG_OP_CONFIG             0x38    /* Configure Register */

/* Port Status and Ctrl Register : OP Base + (400h + (10h * (n–1))) 'n' is port num */
#define FXHCI_REG_OP_PORTS_BASE         0x400   /* Port Status and Control Register Base */
#define FXHCI_REG_OP_PORTS_SIZE          0x10    /* Size of one Port SC Register */
#define FXHCI_REG_OP_PORTS_PORTSC       0x00    /* Port Status and Control Register */
#define FXHCI_REG_OP_PORTS_PORTPMSC     0x04    /* USB3 Port Power Management Status and Control Register */
#define FXHCI_REG_OP_PORTS_PORTLI       0x08    /* Port Link Info Register */

/***************** Host Controller Runtime Registers ***********************/
#define FXHCI_REG_RT_MFINDEX                0x00    /* Microframe Index */
#define FXHCI_REG_RT_IR0                    0x20    /* Interrupter Register Set 0 */
#define FXHCI_REG_RT_IR1023             0x8000  /* Interrupter Register Set 1023 */

/* Interrupter Register Set : RT Base + 020h + (32 * Interrupter) */
#define FXHCI_REG_RT_IR_SIZE             0x20    /* Size of one IR Register */
#define FXHCI_REG_RT_IR_IMAN                0x00    /* Interrupter Management Register */
#define FXHCI_REG_RT_IR_IMOD                0x04    /* Interrupter Moderation Register */
#define FXHCI_REG_RT_IR_ERSTSZ          0x08    /* Event Ring Segment Table Size Register */
#define FXHCI_REG_RT_IR_ERSTBA          0x10    /* Event Ring Segment Table Base Address Register */
#define FXHCI_REG_RT_IR_ERDP                0x18    /* Event Ring Dequeue Pointer Register */

/***************** Doorbell Register ***********************/
#define FXHCI_REG_DB_SIZE                4       /* Doorbell registers are 32 bits in length */

/***************** eXtensible Host Controller Capability Registers ***********************/

/** @name FXHCI_REG_CAP_HCSPARAMS1 Register
 */
#define FXHCI_REG_CAP_HCSPARAMS1_MAX_SLOTS_GET(x)    FUSB_REG32_GET_BITS(x, 7, 0)  /* Number of Device Slots (MaxSlots) */
#define FXHCI_REG_CAP_HCSPARAMS1_MAX_INTRS_GET(x)   FUSB_REG32_GET_BITS(x, 18, 8)  /* Number of Interrupters (MaxIntrs) */
#define FXHCI_REG_CAP_HCSPARAMS1_MAX_PORTS_GET(x)   FUSB_REG32_GET_BITS(x, 31, 24) /* Number of Ports (MaxPorts) */

/** @name FXHCI_REG_CAP_HCSPARAMS2 Register
 */
#define FXHCI_REG_CAP_HCSPARAMS2_IST_GET(x)         FUSB_REG32_GET_BITS(x, 3, 0)    /* Isochronous Scheduling Threshold (IST) */
#define FXHCI_REG_CAP_HCSPARAMS2_ERST_MAX_GET(x)        FUSB_REG32_GET_BITS(x, 7, 4)  /* Event Ring Segment Table Max (ERST Max) */
#define FXHCI_REG_CAP_HCSPARAMS2_SPR                    (1 << 26)                   /* Scratchpad Restore (SPR) */
#define FXHCI_REG_CAP_HCSPARAMS2_MAX_SCRATCHPAD_BUFS_GET(x) FUSB_REG32_GET_BITS(x, 31, 27)    /* Max Scratchpad Buffers (Max Scratchpad Bufs) */

/** @name FXHCI_REG_CAP_HCSPARAMS3 Register
 */
#define FXHCI_REG_CAP_HCSPARAMS3_U1_DEV_EXIT_LATENCY_GET(x) FUSB_REG32_GET_BITS(x, 7, 0)    /* U1 Device Exit Latency */
#define FXHCI_REG_CAP_HCSPARAMS3_U2_DEV_EXIT_LATENCY_GET(x) FUSB_REG32_GET_BITS(x, 31, 16) /* U2 Device Exit Latency */

/** @name FXHCI_REG_CAP_HCCPARAMS Register
 */
#define FXHCI_REG_CAP_HCCPARAMS_AC64                    (1 << 0)    /* 64-bit Addressing Capabilitya 1: 64-bit */
#define FXHCI_REG_CAP_HCCPARAMS_BNC                 (1 << 1)    /* BW Negotiation Capability (BNC) 1: support */
#define FXHCI_REG_CAP_HCCPARAMS_CSZ                 (1 << 2)    /* Context Size (CSZ) 1: 64 byte context data */
#define FXHCI_REG_CAP_HCCPARAMS_PPC                 (1 << 3)    /* Port Power Control (PPC) 1: support */
#define FXHCI_REG_CAP_HCCPARAMS_PIND                    (1 << 4)    /* Port Indicators (PIND) 1: support */
#define FXHCI_REG_CAP_HCCPARAMS_LHRC                    (1 << 5)    /* Light HC Reset Capability (LHRC) 1: support */
#define FXHCI_REG_CAP_HCCPARAMS_LTC                 (1 << 6)    /* Latency Tolerance Messaging Capability (LTC) */
#define FXHCI_REG_CAP_HCCPARAMS_NSS                 (1 << 7)    /* No Secondary SID Support (NSS) */
#define FXHCI_REG_CAP_HCCPARAMS_MAX_PSA_SIZE_GET(x)     FUSB_REG32_GET_BITS(x, 15, 12)    /* Maximum Primary Stream Array Size (MaxPSASize) */
#define FXHCI_REG_CAP_HCCPARAMS_XECP_GET(x)             FUSB_REG32_GET_BITS(x, 31, 16)    /* xHCI Extended Capabilities Pointer (xECP) */

/** @name FXHCI_REG_CAP_DBOFF Register
 */
#define FXHCI_REG_CAP_DBOFF_GET(x)        ((x) & GENMASK(31, 2))  /* 32-byte offset of the Doorbell Array base address from the Base */

/** @name FXHCI_REG_CAP_RTSOFF Register
 */
#define FXHCI_REG_CAP_RTSOFF_GET(x)       ((x) & GENMASK(31, 5)) /* 32-byte offset of the xHCI Runtime Registers */

/***************** Host Controller Operational Registers ***********************/

/** @name FXHCI_REG_OP_USBCMD Register
 */
#define FXHCI_REG_OP_USBCMD_RUN_STOP        (1 << 0)    /* Run/Stop (R/S) 1: RUN, 0: STOP - RW */
#define FXHCI_REG_OP_USBCMD_HCRST           (1 << 1)    /* Host Controller Reset (HCRST) 1: RESET - RW */
#define FXHCI_REG_OP_USBCMD_INTE            (1 << 2)    /* Interrupter Enable (INTE) 1: enabled - RW */
#define FXHCI_REG_OP_USBCMD_HSEE            (1 << 3)    /* Host System Error Enable (HSEE) - RW */
#define FXHCI_REG_OP_USBCMD_LHCRST          (1 << 7)    /* Light Host Controller Reset (LHCRST) - RW */
#define FXHCI_REG_OP_USBCMD_CSS             (1 << 8)    /* Controller Save State (CSS) - RW */
#define FXHCI_REG_OP_USBCMD_CRS             (1 << 9)    /* Controller Restore State (CRS) - RW */
#define FXHCI_REG_OP_USBCMD_EWE             (1 << 10)   /* Enable Wrap Event (EWE) - RW */
#define FXHCI_REG_OP_USBCMD_EU3S            (1 << 11)   /* Enable U3 MFINDEX Stop (EU3S) - RW */

/** @name FXHCI_REG_OP_USBSTS Register
 */
#define FXHCI_REG_OP_USBSTS_HCH             (1 << 0)    /* 1: Stopped executing */
#define FXHCI_REG_OP_USBSTS_HSE             (1 << 2)    /* 1: Serious error detected */
#define FXHCI_REG_OP_USBSTS_EINT            (1 << 3)    /* 1: Interrupt Pending (IP) */
#define FXHCI_REG_OP_USBSTS_PCD             (1 << 4)    /* 1: Port Change Detect */
#define FXHCI_REG_OP_USBSTS_SSS             (1 << 8)    /* remain 1 while the xHC saves its internal state */
#define FXHCI_REG_OP_USBSTS_RSS             (1 << 9)    /* remain 1 while the xHC restores its internal state */
#define FXHCI_REG_OP_USBSTS_SRE             (1 << 10)   /* if error occurs during a Save or Restore operation this bit shall be set to ‘1’. */
#define FXHCI_REG_OP_USBSTS_CNR             (1 << 11)   /* 1: Controller Not Ready */
#define FXHCI_REG_OP_USBSTS_HCE             (1 << 12)   /* 1: Internal xHC error condition */
#define FXHCI_REG_OP_USBSTS_PRSRV_MASK      ((1 << 1) | 0xffffe000) /* Rsvd bits */

/** @name FXHCI_REG_OP_PAGESIZE Register
 */
/* This xHC supports a page size of 2^(n+12) if bit n is Set */
#define FXHCI_REG_OP_PAGESIZE_4K                (1 << 0)    /* if bit 0 is Set, the xHC supports 4k byte page sizes */

/** @name FXHCI_REG_OP_CRCR Register
 */
#define FXHCI_REG_OP_CRCR_RCS               (1 << 0)    /* Ring Cycle State, value of the xHC Consumer Cycle State (CCS) flag */
#define FXHCI_REG_OP_CRCR_CS                    (1 << 1)    /* Command Stop, 1 */
#define FXHCI_REG_OP_CRCR_CA                    (1 << 2)    /* Command Abort, 1 */
#define FXHCI_REG_OP_CRCR_CRR               (1 << 3)    /* Command Ring Running */
#define FXHCI_REG_OP_CRCR_CR_PTR_MASK       GENMASK_ULL(63, 6)  /* Command Ring Pointer, Dequeue Ptr of Command Ring */

/** @name FXHCI_REG_OP_DCBAAP Register
 */
#define FXHCI_REG_OP_DCBAAP_MASK                     GENMASK_ULL(63, 6)             /* bit[31:6] Ptr of DCBAA */

/** @name FXHCI_REG_OP_CONFIG Register
 */
#define FXHCI_REG_OP_CONFIG_MAX_SLOTS_EN_MASK        GENMASK(7, 0)               /* Max Device Slots Enabled (MaxSlotsEn) – RW */
#define FXHCI_REG_OP_CONFIG_MAX_SLOTS_EN_SET(x)     FUSB_REG32_SET_BITS(x, 7, 0)    /* bit[7:0] Max Device Slots Enabled */
#define FXHCI_REG_OP_CONFIG_MAX_SLOTS_EN_GET(x)      FUSB_REG32_GET_BITS(x, 7, 0)

/** @name FXHCI_REG_OP_PORTS_PORTSC Register
 */
#define FXHCI_REG_OP_PORTS_PORTSC_CCS           (1 << 0)    /* Current Connect Status (CCS) – ROS */
#define FXHCI_REG_OP_PORTS_PORTSC_PED           (1 << 1)    /* Port Enabled/Disabled (PED) – RW1CS */
#define FXHCI_REG_OP_PORTS_PORTSC_OCA           (1 << 3)    /* Over-current Active (OCA) – RO */
#define FXHCI_REG_OP_PORTS_PORTSC_PR                (1 << 4)    /* Port Reset (PR) – RW1S */
#define FXHCI_REG_OP_PORTS_PORTSC_PLS_GET(x)    FUSB_REG32_GET_BITS(x, 8, 5)    /* Port Link State (PLS) – RWS */
#define FXHCI_REG_OP_PORTS_PORTSC_PLS_SET(x)    FUSB_REG32_SET_BITS(x, 8, 5)
#define FXHCI_REG_OP_PORTS_PORTSC_PLS_MASK      GENMASK(8, 5)
#define FXHCI_REG_OP_PORTS_PORTSC_PLS(x)            (x << 5)
/* Read value of Port Link State (PLS) */
/* refer to FXHCI doc page-408 for details (Port Link State) */
enum
{
    FXHCI_LINK_STATE_U0 = 0,                  /* U0 State */
    FXHCI_LINK_STATE_U1 = 1,                  /* U1 State */
    FXHCI_LINK_STATE_U2 = 2,                  /* U2 State */
    FXHCI_LINK_STATE_U3 = 3,                  /* U3 State (Device Suspended) */
    FXHCI_LINK_STATE_DISABLED = 4,        /* Disabled State */
    FXHCI_LINK_STATE_RX_DETECT = 5,       /* RxDetect State (Disconnected) */
    FXHCI_LINK_STATE_INACTIVE = 6,        /* Inactive State */
    FXHCI_LINK_STATE_POLLING = 7,         /* Polling State */
    FXHCI_LINK_STATE_RECOVERY = 8,        /* Recovery State */
    FXHCI_LINK_STATE_HOT_RESET = 9,       /* Hot Reset State */
    FXHCI_LINK_STATE_COMPLIANCE_MODE = 10, /* Compliance Mode State */
    FXHCI_LINK_STATE_TEST_MODE = 11,          /* Test Mode State */
    FXHCI_LINK_STATE_RESUME = 15,             /* Resume State */

    FXHCI_LINK_STATE_MAX
};

#define FXHCI_REG_OP_PORTS_PORTSC_PLS_SET(x)           FUSB_REG32_SET_BITS(x, 8, 5)

#define FXHCI_REG_OP_PORTS_PORTSC_PP (1 << 9)           /* Port Power (PP) – RWS */
#define FXHCI_REG_OP_PORTS_PORTSC_PORT_SPEED_GET(x) FUSB_REG32_GET_BITS(x, 13, 10)  /* Port Speed (Port Speed) – ROS */
/* Protocol Speed ID (PSI) 1~15 */
enum
{
    FXHCI_PORT_SPEED_UNDEFINED = 0,
    FXHCI_PORT_SPEED_1  = 1,
    FXHCI_PORT_SPEED_15 = 15,
};


#define FXHCI_REG_OP_PORTS_PORTSC_PIC_SET(x)  FUSB_REG32_SET_BITS(x, 15, 14)
#define FXHCI_REG_OP_PORTS_PORTSC_PIC_MASK    GENMASK(15, 14)
enum
{
    FXHCI_PORT_INDICATOR_OFF    = 0,
    FXHCI_PORT_INDICATOR_AMBER = 1,
    FXHCI_PORT_INDICATOR_GREEN = 2,
    FXHCI_PORT_INDICATOR_UNDEFINED = 3
};

#define FXHCI_REG_OP_PORTS_PORTSC_LWS (1 << 16)      /* Port Link State Write Strobe (LWS) */
#define FXHCI_REG_OP_PORTS_PORTSC_CSC (1 << 17)      /* Connect Status Change (CSC) */
#define FXHCI_REG_OP_PORTS_PORTSC_PEC (1 << 18)      /* Port Enabled/Disabled Change (PEC) 1: clear PED */
#define FXHCI_REG_OP_PORTS_PORTSC_WRC (1 << 19)      /* Warm Port Reset Change 1: Warm Reset complete */
#define FXHCI_REG_OP_PORTS_PORTSC_OCC (1 << 20)      /* Over-current Change 1: Over-current Active */
#define FXHCI_REG_OP_PORTS_PORTSC_PRC (1 << 21)      /* Port Reset Change 1: Transition of Port Reset */
#define FXHCI_REG_OP_PORTS_PORTSC_PLC (1 << 22)      /* Port Link State Change 1: PLS transition */
#define FXHCI_REG_OP_PORTS_PORTSC_CEC (1 << 23)      /* Port Config Error Change 1: Port Config Error detected */
#define FXHCI_REG_OP_PORTS_PORTSC_CAS (1 << 24)      /* Cold Attach Status  1: Far-end Receiver Terminations were detected */
#define FXHCI_REG_OP_PORTS_PORTSC_WCE (1 << 25)      /* Wake on Connect Enable 1: enable port to be sensitive to device connects */
#define FXHCI_REG_OP_PORTS_PORTSC_WDE (1 << 26)      /* Wake on Disconnect Enable 1: enable port to be sensitive to device disconnects */
#define FXHCI_REG_OP_PORTS_PORTSC_WOE (1 << 27)      /* Wake on Over-current Enable 1: enable port to be sensitive to  over-current conditions */
#define FXHCI_REG_OP_PORTS_PORTSC_DR  (1 << 30)      /* Device Removable, 0: Device is removable. 1:  Device is non-removable */
#define FXHCI_REG_OP_PORTS_PORTSC_WPR (1 << 31)      /* Warm Port Reset 1: follow Warm Reset sequence */
#define FXHCI_REG_OP_PORTS_PORTSC_RW_MASK (FXHCI_REG_OP_PORTS_PORTSC_PR | FXHCI_REG_OP_PORTS_PORTSC_PLS_MASK | FXHCI_REG_OP_PORTS_PORTSC_PP \
        | FXHCI_REG_OP_PORTS_PORTSC_PIC_MASK | FXHCI_REG_OP_PORTS_PORTSC_LWS | FXHCI_REG_OP_PORTS_PORTSC_WCE \
        | FXHCI_REG_OP_PORTS_PORTSC_WDE | FXHCI_REG_OP_PORTS_PORTSC_WOE)

/***************** Host Controller Runtime Registers ***********************/

/** @name FXHCI_REG_RT_IR_IMAN Register
 */
#define FXHCI_REG_RT_IR_IMAN_IP             (1 << 0)    /* Interrupt Pending, 1: an interrupt is pending for this Interrupter */
#define FXHCI_REG_RT_IR_IMAN_IE             (1 << 1)    /* Interrupt Enable, 1: capable of generating an interrupt. */

/** @name FXHCI_REG_RT_IR_IMOD Register
 */
#define FXHCI_REG_RT_IR_IMOD_IMODI_MASK         GENMASK(15, 0)  /* bit[15:0] Interrupt Moderation Interval default 4000 ==> 1ms  */
#define FXHCI_REG_RT_IR_IMOD_IMODC_MASK         GENMASK(31, 16) /* bit[31:16] Interrupt Moderation Counter(Down counter) */

/** @name FXHCI_REG_RT_IR_ERSTSZ Register
 */
#define FXHCI_REG_RT_IR_ERSTSZ_MASK                 GENMASK(15, 0)  /* bit[15:0] the number of valid Event Ring Segment Table entries */

/** @name FXHCI_REG_RT_IR_ERSTBA Register
 */
#define FXHCI_REG_RT_IR_ERSTBA_MASK                 GENMASK_ULL(63, 6) /* Event Ring Segment Table Base Address */

/** @name FXHCI_REG_RT_IR_ERDP Register
 */
#define FXHCI_REG_RT_IR_ERDP_DESI_MASK              GENMASK_ULL(2, 0)   /* bit[2:0] Dequeue ERST Segment Index */
#define FXHCI_REG_RT_IR_ERDP_EHB                        (1 << 3)            /* Event Handler Busy */
#define FXHCI_REG_RT_IR_ERDP_MASK                   GENMASK_ULL(63, 4)  /* Event Ring Dequeue Pointer */

/***************** Doorbell Register ***********************/
#define FXHCI_REG_DB_TARGET_HC_COMMAND          0   /* Host Controller Doorbell (0) Command Doorbell */
#define FXHCI_REG_DB_TARGET_EP0                 1   /* Device Context Doorbells Control EP 0 Enqueue Pointer Update */
#define FXHCI_REG_DB_TARGET_EP1_OUT             2   /* EP 1 OUT Enqueue Pointer Update */
#define FXHCI_REG_DB_TARGET_EP1_IN              3   /* EP 1 IN Enqueue Pointer Update */
#define FXHCI_REG_DB_TARGET_EP15_OUT                30  /* EP 15 OUT Enqueue Pointer Update */
#define FXHCI_REG_DB_TARGET_EP15_IN             31  /* EP 15 IN Enqueue Pointer Update */

/***************** xHCI Extended Capabilities Registers ***********************/
#define FXHCI_REG_EXT_CAP_CAP_ID_GET(x)              FUSB_REG32_GET_BITS(x, 7, 0)
/* refer to 'Table 138: xHCI Extended Capability Codes' for more details */
enum
{
    FXHCI_EXT_CAP_ID_USB_LEGACY_SUPPORT         = 1,
    FXHCI_EXT_CAP_ID_SUPPORT_PROTOCOL       = 2,
    FXHCI_EXT_CAP_ID_EXTEND_POWER_MANAGEMENT = 3,
    FXHCI_EXT_CAP_ID_IO_VIRTUALIZATION      = 4,
    FXHCI_EXT_CAP_ID_MESSAGE_INTERRUPT      = 5,
    FXHCI_EXT_CAP_ID_LOCAL_MEMORY           = 6,
    FXHCI_EXT_CAP_ID_USB_DEBUG_CAPABILITY   = 10,
    FXHCI_EXT_CAP_ID_EXT_MESSAGE_INTERRUPT  = 17,

    FXHCI_EXT_CAP_ID_VENDOR_DEFINED_MIN         = 192,
    FXHCI_EXT_CAP_ID_VENDOR_DEFINED_MAX         = 255
};

#define FXHCI_REG_EXT_CAP_NEXT_CAP_PTR_GET(x)        FUSB_REG32_GET_BITS(x, 15, 8)
#define FXHCI_REG_EXT_CAP_CAP_SPEC_GET(x)            FUSB_REG32_GET_BITS(x, 31, 16)
/* Ext capabilities specific definitions */
/* USB Legacy Support Capability */
#define FXHCI_REG_EXT_CAP_USBLEGSUP_OFFSET      0x0 /* used by pre-OS software (BIOS) and the operating system to coordinate ownership of the xHC. */
#define FXHCI_USBLEGSUP_BIOS_OWNED_SEMAPHORE        (1 << 16)   /* RW, The BIOS sets this bit to establish ownership of the xHC */
#define FXHCI_USBLEGSUP_OS_OWNED_SEMAPHORE      (1 << 24)   /* RW, System software sets this bit to request ownership of the xHC */

#define FXHCI_REG_EXT_CAP_USBLEGCTLSTS_OFFSET   0x4 /* uses this register to enable System Management Interrupts (SMIs) for every xHCI/USB event it needs to track */
#define FXHCI_USBLEGCTLSTS_USB_SMI_EN           (1 << 0)    /* RW, enable interrupts to trach event */
#define FXHCI_USBLEGCTLSTS_SMI_HC_ERR_EN            (1 << 4)    /* RW */
#define FXHCI_USBLEGCTLSTS_SMI_OS_OWE_EN            (1 << 13)   /* RW */
#define FXHCI_USBLEGCTLSTS_SMI_PCI_CMD_EN       (1 << 14)   /* RW */
#define FXHCI_USBLEGCTLSTS_SMI_BAR_EN           (1 << 15)   /* RW */
#define FXHCI_USBLEGCTLSTS_SMI_EVT_INTERRUPT    (1 << 16)   /* RO */
#define FXHCI_USBLEGCTLSTS_SMI_HC_SYS_ERR       (1 << 20)   /* RO */
#define FXHCI_USBLEGCTLSTS_SMI_OS_OWN_CHG       (1 << 29)   /* RW1C */
#define FXHCI_USBLEGCTLSTS_SMI_PCI_CMD          (1 << 30)   /* RW1C */
#define FXHCI_USBLEGCTLSTS_SMI_BAR              (1 << 31)   /* RW1C */

/* xHCI Supported Protocol Capability */
#define FXHCI_REG_EXT_CAP_USBSPCF_OFFSET            0x0
#define FXHCI_USBSPCF_MINOR_REVERSION_GET(x)        FUSB_REG32_GET_BITS(x, 23, 16)
#define FXHCI_USBSPCF_MAJOR_REVERSION_GET(x)        FUSB_REG32_GET_BITS(x, 31, 24)
enum
{
    FXHCI_MAJOR_REVERSION_USB2 = 2,
    FXHCI_MAJOR_REVERSION_USB3 = 3
};

#define FXHCI_REG_EXT_CAP_USBSPCFDEF_OFFSET     0x4
#define FXHCI_USBSPCFDEF_NAME_STRING_GET(x)     FUSB_REG32_GET_BITS(x, 31, 0)   /* four ASCII characters may be defined */
#define FXHCI_USBSPCFDEF_NAME_STRING_USB        0x20425355 /* ASCII = "USB" */

#define FXHCI_REG_EXT_CAP_USBSPCFDEF2_OFFSET            0x8
#define FXHCI_USBSPCFDEF2_COMPATIBLE_PORT_OFF_GET(x) FUSB_REG32_GET_BITS(x, 7, 0)
#define FXHCI_USBSPCFDEF2_COMPATIBLE_PORT_CNT_GET(x) FUSB_REG32_GET_BITS(x, 15, 8)
#define FXHCI_USBSPCFDEF2_PROTOCOL_DEFINED_GET(x)    FUSB_REG32_GET_BITS(x, 27, 16)
/* USB3 - No Protocol Defined fields */
/* USB2 */
#define FXHCI_USBSPCFDEF2_USB2_HIGH_SPEED_ONLY      (1 << 17)   /* High-speed Only (HSO) - RO */
#define FXHCI_USBSPCFDEF2_USB2_INTERGRATED_HUB      (1 << 18)   /* Integrated Hub Implemented (IHI) - RO */
#define FXHCI_USBSPCFDEF2_USB2_HW_LMP_CAP           (1 << 19)   /* Hardware LMP Capability (HLC) - RO */

#define FXHCI_USBSPCFDEF2_PROTOCOL_SPEED_ID_CNT_GET(x) FUSB_REG32_GET_BITS(x, 31, 28)

/*  Protocol Speed ID (PSI) */
#define FXHCI_REG_PROTOCOL_SPEED_ID_OFFSET(psic)        (0xc + ((psic) * sizeof(u32)))
#define FXHCI_PROTOCOL_SPEED_ID_VALUE_GET(x)             FUSB_REG32_GET_BITS(x, 3, 0)   /* Protocol Speed ID Value (PSIV) */
#define FXHCI_PROTOCOL_SPEED_ID_EXPONENT_GET(x)      FUSB_REG32_GET_BITS(x, 5, 4) /* Protocol Speed ID Exponent (PSIE) */
#define FXHCI_PROTOCOL_SPEED_ID_PSI_TYPE_GET(x)      FUSB_REG32_GET_BITS(x, 7, 6) /* PSI Type (PLT) */
enum
{
    FXHCI_PROTOCOL_SPEED_ID_PSI_SYMMETRIC = 0,
    FXHCI_PROTOCOL_SPEED_ID_PSI_ASYMMETRIC_RX = 2,
    FXHCI_PROTOCOL_SPEED_ID_PSI_ASYMMETRIC_TX = 3
};
#define FXHCI_PROTOCOL_SPEED_ID_PSI_FULL_DUPLEX     (1 << 8)
#define FXHCI_PROTOCOL_SPEED_ID_MANTISSA_GET(x)     FUSB_REG32_GET_BITS(x, 31, 16) /* Protocol Speed ID Mantissa (PSIM) */

/**************************** Type Definitions *******************************/

/* Device Context Base Address Array */
#define FXHCI_SCRATCHPAD_BUF_ARRAY_BASE_ADDR_MASK     GENMASK_ULL(63, 6)     /* Array Element 0 Field Bit */
#define FXHCI_DEVICE_CONTEXT_BASE_ADDR_MASK           GENMASK_ULL(63, 6)     /* Array Element 1-n Field Bit */

/* Slot index */
#define FXHCI_REG_DB_HOST_CONTROLLER                    0
#define FXHCI_REG_DB_DEVICE_CONTEXT1                    1
#define FXHCI_REG_DB_DEVICE_CONTEXT255                  255

typedef struct
{
    u8 port_beg;
    u8 port_end;
} FXhciPortRange;

typedef enum
{
    FXHCI_USB2_COMPATIBLE_PORT,
    FXHCI_USB3_COMPATIBLE_PORT,

    FXHCI_NONE_COMPATIBLE_PORT
} FXhciPortCompatible;

typedef struct
{
    uintptr base;               /* Capability registers offset */
    uintptr oper_base;          /* Operational registers offset */
    uintptr doorbell_base;      /* Doorbell registers offset */
    uintptr runtime_base;       /* Runtime registers offset */
    uintptr port_base;          /* Port register set offset */
    uintptr xecp_base;          /* xHCI Extended Capabilities register offset */
    u32 hcx_params[4];          /* Capability cache */
    FXhciPortRange usb2_ports;
    FXhciPortRange usb3_ports;
} FXhciMMIO;


/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
static inline FXhciPortCompatible FUsb3CheckPortCompatible(FXhciMMIO *mmio, u8 port_id)
{
    FASSERT(mmio);
    if ((port_id >= mmio->usb3_ports.port_beg) && (port_id <= mmio->usb3_ports.port_end))
    {
        return FXHCI_USB3_COMPATIBLE_PORT;
    }
    else if ((port_id >= mmio->usb2_ports.port_beg) && (port_id <= mmio->usb2_ports.port_end))
    {
        return FXHCI_USB2_COMPATIBLE_PORT;
    }

    FASSERT(0); /* must not reach there */
    return FXHCI_NONE_COMPATIBLE_PORT;
}

static inline u32 FXhciReadCap(const FXhciMMIO *mmio)
{
    FASSERT(mmio);
    FASSERT(mmio->base != 0);

    return FtIn32(mmio->base + FXHCI_REG_CAP_CAPLENGTH);
}

static inline u8 FXhciReadCaplen(const FXhciMMIO *mmio)
{
    FASSERT(mmio);
    FASSERT(mmio->base != 0);
    u32 reg_val = FXhciReadCap(mmio);

    /* get lower 8-bits */
    return (u8)(reg_val & 0xff);
}

static inline u16 FXhciReadHcVersion(const FXhciMMIO *mmio)
{
    FASSERT(mmio);
    FASSERT(mmio->base != 0);
    u32 reg_val = FXhciReadCap(mmio);

    /* get upper 16 bits */
    return (u16)((reg_val >> 16) & 0xffff);
}

static inline u32 FXhciReadCap32(const FXhciMMIO *mmio, u32 offset)
{
    FASSERT(mmio);
    FASSERT(mmio->base != 0);

    offset -= FXHCI_REG_CAP_HCSPARAMS1;
    offset /= 4;

    FASSERT(offset < 4);
    return mmio->hcx_params[offset]; /* read caps from cache */
}

static inline u32 FXhciReadOper32(const FXhciMMIO *mmio, u32 offset)
{
    FASSERT(mmio);
    FASSERT(mmio->base != 0);

    return FtIn32(mmio->oper_base + offset);
}

static inline u64 FXhciReadOper64(const FXhciMMIO *mmio, u32 offset)
{
    FASSERT(mmio);
    FASSERT(mmio->base != 0);

    uintptr addr = mmio->oper_base + offset;

    u64 val = FtIn32(addr);
    val |= ((u64)FtIn32(addr + 4)) << 32;

    return val;
}

static inline void FXhciWriteOper32(const FXhciMMIO *mmio, u32 offset, u32 val)
{
    FASSERT(mmio);
    FASSERT(mmio->base != 0);

    FtOut32(mmio->oper_base + offset, val);
}

static inline void FXhciWriteOper64(const FXhciMMIO *mmio, u32 offset, u64 val)
{
    FASSERT(mmio);
    FASSERT(mmio->base != 0);

    FXhciWriteOper32(mmio, offset, LOWER_32_BITS(val));
    FXhciWriteOper32(mmio, offset + 4, UPPER_32_BITS(val));
}

static inline u32 FXhciReadPort32(const FXhciMMIO *mmio, u32 port, u32 offset)
{
    FASSERT(mmio);
    FASSERT(mmio->base != 0);

    /* Operational Base + (400h + (10h * (n–1))) */
    return FtIn32(mmio->port_base + port * FXHCI_REG_OP_PORTS_SIZE + offset);
}

static inline void FXhciWritePort32(const FXhciMMIO *mmio, u32 port, u32 offset, u32 val)
{
    FASSERT(mmio);
    FASSERT(mmio->base != 0);

    FtOut32(mmio->port_base + port * FXHCI_REG_OP_PORTS_SIZE + offset, val);
}

static inline u32 FXhciReadRt32(const FXhciMMIO *mmio, u32 interrupt, u32 offset)
{
    FASSERT(mmio);
    FASSERT(mmio->base != 0);

    /* Runtime Base + 020h + (32 * Interrupter) */
    return FtIn32(mmio->runtime_base + FXHCI_REG_RT_IR0 + interrupt * FXHCI_REG_RT_IR_SIZE + offset);
}

static inline u64 FXhciReadRt64(const FXhciMMIO *mmio, u32 interrupt, u32 offset)
{
    FASSERT(mmio);
    FASSERT(mmio->base != 0);

    uintptr addr = mmio->runtime_base + FXHCI_REG_RT_IR0 + interrupt * FXHCI_REG_RT_IR_SIZE + offset;
    u64 reg_val = FtIn32(addr);
    reg_val |= (u64)FtIn32(addr + 4) << 32;

    return reg_val;
}

static inline void FXhciWriteRt32(const FXhciMMIO *mmio, u32 interrupt, u32 offset, u32 val)
{
    FASSERT(mmio);
    FASSERT(mmio->base != 0);

    FtOut32(mmio->runtime_base + FXHCI_REG_RT_IR0 + interrupt * FXHCI_REG_RT_IR_SIZE + offset, val);
}

static inline void FXhciWriteRt64(const FXhciMMIO *mmio, u32 interrupt, u32 offset, u64 val)
{
    FASSERT(mmio);
    FASSERT(mmio->base != 0);

    FXhciWriteRt32(mmio, interrupt, offset, (u32)val);
    FXhciWriteRt32(mmio, interrupt, offset + 4, (u32)(val >> 32));
}

static inline u32 FXhciReadExtCap32(const FXhciMMIO *mmio, u32 offset)
{
    FASSERT(mmio);
    FASSERT(mmio->base != 0);
    FASSERT(mmio->xecp_base != 0);

    return FtIn32(mmio->xecp_base + offset);
}

static inline void FXhciWriteDb32(const FXhciMMIO *mmio, u32 slot, u32 val)
{
    FASSERT(mmio);
    FASSERT(mmio->base != 0);

    FtOut32(mmio->doorbell_base + slot * FXHCI_REG_DB_SIZE, val);
}

static inline int FXhciGetCtxSize(const FXhciMMIO *mmio)
{
    FASSERT(mmio);
    FASSERT(mmio->base != 0);

    u32 reg_val = FXhciReadCap32(mmio, FXHCI_REG_CAP_HCCPARAMS);
    return ((reg_val & FXHCI_REG_CAP_HCCPARAMS_CSZ) == FXHCI_REG_CAP_HCCPARAMS_CSZ) ? 64 : 32;
}

/************************** Function Prototypes ******************************/
FError FXhciSetupMMIO(FXhciMMIO *mmio, uintptr base_addr);
void FXhciListExtCap(FXhciMMIO *mmio);
FError FXhciWaitOper32(FXhciMMIO *mmio, u32 offset, u32 mask, u32 exp_val, u32 timeout_tick);

#ifdef __cplusplus
}
#endif


#endif