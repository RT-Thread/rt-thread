/*!
 * @file        apm32f4xx_spi.c
 *
 * @brief       This file provides all the SPI firmware functions
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

#include "apm32f4xx_spi.h"
#include "apm32f4xx_rcm.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @defgroup SPI_Driver
  * @brief SPI driver modules
  @{
*/

/** @defgroup SPI_Functions
  @{
*/

/*!
 * @brief     Reset the specified SPIx peripheral
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6
 *
 * @retval    None
 */
void SPI_I2S_Reset(SPI_T* spi)
{
    if (spi == SPI1)
    {
        RCM_EnableAPB2PeriphReset(RCM_APB2_PERIPH_SPI1);
        RCM_DisableAPB2PeriphReset(RCM_APB2_PERIPH_SPI1);
    }
    else if (spi == SPI2)
    {
        RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_SPI2);
        RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_SPI2);
    }
    else if (spi == SPI3)
    {
        RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_SPI3);
        RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_SPI3);
    }
    else if (spi == SPI4)
    {
        RCM_EnableAPB2PeriphReset(RCM_APB2_PERIPH_SPI4);
        RCM_DisableAPB2PeriphReset(RCM_APB2_PERIPH_SPI4);
    }
    else if (spi == SPI5)
    {
        RCM_EnableAPB2PeriphReset(RCM_APB2_PERIPH_SPI5);
        RCM_DisableAPB2PeriphReset(RCM_APB2_PERIPH_SPI5);
    }
    else if (spi == SPI6)
    {
        RCM_EnableAPB2PeriphReset(RCM_APB2_PERIPH_SPI6);
        RCM_DisableAPB2PeriphReset(RCM_APB2_PERIPH_SPI6);
    }
}

/*!
 * @brief     Config the SPI peripheral according to the specified parameters in the spiConfig
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6.
 *
 * @param     spiConfig: pointer to a SPI_Config_T structure
 *
 * @retval    None
 */
void SPI_Config(SPI_T* spi, SPI_Config_T* spiConfig)
{
    spi->CTRL1_B.MSMCFG = spiConfig->mode;
    spi->CTRL1_B.ISSEL = spiConfig->mode;
    spi->CTRL1_B.DFLSEL = spiConfig->length;
    spi->CTRL1_B.CPHA = spiConfig->phase;
    spi->CTRL1_B.CPOL = spiConfig->polarity;
    spi->CTRL1_B.SSEN = spiConfig->nss;
    spi->CTRL1_B.LSBSEL = spiConfig->firstBit;
    /** 1 line or 2 lines */
    spi->CTRL1_B.BMEN = spiConfig->direction & 0x0001;
    /** Tx or Rx in 1 line */
    spi->CTRL1_B.BMOEN = (spiConfig->direction & 0x0010) >> 4;
    /** receive only or full-duplex in 2 lines */
    spi->CTRL1_B.RXOMEN = (spiConfig->direction & 0x0100) >> 8;
    spi->CTRL1_B.BRSEL = spiConfig->baudrateDiv;

    spi->CRCPOLY_B.CRCPOLY = spiConfig->crcPolynomial;
}

/*!
 * @brief     Config the I2S peripheral according to the specified parameters in the spiConfig
 *
 * @param     spi: The SPIx can be 2,3
 *
 * @param     i2sConfig: pointer to a I2S_Config_T structure
 *
 * @retval    None
 */
