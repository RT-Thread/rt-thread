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
 * @file n32g4fr_dvp.h
 * @author Nations
 * @version v1.0.3
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */

#ifndef __N32G4FR_DVP_H__
#define __N32G4FR_DVP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g4fr.h"

/** @addtogroup N32G4FR_StdPeriph_Driver
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
    uint32_t FifoWatermark; /*!< Specifies the max number of fifo data which will request INT or DMA
                               This parameter can be a value of @ref DVP_FifoWatermark */

    uint16_t LineCapture; /*!< Specifies the number of data line captuered in x lines.
                            This parameter can be a value of @ref DVP_LineSelect_Mode */

    uint16_t ByteCapture; /*!< Specifies the number of stop byte captuered in x bytes.
                            This parameter can be a value of @ref DVP_ByteSelect_Mode */

    uint16_t DataInvert; /*!< Specifies the data invert.
                            This parameter can be a value of @ref DVP_DATA_INVERT */

    uint16_t PixelClkPolarity; /*!< Specifies the pixel clock polarity
                                    This parameter can be a value of @ref DVP_Pixel_Polarity  */

    uint16_t VsyncPolarity; /*!< Specifies the vertical synchronization polarity
                                This parameter can be a value of @ref DVP_Vsync_Polarity  */

    uint16_t HsyncPolarity; /*!< Specifies the Horizontal synchronization polarity
                            This parameter can be a value of @ref DVP_Hsync_Polarity  */

    uint16_t CaptureMode; /*!< Specifies the capture mode.
                            This parameter can be a value of @ref DVP_Capture_Mode */

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

/** @addtogroup DVP_FIFO_SOFT_RESET
 * @{
 */
#define DVP_FIFO_SOFT_RESET             (DVP_CTRL_FFSWRST)
/**
 * @}
 */

/** @addtogroup DVP_LineSelect_Mode
 * @{
 */
#define DVP_LINE_CAPTURE_ALL            (0x00000000)
#define DVP_LINE_CAPTURE_1_2            (0x1UL << DVP_CTRL_LSM_SHIFT)
#define DVP_LINE_CAPTURE_1_3            (0x2UL << DVP_CTRL_LSM_SHIFT)
#define DVP_LINE_CAPTURE_1_4            (0x3UL << DVP_CTRL_LSM_SHIFT)
#define DVP_LINE_CAPTURE_1_5            (0x4UL << DVP_CTRL_LSM_SHIFT)
#define DVP_LINE_CAPTURE_1_6            (0x5UL << DVP_CTRL_LSM_SHIFT)
#define DVP_LINE_CAPTURE_1_7            (0x6UL << DVP_CTRL_LSM_SHIFT)
#define DVP_LINE_CAPTURE_1_8            (0x7UL << DVP_CTRL_LSM_SHIFT)
#define IS_DVP_LINE_CAPTURE(_LSM_)      (((_LSM_) & (~DVP_CTRL_LSM_MASK) )==0)
/**
 * @}
 */

/** @addtogroup DVP_ByteSelect_Mode
 * @{
 */
#define DVP_BYTE_CAPTURE_ALL            (0x00000000)
#define DVP_BYTE_CAPTURE_1_2            (0x1UL << DVP_CTRL_BSM_SHIFT)
#define DVP_BYTE_CAPTURE_1_3            (0x2UL << DVP_CTRL_BSM_SHIFT)
#define DVP_BYTE_CAPTURE_1_4            (0x3UL << DVP_CTRL_BSM_SHIFT)
#define DVP_BYTE_CAPTURE_1_5            (0x4UL << DVP_CTRL_BSM_SHIFT)
#define DVP_BYTE_CAPTURE_1_6            (0x5UL << DVP_CTRL_BSM_SHIFT)
#define DVP_BYTE_CAPTURE_1_7            (0x6UL << DVP_CTRL_BSM_SHIFT)
#define DVP_BYTE_CAPTURE_1_8            (0x7UL << DVP_CTRL_BSM_SHIFT)
#define IS_DVP_BYTE_CAPTURE(_BSM_)      (((_BSM_) & (~DVP_CTRL_BSM_MASK) )==0)

