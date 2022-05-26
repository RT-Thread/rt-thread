/*
 * Copyright 2019-2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_flexram_allocate.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "driver.soc_flexram_allocate"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief FLEXRAM allocate on-chip ram for OCRAM,ITCM,DTCM
 * This function is independent of FLEXRAM_Init, it can be called directly if ram re-allocate
 * is needed.
 * param config allocate configuration.
 * retval kStatus_InvalidArgument the argument is invalid
 *         kStatus_Success allocate success
 */
status_t FLEXRAM_AllocateRam(flexram_allocate_ram_t *config)
{
    assert(config != NULL);

    uint8_t dtcmBankNum  = config->dtcmBankNum;
    uint8_t itcmBankNum  = config->itcmBankNum;
    uint8_t ocramBankNum = config->ocramBankNum;
    uint8_t i            = 0U;
    uint32_t bankCfg     = 0U;
    status_t status      = kStatus_Success;

    /* check the arguments */
    if ((uint8_t)FSL_FEATURE_FLEXRAM_INTERNAL_RAM_TOTAL_BANK_NUMBERS < (dtcmBankNum + itcmBankNum + ocramBankNum))
    {
        status = kStatus_InvalidArgument;
    }
    else
    {
        /* flexram bank config value */
        for (i = 0U; i < (uint8_t)FSL_FEATURE_FLEXRAM_INTERNAL_RAM_TOTAL_BANK_NUMBERS; i++)
        {
            if (i < ocramBankNum)
            {
                bankCfg |= ((uint32_t)kFLEXRAM_BankOCRAM) << (i * 2U);
                continue;
            }

            if (i < (dtcmBankNum + ocramBankNum))
            {
                bankCfg |= ((uint32_t)kFLEXRAM_BankDTCM) << (i * 2U);
                continue;
            }

            if (i < (dtcmBankNum + ocramBankNum + itcmBankNum))
            {
                bankCfg |= ((uint32_t)kFLEXRAM_BankITCM) << (i * 2U);
                continue;
            }
        }

        IOMUXC_GPR->GPR17 = bankCfg;

        /* select ram allocate source from FLEXRAM_BANK_CFG */
        FLEXRAM_SetAllocateRamSrc(kFLEXRAM_BankAllocateThroughBankCfg);
    }

    return status;
}
