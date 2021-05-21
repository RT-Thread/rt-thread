/**************************************************************************//**
 * @file     spi.c
 * @version  V1.00
 * $Revision: 4 $
 * $Date: 18/04/25 11:43a $
 * @brief    M031 series SPI driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "M031Series.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SPI_Driver SPI Driver
  @{
*/


/** @addtogroup SPI_EXPORTED_FUNCTIONS SPI Exported Functions
  @{
*/

/**
  * @brief  This function make SPI module be ready to transfer.
  * @param[in]  spi The pointer of the specified SPI module.
  * @param[in]  u32MasterSlave Decides the SPI module is operating in master mode or in slave mode. (SPI_SLAVE, SPI_MASTER)
  * @param[in]  u32SPIMode Decides the transfer timing. (SPI_MODE_0, SPI_MODE_1, SPI_MODE_2, SPI_MODE_3)
  * @param[in]  u32DataWidth Decides the data width of a SPI transaction.
  * @param[in]  u32BusClock The expected frequency of SPI bus clock in Hz.
  * @return Actual frequency of SPI peripheral clock.
  * @details By default, the SPI transfer sequence is MSB first, the slave selection signal is active low and the automatic
  *          slave selection function is disabled.
  *          In Slave mode, the u32BusClock shall be NULL and the SPI clock divider setting will be 0.
  *          The actual clock rate may be different from the target SPI clock rate.
  *          For example, if the SPI source clock rate is 12 MHz and the target SPI bus clock rate is 7 MHz, the
  *          actual SPI clock rate will be 6MHz.
  * @note   If u32BusClock = 0, DIVIDER setting will be set to the maximum value.
  * @note   If u32BusClock >= system clock frequency, SPI peripheral clock source will be set to APB clock and DIVIDER will be set to 0.
  * @note   If u32BusClock >= SPI peripheral clock source, DIVIDER will be set to 0.
  * @note   In slave mode, the SPI peripheral clock rate will be equal to APB clock rate.
  */
uint32_t SPI_Open(SPI_T *spi,
                  uint32_t u32MasterSlave,
                  uint32_t u32SPIMode,
                  uint32_t u32DataWidth,
                  uint32_t u32BusClock)
{
    uint32_t u32ClkSrc = 0, u32Div, u32HCLKFreq;

    /* check SPI interface */
    if (spi != SPI0) return SPI_NONE;

    /* Disable I2S mode */
    spi->I2SCTL &= ~SPI_I2SCTL_I2SEN_Msk;

    if (u32DataWidth == 32)
        u32DataWidth = 0;

    /* Get system clock frequency */
    u32HCLKFreq = CLK_GetHCLKFreq();

    if (u32MasterSlave == SPI_MASTER)
    {
        /* Default setting: slave selection signal is active low; disable automatic slave selection function. */
        spi->SSCTL = SPI_SS_ACTIVE_LOW;

        /* Default setting: MSB first, disable unit transfer interrupt, SP_CYCLE = 0. */
        spi->CTL = u32MasterSlave | (u32DataWidth << SPI_CTL_DWIDTH_Pos) | (u32SPIMode) | SPI_CTL_SPIEN_Msk;

        if (u32BusClock >= u32HCLKFreq)
        {
            /* Select PCLK as the clock source of SPI */
            if (spi == SPI0)
                CLK->CLKSEL2 = (CLK->CLKSEL2 & (~CLK_CLKSEL2_SPI0SEL_Msk)) | CLK_CLKSEL2_SPI0SEL_PCLK1;
        }

        /* Check clock source of SPI */
        if (spi == SPI0)
        {
            if ((CLK->CLKSEL2 & CLK_CLKSEL2_SPI0SEL_Msk) == CLK_CLKSEL2_SPI0SEL_HXT)
                u32ClkSrc = __HXT; /* Clock source is HXT */
            else if ((CLK->CLKSEL2 & CLK_CLKSEL2_SPI0SEL_Msk) == CLK_CLKSEL2_SPI0SEL_PLL)
                u32ClkSrc = CLK_GetPLLClockFreq(); /* Clock source is PLL */
            else if ((CLK->CLKSEL2 & CLK_CLKSEL2_SPI0SEL_Msk) == CLK_CLKSEL2_SPI0SEL_PCLK1)
                u32ClkSrc = u32HCLKFreq / ((CLK->PCLKDIV & CLK_PCLKDIV_APB0DIV_Msk) + 1);
            else
                u32ClkSrc = 48000000; /* Clock source is HIRC48 */
        }

        if (u32BusClock >= u32HCLKFreq)
        {
            /* Set DIVIDER = 0 */
            spi->CLKDIV = 0;
            /* Return master peripheral clock rate */
            return u32ClkSrc;
        }
        else if (u32BusClock >= u32ClkSrc)
        {
            /* Set DIVIDER = 0 */
            spi->CLKDIV = 0;
            /* Return master peripheral clock rate */
            return u32ClkSrc;
        }
        else if (u32BusClock == 0)
        {
            /* Set DIVIDER to the maximum value 0xFF. f_spi = f_spi_clk_src / (DIVIDER + 1) */
            spi->CLKDIV |= SPI_CLKDIV_DIVIDER_Msk;
            /* Return master peripheral clock rate */
            return (u32ClkSrc / (0xFF + 1));
        }
        else
        {
            u32Div = (((u32ClkSrc * 10) / u32BusClock + 5) / 10) - 1; /* Round to the nearest integer */
            if (u32Div > 0xFF)
            {
                u32Div = 0xFF;
                spi->CLKDIV |= SPI_CLKDIV_DIVIDER_Msk;
                /* Return master peripheral clock rate */
                return (u32ClkSrc / (0xFF + 1));
            }
            else
            {
                spi->CLKDIV = (spi->CLKDIV & (~SPI_CLKDIV_DIVIDER_Msk)) | (u32Div << SPI_CLKDIV_DIVIDER_Pos);
                /* Return master peripheral clock rate */
                return (u32ClkSrc / (u32Div + 1));
            }
        }
    }
    else     /* For slave mode, force the SPI peripheral clock rate to equal APB clock rate. */
    {
        /* Default setting: slave selection signal is low level active. */
        spi->SSCTL = SPI_SS_ACTIVE_LOW;

        /* Default setting: MSB first, disable unit transfer interrupt, SP_CYCLE = 0. */
        spi->CTL = u32MasterSlave | (u32DataWidth << SPI_CTL_DWIDTH_Pos) | (u32SPIMode) | SPI_CTL_SPIEN_Msk;

        /* Set DIVIDER = 0 */
        spi->CLKDIV = 0;

        /* Select PCLK as the clock source of SPI */
        CLK->CLKSEL2 = (CLK->CLKSEL2 & (~CLK_CLKSEL2_SPI0SEL_Msk)) | CLK_CLKSEL2_SPI0SEL_PCLK1;
        /* Return slave peripheral clock rate */
        return (CLK_GetHCLKFreq() / ((CLK->PCLKDIV & CLK_PCLKDIV_APB0DIV_Msk) + 1));
    }
}

