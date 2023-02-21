/*!
 * @file        apm32f0xx_spi.h
 *
 * @brief       This file contains all the functions prototypes for the SPI firmware library
 *
 * @version     V1.0.3
 *
 * @date        2022-09-20
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#ifndef __APM32F0XX_SPI_H
#define __APM32F0XX_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "apm32f0xx.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup SPI_Driver SPI Driver
  @{
*/

/** @defgroup SPI_Macros Macros
  @{
*/

/**@} end of group SPI_Macros */

/** @defgroup SPI_Enumerations Enumerations
  @{
*/

/**
 * @brief   SPI data direction mode
 */
typedef enum
{
    SPI_DIRECTION_2LINES_FULLDUPLEX     = ((uint16_t)0x0000),  /*!< Full duplex mode,in 2-line unidirectional data mode */
    SPI_DIRECTION_2LINES_RXONLY         = ((uint16_t)0x0400),  /*!< Receiver only, in 2-line unidirectional data mode */
    SPI_DIRECTION_1LINE_RX              = ((uint16_t)0x8000),  /*!< Receiver mode, in 1 line bidirectional data mode */
    SPI_DIRECTION_1LINE_TX              = ((uint16_t)0xC000),  /*!< Transmit mode, in 1 line bidirectional data mode */
} SPI_DIRECTION_T;

/**
 * @brief   SPI mode
 */
typedef enum
{
    SPI_MODE_SLAVE      = ((uint8_t)0),     /*!< Slave mode */
    SPI_MODE_MASTER     = ((uint8_t)1),     /*!< Master mode */
} SPI_MODE_T;

/**
 * @brief   SPI data length
 */
typedef enum
{
    SPI_DATA_LENGTH_4B    = ((uint8_t)0x03),   /*!< Set data length to 4 bits */
    SPI_DATA_LENGTH_5B    = ((uint8_t)0x04),   /*!< Set data length to 5 bits */
    SPI_DATA_LENGTH_6B    = ((uint8_t)0x05),   /*!< Set data length to 6 bits */
    SPI_DATA_LENGTH_7B    = ((uint8_t)0x06),   /*!< Set data length to 7 bits */
    SPI_DATA_LENGTH_8B    = ((uint8_t)0x07),   /*!< Set data length to 8 bits */
    SPI_DATA_LENGTH_9B    = ((uint8_t)0x08),   /*!< Set data length to 9 bits */
    SPI_DATA_LENGTH_10B   = ((uint8_t)0x09),   /*!< Set data length to 10 bits */
    SPI_DATA_LENGTH_11B   = ((uint8_t)0x0A),   /*!< Set data length to 11 bits */
    SPI_DATA_LENGTH_12B   = ((uint8_t)0x0B),   /*!< Set data length to 12 bits */
    SPI_DATA_LENGTH_13B   = ((uint8_t)0x0C),   /*!< Set data length to 13 bits */
    SPI_DATA_LENGTH_14B   = ((uint8_t)0x0D),   /*!< Set data length to 14 bits */
    SPI_DATA_LENGTH_15B   = ((uint8_t)0x0E),   /*!< Set data length to 15 bits */
    SPI_DATA_LENGTH_16B   = ((uint8_t)0x0F),   /*!< Set data length to 16 bits */
} SPI_DATA_LENGTH_T;

/**
 * @brief   SPI CRC length
 */
typedef enum
{
    SPI_CRC_LENGTH_8B       = ((uint8_t)0), /*!< 8-bit CRC length */
    SPI_CRC_LENGTH_16B      = ((uint8_t)1), /*!< 16-bit CRC length */
} SPI_CRC_LENGTH_T;

/**
 * @brief   SPI Clock Polarity
 */
typedef enum
{
    SPI_CLKPOL_LOW          = ((uint8_t)0), /*!< Clock Polarity low */
    SPI_CLKPOL_HIGH         = ((uint8_t)1), /*!< Clock Polarity high */
} SPI_CLKPOL_T;

/**
 * @brief   SPI Clock Phase
 */
