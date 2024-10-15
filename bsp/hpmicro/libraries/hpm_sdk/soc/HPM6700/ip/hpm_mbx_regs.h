/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_MBX_H
#define HPM_MBX_H

typedef struct {
    __RW uint32_t CR;                          /* 0x0: Command Registers */
    __RW uint32_t SR;                          /* 0x4: Status Registers */
    __W  uint32_t TXREG;                       /* 0x8: Transmit word message to other core. */
    __R  uint32_t RXREG;                       /* 0xC: Receive word message from other core. */
    __W  uint32_t TXWRD[1];                    /* 0x10: TXFIFO for sending message to other core */
    __R  uint8_t  RESERVED0[12];               /* 0x14 - 0x1F: Reserved */
    __R  uint32_t RXWRD[1];                    /* 0x20: RXFIFO for receiving message from other core */
} MBX_Type;


/* Bitfield definition for register: CR */
/*
 * TXRESET (RW)
 *
 * Reset TX Fifo and word.
 */
#define MBX_CR_TXRESET_MASK (0x80000000UL)
#define MBX_CR_TXRESET_SHIFT (31U)
#define MBX_CR_TXRESET_SET(x) (((uint32_t)(x) << MBX_CR_TXRESET_SHIFT) & MBX_CR_TXRESET_MASK)
#define MBX_CR_TXRESET_GET(x) (((uint32_t)(x) & MBX_CR_TXRESET_MASK) >> MBX_CR_TXRESET_SHIFT)

/*
 * BARCTL (RW)
 *
 * Bus Access Response Control, when bit 15:14=
 * 00: no bus error will be generated,      no wait for fifo write when fifo full and  no wait for word/fifo read when word message invalid or fifo empty; or when write to word/fifo message will be ignored.
 *  01: bus error will be generated when: 1, access invalid address; 2, write to ready only addr; 3, write to fulled fifo or valid message; 4, read from a emptied fifo/word message.
 * 10: no error will be generated, but bus will wait when 1, write to fulled fifo/reg message; 2, read from a emptied fifo/reg message; write to word message will overwrite the existing reg value enven word message are still valid; read from invalid word message will read out last read out message data.happen.
 * 11: reserved.
 */
#define MBX_CR_BARCTL_MASK (0xC000U)
#define MBX_CR_BARCTL_SHIFT (14U)
#define MBX_CR_BARCTL_SET(x) (((uint32_t)(x) << MBX_CR_BARCTL_SHIFT) & MBX_CR_BARCTL_MASK)
#define MBX_CR_BARCTL_GET(x) (((uint32_t)(x) & MBX_CR_BARCTL_MASK) >> MBX_CR_BARCTL_SHIFT)

/*
 * BEIE (RW)
 *
 * Bus Error Interrupt Enable, will enable the interrupt for any bus  error as described in the SR bit 13 to bit 8.
 * 1, enable the bus access error interrupt.
 * 0, disable the bus access error interrupt.
 */
#define MBX_CR_BEIE_MASK (0x100U)
#define MBX_CR_BEIE_SHIFT (8U)
#define MBX_CR_BEIE_SET(x) (((uint32_t)(x) << MBX_CR_BEIE_SHIFT) & MBX_CR_BEIE_MASK)
#define MBX_CR_BEIE_GET(x) (((uint32_t)(x) & MBX_CR_BEIE_MASK) >> MBX_CR_BEIE_SHIFT)

/*
 * TFMAIE (RW)
 *
 * TX FIFO message available interrupt enable.
 * 1, enable the TX FIFO massage available interrupt.
 * 0, disable the TX FIFO message available interrupt.
 */
#define MBX_CR_TFMAIE_MASK (0x80U)
#define MBX_CR_TFMAIE_SHIFT (7U)
#define MBX_CR_TFMAIE_SET(x) (((uint32_t)(x) << MBX_CR_TFMAIE_SHIFT) & MBX_CR_TFMAIE_MASK)
#define MBX_CR_TFMAIE_GET(x) (((uint32_t)(x) & MBX_CR_TFMAIE_MASK) >> MBX_CR_TFMAIE_SHIFT)

