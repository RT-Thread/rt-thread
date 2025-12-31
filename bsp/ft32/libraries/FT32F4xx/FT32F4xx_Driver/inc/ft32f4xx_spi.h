/**
  ******************************************************************************
  * @file               ft32f4xx_spi.h
  * @author             FMD AE
  * @brief              This file contains all the functions prototypes for the SPI
  *                     firmware library.
  * @version            V1.0.0
  * @data                   2025-03-06
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_SPI_H
#define __FT32F4XX_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"


/** @addtogroup SPI
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  SPI Init structure definition
  */

typedef struct
{
    uint16_t SPI_Direction;           /*!< Specifies the SPI unidirectional or bidirectional data mode.
                                         This parameter can be a value of @ref SPI_data_direction */

    uint16_t SPI_Mode;                /*!< Specifies the SPI mode (Master/Slave).
                                         This parameter can be a value of @ref SPI_mode */

    uint16_t SPI_DataSize;            /*!< Specifies the SPI data size.
                                         This parameter can be a value of @ref SPI_data_size */

    uint16_t SPI_CPOL;                /*!< Specifies the serial clock steady state.
                                         This parameter can be a value of @ref SPI_Clock_Polarity */

    uint16_t SPI_CPHA;                /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of @ref SPI_Clock_Phase */

    uint16_t SPI_NSS;                 /*!< Specifies whether the NSS signal is managed by
                                         hardware (NSS pin) or by software using the SSI bit.
                                         This parameter can be a value of @ref SPI_Slave_Select_management */

    uint16_t SPI_BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.
                                         This parameter can be a value of @ref SPI_BaudRate_Prescaler
                                         @note The communication clock is derived from the master
                                               clock. The slave clock does not need to be set. */

    uint16_t SPI_FirstBit;            /*!< Specifies whether data transfers start from MSB or LSB bit.
                                         This parameter can be a value of @ref SPI_MSB_LSB_transmission */

    uint16_t SPI_CRCPolynomial;       /*!< Specifies the polynomial used for the CRC calculation. */
} SPI_InitTypeDef;


/* Exported constants --------------------------------------------------------*/

/** @defgroup SPI_Exported_Constants
  * @{
  */

#define IS_SPI_ALL_PERIPH(PERIPH) (((PERIPH) == SPI1) || \
                                   ((PERIPH) == SPI2) || \
                                   ((PERIPH) == SPI3))

#define IS_SPI_1_PERIPH(PERIPH) (((PERIPH) == SPI1))

/** @defgroup SPI_data_direction
  * @{
  */

#define SPI_Direction_2Lines_FullDuplex ((uint16_t)0x0000)
#define SPI_Direction_2Lines_RxOnly     ((uint16_t)0x0400)
#define SPI_Direction_1Line_Rx          ((uint16_t)0x8000)
#define SPI_Direction_1Line_Tx          ((uint16_t)0xC000)
#define IS_SPI_DIRECTION_MODE(MODE) (((MODE) == SPI_Direction_2Lines_FullDuplex) || \
                                     ((MODE) == SPI_Direction_2Lines_RxOnly) || \
                                     ((MODE) == SPI_Direction_1Line_Rx) || \
                                     ((MODE) == SPI_Direction_1Line_Tx))
/**
  * @}
  */

/** @defgroup SPI_mode
  * @{
  */

#define SPI_Mode_Master                 ((uint16_t)0x0104)
#define SPI_Mode_Slave                  ((uint16_t)0x0000)
#define IS_SPI_MODE(MODE) (((MODE) == SPI_Mode_Master) || \
                           ((MODE) == SPI_Mode_Slave))
/**
  * @}
  */

/** @defgroup SPI_data_size
  * @{
  */

