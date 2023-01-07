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

#include "bl808_osd_draw.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  OSD_DRAW
 *  @{
 */

/** @defgroup  OSD_DRAW_Private_Macros
 *  @{
 */

/*@} end of group OSD_DRAW_Private_Macros */

/** @defgroup  OSD_DRAW_Private_Types
 *  @{
 */

/*@} end of group OSD_DRAW_Private_Types */

/** @defgroup  OSD_DRAW_Private_Variables
 *  @{
 */

/*@} end of group OSD_DRAW_Private_Variables */

/** @defgroup  OSD_DRAW_Global_Variables
 *  @{
 */

/*@} end of group OSD_DRAW_Global_Variables */

/** @defgroup  OSD_DRAW_Private_Fun_Declaration
 *  @{
 */

/*@} end of group OSD_DRAW_Private_Fun_Declaration */

/** @defgroup  OSD_DRAW_Private_Functions
 *  @{
 */

/*@} end of group OSD_DRAW_Private_Functions */

/** @defgroup  OSD_DRAW_Public_Functions
 *  @{
 */

/******************************************************************************
 * @brief  OSD draw layer state control
 *
 * @param  odraw: pointer to a specific OSD draw HW IP.
 * @param  layer: draw layer.
 * @param  state: enable or disable the layer in this draw HW IP.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_draw_set_layer_state(osd_draw_reg_t *odraw, uint32_t layer, OSD_RECT_STATE_Type state)
{
    uint32_t tmpval = 0;
    uint32_t layer_mask = 1 << OSD_VALID_LAYER(layer);

    tmpval = odraw->osd_draw_config.WORD;

    if (state == OSD_RECT_STATE_ENABLE) {
        tmpval |= layer_mask;
    } else {
        tmpval &= ~layer_mask;
    }

    odraw->osd_draw_config.WORD = tmpval;
    return SUCCESS;
}

/******************************************************************************
 * @brief  OSD draw layer state get
 *
 * @param  odraw: pointer to a specific OSD draw HW IP.
 * @param  layer: draw layer.
 * @param  state: pointer to return the state value.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_draw_get_layer_state(osd_draw_reg_t *odraw, uint32_t layer, OSD_RECT_STATE_Type *state)
{
    uint32_t tmpval = 0;
    uint32_t layer_mask = 1 << OSD_VALID_LAYER(layer);

    CHECK_PARAM(NULL != odraw);
    CHECK_PARAM(NULL != state);

    tmpval = odraw->osd_draw_config.WORD;
    tmpval &= layer_mask;
    *state = (!!tmpval) ? OSD_RECT_STATE_ENABLE : OSD_RECT_STATE_DISABLE;

    return SUCCESS;
}

/******************************************************************************
 * @brief  OSD draw layer style set
 *
 * @param  odraw: pointer to a specific OSD draw HW IP.
 * @param  layer: draw layer.
 * @param  style: solid or hollow style.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_draw_set_layer_style(osd_draw_reg_t *odraw, uint32_t layer, OSD_RECT_STYLE_Type style)
{
    uint32_t tmpval = 0;
    uint32_t layer_mask = 1 << OSD_VALID_LAYER(layer);

    if (style == OSD_RECT_STYLE_SOLID) {
        tmpval |= layer_mask << OSD_REG_DRAW_TYPE_L_POS;
    } else {
        tmpval &= ~(layer_mask << OSD_REG_DRAW_TYPE_L_POS);
    }

    odraw->osd_draw_config.WORD = tmpval;
    return SUCCESS;
}

/******************************************************************************
 * @brief  OSD draw layer style get
 *
 * @param  odraw: pointer to a specific OSD draw HW IP.
 * @param  layer: draw layer.
 * @param  style: pointer to return the solid or hollow style.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_draw_get_layer_style(osd_draw_reg_t *odraw, uint32_t layer, OSD_RECT_STYLE_Type *style)
{
    uint32_t tmpval = 0;
    uint32_t layer_mask = 1 << OSD_VALID_LAYER(layer);

    CHECK_PARAM(NULL != odraw);
    CHECK_PARAM(NULL != style);

    tmpval = odraw->osd_draw_config.WORD;
    tmpval &= layer_mask << OSD_REG_DRAW_TYPE_L_POS;
    *style = (!!tmpval) ? OSD_RECT_STYLE_SOLID : OSD_RECT_STYLE_HOLLOW;

    return SUCCESS;
}

/******************************************************************************
 * @brief  OSD draw layer control
 *
 * @param  odraw: pointer to a specific OSD draw HW IP.
 * @param  layer: draw layer.
 * @param  state: enable or disable this draw layer.
 * @param  style: solid or hollow style for this layer.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_draw_config_rect_layer(osd_draw_reg_t *odraw, uint32_t layer, OSD_RECT_STATE_Type state, OSD_RECT_STYLE_Type style)
{
    uint32_t tmpval = 0;
    uint32_t layer_mask = 1 << OSD_VALID_LAYER(layer);

    tmpval = odraw->osd_draw_config.WORD;

    if (state == OSD_RECT_STATE_ENABLE) {
        tmpval |= layer_mask;
    } else {
        tmpval &= ~layer_mask;
    }

    if (style == OSD_RECT_STYLE_SOLID) {
        tmpval |= layer_mask << OSD_REG_DRAW_TYPE_L_POS;
    } else {
        tmpval &= ~(layer_mask << OSD_REG_DRAW_TYPE_L_POS);
    }

    odraw->osd_draw_config.WORD = tmpval;
    return SUCCESS;
}

/******************************************************************************
 * @brief  Draw a specific rectangle with OSD draw HW IP.
 *
 * @param  odraw: pointer to a specific OSD draw HW IP.
 * @param  rect: pointer to a rectangle setting structure.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_draw_rectangle(osd_draw_reg_t *odraw, osd_rectangle_t *rect)
{
    osd_rectangle_desc_t *desc = OSD_RECT_DESC((odraw), OSD_VALID_LAYER(rect->layer));

    CHECK_PARAM(NULL != odraw);
    CHECK_PARAM(NULL != rect);

    osd_draw_set_layer_state(odraw, rect->layer, OSD_RECT_STATE_DISABLE);
    desc->attr = rect->desc.attr;

    /* EVEN and ODD */
    rect->desc.pos.x.start &= -2;
    rect->desc.pos.x.end |= 1;
    rect->desc.pos.y.start &= -2;
    rect->desc.pos.y.end |= 1;
    rect->desc.attr.yuvt.thinkness += (rect->desc.attr.yuvt.thinkness & 1) ? 1 : 0;

    desc->pos.x = rect->desc.pos.x;
    desc->pos.y = rect->desc.pos.y;
    osd_draw_config_rect_layer(odraw, rect->layer, OSD_RECT_STATE_ENABLE, rect->style);

    return SUCCESS;
}