/*
 * TFMEIE (RW)
 *
 * TX FIFO message empty interrupt enable.
 * 1, enable the TX FIFO massage empty interrupt.
 * 0, disable the TX FIFO message empty interrupt.
 */
#define MBX_CR_TFMEIE_MASK (0x40U)
#define MBX_CR_TFMEIE_SHIFT (6U)
#define MBX_CR_TFMEIE_SET(x) (((uint32_t)(x) << MBX_CR_TFMEIE_SHIFT) & MBX_CR_TFMEIE_MASK)
#define MBX_CR_TFMEIE_GET(x) (((uint32_t)(x) & MBX_CR_TFMEIE_MASK) >> MBX_CR_TFMEIE_SHIFT)

/*
 * RFMAIE (RW)
 *
 * RX FIFO message available interrupt enable.
 * 1, enable the RX FIFO massage available interrupt.
 * 0, disable the RX FIFO message available interrupt.
 */
#define MBX_CR_RFMAIE_MASK (0x20U)
#define MBX_CR_RFMAIE_SHIFT (5U)
#define MBX_CR_RFMAIE_SET(x) (((uint32_t)(x) << MBX_CR_RFMAIE_SHIFT) & MBX_CR_RFMAIE_MASK)
#define MBX_CR_RFMAIE_GET(x) (((uint32_t)(x) & MBX_CR_RFMAIE_MASK) >> MBX_CR_RFMAIE_SHIFT)

/*
 * RFMFIE (RW)
 *
 * RX fifo message full interrupt enable.
 * 1, enable the RX fifo message full interrupt.
 * 0, disable the RX fifo message full interrupt.
 */
#define MBX_CR_RFMFIE_MASK (0x10U)
#define MBX_CR_RFMFIE_SHIFT (4U)
#define MBX_CR_RFMFIE_SET(x) (((uint32_t)(x) << MBX_CR_RFMFIE_SHIFT) & MBX_CR_RFMFIE_MASK)
#define MBX_CR_RFMFIE_GET(x) (((uint32_t)(x) & MBX_CR_RFMFIE_MASK) >> MBX_CR_RFMFIE_SHIFT)

/*
 * TWMEIE (RW)
 *
 * TX word message empty interrupt enable.
 * 1, enable the TX word massage empty interrupt.
 * 0, disable the TX word message empty interrupt.
 */
#define MBX_CR_TWMEIE_MASK (0x2U)
#define MBX_CR_TWMEIE_SHIFT (1U)
#define MBX_CR_TWMEIE_SET(x) (((uint32_t)(x) << MBX_CR_TWMEIE_SHIFT) & MBX_CR_TWMEIE_MASK)
#define MBX_CR_TWMEIE_GET(x) (((uint32_t)(x) & MBX_CR_TWMEIE_MASK) >> MBX_CR_TWMEIE_SHIFT)

/*
 * RWMVIE (RW)
 *
 * RX word message valid interrupt enable.
 * 1, enable the RX word massage valid interrupt.
 * 0, disable the RX word message valid interrupt.
 */
#define MBX_CR_RWMVIE_MASK (0x1U)
#define MBX_CR_RWMVIE_SHIFT (0U)
#define MBX_CR_RWMVIE_SET(x) (((uint32_t)(x) << MBX_CR_RWMVIE_SHIFT) & MBX_CR_RWMVIE_MASK)
#define MBX_CR_RWMVIE_GET(x) (((uint32_t)(x) & MBX_CR_RWMVIE_MASK) >> MBX_CR_RWMVIE_SHIFT)

/* Bitfield definition for register: SR */
/*
 * RFVC (RO)
 *
 * RX FIFO valid message count
 */
