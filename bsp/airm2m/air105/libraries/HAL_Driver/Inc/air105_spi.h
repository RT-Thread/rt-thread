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



#ifndef __AIR105_SPI_H
#define __AIR105_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "air105.h"

#define SPI_DMACR_RDMAE_Pos                             (0)
#define SPI_DMACR_RDMAE_Mask                            (0x01U << SPI_DMACR_RDMAE_Pos)

#define SPI_DMACR_TDMAE_Pos                             (1)
#define SPI_DMACR_TDMAE_Mask                            (0x01U << SPI_DMACR_TDMAE_Pos)


/** @defgroup SPI_Exported_Types
  * @{
  */

/**
  * @brief  SPI Init structure definition
  */
typedef struct
{
    uint32_t SPI_Direction;           /*!< Specifies the SPI unidirectional or bidirectional data mode.
                                         This parameter can be a value of @ref SPI_data_direction */
    uint32_t SPI_Mode;                /*!< Specifies the SPI operating mode.
                                         This parameter can be a value of @ref SPI_mode */
    uint32_t SPI_DataSize;            /*!< Specifies the SPI data size.
                                         This parameter can be a value of @ref SPI_data_size */

    uint32_t SPI_CPOL;                /*!< Specifies the serial clock steady state.
                                         This parameter can be a value of @ref SPI_Clock_Polarity */

    uint32_t SPI_CPHA;                /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of @ref SPI_Clock_Phase */

    uint32_t SPI_NSS;                 /*!< Specifies whether the NSS signal is managed by
                                         hardware (NSS pin) or by software using the SSI bit.
                                         This parameter can be a value of @ref SPI_Slave_Select_management */

    uint32_t SPI_BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.
                                         This parameter can be a value of @ref SPI_BaudRate_Prescaler.
                                         @note The communication clock is derived from the master
                                               clock. The slave clock does not need to be set. */
    uint32_t SPI_RXFIFOFullThreshold;

    uint32_t SPI_TXFIFOEmptyThreshold;
}SPI_InitTypeDef;


/**
  * @brief  Texas Instruments Synchronous Serial Protocol (SSP) Init structure definition
  */
typedef struct
{
    uint32_t SSP_Direction;           /*!< Specifies the SPI unidirectional or bidirectional data mode.
                                         This parameter can be a value of @ref SPI_data_direction */

    uint32_t SSP_DataSize;            /*!< Specifies the SPI data size.
                                         This parameter can be a value of @ref SPI_data_size */

    uint32_t SSP_NSS;                 /*!< Specifies whether the NSS signal is managed by
                                         hardware (NSS pin) or by software using the SSI bit.
                                         This parameter can be a value of @ref SPI_Slave_Select_management */

    uint32_t SSP_BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.
                                         This parameter can be a value of @ref SPI_BaudRate_Prescaler.
                                         @note The communication clock is derived from the master
                                               clock. The slave clock does not need to be set. */

    uint32_t SSP_RXFIFOFullThreshold;

    uint32_t SSP_TXFIFOEmptyThreshold;
}SSP_InitTypeDef;


/**
  * @brief  National Semiconductor Microwire (NSM) Init structure definition
  */
typedef struct
{
    uint32_t NSM_Direction;

    uint32_t NSM_TransferMode;

    uint32_t NSM_DataSize;            /*!< Specifies the SPI data size.
                                    This parameter can be a value of @ref SPI_data_size */
    uint32_t NSM_ControlDataSize;

    uint32_t NSM_NSS;                 /*!< Specifies whether the NSS signal is managed by
                                         hardware (NSS pin) or by software using the SSI bit.
                                         This parameter can be a value of @ref SPI_Slave_Select_management */

    uint32_t NSM_BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.
                                         This parameter can be a value of @ref SPI_BaudRate_Prescaler.
                                         @note The communication clock is derived from the master
                                               clock. The slave clock does not need to be set. */

    FunctionalState NSM_HandShakingCmd;

    uint32_t NSM_RXFIFOFullThreshold;

    uint32_t NSM_TXFIFOEmptyThreshold;
}NSM_InitTypeDef;


