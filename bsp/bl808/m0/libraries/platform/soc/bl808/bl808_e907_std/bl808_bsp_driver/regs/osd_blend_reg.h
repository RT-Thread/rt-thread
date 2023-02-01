/**
  ******************************************************************************
  * @file    osd_blend_reg.h
  * @version V1.0
  * @date    2021-06-28
  * @brief   This file is the description of.IP register
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __OSD_BLEND_REG_H__
#define __OSD_BLEND_REG_H__

#include "bl808.h"

/* 0x0 : obnd_layer_xconfig */
#define OSD_BLEND_OBND_LAYER_XCONFIG_OFFSET (0x0)
#define OSD_BLEND_OBND_X_MIN                OSD_BLEND_OBND_X_MIN
#define OSD_BLEND_OBND_X_MIN_POS            (0U)
#define OSD_BLEND_OBND_X_MIN_LEN            (11U)
#define OSD_BLEND_OBND_X_MIN_MSK            (((1U << OSD_BLEND_OBND_X_MIN_LEN) - 1) << OSD_BLEND_OBND_X_MIN_POS)
#define OSD_BLEND_OBND_X_MIN_UMSK           (~(((1U << OSD_BLEND_OBND_X_MIN_LEN) - 1) << OSD_BLEND_OBND_X_MIN_POS))
#define OSD_BLEND_OBND_X_MAX                OSD_BLEND_OBND_X_MAX
#define OSD_BLEND_OBND_X_MAX_POS            (16U)
#define OSD_BLEND_OBND_X_MAX_LEN            (11U)
#define OSD_BLEND_OBND_X_MAX_MSK            (((1U << OSD_BLEND_OBND_X_MAX_LEN) - 1) << OSD_BLEND_OBND_X_MAX_POS)
#define OSD_BLEND_OBND_X_MAX_UMSK           (~(((1U << OSD_BLEND_OBND_X_MAX_LEN) - 1) << OSD_BLEND_OBND_X_MAX_POS))

/* 0x4 : obnd_layer_yconfig */
#define OSD_BLEND_OBND_LAYER_YCONFIG_OFFSET (0x4)
#define OSD_BLEND_OBND_Y_MIN                OSD_BLEND_OBND_Y_MIN
#define OSD_BLEND_OBND_Y_MIN_POS            (0U)
#define OSD_BLEND_OBND_Y_MIN_LEN            (11U)
#define OSD_BLEND_OBND_Y_MIN_MSK            (((1U << OSD_BLEND_OBND_Y_MIN_LEN) - 1) << OSD_BLEND_OBND_Y_MIN_POS)
#define OSD_BLEND_OBND_Y_MIN_UMSK           (~(((1U << OSD_BLEND_OBND_Y_MIN_LEN) - 1) << OSD_BLEND_OBND_Y_MIN_POS))
#define OSD_BLEND_OBND_Y_MAX                OSD_BLEND_OBND_Y_MAX
#define OSD_BLEND_OBND_Y_MAX_POS            (16U)
#define OSD_BLEND_OBND_Y_MAX_LEN            (11U)
#define OSD_BLEND_OBND_Y_MAX_MSK            (((1U << OSD_BLEND_OBND_Y_MAX_LEN) - 1) << OSD_BLEND_OBND_Y_MAX_POS)
#define OSD_BLEND_OBND_Y_MAX_UMSK           (~(((1U << OSD_BLEND_OBND_Y_MAX_LEN) - 1) << OSD_BLEND_OBND_Y_MAX_POS))

/* 0x8 : obnd_mem_config0 */
#define OSD_BLEND_OBND_MEM_CONFIG0_OFFSET (0x8)
#define OSD_BLEND_OBND_FORCE_SH           OSD_BLEND_OBND_FORCE_SH
#define OSD_BLEND_OBND_FORCE_SH_POS       (0U)
#define OSD_BLEND_OBND_FORCE_SH_LEN       (1U)
#define OSD_BLEND_OBND_FORCE_SH_MSK       (((1U << OSD_BLEND_OBND_FORCE_SH_LEN) - 1) << OSD_BLEND_OBND_FORCE_SH_POS)
#define OSD_BLEND_OBND_FORCE_SH_UMSK      (~(((1U << OSD_BLEND_OBND_FORCE_SH_LEN) - 1) << OSD_BLEND_OBND_FORCE_SH_POS))
#define OSD_BLEND_OBND_LAYER_EN           OSD_BLEND_OBND_LAYER_EN
#define OSD_BLEND_OBND_LAYER_EN_POS       (15U)
#define OSD_BLEND_OBND_LAYER_EN_LEN       (1U)
#define OSD_BLEND_OBND_LAYER_EN_MSK       (((1U << OSD_BLEND_OBND_LAYER_EN_LEN) - 1) << OSD_BLEND_OBND_LAYER_EN_POS)
#define OSD_BLEND_OBND_LAYER_EN_UMSK      (~(((1U << OSD_BLEND_OBND_LAYER_EN_LEN) - 1) << OSD_BLEND_OBND_LAYER_EN_POS))

/* 0xC : obnd_mem_config1 */
#define OSD_BLEND_OBND_MEM_CONFIG1_OFFSET (0xC)
#define OSD_BLEND_OBND_MEM_ADDR           OSD_BLEND_OBND_MEM_ADDR
#define OSD_BLEND_OBND_MEM_ADDR_POS       (0U)
#define OSD_BLEND_OBND_MEM_ADDR_LEN       (32U)
#define OSD_BLEND_OBND_MEM_ADDR_MSK       (((1U << OSD_BLEND_OBND_MEM_ADDR_LEN) - 1) << OSD_BLEND_OBND_MEM_ADDR_POS)
#define OSD_BLEND_OBND_MEM_ADDR_UMSK      (~(((1U << OSD_BLEND_OBND_MEM_ADDR_LEN) - 1) << OSD_BLEND_OBND_MEM_ADDR_POS))

