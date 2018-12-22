/**************************************************************************//**
 * @file     ebi.c
 * @version  V3.00
 * $Revision: 9 $
 * $Date: 15/08/11 10:26a $
 * @brief    M451 series EBI driver source file
 *
 * @note
 * Copyright (C) 2013~2015 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "M451Series.h"


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
  * @param[in]  u32BusMode          Enable EBI separate mode. This parameter is current not used.
  * @param[in]  u32CSActiveLevel    CS is active High/Low. Valid values are:
  *                                     - \ref EBI_CS_ACTIVE_HIGH
  *                                     - \ref EBI_CS_ACTIVE_LOW
  *
  * @return none
  *
  * @details    This function is used to open specify EBI bank with different bus width, timing setting and \n
  *             active level of CS pin to access EBI device.
  * @note       Write Buffer Enable(WBUFEN) and Extend Time Of ALE(TALE) are only available in EBI bank0 control register.
  */
void EBI_Open(uint32_t u32Bank, uint32_t u32DataWidth, uint32_t u32TimingClass, uint32_t u32BusMode, uint32_t u32CSActiveLevel)
{
    volatile uint32_t *pu32EBICTL  = (uint32_t *)((uint32_t)&EBI->CTL0 + (u32Bank * 0x10));
    volatile uint32_t *pu32EBITCTL = (uint32_t *)((uint32_t)&EBI->TCTL0 + (u32Bank * 0x10));

    if(u32DataWidth == EBI_BUSWIDTH_8BIT)
        *pu32EBICTL &= ~EBI_CTL0_DW16_Msk;
    else
        *pu32EBICTL |= EBI_CTL0_DW16_Msk;

    switch(u32TimingClass)
    {
        case EBI_TIMING_FASTEST:
            *pu32EBICTL = (*pu32EBICTL & ~(EBI_CTL0_MCLKDIV_Msk | EBI_CTL0_TALE_Msk)) |
                          (EBI_MCLKDIV_1 << EBI_CTL0_MCLKDIV_Pos) |
                          (u32CSActiveLevel << EBI_CTL0_CSPOLINV_Pos) | EBI_CTL0_EN_Msk;
            *pu32EBITCTL = 0x0;
            break;

        case EBI_TIMING_VERYFAST:
            *pu32EBICTL = (*pu32EBICTL & ~(EBI_CTL0_MCLKDIV_Msk | EBI_CTL0_TALE_Msk)) |
                          (EBI_MCLKDIV_1 << EBI_CTL0_MCLKDIV_Pos) |
                          (u32CSActiveLevel << EBI_CTL0_CSPOLINV_Pos) | EBI_CTL0_EN_Msk |
                          (0x3 << EBI_CTL0_TALE_Pos) ;
            *pu32EBITCTL = 0x03003318;
            break;

        case EBI_TIMING_FAST:
            *pu32EBICTL = (*pu32EBICTL & ~(EBI_CTL0_MCLKDIV_Msk | EBI_CTL0_TALE_Msk)) |
                          (EBI_MCLKDIV_2 << EBI_CTL0_MCLKDIV_Pos) |
                          (u32CSActiveLevel << EBI_CTL0_CSPOLINV_Pos) | EBI_CTL0_EN_Msk;
            *pu32EBITCTL = 0x0;
            break;

        case EBI_TIMING_NORMAL:
            *pu32EBICTL = (*pu32EBICTL & ~(EBI_CTL0_MCLKDIV_Msk | EBI_CTL0_TALE_Msk)) |
                          (EBI_MCLKDIV_2 << EBI_CTL0_MCLKDIV_Pos) |
                          (u32CSActiveLevel << EBI_CTL0_CSPOLINV_Pos) | EBI_CTL0_EN_Msk |
                          (0x3 << EBI_CTL0_TALE_Pos) ;
            *pu32EBITCTL = 0x03003318;
            break;

        case EBI_TIMING_SLOW:
            *pu32EBICTL = (*pu32EBICTL & ~(EBI_CTL0_MCLKDIV_Msk | EBI_CTL0_TALE_Msk)) |
                          (EBI_MCLKDIV_2 << EBI_CTL0_MCLKDIV_Pos) |
                          (u32CSActiveLevel << EBI_CTL0_CSPOLINV_Pos) | EBI_CTL0_EN_Msk |
                          (0x7 << EBI_CTL0_TALE_Pos) ;
            *pu32EBITCTL = 0x07007738;
            break;

        case EBI_TIMING_VERYSLOW:
            *pu32EBICTL = (*pu32EBICTL & ~(EBI_CTL0_MCLKDIV_Msk | EBI_CTL0_TALE_Msk)) |
                          (EBI_MCLKDIV_4 << EBI_CTL0_MCLKDIV_Pos) |
                          (u32CSActiveLevel << EBI_CTL0_CSPOLINV_Pos) | EBI_CTL0_EN_Msk |
                          (0x7 << EBI_CTL0_TALE_Pos) ;
            *pu32EBITCTL = 0x07007738;
            break;

        case EBI_TIMING_SLOWEST:
            *pu32EBICTL = (*pu32EBICTL & ~(EBI_CTL0_MCLKDIV_Msk | EBI_CTL0_TALE_Msk)) |
                          (EBI_MCLKDIV_8 << EBI_CTL0_MCLKDIV_Pos) |
                          (u32CSActiveLevel << EBI_CTL0_CSPOLINV_Pos) | EBI_CTL0_EN_Msk |
                          (0x7 << EBI_CTL0_TALE_Pos) ;
            *pu32EBITCTL = 0x07007738;
            break;

        default:
            *pu32EBICTL &= ~EBI_CTL0_EN_Msk;
            break;
    }
}

