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

#ifndef __SOC_CTRL_H_
#define __SOC_CTRL_H_

//---------------------------------//
//
// Module: SOC_CTRL
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
    __IO uint32_t info;
    struct {
      __IO uint32_t  n_clusters : 16;
      __IO uint32_t  n_cores    : 16;
    } info_b;
  };
  __I uint32_t    unused0[2];

  // Offset = 0x000c
  union {
    __IO uint32_t build_date;
    struct {
      __IO uint32_t  day        :  8;
      __IO uint32_t  month      :  8;
      __IO uint32_t  year       : 16;
    } build_date_b;
  };

  // Offset = 0x0010
  union {
    __IO uint32_t build_time;
    struct {
      __IO uint32_t  seconds    :  8;
      __IO uint32_t  minutes    :  8;
      __IO uint32_t  hour       :  8;
    } build_time_b;
  };
  __I uint32_t    unused1[24];

  // Offset = 0x0074
  union {
    __IO uint32_t jtagreg;
  };
  __I uint32_t    unused2[10];

  // Offset = 0x00a0
  union {
    __IO uint32_t corestatus;
    struct {
      __IO uint32_t  status     : 31;
      __IO uint32_t  eoc        :  1;
    } corestatus_b;
  };
  __I uint32_t    unused3[7];

  // Offset = 0x00c0
  union {
    __IO uint32_t cs_ro;
    struct {
      __IO uint32_t  status     : 31;
      __IO uint32_t  eoc        :  1;
    } cs_ro_b;
  };

  // Offset = 0x00c4
  union {
    __IO uint32_t bootsel;
  };

  // Offset = 0x00c8
  union {
    __IO uint32_t clksel;
  };
  __I uint32_t    unused4[3];

  // Offset = 0x00d8
  union {
    __IO uint32_t clk_div_clu;
  };
  __I uint32_t    unused5[1];

  // Offset = 0x00e0
  union {
    __IO uint32_t sel_clk_dc_fifo_efpga;
  };

  // Offset = 0x00e4
  union {
    __IO uint32_t clk_gating_dc_fifo_efpga;
  };

  // Offset = 0x00e8
  union {
    __IO uint32_t reset_type1_efpga;
  };

  // Offset = 0x00ec
  union {
    __IO uint32_t enable_in_out_efpga;
  };
  __I uint32_t    unused6[196];

  // Offset = 0x0400
  union {
    __IO uint32_t io_ctrl[48];
    struct {
      __IO uint32_t  mux        :  2;
      __IO uint32_t             :  6;
      __IO uint32_t  cfg        :  6;
    } io_ctrl_b[48];
  };
} SocCtrl_t;


#define REG_INFO                       0x0000
#define   REG_INFO_N_CORES_LSB                     16
#define   REG_INFO_N_CORES_MASK                    0xffff
#define   REG_INFO_N_CLUSTERS_LSB                  0
#define   REG_INFO_N_CLUSTERS_MASK                 0xffff
#define REG_BUILD_DATE                 0x000C
#define   REG_BUILD_DATE_YEAR_LSB                  16
#define   REG_BUILD_DATE_YEAR_MASK                 0xffff
#define   REG_BUILD_DATE_MONTH_LSB                 8
#define   REG_BUILD_DATE_MONTH_MASK                0xff
#define   REG_BUILD_DATE_DAY_LSB                   0
#define   REG_BUILD_DATE_DAY_MASK                  0xff
#define REG_BUILD_TIME                 0x0010
#define   REG_BUILD_TIME_HOUR_LSB                  16
#define   REG_BUILD_TIME_HOUR_MASK                 0xff
#define   REG_BUILD_TIME_MINUTES_LSB               8
#define   REG_BUILD_TIME_MINUTES_MASK              0xff
#define   REG_BUILD_TIME_SECONDS_LSB               0
#define   REG_BUILD_TIME_SECONDS_MASK              0xff
#define REG_JTAGREG                    0x0074
#define REG_CORESTATUS                 0x00A0
#define   REG_CORESTATUS_EOC_LSB                   31
#define   REG_CORESTATUS_EOC_MASK                  0x1
#define   REG_CORESTATUS_STATUS_LSB                0
#define   REG_CORESTATUS_STATUS_MASK               0x7fffffff
#define REG_CS_RO                      0x00C0
#define   REG_CS_RO_EOC_LSB                        31
#define   REG_CS_RO_EOC_MASK                       0x1
#define   REG_CS_RO_STATUS_LSB                     0
#define   REG_CS_RO_STATUS_MASK                    0x7fffffff
#define REG_BOOTSEL                    0x00C4
#define REG_CLKSEL                     0x00C8
#define REG_CLK_DIV_CLU                0x00D8
#define REG_SEL_CLK_DC_FIFO_EFPGA      0x00E0
#define REG_CLK_GATING_DC_FIFO_EFPGA   0x00E4
#define REG_RESET_TYPE1_EFPGA          0x00E8
#define REG_ENABLE_IN_OUT_EFPGA        0x00EC
#define REG_IO_CTRL                    0x0400
#define   REG_IO_CTRL_CFG_LSB                      8
#define   REG_IO_CTRL_CFG_MASK                     0x3f
#define   REG_IO_CTRL_MUX_LSB                      0
#define   REG_IO_CTRL_MUX_MASK                     0x3

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

#endif // __SOC_CTRL_H_