/* 0x10 : obnd_mem_config2 */
#define OSD_BLEND_OBND_MEM_CONFIG2_OFFSET (0x10)
#define OSD_BLEND_OBND_MEM_DW_CNT         OSD_BLEND_OBND_MEM_DW_CNT
#define OSD_BLEND_OBND_MEM_DW_CNT_POS     (0U)
#define OSD_BLEND_OBND_MEM_DW_CNT_LEN     (32U)
#define OSD_BLEND_OBND_MEM_DW_CNT_MSK     (((1U << OSD_BLEND_OBND_MEM_DW_CNT_LEN) - 1) << OSD_BLEND_OBND_MEM_DW_CNT_POS)
#define OSD_BLEND_OBND_MEM_DW_CNT_UMSK    (~(((1U << OSD_BLEND_OBND_MEM_DW_CNT_LEN) - 1) << OSD_BLEND_OBND_MEM_DW_CNT_POS))

/* 0x14 : obnd_layer_config0 */
#define OSD_BLEND_OBND_LAYER_CONFIG0_OFFSET (0x14)
#define OSD_BLEND_OBND_COLOR_FORMAT         OSD_BLEND_OBND_COLOR_FORMAT
#define OSD_BLEND_OBND_COLOR_FORMAT_POS     (0U)
#define OSD_BLEND_OBND_COLOR_FORMAT_LEN     (5U)
#define OSD_BLEND_OBND_COLOR_FORMAT_MSK     (((1U << OSD_BLEND_OBND_COLOR_FORMAT_LEN) - 1) << OSD_BLEND_OBND_COLOR_FORMAT_POS)
#define OSD_BLEND_OBND_COLOR_FORMAT_UMSK    (~(((1U << OSD_BLEND_OBND_COLOR_FORMAT_LEN) - 1) << OSD_BLEND_OBND_COLOR_FORMAT_POS))
#define OSD_BLEND_OBND_ORDER_A              OSD_BLEND_OBND_ORDER_A
#define OSD_BLEND_OBND_ORDER_A_POS          (8U)
#define OSD_BLEND_OBND_ORDER_A_LEN          (2U)
#define OSD_BLEND_OBND_ORDER_A_MSK          (((1U << OSD_BLEND_OBND_ORDER_A_LEN) - 1) << OSD_BLEND_OBND_ORDER_A_POS)
#define OSD_BLEND_OBND_ORDER_A_UMSK         (~(((1U << OSD_BLEND_OBND_ORDER_A_LEN) - 1) << OSD_BLEND_OBND_ORDER_A_POS))
#define OSD_BLEND_OBND_ORDER_RV             OSD_BLEND_OBND_ORDER_RV
#define OSD_BLEND_OBND_ORDER_RV_POS         (10U)
#define OSD_BLEND_OBND_ORDER_RV_LEN         (2U)
#define OSD_BLEND_OBND_ORDER_RV_MSK         (((1U << OSD_BLEND_OBND_ORDER_RV_LEN) - 1) << OSD_BLEND_OBND_ORDER_RV_POS)
#define OSD_BLEND_OBND_ORDER_RV_UMSK        (~(((1U << OSD_BLEND_OBND_ORDER_RV_LEN) - 1) << OSD_BLEND_OBND_ORDER_RV_POS))
#define OSD_BLEND_OBND_ORDER_GY             OSD_BLEND_OBND_ORDER_GY
#define OSD_BLEND_OBND_ORDER_GY_POS         (12U)
#define OSD_BLEND_OBND_ORDER_GY_LEN         (2U)
#define OSD_BLEND_OBND_ORDER_GY_MSK         (((1U << OSD_BLEND_OBND_ORDER_GY_LEN) - 1) << OSD_BLEND_OBND_ORDER_GY_POS)
#define OSD_BLEND_OBND_ORDER_GY_UMSK        (~(((1U << OSD_BLEND_OBND_ORDER_GY_LEN) - 1) << OSD_BLEND_OBND_ORDER_GY_POS))
#define OSD_BLEND_OBND_ORDER_BU             OSD_BLEND_OBND_ORDER_BU
#define OSD_BLEND_OBND_ORDER_BU_POS         (14U)
#define OSD_BLEND_OBND_ORDER_BU_LEN         (2U)
#define OSD_BLEND_OBND_ORDER_BU_MSK         (((1U << OSD_BLEND_OBND_ORDER_BU_LEN) - 1) << OSD_BLEND_OBND_ORDER_BU_POS)
#define OSD_BLEND_OBND_ORDER_BU_UMSK        (~(((1U << OSD_BLEND_OBND_ORDER_BU_LEN) - 1) << OSD_BLEND_OBND_ORDER_BU_POS))
#define OSD_BLEND_OBND_GLOBAL_A_EN          OSD_BLEND_OBND_GLOBAL_A_EN
#define OSD_BLEND_OBND_GLOBAL_A_EN_POS      (16U)
#define OSD_BLEND_OBND_GLOBAL_A_EN_LEN      (1U)
#define OSD_BLEND_OBND_GLOBAL_A_EN_MSK      (((1U << OSD_BLEND_OBND_GLOBAL_A_EN_LEN) - 1) << OSD_BLEND_OBND_GLOBAL_A_EN_POS)
#define OSD_BLEND_OBND_GLOBAL_A_EN_UMSK     (~(((1U << OSD_BLEND_OBND_GLOBAL_A_EN_LEN) - 1) << OSD_BLEND_OBND_GLOBAL_A_EN_POS))
#define OSD_BLEND_OBND_GLOBAL_A             OSD_BLEND_OBND_GLOBAL_A
#define OSD_BLEND_OBND_GLOBAL_A_POS         (24U)
#define OSD_BLEND_OBND_GLOBAL_A_LEN         (8U)
#define OSD_BLEND_OBND_GLOBAL_A_MSK         (((1U << OSD_BLEND_OBND_GLOBAL_A_LEN) - 1) << OSD_BLEND_OBND_GLOBAL_A_POS)
#define OSD_BLEND_OBND_GLOBAL_A_UMSK        (~(((1U << OSD_BLEND_OBND_GLOBAL_A_LEN) - 1) << OSD_BLEND_OBND_GLOBAL_A_POS))