/**
  * @brief      Disable EBI on specify Bank
  *
  * @param[in]  u32Bank     Bank number for EBI. Valid values are:
  *                             - \ref EBI_BANK0
  *                             - \ref EBI_BANK1
  *
  * @return     none
  *
  * @details    This function is used to close specify EBI function.
  */
void EBI_Close(uint32_t u32Bank)
{
    volatile uint32_t *pu32EBICTL = (uint32_t *)((uint32_t)&EBI->CTL0 + (u32Bank * 0x10));

    *pu32EBICTL &= ~EBI_CTL0_EN_Msk;
}

/**
  * @brief      Set EBI Bus Timing for specify Bank
  *
  * @param[in]  u32Bank             Bank number for EBI. Valid values are:
  *                                     - \ref EBI_BANK0
  *                                     - \ref EBI_BANK1
  * @param[in]  u32TimingConfig     Configure EBI timing settings, includes TACC, TAHD, W2X and R2R setting.
  * @param[in]  u32MclkDiv          Divider for MCLK. Valid values are:
  *                                     - \ref EBI_MCLKDIV_1
  *                                     - \ref EBI_MCLKDIV_2
  *                                     - \ref EBI_MCLKDIV_4
  *                                     - \ref EBI_MCLKDIV_8
  *                                     - \ref EBI_MCLKDIV_16
  *                                     - \ref EBI_MCLKDIV_32
  *
  * @return none
  *
  * @details    This function is used to configure specify EBI bus timing for access EBI device.
  */
void EBI_SetBusTiming(uint32_t u32Bank, uint32_t u32TimingConfig, uint32_t u32MclkDiv)
{
    volatile uint32_t *pu32EBICTL  = (uint32_t *)((uint32_t)&EBI->CTL0 + (u32Bank * 0x10));
    volatile uint32_t *pu32EBITCTL = (uint32_t *)((uint32_t)&EBI->TCTL0 + (u32Bank * 0x10));

    *pu32EBICTL = (*pu32EBICTL & ~EBI_CTL0_MCLKDIV_Msk) | (u32MclkDiv << EBI_CTL0_MCLKDIV_Pos);
    *pu32EBITCTL = u32TimingConfig;
}

/*@}*/ /* end of group EBI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group EBI_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2013~2015 Nuvoton Technology Corp. ***/
