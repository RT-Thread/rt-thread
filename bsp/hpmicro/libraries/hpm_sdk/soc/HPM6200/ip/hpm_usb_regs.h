/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_USB_H
#define HPM_USB_H

typedef struct {
    __R  uint8_t  RESERVED0[128];              /* 0x0 - 0x7F: Reserved */
    __RW uint32_t GPTIMER0LD;                  /* 0x80: General Purpose Timer #0 Load Register */
    __RW uint32_t GPTIMER0CTRL;                /* 0x84: General Purpose Timer #0 Controller Register */
    __RW uint32_t GPTIMER1LD;                  /* 0x88: General Purpose Timer #1 Load Register */
    __RW uint32_t GPTIMER1CTRL;                /* 0x8C: General Purpose Timer #1 Controller Register */
    __RW uint32_t SBUSCFG;                     /* 0x90: System Bus Config Register */
    __R  uint8_t  RESERVED1[172];              /* 0x94 - 0x13F: Reserved */
    __RW uint32_t USBCMD;                      /* 0x140: USB Command Register */
    __RW uint32_t USBSTS;                      /* 0x144: USB Status Register */
    __RW uint32_t USBINTR;                     /* 0x148: Interrupt Enable Register */
    __RW uint32_t FRINDEX;                     /* 0x14C: USB Frame Index Register */
    __R  uint8_t  RESERVED2[4];                /* 0x150 - 0x153: Reserved */
    union {
        __RW uint32_t DEVICEADDR;              /* 0x154: Device Address Register */
        __RW uint32_t PERIODICLISTBASE;        /* 0x154: Frame List Base Address Register */
    };
    union {
        __RW uint32_t ASYNCLISTADDR;           /* 0x158: Next Asynch. Address Register */
        __RW uint32_t ENDPTLISTADDR;           /* 0x158: Endpoint List Address Register */
    };
    __R  uint8_t  RESERVED3[4];                /* 0x15C - 0x15F: Reserved */
    __RW uint32_t BURSTSIZE;                   /* 0x160: Programmable Burst Size Register */
    __RW uint32_t TXFILLTUNING;                /* 0x164: TX FIFO Fill Tuning Register */
    __R  uint8_t  RESERVED4[16];               /* 0x168 - 0x177: Reserved */
    __RW uint32_t ENDPTNAK;                    /* 0x178: Endpoint NAK Register */
    __RW uint32_t ENDPTNAKEN;                  /* 0x17C: Endpoint NAK Enable Register */
    __R  uint8_t  RESERVED5[4];                /* 0x180 - 0x183: Reserved */
    __RW uint32_t PORTSC1;                     /* 0x184: Port Status & Control */
    __R  uint8_t  RESERVED6[28];               /* 0x188 - 0x1A3: Reserved */
    __RW uint32_t OTGSC;                       /* 0x1A4: On-The-Go Status & control Register */
    __RW uint32_t USBMODE;                     /* 0x1A8: USB Device Mode Register */
    __RW uint32_t ENDPTSETUPSTAT;              /* 0x1AC: Endpoint Setup Status Register */
    __RW uint32_t ENDPTPRIME;                  /* 0x1B0: Endpoint Prime Register */
    __RW uint32_t ENDPTFLUSH;                  /* 0x1B4: Endpoint Flush Register */
    __R  uint32_t ENDPTSTAT;                   /* 0x1B8: Endpoint Status Register */
    __RW uint32_t ENDPTCOMPLETE;               /* 0x1BC: Endpoint Complete Register */
    __RW uint32_t ENDPTCTRL[8];                /* 0x1C0 - 0x1DC: Endpoint Control0 Register... Endpoint Control7 Register */
    __R  uint8_t  RESERVED7[32];               /* 0x1E0 - 0x1FF: Reserved */
    __RW uint32_t OTG_CTRL0;                   /* 0x200:  */
    __R  uint8_t  RESERVED8[12];               /* 0x204 - 0x20F: Reserved */
    __RW uint32_t PHY_CTRL0;                   /* 0x210:  */
    __RW uint32_t PHY_CTRL1;                   /* 0x214:  */
    __R  uint8_t  RESERVED9[8];                /* 0x218 - 0x21F: Reserved */
    __RW uint32_t TOP_STATUS;                  /* 0x220:  */
    __RW uint32_t PHY_STATUS;                  /* 0x224:  */
} USB_Type;


/* Bitfield definition for register: GPTIMER0LD */
/*
 * GPTLD (RW)
 *
 * GPTLD
 * General Purpose Timer Load Value
 * These bit fields are loaded to GPTCNT bits when GPTRST bit is set '1b'.
 * This value represents the time in microseconds minus 1 for the timer duration.
 * Example: for a one millisecond timer, load 1000-1=999 or 0x0003E7.
 * NOTE: Max value is 0xFFFFFF or 16.777215 seconds.
 */
#define USB_GPTIMER0LD_GPTLD_MASK (0xFFFFFFUL)
#define USB_GPTIMER0LD_GPTLD_SHIFT (0U)
#define USB_GPTIMER0LD_GPTLD_SET(x) (((uint32_t)(x) << USB_GPTIMER0LD_GPTLD_SHIFT) & USB_GPTIMER0LD_GPTLD_MASK)
#define USB_GPTIMER0LD_GPTLD_GET(x) (((uint32_t)(x) & USB_GPTIMER0LD_GPTLD_MASK) >> USB_GPTIMER0LD_GPTLD_SHIFT)

/* Bitfield definition for register: GPTIMER0CTRL */
/*
 * GPTRUN (RW)
 *
 * GPTRUN
 * General Purpose Timer Run
 * GPTCNT bits are not effected when setting or clearing this bit.
 * 0 - Stop counting
 * 1 - Run
 */
#define USB_GPTIMER0CTRL_GPTRUN_MASK (0x80000000UL)
#define USB_GPTIMER0CTRL_GPTRUN_SHIFT (31U)
#define USB_GPTIMER0CTRL_GPTRUN_SET(x) (((uint32_t)(x) << USB_GPTIMER0CTRL_GPTRUN_SHIFT) & USB_GPTIMER0CTRL_GPTRUN_MASK)
#define USB_GPTIMER0CTRL_GPTRUN_GET(x) (((uint32_t)(x) & USB_GPTIMER0CTRL_GPTRUN_MASK) >> USB_GPTIMER0CTRL_GPTRUN_SHIFT)

/*
 * GPTRST (WO)
 *
 * GPTRST
 * General Purpose Timer Reset
 * 0 - No action
 * 1 - Load counter value from GPTLD bits in n_GPTIMER0LD
 */
#define USB_GPTIMER0CTRL_GPTRST_MASK (0x40000000UL)
#define USB_GPTIMER0CTRL_GPTRST_SHIFT (30U)
#define USB_GPTIMER0CTRL_GPTRST_SET(x) (((uint32_t)(x) << USB_GPTIMER0CTRL_GPTRST_SHIFT) & USB_GPTIMER0CTRL_GPTRST_MASK)
#define USB_GPTIMER0CTRL_GPTRST_GET(x) (((uint32_t)(x) & USB_GPTIMER0CTRL_GPTRST_MASK) >> USB_GPTIMER0CTRL_GPTRST_SHIFT)

/*
 * GPTMODE (RW)
 *
 * GPTMODE
 * General Purpose Timer Mode
 * In one shot mode, the timer will count down to zero, generate an interrupt, and stop until the counter is
 * reset by software;
 * In repeat mode, the timer will count down to zero, generate an interrupt and automatically reload the
 * counter value from GPTLD bits to start again.
 * 0 - One Shot Mode
 * 1 - Repeat Mode
 */
#define USB_GPTIMER0CTRL_GPTMODE_MASK (0x1000000UL)
#define USB_GPTIMER0CTRL_GPTMODE_SHIFT (24U)
#define USB_GPTIMER0CTRL_GPTMODE_SET(x) (((uint32_t)(x) << USB_GPTIMER0CTRL_GPTMODE_SHIFT) & USB_GPTIMER0CTRL_GPTMODE_MASK)
#define USB_GPTIMER0CTRL_GPTMODE_GET(x) (((uint32_t)(x) & USB_GPTIMER0CTRL_GPTMODE_MASK) >> USB_GPTIMER0CTRL_GPTMODE_SHIFT)

/*
 * GPTCNT (RO)
 *
 * GPTCNT
 * General Purpose Timer Counter.
 * This field is the count value of the countdown timer.
 */
#define USB_GPTIMER0CTRL_GPTCNT_MASK (0xFFFFFFUL)
#define USB_GPTIMER0CTRL_GPTCNT_SHIFT (0U)
#define USB_GPTIMER0CTRL_GPTCNT_GET(x) (((uint32_t)(x) & USB_GPTIMER0CTRL_GPTCNT_MASK) >> USB_GPTIMER0CTRL_GPTCNT_SHIFT)

/* Bitfield definition for register: GPTIMER1LD */
/*
 * GPTLD (RW)
 *
 * GPTLD
 * General Purpose Timer Load Value
 * These bit fields are loaded to GPTCNT bits when GPTRST bit is set '1b'.
 * This value represents the time in microseconds minus 1 for the timer duration.
 * Example: for a one millisecond timer, load 1000-1=999 or 0x0003E7.
 * NOTE: Max value is 0xFFFFFF or 16.777215 seconds.
 */
#define USB_GPTIMER1LD_GPTLD_MASK (0xFFFFFFUL)
#define USB_GPTIMER1LD_GPTLD_SHIFT (0U)
#define USB_GPTIMER1LD_GPTLD_SET(x) (((uint32_t)(x) << USB_GPTIMER1LD_GPTLD_SHIFT) & USB_GPTIMER1LD_GPTLD_MASK)
#define USB_GPTIMER1LD_GPTLD_GET(x) (((uint32_t)(x) & USB_GPTIMER1LD_GPTLD_MASK) >> USB_GPTIMER1LD_GPTLD_SHIFT)

/* Bitfield definition for register: GPTIMER1CTRL */
/*
 * GPTRUN (RW)
 *
 * GPTRUN
 * General Purpose Timer Run
 * GPTCNT bits are not effected when setting or clearing this bit.
 * 0 - Stop counting
 * 1 - Run
 */
#define USB_GPTIMER1CTRL_GPTRUN_MASK (0x80000000UL)
#define USB_GPTIMER1CTRL_GPTRUN_SHIFT (31U)
#define USB_GPTIMER1CTRL_GPTRUN_SET(x) (((uint32_t)(x) << USB_GPTIMER1CTRL_GPTRUN_SHIFT) & USB_GPTIMER1CTRL_GPTRUN_MASK)
#define USB_GPTIMER1CTRL_GPTRUN_GET(x) (((uint32_t)(x) & USB_GPTIMER1CTRL_GPTRUN_MASK) >> USB_GPTIMER1CTRL_GPTRUN_SHIFT)

/*
 * GPTRST (WO)
 *
 * GPTRST
 * General Purpose Timer Reset
 * 0 - No action
 * 1 - Load counter value from GPTLD bits in USB_n_GPTIMER1LD
 */
#define USB_GPTIMER1CTRL_GPTRST_MASK (0x40000000UL)
#define USB_GPTIMER1CTRL_GPTRST_SHIFT (30U)
#define USB_GPTIMER1CTRL_GPTRST_SET(x) (((uint32_t)(x) << USB_GPTIMER1CTRL_GPTRST_SHIFT) & USB_GPTIMER1CTRL_GPTRST_MASK)
#define USB_GPTIMER1CTRL_GPTRST_GET(x) (((uint32_t)(x) & USB_GPTIMER1CTRL_GPTRST_MASK) >> USB_GPTIMER1CTRL_GPTRST_SHIFT)

/*
 * GPTMODE (RW)
 *
 * GPTMODE
 * General Purpose Timer Mode
 * In one shot mode, the timer will count down to zero, generate an interrupt, and stop until the counter is
 * reset by software. In repeat mode, the timer will count down to zero, generate an interrupt and
 * automatically reload the counter value from GPTLD bits to start again.
 * 0 - One Shot Mode
 * 1 - Repeat Mode
 */
#define USB_GPTIMER1CTRL_GPTMODE_MASK (0x1000000UL)
#define USB_GPTIMER1CTRL_GPTMODE_SHIFT (24U)
#define USB_GPTIMER1CTRL_GPTMODE_SET(x) (((uint32_t)(x) << USB_GPTIMER1CTRL_GPTMODE_SHIFT) & USB_GPTIMER1CTRL_GPTMODE_MASK)
#define USB_GPTIMER1CTRL_GPTMODE_GET(x) (((uint32_t)(x) & USB_GPTIMER1CTRL_GPTMODE_MASK) >> USB_GPTIMER1CTRL_GPTMODE_SHIFT)

/*
 * GPTCNT (RO)
 *
 * GPTCNT
 * General Purpose Timer Counter.
 * This field is the count value of the countdown timer.
 */
#define USB_GPTIMER1CTRL_GPTCNT_MASK (0xFFFFFFUL)
#define USB_GPTIMER1CTRL_GPTCNT_SHIFT (0U)
#define USB_GPTIMER1CTRL_GPTCNT_GET(x) (((uint32_t)(x) & USB_GPTIMER1CTRL_GPTCNT_MASK) >> USB_GPTIMER1CTRL_GPTCNT_SHIFT)

/* Bitfield definition for register: SBUSCFG */
/*
 * AHBBRST (RW)
 *
 * AHBBRST
 * AHB master interface Burst configuration
 * These bits control AHB master transfer type sequence (or priority).
 * NOTE: This register overrides n_BURSTSIZE register when its value is not zero.
 * 000 - Incremental burst of unspecified length only
 * 001 - INCR4 burst, then single transfer
 * 010 - INCR8 burst, INCR4 burst, then single transfer
 * 011 - INCR16 burst, INCR8 burst, INCR4 burst, then single transfer
 * 100 - Reserved, don't use
 * 101 - INCR4 burst, then incremental burst of unspecified length
 * 110 - INCR8 burst, INCR4 burst, then incremental burst of unspecified length
 * 111 - INCR16 burst, INCR8 burst, INCR4 burst, then incremental burst of unspecified length
 */
#define USB_SBUSCFG_AHBBRST_MASK (0x7U)
#define USB_SBUSCFG_AHBBRST_SHIFT (0U)
#define USB_SBUSCFG_AHBBRST_SET(x) (((uint32_t)(x) << USB_SBUSCFG_AHBBRST_SHIFT) & USB_SBUSCFG_AHBBRST_MASK)
#define USB_SBUSCFG_AHBBRST_GET(x) (((uint32_t)(x) & USB_SBUSCFG_AHBBRST_MASK) >> USB_SBUSCFG_AHBBRST_SHIFT)

/* Bitfield definition for register: USBCMD */
/*
 * ITC (RW)
 *
 * ITC
 * Interrupt Threshold Control -Read/Write.
 * The system software uses this field to set the maximum rate at which the host/device controller will issue interrupts.
 * ITC contains the maximum interrupt interval measured in micro-frames. Valid values are
 * shown below.
 * Value Maximum Interrupt Interval
 * 00000000 - Immediate (no threshold)
 * 00000001 - 1 micro-frame
 * 00000010 - 2 micro-frames
 * 00000100 - 4 micro-frames
 * 00001000 - 8 micro-frames
 * 00010000 - 16 micro-frames
 * 00100000 - 32 micro-frames
 * 01000000 - 64 micro-frames
 */
#define USB_USBCMD_ITC_MASK (0xFF0000UL)
#define USB_USBCMD_ITC_SHIFT (16U)
#define USB_USBCMD_ITC_SET(x) (((uint32_t)(x) << USB_USBCMD_ITC_SHIFT) & USB_USBCMD_ITC_MASK)
#define USB_USBCMD_ITC_GET(x) (((uint32_t)(x) & USB_USBCMD_ITC_MASK) >> USB_USBCMD_ITC_SHIFT)

/*
 * FS_2 (RW)
 *
 * FS_2
 * Frame List Size - (Read/Write or Read Only). [host mode only]
 * This field is Read/Write only if Programmable Frame List Flag in the HCCPARAMS registers is set to one.
 * This field specifies the size of the frame list that controls which bits in the Frame Index Register should be used for the Frame List Current index.
 * NOTE: This field is made up from USBCMD bits 15, 3 and 2.
 * Value Meaning
 * 0b000 - 1024 elements (4096 bytes) Default value
 * 0b001 - 512 elements (2048 bytes)
 * 0b010 - 256 elements (1024 bytes)
 * 0b011 - 128 elements (512 bytes)
 * 0b100 - 64 elements (256 bytes)
 * 0b101 - 32 elements (128 bytes)
 * 0b110 - 16 elements (64 bytes)
 * 0b111 - 8 elements (32 bytes)
 */
#define USB_USBCMD_FS_2_MASK (0x8000U)
#define USB_USBCMD_FS_2_SHIFT (15U)
#define USB_USBCMD_FS_2_SET(x) (((uint32_t)(x) << USB_USBCMD_FS_2_SHIFT) & USB_USBCMD_FS_2_MASK)
#define USB_USBCMD_FS_2_GET(x) (((uint32_t)(x) & USB_USBCMD_FS_2_MASK) >> USB_USBCMD_FS_2_SHIFT)

/*
 * ATDTW (RW)
 *
 * ATDTW
 * Add dTD TripWire - Read/Write. [device mode only]
 * This bit is used as a semaphore to ensure proper addition of a new dTD to an active (primed) endpoint's
 * linked list. This bit is set and cleared by software.
 * This bit would also be cleared by hardware when state machine is hazard region for which adding a dTD
 * to a primed endpoint may go unrecognized.
 */
#define USB_USBCMD_ATDTW_MASK (0x4000U)
#define USB_USBCMD_ATDTW_SHIFT (14U)
#define USB_USBCMD_ATDTW_SET(x) (((uint32_t)(x) << USB_USBCMD_ATDTW_SHIFT) & USB_USBCMD_ATDTW_MASK)
#define USB_USBCMD_ATDTW_GET(x) (((uint32_t)(x) & USB_USBCMD_ATDTW_MASK) >> USB_USBCMD_ATDTW_SHIFT)