typedef enum
{
    SPI_CLKPHA_1EDGE        = ((uint8_t)0), /*!< 1 edge clock phase */
    SPI_CLKPHA_2EDGE        = ((uint8_t)1), /*!< 2 edge clock phase */
} SPI_CLKPHA_T;

/**
 * @brief   Software slave control
 */
typedef enum
{
    SPI_SSC_DISABLE         = ((uint8_t)0), //!< Disable software select slave */
    SPI_SSC_ENABLE          = ((uint8_t)1), //!< Enable software select slave */
} SPI_SSC_T;

/**
 * @brief   SPI BaudRate divider
 */
typedef enum
{
    SPI_BAUDRATE_DIV_2      = ((uint8_t)0), //!< Baud rate divider is 2 */
    SPI_BAUDRATE_DIV_4      = ((uint8_t)1), //!< Baud rate divider is 4 */
    SPI_BAUDRATE_DIV_8      = ((uint8_t)2), //!< Baud rate divider is 8 */
    SPI_BAUDRATE_DIV_16     = ((uint8_t)3), //!< Baud rate divider is 16 */
    SPI_BAUDRATE_DIV_32     = ((uint8_t)4), //!< Baud rate divider is 32 */
    SPI_BAUDRATE_DIV_64     = ((uint8_t)5), //!< Baud rate divider is 64 */
    SPI_BAUDRATE_DIV_128    = ((uint8_t)6), //!< Baud rate divider is 128 */
    SPI_BAUDRATE_DIV_256    = ((uint8_t)7), //!< Baud rate divider is 256 */
} SPI_BAUDRATE_DIV_T;

/**
 * @brief   MSB or LSB is transmitted/received first
 */
typedef enum
{
    SPI_FIRST_BIT_MSB       = ((uint8_t)0), //!< First bit is MSB */
    SPI_FIRST_BIT_LSB       = ((uint8_t)1), //!< First bit is LSB */
} SPI_FIRST_BIT_T;

/**
 * @brief   SPI FIFO reception threshold
 */
typedef enum
{
    SPI_RXFIFO_HALF         = ((uint8_t)0), //!< FIFO level is greater than or equal to 1/2 (16-bit) */
    SPI_RXFIFO_QUARTER      = ((uint8_t)1), //!< FIFO level is greater than or equal to 1/4 (8-bit) */
} SPI_RXFIFO_T;

/**
 * @brief   SPI last DMA transfers and reception
 */
typedef enum
{
    SPI_LAST_DMA_TXRXEVEN    = ((uint16_t)0x0000),  //!< transmission Even reception Even */
    SPI_LAST_DMA_TXEVENRXODD = ((uint16_t)0x2000),  //!< transmission Even reception Odd */
    SPI_LAST_DMA_TXODDRXEVEN = ((uint16_t)0x4000),  //!< transmission Odd reception Even */
    SPI_LAST_DMA_TXRXODD     = ((uint16_t)0x6000),  //!< transmission Odd reception Odd */
} SPI_LAST_DMA_T;

/**
 * @brief   SPI transmission fifo level
 */
typedef enum
{
    SPI_TXFIFO_LEVEL_EMPTY   = ((uint8_t)0x00),     //!< Transmission FIFO filled level is empty */
    SPI_TXFIFO_LEVEL_QUARTER = ((uint8_t)0x01),     //!< Transmission FIFO filled level is more than quarter */
    SPI_TXFIFO_LEVEL_HALF    = ((uint8_t)0x02),     //!< Transmission FIFO filled level is more than half */
    SPI_TXFIFO_LEVEL_FULL    = ((uint8_t)0x03),     //!< Transmission FIFO filled level is full */
} SPI_TXFIFO_LEVEL_T;

/**
 * @brief   SPI reception fifo level
 */
typedef enum
{
    SPI_RXFIFO_LEVEL_EMPTY    = ((uint8_t)0x00),    //!< Reception FIFO filled level is empty */
    SPI_RXFIFO_LEVEL_QUARTER  = ((uint8_t)0x01),    //!< Reception FIFO filled level is more than quarter */
    SPI_RXFIFO_LEVEL_HALF     = ((uint8_t)0x02),    //!< Reception FIFO filled level is more than half */
    SPI_RXFIFO_LEVEL_FULL     = ((uint8_t)0x03),    //!< Reception FIFO filled level is full */
} SPI_RXFIFO_LEVEL_T;