#define SPI_DataSize_4b                 ((uint16_t)0x0300)
#define SPI_DataSize_5b                 ((uint16_t)0x0400)
#define SPI_DataSize_6b                 ((uint16_t)0x0500)
#define SPI_DataSize_7b                 ((uint16_t)0x0600)
#define SPI_DataSize_8b                 ((uint16_t)0x0700)
#define SPI_DataSize_9b                 ((uint16_t)0x0800)
#define SPI_DataSize_10b                ((uint16_t)0x0900)
#define SPI_DataSize_11b                ((uint16_t)0x0A00)
#define SPI_DataSize_12b                ((uint16_t)0x0B00)
#define SPI_DataSize_13b                ((uint16_t)0x0C00)
#define SPI_DataSize_14b                ((uint16_t)0x0D00)
#define SPI_DataSize_15b                ((uint16_t)0x0E00)
#define SPI_DataSize_16b                ((uint16_t)0x0F00)
#define IS_SPI_DATA_SIZE(SIZE) (((SIZE) == SPI_DataSize_4b) || \
                                 ((SIZE) == SPI_DataSize_5b) || \
                                 ((SIZE) == SPI_DataSize_6b) || \
                                 ((SIZE) == SPI_DataSize_7b) || \
                                 ((SIZE) == SPI_DataSize_8b) || \
                                 ((SIZE) == SPI_DataSize_9b) || \
                                 ((SIZE) == SPI_DataSize_10b) || \
                                 ((SIZE) == SPI_DataSize_11b) || \
                                 ((SIZE) == SPI_DataSize_12b) || \
                                 ((SIZE) == SPI_DataSize_13b) || \
                                 ((SIZE) == SPI_DataSize_14b) || \
                                 ((SIZE) == SPI_DataSize_15b) || \
                                 ((SIZE) == SPI_DataSize_16b))
/**
  * @}
  */

/** @defgroup SPI_CRC_length
  * @{
  */

#define SPI_CRCLength_8b                ((uint16_t)0x0000)
#define SPI_CRCLength_16b               SPI_CR1_CRCL
#define IS_SPI_CRC_LENGTH(LENGTH) (((LENGTH) == SPI_CRCLength_8b) || \
                                   ((LENGTH) == SPI_CRCLength_16b))
/**
  * @}
  */

/** @defgroup SPI_Clock_Polarity
  * @{
  */

#define SPI_CPOL_Low                    ((uint16_t)0x0000)
#define SPI_CPOL_High                   SPI_CR1_CPOL
#define IS_SPI_CPOL(CPOL) (((CPOL) == SPI_CPOL_Low) || \
                           ((CPOL) == SPI_CPOL_High))
/**
  * @}
  */

/** @defgroup SPI_Clock_Phase
  * @{
  */

#define SPI_CPHA_1Edge                  ((uint16_t)0x0000)
#define SPI_CPHA_2Edge                  SPI_CR1_CPHA
#define IS_SPI_CPHA(CPHA) (((CPHA) == SPI_CPHA_1Edge) || \
                           ((CPHA) == SPI_CPHA_2Edge))
/**
  * @}
  */

/** @defgroup SPI_Slave_Select_management
  * @{
  */

#define SPI_NSS_Soft                    SPI_CR1_SSM
#define SPI_NSS_Hard                    ((uint16_t)0x0000)
#define IS_SPI_NSS(NSS) (((NSS) == SPI_NSS_Soft) || \
                         ((NSS) == SPI_NSS_Hard))
/**
  * @}
  */

/** @defgroup SPI_BaudRate_Prescaler
  * @{
  */

#define SPI_BaudRatePrescaler_2         ((uint16_t)0x0000)
#define SPI_BaudRatePrescaler_4         ((uint16_t)0x0008)
#define SPI_BaudRatePrescaler_8         ((uint16_t)0x0010)
#define SPI_BaudRatePrescaler_16        ((uint16_t)0x0018)
#define SPI_BaudRatePrescaler_32        ((uint16_t)0x0020)
#define SPI_BaudRatePrescaler_64        ((uint16_t)0x0028)
#define SPI_BaudRatePrescaler_128       ((uint16_t)0x0030)
#define SPI_BaudRatePrescaler_256       ((uint16_t)0x0038)
#define IS_SPI_BAUDRATE_PRESCALER(PRESCALER) (((PRESCALER) == SPI_BaudRatePrescaler_2) || \
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

/** @defgroup SPI_MSB_LSB_transmission
  * @{
  */

#define SPI_FirstBit_MSB                ((uint16_t)0x0000)
#define SPI_FirstBit_LSB                SPI_CR1_LSBFIRST
#define IS_SPI_FIRST_BIT(BIT) (((BIT) == SPI_FirstBit_MSB) || \
                               ((BIT) == SPI_FirstBit_LSB))
/**
  * @}
  */

