/***************************************************************************//**
* \file cy_crypto_core_mem.h
* \version 2.70
*
* \brief
*  This file provides the headers for the memory management API
*  in the Crypto driver.
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


#if !defined (CY_CRYPTO_CORE_MEM_H)
#define CY_CRYPTO_CORE_MEM_H

#include "cy_device.h"

#if defined (CY_IP_MXCRYPTO)

#include "cy_crypto_common.h"

#if defined(__cplusplus)
extern "C" {
#endif

#include "cy_crypto_core_mem_v1.h"
#include "cy_crypto_core_mem_v2.h"
#include "cy_crypto_core_hw.h"

typedef void (*cy_crypto_memcpy_func_t)(CRYPTO_Type *base,
                               void* dst, void const *src, uint16_t size);
typedef void (*cy_crypto_memset_func_t)(CRYPTO_Type *base,
                               void* dst, uint8_t data, uint16_t size);
typedef uint32_t (*cy_crypto_memcmp_func_t)(CRYPTO_Type *base,
                               void const *src0, void const *src1, uint16_t size);
typedef void (*cy_crypto_memxor_func_t)(CRYPTO_Type *base, void* dst,
                               void const *src0, void const *src1, uint16_t size);

/**
* \addtogroup group_crypto_lld_mem_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_Crypto_Core_MemCpy
****************************************************************************//**
*
* Function MemCpy uses Crypto HW.
* Memory structures should not overlap!
* There is no alignment restriction.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param dst
* The pointer to the destination of MemCpy.
*
* \param src
* The pointer to the source of MemCpy.
*
* \param size
* The size in bytes of the copy operation.
*
*******************************************************************************/
__STATIC_INLINE void Cy_Crypto_Core_MemCpy(CRYPTO_Type *base, void* dst, void const *src, uint16_t size)
{
    if (CY_CRYPTO_V1)
    {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        Cy_Crypto_Core_V1_MemCpy(base, dst, src, size);
        #endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        Cy_Crypto_Core_V2_MemCpy(base, dst, src, size);
        #endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */
    }
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_MemSet
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
__STATIC_INLINE void Cy_Crypto_Core_MemSet(CRYPTO_Type *base, void* dst, uint8_t data, uint16_t size)
{
    if (CY_CRYPTO_V1)
    {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        Cy_Crypto_Core_V1_MemSet(base, dst, data, size);
        #endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        Cy_Crypto_Core_V2_MemSet(base, dst, data, size);
        #endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */
    }
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_MemCmp
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
__STATIC_INLINE uint32_t Cy_Crypto_Core_MemCmp(CRYPTO_Type *base, void const *src0, void const *src1, uint16_t size)
{
    uint32_t tmpResult = 1u;
    if (CY_CRYPTO_V1)
    {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        tmpResult = Cy_Crypto_Core_V1_MemCmp(base, src0, src1, size);
        #endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        tmpResult = Cy_Crypto_Core_V2_MemCmp(base, src0, src1, size);
        #endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */
    }

    return (tmpResult);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_MemXor
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
*
* \param src1
* The pointer to the second source of MemXor.
*
* \param size
* The size in bytes of the compare operation.
*
*******************************************************************************/
__STATIC_INLINE void Cy_Crypto_Core_MemXor(CRYPTO_Type *base, void* dst,
                                           void const *src0, void const *src1, uint16_t size)
{
    if (CY_CRYPTO_V1)
    {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        Cy_Crypto_Core_V1_MemXor(base, dst, src0, src1, size);
        #endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        Cy_Crypto_Core_V2_MemXor(base, dst, src0, src1, size);
        #endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */
    }
}

/** \} group_crypto_lld_mem_functions */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCRYPTO */

#endif /* #if !defined (CY_CRYPTO_CORE_MEM_H) */


/* [] END OF FILE */
