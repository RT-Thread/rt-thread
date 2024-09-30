/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_I2C_H
#define HPM_I2C_H

typedef struct {
    __R  uint8_t  RESERVED0[16];               /* 0x0 - 0xF: Reserved */
    __RW uint32_t CFG;                         /* 0x10: Configuration Register */
    __RW uint32_t INTEN;                       /* 0x14: Interrupt Enable Register */
    __RW uint32_t STATUS;                      /* 0x18: Status Register */
    __RW uint32_t ADDR;                        /* 0x1C: Address Register */
    __RW uint32_t DATA;                        /* 0x20: Data Register */
    __RW uint32_t CTRL;                        /* 0x24: Control Register */
    __RW uint32_t CMD;                         /* 0x28: Command Register */
    __RW uint32_t SETUP;                       /* 0x2C: Setup Register */
    __RW uint32_t TPM;                         /* 0x30: I2C Timing Paramater Multiplier */
} I2C_Type;


/* Bitfield definition for register: CFG */
/*
 * FIFOSIZE (RO)
 *
 * FIFO Size:
 * 0: 2 bytes
 * 1: 4 bytes
 * 2: 8 bytes
 * 3: 16 bytes
 */
#define I2C_CFG_FIFOSIZE_MASK (0x3U)
#define I2C_CFG_FIFOSIZE_SHIFT (0U)
#define I2C_CFG_FIFOSIZE_GET(x) (((uint32_t)(x) & I2C_CFG_FIFOSIZE_MASK) >> I2C_CFG_FIFOSIZE_SHIFT)

/* Bitfield definition for register: INTEN */
/*
 * CMPL (RW)
 *
 * Set to enable the Completion Interrupt.
 * Master: interrupts when a transaction is issued from this master and completed without losing the bus arbitration.
 * Slave: interrupts when a transaction addressing the controller is completed.
 */
#define I2C_INTEN_CMPL_MASK (0x200U)
#define I2C_INTEN_CMPL_SHIFT (9U)
#define I2C_INTEN_CMPL_SET(x) (((uint32_t)(x) << I2C_INTEN_CMPL_SHIFT) & I2C_INTEN_CMPL_MASK)
#define I2C_INTEN_CMPL_GET(x) (((uint32_t)(x) & I2C_INTEN_CMPL_MASK) >> I2C_INTEN_CMPL_SHIFT)

/*
 * BYTERECV (RW)
 *
 * Set to enable the Byte Receive Interrupt.
 * Interrupts when a byte of data is received
 * Auto-ACK will be disabled if this interrupt is enabled, that is, the software needs to ACK/NACK the received byte manually.
 */
#define I2C_INTEN_BYTERECV_MASK (0x100U)
#define I2C_INTEN_BYTERECV_SHIFT (8U)
#define I2C_INTEN_BYTERECV_SET(x) (((uint32_t)(x) << I2C_INTEN_BYTERECV_SHIFT) & I2C_INTEN_BYTERECV_MASK)
#define I2C_INTEN_BYTERECV_GET(x) (((uint32_t)(x) & I2C_INTEN_BYTERECV_MASK) >> I2C_INTEN_BYTERECV_SHIFT)

/*
 * BYTETRANS (RW)
 *
 * Set to enable the Byte Transmit Interrupt.
 * Interrupts when a byte of data is transmitted.
 */
#define I2C_INTEN_BYTETRANS_MASK (0x80U)
#define I2C_INTEN_BYTETRANS_SHIFT (7U)
#define I2C_INTEN_BYTETRANS_SET(x) (((uint32_t)(x) << I2C_INTEN_BYTETRANS_SHIFT) & I2C_INTEN_BYTETRANS_MASK)
#define I2C_INTEN_BYTETRANS_GET(x) (((uint32_t)(x) & I2C_INTEN_BYTETRANS_MASK) >> I2C_INTEN_BYTETRANS_SHIFT)

/*
 * START (RW)
 *
 * Set to enable the START Condition Interrupt.
 * Interrupts when a START condition/repeated START condition is detected.
 */
#define I2C_INTEN_START_MASK (0x40U)
#define I2C_INTEN_START_SHIFT (6U)
#define I2C_INTEN_START_SET(x) (((uint32_t)(x) << I2C_INTEN_START_SHIFT) & I2C_INTEN_START_MASK)
#define I2C_INTEN_START_GET(x) (((uint32_t)(x) & I2C_INTEN_START_MASK) >> I2C_INTEN_START_SHIFT)

/*
 * STOP (RW)
 *
 * Set to enable the STOP Condition Interrupt
 * Interrupts when a STOP condition is detected.
 */
