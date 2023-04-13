/*!
 * @file        apm32e10x_spi.c
 *
 * @brief       This file provides all the SPI firmware functions
 *
 * @version     V1.0.2
 *
 * @date        2022-12-31
 *
 * @attention
 *
 *  Copyright (C) 2021-2023 Geehy Semiconductor
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

#include "apm32e10x_spi.h"
#include "apm32e10x_rcm.h"

/** @addtogroup APM32E10x_StdPeriphDriver
  @{
*/

/** @addtogroup SPI_Driver
  * @brief SPI driver modules
  @{
*/

/** @defgroup SPI_Functions Functions
  @{
*/

/*!
 * @brief     Reset the specified SPIx peripheral
 *
 * @param     spi: The SPIx can be 1,2,3
 *
 * @retval    None
 */
void SPI_I2S_Reset(SPI_T* spi)
{
    if(spi == SPI1)
    {
        RCM_EnableAPB2PeriphReset(RCM_APB2_PERIPH_SPI1);
        RCM_DisableAPB2PeriphReset(RCM_APB2_PERIPH_SPI1);
    }
    else if(spi == SPI2)
    {
        RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_SPI2);
        RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_SPI2);
    }
    else if(spi == SPI3)
    {
        RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_SPI3);
        RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_SPI3);
    }
}

/*!
 * @brief     Config the SPI peripheral according to the specified parameters in the spiConfig
 *
 * @param     spi: The SPIx can be 1,2,3
 *
 * @param     spiConfig: pointer to a SPI_Config_T structure
 *
 * @retval    None
 */
