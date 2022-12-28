/*!
 * @file        apm32f0xx_spi.c
 *
 * @brief       This file contains all the functions for the SPI peripheral
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

#include "apm32f0xx_spi.h"
#include "apm32f0xx_rcm.h"

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

/**@} end of group SPI_Enumerations */

/** @defgroup SPI_Structures Structures
  @{
*/

/**@} end of group SPI_Structures */

/** @defgroup SPI_Variables Variables
  @{
*/

/**@} end of group SPI_Variables */

/** @defgroup SPI_Functions Functions
  @{
*/

/*!
 * @brief       Set the SPI peripheral registers to their default reset values
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 */
void SPI_Reset(SPI_T* spi)
{
    if (spi == SPI1)
    {
        RCM_EnableAPB2PeriphReset(RCM_APB2_PERIPH_SPI1);
        RCM_DisableAPB2PeriphReset(RCM_APB2_PERIPH_SPI1);
    }
    else
    {
        RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_SPI2);
        RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_SPI2);
    }
}

/*!
 * @brief       Config the SPI peripheral according to the specified parameters in the adcConfig
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @param       spiConfig:  Pointer to a SPI_Config_T structure that
 *                          contains the configuration information for the SPI peripheral
 *
 * @retval      None
 */
void SPI_Config(SPI_T* spi, SPI_Config_T* spiConfig)
{
    spi->CTRL1_B.MSMCFG = spiConfig->mode;
    spi->CTRL2_B.DSCFG   = spiConfig->length;
    spi->CTRL1_B.CPHA  = spiConfig->phase;
    spi->CTRL1_B.CPOL  = spiConfig->polarity;
    spi->CTRL1_B.SSEN = spiConfig->slaveSelect;
    spi->CTRL1_B.LSBSEL = spiConfig->firstBit;

    spi->CTRL1 &= (uint16_t)~0xC400;
    spi->CTRL1 |= (uint32_t)spiConfig->direction;

    spi->CTRL1_B.BRSEL = spiConfig->baudrateDiv;

    spi->CRCPOLY |= spiConfig->crcPolynomial;
}

/*!
 * @brief       Config the SPI peripheral according to the specified parameters in the adcConfig
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1
 *
 * @param       i2sConfig:  Pointer to a SPI_Config_T structure that
 *                          contains the configuration information for the SPI peripheral
 *
 * @retval      None
 */
void I2S_Config(SPI_T* spi, I2S_Config_T* i2sConfig)
{
    uint16_t i2sDiv = 2, i2sOdd = 0, i2sLen = 1;
    uint32_t sourceClock = 0, value = 0, temp = 0;

    spi->I2SPSC = 0x0002;
    spi->I2SCFG &= 0xF040;
    temp = spi->I2SCFG;

    if (i2sConfig->audioDiv == I2S_AUDIO_DIV_DEFAULT)
    {
        i2sDiv = (uint16_t)2;
        i2sOdd = (uint16_t)0;
    }
    else
    {
        if (i2sConfig->length == I2S_DATA_LENGTH_16B)
        {
            i2sLen = 1;
        }
        else
        {
            i2sLen = 2;
        }

        sourceClock = RCM_ReadSYSCLKFreq();

        if (i2sConfig->MCLKOutput == I2S_MCLK_OUTPUT_ENABLE)
        {
            value = (uint16_t)(((((sourceClock / 256) * 10) / i2sConfig->audioDiv)) + 5);
        }
        else
        {
            value = (uint16_t)(((((sourceClock / (32 * i2sLen)) * 10) / i2sConfig->audioDiv)) + 5);
        }

        value = value / 10;
        i2sOdd = (uint16_t)(value & (uint16_t)0x0001);
        i2sDiv = (uint16_t)((value - i2sOdd) / 2);
    }

    if ((i2sDiv < 2) || (i2sDiv > 0xFF))
    {
        i2sDiv = 2;
        i2sOdd = 0;
    }

    spi->I2SPSC_B.I2SPSC = i2sDiv;
    spi->I2SPSC_B.ODDPSC = i2sOdd;
    spi->I2SPSC_B.MCOEN  = i2sConfig->MCLKOutput;
    spi->I2SCFG_B.MODESEL = BIT_SET;
    spi->I2SCFG_B.I2SMOD = i2sConfig->mode;
    spi->I2SCFG_B.CPOL = i2sConfig->polarity;

    temp = (uint16_t)((uint16_t)i2sConfig->standard | (uint16_t)i2sConfig->length);
    spi->I2SCFG |= temp;
}

