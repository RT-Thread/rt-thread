/**
  ******************************************************************************
  * @file    bl808_dsp2.h
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
#ifndef __BL808_DSP2_H__
#define __BL808_DSP2_H__

#include <stdbool.h>
#include "bl808_common.h"
#include "dsp2_tg_reg.h"
#include "dsp2_front_reg.h"
#include "dsp2_back_reg.h"
#include "dsp2_blback_reg.h"
#include "dsp2_middle_reg.h"
#include "dsp2_middle3_reg.h"
#include "dsp2_middle4_reg.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DSP2
 *  @{
 */

/** @defgroup  DSP2_Public_Types
 *  @{
 */

#define DSP2_EE_LUMA_WEIGHT_NUM (32)
#define DSP2_AWB2_STA_Y_NUM     (5)
#define DSP2_AWB2_STA_C_NUM     (8)
#define CCM_COEF_NUM           (9)
#define GAMMA_COEF_NUM         (256)

/**
 *  @brief Bayer pattern
 */
typedef enum {
    BAYER_PATTERN_RG = 0,
    BAYER_PATTERN_GR,
    BAYER_PATTERN_BG,
    BAYER_PATTERN_GB,
} BAYER_PATTERN_E;

/**
 *  @brief LSC coefficient
 */
typedef enum {
    LSC_COEF_A = 0,
    LSC_COEF_B = 1,
    LSC_COEF_C = 2,
    LSC_COEF_D = 3,
    LSC_COEF_E = 4,
    LSC_COEF_G = 5,
    LSC_COEF_NUM = 6,
} DSP2_LSC_COEF_E;

/**
 *  @brief DSP2 sync mode type definition
 */
typedef enum {
    DSP2_SYNC_MODE_INPUT = 0,
    DSP2_SYNC_MODE_OUTPUT,
    DSP2_SYNC_MODE_OUTPUT_INPUT,
    DSP2_SYNC_MODE_INPUT_VBLANK_NO_TOGGLE,
} DSP2_SYNC_MODE_TYPE;

/**
 *  @brief Color correction matrix coefficient
 */
typedef enum {
    DSP2_CCM_11 = 0,
    DSP2_CCM_12 = 1,
    DSP2_CCM_13 = 2,
    DSP2_CCM_21 = 3,
    DSP2_CCM_22 = 4,
    DSP2_CCM_23 = 5,
    DSP2_CCM_31 = 6,
    DSP2_CCM_32 = 7,
    DSP2_CCM_33 = 8,
} DSP2_CCM_COEF_TYPE_E;

/**
 *  @brief YUV conversion mode
 */
typedef enum {
    DSP2_YUV_CONV_FULL_SCALE = 0,
    DSP2_YUV_CONV_BT601,
} DSP2_YUV_CONV_TYPE;

/**
 *  @brief Defect correction enhance state
 */
typedef enum {
    DSP2_DPC_Enhance1 = 0,
    DSP2_DPC_Enhance2,
    DSP2_DPC_Enhance3,
    DSP2_DPC_Enhance_Num,
} DSP2_DPC_ENHANCE_TYPE;

/**
 *  @brief Defect correction threadhold
 */
typedef enum {
    DSP2_DPC_th1 = 0,
    DSP2_DPC_th2,
    DSP2_DPC_th3,
    DSP2_DPC_th4,
    DSP2_DPC_th5,
    DSP2_DPC_th_Num,
} DSP2_DPC_THRESHOLD_TYPE;

/**
 *  @brief AE grid data type
 */
typedef enum {
    AE_GRID_DATA_RGB = 0,
    AE_GRID_DATA_Y = 1,
} AE_GRID_DATA_TYPE_E;

/**
 *  @brief AWB grid data type
 */
typedef enum {
    AWB_GRID_DATA_RG = 0,
    AWB_GRID_DATA_B = 1,
} AWB_GRID_DATA_TYPE_E;

/**
 *  @brief Image size
 */
typedef struct
{
    uint32_t width;
    uint32_t height;
} BL_Img_Size_T;

/**
 *  @brief RGB sum
 */
typedef struct blRGB_SUM_S {
    uint32_t r_sum;
    uint32_t g_sum;
    uint32_t b_sum;
} RGB_SUM_S;

