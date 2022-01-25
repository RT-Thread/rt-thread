/**
  ******************************************************************************
  * @file    hk32f0xx_spi.h 
  *  @version V1.0.1
  * @date    2019-08-15
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F0XX_SPI_H
#define __HK32F0XX_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f0xx.h"

/** @addtogroup HK32F0xx_StdPeriph_Driver
  * @{
  */

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
}SPI_InitTypeDef;


/** 
  * @brief  I2S Init structure definition
  * @note   These parameters are not available for HK32F030 devices.    
  */

typedef struct
{
  uint16_t I2S_Mode;         /*!< Specifies the I2S operating mode.
                                  This parameter can be a value of @ref SPI_I2S_Mode */

  uint16_t I2S_Standard;     /*!< Specifies the standard used for the I2S communication.
                                  This parameter can be a value of @ref SPI_I2S_Standard */

  uint16_t I2S_DataFormat;   /*!< Specifies the data format for the I2S communication.
                                  This parameter can be a value of @ref SPI_I2S_Data_Format */

  uint16_t I2S_MCLKOutput;   /*!< Specifies whether the I2S MCLK output is enabled or not.
                                  This parameter can be a value of @ref SPI_I2S_MCLK_Output */

  uint32_t I2S_AudioFreq;    /*!< Specifies the frequency selected for the I2S communication.
                                  This parameter can be a value of @ref SPI_I2S_Audio_Frequency */

  uint16_t I2S_CPOL;         /*!< Specifies the idle state of the I2S clock.
                                  This parameter can be a value of @ref SPI_I2S_Clock_Polarity */
}I2S_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup SPI_Exported_Constants
  * @{
  */

#define IS_SPI_ALL_PERIPH(PERIPH) (((PERIPH) == SPI1) || \
                                   ((PERIPH) == SPI2))
                                   
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
  
/** @defgroup SPI_I2S_Mode 
  * @{
  */

#define I2S_Mode_SlaveTx                ((uint16_t)0x0000)
#define I2S_Mode_SlaveRx                ((uint16_t)0x0100)
#define I2S_Mode_MasterTx               ((uint16_t)0x0200)
#define I2S_Mode_MasterRx               ((uint16_t)0x0300)
#define IS_I2S_MODE(MODE) (((MODE) == I2S_Mode_SlaveTx) || \
                           ((MODE) == I2S_Mode_SlaveRx) || \
                           ((MODE) == I2S_Mode_MasterTx)|| \
                           ((MODE) == I2S_Mode_MasterRx))
/**
  * @}
  */

/** @defgroup SPI_I2S_Standard 
  * @{
  */

#define I2S_Standard_Phillips           ((uint16_t)0x0000)
#define I2S_Standard_MSB                ((uint16_t)0x0010)
#define I2S_Standard_LSB                ((uint16_t)0x0020)
#define I2S_Standard_PCMShort           ((uint16_t)0x0030)
#define I2S_Standard_PCMLong            ((uint16_t)0x00B0)
#define IS_I2S_STANDARD(STANDARD) (((STANDARD) == I2S_Standard_Phillips) || \
                                   ((STANDARD) == I2S_Standard_MSB) || \
                                   ((STANDARD) == I2S_Standard_LSB) || \
                                   ((STANDARD) == I2S_Standard_PCMShort) || \
                                   ((STANDARD) == I2S_Standard_PCMLong))
/**
  * @}
  */

/** @defgroup SPI_I2S_Data_Format 
  * @{
  */

#define I2S_DataFormat_16b              ((uint16_t)0x0000)
#define I2S_DataFormat_16bextended      ((uint16_t)0x0001)
#define I2S_DataFormat_24b              ((uint16_t)0x0003)
#define I2S_DataFormat_32b              ((uint16_t)0x0005)
#define IS_I2S_DATA_FORMAT(FORMAT) (((FORMAT) == I2S_DataFormat_16b) || \
                                    ((FORMAT) == I2S_DataFormat_16bextended) || \
                                    ((FORMAT) == I2S_DataFormat_24b) || \
                                    ((FORMAT) == I2S_DataFormat_32b))
/**
  * @}
  */

/** @defgroup SPI_I2S_MCLK_Output 
  * @{
  */

#define I2S_MCLKOutput_Enable           SPI_I2SPR_MCKOE
#define I2S_MCLKOutput_Disable          ((uint16_t)0x0000)
#define IS_I2S_MCLK_OUTPUT(OUTPUT) (((OUTPUT) == I2S_MCLKOutput_Enable) || \
                                    ((OUTPUT) == I2S_MCLKOutput_Disable))
/**
  * @}
  */

/** @defgroup SPI_I2S_Audio_Frequency 
  * @{
  */

#define I2S_AudioFreq_192k               ((uint32_t)192000)
#define I2S_AudioFreq_96k                ((uint32_t)96000)
#define I2S_AudioFreq_48k                ((uint32_t)48000)
#define I2S_AudioFreq_44k                ((uint32_t)44100)
#define I2S_AudioFreq_32k                ((uint32_t)32000)
#define I2S_AudioFreq_22k                ((uint32_t)22050)
#define I2S_AudioFreq_16k                ((uint32_t)16000)
#define I2S_AudioFreq_11k                ((uint32_t)11025)
#define I2S_AudioFreq_8k                 ((uint32_t)8000)
#define I2S_AudioFreq_Default            ((uint32_t)2)

#define IS_I2S_AUDIO_FREQ(FREQ) ((((FREQ) >= I2S_AudioFreq_8k) && \
                                 ((FREQ) <= I2S_AudioFreq_192k)) || \
                                 ((FREQ) == I2S_AudioFreq_Default))