#define I2C_INTEN_STOP_MASK (0x20U)
#define I2C_INTEN_STOP_SHIFT (5U)
#define I2C_INTEN_STOP_SET(x) (((uint32_t)(x) << I2C_INTEN_STOP_SHIFT) & I2C_INTEN_STOP_MASK)
#define I2C_INTEN_STOP_GET(x) (((uint32_t)(x) & I2C_INTEN_STOP_MASK) >> I2C_INTEN_STOP_SHIFT)

/*
 * ARBLOSE (RW)
 *
 * Set to enable the Arbitration Lose Interrupt.
 * Master: interrupts when the controller loses the bus arbitration
 * Slave: not available in this mode.
 */
#define I2C_INTEN_ARBLOSE_MASK (0x10U)
#define I2C_INTEN_ARBLOSE_SHIFT (4U)
#define I2C_INTEN_ARBLOSE_SET(x) (((uint32_t)(x) << I2C_INTEN_ARBLOSE_SHIFT) & I2C_INTEN_ARBLOSE_MASK)
#define I2C_INTEN_ARBLOSE_GET(x) (((uint32_t)(x) & I2C_INTEN_ARBLOSE_MASK) >> I2C_INTEN_ARBLOSE_SHIFT)

/*
 * ADDRHIT (RW)
 *
 * Set to enable the Address Hit Interrupt.
 * Master: interrupts when the addressed slave returned an ACK.
 * Slave: interrupts when the controller is addressed.
 */
#define I2C_INTEN_ADDRHIT_MASK (0x8U)
#define I2C_INTEN_ADDRHIT_SHIFT (3U)
#define I2C_INTEN_ADDRHIT_SET(x) (((uint32_t)(x) << I2C_INTEN_ADDRHIT_SHIFT) & I2C_INTEN_ADDRHIT_MASK)
#define I2C_INTEN_ADDRHIT_GET(x) (((uint32_t)(x) & I2C_INTEN_ADDRHIT_MASK) >> I2C_INTEN_ADDRHIT_SHIFT)

/*
 * FIFOHALF (RW)
 *
 * Set to enable the FIFO Half Interrupt.
 * Receiver: Interrupts when the FIFO is half-empty, i.e, there is >= 1/2 entries in the FIFO.
 * Transmitter: Interrupts when the FIFO is half-empty, i.e. there is <= 1/2 entries in the FIFO.
 * This interrupt depends on the transaction direction; don’t enable this interrupt unless the transfer direction is determined, otherwise unintended interrupts may be triggered.
 */
#define I2C_INTEN_FIFOHALF_MASK (0x4U)
#define I2C_INTEN_FIFOHALF_SHIFT (2U)
#define I2C_INTEN_FIFOHALF_SET(x) (((uint32_t)(x) << I2C_INTEN_FIFOHALF_SHIFT) & I2C_INTEN_FIFOHALF_MASK)
#define I2C_INTEN_FIFOHALF_GET(x) (((uint32_t)(x) & I2C_INTEN_FIFOHALF_MASK) >> I2C_INTEN_FIFOHALF_SHIFT)

/*
 * FIFOFULL (RW)
 *
 * Set to enable the FIFO Full Interrupt.
 * Interrupts when the FIFO is full.
 */
#define I2C_INTEN_FIFOFULL_MASK (0x2U)
#define I2C_INTEN_FIFOFULL_SHIFT (1U)
#define I2C_INTEN_FIFOFULL_SET(x) (((uint32_t)(x) << I2C_INTEN_FIFOFULL_SHIFT) & I2C_INTEN_FIFOFULL_MASK)
#define I2C_INTEN_FIFOFULL_GET(x) (((uint32_t)(x) & I2C_INTEN_FIFOFULL_MASK) >> I2C_INTEN_FIFOFULL_SHIFT)

/*
 * FIFOEMPTY (RW)
 *
 * Set to enabled the FIFO Empty Interrupt
 * Interrupts when the FIFO is empty.
 */
#define I2C_INTEN_FIFOEMPTY_MASK (0x1U)
#define I2C_INTEN_FIFOEMPTY_SHIFT (0U)
#define I2C_INTEN_FIFOEMPTY_SET(x) (((uint32_t)(x) << I2C_INTEN_FIFOEMPTY_SHIFT) & I2C_INTEN_FIFOEMPTY_MASK)
#define I2C_INTEN_FIFOEMPTY_GET(x) (((uint32_t)(x) & I2C_INTEN_FIFOEMPTY_MASK) >> I2C_INTEN_FIFOEMPTY_SHIFT)

