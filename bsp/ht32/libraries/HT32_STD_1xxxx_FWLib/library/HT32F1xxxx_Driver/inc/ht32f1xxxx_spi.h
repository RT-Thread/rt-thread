/*********************************************************************************************************//**
 * @file    ht32f1xxxx_spi.h
 * @version $Rev:: 2797         $
 * @date    $Date:: 2022-11-28 #$
 * @brief   The header file of the SPI library.
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
#ifndef __HT32F1XXXX_SPI_H
#define __HT32F1XXXX_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @addtogroup SPI
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup SPI_Exported_Types SPI exported types
  * @{
  */
typedef u16 SPI_DataTypeDef;
typedef u16 SPI_TimeoutTypeDef;

typedef struct
{
  u32 SPI_Mode;
  u32 SPI_FIFO;
  u32 SPI_DataLength;
  u32 SPI_SELMode;
  u32 SPI_SELPolarity;
  u32 SPI_CPOL;
  u32 SPI_CPHA;
  u32 SPI_FirstBit;
  u32 SPI_RxFIFOTriggerLevel;
  u32 SPI_TxFIFOTriggerLevel;
  u32 SPI_ClockPrescaler;
} SPI_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup SPI_Exported_Constants SPI exported constants
  * @{
  */
#define SPI_FIFO_ENABLE                             ((u32)0x00000400)
#define SPI_FIFO_DISABLE                            ((u32)0x00000000)

#define IS_SPI_FIFO_SET(FIFO)                       ((FIFO == SPI_FIFO_ENABLE) || \
                                                     (FIFO == SPI_FIFO_DISABLE))

#define SPI_DATALENGTH_1                            ((u32)0x00000001)
#define SPI_DATALENGTH_2                            ((u32)0x00000002)
#define SPI_DATALENGTH_3                            ((u32)0x00000003)
#define SPI_DATALENGTH_4                            ((u32)0x00000004)
#define SPI_DATALENGTH_5                            ((u32)0x00000005)
#define SPI_DATALENGTH_6                            ((u32)0x00000006)
#define SPI_DATALENGTH_7                            ((u32)0x00000007)
#define SPI_DATALENGTH_8                            ((u32)0x00000008)
#define SPI_DATALENGTH_9                            ((u32)0x00000009)
#define SPI_DATALENGTH_10                           ((u32)0x0000000A)
#define SPI_DATALENGTH_11                           ((u32)0x0000000B)
#define SPI_DATALENGTH_12                           ((u32)0x0000000C)
#define SPI_DATALENGTH_13                           ((u32)0x0000000D)
#define SPI_DATALENGTH_14                           ((u32)0x0000000E)
#define SPI_DATALENGTH_15                           ((u32)0x0000000F)
#define SPI_DATALENGTH_16                           ((u32)0x00000000)

#define IS_SPI_DATALENGTH(DATALENGTH)               ((DATALENGTH <= 0xF))


#define SPI_MASTER                                  ((u32)0x00004000)
#define SPI_SLAVE                                   ((u32)0x00000000)

#define IS_SPI_MODE(MODE)                           ((MODE == SPI_MASTER) || \
                                                     (MODE == SPI_SLAVE))


#define SPI_SEL_HARDWARE                            ((u32)0x00002000)
#define SPI_SEL_SOFTWARE                            ((u32)0x00000000)

#define IS_SPI_SEL_MODE(SELMODE)                    ((SELMODE == SPI_SEL_HARDWARE) || \
                                                     (SELMODE == SPI_SEL_SOFTWARE))


#define SPI_SEL_ACTIVE                              ((u32)0x00000010)
#define SPI_SEL_INACTIVE                            ((u32)0xFFFFFFEF)

#define IS_SPI_SOFTWARE_SEL(SEL)                    ((SEL == SPI_SEL_ACTIVE) || \
                                                     (SEL == SPI_SEL_INACTIVE))


#define SPI_SELPOLARITY_HIGH                        ((u32)0x00000800)
#define SPI_SELPOLARITY_LOW                         ((u32)0x00000000)

#define IS_SPI_SEL_POLARITY(POLARITY)               ((POLARITY == SPI_SELPOLARITY_HIGH) || \
                                                     (POLARITY == SPI_SELPOLARITY_LOW))


#define SPI_CPOL_HIGH                               ((u32)0x00000400)
#define SPI_CPOL_LOW                                ((u32)0x00000000)

#define IS_SPI_CPOL(CPOL)                           ((CPOL == SPI_CPOL_HIGH) || \
                                                     (CPOL == SPI_CPOL_LOW))


#define SPI_CPHA_FIRST                              ((u32)0x00000000)
#define SPI_CPHA_SECOND                             ((u32)0x00000001)

