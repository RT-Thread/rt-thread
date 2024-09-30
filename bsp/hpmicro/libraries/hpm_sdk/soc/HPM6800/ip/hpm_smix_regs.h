/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_SMIX_H
#define HPM_SMIX_H

typedef struct {
    __R  uint32_t DMAC_ID;                     /* 0x0: DMAC_ID Register */
    __RW uint32_t DMAC_TC_ST;                  /* 0x4: Transfer Complete Status */
    __RW uint32_t DMAC_ABRT_ST;                /* 0x8: Transfer Abort Status */
    __RW uint32_t DMAC_ERR_ST;                 /* 0xC: Transfer Error Status */
    __R  uint8_t  RESERVED0[16];               /* 0x10 - 0x1F: Reserved */
    __RW uint32_t DMAC_CTRL;                   /* 0x20: Control Register */
    __W  uint32_t DMAC_ABRT_CMD;               /* 0x24: Abort Command Register */
    __R  uint8_t  RESERVED1[12];               /* 0x28 - 0x33: Reserved */
    __RW uint32_t DMAC_CHEN;                   /* 0x34: Channel Enable Register */
    __R  uint8_t  RESERVED2[8];                /* 0x38 - 0x3F: Reserved */
    struct {
        __RW uint32_t CTL;                     /* 0x40: Channel N Control Register */
        __RW uint32_t BURST_COUNT;             /* 0x44: Channel N Source Total Beats Register */
        __RW uint32_t SRCADDR;                 /* 0x48: Channel N Source Register */
        __R  uint8_t  RESERVED0[4];            /* 0x4C - 0x4F: Reserved */
        __RW uint32_t DSTADDR;                 /* 0x50: Channel N Destination Register */
        __R  uint8_t  RESERVED1[4];            /* 0x54 - 0x57: Reserved */
        __RW uint32_t LLP;                     /* 0x58: Channel N Linked List Pointer Register */
        __R  uint8_t  RESERVED2[4];            /* 0x5C - 0x5F: Reserved */
    } DMA_CH[26];
    __R  uint8_t  RESERVED3[1152];             /* 0x380 - 0x7FF: Reserved */
    __RW uint32_t CALSAT_ST;                   /* 0x800: SMIX Cal Saturation Status Register */
    __RW uint32_t FDOT_DONE_ST;                /* 0x804: SMIX Fade-Out Done Status Register */
    __R  uint32_t DATA_ST;                     /* 0x808: SMIX Data Status Register */
    __R  uint8_t  RESERVED4[52];               /* 0x80C - 0x83F: Reserved */
    struct {
        __RW uint32_t CTRL;                    /* 0x840: SMIX Dstination N Control Register */
        __RW uint32_t GAIN;                    /* 0x844: SMIX Dstination N Gain Register */
        __RW uint32_t BUFSIZE;                 /* 0x848: SMIX Dstination N Max Index Register */
        __RW uint32_t FADEIN;                  /* 0x84C: SMIX Dstination N Fade-In Configuration Register */
        __RW uint32_t FADEOUT;                 /* 0x850: SMIX Dstination N Fade-Out Configuration Register */
        __R  uint32_t ST;                      /* 0x854: SMIX Dstination N Status Register */
        __R  uint32_t DATA;                    /* 0x858: SMIX Dstination N Data Out Register */
        __R  uint8_t  RESERVED0[4];            /* 0x85C - 0x85F: Reserved */
        __RW uint32_t SOURCE_EN;               /* 0x860: SMIX Dstination N Source Enable Register */
        __RW uint32_t SOURCE_ACT;              /* 0x864: SMIX Dstination N Source Activation Register */
        __RW uint32_t SOURCE_DEACT;            /* 0x868: SMIX Dstination N Source De-Activation Register */
        __RW uint32_t SOURCE_FADEIN_CTRL;      /* 0x86C: SMIX Dstination N Source Fade-in Control Register */
        __R  uint32_t DEACT_ST;                /* 0x870: SMIX Dstination N Source Deactivation Status Register */
        __RW uint32_t SOURCE_MFADEOUT_CTRL;    /* 0x874: SMIX Dstination N Source Manual Fade-out Control Register */
        __R  uint8_t  RESERVED1[8];            /* 0x878 - 0x87F: Reserved */
    } DST_CH[2];
    __R  uint8_t  RESERVED5[64];               /* 0x8C0 - 0x8FF: Reserved */
    struct {
        __RW uint32_t CTRL;                    /* 0x900: SMIX Source N Control Register */
        __RW uint32_t GAIN;                    /* 0x904: SMIX Source N Gain Register */
        __RW uint32_t FADEIN;                  /* 0x908: SMIX Source N Fade-in Control Register */
        __RW uint32_t FADEOUT;                 /* 0x90C: SMIX Source N Fade-out Control Register */
        __RW uint32_t BUFSIZE;                 /* 0x910: SMIX Source N Buffer Size Register */
        __RW uint32_t ST;                      /* 0x914: SMIX Source N Status Register */
        __W  uint32_t DATA;                    /* 0x918: SMIX Source N Data Input Register */
        __R  uint8_t  RESERVED0[4];            /* 0x91C - 0x91F: Reserved */
    } SOURCE_CH[14];
} SMIX_Type;


/* Bitfield definition for register: DMAC_ID */
/*
 * REV (RO)
 *
 * Revision
 */
#define SMIX_DMAC_ID_REV_MASK (0x7FFFFUL)
#define SMIX_DMAC_ID_REV_SHIFT (0U)
#define SMIX_DMAC_ID_REV_GET(x) (((uint32_t)(x) & SMIX_DMAC_ID_REV_MASK) >> SMIX_DMAC_ID_REV_SHIFT)

/* Bitfield definition for register: DMAC_TC_ST */
/*
 * CH (W1C)
 *
 * The terminal count status is set when a channel transfer finishes without abort or error events
 */
#define SMIX_DMAC_TC_ST_CH_MASK (0x3FFFFFFUL)
#define SMIX_DMAC_TC_ST_CH_SHIFT (0U)
#define SMIX_DMAC_TC_ST_CH_SET(x) (((uint32_t)(x) << SMIX_DMAC_TC_ST_CH_SHIFT) & SMIX_DMAC_TC_ST_CH_MASK)
#define SMIX_DMAC_TC_ST_CH_GET(x) (((uint32_t)(x) & SMIX_DMAC_TC_ST_CH_MASK) >> SMIX_DMAC_TC_ST_CH_SHIFT)

/* Bitfield definition for register: DMAC_ABRT_ST */
/*
 * CH (W1C)
 *
 * The abort status is set when a channel transfer is aborted
 */
#define SMIX_DMAC_ABRT_ST_CH_MASK (0x3FFFFFFUL)
#define SMIX_DMAC_ABRT_ST_CH_SHIFT (0U)
#define SMIX_DMAC_ABRT_ST_CH_SET(x) (((uint32_t)(x) << SMIX_DMAC_ABRT_ST_CH_SHIFT) & SMIX_DMAC_ABRT_ST_CH_MASK)
#define SMIX_DMAC_ABRT_ST_CH_GET(x) (((uint32_t)(x) & SMIX_DMAC_ABRT_ST_CH_MASK) >> SMIX_DMAC_ABRT_ST_CH_SHIFT)

/* Bitfield definition for register: DMAC_ERR_ST */
/*
 * CH (W1C)
 *
 * The error status is set when a channel transfer encounters the following error events:
 * . Bus error
 * . Unaligned address
 * . Unaligned transfer width
 * . Reserved configuration
 */
#define SMIX_DMAC_ERR_ST_CH_MASK (0x3FFFFFFUL)
#define SMIX_DMAC_ERR_ST_CH_SHIFT (0U)
#define SMIX_DMAC_ERR_ST_CH_SET(x) (((uint32_t)(x) << SMIX_DMAC_ERR_ST_CH_SHIFT) & SMIX_DMAC_ERR_ST_CH_MASK)
#define SMIX_DMAC_ERR_ST_CH_GET(x) (((uint32_t)(x) & SMIX_DMAC_ERR_ST_CH_MASK) >> SMIX_DMAC_ERR_ST_CH_SHIFT)

/* Bitfield definition for register: DMAC_CTRL */
/*
 * SRST (RW)
 *
 * Software Reset
 */
#define SMIX_DMAC_CTRL_SRST_MASK (0x1U)
#define SMIX_DMAC_CTRL_SRST_SHIFT (0U)
#define SMIX_DMAC_CTRL_SRST_SET(x) (((uint32_t)(x) << SMIX_DMAC_CTRL_SRST_SHIFT) & SMIX_DMAC_CTRL_SRST_MASK)
#define SMIX_DMAC_CTRL_SRST_GET(x) (((uint32_t)(x) & SMIX_DMAC_CTRL_SRST_MASK) >> SMIX_DMAC_CTRL_SRST_SHIFT)

/* Bitfield definition for register: DMAC_ABRT_CMD */
/*
 * CH (WO)
 *
 * Write 1 to force the corresponding channel into abort status
 */
#define SMIX_DMAC_ABRT_CMD_CH_MASK (0x3FFFFFFUL)
#define SMIX_DMAC_ABRT_CMD_CH_SHIFT (0U)
#define SMIX_DMAC_ABRT_CMD_CH_SET(x) (((uint32_t)(x) << SMIX_DMAC_ABRT_CMD_CH_SHIFT) & SMIX_DMAC_ABRT_CMD_CH_MASK)
#define SMIX_DMAC_ABRT_CMD_CH_GET(x) (((uint32_t)(x) & SMIX_DMAC_ABRT_CMD_CH_MASK) >> SMIX_DMAC_ABRT_CMD_CH_SHIFT)