/* Bitfield definition for register: STATUS */
/*
 * LINESDA (RO)
 *
 * Indicates the current status of the SDA line on the bus
 * 1: high
 * 0: low
 */
#define I2C_STATUS_LINESDA_MASK (0x4000U)
#define I2C_STATUS_LINESDA_SHIFT (14U)
#define I2C_STATUS_LINESDA_GET(x) (((uint32_t)(x) & I2C_STATUS_LINESDA_MASK) >> I2C_STATUS_LINESDA_SHIFT)

/*
 * LINESCL (RO)
 *
 * Indicates the current status of the SCL line on the bus
 * 1: high
 * 0: low
 */
#define I2C_STATUS_LINESCL_MASK (0x2000U)
#define I2C_STATUS_LINESCL_SHIFT (13U)
#define I2C_STATUS_LINESCL_GET(x) (((uint32_t)(x) & I2C_STATUS_LINESCL_MASK) >> I2C_STATUS_LINESCL_SHIFT)

/*
 * GENCALL (RO)
 *
 * Indicates that the address of the current transaction is a general call address:
 * 1: General call
 * 0: Not general call
 */
#define I2C_STATUS_GENCALL_MASK (0x1000U)
#define I2C_STATUS_GENCALL_SHIFT (12U)
#define I2C_STATUS_GENCALL_GET(x) (((uint32_t)(x) & I2C_STATUS_GENCALL_MASK) >> I2C_STATUS_GENCALL_SHIFT)

/*
 * BUSBUSY (RO)
 *
 * Indicates that the bus is busy
 * The bus is busy when a START condition is on bus and it ends when a STOP condition is seen on bus
 * 1: Busy
 * 0: Not busy
 */
#define I2C_STATUS_BUSBUSY_MASK (0x800U)
#define I2C_STATUS_BUSBUSY_SHIFT (11U)
#define I2C_STATUS_BUSBUSY_GET(x) (((uint32_t)(x) & I2C_STATUS_BUSBUSY_MASK) >> I2C_STATUS_BUSBUSY_SHIFT)

/*
 * ACK (RO)
 *
 * Indicates the type of the last received/transmitted acknowledgement bit:
 * 1: ACK
 * 0: NACK
 */
#define I2C_STATUS_ACK_MASK (0x400U)
#define I2C_STATUS_ACK_SHIFT (10U)
#define I2C_STATUS_ACK_GET(x) (((uint32_t)(x) & I2C_STATUS_ACK_MASK) >> I2C_STATUS_ACK_SHIFT)

/*
 * CMPL (W1C)
 *
 * Transaction Completion
 * Master: Indicates that a transaction has been issued from this master and completed without losing the bus arbitration
 * Slave: Indicates that a transaction addressing the controller has been completed. This status bit must be cleared to receive the next transaction; otherwise, the next incoming transaction will be blocked.
 */
#define I2C_STATUS_CMPL_MASK (0x200U)
#define I2C_STATUS_CMPL_SHIFT (9U)
#define I2C_STATUS_CMPL_SET(x) (((uint32_t)(x) << I2C_STATUS_CMPL_SHIFT) & I2C_STATUS_CMPL_MASK)
#define I2C_STATUS_CMPL_GET(x) (((uint32_t)(x) & I2C_STATUS_CMPL_MASK) >> I2C_STATUS_CMPL_SHIFT)

/*
 * BYTERECV (W1C)
 *
 * Indicates that a byte of data has been received.
 */
#define I2C_STATUS_BYTERECV_MASK (0x100U)
#define I2C_STATUS_BYTERECV_SHIFT (8U)
#define I2C_STATUS_BYTERECV_SET(x) (((uint32_t)(x) << I2C_STATUS_BYTERECV_SHIFT) & I2C_STATUS_BYTERECV_MASK)
#define I2C_STATUS_BYTERECV_GET(x) (((uint32_t)(x) & I2C_STATUS_BYTERECV_MASK) >> I2C_STATUS_BYTERECV_SHIFT)

/*
 * BYTETRANS (W1C)
 *
 * Indicates that a byte of data has been transmitted.
 */
#define I2C_STATUS_BYTETRANS_MASK (0x80U)
#define I2C_STATUS_BYTETRANS_SHIFT (7U)
#define I2C_STATUS_BYTETRANS_SET(x) (((uint32_t)(x) << I2C_STATUS_BYTETRANS_SHIFT) & I2C_STATUS_BYTETRANS_MASK)
#define I2C_STATUS_BYTETRANS_GET(x) (((uint32_t)(x) & I2C_STATUS_BYTETRANS_MASK) >> I2C_STATUS_BYTETRANS_SHIFT)