/**
 * @brief   SPI flags definition
 */
typedef enum
{
    SPI_FLAG_RXBNE      = ((uint16_t)0x0001),       //!< Receive buffer not empty flag */
    SPI_FLAG_TXBE       = ((uint16_t)0x0002),       //!< Transmit buffer empty flag */
    I2S_FLAG_CHDIR      = ((uint16_t)0x0004),       //!< Channel direction flag */
    I2S_FLAG_UDR        = ((uint16_t)0x0008),       //!< Underrun flag */
    SPI_FLAG_CRCE       = ((uint16_t)0x0010),       //!< CRC error flag */
    SPI_FLAG_MME        = ((uint16_t)0x0020),       //!< Master mode error flag */
    SPI_FLAG_OVR        = ((uint16_t)0x0040),       //!< Receive Overrun flag */
    SPI_FLAG_BUSY       = ((uint16_t)0x0080),       //!< Busy flag */
    SPI_FLAG_FFE        = ((uint16_t)0x0100),       //!< Frame format error flag */
} SPI_FLAG_T;

/**
 * @brief   SPI interrupt source
 */
typedef enum
{
    SPI_INT_ERRIE       = ((uint8_t)0x20),          //!< Error interrupt */
    SPI_INT_RXBNEIE     = ((uint8_t)0x40),          //!< Receive buffer not empty interrupt */
    SPI_INT_TXBEIE      = ((uint8_t)0x80),          //!< Transmit buffer empty interrupt */
} SPI_INT_T;

/**
 * @brief   SPI interrupt flag
 */
typedef enum
{
    SPI_INT_FLAG_RXBNE      = ((uint32_t)0x400001), //!< Receive buffer not empty interrupt flag */
    SPI_INT_FLAG_TXBE       = ((uint32_t)0x800002), //!< Transmit buffer empty interrupt flag */
    SPI_INT_FLAG_UDR        = ((uint32_t)0x200008), //!< Underrun flag interrupt flag */
    SPI_INT_FLAG_MME        = ((uint32_t)0x200020), //!< Master mode error interrupt flag */
    SPI_INT_FLAG_OVR        = ((uint32_t)0x200040), //!< Receive Overrun interrupt flag */
    SPI_INT_FLAG_FFE        = ((uint32_t)0x200100), //!< Frame format error interrupt flag */
} SPI_INT_FLAG_T;

/**
 * @brief   I2S mode
 */
typedef enum
{
    I2S_MODE_SLAVER_TX     = ((uint8_t)0),          //!< Slave TX mode */
    I2S_MODE_SLAVER_RX     = ((uint8_t)1),          //!< Slave RX mode */
    I2S_MODE_MASTER_TX     = ((uint8_t)2),          //!< Master TX mode */
    I2S_MODE_MASTER_RX     = ((uint8_t)3),          //!< Master RX mode */
} I2S_MODE_T;

/**
 * @brief   I2S Standard
 */
typedef enum
{
    I2S_STANDARD_PHILIPS   = ((uint16_t)0x0000),    //!< I2S Philips standard. */
    I2S_STANDARD_MSB       = ((uint16_t)0x0010),    //!< MSB justified standard (left justified) */
    I2S_STANDARD_LSB       = ((uint16_t)0x0020),    //!< LSB justified standard (right justified) */
    I2S_STANDARD_PCM_SHORT = ((uint16_t)0x0030),    //!< PCM short standard */
    I2S_STANDARD_PCM_LONG  = ((uint16_t)0x00B0),    //!< PCM long standard */
} I2S_STANDARD_T;

/**
 * @brief   I2S data length
 */
