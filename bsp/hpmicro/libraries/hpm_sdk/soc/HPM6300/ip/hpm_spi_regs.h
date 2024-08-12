/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_SPI_H
#define HPM_SPI_H

typedef struct {
    __R  uint8_t  RESERVED0[16];               /* 0x0 - 0xF: Reserved */
    __RW uint32_t TRANSFMT;                    /* 0x10: Transfer Format Register */
    __R  uint8_t  RESERVED1[12];               /* 0x14 - 0x1F: Reserved */
    __RW uint32_t TRANSCTRL;                   /* 0x20: Transfer Control Register */
    __RW uint32_t CMD;                         /* 0x24: Command Register */
    __RW uint32_t ADDR;                        /* 0x28: Address Register */
    __RW uint32_t DATA;                        /* 0x2C: Data Register */
    __RW uint32_t CTRL;                        /* 0x30: Control Register */
    __R  uint32_t STATUS;                      /* 0x34: Status Register */
    __RW uint32_t INTREN;                      /* 0x38: Interrupt Enable Register */
    __W  uint32_t INTRST;                      /* 0x3C: Interrupt Status Register */
    __RW uint32_t TIMING;                      /* 0x40: Interface Timing Register */
    __R  uint8_t  RESERVED2[28];               /* 0x44 - 0x5F: Reserved */
    __RW uint32_t SLVST;                       /* 0x60: Slave Status Register */
    __R  uint32_t SLVDATACNT;                  /* 0x64: Slave Data Count Register */
    __R  uint8_t  RESERVED3[20];               /* 0x68 - 0x7B: Reserved */
    __R  uint32_t CONFIG;                      /* 0x7C: Configuration Register */
} SPI_Type;


/* Bitfield definition for register: TRANSFMT */
/*
 * ADDRLEN (RW)
 *
 * Address length in bytes
 * 0x0: 1 byte
 * 0x1: 2 bytes
 * 0x2: 3 bytes
 * 0x3: 4 bytes
 */
#define SPI_TRANSFMT_ADDRLEN_MASK (0x30000UL)
#define SPI_TRANSFMT_ADDRLEN_SHIFT (16U)
#define SPI_TRANSFMT_ADDRLEN_SET(x) (((uint32_t)(x) << SPI_TRANSFMT_ADDRLEN_SHIFT) & SPI_TRANSFMT_ADDRLEN_MASK)
#define SPI_TRANSFMT_ADDRLEN_GET(x) (((uint32_t)(x) & SPI_TRANSFMT_ADDRLEN_MASK) >> SPI_TRANSFMT_ADDRLEN_SHIFT)

/*
 * DATALEN (RW)
 *
 * The length of each data unit in bits
 * The actual bit number of a data unit is (DataLen + 1)
 */
#define SPI_TRANSFMT_DATALEN_MASK (0x1F00U)
#define SPI_TRANSFMT_DATALEN_SHIFT (8U)
#define SPI_TRANSFMT_DATALEN_SET(x) (((uint32_t)(x) << SPI_TRANSFMT_DATALEN_SHIFT) & SPI_TRANSFMT_DATALEN_MASK)
#define SPI_TRANSFMT_DATALEN_GET(x) (((uint32_t)(x) & SPI_TRANSFMT_DATALEN_MASK) >> SPI_TRANSFMT_DATALEN_SHIFT)

/*
 * DATAMERGE (RW)
 *
 * Enable Data Merge mode, which does automatic data split on write and data coalescing on read.
 * This bit only takes effect when DataLen = 0x7. Under Data Merge mode, each write to the Data Register will transmit all fourbytes of the write data; each read from the Data Register will retrieve four bytes of received data as a single word data.
 * When Data Merge mode is disabled, only the least (DataLen+1) significient bits of the Data Register are valid for read/write operations; no automatic data split/coalescing will be performed.
 */
#define SPI_TRANSFMT_DATAMERGE_MASK (0x80U)
#define SPI_TRANSFMT_DATAMERGE_SHIFT (7U)
#define SPI_TRANSFMT_DATAMERGE_SET(x) (((uint32_t)(x) << SPI_TRANSFMT_DATAMERGE_SHIFT) & SPI_TRANSFMT_DATAMERGE_MASK)
#define SPI_TRANSFMT_DATAMERGE_GET(x) (((uint32_t)(x) & SPI_TRANSFMT_DATAMERGE_MASK) >> SPI_TRANSFMT_DATAMERGE_SHIFT)

/*
 * MOSIBIDIR (RW)
 *
 * Bi-directional MOSI in regular (single) mode
 * 0x0: MOSI is uni-directional signal in regular mode.
 * 0x1: MOSI is bi-directional signal in regular mode. This bi-directional signal replaces the two
 */
#define SPI_TRANSFMT_MOSIBIDIR_MASK (0x10U)
#define SPI_TRANSFMT_MOSIBIDIR_SHIFT (4U)
#define SPI_TRANSFMT_MOSIBIDIR_SET(x) (((uint32_t)(x) << SPI_TRANSFMT_MOSIBIDIR_SHIFT) & SPI_TRANSFMT_MOSIBIDIR_MASK)
#define SPI_TRANSFMT_MOSIBIDIR_GET(x) (((uint32_t)(x) & SPI_TRANSFMT_MOSIBIDIR_MASK) >> SPI_TRANSFMT_MOSIBIDIR_SHIFT)

/*
 * LSB (RW)
 *
 * Transfer data with the least significant bit first
 * 0x0: Most significant bit first
 * 0x1: Least significant bit first
 */
#define SPI_TRANSFMT_LSB_MASK (0x8U)
#define SPI_TRANSFMT_LSB_SHIFT (3U)
#define SPI_TRANSFMT_LSB_SET(x) (((uint32_t)(x) << SPI_TRANSFMT_LSB_SHIFT) & SPI_TRANSFMT_LSB_MASK)
#define SPI_TRANSFMT_LSB_GET(x) (((uint32_t)(x) & SPI_TRANSFMT_LSB_MASK) >> SPI_TRANSFMT_LSB_SHIFT)

/*
 * SLVMODE (RW)
 *
 * SPI Master/Slave mode selection
 * 0x0: Master mode
 * 0x1: Slave mode
 */