/*
 * SUTW (RW)
 *
 * SUTW
 * Setup TripWire - Read/Write. [device mode only]
 * This bit is used as a semaphore to ensure that the setup data payload of 8 bytes is extracted from a QH by the DCD without being corrupted.
 * If the setup lockout mode is off (SLOM bit in USB core register n_USBMODE, see USBMODE ) then
 * there is a hazard when new setup data arrives while the DCD is copying the setup data payload
 * from the QH for a previous setup packet. This bit is set and cleared by software.
 * This bit would also be cleared by hardware when a hazard detected.
 */
#define USB_USBCMD_SUTW_MASK (0x2000U)
#define USB_USBCMD_SUTW_SHIFT (13U)
#define USB_USBCMD_SUTW_SET(x) (((uint32_t)(x) << USB_USBCMD_SUTW_SHIFT) & USB_USBCMD_SUTW_MASK)
#define USB_USBCMD_SUTW_GET(x) (((uint32_t)(x) & USB_USBCMD_SUTW_MASK) >> USB_USBCMD_SUTW_SHIFT)

/*
 * ASPE (RW)
 *
 * ASPE
 * Asynchronous Schedule Park Mode Enable - Read/Write.
 * If the Asynchronous Park Capability bit in the HCCPARAMS register is a one, then this bit defaults to a 1h and is R/W.
 * Otherwise the bit must be a zero and is RO. Software uses this bit to enable or disable Park mode.
 * When this bit is one, Park mode is enabled. When this bit is a zero, Park mode is disabled.
 * NOTE: ASPE bit reset value: '0b' for OTG controller .
 */
#define USB_USBCMD_ASPE_MASK (0x800U)
#define USB_USBCMD_ASPE_SHIFT (11U)
#define USB_USBCMD_ASPE_SET(x) (((uint32_t)(x) << USB_USBCMD_ASPE_SHIFT) & USB_USBCMD_ASPE_MASK)
#define USB_USBCMD_ASPE_GET(x) (((uint32_t)(x) & USB_USBCMD_ASPE_MASK) >> USB_USBCMD_ASPE_SHIFT)

/*
 * ASP (RW)
 *
 * ASP
 * Asynchronous Schedule Park Mode Count - Read/Write.
 * If the Asynchronous Park Capability bit in the HCCPARAMS register is a one, then this field defaults to 3h and is R/W. Otherwise it defaults to zero and is Read-Only.
 * It contains a count of the number of successive transactions the host controller is allowed to
 * execute from a high-speed queue head on the Asynchronous schedule before continuing traversal of the Asynchronous schedule.
 * Valid values are 1h to 3h. Software must not write a zero to this bit when Park Mode Enable is a one as this will result in undefined behavior.
 * This field is set to 3h in all controller core.
 */
#define USB_USBCMD_ASP_MASK (0x300U)
#define USB_USBCMD_ASP_SHIFT (8U)
#define USB_USBCMD_ASP_SET(x) (((uint32_t)(x) << USB_USBCMD_ASP_SHIFT) & USB_USBCMD_ASP_MASK)
#define USB_USBCMD_ASP_GET(x) (((uint32_t)(x) & USB_USBCMD_ASP_MASK) >> USB_USBCMD_ASP_SHIFT)

/*
 * IAA (RW)
 *
 * IAA
 * Interrupt on Async Advance Doorbell - Read/Write.
 * This bit is used as a doorbell by software to tell the host controller to issue an interrupt the next time it advances asynchronous schedule. Software must write a 1 to this bit to ring the doorbell.
 * When the host controller has evicted all appropriate cached schedule states,
 * it sets the Interrupt on Async Advance status bit in the USBSTS register.
 * If the Interrupt on Sync Advance Enable bit in the USBINTR register is one, then the host controller will assert an interrupt at the next interrupt threshold.
 * The host controller sets this bit to zero after it has set the Interrupt on Sync Advance status bit in the USBSTS register to one.
 * Software should not write a one to this bit when the asynchronous  schedule is inactive. Doing so will yield undefined results.
 * This bit is only used in host mode. Writing a one to this bit when device mode is selected will have undefined results.
 */
#define USB_USBCMD_IAA_MASK (0x40U)
#define USB_USBCMD_IAA_SHIFT (6U)
#define USB_USBCMD_IAA_SET(x) (((uint32_t)(x) << USB_USBCMD_IAA_SHIFT) & USB_USBCMD_IAA_MASK)
#define USB_USBCMD_IAA_GET(x) (((uint32_t)(x) & USB_USBCMD_IAA_MASK) >> USB_USBCMD_IAA_SHIFT)

/*
 * ASE (RW)
 *
 * ASE
 * Asynchronous Schedule Enable - Read/Write. Default 0b.
 * This bit controls whether the host controller skips processing the Asynchronous Schedule.
 * Only the host controller uses this bit.
 * Values Meaning
 * 0 - Do not process the Asynchronous Schedule.
 * 1 - Use the ASYNCLISTADDR register to access the Asynchronous Schedule.
 */
#define USB_USBCMD_ASE_MASK (0x20U)
#define USB_USBCMD_ASE_SHIFT (5U)
#define USB_USBCMD_ASE_SET(x) (((uint32_t)(x) << USB_USBCMD_ASE_SHIFT) & USB_USBCMD_ASE_MASK)
#define USB_USBCMD_ASE_GET(x) (((uint32_t)(x) & USB_USBCMD_ASE_MASK) >> USB_USBCMD_ASE_SHIFT)

/*
 * PSE (RW)
 *
 * PSE
 * Periodic Schedule Enable- Read/Write. Default 0b.
 * This bit controls whether the host controller skips processing the Periodic Schedule.
 * Only the host controller uses this bit.
 * Values Meaning
 * 0 - Do not process the Periodic Schedule
 * 1 - Use the PERIODICLISTBASE register to access the Periodic Schedule.
 */
#define USB_USBCMD_PSE_MASK (0x10U)
#define USB_USBCMD_PSE_SHIFT (4U)
#define USB_USBCMD_PSE_SET(x) (((uint32_t)(x) << USB_USBCMD_PSE_SHIFT) & USB_USBCMD_PSE_MASK)
#define USB_USBCMD_PSE_GET(x) (((uint32_t)(x) & USB_USBCMD_PSE_MASK) >> USB_USBCMD_PSE_SHIFT)

/*
 * FS_1 (RW)
 *
 * FS_1
 * See description at bit 15
 */
#define USB_USBCMD_FS_1_MASK (0xCU)
#define USB_USBCMD_FS_1_SHIFT (2U)
#define USB_USBCMD_FS_1_SET(x) (((uint32_t)(x) << USB_USBCMD_FS_1_SHIFT) & USB_USBCMD_FS_1_MASK)
#define USB_USBCMD_FS_1_GET(x) (((uint32_t)(x) & USB_USBCMD_FS_1_MASK) >> USB_USBCMD_FS_1_SHIFT)

/*
 * RST (RW)
 *
 * RST
 * Controller Reset (RESET) - Read/Write. Software uses this bit to reset the controller.
 * This bit is set to zero by the Host/Device Controller when the reset process is complete. Software cannot terminate the reset process early by writing a zero to this register.
 * Host operation mode:
 * When software writes a one to this bit, the Controller resets its internal pipelines, timers, counters, state machines etc. to their initial value.
 * Any transaction currently in progress on USB is immediately terminated. A USB reset is not driven on downstream ports.
 * Software should not set this bit to a one when the HCHalted bit in the USBSTS register is a zero.
 * Attempting to reset an actively running host controller will result in undefined behavior.
 * Device operation mode:
 * When software writes a one to this bit, the Controller resets its internal pipelines, timers, counters, state machines etc. to their initial value.
 * Writing a one to this bit when the device is in the attached state is not recommended, because the effect on an attached host is undefined.
 * In order to ensure that the device is not in an attached state before initiating a device controller reset, all primed endpoints should be flushed and the USBCMD Run/Stop bit should be set to 0.
 */
#define USB_USBCMD_RST_MASK (0x2U)
#define USB_USBCMD_RST_SHIFT (1U)
#define USB_USBCMD_RST_SET(x) (((uint32_t)(x) << USB_USBCMD_RST_SHIFT) & USB_USBCMD_RST_MASK)
#define USB_USBCMD_RST_GET(x) (((uint32_t)(x) & USB_USBCMD_RST_MASK) >> USB_USBCMD_RST_SHIFT)

/*
 * RS (RW)
 *
 * RS
 * Run/Stop (RS) - Read/Write. Default 0b. 1=Run. 0=Stop.
 * Host operation mode:
 * When set to '1b', the Controller proceeds with the execution of the schedule. The Controller continues execution as long as this bit is set to a one.
 * When this bit is set to 0, the Host Controller completes the current transaction on the USB and then halts.
 * The HC Halted bit in the status register indicates when the Controller has finished the transaction and has entered the stopped state.
 * Software should not write a one to this field unless the controller is in the Halted state (that is, HCHalted in the USBSTS register is a one).
 * Device operation mode:
 * Writing a one to this bit will cause the controller to enable a pull-up on D+ and initiate an attach event.
 * This control bit is not directly connected to the pull-up enable, as the pull-up will become disabled upon transitioning into high-speed mode.
 * Software should use this bit to prevent an attach event before the controller has been properly initialized. Writing a 0 to this will cause a detach event.
 */
#define USB_USBCMD_RS_MASK (0x1U)
#define USB_USBCMD_RS_SHIFT (0U)
#define USB_USBCMD_RS_SET(x) (((uint32_t)(x) << USB_USBCMD_RS_SHIFT) & USB_USBCMD_RS_MASK)
#define USB_USBCMD_RS_GET(x) (((uint32_t)(x) & USB_USBCMD_RS_MASK) >> USB_USBCMD_RS_SHIFT)

/* Bitfield definition for register: USBSTS */
/*
 * TI1 (RWC)
 *
 * TI1
 * General Purpose Timer Interrupt 1(GPTINT1)--R/WC.
 * This bit is set when the counter in the GPTIMER1CTRL register transitions to zero, writing a one to this
 * bit will clear it.
 */
#define USB_USBSTS_TI1_MASK (0x2000000UL)
#define USB_USBSTS_TI1_SHIFT (25U)
#define USB_USBSTS_TI1_SET(x) (((uint32_t)(x) << USB_USBSTS_TI1_SHIFT) & USB_USBSTS_TI1_MASK)
#define USB_USBSTS_TI1_GET(x) (((uint32_t)(x) & USB_USBSTS_TI1_MASK) >> USB_USBSTS_TI1_SHIFT)

/*
 * TI0 (RWC)
 *
 * TI0
 * General Purpose Timer Interrupt 0(GPTINT0)--R/WC.
 * This bit is set when the counter in the GPTIMER0CTRL register transitions to zero, writing a one to this
 * bit clears it.
 */
#define USB_USBSTS_TI0_MASK (0x1000000UL)
#define USB_USBSTS_TI0_SHIFT (24U)
#define USB_USBSTS_TI0_SET(x) (((uint32_t)(x) << USB_USBSTS_TI0_SHIFT) & USB_USBSTS_TI0_MASK)
#define USB_USBSTS_TI0_GET(x) (((uint32_t)(x) & USB_USBSTS_TI0_MASK) >> USB_USBSTS_TI0_SHIFT)

/*
 * UPI (RWC)
 *
 * USB Host Periodic Interrupt – RWC. Default = 0b.
 * This bit is set by the Host Controller when the cause of an interrupt is a completion of a USB transaction
 * where the Transfer Descriptor (TD) has an interrupt on complete (IOC) bit set and the TD was from the periodic schedule.
 * This bit is also set by the Host Controller when a short packet is detected and the packet is on the periodic schedule.
 * A short packet is when the actual number of bytes received was less than expected.
 * This bit is not used by the device controller and will always be zero.
 */
#define USB_USBSTS_UPI_MASK (0x80000UL)
#define USB_USBSTS_UPI_SHIFT (19U)
#define USB_USBSTS_UPI_SET(x) (((uint32_t)(x) << USB_USBSTS_UPI_SHIFT) & USB_USBSTS_UPI_MASK)
#define USB_USBSTS_UPI_GET(x) (((uint32_t)(x) & USB_USBSTS_UPI_MASK) >> USB_USBSTS_UPI_SHIFT)

/*
 * UAI (RWC)
 *
 * USB Host Asynchronous Interrupt – RWC. Default = 0b.
 * This bit is set by the Host Controller when the cause of an interrupt is a completion of a USB transaction
 * where the Transfer Descriptor (TD) has an interrupt on complete (IOC) bit set AND the TD was from the asynchronous schedule.
 * This bit is also set by the Host when a short packet is detected and the packet is on the asynchronous schedule.
 * A short packet is when the actual number of bytes received was less than expected.
 * This bit is not used by the device controller and will always be zero
 */
#define USB_USBSTS_UAI_MASK (0x40000UL)
#define USB_USBSTS_UAI_SHIFT (18U)
#define USB_USBSTS_UAI_SET(x) (((uint32_t)(x) << USB_USBSTS_UAI_SHIFT) & USB_USBSTS_UAI_MASK)
#define USB_USBSTS_UAI_GET(x) (((uint32_t)(x) & USB_USBSTS_UAI_MASK) >> USB_USBSTS_UAI_SHIFT)

/*
 * NAKI (RO)
 *
 * NAKI
 * NAK Interrupt Bit--RO.
 * This bit is set by hardware when for a particular endpoint both the TX/RX Endpoint NAK bit and
 * corresponding TX/RX Endpoint NAK Enable bit are set. This bit is automatically cleared by hardware
 * when all Enabled TX/RX Endpoint NAK bits are cleared.
 */
#define USB_USBSTS_NAKI_MASK (0x10000UL)
#define USB_USBSTS_NAKI_SHIFT (16U)
#define USB_USBSTS_NAKI_GET(x) (((uint32_t)(x) & USB_USBSTS_NAKI_MASK) >> USB_USBSTS_NAKI_SHIFT)

/*
 * AS (RO)
 *
 * AS
 * Asynchronous Schedule Status - Read Only.
 * This bit reports the current real status of the Asynchronous Schedule. When set to zero the asynchronous schedule status is disabled and if set to one the status is enabled.
 * The Host Controller is not required to immediately disable or enable the Asynchronous Schedule when software transitions the Asynchronous Schedule Enable bit in the USBCMD register.
 * When this bit and the Asynchronous Schedule Enable bit are the same value, the Asynchronous Schedule is either enabled (1) or disabled (0).
 * Only used in the host operation mode.
 */
#define USB_USBSTS_AS_MASK (0x8000U)
#define USB_USBSTS_AS_SHIFT (15U)
#define USB_USBSTS_AS_GET(x) (((uint32_t)(x) & USB_USBSTS_AS_MASK) >> USB_USBSTS_AS_SHIFT)

/*
 * PS (RO)
 *
 * PS
 * Periodic Schedule Status - Read Only.
 * This bit reports the current real status of the Periodic Schedule. When set to zero the periodic schedule is disabled, and if set to one the status is enabled.
 * The Host Controller is not required to immediately disable or enable the Periodic Schedule when software transitions the Periodic Schedule Enable bit in the USBCMD register.
 * When this bit and the Periodic Schedule Enable bit are the same value, the Periodic Schedule is either enabled (1) or disabled (0).
 * Only used in the host operation mode.
 */
#define USB_USBSTS_PS_MASK (0x4000U)
#define USB_USBSTS_PS_SHIFT (14U)
#define USB_USBSTS_PS_GET(x) (((uint32_t)(x) & USB_USBSTS_PS_MASK) >> USB_USBSTS_PS_SHIFT)

/*
 * RCL (RO)
 *
 * RCL
 * Reclamation - Read Only.
 * This is a read-only status bit used to detect an empty asynchronous schedule.
 * Only used in the host operation mode.
 */
#define USB_USBSTS_RCL_MASK (0x2000U)
#define USB_USBSTS_RCL_SHIFT (13U)
#define USB_USBSTS_RCL_GET(x) (((uint32_t)(x) & USB_USBSTS_RCL_MASK) >> USB_USBSTS_RCL_SHIFT)

/*
 * HCH (RO)
 *
 * HCH
 * HCHaIted - Read Only.
 * This bit is a zero whenever the Run/Stop bit is a one.
 *  The Controller sets this bit to one after it has stopped executing because of the Run/Stop bit being set to 0,
 *  either by software or by the Controller hardware (for example, an internal error).
 * Only used in the host operation mode.
 * Default value is '0b' for OTG core .
 * This is because OTG core is not operating as host in default. Please see CM bit in USB_n_USBMODE
 * register.
 * NOTE: HCH bit reset value: '0b' for OTG controller core .
 */
#define USB_USBSTS_HCH_MASK (0x1000U)
#define USB_USBSTS_HCH_SHIFT (12U)
#define USB_USBSTS_HCH_GET(x) (((uint32_t)(x) & USB_USBSTS_HCH_MASK) >> USB_USBSTS_HCH_SHIFT)

/*
 * SLI (RWC)
 *
 * SLI
 * DCSuspend - R/WC.
 * When a controller enters a suspend state from an active state, this bit will be set to a one. The device controller clears the bit upon exiting from a suspend state.
 * Only used in device operation mode.
 */
#define USB_USBSTS_SLI_MASK (0x100U)
#define USB_USBSTS_SLI_SHIFT (8U)
#define USB_USBSTS_SLI_SET(x) (((uint32_t)(x) << USB_USBSTS_SLI_SHIFT) & USB_USBSTS_SLI_MASK)
#define USB_USBSTS_SLI_GET(x) (((uint32_t)(x) & USB_USBSTS_SLI_MASK) >> USB_USBSTS_SLI_SHIFT)

/*
 * SRI (RWC)
 *
 * SRI
 * SOF Received - R/WC.
 * When the device controller detects a Start Of (micro) Frame, this bit will be set to a one.
 * When a SOF is extremely late, the device controller will automatically set this bit to indicate that an SOF was expected.
 * Therefore, this bit will be set roughly every 1ms in device FS mode and every 125ms in HS mode and will be synchronized to the actual SOF that is received.
 * Because the device controller is initialized to FS before connect, this bit will be set at an interval of 1ms during the prelude to connect and chirp.
 * In host mode, this bit will be set every 125us and can be used by host controller driver as a time base.
 * Software writes a 1 to this bit to clear it.
 */