/* 0x18 : obnd_layer_config1 */
#define OSD_BLEND_OBND_LAYER_CONFIG1_OFFSET (0x18)
#define OSD_BLEND_OBND_GLOBAL_COLOR_EN      OSD_BLEND_OBND_GLOBAL_COLOR_EN
#define OSD_BLEND_OBND_GLOBAL_COLOR_EN_POS  (0U)
#define OSD_BLEND_OBND_GLOBAL_COLOR_EN_LEN  (1U)
#define OSD_BLEND_OBND_GLOBAL_COLOR_EN_MSK  (((1U << OSD_BLEND_OBND_GLOBAL_COLOR_EN_LEN) - 1) << OSD_BLEND_OBND_GLOBAL_COLOR_EN_POS)
#define OSD_BLEND_OBND_GLOBAL_COLOR_EN_UMSK (~(((1U << OSD_BLEND_OBND_GLOBAL_COLOR_EN_LEN) - 1) << OSD_BLEND_OBND_GLOBAL_COLOR_EN_POS))
#define OSD_BLEND_OBND_GLOBAL_RV            OSD_BLEND_OBND_GLOBAL_RV
#define OSD_BLEND_OBND_GLOBAL_RV_POS        (8U)
#define OSD_BLEND_OBND_GLOBAL_RV_LEN        (8U)
#define OSD_BLEND_OBND_GLOBAL_RV_MSK        (((1U << OSD_BLEND_OBND_GLOBAL_RV_LEN) - 1) << OSD_BLEND_OBND_GLOBAL_RV_POS)
#define OSD_BLEND_OBND_GLOBAL_RV_UMSK       (~(((1U << OSD_BLEND_OBND_GLOBAL_RV_LEN) - 1) << OSD_BLEND_OBND_GLOBAL_RV_POS))
#define OSD_BLEND_OBND_GLOBAL_GY            OSD_BLEND_OBND_GLOBAL_GY
#define OSD_BLEND_OBND_GLOBAL_GY_POS        (16U)
#define OSD_BLEND_OBND_GLOBAL_GY_LEN        (8U)
#define OSD_BLEND_OBND_GLOBAL_GY_MSK        (((1U << OSD_BLEND_OBND_GLOBAL_GY_LEN) - 1) << OSD_BLEND_OBND_GLOBAL_GY_POS)
#define OSD_BLEND_OBND_GLOBAL_GY_UMSK       (~(((1U << OSD_BLEND_OBND_GLOBAL_GY_LEN) - 1) << OSD_BLEND_OBND_GLOBAL_GY_POS))
#define OSD_BLEND_OBND_GLOBAL_BU            OSD_BLEND_OBND_GLOBAL_BU
#define OSD_BLEND_OBND_GLOBAL_BU_POS        (24U)
#define OSD_BLEND_OBND_GLOBAL_BU_LEN        (8U)
#define OSD_BLEND_OBND_GLOBAL_BU_MSK        (((1U << OSD_BLEND_OBND_GLOBAL_BU_LEN) - 1) << OSD_BLEND_OBND_GLOBAL_BU_POS)
#define OSD_BLEND_OBND_GLOBAL_BU_UMSK       (~(((1U << OSD_BLEND_OBND_GLOBAL_BU_LEN) - 1) << OSD_BLEND_OBND_GLOBAL_BU_POS))