#define SPI_TRANSFMT_SLVMODE_MASK (0x4U)
#define SPI_TRANSFMT_SLVMODE_SHIFT (2U)
#define SPI_TRANSFMT_SLVMODE_SET(x) (((uint32_t)(x) << SPI_TRANSFMT_SLVMODE_SHIFT) & SPI_TRANSFMT_SLVMODE_MASK)
#define SPI_TRANSFMT_SLVMODE_GET(x) (((uint32_t)(x) & SPI_TRANSFMT_SLVMODE_MASK) >> SPI_TRANSFMT_SLVMODE_SHIFT)

/*
 * CPOL (RW)
 *
 * SPI Clock Polarity
 * 0x0: SCLK is LOW in the idle states
 * 0x1: SCLK is HIGH in the idle states
 */
#define SPI_TRANSFMT_CPOL_MASK (0x2U)
#define SPI_TRANSFMT_CPOL_SHIFT (1U)
#define SPI_TRANSFMT_CPOL_SET(x) (((uint32_t)(x) << SPI_TRANSFMT_CPOL_SHIFT) & SPI_TRANSFMT_CPOL_MASK)
#define SPI_TRANSFMT_CPOL_GET(x) (((uint32_t)(x) & SPI_TRANSFMT_CPOL_MASK) >> SPI_TRANSFMT_CPOL_SHIFT)

/*
 * CPHA (RW)
 *
 * SPI Clock Phase
 * 0x0: Sampling data at odd SCLK edges
 * 0x1: Sampling data at even SCLK edges
 */
#define SPI_TRANSFMT_CPHA_MASK (0x1U)
#define SPI_TRANSFMT_CPHA_SHIFT (0U)
#define SPI_TRANSFMT_CPHA_SET(x) (((uint32_t)(x) << SPI_TRANSFMT_CPHA_SHIFT) & SPI_TRANSFMT_CPHA_MASK)
#define SPI_TRANSFMT_CPHA_GET(x) (((uint32_t)(x) & SPI_TRANSFMT_CPHA_MASK) >> SPI_TRANSFMT_CPHA_SHIFT)

/* Bitfield definition for register: TRANSCTRL */
/*
 * SLVDATAONLY (RW)
 *
 * Data-only mode (slave mode only)
 * 0x0: Disable the data-only mode
 * 0x1: Enable the data-only mode
 * Note: This mode only works in the uni-directional regular (single) mode so MOSIBiDir, DualQuad and TransMode should be set to 0.
 */
#define SPI_TRANSCTRL_SLVDATAONLY_MASK (0x80000000UL)
#define SPI_TRANSCTRL_SLVDATAONLY_SHIFT (31U)
#define SPI_TRANSCTRL_SLVDATAONLY_SET(x) (((uint32_t)(x) << SPI_TRANSCTRL_SLVDATAONLY_SHIFT) & SPI_TRANSCTRL_SLVDATAONLY_MASK)
#define SPI_TRANSCTRL_SLVDATAONLY_GET(x) (((uint32_t)(x) & SPI_TRANSCTRL_SLVDATAONLY_MASK) >> SPI_TRANSCTRL_SLVDATAONLY_SHIFT)

/*
 * CMDEN (RW)
 *
 * SPI command phase enable (Master mode only)
 * 0x0: Disable the command phase
 * 0x1: Enable the command phase
 */
#define SPI_TRANSCTRL_CMDEN_MASK (0x40000000UL)
#define SPI_TRANSCTRL_CMDEN_SHIFT (30U)
#define SPI_TRANSCTRL_CMDEN_SET(x) (((uint32_t)(x) << SPI_TRANSCTRL_CMDEN_SHIFT) & SPI_TRANSCTRL_CMDEN_MASK)
#define SPI_TRANSCTRL_CMDEN_GET(x) (((uint32_t)(x) & SPI_TRANSCTRL_CMDEN_MASK) >> SPI_TRANSCTRL_CMDEN_SHIFT)

/*
 * ADDREN (RW)
 *
 * SPI address phase enable (Master mode only)
 * 0x0: Disable the address phase
 * 0x1: Enable the address phase
 */
#define SPI_TRANSCTRL_ADDREN_MASK (0x20000000UL)
#define SPI_TRANSCTRL_ADDREN_SHIFT (29U)
#define SPI_TRANSCTRL_ADDREN_SET(x) (((uint32_t)(x) << SPI_TRANSCTRL_ADDREN_SHIFT) & SPI_TRANSCTRL_ADDREN_MASK)
#define SPI_TRANSCTRL_ADDREN_GET(x) (((uint32_t)(x) & SPI_TRANSCTRL_ADDREN_MASK) >> SPI_TRANSCTRL_ADDREN_SHIFT)

/*
 * ADDRFMT (RW)
 *
 * SPI address phase format (Master mode only)
 * 0x0: Address phase is the regular (single) mode
 * 0x1: The format of the address phase is the same as the data phase (DualQuad).
 */
#define SPI_TRANSCTRL_ADDRFMT_MASK (0x10000000UL)
#define SPI_TRANSCTRL_ADDRFMT_SHIFT (28U)
#define SPI_TRANSCTRL_ADDRFMT_SET(x) (((uint32_t)(x) << SPI_TRANSCTRL_ADDRFMT_SHIFT) & SPI_TRANSCTRL_ADDRFMT_MASK)
#define SPI_TRANSCTRL_ADDRFMT_GET(x) (((uint32_t)(x) & SPI_TRANSCTRL_ADDRFMT_MASK) >> SPI_TRANSCTRL_ADDRFMT_SHIFT)

/*
 * TRANSMODE (RW)
 *
 * Transfer mode
 * The transfer sequence could be
 * 0x0: Write and read at the same time
 * 0x1: Write only
 * 0x2: Read only
 * 0x3: Write, Read
 * 0x4: Read, Write
 * 0x5: Write, Dummy, Read
 * 0x6: Read, Dummy, Write
 * 0x7: None Data (must enable CmdEn or AddrEn in master mode)
 * 0x8: Dummy, Write
 * 0x9: Dummy, Read
 * 0xa~0xf: Reserved
 */