/* Bitfield definition for register: DMAC_CHEN */
/*
 * CH (RO)
 *
 * Write 1 to enable the corresponding channel
 */
#define SMIX_DMAC_CHEN_CH_MASK (0x3FFFFFFUL)
#define SMIX_DMAC_CHEN_CH_SHIFT (0U)
#define SMIX_DMAC_CHEN_CH_GET(x) (((uint32_t)(x) & SMIX_DMAC_CHEN_CH_MASK) >> SMIX_DMAC_CHEN_CH_SHIFT)

/* Bitfield definition for register of struct array DMA_CH: CTL */
/*
 * SRCREQSEL (RW)
 *
 * Source DMA request select. Select the request/ack handshake pair that the source device is connected to.
 */
#define SMIX_DMA_CH_CTL_SRCREQSEL_MASK (0x7C000000UL)
#define SMIX_DMA_CH_CTL_SRCREQSEL_SHIFT (26U)
#define SMIX_DMA_CH_CTL_SRCREQSEL_SET(x) (((uint32_t)(x) << SMIX_DMA_CH_CTL_SRCREQSEL_SHIFT) & SMIX_DMA_CH_CTL_SRCREQSEL_MASK)
#define SMIX_DMA_CH_CTL_SRCREQSEL_GET(x) (((uint32_t)(x) & SMIX_DMA_CH_CTL_SRCREQSEL_MASK) >> SMIX_DMA_CH_CTL_SRCREQSEL_SHIFT)

/*
 * DSTREQSEL (RW)
 *
 * Destination DMA request select. Select the request/ack handshake pair that the destination device is connected to.
 */
#define SMIX_DMA_CH_CTL_DSTREQSEL_MASK (0x3E00000UL)
#define SMIX_DMA_CH_CTL_DSTREQSEL_SHIFT (21U)
#define SMIX_DMA_CH_CTL_DSTREQSEL_SET(x) (((uint32_t)(x) << SMIX_DMA_CH_CTL_DSTREQSEL_SHIFT) & SMIX_DMA_CH_CTL_DSTREQSEL_MASK)
#define SMIX_DMA_CH_CTL_DSTREQSEL_GET(x) (((uint32_t)(x) & SMIX_DMA_CH_CTL_DSTREQSEL_MASK) >> SMIX_DMA_CH_CTL_DSTREQSEL_SHIFT)

/*
 * PRIORITY (RW)
 *
 * 0x0: Lower priority
 * 0x1: Higher priority
 */
#define SMIX_DMA_CH_CTL_PRIORITY_MASK (0x80000UL)
#define SMIX_DMA_CH_CTL_PRIORITY_SHIFT (19U)
#define SMIX_DMA_CH_CTL_PRIORITY_SET(x) (((uint32_t)(x) << SMIX_DMA_CH_CTL_PRIORITY_SHIFT) & SMIX_DMA_CH_CTL_PRIORITY_MASK)
#define SMIX_DMA_CH_CTL_PRIORITY_GET(x) (((uint32_t)(x) & SMIX_DMA_CH_CTL_PRIORITY_MASK) >> SMIX_DMA_CH_CTL_PRIORITY_SHIFT)

/*
 * SRCBURSTSIZE (RW)
 *
 * 0x0: 1 beat per transfer
 * 0x1: 2 beats per transfer
 * 0x2: 4 beats per transfer
 * 0x3: 8 beats per transfer
 * 0x4: 16 beats per transfer
 * 0x5: 32 beats per transfer
 * 0x6: 64 beats per transfer
 * 0x7: 128 beats per transfer
 */
#define SMIX_DMA_CH_CTL_SRCBURSTSIZE_MASK (0x78000UL)
#define SMIX_DMA_CH_CTL_SRCBURSTSIZE_SHIFT (15U)
#define SMIX_DMA_CH_CTL_SRCBURSTSIZE_SET(x) (((uint32_t)(x) << SMIX_DMA_CH_CTL_SRCBURSTSIZE_SHIFT) & SMIX_DMA_CH_CTL_SRCBURSTSIZE_MASK)
#define SMIX_DMA_CH_CTL_SRCBURSTSIZE_GET(x) (((uint32_t)(x) & SMIX_DMA_CH_CTL_SRCBURSTSIZE_MASK) >> SMIX_DMA_CH_CTL_SRCBURSTSIZE_SHIFT)

/*
 * SRCWIDTH (RW)
 *
 * Source Transfer Beat Size:
 * 0x0: Byte transfer
 * 0x1: Half-word transfer
 * 0x2: Word transfer
 */
#define SMIX_DMA_CH_CTL_SRCWIDTH_MASK (0x6000U)
#define SMIX_DMA_CH_CTL_SRCWIDTH_SHIFT (13U)
#define SMIX_DMA_CH_CTL_SRCWIDTH_SET(x) (((uint32_t)(x) << SMIX_DMA_CH_CTL_SRCWIDTH_SHIFT) & SMIX_DMA_CH_CTL_SRCWIDTH_MASK)
#define SMIX_DMA_CH_CTL_SRCWIDTH_GET(x) (((uint32_t)(x) & SMIX_DMA_CH_CTL_SRCWIDTH_MASK) >> SMIX_DMA_CH_CTL_SRCWIDTH_SHIFT)

/*
 * DSTWIDTH (RW)
 *
 * Destination Transfer Beat Size:
 * 0x0: Byte transfer
 * 0x1: Half-word transfer
 * 0x2: Word transfer
 */
#define SMIX_DMA_CH_CTL_DSTWIDTH_MASK (0x1800U)
#define SMIX_DMA_CH_CTL_DSTWIDTH_SHIFT (11U)
#define SMIX_DMA_CH_CTL_DSTWIDTH_SET(x) (((uint32_t)(x) << SMIX_DMA_CH_CTL_DSTWIDTH_SHIFT) & SMIX_DMA_CH_CTL_DSTWIDTH_MASK)
#define SMIX_DMA_CH_CTL_DSTWIDTH_GET(x) (((uint32_t)(x) & SMIX_DMA_CH_CTL_DSTWIDTH_MASK) >> SMIX_DMA_CH_CTL_DSTWIDTH_SHIFT)

/*
 * SRCMODE (RW)
 *
 * DMA Source handshake mode
 * 0x0: Normal mode
 * 0x1: Handshake mode
 */
#define SMIX_DMA_CH_CTL_SRCMODE_MASK (0x400U)
#define SMIX_DMA_CH_CTL_SRCMODE_SHIFT (10U)
#define SMIX_DMA_CH_CTL_SRCMODE_SET(x) (((uint32_t)(x) << SMIX_DMA_CH_CTL_SRCMODE_SHIFT) & SMIX_DMA_CH_CTL_SRCMODE_MASK)
#define SMIX_DMA_CH_CTL_SRCMODE_GET(x) (((uint32_t)(x) & SMIX_DMA_CH_CTL_SRCMODE_MASK) >> SMIX_DMA_CH_CTL_SRCMODE_SHIFT)

/*
 * DSTMODE (RW)
 *
 * DMA Destination handshake mode
 * 0x0: Normal mode
 * 0x1: Handshake mode
 */
#define SMIX_DMA_CH_CTL_DSTMODE_MASK (0x200U)
#define SMIX_DMA_CH_CTL_DSTMODE_SHIFT (9U)
#define SMIX_DMA_CH_CTL_DSTMODE_SET(x) (((uint32_t)(x) << SMIX_DMA_CH_CTL_DSTMODE_SHIFT) & SMIX_DMA_CH_CTL_DSTMODE_MASK)
#define SMIX_DMA_CH_CTL_DSTMODE_GET(x) (((uint32_t)(x) & SMIX_DMA_CH_CTL_DSTMODE_MASK) >> SMIX_DMA_CH_CTL_DSTMODE_SHIFT)

/*
 * SRCADDRCTRL (RW)
 *
 * 0x0: Increment address
 * 0x1: Decrement address
 * 0x2: Fixed address
 * 0x3: Reserved, setting the field with this value triggers an error exception
 */
#define SMIX_DMA_CH_CTL_SRCADDRCTRL_MASK (0x180U)
#define SMIX_DMA_CH_CTL_SRCADDRCTRL_SHIFT (7U)
#define SMIX_DMA_CH_CTL_SRCADDRCTRL_SET(x) (((uint32_t)(x) << SMIX_DMA_CH_CTL_SRCADDRCTRL_SHIFT) & SMIX_DMA_CH_CTL_SRCADDRCTRL_MASK)
#define SMIX_DMA_CH_CTL_SRCADDRCTRL_GET(x) (((uint32_t)(x) & SMIX_DMA_CH_CTL_SRCADDRCTRL_MASK) >> SMIX_DMA_CH_CTL_SRCADDRCTRL_SHIFT)

/*
 * DSTADDRCTRL (RW)
 *
 * 0x0: Increment address
 * 0x1: Decrement address
 * 0x2: Fixed address
 * 0x3: Reserved, setting the field with this value triggers an error exception
 */
#define SMIX_DMA_CH_CTL_DSTADDRCTRL_MASK (0x60U)
#define SMIX_DMA_CH_CTL_DSTADDRCTRL_SHIFT (5U)
#define SMIX_DMA_CH_CTL_DSTADDRCTRL_SET(x) (((uint32_t)(x) << SMIX_DMA_CH_CTL_DSTADDRCTRL_SHIFT) & SMIX_DMA_CH_CTL_DSTADDRCTRL_MASK)
#define SMIX_DMA_CH_CTL_DSTADDRCTRL_GET(x) (((uint32_t)(x) & SMIX_DMA_CH_CTL_DSTADDRCTRL_MASK) >> SMIX_DMA_CH_CTL_DSTADDRCTRL_SHIFT)

