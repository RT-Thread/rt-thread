/*
 * Copyright (C) 2019 ETH Zurich, University of Bologna
 * and GreenWaves Technologies
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef HAL_INCLUDE_HAL_SPI_PERIPH_H_
#define HAL_INCLUDE_HAL_SPI_PERIPH_H_

#include "hal_udma_core_periph.h"

/* ----------------------------------------------------------------------------
   -- SPI Peripheral Access Layer --
   ---------------------------------------------------------------------------- */

/** SPI_Type Register Layout Typedef */
typedef struct {
	udma_channel_t rx; /**< UDMA RX channels struct. */
	udma_channel_t tx; /**< UDMA RX channels struct. */
	udma_channel_t cmd; /**< UDMA RX channels struct. */
} spi_t;

/* ----------------------------------------------------------------------------
   -- SPI Register Bitfield Access --
   ---------------------------------------------------------------------------- */

/* SPI command fields offset, mask, value definition */
/* SPI commands fields offsets */
#define SPI_CMD_ID_OFFSET 28

/* COMMON definitions */
#define SPI_CMD_QPI_ENA		  1
#define SPI_CMD_QPI_DIS		  0
#define SPI_CMD_LSB_FIRST	  1
#define SPI_CMD_MSB_FIRST	  0
#define SPI_CMD_4_WORD_PER_TRANSF 2
#define SPI_CMD_2_WORD_PER_TRANSF 1
#define SPI_CMD_1_WORD_PER_TRANSF 0
#define SPI_CMD_DATA_WITDH(val)	  (val)
#define SPI_CMD_CMD_SIZE(val)	  (val)

/* CFG */
#define SPI_CMD_CFG_CLK_DIV_OFFSET 0
#define SPI_CMD_CFG_CLK_DIV_WIDTH  8
#define SPI_CMD_CFG_CPHA_OFFSET	   8
#define SPI_CMD_CFG_CPOL_OFFSET	   9

#define SPI_CMD_CFG_CLKDIV(val) (val)
#define SPI_CMD_CFG_CPOL_POS	1
#define SPI_CMD_CFG_CPOL_NEG	0
#define SPI_CMD_CFG_CPHA_STD	1
#define SPI_CMD_CFG_CPHA_OPP	0

/* SOT */
#define SPI_CMD_SOT_CS_OFFSET 0
#define SPI_CMD_SOT_CS_WIDTH  2

#define SPI_CMD_SOT_CS0 0
#define SPI_CMD_SOT_CS1 1
#define SPI_CMD_SOT_CS2 2
#define SPI_CMD_SOT_CS3 3

/* SEND_CMD */
#define SPI_CMD_SEND_CMD_CMD_OFFSET  0
#define SPI_CMD_SEND_CMD_CMD_WIDTH   16
#define SPI_CMD_SEND_CMD_SIZE_OFFSET 16
#define SPI_CMD_SEND_CMD_SIZE_WIDTH  4
#define SPI_CMD_SEND_CMD_QPI_OFFSET  27

/* SEND_CMD */
#define SPI_CMD_SEND_BITS_BITS_OFFSET 0
#define SPI_CMD_SEND_BITS_BITS_WIDTH  16
#define SPI_CMD_SEND_BITS_SIZE_OFFSET 16
#define SPI_CMD_SEND_BITS_SIZE_WIDTH  4
#define SPI_CMD_SEND_BITS_QPI_OFFSET  27

/* SEND_ADDR */
#define SPI_CMD_SEND_ADDR_SIZE_OFFSET 16
#define SPI_CMD_SEND_ADDR_SIZE_WIDTH  5
#define SPI_CMD_SEND_ADDR_QPI_OFFSET  27

#define SPI_CMD_SEND_ADDR_VALUE(value) (value)

/* SEND_DUMMY */
#define SPI_CMD_DUMMY_CYCLE_OFFSET 16
#define SPI_CMD_DUMMY_CYCLE_WIDTH  5

