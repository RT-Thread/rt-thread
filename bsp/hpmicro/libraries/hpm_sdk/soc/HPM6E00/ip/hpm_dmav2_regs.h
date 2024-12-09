/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_DMAV2_H
#define HPM_DMAV2_H

typedef struct {
    __R  uint8_t  RESERVED0[4];                /* 0x0 - 0x3: Reserved */
    __R  uint32_t IDMISC;                      /* 0x4: ID Misc */
    __R  uint8_t  RESERVED1[8];                /* 0x8 - 0xF: Reserved */
    __R  uint32_t DMACFG;                      /* 0x10: DMAC Configuration Register */
    __W  uint32_t DMACTRL;                     /* 0x14: DMAC Control Register */
    __W  uint32_t CHABORT;                     /* 0x18: Channel Abort Register */
    __R  uint8_t  RESERVED2[8];                /* 0x1C - 0x23: Reserved */
    __RW uint32_t INTHALFSTS;                  /* 0x24: Harlf Complete Interrupt Status */
    __W  uint32_t INTTCSTS;                    /* 0x28: Trans Complete Interrupt Status Register */
    __W  uint32_t INTABORTSTS;                 /* 0x2C: Abort Interrupt Status Register */
    __W  uint32_t INTERRSTS;                   /* 0x30: Error Interrupt Status Register */
    __R  uint32_t CHEN;                        /* 0x34: Channel Enable Register */
    __R  uint8_t  RESERVED3[8];                /* 0x38 - 0x3F: Reserved */
    struct {
        __RW uint32_t CTRL;                    /* 0x40: Channel  Control Register */
        __RW uint32_t TRANSIZE;                /* 0x44: Channel Transfer Size Register */
        __RW uint32_t SRCADDR;                 /* 0x48: Channel  Source Address Low Part Register */
        __RW uint32_t CHANREQCTRL;             /* 0x4C: Channel  DMA Request Control Register */
        __RW uint32_t DSTADDR;                 /* 0x50: Channel  Destination Address Low Part Register */
        __RW uint32_t SWAPTABLE;               /* 0x54: swap table register */
        __RW uint32_t LLPOINTER;               /* 0x58: Channel  Linked List Pointer Low Part Register */
        __R  uint8_t  RESERVED0[4];            /* 0x5C - 0x5F: Reserved */
    } CHCTRL[32];
} DMAV2_Type;


/* Bitfield definition for register: IDMISC */
/*
 * DMASTATE (RO)
 *
 * DMA state machine
 * localparam ST_IDLE  = 3'b000;
 * localparam ST_READ  = 3'b001;
 * localparam ST_READ_ACK = 3'b010;
 * localparam ST_WRITE = 3'b011;
 * localparam ST_WRITE_ACK = 3'b100;
 * localparam ST_LL  = 3'b101;
 * localparam ST_END  = 3'b110;
 * localparam ST_END_WAIT     = 3'b111;
 */
#define DMAV2_IDMISC_DMASTATE_MASK (0xE000U)
#define DMAV2_IDMISC_DMASTATE_SHIFT (13U)
#define DMAV2_IDMISC_DMASTATE_GET(x) (((uint32_t)(x) & DMAV2_IDMISC_DMASTATE_MASK) >> DMAV2_IDMISC_DMASTATE_SHIFT)

/*
 * CURCHAN (RO)
 *
 * current channel in used
 */
#define DMAV2_IDMISC_CURCHAN_MASK (0x1F00U)
#define DMAV2_IDMISC_CURCHAN_SHIFT (8U)
#define DMAV2_IDMISC_CURCHAN_GET(x) (((uint32_t)(x) & DMAV2_IDMISC_CURCHAN_MASK) >> DMAV2_IDMISC_CURCHAN_SHIFT)

/* Bitfield definition for register: DMACFG */
/*
 * CHAINXFR (RO)
 *
 * Chain transfer
 * 0x0: Chain transfer is not configured
 * 0x1: Chain transfer is configured
 */
#define DMAV2_DMACFG_CHAINXFR_MASK (0x80000000UL)
#define DMAV2_DMACFG_CHAINXFR_SHIFT (31U)
#define DMAV2_DMACFG_CHAINXFR_GET(x) (((uint32_t)(x) & DMAV2_DMACFG_CHAINXFR_MASK) >> DMAV2_DMACFG_CHAINXFR_SHIFT)

/*
 * REQSYNC (RO)
 *
 * DMA request synchronization.
 * The DMA request synchronization should be configured to avoid signal integrity problems when the request signal is not clocked by the system bus clock,
 * which the DMA control logic operates in. If the request synchronization is not configured, the request signal is sampled directly without synchronization.
 * 0x0: Request synchronization is not configured
 * 0x1: Request synchronization is configured
 */