/*
 * ABRT_INT_EN (RW)
 *
 * Abort interrupt enable
 */
#define SMIX_DMA_CH_CTL_ABRT_INT_EN_MASK (0x8U)
#define SMIX_DMA_CH_CTL_ABRT_INT_EN_SHIFT (3U)
#define SMIX_DMA_CH_CTL_ABRT_INT_EN_SET(x) (((uint32_t)(x) << SMIX_DMA_CH_CTL_ABRT_INT_EN_SHIFT) & SMIX_DMA_CH_CTL_ABRT_INT_EN_MASK)
#define SMIX_DMA_CH_CTL_ABRT_INT_EN_GET(x) (((uint32_t)(x) & SMIX_DMA_CH_CTL_ABRT_INT_EN_MASK) >> SMIX_DMA_CH_CTL_ABRT_INT_EN_SHIFT)

/*
 * ERR_INT_EN (RW)
 *
 * Err interrupt enable
 */
#define SMIX_DMA_CH_CTL_ERR_INT_EN_MASK (0x4U)
#define SMIX_DMA_CH_CTL_ERR_INT_EN_SHIFT (2U)
#define SMIX_DMA_CH_CTL_ERR_INT_EN_SET(x) (((uint32_t)(x) << SMIX_DMA_CH_CTL_ERR_INT_EN_SHIFT) & SMIX_DMA_CH_CTL_ERR_INT_EN_MASK)
#define SMIX_DMA_CH_CTL_ERR_INT_EN_GET(x) (((uint32_t)(x) & SMIX_DMA_CH_CTL_ERR_INT_EN_MASK) >> SMIX_DMA_CH_CTL_ERR_INT_EN_SHIFT)

/*
 * TC_INT_EN (RW)
 *
 * TC interrupt enable
 */
#define SMIX_DMA_CH_CTL_TC_INT_EN_MASK (0x2U)
#define SMIX_DMA_CH_CTL_TC_INT_EN_SHIFT (1U)
#define SMIX_DMA_CH_CTL_TC_INT_EN_SET(x) (((uint32_t)(x) << SMIX_DMA_CH_CTL_TC_INT_EN_SHIFT) & SMIX_DMA_CH_CTL_TC_INT_EN_MASK)
#define SMIX_DMA_CH_CTL_TC_INT_EN_GET(x) (((uint32_t)(x) & SMIX_DMA_CH_CTL_TC_INT_EN_MASK) >> SMIX_DMA_CH_CTL_TC_INT_EN_SHIFT)

/*
 * EN (RW)
 *
 * channel enable bit
 */
#define SMIX_DMA_CH_CTL_EN_MASK (0x1U)
#define SMIX_DMA_CH_CTL_EN_SHIFT (0U)
#define SMIX_DMA_CH_CTL_EN_SET(x) (((uint32_t)(x) << SMIX_DMA_CH_CTL_EN_SHIFT) & SMIX_DMA_CH_CTL_EN_MASK)
#define SMIX_DMA_CH_CTL_EN_GET(x) (((uint32_t)(x) & SMIX_DMA_CH_CTL_EN_MASK) >> SMIX_DMA_CH_CTL_EN_SHIFT)

/* Bitfield definition for register of struct array DMA_CH: BURST_COUNT */
/*
 * NUM (RW)
 *
 * the total number of source beats
 */
#define SMIX_DMA_CH_BURST_COUNT_NUM_MASK (0xFFFFFFFFUL)
#define SMIX_DMA_CH_BURST_COUNT_NUM_SHIFT (0U)
#define SMIX_DMA_CH_BURST_COUNT_NUM_SET(x) (((uint32_t)(x) << SMIX_DMA_CH_BURST_COUNT_NUM_SHIFT) & SMIX_DMA_CH_BURST_COUNT_NUM_MASK)
#define SMIX_DMA_CH_BURST_COUNT_NUM_GET(x) (((uint32_t)(x) & SMIX_DMA_CH_BURST_COUNT_NUM_MASK) >> SMIX_DMA_CH_BURST_COUNT_NUM_SHIFT)

/* Bitfield definition for register of struct array DMA_CH: SRCADDR */
/*
 * PTR (RW)
 *
 * source address
 */
#define SMIX_DMA_CH_SRCADDR_PTR_MASK (0xFFFFFFFFUL)
#define SMIX_DMA_CH_SRCADDR_PTR_SHIFT (0U)
#define SMIX_DMA_CH_SRCADDR_PTR_SET(x) (((uint32_t)(x) << SMIX_DMA_CH_SRCADDR_PTR_SHIFT) & SMIX_DMA_CH_SRCADDR_PTR_MASK)
#define SMIX_DMA_CH_SRCADDR_PTR_GET(x) (((uint32_t)(x) & SMIX_DMA_CH_SRCADDR_PTR_MASK) >> SMIX_DMA_CH_SRCADDR_PTR_SHIFT)

/* Bitfield definition for register of struct array DMA_CH: DSTADDR */
/*
 * PTR (RW)
 *
 * destination address
 */
#define SMIX_DMA_CH_DSTADDR_PTR_MASK (0xFFFFFFFFUL)
#define SMIX_DMA_CH_DSTADDR_PTR_SHIFT (0U)
#define SMIX_DMA_CH_DSTADDR_PTR_SET(x) (((uint32_t)(x) << SMIX_DMA_CH_DSTADDR_PTR_SHIFT) & SMIX_DMA_CH_DSTADDR_PTR_MASK)
#define SMIX_DMA_CH_DSTADDR_PTR_GET(x) (((uint32_t)(x) & SMIX_DMA_CH_DSTADDR_PTR_MASK) >> SMIX_DMA_CH_DSTADDR_PTR_SHIFT)

/* Bitfield definition for register of struct array DMA_CH: LLP */
/*
 * PTR (RW)
 *
 * the address pointer for the linked list descriptor
 */
#define SMIX_DMA_CH_LLP_PTR_MASK (0xFFFFFFFFUL)
#define SMIX_DMA_CH_LLP_PTR_SHIFT (0U)
#define SMIX_DMA_CH_LLP_PTR_SET(x) (((uint32_t)(x) << SMIX_DMA_CH_LLP_PTR_SHIFT) & SMIX_DMA_CH_LLP_PTR_MASK)
#define SMIX_DMA_CH_LLP_PTR_GET(x) (((uint32_t)(x) & SMIX_DMA_CH_LLP_PTR_MASK) >> SMIX_DMA_CH_LLP_PTR_SHIFT)

/* Bitfield definition for register: CALSAT_ST */
/*
 * DST (W1C)
 *
 * DST CAL_SAT_ERR. W1C
 */
#define SMIX_CALSAT_ST_DST_MASK (0xC0000000UL)
#define SMIX_CALSAT_ST_DST_SHIFT (30U)
#define SMIX_CALSAT_ST_DST_SET(x) (((uint32_t)(x) << SMIX_CALSAT_ST_DST_SHIFT) & SMIX_CALSAT_ST_DST_MASK)
#define SMIX_CALSAT_ST_DST_GET(x) (((uint32_t)(x) & SMIX_CALSAT_ST_DST_MASK) >> SMIX_CALSAT_ST_DST_SHIFT)

/*
 * SRC (W1C)
 *
 * SRC CAL_SAT_ERR. W1C
 */
#define SMIX_CALSAT_ST_SRC_MASK (0x3FFFU)
#define SMIX_CALSAT_ST_SRC_SHIFT (0U)
#define SMIX_CALSAT_ST_SRC_SET(x) (((uint32_t)(x) << SMIX_CALSAT_ST_SRC_SHIFT) & SMIX_CALSAT_ST_SRC_MASK)
#define SMIX_CALSAT_ST_SRC_GET(x) (((uint32_t)(x) & SMIX_CALSAT_ST_SRC_MASK) >> SMIX_CALSAT_ST_SRC_SHIFT)

/* Bitfield definition for register: FDOT_DONE_ST */
/*
 * DST (W1C)
 *
 * DST fadeout done. W1C
 */
#define SMIX_FDOT_DONE_ST_DST_MASK (0xC0000000UL)
#define SMIX_FDOT_DONE_ST_DST_SHIFT (30U)
#define SMIX_FDOT_DONE_ST_DST_SET(x) (((uint32_t)(x) << SMIX_FDOT_DONE_ST_DST_SHIFT) & SMIX_FDOT_DONE_ST_DST_MASK)
#define SMIX_FDOT_DONE_ST_DST_GET(x) (((uint32_t)(x) & SMIX_FDOT_DONE_ST_DST_MASK) >> SMIX_FDOT_DONE_ST_DST_SHIFT)

/*
 * SRC (W1C)
 *
 * SRC fadeout done. W1C
 */
#define SMIX_FDOT_DONE_ST_SRC_MASK (0x3FFFU)
#define SMIX_FDOT_DONE_ST_SRC_SHIFT (0U)
#define SMIX_FDOT_DONE_ST_SRC_SET(x) (((uint32_t)(x) << SMIX_FDOT_DONE_ST_SRC_SHIFT) & SMIX_FDOT_DONE_ST_SRC_MASK)
#define SMIX_FDOT_DONE_ST_SRC_GET(x) (((uint32_t)(x) & SMIX_FDOT_DONE_ST_SRC_MASK) >> SMIX_FDOT_DONE_ST_SRC_SHIFT)

/* Bitfield definition for register: DATA_ST */
/*
 * DST_DA (RO)
 *
 * DST data available
 */