void SPI_Config(SPI_T* spi, SPI_Config_T* spiConfig)
{
    spi->CTRL1 &= 0x3040;
    spi->CTRL1 |= (uint16_t)((uint32_t)spiConfig->direction | spiConfig->mode |
                   spiConfig->length | spiConfig->polarity |
                   spiConfig->phase | spiConfig->nss |
                   spiConfig->baudrateDiv | spiConfig->firstBit);
    spi->CRCPOLY = spiConfig->crcPolynomial;
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
    spi->I2SPSC = 0x0002;

    if(i2sConfig->audioDiv == I2S_AUDIO_DIV_DEFAULT)
    {
        spi->I2SPSC_B.ODDPSC = 0;
        spi->I2SPSC_B.I2SPSC = 2;
    }
    else
    {
        if(i2sConfig->length == I2S_DATA_LENGHT_16B)
        {
            packetSize = 1;
        }
        else
        {
            packetSize = 2;
        }

        sysClock = RCM_ReadSYSCLKFreq();

        if(i2sConfig->MCLKOutput == I2S_MCLK_OUTPUT_ENABLE)
        {
            tmp = (uint16_t)(((((sysClock / 256) * 10) / i2sConfig ->audioDiv)) + 5);
        }
        else
        {
            tmp = (uint16_t)(((((sysClock / (32 * packetSize)) *10 ) / i2sConfig ->audioDiv )) + 5);
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
    spi->I2SPSC |= i2sConfig->MCLKOutput;

    spi->I2SCFG = (uint32_t)i2sConfig->mode | \
                  (uint32_t)i2sConfig->standard | \
                  (uint32_t)i2sConfig->length | \
                  (uint32_t)i2sConfig->polarity;

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
    spiConfig->direction = SPI_DIRECTION_2LINES_FULLDUPLEX;
    spiConfig->mode = SPI_MODE_SLAVE;
    spiConfig->length = SPI_DATA_LENGTH_8B;
    spiConfig->polarity = SPI_CLKPOL_LOW;
    spiConfig->phase = SPI_CLKPHA_1EDGE;
    spiConfig->nss = SPI_NSS_HARD;
    spiConfig->baudrateDiv = SPI_BAUDRATE_DIV_2;
    spiConfig->firstBit = SPI_FIRSTBIT_MSB;
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
    i2sConfig->mode = I2S_MODE_SLAVE_TX;
    i2sConfig->standard = I2S_STANDARD_PHILLIPS;
    i2sConfig->length = I2S_DATA_LENGHT_16B;
    i2sConfig->MCLKOutput = I2S_MCLK_OUTPUT_DISABLE;
    i2sConfig->audioDiv = I2S_AUDIO_DIV_DEFAULT;
    i2sConfig->polarity = I2S_CLKPOL_LOW;
}
/*!
 * @brief     Enables the specified SPI peripheral
 *
 * @param     spi: The SPIx can be 1,2,3
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
 * @param     spi: The SPIx can be 1,2,3
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
 * @brief     Enables the SPIx/I2Sx DMA interface.
 *
 * @param     spi: The SPIx can be 1,2,3, When the I2S can be 2,3
 *
 * @param     dmaReq: specifies the SPI/I2S DMA transfer request
 *                     The parameter can be one of following values:
 *                     @arg SPI_I2S_DMA_REQ_TX: Tx buffer DMA transfer request
 *                     @arg SPI_I2S_DMA_REQ_RX: Rx buffer DMA transfer request
 * @retval    None
 */
void SPI_I2S_EnableDMA(SPI_T* spi, SPI_I2S_DMA_REQ_T dmaReq)
{
    if(dmaReq == SPI_I2S_DMA_REQ_TX)
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
 * @param     spi: The SPIx can be 1,2,3, When the I2S can be 2,3
 *
 * @param     dmaReq: specifies the SPI/I2S DMA transfer request
 *                     The parameter can be one of following values:
 *                     @arg SPI_I2S_DMA_REQ_TX: Tx buffer DMA transfer request
 *                     @arg SPI_I2S_DMA_REQ_RX: Rx buffer DMA transfer request
 * @retval    None
 */
void SPI_I2S_DisableDMA(SPI_T* spi, SPI_I2S_DMA_REQ_T dmaReq)
{
    if(dmaReq == SPI_I2S_DMA_REQ_TX)
    {
        spi->CTRL2_B.TXDEN = DISABLE;
    }
    else
    {
        spi->CTRL2_B.RXDEN = DISABLE;
    }
}

/*!
 * @brief     Transmits a Data through the SPIx/I2Sx peripheral.
 *
 * @param     spi: The SPIx can be 1,2,3, When the I2S can be 2,3
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
 * @param     spi: The SPIx can be 1,2,3, When the I2S can be 2,3
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
 * @brief     Set the SPI NSS internal by Software
 *
 * @param     spi: The SPIx can be 1,2,3
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
 * @param     spi: The SPIx can be 1,2,3
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
 * @param     spi: The SPIx can be 1,2,3
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
 * @param     spi: The SPIx can be 1,2,3
 *
 * @retval    None
 */
void SPI_DisableSSOutput(SPI_T* spi)
{
    spi->CTRL2_B.SSOEN = BIT_RESET;
}

/*!
 * @brief     Configures the specified SPI data size
 *
 * @param     spi: The SPIx can be 1,2,3
 *
 * @param     length: specifies the SPI data size.
 *                    This parameter can be one of the following values:
 *                    @arg SPI_DATA_LENGTH_16B: Set data frame format to 16bit
 *                    @arg SPI_DATA_LENGTH_8B : Set data frame format to 8bit
 *
 * @retval    None
 */
void SPI_ConfigDataSize(SPI_T* spi, SPI_DATA_LENGTH_T length)
{
    spi->CTRL1_B.DFLSEL = BIT_RESET;
    spi->CTRL1 |= length;
}

/*!
 * @brief     Transmit CRC value
 *
 * @param     spi: The SPIx can be 1,2,3
 *
 * @retval    None
 */
void SPI_TxCRC(SPI_T* spi)
{
    spi->CTRL1_B.CRCNXT = BIT_SET;
}

/*!
 * @brief     Enables the specified SPI CRC value calculation of the transferred bytes
 *
 * @param     spi: The SPIx can be 1,2,3
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
 * @param     spi: The SPIx can be 1,2,3
 *
 */
void SPI_DisableCRC(SPI_T* spi)
{
    spi->CTRL1_B.CRCEN = BIT_RESET;
}

/*!
 * @brief     Reads the specified SPI transmit CRC register value
 *
 * @param     spi: The SPIx can be 1,2,3
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
 * @param     spi: The SPIx can be 1,2,3
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
 * @param     spi: The SPIx can be 1,2,3
 *
 * @retval    The SPI CRC Polynomial register value
 */
uint16_t SPI_ReadCRCPolynomial(SPI_T* spi)
{
    return spi->CRCPOLY_B.CRCPOLY;
}

/*!
 * @brief     Configures the specified SPI data transfer direction
 *
 * @param     spi: The SPIx can be 1,2,3
 *
 * @param     direction: Select the SPI data transfer direction
 *                     The parameter can be one of following values:
 *                     @arg SPI_DIRECTION_RX: Selects Rx receive direction
 *                     @arg SPI_DIRECTION_TX: Selects Tx transmission direction
 * @retval    None
 */
void SPI_ConfigBiDirectionalLine(SPI_T* spi, SPI_DIRECTION_SELECT_T direction)
{
    if(direction == SPI_DIRECTION_TX)
    {
        spi->CTRL1 |= SPI_DIRECTION_TX;
    }
    else
    {
        spi->CTRL1 &= SPI_DIRECTION_RX;
    }
}

/*!
 * @brief     Enables the specified SPI/I2S interrupts.
 *
 * @param     spi: The SPIx can be 1,2,3, When the I2S can be 2,3
 *
 * @param     interrupt: specifies the TMR interrupts sources
 *                     The parameter can be one of following values:
 *                     @arg SPI_I2S_INT_TXBE: Tx buffer empty interrupt
 *                     @arg SPI_I2S_INT_RXBNE: Rx buffer not empty interrupt
 *                     @arg SPI_I2S_INT_ERR: Error interrupt
 * @retval       None
 */
void SPI_I2S_EnableInterrupt(SPI_T* spi, SPI_I2S_INT_T interrupt)
{
     spi->CTRL2 |= (interrupt >> 8);
}

/*!
 * @brief     Disables the specified SPI/I2S interrupts.
 *
 * @param     spi: The SPIx can be 1,2,3, When the I2S can be 2,3
 *
 * @param     interrupt: specifies the TMR interrupts sources
 *                     The parameter can be one of following values:
 *                     @arg SPI_I2S_INT_TXBE: Tx buffer empty interrupt
 *                     @arg SPI_I2S_INT_RXBNE: Rx buffer not empty interrupt
 *                     @arg SPI_I2S_INT_ERR: Error interrupt
 * @retval    None
 */
void SPI_I2S_DisableInterrupt(SPI_T* spi, SPI_I2S_INT_T interrupt)
{
         spi->CTRL2 &= ~(interrupt >> 8);
}

/*!
 * @brief     Checks whether the specified SPI/I2S flag is set or not.
 *
 * @param     spi: The SPIx can be 1,2,3, When the I2S can be 2,3
 *
 * @param     flag: specifies the SPI/I2S flag to check
 *                     The parameter can be one of following values:
 *                     @arg SPI_FLAG_RXBNE: Receive buffer not empty flag
 *                     @arg SPI_FLAG_TXBE: Transmit buffer empty flag
 *                     @arg I2S_FLAG_SCHDIR: Side Channel flag
 *                     @arg I2S_FLAG_UDR: Underrun Error flag
 *                     @arg SPI_FLAG_CRCE: CRC Error flag
 *                     @arg SPI_FLAG_ME: Mode Error flag
 *                     @arg SPI_FLAG_OVR: Overrun flag
 *                     @arg SPI_FLAG_BSY: Busy flag
 *
 * @retval     SET or RESET
 */
uint8_t SPI_I2S_ReadStatusFlag(SPI_T* spi, SPI_FLAG_T flag)
{
    if((spi->STS & flag) != RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/*!
 * @brief     Clears the SPIx CRC Error flag
 *
 * @param     spi: The SPIx can be 1,2,3
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
    spi->STS_B.CRCEFLG = BIT_RESET;
}

/*!
 * @brief     Checks whether the specified SPI/I2S interrupt has occurred or not.
 *
 * @param     spi: The SPIx can be 1,2,3, When the I2S can be 2,3
 *
 * @param     flag: specifies the SPI/I2S interrupt flag to check.
 *                     The parameter can be one of following values:
 *                     @arg SPI_I2S_INT_RXBNE: Receive buffer not empty interrupt flag
 *                     @arg SPI_I2S_INT_TXBE: Transmit buffer empty interrupt flag
 *                     @arg SPI_I2S_INT_OVR: Overrun interrupt flag
 *                     @arg SPI_INT_CRCE: CRC Error interrupt flag
 *                     @arg SPI_INT_ME:  Mode Error interrupt flag
 *                     @arg I2S_INT_UDR: Underrun Error interrupt flag
 *
 * @retval       SET or RESET
 */
uint8_t SPI_I2S_ReadIntFlag(SPI_T* spi, SPI_I2S_INT_T flag)
{
    uint32_t intEnable;
    uint32_t intStatus;

    intEnable = (uint32_t)(spi->CTRL2 & (flag>>8));
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
 * @param     spi: The SPIx can be 1,2,3
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
    spi->STS_B.CRCEFLG = BIT_RESET;
}

/**@} end of group SPI_Functions */
/**@} end of group SPI_Driver */
/**@} end of group APM32E10x_StdPeriphDriver */
