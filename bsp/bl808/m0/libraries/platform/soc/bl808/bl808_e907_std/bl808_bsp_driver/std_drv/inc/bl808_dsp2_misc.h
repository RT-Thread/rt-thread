/**
  ******************************************************************************
  * @file    bl808_dsp2_misc.h
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
#ifndef __BL808_DSP2_MISC_H__
#define __BL808_DSP2_MISC_H__

#include "dsp2_misc_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DSP2_MISC
 *  @{
 */

/** @defgroup  DSP2_MISC_Public_Types
 *  @{
 */

/**
 *  @brief DVP 2X input data order type definition
 */
typedef enum {
    DSP2_MISC_2X_DATA_BYTE_LOWER,  /*!< The first data is lower-byte */
    DSP2_MISC_2X_DATA_BYTE_HIGHER, /*!< The first data is higher-byte */
}DSP2_MISC_2X_Data_Order_Type;

/**
 *  @brief Input V/H sync active level type definition
 */
typedef enum {
    DSP2_MISC_ACTIVE_HIGH, /*!< Input is active-high */
    DSP2_MISC_ACTIVE_LOW,  /*!< Input is active-low */
}DSP2_MISC_Active_Level_Type;

/**
 *  @brief DVP TSRC data source type definition
 */
typedef enum {
    DSP2_MISC_TSRC_SOURCE_DVP, /*!< DVP TSRC data source is DVP */
    DSP2_MISC_TSRC_SOURCE_CSI, /*!< DVP TSRC data source is MIPI CSI */
}DSP2_MISC_TSRC_Source_Type;

/**
 *  @brief CAM id type definition
 */
typedef enum {
    DSP2_MISC_CAM_0_ID,   /*!< CAM 0 port define */
    DSP2_MISC_CAM_1_ID,   /*!< CAM 1 port define */
    DSP2_MISC_CAM_2_ID,   /*!< CAM 2 port define */
    DSP2_MISC_CAM_3_ID,   /*!< CAM 3 port define */
    DSP2_MISC_CAM_4_ID,   /*!< CAM 4 port define */
    DSP2_MISC_CAM_5_ID,   /*!< CAM 5 port define */
    DSP2_MISC_CAM_6_ID,   /*!< CAM 6 port define */
    DSP2_MISC_CAM_7_ID,   /*!< CAM 7 port define */
    DSP2_MISC_CAM_ID_MAX, /*!< CAM max ID define */
} DSP2_MISC_CAM_ID_Type;

/**
 *  @brief Crop id type definition
 */
typedef enum {
    DSP2_MISC_CROP_0_ID,   /*!< Crop 0 port define */
    DSP2_MISC_CROP_1_ID,   /*!< Crop 1 port define */
    DSP2_MISC_CROP_2_ID,   /*!< Crop 2 port define */
    DSP2_MISC_CROP_3_ID,   /*!< Crop 3 port define */
    DSP2_MISC_CROP_ID_MAX, /*!< Crop max ID define */
} DSP2_MISC_Crop_ID_Type;

/**
 *  @brief Scaler id type definition
 */
typedef enum {
    DSP2_MISC_SCALER_0_ID,   /*!< Scaler 0 port define */
    DSP2_MISC_SCALER_1_ID,   /*!< Scaler 1 port define */
    DSP2_MISC_SCALER_2_ID,   /*!< Scaler 2 port define */
    DSP2_MISC_SCALER_3_ID,   /*!< Scaler 3 port define */
    DSP2_MISC_SCALER_ID_MAX, /*!< Scaler max ID define */
} DSP2_MISC_Scaler_ID_Type;

/**
 *  @brief OSD id type definition
 */
typedef enum {
    DSP2_MISC_OSD_0_ID,   /*!< OSD 0 port define */
    DSP2_MISC_OSD_1_ID,   /*!< OSD 1 port define */
    DSP2_MISC_OSD_2_ID,   /*!< OSD 2 port define */
    DSP2_MISC_OSD_3_ID,   /*!< OSD 3 port define */
    DSP2_MISC_OSD_ID_MAX, /*!< OSD max ID define */
} DSP2_MISC_OSD_ID_Type;

/**
 *  @brief Adjust id type definition
 */
typedef enum {
    DSP2_MISC_ADJUST_0_ID,   /*!< Adjust 0 port define */
    DSP2_MISC_ADJUST_1_ID,   /*!< Adjust 1 port define */
    DSP2_MISC_ADJUST_2_ID,   /*!< Adjust 2 port define */
    DSP2_MISC_ADJUST_3_ID,   /*!< Adjust 3 port define */
    DSP2_MISC_ADJUST_ID_MAX, /*!< Adjust max ID define */
} DSP2_MISC_Adjust_ID_Type;

/**
 *  @brief YUV2RGB id type definition
 */
typedef enum {
    DSP2_MISC_YUV2RGB_DISPLAY_ID, /*!< Display YUV2RGB port define */
    DSP2_MISC_YUV2RGB_NORMAL_ID,  /*!< Normal YUV2RGB port define */
    DSP2_MISC_YUV2RGB_ID_MAX,     /*!< YUV2RGB max ID define */
} DSP2_MISC_YUV2RGB_ID_Type;

/**
 *  @brief Frame id type definition
 */
typedef enum {
    DSP2_MISC_FRAME_BAYER_ID, /*!< Bayer ID */
    DSP2_MISC_FRAME_YUV_ID,   /*!< YUV ID */
} DSP2_MISC_Frame_ID_Type;

/**
 *  @brief Frame id vsync edge type definition
 */
typedef enum {
    DSP2_MISC_FRAME_ID_VSYNC_NEGEDGE, /*!< Frame ID base on vsync negedge */
    DSP2_MISC_FRAME_ID_VSYNC_POSEDGE, /*!< Frame ID base on vsync posedge */
} DSP2_MISC_Frame_ID_Edge_Type;