/* 0x1C : obnd_layer_config2 */
#define OSD_BLEND_OBND_LAYER_CONFIG2_OFFSET   (0x1C)
#define OSD_BLEND_OBND_KEY_PALETTE_EN         OSD_BLEND_OBND_KEY_PALETTE_EN
#define OSD_BLEND_OBND_KEY_PALETTE_EN_POS     (0U)
#define OSD_BLEND_OBND_KEY_PALETTE_EN_LEN     (1U)
#define OSD_BLEND_OBND_KEY_PALETTE_EN_MSK     (((1U << OSD_BLEND_OBND_KEY_PALETTE_EN_LEN) - 1) << OSD_BLEND_OBND_KEY_PALETTE_EN_POS)
#define OSD_BLEND_OBND_KEY_PALETTE_EN_UMSK    (~(((1U << OSD_BLEND_OBND_KEY_PALETTE_EN_LEN) - 1) << OSD_BLEND_OBND_KEY_PALETTE_EN_POS))
#define OSD_BLEND_OBND_KEY_INDEX_INV          OSD_BLEND_OBND_KEY_INDEX_INV
#define OSD_BLEND_OBND_KEY_INDEX_INV_POS      (1U)
#define OSD_BLEND_OBND_KEY_INDEX_INV_LEN      (1U)
#define OSD_BLEND_OBND_KEY_INDEX_INV_MSK      (((1U << OSD_BLEND_OBND_KEY_INDEX_INV_LEN) - 1) << OSD_BLEND_OBND_KEY_INDEX_INV_POS)
#define OSD_BLEND_OBND_KEY_INDEX_INV_UMSK     (~(((1U << OSD_BLEND_OBND_KEY_INDEX_INV_LEN) - 1) << OSD_BLEND_OBND_KEY_INDEX_INV_POS))
#define OSD_BLEND_OBND_KEY_INDEX_MIN          OSD_BLEND_OBND_KEY_INDEX_MIN
#define OSD_BLEND_OBND_KEY_INDEX_MIN_POS      (8U)
#define OSD_BLEND_OBND_KEY_INDEX_MIN_LEN      (8U)
#define OSD_BLEND_OBND_KEY_INDEX_MIN_MSK      (((1U << OSD_BLEND_OBND_KEY_INDEX_MIN_LEN) - 1) << OSD_BLEND_OBND_KEY_INDEX_MIN_POS)
#define OSD_BLEND_OBND_KEY_INDEX_MIN_UMSK     (~(((1U << OSD_BLEND_OBND_KEY_INDEX_MIN_LEN) - 1) << OSD_BLEND_OBND_KEY_INDEX_MIN_POS))
#define OSD_BLEND_OBND_KEY_INDEX_MAX          OSD_BLEND_OBND_KEY_INDEX_MAX
#define OSD_BLEND_OBND_KEY_INDEX_MAX_POS      (16U)
#define OSD_BLEND_OBND_KEY_INDEX_MAX_LEN      (8U)
#define OSD_BLEND_OBND_KEY_INDEX_MAX_MSK      (((1U << OSD_BLEND_OBND_KEY_INDEX_MAX_LEN) - 1) << OSD_BLEND_OBND_KEY_INDEX_MAX_POS)
#define OSD_BLEND_OBND_KEY_INDEX_MAX_UMSK     (~(((1U << OSD_BLEND_OBND_KEY_INDEX_MAX_LEN) - 1) << OSD_BLEND_OBND_KEY_INDEX_MAX_POS))
#define OSD_BLEND_OBND_KEY_REPLACE_INDEX      OSD_BLEND_OBND_KEY_REPLACE_INDEX
#define OSD_BLEND_OBND_KEY_REPLACE_INDEX_POS  (24U)
#define OSD_BLEND_OBND_KEY_REPLACE_INDEX_LEN  (8U)
#define OSD_BLEND_OBND_KEY_REPLACE_INDEX_MSK  (((1U << OSD_BLEND_OBND_KEY_REPLACE_INDEX_LEN) - 1) << OSD_BLEND_OBND_KEY_REPLACE_INDEX_POS)
#define OSD_BLEND_OBND_KEY_REPLACE_INDEX_UMSK (~(((1U << OSD_BLEND_OBND_KEY_REPLACE_INDEX_LEN) - 1) << OSD_BLEND_OBND_KEY_REPLACE_INDEX_POS))

/* 0x20 : obnd_layer_config3 */
#define OSD_BLEND_OBND_LAYER_CONFIG3_OFFSET (0x20)
#define OSD_BLEND_OBND_KEY_A_MIN            OSD_BLEND_OBND_KEY_A_MIN
#define OSD_BLEND_OBND_KEY_A_MIN_POS        (0U)
#define OSD_BLEND_OBND_KEY_A_MIN_LEN        (8U)
#define OSD_BLEND_OBND_KEY_A_MIN_MSK        (((1U << OSD_BLEND_OBND_KEY_A_MIN_LEN) - 1) << OSD_BLEND_OBND_KEY_A_MIN_POS)
#define OSD_BLEND_OBND_KEY_A_MIN_UMSK       (~(((1U << OSD_BLEND_OBND_KEY_A_MIN_LEN) - 1) << OSD_BLEND_OBND_KEY_A_MIN_POS))
#define OSD_BLEND_OBND_KEY_A_MAX            OSD_BLEND_OBND_KEY_A_MAX
#define OSD_BLEND_OBND_KEY_A_MAX_POS        (8U)
#define OSD_BLEND_OBND_KEY_A_MAX_LEN        (8U)
#define OSD_BLEND_OBND_KEY_A_MAX_MSK        (((1U << OSD_BLEND_OBND_KEY_A_MAX_LEN) - 1) << OSD_BLEND_OBND_KEY_A_MAX_POS)
#define OSD_BLEND_OBND_KEY_A_MAX_UMSK       (~(((1U << OSD_BLEND_OBND_KEY_A_MAX_LEN) - 1) << OSD_BLEND_OBND_KEY_A_MAX_POS))
#define OSD_BLEND_OBND_KEY_RV_MIN           OSD_BLEND_OBND_KEY_RV_MIN
#define OSD_BLEND_OBND_KEY_RV_MIN_POS       (16U)
#define OSD_BLEND_OBND_KEY_RV_MIN_LEN       (8U)
#define OSD_BLEND_OBND_KEY_RV_MIN_MSK       (((1U << OSD_BLEND_OBND_KEY_RV_MIN_LEN) - 1) << OSD_BLEND_OBND_KEY_RV_MIN_POS)
#define OSD_BLEND_OBND_KEY_RV_MIN_UMSK      (~(((1U << OSD_BLEND_OBND_KEY_RV_MIN_LEN) - 1) << OSD_BLEND_OBND_KEY_RV_MIN_POS))
#define OSD_BLEND_OBND_KEY_RV_MAX           OSD_BLEND_OBND_KEY_RV_MAX
#define OSD_BLEND_OBND_KEY_RV_MAX_POS       (24U)
#define OSD_BLEND_OBND_KEY_RV_MAX_LEN       (8U)
#define OSD_BLEND_OBND_KEY_RV_MAX_MSK       (((1U << OSD_BLEND_OBND_KEY_RV_MAX_LEN) - 1) << OSD_BLEND_OBND_KEY_RV_MAX_POS)
#define OSD_BLEND_OBND_KEY_RV_MAX_UMSK      (~(((1U << OSD_BLEND_OBND_KEY_RV_MAX_LEN) - 1) << OSD_BLEND_OBND_KEY_RV_MAX_POS))

