/**************************************************************************//**
 * @file     spi.c
 * @version  V3.00
 * $Revision: 4 $
 * $Date: 2/07/14 6:59p $
 * @brief    M051 series SPI driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "M051Series.h"
/** @addtogroup M051_Device_Driver M051 Device Driver
  @{
*/

/** @addtogroup M051_SPI_Driver SPI Driver
  @{
*/


/** @addtogroup M051_SPI_EXPORTED_FUNCTIONS SPI Exported Functions
  @{
*/

/**
  * @brief  This function make SPI module be ready to transfer.
  *         By default, the SPI transfer sequence is MSB first and
  *         the automatic slave select function is disabled. In
  *         Slave mode, the u32BusClock must be NULL and the SPI clock
  *         divider setting will be 0.
  * @param  spi is the base address of SPI module.
  * @param  u32MasterSlave decides the SPI module is operating in master mode or in slave mode. (SPI_SLAVE, SPI_MASTER)
  * @param  u32SPIMode decides the transfer timing. (SPI_MODE_0, SPI_MODE_1, SPI_MODE_2, SPI_MODE_03)
  * @param  u32DataWidth decides the data width of a SPI transaction.
  * @param  u32BusClock is the expected frequency of SPI bus clock in Hz.
  * @return Actual frequency of SPI peripheral clock.
  * @note   If u32BusClock = 0, DIVIDER setting will be set to the maximum value.
  * @note   In slave mode, the SPI peripheral clock rate will be set to equal to system clock rate.
  * @note   On M05xxBN, if u32BusClock is equal to system clock rate, DIV_ONE will be set to 1.
  *            So that byte reorder function, byte suspend function and variable clock function must be disabled.
  * @note   On M05xxBN, if u32BusClock is larger than system clock rate, the SPI peripheral clock rate will be set to a half of system clock rate.
  * @note   On M05xxDN and M05xxDE, if u32BusClock is larger than system clock rate, the SPI peripheral clock rate will be set to equal to system clock rate.
  */
