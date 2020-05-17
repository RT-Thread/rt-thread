/**
 **************************************************************************
 * File Name    : at32f4xx_spi.h
 * Description  : at32f4xx SPI header file
 * Date         : 2018-10-08
 * Version      : V1.0.5
 **************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F4xx_SPI_H
#define __AT32F4xx_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup SPI
  * @{
  */

/** @defgroup SPI_Exported_Types
  * @{
  */

/**
  * @brief  SPI Init structure definition
  */

typedef struct
{
    uint16_t SPI_TransMode;                 /*!< Specifies the SPI unidirectional or bidirectional data mode.
                                               This parameter can be a value of @ref SPI_data_direction */
                                            
    uint16_t SPI_Mode;                      /*!< Specifies the SPI operating mode.
                                               This parameter can be a value of @ref SPI_mode */
                                            
    uint16_t SPI_FrameSize;                 /*!< Specifies the SPI data size.
                                               This parameter can be a value of @ref SPI_data_size */
                                            
    uint16_t SPI_CPOL;                      /*!< Specifies the serial clock steady state.
                                               This parameter can be a value of @ref SPI_Clock_Polarity */
                                            
    uint16_t SPI_CPHA;                      /*!< Specifies the clock active edge for the bit capture.
                                               This parameter can be a value of @ref SPI_Clock_Phase */
                                            
    uint16_t SPI_NSSSEL;                    /*!< Specifies whether the NSSSEL signal is managed by
                                               hardware (NSSSEL pin) or by software using the SSI bit.
                                               This parameter can be a value of @ref SPI_Slave_Select_management */
                                            
    uint16_t SPI_MCLKP;                     /*!< Specifies the Baud Rate prescaler value which will be
                                                used to configure the transmit and receive SCK clock.
                                                This parameter can be a value of @ref SPI_BaudRate_Prescaler.
                                                @note The communication clock is derived from the master
                                                      clock. The slave clock does not need to be set. */
                                            
    uint16_t SPI_FirstBit;                  /*!< Specifies whether data transfers start from MSB or LSB bit.
                                                This parameter can be a value of @ref SPI_MSB_LSB_transmission */
                                    
    uint16_t SPI_CPOLY;                     /*!<  Specifies the polynomial used for the CRC calculation. */
} SPI_InitType;                     
                                    
/**                                 
  * @brief  I2S Init structure defi nition
  */                                
                                    
typedef struct                      
{                                   
                                    
    uint16_t I2S_Mode;                      /*!<  Specifies the I2S operating mode.
                                               This parameter can be a value of @ref I2S_Mode */
                                    
    uint16_t I2s_AudioProtocol;             /*!< Specifies the standard used for the I2S communication.
                                                This parameter can be a value of @ref I2s_AudioProtocol */
                                    
    uint16_t I2S_FrameFormat;               /*! < Specifies the data format for the I2S communication.
                                              This parameter can be a value of @ref I2S_Data_Format */

    uint16_t I2S_MCLKOE;                    /*!< Specifies whether the I2S MCLK output is enabled or not.
                                                   This parameter can be a value of @ref I2S_MCLK_Output */

    uint32_t I2S_AudioFreq;                 /*!< Specifies the frequency selected for the I2S communication.
                                               This parameter can be a value of @ref I2S_Audio_Frequency */
                                            
    uint16_t I2S_CPOL;                      /*!< Specifies the idle state of the I2S clock.
                                               This parameter can be a value of @ref I2S_Clock_Polarity */
} I2S_InitType;

/**
  * @}
  */

/** @defgroup SPI_Exported_Constants
  * @{
  */

#if defined (AT32F413xx) || defined (AT32F415xx)
#define IS_SPI_ALL_PERIPH(PERIPH)           (((PERIPH) == SPI1) || \
                                             ((PERIPH) == SPI2))