/* 0x24 : obnd_layer_config4 */
#define OSD_BLEND_OBND_LAYER_CONFIG4_OFFSET (0x24)
#define OSD_BLEND_OBND_KEY_GY_MIN           OSD_BLEND_OBND_KEY_GY_MIN
#define OSD_BLEND_OBND_KEY_GY_MIN_POS       (0U)
#define OSD_BLEND_OBND_KEY_GY_MIN_LEN       (8U)
#define OSD_BLEND_OBND_KEY_GY_MIN_MSK       (((1U << OSD_BLEND_OBND_KEY_GY_MIN_LEN) - 1) << OSD_BLEND_OBND_KEY_GY_MIN_POS)
#define OSD_BLEND_OBND_KEY_GY_MIN_UMSK      (~(((1U << OSD_BLEND_OBND_KEY_GY_MIN_LEN) - 1) << OSD_BLEND_OBND_KEY_GY_MIN_POS))
#define OSD_BLEND_OBND_KEY_GY_MAX           OSD_BLEND_OBND_KEY_GY_MAX
#define OSD_BLEND_OBND_KEY_GY_MAX_POS       (8U)
#define OSD_BLEND_OBND_KEY_GY_MAX_LEN       (8U)
#define OSD_BLEND_OBND_KEY_GY_MAX_MSK       (((1U << OSD_BLEND_OBND_KEY_GY_MAX_LEN) - 1) << OSD_BLEND_OBND_KEY_GY_MAX_POS)
#define OSD_BLEND_OBND_KEY_GY_MAX_UMSK      (~(((1U << OSD_BLEND_OBND_KEY_GY_MAX_LEN) - 1) << OSD_BLEND_OBND_KEY_GY_MAX_POS))
#define OSD_BLEND_OBND_KEY_BU_MIN           OSD_BLEND_OBND_KEY_BU_MIN
#define OSD_BLEND_OBND_KEY_BU_MIN_POS       (16U)
#define OSD_BLEND_OBND_KEY_BU_MIN_LEN       (8U)
#define OSD_BLEND_OBND_KEY_BU_MIN_MSK       (((1U << OSD_BLEND_OBND_KEY_BU_MIN_LEN) - 1) << OSD_BLEND_OBND_KEY_BU_MIN_POS)
#define OSD_BLEND_OBND_KEY_BU_MIN_UMSK      (~(((1U << OSD_BLEND_OBND_KEY_BU_MIN_LEN) - 1) << OSD_BLEND_OBND_KEY_BU_MIN_POS))
#define OSD_BLEND_OBND_KEY_BU_MAX           OSD_BLEND_OBND_KEY_BU_MAX
#define OSD_BLEND_OBND_KEY_BU_MAX_POS       (24U)
#define OSD_BLEND_OBND_KEY_BU_MAX_LEN       (8U)
#define OSD_BLEND_OBND_KEY_BU_MAX_MSK       (((1U << OSD_BLEND_OBND_KEY_BU_MAX_LEN) - 1) << OSD_BLEND_OBND_KEY_BU_MAX_POS)
#define OSD_BLEND_OBND_KEY_BU_MAX_UMSK      (~(((1U << OSD_BLEND_OBND_KEY_BU_MAX_LEN) - 1) << OSD_BLEND_OBND_KEY_BU_MAX_POS))

/* 0x28 : obnd_layer_config5 */
#define OSD_BLEND_OBND_LAYER_CONFIG5_OFFSET (0x28)
#define OSD_BLEND_OBND_KEY_REPLACE_A        OSD_BLEND_OBND_KEY_REPLACE_A
#define OSD_BLEND_OBND_KEY_REPLACE_A_POS    (0U)
#define OSD_BLEND_OBND_KEY_REPLACE_A_LEN    (8U)
#define OSD_BLEND_OBND_KEY_REPLACE_A_MSK    (((1U << OSD_BLEND_OBND_KEY_REPLACE_A_LEN) - 1) << OSD_BLEND_OBND_KEY_REPLACE_A_POS)
#define OSD_BLEND_OBND_KEY_REPLACE_A_UMSK   (~(((1U << OSD_BLEND_OBND_KEY_REPLACE_A_LEN) - 1) << OSD_BLEND_OBND_KEY_REPLACE_A_POS))
#define OSD_BLEND_OBND_KEY_REPLACE_RV       OSD_BLEND_OBND_KEY_REPLACE_RV
#define OSD_BLEND_OBND_KEY_REPLACE_RV_POS   (8U)
#define OSD_BLEND_OBND_KEY_REPLACE_RV_LEN   (8U)
#define OSD_BLEND_OBND_KEY_REPLACE_RV_MSK   (((1U << OSD_BLEND_OBND_KEY_REPLACE_RV_LEN) - 1) << OSD_BLEND_OBND_KEY_REPLACE_RV_POS)
#define OSD_BLEND_OBND_KEY_REPLACE_RV_UMSK  (~(((1U << OSD_BLEND_OBND_KEY_REPLACE_RV_LEN) - 1) << OSD_BLEND_OBND_KEY_REPLACE_RV_POS))
#define OSD_BLEND_OBND_KEY_REPLACE_GY       OSD_BLEND_OBND_KEY_REPLACE_GY
#define OSD_BLEND_OBND_KEY_REPLACE_GY_POS   (16U)
#define OSD_BLEND_OBND_KEY_REPLACE_GY_LEN   (8U)
#define OSD_BLEND_OBND_KEY_REPLACE_GY_MSK   (((1U << OSD_BLEND_OBND_KEY_REPLACE_GY_LEN) - 1) << OSD_BLEND_OBND_KEY_REPLACE_GY_POS)
#define OSD_BLEND_OBND_KEY_REPLACE_GY_UMSK  (~(((1U << OSD_BLEND_OBND_KEY_REPLACE_GY_LEN) - 1) << OSD_BLEND_OBND_KEY_REPLACE_GY_POS))
#define OSD_BLEND_OBND_KEY_REPLACE_BU       OSD_BLEND_OBND_KEY_REPLACE_BU
#define OSD_BLEND_OBND_KEY_REPLACE_BU_POS   (24U)
#define OSD_BLEND_OBND_KEY_REPLACE_BU_LEN   (8U)
#define OSD_BLEND_OBND_KEY_REPLACE_BU_MSK   (((1U << OSD_BLEND_OBND_KEY_REPLACE_BU_LEN) - 1) << OSD_BLEND_OBND_KEY_REPLACE_BU_POS)
#define OSD_BLEND_OBND_KEY_REPLACE_BU_UMSK  (~(((1U << OSD_BLEND_OBND_KEY_REPLACE_BU_LEN) - 1) << OSD_BLEND_OBND_KEY_REPLACE_BU_POS))

