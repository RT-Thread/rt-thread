/**************************************************************************//**
 * @file     acmp.c
 * @version  V3.00
 * $Revision: 4 $
 * $Date: 14/01/28 10:49a $
 * @brief    M051 series Analog Comparator(ACMP) driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include "M051Series.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup M051_Device_Driver M051 Device Driver
  @{
*/

/** @addtogroup M051_ACMP_Driver ACMP Driver
  @{
*/


/** @addtogroup M051_ACMP_EXPORTED_FUNCTIONS ACMP Exported Functions
  @{
*/


/**
  * @brief  Configure the specified ACMP module
  *
  * @param[in]  Acmp The base address of ACMP module
  * @param[in]  u32ChNum comparator number.
  * @param[in]  u32NegSrc is comparator negative input selection.  Including:
  *                  - \ref ACMP_CR_VNEG_PIN
  *                  - \ref ACMP_CR_VNEG_BANDGAP
  *
  * @param[in]  u32HysteresisEn is the hysteresis function option. Including:
  *                  - \ref ACMP_CR_HYSTERESIS_ENABLE
  *                  - \ref ACMP_CR_HYSTERESIS_DISABLE
  * @return None
  */
void ACMP_Open(ACMP_T *Acmp, uint32_t u32ChNum, uint32_t u32NegSrc, uint32_t u32HysteresisEn)
{
    Acmp->CR[u32ChNum % 2] = (Acmp->CR[u32ChNum % 2] & (~(ACMP_CR_NEGSEL_Msk | ACMP_CR_HYSEN_Msk))) | (u32NegSrc | u32HysteresisEn | ACMP_CR_ACMPEN_Msk);
}

/**
  * @brief  This function close comparator
  *
  * @param[in]  Acmp The base address of ACMP module
  * @param[in]  u32ChNum comparator number.
  *
  * @return None
  */
void ACMP_Close(ACMP_T *Acmp, uint32_t u32ChNum)
{
    Acmp->CR[u32ChNum % 2] &= (~ACMP_CR_ACMPEN_Msk);
}



/*@}*/ /* end of group M051_ACMP_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group M051_ACMP_Driver */

/*@}*/ /* end of group M051_Device_Driver */

#ifdef __cplusplus
}
#endif

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/

