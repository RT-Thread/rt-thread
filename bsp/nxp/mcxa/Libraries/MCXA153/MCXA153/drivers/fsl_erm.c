/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_erm.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.erm"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to ERM bases for each instance. */
static ERM_Type *const s_ermBases[] = ERM_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to ERM clocks for each instance. */
static const clock_ip_name_t s_ermClocks[] = ERM_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t ERM_GetInstance(ERM_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_ermBases); instance++)
    {
        if (s_ermBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_ermBases));

    return instance;
}

/*!
 * brief ERM module initialization function.
 *
 * param base ERM base address.
 */
void ERM_Init(ERM_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate ERM clock. */
    CLOCK_EnableClock(s_ermClocks[ERM_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    base->CR0 = 0x00U;
#ifdef ERM_CR1_ENCIE8_MASK
    base->CR1 = 0x00U;
#endif
    base->SR0 = 0xFFFFFFFFU;
#ifdef ERM_SR1_SBC8_MASK
    base->SR1 = 0xFFFFFFFFU;
#endif
}

/*!
 * brief Deinitializes the ERM.
 *
 */
void ERM_Deinit(ERM_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate ERM clock. */
    CLOCK_DisableClock(s_ermClocks[ERM_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

uint32_t ERM_GetMemoryErrorAddr(ERM_Type *base, erm_memory_channel_t channel)
{
    uint32_t absoluteErrorAddress = 0x00U;

    switch ((uint8_t)channel)
    {
        case 0U:
            absoluteErrorAddress = base->EAR0;
            break;
#ifdef ERM_EAR1_EAR_MASK
        case 1U:
            absoluteErrorAddress = base->EAR1;
            break;
#endif
#ifdef ERM_EAR2_EAR_MASK
        case 2U:
            absoluteErrorAddress = base->EAR2;
            break;
#endif
#ifdef ERM_EAR3_EAR_MASK
        case 3U:
            absoluteErrorAddress = base->EAR3;
            break;
#endif
#ifdef ERM_EAR4_EAR_MASK
        case 4U:
            absoluteErrorAddress = base->EAR4;
            break;
#endif
#ifdef ERM_EAR5_EAR_MASK
        case 5U:
            absoluteErrorAddress = base->EAR5;
            break;
#endif
#ifdef ERM_EAR6_EAR_MASK
        case 6U:
            absoluteErrorAddress = base->EAR6;
            break;
#endif
        default:
            assert(NULL);
            break;
    }

    return absoluteErrorAddress;
}

uint32_t ERM_GetSyndrome(ERM_Type *base, erm_memory_channel_t channel)
{
    uint32_t syndrome = 0x00U;

    switch ((uint8_t)channel)
    {
        case 0U:
            syndrome = (base->SYN0 & ERM_SYN0_SYNDROME_MASK) >> ERM_SYN0_SYNDROME_SHIFT;
            break;
#ifdef ERM_SYN1_SYNDROME_MASK
        case 1U:
            syndrome = (base->SYN1 & ERM_SYN1_SYNDROME_MASK) >> ERM_SYN1_SYNDROME_SHIFT;
            break;
#endif
#ifdef ERM_SYN2_SYNDROME_MASK
        case 2U:
            syndrome = (base->SYN2 & ERM_SYN2_SYNDROME_MASK) >> ERM_SYN2_SYNDROME_SHIFT;
            break;
#endif
#ifdef ERM_SYN3_SYNDROME_MASK
        case 3U:
            syndrome = (base->SYN3 & ERM_SYN3_SYNDROME_MASK) >> ERM_SYN3_SYNDROME_SHIFT;
            break;
#endif
#ifdef ERM_SYN4_SYNDROME_MASK
        case 4U:
            syndrome = (base->SYN4 & ERM_SYN4_SYNDROME_MASK) >> ERM_SYN4_SYNDROME_SHIFT;
            break;
#endif
#ifdef ERM_SYN5_SYNDROME_MASK
        case 5U:
            syndrome = (base->SYN5 & ERM_SYN5_SYNDROME_MASK) >> ERM_SYN5_SYNDROME_SHIFT;
            break;
#endif
#ifdef ERM_SYN6_SYNDROME_MASK
        case 6U:
            syndrome = (base->SYN6 & ERM_SYN6_SYNDROME_MASK) >> ERM_SYN6_SYNDROME_SHIFT;
            break;
#endif
#ifdef ERM_SYN7_SYNDROME_MASK
        case 7U:
            syndrome = (base->SYN7 & ERM_SYN6_SYNDROME_MASK) >> ERM_SYN7_SYNDROME_SHIFT;
            break;
#endif
#ifdef ERM_SYN8_SYNDROME_MASK
        case 8U:
            syndrome = (base->SYN8 & ERM_SYN8_SYNDROME_MASK) >> ERM_SYN8_SYNDROME_SHIFT;
            break;
#endif
#ifdef ERM_SYN9_SYNDROME_MASK
        case 8U:
            syndrome = (base->SYN9 & ERM_SYN9_SYNDROME_MASK) >> ERM_SYN9_SYNDROME_SHIFT;
            break;
#endif
        default:
            assert(NULL);
            break;
    }

    return syndrome;
}

uint32_t ERM_GetErrorCount(ERM_Type *base, erm_memory_channel_t channel)
{
    uint32_t count = 0x00U;

    switch ((uint8_t)channel)
    {
        case 0U:
            count = (base->CORR_ERR_CNT0 & ERM_CORR_ERR_CNT0_COUNT_MASK) >> ERM_CORR_ERR_CNT0_COUNT_SHIFT;
            break;
#ifdef ERM_CORR_ERR_CNT1_COUNT_MASK
        case 1U:
            count = (base->CORR_ERR_CNT1 & ERM_CORR_ERR_CNT1_COUNT_MASK) >> ERM_CORR_ERR_CNT1_COUNT_SHIFT;
            break;
#endif
#ifdef ERM_CORR_ERR_CNT2_COUNT_MASK
        case 2U:
            count = (base->CORR_ERR_CNT2 & ERM_CORR_ERR_CNT2_COUNT_MASK) >> ERM_CORR_ERR_CNT2_COUNT_SHIFT;
            break;
#endif
#ifdef ERM_CORR_ERR_CNT3_COUNT_MASK
        case 3U:
            count = (base->CORR_ERR_CNT3 & ERM_CORR_ERR_CNT3_COUNT_MASK) >> ERM_CORR_ERR_CNT3_COUNT_SHIFT;
            break;
#endif
#ifdef ERM_CORR_ERR_CNT4_COUNT_MASK
        case 4U:
            count = (base->CORR_ERR_CNT4 & ERM_CORR_ERR_CNT4_COUNT_MASK) >> ERM_CORR_ERR_CNT4_COUNT_SHIFT;
            break;
#endif
#ifdef ERM_CORR_ERR_CNT5_COUNT_MASK
        case 5U:
            count = (base->CORR_ERR_CNT5 & ERM_CORR_ERR_CNT5_COUNT_MASK) >> ERM_CORR_ERR_CNT5_COUNT_SHIFT;
            break;
#endif
#ifdef ERM_CORR_ERR_CNT6_COUNT_MASK
        case 6U:
            count = (base->CORR_ERR_CNT6 & ERM_CORR_ERR_CNT6_COUNT_MASK) >> ERM_CORR_ERR_CNT6_COUNT_SHIFT;
            break;
#endif
#ifdef ERM_CORR_ERR_CNT7_COUNT_MASK
        case 7U:
            count = (base->CORR_ERR_CNT7 & ERM_CORR_ERR_CNT7_COUNT_MASK) >> ERM_CORR_ERR_CNT7_COUNT_SHIFT;
            break;
#endif
#ifdef ERM_CORR_ERR_CNT8_COUNT_MASK
        case 8U:
            count = (base->CORR_ERR_CNT8 & ERM_CORR_ERR_CNT8_COUNT_MASK) >> ERM_CORR_ERR_CNT8_COUNT_SHIFT;
            break;
#endif
#ifdef ERM_CORR_ERR_CNT9_COUNT_MASK
        case 9U:
            count = (base->CORR_ERR_CNT9 & ERM_CORR_ERR_CNT9_COUNT_MASK) >> ERM_CORR_ERR_CNT9_COUNT_SHIFT;
            break;
#endif
        default:
            assert(NULL);
            break;
    }

    return count;
}

void ERM_ResetErrorCount(ERM_Type *base, erm_memory_channel_t channel)
{
    switch ((uint8_t)channel)
    {
        case 0U:
            base->CORR_ERR_CNT0 = 0x00U;
            break;

#ifdef ERM_CORR_ERR_CNT1_COUNT_MASK
        case 1U:
            base->CORR_ERR_CNT1 = 0x00U;
            break;
#endif
#ifdef ERM_CORR_ERR_CNT2_COUNT_MASK
        case 2U:
            base->CORR_ERR_CNT2 = 0x00U;
            break;
#endif
#ifdef ERM_CORR_ERR_CNT3_COUNT_MASK
        case 3U:
            base->CORR_ERR_CNT3 = 0x00U;
            break;
#endif
#ifdef ERM_CORR_ERR_CNT4_COUNT_MASK
        case 4U:
            base->CORR_ERR_CNT4 = 0x00U;
            break;
#endif
#ifdef ERM_CORR_ERR_CNT5_COUNT_MASK
        case 5U:
            base->CORR_ERR_CNT5 = 0x00U;
            break;
#endif
#ifdef ERM_CORR_ERR_CNT6_COUNT_MASK
        case 6U:
            base->CORR_ERR_CNT6 = 0x00U;
            break;
#endif
#ifdef ERM_CORR_ERR_CNT6_COUNT_MASK
        case 7U:
            base->CORR_ERR_CNT7 = 0x00U;
            break;
#endif
#ifdef ERM_CORR_ERR_CNT8_COUNT_MASK
        case 8U:
            base->CORR_ERR_CNT8 = 0x00U;
            break;
#endif
#ifdef ERM_CORR_ERR_CNT9_COUNT_MASK
        case 9U:
            base->CORR_ERR_CNT9 = 0x00U;
            break;
#endif
        default:
            assert(NULL);
            break;
    }
}