/**
 *  @brief R,Gr,Gb,B black level
 */
typedef struct blDSP2_CLAMP_S {
    int clamp_r;
    int clamp_gr;
    int clamp_gb;
    int clamp_b;
} DSP2_CLAMP_S;

/**
 *  @brief Color correction matrix coefficient group
 */
typedef struct blDSP2_CCM_COEF_GROUP_S {
    int ccm_coef[CCM_COEF_NUM];
} DSP2_CCM_COEF_S;

/**
 *  @brief Gamma curve type
 */
typedef struct blDSP2_GAMMA_COEF_GROUP_S {
    uint16_t curve_coef[GAMMA_COEF_NUM];
} DSP2_Gamma_Curve_Type;

/**
 *  @brief Saturation
 */
typedef struct blDSP2_SATURATION_S {
    uint32_t saturation_cb;
    uint32_t saturation_cr;
} DSP2_SATURATION_S;

/**
 *  @brief Defect correction enhance state group
 */
typedef struct
{
    BL_Fun_Type data[DSP2_DPC_Enhance_Num];
} DSP2_DPC_ENHANCE_GROUP_TYPE;

/**
 *  @brief Defect correction threadhold group
 */
typedef struct
{
    int data[DSP2_DPC_th_Num];
} DSP2_DPC_THRESHOLD_GROUP_TYPE;

/*
    Lens Shading Coef
    Acoef range: -4194304-4194303
    Bcoef range: -4096-4095
    Ccoef range: 0-255
    Dcoef range: -4194304-4194303
    Ecoef range: -4096-4095
    Gcoef range: -4194304-4194303
*/

/**
 *  @brief BNR threshold type
 */
typedef struct
{
    uint16_t th_base_r;  /*!< r/w, shadow, 10'b, range: 0 ~ (2 ^ TH_BW - 1) */
    uint16_t th_base_g;  /*!< r/w, shadow, 10'b, range: 0 ~ (2 ^ TH_BW - 1) */
    uint16_t th_base_b;  /*!< r/w, shadow, 10'b, range: 0 ~ (2 ^ TH_BW - 1) */
    uint16_t th_slope_r; /*!< r/w, shadow, 8'b, = TH_SLOPE_PRECISION, range: 0 ~ (2 ^ TH_SLOPE_PRECISION - 1) */
    uint16_t th_slope_g; /*!< r/w, shadow, 8'b, = TH_SLOPE_PRECISION, range: 0 ~ (2 ^ TH_SLOPE_PRECISION - 1) */
    uint16_t th_slope_b; /*!< r/w, shadow, 8'b, = TH_SLOPE_PRECISION, range: 0 ~ (2 ^ TH_SLOPE_PRECISION - 1) */
    uint16_t slope_gain; /*!< r/w, shadow, 6'b, = 2 + SLOPE_GAIN_PRECISION, 2.4 fixed-point, range: 0 ~ (2 ^ 6 - 1) */
} DSP2_BNR_THRESHOLD_TYPE;

/**
 *  @brief BNR fallback type
 */
typedef struct
{
    uint16_t fb_lpf_weight; /*!< r/w, shadow, 5'b, = 1 + LPF_WEIGHT_PRECISION, range: 0 ~ (2 ^ LPF_WEIGHT_PRECISION) */
    uint16_t fb_level;      /*!< r/w, shadow, 3'b, = FB_LEVEL_BW, range: 0 ~ (2 ^ FB_LEVEL_BW - 1) */
} DSP2_BNR_FALLBACK_TYPE;

/**
 *  @brief LSC coefficient type
 */
typedef struct
{
    int coef[LSC_COEF_NUM];
} DSP2_LSC_COEF_TYPE;

/**
 *  @brief LSC coefficient group
 */
typedef struct blDSP2_LSC_COEF_S {
    DSP2_LSC_COEF_TYPE lsc_coef_r;
    DSP2_LSC_COEF_TYPE lsc_coef_g;
    DSP2_LSC_COEF_TYPE lsc_coef_b;
} DSP2_LSC_COEF_S;

/**
 *  @brief LSC max
 */