#define USB_USBSTS_SRI_MASK (0x80U)
#define USB_USBSTS_SRI_SHIFT (7U)
#define USB_USBSTS_SRI_SET(x) (((uint32_t)(x) << USB_USBSTS_SRI_SHIFT) & USB_USBSTS_SRI_MASK)
#define USB_USBSTS_SRI_GET(x) (((uint32_t)(x) & USB_USBSTS_SRI_MASK) >> USB_USBSTS_SRI_SHIFT)

/*
 * URI (RWC)
 *
 * URI
 * USB Reset Received - R/WC.
 * When the device controller detects a USB Reset and enters the default state, this bit will be set to a one.
 * Software can write a 1 to this bit to clear the USB Reset Received status bit.
 * Only used in device operation mode.
 */
#define USB_USBSTS_URI_MASK (0x40U)
#define USB_USBSTS_URI_SHIFT (6U)
#define USB_USBSTS_URI_SET(x) (((uint32_t)(x) << USB_USBSTS_URI_SHIFT) & USB_USBSTS_URI_MASK)
#define USB_USBSTS_URI_GET(x) (((uint32_t)(x) & USB_USBSTS_URI_MASK) >> USB_USBSTS_URI_SHIFT)

/*
 * AAI (RWC)
 *
 * AAI
 * Interrupt on Async Advance - R/WC.
 * System software can force the host controller to issue an interrupt the next time the host controller advances the asynchronous schedule
 * by writing a one to the Interrupt on Async Advance Doorbell bit in the n_USBCMD register. This status bit indicates the assertion of that interrupt source.
 * Only used in host operation mode.
 */
#define USB_USBSTS_AAI_MASK (0x20U)
#define USB_USBSTS_AAI_SHIFT (5U)
#define USB_USBSTS_AAI_SET(x) (((uint32_t)(x) << USB_USBSTS_AAI_SHIFT) & USB_USBSTS_AAI_MASK)
#define USB_USBSTS_AAI_GET(x) (((uint32_t)(x) & USB_USBSTS_AAI_MASK) >> USB_USBSTS_AAI_SHIFT)

/*
 * SEI (RWC)
 *
 * System Error – RWC. Default = 0b.
 * In the BVCI implementation of the USBHS core, this bit is not used, and will always be cleared to '0b'.
 * In the AMBA implementation, this bit will be set to '1b' when an Error response is seen by the master interface (HRESP[1:0]=ERROR)
 */
#define USB_USBSTS_SEI_MASK (0x10U)
#define USB_USBSTS_SEI_SHIFT (4U)
#define USB_USBSTS_SEI_SET(x) (((uint32_t)(x) << USB_USBSTS_SEI_SHIFT) & USB_USBSTS_SEI_MASK)
#define USB_USBSTS_SEI_GET(x) (((uint32_t)(x) & USB_USBSTS_SEI_MASK) >> USB_USBSTS_SEI_SHIFT)

/*
 * FRI (RWC)
 *
 * FRI
 * Frame List Rollover - R/WC.
 * The Host Controller sets this bit to a one when the Frame List Index rolls over from its maximum value to
 * zero. The exact value at which the rollover occurs depends on the frame list size. For example. If the
 * frame list size (as programmed in the Frame List Size field of the USB_n_USBCMD register) is 1024, the
 * Frame Index Register rolls over every time FRINDEX [13] toggles. Similarly, if the size is 512, the Host
 * Controller sets this bit to a one every time FHINDEX [12] toggles.
 * Only used in host operation mode.
 */
#define USB_USBSTS_FRI_MASK (0x8U)
#define USB_USBSTS_FRI_SHIFT (3U)
#define USB_USBSTS_FRI_SET(x) (((uint32_t)(x) << USB_USBSTS_FRI_SHIFT) & USB_USBSTS_FRI_MASK)
#define USB_USBSTS_FRI_GET(x) (((uint32_t)(x) & USB_USBSTS_FRI_MASK) >> USB_USBSTS_FRI_SHIFT)

/*
 * PCI (RWC)
 *
 * PCI
 * Port Change Detect - R/WC.
 * The Host Controller sets this bit to a one when on any port a Connect Status occurs, a Port Enable/Disable Change occurs,
 * or the Force Port Resume bit is set as the result of a J-K transition on the suspended port.
 * The Device Controller sets this bit to a one when the port controller enters the full or high-speed operational state.
 * When the port controller exits the full or high-speed operation states due to Reset or Suspend events,
 * the notification mechanisms are the USB Reset Received bit and the DCSuspend bits Respectively.
 */
#define USB_USBSTS_PCI_MASK (0x4U)
#define USB_USBSTS_PCI_SHIFT (2U)
#define USB_USBSTS_PCI_SET(x) (((uint32_t)(x) << USB_USBSTS_PCI_SHIFT) & USB_USBSTS_PCI_MASK)
#define USB_USBSTS_PCI_GET(x) (((uint32_t)(x) & USB_USBSTS_PCI_MASK) >> USB_USBSTS_PCI_SHIFT)

/*
 * UEI (RWC)
 *
 * UEI
 * USB Error Interrupt (USBERRINT) - R/WC.
 * When completion of a USB transaction results in an error condition, this bit is set by the Host/Device Controller.
 * This bit is set along with the USBINT bit, if the TD on which the error interrupt occurred also had its interrupt on complete (IOC) bit set.
 */
#define USB_USBSTS_UEI_MASK (0x2U)
#define USB_USBSTS_UEI_SHIFT (1U)
#define USB_USBSTS_UEI_SET(x) (((uint32_t)(x) << USB_USBSTS_UEI_SHIFT) & USB_USBSTS_UEI_MASK)
#define USB_USBSTS_UEI_GET(x) (((uint32_t)(x) & USB_USBSTS_UEI_MASK) >> USB_USBSTS_UEI_SHIFT)

/*
 * UI (RWC)
 *
 * UI
 * USB Interrupt (USBINT) - R/WC.
 * This bit is set by the Host/Device Controller when the cause of an interrupt is a completion of a USB
 * transaction where the Transfer Descriptor (TD) has an interrupt on complete (IOC) bit set.
 * This bit is also set by the Host/Device Controller when a short packet is detected. A short packet is when
 * the actual number of bytes received was less than the expected number of bytes.
 */
#define USB_USBSTS_UI_MASK (0x1U)
#define USB_USBSTS_UI_SHIFT (0U)
#define USB_USBSTS_UI_SET(x) (((uint32_t)(x) << USB_USBSTS_UI_SHIFT) & USB_USBSTS_UI_MASK)
#define USB_USBSTS_UI_GET(x) (((uint32_t)(x) & USB_USBSTS_UI_MASK) >> USB_USBSTS_UI_SHIFT)

/* Bitfield definition for register: USBINTR */
/*
 * TIE1 (RW)
 *
 * TIE1
 * General Purpose Timer #1 Interrupt Enable
 * When this bit is one and the TI1 bit in n_USBSTS register is a one the controller will issue an interrupt.
 */
#define USB_USBINTR_TIE1_MASK (0x2000000UL)
#define USB_USBINTR_TIE1_SHIFT (25U)
#define USB_USBINTR_TIE1_SET(x) (((uint32_t)(x) << USB_USBINTR_TIE1_SHIFT) & USB_USBINTR_TIE1_MASK)
#define USB_USBINTR_TIE1_GET(x) (((uint32_t)(x) & USB_USBINTR_TIE1_MASK) >> USB_USBINTR_TIE1_SHIFT)

/*
 * TIE0 (RW)
 *
 * TIE0
 * General Purpose Timer #0 Interrupt Enable
 * When this bit is one and the TI0 bit in n_USBSTS register is a one the controller will issue an interrupt.
 */
#define USB_USBINTR_TIE0_MASK (0x1000000UL)
#define USB_USBINTR_TIE0_SHIFT (24U)
#define USB_USBINTR_TIE0_SET(x) (((uint32_t)(x) << USB_USBINTR_TIE0_SHIFT) & USB_USBINTR_TIE0_MASK)
#define USB_USBINTR_TIE0_GET(x) (((uint32_t)(x) & USB_USBINTR_TIE0_MASK) >> USB_USBINTR_TIE0_SHIFT)

/*
 * UPIE (RW)
 *
 * UPIE
 * USB Host Periodic Interrupt Enable
 * When this bit is one, and the UPI bit in the n_USBSTS register is one, host controller will issue an
 * interrupt at the next interrupt threshold.
 */
#define USB_USBINTR_UPIE_MASK (0x80000UL)
#define USB_USBINTR_UPIE_SHIFT (19U)
#define USB_USBINTR_UPIE_SET(x) (((uint32_t)(x) << USB_USBINTR_UPIE_SHIFT) & USB_USBINTR_UPIE_MASK)
#define USB_USBINTR_UPIE_GET(x) (((uint32_t)(x) & USB_USBINTR_UPIE_MASK) >> USB_USBINTR_UPIE_SHIFT)

/*
 * UAIE (RW)
 *
 * UAIE
 * USB Host Asynchronous Interrupt Enable
 * When this bit is one, and the UAI bit in the n_USBSTS register is one, host controller will issue an
 * interrupt at the next interrupt threshold.
 */
#define USB_USBINTR_UAIE_MASK (0x40000UL)
#define USB_USBINTR_UAIE_SHIFT (18U)
#define USB_USBINTR_UAIE_SET(x) (((uint32_t)(x) << USB_USBINTR_UAIE_SHIFT) & USB_USBINTR_UAIE_MASK)
#define USB_USBINTR_UAIE_GET(x) (((uint32_t)(x) & USB_USBINTR_UAIE_MASK) >> USB_USBINTR_UAIE_SHIFT)

/*
 * NAKE (RO)
 *
 * NAKE
 * NAK Interrupt Enable
 * When this bit is one and the NAKI bit in n_USBSTS register is a one the controller will issue an interrupt.
 */
#define USB_USBINTR_NAKE_MASK (0x10000UL)
#define USB_USBINTR_NAKE_SHIFT (16U)
#define USB_USBINTR_NAKE_GET(x) (((uint32_t)(x) & USB_USBINTR_NAKE_MASK) >> USB_USBINTR_NAKE_SHIFT)

/*
 * SLE (RW)
 *
 * SLE
 * Sleep Interrupt Enable
 * When this bit is one and the SLI bit in n_n_USBSTS register is a one the controller will issue an interrupt.
 * Only used in device operation mode.
 */
#define USB_USBINTR_SLE_MASK (0x100U)
#define USB_USBINTR_SLE_SHIFT (8U)
#define USB_USBINTR_SLE_SET(x) (((uint32_t)(x) << USB_USBINTR_SLE_SHIFT) & USB_USBINTR_SLE_MASK)
#define USB_USBINTR_SLE_GET(x) (((uint32_t)(x) & USB_USBINTR_SLE_MASK) >> USB_USBINTR_SLE_SHIFT)

/*
 * SRE (RW)
 *
 * SRE
 * SOF Received Interrupt Enable
 * When this bit is one and the SRI bit in n_USBSTS register is a one the controller will issue an interrupt.
 */
#define USB_USBINTR_SRE_MASK (0x80U)
#define USB_USBINTR_SRE_SHIFT (7U)
#define USB_USBINTR_SRE_SET(x) (((uint32_t)(x) << USB_USBINTR_SRE_SHIFT) & USB_USBINTR_SRE_MASK)
#define USB_USBINTR_SRE_GET(x) (((uint32_t)(x) & USB_USBINTR_SRE_MASK) >> USB_USBINTR_SRE_SHIFT)

/*
 * URE (RW)
 *
 * URE
 * USB Reset Interrupt Enable
 * When this bit is one and the URI bit in n_USBSTS register is a one the controller will issue an interrupt.
 * Only used in device operation mode.
 */
#define USB_USBINTR_URE_MASK (0x40U)
#define USB_USBINTR_URE_SHIFT (6U)
#define USB_USBINTR_URE_SET(x) (((uint32_t)(x) << USB_USBINTR_URE_SHIFT) & USB_USBINTR_URE_MASK)
#define USB_USBINTR_URE_GET(x) (((uint32_t)(x) & USB_USBINTR_URE_MASK) >> USB_USBINTR_URE_SHIFT)

/*
 * AAE (RW)
 *
 * AAE
 * Async Advance Interrupt Enable
 * When this bit is one and the AAI bit in n_USBSTS register is a one the controller will issue an interrupt.
 * Only used in host operation mode.
 */
#define USB_USBINTR_AAE_MASK (0x20U)
#define USB_USBINTR_AAE_SHIFT (5U)
#define USB_USBINTR_AAE_SET(x) (((uint32_t)(x) << USB_USBINTR_AAE_SHIFT) & USB_USBINTR_AAE_MASK)
#define USB_USBINTR_AAE_GET(x) (((uint32_t)(x) & USB_USBINTR_AAE_MASK) >> USB_USBINTR_AAE_SHIFT)

/*
 * SEE (RW)
 *
 * SEE
 * System Error Interrupt Enable
 * When this bit is one and the SEI bit in n_USBSTS register is a one the controller will issue an interrupt.
 * Only used in host operation mode.
 */
#define USB_USBINTR_SEE_MASK (0x10U)
#define USB_USBINTR_SEE_SHIFT (4U)
#define USB_USBINTR_SEE_SET(x) (((uint32_t)(x) << USB_USBINTR_SEE_SHIFT) & USB_USBINTR_SEE_MASK)
#define USB_USBINTR_SEE_GET(x) (((uint32_t)(x) & USB_USBINTR_SEE_MASK) >> USB_USBINTR_SEE_SHIFT)

/*
 * FRE (RW)
 *
 * FRE
 * Frame List Rollover Interrupt Enable
 * When this bit is one and the FRI bit in n_USBSTS register is a one the controller will issue an interrupt.
 * Only used in host operation mode.
 */
#define USB_USBINTR_FRE_MASK (0x8U)
#define USB_USBINTR_FRE_SHIFT (3U)
#define USB_USBINTR_FRE_SET(x) (((uint32_t)(x) << USB_USBINTR_FRE_SHIFT) & USB_USBINTR_FRE_MASK)
#define USB_USBINTR_FRE_GET(x) (((uint32_t)(x) & USB_USBINTR_FRE_MASK) >> USB_USBINTR_FRE_SHIFT)

/*
 * PCE (RW)
 *
 * PCE
 * Port Change Detect Interrupt Enable
 * When this bit is one and the PCI bit in n_USBSTS register is a one the controller will issue an interrupt.
 */
#define USB_USBINTR_PCE_MASK (0x4U)
#define USB_USBINTR_PCE_SHIFT (2U)
#define USB_USBINTR_PCE_SET(x) (((uint32_t)(x) << USB_USBINTR_PCE_SHIFT) & USB_USBINTR_PCE_MASK)
#define USB_USBINTR_PCE_GET(x) (((uint32_t)(x) & USB_USBINTR_PCE_MASK) >> USB_USBINTR_PCE_SHIFT)

/*
 * UEE (RWC)
 *
 * UEE
 * USB Error Interrupt Enable
 * When this bit is one and the UEI bit in n_USBSTS register is a one the controller will issue an interrupt.
 */
#define USB_USBINTR_UEE_MASK (0x2U)
#define USB_USBINTR_UEE_SHIFT (1U)
#define USB_USBINTR_UEE_SET(x) (((uint32_t)(x) << USB_USBINTR_UEE_SHIFT) & USB_USBINTR_UEE_MASK)
#define USB_USBINTR_UEE_GET(x) (((uint32_t)(x) & USB_USBINTR_UEE_MASK) >> USB_USBINTR_UEE_SHIFT)

/*
 * UE (RW)
 *
 * UE
 * USB Interrupt Enable
 * When this bit is one and the UI bit in n_USBSTS register is a one the controller will issue an interrupt.
 */
#define USB_USBINTR_UE_MASK (0x1U)
#define USB_USBINTR_UE_SHIFT (0U)
#define USB_USBINTR_UE_SET(x) (((uint32_t)(x) << USB_USBINTR_UE_SHIFT) & USB_USBINTR_UE_MASK)
#define USB_USBINTR_UE_GET(x) (((uint32_t)(x) & USB_USBINTR_UE_MASK) >> USB_USBINTR_UE_SHIFT)

/* Bitfield definition for register: FRINDEX */
/*
 * FRINDEX (RW)
 *
 * FRINDEX
 * Frame Index.
 * The value, in this register, increments at the end of each time frame (micro-frame). Bits [N: 3] are used for the Frame List current index.
 * This means that each location of the frame list is accessed 8 times (frames or micro-frames) before moving to the next index.
 * The following illustrates values of N based on the value of the Frame List Size field in the USBCMD register, when used in host mode.
 * USBCMD [Frame List Size] Number Elements N
 * In device mode the value is the current frame number of the last frame transmitted. It is not used as an index.
 * In either mode bits 2:0 indicate the current microframe.
 * The bit field values description below is represented as (Frame List Size) Number Elements N.
 * 00000000000000 - (1024) 12
 * 00000000000001 - (512) 11
 * 00000000000010 - (256) 10
 * 00000000000011 - (128) 9
 * 00000000000100 - (64) 8
 * 00000000000101 - (32) 7
 * 00000000000110 - (16) 6
 * 00000000000111 - (8) 5
 */
#define USB_FRINDEX_FRINDEX_MASK (0x3FFFU)
#define USB_FRINDEX_FRINDEX_SHIFT (0U)
#define USB_FRINDEX_FRINDEX_SET(x) (((uint32_t)(x) << USB_FRINDEX_FRINDEX_SHIFT) & USB_FRINDEX_FRINDEX_MASK)
#define USB_FRINDEX_FRINDEX_GET(x) (((uint32_t)(x) & USB_FRINDEX_FRINDEX_MASK) >> USB_FRINDEX_FRINDEX_SHIFT)

/* Bitfield definition for register: DEVICEADDR */
/*
 * USBADR (RW)
 *
 * USBADR
 * Device Address.
 * These bits correspond to the USB device address
 */
#define USB_DEVICEADDR_USBADR_MASK (0xFE000000UL)
#define USB_DEVICEADDR_USBADR_SHIFT (25U)
#define USB_DEVICEADDR_USBADR_SET(x) (((uint32_t)(x) << USB_DEVICEADDR_USBADR_SHIFT) & USB_DEVICEADDR_USBADR_MASK)
#define USB_DEVICEADDR_USBADR_GET(x) (((uint32_t)(x) & USB_DEVICEADDR_USBADR_MASK) >> USB_DEVICEADDR_USBADR_SHIFT)