/**
 * @}
 */

/** @addtogroup DVP_DATA_INVERT
 * @{
 */
#define DVP_DATA_INVERT                 (DVP_CTRL_DATINV)
#define DVP_DATA_NOTINVERT              (0x00000000)
#define IS_DVP_DATA_INVERT(_INV_)       (((_INV_) & (~DVP_CTRL_DATINV_MASK) )==0)
/**
 * @}
 */

/** @addtogroup DVP_Pixel_Polarity
 * @{
 */
#define DVP_PIXEL_POLARITY_FALLING      (0x00000000)
#define DVP_PIXEL_POLARITY_RISING       (DVP_CTRL_PCKPOL)
#define IS_DVP_PIXEL_POLARITY(_POL_)    (((_POL_) & (~DVP_CTRL_PCKPOL_MASK) )==0)
/**
 * @}
 */

/** @addtogroup DVP_FifoWatermark
 * @{
 */
#define DVP_WATER_MARK_0                (0x00000000)
#define DVP_WATER_MARK_1                (0x1UL << DVP_CTRL_FWM_SHIFT)
#define DVP_WATER_MARK_2                (0x2UL << DVP_CTRL_FWM_SHIFT)
#define DVP_WATER_MARK_3                (0x3UL << DVP_CTRL_FWM_SHIFT)
#define DVP_WATER_MARK_4                (0x4UL << DVP_CTRL_FWM_SHIFT)
#define DVP_WATER_MARK_5                (0x5UL << DVP_CTRL_FWM_SHIFT)
#define DVP_WATER_MARK_6                (0x6UL << DVP_CTRL_FWM_SHIFT)
#define DVP_WATER_MARK_7                (0x7UL << DVP_CTRL_FWM_SHIFT)

#define IS_DVP_FIFOWATERMARK(_WATER_)   (((_WATER_) >= DVP_WATER_MARK_1) && ((_WATER_) <= DVP_WATER_MARK_7))

/** @addtogroup DVP_Vsync_Polarity
 * @{
 */
#define DVP_VSYNC_POLARITY_HIGH         (DVP_CTRL_VSPOL)
#define DVP_VSYNC_POLARITY_LOW          (0x00000000)
#define IS_DVP_VSYNC_POLARITY(_POL_)    (((_POL_) == DVP_VSYNC_POLARITY_HIGH) || ((_POL_) == DVP_VSYNC_POLARITY_LOW))
/**
 * @}
 */

/** @addtogroup DVP_Hsync_Polarity
 * @{
 */
#define DVP_HSYNC_POLARITY_HIGH         (DVP_CTRL_HSPOL)
#define DVP_HSYNC_POLARITY_LOW          (0x00000000)
#define IS_DVP_HSYNC_POLARITY(_POL_)    (((_POL_) == DVP_HSYNC_POLARITY_HIGH) || ((_POL_) == DVP_HSYNC_POLARITY_LOW))
/**
 * @}
 */

/** @addtogroup DVP_Capture_Mode
 * @{
 */
#define DVP_CAPTURE_MODE_SINGLE         (0x00000000)
#define DVP_CAPTURE_MODE_CONTINUE       (DVP_CTRL_CM)
#define IS_DVP_CAPTURE_MODE(_MODE_)     (((_MODE_) == DVP_CAPTURE_MODE_SINGLE) || ((_MODE_) == DVP_CAPTURE_MODE_CONTINUE))
/**
 * @}
 */

/** @addtogroup DVP_CAPTURE_ENABLE
 * @{
 */
#define DVP_CAPTURE_DISABLE             (0x00000000)
#define DVP_CAPTURE_ENABLE              (DVP_CTRL_CAPTURE)
#define IS_DVP_CAPTURE(_CAPTURE_)       (((_CAPTURE_) == DVP_CAPTURE_DISABLE) || ((_CAPTURE_) == DVP_CAPTURE_ENABLE))
/**
 * @}
 */

/** @addtogroup DVP_DMA
 * @{
 */
