/***************************************************************************//**
* \file cy_crypto_core_mem_v2.c
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

#include "cy_crypto_core_mem_v2.h"

#if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)

#if defined(__cplusplus)
extern "C" {
#endif

#include "cy_crypto_core_hw_v2.h"
#include "cy_syslib.h"

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 11.3', 2, \
'CRYPTO_Type will typecast to either CRYPTO_V1_Type or CRYPTO_V2_Type but not both on PDL initialization based on the target device at compile time.');

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_MemCpy
****************************************************************************//**
*
* Function MemCpy uses Crypto HW.
* Memory structures should not overlap!
*
* For CAT1C devices when D-Cache is enabled parameters dst and src must align and end in 32 byte boundary.
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
void Cy_Crypto_Core_V2_MemCpy(CRYPTO_Type *base, void* dst, void const *src, uint16_t size)
{
    if (size != 0U)
    {

#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
        /* Flush the cache */
        if(((uint32_t)src & 0x1FU) == 0u)
        {

            SCB_CleanDCache_by_Addr((volatile void *)src,(int32_t)size);

        }

        if(((uint32_t)dst & 0x1FU) == 0u)
        {

            SCB_InvalidateDCache_by_Addr((volatile void *)dst,(int32_t)size);

        }

#endif

        Cy_Crypto_Core_V2_FFContinue(base, CY_CRYPTO_V2_RB_FF_LOAD0, (const uint8_t*)src, (uint32_t)size);
        Cy_Crypto_Core_V2_FFStart   (base, CY_CRYPTO_V2_RB_FF_STORE, (const uint8_t*)dst, (uint32_t)size);

        while (size >= CY_CRYPTO_V2_DATA_FIFODEPTH)
        {
            Cy_Crypto_Core_V2_BlockMov(base, CY_CRYPTO_V2_RB_FF_STORE, CY_CRYPTO_V2_RB_FF_LOAD0, CY_CRYPTO_V2_DATA_FIFODEPTH);
            size -= CY_CRYPTO_V2_DATA_FIFODEPTH;
        }

        if (size != 0u)
        {
            Cy_Crypto_Core_V2_BlockMov(base, CY_CRYPTO_V2_RB_FF_STORE, CY_CRYPTO_V2_RB_FF_LOAD0, (uint32_t)size);
        }

        Cy_Crypto_Core_V2_Sync(base);

    }
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_MemSet
****************************************************************************//**
*
* Function MemSet uses Crypto HW.
*
* For CAT1C devices when D-Cache is enabled parameter dst must align and end in 32 byte boundary.
*
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
void Cy_Crypto_Core_V2_MemSet(CRYPTO_Type *base, void* dst, uint8_t data, uint16_t size)
{
    if (size != 0U)
    {
    #if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
        if(((uint32_t)dst & 0x1FU) == 0u)
        {

            SCB_InvalidateDCache_by_Addr((volatile void *)dst,(int32_t)size);

        }

    #endif

        Cy_Crypto_Core_V2_FFStart(base, CY_CRYPTO_V2_RB_FF_STORE, dst, (uint32_t)size);

        while (size >= CY_CRYPTO_V2_DATA_FIFODEPTH)
        {
            Cy_Crypto_Core_V2_BlockSet(base, CY_CRYPTO_V2_RB_FF_STORE, data, CY_CRYPTO_V2_DATA_FIFODEPTH);
            size -= CY_CRYPTO_V2_DATA_FIFODEPTH;
        }

        if (size != 0u)
        {
            Cy_Crypto_Core_V2_BlockSet(base, CY_CRYPTO_V2_RB_FF_STORE, data, (uint32_t)size);
        }

        Cy_Crypto_Core_V2_Sync(base);



    }
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_MemCmp
****************************************************************************//**
*
* Function MemCmp uses Crypto HW.
*
*
* For CAT1C devices when D-Cache is enabled parameters src0 and src1 must align and end in 32 byte boundary.
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
uint32_t Cy_Crypto_Core_V2_MemCmp(CRYPTO_Type *base, void const *src0, void const *src1, uint16_t size)
{
    uint32_t memResult = 1U;

    if (size != 0U)
    {

#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    /* Flush the cache */
    if(((uint32_t)src0 & 0x1FU) == 0u)
    {

        SCB_CleanDCache_by_Addr((volatile void *)src0,(int32_t)size);

    }

    if(((uint32_t)src1 & 0x1FU) == 0u)
    {

        SCB_CleanDCache_by_Addr((volatile void *)src1,(int32_t)size);

    }

#endif

        REG_CRYPTO_RESULT(base) = 0UL;

        Cy_Crypto_Core_V2_FFContinue(base, CY_CRYPTO_V2_RB_FF_LOAD0, (const uint8_t*)src0, (uint32_t)size);
        Cy_Crypto_Core_V2_FFContinue(base, CY_CRYPTO_V2_RB_FF_LOAD1, (const uint8_t*)src1, (uint32_t)size);

        while (size >= CY_CRYPTO_V2_DATA_FIFODEPTH)
        {
            Cy_Crypto_Core_V2_BlockCmp(base, CY_CRYPTO_V2_RB_FF_LOAD0, CY_CRYPTO_V2_RB_FF_LOAD1, CY_CRYPTO_V2_DATA_FIFODEPTH);
            size -= CY_CRYPTO_V2_DATA_FIFODEPTH;
        }

        if (size != 0u)
        {
            Cy_Crypto_Core_V2_BlockCmp(base, CY_CRYPTO_V2_RB_FF_LOAD0, CY_CRYPTO_V2_RB_FF_LOAD1, (uint32_t)size);
        }

        Cy_Crypto_Core_V2_Sync(base);

        memResult = (uint32_t)(REG_CRYPTO_RESULT(base));


    }


    return memResult;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_MemXor
****************************************************************************//**
*
* Function MemXor uses Crypto HW.
* Memory structures should not overlap!
*
* For CAT1C devices when D-Cache is enabled parameters dst, src0 and src1 must align and end in 32 byte boundary.
*
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param src0
* The pointer to the first source of MemXor.

* \param src1
* The pointer to the second source of MemXor.

* \param dst
* The pointer to the destination of MemXor.
*
* \param size
* The size in bytes of the compare operation.
*
*******************************************************************************/
void Cy_Crypto_Core_V2_MemXor(CRYPTO_Type *base,
                               void* dst, void const *src0, void const *src1, uint16_t size)
{
    if (size != 0U)
    {

    #if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
        /* Flush the cache */
        if(((uint32_t)src0 & 0x1FU) == 0u)
        {
            SCB_CleanDCache_by_Addr((volatile void *)src0,(int32_t)size);
        }

        if(((uint32_t)src1 & 0x1FU) == 0u)
        {
            SCB_CleanDCache_by_Addr((volatile void *)src1,(int32_t)size);
        }

        if(((uint32_t)dst & 0x1FU) == 0u)
        {
            SCB_InvalidateDCache_by_Addr((volatile void *)dst,(int32_t)size);
        }


    #endif

        Cy_Crypto_Core_V2_FFContinue(base, CY_CRYPTO_V2_RB_FF_LOAD0, (const uint8_t*)src0, (uint32_t)size);
        Cy_Crypto_Core_V2_FFContinue(base, CY_CRYPTO_V2_RB_FF_LOAD1, (const uint8_t*)src1, (uint32_t)size);
        Cy_Crypto_Core_V2_FFStart   (base, CY_CRYPTO_V2_RB_FF_STORE, dst, (uint32_t)size);

        while (size >= CY_CRYPTO_V2_DATA_FIFODEPTH)
        {
            Cy_Crypto_Core_V2_BlockXor(base, CY_CRYPTO_V2_RB_FF_STORE, CY_CRYPTO_V2_RB_FF_LOAD0,
                                             CY_CRYPTO_V2_RB_FF_LOAD1, CY_CRYPTO_V2_DATA_FIFODEPTH);

            size -= CY_CRYPTO_V2_DATA_FIFODEPTH;
        }

        if (size != 0u)
        {
            Cy_Crypto_Core_V2_BlockXor(base, CY_CRYPTO_V2_RB_FF_STORE, CY_CRYPTO_V2_RB_FF_LOAD0,
                                             CY_CRYPTO_V2_RB_FF_LOAD1, (uint32_t)size);
        }

        Cy_Crypto_Core_V2_Sync(base);

    }
}
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');

#if defined(__cplusplus)
}
#endif

#endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */

#endif /* defined(CY_IP_MXCRYPTO) */

/* [] END OF FILE */
