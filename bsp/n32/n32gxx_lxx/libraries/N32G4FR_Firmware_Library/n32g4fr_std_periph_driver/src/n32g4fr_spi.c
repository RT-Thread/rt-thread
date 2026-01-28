/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g4fr_spi.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32g4fr_spi.h"
#include "n32g4fr_rcc.h"

/** @addtogroup N32G4FR_StdPeriph_Driver
 * @{
 */

/** @addtogroup SPI
 * @brief SPI driver modules
 * @{
 */

/** @addtogroup SPI_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @addtogroup SPI_Private_Defines
 * @{
 */

/* SPI SPE mask */
#define CTRL1_SPIEN_ENABLE  ((uint16_t)0x0040)
#define CTRL1_SPIEN_DISABLE ((uint16_t)0xFFBF)

/* I2S I2SE mask */
#define I2SCFG_I2SEN_ENABLE  ((uint16_t)0x0400)
#define I2SCFG_I2SEN_DISABLE ((uint16_t)0xFBFF)

/* SPI CRCNext mask */
#define CTRL1_CRCNEXT_ENABLE ((uint16_t)0x1000)

/* SPI CRCEN mask */
#define CTRL1_CRCEN_ENABLE  ((uint16_t)0x2000)
#define CTRL1_CRCEN_DISABLE ((uint16_t)0xDFFF)

/* SPI SSOE mask */
#define CTRL2_SSOEN_ENABLE  ((uint16_t)0x0004)
#define CTRL2_SSOEN_DISABLE ((uint16_t)0xFFFB)

/* SPI registers Masks */
#define CTRL1_CLR_MASK  ((uint16_t)0x3040)
#define I2SCFG_CLR_MASK ((uint16_t)0xF040)

/* SPI or I2S mode selection masks */
#define SPI_MODE_ENABLE ((uint16_t)0xF7FF)
#define I2S_MODE_ENABLE ((uint16_t)0x0800)

/* I2S clock source selection masks */
#define I2S2_CLKSRC  ((uint32_t)(0x00020000))
#define I2S3_CLKSRC  ((uint32_t)(0x00040000))
#define I2S_MUL_MASK ((uint32_t)(0x0000F000))
#define I2S_DIV_MASK ((uint32_t)(0x000000F0))

/**
 * @}
 */

/** @addtogroup SPI_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup SPI_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @addtogroup SPI_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @addtogroup SPI_Private_Functions
 * @{
 */

/**
 * @brief  Deinitializes the SPIx peripheral registers to their default
 *         reset values (Affects also the I2Ss).
 * @param SPIx where x can be 1, 2 or 3 to select the SPI peripheral.
 */
void SPI_I2S_DeInit(SPI_Module* SPIx)
{
    /* Check the parameters */
    assert_param(IS_SPI_PERIPH(SPIx));

    if (SPIx == SPI1)
    {
        /* Enable SPI1 reset state */
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_SPI1, ENABLE);
        /* Release SPI1 from reset state */
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_SPI1, DISABLE);
    }
    else if (SPIx == SPI2)
    {
        /* Enable SPI2 reset state */
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_SPI2, ENABLE);
        /* Release SPI2 from reset state */
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_SPI2, DISABLE);
    }
    else
    {
        if (SPIx == SPI3)
        {
            /* Enable SPI3 reset state */
            RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_SPI3, ENABLE);
            /* Release SPI3 from reset state */
            RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_SPI3, DISABLE);
        }
    }
}

/**
 * @brief  Initializes the SPIx peripheral according to the specified
 *         parameters in the SPI_InitStruct.
 * @param SPIx where x can be 1, 2 or 3 to select the SPI peripheral.
 * @param SPI_InitStruct pointer to a SPI_InitType structure that
 *         contains the configuration information for the specified SPI peripheral.
 */