uint32_t SPI_Open(SPI_T *spi,
                  uint32_t u32MasterSlave,
                  uint32_t u32SPIMode,
                  uint32_t u32DataWidth,
                  uint32_t u32BusClock)
{
    uint32_t u32ClkSrc = 0, u32Div;

    if(u32DataWidth == 32)
        u32DataWidth = 0;

    /* Default setting: MSB first, disable unit transfer interrupt, SP_CYCLE = 0. */
    spi->CNTRL = u32MasterSlave | (u32DataWidth << SPI_CNTRL_TX_BIT_LEN_Pos) | (u32SPIMode);

    if(((SYS->PDID & 0xF0000000) == 0) || ((SYS->PDID & 0xF0000000) == 0x10000000)) /* For M05xxAN and M05xxBN, the SPI peripheral clock source is PCLK. */
    {
        /* Get the system clock rate */
        u32ClkSrc = CLK_GetHCLKFreq();

        if(u32MasterSlave == SPI_MASTER)
        {
            /* Default setting: slave select signal is active low; disable automatic slave select function. */
            spi->SSR = SPI_SS_ACTIVE_LOW;

            if((u32BusClock == u32ClkSrc) && ((SYS->PDID & 0xF0000000) == 0x10000000)) /* M05xxBN support DIV_ONE feature */
            {
                /* Enable DIV_ONE feature */
                /* Note: When DIV_ONE feature is enabled, byte reorder function, byte suspend function and variable clock function must be disabled. */
                spi->CNTRL2 |= SPI_CNTRL2_DIV_ONE_Msk;
                /* Return master peripheral clock rate */
                return u32ClkSrc;
            }
            else if(u32BusClock >= u32ClkSrc)
            {
                /* Set DIVIDER = 0 */
                spi->DIVIDER &= (~SPI_DIVIDER_DIVIDER_Msk);
                /* Return master peripheral clock rate */
                return (u32ClkSrc / 2);
            }
            else if(u32BusClock == 0)
            {
                /* Set DIVIDER to the maximum value 0xFFFF */
                spi->DIVIDER = (spi->DIVIDER & (~SPI_DIVIDER_DIVIDER_Msk)) | (0xFFFF << SPI_DIVIDER_DIVIDER_Pos);
                /* Return master peripheral clock rate */
                return (u32ClkSrc / ((0xFFFF + 1) * 2));
            }
            else
            {
                u32Div = (((u32ClkSrc * 10) / (u32BusClock * 2) + 5) / 10) - 1; /* Round to the nearest integer */
                if(u32Div > 0xFFFF)
                    u32Div = 0xFFFF;
                spi->DIVIDER = (spi->DIVIDER & (~SPI_DIVIDER_DIVIDER_Msk)) | (u32Div << SPI_DIVIDER_DIVIDER_Pos);
                /* Return master peripheral clock rate */
                return (u32ClkSrc / ((u32Div + 1) * 2));
            }
        }
        else /* For slave mode, SPI peripheral clock rate is equal to system clock rate. */
        {
            /* Default setting: slave select signal is low level active. */
            spi->SSR = SPI_SSR_SS_LTRIG_Msk;
            /* Return slave peripheral clock rate */
            return u32ClkSrc;
        }
    }
    else /* M05xxDN or M05xxDE */
    {
        /* Set BCn = 1: f_spi = f_spi_clk_src / (DIVIDER + 1) */
        spi->CNTRL2 |= SPI_CNTRL2_BCn_Msk;

        if(u32MasterSlave == SPI_MASTER)
        {
            /* Default setting: slave select signal is active low; disable automatic slave select function. */
            spi->SSR = SPI_SS_ACTIVE_LOW;

            /* Check clock source of SPI */
            if(spi == SPI0)
            {
                if((CLK->CLKSEL1 & CLK_CLKSEL1_SPI0_S_Msk) == CLK_CLKSEL1_SPI0_S_HCLK)
                    u32ClkSrc = CLK_GetHCLKFreq();
                else
                    u32ClkSrc = CLK_GetPLLClockFreq();
            }
            else
            {
                if((CLK->CLKSEL1 & CLK_CLKSEL1_SPI1_S_Msk) == CLK_CLKSEL1_SPI1_S_HCLK)
                    u32ClkSrc = CLK_GetHCLKFreq();
                else
                    u32ClkSrc = CLK_GetPLLClockFreq();
            }

            if(u32BusClock >= u32ClkSrc)
            {
                /* Set DIVIDER = 0 */
                spi->DIVIDER = 0;
                /* Return master peripheral clock rate */
                return u32ClkSrc;
            }
            else if(u32BusClock == 0)
            {
                /* Set BCn = 0: f_spi = f_spi_clk_src / ((DIVIDER + 1) * 2) */
                spi->CNTRL2 &= (~SPI_CNTRL2_BCn_Msk);
                /* Set DIVIDER to the maximum value 0xFF */
                spi->DIVIDER = (spi->DIVIDER & (~SPI_DIVIDER_DIVIDER_Msk)) | (0xFF << SPI_DIVIDER_DIVIDER_Pos);
                /* Return master peripheral clock rate */
                return (u32ClkSrc / ((0xFF + 1) * 2));
            }
            else
            {
                u32Div = (((u32ClkSrc * 10) / u32BusClock + 5) / 10) - 1; /* Round to the nearest integer */
                if(u32Div > 0xFF)
                {
                    /* Set BCn = 0: f_spi = f_spi_clk_src / ((DIVIDER + 1) * 2) */
                    spi->CNTRL2 &= (~SPI_CNTRL2_BCn_Msk);
                    u32Div = (((u32ClkSrc * 10) / (u32BusClock * 2) + 5) / 10) - 1; /* Round to the nearest integer */
                    if(u32Div > 0xFF)
                        u32Div = 0xFF;
                    spi->DIVIDER = (spi->DIVIDER & (~SPI_DIVIDER_DIVIDER_Msk)) | (u32Div << SPI_DIVIDER_DIVIDER_Pos);
                    /* Return master peripheral clock rate */
                    return (u32ClkSrc / ((u32Div + 1) * 2));
                }
                else
                {
                    spi->DIVIDER = (spi->DIVIDER & (~SPI_DIVIDER_DIVIDER_Msk)) | (u32Div << SPI_DIVIDER_DIVIDER_Pos);
                    /* Return master peripheral clock rate */
                    return (u32ClkSrc / (u32Div + 1));
                }
            }

        }
        else /* For slave mode, force the SPI peripheral clock rate to system clock rate. */
        {
            /* Default setting: slave select signal is low level active. */
            spi->SSR = SPI_SSR_SS_LTRIG_Msk;

            /* Select HCLK as the clock source of SPI */
            if(spi == SPI0)
                CLK->CLKSEL1 = (CLK->CLKSEL1 & (~CLK_CLKSEL1_SPI0_S_Msk)) | CLK_CLKSEL1_SPI0_S_HCLK;
            else
                CLK->CLKSEL1 = (CLK->CLKSEL1 & (~CLK_CLKSEL1_SPI1_S_Msk)) | CLK_CLKSEL1_SPI1_S_HCLK;


            /* Set DIVIDER = 0 */
            spi->DIVIDER = 0;
            /* Return slave peripheral clock rate */
            return u32ClkSrc;
        }
    }

}