/* TX_DATA */
#define SPI_CMD_TX_DATA_SIZE_OFFSET	 0
#define SPI_CMD_TX_DATA_SIZE_WIDTH	 16
#define SPI_CMD_TX_DATA_QPI_OFFSET	 27
#define SPI_CMD_TX_DATA_WORDTRANS_OFFSET 21
#define SPI_CMD_TX_DATA_WORDTRANS_WIDTH	 2
#define SPI_CMD_TX_DATA_LSBFIRST_OFFSET	 26
#define SPI_CMD_TX_DATA_BITSWORD_OFFSET	 16
#define SPI_CMD_TX_DATA_BITSWORD_WIDTH	 5

/* RX_DATA */
#define SPI_CMD_RX_DATA_SIZE_OFFSET	 0
#define SPI_CMD_RX_DATA_SIZE_WIDTH	 16
#define SPI_CMD_RX_DATA_QPI_OFFSET	 27
#define SPI_CMD_RX_DATA_WORDTRANS_OFFSET 21
#define SPI_CMD_RX_DATA_WORDTRANS_WIDTH	 2
#define SPI_CMD_RX_DATA_LSBFIRST_OFFSET	 26
#define SPI_CMD_RX_DATA_BITSWORD_OFFSET	 16
#define SPI_CMD_RX_DATA_BITSWORD_WIDTH	 5

/* RPT */
#define SPI_CMD_RPT_NB_OFFSET 0
#define SPI_CMD_RPT_NB_WIDTH  16

/* EOT */
#define SPI_CMD_EOT_GEN_EVT_OFFSET 0
#define SPI_CMD_EOT_CS_KEEP_OFFSET 1

#define SPI_CMD_EOT_EVENT_ENA 1
#define SPI_CMD_EOT_EVENT_DIS 0

/* WAIT */
#define SPI_CMD_WAIT_EVENT_OFFSET 0
#define SPI_CMD_WAIT_EVENT_WIDTH  2

/* RX_CHECK */
#define SPI_CMD_RX_CHECK_VALUE_OFFSET 0
#define SPI_CMD_RX_CHECK_VALUE_WIDTH  16

#define SPI_CMD_RX_CHECK_SIZE_OFFSET 16
#define SPI_CMD_RX_CHECK_SIZE_WIDTH  4

#define SPI_CMD_RX_CHECK_MODE_OFFSET 24
#define SPI_CMD_RX_CHECK_MODE_WIDTH  2

#define SPI_CMD_RX_CHECK_BYTE_ALIGN_OFFSET 26

#define SPI_CMD_RX_CHECK_QPI_OFFSET 27

#define SPI_CMD_RX_CHECK_MODE_MATCH 0
#define SPI_CMD_RX_CHECK_MODE_ONES  1
#define SPI_CMD_RX_CHECK_MODE_ZEROS 2
#define SPI_CMD_RX_CHECK_MODE_MASK  3

/* FULL DUPLEX */
#define SPI_CMD_FUL_SIZE_OFFSET	     0
#define SPI_CMD_FUL_SIZE_WIDTH	     16
#define SPI_CMD_FUL_WORDTRANS_OFFSET 21
#define SPI_CMD_FUL_WORDTRANS_WIDTH  2
#define SPI_CMD_FUL_LSBFIRST_OFFSET  26
#define SPI_CMD_FUL_BITSWORD_OFFSET  16
#define SPI_CMD_FUL_BITSWORD_WIDTH   5

#define SPI_CMD_SETUP_UC_TXRXEN_OFFSET 27
#define SPI_CMD_SETUP_UC_DS_OFFSET     25

/* ----------------------------------------------------------------------------
   -- SPI CMD IDs and macros --
   ---------------------------------------------------------------------------- */

/*! @name CMD_CFG */
/* Channel continuous mode:
  - 1'b0: disable
  - 1'b1: enable
  At the end of the buffer the uDMA reloads the address and size and starts a new transfer. */
#define UDMA_CORE_CMD_CFG_CONTINOUS_MASK  (0x1)
#define UDMA_CORE_CMD_CFG_CONTINOUS_SHIFT (0)
#define UDMA_CORE_CMD_CFG_CONTINOUS(val)                                       \
	(((uint32_t)(((uint32_t)(val))                                         \
		     << UDMA_CORE_CMD_CFG_CONTINOUS_SHIFT)) &                  \
	 UDMA_CORE_CMD_CFG_CONTINOUS_MASK)

