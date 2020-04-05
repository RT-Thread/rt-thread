/**************************************************************************//**
 * @file     acmp.c
 * @version  V3.00
 * $Revision: 2 $
 * $Date: 15/05/04 3:27p $
 * @brief    Analog Comparator(ACMP) driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include "NUC100Series.h"

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
  * @param[in]  Acmp The pointer of the specified ACMP module.
  * @param[in]  u32ChNum Comparator number.
  * @param[in]  u32NegSrc Comparator negative input selection.  Including:
  *                  - \ref ACMP_CR_VNEG_PIN
  *                  - \ref ACMP_CR_VNEG_BANDGAP
  * @param[in]  u32HysteresisEn The hysteresis function option. Including:
  *                  - \ref ACMP_CR_HYSTERESIS_ENABLE
  *                  - \ref ACMP_CR_HYSTERESIS_DISABLE
  *
  * @return     None
  *
  * @details    Configure hysteresis function, select the source of negative input and enable analog comparator.
  */
void ACMP_Open(ACMP_T *Acmp, uint32_t u32ChNum, uint32_t u32NegSrc, uint32_t u32HysteresisEn)
{
    Acmp->CMPCR[u32ChNum] = (Acmp->CMPCR[u32ChNum] & (~(ACMP_CMPCR_CMPCN_Msk | ACMP_CMPCR_CMP_HYSEN_Msk))) | (u32NegSrc | u32HysteresisEn | ACMP_CMPCR_CMPEN_Msk);
}

/**
  * @brief  Close analog comparator
  *
  * @param[in]  Acmp The pointer of the specified ACMP module.
  * @param[in]  u32ChNum Comparator number.
  *
  * @return     None
  *
  * @details  This function will clear CMPEN bit of CMPCR register to disable analog comparator.
  */
void ACMP_Close(ACMP_T *Acmp, uint32_t u32ChNum)
{
    Acmp->CMPCR[u32ChNum] &= (~ACMP_CMPCR_CMPEN_Msk);
}



/*@}*/ /* end of group ACMP_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group ACMP_Driver */

/*@}*/ /* end of group Device_Driver */

#ifdef __cplusplus
}
#endif

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/

