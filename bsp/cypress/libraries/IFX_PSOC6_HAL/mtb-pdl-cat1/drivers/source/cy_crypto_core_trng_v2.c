/***************************************************************************//**
* \file cy_crypto_core_trng_v2.c
* \version 2.50
*
* \brief
*  This file provides the source code to the API for the TRNG
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

#if defined (CY_IP_MXCRYPTO)

#include "cy_crypto_core_trng_v2.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_TR == 1)

#include "cy_crypto_core_trng_config_v2.h"
#include "cy_crypto_core_hw_v2.h"
#include "cy_syslib.h"

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 11.3', 2, \
'CRYPTO_Type will typecast to either CRYPTO_V1_Type or CRYPTO_V2_Type but not both on PDL initialization based on the target device at compile time.');

static void Cy_Crypto_Core_V2_Trng_Init(CRYPTO_Type *base);
static void Cy_Crypto_Core_V2_Trng_Disable(CRYPTO_Type *base);

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Trng_Init
****************************************************************************//**
*
* Initializes the TRNG parameters.
*
* \param base
* The pointer to the CRYPTO instance.
*
*******************************************************************************/
static void Cy_Crypto_Core_V2_Trng_Init(CRYPTO_Type *base)
{
    REG_CRYPTO_TR_CTL0(base)       = CY_CRYPTO_V2_TR_CTL0_VAL;
    REG_CRYPTO_TR_CTL1(base)       = CY_CRYPTO_V2_TR_CTL1_VAL;
    REG_CRYPTO_TR_MON_CTL(base)    = CY_CRYPTO_V2_TR_BTSTR_SEL;
    REG_CRYPTO_TR_MON_CMD(base)    = CY_CRYPTO_V2_TR_START_MON;
    REG_CRYPTO_TR_MON_RC_CTL(base) = CY_CRYPTO_V2_TR_RC_CUTOFF;
    REG_CRYPTO_TR_MON_AP_CTL(base) = CY_CRYPTO_V2_TR_AC_CUTOFF;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Trng_Disable
****************************************************************************//**
*
* Disable TRNG by disabling TRNG ring oscillators
*
* \param base
* The pointer to the CRYPTO instance.
*
*******************************************************************************/
static void Cy_Crypto_Core_V2_Trng_Disable(CRYPTO_Type *base)
{
    REG_CRYPTO_TR_CTL1(base) = CY_CRYPTO_V2_TR_CTL1_DISABLE_VAL;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Trng
****************************************************************************//**
*
* Generates a True Random Number.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param GAROPol
* The polynomial for the programmable Galois ring oscillator.
*
* \param FIROPol
* The polynomial for the programmable Fibonacci ring oscillator.
*
* \param max
* The maximum length of a random number, in the range [0, 32] bits.
*
* \param randomNum
* The pointer to a generated true random number. Must be 4-byte aligned.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V2_Trng(CRYPTO_Type *base,
                                             uint32_t  GAROPol,
                                             uint32_t  FIROPol,
                                             uint32_t  max,
                                             uint32_t *randomNum)
{
    cy_en_crypto_status_t status = CY_CRYPTO_SUCCESS;
    uint32_t stateBusy;
    uint32_t stateROEn;

    Cy_Crypto_Core_V2_Trng_Init(base);

    REG_CRYPTO_TR_GARO_CTL(base) = GAROPol;
    REG_CRYPTO_TR_FIRO_CTL(base) = FIROPol;

    REG_CRYPTO_TR_CTL2(base)     = max;

    if ((REG_CRYPTO_TR_CTL1(base) & (CRYPTO_V2_TR_CTL1_RO11_EN_Msk | CRYPTO_V2_TR_CTL1_RO15_EN_Msk)) != 0u)
    {
        REG_CRYPTO_TR_CMD(base) = _VAL2FLD(CRYPTO_V2_TR_CMD_START, 1u);

        /* Wait until the TRNG instruction is complete */
        do
        {
            stateBusy = _FLD2VAL(CRYPTO_V2_STATUS_BUSY, REG_CRYPTO_STATUS(base));
            stateROEn = REG_CRYPTO_TR_CTL1(base) & (CRYPTO_V2_TR_CTL1_RO11_EN_Msk | CRYPTO_V2_TR_CTL1_RO15_EN_Msk);

            if (0u == stateROEn)
            {
                status = CY_CRYPTO_HW_ERROR;
            }

        } while ((0u != stateBusy) && (CY_CRYPTO_SUCCESS == status));

        if (CY_CRYPTO_HW_ERROR != status)
        {
            *randomNum = (uint32_t)_FLD2VAL(CRYPTO_TR_RESULT_DATA32, REG_CRYPTO_TR_RESULT(base));
        }
    }
    else
    {
        status = CY_CRYPTO_HW_ERROR;
    }

    /* Disable TRNG to reduce power consumption */
    Cy_Crypto_Core_V2_Trng_Disable(base);

    return (status);
}
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');

#endif /* #if (CPUSS_CRYPTO_TR == 1) */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCRYPTO */


/* [] END OF FILE */