#define DMAV2_DMACFG_REQSYNC_MASK (0x40000000UL)
#define DMAV2_DMACFG_REQSYNC_SHIFT (30U)
#define DMAV2_DMACFG_REQSYNC_GET(x) (((uint32_t)(x) & DMAV2_DMACFG_REQSYNC_MASK) >> DMAV2_DMACFG_REQSYNC_SHIFT)

/*
 * DATAWIDTH (RO)
 *
 * AXI bus data width
 * 0x0: 32 bits
 * 0x1: 64 bits
 * 0x2: 128 bits
 * 0x3: 256 bits
 */
#define DMAV2_DMACFG_DATAWIDTH_MASK (0x3000000UL)
#define DMAV2_DMACFG_DATAWIDTH_SHIFT (24U)
#define DMAV2_DMACFG_DATAWIDTH_GET(x) (((uint32_t)(x) & DMAV2_DMACFG_DATAWIDTH_MASK) >> DMAV2_DMACFG_DATAWIDTH_SHIFT)

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
#define DMAV2_DMACFG_ADDRWIDTH_MASK (0xFE0000UL)
#define DMAV2_DMACFG_ADDRWIDTH_SHIFT (17U)
#define DMAV2_DMACFG_ADDRWIDTH_GET(x) (((uint32_t)(x) & DMAV2_DMACFG_ADDRWIDTH_MASK) >> DMAV2_DMACFG_ADDRWIDTH_SHIFT)

/*
 * CORENUM (RO)
 *
 * DMA core number
 * 0x0: 1 core
 * 0x1: 2 cores
 */
#define DMAV2_DMACFG_CORENUM_MASK (0x10000UL)
#define DMAV2_DMACFG_CORENUM_SHIFT (16U)
#define DMAV2_DMACFG_CORENUM_GET(x) (((uint32_t)(x) & DMAV2_DMACFG_CORENUM_MASK) >> DMAV2_DMACFG_CORENUM_SHIFT)

/*
 * BUSNUM (RO)
 *
 * AXI bus interface number
 * 0x0: 1 AXI bus
 * 0x1: 2 AXI busses
 */
#define DMAV2_DMACFG_BUSNUM_MASK (0x8000U)
#define DMAV2_DMACFG_BUSNUM_SHIFT (15U)
#define DMAV2_DMACFG_BUSNUM_GET(x) (((uint32_t)(x) & DMAV2_DMACFG_BUSNUM_MASK) >> DMAV2_DMACFG_BUSNUM_SHIFT)

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
#define DMAV2_DMACFG_REQNUM_MASK (0x7C00U)
#define DMAV2_DMACFG_REQNUM_SHIFT (10U)
#define DMAV2_DMACFG_REQNUM_GET(x) (((uint32_t)(x) & DMAV2_DMACFG_REQNUM_MASK) >> DMAV2_DMACFG_REQNUM_SHIFT)

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
#define DMAV2_DMACFG_FIFODEPTH_MASK (0x3F0U)
#define DMAV2_DMACFG_FIFODEPTH_SHIFT (4U)
#define DMAV2_DMACFG_FIFODEPTH_GET(x) (((uint32_t)(x) & DMAV2_DMACFG_FIFODEPTH_MASK) >> DMAV2_DMACFG_FIFODEPTH_SHIFT)

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
#define DMAV2_DMACFG_CHANNELNUM_MASK (0xFU)
#define DMAV2_DMACFG_CHANNELNUM_SHIFT (0U)
#define DMAV2_DMACFG_CHANNELNUM_GET(x) (((uint32_t)(x) & DMAV2_DMACFG_CHANNELNUM_MASK) >> DMAV2_DMACFG_CHANNELNUM_SHIFT)

/* Bitfield definition for register: DMACTRL */
/*
 * RESET (WO)
 *
 * Software reset control. Write 1 to this bit to reset the DMA core and disable all channels.
 * Note: The software reset may cause the in-completion of AXI transaction.
 */
#define DMAV2_DMACTRL_RESET_MASK (0x1U)
#define DMAV2_DMACTRL_RESET_SHIFT (0U)
#define DMAV2_DMACTRL_RESET_SET(x) (((uint32_t)(x) << DMAV2_DMACTRL_RESET_SHIFT) & DMAV2_DMACTRL_RESET_MASK)
#define DMAV2_DMACTRL_RESET_GET(x) (((uint32_t)(x) & DMAV2_DMACTRL_RESET_MASK) >> DMAV2_DMACTRL_RESET_SHIFT)

/* Bitfield definition for register: CHABORT */
/*
 * CHABORT (WO)
 *
 * Write 1 to bit n to abort channel n. The bits should only be set when the corresponding channels are enabled.
 * Otherwise, the writes will be ignored for channels that are not enabled. (N: Number of channels)
 */
