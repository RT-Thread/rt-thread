/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_DMA_H
#define HPM_DMA_H

typedef struct {
    __R  uint8_t  RESERVED0[16];               /* 0x0 - 0xF: Reserved */
    __R  uint32_t DMACFG;                      /* 0x10: DMAC Configuration Register */
    __R  uint8_t  RESERVED1[12];               /* 0x14 - 0x1F: Reserved */
    __W  uint32_t DMACTRL;                     /* 0x20: DMAC Control Register */
    __W  uint32_t CHABORT;                     /* 0x24: Channel Abort Register */
    __R  uint8_t  RESERVED2[8];                /* 0x28 - 0x2F: Reserved */
    __W  uint32_t INTSTATUS;                   /* 0x30: Interrupt Status Register */
    __R  uint32_t CHEN;                        /* 0x34: Channel Enable Register */
    __R  uint8_t  RESERVED3[8];                /* 0x38 - 0x3F: Reserved */
    struct {
        __RW uint32_t CTRL;                    /* 0x40: Channel n Control Register */
        __RW uint32_t TRANSIZE;                /* 0x44: Channel n Transfer Size Register */
        __RW uint32_t SRCADDR;                 /* 0x48: Channel n Source Address Low Part Register */
        __RW uint32_t SRCADDRH;                /* 0x4C: Channel n Source Address High Part Register */
        __RW uint32_t DSTADDR;                 /* 0x50: Channel n Destination Address Low Part Register */
        __RW uint32_t DSTADDRH;                /* 0x54: Channel n Destination Address High Part Register */
        __RW uint32_t LLPOINTER;               /* 0x58: Channel n Linked List Pointer Low Part Register */
        __RW uint32_t LLPOINTERH;              /* 0x5C: Channel n Linked List Pointer High Part Register */
    } CHCTRL[8];
} DMA_Type;


/* Bitfield definition for register: DMACFG */
/*
 * CHAINXFR (RO)
 *
 * Chain transfer
 * 0x0: Chain transfer is not configured
 * 0x1: Chain transfer is configured
 */
#define DMA_DMACFG_CHAINXFR_MASK (0x80000000UL)
#define DMA_DMACFG_CHAINXFR_SHIFT (31U)
#define DMA_DMACFG_CHAINXFR_GET(x) (((uint32_t)(x) & DMA_DMACFG_CHAINXFR_MASK) >> DMA_DMACFG_CHAINXFR_SHIFT)

/*
 * REQSYNC (RO)
 *
 * DMA request synchronization. The DMA request synchronization should be configured to avoid signal integrity problems when the request signal is not clocked by the system bus clock, which the DMA control logic operates in. If the request synchronization is not configured, the request signal is sampled directly without synchronization.
 * 0x0: Request synchronization is not configured
 * 0x1: Request synchronization is configured
 */
#define DMA_DMACFG_REQSYNC_MASK (0x40000000UL)
#define DMA_DMACFG_REQSYNC_SHIFT (30U)
#define DMA_DMACFG_REQSYNC_GET(x) (((uint32_t)(x) & DMA_DMACFG_REQSYNC_MASK) >> DMA_DMACFG_REQSYNC_SHIFT)

/*
 * DATAWIDTH (RO)
 *
 * AXI bus data width
 * 0x0: 32 bits
 * 0x1: 64 bits
 * 0x2: 128 bits
 * 0x3: 256 bits
 */
#define DMA_DMACFG_DATAWIDTH_MASK (0x3000000UL)
#define DMA_DMACFG_DATAWIDTH_SHIFT (24U)
#define DMA_DMACFG_DATAWIDTH_GET(x) (((uint32_t)(x) & DMA_DMACFG_DATAWIDTH_MASK) >> DMA_DMACFG_DATAWIDTH_SHIFT)

/*
 * ADDRWIDTH (RO)
 *
 * AXI bus address width
 * 0x18: 24 bits
 * 0x19: 25 bits
 * ...
 * 0x40: 64 bits
 * Others: Invalid
 */
#define DMA_DMACFG_ADDRWIDTH_MASK (0xFE0000UL)
#define DMA_DMACFG_ADDRWIDTH_SHIFT (17U)
#define DMA_DMACFG_ADDRWIDTH_GET(x) (((uint32_t)(x) & DMA_DMACFG_ADDRWIDTH_MASK) >> DMA_DMACFG_ADDRWIDTH_SHIFT)

/*
 * CORENUM (RO)
 *
 * DMA core number
 * 0x0: 1 core
 * 0x1: 2 cores
 */