#define IS_SPI_CPHA(CPHA)                           ((CPHA == SPI_CPHA_FIRST) || \
                                                     (CPHA == SPI_CPHA_SECOND))


#define SPI_FIRSTBIT_LSB                            ((u32)0x00001000)
#define SPI_FIRSTBIT_MSB                            ((u32)0x00000000)

#define IS_SPI_FIRST_BIT(BIT)                       ((BIT == SPI_FIRSTBIT_LSB) || \
                                                     (BIT == SPI_FIRSTBIT_MSB))


#define SPI_FLAG_TXBE                               ((u32)0x00000001)
#define SPI_FLAG_TXE                                ((u32)0x00000002)
#define SPI_FLAG_RXBNE                              ((u32)0x00000004)
#define SPI_FLAG_WC                                 ((u32)0x00000008)
#define SPI_FLAG_RO                                 ((u32)0x00000010)
#define SPI_FLAG_MF                                 ((u32)0x00000020)
#define SPI_FLAG_SA                                 ((u32)0x00000040)
#define SPI_FLAG_TOUT                               ((u32)0x00000080)
#define SPI_FLAG_BUSY                               ((u32)0x00000100)

#define IS_SPI_FLAG(FLAG)                           ((FLAG ==  SPI_FLAG_TXBE) || \
                                                     (FLAG ==  SPI_FLAG_TXE) || \
                                                     (FLAG ==  SPI_FLAG_RXBNE) || \
                                                     (FLAG ==  SPI_FLAG_WC) || \
                                                     (FLAG ==  SPI_FLAG_RO) || \
                                                     (FLAG ==  SPI_FLAG_MF) || \
                                                     (FLAG ==  SPI_FLAG_SA) || \
                                                     (FLAG ==  SPI_FLAG_TOUT) || \
                                                     (FLAG ==  SPI_FLAG_BUSY))

#define IS_SPI_FLAG_CLEAR(CLEAR)                    ((CLEAR ==  SPI_FLAG_WC) || \
                                                     (CLEAR ==  SPI_FLAG_RO) || \
                                                     (CLEAR ==  SPI_FLAG_MF) || \
                                                     (CLEAR ==  SPI_FLAG_SA) || \
                                                     (CLEAR ==  SPI_FLAG_TOUT))


#define SPI_INT_TXBE                                ((u32)0x00000001)
#define SPI_INT_TXE                                 ((u32)0x00000002)
#define SPI_INT_RXBNE                               ((u32)0x00000004)
#define SPI_INT_WC                                  ((u32)0x00000008)
#define SPI_INT_RO                                  ((u32)0x00000010)
#define SPI_INT_MF                                  ((u32)0x00000020)
#define SPI_INT_SA                                  ((u32)0x00000040)
#define SPI_INT_TOUT                                ((u32)0x00000080)
#define SPI_INT_ALL                                 ((u32)0x000000FF)

#define IS_SPI_INT(SPI_INT)                         (((SPI_INT & 0xFFFFFF00) == 0x0) && (SPI_INT != 0x0))


#define SPI_FIFO_TX                                 ((u32)0x00000100)
#define SPI_FIFO_RX                                 ((u32)0x00000200)

#define IS_SPI_FIFO_DIRECTION(DIRECTION)            (((DIRECTION & 0xFFFFFCFF) == 0) && (DIRECTION != 0))


#define SPI_PDMAREQ_TX                              ((u32)0x00000002)
#define SPI_PDMAREQ_RX                              ((u32)0x00000004)

#define IS_SPI_PDMA_REQ(REQ)                        (((REQ & 0xFFFFFFF9) == 0x0) && (REQ != 0x0))


#define IS_SPI(SPI)                                 ((SPI == HT_SPI0) || (SPI == HT_SPI1))

#define IS_SPI_DATA(DATA)                           (DATA <= 0xffff)

#define IS_SPI_FIFO_LEVEL(LEVEL)                    (LEVEL <= 8)

#define IS_SPI_CLOCK_PRESCALER(PRESCALER)           (PRESCALER >= 2)

#define SPI_GUADTIME_1_SCK                          ((u16)0x0000)
#define SPI_GUADTIME_2_SCK                          ((u16)0x0001)
#define SPI_GUADTIME_3_SCK                          ((u16)0x0002)
#define SPI_GUADTIME_4_SCK                          ((u16)0x0003)
#define SPI_GUADTIME_5_SCK                          ((u16)0x0004)
#define SPI_GUADTIME_6_SCK                          ((u16)0x0005)
#define SPI_GUADTIME_7_SCK                          ((u16)0x0006)
#define SPI_GUADTIME_8_SCK                          ((u16)0x0007)
#define SPI_GUADTIME_9_SCK                          ((u16)0x0008)
#define SPI_GUADTIME_10_SCK                         ((u16)0x0009)
#define SPI_GUADTIME_11_SCK                         ((u16)0x000A)
#define SPI_GUADTIME_12_SCK                         ((u16)0x000B)
#define SPI_GUADTIME_13_SCK                         ((u16)0x000C)
#define SPI_GUADTIME_14_SCK                         ((u16)0x000D)
#define SPI_GUADTIME_15_SCK                         ((u16)0x000E)
#define SPI_GUADTIME_16_SCK                         ((u16)0x000F)

