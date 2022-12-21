/* THIS FILE HAS BEEN GENERATED, DO NOT MODIFY IT. */
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

#ifndef HAL_INCLUDE_HAL_UART_PERIPH_H_
#define HAL_INCLUDE_HAL_UART_PERIPH_H_
#include "hal_udma_core_periph.h"

/* ----------------------------------------------------------------------------
   -- UART Peripheral Access Layer --
   ---------------------------------------------------------------------------- */

/** UART_Type Register Layout Typedef */
typedef struct
{
	udma_channel_t rx; /**< UDMA RX channels struct. */
	udma_channel_t tx; /**< UDMA TX channels struct. */
	volatile uint32_t status; /**< Status register */
	volatile uint32_t setup; /**< Configuration register */
} uart_t;


/* ----------------------------------------------------------------------------
   -- UART Register Bitfield Access --
   ---------------------------------------------------------------------------- */

/*! @name STATUS */
/* TX busy status flag */
#define UART_STATUS_TX_BUSY_MASK                                     (0x1)
#define UART_STATUS_TX_BUSY_SHIFT                                    (0)
#define UART_STATUS_TX_BUSY(val)                                     (((uint32_t)(((uint32_t)(val)) << UART_STATUS_TX_BUSY_SHIFT)) & UART_STATUS_TX_BUSY_MASK)

/* RX busy status flag */
#define UART_STATUS_RX_BUSY_MASK                                     (0x2)
#define UART_STATUS_RX_BUSY_SHIFT                                    (1)
#define UART_STATUS_RX_BUSY(val)                                     (((uint32_t)(((uint32_t)(val)) << UART_STATUS_RX_BUSY_SHIFT)) & UART_STATUS_RX_BUSY_MASK)

/* RX parity error status flag */
#define UART_STATUS_RX_PE_MASK                                       (0x4)
#define UART_STATUS_RX_PE_SHIFT                                      (2)
#define UART_STATUS_RX_PE(val)                                       (((uint32_t)(((uint32_t)(val)) << UART_STATUS_RX_PE_SHIFT)) & UART_STATUS_RX_PE_MASK)


/*! @name SETUP */
/* Set parity generation and check:
  - 1'b0: disable
  - 1'b1: enable */
#define UART_SETUP_PARITY_ENA_MASK                                   (0x1)
#define UART_SETUP_PARITY_ENA_SHIFT                                  (0)
#define UART_SETUP_PARITY_ENA(val)                                   (((uint32_t)(((uint32_t)(val)) << UART_SETUP_PARITY_ENA_SHIFT)) & UART_SETUP_PARITY_ENA_MASK)

/* Set character length:
  - 2'b00: 5 bits
  - 2'b01: 6 bits
  - 2'b10: 7 bits
  - 2'b11: 8 bits */
#define UART_SETUP_BIT_LENGTH_MASK                                   (0x6)
#define UART_SETUP_BIT_LENGTH_SHIFT                                  (1)
#define UART_SETUP_BIT_LENGTH(val)                                   (((uint32_t)(((uint32_t)(val)) << UART_SETUP_BIT_LENGTH_SHIFT)) & UART_SETUP_BIT_LENGTH_MASK)

/* Set stop bits length:
  - 2'b0: 1 stop bit
  - 2'b1: 2 stop bits */
#define UART_SETUP_STOP_BITS_MASK                                    (0x8)
#define UART_SETUP_STOP_BITS_SHIFT                                   (3)
#define UART_SETUP_STOP_BITS(val)                                    (((uint32_t)(((uint32_t)(val)) << UART_SETUP_STOP_BITS_SHIFT)) & UART_SETUP_STOP_BITS_MASK)

/* Set TX transceiver state:
  - 1'b0: disable
  - 1'b1: enable */
#define UART_SETUP_TX_ENA_MASK                                       (0x100)
#define UART_SETUP_TX_ENA_SHIFT                                      (8)
#define UART_SETUP_TX_ENA(val)                                       (((uint32_t)(((uint32_t)(val)) << UART_SETUP_TX_ENA_SHIFT)) & UART_SETUP_TX_ENA_MASK)

/* Set RX transceiver state:
  - 1'b0: disable
  - 1'b1: enable */
#define UART_SETUP_RX_ENA_MASK                                       (0x200)
#define UART_SETUP_RX_ENA_SHIFT                                      (9)
#define UART_SETUP_RX_ENA(val)                                       (((uint32_t)(((uint32_t)(val)) << UART_SETUP_RX_ENA_SHIFT)) & UART_SETUP_RX_ENA_MASK)

/* Sets the clock divider ratio for the baud rate generator. */
#define UART_SETUP_CLKDIV_MASK                                       (0xffff0000)
#define UART_SETUP_CLKDIV_SHIFT                                      (16)
#define UART_SETUP_CLKDIV(val)                                       (((uint32_t)(((uint32_t)(val)) << UART_SETUP_CLKDIV_SHIFT)) & UART_SETUP_CLKDIV_MASK)


/*! @name STATUS */
typedef union
{
    struct
    {
        /* TX busy status flag */
        uint32_t tx_busy:1;
        /* RX busy status flag */
        uint32_t rx_busy:1;
        /* RX parity error status flag */
        uint32_t rx_pe:1;
    } field;
    uint32_t word;
} uart_status_t;

/*! @name SETUP */
typedef union
{
    struct
    {
        /* Set parity generation and check:
        - 1'b0: disable
        - 1'b1: enable */
        uint32_t parity_ena:1;
        /* Set character length:
        - 2'b00: 5 bits
        - 2'b01: 6 bits
        - 2'b10: 7 bits
        - 2'b11: 8 bits */
        uint32_t bit_length:2;
        /* Set stop bits length:
        - 2'b0: 1 stop bit
        - 2'b1: 2 stop bits */
        uint32_t stop_bits:1;
        uint32_t reserved_0:4;
        /* Set TX transceiver state:
        - 1'b0: disable
        - 1'b1: enable */
        uint32_t tx_ena:1;
        /* Set RX transceiver state:
        - 1'b0: disable
        - 1'b1: enable */
        uint32_t rx_ena:1;
        uint32_t reserved_1:6;
        /* Sets the clock divider ratio for the baud rate generator. */
        uint32_t clkdiv:16;
    } field;
    uint32_t word;
} uart_setup_t;


#endif /* HAL_INCLUDE_HAL_UART_PERIPH_H_ */
