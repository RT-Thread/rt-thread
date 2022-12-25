/**
  ******************************************************************************
  * @file    bl808_dvp_tsrc.h
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
#ifndef __BL808_DVP_TSRC_H__
#define __BL808_DVP_TSRC_H__

#include "dtsrc_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DVP_TSRC
 *  @{
 */

/** @defgroup  DVP_TSRC_Public_Types
 *  @{
 */

/**
 *  @brief DVP_TSRC port type definition
 */
typedef enum {
    DVP_TSRC0_ID,    /*!< DVP TSRC0 port define */
    DVP_TSRC1_ID,    /*!< DVP TSRC1 port define */
    DVP_TSRC_ID_MAX, /*!< DVP TSRC MAX ID define */
} DVP_TSRC_ID_Type;

/**
 *  @brief YUV420 valid line select type definition
 */
typedef enum {
    DVP_TSRC_YUV420_LINE_EVEN, /*!< The even lines are valid, UV will send in Y even lines */
    DVP_TSRC_YUV420_LINE_ODD,  /*!< The odd lines are valid, UV will send in Y odd lines */
} DVP_TSRC_YUV420_Line_Type;

/**
 *  @brief DVP_TSRC swap mode DVP2AXI type definition
 */
typedef enum {
    DVP_TSRC_DVP2AXI_0, /*!< Choose DVP2AXI 0 */
    DVP_TSRC_DVP2AXI_1, /*!< Choose DVP2AXI 1 */
    DVP_TSRC_DVP2AXI_2, /*!< Choose DVP2AXI 2 */
    DVP_TSRC_DVP2AXI_3, /*!< Choose DVP2AXI 3 */
    DVP_TSRC_DVP2AXI_4, /*!< Choose DVP2AXI 4 */
    DVP_TSRC_DVP2AXI_5, /*!< Choose DVP2AXI 5 */
    DVP_TSRC_DVP2AXI_6, /*!< Choose DVP2AXI 6 */
    DVP_TSRC_DVP2AXI_7, /*!< Choose DVP2AXI 7 */
    DVP_TSRC_MJDEC_YY,  /*!< Choose MJDEC YY */
    DVP_TSRC_MJDEC_UV,  /*!< Choose MJDEC UV */
} DVP_TSRC_DVP2AXI_Type;

/**
 *  @brief DVP_TSRC swap index control mode type definition
 */
typedef enum {
    DVP_TSRC_SWAP_HARDWARE, /*!< Swap index is controlled by hardware */
    DVP_TSRC_SWAP_SOFTWARE, /*!< Swap index is controlled by software */
} DVP_TSRC_Swap_Control_Type;

/**
 *  @brief DVP_TSRC pixel format type definition
 */
typedef enum {
    DVP_TSRC_PIXEL_YUV422_16BIT,       /*!< YUV422 16-bit mode */
    DVP_TSRC_PIXEL_RGB888_24BIT,       /*!< RGB888 24-bit mode */
    DVP_TSRC_PIXEL_RGB565_16TO24BIT,   /*!< RGB565 16-bit extend 24-bit mode */
    DVP_TSRC_PIXEL_RGBA8888_32TO24BIT, /*!< RGBA8888 32-bit compress 24-bit mode */
    DVP_TSRC_PIXEL_YUV400_8BIT,        /*!< YUV400 8-bit mode */
} DVP_TSRC_Pixel_Format_Type;

/**
 *  @brief DVP_TSRC AXI burst type definition
 */
typedef enum {
    DVP_TSRC_BURST_TYPE_SINGLE,     /*!< DVP_TSRC AXI burst type:single */
    DVP_TSRC_BURST_TYPE_INCR4,      /*!< DVP_TSRC AXI burst type:incrementing 4 */
    DVP_TSRC_BURST_TYPE_INCR8,      /*!< DVP_TSRC AXI burst type:incrementing 8 */
    DVP_TSRC_BURST_TYPE_INCR16,     /*!< DVP_TSRC AXI burst type:incrementing 16 */
    DVP_TSRC_BURST_TYPE_INCR32 = 5, /*!< DVP_TSRC AXI burst type:incrementing 32 */
    DVP_TSRC_BURST_TYPE_INCR64,     /*!< DVP_TSRC AXI burst type:incrementing 64 */
} DVP_TSRC_Burst_Type;