#define DMA_DMACFG_CORENUM_MASK (0x10000UL)
#define DMA_DMACFG_CORENUM_SHIFT (16U)
#define DMA_DMACFG_CORENUM_GET(x) (((uint32_t)(x) & DMA_DMACFG_CORENUM_MASK) >> DMA_DMACFG_CORENUM_SHIFT)

/*
 * BUSNUM (RO)
 *
 * AXI bus interface number
 * 0x0: 1 AXI bus
 * 0x1: 2 AXI busses
 */
#define DMA_DMACFG_BUSNUM_MASK (0x8000U)
#define DMA_DMACFG_BUSNUM_SHIFT (15U)
#define DMA_DMACFG_BUSNUM_GET(x) (((uint32_t)(x) & DMA_DMACFG_BUSNUM_MASK) >> DMA_DMACFG_BUSNUM_SHIFT)

/*
 * REQNUM (RO)
 *
 * Request/acknowledge pair number
 * 0x0: 0 pair
 * 0x1: 1 pair
 * 0x2: 2 pairs
 * ...
 * 0x10: 16 pairs
 */
#define DMA_DMACFG_REQNUM_MASK (0x7C00U)
#define DMA_DMACFG_REQNUM_SHIFT (10U)
#define DMA_DMACFG_REQNUM_GET(x) (((uint32_t)(x) & DMA_DMACFG_REQNUM_MASK) >> DMA_DMACFG_REQNUM_SHIFT)

/*
 * FIFODEPTH (RO)
 *
 * FIFO depth
 * 0x4: 4 entries
 * 0x8: 8 entries
 * 0x10: 16 entries
 * 0x20: 32 entries
 * Others: Invalid
 */
#define DMA_DMACFG_FIFODEPTH_MASK (0x3F0U)
#define DMA_DMACFG_FIFODEPTH_SHIFT (4U)
#define DMA_DMACFG_FIFODEPTH_GET(x) (((uint32_t)(x) & DMA_DMACFG_FIFODEPTH_MASK) >> DMA_DMACFG_FIFODEPTH_SHIFT)

/*
 * CHANNELNUM (RO)
 *
 * Channel number
 * 0x1: 1 channel
 * 0x2: 2 channels
 * ...
 * 0x8: 8 channels
 * Others: Invalid
 */
#define DMA_DMACFG_CHANNELNUM_MASK (0xFU)
#define DMA_DMACFG_CHANNELNUM_SHIFT (0U)
#define DMA_DMACFG_CHANNELNUM_GET(x) (((uint32_t)(x) & DMA_DMACFG_CHANNELNUM_MASK) >> DMA_DMACFG_CHANNELNUM_SHIFT)

/* Bitfield definition for register: DMACTRL */
/*
 * RESET (WO)
 *
 * Software reset control. Write 1 to this bit to reset the DMA core and disable all channels.
 * Note: The software reset may cause the in-completion of AXI transaction.
 */
#define DMA_DMACTRL_RESET_MASK (0x1U)
#define DMA_DMACTRL_RESET_SHIFT (0U)
#define DMA_DMACTRL_RESET_SET(x) (((uint32_t)(x) << DMA_DMACTRL_RESET_SHIFT) & DMA_DMACTRL_RESET_MASK)
#define DMA_DMACTRL_RESET_GET(x) (((uint32_t)(x) & DMA_DMACTRL_RESET_MASK) >> DMA_DMACTRL_RESET_SHIFT)

/* Bitfield definition for register: CHABORT */
/*
 * CHABORT (WO)
 *
 * Write 1 to bit n to abort channel n. The bits should only be set when the corresponding channels are enabled. Otherwise, the writes will be ignored for channels that are not enabled. (N: Number of channels)
 */
#define DMA_CHABORT_CHABORT_MASK (0xFFFFFFFFUL)
#define DMA_CHABORT_CHABORT_SHIFT (0U)
#define DMA_CHABORT_CHABORT_SET(x) (((uint32_t)(x) << DMA_CHABORT_CHABORT_SHIFT) & DMA_CHABORT_CHABORT_MASK)
#define DMA_CHABORT_CHABORT_GET(x) (((uint32_t)(x) & DMA_CHABORT_CHABORT_MASK) >> DMA_CHABORT_CHABORT_SHIFT)

/* Bitfield definition for register: INTSTATUS */
/*
 * TC (W1C)
 *
 * The terminal count status, one bit per channel. The terminal count status is set when a channel transfer finishes without the abort or error event.
 * 0x0: Channel n has no terminal count status
 * 0x1: Channel n has terminal count status
 */