void SPI_Init(SPI_Module* SPIx, SPI_InitType* SPI_InitStruct)
{
    uint16_t tmpregister = 0;

    /* check the parameters */
    assert_param(IS_SPI_PERIPH(SPIx));

    /* Check the SPI parameters */
    assert_param(IS_SPI_DIR_MODE(SPI_InitStruct->DataDirection));
    assert_param(IS_SPI_MODE(SPI_InitStruct->SpiMode));
    assert_param(IS_SPI_DATASIZE(SPI_InitStruct->DataLen));
    assert_param(IS_SPI_CLKPOL(SPI_InitStruct->CLKPOL));
    assert_param(IS_SPI_CLKPHA(SPI_InitStruct->CLKPHA));
    assert_param(IS_SPI_NSS(SPI_InitStruct->NSS));
    assert_param(IS_SPI_BR_PRESCALER(SPI_InitStruct->BaudRatePres));
    assert_param(IS_SPI_FIRST_BIT(SPI_InitStruct->FirstBit));
    assert_param(IS_SPI_CRC_POLYNOMIAL(SPI_InitStruct->CRCPoly));

    /*---------------------------- SPIx CTRL1 Configuration ------------------------*/
    /* Get the SPIx CTRL1 value */
    tmpregister = SPIx->CTRL1;
    /* Clear BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, MSTR, CPOL and CPHA bits */
    tmpregister &= CTRL1_CLR_MASK;
    /* Configure SPIx: direction, NSS management, first transmitted bit, BaudRate prescaler
       master/salve mode, CPOL and CPHA */
    /* Set BIDImode, BIDIOE and RxONLY bits according to DataDirection value */
    /* Set SSM, SSI and MSTR bits according to SpiMode and NSS values */
    /* Set LSBFirst bit according to FirstBit value */
    /* Set BR bits according to BaudRatePres value */
    /* Set CPOL bit according to CLKPOL value */
    /* Set CPHA bit according to CLKPHA value */
    tmpregister |= (uint16_t)((uint32_t)SPI_InitStruct->DataDirection | SPI_InitStruct->SpiMode
                              | SPI_InitStruct->DataLen | SPI_InitStruct->CLKPOL | SPI_InitStruct->CLKPHA
                              | SPI_InitStruct->NSS | SPI_InitStruct->BaudRatePres | SPI_InitStruct->FirstBit);
    /* Write to SPIx CTRL1 */
    SPIx->CTRL1 = tmpregister;

    /* Activate the SPI mode (Reset I2SMOD bit in I2SCFG register) */
    SPIx->I2SCFG &= SPI_MODE_ENABLE;

    /*---------------------------- SPIx CRCPOLY Configuration --------------------*/
    /* Write to SPIx CRCPOLY */
    SPIx->CRCPOLY = SPI_InitStruct->CRCPoly;
}

/**
 * @brief  Initializes the SPIx peripheral according to the specified
 *         parameters in the I2S_InitStruct.
 * @param SPIx where x can be  2 or 3 to select the SPI peripheral
 *         (configured in I2S mode).
 * @param I2S_InitStruct pointer to an I2S_InitType structure that
 *         contains the configuration information for the specified SPI peripheral
 *         configured in I2S mode.
 * @note
 *  The function calculates the optimal prescaler needed to obtain the most
 *  accurate audio frequency (depending on the I2S clock source, the PLL values
 *  and the product configuration). But in case the prescaler value is greater
 *  than 511, the default value (0x02) will be configured instead.  *
 */
