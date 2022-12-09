/*
 * This is a generated file
 * 
 * Copyright 2021 QuickLogic
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
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __UDMA_UART_H_
#define __UDMA_UART_H_

//---------------------------------//
//
// Module: UDMA_UART
//
//---------------------------------//

#ifndef __IO
#define __IO volatile
#endif

#ifndef __I
#define __I volatile
#endif

#ifndef __O
#define __O volatile
#endif

#include "stdint.h"

typedef struct {

  // Offset = 0x0000
  union {
    __IO uint32_t rx_saddr;
    struct {
      __IO uint32_t  saddr      : 12;
    } rx_saddr_b;
  };

  // Offset = 0x0004
  union {
    __IO uint32_t rx_size;
    struct {
      __IO uint32_t  size       : 16;
    } rx_size_b;
  };

  // Offset = 0x0008
  union {
    __IO uint32_t rx_cfg;
    struct {
      __IO uint32_t  continuous :  1;
      __IO uint32_t             :  3;
      __IO uint32_t  en         :  1;
      __IO uint32_t  pending    :  1;
      __IO uint32_t  clr        :  1;
    } rx_cfg_b;
  };
  __I uint32_t    unused0[1];

  // Offset = 0x0010
  union {
    __IO uint32_t tx_saddr;
    struct {
      __IO uint32_t  saddr      : 12;
    } tx_saddr_b;
  };

  // Offset = 0x0014
  union {
    __IO uint32_t tx_size;
    struct {
      __IO uint32_t  size       : 16;
    } tx_size_b;
  };

  // Offset = 0x0018
  union {
    __IO uint32_t tx_cfg;
    struct {
      __IO uint32_t  continuous :  1;
      __IO uint32_t             :  3;
      __IO uint32_t  en         :  1;
      __IO uint32_t  pending    :  1;
      __IO uint32_t  clr        :  1;
    } tx_cfg_b;
  };
  __I uint32_t    unused1[1];

  // Offset = 0x0020
  union {
    __IO uint32_t status;
    struct {
      __IO uint32_t  tx_busy    :  1;
      __IO uint32_t  rx_busy    :  1;
    } status_b;
  };

  // Offset = 0x0024
  union {
    __IO uint32_t uart_setup;
    struct {
      __IO uint32_t  parity_en  :  1;
      __IO uint32_t  bits       :  2;
      __IO uint32_t  stop_bits  :  1;
      __IO uint32_t  rx_polling_en :  1;
      __IO uint32_t  rx_clean_fifo :  1;
      __IO uint32_t             :  2;
      __IO uint32_t  en_tx      :  1;
      __IO uint32_t  en_rx      :  1;
      __IO uint32_t             :  6;
      __IO uint32_t  div        : 16;
    } uart_setup_b;
  };

  // Offset = 0x0028
  union {
    __IO uint32_t error;
    struct {
      __IO uint32_t  overflow_err :  1;
      __IO uint32_t  parity_err :  1;
    } error_b;
  };

  // Offset = 0x002c
  union {
    __IO uint32_t irq_en;
    struct {
      __IO uint32_t  rx_irq_en  :  1;
      __IO uint32_t  err_irq_en :  1;
    } irq_en_b;
  };

  // Offset = 0x0030
  union {
    __IO uint32_t valid;
    struct {
      __IO uint32_t  rx_data_valid :  1;
    } valid_b;
  };

  // Offset = 0x0034
  union {
    __IO uint32_t data;
    struct {
      __IO uint32_t  rx_data    :  8;
    } data_b;
  };
} UdmaUart_t;


#define REG_RX_SADDR                   0x00
#define   REG_RX_SADDR_SADDR_LSB                   0
#define   REG_RX_SADDR_SADDR_MASK                  0xfff
#define REG_RX_SIZE                    0x04
#define   REG_RX_SIZE_SIZE_LSB                     0
#define   REG_RX_SIZE_SIZE_MASK                    0xffff
#define REG_RX_CFG                     0x08
#define   REG_RX_CFG_CLR_LSB                       6
#define   REG_RX_CFG_CLR_MASK                      0x1
#define   REG_RX_CFG_PENDING_LSB                   5
#define   REG_RX_CFG_PENDING_MASK                  0x1
#define   REG_RX_CFG_EN_LSB                        4
#define   REG_RX_CFG_EN_MASK                       0x1
#define   REG_RX_CFG_CONTINUOUS_LSB                0
#define   REG_RX_CFG_CONTINUOUS_MASK               0x1
#define REG_TX_SADDR                   0x10
#define   REG_TX_SADDR_SADDR_LSB                   0
#define   REG_TX_SADDR_SADDR_MASK                  0xfff
#define REG_TX_SIZE                    0x14
#define   REG_TX_SIZE_SIZE_LSB                     0
#define   REG_TX_SIZE_SIZE_MASK                    0xffff
#define REG_TX_CFG                     0x18
#define   REG_TX_CFG_CLR_LSB                       6
#define   REG_TX_CFG_CLR_MASK                      0x1
#define   REG_TX_CFG_PENDING_LSB                   5
#define   REG_TX_CFG_PENDING_MASK                  0x1
#define   REG_TX_CFG_EN_LSB                        4
#define   REG_TX_CFG_EN_MASK                       0x1
#define   REG_TX_CFG_CONTINUOUS_LSB                0
#define   REG_TX_CFG_CONTINUOUS_MASK               0x1
#define REG_STATUS                     0x20
#define   REG_STATUS_RX_BUSY_LSB                   1
#define   REG_STATUS_RX_BUSY_MASK                  0x1
#define   REG_STATUS_TX_BUSY_LSB                   0
#define   REG_STATUS_TX_BUSY_MASK                  0x1
#define REG_UART_SETUP                 0x24
#define   REG_UART_SETUP_DIV_LSB                   16
#define   REG_UART_SETUP_DIV_MASK                  0xffff
#define   REG_UART_SETUP_EN_RX_LSB                 9
#define   REG_UART_SETUP_EN_RX_MASK                0x1
#define   REG_UART_SETUP_EN_TX_LSB                 8
#define   REG_UART_SETUP_EN_TX_MASK                0x1
#define   REG_UART_SETUP_RX_CLEAN_FIFO_LSB         5
#define   REG_UART_SETUP_RX_CLEAN_FIFO_MASK        0x1
#define   REG_UART_SETUP_RX_POLLING_EN_LSB         4
#define   REG_UART_SETUP_RX_POLLING_EN_MASK        0x1
#define   REG_UART_SETUP_STOP_BITS_LSB             3
#define   REG_UART_SETUP_STOP_BITS_MASK            0x1
#define   REG_UART_SETUP_BITS_LSB                  1
#define   REG_UART_SETUP_BITS_MASK                 0x3
#define   REG_UART_SETUP_PARITY_EN_LSB             0
#define   REG_UART_SETUP_PARITY_EN_MASK            0x1
#define REG_ERROR                      0x28
#define   REG_ERROR_PARITY_ERR_LSB                 1
#define   REG_ERROR_PARITY_ERR_MASK                0x1
#define   REG_ERROR_OVERFLOW_ERR_LSB               0
#define   REG_ERROR_OVERFLOW_ERR_MASK              0x1
#define REG_IRQ_EN                     0x2C
#define   REG_IRQ_EN_ERR_IRQ_EN_LSB                1
#define   REG_IRQ_EN_ERR_IRQ_EN_MASK               0x1
#define   REG_IRQ_EN_RX_IRQ_EN_LSB                 0
#define   REG_IRQ_EN_RX_IRQ_EN_MASK                0x1
#define REG_VALID                      0x30
#define   REG_VALID_RX_DATA_VALID_LSB              0
#define   REG_VALID_RX_DATA_VALID_MASK             0x1
#define REG_DATA                       0x34
#define   REG_DATA_RX_DATA_LSB                     0
#define   REG_DATA_RX_DATA_MASK                    0xff

#ifndef __REGFIELD_OPS_
#define __REGFIELD_OPS_
static inline uint32_t regfield_read(uint32_t reg, uint32_t mask, uint32_t lsb) {
  return (reg >> lsb) & mask;
}
static inline uint32_t regfield_write(uint32_t reg, uint32_t mask, uint32_t lsb, uint32_t value) {
  reg &= ~(mask << lsb);
  reg |= (value & mask) << lsb;
  return reg;
}
#endif  // __REGFIELD_OPS_

#endif // __UDMA_UART_H_
