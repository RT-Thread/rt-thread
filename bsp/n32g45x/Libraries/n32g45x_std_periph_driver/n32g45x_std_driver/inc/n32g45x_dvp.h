/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g45x_dvp.h
 * @author Nations Solution Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */

#ifndef __N32G45X_DVP_H__
#define __N32G45X_DVP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g45x.h"

/** @addtogroup N32G45X_StdPeriph_Driver
 * @{
 */

/** @addtogroup DVP
 * @brief DVP driver modules
 * @{
 */

/** @addtogroup DVP_Exported_Types
 * @{
 */
/**
 * @brief  DVP Init Structure definition
 */
typedef struct
{
    uint32_t FifoWatermark; /*!< It's will request INT or DMA when the datas reach this number in DATFIFO.*/

    uint16_t LineCapture; /*!< Specifies the number of data line captuered in x lines.
                                                                          This parameter can be a value of @ref
                             DVP_LineSelect_Mode */

    uint16_t ByteCapture; /*!< Specifies the number of stop byte captuered in x bytes.
                                                                          This parameter can be a value of @ref
                             DVP_ByteSelect_Mode */

    uint16_t DataInvert; /*!< Specifies the data invert.
                                                                         This parameter can be a value of @ref
                            DVP_DATA_INVERT */

    uint16_t PixelClkPolarity; /*!< Specifies the pixel clock polarity
                                                                               This parameter can be a value of @ref
                                  DVP_Pixel_Polarity  */

    uint16_t VsyncPolarity; /*!< Specifies the vertical synchronization polarity
                                                                            This parameter can be a value of @ref
                               DVP_Vsync_Polarity  */

    uint16_t HsyncPolarity; /*!< Specifies the Horizontal synchronization polarity
                                                                            This parameter can be a value of @ref
                               DVP_Hsync_Polarity  */

    uint16_t CaptureMode; /*!< Specifies the capture mode.
                                                                          This parameter can be a value of @ref
                             DVP_Capture_Mode */

    uint16_t RowStart; /*!< Specifies the startint row of the pixel array in a frame */

    uint16_t ColumnStart; /*!< Specifies the starting column of the pixel array row in a frame */

    uint16_t ImageHeight; /*!< Specifies the image's  height in a frame */

    uint16_t ImageWidth; /*!< Specifies the image's  width in a frame */

} DVP_InitType;
/**
 * @}
 */

/** @addtogroup DVP_Exported_Constants
 * @{
 */
#define IS_DVP_ALL_PERIPH(PERIPH) (((PERIPH) == DVP))

/** @addtogroup DVP_FIFO_SOFT_RESET
 * @{
 */
#define DVP_FIFO_SOFT_RESET ((uint32_t)0x10000)
/**
 * @}
 */

/** @addtogroup DVP_LineSelect_Mode
 * @{
 */
#define DVP_LSM_MASK (0xe00)
#define DVP_LSM_POS  (9)

#define DVP_LINE_CAPTURE_ALL ((uint32_t)0x0000)
#define DVP_LINE_CAPTURE_1_2 ((uint32_t)0x0200)
#define DVP_LINE_CAPTURE_1_3 ((uint32_t)0x0400)
#define DVP_LINE_CAPTURE_1_4 ((uint32_t)0x0600)
#define DVP_LINE_CAPTURE_1_5 ((uint32_t)0x0800)
#define DVP_LINE_CAPTURE_1_6 ((uint32_t)0x0A00)
#define DVP_LINE_CAPTURE_1_7 ((uint32_t)0x0C00)
#define DVP_LINE_CAPTURE_1_8 ((uint32_t)0x0E00)
#define IS_DVP_ROW_CAPTURE(LSM)                                                                                        \
    (((LSM) == DVP_LINE_CAPTURE_ALL) || ((LSM) == DVP_LINE_CAPTURE_1_2) || ((LSM) == DVP_LINE_CAPTURE_1_3)             \
     || ((LSM) == DVP_LINE_CAPTURE_1_4) || ((LSM) == DVP_LINE_CAPTURE_1_5) || ((LSM) == DVP_LINE_CAPTURE_1_6)          \
     || ((LSM) == DVP_LINE_CAPTURE_1_7) || ((LSM) == DVP_LINE_CAPTURE_1_8))
/**
 * @}
 */

/** @addtogroup DVP_ByteSelect_Mode
 * @{
 */