/**
  * @brief  Disable SPI controller.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return None
  * @details This function will reset SPI controller.
  */
void SPI_Close(SPI_T *spi)
{
    if (spi == SPI0)
    {
        /* Reset SPI */
        SYS->IPRST1 |= SYS_IPRST1_SPI0RST_Msk;
        SYS->IPRST1 &= ~SYS_IPRST1_SPI0RST_Msk;
    }
}

/**
  * @brief  Clear RX FIFO buffer.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return None
  * @details This function will clear SPI RX FIFO buffer. The RXEMPTY (SPI_STATUS[8]) will be set to 1.
  */
void SPI_ClearRxFIFO(SPI_T *spi)
{
    spi->FIFOCTL |= SPI_FIFOCTL_RXFBCLR_Msk;
}

/**
  * @brief  Clear TX FIFO buffer.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return None
  * @details This function will clear SPI TX FIFO buffer. The TXEMPTY (SPI_STATUS[16]) will be set to 1.
  * @note The TX shift register will not be cleared.
  */
void SPI_ClearTxFIFO(SPI_T *spi)
{
    spi->FIFOCTL |= SPI_FIFOCTL_TXFBCLR_Msk;
}

/**
  * @brief  Disable the automatic slave selection function.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return None
  * @details This function will disable the automatic slave selection function and set slave selection signal to inactive state.
  */
void SPI_DisableAutoSS(SPI_T *spi)
{
    spi->SSCTL &= ~(SPI_SSCTL_AUTOSS_Msk | SPI_SSCTL_SS_Msk);
}

/**
  * @brief  Enable the automatic slave selection function.
  * @param[in]  spi The pointer of the specified SPI module.
  * @param[in]  u32SSPinMask Specifies slave selection pins. (SPI_SS)
  * @param[in]  u32ActiveLevel Specifies the active level of slave selection signal. (SPI_SS_ACTIVE_HIGH, SPI_SS_ACTIVE_LOW)
  * @return None
  * @details This function will enable the automatic slave selection function. Only available in Master mode.
  *          The slave selection pin and the active level will be set in this function.
  */
void SPI_EnableAutoSS(SPI_T *spi, uint32_t u32SSPinMask, uint32_t u32ActiveLevel)
{
    spi->SSCTL = (spi->SSCTL & (~(SPI_SSCTL_AUTOSS_Msk | SPI_SSCTL_SSACTPOL_Msk | SPI_SSCTL_SS_Msk))) | (u32SSPinMask | u32ActiveLevel | SPI_SSCTL_AUTOSS_Msk);
}

/**
  * @brief  Set the SPI bus clock.
  * @param[in]  spi The pointer of the specified SPI module.
  * @param[in]  u32BusClock The expected frequency of SPI bus clock in Hz.
  * @return Actual frequency of SPI bus clock.
  * @details This function is only available in Master mode. The actual clock rate may be different from the target SPI bus clock rate.
  *          For example, if the SPI source clock rate is 12 MHz and the target SPI bus clock rate is 7 MHz, the actual SPI bus clock
  *          rate will be 6 MHz.
  * @note   If u32BusClock = 0, DIVIDER setting will be set to the maximum value.
  * @note   If u32BusClock >= system clock frequency, SPI peripheral clock source will be set to APB clock and DIVIDER will be set to 0.
  * @note   If u32BusClock >= SPI peripheral clock source, DIVIDER will be set to 0.
  */
uint32_t SPI_SetBusClock(SPI_T *spi, uint32_t u32BusClock)
{
    uint32_t u32ClkSrc, u32HCLKFreq;
    uint32_t u32Div;

    /* check SPI interface */
    if (spi != SPI0) return SPI_NONE;

    /* Get system clock frequency */
    u32HCLKFreq = CLK_GetHCLKFreq();

    if (u32BusClock >= u32HCLKFreq)
    {
        /* Select PCLK as the clock source of SPI */
        if (spi == SPI0)
            CLK->CLKSEL2 = (CLK->CLKSEL2 & (~CLK_CLKSEL2_SPI0SEL_Msk)) | CLK_CLKSEL2_SPI0SEL_PCLK1;
    }

    /* Check clock source of SPI */
    if (spi == SPI0)
    {
        if ((CLK->CLKSEL2 & CLK_CLKSEL2_SPI0SEL_Msk) == CLK_CLKSEL2_SPI0SEL_HXT)
            u32ClkSrc = __HXT; /* Clock source is HXT */
        else if ((CLK->CLKSEL2 & CLK_CLKSEL2_SPI0SEL_Msk) == CLK_CLKSEL2_SPI0SEL_PLL)
            u32ClkSrc = CLK_GetPLLClockFreq(); /* Clock source is PLL */
        else if ((CLK->CLKSEL2 & CLK_CLKSEL2_SPI0SEL_Msk) == CLK_CLKSEL2_SPI0SEL_PCLK1)
            u32ClkSrc = CLK_GetHCLKFreq() / ((CLK->PCLKDIV & CLK_PCLKDIV_APB0DIV_Msk) + 1);
        else
            u32ClkSrc = 48000000; /* Clock source is HIRC48 */
    }

    if (u32BusClock >= u32HCLKFreq)
    {
        /* Set DIVIDER = 0 */
        spi->CLKDIV = 0;
        /* Return master peripheral clock rate */
        return u32ClkSrc;
    }
    else if (u32BusClock >= u32ClkSrc)
    {
        /* Set DIVIDER = 0 */
        spi->CLKDIV = 0;
        /* Return master peripheral clock rate */
        return u32ClkSrc;
    }
    else if (u32BusClock == 0)
    {
        /* Set DIVIDER to the maximum value 0xFF. f_spi = f_spi_clk_src / (DIVIDER + 1) */
        spi->CLKDIV |= SPI_CLKDIV_DIVIDER_Msk;
        /* Return master peripheral clock rate */
        return (u32ClkSrc / (0xFF + 1));
    }
    else
    {
        u32Div = (((u32ClkSrc * 10) / u32BusClock + 5) / 10) - 1; /* Round to the nearest integer */
        if (u32Div > 0xFF)
        {
            u32Div = 0xFF;
            spi->CLKDIV |= SPI_CLKDIV_DIVIDER_Msk;
            /* Return master peripheral clock rate */
            return (u32ClkSrc / (0xFF + 1));
        }
        else
        {
            spi->CLKDIV = (spi->CLKDIV & (~SPI_CLKDIV_DIVIDER_Msk)) | (u32Div << SPI_CLKDIV_DIVIDER_Pos);
            /* Return master peripheral clock rate */
            return (u32ClkSrc / (u32Div + 1));
        }
    }
}

