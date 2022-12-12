/**************************************************************************//**
 * @file     i2s.c
 * @version  V3.00
 * @brief    M460 series I2S driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup I2S_Driver I2S Driver
  @{
*/

/** @addtogroup I2S_EXPORTED_FUNCTIONS I2S Exported Functions
  @{
*/

static uint32_t I2S_GetSourceClockFreq(I2S_T *i2s);

/**
  * @brief  This function is used to get I2S source clock frequency.
  * @param[in]  i2s is the base address of I2S module.
  * @return I2S source clock frequency (Hz).
  */
static uint32_t I2S_GetSourceClockFreq(I2S_T *i2s)
{
    uint32_t u32Freq = 0UL, u32ClkSrcSel;

    if (i2s == I2S0)
    {
        /* get I2S selection clock source */
        u32ClkSrcSel = CLK->CLKSEL3 & CLK_CLKSEL3_I2S0SEL_Msk;

        switch (u32ClkSrcSel)
        {
        case CLK_CLKSEL3_I2S0SEL_HXT:
            u32Freq = __HXT;
            break;

        case CLK_CLKSEL3_I2S0SEL_PLL_DIV2:
            u32Freq = (CLK_GetPLLClockFreq() >> 1);
            break;

        case CLK_CLKSEL3_I2S0SEL_PCLK0:
            u32Freq = CLK_GetPCLK0Freq();
            break;

        case CLK_CLKSEL3_I2S0SEL_HIRC:
            u32Freq = __HIRC;
            break;

        case CLK_CLKSEL3_I2S0SEL_HIRC48M:
            u32Freq = __HIRC48M;
            break;

        case CLK_CLKSEL3_I2S0SEL_PLLFN_DIV2:
            u32Freq = (CLK_GetPLLFNClockFreq() >> 1);
            break;

        default:
            u32Freq = __HXT;
            break;
        }
    }
    else if (i2s == I2S1)
    {
        /* get I2S selection clock source */
        u32ClkSrcSel = CLK->CLKSEL2 & CLK_CLKSEL2_I2S1SEL_Msk;

        switch (u32ClkSrcSel)
        {
        case CLK_CLKSEL2_I2S1SEL_HXT:
            u32Freq = __HXT;
            break;

        case CLK_CLKSEL2_I2S1SEL_PLL_DIV2:
            u32Freq = (CLK_GetPLLClockFreq() >> 1);
            break;

        case CLK_CLKSEL2_I2S1SEL_PCLK1:
            u32Freq = CLK_GetPCLK1Freq();
            break;

        case CLK_CLKSEL2_I2S1SEL_HIRC:
            u32Freq = __HIRC;
            break;

        case CLK_CLKSEL2_I2S1SEL_HIRC48M:
            u32Freq = __HIRC48M;
            break;

        case CLK_CLKSEL2_I2S1SEL_PLLFN_DIV2:
            u32Freq = (CLK_GetPLLFNClockFreq() >> 1);
            break;

        default:
            u32Freq = __HXT;
            break;
        }
    }

    return u32Freq;
}

/**
  * @brief  This function configures some parameters of I2S interface for general purpose use.
  *         The sample rate may not be used from the parameter, it depends on system's clock settings,
  *         but real sample rate used by system will be returned for reference.
  * @param[in] i2s is the base address of I2S module.
  * @param[in] u32MasterSlave I2S operation mode. Valid values are:
  *                                     - \ref I2S_MODE_MASTER
  *                                     - \ref I2S_MODE_SLAVE
  * @param[in] u32SampleRate Sample rate
  * @param[in] u32WordWidth Data length. Valid values are:
  *                                     - \ref I2S_DATABIT_8
  *                                     - \ref I2S_DATABIT_16
  *                                     - \ref I2S_DATABIT_24
  *                                     - \ref I2S_DATABIT_32
  * @param[in] u32MonoData: Set audio data to mono or not. Valid values are:
  *                                     - \ref I2S_ENABLE_MONO
  *                                     - \ref I2S_DISABLE_MONO
  * @param[in] u32DataFormat: Data format. This is also used to select I2S or PCM(TDM) function. Valid values are:
  *                                     - \ref I2S_FORMAT_I2S
  *                                     - \ref I2S_FORMAT_I2S_MSB
  *                                     - \ref I2S_FORMAT_I2S_LSB
  *                                     - \ref I2S_FORMAT_PCM
  *                                     - \ref I2S_FORMAT_PCM_MSB
  *                                     - \ref I2S_FORMAT_PCM_LSB
  * @return Real sample rate.
  */
