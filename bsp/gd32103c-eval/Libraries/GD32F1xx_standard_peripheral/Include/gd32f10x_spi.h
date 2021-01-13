/**
  ******************************************************************************
  * @brief   SPI header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F10X_SPI_H
#define __GD32F10X_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @addtogroup SPI
  * @{
  */

/** @defgroup SPI_Exported_Types
  * @{
  */

/**
  * @brief  SPI Initial Parameters
  */
typedef struct {
    uint16_t SPI_TransType;           /*!< The transfer type, choose one from @ref SPI_transfer_type. */
    uint16_t SPI_Mode;                /*!< The operating mode, choose one from @ref SPI_mode. */
    uint16_t SPI_FrameFormat;         /*!< The SPI data frame format, choose one from @ref SPI_data_frame_format. */
    uint16_t SPI_SCKPL;               /*!< The clock polarity in idel state, choose one from @ref SPI_Clock_Polarity. */
    uint16_t SPI_SCKPH;               /*!< The clock phase, choose one from @ref SPI_Clock_Phase. */
    uint16_t SPI_SWNSSEN;             /*!< The NSS signal management, choose one from @ref SPI_Software_NSS_management. */
    uint16_t SPI_PSC;                 /*!< The Baud Rate prescaler value, choose one from @ref SPI_BaudRate_Prescaler. */
    uint16_t SPI_FirstBit;            /*!< The data transfers start from MSB or LSB bit, choose one from @ref SPI_MSB_LSB_transmission. */
    uint16_t SPI_CRCPOL;              /*!< The polynomial used for the CRC calculation. */
} SPI_InitPara;

/**
  * @brief  I2S Initial Parameters
  */
typedef struct {
    uint16_t I2S_Mode;                /*!< The operating mode and transfer direction, choose one from @ref I2S_Mode. */
    uint16_t I2S_STD;                 /*!< The I2S standard, choose one from @ref I2S_Standard. */
    uint16_t I2S_FrameFormat;         /*!< The I2S data length and channel length, choose one from @ref I2S_Data_Format. */
    uint16_t I2S_MCKOE;               /*!< The I2S MCK output is enabled or disable, choose one from @ref I2S_MCLK_Output. */
    uint32_t I2S_AudioFreq;           /*!< The audio sampling frequency, choose one from @ref I2S_Audio_Frequency. */
    uint16_t I2S_CKPL;                /*!< The clock polarity in idel state, choose one from @ref I2S_Clock_Polarity. */
} I2S_InitPara;

/**
  * @}
  */

/** @defgroup SPI_Exported_Constants
  * @{
  */

/** @defgroup SPI_transfer_type
  * @{
  */
#define SPI_TRANSTYPE_FULLDUPLEX         ((uint16_t)0x0000)
#define SPI_TRANSTYPE_RXONLY             SPI_CTLR1_RO
#define SPI_TRANSTYPE_BDMRX              SPI_CTLR1_BDM
#define SPI_TRANSTYPE_BDMTX              (SPI_CTLR1_BDM | SPI_CTLR1_BDOE)

/**
  * @}
  */

/** @defgroup SPI_mode
  * @{
  */
#define SPI_MODE_MASTER                 (SPI_CTLR1_MSTMODE|SPI_CTLR1_SWNSS)
#define SPI_MODE_SLAVE                  ((uint16_t)0x0000)

/**
  * @}
  */

/** @defgroup SPI_data_frame_format
  * @{
  */
#define SPI_FRAMEFORMAT_16BIT           SPI_CTLR1_FF16
#define SPI_FRAMEFORMAT_8BIT            ((uint16_t)0x0000)

/**
  * @}
  */

/** @defgroup SPI_Clock_Polarity
  * @{
  */
#define SPI_SCKPL_LOW                   ((uint16_t)0x0000)
#define SPI_SCKPL_HIGH                  SPI_CTLR1_SCKPL

/**
  * @}
  */

/** @defgroup SPI_Clock_Phase
  * @{
  */
#define SPI_SCKPH_1EDGE                 ((uint16_t)0x0000)
#define SPI_SCKPH_2EDGE                 SPI_CTLR1_SCKPH

/**
  * @}
  */

/** @defgroup SPI_Software_NSS_management
  * @{
  */
#define SPI_SWNSS_SOFT                  SPI_CTLR1_SWNSSEN
#define SPI_SWNSS_HARD                  ((uint16_t)0x0000)

/**
  * @}
  */