/*
 * USBADRA (RW)
 *
 * USBADRA
 * Device Address Advance. Default=0.
 * When this bit is '0', any writes to USBADR are instantaneous.
 *  When this bit is written to a '1' at the same time or before USBADR is written, the write to the USBADR field is staged and held in a hidden register.
 * After an IN occurs on endpoint 0 and is ACKed, USBADR will be loaded from the holding register.
 * Hardware will automatically clear this bit on the following conditions:
 * 1) IN is ACKed to endpoint 0. (USBADR is updated from staging register).
 * 2) OUT/SETUP occur to endpoint 0. (USBADR is not updated).
 * 3) Device Reset occurs (USBADR is reset to 0).
 * NOTE: After the status phase of the SET_ADDRESS descriptor, the DCD has 2 ms to program the USBADR field.
 * This mechanism will ensure this specification is met when the DCD can not write of the device address within 2ms from the SET_ADDRESS status phase.
 * If the DCD writes the USBADR with USBADRA=1 after the SET_ADDRESS data phase (before the prime of the status phase),
 * the USBADR will be programmed instantly at the correct time and meet the 2ms USB requirement.
 */
#define USB_DEVICEADDR_USBADRA_MASK (0x1000000UL)
#define USB_DEVICEADDR_USBADRA_SHIFT (24U)
#define USB_DEVICEADDR_USBADRA_SET(x) (((uint32_t)(x) << USB_DEVICEADDR_USBADRA_SHIFT) & USB_DEVICEADDR_USBADRA_MASK)
#define USB_DEVICEADDR_USBADRA_GET(x) (((uint32_t)(x) & USB_DEVICEADDR_USBADRA_MASK) >> USB_DEVICEADDR_USBADRA_SHIFT)

/* Bitfield definition for register: PERIODICLISTBASE */
/*
 * BASEADR (RW)
 *
 * BASEADR
 * Base Address (Low).
 * These bits correspond to memory address signals [31:12], respectively.
 * Only used by the host controller.
 */
#define USB_PERIODICLISTBASE_BASEADR_MASK (0xFFFFF000UL)
#define USB_PERIODICLISTBASE_BASEADR_SHIFT (12U)
#define USB_PERIODICLISTBASE_BASEADR_SET(x) (((uint32_t)(x) << USB_PERIODICLISTBASE_BASEADR_SHIFT) & USB_PERIODICLISTBASE_BASEADR_MASK)
#define USB_PERIODICLISTBASE_BASEADR_GET(x) (((uint32_t)(x) & USB_PERIODICLISTBASE_BASEADR_MASK) >> USB_PERIODICLISTBASE_BASEADR_SHIFT)

/* Bitfield definition for register: ASYNCLISTADDR */
/*
 * ASYBASE (RW)
 *
 * ASYBASE
 * Link Pointer Low (LPL).
 * These bits correspond to memory address signals [31:5], respectively. This field may only reference a
 * Queue Head (QH).
 * Only used by the host controller.
 */
#define USB_ASYNCLISTADDR_ASYBASE_MASK (0xFFFFFFE0UL)
#define USB_ASYNCLISTADDR_ASYBASE_SHIFT (5U)
#define USB_ASYNCLISTADDR_ASYBASE_SET(x) (((uint32_t)(x) << USB_ASYNCLISTADDR_ASYBASE_SHIFT) & USB_ASYNCLISTADDR_ASYBASE_MASK)
#define USB_ASYNCLISTADDR_ASYBASE_GET(x) (((uint32_t)(x) & USB_ASYNCLISTADDR_ASYBASE_MASK) >> USB_ASYNCLISTADDR_ASYBASE_SHIFT)

/* Bitfield definition for register: ENDPTLISTADDR */
/*
 * EPBASE (RW)
 *
 * EPBASE
 * Endpoint List Pointer(Low). These bits correspond to memory address signals [31:11], respectively.
 * This field will reference a list of up to 32 Queue Head (QH) (that is, one queue head per endpoint & direction).
 */
#define USB_ENDPTLISTADDR_EPBASE_MASK (0xFFFFF800UL)
#define USB_ENDPTLISTADDR_EPBASE_SHIFT (11U)
#define USB_ENDPTLISTADDR_EPBASE_SET(x) (((uint32_t)(x) << USB_ENDPTLISTADDR_EPBASE_SHIFT) & USB_ENDPTLISTADDR_EPBASE_MASK)
#define USB_ENDPTLISTADDR_EPBASE_GET(x) (((uint32_t)(x) & USB_ENDPTLISTADDR_EPBASE_MASK) >> USB_ENDPTLISTADDR_EPBASE_SHIFT)

/* Bitfield definition for register: BURSTSIZE */
/*
 * TXPBURST (RW)
 *
 * TXPBURST
 * Programmable TX Burst Size.
 * Default value is determined by TXBURST bits in n_HWTXBUF.
 * This register represents the maximum length of a the burst in 32-bit words while moving data from system
 * memory to the USB bus.
 */
#define USB_BURSTSIZE_TXPBURST_MASK (0xFF00U)
#define USB_BURSTSIZE_TXPBURST_SHIFT (8U)
#define USB_BURSTSIZE_TXPBURST_SET(x) (((uint32_t)(x) << USB_BURSTSIZE_TXPBURST_SHIFT) & USB_BURSTSIZE_TXPBURST_MASK)
#define USB_BURSTSIZE_TXPBURST_GET(x) (((uint32_t)(x) & USB_BURSTSIZE_TXPBURST_MASK) >> USB_BURSTSIZE_TXPBURST_SHIFT)

/*
 * RXPBURST (RW)
 *
 * RXPBURST
 * Programmable RX Burst Size.
 * Default value is determined by TXBURST bits in n_HWRXBUF.
 * This register represents the maximum length of a the burst in 32-bit words while moving data from the
 * USB bus to system memory.
 */
#define USB_BURSTSIZE_RXPBURST_MASK (0xFFU)
#define USB_BURSTSIZE_RXPBURST_SHIFT (0U)
#define USB_BURSTSIZE_RXPBURST_SET(x) (((uint32_t)(x) << USB_BURSTSIZE_RXPBURST_SHIFT) & USB_BURSTSIZE_RXPBURST_MASK)
#define USB_BURSTSIZE_RXPBURST_GET(x) (((uint32_t)(x) & USB_BURSTSIZE_RXPBURST_MASK) >> USB_BURSTSIZE_RXPBURST_SHIFT)

/* Bitfield definition for register: TXFILLTUNING */
/*
 * TXFIFOTHRES (RW)
 *
 * TXFIFOTHRES
 * FIFO Burst Threshold. (Read/Write)
 * This register controls the number of data bursts that are posted to the TX latency FIFO in host mode before the packet begins on to the bus.
 * The minimum value is 2 and this value should be a low as possible to maximize USB performance.
 * A higher value can be used in systems with unpredictable latency and/or insufficient bandwidth
 * where the FIFO may underrun because the data transferred from the latency FIFO to USB occurs before it can be replenished from system memory.
 * This value is ignored if the Stream Disable bit in USB_n_USBMODE register is set.
 */
#define USB_TXFILLTUNING_TXFIFOTHRES_MASK (0x3F0000UL)
#define USB_TXFILLTUNING_TXFIFOTHRES_SHIFT (16U)
#define USB_TXFILLTUNING_TXFIFOTHRES_SET(x) (((uint32_t)(x) << USB_TXFILLTUNING_TXFIFOTHRES_SHIFT) & USB_TXFILLTUNING_TXFIFOTHRES_MASK)
#define USB_TXFILLTUNING_TXFIFOTHRES_GET(x) (((uint32_t)(x) & USB_TXFILLTUNING_TXFIFOTHRES_MASK) >> USB_TXFILLTUNING_TXFIFOTHRES_SHIFT)

/*
 * TXSCHHEALTH (RWC)
 *
 * TXSCHHEALTH
 * Scheduler Health Counter. (Read/Write To Clear)
 * Table continues on the next page
 * This register increments when the host controller fails to fill the TX latency FIFO to the level programmed by TXFIFOTHRES
 * before running out of time to send the packet before the next Start-Of-Frame.
 * This health counter measures the number of times this occurs to provide feedback to selecting a proper TXSCHOH.
 * Writing to this register will clear the counter and this counter will max. at 31.
 */
#define USB_TXFILLTUNING_TXSCHHEALTH_MASK (0x1F00U)
#define USB_TXFILLTUNING_TXSCHHEALTH_SHIFT (8U)
#define USB_TXFILLTUNING_TXSCHHEALTH_SET(x) (((uint32_t)(x) << USB_TXFILLTUNING_TXSCHHEALTH_SHIFT) & USB_TXFILLTUNING_TXSCHHEALTH_MASK)
#define USB_TXFILLTUNING_TXSCHHEALTH_GET(x) (((uint32_t)(x) & USB_TXFILLTUNING_TXSCHHEALTH_MASK) >> USB_TXFILLTUNING_TXSCHHEALTH_SHIFT)

/*
 * TXSCHOH (RW)
 *
 * TXSCHOH
 * Scheduler Overhead. (Read/Write) [Default = 0]
 * This register adds an additional fixed offset to the schedule time estimator described above as Tff.
 * As an approximation, the value chosen for this register should limit the number of back-off events captured
 * in the TXSCHHEALTH to less than 10 per second in a highly utilized bus.
 * Choosing a value that is too high for this register is not desired as it can needlessly reduce USB utilization.
 * The time unit represented in this register is 1.267us when a device is connected in High-Speed Mode.
 * The time unit represented in this register is 6.333us when a device is connected in Low/Full Speed Mode.
 * Default value is '08h' for OTG controller core .
 */
#define USB_TXFILLTUNING_TXSCHOH_MASK (0x7FU)
#define USB_TXFILLTUNING_TXSCHOH_SHIFT (0U)
#define USB_TXFILLTUNING_TXSCHOH_SET(x) (((uint32_t)(x) << USB_TXFILLTUNING_TXSCHOH_SHIFT) & USB_TXFILLTUNING_TXSCHOH_MASK)
#define USB_TXFILLTUNING_TXSCHOH_GET(x) (((uint32_t)(x) & USB_TXFILLTUNING_TXSCHOH_MASK) >> USB_TXFILLTUNING_TXSCHOH_SHIFT)

/* Bitfield definition for register: ENDPTNAK */
/*
 * EPTN (RWC)
 *
 * EPTN
 * TX Endpoint NAK - R/WC.
 * Each TX endpoint has 1 bit in this field. The bit is set when the
 * device sends a NAK handshake on a received IN token for the corresponding endpoint.
 * Bit [N] - Endpoint #[N], N is 0-7
 */
#define USB_ENDPTNAK_EPTN_MASK (0xFFFF0000UL)
#define USB_ENDPTNAK_EPTN_SHIFT (16U)
#define USB_ENDPTNAK_EPTN_SET(x) (((uint32_t)(x) << USB_ENDPTNAK_EPTN_SHIFT) & USB_ENDPTNAK_EPTN_MASK)
#define USB_ENDPTNAK_EPTN_GET(x) (((uint32_t)(x) & USB_ENDPTNAK_EPTN_MASK) >> USB_ENDPTNAK_EPTN_SHIFT)

/*
 * EPRN (RWC)
 *
 * EPRN
 * RX Endpoint NAK - R/WC.
 * Each RX endpoint has 1 bit in this field. The bit is set when the
 * device sends a NAK handshake on a received OUT or PING token for the corresponding endpoint.
 * Bit [N] - Endpoint #[N], N is 0-7
 */
#define USB_ENDPTNAK_EPRN_MASK (0xFFFFU)
#define USB_ENDPTNAK_EPRN_SHIFT (0U)
#define USB_ENDPTNAK_EPRN_SET(x) (((uint32_t)(x) << USB_ENDPTNAK_EPRN_SHIFT) & USB_ENDPTNAK_EPRN_MASK)
#define USB_ENDPTNAK_EPRN_GET(x) (((uint32_t)(x) & USB_ENDPTNAK_EPRN_MASK) >> USB_ENDPTNAK_EPRN_SHIFT)

/* Bitfield definition for register: ENDPTNAKEN */
/*
 * EPTNE (RW)
 *
 * EPTNE
 * TX Endpoint NAK Enable - R/W.
 * Each bit is an enable bit for the corresponding TX Endpoint NAK bit. If this bit is set and the
 * corresponding TX Endpoint NAK bit is set, the NAK Interrupt bit is set.
 * Bit [N] - Endpoint #[N], N is 0-7
 */
#define USB_ENDPTNAKEN_EPTNE_MASK (0xFFFF0000UL)
#define USB_ENDPTNAKEN_EPTNE_SHIFT (16U)
#define USB_ENDPTNAKEN_EPTNE_SET(x) (((uint32_t)(x) << USB_ENDPTNAKEN_EPTNE_SHIFT) & USB_ENDPTNAKEN_EPTNE_MASK)
#define USB_ENDPTNAKEN_EPTNE_GET(x) (((uint32_t)(x) & USB_ENDPTNAKEN_EPTNE_MASK) >> USB_ENDPTNAKEN_EPTNE_SHIFT)

/*
 * EPRNE (RW)
 *
 * EPRNE
 * RX Endpoint NAK Enable - R/W.
 * Each bit is an enable bit for the corresponding RX Endpoint NAK bit. If this bit is set and the
 * corresponding RX Endpoint NAK bit is set, the NAK Interrupt bit is set.
 * Bit [N] - Endpoint #[N], N is 0-7
 */
#define USB_ENDPTNAKEN_EPRNE_MASK (0xFFFFU)
#define USB_ENDPTNAKEN_EPRNE_SHIFT (0U)
#define USB_ENDPTNAKEN_EPRNE_SET(x) (((uint32_t)(x) << USB_ENDPTNAKEN_EPRNE_SHIFT) & USB_ENDPTNAKEN_EPRNE_MASK)
#define USB_ENDPTNAKEN_EPRNE_GET(x) (((uint32_t)(x) & USB_ENDPTNAKEN_EPRNE_MASK) >> USB_ENDPTNAKEN_EPRNE_SHIFT)

/* Bitfield definition for register: PORTSC1 */
/*
 * STS (RW)
 *
 * STS
 * Serial Transceiver Select
 * 1 Serial Interface Engine is selected
 * 0 Parallel Interface signals is selected
 * Serial Interface Engine can be used in combination with UTMI+/ULPI physical interface to provide FS/LS signaling instead of the parallel interface signals.
 * When this bit is set '1b', serial interface engine will be used instead of parallel interface signals.
 */
#define USB_PORTSC1_STS_MASK (0x20000000UL)
#define USB_PORTSC1_STS_SHIFT (29U)
#define USB_PORTSC1_STS_SET(x) (((uint32_t)(x) << USB_PORTSC1_STS_SHIFT) & USB_PORTSC1_STS_MASK)
#define USB_PORTSC1_STS_GET(x) (((uint32_t)(x) & USB_PORTSC1_STS_MASK) >> USB_PORTSC1_STS_SHIFT)

/*
 * PTW (RW)
 *
 * PTW
 * Parallel Transceiver Width
 * This bit has no effect if serial interface engine is used.
 * 0 - Select the 8-bit UTMI interface [60MHz]
 * 1 - Select the 16-bit UTMI interface [30MHz]
 */
#define USB_PORTSC1_PTW_MASK (0x10000000UL)
#define USB_PORTSC1_PTW_SHIFT (28U)
#define USB_PORTSC1_PTW_SET(x) (((uint32_t)(x) << USB_PORTSC1_PTW_SHIFT) & USB_PORTSC1_PTW_MASK)
#define USB_PORTSC1_PTW_GET(x) (((uint32_t)(x) & USB_PORTSC1_PTW_MASK) >> USB_PORTSC1_PTW_SHIFT)

/*
 * PSPD (RO)
 *
 * PSPD
 * Port Speed - Read Only.
 * This register field indicates the speed at which the port is operating.
 * 00 - Full Speed
 * 01 - Low Speed
 * 10 - High Speed
 * 11 - Undefined
 */
#define USB_PORTSC1_PSPD_MASK (0xC000000UL)
#define USB_PORTSC1_PSPD_SHIFT (26U)
#define USB_PORTSC1_PSPD_GET(x) (((uint32_t)(x) & USB_PORTSC1_PSPD_MASK) >> USB_PORTSC1_PSPD_SHIFT)

/*
 * PFSC (RW)
 *
 * PFSC
 * Port Force Full Speed Connect - Read/Write. Default = 0b.
 * When this bit is set to '1b', the port will be forced to only connect at Full Speed, It disables the chirp
 * sequence that allows the port to identify itself as High Speed.
 * 0 - Normal operation
 * 1 - Forced to full speed
 */
#define USB_PORTSC1_PFSC_MASK (0x1000000UL)
#define USB_PORTSC1_PFSC_SHIFT (24U)
#define USB_PORTSC1_PFSC_SET(x) (((uint32_t)(x) << USB_PORTSC1_PFSC_SHIFT) & USB_PORTSC1_PFSC_MASK)
#define USB_PORTSC1_PFSC_GET(x) (((uint32_t)(x) & USB_PORTSC1_PFSC_MASK) >> USB_PORTSC1_PFSC_SHIFT)

/*
 * PHCD (RW)
 *
 * PHCD
 * PHY Low Power Suspend - Clock Disable (PLPSCD) - Read/Write. Default = 0b.
 * When this bit is set to '1b', the PHY clock is disabled. Reading this bit will indicate the status of the PHY
 * clock.
 * NOTE: The PHY clock cannot be disabled if it is being used as the system clock.
 * In device mode, The PHY can be put into Low Power Suspend when the device is not running (USBCMD
 * Run/Stop=0b) or the host has signalled suspend (PORTSC1 SUSPEND=1b). PHY Low power suspend
 * will be cleared automatically when the host initials resume. Before forcing a resume from the device, the
 * device controller driver must clear this bit.
 * In host mode, the PHY can be put into Low Power Suspend when the downstream device has been put
 * into suspend mode or when no downstream device is connected. Low power suspend is completely
 * under the control of software.
 * 0 - Enable PHY clock
 * 1 - Disable PHY clock
 */