/**
  * @brief  SPI DMA Init structure definition
  */
typedef struct
{
    uint32_t SPI_DMAReq;
    uint32_t SPI_DMAReceiveLevel;
    uint32_t SPI_DMATransmitLevel;
    FunctionalState SPI_DMAEnCmd;
}SPI_DMAInitTypeDef;


/** @defgroup SPI_data_direction
  * @{
  */
#define SPI_Direction_2Lines_FullDuplex         ((uint32_t)0x0000)
#define SPI_Direction_1Line_Tx                  ((uint32_t)0x0100)
#define SPI_Direction_1Line_Rx                  ((uint32_t)0x0200)
#define SPI_Direction_EEPROM_Read               ((uint32_t)0x0300)
#define IS_SPI_DIRECTION_MODE(MODE)             (((MODE) == SPI_Direction_2Lines_FullDuplex) || \
                                                ((MODE) == SPI_Direction_1Line_Tx) || \
                                                ((MODE) == SPI_Direction_1Line_Rx) || \
                                                ((MODE) == SPI_Direction_EEPROM_Read))
/**
  * @}
  */

#define SPI_Mode_Master                 ((uint32_t)0x0001)
#define SPI_Mode_Slave                  ((uint32_t)0x0000)
#define IS_SPI_MODE(MODE)               (((MODE) == SPI_Mode_Master) || \
                                        ((MODE) == SPI_Mode_Slave))

/** @defgroup SPI_data_size
  * @{
  */
#define SPI_DataSize_8b                 ((uint32_t)0x0007)
#define SPI_DataSize_16b                ((uint32_t)0x000F)
#define IS_SPI_DATASIZE(DATASIZE)       (((DATASIZE) == SPI_DataSize_16b) || \
                                        ((DATASIZE) == SPI_DataSize_8b))
/**
  * @}
  */

/** @defgroup SPI_Clock_Polarity
  * @{
  */

#define SPI_CPOL_Low                    ((uint32_t)0x0000)
#define SPI_CPOL_High                   ((uint32_t)0x0080)
#define IS_SPI_CPOL(CPOL)               (((CPOL) == SPI_CPOL_Low) || \
                                        ((CPOL) == SPI_CPOL_High))
/**
  * @}
  */

/** @defgroup SPI_Clock_Phase
  * @{
  */
#define SPI_CPHA_1Edge                  ((uint32_t)0x0000)
#define SPI_CPHA_2Edge                  ((uint32_t)0x0040)
#define IS_SPI_CPHA(CPHA)               (((CPHA) == SPI_CPHA_1Edge) || \
                                        ((CPHA) == SPI_CPHA_2Edge))
/**
  * @}
  */

#define SPI_NSS_0                    ((uint32_t)0x0001)
#define SPI_NSS_Null                 ((uint32_t)0x0000)
#define IS_SPI_NSS(NSS)              (((NSS) == SPI_NSS_0) || \
                                     ((NSS) == SPI_NSS_Null))

/** @defgroup SPI_BaudRate_Prescaler
  * @{
  */
#define SPI_BaudRatePrescaler_2         ((uint32_t)0x0002)
#define SPI_BaudRatePrescaler_4         ((uint32_t)0x0004)
#define SPI_BaudRatePrescaler_8         ((uint32_t)0x0008)
#define SPI_BaudRatePrescaler_16        ((uint32_t)0x0010)
#define SPI_BaudRatePrescaler_32        ((uint32_t)0x0020)
#define SPI_BaudRatePrescaler_64        ((uint32_t)0x0040)
#define SPI_BaudRatePrescaler_128       ((uint32_t)0x0080)
#define SPI_BaudRatePrescaler_256       ((uint32_t)0x0100)
#define IS_SPI_BAUDRATE_PRESCALER(PRESCALER)  (((PRESCALER) == SPI_BaudRatePrescaler_2) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_4) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_8) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_16) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_32) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_64) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_128) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_256))
/**
  * @}
  */

/** @defgroup SPI_RXFIFOFullThreshold
  * @{
  */