void I2S_Config(SPI_T* spi, I2S_Config_T* i2sConfig)
{
    uint16_t i2sDiv = 2, i2sOdd = 0, packetSize = 1;
    uint32_t tmp = 0;
    uint32_t sysClock = 0;

    /* Clear MODESEL, I2SEN, I2SMOD, PFSSEL, I2SSSEL, CPOL, DATALEN and CHLEN bits */
    spi->I2SCFG &= 0xF040;
    spi->I2SPSC  = 0x0002;

    if (i2sConfig->audioDiv == I2S_AUDIO_DIV_DEFAULT)
    {
        i2sDiv = 2;
        i2sOdd = 0;
    }
    else
    {
        if (i2sConfig->length == I2S_DATA_LENGHT_16B)
        {
            packetSize = 1;
        }
        else
        {
            packetSize = 2;
        }

        sysClock = RCM_ReadSYSCLKFreq();

        if (i2sConfig->MCLKOutput == I2S_MCLK_OUTPUT_ENABLE)
        {
            tmp = (uint16_t)(((((sysClock / 256) * 10) / i2sConfig->audioDiv)) + 5);
        }
        else
        {
            tmp = (uint16_t)(((((sysClock / (32 * packetSize)) * 10) / i2sConfig->audioDiv)) + 5);
        }

        tmp = tmp / 10;

        i2sOdd = (uint16_t)(tmp & (uint16_t)0x0001);
        i2sDiv = (uint16_t)((tmp - i2sOdd) / 2);

        if ((i2sDiv < 2) || (i2sDiv > 0xFF))
        {
            i2sDiv = 2;
            i2sOdd = 0;
        }
    }

    spi->I2SPSC_B.I2SPSC = i2sDiv;
    spi->I2SPSC_B.ODDPSC = i2sOdd;
    spi->I2SPSC_B.MCOEN  = i2sConfig->MCLKOutput;

    spi->I2SCFG_B.I2SMOD  = i2sConfig->mode;
    spi->I2SCFG_B.I2SSSEL = i2sConfig->standard & 0x03;
    spi->I2SCFG_B.PFSSEL  = (i2sConfig->standard & 0x10) >> 4;
    spi->I2SCFG_B.CHLEN   = i2sConfig->length & 0x01;
    spi->I2SCFG_B.DATLEN  = i2sConfig->length >> 1;
    spi->I2SCFG_B.CPOL    = i2sConfig->polarity;

    /** select I2S mode */
    spi->I2SCFG_B.MODESEL = BIT_SET;
}

/*!
 * @brief     Fills each SPI_Config_T member with its default value
 *
 * @param     spiConfig: pointer to a SPI_Config_T structure
 *
 * @retval    None
 */
void SPI_ConfigStructInit(SPI_Config_T* spiConfig)
{
    spiConfig->direction     = SPI_DIRECTION_2LINES_FULLDUPLEX;
    spiConfig->mode          = SPI_MODE_SLAVE;
    spiConfig->length        = SPI_DATA_LENGTH_8B;
    spiConfig->polarity      = SPI_CLKPOL_LOW;
    spiConfig->phase         = SPI_CLKPHA_1EDGE;
    spiConfig->nss           = SPI_NSS_HARD;
    spiConfig->baudrateDiv   = SPI_BAUDRATE_DIV_2;
    spiConfig->firstBit      = SPI_FIRSTBIT_MSB;
    spiConfig->crcPolynomial = 7;
}

/*!
 * @brief     Fills each I2S_Config_T member with its default value
 *
 * @param     i2sConfig: pointer to a I2S_Config_T structure
 *
 * @retval    None
 */
void I2S_ConfigStructInit(I2S_Config_T* i2sConfig)
{
    i2sConfig->mode       = I2S_MODE_SLAVE_TX;
    i2sConfig->standard   = I2S_STANDARD_PHILLIPS;
    i2sConfig->length     = I2S_DATA_LENGHT_16B;
    i2sConfig->MCLKOutput = I2S_MCLK_OUTPUT_DISABLE;
    i2sConfig->audioDiv   = I2S_AUDIO_DIV_DEFAULT;
    i2sConfig->polarity   = I2S_CLKPOL_LOW;
}

/*!
 * @brief     Enables the specified SPI peripheral
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6.
 *
 * @retval    None
 */
void SPI_Enable(SPI_T* spi)
{
    spi->CTRL1_B.SPIEN = BIT_SET;
}

/*!
* @brief     Disable the specified SPI peripheral
*
* @param     spi: The SPIx can be 1,2,3,4,5,6.
*
* @retval    None
*/
void SPI_Disable(SPI_T* spi)
{
    spi->CTRL1_B.SPIEN = BIT_RESET;
}

