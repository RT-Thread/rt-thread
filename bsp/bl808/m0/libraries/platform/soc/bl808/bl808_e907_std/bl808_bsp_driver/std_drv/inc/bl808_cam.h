/**
  ******************************************************************************
  * @file    bl808_cam.h
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
#ifndef __BL808_CAM_H__
#define __BL808_CAM_H__

#include "cam_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  CAM
 *  @{
 */

/** @defgroup  CAM_Public_Types
 *  @{
 */

/**
 *  @brief CAM port type definition
 */
typedef enum {
    CAM0_ID,    /*!< Camera0 port define */
    CAM1_ID,    /*!< Camera1 port define */
    CAM2_ID,    /*!< Camera2 port define */
    CAM3_ID,    /*!< Camera3 port define */
    CAM4_ID,    /*!< Camera4 port define */
    CAM5_ID,    /*!< Camera5 port define */
    CAM6_ID,    /*!< Camera6 port define */
    CAM7_ID,    /*!< Camera7 port define */
    CAM_ID_MAX, /*!< Camera max ID define */
} CAM_ID_Type;

/**
 *  @brief CAM AHB burst type definition
 */
typedef enum {
    CAM_BURST_TYPE_SINGLE,     /*!< Camera AHB burst type:single */
    CAM_BURST_TYPE_INCR4,      /*!< Camera AHB burst type:incrementing 4 */
    CAM_BURST_TYPE_INCR8,      /*!< Camera AHB burst type:incrementing 8 */
    CAM_BURST_TYPE_INCR16,     /*!< Camera AHB burst type:incrementing 16 */
    CAM_BURST_TYPE_INCR32 = 5, /*!< Camera AHB burst type:incrementing 32 */
    CAM_BURST_TYPE_INCR64,     /*!< Camera AHB burst type:incrementing 64 */
} CAM_Burst_Type;

/**
 *  @brief CAM software mode type definition
 */
typedef enum {
    CAM_SW_MODE_AUTO,   /*!< CAM auto mode with mjpeg */
    CAM_SW_MODE_MANUAL, /*!< CAM manual mode(software mode) */
} CAM_SW_Mode_Type;

/**
 *  @brief CAM output drop mode type definition
 */
typedef enum {
    CAM_DROP_NONE,               /*!< Not drop */
    CAM_DROP_ODD_ROW_ODD_PIXEL,  /*!< Dropp odd pix data in odd rows, for example:(raw data:YUYV YUYV..., processed data:YUYV YY...) */
    CAM_DROP_ODD_ROW_EVEN_PIXEL, /*!< Dropp even pix data in odd rows, for example:(raw data:UYVY UYVY..., processed data:UYVY YY...) */
    CAM_DROP_ALL_ODD_PIXEL,      /*!< Dropp odd pix data, for example:(raw data:YUYV YUYV..., processed data:YY YY...) */
    CAM_DROP_ALL_EVEN_PIXEL,     /*!< Dropp even pix data, for example:(raw data:UYVY UYVY..., processed data:YY YY...) */
} CAM_Output_Drop_Mode_Type;

/**
 *  @brief CAM input pix data width type definition
 */
typedef enum {
    CAM_PIX_DATA_BIT_16,     /*!< CAM pix data is 16-bit */
    CAM_PIX_DATA_BIT_24,     /*!< CAM pix data is 24-bit */
    CAM_PIX_DATA_BIT_24TO16, /*!< CAM pix data is 24-comp-16-bit */
    CAM_PIX_DATA_BIT_24TO32, /*!< CAM pix data is 24-exp-32-bit */
    CAM_PIX_DATA_BIT_8,      /*!< CAM pix data is 8-bit */
} CAM_Input_Pix_Width_Type;

/**
 *  @brief CAM 8-bit mode byte select type definition
 */
typedef enum {
    CAM_8_BIT_SELECT_LOWER, /*!< CAM select the lower byte of pix data */
    CAM_8_BIT_SELECT_UPPER, /*!< CAM select the upper byte of pix data */
} CAM_8_Bit_Byte_Type;

