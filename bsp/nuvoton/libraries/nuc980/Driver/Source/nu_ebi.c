/**************************************************************************//**
 * @file     ebi.c
 * @version  V1.00
 * @brief    NUC980 series External Bus Interface(EBI) driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "nuc980.h"
#include "nu_ebi.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup EBI_Driver EBI Driver
  @{
*/


/** @addtogroup EBI_EXPORTED_FUNCTIONS EBI Exported Functions
  @{
*/

/**
  * @brief      Initialize EBI for specify Bank
  *
  * @param[in]  u32Bank             Bank number for EBI. Valid values are:
  *                                     - \ref EBI_BANK0
  *                                     - \ref EBI_BANK1
  *                                     - \ref EBI_BANK2
  * @param[in]  u32DataWidth        Data bus width. Valid values are:
  *                                     - \ref EBI_BUSWIDTH_8BIT
  *                                     - \ref EBI_BUSWIDTH_16BIT
  * @param[in]  u32TimingClass      Default timing configuration. Valid values are:
  *                                     - \ref EBI_TIMING_FASTEST
  *                                     - \ref EBI_TIMING_VERYFAST
  *                                     - \ref EBI_TIMING_FAST
  *                                     - \ref EBI_TIMING_NORMAL
  *                                     - \ref EBI_TIMING_SLOW
  *                                     - \ref EBI_TIMING_VERYSLOW
  *                                     - \ref EBI_TIMING_SLOWEST
  * @param[in]  u32BusMode          Set EBI bus operate mode. Valid values are:
  *                                     - \ref EBI_OPMODE_NORMAL
  *                                     - \ref EBI_OPMODE_CACCESS
  * @param[in]  u32CSActiveLevel    CS is active High/Low. Valid values are:
  *                                     - \ref EBI_CS_ACTIVE_HIGH
  *                                     - \ref EBI_CS_ACTIVE_LOW
  *
  * @return     None
  *
  * @details    This function is used to open specify EBI bank with different bus width, timing setting and \n
  *             active level of CS pin to access EBI device.
  * @note       Write Buffer Enable(WBUFEN) and Extend Time Of ALE(TALE) are only available in EBI bank0 control register.
  */
void EBI_Open(uint32_t u32Bank, uint32_t u32DataWidth, uint32_t u32TimingClass, uint32_t u32BusMode, uint32_t u32CSActiveLevel)
{
    uint32_t u32Index0 = (uint32_t)&EBI->CTL0 + (uint32_t)u32Bank * 0x10U;
    uint32_t u32Index1 = (uint32_t)&EBI->TCTL0 + (uint32_t)u32Bank * 0x10U;
    volatile uint32_t *pu32EBICTL  = (uint32_t *)(u32Index0);
    volatile uint32_t *pu32EBITCTL = (uint32_t *)(u32Index1);

    if (u32DataWidth == EBI_BUSWIDTH_8BIT)
    {
        *pu32EBICTL &= ~EBI_CTL_DW16_Msk;
    }
    else
    {
        *pu32EBICTL |= EBI_CTL_DW16_Msk;
    }

    *pu32EBICTL |= u32BusMode;

    switch (u32TimingClass)
    {
    case EBI_TIMING_FASTEST:
        *pu32EBICTL = (*pu32EBICTL & ~(EBI_CTL_MCLKDIV_Msk)) |
                      (EBI_MCLKDIV_1 << EBI_CTL_MCLKDIV_Pos) |
                      (u32CSActiveLevel << EBI_CTL_CSPOLINV_Pos) | EBI_CTL_EN_Msk;
        *pu32EBITCTL = 0x0U;
        break;

    case EBI_TIMING_VERYFAST:
        *pu32EBICTL = (*pu32EBICTL & ~(EBI_CTL_MCLKDIV_Msk)) |
                      (EBI_MCLKDIV_1 << EBI_CTL_MCLKDIV_Pos) |
                      (u32CSActiveLevel << EBI_CTL_CSPOLINV_Pos) | EBI_CTL_EN_Msk;
        *pu32EBITCTL = 0x03003318U;
        break;

    case EBI_TIMING_FAST:
        *pu32EBICTL = (*pu32EBICTL & ~(EBI_CTL_MCLKDIV_Msk)) |
                      (EBI_MCLKDIV_2 << EBI_CTL_MCLKDIV_Pos) |
                      (u32CSActiveLevel << EBI_CTL_CSPOLINV_Pos) | EBI_CTL_EN_Msk;
        *pu32EBITCTL = 0x0U;
        break;

    case EBI_TIMING_NORMAL:
        *pu32EBICTL = (*pu32EBICTL & ~(EBI_CTL_MCLKDIV_Msk)) |
                      (EBI_MCLKDIV_2 << EBI_CTL_MCLKDIV_Pos) |
                      (u32CSActiveLevel << EBI_CTL_CSPOLINV_Pos) | EBI_CTL_EN_Msk;
        *pu32EBITCTL = 0x03003318U;
        break;

    case EBI_TIMING_SLOW:
        *pu32EBICTL = (*pu32EBICTL & ~(EBI_CTL_MCLKDIV_Msk)) |
                      (EBI_MCLKDIV_2 << EBI_CTL_MCLKDIV_Pos) |
                      (u32CSActiveLevel << EBI_CTL_CSPOLINV_Pos) | EBI_CTL_EN_Msk;
        *pu32EBITCTL = 0x07007738U;
        break;

    case EBI_TIMING_VERYSLOW:
        *pu32EBICTL = (*pu32EBICTL & ~(EBI_CTL_MCLKDIV_Msk)) |
                      (EBI_MCLKDIV_4 << EBI_CTL_MCLKDIV_Pos) |
                      (u32CSActiveLevel << EBI_CTL_CSPOLINV_Pos) | EBI_CTL_EN_Msk ;
        *pu32EBITCTL = 0x07007738U;
        break;

    case EBI_TIMING_SLOWEST:
        *pu32EBICTL = (*pu32EBICTL & ~(EBI_CTL_MCLKDIV_Msk)) |
                      (EBI_MCLKDIV_8 << EBI_CTL_MCLKDIV_Pos) |
                      (u32CSActiveLevel << EBI_CTL_CSPOLINV_Pos) | EBI_CTL_EN_Msk;
        *pu32EBITCTL = 0x07007738U;
        break;

    default:
        *pu32EBICTL &= ~EBI_CTL_EN_Msk;
        break;
    }
}