/*!
 * @brief       Fills each spiConfig member with its default value
 *
 * @param       spiConfig:  Pointer to a SPI_Config_T structure which will be initialized
 *
 * @retval      None
 */
void SPI_ConfigStructInit(SPI_Config_T* spiConfig)
{
    spiConfig->mode      = SPI_MODE_SLAVE;
    spiConfig->length    = SPI_DATA_LENGTH_8B;
    spiConfig->phase     = SPI_CLKPHA_1EDGE;
    spiConfig->polarity  = SPI_CLKPOL_HIGH;
    spiConfig->slaveSelect = SPI_SSC_DISABLE;
    spiConfig->firstBit    = SPI_FIRST_BIT_MSB;
    spiConfig->direction   = SPI_DIRECTION_2LINES_FULLDUPLEX;
    spiConfig->baudrateDiv = SPI_BAUDRATE_DIV_2;
    spiConfig->crcPolynomial = 7;
}

/*!
 * @brief       Fills each i2sConfig member with its default value
 *
 * @param       i2sConfig:  Pointer to a SPI_Config_T structure which will be initialized
 *
 * @retval      None
 */
void I2S_ConfigStructInit(I2S_Config_T* i2sConfig)
{
    i2sConfig->mode       =  I2S_MODE_SLAVER_TX;
    i2sConfig->standard   =  I2S_STANDARD_PHILIPS;
    i2sConfig->length     =  I2S_DATA_LENGTH_16B;
    i2sConfig->MCLKOutput =  I2S_MCLK_OUTPUT_DISABLE;
    i2sConfig->audioDiv   =  I2S_AUDIO_DIV_DEFAULT;
    i2sConfig->polarity   =  I2S_CLKPOL_LOW;
}

/*!
 * @brief       Enable the SPI peripheral
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 */
void SPI_Enable(SPI_T* spi)
{
    spi->CTRL1_B.SPIEN = BIT_SET;
}

/*!
 * @brief       Disable the SPI peripheral
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 */
void SPI_Disable(SPI_T* spi)
{
    spi->CTRL1_B.SPIEN = BIT_RESET;
}

/*!
 * @brief       Enable the SPI peripheral
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1
 *
 * @retval      None
 *
 * @note        Not supported for APM32F030 devices.
 */
void I2S_Enable(SPI_T* spi)
{
    spi->I2SCFG_B.I2SEN = BIT_SET;
}

/*!
 * @brief       Disable the SPI peripheral
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1
 *
 * @retval      None
 *
 * @note        Not supported for APM32F030 devices.
 */
void I2S_Disable(SPI_T* spi)
{
    spi->I2SCFG_B.I2SEN = BIT_RESET;
}

/*!
 * @brief       Enable the frame format mode
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 */
void SPI_EnableFrameFormatMode(SPI_T* spi)
{
    spi->CTRL2_B.FRFCFG = BIT_SET;
}

/*!
 * @brief       Disable the frame format mode
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 */
void SPI_DisableFrameFormatMode(SPI_T* spi)
{
    spi->CTRL2_B.FRFCFG = BIT_RESET;
}

/*!
 * @brief       Configures the SPI data length
 *
 * @param       length:  specifies the SPI length
 *                          The parameter can be one of following values:
 *                          @arg SPI_DATA_LENGTH_4B:  Set data length to 4 bits
 *                          @arg SPI_DATA_LENGTH_5B:  Set data length to 5 bits
 *                          @arg SPI_DATA_LENGTH_6B:  Set data length to 6 bits
 *                          @arg SPI_DATA_LENGTH_7B:  Set data length to 7 bits
 *                          @arg SPI_DATA_LENGTH_8B:  Set data length to 8 bits
 *                          @arg SPI_DATA_LENGTH_9B:  Set data length to 9 bits
 *                          @arg SPI_DATA_LENGTH_10B:  Set data length to 10 bits
 *                          @arg SPI_DATA_LENGTH_11B:  Set data length to 11 bits
 *                          @arg SPI_DATA_LENGTH_12B:  Set data length to 12 bits
 *                          @arg SPI_DATA_LENGTH_13B:  Set data length to 13 bits
 *                          @arg SPI_DATA_LENGTH_14B:  Set data length to 14 bits
 *                          @arg SPI_DATA_LENGTH_15B:  Set data length to 15 bits
 *                          @arg SPI_DATA_LENGTH_16B:  Set data length to 16 bits
 *
 * @retval      None
 */
