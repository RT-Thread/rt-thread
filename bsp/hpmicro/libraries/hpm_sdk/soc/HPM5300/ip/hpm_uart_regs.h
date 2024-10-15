/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_UART_H
#define HPM_UART_H

typedef struct {
    __R  uint8_t  RESERVED0[4];                /* 0x0 - 0x3: Reserved */
    __RW uint32_t IDLE_CFG;                    /* 0x4: Idle Configuration Register */
    __RW uint32_t ADDR_CFG;                    /* 0x8: address match config register */
    __RW uint32_t IIR2;                        /* 0xC: Interrupt Identification Register2 */
    __RW uint32_t CFG;                         /* 0x10: Configuration Register */
    __RW uint32_t OSCR;                        /* 0x14: Over Sample Control Register */
    __RW uint32_t FCRR;                        /* 0x18: FIFO Control Register config */
    __RW uint32_t MOTO_CFG;                    /* 0x1C: moto system control register */
    union {
        __R  uint32_t RBR;                     /* 0x20: Receiver Buffer Register (when DLAB = 0) */
        __W  uint32_t THR;                     /* 0x20: Transmitter Holding Register (when DLAB = 0) */
        __RW uint32_t DLL;                     /* 0x20: Divisor Latch LSB (when DLAB = 1) */
    };
    union {
        __RW uint32_t IER;                     /* 0x24: Interrupt Enable Register (when DLAB = 0) */
        __RW uint32_t DLM;                     /* 0x24: Divisor Latch MSB (when DLAB = 1) */
    };
    union {
        __RW uint32_t IIR;                     /* 0x28: Interrupt Identification Register */
        __W  uint32_t FCR;                     /* 0x28: FIFO Control Register */
    };
    __RW uint32_t LCR;                         /* 0x2C: Line Control Register */
    __RW uint32_t MCR;                         /* 0x30: Modem Control Register ( */
    __R  uint32_t LSR;                         /* 0x34: Line Status Register */
    __R  uint32_t MSR;                         /* 0x38: Modem Status Register */
    __RW uint32_t GPR;                         /* 0x3C: GPR Register */
} UART_Type;


/* Bitfield definition for register: IDLE_CFG */
/*
 * TX_IDLE_COND (RW)
 *
 * IDLE Detection Condition
 * 0 - Treat as idle if TX pin is logic one
 * 1 - Treat as idle if UART state machine state is idle
 */
#define UART_IDLE_CFG_TX_IDLE_COND_MASK (0x2000000UL)
#define UART_IDLE_CFG_TX_IDLE_COND_SHIFT (25U)
#define UART_IDLE_CFG_TX_IDLE_COND_SET(x) (((uint32_t)(x) << UART_IDLE_CFG_TX_IDLE_COND_SHIFT) & UART_IDLE_CFG_TX_IDLE_COND_MASK)
#define UART_IDLE_CFG_TX_IDLE_COND_GET(x) (((uint32_t)(x) & UART_IDLE_CFG_TX_IDLE_COND_MASK) >> UART_IDLE_CFG_TX_IDLE_COND_SHIFT)

/*
 * TX_IDLE_EN (RW)
 *
 * UART TX Idle Detect Enable
 * 0 - Disable
 * 1 - Enable
 */
#define UART_IDLE_CFG_TX_IDLE_EN_MASK (0x1000000UL)
#define UART_IDLE_CFG_TX_IDLE_EN_SHIFT (24U)
#define UART_IDLE_CFG_TX_IDLE_EN_SET(x) (((uint32_t)(x) << UART_IDLE_CFG_TX_IDLE_EN_SHIFT) & UART_IDLE_CFG_TX_IDLE_EN_MASK)
#define UART_IDLE_CFG_TX_IDLE_EN_GET(x) (((uint32_t)(x) & UART_IDLE_CFG_TX_IDLE_EN_MASK) >> UART_IDLE_CFG_TX_IDLE_EN_SHIFT)

/*
 * TX_IDLE_THR (RW)
 *
 * Threshold for UART transmit Idle detection (in terms of bits)
 */
#define UART_IDLE_CFG_TX_IDLE_THR_MASK (0xFF0000UL)
#define UART_IDLE_CFG_TX_IDLE_THR_SHIFT (16U)
#define UART_IDLE_CFG_TX_IDLE_THR_SET(x) (((uint32_t)(x) << UART_IDLE_CFG_TX_IDLE_THR_SHIFT) & UART_IDLE_CFG_TX_IDLE_THR_MASK)
#define UART_IDLE_CFG_TX_IDLE_THR_GET(x) (((uint32_t)(x) & UART_IDLE_CFG_TX_IDLE_THR_MASK) >> UART_IDLE_CFG_TX_IDLE_THR_SHIFT)

/*
 * RXEN (RW)
 *
 * UART receive enable.
 * 0 - hold RX input to high, avoide wrong data input when config pinmux
 * 1 - bypass RX input from PIN
 * software should set it after config pinmux
 */
#define UART_IDLE_CFG_RXEN_MASK (0x800U)
#define UART_IDLE_CFG_RXEN_SHIFT (11U)
#define UART_IDLE_CFG_RXEN_SET(x) (((uint32_t)(x) << UART_IDLE_CFG_RXEN_SHIFT) & UART_IDLE_CFG_RXEN_MASK)
#define UART_IDLE_CFG_RXEN_GET(x) (((uint32_t)(x) & UART_IDLE_CFG_RXEN_MASK) >> UART_IDLE_CFG_RXEN_SHIFT)

/*
 * RX_IDLE_COND (RW)
 *
 * IDLE Detection Condition
 * 0 - Treat as idle if RX pin is logic one
 * 1 - Treat as idle if UART state machine state is idle
 */
#define UART_IDLE_CFG_RX_IDLE_COND_MASK (0x200U)
#define UART_IDLE_CFG_RX_IDLE_COND_SHIFT (9U)
#define UART_IDLE_CFG_RX_IDLE_COND_SET(x) (((uint32_t)(x) << UART_IDLE_CFG_RX_IDLE_COND_SHIFT) & UART_IDLE_CFG_RX_IDLE_COND_MASK)
#define UART_IDLE_CFG_RX_IDLE_COND_GET(x) (((uint32_t)(x) & UART_IDLE_CFG_RX_IDLE_COND_MASK) >> UART_IDLE_CFG_RX_IDLE_COND_SHIFT)

/*
 * RX_IDLE_EN (RW)
 *
 * UART Idle Detect Enable
 * 0 - Disable
 * 1 - Enable
 * it should be enabled if enable address match feature
 */
#define UART_IDLE_CFG_RX_IDLE_EN_MASK (0x100U)
#define UART_IDLE_CFG_RX_IDLE_EN_SHIFT (8U)
#define UART_IDLE_CFG_RX_IDLE_EN_SET(x) (((uint32_t)(x) << UART_IDLE_CFG_RX_IDLE_EN_SHIFT) & UART_IDLE_CFG_RX_IDLE_EN_MASK)
#define UART_IDLE_CFG_RX_IDLE_EN_GET(x) (((uint32_t)(x) & UART_IDLE_CFG_RX_IDLE_EN_MASK) >> UART_IDLE_CFG_RX_IDLE_EN_SHIFT)

/*
 * RX_IDLE_THR (RW)
 *
 * Threshold for UART Receive Idle detection (in terms of bits)
 */
