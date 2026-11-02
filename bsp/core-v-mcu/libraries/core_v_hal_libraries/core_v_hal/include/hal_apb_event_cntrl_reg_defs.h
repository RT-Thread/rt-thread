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

#ifndef __APB_EVENT_CNTRL_H_
#define __APB_EVENT_CNTRL_H_

//---------------------------------//
//
// Module: APB_EVENT_CNTRL
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
    __IO uint32_t apb_events;
    struct {
      __IO uint32_t  apb_event  : 16;
    } apb_events_b;
  };

  // Offset = 0x0004
  union {
    __IO uint32_t event_mask0;
    struct {
      __IO uint32_t             : 30;
      __IO uint32_t  event_enable :  2;
    } event_mask0_b;
  };

  // Offset = 0x0008
  union {
    __IO uint32_t event_mask1;
    struct {
      __IO uint32_t             : 30;
      __IO uint32_t  event_enable :  2;
    } event_mask1_b;
  };

  // Offset = 0x000c
  union {
    __IO uint32_t event_mask2;
    struct {
      __IO uint32_t             : 30;
      __IO uint32_t  event_enable :  2;
    } event_mask2_b;
  };

  // Offset = 0x0010
  union {
    __IO uint32_t event_mask3;
    struct {
      __IO uint32_t             : 30;
      __IO uint32_t  event_enable :  2;
    } event_mask3_b;
  };

  // Offset = 0x0014
  union {
    __IO uint32_t event_mask4;
    struct {
      __IO uint32_t             : 30;
      __IO uint32_t  event_enable :  2;
    } event_mask4_b;
  };

  // Offset = 0x0018
  union {
    __IO uint32_t event_mask5;
    struct {
      __IO uint32_t             : 30;
      __IO uint32_t  event_enable :  2;
    } event_mask5_b;
  };

  // Offset = 0x001c
  union {
    __IO uint32_t event_mask6;
    struct {
      __IO uint32_t             : 30;
      __IO uint32_t  event_enable :  2;
    } event_mask6_b;
  };

  // Offset = 0x0020
  union {
    __IO uint32_t event_mask7;
    struct {
      __IO uint32_t             : 30;
      __IO uint32_t  event_enable :  2;
    } event_mask7_b;
  };
  __I uint32_t    unused0[16];

  // Offset = 0x0064
  union {
    __IO uint32_t event_err0;
    struct {
      __IO uint32_t             : 30;
      __IO uint32_t  event_err  :  2;
    } event_err0_b;
  };

  // Offset = 0x0068
  union {
    __IO uint32_t event_err1;
    struct {
      __IO uint32_t             : 30;
      __IO uint32_t  event_enable :  2;
    } event_err1_b;
  };

  // Offset = 0x006c
  union {
    __IO uint32_t event_err2;
    struct {
      __IO uint32_t             : 30;
      __IO uint32_t  event_enable :  2;
    } event_err2_b;
  };

  // Offset = 0x0070
  union {
    __IO uint32_t event_err3;
    struct {
      __IO uint32_t             : 30;
      __IO uint32_t  event_enable :  2;
    } event_err3_b;
  };

  // Offset = 0x0074
  union {
    __IO uint32_t event_err4;
    struct {
      __IO uint32_t             : 30;
      __IO uint32_t  event_enable :  2;
    } event_err4_b;
  };

  // Offset = 0x0078
  union {
    __IO uint32_t event_err5;
    struct {
      __IO uint32_t             : 30;
      __IO uint32_t  event_enable :  2;
    } event_err5_b;
  };

  // Offset = 0x007c
  union {
    __IO uint32_t event_err6;
    struct {
      __IO uint32_t             : 30;
      __IO uint32_t  event_enable :  2;
    } event_err6_b;
  };

  // Offset = 0x0080
  union {
    __IO uint32_t event_err7;
    struct {
      __IO uint32_t             : 30;
      __IO uint32_t  event_enable :  2;
    } event_err7_b;
  };

  // Offset = 0x0084
  union {
    __IO uint32_t timer_lo_event;
    struct {
      __IO uint32_t  event      :  8;
    } timer_lo_event_b;
  };

  // Offset = 0x0088
  union {
    __IO uint32_t timer_hi_event;
    struct {
      __IO uint32_t  event      :  8;
    } timer_hi_event_b;
  };
  __I uint32_t    unused1[1];

  // Offset = 0x0090
  union {
    __IO uint32_t event_fifo;
    struct {
      __IO uint32_t  event_id   :  8;
    } event_fifo_b;
  };
} ApbEventCntrl_t;