/**
  * @brief  Reset SPI module and disable SPI peripheral clock.
  * @param  spi is the base address of SPI module.
  * @return None
  */
void SPI_Close(SPI_T *spi)
{
    if(spi == SPI0)
    {
        /* Reset SPI */
        SYS->IPRSTC2 |= SYS_IPRSTC2_SPI0_RST_Msk;
        SYS->IPRSTC2 &= ~SYS_IPRSTC2_SPI0_RST_Msk;

        /* Disable SPI clock */
        CLK->APBCLK &= ~CLK_APBCLK_SPI0_EN_Msk;
    }
    else
    {
        /* Reset SPI */
        SYS->IPRSTC2 |= SYS_IPRSTC2_SPI1_RST_Msk;
        SYS->IPRSTC2 &= ~SYS_IPRSTC2_SPI1_RST_Msk;

        /* Disable SPI clock */
        CLK->APBCLK &= ~CLK_APBCLK_SPI1_EN_Msk;
    }
}

/**
  * @brief  Clear RX FIFO buffer.
  * @param  spi is the base address of SPI module.
  * @return None
  */
void SPI_ClearRxFIFO(SPI_T *spi)
{
    spi->FIFO_CTL |= SPI_FIFO_CTL_RX_CLR_Msk;
}

/**
  * @brief  Clear TX FIFO buffer.
  * @param  spi is the base address of SPI module.
  * @return None
  */
void SPI_ClearTxFIFO(SPI_T *spi)
{
    spi->FIFO_CTL |= SPI_FIFO_CTL_TX_CLR_Msk;
}

/**
  * @brief  Disable the automatic slave select function and set slave select signal to inactive state.
  * @param  spi is the base address of SPI module.
  * @return None
  */
void SPI_DisableAutoSS(SPI_T *spi)
{
    spi->SSR &= ~(SPI_SSR_AUTOSS_Msk | SPI_SSR_SSR_Msk);
}

/**
  * @brief  Enable the automatic slave select function. Only available in Master mode.
  * @param  spi is the base address of SPI module.
  * @param  u32SSPinMask specifies slave select pins. (SPI_SS)
  * @param  u32ActiveLevel specifies the active level of slave select signal. (SPI_SS_ACTIVE_HIGH, SPI_SS_ACTIVE_LOW)
  * @return None
  */
void SPI_EnableAutoSS(SPI_T *spi, uint32_t u32SSPinMask, uint32_t u32ActiveLevel)
{
    spi->SSR = (spi->SSR & (~(SPI_SSR_AUTOSS_Msk | SPI_SSR_SS_LVL_Msk | SPI_SSR_SSR_Msk))) | (u32SSPinMask | u32ActiveLevel | SPI_SSR_AUTOSS_Msk);
}

/**
  * @brief  Set the SPI bus clock. Only available in Master mode.
  * @param  spi is the base address of SPI module.
  * @param  u32BusClock is the expected frequency of SPI bus clock in Hz.
  * @return Actual frequency of SPI peripheral clock.
  * @note   If u32BusClock = 0, DIVIDER setting will be set to the maximum value.
  * @note   On M05xxBN, if u32BusClock is equal to system clock rate, DIV_ONE will be set to 1.
  *            So that byte reorder function, byte suspend function and variable clock function must be disabled.
  * @note   On M05xxBN, if u32BusClock is larger than system clock rate, the SPI peripheral clock rate will be set to a half of system clock rate.
  * @note   On M05xxDN and M05xxDE, if u32BusClock is larger than system clock rate, the SPI peripheral clock rate will be set to equal to system clock rate.
  */
