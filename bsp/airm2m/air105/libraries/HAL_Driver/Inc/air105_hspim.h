/*
 * Copyright (c) 2022 OpenLuat & AirM2M
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */



#ifndef __AIR105_HSPIM_H
#define __AIR105_HSPIM_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "air105.h"

typedef struct
{
    uint8_t HSPIM_Enable;
    uint8_t HSPIM_Mode;
    uint8_t HSPIM_FirstBit;
    uint8_t HSPIM_CPOL;
    uint8_t HSPIM_CPHA;
    uint8_t HSPIM_DivideEnable;
    uint8_t HSPIM_BaudRatePrescaler;
    uint8_t HSPIM_ReceiveDataLength;
    uint8_t HSPIM_RXFIFOFullThreshold;
    uint8_t HSPIM_TXFIFOEmptyThreshold;
}HSPIM_InitTypeDef;

typedef struct
{
    uint8_t HSPIM_DMAReceiveEnable;
    uint8_t HSPIM_DMATransmitEnable;
    uint8_t HSPIM_DMAReceiveLevel;
    uint8_t HSPIM_DMATransmitLevel;
}HSPIM_DMAInitTypeDef;


/** @defgroup HSPIM_Mode
  * @{
  */

#define HSPIM_MODE_STANDARD                                         (0x01)
#define HSPIM_MODE_DUAL_RECEIVE                                     (0x02)
#define HSPIM_MODE_DUAL_TRANSMIT                                    (0x03)
#define HSPIM_MODE_QUAD_RECEIVE                                     (0x04)
#define HSPIM_MODE_QUAD_TRANSMIT                                    (0x05)
#define IS_HSPIM_MODE(MODE)                                         (((MODE) == HSPIM_MODE_STANDARD)            || \
                                                                    ((MODE) == HSPIM_MODE_DUAL_RECEIVE)         || \
                                                                    ((MODE) == HSPIM_MODE_DUAL_TRANSMIT)        || \
                                                                    ((MODE) == HSPIM_MODE_QUAD_RECEIVE)         || \
                                                                    ((MODE) == HSPIM_MODE_QUAD_TRANSMIT))
/**
  * @}
  */

/** @defgroup HSPIM_Clock_Polarity
  * @{
  */

#define HSPIM_CPOL_LOW                                              (0x00)
#define HSPIM_CPOL_HIGH                                             (0x01)
#define IS_HSPIM_CPOL(CPOL)                                         (((CPOL) == HSPIM_CPOL_LOW)|| \
                                                                    ((CPOL) == HSPIM_CPOL_HIGH))
/**
  * @}
  */


/** @defgroup HSPIM_Clock_Phase
  * @{
  */

#define HSPIM_CPHA_1EDGE                                            (0x00)
#define HSPIM_CPHA_2EDGE                                            (0x01)
#define IS_HSPIM_CPHA(CPHA)                                         (((CPHA) == HSPIM_CPHA_1EDGE) || \
                                                                    (CPHA) == HSPIM_CPHA_2EDGE)
/**
  * @}
  */

/** @defgroup HSPIM_First_Bit
  * @{
  */

#define HSPIM_FIRST_BIT_MSB                                         (0x00)
#define HSPIM_FIRST_BIT_LSB                                         (0x01)
#define IS_HSPIM_FIRST_BIT(BIT)                                     (((BIT) == HSPIM_FIRST_BIT_MSB) || \
                                                                    ((BIT) == HSPIM_FIRST_BIT_LSB))
/**
  * @}
  */

/** @defgroup HSPIM_BaudRate_Prescaler
  * @{
  */
#define HSPIM_BAUDRATE_PRESCALER_2                                  (0x01)
#define HSPIM_BAUDRATE_PRESCALER_4                                  (0x02)
#define HSPIM_BAUDRATE_PRESCALER_8                                  (0x04)
#define HSPIM_BAUDRATE_PRESCALER_16                                 (0x08)
#define HSPIM_BAUDRATE_PRESCALER_32                                 (0x10)
#define IS_HSPIM_BAUDRATE_PRESCALER(PRESCALER)                      (((PRESCALER) == HSPIM_BAUDRATE_PRESCALER_2) || \
                                                                    ((PRESCALER) == HSPIM_BAUDRATE_PRESCALER_4) || \
                                                                    ((PRESCALER) == HSPIM_BAUDRATE_PRESCALER_8) || \
                                                                    ((PRESCALER) == HSPIM_BAUDRATE_PRESCALER_16) || \
                                                                    ((PRESCALER) == HSPIM_BAUDRATE_PRESCALER_32))
/**
  * @}
  */

/** @defgroup HSPIM_Receive_Data_Length
  * @{
  */
