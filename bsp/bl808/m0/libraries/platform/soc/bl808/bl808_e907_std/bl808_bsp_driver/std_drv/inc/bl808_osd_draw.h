/**
  ******************************************************************************
  * @file    bl808_osd_draw.h
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

#ifndef __BL808_OSD_H__
#define __BL808_OSD_H__

#include <stdint.h>
#include "bl808_common.h"
#include "osd_draw_reg.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  OSD_DRAW
 *  @{
 */

/** @defgroup  OSD_DRAW_Public_Macros
 *  @{
 */

/** @defgroup  OSD_DRAW layer definitions
 *  @{
 */

#define OSD_A_DRAW_LAYER_L ((osd_draw_reg_t *)(OSD_A_BASE + OSD_DRAW_LOW_OFFSET))
#define OSD_A_DRAW_LAYER_H ((osd_draw_reg_t *)(OSD_A_BASE + OSD_DRAW_HIGH_OFFSET))

#define OSD_B_DRAW_LAYER_L ((osd_draw_reg_t *)(OSD_B_BASE + OSD_DRAW_LOW_OFFSET))

#define OSD_DP_DRAW_LAYER_L ((osd_draw_reg_t *)(OSD_DP_BASE + OSD_DRAW_LOW_OFFSET))
#define OSD_DP_DRAW_LAYER_H ((osd_draw_reg_t *)(OSD_DP_BASE + OSD_DRAW_HIGH_OFFSET))

/*@} end of group OSD_DRAW_Public_Macros */
/** @defgroup  OSD_DRAW_Public_Constants
 *  @{
 */

/*@} end of group OSD_DRAW_Public_Constants */

/** @defgroup  OSD_DRAW_Public_Types
 *  @{
 */

/**
 *  @brief OSD_DRAW rectangle style definition
 */

typedef enum {
    OSD_RECT_STYLE_HOLLOW = 0,
    OSD_RECT_STYLE_SOLID = 1,
    OSD_RECT_STYLE_NUM,
    OSD_RECT_STYLE_MAX = 0x7fffffff
} OSD_RECT_STYLE_Type;

/**
 *  @brief OSD_DRAW rectangle state definition
 */

typedef enum {
    OSD_RECT_STATE_DISABLE = 0,
    OSD_RECT_STATE_ENABLE = 1,
    OSD_RECT_STATE_NUM,
    OSD_RECT_STATE_MAX = 0x7fffffff
} OSD_RECT_STATE_Type;

/**
 *  @brief OSD_DRAW rectangle attribute definition
 */

typedef union _osd_attribute {
    struct
    {
        uint32_t thinkness : 8;
        uint32_t v         : 8;
        uint32_t u         : 8;
        uint32_t y         : 8;
#define YUV2ATTR(y, u, v)     ((y << 24) | (u << 16) | (v << 8))
#define OSD_COLOR_BLACK       YUV2ATTR(0, 128, 128)
#define OSD_COLOR_WHITE       YUV2ATTR(255, 128, 128)
#define OSD_COLOR_SILVER      YUV2ATTR(192, 128, 128)
#define OSD_COLOR_GRAY        YUV2ATTR(127, 128, 128)
#define OSD_COLOR_DIMGRAY     YUV2ATTR(105, 128, 128)
#define OSD_COLOR_RED         YUV2ATTR(76, 84, 255)
#define OSD_COLOR_GREEN       YUV2ATTR(149, 43, 21)
#define OSD_COLOR_BLUE        YUV2ATTR(29, 255, 107)
#define OSD_COLOR_SKYBLUE     YUV2ATTR(188, 154, 90)
#define OSD_COLOR_INDIGO      YUV2ATTR(37, 180, 154)
#define OSD_COLOR_NAVY        YUV2ATTR(14, 192, 117)
#define OSD_COLOR_MAGENTA     YUV2ATTR(105, 212, 234)
#define OSD_COLOR_PURPLE      YUV2ATTR(52, 170, 181)
#define OSD_COLOR_CYAN        YUV2ATTR(178, 171, 0)
#define OSD_COLOR_TEAL        YUV2ATTR(89, 149, 64)
#define OSD_COLOR_PINK        YUV2ATTR(212, 122, 158)
#define OSD_COLOR_DEEPPINK    YUV2ATTR(104, 151, 235)
#define OSD_COLOR_YELLOW      YUV2ATTR(255, 0, 148)
#define OSD_COLOR_GREENYELLOW YUV2ATTR(206, 37, 103)
#define OSD_COLOR_GOLD        YUV2ATTR(202, 13, 165)
#define OSD_COLOR_CHOCOLATE   YUV2ATTR(127, 72, 186)
#define OSD_COLOR_ORANGE      YUV2ATTR(173, 30, 186)
    } yuvt;
    uint32_t all;
} osd_attribute_t;