/*!
 * @brief     Enables the specified I2S peripheral
 *
 * @param     spi: The I2S can be SPI2,SPI3
 *
 * @retval    None
 */
void I2S_Enable(SPI_T* spi)
{
    spi->I2SCFG_B.I2SEN = BIT_SET;
}

/*!
 * @brief     Disable the specified I2S peripheral
 *
 * @param     spi: The I2S can be SPI2,SPI3
 *
 * @retval    None
 */
void I2S_Disable(SPI_T* spi)
{
    spi->I2SCFG_B.I2SEN = BIT_RESET;
}

/*!
 * @brief     Configures the data size for the selected SPI.
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6.
 *
 * @param     length: specifies the SPI data size.
 *                    This parameter can be one of the following values:
 *                    @arg SPI_DATA_LENGTH_16B : Set data frame format to 16bit
 *                    @arg SPI_DATA_LENGTH_8B  : Set data frame format to 8bit
 *
 * @retval    None
 */
void SPI_ConfigDataSize(SPI_T* spi, SPI_DATA_LENGTH_T length)
{
    spi->CTRL1_B.DFLSEL = length;
}

/*!
 * @brief     Configures the specified SPI data transfer direction
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6.
 *
 * @param     direction: Select the SPI data transfer direction
 *                      The parameter can be one of following values:
 *                      @arg SPI_DIRECTION_RX : Selects Rx receive direction
 *                      @arg SPI_DIRECTION_TX : Selects Tx transmission direction
 * @retval    None
 */
void SPI_ConfigBiDirectionalLine(SPI_T* spi, SPI_DIRECTION_SELECT_T direction)
{
    spi->CTRL1_B.BMOEN = direction;
}
/*!
 * @brief     Set the SPI NSS internal by Software
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6.
 *
 * @retval    None
 */
void SPI_SetSoftwareNSS(SPI_T* spi)
{
    spi->CTRL1_B.ISSEL = BIT_SET;
}

/*!
 * @brief     Reset the SPI NSS internal by Software
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6.
 *
 * @retval    None
 */
void SPI_ResetSoftwareNSS(SPI_T* spi)
{
    spi->CTRL1_B.ISSEL = BIT_RESET;
}

/*!
 * @brief     Enables the specified SPI SS output
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6.
 *
 * @retval    None
 */
void SPI_EnableSSOutput(SPI_T* spi)
{
    spi->CTRL2_B.SSOEN = BIT_SET;
}

/*!
 * @brief     Disable the specified SPI SS output
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6.
 *
 * @retval    None
 */
void SPI_DisableSSOutput(SPI_T* spi)
{
    spi->CTRL2_B.SSOEN = BIT_RESET;
}

/*!
 * @brief     Enables the specified SPI TI mode
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6.
 *
 * @retval    None
 */
void SPI_EnableTIMode(SPI_T* spi)
{
    spi->CTRL2_B.FRFCFG = BIT_SET;
}

/*!
* @brief     Disable the specified SPI TI mode
*
* @param     spi: The SPIx can be 1,2,3,4,5,6.
*
* @retval    None
*/
void SPI_DisableTIMode(SPI_T* spi)
{
    spi->CTRL2_B.FRFCFG = BIT_RESET;
}

/*!
 * @brief  Configures the full-duplex mode for the I2S peripheral using its extension
 *         I2S peripheral according to the specified parameters in the i2sConfig.
 *
 * @param  i2sExt: Specified the I2S peripheral extension block.
 *                 The parameter can be one of following values:
 *                 @arg I2S2ext : Extended I2S2
 *                 @arg I2S3ext : Extended I2S3
 *
 * @param  i2sConfig: Pointer to the I2S_Config_T structure.
 *
 * @retval None
 *
 * @note   The structure pointed by i2sConfig parameter should be the same used for
 *         the master I2S peripheral.
 *
 * @note   The I2S full-duplex extension only can be configured in slave mode.
 */
