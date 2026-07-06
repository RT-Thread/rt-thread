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

  // Offset = 0x0014
  union {
    __IO uint32_t io_cfg0;
    struct {
      __IO uint32_t  n_io       :  8;
      __IO uint32_t  n_sysio    :  8;
      __IO uint32_t  n_gpio     :  8;
    } io_cfg0_b;
  };

  // Offset = 0x0018
  union {
    __IO uint32_t io_cfg1;
    struct {
      __IO uint32_t  nbit_padcfg :  8;
      __IO uint32_t  nbit_padmux :  8;
    } io_cfg1_b;
  };
  __I uint32_t    unused1[1];

  // Offset = 0x0020
  union {
    __IO uint32_t per_cfg0;
    struct {
      __IO uint32_t  n_uart     :  8;
      __IO uint32_t  n_qspim    :  8;
      __IO uint32_t  n_i2cm     :  8;
      __IO uint32_t  n_i2sc     :  8;
    } per_cfg0_b;
  };

  // Offset = 0x0024
  union {
    __IO uint32_t per_cfg1;
    struct {
      __IO uint32_t  n_sdio     :  8;
      __IO uint32_t  n_cam      :  8;
    } per_cfg1_b;
  };
  __I uint32_t    unused2[19];

  // Offset = 0x0074
  union {
    __IO uint32_t jtagreg;
  };
  __I uint32_t    unused3[10];

  // Offset = 0x00a0
  union {
    __IO uint32_t corestatus;
    struct {
      __IO uint32_t  status     : 31;
      __IO uint32_t  eoc        :  1;
    } corestatus_b;
  };
  __I uint32_t    unused4[7];

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
  __I uint32_t    unused5[3];

  // Offset = 0x00d8
  union {
    __IO uint32_t clk_div_clu;
  };
  __I uint32_t    unused6[1];

  // Offset = 0x00e0
  union {
    __IO uint32_t rto_peripheral_error;
    struct {
      __IO uint32_t  fll_rto    :  1;
      __IO uint32_t  gpio_rto   :  1;
      __IO uint32_t  udma_rto   :  1;
      __IO uint32_t  soc_control_rto :  1;
      __IO uint32_t  adv_timer_rto :  1;
      __IO uint32_t  event_gen_rto :  1;
      __IO uint32_t  i2cs_rto   :  1;
      __IO uint32_t  timer_rto  :  1;
      __IO uint32_t  fcb_rto    :  1;
    } rto_peripheral_error_b;
  };

  // Offset = 0x00e4
  union {
    __IO uint32_t ready_timeout_count;
    struct {
      __IO uint32_t  count      : 20;
    } ready_timeout_count_b;
  };

  // Offset = 0x00e8
  union {
    __IO uint32_t reset_type1_efpga;
    struct {
      __IO uint32_t  reset_lt   :  1;
      __IO uint32_t  reset_rt   :  1;
      __IO uint32_t  reset_rb   :  1;
      __IO uint32_t  reset_lb   :  1;
    } reset_type1_efpga_b;
  };

  // Offset = 0x00ec
  union {
    __IO uint32_t enable_in_out_efpga;
    struct {
      __IO uint32_t  enable_tcdm_p0 :  1;
      __IO uint32_t  enable_tcdm_p1 :  1;
      __IO uint32_t  enable_tcdm_p2 :  1;
      __IO uint32_t  enable_tcdm_p3 :  1;
      __IO uint32_t  enable_soc_access :  1;
      __IO uint32_t  enable_events :  1;
    } enable_in_out_efpga_b;
  };

  // Offset = 0x00f0
  union {
    __IO uint32_t efpga_control_in;
  };

  // Offset = 0x00f4
  union {
    __IO uint32_t efpga_status_out;
  };

  // Offset = 0x00f8
  union {
    __IO uint32_t efpga_version;
  };

  // Offset = 0x00fc
  union {
    __IO uint32_t soft_reset;
  };
  __I uint32_t    unused7[192];

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
#define REG_IO_CFG0                    0x0014
#define   REG_IO_CFG0_N_GPIO_LSB                   16
#define   REG_IO_CFG0_N_GPIO_MASK                  0xff
#define   REG_IO_CFG0_N_SYSIO_LSB                  8
#define   REG_IO_CFG0_N_SYSIO_MASK                 0xff
#define   REG_IO_CFG0_N_IO_LSB                     0
#define   REG_IO_CFG0_N_IO_MASK                    0xff
#define REG_IO_CFG1                    0x0018
#define   REG_IO_CFG1_NBIT_PADMUX_LSB              8
#define   REG_IO_CFG1_NBIT_PADMUX_MASK             0xff
#define   REG_IO_CFG1_NBIT_PADCFG_LSB              0
#define   REG_IO_CFG1_NBIT_PADCFG_MASK             0xff
#define REG_PER_CFG0                   0x0020
#define   REG_PER_CFG0_N_I2SC_LSB                  24
#define   REG_PER_CFG0_N_I2SC_MASK                 0xff
#define   REG_PER_CFG0_N_I2CM_LSB                  16
#define   REG_PER_CFG0_N_I2CM_MASK                 0xff
#define   REG_PER_CFG0_N_QSPIM_LSB                 8
#define   REG_PER_CFG0_N_QSPIM_MASK                0xff
#define   REG_PER_CFG0_N_UART_LSB                  0
#define   REG_PER_CFG0_N_UART_MASK                 0xff
#define REG_PER_CFG1                   0x0024
#define   REG_PER_CFG1_N_CAM_LSB                   8
#define   REG_PER_CFG1_N_CAM_MASK                  0xff
#define   REG_PER_CFG1_N_SDIO_LSB                  0
#define   REG_PER_CFG1_N_SDIO_MASK                 0xff
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
#define REG_RTO_PERIPHERAL_ERROR       0x00E0
#define   REG_RTO_PERIPHERAL_ERROR_FCB_RTO_LSB     8
#define   REG_RTO_PERIPHERAL_ERROR_FCB_RTO_MASK    0x1
#define   REG_RTO_PERIPHERAL_ERROR_TIMER_RTO_LSB   7
#define   REG_RTO_PERIPHERAL_ERROR_TIMER_RTO_MASK  0x1
#define   REG_RTO_PERIPHERAL_ERROR_I2CS_RTO_LSB    6
#define   REG_RTO_PERIPHERAL_ERROR_I2CS_RTO_MASK   0x1
#define   REG_RTO_PERIPHERAL_ERROR_EVENT_GEN_RTO_LSB 5
#define   REG_RTO_PERIPHERAL_ERROR_EVENT_GEN_RTO_MASK 0x1
#define   REG_RTO_PERIPHERAL_ERROR_ADV_TIMER_RTO_LSB 4
#define   REG_RTO_PERIPHERAL_ERROR_ADV_TIMER_RTO_MASK 0x1
#define   REG_RTO_PERIPHERAL_ERROR_SOC_CONTROL_RTO_LSB 3
#define   REG_RTO_PERIPHERAL_ERROR_SOC_CONTROL_RTO_MASK 0x1
#define   REG_RTO_PERIPHERAL_ERROR_UDMA_RTO_LSB    2
#define   REG_RTO_PERIPHERAL_ERROR_UDMA_RTO_MASK   0x1
#define   REG_RTO_PERIPHERAL_ERROR_GPIO_RTO_LSB    1
#define   REG_RTO_PERIPHERAL_ERROR_GPIO_RTO_MASK   0x1
#define   REG_RTO_PERIPHERAL_ERROR_FLL_RTO_LSB     0
#define   REG_RTO_PERIPHERAL_ERROR_FLL_RTO_MASK    0x1
#define REG_READY_TIMEOUT_COUNT        0x00E4
#define   REG_READY_TIMEOUT_COUNT_COUNT_LSB        0
#define   REG_READY_TIMEOUT_COUNT_COUNT_MASK       0xfffff
#define REG_RESET_TYPE1_EFPGA          0x00E8
#define   REG_RESET_TYPE1_EFPGA_RESET_LB_LSB       3
#define   REG_RESET_TYPE1_EFPGA_RESET_LB_MASK      0x1
#define   REG_RESET_TYPE1_EFPGA_RESET_RB_LSB       2
#define   REG_RESET_TYPE1_EFPGA_RESET_RB_MASK      0x1
#define   REG_RESET_TYPE1_EFPGA_RESET_RT_LSB       1
#define   REG_RESET_TYPE1_EFPGA_RESET_RT_MASK      0x1
#define   REG_RESET_TYPE1_EFPGA_RESET_LT_LSB       0
#define   REG_RESET_TYPE1_EFPGA_RESET_LT_MASK      0x1
#define REG_ENABLE_IN_OUT_EFPGA        0x00EC
#define   REG_ENABLE_IN_OUT_EFPGA_ENABLE_EVENTS_LSB 5
#define   REG_ENABLE_IN_OUT_EFPGA_ENABLE_EVENTS_MASK 0x1
#define   REG_ENABLE_IN_OUT_EFPGA_ENABLE_SOC_ACCESS_LSB 4
#define   REG_ENABLE_IN_OUT_EFPGA_ENABLE_SOC_ACCESS_MASK 0x1
#define   REG_ENABLE_IN_OUT_EFPGA_ENABLE_TCDM_P3_LSB 3
#define   REG_ENABLE_IN_OUT_EFPGA_ENABLE_TCDM_P3_MASK 0x1
#define   REG_ENABLE_IN_OUT_EFPGA_ENABLE_TCDM_P2_LSB 2
#define   REG_ENABLE_IN_OUT_EFPGA_ENABLE_TCDM_P2_MASK 0x1
#define   REG_ENABLE_IN_OUT_EFPGA_ENABLE_TCDM_P1_LSB 1
#define   REG_ENABLE_IN_OUT_EFPGA_ENABLE_TCDM_P1_MASK 0x1
#define   REG_ENABLE_IN_OUT_EFPGA_ENABLE_TCDM_P0_LSB 0
#define   REG_ENABLE_IN_OUT_EFPGA_ENABLE_TCDM_P0_MASK 0x1
#define REG_EFPGA_CONTROL_IN           0x00F0
#define REG_EFPGA_STATUS_OUT           0x00F4
#define REG_EFPGA_VERSION              0x00F8
#define REG_SOFT_RESET                 0x00FC
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
