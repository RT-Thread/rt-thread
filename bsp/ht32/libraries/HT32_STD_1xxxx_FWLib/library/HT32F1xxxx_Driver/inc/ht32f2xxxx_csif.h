/*********************************************************************************************************//**
 * @file    ht32f2xxxx_csif.h
 * @version $Rev:: 122          $
 * @date    $Date:: 2017-06-13 #$
 * @brief   The header file of the CSIF library.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F2XXXX_CSIF_H
#define __HT32F2XXXX_CSIF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @addtogroup CSIF
  * @{
  */

/* Exported types ------------------------------------------------------------------------------------------*/

/** @defgroup CSIF_Exported_Types CSIF exported types
  * @{
  */

typedef struct
{
  u32 CSIF_Format;
  u32 CSIF_VSYNCType;
  u32 CSIF_HSYNCType;
  u32 CSIF_SampleEdge;
  u32 CSIF_VSYNCPolarity;
  u32 CSIF_HSYNCPolarity;
  u32 CSIF_LineDelay;
  u32 CSIF_FrameDelay;
  u32 CSIF_ImageWidth;
  u32 CSIF_ImageHeight;
}CSIF_BasicInitTypeDef;


typedef struct
{
  u32 CSIF_Window;
  u32 CSIF_HorizontalStartPoint;
  u32 CSIF_VerticalStartPoint;
  u32 CSIF_WindowWidth;
  u32 CSIF_WindowHeight;
}CSIF_WindowInitTypeDef;


typedef struct
{
  u32 CSIF_SubSample;
  u32 CSIF_ColumnSkipMaskLength;
  u32 CSIF_RowSkipMaskLength;
  u32 CSIF_ColumnSkipMask;
  u32 CSIF_RowSkipMask;
}CSIF_SubSampleInitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup CSIF_Exported_Constants CSIF exported constants
  * @{
  */

#define CSIF_FORMAT_RAWRGB                          ((u32)0x00000000)
#define CSIF_FORMAT_YUV422                          ((u32)0x00000010)

#define IS_CSIF_FORMAT(FORMAT)                      ((FORMAT == CSIF_FORMAT_RAWRGB) || \
                                                     (FORMAT == CSIF_FORMAT_YUV422))


#define CSIF_VSYNCTYPE_PULSE                        ((u32)0x00000000)
#define CSIF_VSYNCTYPE_OVERLAP                      ((u32)0x00000002)

#define IS_CSIF_VSYNC_TYPE(TYPE)                    ((TYPE == CSIF_VSYNCTYPE_PULSE) || \
                                                     (TYPE == CSIF_VSYNCTYPE_OVERLAP))


#define CSIF_HSYNCTYPE_CONTINUOUS                   ((u32)0x00000000)
#define CSIF_HSYNCTYPE_DISCONTINUOUS                ((u32)0x00000004)

#define IS_CSIF_HSYNC_TYPE(TYPE)                    ((TYPE == CSIF_HSYNCTYPE_CONTINUOUS) || \
                                                     (TYPE == CSIF_HSYNCTYPE_DISCONTINUOUS))


#define CSIF_SAMPLEEDGE_FALLING                     ((u32)0x00000000)
#define CSIF_SAMPLEEDGE_RISING                      ((u32)0x00000008)

#define IS_CSIF_SAMPLE_EDGE(EDGE)                   ((EDGE == CSIF_SAMPLEEDGE_FALLING) || \
                                                     (EDGE == CSIF_SAMPLEEDGE_RISING))


#define CSIF_VSYNCPOLARITY_HIGH                     ((u32)0x00000000)
#define CSIF_VSYNCPOLARITY_LOW                      ((u32)0x00000040)

#define IS_CSIF_VSYNC_POLARITY(POLARITY)            ((POLARITY == CSIF_VSYNCPOLARITY_HIGH) || \
                                                     (POLARITY == CSIF_VSYNCPOLARITY_LOW))


#define CSIF_HSYNCPOLARITY_HIGH                     ((u32)0x00000000)
#define CSIF_HSYNCPOLARITY_LOW                      ((u32)0x00000080)

#define IS_CSIF_HSYNC_POLARITY(POLARITY)            ((POLARITY == CSIF_HSYNCPOLARITY_HIGH) || \
                                                     (POLARITY == CSIF_HSYNCPOLARITY_LOW))


#define CSIF_WINDOW_ENABLE                          ((u32)0x80000000)
#define CSIF_WINDOW_DISABLE                         ((u32)0x00000000)