#elif defined (AT32F403xx)
#define IS_SPI_ALL_PERIPH(PERIPH)           (((PERIPH) == SPI1) || \
                                             ((PERIPH) == SPI2) || \
                                             ((PERIPH) == SPI3) || \
                                             ((PERIPH) == SPI4))
#elif defined (AT32F403Axx) || defined (AT32F407xx)
#define IS_SPI_ALL_PERIPH(PERIPH)           (((PERIPH) == SPI1)    || \
                                             ((PERIPH) == SPI2)    || \
                                             ((PERIPH) == SPI3)    || \
                                             ((PERIPH) == SPI4)    || \
                                             ((PERIPH) == I2S2EXT) || \
                                             ((PERIPH) == I2S3EXT))
#endif

#if defined (AT32F413xx) || defined (AT32F415xx)
#define IS_SPI_I2S_PERIPH(PERIPH)           (((PERIPH) == SPI1) || \
                                             ((PERIPH) == SPI2))
#elif defined (AT32F403xx)
#define IS_SPI_I2S_PERIPH(PERIPH)           (((PERIPH) == SPI1) || \
                                             ((PERIPH) == SPI2) || \
                                             ((PERIPH) == SPI3) || \
                                             ((PERIPH) == SPI4))
#elif defined (AT32F403Axx) || defined (AT32F407xx)
#define IS_SPI_I2S_PERIPH(PERIPH)           (((PERIPH) == SPI1)    || \
                                             ((PERIPH) == SPI2)    || \
                                             ((PERIPH) == SPI3)    || \
                                             ((PERIPH) == SPI4)    || \
                                             ((PERIPH) == I2S2EXT) || \
                                             ((PERIPH) == I2S3EXT))
#endif

/** @defgroup SPI_data_direction
  * @{
  */

#define SPI_TRANSMODE_FULLDUPLEX            ((uint16_t)0x0000)
#define SPI_TRANSMODE_RXONLY                ((uint16_t)0x0400)
#define SPI_TRANSMODE_RX_HALFDUPLEX         ((uint16_t)0x8000)
#define SPI_TRANSMODE_TX_HALFDUPLEX         ((uint16_t)0xC000)
#define IS_SPI_TRANS_MODE(MODE)             (((MODE) == SPI_TRANSMODE_FULLDUPLEX) || \
                                             ((MODE) == SPI_TRANSMODE_RXONLY) || \
                                             ((MODE) == SPI_TRANSMODE_RX_HALFDUPLEX) || \
                                             ((MODE) == SPI_TRANSMODE_TX_HALFDUPLEX))
/**
  * @}
  */

/** @defgroup SPI_mode
  * @{
  */

#define SPI_MODE_MASTER                     ((uint16_t)0x0104)
#define SPI_MODE_SLAVE                      ((uint16_t)0x0000)
#define IS_SPI_MODE(MODE)                   (((MODE) == SPI_MODE_MASTER) || \
                                             ((MODE) == SPI_MODE_SLAVE))
/**
  * @}
  */

/** @defgroup SPI_data_size
  * @{
  */

#define SPI_FRAMESIZE_16BIT                 ((uint16_t)0x0800)
#define SPI_FRAMESIZE_8BIT                  ((uint16_t)0x0000)
#define IS_SPI_FRAMESIZE(FRAMESIZE)         (((FRAMESIZE) == SPI_FRAMESIZE_16BIT) || \
                                             ((FRAMESIZE) == SPI_FRAMESIZE_8BIT))
/**
  * @}
  */

/** @defgroup SPI_Clock_Polarity
  * @{
  */

#define SPI_CPOL_LOW                        ((uint16_t)0x0000)
#define SPI_CPOL_HIGH                       ((uint16_t)0x0002)
#define IS_SPI_CPOL(CPOL)                   (((CPOL) == SPI_CPOL_LOW) || \
                                             ((CPOL) == SPI_CPOL_HIGH))
/**
  * @}
  */

/** @defgroup SPI_Clock_Phase
  * @{
  */