/**
 *  @brief CAM input type definition
 */
typedef enum {
    DSP2_MISC_CAM_DSP2_INPUT,             /*!< Use DSP2 input as CAM input */
    DSP2_MISC_CAM_ACTIVE_DVP_OUTPUT,     /*!< Use active DVP(TG) as CAM input */
    DSP2_MISC_CAM_DEFECT_CORRECT_OUTPUT, /*!< Use defect correct as CAM input */
    DSP2_MISC_CAM_CCM_R_OUTPUT,          /*!< Use CCM R as CAM input */
    DSP2_MISC_CAM_CCM_G_OUTPUT,          /*!< Use CCM G as CAM input */
    DSP2_MISC_CAM_CCM_B_OUTPUT,          /*!< Use CCM B as CAM input */
    DSP2_MISC_CAM_GAMMA_R_OUTPUT,        /*!< Use gamma R as CAM input */
    DSP2_MISC_CAM_GAMMA_G_OUTPUT,        /*!< Use gamma G as CAM input */
    DSP2_MISC_CAM_NONE_OUTPUT,           /*!< Don't use */
    DSP2_MISC_CAM_BNR_OUTPUT,            /*!< Use BNR as CAM input */
    DSP2_MISC_CAM_NR_OUTPUT,             /*!< Use NR as CAM input */
    DSP2_MISC_CAM_EE_OUTPUT,             /*!< Use EE as CAM input */
    DSP2_MISC_CAM_DSP2_OUTPUT,            /*!< Use DSP2 output as CAM input */
    DSP2_MISC_CAM_OSD_0_OUTPUT,          /*!< Use OSD 0 as CAM input */
    DSP2_MISC_CAM_OSD_1_OUTPUT,          /*!< Use OSD 1 as CAM input */
    DSP2_MISC_CAM_OSD_2_OUTPUT,          /*!< Use OSD 2 as CAM input */
    DSP2_MISC_CAM_OSD_3_OUTPUT,          /*!< Use OSD 3 as CAM input */
    DSP2_MISC_CAM_SCALER_0_OUTPUT,       /*!< Use scaler 0 as CAM input */
    DSP2_MISC_CAM_SCALER_1_OUTPUT,       /*!< Use scaler 1 as CAM input */
    DSP2_MISC_CAM_SCALER_2_OUTPUT,       /*!< Use scaler 2 as CAM input */
    DSP2_MISC_CAM_SCALER_3_OUTPUT,       /*!< Use scaler 3 as CAM input */
    DSP2_MISC_CAM_ADJUST_0_OUTPUT,       /*!< Use adjust 0 as CAM input */
    DSP2_MISC_CAM_ADJUST_1_OUTPUT,       /*!< Use adjust 1 as CAM input */
    DSP2_MISC_CAM_ADJUST_2_OUTPUT,       /*!< Use adjust 2 as CAM input */
    DSP2_MISC_CAM_ADJUST_3_OUTPUT,       /*!< Use adjust 3 as CAM input */
    DSP2_MISC_CAM_YUV420_0_OUTPUT,       /*!< Use YUV420 0 as CAM input */
    DSP2_MISC_CAM_YUV420_1_OUTPUT,       /*!< Use YUV420 1 as CAM input */
    DSP2_MISC_CAM_YUV420_2_OUTPUT,       /*!< Use YUV420 2 as CAM input */
    DSP2_MISC_CAM_YUV420_3_OUTPUT,       /*!< Use YUV420 3 as CAM input */
    DSP2_MISC_CAM_GAMMA_B_OUTPUT,        /*!< Use gamma B as CAM input */
    DSP2_MISC_CAM_WDR_Y_OUTPUT,          /*!< Use WDR Y as CAM input */
    DSP2_MISC_CAM_WDR_U_OUTPUT,          /*!< Use WDR U as CAM input */
    DSP2_MISC_CAM_WDR_V_OUTPUT,          /*!< Use WDR V as CAM input */
    DSP2_MISC_CAM_LSC_OUTPUT,            /*!< Use LSC as CAM input */
    DSP2_MISC_CAM_AWB2_OUTPUT,           /*!< Use AWB2 as CAM input */
    DSP2_MISC_CAM_YUV2RGB_OUTPUT,        /*!< Use YUV2RGB as CAM input */
    DSP2_MISC_CAM_DVP_AS_2X_OUTPUT,      /*!< Use DVP AS 2X as CAM input */
} DSP2_MISC_CAM_Input_Type;

/**
 *  @brief Scaler input type definition
 */
typedef enum {
    DSP2_MISC_SCALER_DSP2_OUTPUT,   /*!< Use DSP2 output as scaler input */
    DSP2_MISC_SCALER_DSP2_INPUT,    /*!< Use DSP2 input as scaler input */
    DSP2_MISC_SCALER_OSD_0_OUTPUT, /*!< Use OSD 0 as scaler input */
    DSP2_MISC_SCALER_OSD_1_OUTPUT, /*!< Use OSD 1 as scaler input */
    DSP2_MISC_SCALER_OSD_2_OUTPUT, /*!< Use OSD 2 as scaler input */
    DSP2_MISC_SCALER_OSD_3_OUTPUT, /*!< Use OSD 3 as scaler input */
} DSP2_MISC_Scaler_Input_Type;

/**
 *  @brief OSD input type definition
 */