#define SPI_TRANSCTRL_TRANSMODE_MASK (0xF000000UL)
#define SPI_TRANSCTRL_TRANSMODE_SHIFT (24U)
#define SPI_TRANSCTRL_TRANSMODE_SET(x) (((uint32_t)(x) << SPI_TRANSCTRL_TRANSMODE_SHIFT) & SPI_TRANSCTRL_TRANSMODE_MASK)
#define SPI_TRANSCTRL_TRANSMODE_GET(x) (((uint32_t)(x) & SPI_TRANSCTRL_TRANSMODE_MASK) >> SPI_TRANSCTRL_TRANSMODE_SHIFT)

/*
 * DUALQUAD (RW)
 *
 * SPI data phase format
 * 0x0: Regular (Single) mode
 * 0x1: Dual I/O mode
 * 0x2: Quad I/O mode
 * 0x3: Reserved
 */
#define SPI_TRANSCTRL_DUALQUAD_MASK (0xC00000UL)
#define SPI_TRANSCTRL_DUALQUAD_SHIFT (22U)
#define SPI_TRANSCTRL_DUALQUAD_SET(x) (((uint32_t)(x) << SPI_TRANSCTRL_DUALQUAD_SHIFT) & SPI_TRANSCTRL_DUALQUAD_MASK)
#define SPI_TRANSCTRL_DUALQUAD_GET(x) (((uint32_t)(x) & SPI_TRANSCTRL_DUALQUAD_MASK) >> SPI_TRANSCTRL_DUALQUAD_SHIFT)

/*
 * TOKENEN (RW)
 *
 * Token transfer enable (Master mode only)
 * Append a one-byte special token following the address phase for SPI read transfers. The value of the special token should be selected in TokenValue.
 * 0x0: Disable the one-byte special token
 * 0x1: Enable the one-byte special token
 */
#define SPI_TRANSCTRL_TOKENEN_MASK (0x200000UL)
#define SPI_TRANSCTRL_TOKENEN_SHIFT (21U)
#define SPI_TRANSCTRL_TOKENEN_SET(x) (((uint32_t)(x) << SPI_TRANSCTRL_TOKENEN_SHIFT) & SPI_TRANSCTRL_TOKENEN_MASK)
#define SPI_TRANSCTRL_TOKENEN_GET(x) (((uint32_t)(x) & SPI_TRANSCTRL_TOKENEN_MASK) >> SPI_TRANSCTRL_TOKENEN_SHIFT)

/*
 * WRTRANCNT (RW)
 *
 * Transfer count for write data
 * WrTranCnt indicates the number of units of data to be transmitted to the SPI bus from the Data Register. The actual transfer count is (WrTranCnt+1).
 * WrTranCnt only takes effect when TransMode is 0, 1, 3, 4, 5, 6 or 8.
 * The size (bit-width) of a data unit is defined by the DataLen field of the Transfer Format Register.
 * For TransMode 0, WrTranCnt must be equal to RdTranCnt.
 */
#define SPI_TRANSCTRL_WRTRANCNT_MASK (0x1FF000UL)
#define SPI_TRANSCTRL_WRTRANCNT_SHIFT (12U)
#define SPI_TRANSCTRL_WRTRANCNT_SET(x) (((uint32_t)(x) << SPI_TRANSCTRL_WRTRANCNT_SHIFT) & SPI_TRANSCTRL_WRTRANCNT_MASK)
#define SPI_TRANSCTRL_WRTRANCNT_GET(x) (((uint32_t)(x) & SPI_TRANSCTRL_WRTRANCNT_MASK) >> SPI_TRANSCTRL_WRTRANCNT_SHIFT)

/*
 * TOKENVALUE (RW)
 *
 * Token value (Master mode only)
 * The value of the one-byte special token following the address phase for SPI read transfers.
 * 0x0: token value = 0x00
 * 0x1: token value = 0x69
 */
#define SPI_TRANSCTRL_TOKENVALUE_MASK (0x800U)
#define SPI_TRANSCTRL_TOKENVALUE_SHIFT (11U)
#define SPI_TRANSCTRL_TOKENVALUE_SET(x) (((uint32_t)(x) << SPI_TRANSCTRL_TOKENVALUE_SHIFT) & SPI_TRANSCTRL_TOKENVALUE_MASK)
#define SPI_TRANSCTRL_TOKENVALUE_GET(x) (((uint32_t)(x) & SPI_TRANSCTRL_TOKENVALUE_MASK) >> SPI_TRANSCTRL_TOKENVALUE_SHIFT)

/*
 * DUMMYCNT (RW)
 *
 * Dummy data count. The actual dummy count is (DummyCnt +1).
 * The number of dummy cycles on the SPI interface will be (DummyCnt+1)* ((DataLen+1)/SPI IO width)
 * The Data pins are put into the high impedance during the dummy data phase.
 * DummyCnt is only used for TransMode 5, 6, 8 and 9, which has dummy data phases.
 */
#define SPI_TRANSCTRL_DUMMYCNT_MASK (0x600U)
#define SPI_TRANSCTRL_DUMMYCNT_SHIFT (9U)
#define SPI_TRANSCTRL_DUMMYCNT_SET(x) (((uint32_t)(x) << SPI_TRANSCTRL_DUMMYCNT_SHIFT) & SPI_TRANSCTRL_DUMMYCNT_MASK)
#define SPI_TRANSCTRL_DUMMYCNT_GET(x) (((uint32_t)(x) & SPI_TRANSCTRL_DUMMYCNT_MASK) >> SPI_TRANSCTRL_DUMMYCNT_SHIFT)

/*
 * RDTRANCNT (RW)
 *
 * Transfer count for read data
 * RdTranCnt indicates the number of units of data to be received from SPI bus and stored to the Data Register. The actual received count is (RdTranCnt+1).
 * RdTransCnt only takes effect when TransMode is 0, 2, 3, 4, 5, 6 or 9.
 * The size (bit-width) of a data unit is defined by the DataLen field of the Transfer Format Register.
 * For TransMode 0, WrTranCnt must equal RdTranCnt.
 */
#define SPI_TRANSCTRL_RDTRANCNT_MASK (0x1FFU)
#define SPI_TRANSCTRL_RDTRANCNT_SHIFT (0U)
#define SPI_TRANSCTRL_RDTRANCNT_SET(x) (((uint32_t)(x) << SPI_TRANSCTRL_RDTRANCNT_SHIFT) & SPI_TRANSCTRL_RDTRANCNT_MASK)
#define SPI_TRANSCTRL_RDTRANCNT_GET(x) (((uint32_t)(x) & SPI_TRANSCTRL_RDTRANCNT_MASK) >> SPI_TRANSCTRL_RDTRANCNT_SHIFT)

