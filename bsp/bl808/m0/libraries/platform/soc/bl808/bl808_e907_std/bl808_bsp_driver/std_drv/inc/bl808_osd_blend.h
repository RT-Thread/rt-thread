/**
  ******************************************************************************
  * @file    bl808_osd_blend.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2021 Bouffalo Lab</center></h2>
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

#ifndef __BL808_OSD_BLEND_H__
#define __BL808_OSD_BLEND_H__

#include <stdint.h>
#include "bl808_common.h"
#include "osd_blend_reg.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  OSD_BLEND
 *  @{
 */

/** @defgroup  OSD_BLEND_Public_Macros
 *  @{
 */

/** @defgroup  OSD_BLEND layer definitions
 *  @{
 */

#define OSD_A_BLEND_LAYER0 ((osd_blend_reg_t *)(OSD_A_BASE + OSD_BLEND0_OFFSET))
#define OSD_A_BLEND_LAYER1 ((osd_blend_reg_t *)(OSD_A_BASE + OSD_BLEND1_OFFSET))
#define OSD_A_BLEND_LAYER2 ((osd_blend_reg_t *)(OSD_A_BASE + OSD_BLEND2_OFFSET))
#define OSD_A_BLEND_LAYER3 ((osd_blend_reg_t *)(OSD_A_BASE + OSD_BLEND3_OFFSET))

#define OSD_B_BLEND_LAYER0 ((osd_blend_reg_t *)(OSD_B_BASE + OSD_BLEND0_OFFSET))
#define OSD_B_BLEND_LAYER1 ((osd_blend_reg_t *)(OSD_B_BASE + OSD_BLEND1_OFFSET))

#define OSD_DP_BLEND_LAYER0 ((osd_blend_reg_t *)(OSD_DP_BASE + OSD_BLEND0_OFFSET))
#define OSD_DP_BLEND_LAYER1 ((osd_blend_reg_t *)(OSD_DP_BASE + OSD_BLEND1_OFFSET))
#define OSD_DP_BLEND_LAYER2 ((osd_blend_reg_t *)(OSD_DP_BASE + OSD_BLEND2_OFFSET))
#define OSD_DP_BLEND_LAYER3 ((osd_blend_reg_t *)(OSD_DP_BASE + OSD_BLEND3_OFFSET))

/*@} end of group OSD_BLEND_Public_Macros */

/** @defgroup  OSD_BLEND_Public_Constants
 *  @{
 */

/*@} end of group OSD_BLEND_Public_Constants */

/** @defgroup  OSD_BLEND_Public_Types
 *  @{
 */

/**
 *  @brief OSD_BLEND state control definition
 */
typedef enum {
    OSD_BLEND_ST_ENABLE = 0,
    OSD_BLEND_ST_DISABLE,
    OSD_BLEND_ST_MAX = 0x7FFFFFFF
} OSD_BLEND_ST_e;

/* order --- from LSB to MSB.
 * eg1: order_a = 3, order_rv=2, order_gy=1, order_bu=0
 * Byte Address: 0x7   0x6   0x5   0x4   0x3   0x2   0x1   0x0
 *     ARGB8888:  A1    R1    G1    B1    A0    R0    G0    B0
 *
 * eg2: order_a = 3, order_rv=0, order_gy=2, order_bu=1
 * Byte Address: 0x7   0x6   0x5   0x4   0x3   0x2   0x1   0x0
 *     AYUV8888:  A1    Y1    U1    V1    A0    Y0    U0    V0
 */

typedef enum {
    OSD_BLEND_COLOR_ORDER0 = 0,
    OSD_BLEND_COLOR_ORDER1,
    OSD_BLEND_COLOR_ORDER2,
    OSD_BLEND_COLOR_ORDER3,
    OSD_BLEND_COLOR_ORDER_MAX = 0x7F
} OSD_BLEND_COLOR_ORDER_e;