/**
 *  @brief CAM pix data 24-comp-16-bit mode RGB order type definition
 */
typedef enum {
    CAM_16_BIT_RGB, /*!< CAM 16-bit pix data is RGB */
    CAM_16_BIT_GRB, /*!< CAM 16-bit pix data is GRB */
    CAM_16_BIT_RBG, /*!< CAM 16-bit pix data is RBG */
    CAM_16_BIT_GBR, /*!< CAM 16-bit pix data is GBR */
    CAM_16_BIT_BRG, /*!< CAM 16-bit pix data is BRG */
    CAM_16_BIT_BGR, /*!< CAM 16-bit pix data is BGR */
} CAM_16_Bit_RGB_Type;

/**
 *  @brief CAM line active polarity type definition
 */
typedef enum {
    CAM_LINE_ACTIVE_POLARITY_LOW,  /*!< CAM line active polarity low */
    CAM_LINE_ACTIVE_POLARITY_HIGH, /*!< CAM line active polarity high */
} CAM_Line_Active_Pol;

/**
 *  @brief CAM frame active polarity type definition
 */
typedef enum {
    CAM_FRAME_ACTIVE_POLARITY_LOW,  /*!< CAM frame active polarity low */
    CAM_FRAME_ACTIVE_POLARITY_HIGH, /*!< CAM frame active polarity high */
} CAM_Frame_Active_Pol;

/**
 *  @brief CAM sensor mode type definition
 */
typedef enum {
    CAM_SENSOR_MODE_V_AND_H, /*!< CAM sensor type v and h */
    CAM_SENSOR_MODE_V_OR_H,  /*!< CAM sensor type v  or h */
    CAM_SENSOR_MODE_V,       /*!< CAM sensor type v */
    CAM_SENSOR_MODE_H,       /*!< CAM sensor type h */
} CAM_Sensor_Mode_Type;

/**
 *  @brief CAM interrupt type definition
 */
typedef enum {
    CAM_INT_NORMAL,           /*!< Normal write interrupt */
    CAM_INT_MEMORY_OVERWRITE, /*!< Memory overwrite interrupt */
    CAM_INT_FRAME_OVERWRITE,  /*!< Frame overwrite interrupt */
    CAM_INT_FIFO_OVERWRITE,   /*!< Fifo overwrite interrupt */
    CAM_INT_VSYNC_CNT_ERROR,  /*!< Vsync valid line count non-match interrupt */
    CAM_INT_HSYNC_CNT_ERROR,  /*!< Hsync valid pixel count non-match interrupt */
    CAM_INT_ALL,              /*!< All of interrupt */
} CAM_INT_Type;

/**
 *  @brief CAM configuration strcut definition
 */
typedef struct
{
    CAM_SW_Mode_Type swMode;            /*!< Software mode */
    uint8_t swIntCnt;                   /*!< Set frame count to issue interrupt at software mode */
    CAM_Input_Pix_Width_Type pixWidth;  /*!< Input pix data width */
    CAM_Output_Drop_Mode_Type dropMode; /*!< Drop mode */
    CAM_Frame_Active_Pol framePol;      /*!< Frame polarity */
    CAM_Line_Active_Pol linePol;        /*!< Line polarity */
    CAM_Burst_Type burstType;           /*!< AHB burst type */
    CAM_Sensor_Mode_Type camSensorMode; /*!< CAM sensor mode */
    uint8_t waitCount;                  /*!< Cycles in FSM wait mode, default value:0x40 */
    uint32_t memStart;                  /*!< Data start address */
    uint32_t memSize;                   /*!< Memory size in burst */
    uint32_t frameSize;                 /*!< Frame byte size */
} CAM_CFG_Type;

/**
 *  @brief CAM frame information strcut definition
 */
typedef struct
{
    uint8_t validFrames;    /*!< Valid frames */
    uint16_t curFrameId;    /*!< Current frame id */
    uint32_t curFrameAddr;  /*!< Current frame address */
    uint32_t curFrameBytes; /*!< Current frame bytes */
    uint32_t status;        /*!< CAM module status */
} CAM_Frame_Info;