#define HSPIM_RECEIVE_DATA_LENGTH_1_BYTE                            (0x00)
#define HSPIM_RECEIVE_DATA_LENGTH_2_BYTE                            (0x01)
#define HSPIM_RECEIVE_DATA_LENGTH_3_BYTE                            (0x02)
#define HSPIM_RECEIVE_DATA_LENGTH_4_BYTE                            (0x03)
#define HSPIM_RECEIVE_DATA_LENGTH_5_BYTE                            (0x04)
#define HSPIM_RECEIVE_DATA_LENGTH_6_BYTE                            (0x05)
#define HSPIM_RECEIVE_DATA_LENGTH_7_BYTE                            (0x06)
#define HSPIM_RECEIVE_DATA_LENGTH_8_BYTE                            (0x07)
#define HSPIM_RECEIVE_DATA_LENGTH_9_BYTE                            (0x08)
#define HSPIM_RECEIVE_DATA_LENGTH_10_BYTE                           (0x09
#define HSPIM_RECEIVE_DATA_LENGTH_11_BYTE                           (0x0A)
#define HSPIM_RECEIVE_DATA_LENGTH_12_BYTE                           (0x0B)
#define HSPIM_RECEIVE_DATA_LENGTH_13_BYTE                           (0x0C)
#define HSPIM_RECEIVE_DATA_LENGTH_14_BYTE                           (0x0D)
#define HSPIM_RECEIVE_DATA_LENGTH_15_BYTE                           (0x0E)
#define HSPIM_RECEIVE_DATA_LENGTH_16_BYTE                           (0x0F)
#define HSPIM_RECEIVE_DATA_LENGTH_32_BYTE                           (0x1F)

/**
  * @}
  */

/** @defgroup HSPIM_TXFIFOEmptyThreshold
  * @{
  */
#define HSPIM_TX_FIFO_EMPTY_THRESHOLD_1                             ((uint32_t)0x0001)
#define HSPIM_TX_FIFO_EMPTY_THRESHOLD_2                             ((uint32_t)0x0002)
#define HSPIM_TX_FIFO_EMPTY_THRESHOLD_3                             ((uint32_t)0x0003)
#define HSPIM_TX_FIFO_EMPTY_THRESHOLD_4                             ((uint32_t)0x0004)
#define HSPIM_TX_FIFO_EMPTY_THRESHOLD_5                             ((uint32_t)0x0005)
#define HSPIM_TX_FIFO_EMPTY_THRESHOLD_6                             ((uint32_t)0x0006)
#define HSPIM_TX_FIFO_EMPTY_THRESHOLD_7                             ((uint32_t)0x0007)
#define HSPIM_TX_FIFO_EMPTY_THRESHOLD_8                             ((uint32_t)0x0008)
#define HSPIM_TX_FIFO_EMPTY_THRESHOLD_9                             ((uint32_t)0x0009)
#define HSPIM_TX_FIFO_EMPTY_THRESHOLD_10                            ((uint32_t)0x000A)
#define HSPIM_TX_FIFO_EMPTY_THRESHOLD_11                            ((uint32_t)0x000B)
#define HSPIM_TX_FIFO_EMPTY_THRESHOLD_12                            ((uint32_t)0x000C)
#define HSPIM_TX_FIFO_EMPTY_THRESHOLD_13                            ((uint32_t)0x000D)
#define HSPIM_TX_FIFO_EMPTY_THRESHOLD_14                            ((uint32_t)0x000E)
#define HSPIM_TX_FIFO_EMPTY_THRESHOLD_15                            ((uint32_t)0x000F)
#define HSPIM_TX_FIFO_EMPTY_THRESHOLD_31                            ((uint32_t)0x001F)
#define HSPIM_TX_FIFO_EMPTY_THRESHOLD_63                            ((uint32_t)0x003F)

#define IS_HSPIM_TX_FIFO_EMPTY_THRESHOLD(THRESHOLD)                 ((((int32_t)(THRESHOLD)) >= HSPIM_TX_FIFO_EMPTY_THRESHOLD_1) && \
                                                                    (((uint32_t)(THRESHOLD)) <= HSPIM_TX_FIFO_EMPTY_THRESHOLD_63))
/**
  * @}
  */


/** @defgroup HSPIM_RXFIFOFullThreshold
  * @{
  */