#define UART_IDLE_CFG_RX_IDLE_THR_MASK (0xFFU)
#define UART_IDLE_CFG_RX_IDLE_THR_SHIFT (0U)
#define UART_IDLE_CFG_RX_IDLE_THR_SET(x) (((uint32_t)(x) << UART_IDLE_CFG_RX_IDLE_THR_SHIFT) & UART_IDLE_CFG_RX_IDLE_THR_MASK)
#define UART_IDLE_CFG_RX_IDLE_THR_GET(x) (((uint32_t)(x) & UART_IDLE_CFG_RX_IDLE_THR_MASK) >> UART_IDLE_CFG_RX_IDLE_THR_SHIFT)

/* Bitfield definition for register: ADDR_CFG */
/*
 * TXEN_9BIT (RW)
 *
 * set to use 9bit mode for transmitter,
 * will set the MSB for the first character as address flag, keep 0 for others.
 */
#define UART_ADDR_CFG_TXEN_9BIT_MASK (0x100000UL)
#define UART_ADDR_CFG_TXEN_9BIT_SHIFT (20U)
#define UART_ADDR_CFG_TXEN_9BIT_SET(x) (((uint32_t)(x) << UART_ADDR_CFG_TXEN_9BIT_SHIFT) & UART_ADDR_CFG_TXEN_9BIT_MASK)
#define UART_ADDR_CFG_TXEN_9BIT_GET(x) (((uint32_t)(x) & UART_ADDR_CFG_TXEN_9BIT_MASK) >> UART_ADDR_CFG_TXEN_9BIT_SHIFT)

/*
 * RXEN_ADDR_MSB (RW)
 *
 * set to use MSB as address flag at receiver(actually this is done by software set correct MSB in addr0/addr1).
 * Clr to use first character as address.
 * Only needed if enable address match feature
 */
#define UART_ADDR_CFG_RXEN_ADDR_MSB_MASK (0x80000UL)
#define UART_ADDR_CFG_RXEN_ADDR_MSB_SHIFT (19U)
#define UART_ADDR_CFG_RXEN_ADDR_MSB_SET(x) (((uint32_t)(x) << UART_ADDR_CFG_RXEN_ADDR_MSB_SHIFT) & UART_ADDR_CFG_RXEN_ADDR_MSB_MASK)
#define UART_ADDR_CFG_RXEN_ADDR_MSB_GET(x) (((uint32_t)(x) & UART_ADDR_CFG_RXEN_ADDR_MSB_MASK) >> UART_ADDR_CFG_RXEN_ADDR_MSB_SHIFT)

/*
 * RXEN_9BIT (RW)
 *
 * set to use 9bit mode for receiver, only valid if rxen_addr_msb is set
 */
#define UART_ADDR_CFG_RXEN_9BIT_MASK (0x40000UL)
#define UART_ADDR_CFG_RXEN_9BIT_SHIFT (18U)
#define UART_ADDR_CFG_RXEN_9BIT_SET(x) (((uint32_t)(x) << UART_ADDR_CFG_RXEN_9BIT_SHIFT) & UART_ADDR_CFG_RXEN_9BIT_MASK)
#define UART_ADDR_CFG_RXEN_9BIT_GET(x) (((uint32_t)(x) & UART_ADDR_CFG_RXEN_9BIT_MASK) >> UART_ADDR_CFG_RXEN_9BIT_SHIFT)

/*
 * A1_EN (RW)
 *
 * enable addr1 compare for the first character.
 * If a1_en OR a0_en, then do not receive data if address not match.
 * If ~a1_en AND ~a0_en, the receive all data like before.
 * NOTE: should set idle_tmout_en if enable address match feature
 */
#define UART_ADDR_CFG_A1_EN_MASK (0x20000UL)
#define UART_ADDR_CFG_A1_EN_SHIFT (17U)
#define UART_ADDR_CFG_A1_EN_SET(x) (((uint32_t)(x) << UART_ADDR_CFG_A1_EN_SHIFT) & UART_ADDR_CFG_A1_EN_MASK)
#define UART_ADDR_CFG_A1_EN_GET(x) (((uint32_t)(x) & UART_ADDR_CFG_A1_EN_MASK) >> UART_ADDR_CFG_A1_EN_SHIFT)

/*
 * A0_EN (RW)
 *
 * enable addr0 compare for the first character
 */
#define UART_ADDR_CFG_A0_EN_MASK (0x10000UL)
#define UART_ADDR_CFG_A0_EN_SHIFT (16U)
#define UART_ADDR_CFG_A0_EN_SET(x) (((uint32_t)(x) << UART_ADDR_CFG_A0_EN_SHIFT) & UART_ADDR_CFG_A0_EN_MASK)
#define UART_ADDR_CFG_A0_EN_GET(x) (((uint32_t)(x) & UART_ADDR_CFG_A0_EN_MASK) >> UART_ADDR_CFG_A0_EN_SHIFT)

/*
 * ADDR1 (RW)
 *
 * address 1 fileld.
 * in 9bit mode, this is the full address byte.
 * For other mode(8/7/6/5bit), MSB should be set for address flag.
 * If want address==0 to be matched at 8bit mode, should set addr1=0x80
 */
#define UART_ADDR_CFG_ADDR1_MASK (0xFF00U)
#define UART_ADDR_CFG_ADDR1_SHIFT (8U)
#define UART_ADDR_CFG_ADDR1_SET(x) (((uint32_t)(x) << UART_ADDR_CFG_ADDR1_SHIFT) & UART_ADDR_CFG_ADDR1_MASK)
#define UART_ADDR_CFG_ADDR1_GET(x) (((uint32_t)(x) & UART_ADDR_CFG_ADDR1_MASK) >> UART_ADDR_CFG_ADDR1_SHIFT)

/*
 * ADDR0 (RW)
 *
 * address 0 field.
 */
#define UART_ADDR_CFG_ADDR0_MASK (0xFFU)
#define UART_ADDR_CFG_ADDR0_SHIFT (0U)
#define UART_ADDR_CFG_ADDR0_SET(x) (((uint32_t)(x) << UART_ADDR_CFG_ADDR0_SHIFT) & UART_ADDR_CFG_ADDR0_MASK)
#define UART_ADDR_CFG_ADDR0_GET(x) (((uint32_t)(x) & UART_ADDR_CFG_ADDR0_MASK) >> UART_ADDR_CFG_ADDR0_SHIFT)

/* Bitfield definition for register: IIR2 */
/*
 * RXIDLE_FLAG (W1C)
 *
 * UART RX IDLE Flag, assert after rxd high and then rx idle timeout, write one clear
 * 0 - UART RX is busy
 * 1 - UART RX is idle
 */
#define UART_IIR2_RXIDLE_FLAG_MASK (0x80000000UL)
#define UART_IIR2_RXIDLE_FLAG_SHIFT (31U)
#define UART_IIR2_RXIDLE_FLAG_SET(x) (((uint32_t)(x) << UART_IIR2_RXIDLE_FLAG_SHIFT) & UART_IIR2_RXIDLE_FLAG_MASK)
#define UART_IIR2_RXIDLE_FLAG_GET(x) (((uint32_t)(x) & UART_IIR2_RXIDLE_FLAG_MASK) >> UART_IIR2_RXIDLE_FLAG_SHIFT)

/*
 * TXIDLE_FLAG (W1C)
 *
 * UART TX IDLE Flag, assert after txd high and then tx idle timeout, write one clear
 * 0 - UART TX is busy
 * 1 - UART TX is idle
 */