void I2S_Init(SPI_Module* SPIx, I2S_InitType* I2S_InitStruct)
{
    uint16_t tmpregister = 0, i2sdiv = 2, i2sodd = 0, packetlength = 1;
    uint32_t tmp = 0;
    RCC_ClocksType RCC_Clocks;
    uint32_t sourceclock = 0;

    /* Check the I2S parameters */
    assert_param(IS_SPI_2OR3_PERIPH(SPIx));
    assert_param(IS_I2S_MODE(I2S_InitStruct->I2sMode));
    assert_param(IS_I2S_STANDARD(I2S_InitStruct->Standard));
    assert_param(IS_I2S_DATA_FMT(I2S_InitStruct->DataFormat));
    assert_param(IS_I2S_MCLK_ENABLE(I2S_InitStruct->MCLKEnable));
    assert_param(IS_I2S_AUDIO_FREQ(I2S_InitStruct->AudioFrequency));
    assert_param(IS_I2S_CLKPOL(I2S_InitStruct->CLKPOL));

    /*----------------------- SPIx I2SCFG & I2SPREDIV Configuration -----------------*/
    /* Clear I2SMOD, I2SE, MODCFG, PCMSYNC, STDSEL, CKPOL, TDATLEN and CHLEN bits */
    SPIx->I2SCFG &= I2SCFG_CLR_MASK;
    SPIx->I2SPREDIV = 0x0002;

    /* Get the I2SCFG register value */
    tmpregister = SPIx->I2SCFG;

    /* If the default value has to be written, reinitialize i2sdiv and i2sodd*/
    if (I2S_InitStruct->AudioFrequency == I2S_AUDIO_FREQ_DEFAULT)
    {
        i2sodd = (uint16_t)0;
        i2sdiv = (uint16_t)2;
    }
    /* If the requested audio frequency is not the default, compute the prescaler */
    else
    {
        /* Check the frame length (For the Prescaler computing) */
        if (I2S_InitStruct->DataFormat == I2S_DATA_FMT_16BITS)
        {
            /* Packet length is 16 bits */
            packetlength = 1;
        }
        else
        {
            /* Packet length is 32 bits */
            packetlength = 2;
        }

        /* Get the I2S clock source mask depending on the peripheral number */
        if (((uint32_t)SPIx) == SPI2_BASE)
        {
            /* The mask is relative to I2S2 */
            tmp = I2S2_CLKSRC;
        }
        else
        {
            /* The mask is relative to I2S3 */
            tmp = I2S3_CLKSRC;
        }

        /* I2S Clock source is System clock: Get System Clock frequency */
        RCC_GetClocksFreqValue(&RCC_Clocks);

        /* Get the source clock value: based on System Clock value */
        sourceclock = RCC_Clocks.SysclkFreq;

        /* Compute the Real divider depending on the MCLK output state with a floating point */
        if (I2S_InitStruct->MCLKEnable == I2S_MCLK_ENABLE)
        {
            /* MCLK output is enabled */
            tmp = (uint16_t)(((((sourceclock / 256) * 10) / I2S_InitStruct->AudioFrequency)) + 5);
        }
        else
        {
            /* MCLK output is disabled */
            tmp = (uint16_t)(((((sourceclock / (32 * packetlength)) * 10) / I2S_InitStruct->AudioFrequency)) + 5);
        }

        /* Remove the floating point */
        tmp = tmp / 10;

        /* Check the parity of the divider */
        i2sodd = (uint16_t)(tmp & (uint16_t)0x0001);

        /* Compute the i2sdiv prescaler */
        i2sdiv = (uint16_t)((tmp - i2sodd) / 2);

        /* Get the Mask for the Odd bit (SPI_I2SPREDIV[8]) register */
        i2sodd = (uint16_t)(i2sodd << 8);
    }

    /* Test if the divider is 1 or 0 or greater than 0xFF */
    if ((i2sdiv < 2) || (i2sdiv > 0xFF))
    {
        /* Set the default values */
        i2sdiv = 2;
        i2sodd = 0;
    }

    /* Write to SPIx I2SPREDIV register the computed value */
    SPIx->I2SPREDIV = (uint16_t)(i2sdiv | (uint16_t)(i2sodd | (uint16_t)I2S_InitStruct->MCLKEnable));

    /* Configure the I2S with the SPI_InitStruct values */
    tmpregister |= (uint16_t)(
        I2S_MODE_ENABLE
        | (uint16_t)(I2S_InitStruct->I2sMode
                     | (uint16_t)(I2S_InitStruct->Standard
                                  | (uint16_t)(I2S_InitStruct->DataFormat | (uint16_t)I2S_InitStruct->CLKPOL))));

    /* Write to SPIx I2SCFG */
    SPIx->I2SCFG = tmpregister;
}

/**
 * @brief  Fills each SPI_InitStruct member with its default value.
 * @param SPI_InitStruct pointer to a SPI_InitType structure which will be initialized.
 */