/*@} end of group CAM_Public_Types */

/** @defgroup  CAM_Public_Constants
 *  @{
 */

/** @defgroup  CAM_ID_TYPE
 *  @{
 */
#define IS_CAM_ID_TYPE(type) (((type) == CAM0_ID) || \
                              ((type) == CAM1_ID) || \
                              ((type) == CAM2_ID) || \
                              ((type) == CAM3_ID) || \
                              ((type) == CAM4_ID) || \
                              ((type) == CAM5_ID) || \
                              ((type) == CAM6_ID) || \
                              ((type) == CAM7_ID) || \
                              ((type) == CAM_ID_MAX))

/** @defgroup  CAM_BURST_TYPE
 *  @{
 */
#define IS_CAM_BURST_TYPE(type) (((type) == CAM_BURST_TYPE_SINGLE) || \
                                 ((type) == CAM_BURST_TYPE_INCR4) ||  \
                                 ((type) == CAM_BURST_TYPE_INCR8) ||  \
                                 ((type) == CAM_BURST_TYPE_INCR16) || \
                                 ((type) == CAM_BURST_TYPE_INCR32) || \
                                 ((type) == CAM_BURST_TYPE_INCR64))

/** @defgroup  CAM_SW_MODE_TYPE
 *  @{
 */
#define IS_CAM_SW_MODE_TYPE(type) (((type) == CAM_SW_MODE_AUTO) || \
                                   ((type) == CAM_SW_MODE_MANUAL))

/** @defgroup  CAM_OUTPUT_DROP_MODE_TYPE
 *  @{
 */
#define IS_CAM_OUTPUT_DROP_MODE_TYPE(type) (((type) == CAM_DROP_NONE) ||               \
                                            ((type) == CAM_DROP_ODD_ROW_ODD_PIXEL) ||  \
                                            ((type) == CAM_DROP_ODD_ROW_EVEN_PIXEL) || \
                                            ((type) == CAM_DROP_ALL_ODD_PIXEL) ||      \
                                            ((type) == CAM_DROP_ALL_EVEN_PIXEL))

/** @defgroup  CAM_INPUT_PIX_WIDTH_TYPE
 *  @{
 */
#define IS_CAM_INPUT_PIX_WIDTH_TYPE(type) (((type) == CAM_PIX_DATA_BIT_16) ||     \
                                           ((type) == CAM_PIX_DATA_BIT_24) ||     \
                                           ((type) == CAM_PIX_DATA_BIT_24TO16) || \
                                           ((type) == CAM_PIX_DATA_BIT_24TO32) || \
                                           ((type) == CAM_PIX_DATA_BIT_8))

/** @defgroup  CAM_8_BIT_BYTE_TYPE
 *  @{
 */
#define IS_CAM_8_BIT_BYTE_TYPE(type) (((type) == CAM_8_BIT_SELECT_LOWER) || \
                                      ((type) == CAM_8_BIT_SELECT_UPPER))

/** @defgroup  CAM_16_BIT_RGB_TYPE
 *  @{
 */
#define IS_CAM_16_BIT_RGB_TYPE(type) (((type) == CAM_16_BIT_RGB) || \
                                      ((type) == CAM_16_BIT_GRB) || \
                                      ((type) == CAM_16_BIT_RBG) || \
                                      ((type) == CAM_16_BIT_GBR) || \
                                      ((type) == CAM_16_BIT_BRG) || \
                                      ((type) == CAM_16_BIT_BGR))

/** @defgroup  CAM_LINE_ACTIVE_POL
 *  @{
 */
#define IS_CAM_LINE_ACTIVE_POL(type) (((type) == CAM_LINE_ACTIVE_POLARITY_LOW) || \
                                      ((type) == CAM_LINE_ACTIVE_POLARITY_HIGH))