#define UART_IIR2_TXIDLE_FLAG_MASK (0x40000000UL)
#define UART_IIR2_TXIDLE_FLAG_SHIFT (30U)
#define UART_IIR2_TXIDLE_FLAG_SET(x) (((uint32_t)(x) << UART_IIR2_TXIDLE_FLAG_SHIFT) & UART_IIR2_TXIDLE_FLAG_MASK)
#define UART_IIR2_TXIDLE_FLAG_GET(x) (((uint32_t)(x) & UART_IIR2_TXIDLE_FLAG_MASK) >> UART_IIR2_TXIDLE_FLAG_SHIFT)

/*
 * ADDR_MATCH (W1C)
 *
 * address match irq status, assert if either address match(and enabled). Write one clear
 * NOTE: the address byte may not moved by DMA at this point.
 * User can wait next addr_match_idle irq for the whole data include address
 */
#define UART_IIR2_ADDR_MATCH_MASK (0x20000000UL)
#define UART_IIR2_ADDR_MATCH_SHIFT (29U)
#define UART_IIR2_ADDR_MATCH_SET(x) (((uint32_t)(x) << UART_IIR2_ADDR_MATCH_SHIFT) & UART_IIR2_ADDR_MATCH_MASK)
#define UART_IIR2_ADDR_MATCH_GET(x) (((uint32_t)(x) & UART_IIR2_ADDR_MATCH_MASK) >> UART_IIR2_ADDR_MATCH_SHIFT)

/*
 * ADDR_MATCH_IDLE (W1C)
 *
 * address match and idle irq status, assert at rx bus idle if address match event triggered.
 * Write one clear;
 */
#define UART_IIR2_ADDR_MATCH_IDLE_MASK (0x10000000UL)
#define UART_IIR2_ADDR_MATCH_IDLE_SHIFT (28U)
#define UART_IIR2_ADDR_MATCH_IDLE_SET(x) (((uint32_t)(x) << UART_IIR2_ADDR_MATCH_IDLE_SHIFT) & UART_IIR2_ADDR_MATCH_IDLE_MASK)
#define UART_IIR2_ADDR_MATCH_IDLE_GET(x) (((uint32_t)(x) & UART_IIR2_ADDR_MATCH_IDLE_MASK) >> UART_IIR2_ADDR_MATCH_IDLE_SHIFT)

/*
 * DATA_LOST (W1C)
 *
 * assert if data lost before address match status, write one clear;
 * It will not assert if no address match occurs
 */
#define UART_IIR2_DATA_LOST_MASK (0x8000000UL)
#define UART_IIR2_DATA_LOST_SHIFT (27U)
#define UART_IIR2_DATA_LOST_SET(x) (((uint32_t)(x) << UART_IIR2_DATA_LOST_SHIFT) & UART_IIR2_DATA_LOST_MASK)
#define UART_IIR2_DATA_LOST_GET(x) (((uint32_t)(x) & UART_IIR2_DATA_LOST_MASK) >> UART_IIR2_DATA_LOST_SHIFT)

/*
 * FIFOED (RO)
 *
 * FIFOs enabled
 * These two bits are 1 when bit 0 of the FIFO Control
 * Register (FIFOE) is set to 1.
 */
#define UART_IIR2_FIFOED_MASK (0xC0U)
#define UART_IIR2_FIFOED_SHIFT (6U)
#define UART_IIR2_FIFOED_GET(x) (((uint32_t)(x) & UART_IIR2_FIFOED_MASK) >> UART_IIR2_FIFOED_SHIFT)

/*
 * INTRID (RO)
 *
 * Interrupt ID, see IIR2 for detail decoding
 */
#define UART_IIR2_INTRID_MASK (0xFU)
#define UART_IIR2_INTRID_SHIFT (0U)
#define UART_IIR2_INTRID_GET(x) (((uint32_t)(x) & UART_IIR2_INTRID_MASK) >> UART_IIR2_INTRID_SHIFT)

/* Bitfield definition for register: CFG */
/*
 * FIFOSIZE (RO)
 *
 * The depth of RXFIFO and TXFIFO
 * 0: 16-byte FIFO
 * 1: 32-byte FIFO
 * 2: 64-byte FIFO
 * 3: 128-byte FIFO
 */
#define UART_CFG_FIFOSIZE_MASK (0x3U)
#define UART_CFG_FIFOSIZE_SHIFT (0U)
#define UART_CFG_FIFOSIZE_GET(x) (((uint32_t)(x) & UART_CFG_FIFOSIZE_MASK) >> UART_CFG_FIFOSIZE_SHIFT)

/* Bitfield definition for register: OSCR */
/*
 * OSC (RW)
 *
 * Over-sample control
 * The value must be an even number; any odd value
 * writes to this field will be converted to an even value.
 * OSC=0: reserved
 * OSC<=8: The over-sample ratio is 8
 * 8 < OSC< 32: The over sample ratio is OSC
 */
#define UART_OSCR_OSC_MASK (0x1FU)
#define UART_OSCR_OSC_SHIFT (0U)
#define UART_OSCR_OSC_SET(x) (((uint32_t)(x) << UART_OSCR_OSC_SHIFT) & UART_OSCR_OSC_MASK)
#define UART_OSCR_OSC_GET(x) (((uint32_t)(x) & UART_OSCR_OSC_MASK) >> UART_OSCR_OSC_SHIFT)

/* Bitfield definition for register: FCRR */
/*
 * FIFOT4EN (RW)
 *
 * set to use new 4bit fifo threshold(TFIFOT4 and RFIFOT4)
 * clr to use 2bit(TFIFOT and RFIFOT)
 */
#define UART_FCRR_FIFOT4EN_MASK (0x800000UL)
#define UART_FCRR_FIFOT4EN_SHIFT (23U)
#define UART_FCRR_FIFOT4EN_SET(x) (((uint32_t)(x) << UART_FCRR_FIFOT4EN_SHIFT) & UART_FCRR_FIFOT4EN_MASK)
#define UART_FCRR_FIFOT4EN_GET(x) (((uint32_t)(x) & UART_FCRR_FIFOT4EN_MASK) >> UART_FCRR_FIFOT4EN_SHIFT)

/*
 * TFIFOT4 (RW)
 *
 * txfifo threshold(0 for 1byte, 0xF for 16bytes), uart will send tx_dma_req when data in fifo is less than threshold.
 */
#define UART_FCRR_TFIFOT4_MASK (0xF0000UL)
#define UART_FCRR_TFIFOT4_SHIFT (16U)
#define UART_FCRR_TFIFOT4_SET(x) (((uint32_t)(x) << UART_FCRR_TFIFOT4_SHIFT) & UART_FCRR_TFIFOT4_MASK)
#define UART_FCRR_TFIFOT4_GET(x) (((uint32_t)(x) & UART_FCRR_TFIFOT4_MASK) >> UART_FCRR_TFIFOT4_SHIFT)

/*
 * RFIFOT4 (RW)
 *
 * rxfifo threshold(0 for 1byte, 0xF for 16bytes).
 * Uart will send rx_dma_req if data in fifo reachs the threshold, also will set the rxdata irq if enabled
 */