#define DMA_INTSTATUS_TC_MASK (0xFF0000UL)
#define DMA_INTSTATUS_TC_SHIFT (16U)
#define DMA_INTSTATUS_TC_SET(x) (((uint32_t)(x) << DMA_INTSTATUS_TC_SHIFT) & DMA_INTSTATUS_TC_MASK)
#define DMA_INTSTATUS_TC_GET(x) (((uint32_t)(x) & DMA_INTSTATUS_TC_MASK) >> DMA_INTSTATUS_TC_SHIFT)

/*
 * ABORT (W1C)
 *
 * The abort status of channel, one bit per channel. The abort status is set when a channel transfer is aborted.
 * 0x0: Channel n has no abort status
 * 0x1: Channel n has abort status
 */
#define DMA_INTSTATUS_ABORT_MASK (0xFF00U)
#define DMA_INTSTATUS_ABORT_SHIFT (8U)
#define DMA_INTSTATUS_ABORT_SET(x) (((uint32_t)(x) << DMA_INTSTATUS_ABORT_SHIFT) & DMA_INTSTATUS_ABORT_MASK)
#define DMA_INTSTATUS_ABORT_GET(x) (((uint32_t)(x) & DMA_INTSTATUS_ABORT_MASK) >> DMA_INTSTATUS_ABORT_SHIFT)

/*
 * ERROR (W1C)
 *
 * The error status, one bit per channel. The error status is set when a channel transfer encounters the following error events:
 * - Bus error
 * - Unaligned address
 * - Unaligned transfer width
 * - Reserved configuration
 * 0x0: Channel n has no error status
 * 0x1: Channel n has error status
 */
#define DMA_INTSTATUS_ERROR_MASK (0xFFU)
#define DMA_INTSTATUS_ERROR_SHIFT (0U)
#define DMA_INTSTATUS_ERROR_SET(x) (((uint32_t)(x) << DMA_INTSTATUS_ERROR_SHIFT) & DMA_INTSTATUS_ERROR_MASK)
#define DMA_INTSTATUS_ERROR_GET(x) (((uint32_t)(x) & DMA_INTSTATUS_ERROR_MASK) >> DMA_INTSTATUS_ERROR_SHIFT)

/* Bitfield definition for register: CHEN */
/*
 * CHEN (RO)
 *
 * Alias of the Enable field of all ChnCtrl registers
 */
#define DMA_CHEN_CHEN_MASK (0xFFFFFFFFUL)
#define DMA_CHEN_CHEN_SHIFT (0U)
#define DMA_CHEN_CHEN_GET(x) (((uint32_t)(x) & DMA_CHEN_CHEN_MASK) >> DMA_CHEN_CHEN_SHIFT)

/* Bitfield definition for register of struct array CHCTRL: CTRL */
/*
 * SRCBUSINFIDX (RW)
 *
 * Bus interface index that source data is read from
 * 0x0: Data is read from bus interface 0
 * 0x1: Data is read from bus interface
 */
#define DMA_CHCTRL_CTRL_SRCBUSINFIDX_MASK (0x80000000UL)
#define DMA_CHCTRL_CTRL_SRCBUSINFIDX_SHIFT (31U)
#define DMA_CHCTRL_CTRL_SRCBUSINFIDX_SET(x) (((uint32_t)(x) << DMA_CHCTRL_CTRL_SRCBUSINFIDX_SHIFT) & DMA_CHCTRL_CTRL_SRCBUSINFIDX_MASK)
#define DMA_CHCTRL_CTRL_SRCBUSINFIDX_GET(x) (((uint32_t)(x) & DMA_CHCTRL_CTRL_SRCBUSINFIDX_MASK) >> DMA_CHCTRL_CTRL_SRCBUSINFIDX_SHIFT)

/*
 * DSTBUSINFIDX (RW)
 *
 * Bus interface index that destination data is written to
 * 0x0: Data is written to bus interface 0
 * 0x1: Data is written to bus interface 1
 */
#define DMA_CHCTRL_CTRL_DSTBUSINFIDX_MASK (0x40000000UL)
#define DMA_CHCTRL_CTRL_DSTBUSINFIDX_SHIFT (30U)
#define DMA_CHCTRL_CTRL_DSTBUSINFIDX_SET(x) (((uint32_t)(x) << DMA_CHCTRL_CTRL_DSTBUSINFIDX_SHIFT) & DMA_CHCTRL_CTRL_DSTBUSINFIDX_MASK)
#define DMA_CHCTRL_CTRL_DSTBUSINFIDX_GET(x) (((uint32_t)(x) & DMA_CHCTRL_CTRL_DSTBUSINFIDX_MASK) >> DMA_CHCTRL_CTRL_DSTBUSINFIDX_SHIFT)

/*
 * PRIORITY (RW)
 *
 * Channel priority level
 * 0x0: Lower priority
 * 0x1: Higher priority
 */