#define SPI_CPHA_1EDGE                      ((uint16_t)0x0000)
#define SPI_CPHA_2EDGE                      ((uint16_t)0x0001)
#define IS_SPI_CPHA(CPHA)                   (((CPHA) == SPI_CPHA_1EDGE) || \
                                             ((CPHA) == SPI_CPHA_2EDGE))
/**
  * @}
  */

/** @defgroup SPI_Slave_Select_management
  * @{
  */

#define SPI_NSSSEL_SOFT                     ((uint16_t)0x0200)
#define SPI_NSSSEL_HARD                     ((uint16_t)0x0000)
#define IS_SPI_NSSSEL(NSSSEL)               (((NSSSEL) == SPI_NSSSEL_SOFT) || \
                                             ((NSSSEL) == SPI_NSSSEL_HARD))
/**
  * @}
  */

/** @defgroup SPI_BaudRate_Prescaler
  * @{
  */


#define SPI_MCLKP_OVER_256                  ((uint16_t)0x8000)
                                            
#define SPI_MCLKP_2                         ((uint16_t)0x0000)
#define SPI_MCLKP_4                         ((uint16_t)0x0008)
#define SPI_MCLKP_8                         ((uint16_t)0x0010)
#define SPI_MCLKP_16                        ((uint16_t)0x0018)
#define SPI_MCLKP_32                        ((uint16_t)0x0020)
#define SPI_MCLKP_64                        ((uint16_t)0x0028)
#define SPI_MCLKP_128                       ((uint16_t)0x0030)
#define SPI_MCLKP_256                       ((uint16_t)0x0038)
#define SPI_MCLKP_512                       ((uint16_t)0x8000)
#define SPI_MCLKP_1024                      ((uint16_t)0x8008)
#define IS_SPI_MCLKP(MCLKP)                 (((MCLKP) == SPI_MCLKP_2) || \
                                             ((MCLKP) == SPI_MCLKP_4) || \
                                             ((MCLKP) == SPI_MCLKP_8) || \
                                             ((MCLKP) == SPI_MCLKP_16) || \
                                             ((MCLKP) == SPI_MCLKP_32) || \
                                             ((MCLKP) == SPI_MCLKP_64) || \
                                             ((MCLKP) == SPI_MCLKP_128) || \
                                             ((MCLKP) == SPI_MCLKP_256) || \
                                             ((MCLKP) == SPI_MCLKP_512) || \
                                             ((MCLKP) == SPI_MCLKP_1024))
/**
  * @}
  */

/** @defgroup SPI_MSB_LSB_transmission
  * @{
  */

#define SPI_FIRSTBIT_MSB                    ((uint16_t)0x0000)
#define SPI_FIRSTBIT_LSB                    ((uint16_t)0x0080)
#define IS_SPI_FIRST_BIT(BIT)               (((BIT) == SPI_FIRSTBIT_MSB) || \
                                             ((BIT) == SPI_FIRSTBIT_LSB))
/**
  * @}
  */

/** @defgroup I2S_Mode
  * @{
  */

#define I2S_MODE_SLAVETX                    ((uint16_t)0x0000)
#define I2S_MODE_SLAVERX                    ((uint16_t)0x0100)
#define I2S_MODE_MASTERTX                   ((uint16_t)0x0200)
#define I2S_MODE_MASTERRX                   ((uint16_t)0x0300)
#define IS_I2S_MODE(MODE)                   (((MODE) == I2S_MODE_SLAVETX) || \
                                             ((MODE) == I2S_MODE_SLAVERX) || \
                                             ((MODE) == I2S_MODE_MASTERTX) || \
                                             ((MODE) == I2S_MODE_MASTERRX) )
/**
  * @}
  */

/** @defgroup I2S_AUDIOPROTOCOL
  * @{
  */