#define UART_FCRR_RFIFOT4_MASK (0xF00U)
#define UART_FCRR_RFIFOT4_SHIFT (8U)
#define UART_FCRR_RFIFOT4_SET(x) (((uint32_t)(x) << UART_FCRR_RFIFOT4_SHIFT) & UART_FCRR_RFIFOT4_MASK)
#define UART_FCRR_RFIFOT4_GET(x) (((uint32_t)(x) & UART_FCRR_RFIFOT4_MASK) >> UART_FCRR_RFIFOT4_SHIFT)

/*
 * RFIFOT (RW)
 *
 * Receiver FIFO trigger level
 */
#define UART_FCRR_RFIFOT_MASK (0xC0U)
#define UART_FCRR_RFIFOT_SHIFT (6U)
#define UART_FCRR_RFIFOT_SET(x) (((uint32_t)(x) << UART_FCRR_RFIFOT_SHIFT) & UART_FCRR_RFIFOT_MASK)
#define UART_FCRR_RFIFOT_GET(x) (((uint32_t)(x) & UART_FCRR_RFIFOT_MASK) >> UART_FCRR_RFIFOT_SHIFT)

/*
 * TFIFOT (RW)
 *
 * Transmitter FIFO trigger level
 */
#define UART_FCRR_TFIFOT_MASK (0x30U)
#define UART_FCRR_TFIFOT_SHIFT (4U)
#define UART_FCRR_TFIFOT_SET(x) (((uint32_t)(x) << UART_FCRR_TFIFOT_SHIFT) & UART_FCRR_TFIFOT_MASK)
#define UART_FCRR_TFIFOT_GET(x) (((uint32_t)(x) & UART_FCRR_TFIFOT_MASK) >> UART_FCRR_TFIFOT_SHIFT)

/*
 * DMAE (RW)
 *
 * DMA enable
 * 0: Disable
 * 1: Enable
 */
#define UART_FCRR_DMAE_MASK (0x8U)
#define UART_FCRR_DMAE_SHIFT (3U)
#define UART_FCRR_DMAE_SET(x) (((uint32_t)(x) << UART_FCRR_DMAE_SHIFT) & UART_FCRR_DMAE_MASK)
#define UART_FCRR_DMAE_GET(x) (((uint32_t)(x) & UART_FCRR_DMAE_MASK) >> UART_FCRR_DMAE_SHIFT)

/*
 * TFIFORST (WO)
 *
 * Transmitter FIFO reset
 * Write 1 to clear all bytes in the TXFIFO and resets its
 * counter. The Transmitter Shift Register is not cleared.
 * This bit will automatically be cleared.
 */
#define UART_FCRR_TFIFORST_MASK (0x4U)
#define UART_FCRR_TFIFORST_SHIFT (2U)
#define UART_FCRR_TFIFORST_SET(x) (((uint32_t)(x) << UART_FCRR_TFIFORST_SHIFT) & UART_FCRR_TFIFORST_MASK)
#define UART_FCRR_TFIFORST_GET(x) (((uint32_t)(x) & UART_FCRR_TFIFORST_MASK) >> UART_FCRR_TFIFORST_SHIFT)

/*
 * RFIFORST (WO)
 *
 * Receiver FIFO reset
 * Write 1 to clear all bytes in the RXFIFO and resets its
 * counter. The Receiver Shift Register is not cleared.
 * This bit will automatically be cleared.
 */
#define UART_FCRR_RFIFORST_MASK (0x2U)
#define UART_FCRR_RFIFORST_SHIFT (1U)
#define UART_FCRR_RFIFORST_SET(x) (((uint32_t)(x) << UART_FCRR_RFIFORST_SHIFT) & UART_FCRR_RFIFORST_MASK)
#define UART_FCRR_RFIFORST_GET(x) (((uint32_t)(x) & UART_FCRR_RFIFORST_MASK) >> UART_FCRR_RFIFORST_SHIFT)

/*
 * FIFOE (RW)
 *
 * FIFO enable
 * Write 1 to enable both the transmitter and receiver
 * FIFOs.
 * The FIFOs are reset when the value of this bit toggles.
 */
#define UART_FCRR_FIFOE_MASK (0x1U)
#define UART_FCRR_FIFOE_SHIFT (0U)
#define UART_FCRR_FIFOE_SET(x) (((uint32_t)(x) << UART_FCRR_FIFOE_SHIFT) & UART_FCRR_FIFOE_MASK)
#define UART_FCRR_FIFOE_GET(x) (((uint32_t)(x) & UART_FCRR_FIFOE_MASK) >> UART_FCRR_FIFOE_SHIFT)

/* Bitfield definition for register: MOTO_CFG */
/*
 * SWTRG (WO)
 *
 * software trigger. User should avoid use sw/hw trigger at same time, otherwise result unknown.
 * Hardware auto reset.
 */
#define UART_MOTO_CFG_SWTRG_MASK (0x80000000UL)
#define UART_MOTO_CFG_SWTRG_SHIFT (31U)
#define UART_MOTO_CFG_SWTRG_SET(x) (((uint32_t)(x) << UART_MOTO_CFG_SWTRG_SHIFT) & UART_MOTO_CFG_SWTRG_MASK)
#define UART_MOTO_CFG_SWTRG_GET(x) (((uint32_t)(x) & UART_MOTO_CFG_SWTRG_MASK) >> UART_MOTO_CFG_SWTRG_SHIFT)

/*
 * TXSTP_BITS (RW)
 *
 * if TXSTOP_INSERT is enabled, the STOP bits to be inserted between each byte. 0 for 1 bit;  0xFF for 256bits
 */
#define UART_MOTO_CFG_TXSTP_BITS_MASK (0xFF00U)
#define UART_MOTO_CFG_TXSTP_BITS_SHIFT (8U)
#define UART_MOTO_CFG_TXSTP_BITS_SET(x) (((uint32_t)(x) << UART_MOTO_CFG_TXSTP_BITS_SHIFT) & UART_MOTO_CFG_TXSTP_BITS_MASK)
#define UART_MOTO_CFG_TXSTP_BITS_GET(x) (((uint32_t)(x) & UART_MOTO_CFG_TXSTP_BITS_MASK) >> UART_MOTO_CFG_TXSTP_BITS_SHIFT)

/*
 * HWTRG_EN (RW)
 *
 * set to enable hardware trigger(trigger from moto is shared by other UART)
 */
#define UART_MOTO_CFG_HWTRG_EN_MASK (0x80U)
#define UART_MOTO_CFG_HWTRG_EN_SHIFT (7U)
#define UART_MOTO_CFG_HWTRG_EN_SET(x) (((uint32_t)(x) << UART_MOTO_CFG_HWTRG_EN_SHIFT) & UART_MOTO_CFG_HWTRG_EN_MASK)
#define UART_MOTO_CFG_HWTRG_EN_GET(x) (((uint32_t)(x) & UART_MOTO_CFG_HWTRG_EN_MASK) >> UART_MOTO_CFG_HWTRG_EN_SHIFT)

/*
 * TRG_MODE (RW)
 *
 * set to enable trigger mode.
 * software should push needed data into txbuffer frist, uart will not start transmission at this time.
 * User should send trigger signal(by hw or sw), uart will send all data in txfifo till  empty
 * NOTE: the hw_trigger should be pulse signal from trig mux.
 */