typedef struct blDSP2_LSC_MAX_S {
    int max_r;
    int max_g;
    int max_b;
} DSP2_LSC_MAX_S;

/**
 *  @brief TG configuration
 */
typedef struct
{
    DSP2_SYNC_MODE_TYPE sync_mode_value;
    uint32_t DSP2_clk;
    uint32_t pix_clk;
    uint16_t fps;
    uint16_t total_width;
    uint16_t total_height;
    uint16_t active_width;
    uint16_t active_height;
    uint16_t out_width;
    uint16_t out_height;
} DSP2_TG_Cfg_Type;

/**
 *  @brief AE status configuration
 */
typedef struct _dsp2_ae_stats_conf {
    uint16_t roi_start_x;
    uint16_t roi_start_y;
    uint16_t roi_width;
    uint16_t roi_height;
    uint16_t img_width;
    uint16_t img_height;
    uint8_t grid_width;
    uint8_t grid_height;
    uint8_t grid_num_x;
    uint8_t grid_num_y;
} dsp2_ae_stats_conf_t;

/**
 *  @brief AE sum
 */
typedef struct _dsp2_ae_sum {
    uint32_t r_sum          : 8;
    uint32_t g_sum          : 8;
    uint32_t b_sum          : 8;
    uint32_t reserved_24_31 : 8;
    uint32_t y_sum          : 8;
    uint32_t reserved_8_31  : 24;
} dsp2_ae_sum_t;

/**
 *  @brief AWB status configuration
 */
typedef struct _dsp2_awb_stats_conf {
    uint16_t roi_start_x;
    uint16_t roi_start_y;
    uint16_t roi_width;
    uint16_t roi_height;
    uint16_t img_width;
    uint16_t img_height;
    uint8_t grid_width;
    uint8_t grid_height;
    uint8_t grid_num_x;
    uint8_t grid_num_y;
    uint16_t r_max_thr;
    uint16_t r_min_thr;
    uint16_t g_max_thr;
    uint16_t g_min_thr;
    uint16_t b_max_thr;
    uint16_t b_min_thr;
} dsp2_awb_stats_conf_t;

/**
 *  @brief AWB2 status configuration
 */
typedef struct _dsp2_awb2_stats_conf {
    uint16_t stat_x_min;                  /*!< r/w, shadow, 11'b, range: 0 ~ (width - 1) */
    uint16_t stat_x_max;                  /*!< r/w, shadow, 11'b, range: 0 ~ (width - 1) */
    uint16_t stat_y_min;                  /*!< r/w, shadow, 11'b, range: 0 ~ (height - 1) */
    uint16_t stat_y_max;                  /*!< r/w, shadow, 11'b, range: 0 ~ (height - 1) */
    uint32_t stat_pixel_num;              /*!< r/w, shadow, 21'b, = (stat_x_max - stat_x_min + 1) * (stat_y_max - stat_y_min + 1) */
    uint16_t stat_r_gain;                 /*!< r/w, shadow, 16'b, = 4 + GAIN_PRECISION, 4.12 fixed-point, range: 0 ~ (2 ^ 16 - 1) */
    uint16_t stat_g_gain;                 /*!< r/w, shadow, 16'b, = 4 + GAIN_PRECISION, 4.12 fixed-point, range: 0 ~ (2 ^ 16 - 1) */
    uint16_t stat_b_gain;                 /*!< r/w, shadow, 16'b, = 4 + GAIN_PRECISION, 4.12 fixed-point, range: 0 ~ (2 ^ 16 - 1) */
    uint16_t stat_u_gain;                 /*!< r/w, shadow, 10'b, = 2 + C_GAIN_PRECISION, 2.8 fixed-point, range: 0 ~ (2 ^ 10 - 1) */
    uint16_t stat_v_gain;                 /*!< r/w, shadow, 10'b, = 2 + C_GAIN_PRECISION, 2.8 fixed-point, range: 0 ~ (2 ^ 10 - 1) */
    uint16_t reserved0;                   /*!< reserved */
    uint8_t y_th[DSP2_AWB2_STA_Y_NUM];     /*!< r/w, shadow, 8'b, = STAT_PIXEL_BW, range: 0 ~ (2 ^ 8 - 1) */
    uint8_t y_weight[DSP2_AWB2_STA_Y_NUM]; /*!< r/w, shadow, 8'b, = STAT_PIXEL_BW, range: 0 ~ (2 ^ 8 - 1) */
    uint16_t reserved1;                   /*!< reserved */
    int16_t y_slope[DSP2_AWB2_STA_Y_NUM];  /*!< r/w, shadow, 9'b, = 7 + SLOPE_PRECISION, signed 2's complement, range: -256 ~ +255 */
    uint16_t reserved2;                   /*!< reserved */
    int8_t u[DSP2_AWB2_STA_C_NUM];         /*!< r/w, shadow, 8'b, = STAT_PIXEL_BW, signed 2's complement, range: -128 ~ +127 */
    int8_t v[DSP2_AWB2_STA_C_NUM];         /*!< r/w, shadow, 8'b, = STAT_PIXEL_BW, signed 2's complement, range: -128 ~ +127 */
    uint8_t c_th[DSP2_AWB2_STA_C_NUM];     /*!< r/w, shadow, 6'b, = STAT_PIXEL_BW - 2, range: 0 ~ (2 ^ 6 - 1) */
    uint8_t c_slope[DSP2_AWB2_STA_C_NUM];  /*!< r/w, shadow, 8'b, = 6 + SLOPE_PRECISION, range: 0 ~ (2 ^ 8 - 1) */
} dsp2_awb2_stats_conf_t;