void I2S_ConfigFullDuplex(SPI_T* i2sExt, I2S_Config_T* i2sConfig)
{
    /** Reset I2SCFG and I2SPSC register */
    i2sExt->I2SCFG = 0;
    i2sExt->I2SPSC = 0x0002;

    /** Config the extended I2S */
    if ((i2sConfig->mode == I2S_MODE_MASTER_TX) || (i2sConfig->mode == I2S_MODE_SLAVE_TX))
    {
        i2sExt->I2SCFG_B.I2SMOD  = I2S_MODE_SLAVE_RX;
        i2sExt->I2SCFG_B.I2SSSEL = i2sConfig->standard & 0x03;
        i2sExt->I2SCFG_B.PFSSEL  = (i2sConfig->standard & 0x10) >> 4;
        i2sExt->I2SCFG_B.CHLEN   = i2sConfig->length & 0x01;
        i2sExt->I2SCFG_B.DATLEN  = i2sConfig->length >> 1;
        i2sExt->I2SCFG_B.CPOL    = i2sConfig->polarity;
    }
    else
    {
        i2sExt->I2SCFG_B.I2SMOD  = I2S_MODE_SLAVE_TX;
        i2sExt->I2SCFG_B.I2SSSEL = i2sConfig->standard & 0x03;
        i2sExt->I2SCFG_B.PFSSEL  = (i2sConfig->standard & 0x10) >> 4;
        i2sExt->I2SCFG_B.CHLEN   = i2sConfig->length & 0x01;
        i2sExt->I2SCFG_B.DATLEN  = i2sConfig->length >> 1;
        i2sExt->I2SCFG_B.CPOL    = i2sConfig->polarity;
    }

    i2sExt->I2SCFG_B.MODESEL = BIT_SET;
}

/*!
 * @brief     Transmits a Data through the SPIx/I2Sx peripheral.
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6.
 *
 * @param     data: Data to be transmitted
 *
 * @retval    None
 */
void SPI_I2S_TxData(SPI_T* spi, uint16_t data)
{
    spi->DATA = data;
}

/*!
* @brief     Returns the most recent received data by the SPIx/I2Sx peripheral.
*
* @param     spi: The SPIx can be 1,2,3,4,5,6.
*
* @retval    data :The value of the received data
*
* @retval    None
*/
uint16_t SPI_I2S_RxData(SPI_T* spi)
{
    return spi->DATA;
}

/*!
 * @brief     Enables the specified SPI CRC value calculation of the transferred bytes
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6.
 *
 * @retval    None
 */
void SPI_EnableCRC(SPI_T* spi)
{
    spi->CTRL1_B.CRCEN = BIT_SET;
}

/*!
 * @brief     Disable the specified SPI CRC value calculation of the transferred bytes
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6.
 *
 */
void SPI_DisableCRC(SPI_T* spi)
{
    spi->CTRL1_B.CRCEN = BIT_RESET;
}

/*!
 * @brief     Transmit CRC value
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6.
 *
 * @retval    None
 */
void SPI_TxCRC(SPI_T* spi)
{
    spi->CTRL1_B.CRCNXT = BIT_SET;
}

/*!
 * @brief     Reads the specified SPI transmit CRC register value
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6.
 *
 * @retval    The SPI transmit CRC register value
 */
uint16_t SPI_ReadTxCRC(SPI_T* spi)
{
    return spi->TXCRC_B.TXCRC;
}

/*!
 * @brief     Reads the specified SPI receive CRC register value
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6.
 *
 * @retval    The SPI receive CRC register value
 */
uint16_t SPI_ReadRxCRC(SPI_T* spi)
{
    return spi->RXCRC_B.RXCRC;
}

/*!
 * @brief     Reads the specified SPI CRC Polynomial register value
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6.
 *
 * @retval    The SPI CRC Polynomial register value
 */