typedef enum {
    DSP2_MISC_OSD_DSP2_OUTPUT,       /*!< Use DSP2 output as OSD input */
    DSP2_MISC_OSD_DSP2_INPUT,        /*!< Use DSP2 input as OSD input */
    DSP2_MISC_OSD_SCALER_0_OUTPUT,  /*!< Use scaler 0 as OSD input */
    DSP2_MISC_OSD_SCALER_1_OUTPUT,  /*!< Use scaler 1 as OSD input */
    DSP2_MISC_OSD_SCALER_2_OUTPUT,  /*!< Use scaler 2 as OSD input */
    DSP2_MISC_OSD_SCALER_3_OUTPUT,  /*!< Use scaler 3 as OSD input */
    DSP2_MISC_OSD_OSD_0_OUTPUT,     /*!< Use osd 0 as OSD input */
    DSP2_MISC_OSD_DVP_AS_2X_OUTPUT, /*!< Use dvp_as_2x as OSD input */
} DSP2_MISC_OSD_Input_Type;

/**
 *  @brief Adjust input type definition
 */
typedef enum {
    DSP2_MISC_ADJUST_DSP2_OUTPUT,      /*!< Use DSP2 output as adjust input */
    DSP2_MISC_ADJUST_DSP2_INPUT,       /*!< Use DSP2 input as adjust input */
    DSP2_MISC_ADJUST_OSD_0_OUTPUT,    /*!< Use OSD 0 as adjust input */
    DSP2_MISC_ADJUST_OSD_1_OUTPUT,    /*!< Use OSD 1 as adjust input */
    DSP2_MISC_ADJUST_OSD_2_OUTPUT,    /*!< Use OSD 2 as adjust input */
    DSP2_MISC_ADJUST_OSD_3_OUTPUT,    /*!< Use OSD 3 as adjust input */
    DSP2_MISC_ADJUST_SCALER_0_OUTPUT, /*!< Use scaler 0 as adjust input */
    DSP2_MISC_ADJUST_SCALER_1_OUTPUT, /*!< Use scaler 1 as adjust input */
    DSP2_MISC_ADJUST_SCALER_2_OUTPUT, /*!< Use scaler 2 as adjust input */
    DSP2_MISC_ADJUST_SCALER_3_OUTPUT, /*!< Use scaler 3 as adjust input */
} DSP2_MISC_Adjust_Input_Type;

/**
 *  @brief YUV2RGB input type definition
 */
typedef enum {
    DSP2_MISC_YUV2RGB_DSP2_OUTPUT,      /*!< Use DSP2 output as yuv2rgb input */
    DSP2_MISC_YUV2RGB_DSP2_INPUT,       /*!< Use DSP2 input as yuv2rgb input */
    DSP2_MISC_YUV2RGB_OSD_0_OUTPUT,    /*!< Use OSD 0 as yuv2rgb input */
    DSP2_MISC_YUV2RGB_OSD_1_OUTPUT,    /*!< Use OSD 1 as yuv2rgb input */
    DSP2_MISC_YUV2RGB_OSD_2_OUTPUT,    /*!< Use OSD 2 as yuv2rgb input */
    DSP2_MISC_YUV2RGB_OSD_3_OUTPUT,    /*!< Use OSD 3 as yuv2rgb input */
    DSP2_MISC_YUV2RGB_SCALER_0_OUTPUT, /*!< Use scaler 0 as yuv2rgb input */
    DSP2_MISC_YUV2RGB_SCALER_1_OUTPUT, /*!< Use scaler 1 as yuv2rgb input */
    DSP2_MISC_YUV2RGB_SCALER_2_OUTPUT, /*!< Use scaler 2 as yuv2rgb input */
    DSP2_MISC_YUV2RGB_SCALER_3_OUTPUT, /*!< Use scaler 3 as yuv2rgb input */
} DSP2_MISC_YUV2RGB_Input_Type;

/**
 *  @brief Bayer data shift direction type definition
 */
typedef enum {
    DSP2_MISC_BAYER_SHIFT_LEFT,  /*!< Bayer data shift left */
    DSP2_MISC_BAYER_SHIFT_RIGHT, /*!< Bayer data shift right */
} DSP2_MISC_Bayer_Shift_Type;

/**
 *  @brief DSP2 MISC interrupt type definition
 */
typedef enum {
    DSP2_MISC_INT_AWB0,    /*!< AWB 0 interrupt */
    DSP2_MISC_INT_AE,      /*!< AE interrupt */
    DSP2_MISC_INT_WDR,     /*!< WDR interrupt */
    DSP2_MISC_INT_AWB1,    /*!< AWB 1 interrupt */
    DSP2_MISC_INT_OSD_PB,  /*!< OSD probe interrupt */
    DSP2_MISC_INT_SEOF0,   /*!< S/E-oF 0 interrupt */
    DSP2_MISC_INT_SEOF1,   /*!< S/E-oF 1 interrupt */
    DSP2_MISC_INT_SEOF2,   /*!< S/E-oF 2 interrupt */
    DSP2_MISC_INT_AE_HIST, /*!< AE hist interrupt */
    DSP2_MISC_INT_AWB2,    /*!< AWB 2 interrupt */
    DSP2_MISC_INT_DISPLAY, /*!< Display S/E-oF 0 interrupt */
    DSP2_MISC_INT_SEOF3,   /*!< S/E-oF 3 interrupt */
    DSP2_MISC_INT_ALL,     /*!< All the interrupt */
} DSP2_MISC_INT_Type;

/**
 *  @brief SEOF interrupt vsync source type definition
 */