/* Bitfield definition for register: CMD */
/*
 * CMD (RW)
 *
 * SPI Command
 */
#define SPI_CMD_CMD_MASK (0xFFU)
#define SPI_CMD_CMD_SHIFT (0U)
#define SPI_CMD_CMD_SET(x) (((uint32_t)(x) << SPI_CMD_CMD_SHIFT) & SPI_CMD_CMD_MASK)
#define SPI_CMD_CMD_GET(x) (((uint32_t)(x) & SPI_CMD_CMD_MASK) >> SPI_CMD_CMD_SHIFT)

/* Bitfield definition for register: ADDR */
/*
 * ADDR (RW)
 *
 * SPI Address
 * (Master mode only)
 */
#define SPI_ADDR_ADDR_MASK (0xFFFFFFFFUL)
#define SPI_ADDR_ADDR_SHIFT (0U)
#define SPI_ADDR_ADDR_SET(x) (((uint32_t)(x) << SPI_ADDR_ADDR_SHIFT) & SPI_ADDR_ADDR_MASK)
#define SPI_ADDR_ADDR_GET(x) (((uint32_t)(x) & SPI_ADDR_ADDR_MASK) >> SPI_ADDR_ADDR_SHIFT)

/* Bitfield definition for register: DATA */
/*
 * DATA (RW)
 *
 * Data to transmit or the received data
 * For writes, data is enqueued to the TX FIFO. The least significant byte is always transmitted first. If the TX FIFO is full and the SPIActive bit of the status register is 1, the ready signal hready/pready will be deasserted to insert wait states to the transfer.
 * For reads, data is read and dequeued from the RX FIFO. The least significant byte is the first received byte. If the RX FIFO is empty and the SPIActive bit of the status register is 1, the ready signal hready/pready will be deasserted to insert wait states to the transfer.
 * The FIFOs decouple the speed of the SPI transfers and the software鈥檚 generation/consumption of data. When the TX FIFO is empty, SPI transfers will hold until more data is written to the TX FIFO; when the RX FIFO is full, SPI transfers will hold until there is more room in the RX FIFO.
 * If more data is written to the TX FIFO than the write transfer count (WrTranCnt), the remaining data will stay in the TX FIFO for the next transfer or until the TX FIFO is reset.
 */
#define SPI_DATA_DATA_MASK (0xFFFFFFFFUL)
#define SPI_DATA_DATA_SHIFT (0U)
#define SPI_DATA_DATA_SET(x) (((uint32_t)(x) << SPI_DATA_DATA_SHIFT) & SPI_DATA_DATA_MASK)
#define SPI_DATA_DATA_GET(x) (((uint32_t)(x) & SPI_DATA_DATA_MASK) >> SPI_DATA_DATA_SHIFT)

/* Bitfield definition for register: CTRL */
/*
 * TXTHRES (RW)
 *
 * Transmit (TX) FIFO Threshold
 * The TXFIFOInt interrupt or DMA request would be issued to replenish the TX FIFO when the TX data count is less than or equal to the TX FIFO threshold.
 */
#define SPI_CTRL_TXTHRES_MASK (0xFF0000UL)
#define SPI_CTRL_TXTHRES_SHIFT (16U)
#define SPI_CTRL_TXTHRES_SET(x) (((uint32_t)(x) << SPI_CTRL_TXTHRES_SHIFT) & SPI_CTRL_TXTHRES_MASK)
#define SPI_CTRL_TXTHRES_GET(x) (((uint32_t)(x) & SPI_CTRL_TXTHRES_MASK) >> SPI_CTRL_TXTHRES_SHIFT)

/*
 * RXTHRES (RW)
 *
 * Receive (RX) FIFO Threshold
 * The RXFIFOInt interrupt or DMA request would be issued for consuming the RX FIFO when the RX data count is more than or equal to the RX FIFO threshold.
 */
#define SPI_CTRL_RXTHRES_MASK (0xFF00U)
#define SPI_CTRL_RXTHRES_SHIFT (8U)
#define SPI_CTRL_RXTHRES_SET(x) (((uint32_t)(x) << SPI_CTRL_RXTHRES_SHIFT) & SPI_CTRL_RXTHRES_MASK)
#define SPI_CTRL_RXTHRES_GET(x) (((uint32_t)(x) & SPI_CTRL_RXTHRES_MASK) >> SPI_CTRL_RXTHRES_SHIFT)

/*
 * TXDMAEN (RW)
 *
 * TX DMA enable
 */
#define SPI_CTRL_TXDMAEN_MASK (0x10U)
#define SPI_CTRL_TXDMAEN_SHIFT (4U)
#define SPI_CTRL_TXDMAEN_SET(x) (((uint32_t)(x) << SPI_CTRL_TXDMAEN_SHIFT) & SPI_CTRL_TXDMAEN_MASK)
#define SPI_CTRL_TXDMAEN_GET(x) (((uint32_t)(x) & SPI_CTRL_TXDMAEN_MASK) >> SPI_CTRL_TXDMAEN_SHIFT)

/*
 * RXDMAEN (RW)
 *
 * RX DMA enable
 */
#define SPI_CTRL_RXDMAEN_MASK (0x8U)
#define SPI_CTRL_RXDMAEN_SHIFT (3U)
#define SPI_CTRL_RXDMAEN_SET(x) (((uint32_t)(x) << SPI_CTRL_RXDMAEN_SHIFT) & SPI_CTRL_RXDMAEN_MASK)
#define SPI_CTRL_RXDMAEN_GET(x) (((uint32_t)(x) & SPI_CTRL_RXDMAEN_MASK) >> SPI_CTRL_RXDMAEN_SHIFT)

/*
 * TXFIFORST (RW)
 *
 * Transmit FIFO reset
 * Write 1 to reset. It is automatically cleared to 0 after the reset operation completes.
 */