#define DMA_CHCTRL_CTRL_PRIORITY_MASK (0x20000000UL)
#define DMA_CHCTRL_CTRL_PRIORITY_SHIFT (29U)
#define DMA_CHCTRL_CTRL_PRIORITY_SET(x) (((uint32_t)(x) << DMA_CHCTRL_CTRL_PRIORITY_SHIFT) & DMA_CHCTRL_CTRL_PRIORITY_MASK)
#define DMA_CHCTRL_CTRL_PRIORITY_GET(x) (((uint32_t)(x) & DMA_CHCTRL_CTRL_PRIORITY_MASK) >> DMA_CHCTRL_CTRL_PRIORITY_SHIFT)

/*
 * SRCBURSTSIZE (RW)
 *
 * Source burst size. This field indicates the number of transfers before DMA channel re-arbitration.
 * The burst transfer byte number is (SrcBurstSize * SrcWidth).
 * 0x0: 1 transfer
 * 0x1: 2 transfers
 * 0x2: 4 transfers
 * 0x3: 8 transfers
 * 0x4: 16 transfers
 * 0x5: 32 transfers
 * 0x6: 64 transfers
 * 0x7: 128 transfers
 * 0x8: 256 transfers
 * 0x9:512 transfers
 * 0xa: 1024 transfers
 * 0xb-0xf: Reserved, setting this field with a reserved value triggers the error exception
 * for XDMA, the maximum allowed value is 0xa; for HDMA, the maximum allowed value is 0x7
 */
#define DMA_CHCTRL_CTRL_SRCBURSTSIZE_MASK (0xF000000UL)
#define DMA_CHCTRL_CTRL_SRCBURSTSIZE_SHIFT (24U)
#define DMA_CHCTRL_CTRL_SRCBURSTSIZE_SET(x) (((uint32_t)(x) << DMA_CHCTRL_CTRL_SRCBURSTSIZE_SHIFT) & DMA_CHCTRL_CTRL_SRCBURSTSIZE_MASK)
#define DMA_CHCTRL_CTRL_SRCBURSTSIZE_GET(x) (((uint32_t)(x) & DMA_CHCTRL_CTRL_SRCBURSTSIZE_MASK) >> DMA_CHCTRL_CTRL_SRCBURSTSIZE_SHIFT)

/*
 * SRCWIDTH (RW)
 *
 * Source transfer width
 * 0x0: Byte transfer
 * 0x1: Half-word transfer
 * 0x2: Word transfer
 * 0x3: Double word transfer
 * 0x4: Quad word transfer
 * 0x5: Eight word transfer
 * 0x6-x7: Reserved, setting this field with a reserved value triggers the error exception
 * for XDMA, the maximum allowed value is 0x3, for HDMA, the maximum allowed value is 0x2
 */
#define DMA_CHCTRL_CTRL_SRCWIDTH_MASK (0xE00000UL)
#define DMA_CHCTRL_CTRL_SRCWIDTH_SHIFT (21U)
#define DMA_CHCTRL_CTRL_SRCWIDTH_SET(x) (((uint32_t)(x) << DMA_CHCTRL_CTRL_SRCWIDTH_SHIFT) & DMA_CHCTRL_CTRL_SRCWIDTH_MASK)
#define DMA_CHCTRL_CTRL_SRCWIDTH_GET(x) (((uint32_t)(x) & DMA_CHCTRL_CTRL_SRCWIDTH_MASK) >> DMA_CHCTRL_CTRL_SRCWIDTH_SHIFT)

/*
 * DSTWIDTH (RW)
 *
 * Destination transfer width.
 * Both the total transfer byte number and the burst transfer byte number should be aligned to the destination transfer width; otherwise the error event will be triggered. For example, destination transfer width should be set as byte transfer if total transfer byte is not aligned to half-word.
 * See field SrcBurstSize above for the definition of burst transfer byte number and section 3.2.8 for the definition of the total transfer byte number.
 * 0x0: Byte transfer
 * 0x1: Half-word transfer
 * 0x2: Word transfer
 * 0x3: Double word transfer
 * 0x4: Quad word transfer
 * 0x5: Eight word transfer
 * 0x6-x7: Reserved, setting this field with a reserved value triggers the error exception
 * for XDMA, the maximum allowed value is 0x3, for HDMA, the maximum allowed value is 0x2
 */