#define DVP_DMA_DISABLE                 (0x00000000)
#define DVP_DMA_ENABLE                  (DVP_INTEN_DMAEN)
/**
 * @}
 */

/** @addtogroup DVP_StatusFlag
 * @{
 */
#define DVP_FLAG_HERR                   (DVP_INTSTS_HERRIS)
#define DVP_FLAG_VERR                   (DVP_INTSTS_VERRIS)
#define DVP_FLAG_FO                     (DVP_INTSTS_FOIS)
#define DVP_FLAG_FW                     (DVP_INTSTS_FWIS)
#define DVP_FLAG_FF                     (DVP_INTSTS_FFIS)
#define DVP_FLAG_FE                     (DVP_INTSTS_FEIS)
#define DVP_FLAG_LE                     (DVP_INTSTS_LEIS)
#define DVP_FLAG_LS                     (DVP_INTSTS_LSIS)
#define DVP_FLAG_FME                    (DVP_INTSTS_FMEIS)
#define DVP_FLAG_FMS                    (DVP_INTSTS_FMSIS)
#define DVP_FLAG_MASK                   (DVP_FLAG_HERR |DVP_FLAG_VERR |DVP_FLAG_FO  \
                                        |DVP_FLAG_FW   |DVP_FLAG_FF   |DVP_FLAG_FE  \
                                        |DVP_FLAG_LE |DVP_FLAG_LS     |DVP_FLAG_FME \
                                        |DVP_FLAG_FMS)
#define IS_DVP_FLAG(_FLAG_)             (((_FLAG_) & (~DVP_FLAG_MASK))==0)

/** @addtogroup DVP_ClearFlag
 * @{
 */
#define DVP_CLEAR_FLAG_HERR             (DVP_INTSTS_HERRIS)
#define DVP_CLEAR_FLAG_VERR             (DVP_INTSTS_VERRIS)
#define DVP_CLEAR_FLAG_FO               (DVP_INTSTS_FOIS)
#define DVP_CLEAR_FLAG_FE               (DVP_INTSTS_FEIS)
#define DVP_CLEAR_FLAG_LE               (DVP_INTSTS_LEIS)
#define DVP_CLEAR_FLAG_LS               (DVP_INTSTS_LSIS)
#define DVP_CLEAR_FLAG_FME              (DVP_INTSTS_FMEIS)
#define DVP_CLEAR_FLAG_FMS              (DVP_INTSTS_FMSIS)
#define DVP_CLEAR_FLAG_MASK             (DVP_CLEAR_FLAG_HERR |DVP_CLEAR_FLAG_VERR   \
                                        |DVP_CLEAR_FLAG_FO   |DVP_CLEAR_FLAG_FE     \
                                        |DVP_CLEAR_FLAG_LE   |DVP_CLEAR_FLAG_LS     \
                                        |DVP_CLEAR_FLAG_FME  |DVP_CLEAR_FLAG_FMS)
#define IS_DVP_CLEAR_FLAG(_FLAG_)             (((_FLAG_) & (~DVP_CLEAR_FLAG_MASK))==0)


/**
 * @}
 */

/** @addtogroup DVP_IntEnable
 * @{
 */
#define DVP_INTEN_HERR                  (DVP_INTEN_HERRIE)
#define DVP_INTEN_VERR                  (DVP_INTEN_VERRIE)
#define DVP_INTEN_FO                    (DVP_INTEN_FOIE)
#define DVP_INTEN_FW                    (DVP_INTEN_FWIE)
#define DVP_INTEN_FF                    (DVP_INTEN_FFIE)
#define DVP_INTEN_FE                    (DVP_INTEN_FEIE)
#define DVP_INTEN_LE                    (DVP_INTEN_LEIE)
#define DVP_INTEN_LS                    (DVP_INTEN_LSIE)
#define DVP_INTEN_FME                   (DVP_INTEN_FMEIE)
#define DVP_INTEN_FMS                   (DVP_INTEN_FMSIE)
#define DVP_INTEN_MASK                  (DVP_INTEN_HERR |DVP_INTEN_VERR |DVP_INTEN_FO |DVP_INTEN_FW     \
                                        |DVP_INTEN_FF   |DVP_INTEN_FE   |DVP_INTEN_LE |DVP_INTEN_LS     \
                                        |DVP_INTEN_FME  |DVP_INTEN_FMS)