#define REG_APB_EVENTS                 0x000
#define   REG_APB_EVENTS_apb_event_LSB             0
#define   REG_APB_EVENTS_apb_event_MASK            0xffff
#define REG_EVENT_MASK0                0x004
#define   REG_EVENT_MASK0_event_enable_LSB         30
#define   REG_EVENT_MASK0_event_enable_MASK        0x3
#define REG_EVENT_MASK1                0x008
#define   REG_EVENT_MASK1_event_enable_LSB         30
#define   REG_EVENT_MASK1_event_enable_MASK        0x3
#define REG_EVENT_MASK2                0x00C
#define   REG_EVENT_MASK2_event_enable_LSB         30
#define   REG_EVENT_MASK2_event_enable_MASK        0x3
#define REG_EVENT_MASK3                0x010
#define   REG_EVENT_MASK3_event_enable_LSB         30
#define   REG_EVENT_MASK3_event_enable_MASK        0x3
#define REG_EVENT_MASK4                0x014
#define   REG_EVENT_MASK4_event_enable_LSB         30
#define   REG_EVENT_MASK4_event_enable_MASK        0x3
#define REG_EVENT_MASK5                0x018
#define   REG_EVENT_MASK5_event_enable_LSB         30
#define   REG_EVENT_MASK5_event_enable_MASK        0x3
#define REG_EVENT_MASK6                0x01C
#define   REG_EVENT_MASK6_event_enable_LSB         30
#define   REG_EVENT_MASK6_event_enable_MASK        0x3
#define REG_EVENT_MASK7                0x020
#define   REG_EVENT_MASK7_event_enable_LSB         30
#define   REG_EVENT_MASK7_event_enable_MASK        0x3
#define REG_EVENT_ERR0                 0x064
#define   REG_EVENT_ERR0_event_err_LSB             30
#define   REG_EVENT_ERR0_event_err_MASK            0x3
#define REG_EVENT_ERR1                 0x068
#define   REG_EVENT_ERR1_event_enable_LSB          30
#define   REG_EVENT_ERR1_event_enable_MASK         0x3
#define REG_EVENT_ERR2                 0x06C
#define   REG_EVENT_ERR2_event_enable_LSB          30
#define   REG_EVENT_ERR2_event_enable_MASK         0x3
#define REG_EVENT_ERR3                 0x070
#define   REG_EVENT_ERR3_event_enable_LSB          30
#define   REG_EVENT_ERR3_event_enable_MASK         0x3
#define REG_EVENT_ERR4                 0x074
#define   REG_EVENT_ERR4_event_enable_LSB          30
#define   REG_EVENT_ERR4_event_enable_MASK         0x3
#define REG_EVENT_ERR5                 0x078
#define   REG_EVENT_ERR5_event_enable_LSB          30
#define   REG_EVENT_ERR5_event_enable_MASK         0x3
#define REG_EVENT_ERR6                 0x07C
#define   REG_EVENT_ERR6_event_enable_LSB          30
#define   REG_EVENT_ERR6_event_enable_MASK         0x3
#define REG_EVENT_ERR7                 0x080
#define   REG_EVENT_ERR7_event_enable_LSB          30
#define   REG_EVENT_ERR7_event_enable_MASK         0x3
#define REG_TIMER_LO_EVENT             0x0084
#define   REG_TIMER_LO_EVENT_event_LSB             0
#define   REG_TIMER_LO_EVENT_event_MASK            0xff
#define REG_TIMER_HI_EVENT             0x0088
#define   REG_TIMER_HI_EVENT_event_LSB             0
#define   REG_TIMER_HI_EVENT_event_MASK            0xff
#define REG_EVENT_FIFO                 0x090
#define   REG_EVENT_FIFO_EVENT_ID_LSB              0
#define   REG_EVENT_FIFO_EVENT_ID_MASK             0xff

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

#endif // __APB_EVENT_CNTRL_H_