uint16_t SPI_ReadCRCPolynomial(SPI_T* spi)
{
    return spi->CRCPOLY_B.CRCPOLY;
}

/*!
 * @brief     Enables the SPIx/I2Sx DMA interface.
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6, When the I2S can be 2,3
 *
 * @param     dmaReq: specifies the SPI/I2S DMA transfer request
 *                     The parameter can be one of following values:
 *                     @arg SPI_I2S_DMA_REQ_TX : Tx buffer DMA transfer request
 *                     @arg SPI_I2S_DMA_REQ_RX : Rx buffer DMA transfer request
 *
 * @retval    None
 */
void SPI_I2S_EnableDMA(SPI_T* spi, SPI_I2S_DMA_REQ_T dmaReq)
{
    if (dmaReq == SPI_I2S_DMA_REQ_TX)
    {
        spi->CTRL2_B.TXDEN = ENABLE;
    }
    else
    {
        spi->CTRL2_B.RXDEN = ENABLE;
    }
}

/*!
 * @brief     Disables the SPIx/I2Sx DMA interface.
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6., When the I2S can be 2,3
 *
 * @param     dmaReq: specifies the SPI/I2S DMA transfer request
 *                     The parameter can be one of following values:
 *                     @arg SPI_I2S_DMA_REQ_TX : Tx buffer DMA transfer request
 *                     @arg SPI_I2S_DMA_REQ_RX : Rx buffer DMA transfer request
 *
 * @retval    None
 */
void SPI_I2S_DisableDMA(SPI_T* spi, SPI_I2S_DMA_REQ_T dmaReq)
{
    if (dmaReq == SPI_I2S_DMA_REQ_TX)
    {
        spi->CTRL2_B.TXDEN = DISABLE;
    }
    else
    {
        spi->CTRL2_B.RXDEN = DISABLE;
    }
}

/*!
 * @brief     Enables the specified SPI/I2S interrupts.
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6., When the I2S can be 2,3
 *
 * @param     interrupt: specifies the TMR interrupts sources
 *                       The parameter can be any combination of following values:
 *                       @arg SPI_I2S_INT_TXBE  : Tx buffer empty interrupt
 *                       @arg SPI_I2S_INT_RXBNE : Rx buffer not empty interrupt
 *                       @arg SPI_I2S_INT_ERR   : Error interrupt
 *
 * @retval       None
 */
void SPI_I2S_EnableInterrupt(SPI_T* spi, uint32_t interrupt)
{
    spi->CTRL2 |= (uint32_t)(interrupt >> 8);
}

/*!
 * @brief     Disables the specified SPI/I2S interrupts.
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6., When the I2S can be 2,3
 *
 * @param     interrupt: specifies the TMR interrupts sources
 *                     The parameter can be any combination of following values:
 *                     @arg SPI_I2S_INT_TXBE  : Tx buffer empty interrupt
 *                     @arg SPI_I2S_INT_RXBNE : Rx buffer not empty interrupt
 *                     @arg SPI_I2S_INT_ERR   : Error interrupt
 *
 * @retval    None
 */
void SPI_I2S_DisableInterrupt(SPI_T* spi, uint32_t interrupt)
{
    spi->CTRL2 &= ~((uint32_t)(interrupt >> 8));
}

/*!
 * @brief     Checks whether the specified SPI/I2S flag is set or not.
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6., When the I2S can be 2,3
 *
 * @param     flag: specifies the SPI/I2S flag to check
 *                  The parameter can be one of following values:
 *                  @arg SPI_FLAG_RXBNE  : Receive buffer not empty flag
 *                  @arg SPI_FLAG_TXBE   : Transmit buffer empty flag
 *                  @arg I2S_FLAG_SCHDIR : Side Channel flag
 *                  @arg I2S_FLAG_UDR    : Underrun Error flag
 *                  @arg SPI_FLAG_CRCE   : CRC Error flag
 *                  @arg SPI_FLAG_ME     : Mode Error flag
 *                  @arg SPI_FLAG_OVR    : Overrun flag
 *                  @arg SPI_FLAG_BSY    : Busy flag
 *
 * @retval     SET or RESET
 */