typedef enum
{
    I2S_DATA_LENGTH_16B   = ((uint8_t)0x00),        //!< Set data length to 16 bits */
    I2S_DATA_LENGTH_16BEX = ((uint8_t)0x01),        //!< Set data length to 16 bits */
    I2S_DATA_LENGTH_24B   = ((uint8_t)0x03),        //!< Set data length to 24 bits */
    I2S_DATA_LENGTH_32B   = ((uint8_t)0x05),        //!< Set data length to 32 bits */
} I2S_DATA_LENGTH_T;

/**
 * @brief   I2S MCLK Output
 */
typedef enum
{
    I2S_MCLK_OUTPUT_DISABLE = ((uint8_t)0x00),      //!< Set I2S MCLK Output disable */
    I2S_MCLK_OUTPUT_ENABLE  = ((uint8_t)0x01),      //!< Set I2S MCLK Output enable */
} I2S_MCLK_OUTPUT_T;

/**
 * @brief   I2S Audio divider
 */
typedef enum
{
    I2S_AUDIO_DIV_192K    = ((uint32_t)192000), /*!< specifie the AUDIO divider division factor as 192K */
    I2S_AUDIO_DIV_96K     = ((uint32_t)96000),  /*!< specifie the AUDIO divider division factor as 96K */
    I2S_AUDIO_DIV_48K     = ((uint32_t)48000),  /*!< specifie the AUDIO divider division factor as 48K */
    I2S_AUDIO_DIV_44K     = ((uint32_t)44100),  /*!< specifie the AUDIO divider division factor as 44K */
    I2S_AUDIO_DIV_32K     = ((uint32_t)32000),  /*!< specifie the AUDIO divider division factor as 32K */
    I2S_AUDIO_DIV_22K     = ((uint32_t)22050),  /*!< specifie the AUDIO divider division factor as 22K */
    I2S_AUDIO_DIV_16K     = ((uint32_t)16000),  /*!< specifie the AUDIO divider division factor as 16K */
    I2S_AUDIO_DIV_11K     = ((uint32_t)11025),  /*!< specifie the AUDIO divider division factor as 11K */
    I2S_AUDIO_DIV_8K      = ((uint32_t)8000),   /*!< specifie the AUDIO divider division factor as 8K */
    I2S_AUDIO_DIV_DEFAULT = ((uint32_t)2),      /*!< specifie the AUDIO divider division factor as DEFAULT value */
} I2S_AUDIO_DIV_T;

/**
 * @brief   I2S Clock Polarity
 */
typedef enum
{
    I2S_CLKPOL_LOW          = ((uint8_t)0), //!< Clock Polarity low */
    I2S_CLKPOL_HIGH         = ((uint8_t)1), //!< Clock Polarity high */
} I2S_CLKPOL_T;

/**@} end of group SPI_Enumerations*/

/** @defgroup SPI_Structures Structures
  @{
*/

/**
 * @brief   SPI Config struct definition
 */
typedef struct
{
    SPI_MODE_T           mode;          /*!< Specifies the SPI mode */
    SPI_DATA_LENGTH_T    length;        /*!< Specifies the SPI data length */
    SPI_CLKPHA_T         phase;         /*!< Specifies the Clock phase */
    SPI_CLKPOL_T         polarity;      /*!< Specifies the Clock polarity */
    SPI_SSC_T            slaveSelect;   /*!< Specifies the slave select mode */
    SPI_FIRST_BIT_T      firstBit;      /*!< Specifies the Frame format */
    SPI_DIRECTION_T      direction;     /*!< Specifies the data direction mode */
    SPI_BAUDRATE_DIV_T   baudrateDiv;   /*!< Specifies the baud rate divider */
    uint8_t crcPolynomial;              /*!< Specifies the CRC polynomial */
} SPI_Config_T;

/**
 * @brief   I2S Config struct definition
 */
typedef struct
{
    I2S_MODE_T           mode;           /*!< Specifies the I2S mode */
    I2S_STANDARD_T       standard;       /*!< Specifies the I2S standard */
    I2S_DATA_LENGTH_T    length;         /*!< Specifies the I2S data length */
    I2S_MCLK_OUTPUT_T    MCLKOutput;     /*!< Specifies the I2S MCLK Output */
    I2S_AUDIO_DIV_T      audioDiv;       /*!< Specifies the I2S Audio Diver */
    I2S_CLKPOL_T         polarity;       /*!< Specifies the Clock polarity */
} I2S_Config_T;