/**
 *  @brief DVP_TSRC configuration structure type definition
 */
typedef struct
{
    BL_Fun_Type dataFromSensor;             /*!< Enable: pixel data is from sensor, disable: pixel data is from AXI */
    BL_Fun_Type sensorHsyncInverse;         /*!< Enable or disable inverse signal of sensor hsync */
    BL_Fun_Type sensorVsyncInverse;         /*!< Enable or disable inverse signal of sensor vsync */
    BL_Fun_Type yuv420Enable;               /*!< Enable or disable YUV420 mode, YUV420 data is from 2 different planar buffers when enable */
    DVP_TSRC_YUV420_Line_Type lineType;     /*!< Select UV send in Y even lines or odd lines */
    BL_Fun_Type swapMode;                   /*!< Enable or disable swap mode */
    DVP_TSRC_Swap_Control_Type swapControl; /*!< Set swap index controlled by hardware or software */
    DVP_TSRC_DVP2AXI_Type dvp2axi;          /*!< Choose dvp2axi used */
    DVP_TSRC_Pixel_Format_Type format;      /*!< Set pixel data format */
    DVP_TSRC_Burst_Type burst;              /*!< AXI burst length */
    uint8_t byte0;                          /*!< Byte 0 selection */
    uint8_t byte1;                          /*!< Byte 1 Selection */
    uint8_t byte2;                          /*!< Byte 2 Selection */
    uint16_t hTotalCnt;                     /*!< Horizontal total pixel count */
    uint16_t hBlankCnt;                     /*!< Horizontal blank stage pixel count */
    uint16_t vTotalCnt;                     /*!< Vertical total pixel count */
    uint16_t vBlankCnt;                     /*!< Vertical blank stage pixel count */
    uint16_t prefetch;                      /*!< Vertical prefetch start position, relativeto blank start position */
    uint16_t fifoThreshold;                 /*!< FIFO threshold for each DVP line to start to output */
    uint32_t memStartY0;                    /*!< AXI2DVP start address, Y-planar in YUV420 mode, frame 0 in swap mode */
    uint32_t memSizeY0;                     /*!< AXI2DVP memory size of memStartY0 */
    uint32_t memStartY1;                    /*!< AXI2DVP start address, Y-planar in YUV420 mode, frame 1 in swap mode, don't care if not swap mode */
    uint32_t memStartUV0;                   /*!< AXI2DVP start address, UV-planar in YUV420 mode, frame 0 in swap mode, don't care if not YUV420 mode */
    uint32_t memStartUV1;                   /*!< AXI2DVP start address, UV-planar in YUV420 mode, frame 1 in swap mode, don't care if not YUV420 swap mode */
} DVP_TSRC_Cfg_Type;

/**
 *  @brief DVP_TSRC fake gradient data configuration structure type definition
 */
typedef struct
{
    uint16_t minData; /*!< Minimum data value of fake gradient data */
    uint16_t maxData; /*!< Maximum data value of fake gradient data */
    uint8_t step;     /*!< Data step value for eack line of fake gradient data */
} DVP_TSRC_Fake_Data_Cfg_Type;

/**
 *  @brief DVP_TSRC CEA-861 configuration structure type definition
 */
typedef struct
{
    uint8_t hsyncStart; /*!< Hsync start position, relative to blank start position */
    uint8_t hsyncEnd;   /*!< Hsync end position, relative to blank start position */
    uint8_t vsyncStart; /*!< Vsync start position, relative to blank start position */
    uint8_t vsyncEnd;   /*!< Vsync end position, relative to blank start position */
} DVP_TSRC_CEA861_Cfg_Type;

/*@} end of group DVP_TSRC_Public_Types */

/** @defgroup  DVP_TSRC_Public_Constants
 *  @{
 */

/** @defgroup  DVP_TSRC_ID_TYPE
 *  @{
 */
#define IS_DVP_TSRC_ID_TYPE(type) (((type) == DVP_TSRC0_ID) || \
                                   ((type) == DVP_TSRC1_ID) || \
                                   ((type) == DVP_TSRC_ID_MAX))

/** @defgroup  DVP_TSRC_YUV420_LINE_TYPE
 *  @{
 */
#define IS_DVP_TSRC_YUV420_LINE_TYPE(type) (((type) == DVP_TSRC_YUV420_LINE_EVEN) || \
                                            ((type) == DVP_TSRC_YUV420_LINE_ODD))