#define SMIX_DATA_ST_DST_DA_MASK (0xC0000000UL)
#define SMIX_DATA_ST_DST_DA_SHIFT (30U)
#define SMIX_DATA_ST_DST_DA_GET(x) (((uint32_t)(x) & SMIX_DATA_ST_DST_DA_MASK) >> SMIX_DATA_ST_DST_DA_SHIFT)

/*
 * DST_UNDL (RO)
 *
 * DST data underflow
 */
#define SMIX_DATA_ST_DST_UNDL_MASK (0x30000000UL)
#define SMIX_DATA_ST_DST_UNDL_SHIFT (28U)
#define SMIX_DATA_ST_DST_UNDL_GET(x) (((uint32_t)(x) & SMIX_DATA_ST_DST_UNDL_MASK) >> SMIX_DATA_ST_DST_UNDL_SHIFT)

/*
 * SRC_DN (RO)
 *
 * SRC data needed
 */
#define SMIX_DATA_ST_SRC_DN_MASK (0x3FFFU)
#define SMIX_DATA_ST_SRC_DN_SHIFT (0U)
#define SMIX_DATA_ST_SRC_DN_GET(x) (((uint32_t)(x) & SMIX_DATA_ST_SRC_DN_MASK) >> SMIX_DATA_ST_SRC_DN_SHIFT)

/* Bitfield definition for register of struct array DST_CH: CTRL */
/*
 * DATA_UNFL_IE (RW)
 *
 * Data Underflow Error IntEn
 */
#define SMIX_DST_CH_CTRL_DATA_UNFL_IE_MASK (0x100000UL)
#define SMIX_DST_CH_CTRL_DATA_UNFL_IE_SHIFT (20U)
#define SMIX_DST_CH_CTRL_DATA_UNFL_IE_SET(x) (((uint32_t)(x) << SMIX_DST_CH_CTRL_DATA_UNFL_IE_SHIFT) & SMIX_DST_CH_CTRL_DATA_UNFL_IE_MASK)
#define SMIX_DST_CH_CTRL_DATA_UNFL_IE_GET(x) (((uint32_t)(x) & SMIX_DST_CH_CTRL_DATA_UNFL_IE_MASK) >> SMIX_DST_CH_CTRL_DATA_UNFL_IE_SHIFT)

/*
 * THRSH (RW)
 *
 * FIFO threshold for DMA or Int. >= will generate req.  Must be greater or equal than 8. The read burst of DMA should make the fillings in the buffer be greater than 4.
 */
#define SMIX_DST_CH_CTRL_THRSH_MASK (0xFF000UL)
#define SMIX_DST_CH_CTRL_THRSH_SHIFT (12U)
#define SMIX_DST_CH_CTRL_THRSH_SET(x) (((uint32_t)(x) << SMIX_DST_CH_CTRL_THRSH_SHIFT) & SMIX_DST_CH_CTRL_THRSH_MASK)
#define SMIX_DST_CH_CTRL_THRSH_GET(x) (((uint32_t)(x) & SMIX_DST_CH_CTRL_THRSH_MASK) >> SMIX_DST_CH_CTRL_THRSH_SHIFT)

/*
 * CALSAT_INT_EN (RW)
 *
 * Cal Saturation IntEn
 */
#define SMIX_DST_CH_CTRL_CALSAT_INT_EN_MASK (0x800U)
#define SMIX_DST_CH_CTRL_CALSAT_INT_EN_SHIFT (11U)
#define SMIX_DST_CH_CTRL_CALSAT_INT_EN_SET(x) (((uint32_t)(x) << SMIX_DST_CH_CTRL_CALSAT_INT_EN_SHIFT) & SMIX_DST_CH_CTRL_CALSAT_INT_EN_MASK)
#define SMIX_DST_CH_CTRL_CALSAT_INT_EN_GET(x) (((uint32_t)(x) & SMIX_DST_CH_CTRL_CALSAT_INT_EN_MASK) >> SMIX_DST_CH_CTRL_CALSAT_INT_EN_SHIFT)

/*
 * DA_INT_EN (RW)
 *
 * Data Available IntEn
 */
#define SMIX_DST_CH_CTRL_DA_INT_EN_MASK (0x400U)
#define SMIX_DST_CH_CTRL_DA_INT_EN_SHIFT (10U)
#define SMIX_DST_CH_CTRL_DA_INT_EN_SET(x) (((uint32_t)(x) << SMIX_DST_CH_CTRL_DA_INT_EN_SHIFT) & SMIX_DST_CH_CTRL_DA_INT_EN_MASK)
#define SMIX_DST_CH_CTRL_DA_INT_EN_GET(x) (((uint32_t)(x) & SMIX_DST_CH_CTRL_DA_INT_EN_MASK) >> SMIX_DST_CH_CTRL_DA_INT_EN_SHIFT)

/*
 * ADEACTFADEOUT_EN (RW)
 *
 * AutoDeactAfterFadeOut_En:
 * Asserted to enter de-activated mode after fade-out done
 */
#define SMIX_DST_CH_CTRL_ADEACTFADEOUT_EN_MASK (0x200U)
#define SMIX_DST_CH_CTRL_ADEACTFADEOUT_EN_SHIFT (9U)
#define SMIX_DST_CH_CTRL_ADEACTFADEOUT_EN_SET(x) (((uint32_t)(x) << SMIX_DST_CH_CTRL_ADEACTFADEOUT_EN_SHIFT) & SMIX_DST_CH_CTRL_ADEACTFADEOUT_EN_MASK)
#define SMIX_DST_CH_CTRL_ADEACTFADEOUT_EN_GET(x) (((uint32_t)(x) & SMIX_DST_CH_CTRL_ADEACTFADEOUT_EN_MASK) >> SMIX_DST_CH_CTRL_ADEACTFADEOUT_EN_SHIFT)

/*
 * FADEOUT_DONE_IE (RW)
 *
 * Fade-Out interrupt enable
 */
#define SMIX_DST_CH_CTRL_FADEOUT_DONE_IE_MASK (0x100U)
#define SMIX_DST_CH_CTRL_FADEOUT_DONE_IE_SHIFT (8U)
#define SMIX_DST_CH_CTRL_FADEOUT_DONE_IE_SET(x) (((uint32_t)(x) << SMIX_DST_CH_CTRL_FADEOUT_DONE_IE_SHIFT) & SMIX_DST_CH_CTRL_FADEOUT_DONE_IE_MASK)
#define SMIX_DST_CH_CTRL_FADEOUT_DONE_IE_GET(x) (((uint32_t)(x) & SMIX_DST_CH_CTRL_FADEOUT_DONE_IE_MASK) >> SMIX_DST_CH_CTRL_FADEOUT_DONE_IE_SHIFT)

/*
 * DST_DEACT (RW)
 *
 * de-activate the destination channel
 */
#define SMIX_DST_CH_CTRL_DST_DEACT_MASK (0x80U)
#define SMIX_DST_CH_CTRL_DST_DEACT_SHIFT (7U)
#define SMIX_DST_CH_CTRL_DST_DEACT_SET(x) (((uint32_t)(x) << SMIX_DST_CH_CTRL_DST_DEACT_SHIFT) & SMIX_DST_CH_CTRL_DST_DEACT_MASK)
#define SMIX_DST_CH_CTRL_DST_DEACT_GET(x) (((uint32_t)(x) & SMIX_DST_CH_CTRL_DST_DEACT_MASK) >> SMIX_DST_CH_CTRL_DST_DEACT_SHIFT)

/*
 * DST_ACT (RW)
 *
 * activate the destination channel
 */
#define SMIX_DST_CH_CTRL_DST_ACT_MASK (0x40U)
#define SMIX_DST_CH_CTRL_DST_ACT_SHIFT (6U)
#define SMIX_DST_CH_CTRL_DST_ACT_SET(x) (((uint32_t)(x) << SMIX_DST_CH_CTRL_DST_ACT_SHIFT) & SMIX_DST_CH_CTRL_DST_ACT_MASK)
#define SMIX_DST_CH_CTRL_DST_ACT_GET(x) (((uint32_t)(x) & SMIX_DST_CH_CTRL_DST_ACT_MASK) >> SMIX_DST_CH_CTRL_DST_ACT_SHIFT)

/*
 * DSTFADOUT_MEN (RW)
 *
 * Manual FadeOut_Ctrl for destionation. Auto clear.
 */
#define SMIX_DST_CH_CTRL_DSTFADOUT_MEN_MASK (0x20U)
#define SMIX_DST_CH_CTRL_DSTFADOUT_MEN_SHIFT (5U)
#define SMIX_DST_CH_CTRL_DSTFADOUT_MEN_SET(x) (((uint32_t)(x) << SMIX_DST_CH_CTRL_DSTFADOUT_MEN_SHIFT) & SMIX_DST_CH_CTRL_DSTFADOUT_MEN_MASK)
#define SMIX_DST_CH_CTRL_DSTFADOUT_MEN_GET(x) (((uint32_t)(x) & SMIX_DST_CH_CTRL_DSTFADOUT_MEN_MASK) >> SMIX_DST_CH_CTRL_DSTFADOUT_MEN_SHIFT)

/*
 * DSTFADOUT_AEN (RW)
 *
 * Automatically FadeOut_Ctrl for destionation. Only effective after DST_AFADEOUT is assigned a non-zero value
 */