typedef enum {
    OSD_BLEND_COLOR_FMT_ARGB8888 = 0,
    OSD_BLEND_COLOR_FMT_AYUV8888,
    OSD_BLEND_COLOR_FMT_ARGB4444,
    OSD_BLEND_COLOR_FMT_AYUV4444,
    OSD_BLEND_COLOR_FMT_ARGB1555,
    OSD_BLEND_COLOR_FMT_AYUV1555,
    OSD_BLEND_COLOR_FMT_RGB565,
    OSD_BLEND_COLOR_FMT_YUV655,
    OSD_BLEND_COLOR_FMT_A8RGB,
    OSD_BLEND_COLOR_FMT_A8YUV,
    OSD_BLEND_COLOR_FMT_BPP8ARGB = 0x10,
    OSD_BLEND_COLOR_FMT_BPP8AYUV,
    OSD_BLEND_COLOR_FMT_BPP4ARGB,
    OSD_BLEND_COLOR_FMT_BPP4AYUV,
    OSD_BLEND_COLOR_FMT_BPP2ARGB,
    OSD_BLEND_COLOR_FMT_BPP2AYUV,
    OSD_BLEND_COLOR_FMT_BPP1ARGB,
    OSD_BLEND_COLOR_FMT_BPP1AYUV,
    OSD_BLEND_COLOR_FMT_CNT,
    OSD_BLEND_COLOR_FMT_MAX = 0x7F
} OSD_BLEND_COLOR_FMT_e;

/* OSD blending keying mode: nomarl or invert */
typedef enum {
    OSB_BLEND_KEYING_NORMAL = 0,
    OSB_BLEND_KEYING_INVERT,
    OSB_BLEND_KEYING_MAX = 0x7F
} OSB_BLEND_KEYING_MODE_e;

typedef struct _osd_blend_color_keying_set_ {
    /* obnd_layer_config3 */
    uint8_t min_key_alpha;
    uint8_t max_key_alpha;
    uint8_t min_key_rv;
    uint8_t max_key_rv;
    /* obnd_layer_config4 */
    uint8_t min_key_gy;
    uint8_t max_key_gy;
    uint8_t min_key_bu;
    uint8_t max_key_bu;
    /* obnd_layer_config5 */
    uint8_t replace_alpha;
    uint8_t replace_rv;
    uint8_t replace_gy;
    uint8_t replace_bu;
    /* obnd_layer_config6 */
    OSB_BLEND_KEYING_MODE_e mode_alpha;
    OSB_BLEND_KEYING_MODE_e mode_rv;
    OSB_BLEND_KEYING_MODE_e mode_gy;
    OSB_BLEND_KEYING_MODE_e mode_bu;
} osd_blend_color_keying_set_t;

/*@} end of group OSD_BLEND_Public_Types */

/** @defgroup  OSD_BLEND_Public_Functions
 *  @{
 */

BL_Err_Type osd_blend_config_layer(osd_blend_reg_t *pblend,
                                   uint32_t xstart, uint32_t ystart,
                                   uint32_t xend, uint32_t yend,
                                   uintptr_t *data, uint32_t dat_len);

BL_Err_Type osd_blend_mem_access_line(osd_blend_reg_t *pblend, uint32_t req_hlen);
BL_Err_Type osd_blend_layer_early_commit(osd_blend_reg_t *pblend);
BL_Err_Type osd_blend_ctrl_layer(osd_blend_reg_t *pblend, OSD_BLEND_ST_e enable);

BL_Err_Type osd_blend_set_color_format(osd_blend_reg_t *pblend, OSD_BLEND_COLOR_FMT_e fmt,
                                       OSD_BLEND_COLOR_ORDER_e order_alpha,
                                       OSD_BLEND_COLOR_ORDER_e order_r_v,
                                       OSD_BLEND_COLOR_ORDER_e order_g_y,
                                       OSD_BLEND_COLOR_ORDER_e order_b_u);

BL_Err_Type osd_blend_set_global_alpha(osd_blend_reg_t *pblend, uint32_t enable,
                                       uint8_t alpha);
BL_Err_Type osd_blend_set_global_color(osd_blend_reg_t *pblend, uint32_t enable,
                                       uint8_t r_v, uint8_t g_y, uint8_t b_u);

BL_Err_Type osd_blend_update_palette(osd_blend_reg_t *pblend, uint32_t color, uint8_t index);

BL_Err_Type osd_blend_palette_keying_ctrl(osd_blend_reg_t *pblend, OSD_BLEND_ST_e enable);

BL_Err_Type osd_blend_palette_keying(osd_blend_reg_t *pblend, OSD_BLEND_ST_e enable,
                                     OSB_BLEND_KEYING_MODE_e mode,
                                     uint8_t replace_index,
                                     uint8_t min_key_index, uint8_t max_key_index);

BL_Err_Type osd_blend_palette_keying_update_range(osd_blend_reg_t *pblend,
                                                  uint8_t min_key_index, uint8_t max_key_index);

BL_Err_Type osd_blend_color_keying(osd_blend_reg_t *pblend, OSD_BLEND_ST_e enable,
                                   osd_blend_color_keying_set_t *pset);

/*@} end of group OSD_BLEND_Public_Functions */

/*@} end of group OSD_BLEND */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_OSD_BLEND_H__ */