#define I2S_AUDIOPROTOCOL_PHILLIPS                  ((uint16_t)0x0000)
#define I2S_AUDIOPROTOCOL_MSB                       ((uint16_t)0x0010)
#define I2S_AUDIOPROTOCOL_LSB                       ((uint16_t)0x0020)
#define I2S_AUDIOPROTOCOL_PCMSHORT                  ((uint16_t)0x0030)
#define I2S_AUDIOPROTOCOL_PCMLONG                   ((uint16_t)0x00B0)
#define IS_I2S_AUDIOPROTOCOL(AUDIOPROTOCOL)         (((AUDIOPROTOCOL) == I2S_AUDIOPROTOCOL_PHILLIPS) || \
                                                     ((AUDIOPROTOCOL) == I2S_AUDIOPROTOCOL_MSB) || \
                                                     ((AUDIOPROTOCOL) == I2S_AUDIOPROTOCOL_LSB) || \
                                                     ((AUDIOPROTOCOL) == I2S_AUDIOPROTOCOL_PCMSHORT) || \
                                                     ((AUDIOPROTOCOL) == I2S_AUDIOPROTOCOL_PCMLONG))
/**
  * @}
  */

/** @defgroup I2S_Data_Format
  * @{
  */

#define I2S_FRAMEFORMAT_DL16BIT_CHL16BIT    ((uint16_t)0x0000)
#define I2S_FRAMEFORMAT_DL16BIT_CHL32BIT    ((uint16_t)0x0001)
#define I2S_FRAMEFORMAT_DL24BIT_CHL32BIT    ((uint16_t)0x0003)
#define I2S_FRAMEFORMAT_DL32BIT_CHL32BIT    ((uint16_t)0x0005)
#define IS_I2S_FRAMEFORMAT(FRAMEFORMAT)     (((FRAMEFORMAT) == I2S_FRAMEFORMAT_DL16BIT_CHL16BIT) || \
                                             ((FRAMEFORMAT) == I2S_FRAMEFORMAT_DL16BIT_CHL32BIT) || \
                                             ((FRAMEFORMAT) == I2S_FRAMEFORMAT_DL24BIT_CHL32BIT) || \
                                             ((FRAMEFORMAT) == I2S_FRAMEFORMAT_DL32BIT_CHL32BIT))
/**
  * @}
  */

/** @defgroup I2S_MCLK_Output
  * @{
  */

#define I2S_MCLKOE_ENABLE                   ((uint16_t)0x0200)
#define I2S_MCLKOE_DISABLE                  ((uint16_t)0x0000)
#define IS_I2S_MCLKOE(MCLKOE)               (((MCLKOE) == I2S_MCLKOE_ENABLE) || \
                                             ((MCLKOE) == I2S_MCLKOE_DISABLE))
/**
  * @}
  */
  
#define I2S_DIV_VALUE_MAX                   ((uint16_t)0x03FF)
#define I2S_DIV_EXT_VALUE_MASK              ((uint16_t)0x0300)
#define I2S_DIV_EXT_VALUE_LSHIFT_OFFSET     ((uint16_t)2)

/** @defgroup I2S_Audio_Frequency
  * @{
  */

#define I2S_AUDIOFREQ_192K                  ((uint32_t)192000)
#define I2S_AUDIOFREQ_96K                   ((uint32_t)96000)
#define I2S_AUDIOFREQ_48K                   ((uint32_t)48000)
#define I2S_AUDIOFREQ_44K                   ((uint32_t)44100)
#define I2S_AUDIOFREQ_32K                   ((uint32_t)32000)
#define I2S_AUDIOFREQ_22K                   ((uint32_t)22050)
#define I2S_AUDIOFREQ_16K                   ((uint32_t)16000)
#define I2S_AUDIOFREQ_11K                   ((uint32_t)11025)
#define I2S_AUDIOFREQ_8K                    ((uint32_t)8000)
#define I2S_AUDIOFREQ_DEFAULT               ((uint32_t)2)