#define UART_MOTO_CFG_TRG_MODE_MASK (0x40U)
#define UART_MOTO_CFG_TRG_MODE_SHIFT (6U)
#define UART_MOTO_CFG_TRG_MODE_SET(x) (((uint32_t)(x) << UART_MOTO_CFG_TRG_MODE_SHIFT) & UART_MOTO_CFG_TRG_MODE_MASK)
#define UART_MOTO_CFG_TRG_MODE_GET(x) (((uint32_t)(x) & UART_MOTO_CFG_TRG_MODE_MASK) >> UART_MOTO_CFG_TRG_MODE_SHIFT)

/*
 * TRG_CLR_RFIFO (RW)
 *
 * set to enable the feature that, clear rxfifo at tx trigger(sw or hw), avoid unexpected data in rxfifo.
 */
#define UART_MOTO_CFG_TRG_CLR_RFIFO_MASK (0x20U)
#define UART_MOTO_CFG_TRG_CLR_RFIFO_SHIFT (5U)
#define UART_MOTO_CFG_TRG_CLR_RFIFO_SET(x) (((uint32_t)(x) << UART_MOTO_CFG_TRG_CLR_RFIFO_SHIFT) & UART_MOTO_CFG_TRG_CLR_RFIFO_MASK)
#define UART_MOTO_CFG_TRG_CLR_RFIFO_GET(x) (((uint32_t)(x) & UART_MOTO_CFG_TRG_CLR_RFIFO_MASK) >> UART_MOTO_CFG_TRG_CLR_RFIFO_SHIFT)

/*
 * TXSTOP_INSERT (RW)
 *
 * set to insert STOP bits between each tx byte till tx fifo empty.
 * NOTE: there will be no 1.5/2 STOP bits if enabled this feature, LCR.STB should be set to 0 if this bit is set
 */
#define UART_MOTO_CFG_TXSTOP_INSERT_MASK (0x10U)
#define UART_MOTO_CFG_TXSTOP_INSERT_SHIFT (4U)
#define UART_MOTO_CFG_TXSTOP_INSERT_SET(x) (((uint32_t)(x) << UART_MOTO_CFG_TXSTOP_INSERT_SHIFT) & UART_MOTO_CFG_TXSTOP_INSERT_MASK)
#define UART_MOTO_CFG_TXSTOP_INSERT_GET(x) (((uint32_t)(x) & UART_MOTO_CFG_TXSTOP_INSERT_MASK) >> UART_MOTO_CFG_TXSTOP_INSERT_SHIFT)

/* Bitfield definition for register: RBR */
/*
 * RBR (RO)
 *
 * Receive data read port
 */
#define UART_RBR_RBR_MASK (0xFFU)
#define UART_RBR_RBR_SHIFT (0U)
#define UART_RBR_RBR_GET(x) (((uint32_t)(x) & UART_RBR_RBR_MASK) >> UART_RBR_RBR_SHIFT)

/* Bitfield definition for register: THR */
/*
 * THR (WO)
 *
 * Transmit data write port
 */
#define UART_THR_THR_MASK (0xFFU)
#define UART_THR_THR_SHIFT (0U)
#define UART_THR_THR_SET(x) (((uint32_t)(x) << UART_THR_THR_SHIFT) & UART_THR_THR_MASK)
#define UART_THR_THR_GET(x) (((uint32_t)(x) & UART_THR_THR_MASK) >> UART_THR_THR_SHIFT)

/* Bitfield definition for register: DLL */
/*
 * DLL (RW)
 *
 * Least significant byte of the Divisor Latch
 */
#define UART_DLL_DLL_MASK (0xFFU)
#define UART_DLL_DLL_SHIFT (0U)
#define UART_DLL_DLL_SET(x) (((uint32_t)(x) << UART_DLL_DLL_SHIFT) & UART_DLL_DLL_MASK)
#define UART_DLL_DLL_GET(x) (((uint32_t)(x) & UART_DLL_DLL_MASK) >> UART_DLL_DLL_SHIFT)

/* Bitfield definition for register: IER */
/*
 * ERXIDLE (RW)
 *
 * Enable Receive Idle interrupt
 * 0 - Disable Idle interrupt
 * 1 - Enable Idle interrupt
 */
#define UART_IER_ERXIDLE_MASK (0x80000000UL)
#define UART_IER_ERXIDLE_SHIFT (31U)
#define UART_IER_ERXIDLE_SET(x) (((uint32_t)(x) << UART_IER_ERXIDLE_SHIFT) & UART_IER_ERXIDLE_MASK)
#define UART_IER_ERXIDLE_GET(x) (((uint32_t)(x) & UART_IER_ERXIDLE_MASK) >> UART_IER_ERXIDLE_SHIFT)

/*
 * ETXIDLE (RW)
 *
 * enable transmit idle interrupt
 */
#define UART_IER_ETXIDLE_MASK (0x40000000UL)
#define UART_IER_ETXIDLE_SHIFT (30U)
#define UART_IER_ETXIDLE_SET(x) (((uint32_t)(x) << UART_IER_ETXIDLE_SHIFT) & UART_IER_ETXIDLE_MASK)
#define UART_IER_ETXIDLE_GET(x) (((uint32_t)(x) & UART_IER_ETXIDLE_MASK) >> UART_IER_ETXIDLE_SHIFT)

/*
 * EADDRM (RW)
 *
 * enable ADDR_MATCH  interrupt
 */
#define UART_IER_EADDRM_MASK (0x20000000UL)
#define UART_IER_EADDRM_SHIFT (29U)
#define UART_IER_EADDRM_SET(x) (((uint32_t)(x) << UART_IER_EADDRM_SHIFT) & UART_IER_EADDRM_MASK)
#define UART_IER_EADDRM_GET(x) (((uint32_t)(x) & UART_IER_EADDRM_MASK) >> UART_IER_EADDRM_SHIFT)

/*
 * EADDRM_IDLE (RW)
 *
 * enable ADDR_MATCH_IDLE interrupt
 */
#define UART_IER_EADDRM_IDLE_MASK (0x10000000UL)
#define UART_IER_EADDRM_IDLE_SHIFT (28U)
#define UART_IER_EADDRM_IDLE_SET(x) (((uint32_t)(x) << UART_IER_EADDRM_IDLE_SHIFT) & UART_IER_EADDRM_IDLE_MASK)
#define UART_IER_EADDRM_IDLE_GET(x) (((uint32_t)(x) & UART_IER_EADDRM_IDLE_MASK) >> UART_IER_EADDRM_IDLE_SHIFT)

/*
 * EDATLOST (RW)
 *
 * enable DATA_LOST interrupt
 */
#define UART_IER_EDATLOST_MASK (0x8000000UL)
#define UART_IER_EDATLOST_SHIFT (27U)
#define UART_IER_EDATLOST_SET(x) (((uint32_t)(x) << UART_IER_EDATLOST_SHIFT) & UART_IER_EDATLOST_MASK)
#define UART_IER_EDATLOST_GET(x) (((uint32_t)(x) & UART_IER_EDATLOST_MASK) >> UART_IER_EDATLOST_SHIFT)

/*
 * EMSI (RW)
 *
 * Enable modem status interrupt
 * The interrupt asserts when the status of one of the
 * following occurs:
 * The status of modem_rin, modem_dcdn,
 * modem_dsrn or modem_ctsn (If the auto-cts mode is
 * disabled) has been changed.
 * If the auto-cts mode is enabled (MCR bit4 (AFE) = 1),
 * modem_ctsn would be used to control the transmitter.
 */
