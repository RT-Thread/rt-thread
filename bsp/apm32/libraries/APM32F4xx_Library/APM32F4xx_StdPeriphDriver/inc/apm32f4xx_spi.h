/*!
 * @file        apm32f4x_spi.h
 *
 * @brief       This file contains all the functions prototypes for the SPI firmware library
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __APM32F4XX_SPI_H
#define __APM32F4XX_SPI_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "apm32f4xx.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @addtogroup SPI_Driver
  @{
*/

/** @defgroup SPI_Enumerations
  @{
*/

/**
 * @brief   SPI data direction mode
 *
 * @note    BIT0 refer to 1 line or 2 lines
 *          BIT4 refer to Tx or Rx in 1 line
 *          BIT8 refer to receive only or full-duplex in 2 lines
 */
typedef enum
{
    SPI_DIRECTION_2LINES_FULLDUPLEX = 0x0000,   /*!< 2 lines full duplex */
    SPI_DIRECTION_2LINES_RXONLY     = 0x0100,   /*!< 2 lines but receive only */
    SPI_DIRECTION_1LINE_RX          = 0x0001,   /*!< 1 line receive only */
    SPI_DIRECTION_1LINE_TX          = 0x0011    /*!< 1 line send only */
} SPI_DIRECTION_T;

/**
 * @brief SPI mode
 */
typedef enum
{
    SPI_MODE_SLAVE,     /*!< Slave mode */
    SPI_MODE_MASTER     /*!< Master mode */
} SPI_MODE_T;

/**
 * @brief SPI Data length
 */
typedef enum
{
    SPI_DATA_LENGTH_8B, /*!< Set data frame format to 8bit */
    SPI_DATA_LENGTH_16B /*!< Set data frame format to 16bit */
} SPI_DATA_LENGTH_T;

/**
 * @brief SPI Clock Polarity
 */
typedef enum
{
    SPI_CLKPOL_LOW,     /*!< Set SCK polarity to low in idle state */
    SPI_CLKPOL_HIGH     /*!< Set SCK polarity to high in idle state */
} SPI_CLKPOL_T;

/**
 * @brief SPI Clock Phase
 */
typedef enum
{
    SPI_CLKPHA_1EDGE,   /*!< Sample value in the first clock edge */
    SPI_CLKPHA_2EDGE    /*!< Sample value in the second clock edge */
} SPI_CLKPHA_T;

/**
 * @brief SPI Slave Select management
 */
typedef enum
{
    SPI_NSS_HARD,   /*!< Disable software NSS mode */
    SPI_NSS_SOFT    /*!< Enable software NSS mode */
} SPI_NSS_T;

/**
 * @brief SPI BaudRate Prescaler
 */
typedef enum
{
    SPI_BAUDRATE_DIV_2,     /*!< BaudRate DIV = 2 */
    SPI_BAUDRATE_DIV_4,     /*!< BaudRate DIV = 4 */
    SPI_BAUDRATE_DIV_8,     /*!< BaudRate DIV = 8 */
    SPI_BAUDRATE_DIV_16,    /*!< BaudRate DIV = 16 */
    SPI_BAUDRATE_DIV_32,    /*!< BaudRate DIV = 32 */
    SPI_BAUDRATE_DIV_64,    /*!< BaudRate DIV = 64 */
    SPI_BAUDRATE_DIV_128,   /*!< BaudRate DIV = 128 */
    SPI_BAUDRATE_DIV_256,   /*!< BaudRate DIV = 256 */
} SPI_BAUDRATE_DIV_T;

/**
 * @brief SPI MSB LSB transmission
 */
typedef enum
{
    SPI_FIRSTBIT_MSB,   /*!< MSB first */
    SPI_FIRSTBIT_LSB    /*!< LSB first */
} SPI_FIRSTBIT_T;

/**
 * @brief I2S Mode
 */
typedef enum
{
    I2S_MODE_SLAVE_TX,  /*!< Slave transmit mode */
    I2S_MODE_SLAVE_RX,  /*!< Slave receive mode */
    I2S_MODE_MASTER_TX, /*!< Master transmit mode */
    I2S_MODE_MASTER_RX  /*!< Master receive mode */
} I2S_MODE_T;

/**
 * @brief I2S Standard
 */
typedef enum
{
    I2S_STANDARD_PHILLIPS = 0x00,   /*!< I2S phillips mode */
    I2S_STANDARD_MSB      = 0x01,   /*!< MSB alignment mode */
    I2S_STANDARD_LSB      = 0x02,   /*!< LSB alignment mode */
    I2S_STANDARD_PCMSHORT = 0x03,   /*!< PCB short frame synchronization mode */
    I2S_STANDARD_PCMLONG  = 0x13    /*!< PCB long frame synchronization mode */
} I2S_STANDARD_T;