/** @defgroup SPI_BaudRate_Prescaler
  * @{
  */
#define SPI_PSC_2                       ((uint16_t)0x0000)
#define SPI_PSC_4                       ((uint16_t)0x0008)
#define SPI_PSC_8                       ((uint16_t)0x0010)
#define SPI_PSC_16                      ((uint16_t)0x0018)
#define SPI_PSC_32                      ((uint16_t)0x0020)
#define SPI_PSC_64                      ((uint16_t)0x0028)
#define SPI_PSC_128                     ((uint16_t)0x0030)
#define SPI_PSC_256                     ((uint16_t)0x0038)

/**
  * @}
  */

/** @defgroup SPI_MSB_LSB_transmission
  * @{
  */
#define SPI_FIRSTBIT_MSB                ((uint16_t)0x0000)
#define SPI_FIRSTBIT_LSB                SPI_CTLR1_LF

/**
  * @}
  */

/** @defgroup I2S_Mode
  * @{
  */
#define I2S_MODE_SLAVETX                ((uint16_t)0x0000)
#define I2S_MODE_SLAVERX                ((uint16_t)0x0100)
#define I2S_MODE_MASTERTX               ((uint16_t)0x0200)
#define I2S_MODE_MASTERRX               ((uint16_t)0x0300)

/**
  * @}
  */

/** @defgroup I2S_Standard
  * @{
  */
#define I2S_STD_PHILLIPS                ((uint16_t)0x0000)
#define I2S_STD_MSB                     ((uint16_t)0x0010)
#define I2S_STD_LSB                     ((uint16_t)0x0020)
#define I2S_STD_PCMSHORT                ((uint16_t)0x0030)
#define I2S_STD_PCMLONG                 ((uint16_t)0x00B0)

/**
  * @}
  */

/** @defgroup I2S_Data_Format
  * @{
  */
#define I2S_FRAMEFORMAT_DL16b_CL16b     ((uint16_t)0x0000)
#define I2S_FRAMEFORMAT_DL16b_CL32b     ((uint16_t)0x0001)
#define I2S_FRAMEFORMAT_DL24b_CL32b     ((uint16_t)0x0003)
#define I2S_FRAMEFORMAT_DL32b_CL32b     ((uint16_t)0x0005)

/**
  * @}
  */

/** @defgroup I2S_MCLK_Output
  * @{
  */
#define I2S_MCK_ENABLE                  SPI_I2SCKP_MCKOE
#define I2S_MCK_DISABLE                 ((uint16_t)0x0000)

/**
  * @}
  */

/** @defgroup I2S_Audio_Frequency
  * @{
  */
#define I2S_AUDIOFREQ_DEFAULT           ((uint32_t)2)
#define I2S_AUDIOFREQ_8K                ((uint32_t)8000)
#define I2S_AUDIOFREQ_11K               ((uint32_t)11025)
#define I2S_AUDIOFREQ_16K               ((uint32_t)16000)
#define I2S_AUDIOFREQ_22K               ((uint32_t)22050)
#define I2S_AUDIOFREQ_32K               ((uint32_t)32000)
#define I2S_AUDIOFREQ_44K               ((uint32_t)44100)
#define I2S_AUDIOFREQ_48K               ((uint32_t)48000)
#define I2S_AUDIOFREQ_96K               ((uint32_t)96000)
#define I2S_AUDIOFREQ_192K              ((uint32_t)192000)

/**
  * @}
  */

/** @defgroup I2S_Clock_Polarity
  * @{
  */
#define I2S_CKPL_LOW                    ((uint16_t)0x0000)
#define I2S_CKPL_HIGH                   SPI_I2SCTLR_CKPL

/**
  * @}
  */

/** @defgroup SPI_I2S_DMA_transfer_requests
  * @{
  */
#define SPI_I2S_DMA_TX                   SPI_CTLR2_DMATE
#define SPI_I2S_DMA_RX                   SPI_CTLR2_DMARE

/**
  * @}
  */

/** @defgroup SPI_NSS_internal_software_management
  * @{
  */
#define SPI_SWNSS_SET                   ((uint16_t)0x0001)
#define SPI_SWNSS_RESET                 ((uint16_t)0x0000)

/**
  * @}
  */

/** @defgroup SPI_CRC_Transmit_Receive
  * @{
  */
#define SPI_CRC_TX                      ((uint8_t)0x00)
#define SPI_CRC_RX                      ((uint8_t)0x01)

/**
  * @}
  */

