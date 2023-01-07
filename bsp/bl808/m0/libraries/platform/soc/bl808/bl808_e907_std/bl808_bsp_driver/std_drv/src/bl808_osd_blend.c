/**
  ******************************************************************************
  * @file    bl808_osd_blend.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
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

#include "bl808_osd_blend.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  OSD_BLEND
 *  @{
 */

/** @defgroup  OSD_BLEND_Private_Macros
 *  @{
 */

/*@} end of group OSD_BLEND_Private_Macros */

/** @defgroup  OSD_BLEND_Private_Types
 *  @{
 */

/*@} end of group OSD_BLEND_Private_Types */

/** @defgroup  OSD_BLEND_Private_Variables
 *  @{
 */

/*@} end of group OSD_BLEND_Private_Variables */

/** @defgroup  OSD_BLEND_Global_Variables
 *  @{
 */

/*@} end of group OSD_BLEND_Global_Variables */

/** @defgroup  OSD_BLEND_Private_Fun_Declaration
 *  @{
 */

/*@} end of group OSD_BLEND_Private_Fun_Declaration */

/** @defgroup  OSD_BLEND_Private_Functions
 *  @{
 */

/*@} end of group OSD_BLEND_Private_Functions */

/** @defgroup  OSD_BLEND_Public_Functions
 *  @{
 */

/******************************************************************************
 * @brief  OSD blend layer configuration
 *
 * @param  pblend: pointer to a specific OSD blend layer
 * @param  xstart: OSD layer start point: x-axis, better to be even.
 * @param  ystart: OSD layer start point: y-axis, better to be even.
 * @param  xend: OSD layer end point: x-axis, better to be odd.
 * @param  yend: OSD layer end point: y-axis, better to be odd.
 * @param  data: OSD layer data buffer pointer.
 * @param  dat_len: data length in dword size(8bytes).
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_blend_config_layer(osd_blend_reg_t *pblend,
                                   uint32_t xstart, uint32_t ystart,
                                   uint32_t xend, uint32_t yend,
                                   uintptr_t *data, uint32_t dat_len)
{
    pblend->obnd_layer_xconfig.WORD = (xstart & OSD_BLEND_OBND_X_MIN_MSK) |
                                      ((xend << OSD_BLEND_OBND_X_MAX_POS) & OSD_BLEND_OBND_X_MAX_MSK);
    pblend->obnd_layer_yconfig.WORD = (ystart & OSD_BLEND_OBND_Y_MIN_MSK) |
                                      ((yend << OSD_BLEND_OBND_Y_MAX_POS) & OSD_BLEND_OBND_Y_MAX_MSK);

    pblend->obnd_mem_config1.WORD = (uint32_t)(uintptr_t)data;
    pblend->obnd_mem_config2.WORD = dat_len;

    return SUCCESS;
}

/******************************************************************************
 * @brief  OSD blend layer mem access timing configuration
 *
 * @param  pblend: pointer to a specific OSD blend layer
 * @param  req_hlen: memory access timing setting in H-SYNC cycles after V-SYNC.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_blend_mem_access_line(osd_blend_reg_t *pblend, uint32_t req_hlen)
{
    pblend->obnd_sh.BF.obnd_layer_mem_req_cnt = req_hlen;

    return SUCCESS;
}

/******************************************************************************
 * @brief  OSD blend layer force shadow control:
 *         call this API before DSP2 streaming on to ensure the OSD layer 
 *         is activated even in frame 0.
 *         After calling this API, this OSD blending layer has to be enabled.
 *
 * @param  pblend: pointer to a specific OSD blend layer
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_blend_layer_early_commit(osd_blend_reg_t *pblend)
{
    uint32_t val = 0;

    val = pblend->obnd_mem_config0.WORD;
    /* disable this layer */
    val &= OSD_BLEND_OBND_LAYER_EN_UMSK;
    /* set OSD blend force shadow bit, so that the settings will be loaded
     * immediately and mem access will be started after layer is enabled.
     */
    val |= OSD_BLEND_OBND_FORCE_SH_MSK;
    pblend->obnd_mem_config0.WORD = val;

    return SUCCESS;
}