void SPI_ConfigDatalength(SPI_T* spi, uint8_t length)
{
    spi->CTRL2_B.DSCFG = (uint8_t)length;
}

/*!
 * @brief       Configures the FIFO reception threshold
 *
 * @param       threshold: selects the SPI FIFO reception threshold
 *                         The parameter can be one of following values:
 *                         @arg SPI_RXFIFO_HALF:    FIFO level is greater than or equal to 1/2 (16-bit)
 *                         @arg SPI_RXFIFO_QUARTER: FIFO level is greater than or equal to 1/4 (8-bit)
 *
 * @retval      None
 */
void SPI_ConfigFIFOThreshold(SPI_T* spi, SPI_RXFIFO_T  threshold)
{
    spi->CTRL2_B.FRTCFG  =  threshold;
}

/*!
 * @brief       Enable the data transfer direction
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 */
void SPI_EnableOutputDirection(SPI_T* spi)
{
    spi->CTRL1_B.BMOEN  =  BIT_SET;
}

/*!
 * @brief       Disable the data transfer direction
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 */
void SPI_DisableOutputDirection(SPI_T* spi)
{
    spi->CTRL1_B.BMOEN  =  BIT_RESET;
}

/*!
 * @brief       Enable internal slave select
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 */
void SPI_EnableInternalSlave(SPI_T* spi)
{
    spi->CTRL1_B.ISSEL = BIT_SET;
}

/*!
 * @brief       Disable internal slave select
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 */
void SPI_DisableInternalSlave(SPI_T* spi)
{
    spi->CTRL1_B.ISSEL = BIT_RESET;
}

/*!
 * @brief       Enable the SS output mode
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 */
void SPI_EnableSSoutput(SPI_T* spi)
{
    spi->CTRL2_B.SSOEN = BIT_SET;
}

/*!
 * @brief       Disable the SS output mode
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 */
void SPI_DisableSSoutput(SPI_T* spi)
{
    spi->CTRL2_B.SSOEN = BIT_RESET;
}

/*!
 * @brief       Enable the NSS pulse management mode
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 */
void SPI_EnableNSSPulse(SPI_T* spi)
{
    spi->CTRL2_B.NSSPEN = BIT_SET;
}

/*!
 * @brief       Disable the NSS pulse management mode
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 */
void SPI_DisableNSSPulse(SPI_T* spi)
{
    spi->CTRL2_B.NSSPEN = BIT_RESET;
}

/*!
 * @brief       Transmits a Data
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @param       data:   Byte to be transmitted
 *
 * @retval      None
 */
void SPI_I2S_TxData16(SPI_T* spi, uint16_t data)
{
    spi->DATA = (uint16_t)data;
}

/*!
 * @brief       Transmits a  uint8_t Data
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @param       data:   Byte to be transmitted
 *
 * @retval      None
 */
void SPI_TxData8(SPI_T* spi, uint8_t data)
{
    *((uint8_t*) & (spi->DATA)) = data;
}

/*!
 * @brief       Returns the most recent received data by the SPI peripheral
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @param       None
 *
 * @retval      The value of the received data
 */
uint16_t SPI_I2S_RxData16(SPI_T* spi)
{
    return ((uint16_t)spi->DATA);
}

/*!
 * @brief       Returns the most recent received data by the SPI peripheral
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @param       None
 *
 * @retval      The value of the received data
 */
uint8_t SPI_RxData8(SPI_T* spi)
{
    return  *((uint8_t*) & (spi->DATA));
}

/*!
 * @brief       Selects the data transfer direction
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 * @param       crcLength: selects the SPI transfer direction
 *                         The parameter can be one of following values:
 *                         @arg SPI_CRC_LENGTH_8B:  8-bit CRC length
 *                         @arg SPI_CRC_LENGTH_16B: 16-bit CRC length
 *
 * @retval      None
 */
void SPI_CRCLength(SPI_T* spi, SPI_CRC_LENGTH_T  crcLength)
{
    spi->CTRL1_B.CRCLSEL  =  crcLength;
}