#define IS_SPI_GUADTIME(GUADTIMEPERIOD)             ((GUADTIMEPERIOD <= 0x000F))


#define SPI_SELHOLDTIME_HALF_SCK                    ((u16)0x0000)
#define SPI_SELHOLDTIME_1_SCK                       ((u16)0x0001)
#define SPI_SELHOLDTIME_1_HALF_SCK                  ((u16)0x0002)
#define SPI_SELHOLDTIME_2_SCK                       ((u16)0x0003)
#define SPI_SELHOLDTIME_2_HALF_SCK                  ((u16)0x0004)
#define SPI_SELHOLDTIME_3_SCK                       ((u16)0x0005)
#define SPI_SELHOLDTIME_3_HALF_SCK                  ((u16)0x0006)
#define SPI_SELHOLDTIME_4_SCK                       ((u16)0x0007)
#define SPI_SELHOLDTIME_4_HALF_SCK                  ((u16)0x0008)
#define SPI_SELHOLDTIME_5_SCK                       ((u16)0x0009)
#define SPI_SELHOLDTIME_5_HALF_SCK                  ((u16)0x000A)
#define SPI_SELHOLDTIME_6_SCK                       ((u16)0x000B)
#define SPI_SELHOLDTIME_6_HALF_SCK                  ((u16)0x000C)
#define SPI_SELHOLDTIME_7_SCK                       ((u16)0x000D)
#define SPI_SELHOLDTIME_7_HALF_SCK                  ((u16)0x000E)
#define SPI_SELHOLDTIME_8_SCK                       ((u16)0x000F)

#define IS_SPI_SELHOLDTIME(SELHOLDTIME)             ((SELHOLDTIME <= 0x000F))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup SPI_Exported_Functions SPI exported functions
  * @{
  */
void SPI_DeInit(HT_SPI_TypeDef* SPIx);
void SPI_Init(HT_SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void SPI_Cmd(HT_SPI_TypeDef* SPIx, ControlStatus NewState);
void SPI_SELOutputCmd(HT_SPI_TypeDef* SPIx, ControlStatus NewState);
void SPI_FIFOCmd(HT_SPI_TypeDef* SPIx, ControlStatus NewState);
void SPI_SetDataLength(HT_SPI_TypeDef* SPIx, u16 SPI_DataLength);
void SPI_SELModeConfig(HT_SPI_TypeDef* SPIx, u32 SPI_SELMode);
void SPI_SoftwareSELCmd(HT_SPI_TypeDef* SPIx, u32 SPI_SoftwareSEL);
void SPI_SendData(HT_SPI_TypeDef* SPIx, SPI_DataTypeDef SPI_Data);
SPI_DataTypeDef SPI_ReceiveData(HT_SPI_TypeDef* SPIx);
void SPI_SetTimeOutValue(HT_SPI_TypeDef* SPIx, SPI_TimeoutTypeDef SPI_Timeout);
void SPI_IntConfig(HT_SPI_TypeDef* SPIx, u32 SPI_Int, ControlStatus NewState);
FlagStatus SPI_GetFlagStatus(HT_SPI_TypeDef* SPIx, u32 SPI_Flag);
u8 SPI_GetFIFOStatus(HT_SPI_TypeDef* SPIx, u32 SPI_FIFODirection);
void SPI_ClearFlag(HT_SPI_TypeDef* SPIx, u32 SPI_FlagClear);
void SPI_FIFOTriggerLevelConfig(HT_SPI_TypeDef* SPIx, u32 SPI_FIFODirection, u8 SPI_FIFOLevel);
void SPI_PDMACmd(HT_SPI_TypeDef* SPIx, u32 SPI_PDMAREQ, ControlStatus NewState);
void SPI_DUALCmd(HT_SPI_TypeDef* SPIx, ControlStatus NewState);
void SPI_GUARDTCmd(HT_SPI_TypeDef* SPIx, ControlStatus NewState);
void SPI_GUARDTConfig(HT_SPI_TypeDef* SPIx, u32 Guard_Time);
void SPI_SELHTConfig(HT_SPI_TypeDef* SPIx, u32 CS_Hold_Time);
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