#define DMAV2_CHABORT_CHABORT_MASK (0xFFFFFFFFUL)
#define DMAV2_CHABORT_CHABORT_SHIFT (0U)
#define DMAV2_CHABORT_CHABORT_SET(x) (((uint32_t)(x) << DMAV2_CHABORT_CHABORT_SHIFT) & DMAV2_CHABORT_CHABORT_MASK)
#define DMAV2_CHABORT_CHABORT_GET(x) (((uint32_t)(x) & DMAV2_CHABORT_CHABORT_MASK) >> DMAV2_CHABORT_CHABORT_SHIFT)

/* Bitfield definition for register: INTHALFSTS */
/*
 * STS (RW)
 *
 * half transfer done irq status
 */
#define DMAV2_INTHALFSTS_STS_MASK (0xFFFFFFFFUL)
#define DMAV2_INTHALFSTS_STS_SHIFT (0U)
#define DMAV2_INTHALFSTS_STS_SET(x) (((uint32_t)(x) << DMAV2_INTHALFSTS_STS_SHIFT) & DMAV2_INTHALFSTS_STS_MASK)
#define DMAV2_INTHALFSTS_STS_GET(x) (((uint32_t)(x) & DMAV2_INTHALFSTS_STS_MASK) >> DMAV2_INTHALFSTS_STS_SHIFT)

/* Bitfield definition for register: INTTCSTS */
/*
 * STS (W1C)
 *
 * The terminal count status, one bit per channel. The terminal count status is set when a channel transfer finishes without the abort or error event.
 * 0x0: Channel n has no terminal count status
 * 0x1: Channel n has terminal count status
 */
#define DMAV2_INTTCSTS_STS_MASK (0xFFFFFFFFUL)
#define DMAV2_INTTCSTS_STS_SHIFT (0U)
#define DMAV2_INTTCSTS_STS_SET(x) (((uint32_t)(x) << DMAV2_INTTCSTS_STS_SHIFT) & DMAV2_INTTCSTS_STS_MASK)
#define DMAV2_INTTCSTS_STS_GET(x) (((uint32_t)(x) & DMAV2_INTTCSTS_STS_MASK) >> DMAV2_INTTCSTS_STS_SHIFT)

/* Bitfield definition for register: INTABORTSTS */
/*
 * STS (W1C)
 *
 * The abort status of channel, one bit per channel. The abort status is set when a channel transfer is aborted.
 * 0x0: Channel n has no abort status
 * 0x1: Channel n has abort status
 */
#define DMAV2_INTABORTSTS_STS_MASK (0xFFFFFFFFUL)
#define DMAV2_INTABORTSTS_STS_SHIFT (0U)
#define DMAV2_INTABORTSTS_STS_SET(x) (((uint32_t)(x) << DMAV2_INTABORTSTS_STS_SHIFT) & DMAV2_INTABORTSTS_STS_MASK)
#define DMAV2_INTABORTSTS_STS_GET(x) (((uint32_t)(x) & DMAV2_INTABORTSTS_STS_MASK) >> DMAV2_INTABORTSTS_STS_SHIFT)

/* Bitfield definition for register: INTERRSTS */
/*
 * STS (W1C)
 *
 * The error status, one bit per channel. The error status is set when a channel transfer encounters the following error events:
 * - Bus error
 * - Unaligned address
 * - Unaligned transfer width
 * - Reserved configuration
 * 0x0: Channel n has no error status
 * 0x1: Channel n has error status
 */
#define DMAV2_INTERRSTS_STS_MASK (0xFFFFFFFFUL)
#define DMAV2_INTERRSTS_STS_SHIFT (0U)
#define DMAV2_INTERRSTS_STS_SET(x) (((uint32_t)(x) << DMAV2_INTERRSTS_STS_SHIFT) & DMAV2_INTERRSTS_STS_MASK)
#define DMAV2_INTERRSTS_STS_GET(x) (((uint32_t)(x) & DMAV2_INTERRSTS_STS_MASK) >> DMAV2_INTERRSTS_STS_SHIFT)

/* Bitfield definition for register: CHEN */
/*
 * CHEN (RO)
 *
 * Alias of the Enable field of all ChnCtrl registers
 */
#define DMAV2_CHEN_CHEN_MASK (0xFFFFFFFFUL)
#define DMAV2_CHEN_CHEN_SHIFT (0U)
#define DMAV2_CHEN_CHEN_GET(x) (((uint32_t)(x) & DMAV2_CHEN_CHEN_MASK) >> DMAV2_CHEN_CHEN_SHIFT)

/* Bitfield definition for register of struct array CHCTRL: CTRL */
/*
 * INFINITELOOP (RW)
 *
 * set to loop current config infinitely
 */
#define DMAV2_CHCTRL_CTRL_INFINITELOOP_MASK (0x80000000UL)
#define DMAV2_CHCTRL_CTRL_INFINITELOOP_SHIFT (31U)
#define DMAV2_CHCTRL_CTRL_INFINITELOOP_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_CTRL_INFINITELOOP_SHIFT) & DMAV2_CHCTRL_CTRL_INFINITELOOP_MASK)
#define DMAV2_CHCTRL_CTRL_INFINITELOOP_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_CTRL_INFINITELOOP_MASK) >> DMAV2_CHCTRL_CTRL_INFINITELOOP_SHIFT)

