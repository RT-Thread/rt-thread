/**
  ******************************************************************************
  * @file    bl808_mjdec.h
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
#ifndef __BL808_MJDEC_H__
#define __BL808_MJDEC_H__

#include "mjdec_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  MJDEC
 *  @{
 */

/** @defgroup  MJDEC_Public_Types
 *  @{
 */

/**
 *  @brief MJDEC YUV format definition
 */
typedef enum {
    MJDEC_YUV420,        /*!< MJDEC YUV420 planar mode */
    MJDEC_YUV400,        /*!< MJDEC YUV400 grey scale mode */
    MJDEC_YUV422_PLANAR, /*!< MJDEC YUV422 planar mode */
} MJDEC_YUV_Mode_Type;

/**
 *  @brief MJDEC burst type definition
 */
typedef enum {
    MJDEC_BURST_SINGLE, /*!< MJDEC burst single */
    MJDEC_BURST_INCR4,  /*!< MJDEC burst incr4 */
    MJDEC_BURST_INCR8,  /*!< MJDEC burst incr8 */
    MJDEC_BURST_INCR16, /*!< MJDEC burst incr16 */
} MJDEC_Burst_Type;

/**
 *  @brief MJDEC interrupt type definition
 */
typedef enum {
    MJDEC_INT_NORMAL,    /*!< MJDEC normal write interrupt */
    MJDEC_INT_BACK_IDLE, /*!< MJDEC back idle interrupt */
    MJDEC_INT_ALL,       /*!< MJDEC all interrupt type */
} MJDEC_INT_Type;

/**
 *  @brief MJDEC configuration strcut definition
 */
typedef struct {
    MJDEC_Burst_Type burstRead;     /*!< MJDEC burst read type */
    MJDEC_Burst_Type burstWrite;    /*!< MJDEC burst write type */
    MJDEC_YUV_Mode_Type yuv;        /*!< MJDEC control YUV mode */
    uint8_t intCnt;                 /*!< Set frame threshold to issue interrupt */
    uint32_t bufferFrameYY;         /*!< YUV frame buffer address of YY frame */
    uint32_t bufferFrameUV;         /*!< YUV frame buffer address of UV frame */
    uint16_t resolutionX;           /*!< YUV frame RESOLUTION X */
    uint16_t resolutionY;           /*!< YUV frame RESOLUTION Y */
    uint16_t headByte;              /*!< Skip JPEG stream header byte */
    BL_Fun_Type headSkip;           /*!< Skip JPEG stream header */
    BL_Fun_Type evenOrderEnable;    /*!< Enable:U is even byte of UV frame and V is odd byte of UV frame */
    BL_Fun_Type dmyBlock;           /*!< MJPEG last half block with dummy data 8'h80 */
    BL_Fun_Type dmyVertical;        /*!< MJPEG last half vertical block drop */
    BL_Fun_Type dmyHorizational;    /*!< MJPEG last half horizational block drop */
    BL_Fun_Type swapMode;           /*!< MJDEC YUV Memory swap mode */
    uint8_t picQuality;             /*!< Quality must be in 1-75 or 100 */
} MJDEC_CFG_Type;

/**
 *  @brief MJDEC frame information strcut definition
 */
typedef struct
{
    uint8_t validFrames;    /*!< Valid frames */
    uint32_t curFrameAddr;  /*!< Current frame address */
} MJDEC_Frame_Info;

/*@} end of group MJDEC_Public_Types */

/** @defgroup  MJDEC_Public_Constants
 *  @{
 */

/** @defgroup  MJDEC_YUV_MODE_TYPE
 *  @{
 */
#define IS_MJDEC_YUV_MODE_TYPE(type) (((type) == MJDEC_YUV420) || \
                                      ((type) == MJDEC_YUV400) || \
                                      ((type) == MJDEC_YUV422_PLANAR))

/** @defgroup  MJDEC_BURST_TYPE
 *  @{
 */
#define IS_MJDEC_BURST_TYPE(type) (((type) == MJDEC_BURST_SINGLE) || \
                                   ((type) == MJDEC_BURST_INCR4) ||  \
                                   ((type) == MJDEC_BURST_INCR8) ||  \
                                   ((type) == MJDEC_BURST_INCR16))

/** @defgroup  MJDEC_INT_TYPE
 *  @{
 */
#define IS_MJDEC_INT_TYPE(type) (((type) == MJDEC_INT_NORMAL) ||    \
                                 ((type) == MJDEC_INT_BACK_IDLE) || \
                                 ((type) == MJDEC_INT_ALL))

/*@} end of group MJDEC_Public_Constants */

/** @defgroup  MJDEC_Public_Macros
 *  @{
 */
#define MJDEC_BASE MJPEG_DEC_BASE
/*@} end of group MJDEC_Public_Macros */

/** @defgroup  MJDEC_Public_Functions
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
void MJDEC_IRQHandler(void);
#endif
void MJDEC_Init(MJDEC_CFG_Type *cfg);
void MJDEC_Deinit(void);
void MJDEC_Enable(void);
void MJDEC_Disable(void);
void MJDEC_Get_Frame_Info(MJDEC_Frame_Info *info);
uint8_t MJDEC_Get_Frame_Count(void);
BL_Err_Type MJDEC_Push_Frame(uint32_t bufferMjpeg);
void MJDEC_Pop_Frame(void);
void MJDEC_Set_Frame_Threshold(uint8_t count);
void MJDEC_Set_Q_Value(uint8_t q);
void MJDEC_IntMask(MJDEC_INT_Type intType, BL_Mask_Type intMask);
void MJDEC_IntClr(MJDEC_INT_Type intType);
void MJDEC_Int_Callback_Install(MJDEC_INT_Type intType, intCallback_Type *cbFun);

/*@} end of group MJDEC_Public_Functions */

/*@} end of group MJDEC */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_MJDEC_H__ */