#define DVP_BSM_MASK         (0x1c0)
#define DVP_BSM_POS          (6)
#define DVP_BYTE_CAPTURE_ALL ((uint32_t)0x0000)
#define DVP_BYTE_CAPTURE_1_2 ((uint32_t)0x0020)
#define DVP_BYTE_CAPTURE_1_3 ((uint32_t)0x0040)
#define DVP_BYTE_CAPTURE_1_4 ((uint32_t)0x0060)
#define DVP_BYTE_CAPTURE_1_5 ((uint32_t)0x0080)
#define DVP_BYTE_CAPTURE_1_6 ((uint32_t)0x00A0)
#define DVP_BYTE_CAPTURE_1_7 ((uint32_t)0x00C0)
#define DVP_BYTE_CAPTURE_1_8 ((uint32_t)0x00E0)
#define IS_DVP_COLUMN_CAPTURE(BSM)                                                                                     \
    (((BSM) == DVP_BYTE_CAPTURE_ALL) || ((BSM) == DVP_BYTE_CAPTURE_1_2) || ((BSM) == DVP_BYTE_CAPTURE_1_3)             \
     || ((BSM) == DVP_BYTE_CAPTURE_1_4) || ((BSM) == DVP_BYTE_CAPTURE_1_5) || ((BSM) == DVP_BYTE_CAPTURE_1_6)          \
     || ((BSM) == DVP_BYTE_CAPTURE_1_7) || ((BSM) == DVP_BYTE_CAPTURE_1_8))
/**
 * @}
 */

/** @addtogroup DVP_DATA_INVERT
 * @{
 */
#define DVP_DATA_INVERT            ((uint32_t)0x0020)
#define DVP_DATA_NOTINVERT         ((uint32_t)0x0000)
#define IS_DVP_DATA_INVERT(DATINV) (((DATINV) == DVP_DATA_NOTINVERT) || ((DATINV) == DVP_DATA_INVERT))
/**
 * @}
 */

/** @addtogroup DVP_Pixel_Polarity
 * @{
 */
#define DVP_PIXEL_POLARITY_FALLING ((uint32_t)0x0000)
#define DVP_PIXEL_POLARITY_RISING  ((uint32_t)0x0010)
#define IS_DVP_PIXEL_POLARITY(PCKPOL)                                                                                  \
    (((PCKPOL) == DVP_PIXEL_POLARITY_FALLING) || ((PCKPOL) == DVP_PIXEL_POLARITY_RISING))
/**
 * @}
 */

#define DVP_WATER_MARK_POS              ((uint32_t)12)
#define DVP_WATER_MARK_MASK             ((uint32_t)0xF000)
#define IS_DVP_FIFOWATERMARK(WATERMARK) ((WATERMARK) > 0 && (WATERMARK) <= 4)

/** @addtogroup DVP_Vsync_Polarity
 * @{
 */
#define DVP_VSYNC_POLARITY_HIGH       ((uint32_t)0x0008)
#define DVP_VSYNC_POLARITY_LOW        ((uint32_t)0x0000)
#define IS_DVP_VSYNC_POLARITY(VSYNCP) (((VSYNCP) == DVP_VSYNC_POLARITY_HIGH) || ((VSYNCP) == DVP_VSYNC_POLARITY_LOW))
/**
 * @}
 */

/** @addtogroup DVP_Hsync_Polarity
 * @{
 */
#define DVP_HSYNC_POLARITY_HIGH       ((uint32_t)0x0004)
#define DVP_HSYNC_POLARITY_LOW        ((uint32_t)0x0000)
#define IS_DVP_HSYNC_POLARITY(HSYNCP) (((HSYNCP) == DVP_HSYNC_POLARITY_HIGH) || ((HSYNCP) == DVP_HSYNC_POLARITY_LOW))
/**
 * @}
 */

/** @addtogroup DVP_Capture_Mode
 * @{
 */
#define DVP_CAPTURE_MODE_SINGLE    ((uint32_t)0x0000)
#define DVP_CAPTURE_MODE_CONTINUE  ((uint32_t)0x0002)
#define IS_DVP_CAPTURE_MODE(CMODE) (((CMODE) == DVP_CAPTURE_MODE_SINGLE) || ((CMODE) == DVP_CAPTURE_MODE_CONTINUE))
/**
 * @}
 */

/** @addtogroup DVP_CAPTURE_ENABLE
 * @{
 */
#define DVP_CAPTURE_DISABLE     ((uint32_t)0x0000)
#define DVP_CAPTURE_ENABLE      ((uint32_t)0x0001)
#define IS_DVP_CAPTURE(CAPTURE) (((CAPTURE) == DVP_CAPTURE_DISABLE) || ((CAPTURE) == DVP_CAPTURE_ENABLE))
/**
 * @}
 */

/** @addtogroup DVP_DMA
 * @{
 */
#define DVP_DMA_DISABLE ((uint32_t)0x0000)
#define DVP_DMA_ENABLE  ((uint32_t)0x0400)
/**
 * @}
 */

/** @addtogroup DVP_Marked_interrupt
 * @{
 */