#define DMA_CHCTRL_CTRL_DSTWIDTH_MASK (0x1C0000UL)
#define DMA_CHCTRL_CTRL_DSTWIDTH_SHIFT (18U)
#define DMA_CHCTRL_CTRL_DSTWIDTH_SET(x) (((uint32_t)(x) << DMA_CHCTRL_CTRL_DSTWIDTH_SHIFT) & DMA_CHCTRL_CTRL_DSTWIDTH_MASK)
#define DMA_CHCTRL_CTRL_DSTWIDTH_GET(x) (((uint32_t)(x) & DMA_CHCTRL_CTRL_DSTWIDTH_MASK) >> DMA_CHCTRL_CTRL_DSTWIDTH_SHIFT)

/*
 * SRCMODE (RW)
 *
 * Source DMA handshake mode
 * 0x0: Normal mode
 * 0x1: Handshake mode
 */
#define DMA_CHCTRL_CTRL_SRCMODE_MASK (0x20000UL)
#define DMA_CHCTRL_CTRL_SRCMODE_SHIFT (17U)
#define DMA_CHCTRL_CTRL_SRCMODE_SET(x) (((uint32_t)(x) << DMA_CHCTRL_CTRL_SRCMODE_SHIFT) & DMA_CHCTRL_CTRL_SRCMODE_MASK)
#define DMA_CHCTRL_CTRL_SRCMODE_GET(x) (((uint32_t)(x) & DMA_CHCTRL_CTRL_SRCMODE_MASK) >> DMA_CHCTRL_CTRL_SRCMODE_SHIFT)

/*
 * DSTMODE (RW)
 *
 * Destination DMA handshake mode
 * 0x0: Normal mode
 * 0x1: Handshake mode
 */
#define DMA_CHCTRL_CTRL_DSTMODE_MASK (0x10000UL)
#define DMA_CHCTRL_CTRL_DSTMODE_SHIFT (16U)
#define DMA_CHCTRL_CTRL_DSTMODE_SET(x) (((uint32_t)(x) << DMA_CHCTRL_CTRL_DSTMODE_SHIFT) & DMA_CHCTRL_CTRL_DSTMODE_MASK)
#define DMA_CHCTRL_CTRL_DSTMODE_GET(x) (((uint32_t)(x) & DMA_CHCTRL_CTRL_DSTMODE_MASK) >> DMA_CHCTRL_CTRL_DSTMODE_SHIFT)

/*
 * SRCADDRCTRL (RW)
 *
 * Source address control
 * 0x0: Increment address
 * 0x1: Decrement address
 * 0x2: Fixed address
 * 0x3: Reserved, setting the field with this value triggers the error exception
 */
#define DMA_CHCTRL_CTRL_SRCADDRCTRL_MASK (0xC000U)
#define DMA_CHCTRL_CTRL_SRCADDRCTRL_SHIFT (14U)
#define DMA_CHCTRL_CTRL_SRCADDRCTRL_SET(x) (((uint32_t)(x) << DMA_CHCTRL_CTRL_SRCADDRCTRL_SHIFT) & DMA_CHCTRL_CTRL_SRCADDRCTRL_MASK)
#define DMA_CHCTRL_CTRL_SRCADDRCTRL_GET(x) (((uint32_t)(x) & DMA_CHCTRL_CTRL_SRCADDRCTRL_MASK) >> DMA_CHCTRL_CTRL_SRCADDRCTRL_SHIFT)

/*
 * DSTADDRCTRL (RW)
 *
 * Destination address control
 * 0x0: Increment address
 * 0x1: Decrement address
 * 0x2: Fixed address
 * 0x3: Reserved, setting the field with this value triggers the error exception
 */
#define DMA_CHCTRL_CTRL_DSTADDRCTRL_MASK (0x3000U)
#define DMA_CHCTRL_CTRL_DSTADDRCTRL_SHIFT (12U)
#define DMA_CHCTRL_CTRL_DSTADDRCTRL_SET(x) (((uint32_t)(x) << DMA_CHCTRL_CTRL_DSTADDRCTRL_SHIFT) & DMA_CHCTRL_CTRL_DSTADDRCTRL_MASK)
#define DMA_CHCTRL_CTRL_DSTADDRCTRL_GET(x) (((uint32_t)(x) & DMA_CHCTRL_CTRL_DSTADDRCTRL_MASK) >> DMA_CHCTRL_CTRL_DSTADDRCTRL_SHIFT)

/*
 * SRCREQSEL (RW)
 *
 * Source DMA request select. Select the request/ack handshake pair that the source device is connected to.
 */
#define DMA_CHCTRL_CTRL_SRCREQSEL_MASK (0xF00U)
#define DMA_CHCTRL_CTRL_SRCREQSEL_SHIFT (8U)
#define DMA_CHCTRL_CTRL_SRCREQSEL_SET(x) (((uint32_t)(x) << DMA_CHCTRL_CTRL_SRCREQSEL_SHIFT) & DMA_CHCTRL_CTRL_SRCREQSEL_MASK)
#define DMA_CHCTRL_CTRL_SRCREQSEL_GET(x) (((uint32_t)(x) & DMA_CHCTRL_CTRL_SRCREQSEL_MASK) >> DMA_CHCTRL_CTRL_SRCREQSEL_SHIFT)

