/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_xecc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.xecc"
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
 * brief XECC module initialization function.
 *
 * param base XECC base address.
 */
void XECC_Init(XECC_Type *base, const xecc_config_t *config)
{
    /* Enable all the interrupt status */
    base->ERR_STAT_EN = kXECC_AllInterruptsStatusEnable;
    /* Clear all the interrupt status */
    base->ERR_STATUS = kXECC_AllInterruptsFlag;
    /* Disable all the interrpt */
    base->ERR_SIG_EN = 0U;

    /* Set ECC regions, which are 4KB aligned */
    base->ECC_BASE_ADDR0 = config->Region0BaseAddress >> 12U;
    base->ECC_END_ADDR0  = config->Region0EndAddress >> 12U;
    base->ECC_BASE_ADDR1 = config->Region1BaseAddress >> 12U;
    base->ECC_END_ADDR1  = config->Region1EndAddress >> 12U;
    base->ECC_BASE_ADDR2 = config->Region2BaseAddress >> 12U;
    base->ECC_END_ADDR2  = config->Region2EndAddress >> 12U;
    base->ECC_BASE_ADDR3 = config->Region3BaseAddress >> 12U;
    base->ECC_END_ADDR3  = config->Region3EndAddress >> 12U;

    /* Enable ECC function */
    base->ECC_CTRL = XECC_ECC_CTRL_ECC_EN(config->enableXECC);
    base->ECC_CTRL |= XECC_ECC_CTRL_WECC_EN(config->enableWriteECC);
    base->ECC_CTRL |= XECC_ECC_CTRL_RECC_EN(config->enableReadECC);
    base->ECC_CTRL |= XECC_ECC_CTRL_SWAP_EN(config->enableSwap);

    /* Make sure XECC register configuration operation has been done. */
    __DSB();
}

/*!
 * brief Deinitializes the XECC.
 *
 */
void XECC_Deinit(XECC_Type *base)
{
    /* Disable ECC function */
    base->ECC_CTRL &= ~XECC_ECC_CTRL_ECC_EN(1);
}

void XECC_GetDefaultConfig(xecc_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    /* Default XECC function */
    config->enableXECC = false;
    /* Default write ECC function */
    config->enableWriteECC = false;
    /* Default read ECC function */
    config->enableReadECC = false;
    /* Default swap function */
    config->enableSwap = false;

    /* ECC region 0 base address */
    config->Region0BaseAddress = 0U;
    /* ECC region 0 end address */
    config->Region0EndAddress = 0U;
    /* ECC region 1 base address */
    config->Region1BaseAddress = 0U;
    /* ECC region 1 end address */
    config->Region1EndAddress = 0U;
    /* ECC region 2 base address */
    config->Region2BaseAddress = 0U;
    /* ECC region 2 end address */
    config->Region2EndAddress = 0U;
    /* ECC region 3 base address */
    config->Region3BaseAddress = 0U;
    /* ECC region 3 end address */
    config->Region3EndAddress = 0U;
}

/* Mainly use for debug, it can be deprecated when release */
status_t XECC_ErrorInjection(XECC_Type *base, uint32_t errordata, uint8_t erroreccdata)
{
    status_t status = kStatus_Success;

    if ((errordata != 0x00U) || (erroreccdata != 0x00U))
    {
        /* error data injection */
        base->ERR_DATA_INJ = errordata;
        /* error ecc code injection */
        base->ERR_ECC_INJ = erroreccdata;
        /* Make sure injection operation has been done. */
        __DSB();
    }
    else
    {
        status = kStatus_Fail;
    }

    return status;
}

void XECC_GetSingleErrorInfo(XECC_Type *base, xecc_single_error_info_t *info)
{
    assert(info != NULL);

    info->singleErrorAddress  = base->SINGLE_ERR_ADDR;
    info->singleErrorData     = base->SINGLE_ERR_DATA;
    info->singleErrorEccCode  = base->SINGLE_ERR_ECC;
    info->singleErrorBitField = base->SINGLE_ERR_BIT_FIELD;
    info->singleErrorBitPos   = base->SINGLE_ERR_POS;
}

void XECC_GetMultiErrorInfo(XECC_Type *base, xecc_multi_error_info_t *info)
{
    assert(info != NULL);

    info->multiErrorAddress  = base->MULTI_ERR_ADDR;
    info->multiErrorData     = base->MULTI_ERR_DATA;
    info->multiErrorEccCode  = base->MULTI_ERR_ECC;
    info->multiErrorBitField = base->MULTI_ERR_BIT_FIELD;
}