/*
 * HANDSHAKEOPT (RW)
 *
 * 0: one request to transfer one burst
 * 1: one request to transfer all the data defined in ch_tts
 */
#define DMAV2_CHCTRL_CTRL_HANDSHAKEOPT_MASK (0x40000000UL)
#define DMAV2_CHCTRL_CTRL_HANDSHAKEOPT_SHIFT (30U)
#define DMAV2_CHCTRL_CTRL_HANDSHAKEOPT_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_CTRL_HANDSHAKEOPT_SHIFT) & DMAV2_CHCTRL_CTRL_HANDSHAKEOPT_MASK)
#define DMAV2_CHCTRL_CTRL_HANDSHAKEOPT_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_CTRL_HANDSHAKEOPT_MASK) >> DMAV2_CHCTRL_CTRL_HANDSHAKEOPT_SHIFT)

/*
 * PRIORITY (RW)
 *
 * Channel priority level
 * 0x0: Lower priority
 * 0x1: Higher priority
 */
#define DMAV2_CHCTRL_CTRL_PRIORITY_MASK (0x20000000UL)
#define DMAV2_CHCTRL_CTRL_PRIORITY_SHIFT (29U)
#define DMAV2_CHCTRL_CTRL_PRIORITY_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_CTRL_PRIORITY_SHIFT) & DMAV2_CHCTRL_CTRL_PRIORITY_MASK)
#define DMAV2_CHCTRL_CTRL_PRIORITY_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_CTRL_PRIORITY_MASK) >> DMAV2_CHCTRL_CTRL_PRIORITY_SHIFT)

/*
 * BURSTOPT (RW)
 *
 * set to change burst_size definition
 */
#define DMAV2_CHCTRL_CTRL_BURSTOPT_MASK (0x10000000UL)
#define DMAV2_CHCTRL_CTRL_BURSTOPT_SHIFT (28U)
#define DMAV2_CHCTRL_CTRL_BURSTOPT_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_CTRL_BURSTOPT_SHIFT) & DMAV2_CHCTRL_CTRL_BURSTOPT_MASK)
#define DMAV2_CHCTRL_CTRL_BURSTOPT_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_CTRL_BURSTOPT_MASK) >> DMAV2_CHCTRL_CTRL_BURSTOPT_SHIFT)

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
 * 0xb - 0xf: Reserved, setting this field with a reserved value triggers the error exception
 */
#define DMAV2_CHCTRL_CTRL_SRCBURSTSIZE_MASK (0xF000000UL)
#define DMAV2_CHCTRL_CTRL_SRCBURSTSIZE_SHIFT (24U)
#define DMAV2_CHCTRL_CTRL_SRCBURSTSIZE_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_CTRL_SRCBURSTSIZE_SHIFT) & DMAV2_CHCTRL_CTRL_SRCBURSTSIZE_MASK)
#define DMAV2_CHCTRL_CTRL_SRCBURSTSIZE_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_CTRL_SRCBURSTSIZE_MASK) >> DMAV2_CHCTRL_CTRL_SRCBURSTSIZE_SHIFT)

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
 * 0x6 - 0x7: Reserved, setting this field with a reserved value triggers the error exception
 */
#define DMAV2_CHCTRL_CTRL_SRCWIDTH_MASK (0xE00000UL)
#define DMAV2_CHCTRL_CTRL_SRCWIDTH_SHIFT (21U)
#define DMAV2_CHCTRL_CTRL_SRCWIDTH_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_CTRL_SRCWIDTH_SHIFT) & DMAV2_CHCTRL_CTRL_SRCWIDTH_MASK)
#define DMAV2_CHCTRL_CTRL_SRCWIDTH_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_CTRL_SRCWIDTH_MASK) >> DMAV2_CHCTRL_CTRL_SRCWIDTH_SHIFT)

/*
 * DSTWIDTH (RW)
 *
 * Destination transfer width.
 * Both the total transfer byte number and the burst transfer byte number should be aligned to the destination transfer width;
 * otherwise the error event will be triggered.
 * For example, destination transfer width should be set as byte transfer if total transfer byte is not aligned to half-word.
 * See field SrcBurstSize above for the definition of burst transfer byte number and section 3.2.8 for the definition of the total transfer byte number.
 * 0x0: Byte transfer
 * 0x1: Half-word transfer
 * 0x2: Word transfer
 * 0x3: Double word transfer
 * 0x4: Quad word transfer
 * 0x5: Eight word transfer
 * 0x6 - 0x7: Reserved, setting this field with a reserved value triggers the error exception
 */
