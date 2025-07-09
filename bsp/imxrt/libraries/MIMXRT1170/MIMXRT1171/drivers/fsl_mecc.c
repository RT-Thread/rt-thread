/*
 * Copyright 2019-2021, 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_mecc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.mecc"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Gets the instance from the base address to be used to gate or ungate the module clock
 *
 * @param base MECC base address
 *
 * @return The MECC instance
 */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief MECC module initialization function.
 *
 * param base MECC base address.
 */
void MECC_Init(MECC_Type *base, mecc_config_t *config)
{
    /* Check selected memory region is valid. */
    assert(config->startAddress < config->endAddress);

    volatile uint64_t *ocramStartAddr = NULL;

    base->PIPE_ECC_EN = 0UL;

    /* enable all the interrupt status */
    base->ERR_STAT_EN = kMECC_AllInterruptsStatusEnable;
    /* clear all the interrupt status */
    base->ERR_STATUS = kMECC_AllInterruptsFlag;
    /* disable all the interrpt */
    base->ERR_SIG_EN = 0U;
    /* enable ECC function */
    base->PIPE_ECC_EN = MECC_PIPE_ECC_EN_ECC_EN(config->enableMecc) | \
                        MECC_PENDING_STAT_READ_DATA_WAIT_PENDING(config->enableReadDataWait) | \
                        MECC_PENDING_STAT_READ_ADDR_PIPE_PENDING(config->enableReadAddrPipeline) | \
                        MECC_PENDING_STAT_WRITE_DATA_PIPE_PENDING(config->enableWriteDataPipeline) | \
                        MECC_PENDING_STAT_WRITE_ADDR_PIPE_PENDING(config->enableWriteAddrPipeline);

    __DSB();

      /* Need to be initialized for ECC function operation, note that do not use memset() to initialize,
           because it will use STR instruction and STR is byte access and MECC is 64 bits access operation. */
      ocramStartAddr = (uint64_t *)config->startAddress;
      while (ocramStartAddr < (uint64_t *)config->endAddress)
      {
          *ocramStartAddr = 0x00;
          ocramStartAddr++;
      }

}

/*!
 * brief Deinitializes the MECC.
 *
 */
void MECC_Deinit(MECC_Type *base)
{
    /* Disable ECC function */
    base->PIPE_ECC_EN &= ~MECC_PIPE_ECC_EN_ECC_EN(1);
}

void MECC_GetDefaultConfig(mecc_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    /* Default MECC function. */
    config->enableMecc = false;
    config->startAddress = 0UL;
    config->endAddress = 0UL;
    config->enableReadDataWait = false;
    config->enableReadAddrPipeline = false;
    config->enableWriteDataPipeline = false;
    config->enableWriteAddrPipeline = false;
}

/* Initialize OCRAM */

/* Mainly use for debug, it can be deprecated when release */
status_t MECC_ErrorInjection(
    MECC_Type *base, uint32_t lowerrordata, uint32_t higherrordata, uint8_t eccdata, uint8_t banknumber)
{
    status_t status = kStatus_Success;

    switch (banknumber)
    {
        case kMECC_OcramBank0:
            /* Low 32 bits of Ocram bank0 error injection */
            base->ERR_DATA_INJ_LOW0 = lowerrordata;
            /* High 32 bits of Ocram bank0 error injection */
            base->ERR_DATA_INJ_HIGH0 = higherrordata;
            /* Ecc code of Ocram bank0 error injection */
            base->ERR_ECC_INJ0 = eccdata;
            break;

        case kMECC_OcramBank1:
            /* Low 32 bits of Ocram bank1 error injection */
            base->ERR_DATA_INJ_LOW1 = lowerrordata;
            /* High 32 bits of Ocram bank1 error injection */
            base->ERR_DATA_INJ_HIGH1 = higherrordata;
            /* Ecc code of Ocram bank1 error injection */
            base->ERR_ECC_INJ1 = eccdata;
            break;

        case kMECC_OcramBank2:
            /* Low 32 bits of Ocram bank2 error injection */
            base->ERR_DATA_INJ_LOW2 = lowerrordata;
            /* High 32 bits of Ocram bank2 error injection */
            base->ERR_DATA_INJ_HIGH2 = higherrordata;
            /* Ecc code of Ocram bank2 error injection */
            base->ERR_ECC_INJ2 = eccdata;
            break;

        case kMECC_OcramBank3:
            /* Low 32 bits of Ocram bank3 error injection */
            base->ERR_DATA_INJ_LOW3 = lowerrordata;
            /* High 32 bits of Ocram bank3 error injection */
            base->ERR_DATA_INJ_HIGH3 = higherrordata;
            /* Ecc code of Ocram bank3 error injection */
            base->ERR_ECC_INJ3 = eccdata;
            break;

        default:
            status = kStatus_MECC_BankMiss;
            break;
    }

    return status;
}