/**
  * @brief  Configure FIFO threshold setting.
  * @param[in]  spi The pointer of the specified SPI module.
  * @param[in]  u32TxThreshold Decides the TX FIFO threshold. It could be 0 ~ 3.
  * @param[in]  u32RxThreshold Decides the RX FIFO threshold. It could be 0 ~ 3.
  * @return None
  * @details Set TX FIFO threshold and RX FIFO threshold configurations.
  */
void SPI_SetFIFO(SPI_T *spi, uint32_t u32TxThreshold, uint32_t u32RxThreshold)
{
    spi->FIFOCTL = (spi->FIFOCTL & ~(SPI_FIFOCTL_TXTH_Msk | SPI_FIFOCTL_RXTH_Msk)) |
                   (u32TxThreshold << SPI_FIFOCTL_TXTH_Pos) |
                   (u32RxThreshold << SPI_FIFOCTL_RXTH_Pos);
}

/**
  * @brief  Get the actual frequency of SPI bus clock. Only available in Master mode.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return Actual SPI bus clock frequency in Hz.
  * @details This function will calculate the actual SPI bus clock rate according to the SPInSEL and DIVIDER settings. Only available in Master mode.
  */
uint32_t SPI_GetBusClock(SPI_T *spi)
{
    uint32_t u32Div;
    uint32_t u32ClkSrc = 0, u32HCLKFreq;

    /* check SPI interface */
    if (spi != SPI0) return SPI_NONE;

    /* Get DIVIDER setting */
    u32Div = (spi->CLKDIV & SPI_CLKDIV_DIVIDER_Msk) >> SPI_CLKDIV_DIVIDER_Pos;

    /* Get system clock frequency */
    u32HCLKFreq = CLK_GetHCLKFreq();

    /* Check clock source of SPI */
    if (spi == SPI0)
    {
        if ((CLK->CLKSEL2 & CLK_CLKSEL2_SPI0SEL_Msk) == CLK_CLKSEL2_SPI0SEL_HXT)
            u32ClkSrc = __HXT; /* Clock source is HXT */
        else if ((CLK->CLKSEL2 & CLK_CLKSEL2_SPI0SEL_Msk) == CLK_CLKSEL2_SPI0SEL_PLL)
            u32ClkSrc = CLK_GetPLLClockFreq(); /* Clock source is PLL */
        else if ((CLK->CLKSEL2 & CLK_CLKSEL2_SPI0SEL_Msk) == CLK_CLKSEL2_SPI0SEL_PCLK1)
            u32ClkSrc = u32HCLKFreq / ((CLK->PCLKDIV & CLK_PCLKDIV_APB0DIV_Msk) + 1);
        else
            u32ClkSrc = 48000000; /* Clock source is HIRC48 */
    }

    /* Return SPI bus clock rate */
    return (u32ClkSrc / (u32Div + 1));
}

/**
  * @brief  Enable interrupt function.
  * @param[in]  spi The pointer of the specified SPI module.
  * @param[in]  u32Mask The combination of all related interrupt enable bits.
  *                     Each bit corresponds to a interrupt enable bit.
  *                     This parameter decides which interrupts will be enabled. It is combination of:
  *                       - \ref SPI_UNIT_INT_MASK
  *                       - \ref SPI_SSACT_INT_MASK
  *                       - \ref SPI_SSINACT_INT_MASK
  *                       - \ref SPI_SLVUR_INT_MASK
  *                       - \ref SPI_SLVBE_INT_MASK
  *                       - \ref SPI_TXUF_INT_MASK
  *                       - \ref SPI_FIFO_TXTH_INT_MASK
  *                       - \ref SPI_FIFO_RXTH_INT_MASK
  *                       - \ref SPI_FIFO_RXOV_INT_MASK
  *                       - \ref SPI_FIFO_RXTO_INT_MASK
  *
  * @return None
  * @details Enable SPI related interrupts specified by u32Mask parameter.
  */