#define DMAV2_CHCTRL_CTRL_DSTWIDTH_MASK (0x1C0000UL)
#define DMAV2_CHCTRL_CTRL_DSTWIDTH_SHIFT (18U)
#define DMAV2_CHCTRL_CTRL_DSTWIDTH_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_CTRL_DSTWIDTH_SHIFT) & DMAV2_CHCTRL_CTRL_DSTWIDTH_MASK)
#define DMAV2_CHCTRL_CTRL_DSTWIDTH_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_CTRL_DSTWIDTH_MASK) >> DMAV2_CHCTRL_CTRL_DSTWIDTH_SHIFT)

/*
 * SRCMODE (RW)
 *
 * Source DMA handshake mode
 * 0x0: Normal mode
 * 0x1: Handshake mode
 * Normal mode is enabled and started by software set Enable bit;
 * Handshake mode is enabled by software set Enable bit, started by hardware dma request from DMAMUX block
 */
#define DMAV2_CHCTRL_CTRL_SRCMODE_MASK (0x20000UL)
#define DMAV2_CHCTRL_CTRL_SRCMODE_SHIFT (17U)
#define DMAV2_CHCTRL_CTRL_SRCMODE_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_CTRL_SRCMODE_SHIFT) & DMAV2_CHCTRL_CTRL_SRCMODE_MASK)
#define DMAV2_CHCTRL_CTRL_SRCMODE_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_CTRL_SRCMODE_MASK) >> DMAV2_CHCTRL_CTRL_SRCMODE_SHIFT)

/*
 * DSTMODE (RW)
 *
 * Destination DMA handshake mode
 * 0x0: Normal mode
 * 0x1: Handshake mode
 * the difference bewteen Source/Destination handshake mode is:
 * the dma block will response hardware request after read in Source handshake mode;
 * the dma block will response hardware request after write in Destination handshake mode;
 * NOTE: can't set SrcMode and DstMode at same time, otherwise result unknown.
 */
#define DMAV2_CHCTRL_CTRL_DSTMODE_MASK (0x10000UL)
#define DMAV2_CHCTRL_CTRL_DSTMODE_SHIFT (16U)
#define DMAV2_CHCTRL_CTRL_DSTMODE_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_CTRL_DSTMODE_SHIFT) & DMAV2_CHCTRL_CTRL_DSTMODE_MASK)
#define DMAV2_CHCTRL_CTRL_DSTMODE_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_CTRL_DSTMODE_MASK) >> DMAV2_CHCTRL_CTRL_DSTMODE_SHIFT)

/*
 * SRCADDRCTRL (RW)
 *
 * Source address control
 * 0x0: Increment address
 * 0x1: Decrement address
 * 0x2: Fixed address
 * 0x3: Reserved, setting the field with this value triggers the error exception
 */
#define DMAV2_CHCTRL_CTRL_SRCADDRCTRL_MASK (0xC000U)
#define DMAV2_CHCTRL_CTRL_SRCADDRCTRL_SHIFT (14U)
#define DMAV2_CHCTRL_CTRL_SRCADDRCTRL_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_CTRL_SRCADDRCTRL_SHIFT) & DMAV2_CHCTRL_CTRL_SRCADDRCTRL_MASK)
#define DMAV2_CHCTRL_CTRL_SRCADDRCTRL_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_CTRL_SRCADDRCTRL_MASK) >> DMAV2_CHCTRL_CTRL_SRCADDRCTRL_SHIFT)

/*
 * DSTADDRCTRL (RW)
 *
 * Destination address control
 * 0x0: Increment address
 * 0x1: Decrement address
 * 0x2: Fixed address
 * 0x3: Reserved, setting the field with this value triggers the error exception
 */
#define DMAV2_CHCTRL_CTRL_DSTADDRCTRL_MASK (0x3000U)
#define DMAV2_CHCTRL_CTRL_DSTADDRCTRL_SHIFT (12U)
#define DMAV2_CHCTRL_CTRL_DSTADDRCTRL_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_CTRL_DSTADDRCTRL_SHIFT) & DMAV2_CHCTRL_CTRL_DSTADDRCTRL_MASK)
#define DMAV2_CHCTRL_CTRL_DSTADDRCTRL_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_CTRL_DSTADDRCTRL_MASK) >> DMAV2_CHCTRL_CTRL_DSTADDRCTRL_SHIFT)

/*
 * SRC_FIXBURST (RW)
 *
 * set to loop current burst, omit setting in src_addr_ctrl
 */
#define DMAV2_CHCTRL_CTRL_SRC_FIXBURST_MASK (0x400U)
#define DMAV2_CHCTRL_CTRL_SRC_FIXBURST_SHIFT (10U)
#define DMAV2_CHCTRL_CTRL_SRC_FIXBURST_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_CTRL_SRC_FIXBURST_SHIFT) & DMAV2_CHCTRL_CTRL_SRC_FIXBURST_MASK)
#define DMAV2_CHCTRL_CTRL_SRC_FIXBURST_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_CTRL_SRC_FIXBURST_MASK) >> DMAV2_CHCTRL_CTRL_SRC_FIXBURST_SHIFT)