/******************************************************************************
 * @brief  Draw a specific rectangle with OSD draw HW IP on the top if possible.
 *
 * @param  odraw: pointer to a specific OSD draw HW IP.
 * @param  rect: pointer to a rectangle setting structure.
 * @param  layer: pointer to return the current drawing layer.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_draw_rectangle_onTop(osd_draw_reg_t *odraw, osd_rectangle_t *rect, uint32_t *layer)
{
    uint32_t tmpval = 0;
    uint32_t draw_layer = 0;

    CHECK_PARAM(NULL != layer);
    CHECK_PARAM(NULL != rect);

    tmpval = odraw->osd_draw_config.WORD;
    tmpval &= 0x0000FFFF;

    tmpval = __CLZ(tmpval);

    if (OSD_MAX_LAYER == tmpval) {
        /* no available TOP layer since all layers used */
        *layer = (uint32_t)-1;
        return NORESC;
    }

    draw_layer = sizeof(uintptr_t) * 8 - tmpval;

    rect->layer = draw_layer;
    *layer = draw_layer;
    osd_draw_rectangle(odraw, rect);

    return SUCCESS;
}

/******************************************************************************
 * @brief  Init the OSD draw HW IP.
 *
 * @param  odraw: pointer to a specific OSD draw HW IP.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_draw_init(osd_draw_reg_t *odraw)
{
    odraw->osd_draw_config.WORD = 0;
    return SUCCESS;
}

/******************************************************************************
 * @brief  DeInit the OSD draw HW IP.
 *
 * @param  odraw: pointer to a specific OSD draw HW IP.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type osd_draw_deinit(osd_draw_reg_t *odraw)
{
    odraw->osd_draw_config.WORD = 0;
    return SUCCESS;
}

/*@} end of group OSD_DRAW_Public_Functions */

/*@} end of group OSD_DRAW */

/*@} end of group BL808_Peripheral_Driver */