void SPI_InitStruct(SPI_InitType* SPI_InitStruct)
{
    /*--------------- Reset SPI init structure parameters values -----------------*/
    /* Initialize the DataDirection member */
    SPI_InitStruct->DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    /* initialize the SpiMode member */
    SPI_InitStruct->SpiMode = SPI_MODE_SLAVE;
    /* initialize the DataLen member */
    SPI_InitStruct->DataLen = SPI_DATA_SIZE_8BITS;
    /* Initialize the CLKPOL member */
    SPI_InitStruct->CLKPOL = SPI_CLKPOL_LOW;
    /* Initialize the CLKPHA member */
    SPI_InitStruct->CLKPHA = SPI_CLKPHA_FIRST_EDGE;
    /* Initialize the NSS member */
    SPI_InitStruct->NSS = SPI_NSS_HARD;
    /* Initialize the BaudRatePres member */
    SPI_InitStruct->BaudRatePres = SPI_BR_PRESCALER_2;
    /* Initialize the FirstBit member */
    SPI_InitStruct->FirstBit = SPI_FB_MSB;
    /* Initialize the CRCPoly member */
    SPI_InitStruct->CRCPoly = 7;
}

/**
 * @brief  Fills each I2S_InitStruct member with its default value.
 * @param I2S_InitStruct pointer to a I2S_InitType structure which will be initialized.
 */
void I2S_InitStruct(I2S_InitType* I2S_InitStruct)
{
    /*--------------- Reset I2S init structure parameters values -----------------*/
    /* Initialize the I2sMode member */
    I2S_InitStruct->I2sMode = I2S_MODE_SlAVE_TX;

    /* Initialize the Standard member */
    I2S_InitStruct->Standard = I2S_STD_PHILLIPS;

    /* Initialize the DataFormat member */
    I2S_InitStruct->DataFormat = I2S_DATA_FMT_16BITS;

    /* Initialize the MCLKEnable member */
    I2S_InitStruct->MCLKEnable = I2S_MCLK_DISABLE;

    /* Initialize the AudioFrequency member */
    I2S_InitStruct->AudioFrequency = I2S_AUDIO_FREQ_DEFAULT;

    /* Initialize the CLKPOL member */
    I2S_InitStruct->CLKPOL = I2S_CLKPOL_LOW;
}

/**
 * @brief  Enables or disables the specified SPI peripheral.
 * @param SPIx where x can be 1, 2 or 3 to select the SPI peripheral.
 * @param Cmd new state of the SPIx peripheral.
 *   This parameter can be: ENABLE or DISABLE.
 */
void SPI_Enable(SPI_Module* SPIx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_SPI_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI peripheral */
        SPIx->CTRL1 |= CTRL1_SPIEN_ENABLE;
    }
    else
    {
        /* Disable the selected SPI peripheral */
        SPIx->CTRL1 &= CTRL1_SPIEN_DISABLE;
    }
}

/**
 * @brief  Enables or disables the specified SPI peripheral (in I2S mode).
 * @param SPIx where x can be 2 or 3 to select the SPI peripheral.
 * @param Cmd new state of the SPIx peripheral.
 *   This parameter can be: ENABLE or DISABLE.
 */
void I2S_Enable(SPI_Module* SPIx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_SPI_2OR3_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI peripheral (in I2S mode) */
        SPIx->I2SCFG |= I2SCFG_I2SEN_ENABLE;
    }
    else
    {
        /* Disable the selected SPI peripheral (in I2S mode) */
        SPIx->I2SCFG &= I2SCFG_I2SEN_DISABLE;
    }
}

/**
 * @brief  Enables or disables the specified SPI/I2S interrupts.
 * @param SPIx where x can be
 *   - 1, 2 or 3 in SPI mode
 *   - 2 or 3 in I2S mode
 * @param SPI_I2S_IT specifies the SPI/I2S interrupt source to be enabled or disabled.
 *   This parameter can be one of the following values:
 *     @arg SPI_I2S_INT_TE Tx buffer empty interrupt mask
 *     @arg SPI_I2S_INT_RNE Rx buffer not empty interrupt mask
 *     @arg SPI_I2S_INT_ERR Error interrupt mask
 * @param Cmd new state of the specified SPI/I2S interrupt.
 *   This parameter can be: ENABLE or DISABLE.
 */