#define SMIX_DST_CH_CTRL_DSTFADOUT_AEN_MASK (0x10U)
#define SMIX_DST_CH_CTRL_DSTFADOUT_AEN_SHIFT (4U)
#define SMIX_DST_CH_CTRL_DSTFADOUT_AEN_SET(x) (((uint32_t)(x) << SMIX_DST_CH_CTRL_DSTFADOUT_AEN_SHIFT) & SMIX_DST_CH_CTRL_DSTFADOUT_AEN_MASK)
#define SMIX_DST_CH_CTRL_DSTFADOUT_AEN_GET(x) (((uint32_t)(x) & SMIX_DST_CH_CTRL_DSTFADOUT_AEN_MASK) >> SMIX_DST_CH_CTRL_DSTFADOUT_AEN_SHIFT)

/*
 * DSTFADIN_EN (RW)
 *
 * FadeIn_Ctrl for destionation. Auto clear.
 */
#define SMIX_DST_CH_CTRL_DSTFADIN_EN_MASK (0x8U)
#define SMIX_DST_CH_CTRL_DSTFADIN_EN_SHIFT (3U)
#define SMIX_DST_CH_CTRL_DSTFADIN_EN_SET(x) (((uint32_t)(x) << SMIX_DST_CH_CTRL_DSTFADIN_EN_SHIFT) & SMIX_DST_CH_CTRL_DSTFADIN_EN_MASK)
#define SMIX_DST_CH_CTRL_DSTFADIN_EN_GET(x) (((uint32_t)(x) & SMIX_DST_CH_CTRL_DSTFADIN_EN_MASK) >> SMIX_DST_CH_CTRL_DSTFADIN_EN_SHIFT)

/*
 * DST_EN (RW)
 *
 * Dst enabled. When disabled, clear the FIFO pointers.
 */
#define SMIX_DST_CH_CTRL_DST_EN_MASK (0x4U)
#define SMIX_DST_CH_CTRL_DST_EN_SHIFT (2U)
#define SMIX_DST_CH_CTRL_DST_EN_SET(x) (((uint32_t)(x) << SMIX_DST_CH_CTRL_DST_EN_SHIFT) & SMIX_DST_CH_CTRL_DST_EN_MASK)
#define SMIX_DST_CH_CTRL_DST_EN_GET(x) (((uint32_t)(x) & SMIX_DST_CH_CTRL_DST_EN_MASK) >> SMIX_DST_CH_CTRL_DST_EN_SHIFT)

/*
 * SOFTRST (RW)
 *
 * Soft reset
 */
#define SMIX_DST_CH_CTRL_SOFTRST_MASK (0x2U)
#define SMIX_DST_CH_CTRL_SOFTRST_SHIFT (1U)
#define SMIX_DST_CH_CTRL_SOFTRST_SET(x) (((uint32_t)(x) << SMIX_DST_CH_CTRL_SOFTRST_SHIFT) & SMIX_DST_CH_CTRL_SOFTRST_MASK)
#define SMIX_DST_CH_CTRL_SOFTRST_GET(x) (((uint32_t)(x) & SMIX_DST_CH_CTRL_SOFTRST_MASK) >> SMIX_DST_CH_CTRL_SOFTRST_SHIFT)

/*
 * MIXER_EN (RW)
 *
 * mixer function enable.
 */
#define SMIX_DST_CH_CTRL_MIXER_EN_MASK (0x1U)
#define SMIX_DST_CH_CTRL_MIXER_EN_SHIFT (0U)
#define SMIX_DST_CH_CTRL_MIXER_EN_SET(x) (((uint32_t)(x) << SMIX_DST_CH_CTRL_MIXER_EN_SHIFT) & SMIX_DST_CH_CTRL_MIXER_EN_MASK)
#define SMIX_DST_CH_CTRL_MIXER_EN_GET(x) (((uint32_t)(x) & SMIX_DST_CH_CTRL_MIXER_EN_MASK) >> SMIX_DST_CH_CTRL_MIXER_EN_SHIFT)

/* Bitfield definition for register of struct array DST_CH: GAIN */
/*
 * VAL (RW)
 *
 * Unsigned Int, with 12 fractional bits. . The top 3 bits are for shift. Same as SHFT_CTR[2:0]
 */
#define SMIX_DST_CH_GAIN_VAL_MASK (0x7FFFU)
#define SMIX_DST_CH_GAIN_VAL_SHIFT (0U)
#define SMIX_DST_CH_GAIN_VAL_SET(x) (((uint32_t)(x) << SMIX_DST_CH_GAIN_VAL_SHIFT) & SMIX_DST_CH_GAIN_VAL_MASK)
#define SMIX_DST_CH_GAIN_VAL_GET(x) (((uint32_t)(x) & SMIX_DST_CH_GAIN_VAL_MASK) >> SMIX_DST_CH_GAIN_VAL_SHIFT)

/* Bitfield definition for register of struct array DST_CH: BUFSIZE */
/*
 * MAX_IDX (RW)
 *
 * The total length of the dst stream -1. If zero, means there is no  end of the stream.
 */
#define SMIX_DST_CH_BUFSIZE_MAX_IDX_MASK (0xFFFFFFFFUL)
#define SMIX_DST_CH_BUFSIZE_MAX_IDX_SHIFT (0U)
#define SMIX_DST_CH_BUFSIZE_MAX_IDX_SET(x) (((uint32_t)(x) << SMIX_DST_CH_BUFSIZE_MAX_IDX_SHIFT) & SMIX_DST_CH_BUFSIZE_MAX_IDX_MASK)
#define SMIX_DST_CH_BUFSIZE_MAX_IDX_GET(x) (((uint32_t)(x) & SMIX_DST_CH_BUFSIZE_MAX_IDX_MASK) >> SMIX_DST_CH_BUFSIZE_MAX_IDX_SHIFT)

/* Bitfield definition for register of struct array DST_CH: FADEIN */
/*
 * DELTA (RW)
 *
 * Fade-in delta for linear fading in from 0 to 1 (about at most 20s for 48kHz sampled sound)
 * (Using only top 14 bits for mul)
 */
#define SMIX_DST_CH_FADEIN_DELTA_MASK (0xFFFFFUL)
#define SMIX_DST_CH_FADEIN_DELTA_SHIFT (0U)
#define SMIX_DST_CH_FADEIN_DELTA_SET(x) (((uint32_t)(x) << SMIX_DST_CH_FADEIN_DELTA_SHIFT) & SMIX_DST_CH_FADEIN_DELTA_MASK)
#define SMIX_DST_CH_FADEIN_DELTA_GET(x) (((uint32_t)(x) & SMIX_DST_CH_FADEIN_DELTA_MASK) >> SMIX_DST_CH_FADEIN_DELTA_SHIFT)

/* Bitfield definition for register of struct array DST_CH: FADEOUT */
/*
 * DELTA (RW)
 *
 * Fade out in 2^DELTA samples. Now DELTA can be at most 14。
 */
#define SMIX_DST_CH_FADEOUT_DELTA_MASK (0xFFFFFUL)
#define SMIX_DST_CH_FADEOUT_DELTA_SHIFT (0U)
#define SMIX_DST_CH_FADEOUT_DELTA_SET(x) (((uint32_t)(x) << SMIX_DST_CH_FADEOUT_DELTA_SHIFT) & SMIX_DST_CH_FADEOUT_DELTA_MASK)
#define SMIX_DST_CH_FADEOUT_DELTA_GET(x) (((uint32_t)(x) & SMIX_DST_CH_FADEOUT_DELTA_MASK) >> SMIX_DST_CH_FADEOUT_DELTA_SHIFT)

/* Bitfield definition for register of struct array DST_CH: ST */
/*
 * FIFO_FILLINGS (RO)
 *
 * destination channel output FIFO fillings
 */
#define SMIX_DST_CH_ST_FIFO_FILLINGS_MASK (0x7FC0U)
#define SMIX_DST_CH_ST_FIFO_FILLINGS_SHIFT (6U)
#define SMIX_DST_CH_ST_FIFO_FILLINGS_GET(x) (((uint32_t)(x) & SMIX_DST_CH_ST_FIFO_FILLINGS_MASK) >> SMIX_DST_CH_ST_FIFO_FILLINGS_SHIFT)

/*
 * FDOUT_DONE (RO)
 *
 * Fade-Out Done. W1C
 */
#define SMIX_DST_CH_ST_FDOUT_DONE_MASK (0x20U)
#define SMIX_DST_CH_ST_FDOUT_DONE_SHIFT (5U)
#define SMIX_DST_CH_ST_FDOUT_DONE_GET(x) (((uint32_t)(x) & SMIX_DST_CH_ST_FDOUT_DONE_MASK) >> SMIX_DST_CH_ST_FDOUT_DONE_SHIFT)

/*
 * CALSAT (RO)
 *
 * Saturate Error Found. W1C
 */
#define SMIX_DST_CH_ST_CALSAT_MASK (0x10U)
#define SMIX_DST_CH_ST_CALSAT_SHIFT (4U)
#define SMIX_DST_CH_ST_CALSAT_GET(x) (((uint32_t)(x) & SMIX_DST_CH_ST_CALSAT_MASK) >> SMIX_DST_CH_ST_CALSAT_SHIFT)

/*
 * DA (RO)
 *
 * Data Available
 */
#define SMIX_DST_CH_ST_DA_MASK (0x8U)
#define SMIX_DST_CH_ST_DA_SHIFT (3U)
#define SMIX_DST_CH_ST_DA_GET(x) (((uint32_t)(x) & SMIX_DST_CH_ST_DA_MASK) >> SMIX_DST_CH_ST_DA_SHIFT)