void SPI_EnableInt(SPI_T *spi, uint32_t u32Mask)
{
    /* Enable unit transfer interrupt flag */
    if ((u32Mask & SPI_UNIT_INT_MASK) == SPI_UNIT_INT_MASK)
        spi->CTL |= SPI_CTL_UNITIEN_Msk;

    /* Enable slave selection signal active interrupt flag */
    if ((u32Mask & SPI_SSACT_INT_MASK) == SPI_SSACT_INT_MASK)
        spi->SSCTL |= SPI_SSCTL_SSACTIEN_Msk;

    /* Enable slave selection signal inactive interrupt flag */
    if ((u32Mask & SPI_SSINACT_INT_MASK) == SPI_SSINACT_INT_MASK)
        spi->SSCTL |= SPI_SSCTL_SSINAIEN_Msk;

    /* Enable slave TX under run interrupt flag */
    if ((u32Mask & SPI_SLVUR_INT_MASK) == SPI_SLVUR_INT_MASK)
        spi->SSCTL |= SPI_SSCTL_SLVURIEN_Msk;

    /* Enable slave bit count error interrupt flag */
    if ((u32Mask & SPI_SLVBE_INT_MASK) == SPI_SLVBE_INT_MASK)
        spi->SSCTL |= SPI_SSCTL_SLVBEIEN_Msk;

    /* Enable slave TX underflow interrupt flag */
    if ((u32Mask & SPI_TXUF_INT_MASK) == SPI_TXUF_INT_MASK)
        spi->FIFOCTL |= SPI_FIFOCTL_TXUFIEN_Msk;

    /* Enable TX threshold interrupt flag */
    if ((u32Mask & SPI_FIFO_TXTH_INT_MASK) == SPI_FIFO_TXTH_INT_MASK)
        spi->FIFOCTL |= SPI_FIFOCTL_TXTHIEN_Msk;

    /* Enable RX threshold interrupt flag */
    if ((u32Mask & SPI_FIFO_RXTH_INT_MASK) == SPI_FIFO_RXTH_INT_MASK)
        spi->FIFOCTL |= SPI_FIFOCTL_RXTHIEN_Msk;

    /* Enable RX overrun interrupt flag */
    if ((u32Mask & SPI_FIFO_RXOV_INT_MASK) == SPI_FIFO_RXOV_INT_MASK)
        spi->FIFOCTL |= SPI_FIFOCTL_RXOVIEN_Msk;

    /* Enable RX time-out interrupt flag */
    if ((u32Mask & SPI_FIFO_RXTO_INT_MASK) == SPI_FIFO_RXTO_INT_MASK)
        spi->FIFOCTL |= SPI_FIFOCTL_RXTOIEN_Msk;
}

/**
  * @brief  Disable interrupt function.
  * @param[in]  spi The pointer of the specified SPI module.
  * @param[in]  u32Mask The combination of all related interrupt enable bits.
  *                     Each bit corresponds to a interrupt bit.
  *                     This parameter decides which interrupts will be disabled. It is combination of:
  *                       - \ref SPI_UNIT_INT_MASK
  *                       - \ref SPI_SSACT_INT_MASK
  *                       - \ref SPI_SSINACT_INT_MASK
  *                       - \ref SPI_SLVUR_INT_MASK
  *                       - \ref SPI_SLVBE_INT_MASK
  *                       - \ref SPI_TXUF_INT_MASK
  *                       - \ref SPI_FIFO_TXTH_INT_MASK
  *                       - \ref SPI_FIFO_RXTH_INT_MASK
  *                       - \ref SPI_FIFO_RXOV_INT_MASK
  *                       - \ref SPI_FIFO_RXTO_INT_MASK
  *
  * @return None
  * @details Disable SPI related interrupts specified by u32Mask parameter.
  */
void SPI_DisableInt(SPI_T *spi, uint32_t u32Mask)
{
    /* Disable unit transfer interrupt flag */
    if ((u32Mask & SPI_UNIT_INT_MASK) == SPI_UNIT_INT_MASK)
        spi->CTL &= ~SPI_CTL_UNITIEN_Msk;

    /* Disable slave selection signal active interrupt flag */
    if ((u32Mask & SPI_SSACT_INT_MASK) == SPI_SSACT_INT_MASK)
        spi->SSCTL &= ~SPI_SSCTL_SSACTIEN_Msk;

    /* Disable slave selection signal inactive interrupt flag */
    if ((u32Mask & SPI_SSINACT_INT_MASK) == SPI_SSINACT_INT_MASK)
        spi->SSCTL &= ~SPI_SSCTL_SSINAIEN_Msk;

    /* Disable slave TX under run interrupt flag */
    if ((u32Mask & SPI_SLVUR_INT_MASK) == SPI_SLVUR_INT_MASK)
        spi->SSCTL &= ~SPI_SSCTL_SLVURIEN_Msk;

    /* Disable slave bit count error interrupt flag */
    if ((u32Mask & SPI_SLVBE_INT_MASK) == SPI_SLVBE_INT_MASK)
        spi->SSCTL &= ~SPI_SSCTL_SLVBEIEN_Msk;

    /* Disable slave TX underflow interrupt flag */
    if ((u32Mask & SPI_TXUF_INT_MASK) == SPI_TXUF_INT_MASK)
        spi->FIFOCTL &= ~SPI_FIFOCTL_TXUFIEN_Msk;

    /* Disable TX threshold interrupt flag */
    if ((u32Mask & SPI_FIFO_TXTH_INT_MASK) == SPI_FIFO_TXTH_INT_MASK)
        spi->FIFOCTL &= ~SPI_FIFOCTL_TXTHIEN_Msk;

    /* Disable RX threshold interrupt flag */
    if ((u32Mask & SPI_FIFO_RXTH_INT_MASK) == SPI_FIFO_RXTH_INT_MASK)
        spi->FIFOCTL &= ~SPI_FIFOCTL_RXTHIEN_Msk;

    /* Disable RX overrun interrupt flag */
    if ((u32Mask & SPI_FIFO_RXOV_INT_MASK) == SPI_FIFO_RXOV_INT_MASK)
        spi->FIFOCTL &= ~SPI_FIFOCTL_RXOVIEN_Msk;

    /* Disable RX time-out interrupt flag */
    if ((u32Mask & SPI_FIFO_RXTO_INT_MASK) == SPI_FIFO_RXTO_INT_MASK)
        spi->FIFOCTL &= ~SPI_FIFOCTL_RXTOIEN_Msk;
}

/**
  * @brief  Get interrupt flag.
  * @param[in]  spi The pointer of the specified SPI module.
  * @param[in]  u32Mask The combination of all related interrupt sources.
  *                     Each bit corresponds to a interrupt source.
  *                     This parameter decides which interrupt flags will be read. It is combination of:
  *                       - \ref SPI_UNIT_INT_MASK
  *                       - \ref SPI_SSACT_INT_MASK
  *                       - \ref SPI_SSINACT_INT_MASK
  *                       - \ref SPI_SLVUR_INT_MASK
  *                       - \ref SPI_SLVBE_INT_MASK
  *                       - \ref SPI_TXUF_INT_MASK
  *                       - \ref SPI_FIFO_TXTH_INT_MASK
  *                       - \ref SPI_FIFO_RXTH_INT_MASK
  *                       - \ref SPI_FIFO_RXOV_INT_MASK
  *                       - \ref SPI_FIFO_RXTO_INT_MASK
  *
  * @return Interrupt flags of selected sources.
  * @details Get SPI related interrupt flags specified by u32Mask parameter.
  */