void SPI_I2S_EnableInt(SPI_Module* SPIx, uint8_t SPI_I2S_IT, FunctionalState Cmd)
{
    uint16_t itpos = 0, itmask = 0;
    /* Check the parameters */
    assert_param(IS_SPI_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    assert_param(IS_SPI_I2S_CONFIG_INT(SPI_I2S_IT));

    /* Get the SPI/I2S IT index */
    itpos = SPI_I2S_IT >> 4;

    /* Set the IT mask */
    itmask = (uint16_t)1 << (uint16_t)itpos;

    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI/I2S interrupt */
        SPIx->CTRL2 |= itmask;
    }
    else
    {
        /* Disable the selected SPI/I2S interrupt */
        SPIx->CTRL2 &= (uint16_t)~itmask;
    }
}

/**
 * @brief  Enables or disables the SPIx/I2Sx DMA interface.
 * @param SPIx where x can be
 *   - 1, 2 or 3 in SPI mode
 *   - 2 or 3 in I2S mode
 * @param SPI_I2S_DMAReq specifies the SPI/I2S DMA transfer request to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg SPI_I2S_DMA_TX Tx buffer DMA transfer request
 *     @arg SPI_I2S_DMA_RX Rx buffer DMA transfer request
 * @param Cmd new state of the selected SPI/I2S DMA transfer request.
 *   This parameter can be: ENABLE or DISABLE.
 */
void SPI_I2S_EnableDma(SPI_Module* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_SPI_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    assert_param(IS_SPI_I2S_DMA(SPI_I2S_DMAReq));
    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI/I2S DMA requests */
        SPIx->CTRL2 |= SPI_I2S_DMAReq;
    }
    else
    {
        /* Disable the selected SPI/I2S DMA requests */
        SPIx->CTRL2 &= (uint16_t)~SPI_I2S_DMAReq;
    }
}

/**
 * @brief  Transmits a Data through the SPIx/I2Sx peripheral.
 * @param SPIx where x can be
 *   - 1, 2 or 3 in SPI mode
 *   - 2 or 3 in I2S mode
 * @param Data Data to be transmitted.
 */
void SPI_I2S_TransmitData(SPI_Module* SPIx, uint16_t Data)
{
    /* Check the parameters */
    assert_param(IS_SPI_PERIPH(SPIx));

    /* Write in the DAT register the data to be sent */
    SPIx->DAT = Data;
}

/**
 * @brief  Returns the most recent received data by the SPIx/I2Sx peripheral.
 * @param SPIx where x can be
 *   - 1, 2 or 3 in SPI mode
 *   - 2 or 3 in I2S mode
 * @return The value of the received data.
 */
uint16_t SPI_I2S_ReceiveData(SPI_Module* SPIx)
{
    /* Check the parameters */
    assert_param(IS_SPI_PERIPH(SPIx));

    /* Return the data in the DAT register */
    return SPIx->DAT;
}

/**
 * @brief  Configures internally by software the NSS pin for the selected SPI.
 * @param SPIx where x can be 1, 2 or 3 to select the SPI peripheral.
 * @param SPI_NSSInternalSoft specifies the SPI NSS internal state.
 *   This parameter can be one of the following values:
 *     @arg SPI_NSS_HIGH Set NSS pin internally
 *     @arg SPI_NSS_LOW Reset NSS pin internally
 */
void SPI_SetNssLevel(SPI_Module* SPIx, uint16_t SPI_NSSInternalSoft)
{
    /* Check the parameters */
    assert_param(IS_SPI_PERIPH(SPIx));
    assert_param(IS_SPI_NSS_LEVEL(SPI_NSSInternalSoft));
    if (SPI_NSSInternalSoft != SPI_NSS_LOW)
    {
        /* Set NSS pin internally by software */
        SPIx->CTRL1 |= SPI_NSS_HIGH;
    }
    else
    {
        /* Reset NSS pin internally by software */
        SPIx->CTRL1 &= SPI_NSS_LOW;
    }
}