/*
 * MODE (RO)
 *
 * The modes are:
 * Mode 0: Disabled: after reset. Program the registers, and DSTn_CTRL [DST_EN] to enter Mode 1.
 * Mode 1: Enabled and not-activated. wait for DSTn_CTRL [DSTFADIN_EN] or DSTn_CTRL [DST_ACT], jump to Mode 3 or Mode 4 based on whether Fade-in enabled.
 * Mode 3: Enabled and activated and fade-in in progress: Can not be fade out. Will send data to DMA. Jump to Mode 4 after fadin op done.
 * Mode 4: Enabled and activated and done fade-in, no fade-out yet: Can be fade out. Will send data to DMA.
 * Mode 5: Enabled and activated and fade-out in progress: After faded out OP. Will send data to DMA. Will transfer to mode 6 or mode 7 depending on the DSTn_CTRL [ADeactFadeOut_En] cfg
 * Mode 6: Enabled and activated and faded-out: faded out is done. Will send data to DMA. Will transfer to mode 7 if manual deactivated.
 * Mode 7: Enabled and De-activated: If configured to enter this mode, after auto or manuallly fade-out, or after manual de-activated. Won't send data to DMA. Won't gen data avail signals. Intf register can be programmed. Will change to Mode 3 or Mode 4  after manual ACT or Fade-in CMD. Will transfer to Mode 0 if DSTn_CTRL [DST_EN] is assigned 0. To support a new stream or, to continue the old stream after a pause.
 */
#define SMIX_DST_CH_ST_MODE_MASK (0x7U)
#define SMIX_DST_CH_ST_MODE_SHIFT (0U)
#define SMIX_DST_CH_ST_MODE_GET(x) (((uint32_t)(x) & SMIX_DST_CH_ST_MODE_MASK) >> SMIX_DST_CH_ST_MODE_SHIFT)

/* Bitfield definition for register of struct array DST_CH: DATA */
/*
 * VAL (RO)
 *
 * Output data buffer
 */
#define SMIX_DST_CH_DATA_VAL_MASK (0xFFFFFFFFUL)
#define SMIX_DST_CH_DATA_VAL_SHIFT (0U)
#define SMIX_DST_CH_DATA_VAL_GET(x) (((uint32_t)(x) & SMIX_DST_CH_DATA_VAL_MASK) >> SMIX_DST_CH_DATA_VAL_SHIFT)

/* Bitfield definition for register of struct array DST_CH: SOURCE_EN */
/*
 * VAL (RW)
 *
 * After enabled, Data needed req will be asserted. DMA can feed in data. The channel will join in the sum operation of mixer operation.
 */
#define SMIX_DST_CH_SOURCE_EN_VAL_MASK (0xFFU)
#define SMIX_DST_CH_SOURCE_EN_VAL_SHIFT (0U)
#define SMIX_DST_CH_SOURCE_EN_VAL_SET(x) (((uint32_t)(x) << SMIX_DST_CH_SOURCE_EN_VAL_SHIFT) & SMIX_DST_CH_SOURCE_EN_VAL_MASK)
#define SMIX_DST_CH_SOURCE_EN_VAL_GET(x) (((uint32_t)(x) & SMIX_DST_CH_SOURCE_EN_VAL_MASK) >> SMIX_DST_CH_SOURCE_EN_VAL_SHIFT)

/* Bitfield definition for register of struct array DST_CH: SOURCE_ACT */
/*
 * VAL (WO)
 *
 * Manually Activate the channel
 */
#define SMIX_DST_CH_SOURCE_ACT_VAL_MASK (0xFFU)
#define SMIX_DST_CH_SOURCE_ACT_VAL_SHIFT (0U)
#define SMIX_DST_CH_SOURCE_ACT_VAL_SET(x) (((uint32_t)(x) << SMIX_DST_CH_SOURCE_ACT_VAL_SHIFT) & SMIX_DST_CH_SOURCE_ACT_VAL_MASK)
#define SMIX_DST_CH_SOURCE_ACT_VAL_GET(x) (((uint32_t)(x) & SMIX_DST_CH_SOURCE_ACT_VAL_MASK) >> SMIX_DST_CH_SOURCE_ACT_VAL_SHIFT)

/* Bitfield definition for register of struct array DST_CH: SOURCE_DEACT */
/*
 * VAL (WO)
 *
 * Manually DeActivate the channel
 */
#define SMIX_DST_CH_SOURCE_DEACT_VAL_MASK (0xFFU)
#define SMIX_DST_CH_SOURCE_DEACT_VAL_SHIFT (0U)
#define SMIX_DST_CH_SOURCE_DEACT_VAL_SET(x) (((uint32_t)(x) << SMIX_DST_CH_SOURCE_DEACT_VAL_SHIFT) & SMIX_DST_CH_SOURCE_DEACT_VAL_MASK)
#define SMIX_DST_CH_SOURCE_DEACT_VAL_GET(x) (((uint32_t)(x) & SMIX_DST_CH_SOURCE_DEACT_VAL_MASK) >> SMIX_DST_CH_SOURCE_DEACT_VAL_SHIFT)

/* Bitfield definition for register of struct array DST_CH: SOURCE_FADEIN_CTRL */
/*
 * AOP (RW)
 *
 * Asserted to start fade-in operation. When the amplification factors are stable, auto clear.
 */
#define SMIX_DST_CH_SOURCE_FADEIN_CTRL_AOP_MASK (0xFFU)
#define SMIX_DST_CH_SOURCE_FADEIN_CTRL_AOP_SHIFT (0U)
#define SMIX_DST_CH_SOURCE_FADEIN_CTRL_AOP_SET(x) (((uint32_t)(x) << SMIX_DST_CH_SOURCE_FADEIN_CTRL_AOP_SHIFT) & SMIX_DST_CH_SOURCE_FADEIN_CTRL_AOP_MASK)
#define SMIX_DST_CH_SOURCE_FADEIN_CTRL_AOP_GET(x) (((uint32_t)(x) & SMIX_DST_CH_SOURCE_FADEIN_CTRL_AOP_MASK) >> SMIX_DST_CH_SOURCE_FADEIN_CTRL_AOP_SHIFT)

/* Bitfield definition for register of struct array DST_CH: DEACT_ST */
/*
 * DST_DEACT (RO)
 *
 * Asserted when in de-active mode
 */
#define SMIX_DST_CH_DEACT_ST_DST_DEACT_MASK (0x80000000UL)
#define SMIX_DST_CH_DEACT_ST_DST_DEACT_SHIFT (31U)
#define SMIX_DST_CH_DEACT_ST_DST_DEACT_GET(x) (((uint32_t)(x) & SMIX_DST_CH_DEACT_ST_DST_DEACT_MASK) >> SMIX_DST_CH_DEACT_ST_DST_DEACT_SHIFT)

/*
 * SRC_DEACT_ST (RO)
 *
 * Asserted when in de-active mode
 */
#define SMIX_DST_CH_DEACT_ST_SRC_DEACT_ST_MASK (0xFFU)
#define SMIX_DST_CH_DEACT_ST_SRC_DEACT_ST_SHIFT (0U)
#define SMIX_DST_CH_DEACT_ST_SRC_DEACT_ST_GET(x) (((uint32_t)(x) & SMIX_DST_CH_DEACT_ST_SRC_DEACT_ST_MASK) >> SMIX_DST_CH_DEACT_ST_SRC_DEACT_ST_SHIFT)

/* Bitfield definition for register of struct array DST_CH: SOURCE_MFADEOUT_CTRL */
/*
 * OP (RW)
 *
 * Asserted to start fade-out operation. When the amplification factors are stable, auto clear.
 */
#define SMIX_DST_CH_SOURCE_MFADEOUT_CTRL_OP_MASK (0xFFU)
#define SMIX_DST_CH_SOURCE_MFADEOUT_CTRL_OP_SHIFT (0U)
#define SMIX_DST_CH_SOURCE_MFADEOUT_CTRL_OP_SET(x) (((uint32_t)(x) << SMIX_DST_CH_SOURCE_MFADEOUT_CTRL_OP_SHIFT) & SMIX_DST_CH_SOURCE_MFADEOUT_CTRL_OP_MASK)
#define SMIX_DST_CH_SOURCE_MFADEOUT_CTRL_OP_GET(x) (((uint32_t)(x) & SMIX_DST_CH_SOURCE_MFADEOUT_CTRL_OP_MASK) >> SMIX_DST_CH_SOURCE_MFADEOUT_CTRL_OP_SHIFT)

/* Bitfield definition for register of struct array SOURCE_CH: CTRL */
/*
 * FIFO_RESET (RW)
 *
 * Asserted to reset FIFO pointer. Cleared to exit reset state.
 */
#define SMIX_SOURCE_CH_CTRL_FIFO_RESET_MASK (0x200000UL)
#define SMIX_SOURCE_CH_CTRL_FIFO_RESET_SHIFT (21U)
#define SMIX_SOURCE_CH_CTRL_FIFO_RESET_SET(x) (((uint32_t)(x) << SMIX_SOURCE_CH_CTRL_FIFO_RESET_SHIFT) & SMIX_SOURCE_CH_CTRL_FIFO_RESET_MASK)
#define SMIX_SOURCE_CH_CTRL_FIFO_RESET_GET(x) (((uint32_t)(x) & SMIX_SOURCE_CH_CTRL_FIFO_RESET_MASK) >> SMIX_SOURCE_CH_CTRL_FIFO_RESET_SHIFT)

/*
 * THRSH (RW)
 *
 * FIFO threshold for DMA or Int. <= will generate req. Must be greater or equal than 8. This threshold is also used to trgger the internal FIR operation. To avoid the reading and writing to the same address in the memory block, the threshold should greater than 4.
 */