#define IS_I2S_AUDIO_FREQ(FREQ)             ((((FREQ) >= I2S_AUDIOFREQ_8K) && \
                                             ((FREQ) <= I2S_AUDIOFREQ_192K)) || \
                                             ((FREQ) == I2S_AUDIOFREQ_DEFAULT))
/**
  * @}
  */

/** @defgroup I2S_Clock_Polarity
  * @{
  */

#define I2S_CPOL_LOW                        ((uint16_t)0x0000)
#define I2S_CPOL_HIGH                       ((uint16_t)0x0008)
#define IS_I2S_CPOL(CPOL)                   (((CPOL) == I2S_CPOL_LOW) || \
                                             ((CPOL) == I2S_CPOL_HIGH))
/**
  * @}
  */

/** @defgroup SPI_I2S_DMA_transfer_requests
  * @{
  */

#define SPI_I2S_DMA_TX                      ((uint16_t)0x0002)
#define SPI_I2S_DMA_RX                      ((uint16_t)0x0001)
#define IS_SPI_I2S_DMA(DMA)                 ((((DMA) & (uint16_t)0xFFFC) == 0x00) && ((DMA) != 0x00))
/**
  * @}
  */

/** @defgroup SPI_NSS_internal_software_management
  * @{
  */

#define SPI_ISS_SET                         ((uint16_t)0x0100)
#define SPI_ISS_RESET                       ((uint16_t)0xFEFF)
#define IS_SPI_ISS(ISS)                     (((ISS) == SPI_ISS_SET) || \
                                             ((ISS) == SPI_ISS_RESET))
/**
  * @}
  */

/** @defgroup SPI_CRC_Transmit_Receive
  * @{
  */

#define SPI_CRC_TX                          ((uint8_t)0x00)
#define SPI_CRC_RX                          ((uint8_t)0x01)
#define IS_SPI_CRC(CRC)                     (((CRC) == SPI_CRC_TX) || ((CRC) == SPI_CRC_RX))
/**
  * @}
  */

/** @defgroup SPI_direction_transmit_receive
  * @{
  */

#define SPI_HALFDUPLEX_RX                   ((uint16_t)0xBFFF)
#define SPI_HALFDUPLEX_TX                   ((uint16_t)0x4000)
#define IS_SPI_DIRECTION(DIRECTION)         (((DIRECTION) == SPI_HALFDUPLEX_RX) || \
                                             ((DIRECTION) == SPI_HALFDUPLEX_TX))
/**
  * @}
  */

/** @defgroup SPI_I2S_interrupts_definition
  * @{
  */

#define SPI_I2S_INT_TE                      ((uint8_t)0x71)
#define SPI_I2S_INT_RNE                     ((uint8_t)0x60)
#define SPI_I2S_INT_ERR                     ((uint8_t)0x50)
#define IS_SPI_I2S_CONFIG_INT(INT)          (((INT) == SPI_I2S_INT_TE) || \
                                             ((INT) == SPI_I2S_INT_RNE) || \
                                             ((INT) == SPI_I2S_INT_ERR))
#define SPI_I2S_INT_OVR                     ((uint8_t)0x56)
#define SPI_INT_MODF                        ((uint8_t)0x55)
#define SPI_INT_CERR                        ((uint8_t)0x54)
#define I2S_INT_UDR                         ((uint8_t)0x53)
#define IS_SPI_I2S_CLEAR_INT(INT)           (((INT) == SPI_INT_CERR))
#define IS_SPI_I2S_GET_INT(INT)             (((INT) == SPI_I2S_INT_RNE) || ((INT) == SPI_I2S_INT_TE) || \
                                             ((INT) == I2S_INT_UDR)     || ((INT) == SPI_INT_CERR) || \
                                             ((INT) == SPI_INT_MODF)    || ((INT) == SPI_I2S_INT_OVR))
/**
  * @}
  */

/** @defgroup SPI_I2S_flags_definition
  * @{
  */