/* Channel transfer size used to increment uDMA buffer address pointer:
  - 2'b00: +1 (8 bits)
  - 2'b01: +2 (16 bits)
  - 2'b10: +4 (32 bits)
  - 2'b11: +0 */
#define UDMA_CORE_CMD_CFG_DATASIZE_MASK	 (0x6)
#define UDMA_CORE_CMD_CFG_DATASIZE_SHIFT (1)
#define UDMA_CORE_CMD_CFG_DATASIZE(val)                                        \
	(((uint32_t)(((uint32_t)(val)) << UDMA_CORE_CMD_CFG_DATASIZE_SHIFT)) & \
	 UDMA_CORE_CMD_CFG_DATASIZE_MASK)

/* Reserved/Not used. */
#define UDMA_CORE_CMD_CFG_RESERVED_0_MASK  (0x8)
#define UDMA_CORE_CMD_CFG_RESERVED_0_SHIFT (3)
#define UDMA_CORE_CMD_CFG_RESERVED_0(val)                                      \
	(((uint32_t)(((uint32_t)(val))                                         \
		     << UDMA_CORE_CMD_CFG_RESERVED_0_SHIFT)) &                 \
	 UDMA_CORE_CMD_CFG_RESERVED_0_MASK)

/* Channel enable and start transfer:
  - 1'b0: disable
  - 1'b1: enable
  This signal is used also to queue a transfer if one is already ongoing. */
#define UDMA_CORE_CMD_CFG_EN_MASK  (0x10)
#define UDMA_CORE_CMD_CFG_EN_SHIFT (4)
#define UDMA_CORE_CMD_CFG_EN(val)                                              \
	(((uint32_t)(((uint32_t)(val)) << UDMA_CORE_CMD_CFG_EN_SHIFT)) &       \
	 UDMA_CORE_CMD_CFG_EN_MASK)

/* Transfer pending in queue status flag:
  - 1'b0: no pending transfer in the queue
  - 1'b1: pending transfer in the queue */
#define UDMA_CORE_CMD_CFG_PENDING_MASK	(0x20)
#define UDMA_CORE_CMD_CFG_PENDING_SHIFT (5)
#define UDMA_CORE_CMD_CFG_PENDING(val)                                         \
	(((uint32_t)(((uint32_t)(val)) << UDMA_CORE_CMD_CFG_PENDING_SHIFT)) &  \
	 UDMA_CORE_CMD_CFG_PENDING_MASK)

/* Channel clear and stop transfer:
  - 1'b0: disable
  - 1'b1: stop and clear the on-going transfer */
#define UDMA_CORE_CMD_CFG_CLR_MASK  (0x20)
#define UDMA_CORE_CMD_CFG_CLR_SHIFT (5)
#define UDMA_CORE_CMD_CFG_CLR(val)                                             \
	(((uint32_t)(((uint32_t)(val)) << UDMA_CORE_CMD_CFG_CLR_SHIFT)) &      \
	 UDMA_CORE_CMD_CFG_CLR_MASK)

/* Reserved/Not used. */
#define UDMA_CORE_CMD_CFG_RESERVED_1_MASK  (0xffffff80)
#define UDMA_CORE_CMD_CFG_RESERVED_1_SHIFT (7)
#define UDMA_CORE_CMD_CFG_RESERVED_1(val)                                      \
	(((uint32_t)(((uint32_t)(val))                                         \
		     << UDMA_CORE_CMD_CFG_RESERVED_1_SHIFT)) &                 \
	 UDMA_CORE_CMD_CFG_RESERVED_1_MASK)

/*! @name CMD_INITCFG */
/* Reserved/Not used. */
#define UDMA_CORE_CMD_INITCFG_RESERVED_0_MASK  (0xffffffff)
#define UDMA_CORE_CMD_INITCFG_RESERVED_0_SHIFT (0)
#define UDMA_CORE_CMD_INITCFG_RESERVED_0(val)                                  \
	(((uint32_t)(((uint32_t)(val))                                         \
		     << UDMA_CORE_CMD_INITCFG_RESERVED_0_SHIFT)) &             \
	 UDMA_CORE_CMD_INITCFG_RESERVED_0_MASK)