#define HSPIM_RX_FIFO_FULL_THRESHOLD_1                              ((uint32_t)0x0001)
#define HSPIM_RX_FIFO_FULL_THRESHOLD_2                              ((uint32_t)0x0002)
#define HSPIM_RX_FIFO_FULL_THRESHOLD_3                              ((uint32_t)0x0003)
#define HSPIM_RX_FIFO_FULL_THRESHOLD_4                              ((uint32_t)0x0004)
#define HSPIM_RX_FIFO_FULL_THRESHOLD_5                              ((uint32_t)0x0005)
#define HSPIM_RX_FIFO_FULL_THRESHOLD_6                              ((uint32_t)0x0006)
#define HSPIM_RX_FIFO_FULL_THRESHOLD_7                              ((uint32_t)0x0007)
#define HSPIM_RX_FIFO_FULL_THRESHOLD_8                              ((uint32_t)0x0008)
#define HSPIM_RX_FIFO_FULL_THRESHOLD_9                              ((uint32_t)0x0009)
#define HSPIM_RX_FIFO_FULL_THRESHOLD_10                             ((uint32_t)0x000A)
#define HSPIM_RX_FIFO_FULL_THRESHOLD_11                             ((uint32_t)0x000B)
#define HSPIM_RX_FIFO_FULL_THRESHOLD_12                             ((uint32_t)0x000C)
#define HSPIM_RX_FIFO_FULL_THRESHOLD_13                             ((uint32_t)0x000D)
#define HSPIM_RX_FIFO_FULL_THRESHOLD_14                             ((uint32_t)0x000E)
#define HSPIM_RX_FIFO_FULL_THRESHOLD_15                             ((uint32_t)0x000F)
#define HSPIM_RX_FIFO_FULL_THRESHOLD_16                             ((uint32_t)0x0010)
#define HSPIM_RX_FIFO_FULL_THRESHOLD_32                             ((uint32_t)0x0020)
#define HSPIM_RX_FIFO_FULL_THRESHOLD_63                             ((uint32_t)0x003F)


#define IS_HSPIM_RX_FIFO_FULL_THRESHOLD(THRESHOLD)                  ((((uint32_t)(THRESHOLD)) >= HSPIM_RX_FIFO_FULL_THRESHOLD_1) && \
                                                                    (((uint32_t)(THRESHOLD)) <= HSPIM_RX_FIFO_FULL_THRESHOLD_63))

/**
  * @}
  */

/** @defgroup SPI_DMAReceiveLevel
  * @{
  */
#define HSPIM_DMA_RECEIVE_LEVEL_1                                   ((uint32_t)0x0001)
#define HSPIM_DMA_RECEIVE_LEVEL_2                                   ((uint32_t)0x0002)
#define HSPIM_DMA_RECEIVE_LEVEL_3                                   ((uint32_t)0x0003)
#define HSPIM_DMA_RECEIVE_LEVEL_4                                   ((uint32_t)0x0004)
#define HSPIM_DMA_RECEIVE_LEVEL_5                                   ((uint32_t)0x0005)
#define HSPIM_DMA_RECEIVE_LEVEL_6                                   ((uint32_t)0x0006)
#define HSPIM_DMA_RECEIVE_LEVEL_7                                   ((uint32_t)0x0007)
#define HSPIM_DMA_RECEIVE_LEVEL_8                                   ((uint32_t)0x0008)
#define HSPIM_DMA_RECEIVE_LEVEL_9                                   ((uint32_t)0x0009)
#define HSPIM_DMA_RECEIVE_LEVEL_10                                  ((uint32_t)0x000A)
#define HSPIM_DMA_RECEIVE_LEVEL_11                                  ((uint32_t)0x000B)
#define HSPIM_DMA_RECEIVE_LEVEL_12                                  ((uint32_t)0x000C)
#define HSPIM_DMA_RECEIVE_LEVEL_13                                  ((uint32_t)0x000D)
#define HSPIM_DMA_RECEIVE_LEVEL_14                                  ((uint32_t)0x000E)
#define HSPIM_DMA_RECEIVE_LEVEL_15                                  ((uint32_t)0x000F)
#define HSPIM_DMA_RECEIVE_LEVEL_16                                  ((uint32_t)0x0010)
#define HSPIM_DMA_RECEIVE_LEVEL_32                                  ((uint32_t)0x0020)
#define HSPIM_DMA_RECEIVE_LEVEL_64                                  ((uint32_t)0x0040)

#define IS_HSPIM_DMA_RECEIVE_LEVEL(LEVEL)                           ((((uint32_t)(LEVEL)) >= HSPIM_DMA_RECEIVE_LEVEL_1) && \
                                                                    (((uint32_t)(LEVEL)) <= HSPIM_DMA_RECEIVE_LEVEL_64))
/**
  * @}
  */

/** @defgroup SPI_DMATransmitLevel
  * @{
  */