/**
 *  @brief AWB2 sum
 */
typedef struct _dsp2_awb2_sum {
    uint32_t r_avg;       /*!< r, ping-pong, 12'b, = PIXEL_BW */
    uint32_t g_avg;       /*!< r, ping-pong, 12'b, = PIXEL_BW */
    uint32_t b_avg;       /*!< r, ping-pong, 12'b, = PIXEL_BW */
    uint64_t white_r_sum; /*!< r, ping-pong, 41'b, = max. width * height in bit + WEIGHT_PRECISION + PIXEL_BW */
    uint64_t white_g_sum; /*!< r, ping-pong, 41'b, = max. width * height in bit + WEIGHT_PRECISION + PIXEL_BW */
    uint64_t white_b_sum; /*!< r, ping-pong, 41'b, = max. width * height in bit + WEIGHT_PRECISION + PIXEL_BW */
    uint32_t white_ratio; /*!< r, ping-pong, 15'b, = 1 + RATIO_PRECISION, 1.14 fixed-point */
} dsp2_awb2_sum_t;

/**
 *  @brief AWB sum
 */
typedef struct _dsp2_awb_sum {
    uint32_t r_sum          : 12;
    uint32_t reserved_12_15 : 4;
    uint32_t g_sum          : 12;
    uint32_t reserved_28_31 : 4;
    uint32_t b_sum          : 12;
    uint32_t reserved_12_31 : 20;
} dsp2_awb_sum_t;

/**
 *  @brief EE threshold type
 */
typedef struct
{
    uint8_t dirShpnessThresh;
    uint8_t noDirShpnessThresh;
    uint8_t flatThresh;
    uint16_t textureThresh;
    uint16_t edgeThresh;
} DSP2_EE_Thresh_Type;

/**
 *  @brief EE str type
 */
typedef struct
{
    uint8_t posEdgeOvrshtStr;
    uint8_t negEdgeOvrshtStr;
    uint8_t posEdgeStr;
    uint8_t negEdgeStr;
    uint8_t nrStr;
} DSP2_EE_Str_Type;

/**
 *  @brief EE luma weight type
 */
typedef struct
{
    uint16_t lumaWgtTbl[DSP2_EE_LUMA_WEIGHT_NUM];
} DSP2_EE_Luma_Weight_Type;

/**
 *  @brief Chroma suppress type
 */
typedef struct
{
    uint16_t gain;
    uint8_t weight;
    uint8_t gain_thresh;
} DSP2_Chroma_Suppress_Type;

/**
 *  @brief RGB gain type
 */
typedef struct
{
    uint16_t r_gain;
    uint16_t g_gain;
    uint16_t b_gain;
} DSP2_RGB_Gain_Type;

/**
 *  @brief RB gain type
 */