/*
 * DST_FIXBURST (RW)
 *
 * set to loop current burst, omit setting in dst_addr_ctrl
 */
#define DMAV2_CHCTRL_CTRL_DST_FIXBURST_MASK (0x100U)
#define DMAV2_CHCTRL_CTRL_DST_FIXBURST_SHIFT (8U)
#define DMAV2_CHCTRL_CTRL_DST_FIXBURST_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_CTRL_DST_FIXBURST_SHIFT) & DMAV2_CHCTRL_CTRL_DST_FIXBURST_MASK)
#define DMAV2_CHCTRL_CTRL_DST_FIXBURST_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_CTRL_DST_FIXBURST_MASK) >> DMAV2_CHCTRL_CTRL_DST_FIXBURST_SHIFT)

/*
 * SWAP_CTL (RW)
 *
 * 00 ：use swap table(if swap table all 0, then act nothing)
 * 01 :   byte swap
 * 10 :   16bit swap
 * 11 :   32bit swap
 */
#define DMAV2_CHCTRL_CTRL_SWAP_CTL_MASK (0xC0U)
#define DMAV2_CHCTRL_CTRL_SWAP_CTL_SHIFT (6U)
#define DMAV2_CHCTRL_CTRL_SWAP_CTL_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_CTRL_SWAP_CTL_SHIFT) & DMAV2_CHCTRL_CTRL_SWAP_CTL_MASK)
#define DMAV2_CHCTRL_CTRL_SWAP_CTL_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_CTRL_SWAP_CTL_MASK) >> DMAV2_CHCTRL_CTRL_SWAP_CTL_SHIFT)

/*
 * INTHALFCNTMASK (RW)
 *
 * Channel half interrupt mask
 * 0x0: Allow the half interrupt to be triggered
 * 0x1: Disable the half interrupt
 */
#define DMAV2_CHCTRL_CTRL_INTHALFCNTMASK_MASK (0x10U)
#define DMAV2_CHCTRL_CTRL_INTHALFCNTMASK_SHIFT (4U)
#define DMAV2_CHCTRL_CTRL_INTHALFCNTMASK_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_CTRL_INTHALFCNTMASK_SHIFT) & DMAV2_CHCTRL_CTRL_INTHALFCNTMASK_MASK)
#define DMAV2_CHCTRL_CTRL_INTHALFCNTMASK_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_CTRL_INTHALFCNTMASK_MASK) >> DMAV2_CHCTRL_CTRL_INTHALFCNTMASK_SHIFT)

/*
 * INTABTMASK (RW)
 *
 * Channel abort interrupt mask
 * 0x0: Allow the abort interrupt to be triggered
 * 0x1: Disable the abort interrupt
 */
#define DMAV2_CHCTRL_CTRL_INTABTMASK_MASK (0x8U)
#define DMAV2_CHCTRL_CTRL_INTABTMASK_SHIFT (3U)
#define DMAV2_CHCTRL_CTRL_INTABTMASK_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_CTRL_INTABTMASK_SHIFT) & DMAV2_CHCTRL_CTRL_INTABTMASK_MASK)
#define DMAV2_CHCTRL_CTRL_INTABTMASK_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_CTRL_INTABTMASK_MASK) >> DMAV2_CHCTRL_CTRL_INTABTMASK_SHIFT)

/*
 * INTERRMASK (RW)
 *
 * Channel error interrupt mask
 * 0x0: Allow the error interrupt to be triggered
 * 0x1: Disable the error interrupt
 */
#define DMAV2_CHCTRL_CTRL_INTERRMASK_MASK (0x4U)
#define DMAV2_CHCTRL_CTRL_INTERRMASK_SHIFT (2U)
#define DMAV2_CHCTRL_CTRL_INTERRMASK_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_CTRL_INTERRMASK_SHIFT) & DMAV2_CHCTRL_CTRL_INTERRMASK_MASK)
#define DMAV2_CHCTRL_CTRL_INTERRMASK_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_CTRL_INTERRMASK_MASK) >> DMAV2_CHCTRL_CTRL_INTERRMASK_SHIFT)

/*
 * INTTCMASK (RW)
 *
 * Channel terminal count interrupt mask
 * 0x0: Allow the terminal count interrupt to be triggered
 * 0x1: Disable the terminal count interrupt
 */
#define DMAV2_CHCTRL_CTRL_INTTCMASK_MASK (0x2U)
#define DMAV2_CHCTRL_CTRL_INTTCMASK_SHIFT (1U)
#define DMAV2_CHCTRL_CTRL_INTTCMASK_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_CTRL_INTTCMASK_SHIFT) & DMAV2_CHCTRL_CTRL_INTTCMASK_MASK)
#define DMAV2_CHCTRL_CTRL_INTTCMASK_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_CTRL_INTTCMASK_MASK) >> DMAV2_CHCTRL_CTRL_INTTCMASK_SHIFT)

