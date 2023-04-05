/*!
 * @file        apm32s10x_spi.h
 *
 * @brief       This file contains all the functions prototypes for the SPI firmware library
 *
 * @version     V1.0.1
 *
 * @date        2022-12-31
 *
 * @attention
 *
 *  Copyright (C) 2022-2023 Geehy Semiconductor
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
#ifndef __APM32S10X_SPI_H
#define __APM32S10X_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32s10x.h"

/** @addtogroup APM32S10x_StdPeriphDriver
  @{
*/

/** @addtogroup SPI_Driver SPI Driver
  @{
*/

/** @defgroup SPI_Enumerations Enumerations
  @{
*/

/**
 * @brief   SPI data direction mode
 */
typedef enum
{
    SPI_DIRECTION_2LINES_FULLDUPLEX = 0x0000,
    SPI_DIRECTION_2LINES_RXONLY     = 0x0400,
    SPI_DIRECTION_1LINE_RX          = 0x8000,
    SPI_DIRECTION_1LINE_TX          = 0xC000
} SPI_DIRECTION_T;

/**
 * @brief    SPI mode
 */
typedef enum
{
    SPI_MODE_MASTER = 0x0104,
    SPI_MODE_SLAVE  = 0x0000
} SPI_MODE_T;

/**
 * @brief    SPI Data length
 */
typedef enum
{
    SPI_DATA_LENGTH_16B = 0x0800,
    SPI_DATA_LENGTH_8B  = 0x0000
} SPI_DATA_LENGTH_T;

/**
 * @brief    SPI Clock Polarity
 */
typedef enum
{
    SPI_CLKPOL_LOW   = 0x0000,
    SPI_CLKPOL_HIGH  = 0x0002
} SPI_CLKPOL_T;

/**
 * @brief    SPI Clock Phase
 */
typedef enum
{
    SPI_CLKPHA_1EDGE = 0x0000,
    SPI_CLKPHA_2EDGE = 0x0001
} SPI_CLKPHA_T;

/**
 * @brief    SPI Slave Select management
 */
typedef enum
{
    SPI_NSS_SOFT = 0x0200,
    SPI_NSS_HARD = 0x0000
} SPI_NSS_T;

/**
 * @brief    SPI BaudRate Prescaler
 */
typedef enum
{
    SPI_BAUDRATE_DIV_2   = 0x0000,
    SPI_BAUDRATE_DIV_4   = 0x0008,
    SPI_BAUDRATE_DIV_8   = 0x0010,
    SPI_BAUDRATE_DIV_16  = 0x0018,
    SPI_BAUDRATE_DIV_32  = 0x0020,
    SPI_BAUDRATE_DIV_64  = 0x0028,
    SPI_BAUDRATE_DIV_128 = 0x0030,
    SPI_BAUDRATE_DIV_256 = 0x0038,
} SPI_BAUDRATE_DIV_T;

/**
 * @brief    SPI MSB LSB transmission
 */
typedef enum
{
    SPI_FIRSTBIT_MSB = 0x0000,
    SPI_FIRSTBIT_LSB = 0x0080
} SPI_FIRSTBIT_T;

/**
 * @brief    SPI Direction select
 */
typedef enum
{
    SPI_DIRECTION_RX    = 0xBFFF,
    SPI_DIRECTION_TX    = 0x4000
} SPI_DIRECTION_SELECT_T;

/**
 * @brief    SPI interrupts definition
 */
typedef enum
{
    SPI_INT_TXBE        = 0x8002,
    SPI_INT_RXBNE       = 0x4001,
    SPI_INT_ERR         = 0x2000,
    SPI_INT_OVR         = 0x2040,
    SPI_INT_CRCE        = 0x2010,
    SPI_INT_ME          = 0x2020,
    SPI_INT_UDR         = 0x2008
} SPI_INT_T;

/**
 * @brief    SPI flags definition
 */
