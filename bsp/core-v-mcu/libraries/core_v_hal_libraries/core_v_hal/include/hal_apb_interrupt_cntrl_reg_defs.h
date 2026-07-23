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

#ifndef __APB_INTERRUPT_CNTRL_H_
#define __APB_INTERRUPT_CNTRL_H_

//---------------------------------//
//
// Module: APB_INTERRUPT_CNTRL
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
    __IO uint32_t reg_mask;
    struct {
      __IO uint32_t  reserved   :  7;
      __IO uint32_t  timer_lo_event :  1;
      __IO uint32_t  unused2    :  8;
      __IO uint32_t  timer_lo_event :  1;
      __IO uint32_t  timer_hi_event :  1;
      __IO uint32_t  gpio_event :  1;
      __IO uint32_t  adv_timer_evens :  4;
      __IO uint32_t  ref_change_event :  1;
      __IO uint32_t  unused1    :  5;
      __IO uint32_t  fc_err_events :  1;
      __IO uint32_t  fc_hp_events :  2;
    } reg_mask_b;
  };

  // Offset = 0x0004
  union {
    __IO uint32_t reg_mask_set;
    struct {
      __IO uint32_t  reserved   :  7;
      __IO uint32_t  timer_lo_event :  1;
      __IO uint32_t  unused2    :  8;
      __IO uint32_t  timer_lo_event :  1;
      __IO uint32_t  timer_hi_event :  1;
      __IO uint32_t  gpio_event :  1;
      __IO uint32_t  adv_timer_evens :  4;
      __IO uint32_t  ref_change_event :  1;
      __IO uint32_t  unused1    :  5;
      __IO uint32_t  fc_err_events :  1;
      __IO uint32_t  fc_hp_events :  2;
    } reg_mask_set_b;
  };

  // Offset = 0x0008
  union {
    __IO uint32_t reg_mask_clear;
    struct {
      __IO uint32_t  reserved   :  7;
      __IO uint32_t  timer_lo_event :  1;
      __IO uint32_t  unused2    :  8;
      __IO uint32_t  timer_lo_event :  1;
      __IO uint32_t  timer_hi_event :  1;
      __IO uint32_t  gpio_event :  1;
      __IO uint32_t  adv_timer_evens :  4;
      __IO uint32_t  ref_change_event :  1;
      __IO uint32_t  unused1    :  5;
      __IO uint32_t  fc_err_events :  1;
      __IO uint32_t  fc_hp_events :  2;
    } reg_mask_clear_b;
  };

  // Offset = 0x000c
  union {
    __IO uint32_t reg_int;
    struct {
      __IO uint32_t  reserved   :  7;
      __IO uint32_t  timer_lo_event :  1;
      __IO uint32_t  unused2    :  8;
      __IO uint32_t  timer_lo_event :  1;
      __IO uint32_t  timer_hi_event :  1;
      __IO uint32_t  gpio_event :  1;
      __IO uint32_t  adv_timer_evens :  4;
      __IO uint32_t  ref_change_event :  1;
      __IO uint32_t  unused1    :  5;
      __IO uint32_t  fc_err_events :  1;
      __IO uint32_t  fc_hp_events :  2;
    } reg_int_b;
  };

  // Offset = 0x0010
  union {
    __IO uint32_t reg_int_set;
    struct {
      __IO uint32_t  reserved   :  7;
      __IO uint32_t  timer_lo_event :  1;
      __IO uint32_t  unused2    :  8;
      __IO uint32_t  timer_lo_event :  1;
      __IO uint32_t  timer_hi_event :  1;
      __IO uint32_t  gpio_event :  1;
      __IO uint32_t  adv_timer_evens :  4;
      __IO uint32_t  ref_change_event :  1;
      __IO uint32_t  unused1    :  5;
      __IO uint32_t  fc_err_events :  1;
      __IO uint32_t  fc_hp_events :  2;
    } reg_int_set_b;
  };

  // Offset = 0x0014
  union {
    __IO uint32_t reg_int_clear;
    struct {
      __IO uint32_t  reserved   :  7;
      __IO uint32_t  timer_lo_event :  1;
      __IO uint32_t  unused2    :  8;
      __IO uint32_t  timer_lo_event :  1;
      __IO uint32_t  timer_hi_event :  1;
      __IO uint32_t  gpio_event :  1;
      __IO uint32_t  adv_timer_evens :  4;
      __IO uint32_t  ref_change_event :  1;
      __IO uint32_t  unused1    :  5;
      __IO uint32_t  fc_err_events :  1;
      __IO uint32_t  fc_hp_events :  2;
    } reg_int_clear_b;
  };

  // Offset = 0x0018
  union {
    __IO uint32_t reg_ack;
    struct {
      __IO uint32_t  reserved   :  7;
      __IO uint32_t  timer_lo_event :  1;
      __IO uint32_t  unused2    :  8;
      __IO uint32_t  timer_lo_event :  1;
      __IO uint32_t  timer_hi_event :  1;
      __IO uint32_t  gpio_event :  1;
      __IO uint32_t  adv_timer_evens :  4;
      __IO uint32_t  ref_change_event :  1;
      __IO uint32_t  unused1    :  5;
      __IO uint32_t  fc_err_events :  1;
      __IO uint32_t  fc_hp_events :  2;
    } reg_ack_b;
  };

  // Offset = 0x001c
  union {
    __IO uint32_t reg_ack_set;
    struct {
      __IO uint32_t  reserved   :  7;
      __IO uint32_t  timer_lo_event :  1;
      __IO uint32_t  unused2    :  8;
      __IO uint32_t  timer_lo_event :  1;
      __IO uint32_t  timer_hi_event :  1;
      __IO uint32_t  gpio_event :  1;
      __IO uint32_t  adv_timer_evens :  4;
      __IO uint32_t  ref_change_event :  1;
      __IO uint32_t  unused1    :  5;
      __IO uint32_t  fc_err_events :  1;
      __IO uint32_t  fc_hp_events :  2;
    } reg_ack_set_b;
  };

  // Offset = 0x0020
  union {
    __IO uint32_t reg_ack_clear;
    struct {
      __IO uint32_t  reserved   :  7;
      __IO uint32_t  timer_lo_event :  1;
      __IO uint32_t  unused2    :  8;
      __IO uint32_t  timer_lo_event :  1;
      __IO uint32_t  timer_hi_event :  1;
      __IO uint32_t  gpio_event :  1;
      __IO uint32_t  adv_timer_evens :  4;
      __IO uint32_t  ref_change_event :  1;
      __IO uint32_t  unused1    :  5;
      __IO uint32_t  fc_err_events :  1;
      __IO uint32_t  fc_hp_events :  2;
    } reg_ack_clear_b;
  };

  // Offset = 0x0024
  union {
    __IO uint32_t reg_fifo;
    struct {
      __IO uint32_t  event_id   :  8;
    } reg_fifo_b;
  };
} ApbInterruptCntrl_t;