/******************************************************************************
 * @brief  OSD blend layer enable/disable control
 *
 * @param  pblend: pointer to a specific OSD blend layer
 * @param  enable: requested state of this blend layer.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_blend_ctrl_layer(osd_blend_reg_t *pblend, OSD_BLEND_ST_e enable)
{
    uint32_t val = 0;

    val = pblend->obnd_mem_config0.WORD;
    val &= OSD_BLEND_OBND_LAYER_EN_UMSK;
    val |= (OSD_BLEND_ST_ENABLE == enable) ? OSD_BLEND_OBND_LAYER_EN_MSK : 0;
    pblend->obnd_mem_config0.WORD = val;

    return SUCCESS;
}

/******************************************************************************
 * @brief  OSD blend layer color format configuration
 *
 * @param  pblend: pointer to a specific OSD blend layer
 * @param  fmt: color format.
 * @param  order_alpha: order of the alpha.
 * @param  order_r_v: order of the red(RGB) or v(YUV).
 * @param  order_g_y: order of the green(RGB) or y(YUV).
 * @param  order_b_u: order of the blue(RGB) or u(YUV).
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_blend_set_color_format(osd_blend_reg_t *pblend, OSD_BLEND_COLOR_FMT_e fmt,
                                       OSD_BLEND_COLOR_ORDER_e order_alpha,
                                       OSD_BLEND_COLOR_ORDER_e order_r_v,
                                       OSD_BLEND_COLOR_ORDER_e order_g_y,
                                       OSD_BLEND_COLOR_ORDER_e order_b_u)
{
    uint32_t val = 0;

    val = pblend->obnd_layer_config0.WORD;
    val &= ~(OSD_BLEND_OBND_COLOR_FORMAT_MSK |
             OSD_BLEND_OBND_ORDER_A_MSK |
             OSD_BLEND_OBND_ORDER_RV_MSK |
             OSD_BLEND_OBND_ORDER_GY_MSK |
             OSD_BLEND_OBND_ORDER_BU_MSK);

    val |= fmt << OSD_BLEND_OBND_COLOR_FORMAT_POS;
    val |= order_alpha << OSD_BLEND_OBND_ORDER_A_POS;
    val |= order_r_v << OSD_BLEND_OBND_ORDER_RV_POS;
    val |= order_g_y << OSD_BLEND_OBND_ORDER_GY_POS;
    val |= order_b_u << OSD_BLEND_OBND_ORDER_BU_POS;

    pblend->obnd_layer_config0.WORD = val;

    return SUCCESS;
}

/******************************************************************************
 * @brief  OSD blend layer global alpha configuration
 *
 * @param  pblend: pointer to a specific OSD blend layer
 * @param  enable: enable or disable the global alpha for this layer.
 * @param  alpha: value of the alpha.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_blend_set_global_alpha(osd_blend_reg_t *pblend, uint32_t enable,
                                       uint8_t alpha)
{
    uint32_t val = 0;

    val = pblend->obnd_layer_config0.WORD;
    val &= OSD_BLEND_OBND_GLOBAL_A_UMSK;
    val &= OSD_BLEND_OBND_GLOBAL_A_EN_UMSK;
    val |= (alpha << OSD_BLEND_OBND_GLOBAL_A_POS) & OSD_BLEND_OBND_GLOBAL_A_MSK;
    val |= (OSD_BLEND_ST_ENABLE == enable) ? OSD_BLEND_OBND_GLOBAL_A_EN_MSK : 0;
    pblend->obnd_layer_config0.WORD = val;
    return SUCCESS;
}

/******************************************************************************
 * @brief  OSD blend layer global color configuration
 *
 * @param  pblend: pointer to a specific OSD blend layer
 * @param  enable: enable or disable the global color for this layer.
 * @param  r_v: value of the red(RGB) or v(YUV).
 * @param  g_y: value of the green(RGB) or y(YUV).
 * @param  b_u: value of the blue(RGB) or u(YUV).
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_blend_set_global_color(osd_blend_reg_t *pblend, uint32_t enable,
                                       uint8_t r_v, uint8_t g_y, uint8_t b_u)
{
    uint32_t val = 0;

    val = (OSD_BLEND_ST_ENABLE == enable) ? OSD_BLEND_OBND_GLOBAL_COLOR_EN_MSK : 0;
    val |= (r_v << OSD_BLEND_OBND_GLOBAL_RV_POS) & OSD_BLEND_OBND_GLOBAL_RV_MSK;
    val |= (g_y << OSD_BLEND_OBND_GLOBAL_GY_POS) & OSD_BLEND_OBND_GLOBAL_GY_MSK;
    val |= (b_u << OSD_BLEND_OBND_GLOBAL_BU_POS) & OSD_BLEND_OBND_GLOBAL_BU_MSK;
    pblend->obnd_layer_config1.WORD = val;

    return SUCCESS;
}

/******************************************************************************
 * @brief  OSD blend layer update palette value according to the index.
 *
 * @param  pblend: pointer to a specific OSD blend layer
 * @param  color: palette color, can be format ARGB8888 or AYUV8888.
 * @param  index: the palette index for updating.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_blend_update_palette(osd_blend_reg_t *pblend, uint32_t color, uint8_t index)
{
    uint32_t val = 0;

    /* palette should be updated when blend is disabled. */

    pblend->obnd_layer_config7.WORD = color;
    val = pblend->obnd_layer_config6.WORD;
    val &= OSD_BLEND_OBND_UPDATE_INDEX_UMSK;
    val |= index << OSD_BLEND_OBND_UPDATE_INDEX_POS;

    /* trigger update */
    val |= OSD_BLEND_OBND_UPDATE_TRIGGER_MSK;
    pblend->obnd_layer_config6.WORD = val;
    arch_delay_us(1);

    return SUCCESS;
}