#define USB_PORTSC1_PHCD_MASK (0x800000UL)
#define USB_PORTSC1_PHCD_SHIFT (23U)
#define USB_PORTSC1_PHCD_SET(x) (((uint32_t)(x) << USB_PORTSC1_PHCD_SHIFT) & USB_PORTSC1_PHCD_MASK)
#define USB_PORTSC1_PHCD_GET(x) (((uint32_t)(x) & USB_PORTSC1_PHCD_MASK) >> USB_PORTSC1_PHCD_SHIFT)

/*
 * WKOC (RW)
 *
 * WKOC
 * Wake on Over-current Enable (WKOC_E) - Read/Write. Default = 0b.
 * Writing this bit to a one enables the port to be sensitive to over-current conditions as wake-up events.
 * This field is zero if Port Power(PORTSC1) is zero.
 */
#define USB_PORTSC1_WKOC_MASK (0x400000UL)
#define USB_PORTSC1_WKOC_SHIFT (22U)
#define USB_PORTSC1_WKOC_SET(x) (((uint32_t)(x) << USB_PORTSC1_WKOC_SHIFT) & USB_PORTSC1_WKOC_MASK)
#define USB_PORTSC1_WKOC_GET(x) (((uint32_t)(x) & USB_PORTSC1_WKOC_MASK) >> USB_PORTSC1_WKOC_SHIFT)

/*
 * WKDC (RW)
 *
 * WKDC
 * Wake on Disconnect Enable (WKDSCNNT_E) - Read/Write. Default=0b. Writing this bit to a one enables
 * the port to be sensitive to device disconnects as wake-up events.
 * This field is zero if Port Power(PORTSC1) is zero or in device mode.
 */
#define USB_PORTSC1_WKDC_MASK (0x200000UL)
#define USB_PORTSC1_WKDC_SHIFT (21U)
#define USB_PORTSC1_WKDC_SET(x) (((uint32_t)(x) << USB_PORTSC1_WKDC_SHIFT) & USB_PORTSC1_WKDC_MASK)
#define USB_PORTSC1_WKDC_GET(x) (((uint32_t)(x) & USB_PORTSC1_WKDC_MASK) >> USB_PORTSC1_WKDC_SHIFT)

/*
 * WKCN (RW)
 *
 * WKCN
 * Wake on Connect Enable (WKCNNT_E) - Read/Write. Default=0b.
 * Writing this bit to a one enables the port to be sensitive to device connects as wake-up events.
 * This field is zero if Port Power(PORTSC1) is zero or in device mode.
 */
#define USB_PORTSC1_WKCN_MASK (0x100000UL)
#define USB_PORTSC1_WKCN_SHIFT (20U)
#define USB_PORTSC1_WKCN_SET(x) (((uint32_t)(x) << USB_PORTSC1_WKCN_SHIFT) & USB_PORTSC1_WKCN_MASK)
#define USB_PORTSC1_WKCN_GET(x) (((uint32_t)(x) & USB_PORTSC1_WKCN_MASK) >> USB_PORTSC1_WKCN_SHIFT)

/*
 * PTC (RW)
 *
 * PTC
 * Port Test Control - Read/Write. Default = 0000b.
 * Refer to Port Test Mode for the operational model for using these test modes and the USB Specification Revision 2.0, Chapter 7 for details on each test mode.
 * The FORCE_ENABLE_FS and FORCE ENABLE_LS are extensions to the test mode support specified in the EHCI specification.
 * Writing the PTC field to any of the FORCE_ENABLE_{HS/FS/LS} values will force the port into the connected and enabled state at the selected speed.
 * Writing the PTC field back to TEST_MODE_DISABLE will allow the port state machines to progress normally from that point.
 * NOTE: Low speed operations are not supported as a peripheral device.
 * Any other value than zero indicates that the port is operating in test mode.
 * Value Specific Test
 * 0000 - TEST_MODE_DISABLE
 * 0001 - J_STATE
 * 0010 - K_STATE
 * 0011 - SE0 (host) / NAK (device)
 * 0100 - Packet
 * 0101 - FORCE_ENABLE_HS
 * 0110 - FORCE_ENABLE_FS
 * 0111 - FORCE_ENABLE_LS
 * 1000-1111 - Reserved
 */
#define USB_PORTSC1_PTC_MASK (0xF0000UL)
#define USB_PORTSC1_PTC_SHIFT (16U)
#define USB_PORTSC1_PTC_SET(x) (((uint32_t)(x) << USB_PORTSC1_PTC_SHIFT) & USB_PORTSC1_PTC_MASK)
#define USB_PORTSC1_PTC_GET(x) (((uint32_t)(x) & USB_PORTSC1_PTC_MASK) >> USB_PORTSC1_PTC_SHIFT)

/*
 * PP (RW)
 *
 * PP
 * Port Power (PP)-Read/Write or Read Only.
 * The function of this bit depends on the value of the Port Power Switching (PPC) field in the HCSPARAMS register. The behavior is as follows:
 * PPC
 * PP Operation
 * 0
 * 1b Read Only - Host controller does not have port power control switches. Each port is hard-wired to power.
 * 1
 * 1b/0b - Read/Write. OTG controller requires port power control switches. This bit represents the current setting of the switch (0=off, 1=on).
 * When power is not available on a port (that is, PP equals a 0), the port is non-functional and will not report attaches, detaches, etc.
 * When an over-current condition is detected on a powered port and PPC is a one,
 * the PP bit in each affected port may be transitional by the host controller driver from a one to a zero (removing power from the port).
 * This feature is implemented in all controller cores (PPC = 1).
 */
#define USB_PORTSC1_PP_MASK (0x1000U)
#define USB_PORTSC1_PP_SHIFT (12U)
#define USB_PORTSC1_PP_SET(x) (((uint32_t)(x) << USB_PORTSC1_PP_SHIFT) & USB_PORTSC1_PP_MASK)
#define USB_PORTSC1_PP_GET(x) (((uint32_t)(x) & USB_PORTSC1_PP_MASK) >> USB_PORTSC1_PP_SHIFT)

/*
 * LS (RO)
 *
 * LS
 * Line Status-Read Only. These bits reflect the current logical levels of the D+ (bit 11) and D- (bit 10) signal
 * lines.
 * In host mode, the use of linestate by the host controller driver is not necessary (unlike EHCI), because
 * the port controller state machine and the port routing manage the connection of LS and FS.
 * In device mode, the use of linestate by the device controller driver is not necessary.
 * The encoding of the bits are:
 * Bits [11:10] Meaning
 * 00 - SE0
 * 01 - K-state
 * 10 - J-state
 * 11 - Undefined
 */
#define USB_PORTSC1_LS_MASK (0xC00U)
#define USB_PORTSC1_LS_SHIFT (10U)
#define USB_PORTSC1_LS_GET(x) (((uint32_t)(x) & USB_PORTSC1_LS_MASK) >> USB_PORTSC1_LS_SHIFT)

/*
 * HSP (RO)
 *
 * HSP
 * High-Speed Port - Read Only. Default = 0b.
 * When the bit is one, the host/device connected to the port is in high-speed mode and if set to zero, the
 * host/device connected to the port is not in a high-speed mode.
 * NOTE: HSP is redundant with PSPD(bit 27, 26) but remained for compatibility.
 */
#define USB_PORTSC1_HSP_MASK (0x200U)
#define USB_PORTSC1_HSP_SHIFT (9U)
#define USB_PORTSC1_HSP_GET(x) (((uint32_t)(x) & USB_PORTSC1_HSP_MASK) >> USB_PORTSC1_HSP_SHIFT)

/*
 * PR (RW)
 *
 * PR
 * Port Reset - Read/Write or Read Only. Default = 0b.
 * In Host Mode: Read/Write. 1=Port is in Reset. 0=Port is not in Reset. Default 0.
 * When software writes a one to this bit the bus-reset sequence as defined in the USB Specification Revision 2.0 is started.
 * This bit will automatically change to zero after the reset sequence is complete.
 * This behavior is different from EHCI where the host controller driver is required to set this bit to a zero after the reset duration is timed in the driver.
 * In Device Mode: This bit is a read only status bit. Device reset from the USB bus is also indicated in the USBSTS register.
 */
#define USB_PORTSC1_PR_MASK (0x100U)
#define USB_PORTSC1_PR_SHIFT (8U)
#define USB_PORTSC1_PR_SET(x) (((uint32_t)(x) << USB_PORTSC1_PR_SHIFT) & USB_PORTSC1_PR_MASK)
#define USB_PORTSC1_PR_GET(x) (((uint32_t)(x) & USB_PORTSC1_PR_MASK) >> USB_PORTSC1_PR_SHIFT)

/*
 * SUSP (RW)
 *
 * SUSP
 * Suspend - Read/Write or Read Only. Default = 0b.
 * 1=Port in suspend state. 0=Port not in suspend state.
 * In Host Mode: Read/Write.
 * Port Enabled Bit and Suspend bit of this register define the port states as follows:
 * Bits [Port Enabled, Suspend] Port State
 * 0x Disable
 * 10 Enable
 * 11 Suspend
 * When in suspend state, downstream propagation of data is blocked on this port, except for port reset.
 * The blocking occurs at the end of the current transaction if a transaction was in progress when this bit was written to 1.
 * In the suspend state, the port is sensitive to resume detection.
 * Note that the bit status does not change until the port is suspended and that there may be a delay in suspending a port if there is a transaction currently in progress on the USB.
 * The host controller will unconditionally set this bit to zero when software sets the Force Port Resume bit to zero. The host controller ignores a write of zero to this bit.
 * If host software sets this bit to a one when the port is not enabled (that is, Port enabled bit is a zero) the results are undefined.
 * This field is zero if Port Power(PORTSC1) is zero in host mode.
 * In Device Mode: Read Only.
 * In device mode this bit is a read only status bit.
 */
#define USB_PORTSC1_SUSP_MASK (0x80U)
#define USB_PORTSC1_SUSP_SHIFT (7U)
#define USB_PORTSC1_SUSP_SET(x) (((uint32_t)(x) << USB_PORTSC1_SUSP_SHIFT) & USB_PORTSC1_SUSP_MASK)
#define USB_PORTSC1_SUSP_GET(x) (((uint32_t)(x) & USB_PORTSC1_SUSP_MASK) >> USB_PORTSC1_SUSP_SHIFT)

/*
 * FPR (RW)
 *
 * FPR
 * Force Port Resume -Read/Write. 1= Resume detected/driven on port. 0=No resume (K-state) detected driven on port. Default = 0.
 * In Host Mode:
 * Software sets this bit to one to drive resume signaling. The Host Controller sets this bit to one if a J-to-K transition is detected while the port is in the Suspend state.
 * When this bit transitions to a one because a J-to-K transition is detected, the Port Change Detect bit in the USBSTS register is also set to one.
 * This bit will automatically change to zero after the resume sequence is complete.
 * This behavior is different from EHCI where the host controller driver is required to set this bit to a zero after the resume duration is timed in the driver.
 * Note that when the Host controller owns the port, the resume sequence follows the defined sequence documented in the USB Specification Revision 2.0.
 * The resume signaling (Full-speed 'K') is driven on the port as long as this bit remains a one. This bit will remain a one until the port has switched to the high-speed idle.
 * Writing a zero has no effect because the port controller will time the resume operation, clear the bit the port control state switches to HS or FS idle.
 * This field is zero if Port Power(PORTSC1) is zero in host mode.
 * This bit is not-EHCI compatible.
 * In Device mode:
 * After the device has been in Suspend State for 5ms or more, software must set this bit to one to drive resume signaling before clearing.
 * The Device Controller will set this bit to one if a J-to-K transition is detected while the port is in the Suspend state.
 * The bit will be cleared when the device returns to normal operation.
 *  Also, when this bit wil be cleared because a K-to-J transition detected, the Port Change Detect bit in the USBSTS register is also set to one.
 */
#define USB_PORTSC1_FPR_MASK (0x40U)
#define USB_PORTSC1_FPR_SHIFT (6U)
#define USB_PORTSC1_FPR_SET(x) (((uint32_t)(x) << USB_PORTSC1_FPR_SHIFT) & USB_PORTSC1_FPR_MASK)
#define USB_PORTSC1_FPR_GET(x) (((uint32_t)(x) & USB_PORTSC1_FPR_MASK) >> USB_PORTSC1_FPR_SHIFT)

/*
 * OCC (RW)
 *
 * OCC
 * Over-current Change-R/WC. Default=0.
 * This bit is set '1b' by hardware when there is a change to Over-current Active. Software can clear this bit by writing a one to this bit position.
 */
#define USB_PORTSC1_OCC_MASK (0x20U)
#define USB_PORTSC1_OCC_SHIFT (5U)
#define USB_PORTSC1_OCC_SET(x) (((uint32_t)(x) << USB_PORTSC1_OCC_SHIFT) & USB_PORTSC1_OCC_MASK)
#define USB_PORTSC1_OCC_GET(x) (((uint32_t)(x) & USB_PORTSC1_OCC_MASK) >> USB_PORTSC1_OCC_SHIFT)

/*
 * OCA (RO)
 *
 * OCA
 * Over-current Active-Read Only. Default 0.
 * This bit will automatically transition from one to zero when the over current condition is removed.
 * 0 - This port does not have an over-current condition.
 * 1 - This port currently has an over-current condition
 */
#define USB_PORTSC1_OCA_MASK (0x10U)
#define USB_PORTSC1_OCA_SHIFT (4U)
#define USB_PORTSC1_OCA_GET(x) (((uint32_t)(x) & USB_PORTSC1_OCA_MASK) >> USB_PORTSC1_OCA_SHIFT)

/*
 * PEC (RWC)
 *
 * PEC
 * Port Enable/Disable Change-R/WC. 1=Port enabled/disabled status has changed. 0=No change. Default = 0.
 * In Host Mode:
 * For the root hub, this bit is set to a one only when a port is disabled due to disconnect on the port or
 * due to the appropriate conditions existing at the EOF2 point (See Chapter 11 of the USB Specification).
 * Software clears this by writing a one to it.
 * This field is zero if Port Power(PORTSC1) is zero.
 * In Device mode:
 * The device port is always enabled, so this bit is always '0b'.
 */
#define USB_PORTSC1_PEC_MASK (0x8U)
#define USB_PORTSC1_PEC_SHIFT (3U)
#define USB_PORTSC1_PEC_SET(x) (((uint32_t)(x) << USB_PORTSC1_PEC_SHIFT) & USB_PORTSC1_PEC_MASK)
#define USB_PORTSC1_PEC_GET(x) (((uint32_t)(x) & USB_PORTSC1_PEC_MASK) >> USB_PORTSC1_PEC_SHIFT)

/*
 * PE (RWC)
 *
 * PE
 * Port Enabled/Disabled-Read/Write. 1=Enable. 0=Disable. Default 0.
 * In Host Mode:
 * Ports can only be enabled by the host controller as a part of the reset and enable. Software cannot enable a port by writing a one to this field.
 * Ports can be disabled by either a fault condition (disconnect event or other fault condition) or by the host software.
 * Note that the bit status does not change until the port state actually changes. There may be a delay in disabling or enabling a port due to other host controller and bus events.
 * When the port is disabled, (0b) downstream propagation of data is blocked except for reset.
 * This field is zero if Port Power(PORTSC1) is zero in host mode.
 * In Device Mode:
 * The device port is always enabled, so this bit is always '1b'.
 */
#define USB_PORTSC1_PE_MASK (0x4U)
#define USB_PORTSC1_PE_SHIFT (2U)
#define USB_PORTSC1_PE_SET(x) (((uint32_t)(x) << USB_PORTSC1_PE_SHIFT) & USB_PORTSC1_PE_MASK)
#define USB_PORTSC1_PE_GET(x) (((uint32_t)(x) & USB_PORTSC1_PE_MASK) >> USB_PORTSC1_PE_SHIFT)

/*
 * CSC (RWC)
 *
 * CSC
 * Connect Status Change-R/WC. 1 =Change in Current Connect Status. 0=No change. Default 0.
 * In Host Mode:
 * Indicates a change has occurred in the port's Current Connect Status.
 * The host/device controller sets this bit for all changes to the port device connect status, even if system software has not cleared an existing connect status change.
 * For example, the insertion status changes twice before system software has cleared the changed condition,
 * hub hardware will be 'setting' an already-set bit (that is, the bit will remain set). Software clears this bit by writing a one to it.
 * This field is zero if Port Power(PORTSC1) is zero in host mode.
 * In Device Mode:
 * This bit is undefined in device controller mode.
 */
#define USB_PORTSC1_CSC_MASK (0x2U)
#define USB_PORTSC1_CSC_SHIFT (1U)
#define USB_PORTSC1_CSC_SET(x) (((uint32_t)(x) << USB_PORTSC1_CSC_SHIFT) & USB_PORTSC1_CSC_MASK)
#define USB_PORTSC1_CSC_GET(x) (((uint32_t)(x) & USB_PORTSC1_CSC_MASK) >> USB_PORTSC1_CSC_SHIFT)

/*
 * CCS (RWC)
 *
 * CCS
 * Current Connect Status-Read Only.
 * In Host Mode:
 * 1=Device is present on port. 0=No device is present. Default = 0.
 * This value reflects the current state of the port, and may not correspond directly to the event that caused the Connect Status Change bit (Bit 1) to be set.
 * This field is zero if Port Power(PORTSC1) is zero in host mode.
 * In Device Mode:
 * 1=Attached. 0=Not Attached. Default=0.
 * A one indicates that the device successfully attached and is operating in either high speed or full speed as indicated by the High Speed Port bit in this register.
 * A zero indicates that the device did not attach successfully or was forcibly disconnected by the software writing a zero to the Run bit in the USBCMD register.
 * It does not state the device being disconnected or Suspended.
 */
#define USB_PORTSC1_CCS_MASK (0x1U)
#define USB_PORTSC1_CCS_SHIFT (0U)
#define USB_PORTSC1_CCS_SET(x) (((uint32_t)(x) << USB_PORTSC1_CCS_SHIFT) & USB_PORTSC1_CCS_MASK)
#define USB_PORTSC1_CCS_GET(x) (((uint32_t)(x) & USB_PORTSC1_CCS_MASK) >> USB_PORTSC1_CCS_SHIFT)

/* Bitfield definition for register: OTGSC */
/*
 * ASVIE (RW)
 *
 * ASVIE
 * A Session Valid Interrupt Enable - Read/Write.
 */