uint32_t SPI_GetIntFlag(SPI_T *spi, uint32_t u32Mask)
{
    uint32_t u32IntFlag = 0;

    /* Check unit transfer interrupt flag */
    if ((u32Mask & SPI_UNIT_INT_MASK) && (spi->STATUS & SPI_STATUS_UNITIF_Msk))
        u32IntFlag |= SPI_UNIT_INT_MASK;

    /* Check slave selection signal active interrupt flag */
    if ((u32Mask & SPI_SSACT_INT_MASK) && (spi->STATUS & SPI_STATUS_SSACTIF_Msk))
        u32IntFlag |= SPI_SSACT_INT_MASK;

    /* Check slave selection signal inactive interrupt flag */
    if ((u32Mask & SPI_SSINACT_INT_MASK) && (spi->STATUS & SPI_STATUS_SSINAIF_Msk))
        u32IntFlag |= SPI_SSINACT_INT_MASK;

    /* Check slave TX under run interrupt flag */
    if ((u32Mask & SPI_SLVUR_INT_MASK) && (spi->STATUS & SPI_STATUS_SLVURIF_Msk))
        u32IntFlag |= SPI_SLVUR_INT_MASK;

    /* Check slave bit count error interrupt flag */
    if ((u32Mask & SPI_SLVBE_INT_MASK) && (spi->STATUS & SPI_STATUS_SLVBEIF_Msk))
        u32IntFlag |= SPI_SLVBE_INT_MASK;

    /* Check slave TX underflow interrupt flag */
    if ((u32Mask & SPI_TXUF_INT_MASK) && (spi->STATUS & SPI_STATUS_TXUFIF_Msk))
        u32IntFlag |= SPI_TXUF_INT_MASK;

    /* Check TX threshold interrupt flag */
    if ((u32Mask & SPI_FIFO_TXTH_INT_MASK) && (spi->STATUS & SPI_STATUS_TXTHIF_Msk))
        u32IntFlag |= SPI_FIFO_TXTH_INT_MASK;

    /* Check RX threshold interrupt flag */
    if ((u32Mask & SPI_FIFO_RXTH_INT_MASK) && (spi->STATUS & SPI_STATUS_RXTHIF_Msk))
        u32IntFlag |= SPI_FIFO_RXTH_INT_MASK;

    /* Check RX overrun interrupt flag */
    if ((u32Mask & SPI_FIFO_RXOV_INT_MASK) && (spi->STATUS & SPI_STATUS_RXOVIF_Msk))
        u32IntFlag |= SPI_FIFO_RXOV_INT_MASK;

    /* Check RX time-out interrupt flag */
    if ((u32Mask & SPI_FIFO_RXTO_INT_MASK) && (spi->STATUS & SPI_STATUS_RXTOIF_Msk))
        u32IntFlag |= SPI_FIFO_RXTO_INT_MASK;

    return u32IntFlag;
}

/**
  * @brief  Clear interrupt flag.
  * @param[in]  spi The pointer of the specified SPI module.
  * @param[in]  u32Mask The combination of all related interrupt sources.
  *                     Each bit corresponds to a interrupt source.
  *                     This parameter decides which interrupt flags will be cleared. It could be the combination of:
  *                       - \ref SPI_UNIT_INT_MASK
  *                       - \ref SPI_SSACT_INT_MASK
  *                       - \ref SPI_SSINACT_INT_MASK
  *                       - \ref SPI_SLVUR_INT_MASK
  *                       - \ref SPI_SLVBE_INT_MASK
  *                       - \ref SPI_TXUF_INT_MASK
  *                       - \ref SPI_FIFO_RXOV_INT_MASK
  *                       - \ref SPI_FIFO_RXTO_INT_MASK
  *
  * @return None
  * @details Clear SPI related interrupt flags specified by u32Mask parameter.
  */
void SPI_ClearIntFlag(SPI_T *spi, uint32_t u32Mask)
{
    if (u32Mask & SPI_UNIT_INT_MASK)
        spi->STATUS = SPI_STATUS_UNITIF_Msk; /* Clear unit transfer interrupt flag */

    if (u32Mask & SPI_SSACT_INT_MASK)
        spi->STATUS = SPI_STATUS_SSACTIF_Msk; /* Clear slave selection signal active interrupt flag */

    if (u32Mask & SPI_SSINACT_INT_MASK)
        spi->STATUS = SPI_STATUS_SSINAIF_Msk; /* Clear slave selection signal inactive interrupt flag */

    if (u32Mask & SPI_SLVUR_INT_MASK)
        spi->STATUS = SPI_STATUS_SLVURIF_Msk; /* Clear slave TX under run interrupt flag */

    if (u32Mask & SPI_SLVBE_INT_MASK)
        spi->STATUS = SPI_STATUS_SLVBEIF_Msk; /* Clear slave bit count error interrupt flag */

    if (u32Mask & SPI_TXUF_INT_MASK)
        spi->STATUS = SPI_STATUS_TXUFIF_Msk; /* Clear slave TX underflow interrupt flag */

    if (u32Mask & SPI_FIFO_RXOV_INT_MASK)
        spi->STATUS = SPI_STATUS_RXOVIF_Msk; /* Clear RX overrun interrupt flag */

    if (u32Mask & SPI_FIFO_RXTO_INT_MASK)
        spi->STATUS = SPI_STATUS_RXTOIF_Msk; /* Clear RX time-out interrupt flag */
}