/* 0x2C : obnd_layer_config6 */
#define OSD_BLEND_OBND_LAYER_CONFIG6_OFFSET (0x2C)
#define OSD_BLEND_OBND_KEY_COLOR_EN         OSD_BLEND_OBND_KEY_COLOR_EN
#define OSD_BLEND_OBND_KEY_COLOR_EN_POS     (0U)
#define OSD_BLEND_OBND_KEY_COLOR_EN_LEN     (1U)
#define OSD_BLEND_OBND_KEY_COLOR_EN_MSK     (((1U << OSD_BLEND_OBND_KEY_COLOR_EN_LEN) - 1) << OSD_BLEND_OBND_KEY_COLOR_EN_POS)
#define OSD_BLEND_OBND_KEY_COLOR_EN_UMSK    (~(((1U << OSD_BLEND_OBND_KEY_COLOR_EN_LEN) - 1) << OSD_BLEND_OBND_KEY_COLOR_EN_POS))
#define OSD_BLEND_OBND_KEY_A_INV            OSD_BLEND_OBND_KEY_A_INV
#define OSD_BLEND_OBND_KEY_A_INV_POS        (1U)
#define OSD_BLEND_OBND_KEY_A_INV_LEN        (1U)
#define OSD_BLEND_OBND_KEY_A_INV_MSK        (((1U << OSD_BLEND_OBND_KEY_A_INV_LEN) - 1) << OSD_BLEND_OBND_KEY_A_INV_POS)
#define OSD_BLEND_OBND_KEY_A_INV_UMSK       (~(((1U << OSD_BLEND_OBND_KEY_A_INV_LEN) - 1) << OSD_BLEND_OBND_KEY_A_INV_POS))
#define OSD_BLEND_OBND_KEY_RV_INV           OSD_BLEND_OBND_KEY_RV_INV
#define OSD_BLEND_OBND_KEY_RV_INV_POS       (2U)
#define OSD_BLEND_OBND_KEY_RV_INV_LEN       (1U)
#define OSD_BLEND_OBND_KEY_RV_INV_MSK       (((1U << OSD_BLEND_OBND_KEY_RV_INV_LEN) - 1) << OSD_BLEND_OBND_KEY_RV_INV_POS)
#define OSD_BLEND_OBND_KEY_RV_INV_UMSK      (~(((1U << OSD_BLEND_OBND_KEY_RV_INV_LEN) - 1) << OSD_BLEND_OBND_KEY_RV_INV_POS))
#define OSD_BLEND_OBND_KEY_GY_INV           OSD_BLEND_OBND_KEY_GY_INV
#define OSD_BLEND_OBND_KEY_GY_INV_POS       (3U)
#define OSD_BLEND_OBND_KEY_GY_INV_LEN       (1U)
#define OSD_BLEND_OBND_KEY_GY_INV_MSK       (((1U << OSD_BLEND_OBND_KEY_GY_INV_LEN) - 1) << OSD_BLEND_OBND_KEY_GY_INV_POS)
#define OSD_BLEND_OBND_KEY_GY_INV_UMSK      (~(((1U << OSD_BLEND_OBND_KEY_GY_INV_LEN) - 1) << OSD_BLEND_OBND_KEY_GY_INV_POS))
#define OSD_BLEND_OBND_KEY_BU_INV           OSD_BLEND_OBND_KEY_BU_INV
#define OSD_BLEND_OBND_KEY_BU_INV_POS       (4U)
#define OSD_BLEND_OBND_KEY_BU_INV_LEN       (1U)
#define OSD_BLEND_OBND_KEY_BU_INV_MSK       (((1U << OSD_BLEND_OBND_KEY_BU_INV_LEN) - 1) << OSD_BLEND_OBND_KEY_BU_INV_POS)
#define OSD_BLEND_OBND_KEY_BU_INV_UMSK      (~(((1U << OSD_BLEND_OBND_KEY_BU_INV_LEN) - 1) << OSD_BLEND_OBND_KEY_BU_INV_POS))
#define OSD_BLEND_OBND_UPDATE_TRIGGER       OSD_BLEND_OBND_UPDATE_TRIGGER
#define OSD_BLEND_OBND_UPDATE_TRIGGER_POS   (5U)
#define OSD_BLEND_OBND_UPDATE_TRIGGER_LEN   (1U)
#define OSD_BLEND_OBND_UPDATE_TRIGGER_MSK   (((1U << OSD_BLEND_OBND_UPDATE_TRIGGER_LEN) - 1) << OSD_BLEND_OBND_UPDATE_TRIGGER_POS)
#define OSD_BLEND_OBND_UPDATE_TRIGGER_UMSK  (~(((1U << OSD_BLEND_OBND_UPDATE_TRIGGER_LEN) - 1) << OSD_BLEND_OBND_UPDATE_TRIGGER_POS))
#define OSD_BLEND_OBND_UPDATE_INDEX         OSD_BLEND_OBND_UPDATE_INDEX
#define OSD_BLEND_OBND_UPDATE_INDEX_POS     (8U)
#define OSD_BLEND_OBND_UPDATE_INDEX_LEN     (8U)
#define OSD_BLEND_OBND_UPDATE_INDEX_MSK     (((1U << OSD_BLEND_OBND_UPDATE_INDEX_LEN) - 1) << OSD_BLEND_OBND_UPDATE_INDEX_POS)
#define OSD_BLEND_OBND_UPDATE_INDEX_UMSK    (~(((1U << OSD_BLEND_OBND_UPDATE_INDEX_LEN) - 1) << OSD_BLEND_OBND_UPDATE_INDEX_POS))

