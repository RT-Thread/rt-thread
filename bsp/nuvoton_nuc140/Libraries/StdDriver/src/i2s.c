/**************************************************************************//**
 * @file     i2s.c
 * @version  V3.0
 * $Revision: 2 $
 * $Date: 15/05/04 3:27p $
 * @brief    I2S driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include "NUC100Series.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup I2S_Driver I2S Driver
  @{
*/

/** @addtogroup I2S_EXPORTED_FUNCTIONS I2S Exported Functions
  @{
*/

/**
  * @brief  This function is used to get I2S source clock frequency.
  * @param[in]  i2s The pointer of the specified I2S module.
  * @return I2S source clock frequency (Hz).
  * @details Return the source clock frequency according to the setting of I2S_S (CLKSEL2[1:0]).
  */
static uint32_t I2S_GetSourceClockFreq(I2S_T *i2s)
{
    uint32_t u32Freq, u32ClkSrcSel;

    u32ClkSrcSel = CLK->CLKSEL2 & CLK_CLKSEL2_I2S_S_Msk;

    switch(u32ClkSrcSel)
    {
    case CLK_CLKSEL2_I2S_S_HXT:
        u32Freq = __HXT;
        break;

    case CLK_CLKSEL2_I2S_S_PLL:
        u32Freq = CLK_GetPLLClockFreq();
        break;

    case CLK_CLKSEL2_I2S_S_HIRC:
        u32Freq = __HIRC;
        break;

    case CLK_CLKSEL2_I2S_S_HCLK:
        u32Freq = SystemCoreClock;
        break;

    default:
        u32Freq = __HIRC;
        break;
    }

    return u32Freq;
}

/**
  * @brief  This function configures some parameters of I2S interface for general purpose use.
  * @param[in] i2s The pointer of the specified I2S module.
  * @param[in] u32MasterSlave I2S operation mode. Valid values are:
  *                                     - \ref I2S_MODE_MASTER
  *                                     - \ref I2S_MODE_SLAVE
  * @param[in] u32SampleRate Sample rate
  * @param[in] u32WordWidth Data length. Valid values are:
  *                                     - \ref I2S_DATABIT_8
  *                                     - \ref I2S_DATABIT_16
  *                                     - \ref I2S_DATABIT_24
  *                                     - \ref I2S_DATABIT_32
  * @param[in] u32Channels Audio format. Valid values are:
  *                                     - \ref I2S_MONO
  *                                     - \ref I2S_STEREO
  * @param[in] u32DataFormat Data format. Valid values are:
  *                                     - \ref I2S_FORMAT_I2S
  *                                     - \ref I2S_FORMAT_MSB
  * @return Real sample rate.
  * @details This function will configure I2S controller according to the input parameters. Set TX and RX FIFO threshold to middle value.
  *          The actual sample rate may be different from the target sample rate. The real sample rate will be returned for reference.
  * @note   Both the TX and RX functions will be enabled.
  */
uint32_t I2S_Open(I2S_T *i2s, uint32_t u32MasterSlave, uint32_t u32SampleRate, uint32_t u32WordWidth, uint32_t u32Channels, uint32_t u32DataFormat)
{
    uint8_t u8Divider;
    uint32_t u32BitRate, u32SrcClk;

    /* Reset I2S */
    SYS->IPRSTC2 |= SYS_IPRSTC2_I2S_RST_Msk;
    SYS->IPRSTC2 &= ~SYS_IPRSTC2_I2S_RST_Msk;

    /* Configure I2S controller according to input parameters. */
    i2s->CON = u32MasterSlave | u32WordWidth | u32Channels | u32DataFormat | I2S_FIFO_TX_LEVEL_WORD_4 | I2S_FIFO_RX_LEVEL_WORD_4;

    /* Get I2S source clock frequency */
    u32SrcClk = I2S_GetSourceClockFreq(i2s);

    /* Calculate bit clock rate */
    u32BitRate = u32SampleRate * (((u32WordWidth >> 4) & 0x3) + 1) * 16;
    u8Divider = ((u32SrcClk / u32BitRate) >> 1) - 1;
    i2s->CLKDIV = (i2s->CLKDIV & ~I2S_CLKDIV_BCLK_DIV_Msk) | (u8Divider << 8);

    /* Calculate real sample rate */
    u32BitRate = u32SrcClk / ((u8Divider + 1) * 2);
    u32SampleRate = u32BitRate / ((((u32WordWidth >> 4) & 0x3) + 1) * 16);

    /* Enable TX, RX and I2S controller */
    i2s->CON |= (I2S_CON_RXEN_Msk | I2S_CON_TXEN_Msk | I2S_CON_I2SEN_Msk);

    return u32SampleRate;
}

/**
  * @brief  Disable I2S function.
  * @param[in]  i2s The pointer of the specified I2S module.
  * @return None
  * @details Disable I2S function.
  */
void I2S_Close(I2S_T *i2s)
{
    i2s->CON &= ~I2S_CON_I2SEN_Msk;
}

/**
  * @brief Enable interrupt function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @param[in] u32Mask The combination of all related interrupt enable bits.
  *            Each bit corresponds to a interrupt bit.
  * @return None
  * @details This function enables the interrupt according to the mask parameter.
  */
void I2S_EnableInt(I2S_T *i2s, uint32_t u32Mask)
{
    i2s->IE |= u32Mask;
}

/**
  * @brief Disable interrupt function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @param[in] u32Mask The combination of all related interrupt enable bits.
  *            Each bit corresponds to a interrupt bit.
  * @return None
  * @details This function disables the interrupt according to the mask parameter.
  */
void I2S_DisableInt(I2S_T *i2s, uint32_t u32Mask)
{
    i2s->IE &= ~u32Mask;
}

/**
  * @brief  Enable master clock (MCLK).
  * @param[in] i2s The pointer of the specified I2S module.
  * @param[in] u32BusClock The target MCLK clock.
  * @return Actual MCLK clock
  * @details Set the master clock rate according to u32BusClock parameter and enable master clock output.
  *          The actual master clock rate may be different from the target master clock rate. The real master clock rate will be returned for reference.
  */
uint32_t I2S_EnableMCLK(I2S_T *i2s, uint32_t u32BusClock)
{
    uint8_t u8Divider;
    uint32_t u32SrcClk, u32Reg;

    u32SrcClk = I2S_GetSourceClockFreq(i2s);
    if(u32BusClock == u32SrcClk)
        u8Divider = 0;
    else
        u8Divider = (u32SrcClk / u32BusClock) >> 1;

    i2s->CLKDIV = (i2s->CLKDIV & ~I2S_CLKDIV_MCLK_DIV_Msk) | u8Divider;

    i2s->CON |= I2S_CON_MCLKEN_Msk;

    u32Reg = i2s->CLKDIV & I2S_CLKDIV_MCLK_DIV_Msk;

    if(u32Reg == 0)
        return u32SrcClk;
    else
        return ((u32SrcClk >> 1) / u32Reg);
}

/**
  * @brief  Disable master clock (MCLK).
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details Disable master clock output.
  */
void I2S_DisableMCLK(I2S_T *i2s)
{
    i2s->CON &= ~I2S_CON_MCLKEN_Msk;
}

/*@}*/ /* end of group I2S_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group I2S_Driver */

/*@}*/ /* end of group Device_Driver */

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
