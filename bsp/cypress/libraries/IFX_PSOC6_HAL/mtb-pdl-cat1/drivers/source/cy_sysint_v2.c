/***************************************************************************//**
* \file  cy_sysint.c
* \version 1.70
*
* \brief
* Provides an API implementation of the SysInt driver.
*
********************************************************************************
* \copyright
* Copyright (c) (2016-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "cy_device.h"

#if defined (CY_IP_M33SYSCPUSS) || defined(CY_IP_M55APPCPUSS)

#include "cy_sysint.h"

#ifndef CY_SECURE_WORLD
static uint32_t *__ns_vector_table_rw_ptr = (uint32_t*)&__ns_vector_table_rw;
#endif

void Cy_SysInt_SetNmiSource(cy_en_sysint_nmi_t nmiNum, IRQn_Type intrSrc)

{
    CY_ASSERT_L3(CY_SYSINT_IS_NMI_NUM_VALID(nmiNum));
#if (CY_CPU_CORTEX_M55)
    MXCM55_CM55_NMI_CTL((uint32_t)nmiNum - 1UL) = (uint32_t)intrSrc;
#else
    MXCM33_CM33_NMI_CTL((uint32_t)nmiNum - 1UL) = (uint32_t)intrSrc;
#endif
}


IRQn_Type Cy_SysInt_GetNmiSource(cy_en_sysint_nmi_t nmiNum)

{
    CY_ASSERT_L3(CY_SYSINT_IS_NMI_NUM_VALID(nmiNum));
#if (CY_CPU_CORTEX_M55)
    return ((IRQn_Type)(MXCM55_CM55_NMI_CTL((uint32_t)nmiNum - 1UL)));
#else
    return ((IRQn_Type)(MXCM33_CM33_NMI_CTL((uint32_t)nmiNum - 1UL)));
#endif
}


cy_en_sysint_status_t Cy_SysInt_Init(const cy_stc_sysint_t* config, cy_israddress userIsr)
{
    cy_en_sysint_status_t status = CY_SYSINT_SUCCESS;

    if(NULL != config)
    {
        CY_ASSERT_L3(CY_SYSINT_IS_PRIORITY_VALID(config->intrPriority));

        NVIC_SetPriority(config->intrSrc, config->intrPriority);
#ifdef CY_SECURE_WORLD
        if (SCB->VTOR == (uint32_t)__s_vector_table)
#else
        if (SCB->VTOR == (uint32_t)__ns_vector_table_rw_ptr)
#endif
        {
            (void)Cy_SysInt_SetVector(config->intrSrc, userIsr);
        }
    }
    else
    {
        status = CY_SYSINT_BAD_PARAM;
    }

    return(status);
}


cy_israddress Cy_SysInt_SetVector(IRQn_Type IRQn, cy_israddress userIsr)
{
    cy_israddress prevIsr;
#ifdef CY_SECURE_WORLD
    uint32_t *ptr;
    if (SCB->VTOR == (uint32_t)__s_vector_table)
    {
        CY_ASSERT_L1(CY_SYSINT_IS_VECTOR_VALID(userIsr));
        prevIsr = (cy_israddress)__s_vector_table[CY_INT_IRQ_BASE + IRQn];
        ptr = (uint32_t*)&__s_vector_table[CY_INT_IRQ_BASE + IRQn];
        *ptr = (uint32_t) userIsr;
    }
#else
    if (SCB->VTOR == (uint32_t)__ns_vector_table_rw_ptr)
    {
        CY_ASSERT_L1(CY_SYSINT_IS_VECTOR_VALID(userIsr));
        prevIsr = (cy_israddress)__ns_vector_table_rw_ptr[CY_INT_IRQ_BASE + (uint32_t)IRQn];
        __ns_vector_table_rw_ptr[CY_INT_IRQ_BASE + (uint32_t)IRQn] = (uint32_t)userIsr;
    }
#endif
    else
    {
        /* vector table is always loaded to non secure SRAM, so there is no need to return
        the non-secure ROM vector */
        prevIsr = NULL;
    }

    return (prevIsr);
}


cy_israddress Cy_SysInt_GetVector(IRQn_Type IRQn)
{
    cy_israddress currIsr;

#ifdef CY_SECURE_WORLD
    /* Return the SRAM ISR address only if it was moved to __ramVectors */
    if (SCB->VTOR == (uint32_t)__s_vector_table)
    {
        currIsr = (cy_israddress)__s_vector_table[CY_INT_IRQ_BASE + (uint32_t)IRQn];
    }
#else
    if (SCB->VTOR == (uint32_t)__ns_vector_table_rw_ptr)
    {
        currIsr = (cy_israddress)__ns_vector_table_rw_ptr[CY_INT_IRQ_BASE + (uint32_t)IRQn];
    }
#endif
    else
    {
        /* vector table is always loaded to non-secure SRAM, so there is no need to return
        the non-secure ROM vector */
        currIsr = NULL;
    }

    return (currIsr);
}


void Cy_SysInt_SoftwareTrig(IRQn_Type IRQn)
{
    NVIC->STIR = (uint32_t)IRQn & CY_SYSINT_STIR_MASK;
}

#endif

/* [] END OF FILE */
