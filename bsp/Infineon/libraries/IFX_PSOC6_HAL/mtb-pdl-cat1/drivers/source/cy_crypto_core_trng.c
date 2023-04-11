/***************************************************************************//**
* \file cy_crypto_core_trng.c
* \version 2.70
*
* \brief
*  This file provides the source code to the API for the TRNG
*  in the Crypto block driver.
*
********************************************************************************
* Copyright 2016-2019 Cypress Semiconductor Corporation
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


#include "cy_crypto_core_trng.h"

#if defined(CY_IP_MXCRYPTO)

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_TR == 1) && defined(CY_CRYPTO_CFG_TRNG_C)

#if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
#include "cy_crypto_core_hw_v1.h"
#endif

#include "cy_crypto_core_trng_config.h"

const cy_stc_crypto_trng_config_t cy_trngDefaultConfig =
{
    (uint8_t)CY_CRYPTO_DEF_TR_SAMPLE_CLOCK_DIV,            /* sampleClockDiv */
    (uint8_t)CY_CRYPTO_DEF_TR_RED_CLOCK_DIV,               /* reducedClockDiv */
    (uint8_t)CY_CRYPTO_DEF_TR_INIT_DELAY,                  /* initDelay */
    CY_CRYPTO_DEF_TR_VON_NEUMANN_CORR,            /* vnCorrectorEnable */
    CY_CRYPTO_DEF_TR_STOP_ON_AP_DETECT,           /* stopOnAPDetect */
    CY_CRYPTO_DEF_TR_STOP_ON_RC_DETECT,           /* stopOnRCDetect */
    CY_CRYPTO_DEF_TR_RO11_EN,                     /* ro11Enable */
    CY_CRYPTO_DEF_TR_RO15_EN,                     /* ro15Enable */
    CY_CRYPTO_DEF_TR_GARO15_EN,                   /* garo15Enable */
    CY_CRYPTO_DEF_TR_GARO31_EN,                   /* garo31Enable */
    CY_CRYPTO_DEF_TR_FIRO15_EN,                   /* firo15Enable */
    CY_CRYPTO_DEF_TR_FIRO31_EN,                   /* firo31Enable */
    CY_CRYPTO_DEF_TR_GARO,                        /* garo31Poly */
    CY_CRYPTO_DEF_TR_FIRO,                        /* firo31Poly */
    CY_CRYPTO_DEF_TR_BITSTREAM_SEL,               /* monBitStreamSelect */
    (uint8_t)CY_CRYPTO_DEF_TR_CUTOFF_COUNT8,               /* monCutoffCount8 */
    (uint16_t)CY_CRYPTO_DEF_TR_CUTOFF_COUNT16,              /* monCutoffCount16 */
    (uint16_t)CY_CRYPTO_DEF_TR_WINDOW_SIZE                  /* monWindowSize */
};

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_Init
****************************************************************************//**
*
* Initialize the TRNG hardware submodule
*
* \pre If the TRNG submodule is initialized previously, the
* \ref Cy_Crypto_Core_Trng_DeInit() must be called before calling this function.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param config
* The pointer to the configuration structure.
*
*******************************************************************************/
void Cy_Crypto_Core_Trng_Init(CRYPTO_Type *base, cy_stc_crypto_trng_config_t *config)
{
    if(NULL != base)
    {
        if (NULL == config)
        {
            config = (cy_stc_crypto_trng_config_t *)&cy_trngDefaultConfig;
        }
        else
        {
            CY_ASSERT_L3(CY_CRYPTO_IS_BS_SELECT_VALID(config->monBitStreamSelect));
        }

        REG_CRYPTO_TR_MON_CMD(base) = 0UL;
        REG_CRYPTO_TR_CTL1(base) = 0UL;

        Cy_Crypto_Core_ClearInterrupt(base, CRYPTO_INTR_TR_DATA_AVAILABLE_Msk | CRYPTO_INTR_TR_INITIALIZED_Msk);
        Cy_Crypto_Core_Trng_MonClearHealthStatus(base);

        REG_CRYPTO_TR_GARO_CTL(base) = config->garo31Poly;
        REG_CRYPTO_TR_FIRO_CTL(base) = config->firo31Poly;

        REG_CRYPTO_TR_CTL0(base) = (uint32_t)(_VAL2FLD(CRYPTO_TR_CTL0_SAMPLE_CLOCK_DIV, config->sampleClockDiv)
                                            | _VAL2FLD(CRYPTO_TR_CTL0_RED_CLOCK_DIV, config->reducedClockDiv)
                                            | _VAL2FLD(CRYPTO_TR_CTL0_INIT_DELAY, config->initDelay)
                                            | _VAL2FLD(CRYPTO_TR_CTL0_VON_NEUMANN_CORR, config->vnCorrectorEnable)
                                            | _VAL2FLD(CRYPTO_TR_CTL0_STOP_ON_AP_DETECT, config->stopOnAPDetect)
                                            | _VAL2FLD(CRYPTO_TR_CTL0_STOP_ON_RC_DETECT, config->stopOnRCDetect));

        REG_CRYPTO_TR_CTL1(base) = (uint32_t)(_VAL2FLD(CRYPTO_TR_CTL1_RO11_EN, config->ro11Enable)
                                            | _VAL2FLD(CRYPTO_TR_CTL1_RO15_EN, config->ro15Enable)
                                            | _VAL2FLD(CRYPTO_TR_CTL1_GARO15_EN, config->garo15Enable)
                                            | _VAL2FLD(CRYPTO_TR_CTL1_GARO31_EN, config->garo31Enable)
                                            | _VAL2FLD(CRYPTO_TR_CTL1_FIRO15_EN, config->firo15Enable)
                                            | _VAL2FLD(CRYPTO_TR_CTL1_FIRO31_EN, config->firo31Enable));

        REG_CRYPTO_TR_MON_CTL(base) = (uint32_t)_VAL2FLD(CRYPTO_TR_MON_CTL_BITSTREAM_SEL, config->monBitStreamSelect);

        REG_CRYPTO_TR_MON_RC_CTL(base) = (uint32_t)_VAL2FLD(CRYPTO_TR_MON_RC_CTL_CUTOFF_COUNT8, config->monCutoffCount8);

        REG_CRYPTO_TR_MON_AP_CTL(base) = (uint32_t)(_VAL2FLD(CRYPTO_TR_MON_AP_CTL_CUTOFF_COUNT16, config->monCutoffCount16)
                                                  | _VAL2FLD(CRYPTO_TR_MON_AP_CTL_WINDOW_SIZE, config->monWindowSize));
    }
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_DeInit
****************************************************************************//**
*
* Clears all TRNG registers by set to hardware default values.
*
* \param base
* The pointer to the CRYPTO instance.
*
*******************************************************************************/
void Cy_Crypto_Core_Trng_DeInit(CRYPTO_Type *base)
{
    REG_CRYPTO_TR_CTL0(base) = (uint32_t)_VAL2FLD(CRYPTO_TR_CTL0_INIT_DELAY, 3U);
    REG_CRYPTO_TR_CTL1(base) = 0UL;

    #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
    REG_CRYPTO_TR_CTL2(base) = 0UL;
    REG_CRYPTO_TR_CMD(base) = 0UL;
    #endif

    REG_CRYPTO_TR_GARO_CTL(base) = 0UL;
    REG_CRYPTO_TR_FIRO_CTL(base) = 0UL;

    REG_CRYPTO_TR_MON_CTL(base) = 2UL;

    REG_CRYPTO_TR_MON_RC_CTL(base) = 0UL;
    REG_CRYPTO_TR_MON_AP_CTL(base) = 0UL;

    REG_CRYPTO_TR_MON_CMD(base) = 0UL;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_Start
****************************************************************************//**
*
* Starts a random number generation.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param dataSize
* The maximum length of a random number, in the range [0, 32] bits.
*
* \return
* The error / status code. See \ref cy_en_crypto_status_t.
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_Trng_Start(CRYPTO_Type *base, uint32_t dataSize)
{
    cy_en_crypto_status_t status = CY_CRYPTO_NOT_INITIALIZED;

    if (Cy_Crypto_Core_IsEnabled(base))
    {
        Cy_Crypto_Core_Trng_WaitForReady(base);

        if (Cy_Crypto_Core_Trng_AnyRoEnabled(base))
        {
            if (Cy_Crypto_Core_Trng_IsInitialized(base))
            {
                status = CY_CRYPTO_BAD_PARAMS;

                Cy_Crypto_Core_ClearInterrupt(base, CRYPTO_INTR_TR_DATA_AVAILABLE_Msk);

                if (dataSize <= 32U)
                {
                    status = CY_CRYPTO_SUCCESS;
                    if (CY_CRYPTO_V1)
                    {
                        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
                        Cy_Crypto_SetReg1Instr(base, dataSize);
                        Cy_Crypto_Run1ParamInstr(base, CY_CRYPTO_V1_TRNG_OPC, CY_CRYPTO_RSRC0_SHIFT);
                        #endif
                    }
                    else
                    {
                        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
                        REG_CRYPTO_TR_CTL2(base) = dataSize;
                        REG_CRYPTO_TR_CMD(base) = 1UL;
                        #endif
                    }
                }
            }
        }
    }
    return status;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_ReadData
****************************************************************************//**
*
* Reads in blocking mode a generated random number.
*
* \note
* Call this API only after Cy_Crypto_Core_Trng_Start() is successful.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param randomData
* The pointer to a generated true random number. Must be 4-byte aligned.
*
* \return
* The error / status code. See \ref cy_en_crypto_status_t.
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_Trng_ReadData(CRYPTO_Type *base, uint32_t *randomData)
{
    cy_en_crypto_status_t status = CY_CRYPTO_NOT_INITIALIZED;
    uint8_t stateHealthMon;

    if (Cy_Crypto_Core_IsEnabled(base))
    {
        if (false != Cy_Crypto_Core_Trng_AnyRoEnabled(base))
        {
            status = CY_CRYPTO_SUCCESS;

            Cy_Crypto_Core_Trng_WaitForComplete(base);

            *randomData = Cy_Crypto_Core_Trng_GetData(base);

            stateHealthMon = Cy_Crypto_Core_Trng_MonGetHealthStatus(base);
            if (0u != stateHealthMon)
            {
                status = CY_CRYPTO_TRNG_UNHEALTHY;
            }
        }
    }
    return status;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng
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
* The maximum length of a random number, in the range of [0, 32] bits.
*
* \param randomNum
* The pointer to a generated true random number. Must be 4-byte aligned.
*
* \return
* \ref cy_en_crypto_status_t
*
* \funcusage
* \snippet crypto/snippet/main.c snippet_myCryptoCoreTrngUse
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_Trng(CRYPTO_Type *base,
                                             uint32_t  GAROPol,
                                             uint32_t  FIROPol,
                                             uint32_t  max,
                                             uint32_t *randomNum)
{
    cy_en_crypto_status_t status;

    Cy_Crypto_Core_Trng_Init(base, (cy_stc_crypto_trng_config_t *)&cy_trngDefaultConfig);

    Cy_Crypto_Core_Trng_SetGaroPoly(base, GAROPol);
    Cy_Crypto_Core_Trng_SetFiroPoly(base, FIROPol);

    status = Cy_Crypto_Core_Trng_Start(base, max);

    if (CY_CRYPTO_SUCCESS == status)
    {
        status = Cy_Crypto_Core_Trng_ReadData(base, randomNum);
    }

    return (status);
}

#endif /* (CPUSS_CRYPTO_TR == 1) && defined(CY_CRYPTO_CFG_TRNG_C) */

#if defined(__cplusplus)
}
#endif

#endif /* defined(CY_IP_MXCRYPTO) */


/* [] END OF FILE */