/******************************************************************************
 * @brief  OSD blend layer palette keying control.
 *
 * @param  pblend: pointer to a specific OSD blend layer
 * @param  enable: enable or disable the palette keying for this layer.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_blend_palette_keying_ctrl(osd_blend_reg_t *pblend, OSD_BLEND_ST_e enable)
{
    uint32_t val = 0;

    val = pblend->obnd_layer_config2.WORD;
    val &= OSD_BLEND_OBND_KEY_PALETTE_EN_UMSK;

    val |= (OSD_BLEND_ST_ENABLE == enable) ? OSD_BLEND_OBND_KEY_PALETTE_EN_MSK : 0;

    pblend->obnd_layer_config2.WORD = val;
    return SUCCESS;
}

/******************************************************************************
 * @brief  OSD blend layer palette keying configuration.
 *
 * @param  pblend: pointer to a specific OSD blend layer
 * @param  enable: enable or disable the palette keying for this layer.
 * @param  mode: palette keying mode: within or out of the min/max range.
 * @param  replace_index: the palette index that will be used as the replace color.
 * @param  min_key_index: min index for the palette keying.
 * @param  max_key_index: max index for the palette keying.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_blend_palette_keying(osd_blend_reg_t *pblend, OSD_BLEND_ST_e enable,
                                     OSB_BLEND_KEYING_MODE_e mode,
                                     uint8_t replace_index,
                                     uint8_t min_key_index, uint8_t max_key_index)
{
    uint32_t val = 0;

    /* disable palette keying */
    val = pblend->obnd_layer_config2.WORD;
    val &= OSD_BLEND_OBND_KEY_PALETTE_EN_UMSK;
    pblend->obnd_layer_config2.WORD = val;

    /* it is done if palette keying mode is disabled */
    if (OSD_BLEND_ST_ENABLE != enable) {
        return SUCCESS;
    }

    val |= (OSD_BLEND_ST_ENABLE == enable) ? OSD_BLEND_OBND_KEY_PALETTE_EN_MSK : 0;
    val |= (OSB_BLEND_KEYING_INVERT == mode) ? OSD_BLEND_OBND_KEY_INDEX_INV_MSK : 0;
    val |= (min_key_index << OSD_BLEND_OBND_KEY_INDEX_MIN_POS) & OSD_BLEND_OBND_KEY_INDEX_MIN_MSK;
    val |= (max_key_index << OSD_BLEND_OBND_KEY_INDEX_MAX_POS) & OSD_BLEND_OBND_KEY_INDEX_MAX_MSK;
    val |= (replace_index << OSD_BLEND_OBND_KEY_REPLACE_INDEX_POS) &
           OSD_BLEND_OBND_KEY_REPLACE_INDEX_MSK;

    pblend->obnd_layer_config2.WORD = val;

    return SUCCESS;
}