/*
 * START (W1C)
 *
 * Indicates that a START Condition or a repeated START condition has been transmitted/received.
 */
#define I2C_STATUS_START_MASK (0x40U)
#define I2C_STATUS_START_SHIFT (6U)
#define I2C_STATUS_START_SET(x) (((uint32_t)(x) << I2C_STATUS_START_SHIFT) & I2C_STATUS_START_MASK)
#define I2C_STATUS_START_GET(x) (((uint32_t)(x) & I2C_STATUS_START_MASK) >> I2C_STATUS_START_SHIFT)

/*
 * STOP (W1C)
 *
 * Indicates that a STOP Condition has been transmitted/received.
 */
#define I2C_STATUS_STOP_MASK (0x20U)
#define I2C_STATUS_STOP_SHIFT (5U)
#define I2C_STATUS_STOP_SET(x) (((uint32_t)(x) << I2C_STATUS_STOP_SHIFT) & I2C_STATUS_STOP_MASK)
#define I2C_STATUS_STOP_GET(x) (((uint32_t)(x) & I2C_STATUS_STOP_MASK) >> I2C_STATUS_STOP_SHIFT)

/*
 * ARBLOSE (W1C)
 *
 * Indicates that the controller has lost the bus arbitration.
 */
#define I2C_STATUS_ARBLOSE_MASK (0x10U)
#define I2C_STATUS_ARBLOSE_SHIFT (4U)
#define I2C_STATUS_ARBLOSE_SET(x) (((uint32_t)(x) << I2C_STATUS_ARBLOSE_SHIFT) & I2C_STATUS_ARBLOSE_MASK)
#define I2C_STATUS_ARBLOSE_GET(x) (((uint32_t)(x) & I2C_STATUS_ARBLOSE_MASK) >> I2C_STATUS_ARBLOSE_SHIFT)

/*
 * ADDRHIT (W1C)
 *
 * Master: indicates that a slave has responded to the transaction.
 * Slave: indicates that a transaction is targeting the controller (including the General Call).
 */
#define I2C_STATUS_ADDRHIT_MASK (0x8U)
#define I2C_STATUS_ADDRHIT_SHIFT (3U)
#define I2C_STATUS_ADDRHIT_SET(x) (((uint32_t)(x) << I2C_STATUS_ADDRHIT_SHIFT) & I2C_STATUS_ADDRHIT_MASK)
#define I2C_STATUS_ADDRHIT_GET(x) (((uint32_t)(x) & I2C_STATUS_ADDRHIT_MASK) >> I2C_STATUS_ADDRHIT_SHIFT)

/*
 * FIFOHALF (RO)
 *
 * Transmitter: Indicates that the FIFO is half-empty.
 */
#define I2C_STATUS_FIFOHALF_MASK (0x4U)
#define I2C_STATUS_FIFOHALF_SHIFT (2U)
#define I2C_STATUS_FIFOHALF_GET(x) (((uint32_t)(x) & I2C_STATUS_FIFOHALF_MASK) >> I2C_STATUS_FIFOHALF_SHIFT)

/*
 * FIFOFULL (RO)
 *
 * Indicates that the FIFO is full.
 */
#define I2C_STATUS_FIFOFULL_MASK (0x2U)
#define I2C_STATUS_FIFOFULL_SHIFT (1U)
#define I2C_STATUS_FIFOFULL_GET(x) (((uint32_t)(x) & I2C_STATUS_FIFOFULL_MASK) >> I2C_STATUS_FIFOFULL_SHIFT)

/*
 * FIFOEMPTY (RO)
 *
 * Indicates that the FIFO is empty.
 */
#define I2C_STATUS_FIFOEMPTY_MASK (0x1U)
#define I2C_STATUS_FIFOEMPTY_SHIFT (0U)
#define I2C_STATUS_FIFOEMPTY_GET(x) (((uint32_t)(x) & I2C_STATUS_FIFOEMPTY_MASK) >> I2C_STATUS_FIFOEMPTY_SHIFT)

/* Bitfield definition for register: ADDR */
/*
 * ADDR (RW)
 *
 * The slave address.
 * For 7-bit addressing mode, the most significant 3 bits are ignored and only the least-significant 7 bits of Addr are valid
 */
#define I2C_ADDR_ADDR_MASK (0x3FFU)
#define I2C_ADDR_ADDR_SHIFT (0U)
#define I2C_ADDR_ADDR_SET(x) (((uint32_t)(x) << I2C_ADDR_ADDR_SHIFT) & I2C_ADDR_ADDR_MASK)
#define I2C_ADDR_ADDR_GET(x) (((uint32_t)(x) & I2C_ADDR_ADDR_MASK) >> I2C_ADDR_ADDR_SHIFT)