/* 0x30 : obnd_layer_config7 */
#define OSD_BLEND_OBND_LAYER_CONFIG7_OFFSET (0x30)
#define OSD_BLEND_OBND_UPDATE_COLOR         OSD_BLEND_OBND_UPDATE_COLOR
#define OSD_BLEND_OBND_UPDATE_COLOR_POS     (0U)
#define OSD_BLEND_OBND_UPDATE_COLOR_LEN     (32U)
#define OSD_BLEND_OBND_UPDATE_COLOR_MSK     (((1U << OSD_BLEND_OBND_UPDATE_COLOR_LEN) - 1) << OSD_BLEND_OBND_UPDATE_COLOR_POS)
#define OSD_BLEND_OBND_UPDATE_COLOR_UMSK    (~(((1U << OSD_BLEND_OBND_UPDATE_COLOR_LEN) - 1) << OSD_BLEND_OBND_UPDATE_COLOR_POS))

/* 0x40 : obnd_error */
#define OSD_BLEND_OBND_ERROR_OFFSET           (0x40)
#define OSD_BLEND_REG_RFIFO_DRAIN_CLR_W       OSD_BLEND_REG_RFIFO_DRAIN_CLR_W
#define OSD_BLEND_REG_RFIFO_DRAIN_CLR_W_POS   (0U)
#define OSD_BLEND_REG_RFIFO_DRAIN_CLR_W_LEN   (1U)
#define OSD_BLEND_REG_RFIFO_DRAIN_CLR_W_MSK   (((1U << OSD_BLEND_REG_RFIFO_DRAIN_CLR_W_LEN) - 1) << OSD_BLEND_REG_RFIFO_DRAIN_CLR_W_POS)
#define OSD_BLEND_REG_RFIFO_DRAIN_CLR_W_UMSK  (~(((1U << OSD_BLEND_REG_RFIFO_DRAIN_CLR_W_LEN) - 1) << OSD_BLEND_REG_RFIFO_DRAIN_CLR_W_POS))
#define OSD_BLEND_REG_RFIFO_DRAIN_MASK_W      OSD_BLEND_REG_RFIFO_DRAIN_MASK_W
#define OSD_BLEND_REG_RFIFO_DRAIN_MASK_W_POS  (1U)
#define OSD_BLEND_REG_RFIFO_DRAIN_MASK_W_LEN  (1U)
#define OSD_BLEND_REG_RFIFO_DRAIN_MASK_W_MSK  (((1U << OSD_BLEND_REG_RFIFO_DRAIN_MASK_W_LEN) - 1) << OSD_BLEND_REG_RFIFO_DRAIN_MASK_W_POS)
#define OSD_BLEND_REG_RFIFO_DRAIN_MASK_W_UMSK (~(((1U << OSD_BLEND_REG_RFIFO_DRAIN_MASK_W_LEN) - 1) << OSD_BLEND_REG_RFIFO_DRAIN_MASK_W_POS))
#define OSD_BLEND_STS_RFIFO_DRAIN_R           OSD_BLEND_STS_RFIFO_DRAIN_R
#define OSD_BLEND_STS_RFIFO_DRAIN_R_POS       (16U)
#define OSD_BLEND_STS_RFIFO_DRAIN_R_LEN       (1U)
#define OSD_BLEND_STS_RFIFO_DRAIN_R_MSK       (((1U << OSD_BLEND_STS_RFIFO_DRAIN_R_LEN) - 1) << OSD_BLEND_STS_RFIFO_DRAIN_R_POS)
#define OSD_BLEND_STS_RFIFO_DRAIN_R_UMSK      (~(((1U << OSD_BLEND_STS_RFIFO_DRAIN_R_LEN) - 1) << OSD_BLEND_STS_RFIFO_DRAIN_R_POS))

/* 0x44 : obnd_sh */
#define OSD_BLEND_OBND_SH_OFFSET              (0x44)
#define OSD_BLEND_OBND_LAYER_MEM_REQ_CNT      OSD_BLEND_OBND_LAYER_MEM_REQ_CNT
#define OSD_BLEND_OBND_LAYER_MEM_REQ_CNT_POS  (0U)
#define OSD_BLEND_OBND_LAYER_MEM_REQ_CNT_LEN  (32U)
#define OSD_BLEND_OBND_LAYER_MEM_REQ_CNT_MSK  (((1U << OSD_BLEND_OBND_LAYER_MEM_REQ_CNT_LEN) - 1) << OSD_BLEND_OBND_LAYER_MEM_REQ_CNT_POS)
#define OSD_BLEND_OBND_LAYER_MEM_REQ_CNT_UMSK (~(((1U << OSD_BLEND_OBND_LAYER_MEM_REQ_CNT_LEN) - 1) << OSD_BLEND_OBND_LAYER_MEM_REQ_CNT_POS))

