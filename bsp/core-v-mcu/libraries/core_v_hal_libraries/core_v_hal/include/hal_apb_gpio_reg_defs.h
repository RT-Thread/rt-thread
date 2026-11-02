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

#ifndef __APB_GPIO_H_
#define __APB_GPIO_H_

//---------------------------------//
//
// Module: APB_GPIO
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
    __IO uint32_t setgpio;
    struct {
      __IO uint32_t  gpio_num   :  8;
    } setgpio_b;
  };

  // Offset = 0x0004
  union {
    __IO uint32_t clrgpio;
    struct {
      __IO uint32_t  gpio_num   :  8;
    } clrgpio_b;
  };

  // Offset = 0x0008
  union {
    __IO uint32_t toggpio;
    struct {
      __IO uint32_t  gpio_num   :  8;
    } toggpio_b;
  };
  __I uint32_t    unused0[1];

  // Offset = 0x0010
  union {
    __IO uint32_t pin0;
    struct {
      __IO uint32_t  gpio_value : 32;
    } pin0_b;
  };

  // Offset = 0x0014
  union {
    __IO uint32_t pin1;
    struct {
      __IO uint32_t  gpio_value : 32;
    } pin1_b;
  };

  // Offset = 0x0018
  union {
    __IO uint32_t pin2;
    struct {
      __IO uint32_t  gpio_value : 32;
    } pin2_b;
  };

  // Offset = 0x001c
  union {
    __IO uint32_t pin3;
    struct {
      __IO uint32_t  gpio_value : 32;
    } pin3_b;
  };

  // Offset = 0x0020
  union {
    __IO uint32_t out0;
    struct {
      __IO uint32_t  value      : 32;
    } out0_b;
  };

  // Offset = 0x0024
  union {
    __IO uint32_t out1;
    struct {
      __IO uint32_t  value      : 32;
    } out1_b;
  };

  // Offset = 0x0028
  union {
    __IO uint32_t out2;
    struct {
      __IO uint32_t  value      : 32;
    } out2_b;
  };

  // Offset = 0x002c
  union {
    __IO uint32_t out3;
    struct {
      __IO uint32_t  value      : 32;
    } out3_b;
  };

  // Offset = 0x0030
  union {
    __IO uint32_t setsel;
    struct {
      __IO uint32_t  gpio_num   :  8;
    } setsel_b;
  };

  // Offset = 0x0034
  union {
    __IO uint32_t rdstat;
    struct {
      __IO uint32_t  gpio_sel   :  8;
      __IO uint32_t  output     :  1;
      __IO uint32_t             :  3;
      __IO uint32_t  input      :  1;
      __IO uint32_t             :  3;
      __IO uint32_t  inten      :  1;
      __IO uint32_t  inttype    :  3;
      __IO uint32_t             :  4;
      __IO uint32_t  mode       :  2;
    } rdstat_b;
  };

  // Offset = 0x0038
  union {
    __IO uint32_t setmode;
    struct {
      __IO uint32_t  gpio_num   :  8;
      __IO uint32_t             : 16;
      __IO uint32_t  mode       :  2;
    } setmode_b;
  };

  // Offset = 0x003c
  union {
    __IO uint32_t setint;
    struct {
      __IO uint32_t  gpio_num   :  8;
      __IO uint32_t             :  8;
      __IO uint32_t  intenable  :  1;
      __IO uint32_t  inttype    :  3;
    } setint_b;
  };
  union {
     __IO uint32_t intack;
     struct {
       __IO uint32_t  gpio_num   :  8;
       __IO uint32_t             :  24;
     } intack_b;
  };
} ApbGpio_t;


#define REG_SETGPIO                    0x00
#define   REG_SETGPIO_gpio_num_LSB                 0
#define   REG_SETGPIO_gpio_num_MASK                0xff
#define REG_CLRGPIO                    0x04
#define   REG_CLRGPIO_gpio_num_LSB                 0
#define   REG_CLRGPIO_gpio_num_MASK                0xff
#define REG_TOGGPIO                    0x08
#define   REG_TOGGPIO_gpio_num_LSB                 0
#define   REG_TOGGPIO_gpio_num_MASK                0xff
#define REG_PIN0                       0x10
#define   REG_PIN0_gpio_value_LSB                  0
#define   REG_PIN0_gpio_value_MASK                 0xffffffff
#define REG_PIN1                       0x14
#define   REG_PIN1_gpio_value_LSB                  0
#define   REG_PIN1_gpio_value_MASK                 0xffffffff
#define REG_PIN2                       0x18
#define   REG_PIN2_gpio_value_LSB                  0
#define   REG_PIN2_gpio_value_MASK                 0xffffffff
#define REG_PIN3                       0x1C
#define   REG_PIN3_gpio_value_LSB                  0
#define   REG_PIN3_gpio_value_MASK                 0xffffffff
#define REG_OUT0                       0x20
#define   REG_OUT0_value_LSB                       0
#define   REG_OUT0_value_MASK                      0xffffffff
#define REG_OUT1                       0x24
#define   REG_OUT1_value_LSB                       0
#define   REG_OUT1_value_MASK                      0xffffffff
#define REG_OUT2                       0x28
#define   REG_OUT2_value_LSB                       0
#define   REG_OUT2_value_MASK                      0xffffffff
#define REG_OUT3                       0x2C
#define   REG_OUT3_value_LSB                       0
#define   REG_OUT3_value_MASK                      0xffffffff
#define REG_SETSEL                     0x30
#define   REG_SETSEL_gpio_num_LSB                  0
#define   REG_SETSEL_gpio_num_MASK                 0xff
#define REG_RDSTAT                     0x34
#define   REG_RDSTAT_mode_LSB                      24
#define   REG_RDSTAT_mode_MASK                     0x3
#define   REG_RDSTAT_INTTYPE_LSB                   16
#define   REG_RDSTAT_INTTYPE_MASK                  0x7
#define   REG_RDSTAT_INPUT_LSB                     12
#define   REG_RDSTAT_INPUT_MASK                    0x1
#define   REG_RDSTAT_OUTPUT_LSB                    8
#define   REG_RDSTAT_OUTPUT_MASK                   0x1
#define REG_SETMODE                    0x38
#define   REG_SETMODE_mode_LSB                     24
#define   REG_SETMODE_mode_MASK                    0x3
#define   REG_SETMODE_gpio_num_LSB                 0
#define   REG_SETMODE_gpio_num_MASK                0xff
#define REG_SETINT                     0x3C
#define   REG_SETINT_INTTYPE_LSB                   17
#define   REG_SETINT_INTTYPE_MASK                  0x7
#define   REG_SETINT_INTENABLE_LSB                 16
#define   REG_SETINT_INTENABLE_MASK                0x1
#define   REG_SETINT_gpio_num_LSB                  0
#define   REG_SETINT_gpio_num_MASK                 0xff

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

#endif // __APB_GPIO_H_
