/**************************************************************************//**
 * @file     ecap.c
 * @version  V3.00
 * @brief    Enhanced Input Capture Timer (ECAP) driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NuMicro.h"


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup ECAP_Driver ECAP Driver
  @{
*/

/** @addtogroup ECAP_EXPORTED_FUNCTIONS ECAP Exported Functions
  @{
*/

/**
  * @brief      Enable ECAP function
  * @param[in]  ecap        The pointer of the specified ECAP module.
  * @param[in]  u32FuncMask Input capture function select
  *                         - \ref ECAP_DISABLE_COMPARE
  *                         - \ref ECAP_COMPARE_FUNCTION
  * @return     None
  * @details    This macro enable input capture function and select compare and reload function.
  */
void ECAP_Open(ECAP_T *ecap, uint32_t u32FuncMask)
{
    /* Clear Input capture mode*/
    ecap->CTL0 = ecap->CTL0 & ~(ECAP_CTL0_CMPEN_Msk);

    /* Enable Input Capture and set mode */
    ecap->CTL0 |= ECAP_CTL0_CAPEN_Msk | (u32FuncMask);
}



/**
  * @brief      Disable ECAP function
  * @param[in]  ecap        The pointer of the specified ECAP module.
  * @return     None
  * @details    This macro disable input capture function.
  */
void ECAP_Close(ECAP_T *ecap)
{
    /* Disable Input Capture*/
    ecap->CTL0 &= ~ECAP_CTL0_CAPEN_Msk;
}

/**
  * @brief This macro is used to enable input channel interrupt
  * @param[in] ecap      Specify ECAP port
  * @param[in] u32Mask  The input channel Mask
  *                  - \ref ECAP_CTL0_CAPIEN0_Msk
  *                  - \ref ECAP_CTL0_CAPIEN1_Msk
  *                  - \ref ECAP_CTL0_CAPIEN2_Msk
  *                  - \ref ECAP_CTL0_OVIEN_Msk
  *                  - \ref ECAP_CTL0_CMPIEN_Msk
  * @return None
  * @details This macro will enable the input channel_n interrupt.
  */
void ECAP_EnableINT(ECAP_T *ecap, uint32_t u32Mask)
{
    /* Enable input channel interrupt */
    ecap->CTL0 |= (u32Mask);

    /* Enable NVIC ECAP IRQ */
    if (ecap == (ECAP_T *)ECAP0)
    {
        NVIC_EnableIRQ((IRQn_Type)ECAP0_IRQn);
    }
    else if (ecap == (ECAP_T *)ECAP1)
    {
        NVIC_EnableIRQ((IRQn_Type)ECAP1_IRQn);
    }
    else if (ecap == (ECAP_T *)ECAP2)
    {
        NVIC_EnableIRQ((IRQn_Type)ECAP2_IRQn);
    }
    else
    {
        NVIC_EnableIRQ((IRQn_Type)ECAP3_IRQn);
    }
}

/**
  * @brief This macro is used to disable input channel interrupt
  * @param[in] ecap      Specify ECAP port
  * @param[in] u32Mask  The input channel number
  *                  - \ref ECAP_CTL0_CAPIEN0_Msk
  *                  - \ref ECAP_CTL0_CAPIEN1_Msk
  *                  - \ref ECAP_CTL0_CAPIEN2_Msk
  *                  - \ref ECAP_CTL0_OVIEN_Msk
  *                  - \ref ECAP_CTL0_CMPIEN_Msk
  * @return None
  * @details This macro will disable the input channel_n interrupt.
  */
void ECAP_DisableINT(ECAP_T *ecap, uint32_t u32Mask)
{
    /* Disable input channel interrupt */
    ecap->CTL0 &= ~(u32Mask);

    /* Disable NVIC ECAP IRQ */
    if (ecap == (ECAP_T *)ECAP0)
    {
        NVIC_DisableIRQ((IRQn_Type)ECAP0_IRQn);
    }
    if (ecap == (ECAP_T *)ECAP1)
    {
        NVIC_DisableIRQ((IRQn_Type)ECAP1_IRQn);
    }
    if (ecap == (ECAP_T *)ECAP2)
    {
        NVIC_DisableIRQ((IRQn_Type)ECAP2_IRQn);
    }
    else
    {
        NVIC_DisableIRQ((IRQn_Type)ECAP3_IRQn);
    }
}

/*@}*/ /* end of group ECAP_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group ECAP_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2021 Nuvoton Technology Corp. ***/
