/***************************************************************************//**
* \file cy_crypto_core_mem_v1.c
* \version 2.70
*
* \brief
*  This file provides the source code to the API for the PRNG
*  in the Crypto block driver.
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "cy_device.h"

#if defined(CY_IP_MXCRYPTO)

#include "cy_crypto_core_mem_v1.h"

#if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_STR == 1)

#include "cy_crypto_core_hw_v1.h"
#include "cy_syslib.h"


/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_MemCpy
****************************************************************************//**
*
* Function MemCpy uses Crypto HW.
* Memory structures should not overlap!
* There is no alignment restriction.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param src
* The pointer to the source of MemCpy.
*
* \param dst
* The pointer to the destination of MemCpy.
*
* \param size
* The size in bytes of the copy operation.
*
*******************************************************************************/
void Cy_Crypto_Core_V1_MemCpy(CRYPTO_Type *base, void* dst, void const *src, uint16_t size)
{
    if (size != 0U)
    {
        /* Prepare data in the register file for next instruction */
        Cy_Crypto_SetReg3Instr(base,
                               (uint32_t)src,
                               (uint32_t)dst,
                               (uint32_t)size);

        /* Issue the STR_MEMCPY instruction */
        Cy_Crypto_Run3ParamInstr(base,
                                 CY_CRYPTO_V1_STR_MEMCPY_OPC,
                                 CY_CRYPTO_RSRC0_SHIFT,
                                 CY_CRYPTO_RSRC4_SHIFT,
                                 CY_CRYPTO_RSRC8_SHIFT);

        /* Wait until the STR instruction is complete */
        while (0uL != _FLD2VAL(CRYPTO_STATUS_STR_BUSY, REG_CRYPTO_STATUS(base)))
        {
        }
    }
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_MemSet
****************************************************************************//**
*
* Function MemSet uses Crypto HW.
* There is no alignment restriction.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param dst
* The pointer to the destination of MemSet.

* \param data
* The value to be set.

* \param size
* The size in bytes of the set operation.
*
*******************************************************************************/
void Cy_Crypto_Core_V1_MemSet(CRYPTO_Type *base, void* dst, uint8_t data, uint16_t size)
{
    if (size != 0U)
    {
        Cy_Crypto_SetReg3Instr(base,
                               (uint32_t)dst,
                               (uint32_t)size,
                               (uint32_t)data);

        /* Issue the STR_MEMSET instruction */
        Cy_Crypto_Run3ParamInstr(base,
                                 CY_CRYPTO_V1_STR_MEMSET_OPC,
                                 CY_CRYPTO_RSRC0_SHIFT,
                                 CY_CRYPTO_RSRC8_SHIFT,
                                 CY_CRYPTO_RSRC12_SHIFT);

        /* Wait until the STR instruction is complete */
        while (0uL != _FLD2VAL(CRYPTO_STATUS_STR_BUSY, REG_CRYPTO_STATUS(base)))
        {
        }
    }
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_MemCmp
****************************************************************************//**
*
* Function MemCmp uses Crypto HW.
* There is no alignment restriction.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param src0
* The pointer to the first source of MemCmp.

* \param src1
* The pointer to the second source of MemCmp.

* \param size
* the size in bytes of the compare operation.
*
* \return
* 0 - if Source 1 = Source 2, 1 - if not.
*
*******************************************************************************/
uint32_t Cy_Crypto_Core_V1_MemCmp(CRYPTO_Type *base, void const *src0, void const *src1, uint16_t size)
{
    uint32_t memResult = 1U;

    if (size != 0U)
    {
        Cy_Crypto_SetReg3Instr(base,
                               (uint32_t)src0,
                               (uint32_t)src1,
                               (uint32_t)size);

        /* Issue the STR_MEMCMP instruction */
        Cy_Crypto_Run3ParamInstr(base,
                                 CY_CRYPTO_V1_STR_MEMCMP_OPC,
                                 CY_CRYPTO_RSRC0_SHIFT,
                                 CY_CRYPTO_RSRC4_SHIFT,
                                 CY_CRYPTO_RSRC8_SHIFT);

        /* Wait until the STR instruction is complete */
        while (0uL != _FLD2VAL(CRYPTO_STATUS_STR_BUSY, REG_CRYPTO_STATUS(base)))
        {
        }

        CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 11.3','This piece of code is written for CRYPTO_V1_Type and will not execute for CRYPTO_V2_Type');
        memResult = (uint32_t)(REG_CRYPTO_STR_RESULT(base));
    }

    return memResult;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_MemXor
****************************************************************************//**
*
* Function MemXor uses Crypto HW.
* Memory structures should not overlap!
* There is no alignment restriction.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param dst
* The pointer to the destination of MemXor.
*
* \param src0
* The pointer to the first source of MemXor.

* \param src1
* The pointer to the second source of MemXor.
*
* \param size
* The size in bytes of the compare operation.
*
*******************************************************************************/
void Cy_Crypto_Core_V1_MemXor(CRYPTO_Type *base,
                              void* dst, void const *src0, void const *src1, uint16_t size)
{
    if (size != 0U)
    {
        Cy_Crypto_SetReg4Instr(base,
                               (uint32_t)src0,
                               (uint32_t)src1,
                               (uint32_t)size,
                               (uint32_t)dst);

        /* Issue the STR_MEMXOR instruction */
        Cy_Crypto_Run4ParamInstr(base,
                                 CY_CRYPTO_V1_STR_MEMXOR_OPC,
                                 CY_CRYPTO_RSRC0_SHIFT,
                                 CY_CRYPTO_RSRC4_SHIFT,
                                 CY_CRYPTO_RSRC8_SHIFT,
                                 CY_CRYPTO_RSRC12_SHIFT);

        /* Wait until the STR instruction is complete */
        while (0uL != _FLD2VAL(CRYPTO_STATUS_STR_BUSY, REG_CRYPTO_STATUS(base)))
        {
        }
    }
}

#endif /* #if (CPUSS_CRYPTO_STR == 1) */

#if defined(__cplusplus)
}
#endif

#endif /*  defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */

#endif /* defined(CY_IP_MXCRYPTO) */


/* [] END OF FILE */