/** @defgroup  CAM_FRAME_ACTIVE_POL
 *  @{
 */
#define IS_CAM_FRAME_ACTIVE_POL(type) (((type) == CAM_FRAME_ACTIVE_POLARITY_LOW) || \
                                       ((type) == CAM_FRAME_ACTIVE_POLARITY_HIGH))

/** @defgroup  CAM_SENSOR_MODE_TYPE
 *  @{
 */
#define IS_CAM_SENSOR_MODE_TYPE(type) (((type) == CAM_SENSOR_MODE_V_AND_H) || \
                                       ((type) == CAM_SENSOR_MODE_V_OR_H) ||  \
                                       ((type) == CAM_SENSOR_MODE_V) ||       \
                                       ((type) == CAM_SENSOR_MODE_H))

/** @defgroup  CAM_INT_TYPE
 *  @{
 */
#define IS_CAM_INT_TYPE(type) (((type) == CAM_INT_NORMAL) ||           \
                               ((type) == CAM_INT_MEMORY_OVERWRITE) || \
                               ((type) == CAM_INT_FRAME_OVERWRITE) ||  \
                               ((type) == CAM_INT_FIFO_OVERWRITE) ||   \
                               ((type) == CAM_INT_VSYNC_CNT_ERROR) ||  \
                               ((type) == CAM_INT_HSYNC_CNT_ERROR) ||  \
                               ((type) == CAM_INT_ALL))

/*@} end of group CAM_Public_Constants */

/** @defgroup  CAM_Public_Macros
 *  @{
 */

/*@} end of group CAM_Public_Macros */

/** @defgroup  CAM_Public_Functions
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
void CAM0_IRQHandler(void);
void CAM1_IRQHandler(void);
void CAM2_IRQHandler(void);
void CAM3_IRQHandler(void);
void CAM4_IRQHandler(void);
void CAM5_IRQHandler(void);
void CAM6_IRQHandler(void);
void CAM7_IRQHandler(void);
#endif
void CAM_Init(CAM_ID_Type camId, CAM_CFG_Type *cfg);
void CAM_Deinit(CAM_ID_Type camId);
void CAM_Enable(CAM_ID_Type camId);
void CAM_Disable(CAM_ID_Type camId);
void CAM_Clock_Gate(CAM_ID_Type camId, BL_Fun_Type enable);
void CAM_Hsync_Crop(CAM_ID_Type camId, uint16_t start, uint16_t end);
void CAM_Vsync_Crop(CAM_ID_Type camId, uint16_t start, uint16_t end);
void CAM_Set_Hsync_Total_Count(CAM_ID_Type camId, uint16_t count);
void CAM_Set_Vsync_Total_Count(CAM_ID_Type camId, uint16_t count);
void CAM_Get_Frame_Info(CAM_ID_Type camId, CAM_Frame_Info *info);
uint8_t CAM_Get_Frame_Count(CAM_ID_Type camId);
void CAM_Pop_Frame(CAM_ID_Type camId);
void CAM_IntMask(CAM_ID_Type camId, CAM_INT_Type intType, BL_Mask_Type intMask);
void CAM_IntClr(CAM_ID_Type camId, CAM_INT_Type intType);
void CAM_Int_Callback_Install(CAM_ID_Type camId, CAM_INT_Type intType, intCallback_Type *cbFun);
void CAM_8_Bit_Byte_Select(CAM_ID_Type camId, CAM_8_Bit_Byte_Type byteType);
void CAM_16_Bit_RGB_order(CAM_ID_Type camId, CAM_16_Bit_RGB_Type rgbType);
void CAM_32_Bit_Alpha_Set(CAM_ID_Type camId, uint8_t alpha);
void CAM_Set_Frame_Valid_Period(CAM_ID_Type camId, uint8_t period, uint32_t validBit);
void CAM_HW_Cover_First_Frame_Everytime(CAM_ID_Type camId, BL_Fun_Type enable);

/*@} end of group CAM_Public_Functions */

/*@} end of group CAM */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_CAM_H__ */