#define MBX_SR_RFVC_MASK (0xF00000UL)
#define MBX_SR_RFVC_SHIFT (20U)
#define MBX_SR_RFVC_GET(x) (((uint32_t)(x) & MBX_SR_RFVC_MASK) >> MBX_SR_RFVC_SHIFT)

/*
 * TFEC (RO)
 *
 * TX FIFO empty message word count
 */
#define MBX_SR_TFEC_MASK (0xF0000UL)
#define MBX_SR_TFEC_SHIFT (16U)
#define MBX_SR_TFEC_GET(x) (((uint32_t)(x) & MBX_SR_TFEC_MASK) >> MBX_SR_TFEC_SHIFT)

/*
 * ERRRE (W1C)
 *
 * bus Error for read when rx word message are still invalid, this bit is W1C bit.
 * 1, read from word message when the word message are still invalid will cause this error bit set.
 * 0, nothis kind of bus error; write this bit to 1 will clear this bit when this kind of error happen.
 */
#define MBX_SR_ERRRE_MASK (0x2000U)
#define MBX_SR_ERRRE_SHIFT (13U)
#define MBX_SR_ERRRE_SET(x) (((uint32_t)(x) << MBX_SR_ERRRE_SHIFT) & MBX_SR_ERRRE_MASK)
#define MBX_SR_ERRRE_GET(x) (((uint32_t)(x) & MBX_SR_ERRRE_MASK) >> MBX_SR_ERRRE_SHIFT)

/*
 * EWTRF (W1C)
 *
 * bus Error for write when tx word message are still valid, this bit is W1C bit.
 * 1, write to word message when the word message are still valid will cause this error bit set.
 * 0, nothis kind of bus error; write this bit to 1 will clear this bit when this kind of error happen.
 */
#define MBX_SR_EWTRF_MASK (0x1000U)
#define MBX_SR_EWTRF_SHIFT (12U)
#define MBX_SR_EWTRF_SET(x) (((uint32_t)(x) << MBX_SR_EWTRF_SHIFT) & MBX_SR_EWTRF_MASK)
#define MBX_SR_EWTRF_GET(x) (((uint32_t)(x) & MBX_SR_EWTRF_MASK) >> MBX_SR_EWTRF_SHIFT)

/*
 * ERRFE (W1C)
 *
 * bus Error for read when rx fifo empty, this bit is W1C bit.
 * 1, read from a empty rx fifo will cause this error bit set.
 * 0, nothis kind of bus error; write this bit to 1 will clear this bit when this kind of error happen.
 */
#define MBX_SR_ERRFE_MASK (0x800U)
#define MBX_SR_ERRFE_SHIFT (11U)
#define MBX_SR_ERRFE_SET(x) (((uint32_t)(x) << MBX_SR_ERRFE_SHIFT) & MBX_SR_ERRFE_MASK)
#define MBX_SR_ERRFE_GET(x) (((uint32_t)(x) & MBX_SR_ERRFE_MASK) >> MBX_SR_ERRFE_SHIFT)

/*
 * EWTFF (W1C)
 *
 * bus Error for write when tx fifo full, this bit is W1C bit.
 * 1, write to a fulled tx fifo will cause this error bit set.
 * 0, nothis kind of bus error; write this bit to 1 will clear this bit when this kind of error happen.
 */
#define MBX_SR_EWTFF_MASK (0x400U)
#define MBX_SR_EWTFF_SHIFT (10U)
#define MBX_SR_EWTFF_SET(x) (((uint32_t)(x) << MBX_SR_EWTFF_SHIFT) & MBX_SR_EWTFF_MASK)
#define MBX_SR_EWTFF_GET(x) (((uint32_t)(x) & MBX_SR_EWTFF_MASK) >> MBX_SR_EWTFF_SHIFT)

/*
 * EAIVA (W1C)
 *
 * bus Error for Accessing Invalid Address; this bit is W1C bit.
 * 1, read and write to invalid address in the bus of this block, will set this bit.
 * 0, nothis kind of bus error; write this bit to 1 will clear this bit when this kind of error happen.
 */