#define USB_OTGSC_ASVIE_MASK (0x4000000UL)
#define USB_OTGSC_ASVIE_SHIFT (26U)
#define USB_OTGSC_ASVIE_SET(x) (((uint32_t)(x) << USB_OTGSC_ASVIE_SHIFT) & USB_OTGSC_ASVIE_MASK)
#define USB_OTGSC_ASVIE_GET(x) (((uint32_t)(x) & USB_OTGSC_ASVIE_MASK) >> USB_OTGSC_ASVIE_SHIFT)

/*
 * AVVIE (RW)
 *
 * AVVIE
 * A VBus Valid Interrupt Enable - Read/Write.
 * Setting this bit enables the A VBus valid interrupt.
 */
#define USB_OTGSC_AVVIE_MASK (0x2000000UL)
#define USB_OTGSC_AVVIE_SHIFT (25U)
#define USB_OTGSC_AVVIE_SET(x) (((uint32_t)(x) << USB_OTGSC_AVVIE_SHIFT) & USB_OTGSC_AVVIE_MASK)
#define USB_OTGSC_AVVIE_GET(x) (((uint32_t)(x) & USB_OTGSC_AVVIE_MASK) >> USB_OTGSC_AVVIE_SHIFT)

/*
 * IDIE (RW)
 *
 * IDIE
 * USB ID Interrupt Enable - Read/Write.
 * Setting this bit enables the USB ID interrupt.
 */
#define USB_OTGSC_IDIE_MASK (0x1000000UL)
#define USB_OTGSC_IDIE_SHIFT (24U)
#define USB_OTGSC_IDIE_SET(x) (((uint32_t)(x) << USB_OTGSC_IDIE_SHIFT) & USB_OTGSC_IDIE_MASK)
#define USB_OTGSC_IDIE_GET(x) (((uint32_t)(x) & USB_OTGSC_IDIE_MASK) >> USB_OTGSC_IDIE_SHIFT)

/*
 * ASVIS (RWC)
 *
 * ASVIS
 * A Session Valid Interrupt Status - Read/Write to Clear.
 * This bit is set when VBus has either risen above or fallen below the A session valid threshold.
 * Software must write a one to clear this bit.
 */
#define USB_OTGSC_ASVIS_MASK (0x40000UL)
#define USB_OTGSC_ASVIS_SHIFT (18U)
#define USB_OTGSC_ASVIS_SET(x) (((uint32_t)(x) << USB_OTGSC_ASVIS_SHIFT) & USB_OTGSC_ASVIS_MASK)
#define USB_OTGSC_ASVIS_GET(x) (((uint32_t)(x) & USB_OTGSC_ASVIS_MASK) >> USB_OTGSC_ASVIS_SHIFT)

/*
 * AVVIS (RWC)
 *
 * AVVIS
 * A VBus Valid Interrupt Status - Read/Write to Clear.
 * This bit is set when VBus has either risen above or fallen below the VBus valid threshold on an A device.
 * Software must write a one to clear this bit.
 */
#define USB_OTGSC_AVVIS_MASK (0x20000UL)
#define USB_OTGSC_AVVIS_SHIFT (17U)
#define USB_OTGSC_AVVIS_SET(x) (((uint32_t)(x) << USB_OTGSC_AVVIS_SHIFT) & USB_OTGSC_AVVIS_MASK)
#define USB_OTGSC_AVVIS_GET(x) (((uint32_t)(x) & USB_OTGSC_AVVIS_MASK) >> USB_OTGSC_AVVIS_SHIFT)

/*
 * IDIS (RWC)
 *
 * IDIS
 * USB ID Interrupt Status - Read/Write.
 * This bit is set when a change on the ID input has been detected.
 * Software must write a one to clear this bit.
 */
#define USB_OTGSC_IDIS_MASK (0x10000UL)
#define USB_OTGSC_IDIS_SHIFT (16U)
#define USB_OTGSC_IDIS_SET(x) (((uint32_t)(x) << USB_OTGSC_IDIS_SHIFT) & USB_OTGSC_IDIS_MASK)
#define USB_OTGSC_IDIS_GET(x) (((uint32_t)(x) & USB_OTGSC_IDIS_MASK) >> USB_OTGSC_IDIS_SHIFT)

/*
 * ASV (RO)
 *
 * ASV
 * A Session Valid - Read Only.
 * Indicates VBus is above the A session valid threshold.
 */
#define USB_OTGSC_ASV_MASK (0x400U)
#define USB_OTGSC_ASV_SHIFT (10U)
#define USB_OTGSC_ASV_GET(x) (((uint32_t)(x) & USB_OTGSC_ASV_MASK) >> USB_OTGSC_ASV_SHIFT)

/*
 * AVV (RO)
 *
 * AVV
 * A VBus Valid - Read Only.
 * Indicates VBus is above the A VBus valid threshold.
 */
#define USB_OTGSC_AVV_MASK (0x200U)
#define USB_OTGSC_AVV_SHIFT (9U)
#define USB_OTGSC_AVV_GET(x) (((uint32_t)(x) & USB_OTGSC_AVV_MASK) >> USB_OTGSC_AVV_SHIFT)

/*
 * ID (RO)
 *
 * ID
 * USB ID - Read Only.
 * 0 = A device, 1 = B device
 */
#define USB_OTGSC_ID_MASK (0x100U)
#define USB_OTGSC_ID_SHIFT (8U)
#define USB_OTGSC_ID_GET(x) (((uint32_t)(x) & USB_OTGSC_ID_MASK) >> USB_OTGSC_ID_SHIFT)

/*
 * IDPU (RW)
 *
 * IDPU
 * ID Pullup - Read/Write
 * This bit provide control over the ID pull-up resistor; 0 = off, 1 = on [default]. When this bit is 0, the ID input
 * will not be sampled.
 */
#define USB_OTGSC_IDPU_MASK (0x20U)
#define USB_OTGSC_IDPU_SHIFT (5U)
#define USB_OTGSC_IDPU_SET(x) (((uint32_t)(x) << USB_OTGSC_IDPU_SHIFT) & USB_OTGSC_IDPU_MASK)
#define USB_OTGSC_IDPU_GET(x) (((uint32_t)(x) & USB_OTGSC_IDPU_MASK) >> USB_OTGSC_IDPU_SHIFT)

/*
 * VC (RW)
 *
 * VC
 * VBUS Charge - Read/Write.
 * Setting this bit causes the VBus line to be charged. This is used for VBus pulsing during SRP.
 */
#define USB_OTGSC_VC_MASK (0x2U)
#define USB_OTGSC_VC_SHIFT (1U)
#define USB_OTGSC_VC_SET(x) (((uint32_t)(x) << USB_OTGSC_VC_SHIFT) & USB_OTGSC_VC_MASK)
#define USB_OTGSC_VC_GET(x) (((uint32_t)(x) & USB_OTGSC_VC_MASK) >> USB_OTGSC_VC_SHIFT)

/*
 * VD (RW)
 *
 * VD
 * VBUS_Discharge - Read/Write.
 * Setting this bit causes VBus to discharge through a resistor.
 */
#define USB_OTGSC_VD_MASK (0x1U)
#define USB_OTGSC_VD_SHIFT (0U)
#define USB_OTGSC_VD_SET(x) (((uint32_t)(x) << USB_OTGSC_VD_SHIFT) & USB_OTGSC_VD_MASK)
#define USB_OTGSC_VD_GET(x) (((uint32_t)(x) & USB_OTGSC_VD_MASK) >> USB_OTGSC_VD_SHIFT)

/* Bitfield definition for register: USBMODE */
/*
 * SDIS (RW)
 *
 * SDIS
 * Stream Disable Mode. (0 - Inactive [default]; 1 - Active)
 * Device Mode: Setting to a '1' disables double priming on both RX and TX for low bandwidth systems.
 * This mode ensures that when the RX and TX buffers are sufficient to contain an entire packet that the standard double buffering scheme is disabled to prevent overruns/underruns in bandwidth limited systems.
 * Note: In High Speed Mode, all packets received are responded to with a NYET handshake when stream disable is active.
 * Host Mode: Setting to a '1' ensures that overruns/underruns of the latency FIFO are eliminated for low bandwidth systems
 * where the RX and TX buffers are sufficient to contain the entire packet. Enabling stream disable also has the effect of ensuring the TX latency is filled to capacity before the packet is launched onto the USB.
 * NOTE: Time duration to pre-fill the FIFO becomes significant when stream disable is active. See TXFILLTUNING and TXTTFILLTUNING [MPH Only] to characterize the adjustments needed for
 * the scheduler when using this feature.
 * NOTE: The use of this feature substantially limits of the overall USB performance that can be achieved.
 */
#define USB_USBMODE_SDIS_MASK (0x10U)
#define USB_USBMODE_SDIS_SHIFT (4U)
#define USB_USBMODE_SDIS_SET(x) (((uint32_t)(x) << USB_USBMODE_SDIS_SHIFT) & USB_USBMODE_SDIS_MASK)
#define USB_USBMODE_SDIS_GET(x) (((uint32_t)(x) & USB_USBMODE_SDIS_MASK) >> USB_USBMODE_SDIS_SHIFT)

/*
 * SLOM (RW)
 *
 * SLOM
 * Setup Lockout Mode. In device mode, this bit controls behavior of the setup lock mechanism. See Control Endpoint Operation Model .
 * 0 - Setup Lockouts On (default);
 * 1 - Setup Lockouts Off. DCD requires use of Setup Data Buffer Tripwire in USBCMD.
 */
#define USB_USBMODE_SLOM_MASK (0x8U)
#define USB_USBMODE_SLOM_SHIFT (3U)
#define USB_USBMODE_SLOM_SET(x) (((uint32_t)(x) << USB_USBMODE_SLOM_SHIFT) & USB_USBMODE_SLOM_MASK)
#define USB_USBMODE_SLOM_GET(x) (((uint32_t)(x) & USB_USBMODE_SLOM_MASK) >> USB_USBMODE_SLOM_SHIFT)

/*
 * ES (RW)
 *
 * ES
 * Endian Select - Read/Write. This bit can change the byte alignment of the transfer buffers to match the
 * host microprocessor. The bit fields in the microprocessor interface and the data structures are unaffected
 * by the value of this bit because they are based upon the 32-bit word.
 * Bit Meaning
 * 0 - Little Endian [Default]
 * 1 - Big Endian
 */
#define USB_USBMODE_ES_MASK (0x4U)
#define USB_USBMODE_ES_SHIFT (2U)
#define USB_USBMODE_ES_SET(x) (((uint32_t)(x) << USB_USBMODE_ES_SHIFT) & USB_USBMODE_ES_MASK)
#define USB_USBMODE_ES_GET(x) (((uint32_t)(x) & USB_USBMODE_ES_MASK) >> USB_USBMODE_ES_SHIFT)

/*
 * CM (RW)
 *
 * CM
 * Controller Mode - R/WO. Controller mode is defaulted to the proper mode for host only and device only
 * implementations. For those designs that contain both host & device capability, the controller defaults to
 * an idle state and needs to be initialized to the desired operating mode after reset. For combination host/
 * device controllers, this register can only be written once after reset. If it is necessary to switch modes,
 * software must reset the controller by writing to the RESET bit in the USBCMD register before
 * reprogramming this register.
 * For OTG controller core, reset value is '00b'.
 * 00 - Idle [Default for combination host/device]
 * 01 - Reserved
 * 10 - Device Controller [Default for device only controller]
 * 11 - Host Controller [Default for host only controller]
 */
#define USB_USBMODE_CM_MASK (0x3U)
#define USB_USBMODE_CM_SHIFT (0U)
#define USB_USBMODE_CM_SET(x) (((uint32_t)(x) << USB_USBMODE_CM_SHIFT) & USB_USBMODE_CM_MASK)
#define USB_USBMODE_CM_GET(x) (((uint32_t)(x) & USB_USBMODE_CM_MASK) >> USB_USBMODE_CM_SHIFT)

/* Bitfield definition for register: ENDPTSETUPSTAT */
/*
 * ENDPTSETUPSTAT (RWC)
 *
 * ENDPTSETUPSTAT
 * Setup Endpoint Status. For every setup transaction that is received, a corresponding bit in this register is set to one.
 * Software must clear or acknowledge the setup transfer by writing a one to a respective bit after it has read the setup data from Queue head.
 * The response to a setup packet as in the order of operations and total response time is crucial to limit bus time outs while the setup lock out mechanism is engaged.
 * This register is only used in device mode.
 */
#define USB_ENDPTSETUPSTAT_ENDPTSETUPSTAT_MASK (0xFFFFU)
#define USB_ENDPTSETUPSTAT_ENDPTSETUPSTAT_SHIFT (0U)
#define USB_ENDPTSETUPSTAT_ENDPTSETUPSTAT_SET(x) (((uint32_t)(x) << USB_ENDPTSETUPSTAT_ENDPTSETUPSTAT_SHIFT) & USB_ENDPTSETUPSTAT_ENDPTSETUPSTAT_MASK)
#define USB_ENDPTSETUPSTAT_ENDPTSETUPSTAT_GET(x) (((uint32_t)(x) & USB_ENDPTSETUPSTAT_ENDPTSETUPSTAT_MASK) >> USB_ENDPTSETUPSTAT_ENDPTSETUPSTAT_SHIFT)

/* Bitfield definition for register: ENDPTPRIME */
/*
 * PETB (RWS)
 *
 * PETB
 * Prime Endpoint Transmit Buffer - R/WS. For each endpoint a corresponding bit is used to request that a
 * buffer is prepared for a transmit operation in order to respond to a USB IN/INTERRUPT transaction.
 * Software should write a one to the corresponding bit when posting a new transfer descriptor to an
 * endpoint queue head. Hardware automatically uses this bit to begin parsing for a new transfer descriptor
 * from the queue head and prepare a transmit buffer. Hardware clears this bit when the associated
 * endpoint(s) is (are) successfully primed.
 * NOTE: These bits are momentarily set by hardware during hardware re-priming operations when a dTD
 * is retired, and the dQH is updated.
 * PETB[N] - Endpoint #N, N is in 0..7
 */
#define USB_ENDPTPRIME_PETB_MASK (0xFFFF0000UL)
#define USB_ENDPTPRIME_PETB_SHIFT (16U)
#define USB_ENDPTPRIME_PETB_SET(x) (((uint32_t)(x) << USB_ENDPTPRIME_PETB_SHIFT) & USB_ENDPTPRIME_PETB_MASK)
#define USB_ENDPTPRIME_PETB_GET(x) (((uint32_t)(x) & USB_ENDPTPRIME_PETB_MASK) >> USB_ENDPTPRIME_PETB_SHIFT)

/*
 * PERB (RWS)
 *
 * PERB
 * Prime Endpoint Receive Buffer - R/WS. For each endpoint, a corresponding bit is used to request a buffer prepare for a receive operation for when a USB host initiates a USB OUT transaction.
 * Software should write a one to the corresponding bit whenever posting a new transfer descriptor to an endpoint queue head.
 * Hardware automatically uses this bit to begin parsing for a new transfer descriptor from the queue head and prepare a receive buffer.
 * Hardware clears this bit when the associated endpoint(s) is (are) successfully primed.
 * NOTE: These bits are momentarily set by hardware during hardware re-priming operations when a dTD
 * is retired, and the dQH is updated.
 * PERB[N] - Endpoint #N, N is in 0..7
 */
#define USB_ENDPTPRIME_PERB_MASK (0xFFFFU)
#define USB_ENDPTPRIME_PERB_SHIFT (0U)
#define USB_ENDPTPRIME_PERB_SET(x) (((uint32_t)(x) << USB_ENDPTPRIME_PERB_SHIFT) & USB_ENDPTPRIME_PERB_MASK)
#define USB_ENDPTPRIME_PERB_GET(x) (((uint32_t)(x) & USB_ENDPTPRIME_PERB_MASK) >> USB_ENDPTPRIME_PERB_SHIFT)

/* Bitfield definition for register: ENDPTFLUSH */
/*
 * FETB (RWS)
 *
 * FETB
 * Flush Endpoint Transmit Buffer - R/WS. Writing one to a bit(s) in this register causes the associated endpoint(s) to clear any primed buffers.
 * If a packet is in progress for one of the associated endpoints, then that transfer continues until completion.
 * Hardware clears this register after the endpoint flush operation is successful.
 * FETB[N] - Endpoint #N, N is in 0..7
 */
#define USB_ENDPTFLUSH_FETB_MASK (0xFFFF0000UL)
#define USB_ENDPTFLUSH_FETB_SHIFT (16U)
#define USB_ENDPTFLUSH_FETB_SET(x) (((uint32_t)(x) << USB_ENDPTFLUSH_FETB_SHIFT) & USB_ENDPTFLUSH_FETB_MASK)
#define USB_ENDPTFLUSH_FETB_GET(x) (((uint32_t)(x) & USB_ENDPTFLUSH_FETB_MASK) >> USB_ENDPTFLUSH_FETB_SHIFT)

/*
 * FERB (RWS)
 *
 * FERB
 * Flush Endpoint Receive Buffer - R/WS. Writing one to a bit(s) causes the associated endpoint(s) to clear any primed buffers.
 *  If a packet is in progress for one of the associated endpoints, then that transfer continues until completion.
 * Hardware clears this register after the endpoint flush operation is successful.
 * FERB[N] - Endpoint #N, N is in 0..7
 */
#define USB_ENDPTFLUSH_FERB_MASK (0xFFFFU)
#define USB_ENDPTFLUSH_FERB_SHIFT (0U)
#define USB_ENDPTFLUSH_FERB_SET(x) (((uint32_t)(x) << USB_ENDPTFLUSH_FERB_SHIFT) & USB_ENDPTFLUSH_FERB_MASK)
#define USB_ENDPTFLUSH_FERB_GET(x) (((uint32_t)(x) & USB_ENDPTFLUSH_FERB_MASK) >> USB_ENDPTFLUSH_FERB_SHIFT)

/* Bitfield definition for register: ENDPTSTAT */
/*
 * ETBR (RO)
 *
 * ETBR
 * Endpoint Transmit Buffer Ready -- Read Only. One bit for each endpoint indicates status of the respective endpoint buffer.
 * This bit is set to one by the hardware as a response to receiving a command from a corresponding bit in the ENDPTPRIME register.
 * There is always a delay between setting a bit in the ENDPTPRIME register and endpoint indicating ready.
 * This delay time varies based upon the current USB traffic and the number of bits set in the ENDPRIME register.
 * Buffer ready is cleared by USB reset, by the USB DMA system, or through the ENDPTFLUSH register.
 * NOTE: These bits are momentarily cleared by hardware during hardware endpoint re-priming operations when a dTD is retired, and the dQH is updated.
 * ETBR[N] - Endpoint #N, N is in 0..7
 */