/**@} end of group SPI_Structures*/

/** @defgroup SPI_Variables Variables
  @{
*/

/**@} end of group SPI_Variables */

/** @defgroup SPI_Functions Functions
  @{
*/

/** SPI reset and configuration */
void SPI_Reset(SPI_T* spi);
void SPI_Config(SPI_T* spi, SPI_Config_T* spiConfig);
void I2S_Config(SPI_T* spi, I2S_Config_T* i2sConfig);  /*!< Not for APM32F030 devices */
void SPI_ConfigStructInit(SPI_Config_T* spiConfig);
void I2S_ConfigStructInit(I2S_Config_T* i2sConfig);   /*!< Not for APM32F030 devices */
void SPI_Enable(SPI_T* spi);
void SPI_Disable(SPI_T* spi);
void I2S_Enable(SPI_T* spi);   /*!< Not for APM32F030 devices */
void I2S_Disable(SPI_T* spi);  /*!< Not for APM32F030 devices */
void SPI_EnableFrameFormatMode(SPI_T* spi);
void SPI_DisableFrameFormatMode(SPI_T* spi);
void SPI_ConfigDatalength(SPI_T* spi, uint8_t length);
void SPI_EnableOutputDirection(SPI_T* spi);
void SPI_DisableOutputDirection(SPI_T* spi);
void SPI_EnableInternalSlave(SPI_T* spi);
void SPI_DisableInternalSlave(SPI_T* spi);
void SPI_EnableSSoutput(SPI_T* spi);
void SPI_DisableSSoutput(SPI_T* spi);
void SPI_EnableNSSPulse(SPI_T* spi);
void SPI_DisableNSSPulse(SPI_T* spi);

/**  CRC */
void SPI_CRCLength(SPI_T* spi, SPI_CRC_LENGTH_T  crcLength);
void SPI_EnableCRC(SPI_T* spi);
void SPI_DisableCRC(SPI_T* spi);
void SPI_TxCRC(SPI_T* spi);
uint16_t SPI_ReadRxCRC(SPI_T* spi);
uint16_t SPI_ReadTxCRC(SPI_T* spi);
uint16_t SPI_ReadCRCPolynomial(SPI_T* spi);

/**  DMA */
void SPI_EnableDMARxBuffer(SPI_T* spi);
void SPI_DisableDMARxBuffer(SPI_T* spi);
void SPI_EnableDMATxBuffer(SPI_T* spi);
void SPI_DisableDMATxBuffer(SPI_T* spi);
void SPI_LastDMATransfer(SPI_T* spi, SPI_LAST_DMA_T  lastDMA);

/** FIFO */
void SPI_ConfigFIFOThreshold(SPI_T* spi, SPI_RXFIFO_T  threshold);
uint8_t SPI_ReadTransmissionFIFOLeve(SPI_T* spi);
uint8_t SPI_ReadReceptionFIFOLeve(SPI_T* spi);

/** Interrupt */
void SPI_EnableInterrupt(SPI_T* spi, uint8_t interrupt);
void SPI_DisableInterrupt(SPI_T* spi, uint8_t interrupt);

/** Transmit and receive */
void SPI_TxData8(SPI_T* spi, uint8_t data);
void SPI_I2S_TxData16(SPI_T* spi, uint16_t data);
uint8_t SPI_RxData8(SPI_T* spi);
uint16_t SPI_I2S_RxData16(SPI_T* spi);

/** flag */
uint8_t SPI_ReadStatusFlag(SPI_T* spi, SPI_FLAG_T flag);
void SPI_ClearStatusFlag(SPI_T* spi, uint8_t flag);
uint8_t SPI_ReadIntFlag(SPI_T* spi, SPI_INT_FLAG_T flag);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0XX_SPI_H */

/**@} end of group SPI_Functions */
/**@} end of group SPI_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