#define SPI_CTRL_TXFIFORST_MASK (0x4U)
#define SPI_CTRL_TXFIFORST_SHIFT (2U)
#define SPI_CTRL_TXFIFORST_SET(x) (((uint32_t)(x) << SPI_CTRL_TXFIFORST_SHIFT) & SPI_CTRL_TXFIFORST_MASK)
#define SPI_CTRL_TXFIFORST_GET(x) (((uint32_t)(x) & SPI_CTRL_TXFIFORST_MASK) >> SPI_CTRL_TXFIFORST_SHIFT)

/*
 * RXFIFORST (RW)
 *
 * Receive FIFO reset
 * Write 1 to reset. It is automatically cleared to 0 after the reset operation completes.
 */
#define SPI_CTRL_RXFIFORST_MASK (0x2U)
#define SPI_CTRL_RXFIFORST_SHIFT (1U)
#define SPI_CTRL_RXFIFORST_SET(x) (((uint32_t)(x) << SPI_CTRL_RXFIFORST_SHIFT) & SPI_CTRL_RXFIFORST_MASK)
#define SPI_CTRL_RXFIFORST_GET(x) (((uint32_t)(x) & SPI_CTRL_RXFIFORST_MASK) >> SPI_CTRL_RXFIFORST_SHIFT)

/*
 * SPIRST (RW)
 *
 * SPI reset
 * Write 1 to reset. It is automatically cleared to 0 after the reset operation completes.
 */
#define SPI_CTRL_SPIRST_MASK (0x1U)
#define SPI_CTRL_SPIRST_SHIFT (0U)
#define SPI_CTRL_SPIRST_SET(x) (((uint32_t)(x) << SPI_CTRL_SPIRST_SHIFT) & SPI_CTRL_SPIRST_MASK)
#define SPI_CTRL_SPIRST_GET(x) (((uint32_t)(x) & SPI_CTRL_SPIRST_MASK) >> SPI_CTRL_SPIRST_SHIFT)

/* Bitfield definition for register: STATUS */
/*
 * TXNUM_7_6 (RO)
 *
 * Number of valid entries in the Transmit FIFO
 */
#define SPI_STATUS_TXNUM_7_6_MASK (0x30000000UL)
#define SPI_STATUS_TXNUM_7_6_SHIFT (28U)
#define SPI_STATUS_TXNUM_7_6_GET(x) (((uint32_t)(x) & SPI_STATUS_TXNUM_7_6_MASK) >> SPI_STATUS_TXNUM_7_6_SHIFT)

/*
 * RXNUM_7_6 (RO)
 *
 * Number of valid entries in the Receive FIFO
 */
#define SPI_STATUS_RXNUM_7_6_MASK (0x3000000UL)
#define SPI_STATUS_RXNUM_7_6_SHIFT (24U)
#define SPI_STATUS_RXNUM_7_6_GET(x) (((uint32_t)(x) & SPI_STATUS_RXNUM_7_6_MASK) >> SPI_STATUS_RXNUM_7_6_SHIFT)

/*
 * TXFULL (RO)
 *
 * Transmit FIFO Full flag
 */
#define SPI_STATUS_TXFULL_MASK (0x800000UL)
#define SPI_STATUS_TXFULL_SHIFT (23U)
#define SPI_STATUS_TXFULL_GET(x) (((uint32_t)(x) & SPI_STATUS_TXFULL_MASK) >> SPI_STATUS_TXFULL_SHIFT)

/*
 * TXEMPTY (RO)
 *
 * Transmit FIFO Empty flag
 */
#define SPI_STATUS_TXEMPTY_MASK (0x400000UL)
#define SPI_STATUS_TXEMPTY_SHIFT (22U)
#define SPI_STATUS_TXEMPTY_GET(x) (((uint32_t)(x) & SPI_STATUS_TXEMPTY_MASK) >> SPI_STATUS_TXEMPTY_SHIFT)

/*
 * TXNUM_5_0 (RO)
 *
 * Number of valid entries in the Transmit FIFO
 */
#define SPI_STATUS_TXNUM_5_0_MASK (0x3F0000UL)
#define SPI_STATUS_TXNUM_5_0_SHIFT (16U)
#define SPI_STATUS_TXNUM_5_0_GET(x) (((uint32_t)(x) & SPI_STATUS_TXNUM_5_0_MASK) >> SPI_STATUS_TXNUM_5_0_SHIFT)

/*
 * RXFULL (RO)
 *
 * Receive FIFO Full flag
 */
#define SPI_STATUS_RXFULL_MASK (0x8000U)
#define SPI_STATUS_RXFULL_SHIFT (15U)
#define SPI_STATUS_RXFULL_GET(x) (((uint32_t)(x) & SPI_STATUS_RXFULL_MASK) >> SPI_STATUS_RXFULL_SHIFT)

/*
 * RXEMPTY (RO)
 *
 * Receive FIFO Empty flag
 */
#define SPI_STATUS_RXEMPTY_MASK (0x4000U)
#define SPI_STATUS_RXEMPTY_SHIFT (14U)
#define SPI_STATUS_RXEMPTY_GET(x) (((uint32_t)(x) & SPI_STATUS_RXEMPTY_MASK) >> SPI_STATUS_RXEMPTY_SHIFT)

/*
 * RXNUM_5_0 (RO)
 *
 * Number of valid entries in the Receive FIFO
 */
#define SPI_STATUS_RXNUM_5_0_MASK (0x3F00U)
#define SPI_STATUS_RXNUM_5_0_SHIFT (8U)
#define SPI_STATUS_RXNUM_5_0_GET(x) (((uint32_t)(x) & SPI_STATUS_RXNUM_5_0_MASK) >> SPI_STATUS_RXNUM_5_0_SHIFT)

/*
 * SPIACTIVE (RO)
 *
 * SPI register programming is in progress.
 * In master mode, SPIActive becomes 1 after the SPI command register is written and becomes 0 after the transfer is finished.
 * In slave mode, SPIActive becomes 1 after the SPI CS signal is asserted and becomes 0 after the SPI CS signal is deasserted.
 * Note that due to clock synchronization, it may take at most two spi_clock cycles for SPIActive to change when the corresponding condition happens.
 * Note this bit stays 0 when Direct IO Control or the memory-mapped interface is used.
 */
