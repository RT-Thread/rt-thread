/**
  ******************************************************************************
  * @file    bl808_dsp2_wdr.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
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
#ifndef __BL808_DSP2_WDR_H__
#define __BL808_DSP2_WDR_H__

#include "bl808_common.h"
#include "bl808_dsp2.h"

#define DSP2_WDR_HIST_BIN_NUM   (65)
#define DSP2_WDR_CURVE_COEF_NUM (64)

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DSP2_WDR
 *  @{
 */

/** @defgroup  DSP2_WDR_Public_Types
 *  @{
 */

/**
 *  @brief WDR hist data struct definition
 */
typedef struct
{
    uint32_t hist_bin[DSP2_WDR_HIST_BIN_NUM];
} DSP2_WDR_Hist_Data_Type;

/**
 *  @brief WDR curve strcut definition
 */
typedef struct
{
    uint16_t curve_coef[DSP2_WDR_CURVE_COEF_NUM];
} DSP2_WDR_Curve_Type;

/*@} end of group DSP2_WDR_Public_Types */

/** @defgroup  DSP2_WDR_Public_Constants
 *  @{
 */

/*@} end of group DSP2_WDR_Public_Constants */

/** @defgroup  DSP2_WDR_Public_Macros
 *  @{
 */

/*@} end of group DSP2_WDR_Public_Macros */

/** @defgroup  DSP2_WDR_Public_Functions
 *  @{
 */
void DSP2_WDR_Get_WDR_State(BL_Fun_Type *state);
void DSP2_WDR_Set_WDR_State(BL_Fun_Type state);
void DSP2_WDR_Set_CS_State(BL_Fun_Type state);
void DSP2_WDR_Set_CS_Config(const DSP2_Chroma_Suppress_Type *chromaSupprCfg);
void DSP2_WDR_Get_CS_Config(DSP2_Chroma_Suppress_Type *chromaSupprCfg);
void DSP2_WDR_Set_ROI_State(int roi_id, BL_Fun_Type state);
void DSP2_WDR_Set_ROI_Position(int roi_id, uint32_t left_x, uint32_t right_x,
                              uint32_t top_y, uint32_t bottom_y);
void DSP2_WDR_Set_ROI_Weight(int roi_id, uint32_t weight);
int DSP2_WDR_Get_Hist_Data(DSP2_WDR_Hist_Data_Type *hist);
void DSP2_WDR_Set_WDR_Curve_State(BL_Fun_Type state);
void DSP2_WDR_Set_WDR_Curve(const DSP2_WDR_Curve_Type *wdr_curve);
void DSP2_WDR_Get_WDR_Curve(DSP2_WDR_Curve_Type *wdr_curve);
void DSP2_WDR_Set_WDR_Curve_Weight(uint32_t weight);
void DSP2_WDR_Get_WDR_Curve_Weight(uint32_t *weight);
void DSP2_WDR_Set_Post_Enhance_State(BL_Fun_Type state);
void DSP2_WDR_Set_Post_Enhance_Weight(uint32_t weight);
void DSP2_WDR_Get_Post_Enhance_Weight(uint32_t *weight);
void DSP2_WDR_Set_Post_Enhance_Y_Offset(uint32_t y_offset);
void DSP2_WDR_Get_Post_Enhance_Y_Offset(uint32_t *y_offset);
void DSP2_WDR_Set_Post_Enhance_Luma_Gain(uint32_t gain);
void DSP2_WDR_Get_Post_Enhance_Luma_Gain(uint32_t *gain);
void DSP2_WDR_Set_Post_Enhance_Chroma_Gain(uint32_t gain);
void DSP2_WDR_Get_Post_Enhance_Chroma_Gain(uint32_t *gain);

/*@} end of group DSP2_WDR_Public_Functions */

/*@} end of group DSP2_WDR */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_DSP2_WDR_H__ */