/******************************************************************************
 * @brief  OSD blend layer palette keying min/max updating control.
 *
 * @param  pblend: pointer to a specific OSD blend layer
 * @param  min_key_index: min index for the palette keying.
 * @param  max_key_index: max index for the palette keying.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_blend_palette_keying_update_range(osd_blend_reg_t *pblend,
                                                  uint8_t min_key_index, uint8_t max_key_index)
{
    uint32_t val = 0;

    val = pblend->obnd_layer_config2.WORD;

    val &= OSD_BLEND_OBND_KEY_INDEX_MIN_UMSK;
    val &= OSD_BLEND_OBND_KEY_INDEX_MAX_UMSK;
    val |= (min_key_index << OSD_BLEND_OBND_KEY_INDEX_MIN_POS) & OSD_BLEND_OBND_KEY_INDEX_MIN_MSK;
    val |= (max_key_index << OSD_BLEND_OBND_KEY_INDEX_MAX_POS) & OSD_BLEND_OBND_KEY_INDEX_MAX_MSK;

    pblend->obnd_layer_config2.WORD = val;

    return SUCCESS;
}

/******************************************************************************
 * @brief  OSD blend layer color keying configuration.
 *
 * @param  pblend: pointer to a specific OSD blend layer
 * @param  enable: enable or disable the color keying for this layer.
 * @param  pset: point to the color keying setting.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_blend_color_keying(osd_blend_reg_t *pblend, OSD_BLEND_ST_e enable,
                                   osd_blend_color_keying_set_t *pset)
{
    uint32_t val = 0;

    CHECK_PARAM(NULL != pset);

    /* disable color keying */
    val = pblend->obnd_layer_config6.WORD;
    val &= OSD_BLEND_OBND_KEY_COLOR_EN_UMSK;
    pblend->obnd_layer_config6.WORD = val;

    /* it is done if color keying mode is disabled */
    if (OSD_BLEND_ST_ENABLE != enable) {
        return SUCCESS;
    }

    /* layer_config3: min & max for alpha and rv */
    val = pset->min_key_alpha << OSD_BLEND_OBND_KEY_A_MIN_POS;
    val |= pset->max_key_alpha << OSD_BLEND_OBND_KEY_A_MAX_POS;
    val |= pset->min_key_rv << OSD_BLEND_OBND_KEY_RV_MIN_POS;
    val |= pset->max_key_rv << OSD_BLEND_OBND_KEY_RV_MAX_POS;
    pblend->obnd_layer_config3.WORD = val;

    /* layer_config4: min & max for gy and bu */
    val = pset->min_key_gy << OSD_BLEND_OBND_KEY_GY_MIN_POS;
    val |= pset->max_key_gy << OSD_BLEND_OBND_KEY_GY_MAX_POS;
    val |= pset->min_key_bu << OSD_BLEND_OBND_KEY_BU_MIN_POS;
    val |= pset->max_key_bu << OSD_BLEND_OBND_KEY_BU_MAX_POS;
    pblend->obnd_layer_config4.WORD = val;

    /* layer_config5: replace color */
    val = pset->replace_alpha << OSD_BLEND_OBND_KEY_REPLACE_A_POS;
    val |= pset->replace_rv << OSD_BLEND_OBND_KEY_REPLACE_RV_POS;
    val |= pset->replace_gy << OSD_BLEND_OBND_KEY_REPLACE_GY_POS;
    val |= pset->replace_bu << OSD_BLEND_OBND_KEY_REPLACE_BU_POS;
    pblend->obnd_layer_config5.WORD = val;

    /* color range inverted? */
    val = pblend->obnd_layer_config6.WORD;
    val &= ~(OSD_BLEND_OBND_KEY_A_INV_MSK |
             OSD_BLEND_OBND_KEY_RV_INV_MSK |
             OSD_BLEND_OBND_KEY_GY_INV_MSK |
             OSD_BLEND_OBND_KEY_BU_INV_MSK);
    val |= (OSB_BLEND_KEYING_INVERT == pset->mode_alpha) ?
               OSD_BLEND_OBND_KEY_A_INV_MSK :
               0;
    val |= (OSB_BLEND_KEYING_INVERT == pset->mode_rv) ?
               OSD_BLEND_OBND_KEY_RV_INV_MSK :
               0;
    val |= (OSB_BLEND_KEYING_INVERT == pset->mode_gy) ?
               OSD_BLEND_OBND_KEY_GY_INV_MSK :
               0;
    val |= (OSB_BLEND_KEYING_INVERT == pset->mode_bu) ?
               OSD_BLEND_OBND_KEY_BU_INV_MSK :
               0;

    /* enable color keying */
    val |= OSD_BLEND_OBND_KEY_COLOR_EN_MSK;
    pblend->obnd_layer_config6.WORD = val;

    return SUCCESS;
}

/*@} end of group OSD_BLEND_Public_Functions */

/*@} end of group OSD_BLEND */

/*@} end of group BL808_Peripheral_Driver */