/**
 *  @brief OSD_DRAW rectangle axis settings
 */

typedef struct _osd_pos_axis {
    uint32_t start : 11; /* must be EVEN */
    uint32_t rsvd0 : 5;
    uint32_t end   : 11; /* must be ODD */
    uint32_t rsvd1 : 5;
} osd_pos_axis_t;

/**
 *  @brief OSD_DRAW rectangle position definition
 */

typedef struct _osd_rectangle_position {
    osd_pos_axis_t x;
    osd_pos_axis_t y;
} osd_rectangle_pos_t;

/**
 *  @brief OSD_DRAW rectangle descriptor definition
 */

typedef struct _osd_rectangle_descriptor {
    osd_attribute_t attr;
    osd_rectangle_pos_t pos;
} osd_rectangle_desc_t;

/**
 *  @brief OSD_DRAW rectangle definition
 */

#define OSD_RECT_DESC_OFFSET(osd_draw)  ((uintptr_t)(osd_draw) + 0x4)
#define OSD_RECT_DESC_SIZE              (4 * 3)
#define OSD_RECT_DESC_ADDR(osd_draw, i) (OSD_RECT_DESC_OFFSET(osd_draw) + (i)*OSD_RECT_DESC_SIZE)
#define OSD_RECT_DESC(osd_draw, i)      (osd_rectangle_desc_t *)((uintptr_t)(OSD_RECT_DESC_ADDR(osd_draw, i)))

typedef struct _osd_rectangle {
    osd_rectangle_desc_t desc;

#define OSD_MAX_LAYER      (16)
#define OSD_ALL_LAYER      (-1)
#define OSD_VALID_LAYER(l) ((l)&0x0F)
    uint32_t layer;
    OSD_RECT_STYLE_Type style;
} osd_rectangle_t;

/*@} end of group OSD_DRAW_Public_Types */

/** @defgroup  OSD_DRAW_Public_Functions
 *  @{
 */

BL_Err_Type osd_draw_init(osd_draw_reg_t *odraw);
BL_Err_Type osd_draw_deinit(osd_draw_reg_t *odraw);

BL_Err_Type osd_draw_set_layer_state(osd_draw_reg_t *odraw, uint32_t layer, OSD_RECT_STATE_Type state);
BL_Err_Type osd_draw_get_layer_state(osd_draw_reg_t *odraw, uint32_t layer, OSD_RECT_STATE_Type *state);
BL_Err_Type osd_draw_set_layer_style(osd_draw_reg_t *odraw, uint32_t layer, OSD_RECT_STYLE_Type style);
BL_Err_Type osd_draw_get_layer_style(osd_draw_reg_t *odraw, uint32_t layer, OSD_RECT_STYLE_Type *style);
BL_Err_Type osd_draw_config_rect_layer(osd_draw_reg_t *odraw, uint32_t layer, OSD_RECT_STATE_Type state, OSD_RECT_STYLE_Type style);

BL_Err_Type osd_draw_rectangle(osd_draw_reg_t *odraw, osd_rectangle_t *rect);

BL_Err_Type osd_draw_rectangle_onTop(osd_draw_reg_t *odraw, osd_rectangle_t *rect, uint32_t *layer);

/*@} end of group OSD_DRAW_Public_Functions */

/*@} end of group OSD_DRAW */

/*@} end of group BL808_Peripheral_Driver */

#endif