#define SPI_RXFIFOFullThreshold_1        ((uint32_t)0x0000)
#define SPI_RXFIFOFullThreshold_2        ((uint32_t)0x0001)
#define SPI_RXFIFOFullThreshold_3        ((uint32_t)0x0002)
#define SPI_RXFIFOFullThreshold_4        ((uint32_t)0x0003)
#define SPI_RXFIFOFullThreshold_5        ((uint32_t)0x0004)
#define SPI_RXFIFOFullThreshold_6        ((uint32_t)0x0005)
#define SPI_RXFIFOFullThreshold_7        ((uint32_t)0x0006)
#define SPI_RXFIFOFullThreshold_8        ((uint32_t)0x0007)
#define SPI_RXFIFOFullThreshold_9        ((uint32_t)0x0008)
#define SPI_RXFIFOFullThreshold_10       ((uint32_t)0x0009)
#define SPI_RXFIFOFullThreshold_11       ((uint32_t)0x000A)
#define SPI_RXFIFOFullThreshold_12       ((uint32_t)0x000B)
#define SPI_RXFIFOFullThreshold_13       ((uint32_t)0x000C)
#define SPI_RXFIFOFullThreshold_14       ((uint32_t)0x000D)
#define SPI_RXFIFOFullThreshold_15       ((uint32_t)0x000E)
#define SPI_RXFIFOFullThreshold_16       ((uint32_t)0x000F)

#define IS_SPI_RX_FIFO_FULL_THRESHOLD(THRESHOLD)    (((THRESHOLD) == SPI_RXFIFOFullThreshold_1) || \
                                                    ((THRESHOLD) == SPI_RXFIFOFullThreshold_2) || \
                                                    ((THRESHOLD) == SPI_RXFIFOFullThreshold_3) || \
                                                    ((THRESHOLD) == SPI_RXFIFOFullThreshold_4) || \
                                                    ((THRESHOLD) == SPI_RXFIFOFullThreshold_5) || \
                                                    ((THRESHOLD) == SPI_RXFIFOFullThreshold_6) || \
                                                    ((THRESHOLD) == SPI_RXFIFOFullThreshold_7) || \
                                                    ((THRESHOLD) == SPI_RXFIFOFullThreshold_8) || \
                                                    ((THRESHOLD) == SPI_RXFIFOFullThreshold_9) || \
                                                    ((THRESHOLD) == SPI_RXFIFOFullThreshold_10) || \
                                                    ((THRESHOLD) == SPI_RXFIFOFullThreshold_11) || \
                                                    ((THRESHOLD) == SPI_RXFIFOFullThreshold_12) || \
                                                    ((THRESHOLD) == SPI_RXFIFOFullThreshold_13) || \
                                                    ((THRESHOLD) == SPI_RXFIFOFullThreshold_14) || \
                                                    ((THRESHOLD) == SPI_RXFIFOFullThreshold_15) || \
                                                    ((THRESHOLD) == SPI_RXFIFOFullThreshold_16))
/**
  * @}
  */

/** @defgroup SPI_TXFIFOEmptyThreshold
  * @{
  */
#define SPI_TXFIFOEmptyThreshold_0        ((uint32_t)0x0000)
#define SPI_TXFIFOEmptyThreshold_1        ((uint32_t)0x0001)
#define SPI_TXFIFOEmptyThreshold_2        ((uint32_t)0x0002)
#define SPI_TXFIFOEmptyThreshold_3        ((uint32_t)0x0003)
#define SPI_TXFIFOEmptyThreshold_4        ((uint32_t)0x0004)
#define SPI_TXFIFOEmptyThreshold_5        ((uint32_t)0x0005)
#define SPI_TXFIFOEmptyThreshold_6        ((uint32_t)0x0006)
#define SPI_TXFIFOEmptyThreshold_7        ((uint32_t)0x0007)
#define SPI_TXFIFOEmptyThreshold_8        ((uint32_t)0x0008)
#define SPI_TXFIFOEmptyThreshold_9        ((uint32_t)0x0009)
#define SPI_TXFIFOEmptyThreshold_10       ((uint32_t)0x000A)
#define SPI_TXFIFOEmptyThreshold_11       ((uint32_t)0x000B)
#define SPI_TXFIFOEmptyThreshold_12       ((uint32_t)0x000C)
#define SPI_TXFIFOEmptyThreshold_13       ((uint32_t)0x000D)
#define SPI_TXFIFOEmptyThreshold_14       ((uint32_t)0x000E)
#define SPI_TXFIFOEmptyThreshold_15       ((uint32_t)0x000F)