/** @defgroup SPI_direction_transmit_receive
  * @{
  */
#define SPI_BDOE_RX                     (~SPI_CTLR1_BDOE)
#define SPI_BDOE_TX                     SPI_CTLR1_BDOE

/**
  * @}
  */

/** @defgroup SPI_I2S_interrupts_definition
  * @{
  */
#define SPI_I2S_INT_TBE                 ((uint8_t)0x71)
#define SPI_I2S_INT_RBNE                ((uint8_t)0x60)
#define SPI_I2S_INT_ERR                 ((uint8_t)0x50)
#define SPI_I2S_INT_OVR                 ((uint8_t)0x56)
#define SPI_INT_MODF                    ((uint8_t)0x55)
#define SPI_INT_CRCERR                  ((uint8_t)0x54)
#define I2S_INT_UDR                     ((uint8_t)0x53)

/**
  * @}
  */

/** @defgroup SPI_I2S_flags_definition
  * @{
  */
#define SPI_FLAG_RBNE                   SPI_STR_RBNE
#define SPI_FLAG_TBE                    SPI_STR_TBE
#define SPI_FLAG_CRCERR                 SPI_STR_CRCE
#define SPI_FLAG_MODF                   SPI_STR_CONFE
#define SPI_FLAG_OVR                    SPI_STR_RXORE
#define SPI_FLAG_BSY                    SPI_STR_TRANS

#define I2S_FLAG_RBNE                   SPI_STR_RBNE
#define I2S_FLAG_TBE                    SPI_STR_TBE
#define I2S_FLAG_CHSIDE                 SPI_STR_I2SCH
#define I2S_FLAG_UDR                    SPI_STR_TXURE
#define I2S_FLAG_OVR                    SPI_STR_RXORE
#define I2S_FLAG_BSY                    SPI_STR_TRANS

/**
  * @}
  */

/**
  * @}
  */


/** @defgroup SPI_Exported_Functions
  * @{
  */
void SPI_I2S_DeInit(SPI_TypeDef *SPIx);
void SPI_Init(SPI_TypeDef *SPIx, SPI_InitPara *SPI_InitParameter);
void I2S_Init(SPI_TypeDef *SPIx, I2S_InitPara *I2S_InitParameter);
void SPI_ParaInit(SPI_InitPara *SPI_InitParameter);
void I2S_ParaInit(I2S_InitPara *I2S_InitParameter);
void SPI_Enable(SPI_TypeDef *SPIx, TypeState NewValue);
void I2S_Enable(SPI_TypeDef *SPIx, TypeState NewValue);
void SPI_I2S_INTConfig(SPI_TypeDef *SPIx, uint8_t SPI_I2S_INT, TypeState NewValue);
void SPI_I2S_DMA_Enable(SPI_TypeDef *SPIx, uint16_t SPI_I2S_DMAReq, TypeState NewValue);
void SPI_I2S_SendData(SPI_TypeDef *SPIx, uint16_t Data);
uint16_t SPI_I2S_ReceiveData(SPI_TypeDef *SPIx);
void SPI_SWNSSConfig(SPI_TypeDef *SPIx, uint16_t SPI_SWNSS);
void SPI_NSSDRV(SPI_TypeDef *SPIx, TypeState NewValue);
void SPI_FrameFormatConfig(SPI_TypeDef *SPIx, uint16_t SPI_DataSize);
void SPI_SendCRCNext(SPI_TypeDef *SPIx);
void SPI_CRC_Enable(SPI_TypeDef *SPIx, TypeState NewValue);
uint16_t SPI_GetCRC(SPI_TypeDef *SPIx, uint8_t SPI_CRC);
uint16_t SPI_GetCRCPolynomial(SPI_TypeDef *SPIx);
void SPI_BDOEConfig(SPI_TypeDef *SPIx, uint16_t SPI_BDOE);
TypeState SPI_I2S_GetBitState(SPI_TypeDef *SPIx, uint16_t SPI_I2S_FLAG);
void SPI_I2S_ClearBitState(SPI_TypeDef *SPIx, uint16_t SPI_I2S_FLAG);
TypeState SPI_I2S_GetIntBitState(SPI_TypeDef *SPIx, uint8_t SPI_I2S_INT);
void SPI_I2S_ClearIntBitState(SPI_TypeDef *SPIx, uint8_t SPI_I2S_INT);

#ifdef __cplusplus
}
#endif

#endif /*__GD32F10X_SPI_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