/**
  * @brief  Get SPI status.
  * @param[in]  spi The pointer of the specified SPI module.
  * @param[in]  u32Mask The combination of all related sources.
  *                     Each bit corresponds to a source.
  *                     This parameter decides which flags will be read. It is combination of:
  *                       - \ref SPI_BUSY_MASK
  *                       - \ref SPI_RX_EMPTY_MASK
  *                       - \ref SPI_RX_FULL_MASK
  *                       - \ref SPI_TX_EMPTY_MASK
  *                       - \ref SPI_TX_FULL_MASK
  *                       - \ref SPI_TXRX_RESET_MASK
  *                       - \ref SPI_SPIEN_STS_MASK
  *                       - \ref SPI_SSLINE_STS_MASK
  *
  * @return Flags of selected sources.
  * @details Get SPI related status specified by u32Mask parameter.
  */
uint32_t SPI_GetStatus(SPI_T *spi, uint32_t u32Mask)
{
    uint32_t u32Flag = 0;

    /* Check busy status */
    if ((u32Mask & SPI_BUSY_MASK) && (spi->STATUS & SPI_STATUS_BUSY_Msk))
        u32Flag |= SPI_BUSY_MASK;

    /* Check RX empty flag */
    if ((u32Mask & SPI_RX_EMPTY_MASK) && (spi->STATUS & SPI_STATUS_RXEMPTY_Msk))
        u32Flag |= SPI_RX_EMPTY_MASK;

    /* Check RX full flag */
    if ((u32Mask & SPI_RX_FULL_MASK) && (spi->STATUS & SPI_STATUS_RXFULL_Msk))
        u32Flag |= SPI_RX_FULL_MASK;

    /* Check TX empty flag */
    if ((u32Mask & SPI_TX_EMPTY_MASK) && (spi->STATUS & SPI_STATUS_TXEMPTY_Msk))
        u32Flag |= SPI_TX_EMPTY_MASK;

    /* Check TX full flag */
    if ((u32Mask & SPI_TX_FULL_MASK) && (spi->STATUS & SPI_STATUS_TXFULL_Msk))
        u32Flag |= SPI_TX_FULL_MASK;

    /* Check TX/RX reset flag */
    if ((u32Mask & SPI_TXRX_RESET_MASK) && (spi->STATUS & SPI_STATUS_TXRXRST_Msk))
        u32Flag |= SPI_TXRX_RESET_MASK;

    /* Check SPIEN flag */
    if ((u32Mask & SPI_SPIEN_STS_MASK) && (spi->STATUS & SPI_STATUS_SPIENSTS_Msk))
        u32Flag |= SPI_SPIEN_STS_MASK;

    /* Check SPIx_SS line status */
    if ((u32Mask & SPI_SSLINE_STS_MASK) && (spi->STATUS & SPI_STATUS_SSLINE_Msk))
        u32Flag |= SPI_SSLINE_STS_MASK;

    return u32Flag;
}


/**
  * @brief  This function is used to get SPII2S source clock frequency.
  * @param[in]  i2s The pointer of the specified SPII2S module.
  * @return SPII2S source clock frequency (Hz).
  * @details Return the source clock frequency according to the setting of SPI0SEL (CLKSEL2[25:24])
  */
static uint32_t SPII2S_GetSourceClockFreq(SPI_T *i2s)
{
    uint32_t u32Freq = 0, u32HCLKFreq;

    /* check SPI interface */
    if (i2s != SPI0) return SPI_NONE;

    if (i2s == SPI0)
    {
        if ((CLK->CLKSEL2 & CLK_CLKSEL2_SPI0SEL_Msk) == CLK_CLKSEL2_SPI0SEL_HXT)
            u32Freq = __HXT; /* Clock source is HXT */
        else if ((CLK->CLKSEL2 & CLK_CLKSEL2_SPI0SEL_Msk) == CLK_CLKSEL2_SPI0SEL_PLL)
            u32Freq = CLK_GetPLLClockFreq(); /* Clock source is PLL */
        else if ((CLK->CLKSEL2 & CLK_CLKSEL2_SPI0SEL_Msk) == CLK_CLKSEL2_SPI0SEL_PCLK1)
        {
            /* Get system clock frequency */
            u32HCLKFreq = CLK_GetHCLKFreq();
            /* Clock source is PCLK0 */
            u32Freq = u32HCLKFreq / ((CLK->PCLKDIV & CLK_PCLKDIV_APB0DIV_Msk) + 1);
        }
        else
            u32Freq = 48000000; /* Clock source is HIRC48 */
    }

    return u32Freq;
}

/**
  * @brief  This function configures some parameters of SPII2S interface for general purpose use.
  * @param[in] i2s The pointer of the specified SPII2S module.
  * @param[in] u32MasterSlave SPII2S operation mode. Valid values are listed below.
  *                                     - \ref SPII2S_MODE_MASTER
  *                                     - \ref SPII2S_MODE_SLAVE
  * @param[in] u32SampleRate Sample rate
  * @param[in] u32WordWidth Data length. Valid values are listed below.
  *                                     - \ref SPII2S_DATABIT_8
  *                                     - \ref SPII2S_DATABIT_16
  *                                     - \ref SPII2S_DATABIT_24
  *                                     - \ref SPII2S_DATABIT_32
  * @param[in] u32Channels Audio format. Valid values are listed below.
  *                                     - \ref SPII2S_MONO
  *                                     - \ref SPII2S_STEREO
  * @param[in] u32DataFormat Data format. Valid values are listed below.
  *                                     - \ref SPII2S_FORMAT_I2S
  *                                     - \ref SPII2S_FORMAT_MSB
  *                                     - \ref SPII2S_FORMAT_PCMA
  *                                     - \ref SPII2S_FORMAT_PCMB
  * @return Real sample rate of master mode or peripheral clock rate of slave mode.
  * @details This function will reset SPI/I2S controller and configure SPII2S controller according to the input parameters.
  *          Set TX FIFO threshold to 2 and RX FIFO threshold to 1. Both the TX and RX functions will be enabled.
  *          The actual sample rate may be different from the target sample rate. The real sample rate will be returned for reference.
  * @note   In slave mode, the SPI peripheral clock rate will be equal to APB clock rate.
  */