#define SMIX_SOURCE_CH_CTRL_THRSH_MASK (0x1FE000UL)
#define SMIX_SOURCE_CH_CTRL_THRSH_SHIFT (13U)
#define SMIX_SOURCE_CH_CTRL_THRSH_SET(x) (((uint32_t)(x) << SMIX_SOURCE_CH_CTRL_THRSH_SHIFT) & SMIX_SOURCE_CH_CTRL_THRSH_MASK)
#define SMIX_SOURCE_CH_CTRL_THRSH_GET(x) (((uint32_t)(x) & SMIX_SOURCE_CH_CTRL_THRSH_MASK) >> SMIX_SOURCE_CH_CTRL_THRSH_SHIFT)

/*
 * CALSAT_INT_EN (RW)
 *
 * Cal Saturation IntEn
 */
#define SMIX_SOURCE_CH_CTRL_CALSAT_INT_EN_MASK (0x1000U)
#define SMIX_SOURCE_CH_CTRL_CALSAT_INT_EN_SHIFT (12U)
#define SMIX_SOURCE_CH_CTRL_CALSAT_INT_EN_SET(x) (((uint32_t)(x) << SMIX_SOURCE_CH_CTRL_CALSAT_INT_EN_SHIFT) & SMIX_SOURCE_CH_CTRL_CALSAT_INT_EN_MASK)
#define SMIX_SOURCE_CH_CTRL_CALSAT_INT_EN_GET(x) (((uint32_t)(x) & SMIX_SOURCE_CH_CTRL_CALSAT_INT_EN_MASK) >> SMIX_SOURCE_CH_CTRL_CALSAT_INT_EN_SHIFT)

/*
 * DN_INT_EN (RW)
 *
 * Data Needed IntEn
 */
#define SMIX_SOURCE_CH_CTRL_DN_INT_EN_MASK (0x800U)
#define SMIX_SOURCE_CH_CTRL_DN_INT_EN_SHIFT (11U)
#define SMIX_SOURCE_CH_CTRL_DN_INT_EN_SET(x) (((uint32_t)(x) << SMIX_SOURCE_CH_CTRL_DN_INT_EN_SHIFT) & SMIX_SOURCE_CH_CTRL_DN_INT_EN_MASK)
#define SMIX_SOURCE_CH_CTRL_DN_INT_EN_GET(x) (((uint32_t)(x) & SMIX_SOURCE_CH_CTRL_DN_INT_EN_MASK) >> SMIX_SOURCE_CH_CTRL_DN_INT_EN_SHIFT)

/*
 * SHFT_CTRL (RW)
 *
 * Shift operation after FIR
 * 0: no shift (when no upsampling or up-sampling-by-2 or up-sampling-by-3)
 * 1: left-shift-by-1 (when up-sampling-by-4 or up-sampling-by-6)
 * 2: left-shift-by-1 (when up-sampling-by-8 or up-sampling-by-12)
 * 7: /2  (when rate /2)
 * Other n: shift-left-by-n, but not suggested to be used.
 */
#define SMIX_SOURCE_CH_CTRL_SHFT_CTRL_MASK (0x700U)
#define SMIX_SOURCE_CH_CTRL_SHFT_CTRL_SHIFT (8U)
#define SMIX_SOURCE_CH_CTRL_SHFT_CTRL_SET(x) (((uint32_t)(x) << SMIX_SOURCE_CH_CTRL_SHFT_CTRL_SHIFT) & SMIX_SOURCE_CH_CTRL_SHFT_CTRL_MASK)
#define SMIX_SOURCE_CH_CTRL_SHFT_CTRL_GET(x) (((uint32_t)(x) & SMIX_SOURCE_CH_CTRL_SHFT_CTRL_MASK) >> SMIX_SOURCE_CH_CTRL_SHFT_CTRL_SHIFT)

/*
 * AUTODEACTAFTERFADEOUT_EN (RW)
 *
 * Asserted to enter de-activated mode after fade-out done
 */
#define SMIX_SOURCE_CH_CTRL_AUTODEACTAFTERFADEOUT_EN_MASK (0x80U)
#define SMIX_SOURCE_CH_CTRL_AUTODEACTAFTERFADEOUT_EN_SHIFT (7U)
#define SMIX_SOURCE_CH_CTRL_AUTODEACTAFTERFADEOUT_EN_SET(x) (((uint32_t)(x) << SMIX_SOURCE_CH_CTRL_AUTODEACTAFTERFADEOUT_EN_SHIFT) & SMIX_SOURCE_CH_CTRL_AUTODEACTAFTERFADEOUT_EN_MASK)
#define SMIX_SOURCE_CH_CTRL_AUTODEACTAFTERFADEOUT_EN_GET(x) (((uint32_t)(x) & SMIX_SOURCE_CH_CTRL_AUTODEACTAFTERFADEOUT_EN_MASK) >> SMIX_SOURCE_CH_CTRL_AUTODEACTAFTERFADEOUT_EN_SHIFT)

/*
 * FADEOUT_DONE_IE (RW)
 *
 * Fade-Out interrupt enable
 */
#define SMIX_SOURCE_CH_CTRL_FADEOUT_DONE_IE_MASK (0x40U)
#define SMIX_SOURCE_CH_CTRL_FADEOUT_DONE_IE_SHIFT (6U)
#define SMIX_SOURCE_CH_CTRL_FADEOUT_DONE_IE_SET(x) (((uint32_t)(x) << SMIX_SOURCE_CH_CTRL_FADEOUT_DONE_IE_SHIFT) & SMIX_SOURCE_CH_CTRL_FADEOUT_DONE_IE_MASK)
#define SMIX_SOURCE_CH_CTRL_FADEOUT_DONE_IE_GET(x) (((uint32_t)(x) & SMIX_SOURCE_CH_CTRL_FADEOUT_DONE_IE_MASK) >> SMIX_SOURCE_CH_CTRL_FADEOUT_DONE_IE_SHIFT)

/*
 * RATECONV (RW)
 *
 * 0: no rate conversion
 * 1: up-conversion x2
 * 2: up-conversion x3
 * 3: up-conversion x4
 * 4: up-conversion x6
 * 5: up-conversion x8
 * 6: up-conversion x12
 * 7: down-conversion /2
 */
#define SMIX_SOURCE_CH_CTRL_RATECONV_MASK (0x7U)
#define SMIX_SOURCE_CH_CTRL_RATECONV_SHIFT (0U)
#define SMIX_SOURCE_CH_CTRL_RATECONV_SET(x) (((uint32_t)(x) << SMIX_SOURCE_CH_CTRL_RATECONV_SHIFT) & SMIX_SOURCE_CH_CTRL_RATECONV_MASK)
#define SMIX_SOURCE_CH_CTRL_RATECONV_GET(x) (((uint32_t)(x) & SMIX_SOURCE_CH_CTRL_RATECONV_MASK) >> SMIX_SOURCE_CH_CTRL_RATECONV_SHIFT)

/* Bitfield definition for register of struct array SOURCE_CH: GAIN */
/*
 * VAL (RW)
 *
 * Unsigned Int, with 12 fractional bits. The top 3 bits are for shift. Same as SHFT_CTR[2:0].
 */
#define SMIX_SOURCE_CH_GAIN_VAL_MASK (0x7FFFU)
#define SMIX_SOURCE_CH_GAIN_VAL_SHIFT (0U)
#define SMIX_SOURCE_CH_GAIN_VAL_SET(x) (((uint32_t)(x) << SMIX_SOURCE_CH_GAIN_VAL_SHIFT) & SMIX_SOURCE_CH_GAIN_VAL_MASK)
#define SMIX_SOURCE_CH_GAIN_VAL_GET(x) (((uint32_t)(x) & SMIX_SOURCE_CH_GAIN_VAL_MASK) >> SMIX_SOURCE_CH_GAIN_VAL_SHIFT)

/* Bitfield definition for register of struct array SOURCE_CH: FADEIN */
/*
 * DELTA (RW)
 *
 * Fade -in confg.
 */
#define SMIX_SOURCE_CH_FADEIN_DELTA_MASK (0xFFFFFUL)
#define SMIX_SOURCE_CH_FADEIN_DELTA_SHIFT (0U)
#define SMIX_SOURCE_CH_FADEIN_DELTA_SET(x) (((uint32_t)(x) << SMIX_SOURCE_CH_FADEIN_DELTA_SHIFT) & SMIX_SOURCE_CH_FADEIN_DELTA_MASK)
#define SMIX_SOURCE_CH_FADEIN_DELTA_GET(x) (((uint32_t)(x) & SMIX_SOURCE_CH_FADEIN_DELTA_MASK) >> SMIX_SOURCE_CH_FADEIN_DELTA_SHIFT)

/* Bitfield definition for register of struct array SOURCE_CH: FADEOUT */
/*
 * DELTA (RW)
 *
 * Fade out in 2^DELTA samples. Now DELTA can be at most 14。
 */
#define SMIX_SOURCE_CH_FADEOUT_DELTA_MASK (0xFFFFFUL)
#define SMIX_SOURCE_CH_FADEOUT_DELTA_SHIFT (0U)
#define SMIX_SOURCE_CH_FADEOUT_DELTA_SET(x) (((uint32_t)(x) << SMIX_SOURCE_CH_FADEOUT_DELTA_SHIFT) & SMIX_SOURCE_CH_FADEOUT_DELTA_MASK)
#define SMIX_SOURCE_CH_FADEOUT_DELTA_GET(x) (((uint32_t)(x) & SMIX_SOURCE_CH_FADEOUT_DELTA_MASK) >> SMIX_SOURCE_CH_FADEOUT_DELTA_SHIFT)

/* Bitfield definition for register of struct array SOURCE_CH: BUFSIZE */
/*
 * MAXIDX (RW)
 *
 * unit as 16-bits per sample. Zero means no length limit. = Act Len-1.
 * The actual length is the up_rate*(input_data_length-4).
 * If the filter processing is down-sampling, the value of up_rate above is 1.
 * If the filter processing is up-sampling, the value of up_rate above is the up-sampling rate.
 */