/*!
 * @brief       Enable the CRC value calculation
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 */
void SPI_EnableCRC(SPI_T* spi)
{
    spi->CTRL1_B.CRCEN = BIT_SET;
}

/*!
 * @brief       Disable the CRC value calculation
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 */
void SPI_DisableCRC(SPI_T* spi)
{
    spi->CTRL1_B.CRCEN = BIT_RESET;
}

/*!
 * @brief       Transmit CRC value
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 */
void SPI_TxCRC(SPI_T* spi)
{
    spi->CTRL1_B.CRCNXT = BIT_SET;
}

/*!
 * @brief       Returns the receive CRC register value
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 *
 * @note        None
 */
uint16_t SPI_ReadRxCRC(SPI_T* spi)
{
    return (uint16_t)spi->RXCRC;
}

/*!
 * @brief       Returns the transmit CRC register value
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 *
 * @note        None
 */
uint16_t SPI_ReadTxCRC(SPI_T* spi)
{
    return (uint16_t)spi->TXCRC;
}

/*!
 * @brief       Returns the CRC Polynomial register value
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 */
uint16_t SPI_ReadCRCPolynomial(SPI_T* spi)
{
    return (uint16_t)spi->CRCPOLY;
}

/*!
 * @brief       Enable the DMA Rx buffer
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 */
void SPI_EnableDMARxBuffer(SPI_T* spi)
{
    spi->CTRL2_B.RXDEN = BIT_SET;
}

/*!
 * @brief       Disable the DMA Rx buffer
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 */
void SPI_DisableDMARxBuffer(SPI_T* spi)
{
    spi->CTRL2_B.RXDEN = BIT_RESET;
}

/*!
 * @brief       Enable the DMA Tx buffer
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 */
void SPI_EnableDMATxBuffer(SPI_T* spi)
{
    spi->CTRL2_B.TXDEN = BIT_SET;
}

/*!
 * @brief       Disable the DMA Tx buffer
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      None
 */
void SPI_DisableDMATxBuffer(SPI_T* spi)
{
    spi->CTRL2_B.TXDEN = BIT_RESET;
}

/*!
 * @brief       Selects the last DMA transfer is type(Even/Odd)
 *
 * @param       crcLength: specifies the SPI last DMA transfers
 *                         The parameter can be one of following values:
 *                         @arg SPI_LAST_DMA_TXRXEVEN:    transmission Even reception Even
 *                         @arg SPI_LAST_DMA_TXEVENRXODD: transmission Even reception Odd
 *                         @arg SPI_LAST_DMA_TXODDRXEVEN: transmission Odd reception Even
 *                         @arg SPI_LAST_DMA_TXRXODD:     transmission Odd reception Odd
 *
 * @retval      None
 */
void SPI_LastDMATransfer(SPI_T* spi, SPI_LAST_DMA_T  lastDMA)
{
    spi->CTRL2 &= 0x9FFF;
    spi->CTRL2 |= (uint16_t)lastDMA;
}

/*!
 * @brief       Returns the SPI Transmission FIFO filled level
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      Transmission FIFO filled level:
 *              SPI_TXFIFO_LEVEL_EMPTY:   Transmission FIFO filled level is empty
 *              SPI_TXFIFO_LEVEL_QUARTER: Transmission FIFO filled level is more than quarter
 *              SPI_TXFIFO_LEVEL_HALF:    Transmission FIFO filled level is more than half
 *              SPI_TXFIFO_LEVEL_FULL:    Transmission FIFO filled level is full
 */
uint8_t SPI_ReadTransmissionFIFOLeve(SPI_T* spi)
{
    return (uint8_t)((spi->STS_B.FTLSEL & 0x03));
}

/*!
 * @brief       Returns the SPI Reception FIFO filled level
 *
 * @param       spi:    Select the the SPI peripheral.It can be SPI1/SPI2
 *
 * @retval      Reception FIFO filled level:
 *              SPI_RXFIFO_LEVEL_EMPTY:   Reception FIFO filled level is empty
 *              SPI_RXFIFO_LEVEL_QUARTER: Reception FIFO filled level is more than quarter
 *              SPI_RXFIFO_LEVEL_HALF:    Reception FIFO filled level is more than half
 *              SPI_RXFIFO_LEVEL_FULL:    Reception FIFO filled level is full
 */