#define DVP_FLAG_HERR ((uint32_t)0x0200)
#define DVP_FLAG_VERR ((uint32_t)0x0100)
#define DVP_FLAG_FO   ((uint32_t)0x0080)
#define DVP_FLAG_FW   ((uint32_t)0x0040)
#define DVP_FLAG_FF   ((uint32_t)0x0020)
#define DVP_FLAG_FE   ((uint32_t)0x0010)
#define DVP_FLAG_LE   ((uint32_t)0x0008)
#define DVP_FLAG_LS   ((uint32_t)0x0004)
#define DVP_FLAG_FME  ((uint32_t)0x0002)
#define DVP_FLAG_FMS  ((uint32_t)0x0001)
#define IS_DVP_FLAG(FLAG)                                                                                              \
    (((FLAG) == DVP_FLAG_FMS) || ((FLAG) == DVP_FLAG_FME) || ((FLAG) == DVP_FLAG_LS) || ((FLAG) == DVP_FLAG_LE)        \
     || ((FLAG) == DVP_FLAG_FE) || ((FLAG) == DVP_FLAG_FF) || ((FLAG) == DVP_FLAG_FW) || ((FLAG) == DVP_FLAG_FO)       \
     || ((FLAG) == DVP_FLAG_VERR) || ((FLAG) == DVP_FLAG_HERR))

#define IS_DVP_CLEAR_FLAG(FLAG)                                                                                        \
    (((FLAG) == DVP_FLAG_FMS) || ((FLAG) == DVP_FLAG_FME) || ((FLAG) == DVP_FLAG_LS) || ((FLAG) == DVP_FLAG_LE)        \
     || ((FLAG) == DVP_FLAG_FE) || ((FLAG) == DVP_FLAG_FO) || ((FLAG) == DVP_FLAG_VERR) || ((FLAG) == DVP_FLAG_HERR))
/**
 * @}
 */

/** @addtogroup DVP_Interrupts
 * @{
 */
#define DVP_INT_HERR ((uint32_t)0x0200)
#define DVP_INT_VERR ((uint32_t)0x0100)
#define DVP_INT_FO   ((uint32_t)0x0080)
#define DVP_INT_FW   ((uint32_t)0x0040)
#define DVP_INT_FF   ((uint32_t)0x0020)
#define DVP_INT_FE   ((uint32_t)0x0010)
#define DVP_INT_LE   ((uint32_t)0x0008)
#define DVP_INT_LS   ((uint32_t)0x0004)
#define DVP_INT_FME  ((uint32_t)0x0002)
#define DVP_INT_FMS  ((uint32_t)0x0001)
#define IS_DVP_INT(IT)                                                                                                 \
    (((IT) == DVP_INT_FMS) || ((IT) == DVP_INT_FME) || ((IT) == DVP_INT_LS) || ((IT) == DVP_INT_LE)                    \
     || ((IT) == DVP_INT_FE) || ((IT) == DVP_INT_FF) || ((IT) == DVP_INT_FW) || ((IT) == DVP_INT_FO)                   \
     || ((IT) == DVP_INT_VERR) || ((IT) == DVP_INT_HERR))
/**
 * @}
 */

/** @addtogroup DVP_Flag
 * @{
 */
#define DVP_MINT_HERR ((uint32_t)0x0200)
#define DVP_MINT_VERR ((uint32_t)0x0100)
#define DVP_MINT_FO   ((uint32_t)0x0080)
#define DVP_MINT_FW   ((uint32_t)0x0040)
#define DVP_MINT_FF   ((uint32_t)0x0020)
#define DVP_MINT_FE   ((uint32_t)0x0010)
#define DVP_MINT_LE   ((uint32_t)0x0008)
#define DVP_MINT_LS   ((uint32_t)0x0004)
#define DVP_MINT_FME  ((uint32_t)0x0002)
#define DVP_MINT_FMS  ((uint32_t)0x0001)
#define IS_DVP_MINT(Status)                                                                                            \
    (((Status) == DVP_MINT_FMS) || ((Status) == DVP_MINT_FME) || ((Status) == DVP_MINT_LS)                             \
     || ((Status) == DVP_MINT_LE) || ((Status) == DVP_MINT_FE) || ((Status) == DVP_MINT_FF)                            \
     || ((Status) == DVP_MINT_FW) || ((Status) == DVP_MINT_FO) || ((Status) == DVP_MINT_VERR)                          \
     || ((Status) == DVP_MINT_HERR))
/**
 * @}
 */

/**
 * @}
 */

/** @addtogroup DVP_Exported_Functions
 * @{
 */
void DVP_DeInit(DVP_Module* DVPx);
FlagStatus DVP_GetFlagStatus(DVP_Module* DVPx, uint16_t DVP_FLAG);
void DVP_ClrFlag(DVP_Module* DVPx, uint16_t DVP_FLAG);
INTStatus DVP_GetIntStatus(DVP_Module* DVPx, uint16_t DVP_IT);
void DVP_Init(DVP_Module* DVPx, DVP_InitType* DVP_InitStruct);
void DVP_InitStruct(DVP_InitType* DVP_InitStruct);
void DVP_Enable(DVP_Module* DVPx, FunctionalState Cmd);
void DVP_EnableDma(DVP_Module* DVPx, FunctionalState Cmd);
uint32_t DVP_ReadFifo(DVP_Module* DVPx);
uint32_t DVP_GetFifoCount(DVP_Module* DVPx);
void DVP_SetFifoWatermark(DVP_Module* DVPx, uint16_t Watermark);
void DVP_ResetFifo(DVP_Module* DVPx);
/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */

#endif