typedef struct
{
    uint16_t r_gain;
    uint16_t b_gain;
} DSP2_RB_Gain_Type;

/*@} end of group DSP2_Public_Types */

/** @defgroup  DSP2_Public_Constants
 *  @{
 */

/** @defgroup  DSP2_SYNC_MODE_TYPE
 *  @{
 */
#define IS_DSP2_SYNC_MODE_TYPE(type) (((type) == DSP2_SYNC_MODE_INPUT) ||        \
                                     ((type) == DSP2_SYNC_MODE_OUTPUT) ||       \
                                     ((type) == DSP2_SYNC_MODE_OUTPUT_INPUT) || \
                                     ((type) == DSP2_SYNC_MODE_INPUT_VBLANK_NO_TOGGLE))

/** @defgroup  DSP2_CCM_COEF_TYPE_E
 *  @{
 */
#define IS_DSP2_CCM_COEF_TYPE_E(type) (((type) == DSP2_CCM_11) || \
                                      ((type) == DSP2_CCM_12) || \
                                      ((type) == DSP2_CCM_13) || \
                                      ((type) == DSP2_CCM_21) || \
                                      ((type) == DSP2_CCM_22) || \
                                      ((type) == DSP2_CCM_23) || \
                                      ((type) == DSP2_CCM_31) || \
                                      ((type) == DSP2_CCM_32) || \
                                      ((type) == DSP2_CCM_33))

/** @defgroup  DSP2_YUV_CONV_TYPE
 *  @{
 */
#define IS_DSP2_YUV_CONV_TYPE(type) (((type) == DSP2_YUV_CONV_FULL_SCALE) || \
                                    ((type) == DSP2_YUV_CONV_BT601))

/** @defgroup  DSP2_DPC_ENHANCE_TYPE
 *  @{
 */
#define IS_DSP2_DPC_ENHANCE_TYPE(type) (((type) == DSP2_DPC_Enhance1) || \
                                       ((type) == DSP2_DPC_Enhance2) || \
                                       ((type) == DSP2_DPC_Enhance3) || \
                                       ((type) == DSP2_DPC_Enhance_Num))

/** @defgroup  DSP2_DPC_THRESHOLD_TYPE
 *  @{
 */
#define IS_DSP2_DPC_THRESHOLD_TYPE(type) (((type) == DSP2_DPC_th1) || \
                                         ((type) == DSP2_DPC_th2) || \
                                         ((type) == DSP2_DPC_th3) || \
                                         ((type) == DSP2_DPC_th4) || \
                                         ((type) == DSP2_DPC_th5) || \
                                         ((type) == DSP2_DPC_th_Num))

/** @defgroup  AE_GRID_DATA_TYPE_E
 *  @{
 */
#define IS_AE_GRID_DATA_TYPE_E(type) (((type) == AE_GRID_DATA_RGB) || \
                                      ((type) == AE_GRID_DATA_Y))

/** @defgroup  AWB_GRID_DATA_TYPE_E
 *  @{
 */
#define IS_AWB_GRID_DATA_TYPE_E(type) (((type) == AWB_GRID_DATA_RG) || \
                                       ((type) == AWB_GRID_DATA_B))

/*@} end of group DSP2_Public_Constants */

/** @defgroup  DSP2_Public_Macros
 *  @{
 */
#define CHECK_PARAM_RANGE(value, min, max) \
    CHECK_PARAM((value) >= min && (value) <= max)
#define CHECK_PARAM_MAX(value, max) \
    CHECK_PARAM((value) <= max)
#define CHECK_PARAM_MIN(value, min) \
    CHECK_PARAM((value) >= min)

/*@} end of group DSP2_Public_Macros */

/** @defgroup  DSP2_Public_Functions
 *  @{
 */
void DSP2_Init(void);

void DSP2_Set_TG_Cfg(const DSP2_TG_Cfg_Type *cfg);
void DSP2_Set_Bayer_Pattern(const BAYER_PATTERN_E *pattern);