#define SMIX_SOURCE_CH_BUFSIZE_MAXIDX_MASK (0xFFFFFFFFUL)
#define SMIX_SOURCE_CH_BUFSIZE_MAXIDX_SHIFT (0U)
#define SMIX_SOURCE_CH_BUFSIZE_MAXIDX_SET(x) (((uint32_t)(x) << SMIX_SOURCE_CH_BUFSIZE_MAXIDX_SHIFT) & SMIX_SOURCE_CH_BUFSIZE_MAXIDX_MASK)
#define SMIX_SOURCE_CH_BUFSIZE_MAXIDX_GET(x) (((uint32_t)(x) & SMIX_SOURCE_CH_BUFSIZE_MAXIDX_MASK) >> SMIX_SOURCE_CH_BUFSIZE_MAXIDX_SHIFT)

/* Bitfield definition for register of struct array SOURCE_CH: ST */
/*
 * FIFO_FILLINGS (RO)
 *
 * The fillings of input FIFO.
 */
#define SMIX_SOURCE_CH_ST_FIFO_FILLINGS_MASK (0x7FC00UL)
#define SMIX_SOURCE_CH_ST_FIFO_FILLINGS_SHIFT (10U)
#define SMIX_SOURCE_CH_ST_FIFO_FILLINGS_GET(x) (((uint32_t)(x) & SMIX_SOURCE_CH_ST_FIFO_FILLINGS_MASK) >> SMIX_SOURCE_CH_ST_FIFO_FILLINGS_SHIFT)

/*
 * FDOUT_DONE (W1C)
 *
 * Fade-Out Done. W1C
 */
#define SMIX_SOURCE_CH_ST_FDOUT_DONE_MASK (0x200U)
#define SMIX_SOURCE_CH_ST_FDOUT_DONE_SHIFT (9U)
#define SMIX_SOURCE_CH_ST_FDOUT_DONE_SET(x) (((uint32_t)(x) << SMIX_SOURCE_CH_ST_FDOUT_DONE_SHIFT) & SMIX_SOURCE_CH_ST_FDOUT_DONE_MASK)
#define SMIX_SOURCE_CH_ST_FDOUT_DONE_GET(x) (((uint32_t)(x) & SMIX_SOURCE_CH_ST_FDOUT_DONE_MASK) >> SMIX_SOURCE_CH_ST_FDOUT_DONE_SHIFT)

/*
 * CALSAT (W1C)
 *
 * Calculation saturation status. W1C
 */
#define SMIX_SOURCE_CH_ST_CALSAT_MASK (0x100U)
#define SMIX_SOURCE_CH_ST_CALSAT_SHIFT (8U)
#define SMIX_SOURCE_CH_ST_CALSAT_SET(x) (((uint32_t)(x) << SMIX_SOURCE_CH_ST_CALSAT_SHIFT) & SMIX_SOURCE_CH_ST_CALSAT_MASK)
#define SMIX_SOURCE_CH_ST_CALSAT_GET(x) (((uint32_t)(x) & SMIX_SOURCE_CH_ST_CALSAT_MASK) >> SMIX_SOURCE_CH_ST_CALSAT_SHIFT)

/*
 * DN (RO)
 *
 * Data needed flag
 */
#define SMIX_SOURCE_CH_ST_DN_MASK (0x80U)
#define SMIX_SOURCE_CH_ST_DN_SHIFT (7U)
#define SMIX_SOURCE_CH_ST_DN_GET(x) (((uint32_t)(x) & SMIX_SOURCE_CH_ST_DN_MASK) >> SMIX_SOURCE_CH_ST_DN_SHIFT)

/*
 * FIRPHASE (RO)
 *
 * the poly phase counter
 */
#define SMIX_SOURCE_CH_ST_FIRPHASE_MASK (0x78U)
#define SMIX_SOURCE_CH_ST_FIRPHASE_SHIFT (3U)
#define SMIX_SOURCE_CH_ST_FIRPHASE_GET(x) (((uint32_t)(x) & SMIX_SOURCE_CH_ST_FIRPHASE_MASK) >> SMIX_SOURCE_CH_ST_FIRPHASE_SHIFT)

/*
 * MODE (RO)
 *
 * The modes are:
 * Mode 0: Disabled: after reset. Program the registers, and DSTx_SRC_EN[n] to enter Mode 1.
 * Mode 1: Enabled but not activated: After Enabled. Data needed signal can send out, can receive DMA data. Will enter Mode 2 after manual ACT or Fade-in CMD
 * Mode 2: Enabled and activated and buffer feed-in in progress: Can not be fade out. Will consume data from DMA. If not enter due to Fade-in CMD, will enter Mode 4, else enter Mode 3. This mode is used to make the channel in MIX only after initial data are ready, thus will not stall mix operation due to the lackness of data of this channel omly.
 * Mode 3: Enabled and activated and fade-in in progress: Can not be fade out. Will consume data from DMA.
 * Mode 4: Enabled and activated and done fade-in, no fade-out yet: Can be fade out. Will consume data from DMA.
 * Mode 5: Enabled and activated and fade-out in progress: After faded out done. Will consume data from DMA. Will transfer to mode 6 or mode 7 depending on the SRCn_CTRL[AutoDeactAfterFadeOut_En] cfg
 * Mode 6: Enabled and activated and faded-out: faded out is done. Will consume data from DMA. Will transfer to mode 7 if manual deactivated.
 * Mode 7: Enabled and De-activated: If configured to enter this mode, after auto or manuallly fade-out, or after manual de-activated. Won't consume data from DMA. Won't gen data needed signals. Intf register can be programmed. Will change to Mode 2 after manual ACT or Fade-in CMD. Will transfer to Mode 0 if DSTx_SRC_EN[n] is assigned 0. To support a new stream or, to continue the old stream after a pause.
 */
#define SMIX_SOURCE_CH_ST_MODE_MASK (0x7U)
#define SMIX_SOURCE_CH_ST_MODE_SHIFT (0U)
#define SMIX_SOURCE_CH_ST_MODE_GET(x) (((uint32_t)(x) & SMIX_SOURCE_CH_ST_MODE_MASK) >> SMIX_SOURCE_CH_ST_MODE_SHIFT)

/* Bitfield definition for register of struct array SOURCE_CH: DATA */
/*
 * VAL (WO)
 *
 * Data input register
 */
#define SMIX_SOURCE_CH_DATA_VAL_MASK (0xFFFFFFFFUL)
#define SMIX_SOURCE_CH_DATA_VAL_SHIFT (0U)
#define SMIX_SOURCE_CH_DATA_VAL_SET(x) (((uint32_t)(x) << SMIX_SOURCE_CH_DATA_VAL_SHIFT) & SMIX_SOURCE_CH_DATA_VAL_MASK)
#define SMIX_SOURCE_CH_DATA_VAL_GET(x) (((uint32_t)(x) & SMIX_SOURCE_CH_DATA_VAL_MASK) >> SMIX_SOURCE_CH_DATA_VAL_SHIFT)



/* DMA_CH register group index macro definition */
#define SMIX_DMA_CH_0 (0UL)
#define SMIX_DMA_CH_1 (1UL)
#define SMIX_DMA_CH_2 (2UL)
#define SMIX_DMA_CH_3 (3UL)
#define SMIX_DMA_CH_4 (4UL)
#define SMIX_DMA_CH_5 (5UL)
#define SMIX_DMA_CH_6 (6UL)
#define SMIX_DMA_CH_7 (7UL)
#define SMIX_DMA_CH_8 (8UL)
#define SMIX_DMA_CH_9 (9UL)
#define SMIX_DMA_CH_10 (10UL)
#define SMIX_DMA_CH_11 (11UL)
#define SMIX_DMA_CH_12 (12UL)
#define SMIX_DMA_CH_13 (13UL)
#define SMIX_DMA_CH_14 (14UL)
#define SMIX_DMA_CH_15 (15UL)
#define SMIX_DMA_CH_16 (16UL)
#define SMIX_DMA_CH_17 (17UL)
#define SMIX_DMA_CH_18 (18UL)
#define SMIX_DMA_CH_19 (19UL)
#define SMIX_DMA_CH_20 (20UL)
#define SMIX_DMA_CH_21 (21UL)
#define SMIX_DMA_CH_22 (22UL)
#define SMIX_DMA_CH_23 (23UL)
#define SMIX_DMA_CH_24 (24UL)
#define SMIX_DMA_CH_25 (25UL)

/* DST_CH register group index macro definition */
#define SMIX_DST_CH_0 (0UL)
#define SMIX_DST_CH_1 (1UL)

/* SOURCE_CH register group index macro definition */
#define SMIX_SOURCE_CH_0 (0UL)
#define SMIX_SOURCE_CH_1 (1UL)
#define SMIX_SOURCE_CH_2 (2UL)
#define SMIX_SOURCE_CH_3 (3UL)
#define SMIX_SOURCE_CH_4 (4UL)
#define SMIX_SOURCE_CH_5 (5UL)
#define SMIX_SOURCE_CH_6 (6UL)
#define SMIX_SOURCE_CH_7 (7UL)
#define SMIX_SOURCE_CH_8 (8UL)
#define SMIX_SOURCE_CH_9 (9UL)
#define SMIX_SOURCE_CH_10 (10UL)
#define SMIX_SOURCE_CH_11 (11UL)
#define SMIX_SOURCE_CH_12 (12UL)
#define SMIX_SOURCE_CH_13 (13UL)


#endif /* HPM_SMIX_H */