status_t MECC_GetSingleErrorInfo(MECC_Type *base, mecc_single_error_info_t *info, uint8_t banknumber)
{
    assert(info != NULL);
    status_t status     = kStatus_Success;
    uint8_t tempPosLow  = 0U;
    uint8_t tempPosHigh = 0U;
    volatile uint32_t counter    = 0U;

    switch (banknumber)
    {
        case kMECC_OcramBank0:
            info->singleErrorEccCode =
                (uint8_t)((base->SINGLE_ERR_ADDR_ECC0 & MECC_SINGLE_ERR_ADDR_ECC0_SINGLE_ERR_ECC_MASK) >>
                          MECC_SINGLE_ERR_ADDR_ECC0_SINGLE_ERR_ECC_SHIFT);
            info->singleErrorAddress = (base->SINGLE_ERR_ADDR_ECC0 & MECC_SINGLE_ERR_ADDR_ECC0_SINGLE_ERR_ADDR_MASK) >>
                                       MECC_SINGLE_ERR_ADDR_ECC0_SINGLE_ERR_ADDR_SHIFT;
            info->singleErrorDataLow  = base->SINGLE_ERR_DATA_LOW0;
            info->singleErrorDataHigh = base->SINGLE_ERR_DATA_HIGH0;
            tempPosLow                = (uint8_t)base->SINGLE_ERR_POS_LOW0;
            tempPosHigh               = (uint8_t)base->SINGLE_ERR_POS_HIGH0;
            break;

        case kMECC_OcramBank1:
            info->singleErrorEccCode =
                (uint8_t)((base->SINGLE_ERR_ADDR_ECC1 & MECC_SINGLE_ERR_ADDR_ECC1_SINGLE_ERR_ECC_MASK) >>
                          MECC_SINGLE_ERR_ADDR_ECC1_SINGLE_ERR_ECC_SHIFT);
            info->singleErrorAddress = (base->SINGLE_ERR_ADDR_ECC1 & MECC_SINGLE_ERR_ADDR_ECC1_SINGLE_ERR_ADDR_MASK) >>
                                       MECC_SINGLE_ERR_ADDR_ECC1_SINGLE_ERR_ADDR_SHIFT;
            info->singleErrorDataLow  = base->SINGLE_ERR_DATA_LOW1;
            info->singleErrorDataHigh = base->SINGLE_ERR_DATA_HIGH1;
            tempPosLow                = (uint8_t)base->SINGLE_ERR_POS_LOW1;
            tempPosHigh               = (uint8_t)base->SINGLE_ERR_POS_HIGH1;
            break;

        case kMECC_OcramBank2:
            info->singleErrorEccCode =
                (uint8_t)((base->SINGLE_ERR_ADDR_ECC2 & MECC_SINGLE_ERR_ADDR_ECC2_SINGLE_ERR_ECC_MASK) >>
                          MECC_SINGLE_ERR_ADDR_ECC2_SINGLE_ERR_ECC_SHIFT);
            info->singleErrorAddress = (base->SINGLE_ERR_ADDR_ECC2 & MECC_SINGLE_ERR_ADDR_ECC2_SINGLE_ERR_ADDR_MASK) >>
                                       MECC_SINGLE_ERR_ADDR_ECC2_SINGLE_ERR_ADDR_SHIFT;
            info->singleErrorDataLow  = base->SINGLE_ERR_DATA_LOW2;
            info->singleErrorDataHigh = base->SINGLE_ERR_DATA_HIGH2;
            tempPosLow                = (uint8_t)base->SINGLE_ERR_POS_LOW2;
            tempPosHigh               = (uint8_t)base->SINGLE_ERR_POS_HIGH2;
            break;

        case kMECC_OcramBank3:
            info->singleErrorEccCode =
                (uint8_t)((base->SINGLE_ERR_ADDR_ECC3 & MECC_SINGLE_ERR_ADDR_ECC3_SINGLE_ERR_ECC_MASK) >>
                          MECC_SINGLE_ERR_ADDR_ECC3_SINGLE_ERR_ECC_SHIFT);
            info->singleErrorAddress = (base->SINGLE_ERR_ADDR_ECC3 & MECC_SINGLE_ERR_ADDR_ECC3_SINGLE_ERR_ADDR_MASK) >>
                                       MECC_SINGLE_ERR_ADDR_ECC3_SINGLE_ERR_ADDR_SHIFT;
            info->singleErrorDataLow  = base->SINGLE_ERR_DATA_LOW3;
            info->singleErrorDataHigh = base->SINGLE_ERR_DATA_HIGH3;
            tempPosLow                = (uint8_t)base->SINGLE_ERR_POS_LOW3;
            tempPosHigh               = (uint8_t)base->SINGLE_ERR_POS_HIGH3;
            break;

        default:
            status = kStatus_MECC_BankMiss;
            break;
    }

    while (tempPosLow > 0U)
    {
        tempPosLow = tempPosLow >> 1;
        counter++;
    }

    if (counter == 0U)
    {
        info->singleErrorPosLow = 0;
    }
    else
    {
        info->singleErrorPosLow = counter - 1U;
    }

    counter = 0U;
    while (tempPosHigh > 0U)
    {
        tempPosHigh = tempPosHigh >> 1;
        counter++;
    }

    if (counter == 0U)
    {
        info->singleErrorPosHigh = 0;
    }
    else
    {
        info->singleErrorPosHigh = counter - 1U;
    }

    return status;
}