/**
 * @brief I2S data length
 */
typedef enum
{
    I2S_DATA_LENGHT_16B   = 0x00,   /*!< Set the length of data to 16-bit */
    I2S_DATA_LENGHT_16BEX = 0x01,   /*!< Set the length of data to 16-bit extended */
    I2S_DATA_LENGHT_24B   = 0x03,   /*!< Set the length of data to 24-bit */
    I2S_DATA_LENGHT_32B   = 0x05,   /*!< Set the length of data to 32-bit */
} I2S_DATA_LENGTH_T;

/**
 * @brief I2S MCLK Output
 */
typedef enum
{
    I2S_MCLK_OUTPUT_DISABLE,    /*!< Disable I2S MCLK output */
    I2S_MCLK_OUTPUT_ENABLE      /*!< Enable I2S MCLK output */
} I2S_MCLK_OUTPUT_T;

/**
 * @brief I2S Audio divider
 */
typedef enum
{
    I2S_AUDIO_DIV_192K    = 192000, /*!< Audio div = 192K */
    I2S_AUDIO_DIV_96K     = 96000,  /*!< Audio div = 96K */
    I2S_AUDIO_DIV_48K     = 48000,  /*!< Audio div = 48K */
    I2S_AUDIO_DIV_44K     = 44100,  /*!< Audio div = 44.1K */
    I2S_AUDIO_DIV_32K     = 32000,  /*!< Audio div = 32K */
    I2S_AUDIO_DIV_22K     = 22050,  /*!< Audio div = 22.05K */
    I2S_AUDIO_DIV_16K     = 16000,  /*!< Audio div = 16K */
    I2S_AUDIO_DIV_11K     = 11025,  /*!< Audio div = 11.025K */
    I2S_AUDIO_DIV_8K      = 8000,   /*!< Audio div = 8K */
    I2S_AUDIO_DIV_DEFAULT = 2       /*!< Audio div = 2 */
} I2S_AUDIO_DIV_T;

/**
 * @brief I2S Clock Polarity
 */
typedef enum
{
    I2S_CLKPOL_LOW,     /*!< Set clock polarity to low */
    I2S_CLKPOL_HIGH     /*!< Set clock polarity to high */
} I2S_CLKPOL_T;

/**
 * @brief SPI I2S DMA requests
 */
typedef enum
{
    SPI_I2S_DMA_REQ_TX, /*!< Tx buffer DMA transfer request */
    SPI_I2S_DMA_REQ_RX  /*!< Rx buffer DMA transfer request */
} SPI_I2S_DMA_REQ_T;

/**
 * @brief SPI Direction select
 */
typedef enum
{
    SPI_DIRECTION_RX,   /*!< Selects Rx receive direction */
    SPI_DIRECTION_TX    /*!< Selects Tx transmission direction */
} SPI_DIRECTION_SELECT_T;

/**
 * @brief    SPI interrupts definition
 */
typedef enum
{
    SPI_I2S_INT_TXBE  = 0x8002, /*!< Tx buffer empty interrupt */
    SPI_I2S_INT_RXBNE = 0x4001, /*!< Rx buffer not empty interrupt */
    SPI_I2S_INT_ERR   = 0x2000, /*!< Error interrupt */
    I2S_INT_UDR       = 0x2008, /*!< Underrun Error interrupt flag */
    SPI_INT_CRCE      = 0x2010, /*!< CRC Error interrupt flag */
    SPI_INT_ME        = 0x2020, /*!< Mode Error interrupt flag */
    SPI_I2S_INT_OVR   = 0x2040  /*!< Overrun interrupt flag */
} SPI_I2S_INT_T;

/**
 * @brief SPI flags definition
 */
typedef enum
{
    SPI_FLAG_RXBNE  = 0x0001,   /*!< Receive buffer not empty flag */
    SPI_FLAG_TXBE   = 0x0002,   /*!< Transmit buffer empty flag */
    I2S_FLAG_SCHDIR = 0x0004,   /*!< Side Channel flag */
    I2S_FLAG_UDR    = 0x0008,   /*!< Underrun Error flag */
    SPI_FLAG_CRCE   = 0x0010,   /*!< CRC Error flag */
    SPI_FLAG_ME     = 0x0020,   /*!< Mode Error flag */
    SPI_FLAG_OVR    = 0x0040,   /*!< Overrun flag */
    SPI_FLAG_BSY    = 0x0080    /*!< Busy flag */
} SPI_FLAG_T;

/**@} end of group SPI_Enumerations*/