#define IS_DVP_INTEN(_INT_)             (((_INT_) & (~DVP_INTEN_MASK))==0)
/**
 * @}
 */

/** @addtogroup DVP_IntMark
 * @{
 */
#define DVP_MINT_HERR                   (DVP_MINTSTS_HERRMIS)
#define DVP_MINT_VERR                   (DVP_MINTSTS_VERRMIS)
#define DVP_MINT_FO                     (DVP_MINTSTS_FOMIS)
#define DVP_MINT_FW                     (DVP_MINTSTS_FWMIS)
#define DVP_MINT_FF                     (DVP_MINTSTS_FFMIS)
#define DVP_MINT_FE                     (DVP_MINTSTS_FEMIS)
#define DVP_MINT_LE                     (DVP_MINTSTS_LEMIS)
#define DVP_MINT_LS                     (DVP_MINTSTS_LSMIS)
#define DVP_MINT_FME                    (DVP_MINTSTS_FMEMIS)
#define DVP_MINT_FMS                    (DVP_MINTSTS_FMSMIS)
#define DVP_MINT_MASK                   (DVP_MINT_HERR |DVP_MINT_VERR |DVP_MINT_FO |DVP_MINT_FW     \
                                        |DVP_MINT_FF   |DVP_MINT_FE   |DVP_MINT_LE |DVP_MINT_LS     \
                                        |DVP_MINT_FME  |DVP_MINT_FMS)
#define IS_DVP_MINT(_MINT_)             (((_MINT_) & (~DVP_MINT_MASK))==0)
/**
 * @}
 */

/* Exported macros -----------------------------------------------------------*/
/** @addtogroup DVP_Exported_Macros
 * @{
 */

/**
 * @brief  Config the water mark of FIFO.
 * @param _Watermark_ Select the new water mark of FIFO.
 *  This parameter can be one of the following values:
 *      @arg DVP_WATER_MARK_1
 *      @arg DVP_WATER_MARK_2
 *      @arg DVP_WATER_MARK_3
 *      @arg DVP_WATER_MARK_4
 * @retval None
 */
#define __DVP_SetFifoWatermark(_Watermark_)     (MODIFY_REG(DVP->CTRL, DVP_CTRL_FWM_MASK, _Watermark_))

/**
 * @brief  Config the line capture mode.
 * @param _LSM_ Specifies the new mode of line capture.
 *  This parameter can be one of the following values:
 *      @arg DVP_LINE_CAPTURE_ALL   Capture all lines
 *      @arg DVP_LINE_CAPTURE_1_2   Capture 1 line of each 2 lines
 *      @arg DVP_LINE_CAPTURE_1_3   Capture 1 line of each 3 lines
 *      @arg DVP_LINE_CAPTURE_1_4   Capture 1 line of each 4 lines
 *      @arg DVP_LINE_CAPTURE_1_5   Capture 1 line of each 5 lines
 *      @arg DVP_LINE_CAPTURE_1_6   Capture 1 line of each 6 lines
 *      @arg DVP_LINE_CAPTURE_1_7   Capture 1 line of each 7 lines
 *      @arg DVP_LINE_CAPTURE_1_8   Capture 1 line of each 8 lines
 * @retval None
 */
#define __DVP_SetLineCaptureMode(_LSM_)        (MODIFY_REG(DVP->CTRL, DVP_CTRL_LSM_MASK, _LSM_))