/* Bitfield definition for register: DATA */
/*
 * DATA (RW)
 *
 * Write this register to put one byte of data to the FIFO.
 * Read this register to get one byte of data from the FIFO.
 */
#define I2C_DATA_DATA_MASK (0xFFU)
#define I2C_DATA_DATA_SHIFT (0U)
#define I2C_DATA_DATA_SET(x) (((uint32_t)(x) << I2C_DATA_DATA_SHIFT) & I2C_DATA_DATA_MASK)
#define I2C_DATA_DATA_GET(x) (((uint32_t)(x) & I2C_DATA_DATA_MASK) >> I2C_DATA_DATA_SHIFT)

/* Bitfield definition for register: CTRL */
/*
 * DATACNT_HIGH (RW)
 *
 * Data counts in bytes.
 * Master: The number of bytes to transmit/receive. 0 means max length. DataCnt will be decreased by one for each byte transmitted/received.
 * Slave: the meaning of DataCnt depends on the DMA mode:
 * If DMA is not enabled, DataCnt is the number of bytes transmitted/received from the bus master. It is reset to 0 when the controller is addressed and then increased by one for each byte of data transmitted/received.
 * If DMA is enabled, DataCnt is the number of bytes to transmit/receive. It will not be reset to 0 when the slave is addressed and it will be decreased by one for each byte of data transmitted/received.
 */
#define I2C_CTRL_DATACNT_HIGH_MASK (0xFF000000UL)
#define I2C_CTRL_DATACNT_HIGH_SHIFT (24U)
#define I2C_CTRL_DATACNT_HIGH_SET(x) (((uint32_t)(x) << I2C_CTRL_DATACNT_HIGH_SHIFT) & I2C_CTRL_DATACNT_HIGH_MASK)
#define I2C_CTRL_DATACNT_HIGH_GET(x) (((uint32_t)(x) & I2C_CTRL_DATACNT_HIGH_MASK) >> I2C_CTRL_DATACNT_HIGH_SHIFT)

/*
 * RESET_LEN (RW)
 *
 * reset clock cycles. the clock high/low time is defined by Setup.T_SCLHi, 50% duty cycle.
 */
#define I2C_CTRL_RESET_LEN_MASK (0xF00000UL)
#define I2C_CTRL_RESET_LEN_SHIFT (20U)
#define I2C_CTRL_RESET_LEN_SET(x) (((uint32_t)(x) << I2C_CTRL_RESET_LEN_SHIFT) & I2C_CTRL_RESET_LEN_MASK)
#define I2C_CTRL_RESET_LEN_GET(x) (((uint32_t)(x) & I2C_CTRL_RESET_LEN_MASK) >> I2C_CTRL_RESET_LEN_SHIFT)

/*
 * RESET_HOLD_SCKIN (RW)
 *
 * set to hold input clock to high when reset is active
 */
#define I2C_CTRL_RESET_HOLD_SCKIN_MASK (0x4000U)
#define I2C_CTRL_RESET_HOLD_SCKIN_SHIFT (14U)
#define I2C_CTRL_RESET_HOLD_SCKIN_SET(x) (((uint32_t)(x) << I2C_CTRL_RESET_HOLD_SCKIN_SHIFT) & I2C_CTRL_RESET_HOLD_SCKIN_MASK)
#define I2C_CTRL_RESET_HOLD_SCKIN_GET(x) (((uint32_t)(x) & I2C_CTRL_RESET_HOLD_SCKIN_MASK) >> I2C_CTRL_RESET_HOLD_SCKIN_SHIFT)

/*
 * RESET_ON (RW)
 *
 * set to send reset signals(just toggle clock bus defined by reset_len).
 * this register is clered when reset is end, can't be cleared by software
 */
#define I2C_CTRL_RESET_ON_MASK (0x2000U)
#define I2C_CTRL_RESET_ON_SHIFT (13U)
#define I2C_CTRL_RESET_ON_SET(x) (((uint32_t)(x) << I2C_CTRL_RESET_ON_SHIFT) & I2C_CTRL_RESET_ON_MASK)
#define I2C_CTRL_RESET_ON_GET(x) (((uint32_t)(x) & I2C_CTRL_RESET_ON_MASK) >> I2C_CTRL_RESET_ON_SHIFT)

/*
 * PHASE_START (RW)
 *
 * Enable this bit to send a START condition at the beginning of transaction.
 * Master mode only.
 */