/**
 * @brief  Enables or disables the SS output for the selected SPI.
 * @param SPIx where x can be 1, 2 or 3 to select the SPI peripheral.
 * @param Cmd new state of the SPIx SS output.
 *   This parameter can be: ENABLE or DISABLE.
 */
void SPI_SSOutputEnable(SPI_Module* SPIx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_SPI_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI SS output */
        SPIx->CTRL2 |= CTRL2_SSOEN_ENABLE;
    }
    else
    {
        /* Disable the selected SPI SS output */
        SPIx->CTRL2 &= CTRL2_SSOEN_DISABLE;
    }
}

/**
 * @brief  Configures the data size for the selected SPI.
 * @param SPIx where x can be 1, 2 or 3 to select the SPI peripheral.
 * @param DataLen specifies the SPI data size.
 *   This parameter can be one of the following values:
 *     @arg SPI_DATA_SIZE_16BITS Set data frame format to 16bit
 *     @arg SPI_DATA_SIZE_8BITS Set data frame format to 8bit
 */
void SPI_ConfigDataLen(SPI_Module* SPIx, uint16_t DataLen)
{
    /* Check the parameters */
    assert_param(IS_SPI_PERIPH(SPIx));
    assert_param(IS_SPI_DATASIZE(DataLen));
    /* Clear DFF bit */
    SPIx->CTRL1 &= (uint16_t)~SPI_DATA_SIZE_16BITS;
    /* Set new DFF bit value */
    SPIx->CTRL1 |= DataLen;
}

/**
 * @brief  Transmit the SPIx CRC value.
 * @param SPIx where x can be 1, 2 or 3 to select the SPI peripheral.
 */
void SPI_TransmitCrcNext(SPI_Module* SPIx)
{
    /* Check the parameters */
    assert_param(IS_SPI_PERIPH(SPIx));

    /* Enable the selected SPI CRC transmission */
    SPIx->CTRL1 |= CTRL1_CRCNEXT_ENABLE;
}

/**
 * @brief  Enables or disables the CRC value calculation of the transferred bytes.
 * @param SPIx where x can be 1, 2 or 3 to select the SPI peripheral.
 * @param Cmd new state of the SPIx CRC value calculation.
 *   This parameter can be: ENABLE or DISABLE.
 */
void SPI_EnableCalculateCrc(SPI_Module* SPIx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_SPI_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI CRC calculation */
        SPIx->CTRL1 |= CTRL1_CRCEN_ENABLE;
    }
    else
    {
        /* Disable the selected SPI CRC calculation */
        SPIx->CTRL1 &= CTRL1_CRCEN_DISABLE;
    }
}

/**
 * @brief  Returns the transmit or the receive CRC register value for the specified SPI.
 * @param SPIx where x can be 1, 2 or 3 to select the SPI peripheral.
 * @param SPI_CRC specifies the CRC register to be read.
 *   This parameter can be one of the following values:
 *     @arg SPI_CRC_TX Selects Tx CRC register
 *     @arg SPI_CRC_RX Selects Rx CRC register
 * @return The selected CRC register value..
 */
uint16_t SPI_GetCRCDat(SPI_Module* SPIx, uint8_t SPI_CRC)
{
    uint16_t crcreg = 0;
    /* Check the parameters */
    assert_param(IS_SPI_PERIPH(SPIx));
    assert_param(IS_SPI_CRC(SPI_CRC));
    if (SPI_CRC != SPI_CRC_RX)
    {
        /* Get the Tx CRC register */
        crcreg = SPIx->CRCTDAT;
    }
    else
    {
        /* Get the Rx CRC register */
        crcreg = SPIx->CRCRDAT;
    }
    /* Return the selected CRC register */
    return crcreg;
}

/**
 * @brief  Returns the CRC Polynomial register value for the specified SPI.
 * @param SPIx where x can be 1, 2 or 3 to select the SPI peripheral.
 * @return The CRC Polynomial register value.
 */