#define IS_SPI_TX_FIFO_EMPTY_THRESHOLD(THRESHOLD)   (((THRESHOLD) == SPI_TXFIFOEmptyThreshold_0) || \
                                                    ((THRESHOLD) == SPI_TXFIFOEmptyThreshold_1) || \
                                                    ((THRESHOLD) == SPI_TXFIFOEmptyThreshold_2) || \
                                                    ((THRESHOLD) == SPI_TXFIFOEmptyThreshold_3) || \
                                                    ((THRESHOLD) == SPI_TXFIFOEmptyThreshold_4) || \
                                                    ((THRESHOLD) == SPI_TXFIFOEmptyThreshold_5) || \
                                                    ((THRESHOLD) == SPI_TXFIFOEmptyThreshold_6) || \
                                                    ((THRESHOLD) == SPI_TXFIFOEmptyThreshold_7) || \
                                                    ((THRESHOLD) == SPI_TXFIFOEmptyThreshold_8) || \
                                                    ((THRESHOLD) == SPI_TXFIFOEmptyThreshold_9) || \
                                                    ((THRESHOLD) == SPI_TXFIFOEmptyThreshold_10) || \
                                                    ((THRESHOLD) == SPI_TXFIFOEmptyThreshold_11) || \
                                                    ((THRESHOLD) == SPI_TXFIFOEmptyThreshold_12) || \
                                                    ((THRESHOLD) == SPI_TXFIFOEmptyThreshold_13) || \
                                                    ((THRESHOLD) == SPI_TXFIFOEmptyThreshold_14) || \
                                                    ((THRESHOLD) <= SPI_TXFIFOEmptyThreshold_15))
/**
  * @}
  */

/** @defgroup SPI_DMAReceiveLevel
  * @{
  */
#define SPI_DMAReceiveLevel_1                   ((uint32_t)0x0000)
#define SPI_DMAReceiveLevel_2                   ((uint32_t)0x0001)
#define SPI_DMAReceiveLevel_3                   ((uint32_t)0x0002)
#define SPI_DMAReceiveLevel_4                   ((uint32_t)0x0003)
#define SPI_DMAReceiveLevel_5                   ((uint32_t)0x0004)
#define SPI_DMAReceiveLevel_6                   ((uint32_t)0x0005)
#define SPI_DMAReceiveLevel_7                   ((uint32_t)0x0006)
#define SPI_DMAReceiveLevel_8                   ((uint32_t)0x0007)
#define SPI_DMAReceiveLevel_9                   ((uint32_t)0x0008)
#define SPI_DMAReceiveLevel_10                  ((uint32_t)0x0009)
#define SPI_DMAReceiveLevel_11                  ((uint32_t)0x000A)
#define SPI_DMAReceiveLevel_12                  ((uint32_t)0x000B)
#define SPI_DMAReceiveLevel_13                  ((uint32_t)0x000C)
#define SPI_DMAReceiveLevel_14                  ((uint32_t)0x000D)
#define SPI_DMAReceiveLevel_15                  ((uint32_t)0x000E)
#define SPI_DMAReceiveLevel_16                  ((uint32_t)0x000F)

#define IS_SPI_DMA_RECEIVE_LEVEL(LEVEL)         ((((int32_t)(LEVEL)) >= SPI_DMAReceiveLevel_1) && \
                                                (((int32_t)(LEVEL)) <= SPI_DMAReceiveLevel_16))
/**
  * @}
  */

/** @defgroup SPI_DMATransmitLevel
  * @{
  */