void DSP2_Set_AE_State(BL_Fun_Type state);
void DSP2_Set_AE_Stats_Conf(const dsp2_ae_stats_conf_t *ae_stats_conf);
void DSP2_Get_AE_Stats_Conf(dsp2_ae_stats_conf_t *ae_stats_conf);
void DSP2_Get_AE_Sum(int grid_idx, AE_GRID_DATA_TYPE_E data_type, uint32_t *data);
int DSP2_Get_AE_Stats(int grid_num, uint32_t *data);

void DSP2_Set_AWB_State(BL_Fun_Type state);
int DSP2_Get_AWB_Stats(int grid_num, uint32_t *data);
void DSP2_Set_AWB_Stats_Conf(const dsp2_awb_stats_conf_t *awb_stats_conf);
void DSP2_Get_AWB_Stats_Conf(dsp2_awb_stats_conf_t *awb_stats_conf);
void DSP2_Get_AWB_Sum(int grid_idx, RGB_SUM_S *rgb_sum);
void DSP2_Get_AWB_ValidGridNum(int *valid_grid_num);

void DSP2_Set_AWB_Gain(const DSP2_RGB_Gain_Type *rgb_gain);
void DSP2_Get_AWB_Gain(DSP2_RGB_Gain_Type *rgb_gain);
void DSP2_Set_RB_Gain(const DSP2_RB_Gain_Type *rb_gain);

void DSP2_Set_AWB2_State(BL_Fun_Type state);
void DSP2_Set_AWB2_Stats_Conf(const dsp2_awb2_stats_conf_t *awb_stats_conf);
int DSP2_Get_AWB2_Sum(dsp2_awb2_sum_t *sum);
void DSP2_Set_AWB2_Gain_State(BL_Fun_Type state);
void DSP2_Set_AWB2_Gain(const DSP2_RGB_Gain_Type *gain);
void DSP2_Get_AWB2_Gain(DSP2_RGB_Gain_Type *rgb_gain);

int DSP2_Get_Output_Window(BL_Img_Size_T *out_win);

/* Set R/G/B BLC, value range : 0-1023 */
int DSP2_Set_BLC(const DSP2_CLAMP_S *clamp);
int DSP2_Get_BLC(DSP2_CLAMP_S *clamp);

void DSP2_Set_DPC_State(BL_Fun_Type state);
void DSP2_Enable_DPC(void);
void DSP2_Disable_DPC(void);
int DSP2_Set_Defect_Correction_Enhance_Group(const DSP2_DPC_ENHANCE_GROUP_TYPE *value);
int DSP2_Get_Defect_Correction_Enhance_Group(DSP2_DPC_ENHANCE_GROUP_TYPE *value);
int DSP2_Set_Defect_Correction_Threshold_Group(const DSP2_DPC_THRESHOLD_GROUP_TYPE *value);
int DSP2_Get_Defect_Correction_Threshold_Group(DSP2_DPC_THRESHOLD_GROUP_TYPE *value);

void DSP2_Set_BNR_State(BL_Fun_Type state);
void DSP2_Get_BNR_State(BL_Fun_Type *state);
void DSP2_Set_BNR_Weight(int value);
void DSP2_Get_BNR_Weight(int *value);
void DSP2_Set_BNR_LPF_Weight(int value);
void DSP2_Get_BNR_LPF_Weight(int *value);
void DSP2_Set_BNR_Threshold(const DSP2_BNR_THRESHOLD_TYPE *value);
void DSP2_Get_BNR_Threshold(DSP2_BNR_THRESHOLD_TYPE *value);
void DSP2_Set_BNR_Fallback(const DSP2_BNR_FALLBACK_TYPE *value);
void DSP2_Get_BNR_Fallback(DSP2_BNR_FALLBACK_TYPE *value);

void DSP2_Set_Brightness(int value);
void DSP2_Get_Brightness(int *value);

void DSP2_Set_LSC_State(BL_Fun_Type state);
void DSP2_Enable_LSC(void);
void DSP2_Disable_LSC(void);
void DSP2_Get_LSC_State(BL_Fun_Type *state);

/* Set Lens Shading Correction offset */
int DSP2_Set_LSC_Offset(int xoffset, int yoffset);

/* Set/Get Lens Shading Correction setting, value range: please see DSP2_LSC_COEF_S */
int DSP2_Set_LSC_Coeff(const DSP2_LSC_COEF_S *lsc);
int DSP2_Get_LSC_Coeff(DSP2_LSC_COEF_S *lsc);