/** @defgroup SPI_FIFO_reception_threshold
  * @{
  */

#define SPI_RxFIFOThreshold_HF          ((uint16_t)0x0000)
#define SPI_RxFIFOThreshold_QF          SPI_CR2_FRXTH
#define IS_SPI_RX_FIFO_THRESHOLD(THRESHOLD) (((THRESHOLD) == SPI_RxFIFOThreshold_HF) || \
                                             ((THRESHOLD) == SPI_RxFIFOThreshold_QF))
/**
  * @}
  */

/** @defgroup SPI_DMA_transfer_requests
  * @{
  */

#define SPI_DMAReq_Tx                       (SPI_CR2_TXDMAEN)
#define SPI_DMAReq_Rx                       (SPI_CR2_RXDMAEN)
#define IS_SPI_DMA_REQ(REQ)                 ((((REQ) & (uint16_t)0xFFFC) == 0x00) && ((REQ) != 0x00))

/**
  * @}
  */

/** @defgroup SPI_last_DMA_transfers
  * @{
  */

#define SPI_LastDMATransfer_TxEvenRxEven   ((uint16_t)0x0000)
#define SPI_LastDMATransfer_TxOddRxEven    ((uint16_t)0x4000)
#define SPI_LastDMATransfer_TxEvenRxOdd    ((uint16_t)0x2000)
#define SPI_LastDMATransfer_TxOddRxOdd     ((uint16_t)0x6000)
#define IS_SPI_LAST_DMA_TRANSFER(TRANSFER) (((TRANSFER) == SPI_LastDMATransfer_TxEvenRxEven) || \
                                            ((TRANSFER) == SPI_LastDMATransfer_TxOddRxEven) || \
                                            ((TRANSFER) == SPI_LastDMATransfer_TxEvenRxOdd) || \
                                            ((TRANSFER) == SPI_LastDMATransfer_TxOddRxOdd))
/**
  * @}
  */
/** @defgroup SPI_NSS_internal_software_management
  * @{
  */

#define SPI_NSSInternalSoft_Set         SPI_CR1_SSI
#define SPI_NSSInternalSoft_Reset       ((uint16_t)0xFEFF)
#define IS_SPI_NSS_INTERNAL(INTERNAL) (((INTERNAL) == SPI_NSSInternalSoft_Set) || \
                                       ((INTERNAL) == SPI_NSSInternalSoft_Reset))
/**
  * @}
  */

/** @defgroup SPI_CRC_Transmit_Receive
  * @{
  */

#define SPI_CRC_Tx                      ((uint8_t)0x00)
#define SPI_CRC_Rx                      ((uint8_t)0x01)
#define IS_SPI_CRC(CRC) (((CRC) == SPI_CRC_Tx) || ((CRC) == SPI_CRC_Rx))
/**
  * @}
  */

/** @defgroup SPI_direction_transmit_receive
  * @{
  */

#define SPI_Direction_Rx                ((uint16_t)0xBFFF)
#define SPI_Direction_Tx                ((uint16_t)0x4000)
#define IS_SPI_DIRECTION(DIRECTION) (((DIRECTION) == SPI_Direction_Rx) || \
                                     ((DIRECTION) == SPI_Direction_Tx))
/**
  * @}
  */

/** @defgroup SPI_interrupts_definition
  * @{
  */

#define SPI_IT_TXE                  ((uint8_t)0x71)
#define SPI_IT_RXNE                 ((uint8_t)0x60)
#define SPI_IT_ERR                  ((uint8_t)0x50)

#define IS_SPI_CONFIG_IT(IT) (((IT) == SPI_IT_TXE) || \
                                  ((IT) == SPI_IT_RXNE) || \
                                  ((IT) == SPI_IT_ERR))

#define IT_UDR                      ((uint8_t)0x53)
#define SPI_IT_MODF                     ((uint8_t)0x55)
#define SPI_IT_OVR                  ((uint8_t)0x56)
#define SPI_IT_FRE                  ((uint8_t)0x58)

#define IS_SPI_GET_IT(IT) (((IT) == SPI_IT_RXNE) || ((IT) == SPI_IT_TXE) || \
                               ((IT) == SPI_IT_OVR) || ((IT) == SPI_IT_MODF) || \
                               ((IT) == SPI_IT_FRE)|| ((IT) == IT_UDR))