#define MBX_SR_EAIVA_MASK (0x200U)
#define MBX_SR_EAIVA_SHIFT (9U)
#define MBX_SR_EAIVA_SET(x) (((uint32_t)(x) << MBX_SR_EAIVA_SHIFT) & MBX_SR_EAIVA_MASK)
#define MBX_SR_EAIVA_GET(x) (((uint32_t)(x) & MBX_SR_EAIVA_MASK) >> MBX_SR_EAIVA_SHIFT)

/*
 * EW2RO (W1C)
 *
 * bus Error for Write to Read Only address; this bit is W1C bit.
 * 1, write to read only address happened in the bus of this block.
 * 0, nothis kind of bus error; write this bit to 1 will clear this bit when this kind of error happen.
 */
#define MBX_SR_EW2RO_MASK (0x100U)
#define MBX_SR_EW2RO_SHIFT (8U)
#define MBX_SR_EW2RO_SET(x) (((uint32_t)(x) << MBX_SR_EW2RO_SHIFT) & MBX_SR_EW2RO_MASK)
#define MBX_SR_EW2RO_GET(x) (((uint32_t)(x) & MBX_SR_EW2RO_MASK) >> MBX_SR_EW2RO_SHIFT)

/*
 * TFMA (RW)
 *
 * TX FIFO Message slot available, the 4x32 TX FIFO message buffer to the other core full, will not trigger any interrupt.
 * 1, TXFIFO message buffer has slot available
 * 0, no slot available (fifo full)
 */
#define MBX_SR_TFMA_MASK (0x80U)
#define MBX_SR_TFMA_SHIFT (7U)
#define MBX_SR_TFMA_SET(x) (((uint32_t)(x) << MBX_SR_TFMA_SHIFT) & MBX_SR_TFMA_MASK)
#define MBX_SR_TFMA_GET(x) (((uint32_t)(x) & MBX_SR_TFMA_MASK) >> MBX_SR_TFMA_SHIFT)

/*
 * TFME (RW)
 *
 * TX FIFO Message Empty, no any data in the message FIFO buffer from other core, will not trigger any interrupt.message from other core.
 * 1, no any message data in TXFIFO from other core.
 * 0, there are some data in the 4x32 TX FIFO from other core yet.
 */
#define MBX_SR_TFME_MASK (0x40U)
#define MBX_SR_TFME_SHIFT (6U)
#define MBX_SR_TFME_SET(x) (((uint32_t)(x) << MBX_SR_TFME_SHIFT) & MBX_SR_TFME_MASK)
#define MBX_SR_TFME_GET(x) (((uint32_t)(x) & MBX_SR_TFME_MASK) >> MBX_SR_TFME_SHIFT)

/*
 * RFMA (RO)
 *
 * RX FIFO Message Available, available data in the 4x32 TX FIFO message buffer to the other core, will trigger interrupt if the related interrupt enable bit set in the control (CR) registrer.
 * 1, no any data in the 4x32 TXFIFO message buffer.
 * 0, there are some data in the  the 4x32 TXFIFO message buffer already.
 */
#define MBX_SR_RFMA_MASK (0x20U)
#define MBX_SR_RFMA_SHIFT (5U)
#define MBX_SR_RFMA_GET(x) (((uint32_t)(x) & MBX_SR_RFMA_MASK) >> MBX_SR_RFMA_SHIFT)

/*
 * RFMF (RO)
 *
 * RX FIFO Message Full, message from other core; will trigger interrupt if the related interrupt enable bit set in the control (CR) registrer.
 * 1, the other core had written 4x32 message in the RXFIFO.
 * 0, no 4x32 RX FIFO message from other core yet.
 */
#define MBX_SR_RFMF_MASK (0x10U)
#define MBX_SR_RFMF_SHIFT (4U)
#define MBX_SR_RFMF_GET(x) (((uint32_t)(x) & MBX_SR_RFMF_MASK) >> MBX_SR_RFMF_SHIFT)