#define UART_IER_EMSI_MASK (0x8U)
#define UART_IER_EMSI_SHIFT (3U)
#define UART_IER_EMSI_SET(x) (((uint32_t)(x) << UART_IER_EMSI_SHIFT) & UART_IER_EMSI_MASK)
#define UART_IER_EMSI_GET(x) (((uint32_t)(x) & UART_IER_EMSI_MASK) >> UART_IER_EMSI_SHIFT)

/*
 * ELSI (RW)
 *
 * Enable receiver line status interrupt
 */
#define UART_IER_ELSI_MASK (0x4U)
#define UART_IER_ELSI_SHIFT (2U)
#define UART_IER_ELSI_SET(x) (((uint32_t)(x) << UART_IER_ELSI_SHIFT) & UART_IER_ELSI_MASK)
#define UART_IER_ELSI_GET(x) (((uint32_t)(x) & UART_IER_ELSI_MASK) >> UART_IER_ELSI_SHIFT)

/*
 * ETHEI (RW)
 *
 * Enable transmitter holding register interrupt
 */
#define UART_IER_ETHEI_MASK (0x2U)
#define UART_IER_ETHEI_SHIFT (1U)
#define UART_IER_ETHEI_SET(x) (((uint32_t)(x) << UART_IER_ETHEI_SHIFT) & UART_IER_ETHEI_MASK)
#define UART_IER_ETHEI_GET(x) (((uint32_t)(x) & UART_IER_ETHEI_MASK) >> UART_IER_ETHEI_SHIFT)

/*
 * ERBI (RW)
 *
 * Enable received data available interrupt and the
 * character timeout interrupt
 * 0: Disable
 * 1: Enable
 */
#define UART_IER_ERBI_MASK (0x1U)
#define UART_IER_ERBI_SHIFT (0U)
#define UART_IER_ERBI_SET(x) (((uint32_t)(x) << UART_IER_ERBI_SHIFT) & UART_IER_ERBI_MASK)
#define UART_IER_ERBI_GET(x) (((uint32_t)(x) & UART_IER_ERBI_MASK) >> UART_IER_ERBI_SHIFT)

/* Bitfield definition for register: DLM */
/*
 * DLM (RW)
 *
 * Most significant byte of the Divisor Latch
 */
#define UART_DLM_DLM_MASK (0xFFU)
#define UART_DLM_DLM_SHIFT (0U)
#define UART_DLM_DLM_SET(x) (((uint32_t)(x) << UART_DLM_DLM_SHIFT) & UART_DLM_DLM_MASK)
#define UART_DLM_DLM_GET(x) (((uint32_t)(x) & UART_DLM_DLM_MASK) >> UART_DLM_DLM_SHIFT)

/* Bitfield definition for register: IIR */
/*
 * RXIDLE_FLAG (W1C)
 *
 * UART IDLE Flag
 * 0 - UART is busy
 * 1 - UART is idle
 * NOTE: when write one to clear this bit, avoid changging FCR register since it's same address as IIR
 */
#define UART_IIR_RXIDLE_FLAG_MASK (0x80000000UL)
#define UART_IIR_RXIDLE_FLAG_SHIFT (31U)
#define UART_IIR_RXIDLE_FLAG_SET(x) (((uint32_t)(x) << UART_IIR_RXIDLE_FLAG_SHIFT) & UART_IIR_RXIDLE_FLAG_MASK)
#define UART_IIR_RXIDLE_FLAG_GET(x) (((uint32_t)(x) & UART_IIR_RXIDLE_FLAG_MASK) >> UART_IIR_RXIDLE_FLAG_SHIFT)

/*
 * FIFOED (RO)
 *
 * FIFOs enabled
 * These two bits are 1 when bit 0 of the FIFO Control
 * Register (FIFOE) is set to 1.
 */
#define UART_IIR_FIFOED_MASK (0xC0U)
#define UART_IIR_FIFOED_SHIFT (6U)
#define UART_IIR_FIFOED_GET(x) (((uint32_t)(x) & UART_IIR_FIFOED_MASK) >> UART_IIR_FIFOED_SHIFT)

/*
 * INTRID (RO)
 *
 * Interrupt ID, see IIR2 for detail decoding
 */
#define UART_IIR_INTRID_MASK (0xFU)
#define UART_IIR_INTRID_SHIFT (0U)
#define UART_IIR_INTRID_GET(x) (((uint32_t)(x) & UART_IIR_INTRID_MASK) >> UART_IIR_INTRID_SHIFT)

/* Bitfield definition for register: FCR */
/*
 * RFIFOT (WO)
 *
 * Receiver FIFO trigger level
 */
#define UART_FCR_RFIFOT_MASK (0xC0U)
#define UART_FCR_RFIFOT_SHIFT (6U)
#define UART_FCR_RFIFOT_SET(x) (((uint32_t)(x) << UART_FCR_RFIFOT_SHIFT) & UART_FCR_RFIFOT_MASK)
#define UART_FCR_RFIFOT_GET(x) (((uint32_t)(x) & UART_FCR_RFIFOT_MASK) >> UART_FCR_RFIFOT_SHIFT)

/*
 * TFIFOT (WO)
 *
 * Transmitter FIFO trigger level
 */
#define UART_FCR_TFIFOT_MASK (0x30U)
#define UART_FCR_TFIFOT_SHIFT (4U)
#define UART_FCR_TFIFOT_SET(x) (((uint32_t)(x) << UART_FCR_TFIFOT_SHIFT) & UART_FCR_TFIFOT_MASK)
#define UART_FCR_TFIFOT_GET(x) (((uint32_t)(x) & UART_FCR_TFIFOT_MASK) >> UART_FCR_TFIFOT_SHIFT)

/*
 * DMAE (WO)
 *
 * DMA enable
 * 0: Disable
 * 1: Enable
 */
#define UART_FCR_DMAE_MASK (0x8U)
#define UART_FCR_DMAE_SHIFT (3U)
#define UART_FCR_DMAE_SET(x) (((uint32_t)(x) << UART_FCR_DMAE_SHIFT) & UART_FCR_DMAE_MASK)
#define UART_FCR_DMAE_GET(x) (((uint32_t)(x) & UART_FCR_DMAE_MASK) >> UART_FCR_DMAE_SHIFT)

/*
 * TFIFORST (WO)
 *
 * Transmitter FIFO reset
 * Write 1 to clear all bytes in the TXFIFO and resets its
 * counter. The Transmitter Shift Register is not cleared.
 * This bit will automatically be cleared.
 */
#define UART_FCR_TFIFORST_MASK (0x4U)
#define UART_FCR_TFIFORST_SHIFT (2U)
#define UART_FCR_TFIFORST_SET(x) (((uint32_t)(x) << UART_FCR_TFIFORST_SHIFT) & UART_FCR_TFIFORST_MASK)
#define UART_FCR_TFIFORST_GET(x) (((uint32_t)(x) & UART_FCR_TFIFORST_MASK) >> UART_FCR_TFIFORST_SHIFT)

/*
 * RFIFORST (WO)
 *
 * Receiver FIFO reset
 * Write 1 to clear all bytes in the RXFIFO and resets its
 * counter. The Receiver Shift Register is not cleared.
 * This bit will automatically be cleared.
 */
#define UART_FCR_RFIFORST_MASK (0x2U)
#define UART_FCR_RFIFORST_SHIFT (1U)
#define UART_FCR_RFIFORST_SET(x) (((uint32_t)(x) << UART_FCR_RFIFORST_SHIFT) & UART_FCR_RFIFORST_MASK)
#define UART_FCR_RFIFORST_GET(x) (((uint32_t)(x) & UART_FCR_RFIFORST_MASK) >> UART_FCR_RFIFORST_SHIFT)

