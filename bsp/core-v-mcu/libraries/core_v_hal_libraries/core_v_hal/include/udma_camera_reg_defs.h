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

#ifndef __UDMA_CAMERA_H_
#define __UDMA_CAMERA_H_

//---------------------------------//
//
// Module: UDMA_CAMERA
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
      __IO uint32_t  saddr      : 32;
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
      __IO uint32_t  datasize   :  2;
      __IO uint32_t             :  1;
      __IO uint32_t  en         :  1;
      __IO uint32_t  pending    :  1;
      __IO uint32_t  clr        :  1;
    } rx_cfg_b;
  };
  __I uint32_t    unused0[5];

  // Offset = 0x0020
  union {
    __IO uint32_t cfg_glob;
    struct {
      __IO uint32_t  framedrop_en :  1;
      __IO uint32_t  framedrop_val :  6;
      __IO uint32_t  framewindow_en :  1;
      __IO uint32_t  format     :  3;
      __IO uint32_t  shift      :  4;
      __IO uint32_t             : 16;
      __IO uint32_t  en         :  1;
    } cfg_glob_b;
  };

  // Offset = 0x0024
  union {
    __IO uint32_t cfg_ll;
    struct {
      __IO uint32_t  framewindow_llx : 16;
      __IO uint32_t  framewindow_lly : 16;
    } cfg_ll_b;
  };

  // Offset = 0x0028
  union {
    __IO uint32_t cfg_ur;
    struct {
      __IO uint32_t  framewindow_urx : 16;
      __IO uint32_t  framewindow_ury : 16;
    } cfg_ur_b;
  };

  // Offset = 0x002c
  union {
    __IO uint32_t cfg_size;
    struct {
      __IO uint32_t             : 16;
      __IO uint32_t  rowlen     : 16;
    } cfg_size_b;
  };

  // Offset = 0x0030
  union {
    __IO uint32_t cfg_filter;
    struct {
      __IO uint32_t             :  8;
      __IO uint32_t  b_coeff    :  8;
      __IO uint32_t  g_coeff    :  8;
      __IO uint32_t  r_coeff    :  8;
    } cfg_filter_b;
  };

  // Offset = 0x0034
  union {
    __IO uint32_t vsync_polarity;
    struct {
      __IO uint32_t  vsync_polarity :  1;
    } vsync_polarity_b;
  };
} UdmaCamera_t;


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
#define REG_CFG_GLOB                   0x20
#define   REG_CFG_GLOB_EN_LSB                      31
#define   REG_CFG_GLOB_EN_MASK                     0x1
#define   REG_CFG_GLOB_SHIFT_LSB                   11
#define   REG_CFG_GLOB_SHIFT_MASK                  0xf
#define   REG_CFG_GLOB_FORMAT_LSB                  8
#define   REG_CFG_GLOB_FORMAT_MASK                 0x7
#define   REG_CFG_GLOB_FRAMEWINDOW_EN_LSB          7
#define   REG_CFG_GLOB_FRAMEWINDOW_EN_MASK         0x1
#define   REG_CFG_GLOB_FRAMEDROP_VAL_LSB           1
#define   REG_CFG_GLOB_FRAMEDROP_VAL_MASK          0x3f
#define   REG_CFG_GLOB_FRAMEDROP_EN_LSB            0
#define   REG_CFG_GLOB_FRAMEDROP_EN_MASK           0x1
#define REG_CFG_LL                     0x24
#define   REG_CFG_LL_FRAMEWINDOW_LLY_LSB           16
#define   REG_CFG_LL_FRAMEWINDOW_LLY_MASK          0xffff
#define   REG_CFG_LL_FRAMEWINDOW_LLX_LSB           0
#define   REG_CFG_LL_FRAMEWINDOW_LLX_MASK          0xffff
#define REG_CFG_UR                     0x28
#define   REG_CFG_UR_FRAMEWINDOW_URY_LSB           16
#define   REG_CFG_UR_FRAMEWINDOW_URY_MASK          0xffff
#define   REG_CFG_UR_FRAMEWINDOW_URX_LSB           0
#define   REG_CFG_UR_FRAMEWINDOW_URX_MASK          0xffff
#define REG_CFG_SIZE                   0x2C
#define   REG_CFG_SIZE_ROWLEN_LSB                  16
#define   REG_CFG_SIZE_ROWLEN_MASK                 0xffff
#define REG_CFG_FILTER                 0x30
#define   REG_CFG_FILTER_R_COEFF_LSB               16
#define   REG_CFG_FILTER_R_COEFF_MASK              0xff
#define   REG_CFG_FILTER_G_COEFF_LSB               8
#define   REG_CFG_FILTER_G_COEFF_MASK              0xff
#define   REG_CFG_FILTER_B_COEFF_LSB               8
#define   REG_CFG_FILTER_B_COEFF_MASK              0xff
#define REG_VSYNC_POLARITY             0x34
#define   REG_VSYNC_POLARITY_VSYNC_POLARITY_LSB    0
#define   REG_VSYNC_POLARITY_VSYNC_POLARITY_MASK   0x1

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

#endif // __UDMA_CAMERA_H_