#define SPI_DMATransmitLevel_0                  ((uint32_t)0x0000)
#define SPI_DMATransmitLevel_1                  ((uint32_t)0x0001)
#define SPI_DMATransmitLevel_2                  ((uint32_t)0x0002)
#define SPI_DMATransmitLevel_3                  ((uint32_t)0x0003)
#define SPI_DMATransmitLevel_4                  ((uint32_t)0x0004)
#define SPI_DMATransmitLevel_5                  ((uint32_t)0x0005)
#define SPI_DMATransmitLevel_6                  ((uint32_t)0x0006)
#define SPI_DMATransmitLevel_7                  ((uint32_t)0x0007)
#define SPI_DMATransmitLevel_8                  ((uint32_t)0x0008)
#define SPI_DMATransmitLevel_9                  ((uint32_t)0x0009)
#define SPI_DMATransmitLevel_10                 ((uint32_t)0x000A)
#define SPI_DMATransmitLevel_11                 ((uint32_t)0x000B)
#define SPI_DMATransmitLevel_12                 ((uint32_t)0x000C)
#define SPI_DMATransmitLevel_13                 ((uint32_t)0x000D)
#define SPI_DMATransmitLevel_14                 ((uint32_t)0x000E)
#define SPI_DMATransmitLevel_15                 ((uint32_t)0x000F)

#define IS_SPI_DMA_TRANSMIT_LEVEL(LEVEL)    ((((int32_t)(LEVEL)) >= SPI_DMATransmitLevel_0) && \
                                            (((int32_t)(LEVEL)) <= SPI_DMATransmitLevel_15))
/**
  * @}
  */


/** @defgroup SPI_DMA_transfer_requests
  * @{
  */
#define SPI_DMAReq_Rx               ((uint32_t)0x0001)
#define SPI_DMAReq_Tx               ((uint32_t)0x0002)
#define IS_SPI_DMAREQ(DMAREQ)       ((((DMAREQ) & (uint32_t)0xFFFC) == (uint32_t)0x00) && \
                                    ((DMAREQ) != (uint32_t)0x00))
/**
  * @}
  */

/** @defgroup SPI_Interrupt Mask and Status Flag
  * @{
  */
#define SPI_IT_TXE                      ((uint32_t)0x0001)              //clear by hardware
#define SPI_IT_TXOVF                    ((uint32_t)0x0002)              //clear by read TXOICR register
#define SPI_IT_RXF                      ((uint32_t)0x0010)              //clear by hardware
#define SPI_IT_RXOVF                    ((uint32_t)0x0008)              //clear by read RXOICR register
#define SPI_IT_RXUDF                    ((uint32_t)0x0004)              //clear by read RXURCR register
#define SPI_IT_MMC                      ((uint32_t)0x0020)              //clear by read MSTICR register
#define SPI_IT_All                      ((uint32_t)0x002E)
#define IS_SPI_GET_IT(IT)               (((IT) == SPI_IT_TXE) || \
                                        ((IT) == SPI_IT_TXOVF) || \
                                        ((IT) == SPI_IT_RXF) || \
                                        ((IT) == SPI_IT_RXUDF) || \
                                        ((IT) == SPI_IT_RXOVF) || \
                                        ((IT) == SPI_IT_MMC))

#define SPI_FLAG_BSY                    ((uint32_t)0x0001)
#define SPI_FLAG_TXNF                   ((uint32_t)0x0002)              //clear by hardware
#define SPI_FLAG_TXE                    ((uint32_t)0x0004)              //clear by hardware
#define SPI_FLAG_RXNE                   ((uint32_t)0x0008)              //clear by hardware
#define SPI_FLAG_RXF                    ((uint32_t)0x0010)              //clear by hardware
#define SPI_FLAG_TXERR                  ((uint32_t)0x0020)              //read clear
#define SPI_FLAG_DCERR                  ((uint32_t)0x0040)              //read clear
#define IS_SPI_GET_FLAG(FLAG)           (((FLAG) == SPI_SR_RFNE) || \
                                        ((FLAG) == SPI_SR_RFF) || \
                                        ((FLAG) == SPI_SR_TFE) || \
                                        ((FLAG) == SPI_SR_TFNF) || \
                                        ((FLAG) == SPI_SR_BUSY))
