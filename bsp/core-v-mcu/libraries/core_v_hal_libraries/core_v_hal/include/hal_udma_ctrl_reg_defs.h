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

#ifndef __UDMA_CTRL_H_
#define __UDMA_CTRL_H_

//---------------------------------//
//
// Module: UDMA_CTRL
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
    __IO uint32_t reg_cg;
    struct {
      __IO uint32_t  periph_clk_enable : 32;
    } reg_cg_b;
  };

  // Offset = 0x0004
  union {
    __IO uint32_t reg_cfg_evt;
    struct {
      __IO uint32_t  cmp_event0 :  8;
      __IO uint32_t  cmp_event1 :  8;
      __IO uint32_t  cmp_event2 :  8;
      __IO uint32_t  cmp_event3 :  8;
    } reg_cfg_evt_b;
  };

  // Offset = 0x0008
  union {
    __IO uint32_t reg_rst;
    struct {
      __IO uint32_t  periph_reset : 32;
    } reg_rst_b;
  };
} UdmaCtrl_t;


#define REG_REG_CG                     0x000
#define   REG_REG_CG_PERIPH_CLK_ENABLE_LSB         0
#define   REG_REG_CG_PERIPH_CLK_ENABLE_MASK        0xffffffff
#define REG_REG_CFG_EVT                0x004
#define   REG_REG_CFG_EVT_CMP_EVENT3_LSB           24
#define   REG_REG_CFG_EVT_CMP_EVENT3_MASK          0xff
#define   REG_REG_CFG_EVT_CMP_EVENT2_LSB           16
#define   REG_REG_CFG_EVT_CMP_EVENT2_MASK          0xff
#define   REG_REG_CFG_EVT_CMP_EVENT1_LSB           8
#define   REG_REG_CFG_EVT_CMP_EVENT1_MASK          0xff
#define   REG_REG_CFG_EVT_CMP_EVENT0_LSB           0
#define   REG_REG_CFG_EVT_CMP_EVENT0_MASK          0xff
#define REG_REG_RST                    0x008
#define   REG_REG_RST_PERIPH_RESET_LSB             0
#define   REG_REG_RST_PERIPH_RESET_MASK            0xffffffff

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

#endif // __UDMA_CTRL_H_