#define I2C_CTRL_PHASE_START_MASK (0x1000U)
#define I2C_CTRL_PHASE_START_SHIFT (12U)
#define I2C_CTRL_PHASE_START_SET(x) (((uint32_t)(x) << I2C_CTRL_PHASE_START_SHIFT) & I2C_CTRL_PHASE_START_MASK)
#define I2C_CTRL_PHASE_START_GET(x) (((uint32_t)(x) & I2C_CTRL_PHASE_START_MASK) >> I2C_CTRL_PHASE_START_SHIFT)

/*
 * PHASE_ADDR (RW)
 *
 * Enable this bit to send the address after START condition.
 * Master mode only.
 */
#define I2C_CTRL_PHASE_ADDR_MASK (0x800U)
#define I2C_CTRL_PHASE_ADDR_SHIFT (11U)
#define I2C_CTRL_PHASE_ADDR_SET(x) (((uint32_t)(x) << I2C_CTRL_PHASE_ADDR_SHIFT) & I2C_CTRL_PHASE_ADDR_MASK)
#define I2C_CTRL_PHASE_ADDR_GET(x) (((uint32_t)(x) & I2C_CTRL_PHASE_ADDR_MASK) >> I2C_CTRL_PHASE_ADDR_SHIFT)

/*
 * PHASE_DATA (RW)
 *
 * Enable this bit to send the data after Address phase.
 * Master mode only.
 */
#define I2C_CTRL_PHASE_DATA_MASK (0x400U)
#define I2C_CTRL_PHASE_DATA_SHIFT (10U)
#define I2C_CTRL_PHASE_DATA_SET(x) (((uint32_t)(x) << I2C_CTRL_PHASE_DATA_SHIFT) & I2C_CTRL_PHASE_DATA_MASK)
#define I2C_CTRL_PHASE_DATA_GET(x) (((uint32_t)(x) & I2C_CTRL_PHASE_DATA_MASK) >> I2C_CTRL_PHASE_DATA_SHIFT)

/*
 * PHASE_STOP (RW)
 *
 * Enable this bit to send a STOP condition at the end of a transaction.
 * Master mode only.
 */
#define I2C_CTRL_PHASE_STOP_MASK (0x200U)
#define I2C_CTRL_PHASE_STOP_SHIFT (9U)
#define I2C_CTRL_PHASE_STOP_SET(x) (((uint32_t)(x) << I2C_CTRL_PHASE_STOP_SHIFT) & I2C_CTRL_PHASE_STOP_MASK)
#define I2C_CTRL_PHASE_STOP_GET(x) (((uint32_t)(x) & I2C_CTRL_PHASE_STOP_MASK) >> I2C_CTRL_PHASE_STOP_SHIFT)

/*
 * DIR (RW)
 *
 * Transaction direction
 * Master: Set this bit to determine the direction for the next transaction.
 * 0: Transmitter
 * 1: Receiver
 * Slave: The direction of the last received transaction.
 * 0: Receiver
 * 1: Transmitter
 */
#define I2C_CTRL_DIR_MASK (0x100U)
#define I2C_CTRL_DIR_SHIFT (8U)
#define I2C_CTRL_DIR_SET(x) (((uint32_t)(x) << I2C_CTRL_DIR_SHIFT) & I2C_CTRL_DIR_MASK)
#define I2C_CTRL_DIR_GET(x) (((uint32_t)(x) & I2C_CTRL_DIR_MASK) >> I2C_CTRL_DIR_SHIFT)

/*
 * DATACNT (RW)
 *
 * Data counts in bytes.
 * Master: The number of bytes to transmit/receive. 0 means max length. DataCnt will be decreased by one for each byte transmitted/received.
 * Slave: the meaning of DataCnt depends on the DMA mode:
 * If DMA is not enabled, DataCnt is the number of bytes transmitted/received from the bus master. It is reset to 0 when the controller is addressed and then increased by one for each byte of data transmitted/received.
 * If DMA is enabled, DataCnt is the number of bytes to transmit/receive. It will not be reset to 0 when the slave is addressed and it will be decreased by one for each byte of data transmitted/received.
 */
#define I2C_CTRL_DATACNT_MASK (0xFFU)
#define I2C_CTRL_DATACNT_SHIFT (0U)
#define I2C_CTRL_DATACNT_SET(x) (((uint32_t)(x) << I2C_CTRL_DATACNT_SHIFT) & I2C_CTRL_DATACNT_MASK)
#define I2C_CTRL_DATACNT_GET(x) (((uint32_t)(x) & I2C_CTRL_DATACNT_MASK) >> I2C_CTRL_DATACNT_SHIFT)