uint32_t I2S_Open(I2S_T *i2s, uint32_t u32MasterSlave, uint32_t u32SampleRate, uint32_t u32WordWidth, uint32_t u32MonoData, uint32_t u32DataFormat)
{
    uint16_t u16Divider;
    uint32_t u32BitRate, u32SrcClk;

    if (i2s == I2S0)
    {
        SYS->IPRST1 |= SYS_IPRST1_I2S0RST_Msk;
        SYS->IPRST1 &= ~SYS_IPRST1_I2S0RST_Msk;
    }
    else if (i2s == I2S1)
    {
        SYS->IPRST2 |= SYS_IPRST2_I2S1RST_Msk;
        SYS->IPRST2 &= ~SYS_IPRST2_I2S1RST_Msk;
    }

    i2s->CTL0 = u32MasterSlave | u32WordWidth | u32MonoData | u32DataFormat;
    i2s->CTL1 = I2S_FIFO_TX_LEVEL_WORD_8 | I2S_FIFO_RX_LEVEL_WORD_8;

    u32SrcClk = I2S_GetSourceClockFreq(i2s);

    u32BitRate = u32SampleRate * (((u32WordWidth >> 4U) & 0x3U) + 1U) * 16U;
    u16Divider = (uint16_t)((((u32SrcClk * 10UL / u32BitRate) >> 1U) + 5UL) / 10UL) - 1U; /* Round to the nearest integer */
    i2s->CLKDIV = (i2s->CLKDIV & ~I2S_CLKDIV_BCLKDIV_Msk) | ((uint32_t)u16Divider << 8U);

    /* Calculate real sample rate */
    u32BitRate = u32SrcClk / (2U * ((uint32_t)u16Divider + 1U));
    u32SampleRate = u32BitRate / ((((u32WordWidth >> 4U) & 0x3U) + 1U) * 16U);

    i2s->CTL0 |= I2S_CTL0_I2SEN_Msk;

    return u32SampleRate;
}

/**
  * @brief  Disable I2S function and I2S clock.
  * @param[in]  i2s is the base address of I2S module.
  * @return none
  */
void I2S_Close(I2S_T *i2s)
{
    i2s->CTL0 &= ~I2S_CTL0_I2SEN_Msk;
}

/**
  * @brief This function enables the interrupt according to the mask parameter.
  * @param[in] i2s is the base address of I2S module.
  * @param[in] u32Mask is the combination of all related interrupt enable bits.
  *            Each bit corresponds to a interrupt bit.
  * @return none
  */
void I2S_EnableInt(I2S_T *i2s, uint32_t u32Mask)
{
    i2s->IEN |= u32Mask;
}

/**
  * @brief This function disables the interrupt according to the mask parameter.
  * @param[in] i2s is the base address of I2S module.
  * @param[in] u32Mask is the combination of all related interrupt enable bits.
  *            Each bit corresponds to a interrupt bit.
  * @return none
  */
void I2S_DisableInt(I2S_T *i2s, uint32_t u32Mask)
{
    i2s->IEN &= ~u32Mask;
}

/**
  * @brief  Enable MCLK .
  * @param[in] i2s is the base address of I2S module.
  * @param[in] u32BusClock is the target MCLK clock
  * @return Actual MCLK clock
  */