typedef enum {
    DSP2_MISC_SEOF_VSYNC_SENSOR = 0,     /*!< Use sensor vsync as SEOF vsync source */
    DSP2_MISC_SEOF_VSYNC_DSP2_ACT = 1,    /*!< Use dsp2 active vsync as SEOF vsync source */
    DSP2_MISC_SEOF_VSYNC_DSP2_OUT = 2,    /*!< Use dsp2 out vsync as SEOF vsync source */
    DSP2_MISC_SEOF_VSYNC_DVP_TSRC = 3,   /*!< Use dvp tsrc vsync as SEOF vsync source */
    DSP2_MISC_SEOF_DISPLAY_TEST_SRC = 0, /*!< Use display test source as display SEOF vsync source */
    DSP2_MISC_SEOF_DISPLAY_OUTPUT = 1,   /*!< Use display output as display SEOF vsync source */
} DSP2_MISC_SEOF_Source_Type;

/**
 *  @brief SEOF interrupt trigger vsync edge type definition
 */
typedef enum {
    DSP2_MISC_SEOF_VSYNC_NEGEDGE, /*!< Vsync negedge will trigger interrupt */
    DSP2_MISC_SEOF_VSYNC_POSEDGE, /*!< Vsync posedge will trigger interrupt */
} DSP2_MISC_SEOF_Edge_Type;

/**
 *  @brief Display input type definition
 */
typedef enum {
    DSP2_MISC_DISPLAY_YUV2RGB_OUTPUT,     /*!< Use yuv2rgb output as display input */
    DSP2_MISC_DISPLAY_OSD_DP_OUTPUT,      /*!< Use OSD_DP output as display input */
    DSP2_MISC_DISPLAY_TSRC_RGB_OUTPUT,    /*!< Use dvp tsrc rgb output as display input */
    DSP2_MISC_DISPLAY_TSRC_YUV422_OUTPUT, /*!< Use dvp tsrc yuv422 output as display input */
} DSP2_MISC_Display_Input_Type;

/**
 *  @brief Display OSD input type definition
 */
typedef enum {
    DSP2_MISC_DISPLAY_OSD_YUV420TO422_OUTPUT, /*!< Use yuv420to422 output as display OSD input */
    DSP2_MISC_DISPLAY_OSD_RGB2YUV422_OUTPUT,  /*!< Use rgb2yuv422 output as display OSD input */
    DSP2_MISC_DISPLAY_OSD_TSRCYUV422_OUTPUT,  /*!< Use dvp tsrc yuv422 output as display OSD input */
} DSP2_MISC_Display_OSD_Input_Type;

/**
 *  @brief DVP AS 2X configuration struct definition
 */
typedef struct {
    DSP2_MISC_Active_Level_Type hSyncLevel; /*!< Input H-Sync active level */
    DSP2_MISC_Active_Level_Type vSyncLevel; /*!< Input V-Sync active level */
    DSP2_MISC_2X_Data_Order_Type dataOrder; /*!< Input data order */
    uint16_t fifoThreshold;                /*!< Fifo threshold for each DVP line to start to 
                                                output,((Width-Fifo_th)*T_in*2)<(Width*T_out)<((Width-Fifo_th)*T_in*2+Blank*T_in) */
}DSP2_MISC_2X_Cfg_Type;

/**
 *  @brief DVP reshape configuration struct definition
 */
typedef struct {
    DSP2_MISC_Active_Level_Type hSyncLevel; /*!< Input H-Sync active level */
    DSP2_MISC_Active_Level_Type vSyncLevel; /*!< Input V-Sync active level */
    BL_Fun_Type enable;                    /*!< Enable or disable sensor vsync toggle remove */
    uint8_t vsyncNumber;                   /*!< Number of sensor vsync toggle before sensor stable */
}DSP2_MISC_Reshape_Cfg_Type;

/**
 *  @brief Display configuration structure type definition
 */
typedef struct
{
    BL_Fun_Type dpiEnable;                   /*!< Enable or disable dpi function, only one of the four functions can be enabled at the same time */
    BL_Fun_Type bt1120Enable;                /*!< Enable or disable BT1120 function, only one of the four functions can be enabled at the same time */
    BL_Fun_Type hdmiEnable;                  /*!< Enable or disable HDMI function, only one of the four functions can be enabled at the same time */
    DSP2_MISC_Display_Input_Type inputType;   /*!< Select display input */
    DSP2_MISC_Display_OSD_Input_Type osdType; /*!< Select display OSD input */
    uint8_t hsyncWidth;                      /*!< Horizontal synchronization width */
    uint8_t hfpWidth;                        /*!< Horizontal front porch width */
    uint8_t vsyncWidth;                      /*!< Vertical synchronization width */
    uint8_t vfpWidth;                        /*!< Vertical front porch width */
} DSP2_MISC_Display_Cfg_Type;

/**
 *  @brief Display gamma configuration structure type definition
 */
typedef struct
{
    BL_Fun_Type ch0Enable; /*!< Enable or disable display gamma channel 0 */
    BL_Fun_Type ch1Enable; /*!< Enable or disable display gamma channel 1 */
    BL_Fun_Type ch2Enable; /*!< Enable or disable display gamma channel 2 */
    uint8_t *gammaCurve;   /*!< Gamma curve */
} DSP2_MISC_Display_Gamma_Cfg_Type;

/**
 *  @brief YUV2RGB configuration struct definition
 */
typedef struct
{
    BL_Fun_Type enable;   /*!< Enable or disable yuv2rgb function */
    uint16_t preOffset0;  /*!< YUV2RGB pre offset 0 */
    uint16_t preOffset1;  /*!< YUV2RGB pre offset 1 */
    uint16_t preOffset2;  /*!< YUV2RGB pre offset 2 */
    uint16_t postOffset0; /*!< YUV2RGB post offset 0 */
    uint16_t postOffset1; /*!< YUV2RGB post offset 1 */
    uint16_t postOffset2; /*!< YUV2RGB post offset 2 */
    uint16_t matrix00;    /*!< YUV2RGB matrix 00 */
    uint16_t matrix01;    /*!< YUV2RGB matrix 01 */
    uint16_t matrix02;    /*!< YUV2RGB matrix 02 */
    uint16_t matrix10;    /*!< YUV2RGB matrix 10 */
    uint16_t matrix11;    /*!< YUV2RGB matrix 11 */
    uint16_t matrix12;    /*!< YUV2RGB matrix 12 */
    uint16_t matrix20;    /*!< YUV2RGB matrix 20 */
    uint16_t matrix21;    /*!< YUV2RGB matrix 21 */
    uint16_t matrix22;    /*!< YUV2RGB matrix 22 */
} DSP2_MISC_YUV2RGB_Cfg_Type;