/**
 * @brief  Config the byte capture mode.
 * @param _BSM_ Specifies the new mode of byte capture.
 *  This parameter can be one of the following values:
 *      @arg DVP_BYTE_CAPTURE_ALL   Capture all pixels
 *      @arg DVP_BYTE_CAPTURE_1_2   Capture 1 pixel of each 2 pixels
 *      @arg DVP_BYTE_CAPTURE_1_3   Capture 1 pixel of each 3 pixels
 *      @arg DVP_BYTE_CAPTURE_1_4   Capture 1 pixel of each 4 pixels
 *      @arg DVP_BYTE_CAPTURE_1_5   Capture 1 pixel of each 5 pixels
 *      @arg DVP_BYTE_CAPTURE_1_6   Capture 1 pixel of each 6 pixels
 *      @arg DVP_BYTE_CAPTURE_1_7   Capture 1 pixel of each 7 pixels
 *      @arg DVP_BYTE_CAPTURE_1_8   Capture 1 pixel of each 8 pixels
 * @retval None
 */
#define __DVP_SetByteCaptureMode(_BSM_)        (MODIFY_REG(DVP->CTRL, DVP_CTRL_BSM_MASK, _BSM_))

/**
 * @brief  Config the data invert function.
 * @param _INV_ Specifies the data invert or not.
 *  This parameter can be one of the following values:
 *      @arg DVP_DATA_INVERT        Invert capture data
 *      @arg DVP_DATA_NOTINVERT     Capture data not invert
 * @retval None
 */
#define __DVP_SetDataInvert(_INV_)        (MODIFY_REG(DVP->CTRL, DVP_CTRL_DATINV_MASK, _INV_))

/**
 * @brief  Config the pixel clock polarity.
 * @param _POL_ Specifies the clock edge of pixel clock.
 *  This parameter can be one of the following values:
 *      @arg DVP_PIXEL_POLARITY_FALLING    Get data at falling edge
 *      @arg DVP_PIXEL_POLARITY_RISING     Get data at rising edge
 * @retval None
 */
#define __DVP_SetPclkPol(_POL_)        (MODIFY_REG(DVP->CTRL, DVP_CTRL_PCKPOL_MASK, _POL_))

/**
 * @brief  Config the VSYNC polarity.
 * @param _POL_ Specifies the active polarity of VSYNC pin.
 *  This parameter can be one of the following values:
 *      @arg DVP_VSYNC_POLARITY_HIGH    VSYNC active high
 *      @arg DVP_VSYNC_POLARITY_LOW     VSYNC active low
 * @retval None
 */
#define __DVP_SetVsyncPol(_POL_)        (MODIFY_REG(DVP->CTRL, DVP_CTRL_VSPOL_MASK, _POL_))

/**
 * @brief  Config the HSYNC polarity.
 * @param _POL_ Specifies the active polarity of HSYNC pin.
 *  This parameter can be one of the following values:
 *      @arg DVP_HSYNC_POLARITY_HIGH    VSYNC active high
 *      @arg DVP_HSYNC_POLARITY_LOW     VSYNC active low
 * @retval None
 */
#define __DVP_SetHsyncPol(_POL_)        (MODIFY_REG(DVP->CTRL, DVP_CTRL_HSPOL_MASK, _POL_))

/**
 * @brief  Config the capture mode.
 * @param _POL_ Specifies the new capture mode.
 *  This parameter can be one of the following values:
 *      @arg DVP_CAPTURE_MODE_SINGLE    Capture one frame
 *      @arg DVP_CAPTURE_MODE_CONTINUE  Capture many frames
 * @retval None
 */
#define __DVP_SetCaptureMode(_MODE_)    (MODIFY_REG(DVP->CTRL, DVP_CTRL_CM_MASK, _MODE_))

/**
 * @brief  Enable DVP interface.
 * @param  None
 * @retval None
 */
#define __DVP_StartCapture()                  (SET_BIT(DVP->CTRL, DVP_CAPTURE_ENABLE))

/**
 * @brief  Disable DVP interface.
 * @param  None
 * @retval None
 */
#define __DVP_StopCapture()                 (CLEAR_BIT(DVP->CTRL, DVP_CAPTURE_ENABLE))

/**
 * @brief  Disable DVP interface.
 * @param  None
 * @retval None
 */
#define __FIFOIsNotEmpty()              (READ_BIT(DVP->STS, DVP_STS_FNE))