uint32_t SPI_SetBusClock(SPI_T *spi, uint32_t u32BusClock)
{
    uint32_t u32ClkSrc;
    uint32_t u32Div;

    if(((SYS->PDID & 0xF0000000) == 0) || ((SYS->PDID & 0xF0000000) == 0x10000000)) /* For M05xxAN and M05xxBN, the SPI peripheral clock source is PCLK. */
    {
        /* Get the system clock rate */
        u32ClkSrc = CLK_GetHCLKFreq();

        if((u32BusClock == u32ClkSrc) && ((SYS->PDID & 0xF0000000) == 0x10000000)) /* M05xxBN support DIV_ONE feature */
        {
            /* Enable DIV_ONE feature */
            /* Note: When DIV_ONE feature is enabled, byte reorder function, byte suspend function and variable clock function must be disabled. */
            spi->CNTRL2 |= SPI_CNTRL2_DIV_ONE_Msk;
            /* Return master peripheral clock rate */
            return u32ClkSrc;
        }
        else if(u32BusClock >= u32ClkSrc)
        {
            /* Set DIVIDER = 0 */
            spi->DIVIDER &= (~SPI_DIVIDER_DIVIDER_Msk);
            /* Return master peripheral clock rate */
            return (u32ClkSrc / 2);
        }
        else if(u32BusClock == 0)
        {
            /* Set DIVIDER to the maximum value 0xFFFF */
            spi->DIVIDER = (spi->DIVIDER & (~SPI_DIVIDER_DIVIDER_Msk)) | (0xFFFF << SPI_DIVIDER_DIVIDER_Pos);
            /* Return master peripheral clock rate */
            return (u32ClkSrc / ((0xFFFF + 1) * 2));
        }
        else
        {
            u32Div = (((u32ClkSrc * 10) / (u32BusClock * 2) + 5) / 10) - 1; /* Round to the nearest integer */
            if(u32Div > 0xFFFF)
                u32Div = 0xFFFF;
            spi->DIVIDER = (spi->DIVIDER & (~SPI_DIVIDER_DIVIDER_Msk)) | (u32Div << SPI_DIVIDER_DIVIDER_Pos);
            /* Return master peripheral clock rate */
            return (u32ClkSrc / ((u32Div + 1) * 2));
        }
    }
    else /* M05xxDN or M05xxDE */
    {
        /* Set BCn = 1: f_spi = f_spi_clk_src / (DIVIDER + 1) */
        spi->CNTRL2 |= SPI_CNTRL2_BCn_Msk;

        /* Check clock source of SPI */
        if(spi == SPI0)
        {
            if((CLK->CLKSEL1 & CLK_CLKSEL1_SPI0_S_Msk) == CLK_CLKSEL1_SPI0_S_HCLK)
                u32ClkSrc = CLK_GetHCLKFreq();
            else
                u32ClkSrc = CLK_GetPLLClockFreq();
        }
        else
        {
            if((CLK->CLKSEL1 & CLK_CLKSEL1_SPI1_S_Msk) == CLK_CLKSEL1_SPI1_S_HCLK)
                u32ClkSrc = CLK_GetHCLKFreq();
            else
                u32ClkSrc = CLK_GetPLLClockFreq();
        }

        if(u32BusClock >= u32ClkSrc)
        {
            /* Set DIVIDER = 0 */
            spi->DIVIDER = 0;
            /* Return master peripheral clock rate */
            return u32ClkSrc;
        }
        else if(u32BusClock == 0)
        {
            /* Set BCn = 0: f_spi = f_spi_clk_src / ((DIVIDER + 1) * 2) */
            spi->CNTRL2 &= (~SPI_CNTRL2_BCn_Msk);
            /* Set DIVIDER to the maximum value 0xFF */
            spi->DIVIDER = (spi->DIVIDER & (~SPI_DIVIDER_DIVIDER_Msk)) | (0xFF << SPI_DIVIDER_DIVIDER_Pos);
            /* Return master peripheral clock rate */
            return (u32ClkSrc / ((0xFF + 1) * 2));
        }
        else
        {
            u32Div = (((u32ClkSrc * 10) / u32BusClock + 5) / 10) - 1; /* Round to the nearest integer */
            if(u32Div > 0xFF)
            {
                /* Set BCn = 0: f_spi = f_spi_clk_src / ((DIVIDER + 1) * 2) */
                spi->CNTRL2 &= (~SPI_CNTRL2_BCn_Msk);
                u32Div = (((u32ClkSrc * 10) / (u32BusClock * 2) + 5) / 10) - 1; /* Round to the nearest integer */
                if(u32Div > 0xFF)
                    u32Div = 0xFF;
                spi->DIVIDER = (spi->DIVIDER & (~SPI_DIVIDER_DIVIDER_Msk)) | (u32Div << SPI_DIVIDER_DIVIDER_Pos);
                /* Return master peripheral clock rate */
                return (u32ClkSrc / ((u32Div + 1) * 2));
            }
            else
            {
                spi->DIVIDER = (spi->DIVIDER & (~SPI_DIVIDER_DIVIDER_Msk)) | (u32Div << SPI_DIVIDER_DIVIDER_Pos);
                /* Return master peripheral clock rate */
                return (u32ClkSrc / (u32Div + 1));
            }
        }
    }
}