#define SPI_CMD_CFG_ID	     0x0 /* Sets the configuration for the SPI Master IP. */
#define SPI_CMD_SOT_ID	     0x1 /* Sets the Chip Select (CS). */
#define SPI_CMD_SEND_CMD_ID  0x2 /* Transmits a configurable size command. */
#define SPI_CMD_SEND_BITS_ID 0x2 /* Transmits a configurable size command. */
#define SPI_CMD_SEND_ADDR_ID 0x3 /* Transmits a configurable size address. */
#define SPI_CMD_DUMMY_ID                                                       \
	0x4 /* Receives a number of dummy bits (not sent to the rx interface). */
#define SPI_CMD_WAIT_ID                                                        \
	0x5 /* Waits an external event to move to the next instruction. */
#define SPI_CMD_TX_DATA_ID 0x6 /* Sends data (max 64Kbits). */
#define SPI_CMD_RX_DATA_ID 0x7 /* Receives data (max 64Kbits). */
#define SPI_CMD_RPT_ID	   0x8 /* Repeat the next transfer N times. */
#define SPI_CMD_EOT_ID	   0x9 /* Clears the Chip Select (CS). */
#define SPI_CMD_RPT_END_ID 0xA /* End of the repeat loop command. */
#define SPI_CMD_RX_CHECK_ID                                                    \
	0xB /* Check up ot 16 bits of data against an expected value. */
#define SPI_CMD_FULL_DUPL_ID 0xC /* Activate full duplex mode. */

#define SPI_CMD_CFG(clockDiv, cpol, cpha)                                      \
	((SPI_CMD_CFG_ID << SPI_CMD_ID_OFFSET) |                               \
	 ((cpol) << SPI_CMD_CFG_CPOL_OFFSET) |                                 \
	 ((cpha) << SPI_CMD_CFG_CPHA_OFFSET) |                                 \
	 ((clockDiv) << SPI_CMD_CFG_CLK_DIV_OFFSET))
#define SPI_CMD_SOT(cs)                                                        \
	((SPI_CMD_SOT_ID << SPI_CMD_ID_OFFSET) |                               \
	 ((cs) << SPI_CMD_SOT_CS_OFFSET))
#define SPI_CMD_SEND_CMD(cmd, bits, qpi)                                       \
	((SPI_CMD_SEND_CMD_ID << SPI_CMD_ID_OFFSET) |                          \
	 ((qpi) << SPI_CMD_SEND_CMD_QPI_OFFSET) |                              \
	 (((bits)-1) << SPI_CMD_SEND_CMD_SIZE_OFFSET) | (cmd & 0xFFFF))
#define SPI_CMD_SEND_BITS(data, bits, qpi)                                     \
	((SPI_CMD_SEND_CMD_ID << SPI_CMD_ID_OFFSET) |                          \
	 ((qpi) << SPI_CMD_SEND_CMD_QPI_OFFSET) |                              \
	 (((bits)-1) << SPI_CMD_SEND_CMD_SIZE_OFFSET) | (data & 0xFFFF))
#define SPI_CMD_DUMMY(cycles)                                                  \
	((SPI_CMD_DUMMY_ID << SPI_CMD_ID_OFFSET) |                             \
	 (((cycles)-1) << SPI_CMD_DUMMY_CYCLE_OFFSET))

#define SPI_CMD_SETUP_UCA(txrxen, ds, addr)                                    \
	((SPI_CMD_SETUP_UCA_ID << SPI_CMD_ID_OFFSET) |                         \
	 ((txrxen) << SPI_CMD_SETUP_UC_TXRXEN_OFFSET) | ((int)addr & 0xFFFFF))
