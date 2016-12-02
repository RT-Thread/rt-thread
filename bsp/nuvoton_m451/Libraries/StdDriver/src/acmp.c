/**************************************************************************//**
 * @file     acmp.c
 * @version  V3.00
 * $Revision: 4 $
 * $Date: 15/08/11 10:26a $
 * @brief    M451 series Analog Comparator(ACMP) driver source file
 *
 * @note
 * Copyright (C) 2014~2015 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include "M451Series.h"

#ifdef __cplusplus
extern "C"
{
#endif

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
  * @param[in]  Acmp The pointer of the specified ACMP module
  * @param[in]  u32ChNum Comparator number.
  * @param[in]  u32NegSrc Comparator negative input selection.  Including:
  *                  - \ref ACMP_CTL_NEGSEL_PIN
  *                  - \ref ACMP_CTL_NEGSEL_CRV
  *                  - \ref ACMP_CTL_NEGSEL_VBG
  *                  - \ref ACMP_CTL_NEGSEL_DAC
  * @param[in]  u32HysteresisEn The hysteresis function option. Including:
  *                  - \ref ACMP_CTL_HYSTERESIS_ENABLE
  *                  - \ref ACMP_CTL_HYSTERESIS_DISABLE
  *
  * @return     None
  *
  * @details    Configure hysteresis function, select the source of negative input and enable analog comparator.
  */
void ACMP_Open(ACMP_T *Acmp, uint32_t u32ChNum, uint32_t u32NegSrc, uint32_t u32HysteresisEn)
{
    Acmp->CTL[u32ChNum] = (Acmp->CTL[u32ChNum] & (~(ACMP_CTL_NEGSEL_Msk | ACMP_CTL_HYSEN_Msk))) | (u32NegSrc | u32HysteresisEn | ACMP_CTL_ACMPEN_Msk);
}

/**
  * @brief  Close analog comparator
  *
  * @param[in]  Acmp The pointer of the specified ACMP module
  * @param[in]  u32ChNum Comparator number.
  *
  * @return     None
  *
  * @details  This function will clear ACMPEN bit of ACMP_CTL register to disable analog comparator.
  */
void ACMP_Close(ACMP_T *Acmp, uint32_t u32ChNum)
{
    Acmp->CTL[u32ChNum] &= (~ACMP_CTL_ACMPEN_Msk);
}



/*@}*/ /* end of group ACMP_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group ACMP_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

/*** (C) COPYRIGHT 2014~2015 Nuvoton Technology Corp. ***/