#define IS_CSIF_WINDOW(WINDOW)                      ((WINDOW == CSIF_WINDOW_ENABLE) || \
                                                     (WINDOW == CSIF_WINDOW_DISABLE))


#define CSIF_SUBSAMPLE_ENABLE                       ((u32)0x80000000)
#define CSIF_SUBSAMPLE_DISABLE                      ((u32)0x00000000)

#define IS_CSIF_SUB_SAMPLE(SAMPLE)                  ((SAMPLE == CSIF_SUBSAMPLE_ENABLE) || \
                                                     (SAMPLE == CSIF_SUBSAMPLE_DISABLE))


#define CSIF_MASKLENGTH_1B                          ((u32)0x00000000)
#define CSIF_MASKLENGTH_2B                          ((u32)0x00000001)
#define CSIF_MASKLENGTH_3B                          ((u32)0x00000002)
#define CSIF_MASKLENGTH_4B                          ((u32)0x00000003)
#define CSIF_MASKLENGTH_5B                          ((u32)0x00000004)
#define CSIF_MASKLENGTH_6B                          ((u32)0x00000005)
#define CSIF_MASKLENGTH_7B                          ((u32)0x00000006)
#define CSIF_MASKLENGTH_8B                          ((u32)0x00000007)
#define CSIF_MASKLENGTH_9B                          ((u32)0x00000008)
#define CSIF_MASKLENGTH_10B                         ((u32)0x00000009)
#define CSIF_MASKLENGTH_11B                         ((u32)0x0000000A)
#define CSIF_MASKLENGTH_12B                         ((u32)0x0000000B)
#define CSIF_MASKLENGTH_13B                         ((u32)0x0000000C)
#define CSIF_MASKLENGTH_14B                         ((u32)0x0000000D)
#define CSIF_MASKLENGTH_15B                         ((u32)0x0000000E)
#define CSIF_MASKLENGTH_16B                         ((u32)0x0000000F)
#define CSIF_MASKLENGTH_17B                         ((u32)0x00000010)
#define CSIF_MASKLENGTH_18B                         ((u32)0x00000011)
#define CSIF_MASKLENGTH_19B                         ((u32)0x00000012)
#define CSIF_MASKLENGTH_20B                         ((u32)0x00000013)
#define CSIF_MASKLENGTH_21B                         ((u32)0x00000014)
#define CSIF_MASKLENGTH_22B                         ((u32)0x00000015)
#define CSIF_MASKLENGTH_23B                         ((u32)0x00000016)
#define CSIF_MASKLENGTH_24B                         ((u32)0x00000017)
#define CSIF_MASKLENGTH_25B                         ((u32)0x00000018)
#define CSIF_MASKLENGTH_26B                         ((u32)0x00000019)
#define CSIF_MASKLENGTH_27B                         ((u32)0x0000001A)
#define CSIF_MASKLENGTH_28B                         ((u32)0x0000001B)
#define CSIF_MASKLENGTH_29B                         ((u32)0x0000001C)
#define CSIF_MASKLENGTH_30B                         ((u32)0x0000001D)
#define CSIF_MASKLENGTH_31B                         ((u32)0x0000001E)
#define CSIF_MASKLENGTH_32B                         ((u32)0x0000001F)

#define IS_CSIF_MASK_LENGTH(LENGTH)                 (LENGTH <= 0x1F)


#define CSIF_FIFO_0                                 ((u8)0x20)
#define CSIF_FIFO_1                                 ((u8)0x24)
#define CSIF_FIFO_2                                 ((u8)0x28)
#define CSIF_FIFO_3                                 ((u8)0x2C)
#define CSIF_FIFO_4                                 ((u8)0x30)
#define CSIF_FIFO_5                                 ((u8)0x34)
#define CSIF_FIFO_6                                 ((u8)0x38)
#define CSIF_FIFO_7                                 ((u8)0x3C)

#define IS_CSIF_FIFO(FIFO)                          ((FIFO == CSIF_FIFO_0) || \
                                                     (FIFO == CSIF_FIFO_1) || \
                                                     (FIFO == CSIF_FIFO_2) || \
                                                     (FIFO == CSIF_FIFO_3) || \
                                                     (FIFO == CSIF_FIFO_4) || \
                                                     (FIFO == CSIF_FIFO_5) || \
                                                     (FIFO == CSIF_FIFO_6) || \
                                                     (FIFO == CSIF_FIFO_7))

