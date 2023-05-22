/***************************************************************************//**
* \file cy_crypto_core_prng_v2.c
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

#include "cy_crypto_core_prng_v2.h"

#if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_PR == 1) && defined(CY_CRYPTO_CFG_PRNG_C)

#include "cy_crypto_core_hw_v2.h"
#include "cy_syslib.h"

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 11.3', 2, \
'CRYPTO_Type will typecast to either CRYPTO_V1_Type or CRYPTO_V2_Type but not both on PDL initialization based on the target device at compile time.');

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Prng_Init
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
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V2_Prng_Init(CRYPTO_Type *base,
                                                  uint32_t lfsr32InitState,
                                                  uint32_t lfsr31InitState,
                                                  uint32_t lfsr29InitState)
{
    REG_CRYPTO_PR_LFSR_CTL0(base) = (uint32_t)(_VAL2FLD(CRYPTO_PR_LFSR_CTL0_LFSR32, lfsr32InitState));

    REG_CRYPTO_PR_LFSR_CTL1(base) = (uint32_t)(_VAL2FLD(CRYPTO_PR_LFSR_CTL1_LFSR31, lfsr31InitState));

    REG_CRYPTO_PR_LFSR_CTL2(base) = (uint32_t)(_VAL2FLD(CRYPTO_PR_LFSR_CTL2_LFSR29, lfsr29InitState));

    return (CY_CRYPTO_SUCCESS);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Prng
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
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V2_Prng(CRYPTO_Type *base,
                                             uint32_t max,
                                             uint32_t *randomNum)
{
    REG_CRYPTO_PR_MAX_CTL(base) = max;

    REG_CRYPTO_PR_CMD(base) = _VAL2FLD(CRYPTO_V2_PR_CMD_START, 1u);

    /* Wait until the PRNG instruction is complete */
    while(0uL != _FLD2VAL(CRYPTO_V2_STATUS_BUSY, REG_CRYPTO_STATUS(base)))
    {
    }

    *randomNum = (uint32_t)_FLD2VAL(CRYPTO_V2_PR_RESULT_DATA32, REG_CRYPTO_PR_RESULT(base));

    return (CY_CRYPTO_SUCCESS);
}

CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');

#endif /* (CPUSS_CRYPTO_PR == 1) && defined(CY_CRYPTO_CFG_PRNG_C) */

#if defined(__cplusplus)
}
#endif

#endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */

#endif /* defined(CY_IP_MXCRYPTO) */


/* [] END OF FILE */