/* Bitfield definition for register: CMD */
/*
 * CMD (RW)
 *
 * Write this register with the following values to perform the corresponding actions:
 * 0x0: no action
 * 0x1: issue a data transaction (Master only)
 * 0x2: respond with an ACK to the received byte
 * 0x3: respond with a NACK to the received byte
 * 0x4: clear the FIFO
 * 0x5: reset the I2C controller (abort current transaction, set the SDA and SCL line to the open-drain mode, reset the Status Register and the Interrupt Enable Register, and empty the FIFO)
 * When issuing a data transaction by writing 0x1 to this register, the CMD field stays at 0x1 for the duration of the entire transaction, and it is only cleared to 0x0 after when the transaction has completed or when the controller loses the arbitration.
 * Note: No transaction will be issued by the controller when all phases (Start, Address, Data and Stop) are disabled.
 */
#define I2C_CMD_CMD_MASK (0x7U)
#define I2C_CMD_CMD_SHIFT (0U)
#define I2C_CMD_CMD_SET(x) (((uint32_t)(x) << I2C_CMD_CMD_SHIFT) & I2C_CMD_CMD_MASK)
#define I2C_CMD_CMD_GET(x) (((uint32_t)(x) & I2C_CMD_CMD_MASK) >> I2C_CMD_CMD_SHIFT)

/* Bitfield definition for register: SETUP */
/*
 * T_SUDAT (RW)
 *
 * T_SUDAT defines the data setup time before releasing the SCL.
 * Setup time = (2 * tpclk) + (2 + T_SP + T_SUDAT) * tpclk* (TPM+1)
 * tpclk = PCLK period
 * TPM = The multiplier value in Timing Parameter Multiplier Register
 */
#define I2C_SETUP_T_SUDAT_MASK (0x1F000000UL)
#define I2C_SETUP_T_SUDAT_SHIFT (24U)
#define I2C_SETUP_T_SUDAT_SET(x) (((uint32_t)(x) << I2C_SETUP_T_SUDAT_SHIFT) & I2C_SETUP_T_SUDAT_MASK)
#define I2C_SETUP_T_SUDAT_GET(x) (((uint32_t)(x) & I2C_SETUP_T_SUDAT_MASK) >> I2C_SETUP_T_SUDAT_SHIFT)

/*
 * T_SP (RW)
 *
 * T_SP defines the pulse width of spikes that must be suppressed by the input filter.
 * Pulse width = T_SP * tpclk* (TPM+1)
 */
#define I2C_SETUP_T_SP_MASK (0xE00000UL)
#define I2C_SETUP_T_SP_SHIFT (21U)
#define I2C_SETUP_T_SP_SET(x) (((uint32_t)(x) << I2C_SETUP_T_SP_SHIFT) & I2C_SETUP_T_SP_MASK)
#define I2C_SETUP_T_SP_GET(x) (((uint32_t)(x) & I2C_SETUP_T_SP_MASK) >> I2C_SETUP_T_SP_SHIFT)

/*
 * T_HDDAT (RW)
 *
 * T_HDDAT defines the data hold time after SCL goes LOW
 * Hold time = (2 * tpclk) + (2 + T_SP + T_HDDAT) * tpclk* (TPM+1)
 */
#define I2C_SETUP_T_HDDAT_MASK (0x1F0000UL)
#define I2C_SETUP_T_HDDAT_SHIFT (16U)
#define I2C_SETUP_T_HDDAT_SET(x) (((uint32_t)(x) << I2C_SETUP_T_HDDAT_SHIFT) & I2C_SETUP_T_HDDAT_MASK)
#define I2C_SETUP_T_HDDAT_GET(x) (((uint32_t)(x) & I2C_SETUP_T_HDDAT_MASK) >> I2C_SETUP_T_HDDAT_SHIFT)

/*
 * T_SCLRADIO (RW)
 *
 * The LOW period of the generated SCL clock is defined by the combination of T_SCLRatio and T_SCLHi values. When T_SCLRatio = 0, the LOW period is equal to HIGH period. When T_SCLRatio = 1, the LOW period is roughly two times of HIGH period.
 * SCL LOW period = (2 * tpclk) + (2 + T_SP + T_SCLHi * ratio) * tpclk * (TPM+1)
 * 1: ratio = 2
 * 0: ratio = 1
 * This field is only valid when the controller is in the master mode.
 */
#define I2C_SETUP_T_SCLRADIO_MASK (0x2000U)
#define I2C_SETUP_T_SCLRADIO_SHIFT (13U)
#define I2C_SETUP_T_SCLRADIO_SET(x) (((uint32_t)(x) << I2C_SETUP_T_SCLRADIO_SHIFT) & I2C_SETUP_T_SCLRADIO_MASK)
#define I2C_SETUP_T_SCLRADIO_GET(x) (((uint32_t)(x) & I2C_SETUP_T_SCLRADIO_MASK) >> I2C_SETUP_T_SCLRADIO_SHIFT)