struct osd_blend_reg {
    /* 0x0 : obnd_layer_xconfig */
    union {
        struct {
            uint32_t obnd_x_min     : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15 : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t obnd_x_max     : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31 : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } obnd_layer_xconfig;

    /* 0x4 : obnd_layer_yconfig */
    union {
        struct {
            uint32_t obnd_y_min     : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15 : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t obnd_y_max     : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31 : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } obnd_layer_yconfig;

    /* 0x8 : obnd_mem_config0 */
    union {
        struct {
            uint32_t obnd_force_sh  : 1;  /* [    0],        w1p,        0x0 */
            uint32_t reserved_1_14  : 14; /* [14: 1],       rsvd,        0x0 */
            uint32_t obnd_layer_en  : 1;  /* [   15],        r/w,        0x0 */
            uint32_t reserved_16_31 : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } obnd_mem_config0;

    /* 0xC : obnd_mem_config1 */
    union {
        struct {
            uint32_t obnd_mem_addr : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } obnd_mem_config1;

    /* 0x10 : obnd_mem_config2 */
    union {
        struct {
            uint32_t obnd_mem_dw_cnt : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } obnd_mem_config2;

    /* 0x14 : obnd_layer_config0 */
    union {
        struct {
            uint32_t obnd_color_format : 5; /* [ 4: 0],        r/w,        0x0 */
            uint32_t reserved_5_7      : 3; /* [ 7: 5],       rsvd,        0x0 */
            uint32_t obnd_order_a      : 2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t obnd_order_rv     : 2; /* [11:10],        r/w,        0x0 */
            uint32_t obnd_order_gy     : 2; /* [13:12],        r/w,        0x0 */
            uint32_t obnd_order_bu     : 2; /* [15:14],        r/w,        0x0 */
            uint32_t obnd_global_a_en  : 1; /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_23    : 7; /* [23:17],       rsvd,        0x0 */
            uint32_t obnd_global_a     : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } obnd_layer_config0;

    /* 0x18 : obnd_layer_config1 */
    union {
        struct {
            uint32_t obnd_global_color_en : 1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_7         : 7; /* [ 7: 1],       rsvd,        0x0 */
            uint32_t obnd_global_rv       : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t obnd_global_gy       : 8; /* [23:16],        r/w,        0x0 */
            uint32_t obnd_global_bu       : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } obnd_layer_config1;

    /* 0x1C : obnd_layer_config2 */
    union {
        struct {
            uint32_t obnd_key_palette_en    : 1; /* [    0],        r/w,        0x0 */
            uint32_t obnd_key_index_inv     : 1; /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_7           : 6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t obnd_key_index_min     : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t obnd_key_index_max     : 8; /* [23:16],        r/w,        0x0 */
            uint32_t obnd_key_replace_index : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } obnd_layer_config2;

    /* 0x20 : obnd_layer_config3 */
    union {
        struct {
            uint32_t obnd_key_a_min  : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t obnd_key_a_max  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t obnd_key_rv_min : 8; /* [23:16],        r/w,        0x0 */
            uint32_t obnd_key_rv_max : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } obnd_layer_config3;

    /* 0x24 : obnd_layer_config4 */
    union {
        struct {
            uint32_t obnd_key_gy_min : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t obnd_key_gy_max : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t obnd_key_bu_min : 8; /* [23:16],        r/w,        0x0 */
            uint32_t obnd_key_bu_max : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } obnd_layer_config4;

    /* 0x28 : obnd_layer_config5 */
    union {
        struct {
            uint32_t obnd_key_replace_a  : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t obnd_key_replace_rv : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t obnd_key_replace_gy : 8; /* [23:16],        r/w,        0x0 */
            uint32_t obnd_key_replace_bu : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } obnd_layer_config5;

    /* 0x2C : obnd_layer_config6 */
    union {
        struct {
            uint32_t obnd_key_color_en   : 1;  /* [    0],        r/w,        0x0 */
            uint32_t obnd_key_a_inv      : 1;  /* [    1],        r/w,        0x0 */
            uint32_t obnd_key_rv_inv     : 1;  /* [    2],        r/w,        0x0 */
            uint32_t obnd_key_gy_inv     : 1;  /* [    3],        r/w,        0x0 */
            uint32_t obnd_key_bu_inv     : 1;  /* [    4],        r/w,        0x0 */
            uint32_t obnd_update_trigger : 1;  /* [    5],        w1p,        0x0 */
            uint32_t reserved_6_7        : 2;  /* [ 7: 6],       rsvd,        0x0 */
            uint32_t obnd_update_index   : 8;  /* [15: 8],        r/w,        0x0 */
            uint32_t reserved_16_31      : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } obnd_layer_config6;

    /* 0x30 : obnd_layer_config7 */
    union {
        struct {
            uint32_t obnd_update_color : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } obnd_layer_config7;

    /* 0x34  reserved */
    uint8_t RESERVED0x34[12];

    /* 0x40 : obnd_error */
    union {
        struct {
            uint32_t reg_rfifo_drain_clr_w  : 1;  /* [    0],        w1p,        0x0 */
            uint32_t reg_rfifo_drain_mask_w : 1;  /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_15          : 14; /* [15: 2],       rsvd,        0x0 */
            uint32_t sts_rfifo_drain_r      : 1;  /* [   16],          r,        0x0 */
            uint32_t reserved_17_31         : 15; /* [31:17],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } obnd_error;

    /* 0x44 : obnd_sh */
    union {
        struct {
            uint32_t obnd_layer_mem_req_cnt : 32; /* [31: 0],        r/w,     0x1000 */
        } BF;
        uint32_t WORD;
    } obnd_sh;
};

typedef volatile struct osd_blend_reg osd_blend_reg_t;

#endif /* __OSD_BLEND_REG_H__ */