uint8_t SPI_ReadReceptionFIFOLeve(SPI_T* spi)
{
    return (uint8_t)((spi->STS_B.FRLSEL & 0x03));
}

/*!
 * @brief       Enable the SPI interrupts
 *
 * @param       interrupt:  Specifies the SPI interrupts sources
 *                          The parameter can be combination of following values:
 *                          @arg SPI_INT_ERRIE:    Error interrupt
 *                          @arg SPI_INT_RXBNEIE:  Receive buffer not empty interrupt
 *                          @arg SPI_INT_TXBEIE:   Transmit buffer empty interrupt
 *
 * @retval      None
 */
void SPI_EnableInterrupt(SPI_T* spi, uint8_t interrupt)
{
    spi->CTRL2 |= (uint8_t)interrupt;
}

/*!
 * @brief       Disable the SPI interrupts
 *
 * @param       interrupt:  Specifies the SPI interrupts sources
 *                          The parameter can be combination of following values:
 *                          @arg SPI_INT_ERRIE:    Error interrupt
 *                          @arg SPI_INT_RXBNEIE:  Receive buffer not empty interrupt
 *                          @arg SPI_INT_TXBEIE:   Transmit buffer empty interrupt
 *
 * @retval      None
 */
void SPI_DisableInterrupt(SPI_T* spi, uint8_t interrupt)
{
    spi->CTRL2 &= (uint8_t)~interrupt;
}

/*!
 * @brief       Checks whether the specified SPI flag is set or not
 *
 * @param       flag:   Specifies the flag to check
 *                      This parameter can be one of the following values:
 *                      @arg SPI_FLAG_RXBNE:    Receive buffer not empty flag
 *                      @arg SPI_FLAG_TXBE:     Transmit buffer empty flag
 *                      @arg I2S_FLAG_CHDIR:    Channel direction flag
 *                      @arg I2S_FLAG_UDR:      Underrun flag
 *                      @arg SPI_FLAG_CRCE:     CRC error flag
 *                      @arg SPI_FLAG_MME:      Master mode error flag
 *                      @arg SPI_FLAG_OVR:      Receive Overrun flag
 *                      @arg SPI_FLAG_BUSY:     Busy flag
 *                      @arg SPI_FLAG_FFE:      Frame format error flag
 *
 * @retval      The new state of flag (SET or RESET)
 */
uint8_t SPI_ReadStatusFlag(SPI_T* spi, SPI_FLAG_T flag)
{
    uint16_t status;

    status = (uint16_t)(spi->STS & flag);

    if (status == flag)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clear the specified SPI flag
 *
 * @param       flag:   Specifies the flag to clear
 *                      This parameter can be any combination of the following values:
 *                      @arg SPI_FLAG_CRCE:     CRC error flag

 * @retval      None
 */
void SPI_ClearStatusFlag(SPI_T* spi, uint8_t flag)
{
    spi->STS &= (uint32_t)~flag;
}

/*!
 * @brief       Checks whether the specified interrupt has occurred or not
 *
 * @param       flag:   Specifies the SPI interrupt pending bit to check
 *                      This parameter can be one of the following values:
 *                      @arg SPI_INT_FLAG_RXBNE:    Receive buffer not empty flag
 *                      @arg SPI_INT_FLAG_TXBE:     Transmit buffer empty flag
 *                      @arg SPI_INT_FLAG_UDR:      Underrun flag interrupt flag
 *                      @arg SPI_INT_FLAG_MME:      Master mode error flag
 *                      @arg SPI_INT_FLAG_OVR:      Receive Overrun flag
 *                      @arg SPI_INT_FLAG_FFE:      Frame format error interrupt flag
 *
 * @retval      None
 */
uint8_t SPI_ReadIntFlag(SPI_T* spi, SPI_INT_FLAG_T flag)
{
    uint32_t intEnable;
    uint32_t intStatus;

    intEnable = (uint32_t)(spi->CTRL2 & (uint32_t)(flag >> 16));

    intStatus = (uint32_t)(spi->STS & (uint32_t)(flag & 0x1ff));

    if (intEnable && intStatus)
    {
        return SET;
    }

    return RESET;
}

/**@} end of group SPI_Functions*/
/**@} end of group SPI_Driver*/
/**@} end of group APM32F0xx_StdPeriphDriver*/