/*
 * ENABLE (RW)
 *
 * Channel enable bit
 * 0x0: Disable
 * 0x1: Enable
 */
#define DMAV2_CHCTRL_CTRL_ENABLE_MASK (0x1U)
#define DMAV2_CHCTRL_CTRL_ENABLE_SHIFT (0U)
#define DMAV2_CHCTRL_CTRL_ENABLE_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_CTRL_ENABLE_SHIFT) & DMAV2_CHCTRL_CTRL_ENABLE_MASK)
#define DMAV2_CHCTRL_CTRL_ENABLE_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_CTRL_ENABLE_MASK) >> DMAV2_CHCTRL_CTRL_ENABLE_SHIFT)

/* Bitfield definition for register of struct array CHCTRL: TRANSIZE */
/*
 * TRANSIZE (RW)
 *
 * Total transfer size from source. The total number of transferred bytes is (TranSize * SrcWidth). This register is cleared when the DMA transfer is done.
 * If a channel is enabled with zero total transfer size, the error event will be triggered and the transfer will be terminated.
 */
#define DMAV2_CHCTRL_TRANSIZE_TRANSIZE_MASK (0xFFFFFFFUL)
#define DMAV2_CHCTRL_TRANSIZE_TRANSIZE_SHIFT (0U)
#define DMAV2_CHCTRL_TRANSIZE_TRANSIZE_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_TRANSIZE_TRANSIZE_SHIFT) & DMAV2_CHCTRL_TRANSIZE_TRANSIZE_MASK)
#define DMAV2_CHCTRL_TRANSIZE_TRANSIZE_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_TRANSIZE_TRANSIZE_MASK) >> DMAV2_CHCTRL_TRANSIZE_TRANSIZE_SHIFT)

/* Bitfield definition for register of struct array CHCTRL: SRCADDR */
/*
 * SRCADDRL (RW)
 *
 * Low part of the source starting address. When the transfer completes, the value of {SrcAddrH,SrcAddrL} is updated to the ending address.
 * This address must be aligned to the source transfer size; otherwise, an error event will be triggered.
 */
#define DMAV2_CHCTRL_SRCADDR_SRCADDRL_MASK (0xFFFFFFFFUL)
#define DMAV2_CHCTRL_SRCADDR_SRCADDRL_SHIFT (0U)
#define DMAV2_CHCTRL_SRCADDR_SRCADDRL_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_SRCADDR_SRCADDRL_SHIFT) & DMAV2_CHCTRL_SRCADDR_SRCADDRL_MASK)
#define DMAV2_CHCTRL_SRCADDR_SRCADDRL_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_SRCADDR_SRCADDRL_MASK) >> DMAV2_CHCTRL_SRCADDR_SRCADDRL_SHIFT)

/* Bitfield definition for register of struct array CHCTRL: CHANREQCTRL */
/*
 * SRCREQSEL (RW)
 *
 * Source DMA request select. Select the request/ack handshake pair that the source device is connected to.
 */
#define DMAV2_CHCTRL_CHANREQCTRL_SRCREQSEL_MASK (0x1F000000UL)
#define DMAV2_CHCTRL_CHANREQCTRL_SRCREQSEL_SHIFT (24U)
#define DMAV2_CHCTRL_CHANREQCTRL_SRCREQSEL_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_CHANREQCTRL_SRCREQSEL_SHIFT) & DMAV2_CHCTRL_CHANREQCTRL_SRCREQSEL_MASK)
#define DMAV2_CHCTRL_CHANREQCTRL_SRCREQSEL_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_CHANREQCTRL_SRCREQSEL_MASK) >> DMAV2_CHCTRL_CHANREQCTRL_SRCREQSEL_SHIFT)

/*
 * DSTREQSEL (RW)
 *
 * Destination DMA request select. Select the request/ack handshake pair that the destination device is connected to.
 */
#define DMAV2_CHCTRL_CHANREQCTRL_DSTREQSEL_MASK (0x1F0000UL)
#define DMAV2_CHCTRL_CHANREQCTRL_DSTREQSEL_SHIFT (16U)
#define DMAV2_CHCTRL_CHANREQCTRL_DSTREQSEL_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_CHANREQCTRL_DSTREQSEL_SHIFT) & DMAV2_CHCTRL_CHANREQCTRL_DSTREQSEL_MASK)
#define DMAV2_CHCTRL_CHANREQCTRL_DSTREQSEL_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_CHANREQCTRL_DSTREQSEL_MASK) >> DMAV2_CHCTRL_CHANREQCTRL_DSTREQSEL_SHIFT)