#define SPI_STATUS_SPIACTIVE_MASK (0x1U)
#define SPI_STATUS_SPIACTIVE_SHIFT (0U)
#define SPI_STATUS_SPIACTIVE_GET(x) (((uint32_t)(x) & SPI_STATUS_SPIACTIVE_MASK) >> SPI_STATUS_SPIACTIVE_SHIFT)

/* Bitfield definition for register: INTREN */
/*
 * SLVCMDEN (RW)
 *
 * Enable the Slave Command Interrupt.
 * Control whether interrupts are triggered whenever slave commands are received.
 * (Slave mode only)
 */
#define SPI_INTREN_SLVCMDEN_MASK (0x20U)
#define SPI_INTREN_SLVCMDEN_SHIFT (5U)
#define SPI_INTREN_SLVCMDEN_SET(x) (((uint32_t)(x) << SPI_INTREN_SLVCMDEN_SHIFT) & SPI_INTREN_SLVCMDEN_MASK)
#define SPI_INTREN_SLVCMDEN_GET(x) (((uint32_t)(x) & SPI_INTREN_SLVCMDEN_MASK) >> SPI_INTREN_SLVCMDEN_SHIFT)

/*
 * ENDINTEN (RW)
 *
 * Enable the End of SPI Transfer interrupt.
 * Control whether interrupts are triggered when SPI transfers end.
 * (In slave mode, end of read status transaction doesn鈥檛 trigger this interrupt.)
 */
#define SPI_INTREN_ENDINTEN_MASK (0x10U)
#define SPI_INTREN_ENDINTEN_SHIFT (4U)
#define SPI_INTREN_ENDINTEN_SET(x) (((uint32_t)(x) << SPI_INTREN_ENDINTEN_SHIFT) & SPI_INTREN_ENDINTEN_MASK)
#define SPI_INTREN_ENDINTEN_GET(x) (((uint32_t)(x) & SPI_INTREN_ENDINTEN_MASK) >> SPI_INTREN_ENDINTEN_SHIFT)

/*
 * TXFIFOINTEN (RW)
 *
 * Enable the SPI Transmit FIFO Threshold interrupt.
 * Control whether interrupts are triggered when the valid entries are less than or equal to the TX FIFO threshold.
 */
#define SPI_INTREN_TXFIFOINTEN_MASK (0x8U)
#define SPI_INTREN_TXFIFOINTEN_SHIFT (3U)
#define SPI_INTREN_TXFIFOINTEN_SET(x) (((uint32_t)(x) << SPI_INTREN_TXFIFOINTEN_SHIFT) & SPI_INTREN_TXFIFOINTEN_MASK)
#define SPI_INTREN_TXFIFOINTEN_GET(x) (((uint32_t)(x) & SPI_INTREN_TXFIFOINTEN_MASK) >> SPI_INTREN_TXFIFOINTEN_SHIFT)

/*
 * RXFIFOINTEN (RW)
 *
 * Enable the SPI Receive FIFO Threshold interrupt.
 * Control whether interrupts are triggered when the valid entries are greater than or equal to the RX FIFO threshold.
 */
#define SPI_INTREN_RXFIFOINTEN_MASK (0x4U)
#define SPI_INTREN_RXFIFOINTEN_SHIFT (2U)
#define SPI_INTREN_RXFIFOINTEN_SET(x) (((uint32_t)(x) << SPI_INTREN_RXFIFOINTEN_SHIFT) & SPI_INTREN_RXFIFOINTEN_MASK)
#define SPI_INTREN_RXFIFOINTEN_GET(x) (((uint32_t)(x) & SPI_INTREN_RXFIFOINTEN_MASK) >> SPI_INTREN_RXFIFOINTEN_SHIFT)

/*
 * TXFIFOURINTEN (RW)
 *
 * Enable the SPI Transmit FIFO Underrun interrupt.
 * Control whether interrupts are triggered when the Transmit FIFO run out of data.
 * (Slave mode only)
 */
#define SPI_INTREN_TXFIFOURINTEN_MASK (0x2U)
#define SPI_INTREN_TXFIFOURINTEN_SHIFT (1U)
#define SPI_INTREN_TXFIFOURINTEN_SET(x) (((uint32_t)(x) << SPI_INTREN_TXFIFOURINTEN_SHIFT) & SPI_INTREN_TXFIFOURINTEN_MASK)
#define SPI_INTREN_TXFIFOURINTEN_GET(x) (((uint32_t)(x) & SPI_INTREN_TXFIFOURINTEN_MASK) >> SPI_INTREN_TXFIFOURINTEN_SHIFT)

/*
 * RXFIFOORINTEN (RW)
 *
 * Enable the SPI Receive FIFO Overrun interrupt.
 * Control whether interrupts are triggered when the Receive FIFO overflows.
 * (Slave mode only)
 */
#define SPI_INTREN_RXFIFOORINTEN_MASK (0x1U)
#define SPI_INTREN_RXFIFOORINTEN_SHIFT (0U)
#define SPI_INTREN_RXFIFOORINTEN_SET(x) (((uint32_t)(x) << SPI_INTREN_RXFIFOORINTEN_SHIFT) & SPI_INTREN_RXFIFOORINTEN_MASK)
#define SPI_INTREN_RXFIFOORINTEN_GET(x) (((uint32_t)(x) & SPI_INTREN_RXFIFOORINTEN_MASK) >> SPI_INTREN_RXFIFOORINTEN_SHIFT)

/* Bitfield definition for register: INTRST */
/*
 * SLVCMDINT (W1C)
 *
 * Slave Command Interrupt.
 * This bit is set when Slave Command interrupts occur.
 * (Slave mode only)
 */
#define SPI_INTRST_SLVCMDINT_MASK (0x20U)
#define SPI_INTRST_SLVCMDINT_SHIFT (5U)
#define SPI_INTRST_SLVCMDINT_SET(x) (((uint32_t)(x) << SPI_INTRST_SLVCMDINT_SHIFT) & SPI_INTRST_SLVCMDINT_MASK)
#define SPI_INTRST_SLVCMDINT_GET(x) (((uint32_t)(x) & SPI_INTRST_SLVCMDINT_MASK) >> SPI_INTRST_SLVCMDINT_SHIFT)

/*
 * ENDINT (W1C)
 *
 * End of SPI Transfer interrupt.
 * This bit is set when End of SPI Transfer interrupts occur.
 */
