/******************************************************************************
 * @file     i2s.c
 * @version  V0.10
 * $Revision: 15 $
 * $Date: 15/06/23 5:56p $
 * @brief    NUC472/NUC442 I2S driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include "NUC472_442.h"

/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_I2S_Driver I2S Driver
  @{
*/

/** @addtogroup NUC472_442_I2S_EXPORTED_FUNCTIONS I2S Exported Functions
  @{
*/

/**
  * @brief  This function is used to get I2S source clock frequency.
  * @param[in]  i2s is the base address of I2S module.
  * @return I2S source clock frequency (Hz).
  */
static uint32_t I2S_GetSourceClockFreq(I2S_T *i2s)
{
    uint32_t u32Freq, u32ClkSrcSel;

    // get I2S selection clock source
    if((uint32_t)i2s == I2S0_BASE)
        u32ClkSrcSel = CLK->CLKSEL3 & CLK_CLKSEL3_I2S0SEL_Msk;
    else
        u32ClkSrcSel = CLK->CLKSEL3 & CLK_CLKSEL3_I2S1SEL_Msk;

    switch (u32ClkSrcSel) {
    case CLK_CLKSEL3_I2S0SEL_HXT:
        u32Freq = __HXT;
        break;

    case CLK_CLKSEL3_I2S0SEL_PLL:
    case CLK_CLKSEL3_I2S1SEL_PLL:
        u32Freq = CLK_GetPLLClockFreq();
        break;

    case CLK_CLKSEL3_I2S0SEL_HIRC:
    case CLK_CLKSEL3_I2S1SEL_HIRC:
        u32Freq = __HIRC;
        break;

    case CLK_CLKSEL3_I2S0SEL_PCLK:
    case CLK_CLKSEL3_I2S1SEL_PCLK:
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
  * @param[in] u32Channels: Audio format. Valid values are:
  *                                     - \ref I2S_MONO
  *                                     - \ref I2S_STEREO
  * @param[in] u32DataFormat: Data format. Valid values are:
  *                                     - \ref I2S_FORMAT_I2S
  *                                     - \ref I2S_FORMAT_MSB
  *                                     - \ref I2S_FORMAT_PCMA
  *                                     - \ref I2S_FORMAT_PCMB
  * @param[in] u32AudioInterface: Audio interface. Valid values are:
  *                                     - \ref I2S_I2S
  *                                     - \ref I2S_PCM
  * @return Real sample rate.
  */
uint32_t I2S_Open(I2S_T *i2s, uint32_t u32MasterSlave, uint32_t u32SampleRate, uint32_t u32WordWidth, uint32_t u32Channels, uint32_t u32DataFormat, uint32_t u32AudioInterface)
{
    uint16_t u16Divider;
    uint32_t u32BitRate, u32SrcClk;

    if((uint32_t)i2s == I2S0_BASE) {
        SYS->IPRST1 |= SYS_IPRST1_I2S0RST_Msk;
        SYS->IPRST1 &= ~SYS_IPRST1_I2S0RST_Msk;
    } else {
        SYS->IPRST1 |= SYS_IPRST1_I2S1RST_Msk;
        SYS->IPRST1 &= ~SYS_IPRST1_I2S1RST_Msk;
    }

    i2s->CTL = u32MasterSlave | u32WordWidth | u32Channels | u32DataFormat | u32AudioInterface | I2S_FIFO_TX_LEVEL_WORD_4 | I2S_FIFO_RX_LEVEL_WORD_4;

    u32SrcClk = I2S_GetSourceClockFreq(i2s);

    u32BitRate = u32SampleRate * (((u32WordWidth>>4) & 0x3) + 1) * 16;
    u16Divider = ((u32SrcClk/u32BitRate) >> 1) - 1;
    i2s->CLKDIV = (i2s->CLKDIV & ~I2S_CLKDIV_BCLKDIV_Msk) | (u16Divider << 8);

    //calculate real sample rate
    u32BitRate = u32SrcClk / (2*(u16Divider+1));
    u32SampleRate = u32BitRate / ((((u32WordWidth>>4) & 0x3) + 1) * 16);

    i2s->CTL |= I2S_CTL_I2SEN_Msk;

    return u32SampleRate;
}

/**
  * @brief  Disable I2S function and I2S clock.
  * @param[in]  i2s is the base address of I2S module.
  * @return none
  */
void I2S_Close(I2S_T *i2s)
{
    i2s->CTL &= ~I2S_CTL_I2SEN_Msk;
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
    uint32_t u32SrcClk, u32Reg;

    u32SrcClk = I2S_GetSourceClockFreq(i2s);
    if (u32BusClock == u32SrcClk)
        u8Divider = 0;
    else
        u8Divider = (u32SrcClk/u32BusClock) >> 1;

    i2s->CLKDIV = (i2s->CLKDIV & ~I2S_CLKDIV_MCLKDIV_Msk) | u8Divider;

    i2s->CTL |= I2S_CTL_MCLKEN_Msk;

    u32Reg = i2s->CLKDIV & I2S_CLKDIV_MCLKDIV_Msk;

    if (u32Reg == 0)
        return u32SrcClk;
    else
        return ((u32SrcClk >> 1) / u32Reg);
}

/**
  * @brief  Disable MCLK .
  * @param[in] i2s is the base address of I2S module.
  * @return none
  */
void I2S_DisableMCLK(I2S_T *i2s)
{
    i2s->CTL &= ~I2S_CTL_MCLKEN_Msk;
}

/**
  * @brief  Configure FIFO threshold setting.
  * @param[in]  i2s The pointer of the specified I2S module.
  * @param[in]  u32TxThreshold Decides the TX FIFO threshold. It could be 0 ~ 7.
  * @param[in]  u32RxThreshold Decides the RX FIFO threshold. It could be 0 ~ 7.
  * @return None
  * @details Set TX FIFO threshold and RX FIFO threshold configurations.
  */
void I2S_SetFIFO(I2S_T *i2s, uint32_t u32TxThreshold, uint32_t u32RxThreshold)
{
    i2s->CTL = (i2s->CTL & ~(I2S_CTL_TXTH_Msk | I2S_CTL_RXTH_Msk) |
                (u32TxThreshold << I2S_CTL_TXTH_Pos) |
                (u32RxThreshold << I2S_CTL_RXTH_Pos));
}
/*@}*/ /* end of group NUC472_442_I2S_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_I2S_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