/* Set/Get Lens Shading Correction R,G,B MAX, value range: 0-255 (refs to demo app) */
int DSP2_Set_LSC_Max(const DSP2_LSC_MAX_S *lsc_max);
int DSP2_Get_LSC_Max(DSP2_LSC_MAX_S *lsc_max);

void DSP2_Set_Digital_Gain(uint16_t dgain);

void DSP2_Set_CCM_State(BL_Fun_Type state);
void DSP2_Get_CCM_State(BL_Fun_Type *state);

/* Set/Get Color Correction Matrix Coefficient Value, value range: 0-4095, 512 normalize to 1 */
void DSP2_Set_CCM_Coef(const DSP2_CCM_COEF_S *ccm);
void DSP2_Get_CCM_Coef(DSP2_CCM_COEF_S *ccm);

void DSP2_Set_Gamma_State(BL_Fun_Type state);
void DSP2_Get_Gamma_State(BL_Fun_Type *state);

/* Set/Get Gamma, value range: 0-4095 */
void DSP2_Set_Gamma_Coef(const DSP2_Gamma_Curve_Type *gamma_curve);
void DSP2_Get_Gamma_Coef(DSP2_Gamma_Curve_Type *gamma_curve);

void DSP2_Init_Color_Enhancement();

/* Set/Get YUV Conversion mode, if you want to change the yuv range, please set yuv adjust */
void DSP2_Set_YUV_Conv_Mode(DSP2_YUV_CONV_TYPE type);
void DSP2_Get_YUV_Conv_Mode(DSP2_YUV_CONV_TYPE *type);

/* Set/Get Brightness, value range: TODO -128-127 */
void DSP2_Set_Brightness(int value);
void DSP2_Get_Brightness(int *value);

/* Set/Get Contrast, value range: TODO 0-255 */
void DSP2_Set_Contrast(int value);
void DSP2_Get_Contrast(int *value);

/* Set/Get Saturation, value range: TODO 0-255 */
void DSP2_Set_Saturation(const DSP2_SATURATION_S *saturation);
void DSP2_Get_Saturation(DSP2_SATURATION_S *saturation);

/* Set/Get Noise Level, value range: 0-63 */
void DSP2_Set_Noise_Level(int value);
void DSP2_Get_Noise_Level(int *value);

/* Set/Get 2D Noise Reduction, value range: 0-31 */
void DSP2_Set_2D_NR(int value);
void DSP2_Get_2D_NR(int *value);

/* Set/Get 3D Noise Reduction, value range: 0-31 */
void DSP2_Set_3D_NR(int value);
void DSP2_Get_3D_NR(int *value);

void DSP2_Set_EE_State(BL_Fun_Type state);
void DSP2_Enable_EE(void);
void DSP2_Disable_EE(void);
void DSP2_EnableEEOverShoot(void);
void DSP2_DisableEEOverShoot(void);
void DSP2_Set_EE_Thresh(const DSP2_EE_Thresh_Type *threshCfg);
void DSP2_Get_EE_Thresh(DSP2_EE_Thresh_Type *threshCfg);
void DSP2_Set_EE_Strength(const DSP2_EE_Str_Type *strCfg);
void DSP2_Get_EE_Strength(DSP2_EE_Str_Type *strCfg);
void DSP2_Set_EE_LumaWeight(const DSP2_EE_Luma_Weight_Type *lumaWgtCfg);
void DSP2_Get_EE_LumaWeight(DSP2_EE_Luma_Weight_Type *lumaWgtCfg);

void DSP2_Set_ChromaSuppress_State(BL_Fun_Type state);
void DSP2_Enable_ChromaSuppress(void);
void DSP2_Disable_ChromaSuppress(void);

void DSP2_Set_ChromaSuppress(const DSP2_Chroma_Suppress_Type *chromaSupprCfg);
void DSP2_Get_ChromaSuppress(DSP2_Chroma_Suppress_Type *chromaSupprCfg);

/*@} end of group DSP2_Public_Functions */

/*@} end of group DSP2 */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_DSP2_H__ */