#define SPI_INTRST_ENDINT_MASK (0x10U)
#define SPI_INTRST_ENDINT_SHIFT (4U)
#define SPI_INTRST_ENDINT_SET(x) (((uint32_t)(x) << SPI_INTRST_ENDINT_SHIFT) & SPI_INTRST_ENDINT_MASK)
#define SPI_INTRST_ENDINT_GET(x) (((uint32_t)(x) & SPI_INTRST_ENDINT_MASK) >> SPI_INTRST_ENDINT_SHIFT)

/*
 * TXFIFOINT (W1C)
 *
 * TX FIFO Threshold interrupt.
 * This bit is set when TX FIFO Threshold interrupts occur.
 */
#define SPI_INTRST_TXFIFOINT_MASK (0x8U)
#define SPI_INTRST_TXFIFOINT_SHIFT (3U)
#define SPI_INTRST_TXFIFOINT_SET(x) (((uint32_t)(x) << SPI_INTRST_TXFIFOINT_SHIFT) & SPI_INTRST_TXFIFOINT_MASK)
#define SPI_INTRST_TXFIFOINT_GET(x) (((uint32_t)(x) & SPI_INTRST_TXFIFOINT_MASK) >> SPI_INTRST_TXFIFOINT_SHIFT)

/*
 * RXFIFOINT (W1C)
 *
 * RX FIFO Threshold interrupt.
 * This bit is set when RX FIFO Threshold interrupts occur.
 */
#define SPI_INTRST_RXFIFOINT_MASK (0x4U)
#define SPI_INTRST_RXFIFOINT_SHIFT (2U)
#define SPI_INTRST_RXFIFOINT_SET(x) (((uint32_t)(x) << SPI_INTRST_RXFIFOINT_SHIFT) & SPI_INTRST_RXFIFOINT_MASK)
#define SPI_INTRST_RXFIFOINT_GET(x) (((uint32_t)(x) & SPI_INTRST_RXFIFOINT_MASK) >> SPI_INTRST_RXFIFOINT_SHIFT)

/*
 * TXFIFOURINT (W1C)
 *
 * TX FIFO Underrun interrupt.
 * This bit is set when TX FIFO Underrun interrupts occur.
 * (Slave mode only)
 */
#define SPI_INTRST_TXFIFOURINT_MASK (0x2U)
#define SPI_INTRST_TXFIFOURINT_SHIFT (1U)
#define SPI_INTRST_TXFIFOURINT_SET(x) (((uint32_t)(x) << SPI_INTRST_TXFIFOURINT_SHIFT) & SPI_INTRST_TXFIFOURINT_MASK)
#define SPI_INTRST_TXFIFOURINT_GET(x) (((uint32_t)(x) & SPI_INTRST_TXFIFOURINT_MASK) >> SPI_INTRST_TXFIFOURINT_SHIFT)

/*
 * RXFIFOORINT (W1C)
 *
 * RX FIFO Overrun interrupt.
 * This bit is set when RX FIFO Overrun interrupts occur.
 * (Slave mode only)
 */
#define SPI_INTRST_RXFIFOORINT_MASK (0x1U)
#define SPI_INTRST_RXFIFOORINT_SHIFT (0U)
#define SPI_INTRST_RXFIFOORINT_SET(x) (((uint32_t)(x) << SPI_INTRST_RXFIFOORINT_SHIFT) & SPI_INTRST_RXFIFOORINT_MASK)
#define SPI_INTRST_RXFIFOORINT_GET(x) (((uint32_t)(x) & SPI_INTRST_RXFIFOORINT_MASK) >> SPI_INTRST_RXFIFOORINT_SHIFT)

/* Bitfield definition for register: TIMING */
/*
 * CS2SCLK (RW)
 *
 * The minimum time between the edges of SPI CS and the edges of SCLK.
 * SCLK_period * (CS2SCLK + 1) / 2
 */
#define SPI_TIMING_CS2SCLK_MASK (0x3000U)
#define SPI_TIMING_CS2SCLK_SHIFT (12U)
#define SPI_TIMING_CS2SCLK_SET(x) (((uint32_t)(x) << SPI_TIMING_CS2SCLK_SHIFT) & SPI_TIMING_CS2SCLK_MASK)
#define SPI_TIMING_CS2SCLK_GET(x) (((uint32_t)(x) & SPI_TIMING_CS2SCLK_MASK) >> SPI_TIMING_CS2SCLK_SHIFT)

/*
 * CSHT (RW)
 *
 * The minimum time that SPI CS should stay HIGH.
 * SCLK_period * (CSHT + 1) / 2
 */
#define SPI_TIMING_CSHT_MASK (0xF00U)
#define SPI_TIMING_CSHT_SHIFT (8U)
#define SPI_TIMING_CSHT_SET(x) (((uint32_t)(x) << SPI_TIMING_CSHT_SHIFT) & SPI_TIMING_CSHT_MASK)
#define SPI_TIMING_CSHT_GET(x) (((uint32_t)(x) & SPI_TIMING_CSHT_MASK) >> SPI_TIMING_CSHT_SHIFT)

/*
 * SCLK_DIV (RW)
 *
 * The clock frequency ratio between the clock source and SPI interface SCLK.
 * SCLK_period = ((SCLK_DIV + 1) * 2) * (Period of the SPI clock source)
 * The SCLK_DIV value 0xff is a special value which indicates that the SCLK frequency should be the same as the spi_clock frequency.
 */
#define SPI_TIMING_SCLK_DIV_MASK (0xFFU)
#define SPI_TIMING_SCLK_DIV_SHIFT (0U)
#define SPI_TIMING_SCLK_DIV_SET(x) (((uint32_t)(x) << SPI_TIMING_SCLK_DIV_SHIFT) & SPI_TIMING_SCLK_DIV_MASK)
#define SPI_TIMING_SCLK_DIV_GET(x) (((uint32_t)(x) & SPI_TIMING_SCLK_DIV_MASK) >> SPI_TIMING_SCLK_DIV_SHIFT)

/* Bitfield definition for register: SLVST */
/*
 * UNDERRUN (W1C)
 *
 * Data underrun occurs in the last transaction
 */