#define CSIF_INT_SOFFLG                             ((u32)0x00000001)
#define CSIF_INT_EOFFLG                             ((u32)0x00000002)
#define CSIF_INT_CAPSTA                             ((u32)0x00000004)
#define CSIF_INT_CAPSTS                             ((u32)0x00000008)
#define CSIF_INT_BADFRAME                           ((u32)0x00000010)
#define CSIF_INT_FIFOOVR                            ((u32)0x00000100)
#define CSIF_INT_FIFOEMP                            ((u32)0x00000200)
#define CSIF_INT_FIFOFUL                            ((u32)0x00000400)
#define CSIF_INT_ALL                                ((u32)0x0000071F)

#define IS_CSIF_INT(INT)                            (((INT & 0xFFFFF8E0) == 0x0) && (INT != 0x0))



#define CSIF_FLAG_SOFFLG                            ((u32)0x00000001)
#define CSIF_FLAG_EOFFLG                            ((u32)0x00000002)
#define CSIF_FLAG_CAPSTA                            ((u32)0x00000004)
#define CSIF_FLAG_CAPSTS                            ((u32)0x00000008)
#define CSIF_FLAG_BADFRAME                          ((u32)0x00000010)
#define CSIF_FLAG_FIFOOVR                           ((u32)0x00000100)
#define CSIF_FLAG_FIFOEMP                           ((u32)0x00000200)
#define CSIF_FLAG_FIFOFUL                           ((u32)0x00000400)

#define IS_CSIF_FLAG(FLAG)                          ((FLAG == CSIF_FLAG_SOFFLG) || \
                                                     (FLAG == CSIF_FLAG_EOFFLG) || \
                                                     (FLAG == CSIF_FLAG_CAPSTA) || \
                                                     (FLAG == CSIF_FLAG_CAPSTS) || \
                                                     (FLAG == CSIF_FLAG_BADFRAME) || \
                                                     (FLAG == CSIF_FLAG_FIFOOVR) || \
                                                     (FLAG == CSIF_FLAG_FIFOEMP) || \
                                                     (FLAG == CSIF_FLAG_FIFOFUL))

#define IS_CSIF_CLEAR_FLAG(FLAG)                    ((FLAG == CSIF_FLAG_SOFFLG) || \
                                                     (FLAG == CSIF_FLAG_EOFFLG) || \
                                                     (FLAG == CSIF_FLAG_CAPSTA) || \
                                                     (FLAG == CSIF_FLAG_CAPSTS) || \
                                                     (FLAG == CSIF_FLAG_BADFRAME))


#define IS_CSIF_LINE_DELAY(DELAY)                   (DELAY <= 0xFF)

#define IS_CSIF_FRAME_DELAY(DELAY)                  (DELAY <= 0xFF)

#define IS_CSIF_IMAGE_WIDTH(WIDTH)                  (WIDTH <= 0x800)

#define IS_CSIF_IMAGE_HEIGHT(HEIGHT)                (HEIGHT <= 0x800)

#define IS_CSIF_HORSTART_POINT(POINT)               (POINT <= 0x7FF)

#define IS_CSIF_VERSTART_POINT(POINT)               (POINT <= 0x7FF)

#define IS_CSIF_WINDOW_WIDTH(WIDTH)                 (WIDTH <= 0x800)

#define IS_CSIF_WINDOW_HEIGHT(HEIGHT)               (HEIGHT <= 0x800)

#define IS_CSIF_PRESCALER(PRESCALER)                ((PRESCALER%2 == 0) && (PRESCALER != 0))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup CSIF_Exported_Functions CSIF exported functions
  * @{
  */
void CSIF_DeInit(void);
void CSIF_BasicInit(CSIF_BasicInitTypeDef* CSIF_BasicInitStruct);
void CSIF_BasicStructInit(CSIF_BasicInitTypeDef* CSIF_BasicInitStruct);
void CSIF_WindowInit(CSIF_WindowInitTypeDef* CSIF_WindowInitStruct);
void CSIF_WindowStructInit(CSIF_WindowInitTypeDef* CSIF_WindowInitStruct);
void CSIF_SubSampleInit(CSIF_SubSampleInitTypeDef* CSIF_SubSampleInitStruct);
void CSIF_SunSampleStructInit(CSIF_SubSampleInitTypeDef* CSIF_SubSampleInitStruct);
void CSIF_Cmd(ControlStatus NewState);
void CSIF_IntConfig(u32 CSIF_Int, ControlStatus NewState);
FlagStatus CSIF_GetFlagStatus(u32 CSIF_Flag);
void CSIF_ClearFlag(u32 CSIF_Flag);
u32 CSIF_ReceiveData(u8 CSIF_FIFO);
void CSIF_MasterClockCmd(ControlStatus NewState);
void CSIF_SetMasterClockPrescaler(u8 CSIF_Prescaler);
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