/**
  * @brief  Enable FIFO mode with user-specified TX FIFO threshold and RX FIFO threshold configurations.
  * @param  spi is the base address of SPI module.
  * @param  u32TxThreshold decides the TX FIFO threshold.
  * @param  u32RxThreshold decides the RX FIFO threshold.
  * @return None
  */
void SPI_EnableFIFO(SPI_T *spi, uint32_t u32TxThreshold, uint32_t u32RxThreshold)
{
    spi->FIFO_CTL = (spi->FIFO_CTL & ~(SPI_FIFO_CTL_TX_THRESHOLD_Msk | SPI_FIFO_CTL_RX_THRESHOLD_Msk) |
                     (u32TxThreshold << SPI_FIFO_CTL_TX_THRESHOLD_Pos) |
                     (u32RxThreshold << SPI_FIFO_CTL_RX_THRESHOLD_Pos));

    spi->CNTRL |= SPI_CNTRL_FIFO_Msk;
}

/**
  * @brief  Disable FIFO mode.
  * @param  spi is the base address of SPI module.
  * @return None
  */
void SPI_DisableFIFO(SPI_T *spi)
{
    spi->CNTRL &= ~SPI_CNTRL_FIFO_Msk;
}

/**
  * @brief  Get the actual frequency of SPI bus clock. Only available in Master mode.
  * @param  spi is the base address of SPI module.
  * @return Actual SPI bus clock frequency.
  */
uint32_t SPI_GetBusClock(SPI_T *spi)
{
    uint32_t u32Div;
    uint32_t u32ClkSrc;

    if(((SYS->PDID & 0xF0000000) == 0) || ((SYS->PDID & 0xF0000000) == 0x10000000)) /* For M05xxAN and M05xxBN, the SPI peripheral clock source is PCLK. */
    {
        /* Get the system clock rate */
        u32ClkSrc = CLK_GetHCLKFreq();

        if(((SYS->PDID & 0xF0000000) == 0x10000000) && (spi->CNTRL2 & SPI_CNTRL2_DIV_ONE_Msk))
        {
            /* SPI bus clock rate is equal to system clock rate */
            return u32ClkSrc;
        }

        /* Get DIVIDER setting */
        u32Div = (spi->DIVIDER & SPI_DIVIDER_DIVIDER_Msk) >> SPI_DIVIDER_DIVIDER_Pos;
        /* Return SPI bus clock rate */
        return (u32ClkSrc / ((u32Div + 1) * 2));
    }
    else /* M05xxDN or M05xxDE */
    {
        /* Get DIVIDER setting */
        u32Div = (spi->DIVIDER & SPI_DIVIDER_DIVIDER_Msk) >> SPI_DIVIDER_DIVIDER_Pos;

        /* Check clock source of SPI */
        if(spi == SPI0)
        {
            if((CLK->CLKSEL1 & CLK_CLKSEL1_SPI0_S_Msk) == CLK_CLKSEL1_SPI0_S_HCLK)
                u32ClkSrc = CLK_GetHCLKFreq();
            else
                u32ClkSrc = CLK_GetPLLClockFreq();
        }
        else
        {
            if((CLK->CLKSEL1 & CLK_CLKSEL1_SPI1_S_Msk) == CLK_CLKSEL1_SPI1_S_HCLK)
                u32ClkSrc = CLK_GetHCLKFreq();
            else
                u32ClkSrc = CLK_GetPLLClockFreq();
        }

        if(spi->CNTRL2 & SPI_CNTRL2_BCn_Msk)   /* BCn = 1: f_spi = f_spi_clk_src / (DIVIDER + 1) */
        {
            /* Return SPI bus clock rate */
            return (u32ClkSrc / (u32Div + 1));
        }
        else /* BCn = 0: f_spi = f_spi_clk_src / ((DIVIDER + 1) * 2) */
        {
            /* Return SPI bus clock rate */
            return (u32ClkSrc / ((u32Div + 1) * 2));
        }
    }
}