typedef enum
{
    SPI_FLAG_RXBNE      = 0x0001,
    SPI_FLAG_TXBE       = 0x0002,
    SPI_FLAG_SCHDIR     = 0x0004,
    SPI_FLAG_UDR        = 0x0008,
    SPI_FLAG_CRCE       = 0x0010,
    SPI_FLAG_ME         = 0x0020,
    SPI_FLAG_OVR        = 0x0040,
    SPI_FLAG_BSY        = 0x0080
} SPI_FLAG_T;

/**
 * @brief    SPI DMA requests
 */
typedef enum
{
    SPI_DMA_REQ_TX  = 0x0002,
    SPI_DMA_REQ_RX  = 0x0001
} SPI_DMA_REQ_T;

/**@} end of group SPI_Enumerations */

/** @defgroup SPI_Structures Structures
  @{
*/

/**
 * @brief    SPI Configure structure definition
 */
typedef struct
{
    SPI_MODE_T          mode;
    SPI_DATA_LENGTH_T   length;
    SPI_CLKPHA_T        phase;
    SPI_CLKPOL_T        polarity;
    SPI_NSS_T           nss;
    SPI_FIRSTBIT_T      firstBit;
    SPI_DIRECTION_T     direction;
    SPI_BAUDRATE_DIV_T  baudrateDiv;
    uint16_t            crcPolynomial;
} SPI_Config_T;

/**@} end of group SPI_Structures */

/** @defgroup SPI_Functions Functions
  @{
*/

/* Reset and Configuration */
void SPI_Reset(SPI_T* spi);
void SPI_Config(SPI_T* spi, SPI_Config_T* spiConfig);
void SPI_ConfigStructInit(SPI_Config_T* spiConfig);
void SPI_Enable(SPI_T* spi);
void SPI_Disable(SPI_T* spi);

void SPI_TxData(SPI_T* spi, uint16_t data);
uint16_t SPI_RxData(SPI_T* spi);
void SPI_SetSoftwareNSS(SPI_T* spi);
void SPI_ResetSoftwareNSS(SPI_T* spi);
void SPI_EnableSSOutput(SPI_T* spi);
void SPI_DisableSSOutput(SPI_T* spi);
void SPI_ConfigDataSize(SPI_T* spi, SPI_DATA_LENGTH_T length);

/* DMA */
void SPI_EnableDMA(SPI_T* spi, SPI_DMA_REQ_T dmaReq);
void SPI_DisableDMA(SPI_T* spi, SPI_DMA_REQ_T dmaReq);

/* CRC */
void SPI_TxCRC(SPI_T* spi);
void SPI_EnableCRC(SPI_T* spi);
void SPI_DisableCRC(SPI_T* spi);
uint16_t SPI_ReadTxCRC(SPI_T* spi);
uint16_t SPI_ReadRxCRC(SPI_T* spi);
uint16_t SPI_ReadCRCPolynomial(SPI_T* spi);
void SPI_ConfigBiDirectionalLine(SPI_T* spi, SPI_DIRECTION_SELECT_T direction);

/* Interrupts and flag */
void SPI_EnableInterrupt(SPI_T* spi, SPI_INT_T interrupt);
void SPI_DisableInterrupt(SPI_T* spi, SPI_INT_T interrupt);
uint8_t SPI_ReadStatusFlag(SPI_T* spi, SPI_FLAG_T flag);
void SPI_ClearStatusFlag(SPI_T* spi, SPI_FLAG_T flag);
uint8_t SPI_ReadIntFlag(SPI_T* spi, SPI_INT_T flag);
void SPI_ClearIntFlag(SPI_T* spi, SPI_INT_T flag);

/**@} end of group SPI_Functions */
/**@} end of group SPI_Driver */
/**@} end of group APM32S10x_StdPeriphDriver */

#ifdef __cplusplus
}
#endif

#endif /* __APM32S10X_SPI_H */