uint32_t SPII2S_Open(SPI_T *i2s, uint32_t u32MasterSlave, uint32_t u32SampleRate, uint32_t u32WordWidth, uint32_t u32Channels, uint32_t u32DataFormat)
{
    uint32_t u32Divider;
    uint32_t u32BitRate, u32SrcClk;
    uint32_t u32HCLKFreq;

    /* check SPI interface */
    if (i2s != SPI0) return SPI_NONE;

    /* Reset SPI/I2S */
    if (i2s == SPI0)
    {
        SYS->IPRST1 |= SYS_IPRST1_SPI0RST_Msk;
        SYS->IPRST1 &= ~SYS_IPRST1_SPI0RST_Msk;
    }

    /* Configure SPII2S controller */
    i2s->I2SCTL = u32MasterSlave | u32WordWidth | u32Channels | u32DataFormat;
    /* Set TX FIFO threshold to 2 and RX FIFO threshold to 1 */
    i2s->FIFOCTL = SPII2S_FIFO_TX_LEVEL_WORD_2 | SPII2S_FIFO_RX_LEVEL_WORD_2;

    if (u32MasterSlave == SPI_MASTER)
    {
        /* Get the source clock rate */
        u32SrcClk = SPII2S_GetSourceClockFreq(i2s);

        /* Calculate the bit clock rate */
        u32BitRate = u32SampleRate * ((u32WordWidth >> SPI_I2SCTL_WDWIDTH_Pos) + 1) * 16;
        u32Divider = ((u32SrcClk / u32BitRate) >> 1) - 1;
        /* Set BCLKDIV setting */
        i2s->I2SCLK = (i2s->I2SCLK & ~SPI_I2SCLK_BCLKDIV_Msk) | (u32Divider << SPI_I2SCLK_BCLKDIV_Pos);

        /* Calculate bit clock rate */
        u32BitRate = u32SrcClk / ((u32Divider + 1) * 2);
        /* Calculate real sample rate */
        u32SampleRate = u32BitRate / (((u32WordWidth >> SPI_I2SCTL_WDWIDTH_Pos) + 1) * 16);

        /* Enable TX function, RX function and SPII2S mode. */
        i2s->I2SCTL |= (SPI_I2SCTL_RXEN_Msk | SPI_I2SCTL_TXEN_Msk | SPI_I2SCTL_I2SEN_Msk);

        /* Return the real sample rate */
        return u32SampleRate;
    }
    else
    {
        /* Set BCLKDIV = 0 */
        i2s->I2SCLK &= ~SPI_I2SCLK_BCLKDIV_Msk;
        /* Get system clock frequency */
        u32HCLKFreq = CLK_GetHCLKFreq();

        /* Set the peripheral clock rate to equal APB clock rate */
        CLK->CLKSEL2 = (CLK->CLKSEL2 & (~CLK_CLKSEL2_SPI0SEL_Msk)) | CLK_CLKSEL2_SPI0SEL_PCLK1;
        /* Enable TX function, RX function and SPII2S mode. */
        i2s->I2SCTL |= (SPI_I2SCTL_RXEN_Msk | SPI_I2SCTL_TXEN_Msk | SPI_I2SCTL_I2SEN_Msk);
        /* Return slave peripheral clock rate */
        return (u32HCLKFreq / ((CLK->PCLKDIV & CLK_PCLKDIV_APB0DIV_Msk) + 1));
    }
}

/**
  * @brief  Disable SPII2S function.
  * @param[in]  i2s The pointer of the specified SPII2S module.
  * @return None
  * @details Disable SPII2S function.
  */
void SPII2S_Close(SPI_T *i2s)
{
    i2s->I2SCTL &= ~SPI_I2SCTL_I2SEN_Msk;
}

/**
  * @brief Enable interrupt function.
  * @param[in] i2s The pointer of the specified SPII2S module.
  * @param[in] u32Mask The combination of all related interrupt enable bits.
  *            Each bit corresponds to a interrupt source. Valid values are listed below.
  *            - \ref SPII2S_FIFO_TXTH_INT_MASK
  *            - \ref SPII2S_FIFO_RXTH_INT_MASK
  *            - \ref SPII2S_FIFO_RXOV_INT_MASK
  *            - \ref SPII2S_FIFO_RXTO_INT_MASK
  *            - \ref SPII2S_TXUF_INT_MASK
  *            - \ref SPII2S_RIGHT_ZC_INT_MASK
  *            - \ref SPII2S_LEFT_ZC_INT_MASK
  * @return None
  * @details This function enables the interrupt according to the u32Mask parameter.
  */
void SPII2S_EnableInt(SPI_T *i2s, uint32_t u32Mask)
{
    /* Enable TX threshold interrupt flag */
    if ((u32Mask & SPII2S_FIFO_TXTH_INT_MASK) == SPII2S_FIFO_TXTH_INT_MASK)
        i2s->FIFOCTL |= SPI_FIFOCTL_TXTHIEN_Msk;

    /* Enable RX threshold interrupt flag */
    if ((u32Mask & SPII2S_FIFO_RXTH_INT_MASK) == SPII2S_FIFO_RXTH_INT_MASK)
        i2s->FIFOCTL |= SPI_FIFOCTL_RXTHIEN_Msk;

    /* Enable RX overrun interrupt flag */
    if ((u32Mask & SPII2S_FIFO_RXOV_INT_MASK) == SPII2S_FIFO_RXOV_INT_MASK)
        i2s->FIFOCTL |= SPI_FIFOCTL_RXOVIEN_Msk;

    /* Enable RX time-out interrupt flag */
    if ((u32Mask & SPII2S_FIFO_RXTO_INT_MASK) == SPII2S_FIFO_RXTO_INT_MASK)
        i2s->FIFOCTL |= SPI_FIFOCTL_RXTOIEN_Msk;

    /* Enable TX underflow interrupt flag */
    if ((u32Mask & SPII2S_TXUF_INT_MASK) == SPII2S_TXUF_INT_MASK)
        i2s->FIFOCTL |= SPI_FIFOCTL_TXUFIEN_Msk;

    /* Enable right channel zero cross interrupt flag */
    if ((u32Mask & SPII2S_RIGHT_ZC_INT_MASK) == SPII2S_RIGHT_ZC_INT_MASK)
        i2s->I2SCTL |= SPI_I2SCTL_RZCIEN_Msk;

    /* Enable left channel zero cross interrupt flag */
    if ((u32Mask & SPII2S_LEFT_ZC_INT_MASK) == SPII2S_LEFT_ZC_INT_MASK)
        i2s->I2SCTL |= SPI_I2SCTL_LZCIEN_Msk;
}