uint16_t SPI_GetCRCPoly(SPI_Module* SPIx)
{
    /* Check the parameters */
    assert_param(IS_SPI_PERIPH(SPIx));

    /* Return the CRC polynomial register */
    return SPIx->CRCPOLY;
}

/**
 * @brief  Selects the data transfer direction in bi-directional mode for the specified SPI.
 * @param SPIx where x can be 1, 2 or 3 to select the SPI peripheral.
 * @param DataDirection specifies the data transfer direction in bi-directional mode.
 *   This parameter can be one of the following values:
 *     @arg SPI_BIDIRECTION_TX Selects Tx transmission direction
 *     @arg SPI_BIDIRECTION_RX Selects Rx receive direction
 */
void SPI_ConfigBidirectionalMode(SPI_Module* SPIx, uint16_t DataDirection)
{
    /* Check the parameters */
    assert_param(IS_SPI_PERIPH(SPIx));
    assert_param(IS_SPI_BIDIRECTION(DataDirection));
    if (DataDirection == SPI_BIDIRECTION_TX)
    {
        /* Set the Tx only mode */
        SPIx->CTRL1 |= SPI_BIDIRECTION_TX;
    }
    else
    {
        /* Set the Rx only mode */
        SPIx->CTRL1 &= SPI_BIDIRECTION_RX;
    }
}

/**
 * @brief  Checks whether the specified SPI/I2S flag is set or not.
 * @param SPIx where x can be
 *   - 1, 2 or 3 in SPI mode
 *   - 2 or 3 in I2S mode
 * @param SPI_I2S_FLAG specifies the SPI/I2S flag to check.
 *   This parameter can be one of the following values:
 *     @arg SPI_I2S_TE_FLAG Transmit buffer empty flag.
 *     @arg SPI_I2S_RNE_FLAG Receive buffer not empty flag.
 *     @arg SPI_I2S_BUSY_FLAG Busy flag.
 *     @arg SPI_I2S_OVER_FLAG Overrun flag.
 *     @arg SPI_MODERR_FLAG Mode Fault flag.
 *     @arg SPI_CRCERR_FLAG CRC Error flag.
 *     @arg I2S_UNDER_FLAG Underrun Error flag.
 *     @arg I2S_CHSIDE_FLAG Channel Side flag.
 * @return The new state of SPI_I2S_FLAG (SET or RESET).
 */
FlagStatus SPI_I2S_GetStatus(SPI_Module* SPIx, uint16_t SPI_I2S_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_SPI_PERIPH(SPIx));
    assert_param(IS_SPI_I2S_GET_FLAG(SPI_I2S_FLAG));
    /* Check the status of the specified SPI/I2S flag */
    if ((SPIx->STS & SPI_I2S_FLAG) != (uint16_t)RESET)
    {
        /* SPI_I2S_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* SPI_I2S_FLAG is reset */
        bitstatus = RESET;
    }
    /* Return the SPI_I2S_FLAG status */
    return bitstatus;
}

/**
 * @brief  Clears the SPIx CRC Error (CRCERR) flag.
 * @param SPIx where x can be
 *   - 1, 2 or 3 in SPI mode
 * @param SPI_I2S_FLAG specifies the SPI flag to clear.
 *   This function clears only CRCERR flag.
 * @note
 *   - OVR (OverRun error) flag is cleared by software sequence: a read
 *     operation to SPI_DAT register (SPI_I2S_ReceiveData()) followed by a read
 *     operation to SPI_STS register (SPI_I2S_GetStatus()).
 *   - UDR (UnderRun error) flag is cleared by a read operation to
 *     SPI_STS register (SPI_I2S_GetStatus()).
 *   - MODF (Mode Fault) flag is cleared by software sequence: a read/write
 *     operation to SPI_STS register (SPI_I2S_GetStatus()) followed by a
 *     write operation to SPI_CTRL1 register (SPI_Enable() to enable the SPI).
 */