/**
  * @}
  */

/** @defgroup SPI_I2S_Clock_Polarity 
  * @{
  */

#define I2S_CPOL_Low                    ((uint16_t)0x0000)
#define I2S_CPOL_High                   SPI_I2SCFGR_CKPOL
#define IS_I2S_CPOL(CPOL) (((CPOL) == I2S_CPOL_Low) || \
                           ((CPOL) == I2S_CPOL_High))
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

/** @defgroup SPI_I2S_DMA_transfer_requests 
  * @{
  */

#define SPI_I2S_DMAReq_Tx               SPI_CR2_TXDMAEN
#define SPI_I2S_DMAReq_Rx               SPI_CR2_RXDMAEN
#define IS_SPI_I2S_DMA_REQ(REQ) ((((REQ) & (uint16_t)0xFFFC) == 0x00) && ((REQ) != 0x00))
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

/** @defgroup SPI_I2S_interrupts_definition 
  * @{
  */

#define SPI_I2S_IT_TXE                  ((uint8_t)0x71)
#define SPI_I2S_IT_RXNE                 ((uint8_t)0x60)
#define SPI_I2S_IT_ERR                  ((uint8_t)0x50)

#define IS_SPI_I2S_CONFIG_IT(IT) (((IT) == SPI_I2S_IT_TXE) || \
                                  ((IT) == SPI_I2S_IT_RXNE) || \
                                  ((IT) == SPI_I2S_IT_ERR))

#define I2S_IT_UDR                      ((uint8_t)0x53)
#define SPI_IT_MODF                     ((uint8_t)0x55)
#define SPI_I2S_IT_OVR                  ((uint8_t)0x56)
#define SPI_I2S_IT_FRE                  ((uint8_t)0x58)

#define IS_SPI_I2S_GET_IT(IT) (((IT) == SPI_I2S_IT_RXNE) || ((IT) == SPI_I2S_IT_TXE) || \
                               ((IT) == SPI_I2S_IT_OVR) || ((IT) == SPI_IT_MODF) || \
                               ((IT) == SPI_I2S_IT_FRE)|| ((IT) == I2S_IT_UDR))
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


/** @defgroup SPI_I2S_flags_definition 
  * @{
  */

#define SPI_I2S_FLAG_RXNE               SPI_SR_RXNE
#define SPI_I2S_FLAG_TXE                SPI_SR_TXE
#define I2S_FLAG_CHSIDE                 SPI_SR_CHSIDE
#define I2S_FLAG_UDR                    SPI_SR_UDR
#define SPI_FLAG_CRCERR                 SPI_SR_CRCERR
#define SPI_FLAG_MODF                   SPI_SR_MODF
#define SPI_I2S_FLAG_OVR                SPI_SR_OVR
#define SPI_I2S_FLAG_BSY                SPI_SR_BSY
#define SPI_I2S_FLAG_FRE                SPI_SR_FRE



#define IS_SPI_CLEAR_FLAG(FLAG) (((FLAG) == SPI_FLAG_CRCERR))
#define IS_SPI_I2S_GET_FLAG(FLAG) (((FLAG) == SPI_I2S_FLAG_BSY) || ((FLAG) == SPI_I2S_FLAG_OVR) || \
                                   ((FLAG) == SPI_FLAG_MODF) || ((FLAG) == SPI_FLAG_CRCERR) || \
                                   ((FLAG) == SPI_I2S_FLAG_TXE) || ((FLAG) == SPI_I2S_FLAG_RXNE)|| \
                                   ((FLAG) == SPI_I2S_FLAG_FRE)|| ((FLAG) == I2S_FLAG_CHSIDE)|| \
                                   ((FLAG) == I2S_FLAG_UDR))
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
void SPI_I2S_DeInit(SPI_TypeDef* SPIx);
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct); /*!< Not applicable for HK32F030 devices */
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct); /*!< Not applicable for HK32F030 devices */
void SPI_TIModeCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_NSSPulseModeCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState); /*!< Not applicable for HK32F030 devices */
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize);
void SPI_RxFIFOThresholdConfig(SPI_TypeDef* SPIx, uint16_t SPI_RxFIFOThreshold);
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction);
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft);
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState);

/* Data transfers functions ***************************************************/
void SPI_SendData8(SPI_TypeDef* SPIx, uint8_t Data);
void SPI_I2S_SendData16(SPI_TypeDef* SPIx, uint16_t Data);
uint8_t SPI_ReceiveData8(SPI_TypeDef* SPIx);
uint16_t SPI_I2S_ReceiveData16(SPI_TypeDef* SPIx);

/* Hardware CRC Calculation functions *****************************************/
void SPI_CRCLengthConfig(SPI_TypeDef* SPIx, uint16_t SPI_CRCLength);
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_TransmitCRC(SPI_TypeDef* SPIx);
uint16_t SPI_GetCRC(SPI_TypeDef* SPIx, uint8_t SPI_CRC);
uint16_t SPI_GetCRCPolynomial(SPI_TypeDef* SPIx);

/* DMA transfers management functions *****************************************/
void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState);
void SPI_LastDMATransferCmd(SPI_TypeDef* SPIx, uint16_t SPI_LastDMATransfer);

/* Interrupts and flags management functions **********************************/
void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState);
uint16_t SPI_GetTransmissionFIFOStatus(SPI_TypeDef* SPIx);
uint16_t SPI_GetReceptionFIFOStatus(SPI_TypeDef* SPIx);
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);

#ifdef __cplusplus
}
#endif

#endif /*__HK32F0XX_SPI_H */

/**
  * @}
  */

/**
  * @}
  */