/**
 *  @brief Crop configuration struct definition
 */
typedef struct
{
    uint16_t hsyncStart; /*!< Hsync valid start */
    uint16_t hsyncEnd;   /*!< Hsync valid end */
    uint16_t vsyncStart; /*!< Vsync valid start */
    uint16_t vsyncEnd;   /*!< Vsync valid end */
} DSP2_MISC_Crop_Cfg_Type;

/**
 *  @brief Scaler configuration struct definition
 */
typedef struct
{
    uint16_t inputWidth;   /*!< Width of input frame */
    uint16_t inputHeight;  /*!< Height of input frame */
    uint16_t outputWidth;  /*!< Width of output frame */
    uint16_t outputHeight; /*!< Height of output frame */
} DSP2_MISC_Scaler_Cfg_Type;

/**
 *  @brief Adjust configuration struct definition
 */
typedef struct
{
    uint16_t yLuma;  /*!< Y luma,higher luma */
    uint16_t yMul0;  /*!< Contrast adjust mul0 */
    uint16_t yMul1;  /*!< Contrast adjust mul1 */
    uint8_t yMin;    /*!< Y min clip value */
    uint8_t yMax;    /*!< Y max clip value */
    uint16_t uvMul0; /*!< Saturation adjust, software can multipiler gain to this value */
    uint16_t uvMul1; /*!< Saturation adjust, software can multipiler gain to this value */
    uint8_t uvMin;   /*!< UV min clip value */
    uint8_t uvMax;   /*!< UV max clip value */
} DSP2_MISC_Adjust_Cfg_Type;

/*@} end of group DSP2_MISC_Public_Types */

/** @defgroup  DSP2_MISC_Public_Constants
 *  @{
 */

/** @defgroup  DSP2_MISC_2X_DATA_ORDER_TYPE
 *  @{
 */
#define IS_DSP2_MISC_2X_DATA_ORDER_TYPE(type) (((type) == DSP2_MISC_2X_DATA_BYTE_LOWER) || \
                                              ((type) == DSP2_MISC_2X_DATA_BYTE_HIGHER))

/** @defgroup  DSP2_MISC_ACTIVE_LEVEL_TYPE
 *  @{
 */
#define IS_DSP2_MISC_ACTIVE_LEVEL_TYPE(type) (((type) == DSP2_MISC_ACTIVE_HIGH) || \
                                             ((type) == DSP2_MISC_ACTIVE_LOW))

/** @defgroup  DSP2_MISC_TSRC_SOURCE_TYPE
 *  @{
 */
#define IS_DSP2_MISC_TSRC_SOURCE_TYPE(type) (((type) == DSP2_MISC_TSRC_SOURCE_DVP) || \
                                            ((type) == DSP2_MISC_TSRC_SOURCE_CSI))

/** @defgroup  DSP2_MISC_CAM_ID_TYPE
 *  @{
 */
#define IS_DSP2_MISC_CAM_ID_TYPE(type) (((type) == DSP2_MISC_CAM_0_ID) || \
                                       ((type) == DSP2_MISC_CAM_1_ID) || \
                                       ((type) == DSP2_MISC_CAM_2_ID) || \
                                       ((type) == DSP2_MISC_CAM_3_ID) || \
                                       ((type) == DSP2_MISC_CAM_4_ID) || \
                                       ((type) == DSP2_MISC_CAM_5_ID) || \
                                       ((type) == DSP2_MISC_CAM_6_ID) || \
                                       ((type) == DSP2_MISC_CAM_7_ID) || \
                                       ((type) == DSP2_MISC_CAM_ID_MAX))

/** @defgroup  DSP2_MISC_CROP_ID_TYPE
 *  @{
 */
#define IS_DSP2_MISC_CROP_ID_TYPE(type) (((type) == DSP2_MISC_CROP_0_ID) || \
                                        ((type) == DSP2_MISC_CROP_1_ID) || \
                                        ((type) == DSP2_MISC_CROP_2_ID) || \
                                        ((type) == DSP2_MISC_CROP_3_ID) || \
                                        ((type) == DSP2_MISC_CROP_ID_MAX))

/** @defgroup  DSP2_MISC_SCALER_ID_TYPE
 *  @{
 */
#define IS_DSP2_MISC_SCALER_ID_TYPE(type) (((type) == DSP2_MISC_SCALER_0_ID) || \
                                          ((type) == DSP2_MISC_SCALER_1_ID) || \
                                          ((type) == DSP2_MISC_SCALER_2_ID) || \
                                          ((type) == DSP2_MISC_SCALER_3_ID) || \
                                          ((type) == DSP2_MISC_SCALER_ID_MAX))

/** @defgroup  DSP2_MISC_OSD_ID_TYPE
 *  @{
 */
#define IS_DSP2_MISC_OSD_ID_TYPE(type) (((type) == DSP2_MISC_OSD_0_ID) || \
                                       ((type) == DSP2_MISC_OSD_1_ID) || \
                                       ((type) == DSP2_MISC_OSD_2_ID) || \
                                       ((type) == DSP2_MISC_OSD_3_ID) || \
                                       ((type) == DSP2_MISC_OSD_ID_MAX))