/**
 * @brief  Checks whether the specified DVP flag is set.
 * @param _FLAG_    specifies the flag to check.
 *   This parameter can be any combination of the following values:
 *     @arg DVP_FLAG_HERR   Hsync error interrupt flag
 *     @arg DVP_FLAG_VERR   Vsync error interrupt flag
 *     @arg DVP_FLAG_FO     FIFO overflow intterrupt flag
 *     @arg DVP_FLAG_FW     FIFO watermark interrupt flag
 *     @arg DVP_FLAG_FF     FIFO full interrupt flag
 *     @arg DVP_FLAG_FE     FIFO empty interrupt flag
 *     @arg DVP_FLAG_LE     Line end interrupt flag
 *     @arg DVP_FLAG_LS     Line start interrupt flag
 *     @arg DVP_FLAG_FME    Frame end interrupt flag
 *     @arg DVP_FLAG_FMS    Frame start interrupt flag
 * @retval  true or false.
 */
#define __DVP_FlagIsSet(_FLAG_)         (((DVP->INTSTS) & (_FLAG_))==(_FLAG_))

/**
 * @brief  Checks whether the specified DVP flag is not set.
 * @param _FLAG_    specifies the flag to check.
 *   This parameter can be any combination of the following values:
 *     @arg DVP_FLAG_HERR   Hsync error interrupt flag
 *     @arg DVP_FLAG_VERR   Vsync error interrupt flag
 *     @arg DVP_FLAG_FO     FIFO overflow intterrupt flag
 *     @arg DVP_FLAG_FW     FIFO watermark interrupt flag
 *     @arg DVP_FLAG_FF     FIFO full interrupt flag
 *     @arg DVP_FLAG_FE     FIFO empty interrupt flag
 *     @arg DVP_FLAG_LE     Line end interrupt flag
 *     @arg DVP_FLAG_LS     Line start interrupt flag
 *     @arg DVP_FLAG_FME    Frame end interrupt flag
 *     @arg DVP_FLAG_FMS    Frame start interrupt flag
 * @retval  true or false.
 */
#define __DVP_FlagIsNotSet(_FLAG_)      (((DVP->INTSTS) & (_FLAG_))!=(_FLAG_))

/**
 * @brief  Clears the DVP flags.
 * @param _FLAG_    specifies the flag to clear.
 *   This parameter can be any combination of the following values:
 *     @arg DVP_CLEAR_FLAG_HERR   Hsync error interrupt flag clear
 *     @arg DVP_CLEAR_FLAG_VERR   Vsync error interrupt flag clear
 *     @arg DVP_CLEAR_FLAG_FO     FIFO overflow intterrupt flag clear
 *     @arg DVP_CLEAR_FLAG_FE     FIFO empty interrupt flag clear
 *     @arg DVP_CLEAR_FLAG_LE     Line end interrupt flag clear
 *     @arg DVP_CLEAR_FLAG_LS     Line start interrupt flag clear
 *     @arg DVP_CLEAR_FLAG_FME    Frame end interrupt flag clear
 *     @arg DVP_CLEAR_FLAG_FMS    Frame start interrupt flag clear
 * @retval  None.
 */
#define __DVP_ClrFlag(_FLAG_)           (DVP->INTSTS = (~(_FLAG_)) & DVP_CLEAR_FLAG_MASK)

/**
 * @brief  Enable DVP interrupts.
 * @param _INT_    specifies the interrupt to be enable.
 *   This parameter can be any combination of the following values:
 *     @arg DVP_INTEN_HERR   Hsync error interrupt enable
 *     @arg DVP_INTEN_VERR   Vsync error interrupt enable
 *     @arg DVP_INTEN_FO     FIFO overflow intterrupt enable
 *     @arg DVP_INTEN_FE     FIFO empty interrupt enable
 *     @arg DVP_INTEN_LE     Line end interrupt enable
 *     @arg DVP_INTEN_LS     Line start interrupt enable
 *     @arg DVP_INTEN_FME    Frame end interrupt enable
 *     @arg DVP_INTEN_FMS    Frame start interrupt enable
 * @retval  None.
 */
#define __DVP_EnableInt(_INT_)          (SET_BIT(DVP->INTEN, _INT_))