/**
  * @brief      Disable EBI on specify Bank
  *
  * @param[in]  u32Bank     Bank number for EBI. Valid values are:
  *                             - \ref EBI_BANK0
  *                             - \ref EBI_BANK1
  *                             - \ref EBI_BANK2
  *
  * @return     None
  *
  * @details    This function is used to close specify EBI function.
  */
void EBI_Close(uint32_t u32Bank)
{
    uint32_t u32Index = (uint32_t)&EBI->CTL0 + u32Bank * 0x10U;
    volatile uint32_t *pu32EBICTL = (uint32_t *)(u32Index);

    *pu32EBICTL &= ~EBI_CTL_EN_Msk;
}

/**
  * @brief      Set EBI Bus Timing for specify Bank
  *
  * @param[in]  u32Bank             Bank number for EBI. Valid values are:
  *                                     - \ref EBI_BANK0
  *                                     - \ref EBI_BANK1
  *                                     - \ref EBI_BANK2
  * @param[in]  u32TimingConfig     Configure EBI timing settings, includes TACC, TAHD, W2X and R2R setting.
  * @param[in]  u32MclkDiv          Divider for MCLK. Valid values are:
  *                                     - \ref EBI_MCLKDIV_1
  *                                     - \ref EBI_MCLKDIV_2
  *                                     - \ref EBI_MCLKDIV_4
  *                                     - \ref EBI_MCLKDIV_8
  *                                     - \ref EBI_MCLKDIV_16
  *                                     - \ref EBI_MCLKDIV_32
  *                                     - \ref EBI_MCLKDIV_64
  *                                     - \ref EBI_MCLKDIV_128
  *
  * @return     None
  *
  * @details    This function is used to configure specify EBI bus timing for access EBI device.
  */
void EBI_SetBusTiming(uint32_t u32Bank, uint32_t u32TimingConfig, uint32_t u32MclkDiv)
{
    uint32_t u32Index0 = (uint32_t)&EBI->CTL0 + (uint32_t)u32Bank * 0x10U;
    uint32_t u32Index1 = (uint32_t)&EBI->TCTL0 + (uint32_t)u32Bank * 0x10U;
    volatile uint32_t *pu32EBICTL  = (uint32_t *)(u32Index0);
    volatile uint32_t *pu32EBITCTL = (uint32_t *)(u32Index1);

    *pu32EBICTL = (*pu32EBICTL & ~EBI_CTL_MCLKDIV_Msk) | (u32MclkDiv << EBI_CTL_MCLKDIV_Pos);
    *pu32EBITCTL = u32TimingConfig;
}

/*@}*/ /* end of group EBI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group EBI_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2019 Nuvoton Technology Corp. ***/