#define SPI_SLVST_UNDERRUN_MASK (0x40000UL)
#define SPI_SLVST_UNDERRUN_SHIFT (18U)
#define SPI_SLVST_UNDERRUN_SET(x) (((uint32_t)(x) << SPI_SLVST_UNDERRUN_SHIFT) & SPI_SLVST_UNDERRUN_MASK)
#define SPI_SLVST_UNDERRUN_GET(x) (((uint32_t)(x) & SPI_SLVST_UNDERRUN_MASK) >> SPI_SLVST_UNDERRUN_SHIFT)

/*
 * OVERRUN (RW)
 *
 * Data overrun occurs in the last transaction
 */
#define SPI_SLVST_OVERRUN_MASK (0x20000UL)
#define SPI_SLVST_OVERRUN_SHIFT (17U)
#define SPI_SLVST_OVERRUN_SET(x) (((uint32_t)(x) << SPI_SLVST_OVERRUN_SHIFT) & SPI_SLVST_OVERRUN_MASK)
#define SPI_SLVST_OVERRUN_GET(x) (((uint32_t)(x) & SPI_SLVST_OVERRUN_MASK) >> SPI_SLVST_OVERRUN_SHIFT)

/*
 * READY (RW)
 *
 * Set this bit to indicate that the ATCSPI200 is ready for data transaction.
 * When an SPI transaction other than slave status-reading command ends, this bit will be cleared to 0.
 */
#define SPI_SLVST_READY_MASK (0x10000UL)
#define SPI_SLVST_READY_SHIFT (16U)
#define SPI_SLVST_READY_SET(x) (((uint32_t)(x) << SPI_SLVST_READY_SHIFT) & SPI_SLVST_READY_MASK)
#define SPI_SLVST_READY_GET(x) (((uint32_t)(x) & SPI_SLVST_READY_MASK) >> SPI_SLVST_READY_SHIFT)

/*
 * USR_STATUS (RW)
 *
 * User defined status flags
 */
#define SPI_SLVST_USR_STATUS_MASK (0xFFFFU)
#define SPI_SLVST_USR_STATUS_SHIFT (0U)
#define SPI_SLVST_USR_STATUS_SET(x) (((uint32_t)(x) << SPI_SLVST_USR_STATUS_SHIFT) & SPI_SLVST_USR_STATUS_MASK)
#define SPI_SLVST_USR_STATUS_GET(x) (((uint32_t)(x) & SPI_SLVST_USR_STATUS_MASK) >> SPI_SLVST_USR_STATUS_SHIFT)

/* Bitfield definition for register: SLVDATACNT */
/*
 * WCNT (RO)
 *
 * Slave transmitted data count
 */
#define SPI_SLVDATACNT_WCNT_MASK (0x3FF0000UL)
#define SPI_SLVDATACNT_WCNT_SHIFT (16U)
#define SPI_SLVDATACNT_WCNT_GET(x) (((uint32_t)(x) & SPI_SLVDATACNT_WCNT_MASK) >> SPI_SLVDATACNT_WCNT_SHIFT)

/*
 * RCNT (RO)
 *
 * Slave received data count
 */
#define SPI_SLVDATACNT_RCNT_MASK (0x3FFU)
#define SPI_SLVDATACNT_RCNT_SHIFT (0U)
#define SPI_SLVDATACNT_RCNT_GET(x) (((uint32_t)(x) & SPI_SLVDATACNT_RCNT_MASK) >> SPI_SLVDATACNT_RCNT_SHIFT)

/* Bitfield definition for register: CONFIG */
/*
 * SLAVE (RO)
 *
 * Support for SPI Slave mode
 */
#define SPI_CONFIG_SLAVE_MASK (0x4000U)
#define SPI_CONFIG_SLAVE_SHIFT (14U)
#define SPI_CONFIG_SLAVE_GET(x) (((uint32_t)(x) & SPI_CONFIG_SLAVE_MASK) >> SPI_CONFIG_SLAVE_SHIFT)

/*
 * QUADSPI (RO)
 *
 * Support for Quad I/O SPI
 */
#define SPI_CONFIG_QUADSPI_MASK (0x200U)
#define SPI_CONFIG_QUADSPI_SHIFT (9U)
#define SPI_CONFIG_QUADSPI_GET(x) (((uint32_t)(x) & SPI_CONFIG_QUADSPI_MASK) >> SPI_CONFIG_QUADSPI_SHIFT)

/*
 * DUALSPI (RO)
 *
 * Support for Dual I/O SPI
 */
#define SPI_CONFIG_DUALSPI_MASK (0x100U)
#define SPI_CONFIG_DUALSPI_SHIFT (8U)
#define SPI_CONFIG_DUALSPI_GET(x) (((uint32_t)(x) & SPI_CONFIG_DUALSPI_MASK) >> SPI_CONFIG_DUALSPI_SHIFT)

/*
 * TXFIFOSIZE (RO)
 *
 * Depth of TX FIFO
 * 0x0: 2 words
 * 0x1: 4 words
 * 0x2: 8 words
 * 0x3: 16 words
 * 0x4: 32 words
 * 0x5: 64 words
 * 0x6: 128 words
 */
#define SPI_CONFIG_TXFIFOSIZE_MASK (0xF0U)
#define SPI_CONFIG_TXFIFOSIZE_SHIFT (4U)
#define SPI_CONFIG_TXFIFOSIZE_GET(x) (((uint32_t)(x) & SPI_CONFIG_TXFIFOSIZE_MASK) >> SPI_CONFIG_TXFIFOSIZE_SHIFT)

/*
 * RXFIFOSIZE (RO)
 *
 * Depth of RX FIFO
 * 0x0: 2 words
 * 0x1: 4 words
 * 0x2: 8 words
 * 0x3: 16 words
 * 0x4: 32 words
 * 0x5: 64 words
 * 0x6: 128 words
 */
#define SPI_CONFIG_RXFIFOSIZE_MASK (0xFU)
#define SPI_CONFIG_RXFIFOSIZE_SHIFT (0U)
#define SPI_CONFIG_RXFIFOSIZE_GET(x) (((uint32_t)(x) & SPI_CONFIG_RXFIFOSIZE_MASK) >> SPI_CONFIG_RXFIFOSIZE_SHIFT)




#endif /* HPM_SPI_H */