/*
 * FIFOE (WO)
 *
 * FIFO enable
 * Write 1 to enable both the transmitter and receiver
 * FIFOs.
 * The FIFOs are reset when the value of this bit toggles.
 */
#define UART_FCR_FIFOE_MASK (0x1U)
#define UART_FCR_FIFOE_SHIFT (0U)
#define UART_FCR_FIFOE_SET(x) (((uint32_t)(x) << UART_FCR_FIFOE_SHIFT) & UART_FCR_FIFOE_MASK)
#define UART_FCR_FIFOE_GET(x) (((uint32_t)(x) & UART_FCR_FIFOE_MASK) >> UART_FCR_FIFOE_SHIFT)

/* Bitfield definition for register: LCR */
/*
 * DLAB (RW)
 *
 * Divisor latch access bit
 */
#define UART_LCR_DLAB_MASK (0x80U)
#define UART_LCR_DLAB_SHIFT (7U)
#define UART_LCR_DLAB_SET(x) (((uint32_t)(x) << UART_LCR_DLAB_SHIFT) & UART_LCR_DLAB_MASK)
#define UART_LCR_DLAB_GET(x) (((uint32_t)(x) & UART_LCR_DLAB_MASK) >> UART_LCR_DLAB_SHIFT)

/*
 * BC (RW)
 *
 * Break control
 */
#define UART_LCR_BC_MASK (0x40U)
#define UART_LCR_BC_SHIFT (6U)
#define UART_LCR_BC_SET(x) (((uint32_t)(x) << UART_LCR_BC_SHIFT) & UART_LCR_BC_MASK)
#define UART_LCR_BC_GET(x) (((uint32_t)(x) & UART_LCR_BC_MASK) >> UART_LCR_BC_SHIFT)

/*
 * SPS (RW)
 *
 * Stick parity
 * 1: Parity bit is constant 0 or 1, depending on bit4 (EPS).
 * 0: Disable the sticky bit parity.
 */
#define UART_LCR_SPS_MASK (0x20U)
#define UART_LCR_SPS_SHIFT (5U)
#define UART_LCR_SPS_SET(x) (((uint32_t)(x) << UART_LCR_SPS_SHIFT) & UART_LCR_SPS_MASK)
#define UART_LCR_SPS_GET(x) (((uint32_t)(x) & UART_LCR_SPS_MASK) >> UART_LCR_SPS_SHIFT)

/*
 * EPS (RW)
 *
 * Even parity select
 * 1: Even parity (an even number of logic-1 is in the data
 * and parity bits)
 * 0: Old parity.
 */
#define UART_LCR_EPS_MASK (0x10U)
#define UART_LCR_EPS_SHIFT (4U)
#define UART_LCR_EPS_SET(x) (((uint32_t)(x) << UART_LCR_EPS_SHIFT) & UART_LCR_EPS_MASK)
#define UART_LCR_EPS_GET(x) (((uint32_t)(x) & UART_LCR_EPS_MASK) >> UART_LCR_EPS_SHIFT)

/*
 * PEN (RW)
 *
 * Parity enable
 * When this bit is set, a parity bit is generated in
 * transmitted data before the first STOP bit and the parity
 * bit would be checked for the received data.
 */
#define UART_LCR_PEN_MASK (0x8U)
#define UART_LCR_PEN_SHIFT (3U)
#define UART_LCR_PEN_SET(x) (((uint32_t)(x) << UART_LCR_PEN_SHIFT) & UART_LCR_PEN_MASK)
#define UART_LCR_PEN_GET(x) (((uint32_t)(x) & UART_LCR_PEN_MASK) >> UART_LCR_PEN_SHIFT)

/*
 * STB (RW)
 *
 * Number of STOP bits
 * 0: 1 bits
 * 1: The number of STOP bit is based on the WLS setting
 * When WLS = 0, STOP bit is 1.5 bits
 * When WLS = 1, 2, 3, STOP bit is 2 bits
 */
#define UART_LCR_STB_MASK (0x4U)
#define UART_LCR_STB_SHIFT (2U)
#define UART_LCR_STB_SET(x) (((uint32_t)(x) << UART_LCR_STB_SHIFT) & UART_LCR_STB_MASK)
#define UART_LCR_STB_GET(x) (((uint32_t)(x) & UART_LCR_STB_MASK) >> UART_LCR_STB_SHIFT)

/*
 * WLS (RW)
 *
 * Word length setting
 * 0: 5 bits
 * 1: 6 bits
 * 2: 7 bits
 * 3: 8 bits
 */
#define UART_LCR_WLS_MASK (0x3U)
#define UART_LCR_WLS_SHIFT (0U)
#define UART_LCR_WLS_SET(x) (((uint32_t)(x) << UART_LCR_WLS_SHIFT) & UART_LCR_WLS_MASK)
#define UART_LCR_WLS_GET(x) (((uint32_t)(x) & UART_LCR_WLS_MASK) >> UART_LCR_WLS_SHIFT)

/* Bitfield definition for register: MCR */
/*
 * AFE (RW)
 *
 * Auto flow control enable
 * 0: Disable
 * 1: The auto-CTS and auto-RTS setting is based on the
 * RTS bit setting:
 * When RTS = 0, auto-CTS only
 * When RTS = 1, auto-CTS and auto-RTS
 */
#define UART_MCR_AFE_MASK (0x20U)
#define UART_MCR_AFE_SHIFT (5U)
#define UART_MCR_AFE_SET(x) (((uint32_t)(x) << UART_MCR_AFE_SHIFT) & UART_MCR_AFE_MASK)
#define UART_MCR_AFE_GET(x) (((uint32_t)(x) & UART_MCR_AFE_MASK) >> UART_MCR_AFE_SHIFT)

/*
 * LOOP (RW)
 *
 * Enable loopback mode
 * 0: Disable
 * 1: Enable
 */
#define UART_MCR_LOOP_MASK (0x10U)
#define UART_MCR_LOOP_SHIFT (4U)
#define UART_MCR_LOOP_SET(x) (((uint32_t)(x) << UART_MCR_LOOP_SHIFT) & UART_MCR_LOOP_MASK)
#define UART_MCR_LOOP_GET(x) (((uint32_t)(x) & UART_MCR_LOOP_MASK) >> UART_MCR_LOOP_SHIFT)

/*
 * RTS (RW)
 *
 * Request to send
 * This bit controls the modem_rtsn output.
 * 0: The modem_rtsn output signal will be driven HIGH
 * 1: The modem_rtsn output signal will be driven LOW
 */
#define UART_MCR_RTS_MASK (0x2U)
#define UART_MCR_RTS_SHIFT (1U)
#define UART_MCR_RTS_SET(x) (((uint32_t)(x) << UART_MCR_RTS_SHIFT) & UART_MCR_RTS_MASK)
#define UART_MCR_RTS_GET(x) (((uint32_t)(x) & UART_MCR_RTS_MASK) >> UART_MCR_RTS_SHIFT)

/* Bitfield definition for register: LSR */
/*
 * RXIDLE (RO)
 *
 * rxidle after timeout, clear after rx idle condition not match
 */
#define UART_LSR_RXIDLE_MASK (0x80000000UL)
#define UART_LSR_RXIDLE_SHIFT (31U)
#define UART_LSR_RXIDLE_GET(x) (((uint32_t)(x) & UART_LSR_RXIDLE_MASK) >> UART_LSR_RXIDLE_SHIFT)