/**
  * @brief  Enable SPI related interrupts specified by u32Mask parameter.
  * @param  spi is the base address of SPI module.
  * @param  u32Mask is the combination of all related interrupt enable bits.
  *         Each bit corresponds to a interrupt bit.
  *         This parameter decides which interrupts will be enabled.
  *            (SPI_UNIT_INT_MASK, SPI_SSTA_INT_MASK, SPI_FIFO_TX_INT_MASK,
  *            SPI_FIFO_RX_INT_MASK, SPI_FIFO_RXOV_INT_MASK, SPI_FIFO_TIMEOUT_INT_MASK)
  * @return None
  */
void SPI_EnableInt(SPI_T *spi, uint32_t u32Mask)
{
    /* Enable unit transfer interrupt flag */
    if((u32Mask & SPI_UNIT_INT_MASK) == SPI_UNIT_INT_MASK)
        spi->CNTRL |= SPI_CNTRL_IE_Msk;

    /* Enable slave 3-wire mode start interrupt flag */
    if((u32Mask & SPI_SSTA_INT_MASK) == SPI_SSTA_INT_MASK)
        spi->CNTRL2 |= SPI_CNTRL2_SSTA_INTEN_Msk;

    if(((SYS->PDID & 0xF0000000) == 0) || ((SYS->PDID & 0xF0000000) == 0x10000000)) /* M05xxAN or M05xxBN */
        return; /* M05xxAN and M05xxBN does not support the following functions */

    /* Enable TX threshold interrupt flag */
    if((u32Mask & SPI_FIFO_TX_INT_MASK) == SPI_FIFO_TX_INT_MASK)
        spi->FIFO_CTL |= SPI_FIFO_CTL_TX_INTEN_Msk;

    /* Enable RX threshold interrupt flag */
    if((u32Mask & SPI_FIFO_RX_INT_MASK) == SPI_FIFO_RX_INT_MASK)
        spi->FIFO_CTL |= SPI_FIFO_CTL_RX_INTEN_Msk;

    /* Enable RX overrun interrupt flag */
    if((u32Mask & SPI_FIFO_RXOV_INT_MASK) == SPI_FIFO_RXOV_INT_MASK)
        spi->FIFO_CTL |= SPI_FIFO_CTL_RXOV_INTEN_Msk;

    /* Enable RX time-out interrupt flag */
    if((u32Mask & SPI_FIFO_TIMEOUT_INT_MASK) == SPI_FIFO_TIMEOUT_INT_MASK)
        spi->FIFO_CTL |= SPI_FIFO_CTL_TIMEOUT_INTEN_Msk;
}

/**
  * @brief  Disable SPI related interrupts specified by u32Mask parameter.
  * @param  spi is the base address of SPI module.
  * @param  u32Mask is the combination of all related interrupt enable bits.
  *         Each bit corresponds to a interrupt bit.
  *         This parameter decides which interrupts will be disabled.
  *            (SPI_UNIT_INT_MASK, SPI_SSTA_INT_MASK, SPI_FIFO_TX_INT_MASK,
  *            SPI_FIFO_RX_INT_MASK, SPI_FIFO_RXOV_INT_MASK, SPI_FIFO_TIMEOUT_INT_MASK)
  * @return None
  */