uint32_t I2S_EnableMCLK(I2S_T *i2s, uint32_t u32BusClock)
{
    uint8_t u8Divider;
    uint32_t u32SrcClk, u32Reg, u32Clock;

    u32SrcClk = I2S_GetSourceClockFreq(i2s);
    if (u32BusClock == u32SrcClk)
    {
        u8Divider = 0U;
    }
    else
    {
        u8Divider = (uint8_t)(u32SrcClk / u32BusClock) >> 1U;
    }

    i2s->CLKDIV = (i2s->CLKDIV & ~I2S_CLKDIV_MCLKDIV_Msk) | u8Divider;

    i2s->CTL0 |= I2S_CTL0_MCLKEN_Msk;

    u32Reg = i2s->CLKDIV & I2S_CLKDIV_MCLKDIV_Msk;

    if (u32Reg == 0U)
    {
        u32Clock = u32SrcClk;
    }
    else
    {
        u32Clock = (u32SrcClk >> 1U) / u32Reg;
    }

    return u32Clock;
}

/**
  * @brief  Disable MCLK .
  * @param[in] i2s is the base address of I2S module.
  * @return none
  */
void I2S_DisableMCLK(I2S_T *i2s)
{
    i2s->CTL0 &= ~I2S_CTL0_MCLKEN_Msk;
}

/**
  * @brief  Configure FIFO threshold setting.
  * @param[in]  i2s The pointer of the specified I2S module.
  * @param[in]  u32TxThreshold Decides the TX FIFO threshold. It could be 0 ~ 15.
  * @param[in]  u32RxThreshold Decides the RX FIFO threshold. It could be 0 ~ 15.
  * @return None
  * @details Set TX FIFO threshold and RX FIFO threshold configurations.
  */
void I2S_SetFIFO(I2S_T *i2s, uint32_t u32TxThreshold, uint32_t u32RxThreshold)
{
    i2s->CTL1 = (i2s->CTL1 & ~(I2S_CTL1_TXTH_Msk | I2S_CTL1_RXTH_Msk)) |
                (u32TxThreshold << I2S_CTL1_TXTH_Pos) |
                (u32RxThreshold << I2S_CTL1_RXTH_Pos);
}

/**
  * @brief  Configure PCM(TDM) function parameters, such as channel width, channel number and sync pulse width
  * @param[in]  i2s The pointer of the specified I2S module.
  * @param[in]  u32ChannelWidth Channel width. Valid values are:
  *                                                             - \ref I2S_TDM_WIDTH_8BIT
  *                                                             - \ref I2S_TDM_WIDTH_16BIT
  *                                                             - \ref I2S_TDM_WIDTH_24BIT
  *                                                             - \ref I2S_TDM_WIDTH_32BIT
  * @param[in]  u32ChannelNum Channel number. Valid values are:
  *                                                             - \ref I2S_TDM_2CH
  *                                                             - \ref I2S_TDM_4CH
  *                                                             - \ref I2S_TDM_6CH
  *                                                             - \ref I2S_TDM_8CH
  * @param[in]  u32SyncWidth Width for sync pulse. Valid values are:
  *                                                             - \ref I2S_TDM_SYNC_ONE_BCLK
  *                                                             - \ref I2S_TDM_SYNC_ONE_CHANNEL
  * @return None
  * @details Set TX FIFO threshold and RX FIFO threshold configurations.
  */
void I2S_ConfigureTDM(I2S_T *i2s, uint32_t u32ChannelWidth, uint32_t u32ChannelNum, uint32_t u32SyncWidth)
{
    i2s->CTL0 = (i2s->CTL0 & ~(I2S_CTL0_TDMCHNUM_Msk | I2S_CTL0_CHWIDTH_Msk | I2S_CTL0_PCMSYNC_Msk)) |
                (u32ChannelWidth << I2S_CTL0_CHWIDTH_Pos) |
                (u32ChannelNum << I2S_CTL0_TDMCHNUM_Pos) |
                (u32SyncWidth << I2S_CTL0_PCMSYNC_Pos);
}

/*@}*/ /* end of group I2S_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group I2S_Driver */

/*@}*/ /* end of group Standard_Driver */
