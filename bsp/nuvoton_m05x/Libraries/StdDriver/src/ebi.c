/**************************************************************************//**
 * @file     ebi.c
 * @version  V3.00
 * $Revision: 3 $
 * $Date: 14/01/28 10:49a $
 * @brief    M051 series EBI driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "M051Series.h"


/** @addtogroup M051_Device_Driver M051 Device Driver
  @{
*/

/** @addtogroup M051_EBI_Driver EBI Driver
  @{
*/


/** @addtogroup M051_EBI_EXPORTED_FUNCTIONS EBI Exported Functions
  @{
*/

/**
  * @brief      Initialize EBI function
  *
  * @param[in]  u32Bank             Bank number for EBI. This parameter is current not used.
  * @param[in]  u32DataWidth        Data bus width. Valid values are:
  *                                 - \ref EBI_BUSWIDTH_8BIT
  *                                 - \ref EBI_BUSWIDTH_16BIT
  * @param[in]  u32TimingClass      Default timing configuration. Valid values are:
  *                                 - \ref EBI_TIMING_FASTEST
  *                                 - \ref EBI_TIMING_VERYFAST
  *                                 - \ref EBI_TIMING_FAST
  *                                 - \ref EBI_TIMING_NORMAL
  *                                 - \ref EBI_TIMING_SLOW
  *                                 - \ref EBI_TIMING_VERYSLOW
  *                                 - \ref EBI_TIMING_SLOWEST
  * @param[in]  u32BusMode          Enable EBI separate mode. This parameter is current not used.
  * @param[in]  u32CSActiveLevel    CS is active High/Low. This parameter is current not used.
  *
  * @return none
  *
  * @details    This function make EBI module be ready for read and write operation.
  * @note       Only u32DataWidth and u32TimingClass is valid in M051 series.
  */
void EBI_Open(uint32_t u32Bank, uint32_t u32DataWidth, uint32_t u32TimingClass, uint32_t u32BusMode, uint32_t u32CSActiveLevel)
{
    if(u32DataWidth == EBI_BUSWIDTH_8BIT)
        EBI->EBICON &= ~EBI_EBICON_ExtBW16_Msk;
    else
        EBI->EBICON |= EBI_EBICON_ExtBW16_Msk;

    switch(u32TimingClass)
    {
    case EBI_TIMING_FASTEST:
        EBI->EBICON = (EBI->EBICON & ~(EBI_EBICON_MCLKDIV_Msk | EBI_EBICON_ExttALE_Msk)) |
                      (EBI_MCLKDIV_1 << EBI_EBICON_MCLKDIV_Pos) | EBI_EBICON_ExtEN_Msk;
        EBI->EXTIME = 0x0;
        break;

    case EBI_TIMING_VERYFAST:
        EBI->EBICON = (EBI->EBICON & ~(EBI_EBICON_MCLKDIV_Msk | EBI_EBICON_ExttALE_Msk)) |
                      (EBI_MCLKDIV_1 << EBI_EBICON_MCLKDIV_Pos) | EBI_EBICON_ExtEN_Msk   |
                      (0x3 << EBI_EBICON_ExttALE_Pos) ;
        EBI->EXTIME = 0x03003318;
        break;

    case EBI_TIMING_FAST:
        EBI->EBICON = (EBI->EBICON & ~(EBI_EBICON_MCLKDIV_Msk | EBI_EBICON_ExttALE_Msk)) |
                      (EBI_MCLKDIV_2 << EBI_EBICON_MCLKDIV_Pos) | EBI_EBICON_ExtEN_Msk;
        EBI->EXTIME = 0x0;
        break;

    case EBI_TIMING_NORMAL:
        EBI->EBICON = (EBI->EBICON & ~(EBI_EBICON_MCLKDIV_Msk | EBI_EBICON_ExttALE_Msk)) |
                      (EBI_MCLKDIV_2 << EBI_EBICON_MCLKDIV_Pos) | EBI_EBICON_ExtEN_Msk   |
                      (0x3 << EBI_EBICON_ExttALE_Pos) ;
        EBI->EXTIME = 0x03003318;
        break;

    case EBI_TIMING_SLOW:
        EBI->EBICON = (EBI->EBICON & ~(EBI_EBICON_MCLKDIV_Msk | EBI_EBICON_ExttALE_Msk)) |
                      (EBI_MCLKDIV_2 << EBI_EBICON_MCLKDIV_Pos) | EBI_EBICON_ExtEN_Msk   |
                      (0x7 << EBI_EBICON_ExttALE_Pos) ;
        EBI->EXTIME = 0x07007738;
        break;

    case EBI_TIMING_VERYSLOW:
        EBI->EBICON = (EBI->EBICON & ~(EBI_EBICON_MCLKDIV_Msk | EBI_EBICON_ExttALE_Msk)) |
                      (EBI_MCLKDIV_4 << EBI_EBICON_MCLKDIV_Pos) | EBI_EBICON_ExtEN_Msk   |
                      (0x7 << EBI_EBICON_ExttALE_Pos) ;
        EBI->EXTIME = 0x07007738;
        break;

    case EBI_TIMING_SLOWEST:
        EBI->EBICON = (EBI->EBICON & ~(EBI_EBICON_MCLKDIV_Msk | EBI_EBICON_ExttALE_Msk)) |
                      (EBI_MCLKDIV_8 << EBI_EBICON_MCLKDIV_Pos) | EBI_EBICON_ExtEN_Msk   |
                      (0x7 << EBI_EBICON_ExttALE_Pos) ;
        EBI->EXTIME = 0x07007738;
        break;

    default:
        EBI->EBICON &= ~EBI_EBICON_ExtEN_Msk;
        break;
    }
}

/**
  * @brief      Disable EBI function
  *
  * @param[in]  u32Bank     Bank number for EBI. This parameter is current not used.
  *
  * @return     none
  *
  * @details    This function close EBI module.
  */
void EBI_Close(uint32_t u32Bank)
{
    EBI->EBICON &= ~EBI_EBICON_ExtEN_Msk;
}

/**
  * @brief      Set EBI bus timings
  *
  * @param[in]  u32Bank         Bank number for EBI. This parameter is current not used.
  *
  * @param[in]  u32TimingConfig Configure EBI timing settings, ExttACC, ExttAHD, ExtIW2X and ExtIR2R.
  * @param[in]  u32MclkDiv      Divider for MCLK. Valid values are:
  *                             - \ref EBI_MCLKDIV_1
  *                             - \ref EBI_MCLKDIV_2
  *                             - \ref EBI_MCLKDIV_4
  *                             - \ref EBI_MCLKDIV_8
  *                             - \ref EBI_MCLKDIV_16
  *                             - \ref EBI_MCLKDIV_32
  *
  * @return none
  *
  * @details    This function make EBI module be ready for read and write operation.
  */
void EBI_SetBusTiming(uint32_t u32Bank, uint32_t u32TimingConfig, uint32_t u32MclkDiv)
{
    EBI->EBICON = (EBI->EBICON & ~EBI_EBICON_MCLKDIV_Msk) | (u32MclkDiv << EBI_EBICON_MCLKDIV_Pos);
    EBI->EXTIME = u32TimingConfig;
}

/*@}*/ /* end of group M051_EBI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group M051_EBI_Driver */

/*@}*/ /* end of group M051_Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