void SPI_DisableInt(SPI_T *spi, uint32_t u32Mask)
{
    /* Disable unit transfer interrupt flag */
    if((u32Mask & SPI_UNIT_INT_MASK) == SPI_UNIT_INT_MASK)
        spi->CNTRL &= ~SPI_CNTRL_IE_Msk;

    /* Disable slave 3-wire mode start interrupt flag */
    if((u32Mask & SPI_SSTA_INT_MASK) == SPI_SSTA_INT_MASK)
        spi->CNTRL2 &= ~SPI_CNTRL2_SSTA_INTEN_Msk;

    if(((SYS->PDID & 0xF0000000) == 0) || ((SYS->PDID & 0xF0000000) == 0x10000000)) /* M05xxAN or M05xxBN */
        return; /* M05xxAN and M05xxBN does not support the following functions */

    /* Disable TX threshold interrupt flag */
    if((u32Mask & SPI_FIFO_TX_INT_MASK) == SPI_FIFO_TX_INT_MASK)
        spi->FIFO_CTL &= ~SPI_FIFO_CTL_TX_INTEN_Msk;

    /* Disable RX threshold interrupt flag */
    if((u32Mask & SPI_FIFO_RX_INT_MASK) == SPI_FIFO_RX_INT_MASK)
        spi->FIFO_CTL &= ~SPI_FIFO_CTL_RX_INTEN_Msk;

    /* Disable RX overrun interrupt flag */
    if((u32Mask & SPI_FIFO_RXOV_INT_MASK) == SPI_FIFO_RXOV_INT_MASK)
        spi->FIFO_CTL &= ~SPI_FIFO_CTL_RXOV_INTEN_Msk;

    /* Disable RX time-out interrupt flag */
    if((u32Mask & SPI_FIFO_TIMEOUT_INT_MASK) == SPI_FIFO_TIMEOUT_INT_MASK)
        spi->FIFO_CTL &= ~SPI_FIFO_CTL_TIMEOUT_INTEN_Msk;
}

/**
  * @brief  Get SPI related interrupt flags specified by u32Mask parameter.
  * @param  spi is the base address of SPI module.
  * @param  u32Mask is the combination of all related interrupt sources.
  *         Each bit corresponds to a interrupt source.
  *         This parameter decides which interrupt flags will be read.
  *            (SPI_UNIT_INT_MASK, SPI_SSTA_INT_MASK, SPI_FIFO_TX_INT_MASK,
  *            SPI_FIFO_RX_INT_MASK, SPI_FIFO_RXOV_INT_MASK, SPI_FIFO_TIMEOUT_INT_MASK)
  * @return Interrupt flags of selected sources.
  */
uint32_t SPI_GetIntFlag(SPI_T *spi, uint32_t u32Mask)
{
    uint32_t u32IntFlag = 0;

    /* Check unit transfer interrupt flag */
    if((u32Mask & SPI_UNIT_INT_MASK) && (spi->CNTRL & SPI_CNTRL_IF_Msk))
        u32IntFlag |= SPI_UNIT_INT_MASK;

    /* Check slave 3-wire mode start interrupt flag */
    if((u32Mask & SPI_SSTA_INT_MASK) && (spi->CNTRL2 & SPI_CNTRL2_SLV_START_INTSTS_Msk))
        u32IntFlag |= SPI_SSTA_INT_MASK;

    if(((SYS->PDID & 0xF0000000) == 0) || ((SYS->PDID & 0xF0000000) == 0x10000000)) /* M05xxAN or M05xxBN */
        return u32IntFlag; /* M05xxAN and M05xxBN does not support the following functions */

    /* Check TX threshold interrupt flag */
    if((u32Mask & SPI_FIFO_TX_INT_MASK) && (spi->STATUS & SPI_STATUS_TX_INTSTS_Msk))
        u32IntFlag |= SPI_FIFO_TX_INT_MASK;

    /* Check RX threshold interrupt flag */
    if((u32Mask & SPI_FIFO_RX_INT_MASK) && (spi->STATUS & SPI_STATUS_RX_INTSTS_Msk))
        u32IntFlag |= SPI_FIFO_RX_INT_MASK;

    /* Check RX overrun interrupt flag */
    if((u32Mask & SPI_FIFO_RXOV_INT_MASK) && (spi->STATUS & SPI_STATUS_RX_OVERRUN_Msk))
        u32IntFlag |= SPI_FIFO_RXOV_INT_MASK;

    /* Check RX time-out interrupt flag */
    if((u32Mask & SPI_FIFO_TIMEOUT_INT_MASK) && (spi->STATUS & SPI_STATUS_TIMEOUT_Msk))
        u32IntFlag |= SPI_FIFO_TIMEOUT_INT_MASK;

    return u32IntFlag;
}