/*
 * DSTREQSEL (RW)
 *
 * Destination DMA request select. Select the request/ack handshake pair that the destination device is connected to.
 */
#define DMA_CHCTRL_CTRL_DSTREQSEL_MASK (0xF0U)
#define DMA_CHCTRL_CTRL_DSTREQSEL_SHIFT (4U)
#define DMA_CHCTRL_CTRL_DSTREQSEL_SET(x) (((uint32_t)(x) << DMA_CHCTRL_CTRL_DSTREQSEL_SHIFT) & DMA_CHCTRL_CTRL_DSTREQSEL_MASK)
#define DMA_CHCTRL_CTRL_DSTREQSEL_GET(x) (((uint32_t)(x) & DMA_CHCTRL_CTRL_DSTREQSEL_MASK) >> DMA_CHCTRL_CTRL_DSTREQSEL_SHIFT)

/*
 * INTABTMASK (RW)
 *
 * Channel abort interrupt mask
 * 0x0: Allow the abort interrupt to be triggered
 * 0x1: Disable the abort interrupt
 */
#define DMA_CHCTRL_CTRL_INTABTMASK_MASK (0x8U)
#define DMA_CHCTRL_CTRL_INTABTMASK_SHIFT (3U)
#define DMA_CHCTRL_CTRL_INTABTMASK_SET(x) (((uint32_t)(x) << DMA_CHCTRL_CTRL_INTABTMASK_SHIFT) & DMA_CHCTRL_CTRL_INTABTMASK_MASK)
#define DMA_CHCTRL_CTRL_INTABTMASK_GET(x) (((uint32_t)(x) & DMA_CHCTRL_CTRL_INTABTMASK_MASK) >> DMA_CHCTRL_CTRL_INTABTMASK_SHIFT)

/*
 * INTERRMASK (RW)
 *
 * Channel error interrupt mask
 * 0x0: Allow the error interrupt to be triggered
 * 0x1: Disable the error interrupt
 */
#define DMA_CHCTRL_CTRL_INTERRMASK_MASK (0x4U)
#define DMA_CHCTRL_CTRL_INTERRMASK_SHIFT (2U)
#define DMA_CHCTRL_CTRL_INTERRMASK_SET(x) (((uint32_t)(x) << DMA_CHCTRL_CTRL_INTERRMASK_SHIFT) & DMA_CHCTRL_CTRL_INTERRMASK_MASK)
#define DMA_CHCTRL_CTRL_INTERRMASK_GET(x) (((uint32_t)(x) & DMA_CHCTRL_CTRL_INTERRMASK_MASK) >> DMA_CHCTRL_CTRL_INTERRMASK_SHIFT)

/*
 * INTTCMASK (RW)
 *
 * Channel terminal count interrupt mask
 * 0x0: Allow the terminal count interrupt to be triggered
 * 0x1: Disable the terminal count interrupt
 */
#define DMA_CHCTRL_CTRL_INTTCMASK_MASK (0x2U)
#define DMA_CHCTRL_CTRL_INTTCMASK_SHIFT (1U)
#define DMA_CHCTRL_CTRL_INTTCMASK_SET(x) (((uint32_t)(x) << DMA_CHCTRL_CTRL_INTTCMASK_SHIFT) & DMA_CHCTRL_CTRL_INTTCMASK_MASK)
#define DMA_CHCTRL_CTRL_INTTCMASK_GET(x) (((uint32_t)(x) & DMA_CHCTRL_CTRL_INTTCMASK_MASK) >> DMA_CHCTRL_CTRL_INTTCMASK_SHIFT)

/*
 * ENABLE (RW)
 *
 * Channel enable bit
 * 0x0: Disable
 * 0x1: Enable
 */
#define DMA_CHCTRL_CTRL_ENABLE_MASK (0x1U)
#define DMA_CHCTRL_CTRL_ENABLE_SHIFT (0U)
#define DMA_CHCTRL_CTRL_ENABLE_SET(x) (((uint32_t)(x) << DMA_CHCTRL_CTRL_ENABLE_SHIFT) & DMA_CHCTRL_CTRL_ENABLE_MASK)
#define DMA_CHCTRL_CTRL_ENABLE_GET(x) (((uint32_t)(x) & DMA_CHCTRL_CTRL_ENABLE_MASK) >> DMA_CHCTRL_CTRL_ENABLE_SHIFT)