status_t MECC_GetMultiErrorInfo(MECC_Type *base, mecc_multi_error_info_t *info, uint8_t banknumber)
{
    assert(info != NULL);
    status_t status = kStatus_Success;

    switch (banknumber)
    {
        case kMECC_OcramBank0:
            info->multiErrorEccCode =
                (uint8_t)((base->MULTI_ERR_ADDR_ECC0 & MECC_MULTI_ERR_ADDR_ECC0_MULTI_ERR_ECC_MASK) >>
                          MECC_MULTI_ERR_ADDR_ECC0_MULTI_ERR_ECC_SHIFT);
            info->multiErrorAddress = (base->MULTI_ERR_ADDR_ECC0 & MECC_MULTI_ERR_ADDR_ECC0_MULTI_ERR_ADDR_MASK) >>
                                      MECC_MULTI_ERR_ADDR_ECC0_MULTI_ERR_ADDR_SHIFT;
            info->multiErrorDataLow  = base->MULTI_ERR_DATA_LOW0;
            info->multiErrorDataHigh = base->MULTI_ERR_DATA_HIGH0;
            break;

        case kMECC_OcramBank1:
            info->multiErrorEccCode =
                (uint8_t)((base->MULTI_ERR_ADDR_ECC1 & MECC_MULTI_ERR_ADDR_ECC1_MULTI_ERR_ECC_MASK) >>
                          MECC_MULTI_ERR_ADDR_ECC1_MULTI_ERR_ECC_SHIFT);
            info->multiErrorAddress = (base->MULTI_ERR_ADDR_ECC1 & MECC_MULTI_ERR_ADDR_ECC1_MULTI_ERR_ADDR_MASK) >>
                                      MECC_MULTI_ERR_ADDR_ECC1_MULTI_ERR_ADDR_SHIFT;
            info->multiErrorDataLow  = base->MULTI_ERR_DATA_LOW1;
            info->multiErrorDataHigh = base->MULTI_ERR_DATA_HIGH1;
            break;

        case kMECC_OcramBank2:
            info->multiErrorEccCode =
                (uint8_t)((base->MULTI_ERR_ADDR_ECC2 & MECC_MULTI_ERR_ADDR_ECC2_MULTI_ERR_ECC_MASK) >>
                          MECC_MULTI_ERR_ADDR_ECC2_MULTI_ERR_ECC_SHIFT);
            info->multiErrorAddress = (base->MULTI_ERR_ADDR_ECC2 & MECC_MULTI_ERR_ADDR_ECC2_MULTI_ERR_ADDR_MASK) >>
                                      MECC_MULTI_ERR_ADDR_ECC2_MULTI_ERR_ADDR_SHIFT;
            info->multiErrorDataLow  = base->MULTI_ERR_DATA_LOW2;
            info->multiErrorDataHigh = base->MULTI_ERR_DATA_HIGH2;
            break;

        case kMECC_OcramBank3:
            info->multiErrorEccCode =
                (uint8_t)((base->MULTI_ERR_ADDR_ECC3 & MECC_MULTI_ERR_ADDR_ECC3_MULTI_ERR_ECC_MASK) >>
                          MECC_MULTI_ERR_ADDR_ECC3_MULTI_ERR_ECC_SHIFT);
            info->multiErrorAddress = (base->MULTI_ERR_ADDR_ECC3 & MECC_MULTI_ERR_ADDR_ECC3_MULTI_ERR_ADDR_MASK) >>
                                      MECC_MULTI_ERR_ADDR_ECC3_MULTI_ERR_ADDR_SHIFT;
            info->multiErrorDataLow  = base->MULTI_ERR_DATA_LOW3;
            info->multiErrorDataHigh = base->MULTI_ERR_DATA_HIGH3;
            break;

        default:
            status = kStatus_MECC_BankMiss;
            break;
    }

    return status;
}