/*
 * TXIDLE (RO)
 *
 * txidle after timeout, clear after tx idle condition not match
 */
#define UART_LSR_TXIDLE_MASK (0x40000000UL)
#define UART_LSR_TXIDLE_SHIFT (30U)
#define UART_LSR_TXIDLE_GET(x) (((uint32_t)(x) & UART_LSR_TXIDLE_MASK) >> UART_LSR_TXIDLE_SHIFT)

/*
 * RFIFO_NUM (RO)
 *
 * data bytes in rxfifo not read
 */
#define UART_LSR_RFIFO_NUM_MASK (0x1F0000UL)
#define UART_LSR_RFIFO_NUM_SHIFT (16U)
#define UART_LSR_RFIFO_NUM_GET(x) (((uint32_t)(x) & UART_LSR_RFIFO_NUM_MASK) >> UART_LSR_RFIFO_NUM_SHIFT)

/*
 * TFIFO_NUM (RO)
 *
 * data bytes in txfifo not sent
 */
#define UART_LSR_TFIFO_NUM_MASK (0x1F00U)
#define UART_LSR_TFIFO_NUM_SHIFT (8U)
#define UART_LSR_TFIFO_NUM_GET(x) (((uint32_t)(x) & UART_LSR_TFIFO_NUM_MASK) >> UART_LSR_TFIFO_NUM_SHIFT)

/*
 * ERRF (RO)
 *
 * Error in RXFIFO
 * In the FIFO mode, this bit is set when there is at least
 * one parity error, framing error, or line break
 * associated with data in the RXFIFO. It is cleared when
 * this register is read and there is no more error for the
 * rest of data in the RXFIFO.
 */
#define UART_LSR_ERRF_MASK (0x80U)
#define UART_LSR_ERRF_SHIFT (7U)
#define UART_LSR_ERRF_GET(x) (((uint32_t)(x) & UART_LSR_ERRF_MASK) >> UART_LSR_ERRF_SHIFT)

/*
 * TEMT (RO)
 *
 * Transmitter empty
 * This bit is 1 when the THR (TXFIFO in the FIFO
 * mode) and the Transmitter Shift Register (TSR) are
 * both empty. Otherwise, it is zero.
 */
#define UART_LSR_TEMT_MASK (0x40U)
#define UART_LSR_TEMT_SHIFT (6U)
#define UART_LSR_TEMT_GET(x) (((uint32_t)(x) & UART_LSR_TEMT_MASK) >> UART_LSR_TEMT_SHIFT)

/*
 * THRE (RO)
 *
 * Transmitter Holding Register empty
 * This bit is 1 when the THR (TXFIFO in the FIFO
 * mode) is empty. Otherwise, it is zero.
 * If the THRE interrupt is enabled, an interrupt is
 * triggered when THRE becomes 1.
 */
#define UART_LSR_THRE_MASK (0x20U)
#define UART_LSR_THRE_SHIFT (5U)
#define UART_LSR_THRE_GET(x) (((uint32_t)(x) & UART_LSR_THRE_MASK) >> UART_LSR_THRE_SHIFT)

/*
 * LBREAK (RO)
 *
 * Line break
 * This bit is set when the uart_sin input signal was held
 * LOWfor longer than the time for a full-word
 * transmission. A full-word transmission is the
 * transmission of the START, data, parity, and STOP
 * bits. It is cleared when this register is read.
 * In the FIFO mode, this bit indicates the line break for
 * the received data at the top of the RXFIFO.
 */
#define UART_LSR_LBREAK_MASK (0x10U)
#define UART_LSR_LBREAK_SHIFT (4U)
#define UART_LSR_LBREAK_GET(x) (((uint32_t)(x) & UART_LSR_LBREAK_MASK) >> UART_LSR_LBREAK_SHIFT)

/*
 * FE (RO)
 *
 * Framing error
 * This bit is set when the received STOP bit is not
 * HIGH. It is cleared when this register is read.
 * In the FIFO mode, this bit indicates the framing error
 * for the received data at the top of the RXFIFO.
 */
#define UART_LSR_FE_MASK (0x8U)
#define UART_LSR_FE_SHIFT (3U)
#define UART_LSR_FE_GET(x) (((uint32_t)(x) & UART_LSR_FE_MASK) >> UART_LSR_FE_SHIFT)

/*
 * PE (RO)
 *
 * Parity error
 * This bit is set when the received parity does not match
 * with the parity selected in the LCR[5:4]. It is cleared
 * when this register is read.
 * In the FIFO mode, this bit indicates the parity error
 * for the received data at the top of the RXFIFO.
 */
#define UART_LSR_PE_MASK (0x4U)
#define UART_LSR_PE_SHIFT (2U)
#define UART_LSR_PE_GET(x) (((uint32_t)(x) & UART_LSR_PE_MASK) >> UART_LSR_PE_SHIFT)

/*
 * OE (RO)
 *
 * Overrun error
 * This bit indicates that data in the Receiver Buffer
 * Register (RBR) is overrun.
 */
#define UART_LSR_OE_MASK (0x2U)
#define UART_LSR_OE_SHIFT (1U)
#define UART_LSR_OE_GET(x) (((uint32_t)(x) & UART_LSR_OE_MASK) >> UART_LSR_OE_SHIFT)

/*
 * DR (RO)
 *
 * Data ready.
 * This bit is set when there are incoming received data
 * in the Receiver Buffer Register (RBR). It is cleared
 * when all of the received data are read.
 */
#define UART_LSR_DR_MASK (0x1U)
#define UART_LSR_DR_SHIFT (0U)
#define UART_LSR_DR_GET(x) (((uint32_t)(x) & UART_LSR_DR_MASK) >> UART_LSR_DR_SHIFT)

/* Bitfield definition for register: MSR */
/*
 * CTS (RO)
 *
 * Clear to send
 * 0: The modem_ctsn input signal is HIGH.
 * 1: The modem_ctsn input signal is LOW.
 */
#define UART_MSR_CTS_MASK (0x10U)
#define UART_MSR_CTS_SHIFT (4U)
#define UART_MSR_CTS_GET(x) (((uint32_t)(x) & UART_MSR_CTS_MASK) >> UART_MSR_CTS_SHIFT)

/*
 * DCTS (RC)
 *
 * Delta clear to send
 * This bit is set when the state of the modem_ctsn input
 * signal has been changed since the last time this
 * register is read.
 */
#define UART_MSR_DCTS_MASK (0x1U)
#define UART_MSR_DCTS_SHIFT (0U)
#define UART_MSR_DCTS_GET(x) (((uint32_t)(x) & UART_MSR_DCTS_MASK) >> UART_MSR_DCTS_SHIFT)

/* Bitfield definition for register: GPR */
/*
 * DATA (RW)
 *
 * A one-byte storage register
 */
#define UART_GPR_DATA_MASK (0xFFU)
#define UART_GPR_DATA_SHIFT (0U)
#define UART_GPR_DATA_SET(x) (((uint32_t)(x) << UART_GPR_DATA_SHIFT) & UART_GPR_DATA_MASK)
#define UART_GPR_DATA_GET(x) (((uint32_t)(x) & UART_GPR_DATA_MASK) >> UART_GPR_DATA_SHIFT)




#endif /* HPM_UART_H */