/* Bitfield definition for register of struct array CHCTRL: DSTADDR */
/*
 * DSTADDRL (RW)
 *
 * Low part of the destination starting address. When the transfer completes, the value of {DstAddrH,DstAddrL} is updated to the ending address.
 * This address must be aligned to the destination transfer size; otherwise the error event will be triggered.
 */
#define DMAV2_CHCTRL_DSTADDR_DSTADDRL_MASK (0xFFFFFFFFUL)
#define DMAV2_CHCTRL_DSTADDR_DSTADDRL_SHIFT (0U)
#define DMAV2_CHCTRL_DSTADDR_DSTADDRL_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_DSTADDR_DSTADDRL_SHIFT) & DMAV2_CHCTRL_DSTADDR_DSTADDRL_MASK)
#define DMAV2_CHCTRL_DSTADDR_DSTADDRL_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_DSTADDR_DSTADDRL_MASK) >> DMAV2_CHCTRL_DSTADDR_DSTADDRL_SHIFT)

/* Bitfield definition for register of struct array CHCTRL: SWAPTABLE */
/*
 * TABLE (RW)
 *
 * "4bit for one byte, define how to swap, default is no swap.
 * For HDMA, support up to 4-byte, the register default value is 0x3210"
 */
#define DMAV2_CHCTRL_SWAPTABLE_TABLE_MASK (0xFFFFFFFFUL)
#define DMAV2_CHCTRL_SWAPTABLE_TABLE_SHIFT (0U)
#define DMAV2_CHCTRL_SWAPTABLE_TABLE_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_SWAPTABLE_TABLE_SHIFT) & DMAV2_CHCTRL_SWAPTABLE_TABLE_MASK)
#define DMAV2_CHCTRL_SWAPTABLE_TABLE_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_SWAPTABLE_TABLE_MASK) >> DMAV2_CHCTRL_SWAPTABLE_TABLE_SHIFT)

/* Bitfield definition for register of struct array CHCTRL: LLPOINTER */
/*
 * LLPOINTERL (RW)
 *
 * Low part of the pointer to the next descriptor. The pointer must be double word aligned.
 */
#define DMAV2_CHCTRL_LLPOINTER_LLPOINTERL_MASK (0xFFFFFFF8UL)
#define DMAV2_CHCTRL_LLPOINTER_LLPOINTERL_SHIFT (3U)
#define DMAV2_CHCTRL_LLPOINTER_LLPOINTERL_SET(x) (((uint32_t)(x) << DMAV2_CHCTRL_LLPOINTER_LLPOINTERL_SHIFT) & DMAV2_CHCTRL_LLPOINTER_LLPOINTERL_MASK)
#define DMAV2_CHCTRL_LLPOINTER_LLPOINTERL_GET(x) (((uint32_t)(x) & DMAV2_CHCTRL_LLPOINTER_LLPOINTERL_MASK) >> DMAV2_CHCTRL_LLPOINTER_LLPOINTERL_SHIFT)



/* CHCTRL register group index macro definition */
#define DMAV2_CHCTRL_CH0 (0UL)
#define DMAV2_CHCTRL_CH1 (1UL)
#define DMAV2_CHCTRL_CH2 (2UL)
#define DMAV2_CHCTRL_CH3 (3UL)
#define DMAV2_CHCTRL_CH4 (4UL)
#define DMAV2_CHCTRL_CH5 (5UL)
#define DMAV2_CHCTRL_CH6 (6UL)
#define DMAV2_CHCTRL_CH7 (7UL)
#define DMAV2_CHCTRL_CH8 (8UL)
#define DMAV2_CHCTRL_CH9 (9UL)
#define DMAV2_CHCTRL_CH10 (10UL)
#define DMAV2_CHCTRL_CH11 (11UL)
#define DMAV2_CHCTRL_CH12 (12UL)
#define DMAV2_CHCTRL_CH13 (13UL)
#define DMAV2_CHCTRL_CH14 (14UL)
#define DMAV2_CHCTRL_CH15 (15UL)
#define DMAV2_CHCTRL_CH16 (16UL)
#define DMAV2_CHCTRL_CH17 (17UL)
#define DMAV2_CHCTRL_CH18 (18UL)
#define DMAV2_CHCTRL_CH19 (19UL)
#define DMAV2_CHCTRL_CH20 (20UL)
#define DMAV2_CHCTRL_CH21 (21UL)
#define DMAV2_CHCTRL_CH22 (22UL)
#define DMAV2_CHCTRL_CH23 (23UL)
#define DMAV2_CHCTRL_CH24 (24UL)
#define DMAV2_CHCTRL_CH25 (25UL)
#define DMAV2_CHCTRL_CH26 (26UL)
#define DMAV2_CHCTRL_CH27 (27UL)
#define DMAV2_CHCTRL_CH28 (28UL)
#define DMAV2_CHCTRL_CH29 (29UL)
#define DMAV2_CHCTRL_CH30 (30UL)
#define DMAV2_CHCTRL_CH31 (31UL)


#endif /* HPM_DMAV2_H */