#define REG_REG_MASK                   0x000
#define   REG_REG_MASK_fc_hp_events_LSB            30
#define   REG_REG_MASK_fc_hp_events_MASK           0x3
#define   REG_REG_MASK_fc_err_events_LSB           29
#define   REG_REG_MASK_fc_err_events_MASK          0x1
#define   REG_REG_MASK_unused1_LSB                 24
#define   REG_REG_MASK_unused1_MASK                0x1f
#define   REG_REG_MASK_ref_change_event_LSB        23
#define   REG_REG_MASK_ref_change_event_MASK       0x1
#define   REG_REG_MASK_adv_timer_evens_LSB         19
#define   REG_REG_MASK_adv_timer_evens_MASK        0xf
#define   REG_REG_MASK_gpio_event_LSB              18
#define   REG_REG_MASK_gpio_event_MASK             0x1
#define   REG_REG_MASK_timer_hi_event_LSB          17
#define   REG_REG_MASK_timer_hi_event_MASK         0x1
#define   REG_REG_MASK_timer_lo_event_LSB          16
#define   REG_REG_MASK_timer_lo_event_MASK         0x1
#define   REG_REG_MASK_unused2_LSB                 8
#define   REG_REG_MASK_unused2_MASK                0xff
#define   REG_REG_MASK_timer_lo_event_LSB          7
#define   REG_REG_MASK_timer_lo_event_MASK         0x1
#define   REG_REG_MASK_reserved_LSB                0
#define   REG_REG_MASK_reserved_MASK               0x7f
#define REG_REG_MASK_SET               0x004
#define   REG_REG_MASK_SET_fc_hp_events_LSB        30
#define   REG_REG_MASK_SET_fc_hp_events_MASK       0x3
#define   REG_REG_MASK_SET_fc_err_events_LSB       29
#define   REG_REG_MASK_SET_fc_err_events_MASK      0x1
#define   REG_REG_MASK_SET_unused1_LSB             24
#define   REG_REG_MASK_SET_unused1_MASK            0x1f
#define   REG_REG_MASK_SET_ref_change_event_LSB    23
#define   REG_REG_MASK_SET_ref_change_event_MASK   0x1
#define   REG_REG_MASK_SET_adv_timer_evens_LSB     19
#define   REG_REG_MASK_SET_adv_timer_evens_MASK    0xf
#define   REG_REG_MASK_SET_gpio_event_LSB          18
#define   REG_REG_MASK_SET_gpio_event_MASK         0x1
#define   REG_REG_MASK_SET_timer_hi_event_LSB      17
#define   REG_REG_MASK_SET_timer_hi_event_MASK     0x1
#define   REG_REG_MASK_SET_timer_lo_event_LSB      16
#define   REG_REG_MASK_SET_timer_lo_event_MASK     0x1
#define   REG_REG_MASK_SET_unused2_LSB             8
#define   REG_REG_MASK_SET_unused2_MASK            0xff
#define   REG_REG_MASK_SET_timer_lo_event_LSB      7
#define   REG_REG_MASK_SET_timer_lo_event_MASK     0x1
#define   REG_REG_MASK_SET_reserved_LSB            0
#define   REG_REG_MASK_SET_reserved_MASK           0x7f
#define REG_REG_MASK_CLEAR             0x008
#define   REG_REG_MASK_CLEAR_fc_hp_events_LSB      30
#define   REG_REG_MASK_CLEAR_fc_hp_events_MASK     0x3
#define   REG_REG_MASK_CLEAR_fc_err_events_LSB     29
#define   REG_REG_MASK_CLEAR_fc_err_events_MASK    0x1
#define   REG_REG_MASK_CLEAR_unused1_LSB           24
#define   REG_REG_MASK_CLEAR_unused1_MASK          0x1f
#define   REG_REG_MASK_CLEAR_ref_change_event_LSB  23
#define   REG_REG_MASK_CLEAR_ref_change_event_MASK 0x1
#define   REG_REG_MASK_CLEAR_adv_timer_evens_LSB   19
#define   REG_REG_MASK_CLEAR_adv_timer_evens_MASK  0xf
#define   REG_REG_MASK_CLEAR_gpio_event_LSB        18
#define   REG_REG_MASK_CLEAR_gpio_event_MASK       0x1
#define   REG_REG_MASK_CLEAR_timer_hi_event_LSB    17
#define   REG_REG_MASK_CLEAR_timer_hi_event_MASK   0x1
#define   REG_REG_MASK_CLEAR_timer_lo_event_LSB    16
#define   REG_REG_MASK_CLEAR_timer_lo_event_MASK   0x1
#define   REG_REG_MASK_CLEAR_unused2_LSB           8
#define   REG_REG_MASK_CLEAR_unused2_MASK          0xff
#define   REG_REG_MASK_CLEAR_timer_lo_event_LSB    7
#define   REG_REG_MASK_CLEAR_timer_lo_event_MASK   0x1
#define   REG_REG_MASK_CLEAR_reserved_LSB          0
#define   REG_REG_MASK_CLEAR_reserved_MASK         0x7f
#define REG_REG_INT                    0x00C
#define   REG_REG_INT_fc_hp_events_LSB             30
#define   REG_REG_INT_fc_hp_events_MASK            0x3
#define   REG_REG_INT_fc_err_events_LSB            29
#define   REG_REG_INT_fc_err_events_MASK           0x1
#define   REG_REG_INT_unused1_LSB                  24
#define   REG_REG_INT_unused1_MASK                 0x1f
#define   REG_REG_INT_ref_change_event_LSB         23
#define   REG_REG_INT_ref_change_event_MASK        0x1
#define   REG_REG_INT_adv_timer_evens_LSB          19
#define   REG_REG_INT_adv_timer_evens_MASK         0xf
#define   REG_REG_INT_gpio_event_LSB               18
#define   REG_REG_INT_gpio_event_MASK              0x1
#define   REG_REG_INT_timer_hi_event_LSB           17
#define   REG_REG_INT_timer_hi_event_MASK          0x1
#define   REG_REG_INT_timer_lo_event_LSB           16
#define   REG_REG_INT_timer_lo_event_MASK          0x1
#define   REG_REG_INT_unused2_LSB                  8
#define   REG_REG_INT_unused2_MASK                 0xff
#define   REG_REG_INT_timer_lo_event_LSB           7
#define   REG_REG_INT_timer_lo_event_MASK          0x1
#define   REG_REG_INT_reserved_LSB                 0
#define   REG_REG_INT_reserved_MASK                0x7f
#define REG_REG_INT_SET                0x010
#define   REG_REG_INT_SET_fc_hp_events_LSB         30
#define   REG_REG_INT_SET_fc_hp_events_MASK        0x3
#define   REG_REG_INT_SET_fc_err_events_LSB        29
#define   REG_REG_INT_SET_fc_err_events_MASK       0x1
#define   REG_REG_INT_SET_unused1_LSB              24
#define   REG_REG_INT_SET_unused1_MASK             0x1f
#define   REG_REG_INT_SET_ref_change_event_LSB     23
#define   REG_REG_INT_SET_ref_change_event_MASK    0x1
#define   REG_REG_INT_SET_adv_timer_evens_LSB      19
#define   REG_REG_INT_SET_adv_timer_evens_MASK     0xf
#define   REG_REG_INT_SET_gpio_event_LSB           18
#define   REG_REG_INT_SET_gpio_event_MASK          0x1
#define   REG_REG_INT_SET_timer_hi_event_LSB       17
#define   REG_REG_INT_SET_timer_hi_event_MASK      0x1
#define   REG_REG_INT_SET_timer_lo_event_LSB       16
#define   REG_REG_INT_SET_timer_lo_event_MASK      0x1
#define   REG_REG_INT_SET_unused2_LSB              8
#define   REG_REG_INT_SET_unused2_MASK             0xff
#define   REG_REG_INT_SET_timer_lo_event_LSB       7
#define   REG_REG_INT_SET_timer_lo_event_MASK      0x1
#define   REG_REG_INT_SET_reserved_LSB             0
#define   REG_REG_INT_SET_reserved_MASK            0x7f
#define REG_REG_INT_CLEAR              0x014
#define   REG_REG_INT_CLEAR_fc_hp_events_LSB       30
#define   REG_REG_INT_CLEAR_fc_hp_events_MASK      0x3
#define   REG_REG_INT_CLEAR_fc_err_events_LSB      29
#define   REG_REG_INT_CLEAR_fc_err_events_MASK     0x1
#define   REG_REG_INT_CLEAR_unused1_LSB            24
#define   REG_REG_INT_CLEAR_unused1_MASK           0x1f
#define   REG_REG_INT_CLEAR_ref_change_event_LSB   23
#define   REG_REG_INT_CLEAR_ref_change_event_MASK  0x1
#define   REG_REG_INT_CLEAR_adv_timer_evens_LSB    19
#define   REG_REG_INT_CLEAR_adv_timer_evens_MASK   0xf
#define   REG_REG_INT_CLEAR_gpio_event_LSB         18
#define   REG_REG_INT_CLEAR_gpio_event_MASK        0x1
#define   REG_REG_INT_CLEAR_timer_hi_event_LSB     17
#define   REG_REG_INT_CLEAR_timer_hi_event_MASK    0x1
#define   REG_REG_INT_CLEAR_timer_lo_event_LSB     16
#define   REG_REG_INT_CLEAR_timer_lo_event_MASK    0x1
#define   REG_REG_INT_CLEAR_unused2_LSB            8
#define   REG_REG_INT_CLEAR_unused2_MASK           0xff
#define   REG_REG_INT_CLEAR_timer_lo_event_LSB     7
#define   REG_REG_INT_CLEAR_timer_lo_event_MASK    0x1
#define   REG_REG_INT_CLEAR_reserved_LSB           0
#define   REG_REG_INT_CLEAR_reserved_MASK          0x7f
#define REG_REG_ACK                    0x018
#define   REG_REG_ACK_fc_hp_events_LSB             30
#define   REG_REG_ACK_fc_hp_events_MASK            0x3
#define   REG_REG_ACK_fc_err_events_LSB            29
#define   REG_REG_ACK_fc_err_events_MASK           0x1
#define   REG_REG_ACK_unused1_LSB                  24
#define   REG_REG_ACK_unused1_MASK                 0x1f
#define   REG_REG_ACK_ref_change_event_LSB         23
#define   REG_REG_ACK_ref_change_event_MASK        0x1
#define   REG_REG_ACK_adv_timer_evens_LSB          19
#define   REG_REG_ACK_adv_timer_evens_MASK         0xf
#define   REG_REG_ACK_gpio_event_LSB               18
#define   REG_REG_ACK_gpio_event_MASK              0x1
#define   REG_REG_ACK_timer_hi_event_LSB           17
#define   REG_REG_ACK_timer_hi_event_MASK          0x1
#define   REG_REG_ACK_timer_lo_event_LSB           16
#define   REG_REG_ACK_timer_lo_event_MASK          0x1
#define   REG_REG_ACK_unused2_LSB                  8
#define   REG_REG_ACK_unused2_MASK                 0xff
#define   REG_REG_ACK_timer_lo_event_LSB           7
#define   REG_REG_ACK_timer_lo_event_MASK          0x1
#define   REG_REG_ACK_reserved_LSB                 0
#define   REG_REG_ACK_reserved_MASK                0x7f
#define REG_REG_ACK_SET                0x01C
#define   REG_REG_ACK_SET_fc_hp_events_LSB         30
#define   REG_REG_ACK_SET_fc_hp_events_MASK        0x3
#define   REG_REG_ACK_SET_fc_err_events_LSB        29
#define   REG_REG_ACK_SET_fc_err_events_MASK       0x1
#define   REG_REG_ACK_SET_unused1_LSB              24
#define   REG_REG_ACK_SET_unused1_MASK             0x1f
#define   REG_REG_ACK_SET_ref_change_event_LSB     23
#define   REG_REG_ACK_SET_ref_change_event_MASK    0x1
#define   REG_REG_ACK_SET_adv_timer_evens_LSB      19
#define   REG_REG_ACK_SET_adv_timer_evens_MASK     0xf
#define   REG_REG_ACK_SET_gpio_event_LSB           18
#define   REG_REG_ACK_SET_gpio_event_MASK          0x1
#define   REG_REG_ACK_SET_timer_hi_event_LSB       17
#define   REG_REG_ACK_SET_timer_hi_event_MASK      0x1
#define   REG_REG_ACK_SET_timer_lo_event_LSB       16
#define   REG_REG_ACK_SET_timer_lo_event_MASK      0x1
#define   REG_REG_ACK_SET_unused2_LSB              8
#define   REG_REG_ACK_SET_unused2_MASK             0xff
#define   REG_REG_ACK_SET_timer_lo_event_LSB       7
#define   REG_REG_ACK_SET_timer_lo_event_MASK      0x1
#define   REG_REG_ACK_SET_reserved_LSB             0
#define   REG_REG_ACK_SET_reserved_MASK            0x7f
#define REG_REG_ACK_CLEAR              0x020
#define   REG_REG_ACK_CLEAR_fc_hp_events_LSB       30
#define   REG_REG_ACK_CLEAR_fc_hp_events_MASK      0x3
#define   REG_REG_ACK_CLEAR_fc_err_events_LSB      29
#define   REG_REG_ACK_CLEAR_fc_err_events_MASK     0x1
#define   REG_REG_ACK_CLEAR_unused1_LSB            24
#define   REG_REG_ACK_CLEAR_unused1_MASK           0x1f
#define   REG_REG_ACK_CLEAR_ref_change_event_LSB   23
#define   REG_REG_ACK_CLEAR_ref_change_event_MASK  0x1
#define   REG_REG_ACK_CLEAR_adv_timer_evens_LSB    19
#define   REG_REG_ACK_CLEAR_adv_timer_evens_MASK   0xf
#define   REG_REG_ACK_CLEAR_gpio_event_LSB         18
#define   REG_REG_ACK_CLEAR_gpio_event_MASK        0x1
#define   REG_REG_ACK_CLEAR_timer_hi_event_LSB     17
#define   REG_REG_ACK_CLEAR_timer_hi_event_MASK    0x1
#define   REG_REG_ACK_CLEAR_timer_lo_event_LSB     16
#define   REG_REG_ACK_CLEAR_timer_lo_event_MASK    0x1
#define   REG_REG_ACK_CLEAR_unused2_LSB            8
#define   REG_REG_ACK_CLEAR_unused2_MASK           0xff
#define   REG_REG_ACK_CLEAR_timer_lo_event_LSB     7
#define   REG_REG_ACK_CLEAR_timer_lo_event_MASK    0x1
#define   REG_REG_ACK_CLEAR_reserved_LSB           0
#define   REG_REG_ACK_CLEAR_reserved_MASK          0x7f
#define REG_REG_FIFO                   0x024
#define   REG_REG_FIFO_EVENT_ID_LSB                0
#define   REG_REG_FIFO_EVENT_ID_MASK               0xff

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

#endif // __APB_INTERRUPT_CNTRL_H_
