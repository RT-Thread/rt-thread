/***************************************************************************//**
* \file cy_crypto_core_prng.h
* \version 2.70
*
* \brief
*  This file provides provides constant and parameters for the API of the PRNG
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


#if !defined (CY_CRYPTO_CORE_PRNG_H)
#define CY_CRYPTO_CORE_PRNG_H

#include "cy_device.h"

#if defined (CY_IP_MXCRYPTO)

#include "cy_crypto_common.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_PR == 1) && defined(CY_CRYPTO_CFG_PRNG_C)

#include "cy_crypto_core_prng_v1.h"
#include "cy_crypto_core_prng_v2.h"

typedef cy_en_crypto_status_t (*cy_crypto_prng_init_func_t)(CRYPTO_Type *base,
                                                  uint32_t lfsr32InitState,
                                                  uint32_t lfsr31InitState,
                                                  uint32_t lfsr29InitState);

typedef cy_en_crypto_status_t (*cy_crypto_prng_func_t)(CRYPTO_Type *base,
                                             uint32_t max,
                                             uint32_t *randomNum);

/**
* \addtogroup group_crypto_lld_rng_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Prng_Init
****************************************************************************//**
*
* Initializes the PRND parameters.
* Invoking this function causes a restart of the pseudo-random sequence.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param lfsr32InitState
* A non-zero seed value for the first LFSR.

* \param lfsr31InitState
* A non-zero seed value for the second LFSR.

* \param lfsr29InitState
* A non-zero seed value for the third LFSR.
*
* \return
* \ref cy_en_crypto_status_t
*
* \funcusage
* \snippet crypto/snippet/main.c snippet_myCryptoCorePrngUse
*
*******************************************************************************/
__STATIC_INLINE cy_en_crypto_status_t Cy_Crypto_Core_Prng_Init(CRYPTO_Type *base,
                                                  uint32_t lfsr32InitState,
                                                  uint32_t lfsr31InitState,
                                                  uint32_t lfsr29InitState)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_NOT_SUPPORTED;

    if (CY_CRYPTO_V1)
    {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        tmpResult = Cy_Crypto_Core_V1_Prng_Init(base, lfsr32InitState, lfsr31InitState, lfsr29InitState);
        #endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        tmpResult = Cy_Crypto_Core_V2_Prng_Init(base, lfsr32InitState, lfsr31InitState, lfsr29InitState);
        #endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */
    }

    return tmpResult;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Prng
****************************************************************************//**
*
* Generates a Pseudo Random Number.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param max
* The maximum value of a random number.
*
* \param randomNum
* The pointer to a variable to store the generated pseudo random number.
*
* \return
* \ref cy_en_crypto_status_t
*
* \funcusage
* \snippet crypto/snippet/main.c snippet_myCryptoCorePrngUse
*
*******************************************************************************/
__STATIC_INLINE cy_en_crypto_status_t Cy_Crypto_Core_Prng(CRYPTO_Type *base,
                                             uint32_t max,
                                             uint32_t *randomNum)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_NOT_SUPPORTED;

    if (CY_CRYPTO_V1)
    {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        tmpResult = Cy_Crypto_Core_V1_Prng(base, max, randomNum);
        #endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        tmpResult = Cy_Crypto_Core_V2_Prng(base, max, randomNum);
        #endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */
    }

    return tmpResult;
}

/** \} group_crypto_lld_rng_functions */

#endif /* (CPUSS_CRYPTO_PR == 1) && defined(CY_CRYPTO_CFG_PRNG_C) */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCRYPTO */

#endif /* #if !defined (CY_CRYPTO_CORE_PRNG_H) */


/* [] END OF FILE */