/* Bitfield definition for register of struct array CHCTRL: TRANSIZE */
/*
 * TRANSIZE (RW)
 *
 * Total transfer size from source. The total number of transferred bytes is (TranSize * SrcWidth). This register is cleared when the DMA transfer is done.
 * If a channel is enabled with zero total transfer size, the error event will be triggered and the transfer will be terminated.
 */
#define DMA_CHCTRL_TRANSIZE_TRANSIZE_MASK (0xFFFFFFFFUL)
#define DMA_CHCTRL_TRANSIZE_TRANSIZE_SHIFT (0U)
#define DMA_CHCTRL_TRANSIZE_TRANSIZE_SET(x) (((uint32_t)(x) << DMA_CHCTRL_TRANSIZE_TRANSIZE_SHIFT) & DMA_CHCTRL_TRANSIZE_TRANSIZE_MASK)
#define DMA_CHCTRL_TRANSIZE_TRANSIZE_GET(x) (((uint32_t)(x) & DMA_CHCTRL_TRANSIZE_TRANSIZE_MASK) >> DMA_CHCTRL_TRANSIZE_TRANSIZE_SHIFT)

/* Bitfield definition for register of struct array CHCTRL: SRCADDR */
/*
 * SRCADDRL (RW)
 *
 * Low part of the source starting address. When the transfer completes, the value of {SrcAddrH,SrcAddrL} is updated to the ending address.
 * This address must be aligned to the source transfer size; otherwise, an error event will be triggered.
 */
#define DMA_CHCTRL_SRCADDR_SRCADDRL_MASK (0xFFFFFFFFUL)
#define DMA_CHCTRL_SRCADDR_SRCADDRL_SHIFT (0U)
#define DMA_CHCTRL_SRCADDR_SRCADDRL_SET(x) (((uint32_t)(x) << DMA_CHCTRL_SRCADDR_SRCADDRL_SHIFT) & DMA_CHCTRL_SRCADDR_SRCADDRL_MASK)
#define DMA_CHCTRL_SRCADDR_SRCADDRL_GET(x) (((uint32_t)(x) & DMA_CHCTRL_SRCADDR_SRCADDRL_MASK) >> DMA_CHCTRL_SRCADDR_SRCADDRL_SHIFT)

/* Bitfield definition for register of struct array CHCTRL: SRCADDRH */
/*
 * SRCADDRH (RW)
 *
 * High part of the source starting address. When the transfer completes, the value of {SrcAddrH,SrcAddrL} is updated to the ending address.
 * This register exists only when the address bus width is wider than 32 bits.
 */
#define DMA_CHCTRL_SRCADDRH_SRCADDRH_MASK (0xFFFFFFFFUL)
#define DMA_CHCTRL_SRCADDRH_SRCADDRH_SHIFT (0U)
#define DMA_CHCTRL_SRCADDRH_SRCADDRH_SET(x) (((uint32_t)(x) << DMA_CHCTRL_SRCADDRH_SRCADDRH_SHIFT) & DMA_CHCTRL_SRCADDRH_SRCADDRH_MASK)
#define DMA_CHCTRL_SRCADDRH_SRCADDRH_GET(x) (((uint32_t)(x) & DMA_CHCTRL_SRCADDRH_SRCADDRH_MASK) >> DMA_CHCTRL_SRCADDRH_SRCADDRH_SHIFT)

/* Bitfield definition for register of struct array CHCTRL: DSTADDR */
/*
 * DSTADDRL (RW)
 *
 * Low part of the destination starting address. When the transfer completes, the value of {DstAddrH,DstAddrL} is updated to the ending address.
 * This address must be aligned to the destination transfer size; otherwise the error event will be triggered.
 */
#define DMA_CHCTRL_DSTADDR_DSTADDRL_MASK (0xFFFFFFFFUL)
#define DMA_CHCTRL_DSTADDR_DSTADDRL_SHIFT (0U)
#define DMA_CHCTRL_DSTADDR_DSTADDRL_SET(x) (((uint32_t)(x) << DMA_CHCTRL_DSTADDR_DSTADDRL_SHIFT) & DMA_CHCTRL_DSTADDR_DSTADDRL_MASK)
#define DMA_CHCTRL_DSTADDR_DSTADDRL_GET(x) (((uint32_t)(x) & DMA_CHCTRL_DSTADDR_DSTADDRL_MASK) >> DMA_CHCTRL_DSTADDR_DSTADDRL_SHIFT)