/**
  * @}
  */


/** @defgroup SPI_transmission_fifo_status_level
  * @{
  */

#define SPI_TransmissionFIFOStatus_Empty           ((uint16_t)0x0000)
#define SPI_TransmissionFIFOStatus_1QuarterFull    ((uint16_t)0x0800)
#define SPI_TransmissionFIFOStatus_HalfFull        ((uint16_t)0x1000)
#define SPI_TransmissionFIFOStatus_Full            ((uint16_t)0x1800)

/**
  * @}
  */

/** @defgroup SPI_reception_fifo_status_level
  * @{
  */
#define SPI_ReceptionFIFOStatus_Empty           ((uint16_t)0x0000)
#define SPI_ReceptionFIFOStatus_1QuarterFull    ((uint16_t)0x0200)
#define SPI_ReceptionFIFOStatus_HalfFull        ((uint16_t)0x0400)
#define SPI_ReceptionFIFOStatus_Full            ((uint16_t)0x0600)

/**
  * @}
  */


/** @defgroup SPI_flags_definition
  * @{
  */

#define SPI_FLAG_RXNE               SPI_SR_RXNE
#define SPI_FLAG_TXE                SPI_SR_TXE
#define SPI_FLAG_CRCERR             SPI_SR_CRCERR
#define SPI_FLAG_MODF               SPI_SR_MODF
#define SPI_FLAG_OVR                SPI_SR_OVR
#define SPI_FLAG_BSY                SPI_SR_BSY
#define SPI_FLAG_FRE                SPI_SR_FRE



#define IS_SPI_CLEAR_FLAG(FLAG) (((FLAG) == SPI_FLAG_CRCERR))
#define IS_SPI_GET_FLAG(FLAG) (((FLAG) == SPI_FLAG_BUSY) || ((FLAG) == SPI_FLAG_OVR) || \
                                   ((FLAG) == SPI_FLAG_MODF) || ((FLAG) == SPI_FLAG_CRCERR) || \
                                   ((FLAG) == SPI_FLAG_TXE) || ((FLAG) == SPI_FLAG_RXNE)|| \
                                   ((FLAG) == SPI_FLAG_FRE))
/**
  * @}
  */

/** @defgroup SPI_CRC_polynomial
  * @{
  */

#define IS_SPI_CRC_POLYNOMIAL(POLYNOMIAL) ((POLYNOMIAL) >= 0x1)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Initialization and Configuration functions *********************************/
void SPI_DeInit(SPI_TypeDef* SPIx);
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void SPI_TIModeCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_NSSPulseModeCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize);
void SPI_RxFIFOThresholdConfig(SPI_TypeDef* SPIx, uint16_t SPI_RxFIFOThreshold);
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction);
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft);
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState);

/* Data transfers functions ***************************************************/
void SPI_SendData8(SPI_TypeDef* SPIx, uint8_t Data);
void SPI_SendData16(SPI_TypeDef* SPIx, uint16_t Data);
uint8_t SPI_ReceiveData8(SPI_TypeDef* SPIx);
uint16_t SPI_ReceiveData16(SPI_TypeDef* SPIx);

/* Hardware CRC Calculation functions *****************************************/
void SPI_CRCLengthConfig(SPI_TypeDef* SPIx, uint16_t SPI_CRCLength);
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_TransmitCRC(SPI_TypeDef* SPIx);
uint16_t SPI_GetCRC(SPI_TypeDef* SPIx, uint8_t SPI_CRC);
uint16_t SPI_GetCRCPolynomial(SPI_TypeDef* SPIx);

/* DMA transfers management functions *****************************************/
void SPI_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_DMAReq, FunctionalState NewState);
void SPI_LastDMATransferCmd(SPI_TypeDef* SPIx, uint16_t SPI_LastDMATransfer);

/* Interrupts and flags management functions **********************************/
void SPI_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_IT, FunctionalState NewState);
uint16_t SPI_GetTransmissionFIFOStatus(SPI_TypeDef* SPIx);
uint16_t SPI_GetReceptionFIFOStatus(SPI_TypeDef* SPIx);
FlagStatus SPI_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_FLAG);
void SPI_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_FLAG);
ITStatus SPI_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_IT);

#ifdef __cplusplus
}
#endif

#endif /*__FT32F4XX_SPI_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
