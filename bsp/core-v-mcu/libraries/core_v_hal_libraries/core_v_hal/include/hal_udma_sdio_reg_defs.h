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

#ifndef __UDMA_SDIO_H_
#define __UDMA_SDIO_H_

//---------------------------------//
//
// Module: UDMA_SDIO
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
      __IO uint32_t  saddr      : 32;	// 21 localparam L2_AWIDTH_NOAL = L2_ADDR_WIDTH + 2;
    } rx_saddr_b;
  };

  // Offset = 0x0004
  union {
    __IO uint32_t rx_size;
    struct {
      __IO uint32_t  size       : 20;//16; //should be 20 bit. udma 1MB addressing.
    } rx_size_b;
  };

  // Offset = 0x0008
  union {
    __IO uint32_t rx_cfg;
    struct {
      __IO uint32_t  continuous :  1;
      __IO uint32_t  datasize   :  2;
      __IO uint32_t             :  1;
      __IO uint32_t  en         :  1;
      //__IO uint32_t  pending    :  1;
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
      __IO uint32_t  datasize   :  2;
      __IO uint32_t             :  1;
      __IO uint32_t  en         :  1;
      //__IO uint32_t  pending    :  1;
      __IO uint32_t  clr        :  1;
    } tx_cfg_b;
  };
  __I uint32_t    unused1[1];

  // Offset = 0x0020
  union {
    __IO uint32_t cmd_op;
    struct {
      __IO uint32_t  cmd_rsp_type :  3;
      __IO uint32_t             :  5;
      __IO uint32_t  cmd_op     :  6;
    } cmd_op_b;
  };

  // Offset = 0x0024
  union {
    __IO uint32_t cmd_arg;
    struct {
      __IO uint32_t  cmd_arg    : 32;
    } cmd_arg_b;
  };

  // Offset = 0x0028
  union {
    __IO uint32_t data_setup;
    struct {
      __IO uint32_t  data_en    :  1;
      __IO uint32_t  data_rwn   :  1;
      __IO uint32_t  data_quad  :  1;
      __IO uint32_t             :  5;
      __IO uint32_t  block_num  :  8;
      __IO uint32_t  block_size : 10;
    } data_setup_b;
  };

  // Offset = 0x002c
  union {
    __IO uint32_t start;
    struct {
      __IO uint32_t  start      :  1;
    } start_b;
  };

  // Offset = 0x0030
  union {
    __IO uint32_t rsp0;
    struct {
      __IO uint32_t  rsp0       : 32;
    } rsp0_b;
  };

  // Offset = 0x0034
  union {
    __IO uint32_t rsp1;
    struct {
      __IO uint32_t  rsp1       : 32;
    } rsp1_b;
  };

  // Offset = 0x0038
  union {
    __IO uint32_t rsp2;
    struct {
      __IO uint32_t  rsp2       : 32;
    } rsp2_b;
  };

  // Offset = 0x003c
  union {
    __IO uint32_t rsp3;
    struct {
      __IO uint32_t  rsp3       : 32;
    } rsp3_b;
  };

  // Offset = 0x0040
  union {
    __IO uint32_t clk_div;
    struct {
      __IO uint32_t  clk_div    :  8;
      __IO uint32_t  valid      :  1;
    } clk_div_b;
  };

  // Offset = 0x0044
  union {
    __IO uint32_t status;
    struct {
      __IO uint32_t  eot        :  1;
      __IO uint32_t  error      :  1;
      __IO uint32_t             : 14;
      __IO uint32_t  cmd_err_status :  6;
    } status_b;
  };
} UdmaSdio_t;