/** @defgroup  DSP2_MISC_ADJUST_ID_TYPE
 *  @{
 */
#define IS_DSP2_MISC_ADJUST_ID_TYPE(type) (((type) == DSP2_MISC_ADJUST_0_ID) || \
                                          ((type) == DSP2_MISC_ADJUST_1_ID) || \
                                          ((type) == DSP2_MISC_ADJUST_2_ID) || \
                                          ((type) == DSP2_MISC_ADJUST_3_ID) || \
                                          ((type) == DSP2_MISC_ADJUST_ID_MAX))

/** @defgroup  DSP2_MISC_YUV2RGB_ID_TYPE
 *  @{
 */
#define IS_DSP2_MISC_YUV2RGB_ID_TYPE(type) (((type) == DSP2_MISC_YUV2RGB_DISPLAY_ID) || \
                                           ((type) == DSP2_MISC_YUV2RGB_NORMAL_ID) ||  \
                                           ((type) == DSP2_MISC_YUV2RGB_ID_MAX))

/** @defgroup  DSP2_MISC_FRAME_ID_TYPE
 *  @{
 */
#define IS_DSP2_MISC_FRAME_ID_TYPE(type) (((type) == DSP2_MISC_FRAME_BAYER_ID) || \
                                         ((type) == DSP2_MISC_FRAME_YUV_ID))

/** @defgroup  DSP2_MISC_FRAME_ID_EDGE_TYPE
 *  @{
 */
#define IS_DSP2_MISC_FRAME_ID_EDGE_TYPE(type) (((type) == DSP2_MISC_FRAME_ID_VSYNC_NEGEDGE) || \
                                              ((type) == DSP2_MISC_FRAME_ID_VSYNC_POSEDGE))

/** @defgroup  DSP2_MISC_CAM_INPUT_TYPE
 *  @{
 */
#define IS_DSP2_MISC_CAM_INPUT_TYPE(type) (((type) == DSP2_MISC_CAM_DSP2_INPUT) ||             \
                                          ((type) == DSP2_MISC_CAM_ACTIVE_DVP_OUTPUT) ||     \
                                          ((type) == DSP2_MISC_CAM_DEFECT_CORRECT_OUTPUT) || \
                                          ((type) == DSP2_MISC_CAM_CCM_R_OUTPUT) ||          \
                                          ((type) == DSP2_MISC_CAM_CCM_G_OUTPUT) ||          \
                                          ((type) == DSP2_MISC_CAM_CCM_B_OUTPUT) ||          \
                                          ((type) == DSP2_MISC_CAM_GAMMA_R_OUTPUT) ||        \
                                          ((type) == DSP2_MISC_CAM_GAMMA_G_OUTPUT) ||        \
                                          ((type) == DSP2_MISC_CAM_NONE_OUTPUT) ||           \
                                          ((type) == DSP2_MISC_CAM_BNR_OUTPUT) ||            \
                                          ((type) == DSP2_MISC_CAM_NR_OUTPUT) ||             \
                                          ((type) == DSP2_MISC_CAM_EE_OUTPUT) ||             \
                                          ((type) == DSP2_MISC_CAM_DSP2_OUTPUT) ||            \
                                          ((type) == DSP2_MISC_CAM_OSD_0_OUTPUT) ||          \
                                          ((type) == DSP2_MISC_CAM_OSD_1_OUTPUT) ||          \
                                          ((type) == DSP2_MISC_CAM_OSD_2_OUTPUT) ||          \
                                          ((type) == DSP2_MISC_CAM_OSD_3_OUTPUT) ||          \
                                          ((type) == DSP2_MISC_CAM_SCALER_0_OUTPUT) ||       \
                                          ((type) == DSP2_MISC_CAM_SCALER_1_OUTPUT) ||       \
                                          ((type) == DSP2_MISC_CAM_SCALER_2_OUTPUT) ||       \
                                          ((type) == DSP2_MISC_CAM_SCALER_3_OUTPUT) ||       \
                                          ((type) == DSP2_MISC_CAM_ADJUST_0_OUTPUT) ||       \
                                          ((type) == DSP2_MISC_CAM_ADJUST_1_OUTPUT) ||       \
                                          ((type) == DSP2_MISC_CAM_ADJUST_2_OUTPUT) ||       \
                                          ((type) == DSP2_MISC_CAM_ADJUST_3_OUTPUT) ||       \
                                          ((type) == DSP2_MISC_CAM_YUV420_0_OUTPUT) ||       \
                                          ((type) == DSP2_MISC_CAM_YUV420_1_OUTPUT) ||       \
                                          ((type) == DSP2_MISC_CAM_YUV420_2_OUTPUT) ||       \
                                          ((type) == DSP2_MISC_CAM_YUV420_3_OUTPUT) ||       \
                                          ((type) == DSP2_MISC_CAM_GAMMA_B_OUTPUT) ||        \
                                          ((type) == DSP2_MISC_CAM_WDR_Y_OUTPUT) ||          \
                                          ((type) == DSP2_MISC_CAM_WDR_U_OUTPUT) ||          \
                                          ((type) == DSP2_MISC_CAM_WDR_V_OUTPUT) ||          \
                                          ((type) == DSP2_MISC_CAM_LSC_OUTPUT) ||            \
                                          ((type) == DSP2_MISC_CAM_AWB2_OUTPUT) ||           \
                                          ((type) == DSP2_MISC_CAM_YUV2RGB_OUTPUT) ||        \
                                          ((type) == DSP2_MISC_CAM_DVP_AS_2X_OUTPUT))

/** @defgroup  DSP2_MISC_SCALER_INPUT_TYPE
 *  @{
 */