#define SPI_CMD_SETUP_UCS(txrxen, ds, size)                                    \
	((SPI_CMD_SETUP_UCS_ID << SPI_CMD_ID_OFFSET) |                         \
	 ((txrxen) << SPI_CMD_SETUP_UC_TXRXEN_OFFSET) |                        \
	 ((ds) << SPI_CMD_SETUP_UC_DS_OFFSET) | (size & 0xFFFF))

#define SPI_CMD_TX_DATA(words, wordstrans, bitsword, qpi, lsbfirst)            \
	((SPI_CMD_TX_DATA_ID << SPI_CMD_ID_OFFSET) |                           \
	 ((qpi) << SPI_CMD_TX_DATA_QPI_OFFSET) |                               \
	 ((wordstrans) << SPI_CMD_TX_DATA_WORDTRANS_OFFSET) |                  \
	 ((bitsword - 1) << SPI_CMD_TX_DATA_BITSWORD_OFFSET) |                 \
	 (((words)-1) << SPI_CMD_TX_DATA_SIZE_OFFSET) |                        \
	 ((lsbfirst) << SPI_CMD_TX_DATA_LSBFIRST_OFFSET))
#define SPI_CMD_RX_DATA(words, wordstrans, bitsword, qpi, lsbfirst)            \
	((SPI_CMD_RX_DATA_ID << SPI_CMD_ID_OFFSET) |                           \
	 ((qpi) << SPI_CMD_RX_DATA_QPI_OFFSET) |                               \
	 ((wordstrans) << SPI_CMD_RX_DATA_WORDTRANS_OFFSET) |                  \
	 ((bitsword - 1) << SPI_CMD_RX_DATA_BITSWORD_OFFSET) |                 \
	 (((words)-1) << SPI_CMD_RX_DATA_SIZE_OFFSET) |                        \
	 ((lsbfirst) << SPI_CMD_RX_DATA_LSBFIRST_OFFSET))
#define SPI_CMD_RPT(iter)                                                      \
	((SPI_CMD_RPT_ID << SPI_CMD_ID_OFFSET) |                               \
	 ((iter) << SPI_CMD_RPT_NB_OFFSET))
#define SPI_CMD_EOT(evt, cs_keep)                                              \
	((SPI_CMD_EOT_ID << SPI_CMD_ID_OFFSET) |                               \
	 ((evt) << SPI_CMD_EOT_GEN_EVT_OFFSET) |                               \
	 ((cs_keep) << SPI_CMD_EOT_CS_KEEP_OFFSET))

#define SPI_CMD_RX_CHECK(mode, bits, value, qpi, byte_align)                   \
	((SPI_CMD_RX_CHECK_ID << SPI_CMD_ID_OFFSET) |                          \
	 ((value) << SPI_CMD_RX_CHECK_VALUE_OFFSET) |                          \
	 ((mode) << SPI_CMD_RX_CHECK_MODE_OFFSET) |                            \
	 (((bits)-1) << SPI_CMD_RX_CHECK_SIZE_OFFSET) |                        \
	 ((byte_align) << SPI_CMD_RX_CHECK_BYTE_ALIGN_OFFSET) |                \
	 ((qpi) << SPI_CMD_RX_CHECK_QPI_OFFSET))

#define SPI_CMD_WAIT(event)                                                    \
	((SPI_CMD_WAIT_ID << SPI_CMD_ID_OFFSET) |                              \
	 ((event) << SPI_CMD_WAIT_EVENT_OFFSET))
#define SPI_CMD_RPT_END() ((SPI_CMD_RPT_END_ID << SPI_CMD_ID_OFFSET))
#define SPI_CMD_FUL(words, wordstrans, bitsword, lsbfirst)                     \
	((SPI_CMD_FUL_ID << SPI_CMD_ID_OFFSET) |                               \
	 ((wordstrans) << SPI_CMD_FUL_WORDTRANS_OFFSET) |                      \
	 ((bitsword - 1) << SPI_CMD_FUL_BITSWORD_OFFSET) |                     \
	 (((words)-1) << SPI_CMD_FUL_SIZE_OFFSET) |                            \
	 ((lsbfirst) << SPI_CMD_FUL_LSBFIRST_OFFSET))


#endif /* HAL_INCLUDE_HAL_SPI_PERIPH_H_ */