#define REG_RX_SADDR                   0x00
#define   REG_RX_SADDR_SADDR_LSB                   0
#define   REG_RX_SADDR_SADDR_MASK                  0xffffffff
#define REG_RX_SIZE                    0x04
#define   REG_RX_SIZE_SIZE_LSB                     0
#define   REG_RX_SIZE_SIZE_MASK                    0xffff
#define REG_RX_CFG                     0x08
#define   REG_RX_CFG_CLR_LSB                       5
#define   REG_RX_CFG_CLR_MASK                      0x1
#define   REG_RX_CFG_PENDING_LSB                   5
#define   REG_RX_CFG_PENDING_MASK                  0x1
#define   REG_RX_CFG_EN_LSB                        4
#define   REG_RX_CFG_EN_MASK                       0x1
#define   REG_RX_CFG_DATASIZE_LSB                  1
#define   REG_RX_CFG_DATASIZE_MASK                 0x3
#define   REG_RX_CFG_CONTINUOUS_LSB                0
#define   REG_RX_CFG_CONTINUOUS_MASK               0x1
#define REG_TX_SADDR                   0x10
#define   REG_TX_SADDR_SADDR_LSB                   0
#define   REG_TX_SADDR_SADDR_MASK                  0xfff
#define REG_TX_SIZE                    0x14
#define   REG_TX_SIZE_SIZE_LSB                     0
#define   REG_TX_SIZE_SIZE_MASK                    0xffff
#define REG_TX_CFG                     0x18
#define   REG_TX_CFG_CLR_LSB                       5
#define   REG_TX_CFG_CLR_MASK                      0x1
#define   REG_TX_CFG_PENDING_LSB                   5
#define   REG_TX_CFG_PENDING_MASK                  0x1
#define   REG_TX_CFG_EN_LSB                        4
#define   REG_TX_CFG_EN_MASK                       0x1
#define   REG_TX_CFG_DATASIZE_LSB                  1
#define   REG_TX_CFG_DATASIZE_MASK                 0x3
#define   REG_TX_CFG_CONTINUOUS_LSB                0
#define   REG_TX_CFG_CONTINUOUS_MASK               0x1
#define REG_CMD_OP                     0x20
#define   REG_CMD_OP_CMD_OP_LSB                    8
#define   REG_CMD_OP_CMD_OP_MASK                   0x3f
#define   REG_CMD_OP_CMD_RSP_TYPE_LSB              0
#define   REG_CMD_OP_CMD_RSP_TYPE_MASK             0x7
#define REG_CMD_ARG                    0x24
#define   REG_CMD_ARG_CMD_ARG_LSB                  0
#define   REG_CMD_ARG_CMD_ARG_MASK                 0xffffffff
#define REG_DATA_SETUP                 0x28
#define   REG_DATA_SETUP_BLOCK_SIZE_LSB            16
#define   REG_DATA_SETUP_BLOCK_SIZE_MASK           0x3ff
#define   REG_DATA_SETUP_BLOCK_NUM_LSB             8
#define   REG_DATA_SETUP_BLOCK_NUM_MASK            0xff
#define   REG_DATA_SETUP_DATA_QUAD_LSB             2
#define   REG_DATA_SETUP_DATA_QUAD_MASK            0x1
#define   REG_DATA_SETUP_DATA_RWN_LSB              1
#define   REG_DATA_SETUP_DATA_RWN_MASK             0x1
#define   REG_DATA_SETUP_DATA_EN_LSB               0
#define   REG_DATA_SETUP_DATA_EN_MASK              0x1
#define REG_START                      0x2C
#define   REG_START_START_LSB                      0
#define   REG_START_START_MASK                     0x1
#define REG_RSP0                       0x30
#define   REG_RSP0_RSP0_LSB                        0
#define   REG_RSP0_RSP0_MASK                       0xffffffff
#define REG_RSP1                       0x34
#define   REG_RSP1_RSP1_LSB                        0
#define   REG_RSP1_RSP1_MASK                       0xffffffff
#define REG_RSP2                       0x38
#define   REG_RSP2_RSP2_LSB                        0
#define   REG_RSP2_RSP2_MASK                       0xffffffff
#define REG_RSP3                       0x3C
#define   REG_RSP3_RSP3_LSB                        0
#define   REG_RSP3_RSP3_MASK                       0xffffffff
#define REG_CLK_DIV                    0x40
#define   REG_CLK_DIV_VALID_LSB                    8
#define   REG_CLK_DIV_VALID_MASK                   0x1
#define   REG_CLK_DIV_CLK_DIV_LSB                  0
#define   REG_CLK_DIV_CLK_DIV_MASK                 0xff
#define REG_STATUS                     0x44
#define   REG_STATUS_CMD_ERR_STATUS_LSB            16
#define   REG_STATUS_CMD_ERR_STATUS_MASK           0x3f
#define   REG_STATUS_ERROR_LSB                     1
#define   REG_STATUS_ERROR_MASK                    0x1
#define   REG_STATUS_EOT_LSB                       0
#define   REG_STATUS_EOT_MASK                      0x1

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

#endif // __UDMA_SDIO_H_