#define IS_DSP2_MISC_SCALER_INPUT_TYPE(type) (((type) == DSP2_MISC_SCALER_DSP2_OUTPUT) ||   \
                                             ((type) == DSP2_MISC_SCALER_DSP2_INPUT) ||    \
                                             ((type) == DSP2_MISC_SCALER_OSD_0_OUTPUT) || \
                                             ((type) == DSP2_MISC_SCALER_OSD_1_OUTPUT) || \
                                             ((type) == DSP2_MISC_SCALER_OSD_2_OUTPUT) || \
                                             ((type) == DSP2_MISC_SCALER_OSD_3_OUTPUT))

/** @defgroup  DSP2_MISC_OSD_INPUT_TYPE
 *  @{
 */
#define IS_DSP2_MISC_OSD_INPUT_TYPE(type) (((type) == DSP2_MISC_OSD_DSP2_OUTPUT) ||      \
                                          ((type) == DSP2_MISC_OSD_DSP2_INPUT) ||       \
                                          ((type) == DSP2_MISC_OSD_SCALER_0_OUTPUT) || \
                                          ((type) == DSP2_MISC_OSD_SCALER_1_OUTPUT) || \
                                          ((type) == DSP2_MISC_OSD_SCALER_2_OUTPUT) || \
                                          ((type) == DSP2_MISC_OSD_SCALER_3_OUTPUT) || \
                                          ((type) == DSP2_MISC_OSD_OSD_0_OUTPUT) ||    \
                                          ((type) == DSP2_MISC_OSD_DVP_AS_2X_OUTPUT))

/** @defgroup  DSP2_MISC_YUV2RGB_INPUT_TYPE
 *  @{
 */
#define IS_DSP2_MISC_YUV2RGB_INPUT_TYPE(type) (((type) == DSP2_MISC_YUV2RGB_DSP2_OUTPUT) ||      \
                                              ((type) == DSP2_MISC_YUV2RGB_DSP2_INPUT) ||       \
                                              ((type) == DSP2_MISC_YUV2RGB_OSD_0_OUTPUT) ||    \
                                              ((type) == DSP2_MISC_YUV2RGB_OSD_1_OUTPUT) ||    \
                                              ((type) == DSP2_MISC_YUV2RGB_OSD_2_OUTPUT) ||    \
                                              ((type) == DSP2_MISC_YUV2RGB_OSD_3_OUTPUT) ||    \
                                              ((type) == DSP2_MISC_YUV2RGB_SCALER_0_OUTPUT) || \
                                              ((type) == DSP2_MISC_YUV2RGB_SCALER_1_OUTPUT) || \
                                              ((type) == DSP2_MISC_YUV2RGB_SCALER_2_OUTPUT) || \
                                              ((type) == DSP2_MISC_YUV2RGB_SCALER_3_OUTPUT))

/** @defgroup  DSP2_MISC_BAYER_SHIFT_TYPE
 *  @{
 */
#define IS_DSP2_MISC_BAYER_SHIFT_TYPE(type) (((type) == DSP2_MISC_BAYER_SHIFT_LEFT) || \
                                            ((type) == DSP2_MISC_BAYER_SHIFT_RIGHT))

/** @defgroup  DSP2_MISC_INT_TYPE
 *  @{
 */
#define IS_DSP2_MISC_INT_TYPE(type) (((type) == DSP2_MISC_INT_AWB0) ||    \
                                    ((type) == DSP2_MISC_INT_AE) ||      \
                                    ((type) == DSP2_MISC_INT_WDR) ||     \
                                    ((type) == DSP2_MISC_INT_AWB1) ||    \
                                    ((type) == DSP2_MISC_INT_OSD_PB) ||  \
                                    ((type) == DSP2_MISC_INT_SEOF0) ||   \
                                    ((type) == DSP2_MISC_INT_SEOF1) ||   \
                                    ((type) == DSP2_MISC_INT_SEOF2) ||   \
                                    ((type) == DSP2_MISC_INT_AE_HIST) || \
                                    ((type) == DSP2_MISC_INT_AWB2) ||    \
                                    ((type) == DSP2_MISC_INT_DISPLAY) || \
                                    ((type) == DSP2_MISC_INT_SEOF3) ||   \
                                    ((type) == DSP2_MISC_INT_ALL))

/** @defgroup  DSP2_MISC_SEOF_SOURCE_TYPE
 *  @{
 */
#define IS_DSP2_MISC_SEOF_SOURCE_TYPE(type) (((type) == DSP2_MISC_SEOF_VSYNC_SENSOR) ||     \
                                            ((type) == DSP2_MISC_SEOF_VSYNC_DSP2_ACT) ||    \
                                            ((type) == DSP2_MISC_SEOF_VSYNC_DSP2_OUT) ||    \
                                            ((type) == DSP2_MISC_SEOF_VSYNC_DVP_TSRC) ||    \
                                            ((type) == DSP2_MISC_SEOF_DISPLAY_TEST_SRC) || \
                                            ((type) == DSP2_MISC_SEOF_DISPLAY_OUTPUT))

/** @defgroup  DSP2_MISC_SEOF_EDGE_TYPE
 *  @{
 */
#define IS_DSP2_MISC_SEOF_EDGE_TYPE(type) (((type) == DSP2_MISC_SEOF_VSYNC_NEGEDGE) || \
                                          ((type) == DSP2_MISC_SEOF_VSYNC_POSEDGE))

/** @defgroup  DSP2_MISC_DISPLAY_INPUT_TYPE
 *  @{
 */
#define IS_DSP2_MISC_DISPLAY_INPUT_TYPE(type) (((type) == DSP2_MISC_DISPLAY_YUV2RGB_OUTPUT) || \
                                              ((type) == DSP2_MISC_DISPLAY_YUV422_OUTPUT))