#define HSPIM_DMA_TRANSMIT_LEVEL_1                                  ((uint32_t)0x0001)
#define HSPIM_DMA_TRANSMIT_LEVEL_2                                  ((uint32_t)0x0002)
#define HSPIM_DMA_TRANSMIT_LEVEL_3                                  ((uint32_t)0x0003)
#define HSPIM_DMA_TRANSMIT_LEVEL_4                                  ((uint32_t)0x0004)
#define HSPIM_DMA_TRANSMIT_LEVEL_5                                  ((uint32_t)0x0005)
#define HSPIM_DMA_TRANSMIT_LEVEL_6                                  ((uint32_t)0x0006)
#define HSPIM_DMA_TRANSMIT_LEVEL_7                                  ((uint32_t)0x0007)
#define HSPIM_DMA_TRANSMIT_LEVEL_8                                  ((uint32_t)0x0008)
#define HSPIM_DMA_TRANSMIT_LEVEL_9                                  ((uint32_t)0x0009)
#define HSPIM_DMA_TRANSMIT_LEVEL_10                                 ((uint32_t)0x000A)
#define HSPIM_DMA_TRANSMIT_LEVEL_11                                 ((uint32_t)0x000B)
#define HSPIM_DMA_TRANSMIT_LEVEL_12                                 ((uint32_t)0x000C)
#define HSPIM_DMA_TRANSMIT_LEVEL_13                                 ((uint32_t)0x000D)
#define HSPIM_DMA_TRANSMIT_LEVEL_14                                 ((uint32_t)0x000E)
#define HSPIM_DMA_TRANSMIT_LEVEL_15                                 ((uint32_t)0x000F)
#define HSPIM_DMA_TRANSMIT_LEVEL_31                                 ((uint32_t)0x001F)
#define HSPIM_DMA_TRANSMIT_LEVEL_63                                 ((uint32_t)0x003F)

#define IS_HSPIM_DMA_TRANSMIT_LEVEL(LEVEL)                          ((((uint32_t)(LEVEL)) >= HSPIM_DMA_TRANSMIT_LEVEL_1) && \
                                                                    (((uint32_t)(LEVEL)) <= HSPIM_DMA_TRANSMIT_LEVEL_63))
/**
  * @}
  */

/** @defgroup HSPIM_Interrupt Mask and Status Flag
  * @{
  */

#define HSPIM_IT_RX                                                 ((uint32_t)0x8000)
#define HSPIM_IT_TX                                                 ((uint32_t)0x4000)
#define HSPIM_IT_EN                                                 ((uint32_t)0x2000)

#define HSPIM_IT_ID_RXF                                             ((uint32_t)0x0080)
#define HSPIM_IT_ID_RXTF                                                ((uint32_t)0x0040)
#define HSPIM_IT_ID_RXE                                             ((uint32_t)0x0020)

#define HSPIM_IT_ID_TXF                                             ((uint32_t)0x0008)
#define HSPIM_IT_ID_TXE                                             ((uint32_t)0x0002)
#define HSPIM_IT_ID_TXTF                                                ((uint32_t)0x0001)

#define HSPIM_FLAG_TXE                                              ((uint32_t)0x0004)
#define HSPIM_FLAG_TXF                                              ((uint32_t)0x0010)
#define HSPIM_FLAG_TXTF                                             ((uint32_t)0x0020)

#define HSPIM_FLAG_RXE                                              ((uint32_t)0x0400)
#define HSPIM_FLAG_RXF                                              ((uint32_t)0x1000)
#define HSPIM_FLAG_RXTF                                             ((uint32_t)0x2000)

#define HSPIM_FIFO_TX                                               ((uint32_t)0x0080)
#define HSPIM_FIFO_RX                                               ((uint32_t)0x0040)

/**
  * @}
  */

void HSPIM_Init(HSPIM_InitTypeDef* HSPIM_InitStruct);
void HSPIM_DMAInit(HSPIM_DMAInitTypeDef* HSPIM_DMAInitStruct);
void HSPIM_Cmd(FunctionalState NewState);
void HSPIM_TransmitCmd(FunctionalState NewState);
void HSPIM_DualQuadReceiveCmd(FunctionalState NewState);
void HSPIM_SendData(uint8_t Data);
uint8_t HSPIM_ReceiveData(void);
void HSPIM_ITConfig(uint32_t HSPIM_IT, FunctionalState NewState);
void HSPIM_FIFOReset(uint32_t HSPIM_IT);
FlagStatus HSPIM_IsTransmitDone(void);
FlagStatus HSPIM_IsReady(void);
FlagStatus HSPIM_GetFlagStatus(uint32_t HSPIM_Flag);
ITStatus HSPIM_GetITStatus(uint32_t HSPIM_IT);

void HSPIM_ModeSwitch(uint8_t Mode);
void HSPIM_WriteBuff(uint8_t Mode, uint16_t Size, uint8_t* Buff);
void HSPIM_ReadBuff(uint8_t Mode, uint16_t Size, uint8_t* Buff);

#ifdef __cplusplus
}
#endif
#endif

/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE***********************************************************************/
