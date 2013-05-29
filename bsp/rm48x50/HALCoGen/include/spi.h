/** @file spi.h
*   @brief SPI Driver Definition File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   (c) Texas Instruments 2009-2013, All rights reserved.
*/


#ifndef __SPI_H__
#define __SPI_H__

#include "reg_spi.h"

/** @enum chipSelect
*   @brief Transfer Group Chip Select
*/
enum spiChipSelect
{
    SPI_CS_NONE = 0xFFU,
    SPI_CS_0    = 0xFEU,
    SPI_CS_1    = 0xFDU,
    SPI_CS_2    = 0xFBU,
    SPI_CS_3    = 0xF7U,
    SPI_CS_4    = 0xEFU,
    SPI_CS_5    = 0xDFU,
    SPI_CS_6    = 0xBFU,
    SPI_CS_7    = 0x7FU
};

/** @enum spiPinSelect
*   @brief spi Pin Select
*/
enum spiPinSelect
{
    SPI_PIN_CS0    = 0U,
    SPI_PIN_CS1    = 1U,
    SPI_PIN_CS2    = 2U,
    SPI_PIN_CS3    = 3U,
    SPI_PIN_CS4    = 4U,
    SPI_PIN_CS5    = 5U,
    SPI_PIN_CS6    = 6U,
    SPI_PIN_CS7    = 7U,
    SPI_PIN_ENA    = 8U,
    SPI_PIN_CLK    = 9U,
    SPI_PIN_SIMO   = 10U,
    SPI_PIN_SOMI   = 11U,
    SPI_PIN_SIMO_1 = 17U,
    SPI_PIN_SIMO_2 = 18U,
    SPI_PIN_SIMO_3 = 19U,
    SPI_PIN_SIMO_4 = 20U,
    SPI_PIN_SIMO_5 = 21U,
    SPI_PIN_SIMO_6 = 22U,
    SPI_PIN_SIMO_7 = 23U,
    SPI_PIN_SOMI_1 = 25U,
    SPI_PIN_SOMI_2 = 26U,
    SPI_PIN_SOMI_3 = 27U,
    SPI_PIN_SOMI_4 = 28U,
    SPI_PIN_SOMI_5 = 29U,
    SPI_PIN_SOMI_6 = 30U,
    SPI_PIN_SOMI_7 = 31U
};

/** @enum dataformat
*   @brief SPI dataformat register select
*/
typedef enum dataformat
{
    SPI_FMT_0 = 0U,
    SPI_FMT_1 = 1U,
    SPI_FMT_2 = 2U,
    SPI_FMT_3 = 3U
}SPIDATAFMT_t;

/** @struct spiDAT1RegConfig
*   @brief SPI data register configuration
*/
typedef struct spiDAT1RegConfig
{
    boolean CS_HOLD;
    boolean WDEL;
    SPIDATAFMT_t DFSEL;
    uint8 CSNR;
}spiDAT1_t;

/** @enum SpiTxRxDataStatus
*   @brief SPI Data Status
*/
typedef enum SpiTxRxDataStatus
{
    SPI_READY = 0U,
	SPI_PENDING = 1U,
    SPI_COMPLETED = 2U
}SpiDataStatus_t;

/* USER CODE BEGIN (0) */
/* USER CODE END */

/** 
 *  @defgroup SPI SPI
 *  @brief Serial Peripheral Interface Module.
 *  
 *  SPI is a high-speed synchronous serial input/output port that allows a serial bit stream of
 *  programmed length (2 to 16 bits) to be shifted in and out of the device at a programmed bit-transfer rate.
 *
 *	Related Files
 *   - reg_spi.h
 *   - spi.h
 *   - spi.c
 *  @addtogroup SPI
 *  @{
 */
 
/* SPI Interface Functions */
void spiInit(void);
void spiSetFunctional(spiBASE_t *spi, uint32 port);
void spiEnableNotification(spiBASE_t *spi, uint32 flags);
void spiDisableNotification(spiBASE_t *spi, uint32 flags);
uint32 spiTransmitData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32 blocksize, uint16 * srcbuff);
void spiSendData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32 blocksize, uint16 * srcbuff);
uint32 spiReceiveData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32 blocksize, uint16 * destbuff);
void spiGetData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32 blocksize, uint16 * destbuff);
uint32 spiTransmitAndReceiveData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32 blocksize, uint16 * srcbuff, uint16 * destbuff);
void spiSendAndGetData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32 blocksize, uint16 * srcbuff, uint16 * destbuff);
void spiEnableLoopback(spiBASE_t *spi, loopBackType_t Loopbacktype);
void spiDisableLoopback(spiBASE_t *spi);
SpiDataStatus_t SpiTxStatus(spiBASE_t *spi);
SpiDataStatus_t SpiRxStatus(spiBASE_t *spi);

/** @fn void spiNotification(spiBASE_t *spi, uint32 flags)
*   @brief Interrupt callback
*   @param[in] spi   - Spi module base address
*   @param[in] flags - Copy of error interrupt flags
*
* This is a callback that is provided by the application and is called upon
* an interrupt.  The parameter passed to the callback is a copy of the 
* interrupt flag register.
*/
void spiNotification(spiBASE_t *spi, uint32 flags);

/** @fn void spiEndNotification(spiBASE_t *spi)
*   @brief Interrupt callback for End of TX or RX data length.
*   @param[in] spi   - Spi module base address
*
* This is a callback that is provided by the application and is called upon
* an interrupt at the End of TX or RX data length.
*/
void spiEndNotification(spiBASE_t *spi);

/**@}*/
/* USER CODE BEGIN (1) */
/* USER CODE END */

#endif