/**
 * @brief  Disable DVP interrupts.
 * @param _INT_    specifies the interrupt to be disable.
 *   This parameter can be any combination of the following values:
 *     @arg DVP_INTEN_HERR   Hsync error interrupt disable
 *     @arg DVP_INTEN_VERR   Vsync error interrupt disable
 *     @arg DVP_INTEN_FO     FIFO overflow intterrupt disable
 *     @arg DVP_INTEN_FE     FIFO empty interrupt disable
 *     @arg DVP_INTEN_LE     Line end interrupt disable
 *     @arg DVP_INTEN_LS     Line start interrupt disable
 *     @arg DVP_INTEN_FME    Frame end interrupt disable
 *     @arg DVP_INTEN_FMS    Frame start interrupt disable
 * @retval  None.
 */
#define __DVP_DisableInt(_INT_)         (CLEAR_BIT(DVP->INTEN, _INT_))

/**
 * @brief  Enable DVP DMA.
 * @param  None.
 * @retval None.
 */
#define __DVP_EnableDMA()               (SET_BIT(DVP->INTEN, DVP_INTEN_DMAEN))

/**
 * @brief  Enable DVP DMA.
 * @param  None.
 * @retval None.
 */
#define __DVP_DisableDMA()              (CLEAR_BIT(DVP->INTEN, DVP_INTEN_DMAEN))

/**
 * @brief  Checks whether the specified DVP interrupt has occurred or not.
 * @param _INT_     specifies the DVP interrupt source to check.
 *   This parameter can be one of the following values:
 *     @arg DVP_MINT_HERR   Hsync error interrupt
 *     @arg DVP_MINT_VERR   Vsync error interrupt
 *     @arg DVP_MINT_FO     FIFO overflow intterrupt
 *     @arg DVP_MINT_FW     FIFO watermark interrupt
 *     @arg DVP_MINT_FF     FIFO full interrupt
 *     @arg DVP_MINT_FE     FIFO empty interrupt
 *     @arg DVP_MINT_LE     Line end interrupt
 *     @arg DVP_MINT_LS     Line start interrupt
 *     @arg DVP_MINT_FME    Frame end interrupt
 *     @arg DVP_MINT_FMS    Frame start interrupt
 * @retval The state of _INT_ (SET or RESET).
 */
#define __DVP_GetIntMark(_INT_)         (((DVP->MINTSTS) & (_INT_))==(_INT_))

/**
 * @brief  Config the positon of first capture pixel .
 * @param _VST_     specifies the line positon.
 *   This parameter must be less than 2048.
 * @param _HST_     specifies the pixel positon.
 *   This parameter must be less than 2048.
 * @retval None.
 */
#define __DVP_SetStartSHIFT(_VST_,_HST_)  (DVP->WST=((_VST_)<<DVP_WST_VST_SHIFT)|(_HST_))

/**
 * @brief  Config the size of capture picture (frame) .
 * @param _VLINE_     specifies the total lines of a frame.
 *   This parameter must be less than 2048.
 * @param _HCNT_     specifies the pixels of a line.
 *   This parameter must be less than 2048.
 * @retval None.
 */
#define __DVP_SetPicSize(_VLINE_,_HCNT_)    (DVP->WSIZE=((_VLINE_)<<DVP_WSIZE_VLINE_SHIFT)|(_HCNT_))

/**
 * @brief  Read data from FIFO.
 * @param  None.
 * @retval Data in FIFO
 */
#define __DVP_ReadFIFO()                    (READ_REG(DVP->FIFO))


/**
 * @}
 */

/** @addtogroup DVP_Exported_Functions
 * @{
 */
void DVP_ResetReg(void);
void DVP_Init(DVP_InitType* DVP_InitStruct);
void DVP_DafaultInitParam(DVP_InitType* DVP_InitStruct);
uint32_t DVP_GetFifoCount(void);
void DVP_ResetFifo(void);
void DVP_ConfigDma( FunctionalState Cmd);

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */

#ifdef __cplusplus
 }
#endif

#endif