#define USB_ENDPTSTAT_ETBR_MASK (0xFFFF0000UL)
#define USB_ENDPTSTAT_ETBR_SHIFT (16U)
#define USB_ENDPTSTAT_ETBR_GET(x) (((uint32_t)(x) & USB_ENDPTSTAT_ETBR_MASK) >> USB_ENDPTSTAT_ETBR_SHIFT)

/*
 * ERBR (RO)
 *
 * ERBR
 * Endpoint Receive Buffer Ready -- Read Only. One bit for each endpoint indicates status of the respective
 * endpoint buffer. This bit is set to a one by the hardware as a response to receiving a command from a
 * corresponding bit in the ENDPRIME register. There is always a delay between setting a bit in the
 * ENDPRIME register and endpoint indicating ready. This delay time varies based upon the current USB
 * traffic and the number of bits set in the ENDPRIME register. Buffer ready is cleared by USB reset, by the
 * USB DMA system, or through the ENDPTFLUSH register.
 * NOTE: These bits are momentarily cleared by hardware during hardware endpoint re-priming operations
 * when a dTD is retired, and the dQH is updated.
 * ERBR[N] - Endpoint #N, N is in 0..7
 */
#define USB_ENDPTSTAT_ERBR_MASK (0xFFFFU)
#define USB_ENDPTSTAT_ERBR_SHIFT (0U)
#define USB_ENDPTSTAT_ERBR_GET(x) (((uint32_t)(x) & USB_ENDPTSTAT_ERBR_MASK) >> USB_ENDPTSTAT_ERBR_SHIFT)

/* Bitfield definition for register: ENDPTCOMPLETE */
/*
 * ETCE (RWC)
 *
 * ETCE
 * Endpoint Transmit Complete Event - R/WC. Each bit indicates a transmit event (IN/INTERRUPT) occurred and software should read the corresponding endpoint queue to determine the endpoint status.
 * If the corresponding IOC bit is set in the Transfer Descriptor, then this bit is set simultaneously with the USBINT . Writing one clears the corresponding bit in this register.
 * ETCE[N] - Endpoint #N, N is in 0..7
 */
#define USB_ENDPTCOMPLETE_ETCE_MASK (0xFFFF0000UL)
#define USB_ENDPTCOMPLETE_ETCE_SHIFT (16U)
#define USB_ENDPTCOMPLETE_ETCE_SET(x) (((uint32_t)(x) << USB_ENDPTCOMPLETE_ETCE_SHIFT) & USB_ENDPTCOMPLETE_ETCE_MASK)
#define USB_ENDPTCOMPLETE_ETCE_GET(x) (((uint32_t)(x) & USB_ENDPTCOMPLETE_ETCE_MASK) >> USB_ENDPTCOMPLETE_ETCE_SHIFT)

/*
 * ERCE (RWC)
 *
 * ERCE
 * Endpoint Receive Complete Event - RW/C. Each bit indicates a received event (OUT/SETUP) occurred
 * and software should read the corresponding endpoint queue to determine the transfer status. If the
 * corresponding IOC bit is set in the Transfer Descriptor, then this bit is set simultaneously with the
 * USBINT . Writing one clears the corresponding bit in this register.
 * ERCE[N] - Endpoint #N, N is in 0..7
 */
#define USB_ENDPTCOMPLETE_ERCE_MASK (0xFFFFU)
#define USB_ENDPTCOMPLETE_ERCE_SHIFT (0U)
#define USB_ENDPTCOMPLETE_ERCE_SET(x) (((uint32_t)(x) << USB_ENDPTCOMPLETE_ERCE_SHIFT) & USB_ENDPTCOMPLETE_ERCE_MASK)
#define USB_ENDPTCOMPLETE_ERCE_GET(x) (((uint32_t)(x) & USB_ENDPTCOMPLETE_ERCE_MASK) >> USB_ENDPTCOMPLETE_ERCE_SHIFT)

/* Bitfield definition for register array: ENDPTCTRL */
/*
 * TXE (RW)
 *
 * TXE
 * TX Endpoint Enable
 * 0 Disabled [Default]
 * 1 Enabled
 * An Endpoint should be enabled only after it has been configured.
 */
#define USB_ENDPTCTRL_TXE_MASK (0x800000UL)
#define USB_ENDPTCTRL_TXE_SHIFT (23U)
#define USB_ENDPTCTRL_TXE_SET(x) (((uint32_t)(x) << USB_ENDPTCTRL_TXE_SHIFT) & USB_ENDPTCTRL_TXE_MASK)
#define USB_ENDPTCTRL_TXE_GET(x) (((uint32_t)(x) & USB_ENDPTCTRL_TXE_MASK) >> USB_ENDPTCTRL_TXE_SHIFT)

/*
 * TXR (WS)
 *
 * TXR
 * TX Data Toggle Reset (WS)
 * Write 1 - Reset PID Sequence
 * Whenever a configuration event is received for this Endpoint, software must write a one to this bit in order
 * to synchronize the data PID's between the Host and device.
 */
#define USB_ENDPTCTRL_TXR_MASK (0x400000UL)
#define USB_ENDPTCTRL_TXR_SHIFT (22U)
#define USB_ENDPTCTRL_TXR_SET(x) (((uint32_t)(x) << USB_ENDPTCTRL_TXR_SHIFT) & USB_ENDPTCTRL_TXR_MASK)
#define USB_ENDPTCTRL_TXR_GET(x) (((uint32_t)(x) & USB_ENDPTCTRL_TXR_MASK) >> USB_ENDPTCTRL_TXR_SHIFT)

/*
 * TXT (RW)
 *
 * TXT
 * TX Endpoint Type - Read/Write
 * 00 Control
 * 01 Isochronous
 * 10 Bulk
 * 11 Interrupt
 */
#define USB_ENDPTCTRL_TXT_MASK (0xC0000UL)
#define USB_ENDPTCTRL_TXT_SHIFT (18U)
#define USB_ENDPTCTRL_TXT_SET(x) (((uint32_t)(x) << USB_ENDPTCTRL_TXT_SHIFT) & USB_ENDPTCTRL_TXT_MASK)
#define USB_ENDPTCTRL_TXT_GET(x) (((uint32_t)(x) & USB_ENDPTCTRL_TXT_MASK) >> USB_ENDPTCTRL_TXT_SHIFT)

/*
 * TXS (RW)
 *
 * TXS
 * TX Endpoint Stall - Read/Write
 * 0 End Point OK
 * 1 End Point Stalled
 * This bit will be cleared automatically upon receipt of a SETUP request if this Endpoint is configured
 * as a Control Endpoint and this bit will continue to be cleared by hardware until the associated ENDPTSETUPSTAT bit is cleared.
 * Software can write a one to this bit to force the endpoint to return a STALL handshake to the Host.
 * This control will continue to STALL until this bit is either cleared by software or automatically cleared as above for control endpoints.
 * NOTE: [CONTROL ENDPOINT TYPES ONLY]: there is a slight delay (50 clocks max) between the ENDPTSETUPSTAT begin cleared and hardware continuing to clear this bit.
 * In most systems, it is unlikely the DCD software will observe this delay. However, should the DCD observe that the stall bit is not set after writing a one to it then follow this procedure:
 * continually write this stall bit until it is set or until a new setup has been received by checking the associated endptsetupstat Bit.
 */
#define USB_ENDPTCTRL_TXS_MASK (0x10000UL)
#define USB_ENDPTCTRL_TXS_SHIFT (16U)
#define USB_ENDPTCTRL_TXS_SET(x) (((uint32_t)(x) << USB_ENDPTCTRL_TXS_SHIFT) & USB_ENDPTCTRL_TXS_MASK)
#define USB_ENDPTCTRL_TXS_GET(x) (((uint32_t)(x) & USB_ENDPTCTRL_TXS_MASK) >> USB_ENDPTCTRL_TXS_SHIFT)

/*
 * RXE (RW)
 *
 * RXE
 * RX Endpoint Enable
 * 0 Disabled [Default]
 * 1 Enabled
 * An Endpoint should be enabled only after it has been configured.
 */
#define USB_ENDPTCTRL_RXE_MASK (0x80U)
#define USB_ENDPTCTRL_RXE_SHIFT (7U)
#define USB_ENDPTCTRL_RXE_SET(x) (((uint32_t)(x) << USB_ENDPTCTRL_RXE_SHIFT) & USB_ENDPTCTRL_RXE_MASK)
#define USB_ENDPTCTRL_RXE_GET(x) (((uint32_t)(x) & USB_ENDPTCTRL_RXE_MASK) >> USB_ENDPTCTRL_RXE_SHIFT)

/*
 * RXR (WS)
 *
 * RXR
 * RX Data Toggle Reset (WS)
 * Write 1 - Reset PID Sequence
 * Whenever a configuration event is received for this Endpoint, software must write a one to this bit in order
 * to synchronize the data PID's between the host and device.
 */
#define USB_ENDPTCTRL_RXR_MASK (0x40U)
#define USB_ENDPTCTRL_RXR_SHIFT (6U)
#define USB_ENDPTCTRL_RXR_SET(x) (((uint32_t)(x) << USB_ENDPTCTRL_RXR_SHIFT) & USB_ENDPTCTRL_RXR_MASK)
#define USB_ENDPTCTRL_RXR_GET(x) (((uint32_t)(x) & USB_ENDPTCTRL_RXR_MASK) >> USB_ENDPTCTRL_RXR_SHIFT)

/*
 * RXT (RW)
 *
 * RXT
 * RX Endpoint Type - Read/Write
 * 00 Control
 * 01 Isochronous
 * 10 Bulk
 * 11 Interrupt
 */
#define USB_ENDPTCTRL_RXT_MASK (0xCU)
#define USB_ENDPTCTRL_RXT_SHIFT (2U)
#define USB_ENDPTCTRL_RXT_SET(x) (((uint32_t)(x) << USB_ENDPTCTRL_RXT_SHIFT) & USB_ENDPTCTRL_RXT_MASK)
#define USB_ENDPTCTRL_RXT_GET(x) (((uint32_t)(x) & USB_ENDPTCTRL_RXT_MASK) >> USB_ENDPTCTRL_RXT_SHIFT)

/*
 * RXS (RW)
 *
 * RXS
 * RX Endpoint Stall - Read/Write
 * 0 End Point OK. [Default]
 * 1 End Point Stalled
 * This bit is set automatically upon receipt of a SETUP request if this Endpoint is configured as a Control
 * Endpointand this bit will continue to be cleared by hardware until the associated ENDPTSETUPSTAT bit
 * is cleared.
 * Software can write a one to this bit to force the endpoint to return a STALL handshake to the Host. This
 * control will continue to STALL until this bit is either cleared by software or automatically cleared as above
 * for control endpoints.
 * NOTE: [CONTROL ENDPOINT TYPES ONLY]: there is a slight delay (50 clocks max) between the
 * ENDPTSETUPSTAT begin cleared and hardware continuing to clear this bit. In most systems, it
 * is unlikely the DCD software will observe this delay. However, should the DCD observe that the
 * stall bit is not set after writing a one to it then follow this procedure: continually write this stall bit
 * until it is set or until a new setup has been received by checking the associated endptsetupstat
 * Bit.
 */
#define USB_ENDPTCTRL_RXS_MASK (0x1U)
#define USB_ENDPTCTRL_RXS_SHIFT (0U)
#define USB_ENDPTCTRL_RXS_SET(x) (((uint32_t)(x) << USB_ENDPTCTRL_RXS_SHIFT) & USB_ENDPTCTRL_RXS_MASK)
#define USB_ENDPTCTRL_RXS_GET(x) (((uint32_t)(x) & USB_ENDPTCTRL_RXS_MASK) >> USB_ENDPTCTRL_RXS_SHIFT)

/* Bitfield definition for register: OTG_CTRL0 */
/*
 * OTG_WKDPDMCHG_EN (RW)
 *
 */
#define USB_OTG_CTRL0_OTG_WKDPDMCHG_EN_MASK (0x2000000UL)
#define USB_OTG_CTRL0_OTG_WKDPDMCHG_EN_SHIFT (25U)
#define USB_OTG_CTRL0_OTG_WKDPDMCHG_EN_SET(x) (((uint32_t)(x) << USB_OTG_CTRL0_OTG_WKDPDMCHG_EN_SHIFT) & USB_OTG_CTRL0_OTG_WKDPDMCHG_EN_MASK)
#define USB_OTG_CTRL0_OTG_WKDPDMCHG_EN_GET(x) (((uint32_t)(x) & USB_OTG_CTRL0_OTG_WKDPDMCHG_EN_MASK) >> USB_OTG_CTRL0_OTG_WKDPDMCHG_EN_SHIFT)

/*
 * AUTORESUME_EN (RW)
 *
 */
#define USB_OTG_CTRL0_AUTORESUME_EN_MASK (0x80000UL)
#define USB_OTG_CTRL0_AUTORESUME_EN_SHIFT (19U)
#define USB_OTG_CTRL0_AUTORESUME_EN_SET(x) (((uint32_t)(x) << USB_OTG_CTRL0_AUTORESUME_EN_SHIFT) & USB_OTG_CTRL0_AUTORESUME_EN_MASK)
#define USB_OTG_CTRL0_AUTORESUME_EN_GET(x) (((uint32_t)(x) & USB_OTG_CTRL0_AUTORESUME_EN_MASK) >> USB_OTG_CTRL0_AUTORESUME_EN_SHIFT)

/*
 * OTG_VBUS_WAKEUP_EN (RW)
 *
 */
#define USB_OTG_CTRL0_OTG_VBUS_WAKEUP_EN_MASK (0x20000UL)
#define USB_OTG_CTRL0_OTG_VBUS_WAKEUP_EN_SHIFT (17U)
#define USB_OTG_CTRL0_OTG_VBUS_WAKEUP_EN_SET(x) (((uint32_t)(x) << USB_OTG_CTRL0_OTG_VBUS_WAKEUP_EN_SHIFT) & USB_OTG_CTRL0_OTG_VBUS_WAKEUP_EN_MASK)
#define USB_OTG_CTRL0_OTG_VBUS_WAKEUP_EN_GET(x) (((uint32_t)(x) & USB_OTG_CTRL0_OTG_VBUS_WAKEUP_EN_MASK) >> USB_OTG_CTRL0_OTG_VBUS_WAKEUP_EN_SHIFT)

/*
 * OTG_ID_WAKEUP_EN (RW)
 *
 */
#define USB_OTG_CTRL0_OTG_ID_WAKEUP_EN_MASK (0x10000UL)
#define USB_OTG_CTRL0_OTG_ID_WAKEUP_EN_SHIFT (16U)
#define USB_OTG_CTRL0_OTG_ID_WAKEUP_EN_SET(x) (((uint32_t)(x) << USB_OTG_CTRL0_OTG_ID_WAKEUP_EN_SHIFT) & USB_OTG_CTRL0_OTG_ID_WAKEUP_EN_MASK)
#define USB_OTG_CTRL0_OTG_ID_WAKEUP_EN_GET(x) (((uint32_t)(x) & USB_OTG_CTRL0_OTG_ID_WAKEUP_EN_MASK) >> USB_OTG_CTRL0_OTG_ID_WAKEUP_EN_SHIFT)

/*
 * OTG_VBUS_SOURCE_SEL (RW)
 *
 */
#define USB_OTG_CTRL0_OTG_VBUS_SOURCE_SEL_MASK (0x2000U)
#define USB_OTG_CTRL0_OTG_VBUS_SOURCE_SEL_SHIFT (13U)
#define USB_OTG_CTRL0_OTG_VBUS_SOURCE_SEL_SET(x) (((uint32_t)(x) << USB_OTG_CTRL0_OTG_VBUS_SOURCE_SEL_SHIFT) & USB_OTG_CTRL0_OTG_VBUS_SOURCE_SEL_MASK)
#define USB_OTG_CTRL0_OTG_VBUS_SOURCE_SEL_GET(x) (((uint32_t)(x) & USB_OTG_CTRL0_OTG_VBUS_SOURCE_SEL_MASK) >> USB_OTG_CTRL0_OTG_VBUS_SOURCE_SEL_SHIFT)

/*
 * OTG_UTMI_SUSPENDM_SW (RW)
 *
 * default 0 for naneng usbphy
 */
#define USB_OTG_CTRL0_OTG_UTMI_SUSPENDM_SW_MASK (0x1000U)
#define USB_OTG_CTRL0_OTG_UTMI_SUSPENDM_SW_SHIFT (12U)
#define USB_OTG_CTRL0_OTG_UTMI_SUSPENDM_SW_SET(x) (((uint32_t)(x) << USB_OTG_CTRL0_OTG_UTMI_SUSPENDM_SW_SHIFT) & USB_OTG_CTRL0_OTG_UTMI_SUSPENDM_SW_MASK)
#define USB_OTG_CTRL0_OTG_UTMI_SUSPENDM_SW_GET(x) (((uint32_t)(x) & USB_OTG_CTRL0_OTG_UTMI_SUSPENDM_SW_MASK) >> USB_OTG_CTRL0_OTG_UTMI_SUSPENDM_SW_SHIFT)

/*
 * OTG_UTMI_RESET_SW (RW)
 *
 * default 1 for naneng usbphy
 */
#define USB_OTG_CTRL0_OTG_UTMI_RESET_SW_MASK (0x800U)
#define USB_OTG_CTRL0_OTG_UTMI_RESET_SW_SHIFT (11U)
#define USB_OTG_CTRL0_OTG_UTMI_RESET_SW_SET(x) (((uint32_t)(x) << USB_OTG_CTRL0_OTG_UTMI_RESET_SW_SHIFT) & USB_OTG_CTRL0_OTG_UTMI_RESET_SW_MASK)
#define USB_OTG_CTRL0_OTG_UTMI_RESET_SW_GET(x) (((uint32_t)(x) & USB_OTG_CTRL0_OTG_UTMI_RESET_SW_MASK) >> USB_OTG_CTRL0_OTG_UTMI_RESET_SW_SHIFT)