/** @defgroup  DVP_TSRC_DVP2AXI_TYPE
 *  @{
 */
#define IS_DVP_TSRC_DVP2AXI_TYPE(type) (((type) == DVP_TSRC_DVP2AXI_0) || \
                                        ((type) == DVP_TSRC_DVP2AXI_1) || \
                                        ((type) == DVP_TSRC_DVP2AXI_2) || \
                                        ((type) == DVP_TSRC_DVP2AXI_3) || \
                                        ((type) == DVP_TSRC_DVP2AXI_4) || \
                                        ((type) == DVP_TSRC_DVP2AXI_5) || \
                                        ((type) == DVP_TSRC_DVP2AXI_6) || \
                                        ((type) == DVP_TSRC_DVP2AXI_7) || \
                                        ((type) == DVP_TSRC_MJDEC_YY) || \
                                        ((type) == DVP_TSRC_MJDEC_UV))

/** @defgroup  DVP_TSRC_SWAP_CONTROL_TYPE
 *  @{
 */
#define IS_DVP_TSRC_SWAP_CONTROL_TYPE(type) (((type) == DVP_TSRC_SWAP_HARDWARE) || \
                                             ((type) == DVP_TSRC_SWAP_SOFTWARE))

/** @defgroup  DVP_TSRC_PIXEL_FORMAT_TYPE
 *  @{
 */
#define IS_DVP_TSRC_PIXEL_FORMAT_TYPE(type) (((type) == DVP_TSRC_PIXEL_YUV422_16BIT) ||       \
                                             ((type) == DVP_TSRC_PIXEL_RGB888_24BIT) ||       \
                                             ((type) == DVP_TSRC_PIXEL_RGB565_16TO24BIT) ||   \
                                             ((type) == DVP_TSRC_PIXEL_RGBA8888_32TO24BIT) || \
                                             ((type) == DVP_TSRC_PIXEL_YUV400_8BIT))

/** @defgroup  DVP_TSRC_BURST_TYPE
 *  @{
 */
#define IS_DVP_TSRC_BURST_TYPE(type) (((type) == DVP_TSRC_BURST_TYPE_SINGLE) || \
                                      ((type) == DVP_TSRC_BURST_TYPE_INCR4) ||  \
                                      ((type) == DVP_TSRC_BURST_TYPE_INCR8) ||  \
                                      ((type) == DVP_TSRC_BURST_TYPE_INCR16) || \
                                      ((type) == DVP_TSRC_BURST_TYPE_INCR32) || \
                                      ((type) == DVP_TSRC_BURST_TYPE_INCR64))

/*@} end of group DVP_TSRC_Public_Constants */

/** @defgroup  DVP_TSRC_Public_Macros
 *  @{
 */

/*@} end of group DVP_TSRC_Public_Macros */

/** @defgroup  DVP_TSRC_Public_Functions
 *  @{
 */
BL_Err_Type DVP_TSRC_Init(DVP_TSRC_ID_Type tsrcId, DVP_TSRC_Cfg_Type *dvpTsrcCfg);
void DVP_TSRC_Fake_Data_Init(DVP_TSRC_ID_Type tsrcId, DVP_TSRC_Fake_Data_Cfg_Type *dataCfg);
void DVP_TSRC_CEA861_Init(DVP_TSRC_ID_Type tsrcId, DVP_TSRC_CEA861_Cfg_Type *ceaCfg);
void DVP_TSRC_Sensor_Input_Set(DVP_TSRC_ID_Type tsrcId, uint16_t threshold, BL_Fun_Type hsyncInv, BL_Fun_Type vsyncInv);
void DVP_TSRC_Enable(DVP_TSRC_ID_Type tsrcId);
void DVP_TSRC_Disable(DVP_TSRC_ID_Type tsrcId);
void DVP_TSRC_Set_Swap_Index(DVP_TSRC_ID_Type tsrcId, uint8_t index);
void DVP_TSRC_Clear_Drain_Error(DVP_TSRC_ID_Type tsrcId);
uint32_t DVP_TSRC_Get_Status(DVP_TSRC_ID_Type tsrcId);

/*@} end of group DVP_TSRC_Public_Functions */

/*@} end of group DVP_TSRC */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_DVP_TSRC_H__ */