/*
 * TWME (RO)
 *
 * TX word message empty, will trigger interrupt if the related interrupt enable bit set in the control (CR) registrer.
 * 1, means this core had write word message to TXREG.
 * 0, means no valid word message in the TXREG yet.
 */
#define MBX_SR_TWME_MASK (0x2U)
#define MBX_SR_TWME_SHIFT (1U)
#define MBX_SR_TWME_GET(x) (((uint32_t)(x) & MBX_SR_TWME_MASK) >> MBX_SR_TWME_SHIFT)

/*
 * RWMV (RO)
 *
 * RX word message valid, will trigger interrupt if the related interrupt enable bit set in the control (CR) registrer.
 * 1, the other core had written word message in the RXREG.
 * 0, no valid word message yet in the RXREG.
 */
#define MBX_SR_RWMV_MASK (0x1U)
#define MBX_SR_RWMV_SHIFT (0U)
#define MBX_SR_RWMV_GET(x) (((uint32_t)(x) & MBX_SR_RWMV_MASK) >> MBX_SR_RWMV_SHIFT)

/* Bitfield definition for register: TXREG */
/*
 * TXREG (WO)
 *
 * Transmit word message to other core.
 */
#define MBX_TXREG_TXREG_MASK (0xFFFFFFFFUL)
#define MBX_TXREG_TXREG_SHIFT (0U)
#define MBX_TXREG_TXREG_SET(x) (((uint32_t)(x) << MBX_TXREG_TXREG_SHIFT) & MBX_TXREG_TXREG_MASK)
#define MBX_TXREG_TXREG_GET(x) (((uint32_t)(x) & MBX_TXREG_TXREG_MASK) >> MBX_TXREG_TXREG_SHIFT)

/* Bitfield definition for register: RXREG */
/*
 * RXREG (RO)
 *
 * Receive word message from other core.
 */
#define MBX_RXREG_RXREG_MASK (0xFFFFFFFFUL)
#define MBX_RXREG_RXREG_SHIFT (0U)
#define MBX_RXREG_RXREG_GET(x) (((uint32_t)(x) & MBX_RXREG_RXREG_MASK) >> MBX_RXREG_RXREG_SHIFT)

/* Bitfield definition for register array: TXWRD */
/*
 * TXFIFO (WO)
 *
 * TXFIFO for sending message to other core, FIFO size, 4x32
 * can write one of the word address to push data to the FIFO;
 * can also use 4x32 burst write from 0x010 to push 4 words to the FIFO.
 */
#define MBX_TXWRD_TXFIFO_MASK (0xFFFFFFFFUL)
#define MBX_TXWRD_TXFIFO_SHIFT (0U)
#define MBX_TXWRD_TXFIFO_SET(x) (((uint32_t)(x) << MBX_TXWRD_TXFIFO_SHIFT) & MBX_TXWRD_TXFIFO_MASK)
#define MBX_TXWRD_TXFIFO_GET(x) (((uint32_t)(x) & MBX_TXWRD_TXFIFO_MASK) >> MBX_TXWRD_TXFIFO_SHIFT)

/* Bitfield definition for register array: RXWRD */
/*
 * RXFIFO (RO)
 *
 * RXFIFO for receiving message from other core, FIFO size, 4x32
 * can read one of the word address to pop data to the FIFO;
 * can also use 4x32 burst read from 0x020 to read 4 words from the FIFO.
 */
#define MBX_RXWRD_RXFIFO_MASK (0xFFFFFFFFUL)
#define MBX_RXWRD_RXFIFO_SHIFT (0U)
#define MBX_RXWRD_RXFIFO_GET(x) (((uint32_t)(x) & MBX_RXWRD_RXFIFO_MASK) >> MBX_RXWRD_RXFIFO_SHIFT)



/* TXWRD register group index macro definition */
#define MBX_TXWRD_TXFIFO0 (0UL)

/* RXWRD register group index macro definition */
#define MBX_RXWRD_RXFIFO0 (0UL)


#endif /* HPM_MBX_H */