/** @addtogroup SPI_Structure Data Structure
  @{
*/

/**
 * @brief SPI Config structure definition
 */
typedef struct
{
    SPI_MODE_T          mode;           /*!< SPI mode selection */
    SPI_DATA_LENGTH_T   length;         /*!< SPI data length selection */
    SPI_CLKPHA_T        phase;          /*!< SPI clock phase selection */
    SPI_CLKPOL_T        polarity;       /*!< SPI clock polarity selection */
    SPI_NSS_T           nss;            /*!< Set SPI software NSS */
    SPI_FIRSTBIT_T      firstBit;       /*!< Set first bit */
    SPI_DIRECTION_T     direction;      /*!< SPI data direction mode selection */
    SPI_BAUDRATE_DIV_T  baudrateDiv;    /*!< SPI BaudRate Prescaler selection */
    uint16_t            crcPolynomial;  /*!< Setup CRC polynomial value */
} SPI_Config_T;

/**
 * @brief I2S Config structure definition
 */
typedef struct
{
    I2S_MODE_T          mode;       /*!< I2S mode selection */
    I2S_STANDARD_T      standard;   /*!< I2S standard selection */
    I2S_DATA_LENGTH_T   length;     /*!< Set I2S data length */
    I2S_MCLK_OUTPUT_T   MCLKOutput; /*!< Set I2S MCLK output */
    I2S_AUDIO_DIV_T     audioDiv;   /*!< I2S Audio divider selection */
    I2S_CLKPOL_T        polarity;   /*!< I2S Clock polarity selection */
} I2S_Config_T;

/**@} end of group SPI_Structure*/

/** @defgroup SPI_Functions
  @{
*/

/* Reset */
void SPI_I2S_Reset(SPI_T* spi);

/* Initialization and Configuration */
void SPI_Config(SPI_T* spi, SPI_Config_T* spiConfig);
void I2S_Config(SPI_T* spi, I2S_Config_T* i2sConfig);
void SPI_ConfigStructInit(SPI_Config_T* spiConfig);
void I2S_ConfigStructInit(I2S_Config_T* i2sConfig);
void SPI_Enable(SPI_T* spi);
void SPI_Disable(SPI_T* spi);
void I2S_Enable(SPI_T* spi);
void I2S_Disable(SPI_T* spi);
void SPI_ConfigDataSize(SPI_T* spi, SPI_DATA_LENGTH_T length);

void SPI_SetSoftwareNSS(SPI_T* spi);
void SPI_ResetSoftwareNSS(SPI_T* spi);
void SPI_EnableSSOutput(SPI_T* spi);
void SPI_DisableSSOutput(SPI_T* spi);
void SPI_ConfigBiDirectionalLine(SPI_T* spi, SPI_DIRECTION_SELECT_T direction);

void SPI_EnableTIMode(SPI_T* spi);
void SPI_DisableTIMode(SPI_T* spi);
void I2S_ConfigFullDuplex(SPI_T* spi, I2S_Config_T* i2sConfig);

/* Data transfers */
void SPI_I2S_TxData(SPI_T* spi, uint16_t data);
uint16_t SPI_I2S_RxData(SPI_T* spi);

/* Hardware CRC Calculation */
void SPI_EnableCRC(SPI_T* spi);
void SPI_DisableCRC(SPI_T* spi);
void SPI_TxCRC(SPI_T* spi);
uint16_t SPI_ReadTxCRC(SPI_T* spi);
uint16_t SPI_ReadRxCRC(SPI_T* spi);
uint16_t SPI_ReadCRCPolynomial(SPI_T* spi);

/* DMA transfers */
void SPI_I2S_EnableDMA(SPI_T* spi, SPI_I2S_DMA_REQ_T dmaReq);
void SPI_I2S_DisableDMA(SPI_T* spi, SPI_I2S_DMA_REQ_T dmaReq);

/* Interrupts and flags */
void SPI_I2S_EnableInterrupt(SPI_T* spi, uint32_t interrupt);
void SPI_I2S_DisableInterrupt(SPI_T* spi, uint32_t interrupt);
uint8_t SPI_I2S_ReadStatusFlag(SPI_T* spi, SPI_FLAG_T flag);
void SPI_I2S_ClearStatusFlag(SPI_T* spi, SPI_FLAG_T flag);
uint8_t SPI_I2S_ReadIntFlag(SPI_T* spi, SPI_I2S_INT_T flag);
void SPI_I2S_ClearIntFlag(SPI_T* spi, SPI_I2S_INT_T flag);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F4XX_SPI_H */

/**@} end of group SPI_Enumerations */
/**@} end of group SPI_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