#define SPI_I2S_FLAG_RNE                    ((uint16_t)0x0001)
#define SPI_I2S_FLAG_TE                     ((uint16_t)0x0002)
#define I2S_FLAG_CS                         ((uint16_t)0x0004)
#define I2S_FLAG_UDR                        ((uint16_t)0x0008)
#define SPI_FLAG_CERR                       ((uint16_t)0x0010)
#define SPI_FLAG_MODF                       ((uint16_t)0x0020)
#define SPI_I2S_FLAG_OVR                    ((uint16_t)0x0040)
#define SPI_I2S_FLAG_BUSY                   ((uint16_t)0x0080)
#define IS_SPI_I2S_CLEAR_FLAG(FLAG)         (((FLAG) == SPI_FLAG_CERR))
#define IS_SPI_I2S_GET_FLAG(FLAG)           (((FLAG) == SPI_I2S_FLAG_BUSY) || ((FLAG) == SPI_I2S_FLAG_OVR) || \
                                             ((FLAG) == SPI_FLAG_MODF)     || ((FLAG) == SPI_FLAG_CERR) || \
                                             ((FLAG) == I2S_FLAG_UDR)      || ((FLAG) == I2S_FLAG_CS) || \
                                             ((FLAG) == SPI_I2S_FLAG_TE)   || ((FLAG) == SPI_I2S_FLAG_RNE))
/**
  * @}
  */

/** @defgroup SPI_CRC_polynomial
  * @{
  */

#define IS_SPI_CPOLY(CPOLY)                 ((CPOLY) >= 0x1)
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup SPI_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup SPI_Exported_Functions
  * @{
  */

void SPI_I2S_Reset(SPI_Type* SPIx);
void SPI_Init(SPI_Type* SPIx, SPI_InitType* SPI_InitStruct);
void I2S_Init(SPI_Type* SPIx, I2S_InitType* I2S_InitStruct);
void SPI_DefaultInitParaConfig(SPI_InitType* SPI_InitStruct);
void I2S_DefaultInit(I2S_InitType* I2S_InitStruct);
void SPI_Enable(SPI_Type* SPIx, FunctionalState NewState);
void I2S_Enable(SPI_Type* SPIx, FunctionalState NewState);
void SPI_I2S_INTConfig(SPI_Type* SPIx, uint8_t SPI_I2S_INT, FunctionalState NewState);
void SPI_I2S_DMAEnable(SPI_Type* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState);
void SPI_I2S_TxData(SPI_Type* SPIx, uint16_t Data);
uint16_t SPI_I2S_RxData(SPI_Type* SPIx);
void SPI_NSSInternalSoftwareConfig(SPI_Type* SPIx, uint16_t SPI_NSSInternalSoft);
void SPI_NSSHardwareOutputEnable(SPI_Type* SPIx, FunctionalState NewState);
void SPI_FrameSizeConfig(SPI_Type* SPIx, uint16_t SPI_DataSize);
void SPI_TxCRC(SPI_Type* SPIx);
void SPI_CRCEN(SPI_Type* SPIx, FunctionalState NewState);
uint16_t SPI_GetCRC(SPI_Type* SPIx, uint8_t SPI_CRC);
uint16_t SPI_GetCRCPolynomial(SPI_Type* SPIx);
void SPI_HalfDuplexTransModeConfig(SPI_Type* SPIx, uint16_t SPI_Direction);
FlagStatus SPI_I2S_GetFlagStatus(SPI_Type* SPIx, uint16_t SPI_I2S_FLAG);
void SPI_I2S_ClearFlag(SPI_Type* SPIx, uint16_t SPI_I2S_FLAG);
ITStatus SPI_I2S_GetITStatus(SPI_Type* SPIx, uint8_t SPI_I2S_INT);
void SPI_I2S_ClearINTPendingBit(SPI_Type* SPIx, uint8_t SPI_I2S_INT);

#ifdef __cplusplus
}
#endif

#endif /*__AT32F4xx_SPI_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