uint8_t SPI_I2S_ReadStatusFlag(SPI_T* spi, SPI_FLAG_T flag)
{
    return (spi->STS & flag) ? SET : RESET;
}

/*!
 * @brief     Clears the SPIx CRC Error flag
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6.
 *
 * @param     flag: only clears SPI_FLAG_CRCE(CRC Error flag)
 *
 * @retval    None
 *
 * @note      1)SPI_FLAG_OVR: (OverRun error) flag is cleared by software sequence:
 *              a read operation to SPI_DATA register (SPI_I2S_RxData())
 *              followed by a read operation to SPI_STS register (SPI_I2S_ReadStatusFlag()).
 *            2)I2S_FLAG_UDR: (UnderRun error) flag is cleared:
 *              a read operation to SPI_STS register (SPI_I2S_ReadStatusFlag()).
 *            3)SPI_FLAG_ME: (Mode Fault) flag is cleared by software sequence:
 *              a read/write operation to SPI_STS register (SPI_I2S_ReadStatusFlag())
 *              followed by a write operation to SPI_CTRL1 register (SPI_Enable()).
 */
void SPI_I2S_ClearStatusFlag(SPI_T* spi, SPI_FLAG_T flag)
{
    if (flag == SPI_FLAG_CRCE)
    {
        spi->STS_B.CRCEFLG = BIT_RESET;
    }
}

/*!
 * @brief     Checks whether the specified SPI/I2S interrupt has occurred or not.
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6., When the I2S can be 2,3
 *
 * @param     flag: specifies the SPI/I2S interrupt flag to check.
 *                     The parameter can be one of following values:
 *                     @arg SPI_I2S_INT_RXBNE : Receive buffer not empty interrupt flag
 *                     @arg SPI_I2S_INT_TXBE  : Transmit buffer empty interrupt flag
 *                     @arg SPI_I2S_INT_OVR   : Overrun interrupt flag
 *                     @arg SPI_INT_CRCE      : CRC Error interrupt flag
 *                     @arg SPI_INT_ME        :  Mode Error interrupt flag
 *                     @arg I2S_INT_UDR       : Underrun Error interrupt flag
 *
 * @retval       SET or RESET
 */
uint8_t SPI_I2S_ReadIntFlag(SPI_T* spi, SPI_I2S_INT_T flag)
{
    uint32_t intEnable;
    uint32_t intStatus;

    intEnable = (uint32_t)(spi->CTRL2 & (flag >> 8));
    intStatus = (uint32_t)(spi->STS & flag);

    if (intEnable && intStatus)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief     Clears the SPIx CRC Error interrupt flag
 *
 * @param     spi: The SPIx can be 1,2,3,4,5,6.
 *
 * @param     flag: only clears SPI_INT_CRCE(CRC Error interrupt flag)
 *
 * @retval    None
 *
 * @note      1)SPI_I2S_INT_OVR: (OverRun interrupt error) flag is cleared by software sequence:
 *              a read operation to SPI_DATA register (SPI_I2S_RxData())
 *              followed by a read operation to SPI_STS register (SPI_I2S_ReadIntFlag()).
 *            2)I2S_INT_UDR: (UnderRun interrupt error) flag is cleared:
 *              a read operation to SPI_STS register (SPI_I2S_ReadIntFlag()).
 *            3)SPI_INT_ME: (Mode interrupt Fault) flag is cleared by software sequence:
 *              a read/write operation to SPI_STS register (SPI_I2S_ReadIntFlag())
 *              followed by a write operation to SPI_CTRL1 register (SPI_Enable()).
 */
void SPI_I2S_ClearIntFlag(SPI_T* spi, SPI_I2S_INT_T flag)
{
    if (flag == SPI_INT_CRCE)
    {
        spi->STS_B.CRCEFLG = BIT_RESET;
    }

}

/**@} end of group SPI_Functions */
/**@} end of group SPI_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