/*
 * OTG_WAKEUP_INT_ENABLE (RW)
 *
 */
#define USB_OTG_CTRL0_OTG_WAKEUP_INT_ENABLE_MASK (0x400U)
#define USB_OTG_CTRL0_OTG_WAKEUP_INT_ENABLE_SHIFT (10U)
#define USB_OTG_CTRL0_OTG_WAKEUP_INT_ENABLE_SET(x) (((uint32_t)(x) << USB_OTG_CTRL0_OTG_WAKEUP_INT_ENABLE_SHIFT) & USB_OTG_CTRL0_OTG_WAKEUP_INT_ENABLE_MASK)
#define USB_OTG_CTRL0_OTG_WAKEUP_INT_ENABLE_GET(x) (((uint32_t)(x) & USB_OTG_CTRL0_OTG_WAKEUP_INT_ENABLE_MASK) >> USB_OTG_CTRL0_OTG_WAKEUP_INT_ENABLE_SHIFT)

/*
 * OTG_POWER_MASK (RW)
 *
 */
#define USB_OTG_CTRL0_OTG_POWER_MASK_MASK (0x200U)
#define USB_OTG_CTRL0_OTG_POWER_MASK_SHIFT (9U)
#define USB_OTG_CTRL0_OTG_POWER_MASK_SET(x) (((uint32_t)(x) << USB_OTG_CTRL0_OTG_POWER_MASK_SHIFT) & USB_OTG_CTRL0_OTG_POWER_MASK_MASK)
#define USB_OTG_CTRL0_OTG_POWER_MASK_GET(x) (((uint32_t)(x) & USB_OTG_CTRL0_OTG_POWER_MASK_MASK) >> USB_OTG_CTRL0_OTG_POWER_MASK_SHIFT)

/*
 * OTG_OVER_CUR_POL (RW)
 *
 */
#define USB_OTG_CTRL0_OTG_OVER_CUR_POL_MASK (0x100U)
#define USB_OTG_CTRL0_OTG_OVER_CUR_POL_SHIFT (8U)
#define USB_OTG_CTRL0_OTG_OVER_CUR_POL_SET(x) (((uint32_t)(x) << USB_OTG_CTRL0_OTG_OVER_CUR_POL_SHIFT) & USB_OTG_CTRL0_OTG_OVER_CUR_POL_MASK)
#define USB_OTG_CTRL0_OTG_OVER_CUR_POL_GET(x) (((uint32_t)(x) & USB_OTG_CTRL0_OTG_OVER_CUR_POL_MASK) >> USB_OTG_CTRL0_OTG_OVER_CUR_POL_SHIFT)

/*
 * OTG_OVER_CUR_DIS (RW)
 *
 */
#define USB_OTG_CTRL0_OTG_OVER_CUR_DIS_MASK (0x80U)
#define USB_OTG_CTRL0_OTG_OVER_CUR_DIS_SHIFT (7U)
#define USB_OTG_CTRL0_OTG_OVER_CUR_DIS_SET(x) (((uint32_t)(x) << USB_OTG_CTRL0_OTG_OVER_CUR_DIS_SHIFT) & USB_OTG_CTRL0_OTG_OVER_CUR_DIS_MASK)
#define USB_OTG_CTRL0_OTG_OVER_CUR_DIS_GET(x) (((uint32_t)(x) & USB_OTG_CTRL0_OTG_OVER_CUR_DIS_MASK) >> USB_OTG_CTRL0_OTG_OVER_CUR_DIS_SHIFT)

/*
 * SER_MODE_SUSPEND_EN (RW)
 *
 * for naneng usbphy, only switch to serial mode when suspend
 */
#define USB_OTG_CTRL0_SER_MODE_SUSPEND_EN_MASK (0x10U)
#define USB_OTG_CTRL0_SER_MODE_SUSPEND_EN_SHIFT (4U)
#define USB_OTG_CTRL0_SER_MODE_SUSPEND_EN_SET(x) (((uint32_t)(x) << USB_OTG_CTRL0_SER_MODE_SUSPEND_EN_SHIFT) & USB_OTG_CTRL0_SER_MODE_SUSPEND_EN_MASK)
#define USB_OTG_CTRL0_SER_MODE_SUSPEND_EN_GET(x) (((uint32_t)(x) & USB_OTG_CTRL0_SER_MODE_SUSPEND_EN_MASK) >> USB_OTG_CTRL0_SER_MODE_SUSPEND_EN_SHIFT)

/* Bitfield definition for register: PHY_CTRL0 */
/*
 * GPIO_ID_SEL_N (RW)
 *
 */
#define USB_PHY_CTRL0_GPIO_ID_SEL_N_MASK (0x2000000UL)
#define USB_PHY_CTRL0_GPIO_ID_SEL_N_SHIFT (25U)
#define USB_PHY_CTRL0_GPIO_ID_SEL_N_SET(x) (((uint32_t)(x) << USB_PHY_CTRL0_GPIO_ID_SEL_N_SHIFT) & USB_PHY_CTRL0_GPIO_ID_SEL_N_MASK)
#define USB_PHY_CTRL0_GPIO_ID_SEL_N_GET(x) (((uint32_t)(x) & USB_PHY_CTRL0_GPIO_ID_SEL_N_MASK) >> USB_PHY_CTRL0_GPIO_ID_SEL_N_SHIFT)

/*
 * ID_DIG_OVERRIDE (RW)
 *
 */
#define USB_PHY_CTRL0_ID_DIG_OVERRIDE_MASK (0x4000U)
#define USB_PHY_CTRL0_ID_DIG_OVERRIDE_SHIFT (14U)
#define USB_PHY_CTRL0_ID_DIG_OVERRIDE_SET(x) (((uint32_t)(x) << USB_PHY_CTRL0_ID_DIG_OVERRIDE_SHIFT) & USB_PHY_CTRL0_ID_DIG_OVERRIDE_MASK)
#define USB_PHY_CTRL0_ID_DIG_OVERRIDE_GET(x) (((uint32_t)(x) & USB_PHY_CTRL0_ID_DIG_OVERRIDE_MASK) >> USB_PHY_CTRL0_ID_DIG_OVERRIDE_SHIFT)

/*
 * SESS_VALID_OVERRIDE (RW)
 *
 */
#define USB_PHY_CTRL0_SESS_VALID_OVERRIDE_MASK (0x2000U)
#define USB_PHY_CTRL0_SESS_VALID_OVERRIDE_SHIFT (13U)
#define USB_PHY_CTRL0_SESS_VALID_OVERRIDE_SET(x) (((uint32_t)(x) << USB_PHY_CTRL0_SESS_VALID_OVERRIDE_SHIFT) & USB_PHY_CTRL0_SESS_VALID_OVERRIDE_MASK)
#define USB_PHY_CTRL0_SESS_VALID_OVERRIDE_GET(x) (((uint32_t)(x) & USB_PHY_CTRL0_SESS_VALID_OVERRIDE_MASK) >> USB_PHY_CTRL0_SESS_VALID_OVERRIDE_SHIFT)

/*
 * VBUS_VALID_OVERRIDE (RW)
 *
 */
#define USB_PHY_CTRL0_VBUS_VALID_OVERRIDE_MASK (0x1000U)
#define USB_PHY_CTRL0_VBUS_VALID_OVERRIDE_SHIFT (12U)
#define USB_PHY_CTRL0_VBUS_VALID_OVERRIDE_SET(x) (((uint32_t)(x) << USB_PHY_CTRL0_VBUS_VALID_OVERRIDE_SHIFT) & USB_PHY_CTRL0_VBUS_VALID_OVERRIDE_MASK)
#define USB_PHY_CTRL0_VBUS_VALID_OVERRIDE_GET(x) (((uint32_t)(x) & USB_PHY_CTRL0_VBUS_VALID_OVERRIDE_MASK) >> USB_PHY_CTRL0_VBUS_VALID_OVERRIDE_SHIFT)

/*
 * ID_DIG_OVERRIDE_EN (RW)
 *
 */
#define USB_PHY_CTRL0_ID_DIG_OVERRIDE_EN_MASK (0x4U)
#define USB_PHY_CTRL0_ID_DIG_OVERRIDE_EN_SHIFT (2U)
#define USB_PHY_CTRL0_ID_DIG_OVERRIDE_EN_SET(x) (((uint32_t)(x) << USB_PHY_CTRL0_ID_DIG_OVERRIDE_EN_SHIFT) & USB_PHY_CTRL0_ID_DIG_OVERRIDE_EN_MASK)
#define USB_PHY_CTRL0_ID_DIG_OVERRIDE_EN_GET(x) (((uint32_t)(x) & USB_PHY_CTRL0_ID_DIG_OVERRIDE_EN_MASK) >> USB_PHY_CTRL0_ID_DIG_OVERRIDE_EN_SHIFT)

/*
 * SESS_VALID_OVERRIDE_EN (RW)
 *
 */
#define USB_PHY_CTRL0_SESS_VALID_OVERRIDE_EN_MASK (0x2U)
#define USB_PHY_CTRL0_SESS_VALID_OVERRIDE_EN_SHIFT (1U)
#define USB_PHY_CTRL0_SESS_VALID_OVERRIDE_EN_SET(x) (((uint32_t)(x) << USB_PHY_CTRL0_SESS_VALID_OVERRIDE_EN_SHIFT) & USB_PHY_CTRL0_SESS_VALID_OVERRIDE_EN_MASK)
#define USB_PHY_CTRL0_SESS_VALID_OVERRIDE_EN_GET(x) (((uint32_t)(x) & USB_PHY_CTRL0_SESS_VALID_OVERRIDE_EN_MASK) >> USB_PHY_CTRL0_SESS_VALID_OVERRIDE_EN_SHIFT)

/*
 * VBUS_VALID_OVERRIDE_EN (RW)
 *
 */
#define USB_PHY_CTRL0_VBUS_VALID_OVERRIDE_EN_MASK (0x1U)
#define USB_PHY_CTRL0_VBUS_VALID_OVERRIDE_EN_SHIFT (0U)
#define USB_PHY_CTRL0_VBUS_VALID_OVERRIDE_EN_SET(x) (((uint32_t)(x) << USB_PHY_CTRL0_VBUS_VALID_OVERRIDE_EN_SHIFT) & USB_PHY_CTRL0_VBUS_VALID_OVERRIDE_EN_MASK)
#define USB_PHY_CTRL0_VBUS_VALID_OVERRIDE_EN_GET(x) (((uint32_t)(x) & USB_PHY_CTRL0_VBUS_VALID_OVERRIDE_EN_MASK) >> USB_PHY_CTRL0_VBUS_VALID_OVERRIDE_EN_SHIFT)

/* Bitfield definition for register: PHY_CTRL1 */
/*
 * UTMI_CFG_RST_N (RW)
 *
 */
#define USB_PHY_CTRL1_UTMI_CFG_RST_N_MASK (0x100000UL)
#define USB_PHY_CTRL1_UTMI_CFG_RST_N_SHIFT (20U)
#define USB_PHY_CTRL1_UTMI_CFG_RST_N_SET(x) (((uint32_t)(x) << USB_PHY_CTRL1_UTMI_CFG_RST_N_SHIFT) & USB_PHY_CTRL1_UTMI_CFG_RST_N_MASK)
#define USB_PHY_CTRL1_UTMI_CFG_RST_N_GET(x) (((uint32_t)(x) & USB_PHY_CTRL1_UTMI_CFG_RST_N_MASK) >> USB_PHY_CTRL1_UTMI_CFG_RST_N_SHIFT)

/*
 * UTMI_OTG_SUSPENDM (RW)
 *
 * OTG suspend, not utmi_suspendm
 */
#define USB_PHY_CTRL1_UTMI_OTG_SUSPENDM_MASK (0x2U)
#define USB_PHY_CTRL1_UTMI_OTG_SUSPENDM_SHIFT (1U)
#define USB_PHY_CTRL1_UTMI_OTG_SUSPENDM_SET(x) (((uint32_t)(x) << USB_PHY_CTRL1_UTMI_OTG_SUSPENDM_SHIFT) & USB_PHY_CTRL1_UTMI_OTG_SUSPENDM_MASK)
#define USB_PHY_CTRL1_UTMI_OTG_SUSPENDM_GET(x) (((uint32_t)(x) & USB_PHY_CTRL1_UTMI_OTG_SUSPENDM_MASK) >> USB_PHY_CTRL1_UTMI_OTG_SUSPENDM_SHIFT)

/* Bitfield definition for register: TOP_STATUS */
/*
 * WAKEUP_INT_STATUS (RW)
 *
 */
#define USB_TOP_STATUS_WAKEUP_INT_STATUS_MASK (0x80000000UL)
#define USB_TOP_STATUS_WAKEUP_INT_STATUS_SHIFT (31U)
#define USB_TOP_STATUS_WAKEUP_INT_STATUS_SET(x) (((uint32_t)(x) << USB_TOP_STATUS_WAKEUP_INT_STATUS_SHIFT) & USB_TOP_STATUS_WAKEUP_INT_STATUS_MASK)
#define USB_TOP_STATUS_WAKEUP_INT_STATUS_GET(x) (((uint32_t)(x) & USB_TOP_STATUS_WAKEUP_INT_STATUS_MASK) >> USB_TOP_STATUS_WAKEUP_INT_STATUS_SHIFT)

/* Bitfield definition for register: PHY_STATUS */
/*
 * UTMI_CLK_VALID (RW)
 *
 */
#define USB_PHY_STATUS_UTMI_CLK_VALID_MASK (0x80000000UL)
#define USB_PHY_STATUS_UTMI_CLK_VALID_SHIFT (31U)
#define USB_PHY_STATUS_UTMI_CLK_VALID_SET(x) (((uint32_t)(x) << USB_PHY_STATUS_UTMI_CLK_VALID_SHIFT) & USB_PHY_STATUS_UTMI_CLK_VALID_MASK)
#define USB_PHY_STATUS_UTMI_CLK_VALID_GET(x) (((uint32_t)(x) & USB_PHY_STATUS_UTMI_CLK_VALID_MASK) >> USB_PHY_STATUS_UTMI_CLK_VALID_SHIFT)

/*
 * LINE_STATE (RW)
 *
 */
#define USB_PHY_STATUS_LINE_STATE_MASK (0xC0U)
#define USB_PHY_STATUS_LINE_STATE_SHIFT (6U)
#define USB_PHY_STATUS_LINE_STATE_SET(x) (((uint32_t)(x) << USB_PHY_STATUS_LINE_STATE_SHIFT) & USB_PHY_STATUS_LINE_STATE_MASK)
#define USB_PHY_STATUS_LINE_STATE_GET(x) (((uint32_t)(x) & USB_PHY_STATUS_LINE_STATE_MASK) >> USB_PHY_STATUS_LINE_STATE_SHIFT)

/*
 * HOST_DISCONNECT (RW)
 *
 */
#define USB_PHY_STATUS_HOST_DISCONNECT_MASK (0x20U)
#define USB_PHY_STATUS_HOST_DISCONNECT_SHIFT (5U)
#define USB_PHY_STATUS_HOST_DISCONNECT_SET(x) (((uint32_t)(x) << USB_PHY_STATUS_HOST_DISCONNECT_SHIFT) & USB_PHY_STATUS_HOST_DISCONNECT_MASK)
#define USB_PHY_STATUS_HOST_DISCONNECT_GET(x) (((uint32_t)(x) & USB_PHY_STATUS_HOST_DISCONNECT_MASK) >> USB_PHY_STATUS_HOST_DISCONNECT_SHIFT)

/*
 * ID_DIG (RW)
 *
 */
#define USB_PHY_STATUS_ID_DIG_MASK (0x10U)
#define USB_PHY_STATUS_ID_DIG_SHIFT (4U)
#define USB_PHY_STATUS_ID_DIG_SET(x) (((uint32_t)(x) << USB_PHY_STATUS_ID_DIG_SHIFT) & USB_PHY_STATUS_ID_DIG_MASK)
#define USB_PHY_STATUS_ID_DIG_GET(x) (((uint32_t)(x) & USB_PHY_STATUS_ID_DIG_MASK) >> USB_PHY_STATUS_ID_DIG_SHIFT)

/*
 * UTMI_SESS_VALID (RW)
 *
 */
#define USB_PHY_STATUS_UTMI_SESS_VALID_MASK (0x4U)
#define USB_PHY_STATUS_UTMI_SESS_VALID_SHIFT (2U)
#define USB_PHY_STATUS_UTMI_SESS_VALID_SET(x) (((uint32_t)(x) << USB_PHY_STATUS_UTMI_SESS_VALID_SHIFT) & USB_PHY_STATUS_UTMI_SESS_VALID_MASK)
#define USB_PHY_STATUS_UTMI_SESS_VALID_GET(x) (((uint32_t)(x) & USB_PHY_STATUS_UTMI_SESS_VALID_MASK) >> USB_PHY_STATUS_UTMI_SESS_VALID_SHIFT)

/*
 * VBUS_VALID (RW)
 *
 */
#define USB_PHY_STATUS_VBUS_VALID_MASK (0x1U)
#define USB_PHY_STATUS_VBUS_VALID_SHIFT (0U)
#define USB_PHY_STATUS_VBUS_VALID_SET(x) (((uint32_t)(x) << USB_PHY_STATUS_VBUS_VALID_SHIFT) & USB_PHY_STATUS_VBUS_VALID_MASK)
#define USB_PHY_STATUS_VBUS_VALID_GET(x) (((uint32_t)(x) & USB_PHY_STATUS_VBUS_VALID_MASK) >> USB_PHY_STATUS_VBUS_VALID_SHIFT)



/* ENDPTCTRL register group index macro definition */
#define USB_ENDPTCTRL_ENDPTCTRL0 (0UL)
#define USB_ENDPTCTRL_ENDPTCTRL1 (1UL)
#define USB_ENDPTCTRL_ENDPTCTRL2 (2UL)
#define USB_ENDPTCTRL_ENDPTCTRL3 (3UL)
#define USB_ENDPTCTRL_ENDPTCTRL4 (4UL)
#define USB_ENDPTCTRL_ENDPTCTRL5 (5UL)
#define USB_ENDPTCTRL_ENDPTCTRL6 (6UL)
#define USB_ENDPTCTRL_ENDPTCTRL7 (7UL)


#endif /* HPM_USB_H */