/**
  * @}
  */

/** @defgroup NSM_Direction
  * @{
  */
#define NSM_Direction_Data_Transmit         ((uint32_t)(0x0001))
#define NSM_Direction_Data_Receive          ((uint32_t)(0x0002))
#define IS_NSM_DIRECTION_MODE(MODE)         (((MODE) == NSM_Direction_Data_Transmit) || \
                                            ((MODE) == NSM_Direction_Data_Receive))
/**
  * @}
  */


/** @defgroup NSM_TransferMode
  * @{
  */
#define NSM_TransferMode_Non_Sequential     ((uint32_t)(0x0001))
#define NSM_TransferMode_Sequential         ((uint32_t)(0x0002))
#define IS_NSM_TRANSFER_MODE(MODE)          (((MODE) == NSM_TransferMode_Non_Sequential) || \
                                            ((MODE) == NSM_TransferMode_Sequential))
/**
  * @}
  */


/** @defgroup NSM_DataSize
  * @{
  */
#define NSM_DataSize_8b                 ((uint32_t)0x0007)
#define NSM_DataSize_16b                ((uint32_t)0x000F)
#define IS_NSM_DATASIZE(DATASIZE)       (((DATASIZE) == NSM_DataSize_8b) || \
                                        ((DATASIZE) == NSM_DataSize_16b))
/**
  * @}
  */


/** @defgroup NSM_ControlDataSize
  * @{
  */
#define NSM_ControlDataSize_8b           ((uint32_t)0x0007)
#define NSM_ControlDataSize_16b          ((uint32_t)0x000F)
#define IS_NSM_CONTROL_DATASIZE(DATASIZE)       (((DATASIZE) == NSM_ControlDataSize_8b) || \
                                                ((DATASIZE) == NSM_ControlDataSize_16b))
/**
  * @}
  */

void SPI_DeInit(SPI_TypeDef* SPIx);
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);

void SPI_DMAInit(SPI_TypeDef* SPIx, SPI_DMAInitTypeDef* SPI_DMAInitStruct);
void SPI_DMAStructInit(SPI_DMAInitTypeDef* SPI_DMAInitStruct);
void SPI_DMACmd(SPI_TypeDef* SPIx, uint32_t SPI_DMAReq, FunctionalState NewState);

void SPI_ITConfig(SPI_TypeDef* SPIx, uint32_t SPI_IT, FunctionalState NewState);
void SPI_SendData(SPI_TypeDef* SPIx, uint16_t Data);
uint16_t SPI_ReceiveData(SPI_TypeDef* SPIx);
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint32_t SPI_DataSize);
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint32_t SPI_Direction);

ITStatus SPI_GetITStatus(SPI_TypeDef* SPIx, uint32_t SPI_IT);
void SPI_ClearITPendingBit(SPI_TypeDef* SPIx, uint32_t SPI_IT);

FlagStatus SPI_GetFlagStatus(SPI_TypeDef* SPIx, uint32_t SPI_FLAG);
uint32_t SPI_GetFlagStatusReg(SPI_TypeDef* SPIx);

FlagStatus SPI_IsBusy(SPI_TypeDef* SPIx);
FlagStatus SPI_IsTXErr(SPI_TypeDef* SPIx);
FlagStatus SPI_IsDataCollisionErr(SPI_TypeDef* SPIx);

void SSP_Init(SPI_TypeDef* SPIx, SSP_InitTypeDef* SSP_InitStruct);
void SSP_StructInit(SSP_InitTypeDef* SSP_InitStruct);

void NSM_Init(SPI_TypeDef* SPIx, NSM_InitTypeDef* NSM_InitStruct);
void NSM_StructInit(NSM_InitTypeDef* NSM_InitStruct);


#ifdef __cplusplus
}
#endif

/**
  * @}
  */

#endif /*__MSSCPU_SPI_H */


/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE****/
