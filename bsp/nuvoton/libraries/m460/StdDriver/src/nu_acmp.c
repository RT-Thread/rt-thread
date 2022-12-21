/**************************************************************************//**
 * @file     acmp.c
 * @version  V1.00
 * @brief    M480 series Analog Comparator(ACMP) driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NuMicro.h"


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup ACMP_Driver ACMP Driver
  @{
*/


/** @addtogroup ACMP_EXPORTED_FUNCTIONS ACMP Exported Functions
  @{
*/


/**
  * @brief  Configure the specified ACMP module
  *
  * @param[in]  acmp The pointer of the specified ACMP module
  * @param[in]  u32ChNum Comparator number.
  * @param[in]  u32NegSrc Comparator negative input selection.  Including:
  *                  - \ref ACMP_CTL_NEGSEL_PIN
  *                  - \ref ACMP_CTL_NEGSEL_CRV
  *                  - \ref ACMP_CTL_NEGSEL_VBG
  *                  - \ref ACMP_CTL_NEGSEL_DAC
  * @param[in]  u32HysSel The hysteresis function option. Including:
  *                  - \ref ACMP_CTL_HYSTERESIS_30MV
  *                  - \ref ACMP_CTL_HYSTERESIS_20MV
  *                  - \ref ACMP_CTL_HYSTERESIS_10MV
  *                  - \ref ACMP_CTL_HYSTERESIS_DISABLE
  *
  * @return     None
  *
  * @details    Configure hysteresis function, select the source of negative input and enable analog comparator.
  */
void ACMP_Open(ACMP_T *acmp, uint32_t u32ChNum, uint32_t u32NegSrc, uint32_t u32HysSel)
{
    volatile int32_t delay;

    acmp->CTL[u32ChNum] = (acmp->CTL[u32ChNum] & (~(ACMP_CTL_NEGSEL_Msk | ACMP_CTL_HYSSEL_Msk | ACMP_CTL_MODESEL_Msk))) | (2 << ACMP_CTL_MODESEL_Pos) | (u32NegSrc | u32HysSel | ACMP_CTL_ACMPEN_Msk);

    /*
        ACMP stable time is 1us for MODESEL = 2'b10 or 2'b11.
        ACMP stable time is 20us for MODESEL = 2'b00 or 2'b01.

        By default, it is set MODESEL = 2'b10 here
    */
    for (delay = 25; delay > 0; delay--) {} // Delay about 1.2us @ CPU = 192MHz
}

/**
  * @brief  Close analog comparator
  *
  * @param[in]  acmp The pointer of the specified ACMP module
  * @param[in]  u32ChNum Comparator number.
  *
  * @return     None
  *
  * @details  This function will clear ACMPEN bit of ACMP_CTL register to disable analog comparator.
  */
void ACMP_Close(ACMP_T *acmp, uint32_t u32ChNum)
{
    acmp->CTL[u32ChNum] &= (~ACMP_CTL_ACMPEN_Msk);
}



/*@}*/ /* end of group ACMP_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group ACMP_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/