/**
  * @brief  Clear SPI related interrupt flags specified by u32Mask parameter.
  * @param  spi is the base address of SPI module.
  * @param  u32Mask is the combination of all related interrupt sources.
  *         Each bit corresponds to a interrupt source.
  *         This parameter decides which interrupt flags will be cleared.
  *            (SPI_UNIT_INT_MASK, SPI_SSTA_INT_MASK,
  *            SPI_FIFO_RXOV_INT_MASK, SPI_FIFO_TIMEOUT_INT_MASK)
  * @return None
  */
void SPI_ClearIntFlag(SPI_T *spi, uint32_t u32Mask)
{
    if(u32Mask & SPI_UNIT_INT_MASK)
        spi->CNTRL |= SPI_CNTRL_IF_Msk; /* Clear unit transfer interrupt flag */

    if(u32Mask & SPI_SSTA_INT_MASK)
        spi->CNTRL2 |= SPI_CNTRL2_SLV_START_INTSTS_Msk; /* Clear slave 3-wire mode start interrupt flag */

    if(((SYS->PDID & 0xF0000000) == 0) || ((SYS->PDID & 0xF0000000) == 0x10000000)) /* M05xxAN or M05xxBN */
        return; /* M05xxAN and M05xxBN does not support the following functions */

    if(u32Mask & SPI_FIFO_RXOV_INT_MASK)
        spi->STATUS = SPI_STATUS_RX_OVERRUN_Msk; /* Clear RX overrun interrupt flag */

    if(u32Mask & SPI_FIFO_TIMEOUT_INT_MASK)
        spi->STATUS = SPI_STATUS_TIMEOUT_Msk; /* Clear RX time-out interrupt flag */
}

/**
  * @brief  Get SPI related status specified by u32Mask parameter.
  * @param  spi is the base address of SPI module.
  * @param  u32Mask is the combination of all related sources.
  *         Each bit corresponds to a source.
  *         This parameter decides which flags will be read.
  *            (SPI_BUSY_MASK, SPI_RX_EMPTY_MASK, SPI_RX_FULL_MASK,
  *            SPI_TX_EMPTY_MASK, SPI_TX_FULL_MASK)
  * @return Flags of selected sources.
  */
uint32_t SPI_GetStatus(SPI_T *spi, uint32_t u32Mask)
{
    uint32_t u32Flag = 0;

    /* Check busy status */
    if((u32Mask & SPI_BUSY_MASK) && (spi->CNTRL & SPI_CNTRL_GO_BUSY_Msk))
        u32Flag |= SPI_BUSY_MASK;

    if(((SYS->PDID & 0xF0000000) == 0) || ((SYS->PDID & 0xF0000000) == 0x10000000)) /* M05xxAN or M05xxBN */
        return u32Flag; /* M05xxAN and M05xxBN does not support the following functions */

    /* Check RX empty flag */
    if((u32Mask & SPI_RX_EMPTY_MASK) && (spi->CNTRL & SPI_CNTRL_RX_EMPTY_Msk))
        u32Flag |= SPI_RX_EMPTY_MASK;

    /* Check RX full flag */
    if((u32Mask & SPI_RX_FULL_MASK) && (spi->CNTRL & SPI_CNTRL_RX_FULL_Msk))
        u32Flag |= SPI_RX_FULL_MASK;

    /* Check TX empty flag */
    if((u32Mask & SPI_TX_EMPTY_MASK) && (spi->CNTRL & SPI_CNTRL_TX_EMPTY_Msk))
        u32Flag |= SPI_TX_EMPTY_MASK;

    /* Check TX full flag */
    if((u32Mask & SPI_TX_FULL_MASK) && (spi->CNTRL & SPI_CNTRL_TX_FULL_Msk))
        u32Flag |= SPI_TX_FULL_MASK;

    return u32Flag;
}

/*@}*/ /* end of group M051_SPI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group M051_SPI_Driver */

/*@}*/ /* end of group M051_Device_Driver */

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