/* Bitfield definition for register of struct array CHCTRL: DSTADDRH */
/*
 * DSTADDRH (RW)
 *
 * High part of the destination starting address. When the transfer completes, the value of {DstAddrH,DstAddrL} is updated to the ending address.
 * This address must be aligned to the destination transfer size; otherwise the error event will be triggered.
 * This register exists only when the address bus width is wider than 32 bits.
 */
#define DMA_CHCTRL_DSTADDRH_DSTADDRH_MASK (0xFFFFFFFFUL)
#define DMA_CHCTRL_DSTADDRH_DSTADDRH_SHIFT (0U)
#define DMA_CHCTRL_DSTADDRH_DSTADDRH_SET(x) (((uint32_t)(x) << DMA_CHCTRL_DSTADDRH_DSTADDRH_SHIFT) & DMA_CHCTRL_DSTADDRH_DSTADDRH_MASK)
#define DMA_CHCTRL_DSTADDRH_DSTADDRH_GET(x) (((uint32_t)(x) & DMA_CHCTRL_DSTADDRH_DSTADDRH_MASK) >> DMA_CHCTRL_DSTADDRH_DSTADDRH_SHIFT)

/* Bitfield definition for register of struct array CHCTRL: LLPOINTER */
/*
 * LLPOINTERL (RW)
 *
 * Low part of the pointer to the next descriptor. The pointer must be double word aligned.
 */
#define DMA_CHCTRL_LLPOINTER_LLPOINTERL_MASK (0xFFFFFFF8UL)
#define DMA_CHCTRL_LLPOINTER_LLPOINTERL_SHIFT (3U)
#define DMA_CHCTRL_LLPOINTER_LLPOINTERL_SET(x) (((uint32_t)(x) << DMA_CHCTRL_LLPOINTER_LLPOINTERL_SHIFT) & DMA_CHCTRL_LLPOINTER_LLPOINTERL_MASK)
#define DMA_CHCTRL_LLPOINTER_LLPOINTERL_GET(x) (((uint32_t)(x) & DMA_CHCTRL_LLPOINTER_LLPOINTERL_MASK) >> DMA_CHCTRL_LLPOINTER_LLPOINTERL_SHIFT)

/*
 * LLDBUSINFIDX (RW)
 *
 * Bus interface index that the next descriptor is read from
 * 0x0: The next descriptor is read from bus interface 0
 */
#define DMA_CHCTRL_LLPOINTER_LLDBUSINFIDX_MASK (0x1U)
#define DMA_CHCTRL_LLPOINTER_LLDBUSINFIDX_SHIFT (0U)
#define DMA_CHCTRL_LLPOINTER_LLDBUSINFIDX_SET(x) (((uint32_t)(x) << DMA_CHCTRL_LLPOINTER_LLDBUSINFIDX_SHIFT) & DMA_CHCTRL_LLPOINTER_LLDBUSINFIDX_MASK)
#define DMA_CHCTRL_LLPOINTER_LLDBUSINFIDX_GET(x) (((uint32_t)(x) & DMA_CHCTRL_LLPOINTER_LLDBUSINFIDX_MASK) >> DMA_CHCTRL_LLPOINTER_LLDBUSINFIDX_SHIFT)

/* Bitfield definition for register of struct array CHCTRL: LLPOINTERH */
/*
 * LLPOINTERH (RW)
 *
 * High part of the pointer to the next descriptor.
 * This register exists only when the address bus width is wider than 32 bits.
 */
#define DMA_CHCTRL_LLPOINTERH_LLPOINTERH_MASK (0xFFFFFFFFUL)
#define DMA_CHCTRL_LLPOINTERH_LLPOINTERH_SHIFT (0U)
#define DMA_CHCTRL_LLPOINTERH_LLPOINTERH_SET(x) (((uint32_t)(x) << DMA_CHCTRL_LLPOINTERH_LLPOINTERH_SHIFT) & DMA_CHCTRL_LLPOINTERH_LLPOINTERH_MASK)
#define DMA_CHCTRL_LLPOINTERH_LLPOINTERH_GET(x) (((uint32_t)(x) & DMA_CHCTRL_LLPOINTERH_LLPOINTERH_MASK) >> DMA_CHCTRL_LLPOINTERH_LLPOINTERH_SHIFT)



/* CHCTRL register group index macro definition */
#define DMA_CHCTRL_CH0 (0UL)
#define DMA_CHCTRL_CH1 (1UL)
#define DMA_CHCTRL_CH2 (2UL)
#define DMA_CHCTRL_CH3 (3UL)
#define DMA_CHCTRL_CH4 (4UL)
#define DMA_CHCTRL_CH5 (5UL)
#define DMA_CHCTRL_CH6 (6UL)
#define DMA_CHCTRL_CH7 (7UL)


#endif /* HPM_DMA_H */