/**
  * @brief Disable interrupt function.
  * @param[in] i2s The pointer of the specified SPII2S module.
  * @param[in] u32Mask The combination of all related interrupt enable bits.
  *            Each bit corresponds to a interrupt source. Valid values are listed below.
  *            - \ref SPII2S_FIFO_TXTH_INT_MASK
  *            - \ref SPII2S_FIFO_RXTH_INT_MASK
  *            - \ref SPII2S_FIFO_RXOV_INT_MASK
  *            - \ref SPII2S_FIFO_RXTO_INT_MASK
  *            - \ref SPII2S_TXUF_INT_MASK
  *            - \ref SPII2S_RIGHT_ZC_INT_MASK
  *            - \ref SPII2S_LEFT_ZC_INT_MASK
  * @return None
  * @details This function disables the interrupt according to the u32Mask parameter.
  */
void SPII2S_DisableInt(SPI_T *i2s, uint32_t u32Mask)
{
    /* Disable TX threshold interrupt flag */
    if ((u32Mask & SPII2S_FIFO_TXTH_INT_MASK) == SPII2S_FIFO_TXTH_INT_MASK)
        i2s->FIFOCTL &= ~SPI_FIFOCTL_TXTHIEN_Msk;

    /* Disable RX threshold interrupt flag */
    if ((u32Mask & SPII2S_FIFO_RXTH_INT_MASK) == SPII2S_FIFO_RXTH_INT_MASK)
        i2s->FIFOCTL &= ~SPI_FIFOCTL_RXTHIEN_Msk;

    /* Disable RX overrun interrupt flag */
    if ((u32Mask & SPII2S_FIFO_RXOV_INT_MASK) == SPII2S_FIFO_RXOV_INT_MASK)
        i2s->FIFOCTL &= ~SPI_FIFOCTL_RXOVIEN_Msk;

    /* Disable RX time-out interrupt flag */
    if ((u32Mask & SPII2S_FIFO_RXTO_INT_MASK) == SPII2S_FIFO_RXTO_INT_MASK)
        i2s->FIFOCTL &= ~SPI_FIFOCTL_RXTOIEN_Msk;

    /* Disable TX underflow interrupt flag */
    if ((u32Mask & SPII2S_TXUF_INT_MASK) == SPII2S_TXUF_INT_MASK)
        i2s->FIFOCTL &= ~SPI_FIFOCTL_TXUFIEN_Msk;

    /* Disable right channel zero cross interrupt flag */
    if ((u32Mask & SPII2S_RIGHT_ZC_INT_MASK) == SPII2S_RIGHT_ZC_INT_MASK)
        i2s->I2SCTL &= ~SPI_I2SCTL_RZCIEN_Msk;

    /* Disable left channel zero cross interrupt flag */
    if ((u32Mask & SPII2S_LEFT_ZC_INT_MASK) == SPII2S_LEFT_ZC_INT_MASK)
        i2s->I2SCTL &= ~SPI_I2SCTL_LZCIEN_Msk;
}

/**
  * @brief  Enable master clock (MCLK).
  * @param[in] i2s The pointer of the specified SPII2S module.
  * @param[in] u32BusClock The target MCLK clock rate.
  * @return Actual MCLK clock rate
  * @details Set the master clock rate according to u32BusClock parameter and enable master clock output.
  *          The actual master clock rate may be different from the target master clock rate. The real master clock rate will be returned for reference.
  */
uint32_t SPII2S_EnableMCLK(SPI_T *i2s, uint32_t u32BusClock)
{
    uint32_t u32Divider;
    uint32_t u32SrcClk;

    u32SrcClk = SPII2S_GetSourceClockFreq(i2s);
    if (u32BusClock == u32SrcClk)
        u32Divider = 0;
    else
    {
        u32Divider = (u32SrcClk / u32BusClock) >> 1;
        /* MCLKDIV is a 7-bit width configuration. The maximum value is 0xFF. */
        if (u32Divider > 0xFF)
            u32Divider = 0xFF;
    }

    /* Write u32Divider to MCLKDIV (SPI_I2SCLK[5:0]) */
    i2s->I2SCLK = (i2s->I2SCLK & ~SPI_I2SCLK_MCLKDIV_Msk) | (u32Divider << SPI_I2SCLK_MCLKDIV_Pos);

    /* Enable MCLK output */
    i2s->I2SCTL |= SPI_I2SCTL_MCLKEN_Msk;

    if (u32Divider == 0)
        return u32SrcClk; /* If MCLKDIV=0, master clock rate is equal to the source clock rate. */
    else
        return ((u32SrcClk >> 1) / u32Divider); /* If MCLKDIV>0, master clock rate = source clock rate / (MCLKDIV * 2) */
}

/**
  * @brief  Disable master clock (MCLK).
  * @param[in] i2s The pointer of the specified SPII2S module.
  * @return None
  * @details Clear MCLKEN bit of SPI_I2SCTL register to disable master clock output.
  */
void SPII2S_DisableMCLK(SPI_T *i2s)
{
    i2s->I2SCTL &= ~SPI_I2SCTL_MCLKEN_Msk;
}

/**
  * @brief  Configure FIFO threshold setting.
  * @param[in]  i2s The pointer of the specified SPII2S module.
  * @param[in]  u32TxThreshold Decides the TX FIFO threshold. It could be 0 ~ 3.
  * @param[in]  u32RxThreshold Decides the RX FIFO threshold. It could be 0 ~ 3.
  * @return None
  * @details Set TX FIFO threshold and RX FIFO threshold configurations.
  */
void SPII2S_SetFIFO(SPI_T *i2s, uint32_t u32TxThreshold, uint32_t u32RxThreshold)
{
    i2s->FIFOCTL = (i2s->FIFOCTL & ~(SPI_FIFOCTL_TXTH_Msk | SPI_FIFOCTL_RXTH_Msk)) |
                   (u32TxThreshold << SPI_FIFOCTL_TXTH_Pos) |
                   (u32RxThreshold << SPI_FIFOCTL_RXTH_Pos);
}

/*@}*/ /* end of group SPI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SPI_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