/*
 * T_SCLHI (RW)
 *
 * The HIGH period of generated SCL clock is defined by T_SCLHi.
 * SCL HIGH period = (2 * tpclk) + (2 + T_SP + T_SCLHi) * tpclk* (TPM+1)
 * The T_SCLHi value must be greater than T_SP and T_HDDAT values.
 * This field is only valid when the controller is in the master mode.
 */
#define I2C_SETUP_T_SCLHI_MASK (0x1FF0U)
#define I2C_SETUP_T_SCLHI_SHIFT (4U)
#define I2C_SETUP_T_SCLHI_SET(x) (((uint32_t)(x) << I2C_SETUP_T_SCLHI_SHIFT) & I2C_SETUP_T_SCLHI_MASK)
#define I2C_SETUP_T_SCLHI_GET(x) (((uint32_t)(x) & I2C_SETUP_T_SCLHI_MASK) >> I2C_SETUP_T_SCLHI_SHIFT)

/*
 * DMAEN (RW)
 *
 * Enable the direct memory access mode data transfer.
 * 1: Enable
 * 0: Disable
 */
#define I2C_SETUP_DMAEN_MASK (0x8U)
#define I2C_SETUP_DMAEN_SHIFT (3U)
#define I2C_SETUP_DMAEN_SET(x) (((uint32_t)(x) << I2C_SETUP_DMAEN_SHIFT) & I2C_SETUP_DMAEN_MASK)
#define I2C_SETUP_DMAEN_GET(x) (((uint32_t)(x) & I2C_SETUP_DMAEN_MASK) >> I2C_SETUP_DMAEN_SHIFT)

/*
 * MASTER (RW)
 *
 * Configure this device as a master or a slave.
 * 1: Master mode
 * 0: Slave mode
 */
#define I2C_SETUP_MASTER_MASK (0x4U)
#define I2C_SETUP_MASTER_SHIFT (2U)
#define I2C_SETUP_MASTER_SET(x) (((uint32_t)(x) << I2C_SETUP_MASTER_SHIFT) & I2C_SETUP_MASTER_MASK)
#define I2C_SETUP_MASTER_GET(x) (((uint32_t)(x) & I2C_SETUP_MASTER_MASK) >> I2C_SETUP_MASTER_SHIFT)

/*
 * ADDRESSING (RW)
 *
 * I2C addressing mode:
 * 1: 10-bit addressing mode
 * 0: 7-bit addressing mode
 */
#define I2C_SETUP_ADDRESSING_MASK (0x2U)
#define I2C_SETUP_ADDRESSING_SHIFT (1U)
#define I2C_SETUP_ADDRESSING_SET(x) (((uint32_t)(x) << I2C_SETUP_ADDRESSING_SHIFT) & I2C_SETUP_ADDRESSING_MASK)
#define I2C_SETUP_ADDRESSING_GET(x) (((uint32_t)(x) & I2C_SETUP_ADDRESSING_MASK) >> I2C_SETUP_ADDRESSING_SHIFT)

/*
 * IICEN (RW)
 *
 * Enable the I2C controller.
 * 1: Enable
 * 0: Disable
 */
#define I2C_SETUP_IICEN_MASK (0x1U)
#define I2C_SETUP_IICEN_SHIFT (0U)
#define I2C_SETUP_IICEN_SET(x) (((uint32_t)(x) << I2C_SETUP_IICEN_SHIFT) & I2C_SETUP_IICEN_MASK)
#define I2C_SETUP_IICEN_GET(x) (((uint32_t)(x) & I2C_SETUP_IICEN_MASK) >> I2C_SETUP_IICEN_SHIFT)

/* Bitfield definition for register: TPM */
/*
 * TPM (RW)
 *
 * A multiplication value for I2C timing parameters. All the timing parameters in the Setup Register are multiplied by (TPM+1).
 */
#define I2C_TPM_TPM_MASK (0x1FU)
#define I2C_TPM_TPM_SHIFT (0U)
#define I2C_TPM_TPM_SET(x) (((uint32_t)(x) << I2C_TPM_TPM_SHIFT) & I2C_TPM_TPM_MASK)
#define I2C_TPM_TPM_GET(x) (((uint32_t)(x) & I2C_TPM_TPM_MASK) >> I2C_TPM_TPM_SHIFT)




#endif /* HPM_I2C_H */