void SPI_I2S_ClrCRCErrFlag(SPI_Module* SPIx, uint16_t SPI_I2S_FLAG)
{
    /* Check the parameters */
    assert_param(IS_SPI_PERIPH(SPIx));
    assert_param(IS_SPI_I2S_CLR_FLAG(SPI_I2S_FLAG));

    /* Clear the selected SPI CRC Error (CRCERR) flag */
    SPIx->STS = (uint16_t)~SPI_I2S_FLAG;
}

/**
 * @brief  Checks whether the specified SPI/I2S interrupt has occurred or not.
 * @param SPIx where x can be
 *   - 1, 2 or 3 in SPI mode
 *   - 2 or 3 in I2S mode
 * @param SPI_I2S_IT specifies the SPI/I2S interrupt source to check.
 *   This parameter can be one of the following values:
 *     @arg SPI_I2S_INT_TE Transmit buffer empty interrupt.
 *     @arg SPI_I2S_INT_RNE Receive buffer not empty interrupt.
 *     @arg SPI_I2S_INT_OVER Overrun interrupt.
 *     @arg SPI_INT_MODERR Mode Fault interrupt.
 *     @arg SPI_INT_CRCERR CRC Error interrupt.
 *     @arg I2S_INT_UNDER Underrun Error interrupt.
 * @return The new state of SPI_I2S_IT (SET or RESET).
 */
INTStatus SPI_I2S_GetIntStatus(SPI_Module* SPIx, uint8_t SPI_I2S_IT)
{
    INTStatus bitstatus = RESET;
    uint16_t itpos = 0, itmask = 0, enablestatus = 0;

    /* Check the parameters */
    assert_param(IS_SPI_PERIPH(SPIx));
    assert_param(IS_SPI_I2S_GET_INT(SPI_I2S_IT));

    /* Get the SPI/I2S IT index */
    itpos = 0x01 << (SPI_I2S_IT & 0x0F);

    /* Get the SPI/I2S IT mask */
    itmask = SPI_I2S_IT >> 4;

    /* Set the IT mask */
    itmask = 0x01 << itmask;

    /* Get the SPI_I2S_IT enable bit status */
    enablestatus = (SPIx->CTRL2 & itmask);

    /* Check the status of the specified SPI/I2S interrupt */
    if (((SPIx->STS & itpos) != (uint16_t)RESET) && enablestatus)
    {
        /* SPI_I2S_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* SPI_I2S_IT is reset */
        bitstatus = RESET;
    }
    /* Return the SPI_I2S_IT status */
    return bitstatus;
}

/**
 * @brief  Clears the SPIx CRC Error (CRCERR) interrupt pending bit.
 * @param SPIx where x can be
 *   - 1, 2 or 3 in SPI mode
 * @param SPI_I2S_IT specifies the SPI interrupt pending bit to clear.
 *   This function clears only CRCERR interrupt pending bit.
 * @note
 *   - OVR (OverRun Error) interrupt pending bit is cleared by software
 *     sequence: a read operation to SPI_DAT register (SPI_I2S_ReceiveData())
 *     followed by a read operation to SPI_STS register (SPI_I2S_GetIntStatus()).
 *   - UDR (UnderRun Error) interrupt pending bit is cleared by a read
 *     operation to SPI_STS register (SPI_I2S_GetIntStatus()).
 *   - MODF (Mode Fault) interrupt pending bit is cleared by software sequence:
 *     a read/write operation to SPI_STS register (SPI_I2S_GetIntStatus())
 *     followed by a write operation to SPI_CTRL1 register (SPI_Enable() to enable
 *     the SPI).
 */
void SPI_I2S_ClrITPendingBit(SPI_Module* SPIx, uint8_t SPI_I2S_IT)
{
    uint16_t itpos = 0;
    /* Check the parameters */
    assert_param(IS_SPI_PERIPH(SPIx));
    assert_param(IS_SPI_I2S_CLR_INT(SPI_I2S_IT));

    /* Get the SPI IT index */
    itpos = 0x01 << (SPI_I2S_IT & 0x0F);

    /* Clear the selected SPI CRC Error (CRCERR) interrupt pending bit */
    SPIx->STS = (uint16_t)~itpos;
}
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