/*@} end of group DSP2_MISC_Public_Constants */

/** @defgroup  DSP2_MISC_Public_Macros
 *  @{
 */

/*@} end of group DSP2_MISC_Public_Macros */

/** @defgroup  DSP2_MISC_Public_Functions
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
void SEOF0_IRQHandler(void);
void SEOF1_IRQHandler(void);
void SEOF2_IRQHandler(void);
void SEOF3_IRQHandler(void);
void AWB0_IRQHandler(void);
void AWB1_IRQHandler(void);
void AWB2_IRQHandler(void);
void AE_IRQHandler(void);
void AE_HIST_IRQHandler(void);
void WDR_IRQHandler(void);
void OSD_PB_IRQHandler(void);
void Display_IRQHandler(void);
#endif
void DSP2_MISC_2X_Init(DSP2_MISC_2X_Cfg_Type *dvp2xCfg);
void DSP2_MISC_2X_Enable(void);
void DSP2_MISC_2X_Disable(void);
void DSP2_MISC_CAM_Input_Select(DSP2_MISC_CAM_ID_Type camId, DSP2_MISC_CAM_Input_Type inputType);
void DSP2_MISC_CAM_Frame_ID_Select(DSP2_MISC_CAM_ID_Type camId, DSP2_MISC_Frame_ID_Type idType);
void DSP2_MISC_Frame_ID_Init(DSP2_MISC_Frame_ID_Type idType, DSP2_MISC_Frame_ID_Edge_Type edgeType, uint16_t vsyncCnt);
void DSP2_MISC_Frame_ID_Reset(DSP2_MISC_Frame_ID_Type idType);
void DSP2_MISC_OSD_Input_Select(DSP2_MISC_OSD_ID_Type osdId, DSP2_MISC_OSD_Input_Type inputType);
void DSP2_MISC_OSD_Probe_Input_Select(DSP2_MISC_OSD_Input_Type inputType);
void DSP2_MISC_Crop_Init(DSP2_MISC_Crop_ID_Type cropId, DSP2_MISC_Crop_Cfg_Type *cropCfg);
void DSP2_MISC_Crop_Enable(DSP2_MISC_Crop_ID_Type cropId);
void DSP2_MISC_Crop_Disable(DSP2_MISC_Crop_ID_Type cropId);
void DSP2_MISC_Scaler_Input_Select(DSP2_MISC_Scaler_ID_Type scalerId, DSP2_MISC_Scaler_Input_Type inputType);
void DSP2_MISC_Scaler_Init(DSP2_MISC_Scaler_ID_Type scalerId, DSP2_MISC_Scaler_Cfg_Type *scalerCfg);
void DSP2_MISC_Scaler_Enable(DSP2_MISC_Scaler_ID_Type scalerId);
void DSP2_MISC_Scaler_Disable(DSP2_MISC_Scaler_ID_Type scalerId);
void DSP2_MISC_Scaler_Shadow(DSP2_MISC_Scaler_ID_Type scalerId);
void DSP2_MISC_Adjust_Input_Select(DSP2_MISC_Adjust_ID_Type adjustId, DSP2_MISC_Adjust_Input_Type inputType);
void DSP2_MISC_Adjust_Init(DSP2_MISC_Adjust_ID_Type adjustId, DSP2_MISC_Adjust_Cfg_Type *adjustCfg);
void DSP2_MISC_Adjust_Enable(DSP2_MISC_Adjust_ID_Type adjustId);
void DSP2_MISC_Adjust_Disable(DSP2_MISC_Adjust_ID_Type adjustId);
void DSP2_MISC_Display_Init(DSP2_MISC_Display_Cfg_Type *displayCfg);
void DSP2_MISC_Display_Gamma_Init(DSP2_MISC_Display_Gamma_Cfg_Type *gammaCfg);
void DSP2_MISC_YUV2RGB_Input_Select(DSP2_MISC_YUV2RGB_Input_Type inputType);
void DSP2_MISC_YUV2RGB_Init(DSP2_MISC_YUV2RGB_ID_Type yuv2rgbId, DSP2_MISC_YUV2RGB_Cfg_Type *yuv2rgbCfg);
void DSP2_MISC_RGB2YUV_Init(DSP2_MISC_YUV2RGB_Cfg_Type *rgb2yuvCfg);
void DSP2_MISC_Int_Clear(DSP2_MISC_INT_Type intType);
void DSP2_MISC_Int_Mask(DSP2_MISC_INT_Type intType, BL_Mask_Type intMask);
void DSP2_MISC_Int_Callback_Install(DSP2_MISC_INT_Type intType, intCallback_Type *cbFun);
void DSP2_MISC_SEOF_Set_Source(DSP2_MISC_INT_Type intType, DSP2_MISC_SEOF_Source_Type source);
void DSP2_MISC_SEOF_Set_Edge(DSP2_MISC_INT_Type intType, DSP2_MISC_SEOF_Edge_Type edge);
void DSP2_MISC_Reshape_Init(DSP2_MISC_Reshape_Cfg_Type *reshapeCfg);
void DSP2_MISC_Reshape_Counter_Clear(void);
void DSP2_MISC_DE_As_Hsync(BL_Fun_Type enable);
void DSP2_MISC_TSRC_Source_Select(DSP2_MISC_TSRC_Source_Type sourceType);
void DSP2_MISC_Bayer_Shift(uint16_t bitEnable, DSP2_MISC_Bayer_Shift_Type shiftType, uint8_t bitShift);
void DSP2_MISC_M2N_Enable(uint8_t m, uint8_t n, uint8_t step);
void DSP2_MISC_M2N_Disable(void);

/*@} end of group DSP2_MISC_Public_Functions */

/*@} end of group DSP2_MISC */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_DSP2_MISC_H__ */
