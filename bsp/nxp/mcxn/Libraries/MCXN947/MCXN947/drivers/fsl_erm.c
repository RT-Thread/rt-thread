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
    base->CR1 = 0x00U;
    base->SR0 = 0xFFFFFFFFU;
    base->SR1 = 0xFFFFFFFFU;
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

    switch (channel)
    {
        case kERM_MemoryChannelRAMX:
            /* Total RAMX size: 96KB
                     RAMX0: 32KB(0x04000000 ~ 0x04007FFF)
                     RAMX1: 32KB(0x04008000 ~ 0x0400FFFF)
                     RAMX2: 32KB(0x04100000 ~ 0x04017FFF)
             */
            absoluteErrorAddress = base->EAR0;
            break;

        case kERM_MemoryChannelRAMA:
            /* Total RAMA size: 32KB
                     RAMA0: 8KB(0x20000000 ~ 0x20001FFF)
                     RAMA1: 8KB(0x20002000 ~ 0x20003FFF)
                     RAMA2: 8KB(0x20004000 ~ 0x20005FFF)
                     RAMA3: 8KB(0x20006000 ~ 0x20007FFF)
             */
            absoluteErrorAddress = base->EAR1;
            break;

        case kERM_MemoryChannelRAMB:
            /* Total RAMB size: 32KB
                     RAMB0: 32KB(0x20008000 ~ 0x2000FFFF)
             */
            absoluteErrorAddress = base->EAR2;
            break;

        case kERM_MemoryChannelRAMC:
            /* Total RAMC size: 64KB
                     RAMC0: 32KB(0x20010000 ~ 0x20017FFF)
                     RAMC0: 32KB(0x20018000 ~ 0x2001FFFF)
             */
            absoluteErrorAddress = base->EAR3;
            break;

        case kERM_MemoryChannelRAMD:
            /* Total RAMD size: 64KB
                     RAMD0: 32KB(0x20020000 ~ 0x20027FFF)
                     RAMD0: 32KB(0x20028000 ~ 0x2002FFFF)
             */
            absoluteErrorAddress = base->EAR4;
            break;

        case kERM_MemoryChannelRAME:
            /* Total RAME size: 64KB
                     RAME0: 32KB(0x20030000 ~ 0x20037FFF)
                     RAME0: 32KB(0x20038000 ~ 0x2003FFFF)
             */
            absoluteErrorAddress = base->EAR5;
            break;

        case kERM_MemoryChannelRAMF:
            /* Total RAMF size: 64KB
                     RAMF0: 32KB(0x20040000 ~ 0x20047FFF)
                     RAMF0: 32KB(0x20048000 ~ 0x2004FFFF)
             */
            absoluteErrorAddress = base->EAR6;
            break;

        default:
            assert(NULL);
            break;
    }

    return absoluteErrorAddress;
}

uint32_t ERM_GetSyndrome(ERM_Type *base, erm_memory_channel_t channel)
{
    uint32_t syndrome = 0x00U;

    switch (channel)
    {
        case kERM_MemoryChannelRAMX:
            syndrome = (base->SYN0 & ERM_SYN0_SYNDROME_MASK) >> ERM_SYN0_SYNDROME_SHIFT;
            break;

        case kERM_MemoryChannelRAMA:
            syndrome = (base->SYN1 & ERM_SYN1_SYNDROME_MASK) >> ERM_SYN1_SYNDROME_SHIFT;
            break;

        case kERM_MemoryChannelRAMB:
            syndrome = (base->SYN2 & ERM_SYN2_SYNDROME_MASK) >> ERM_SYN2_SYNDROME_SHIFT;
            break;

        case kERM_MemoryChannelRAMC:
            syndrome = (base->SYN3 & ERM_SYN3_SYNDROME_MASK) >> ERM_SYN3_SYNDROME_SHIFT;
            break;

        case kERM_MemoryChannelRAMD:
            syndrome = (base->SYN4 & ERM_SYN4_SYNDROME_MASK) >> ERM_SYN4_SYNDROME_SHIFT;
            break;

        case kERM_MemoryChannelRAME:
            syndrome = (base->SYN5 & ERM_SYN5_SYNDROME_MASK) >> ERM_SYN5_SYNDROME_SHIFT;
            break;

        case kERM_MemoryChannelRAMF:
            syndrome = (base->SYN6 & ERM_SYN6_SYNDROME_MASK) >> ERM_SYN6_SYNDROME_SHIFT;
            break;

        case kERM_MemoryChannelLPCACRAM:
            assert(NULL);
            break;

        case kERM_MemoryChannelPKCRAM:
            syndrome = (base->SYN8 & ERM_SYN8_SYNDROME_MASK) >> ERM_SYN8_SYNDROME_SHIFT;
            break;

        case kERM_MemoryChannelFLASH:
            assert(NULL);
            break;

        default:
            assert(NULL);
            break;
    }

    return syndrome;
}

uint32_t ERM_GetErrorCount(ERM_Type *base, erm_memory_channel_t channel)
{
    uint32_t count = 0x00U;

    switch (channel)
    {
        case kERM_MemoryChannelRAMX:
            count = (base->CORR_ERR_CNT0 & ERM_CORR_ERR_CNT0_COUNT_MASK) >> ERM_CORR_ERR_CNT0_COUNT_SHIFT;
            break;

        case kERM_MemoryChannelRAMA:
            count = (base->CORR_ERR_CNT1 & ERM_CORR_ERR_CNT1_COUNT_MASK) >> ERM_CORR_ERR_CNT1_COUNT_SHIFT;
            break;

        case kERM_MemoryChannelRAMB:
            count = (base->CORR_ERR_CNT2 & ERM_CORR_ERR_CNT2_COUNT_MASK) >> ERM_CORR_ERR_CNT2_COUNT_SHIFT;
            break;

        case kERM_MemoryChannelRAMC:
            count = (base->CORR_ERR_CNT3 & ERM_CORR_ERR_CNT3_COUNT_MASK) >> ERM_CORR_ERR_CNT3_COUNT_SHIFT;
            break;

        case kERM_MemoryChannelRAMD:
            count = (base->CORR_ERR_CNT4 & ERM_CORR_ERR_CNT4_COUNT_MASK) >> ERM_CORR_ERR_CNT4_COUNT_SHIFT;
            break;

        case kERM_MemoryChannelRAME:
            count = (base->CORR_ERR_CNT5 & ERM_CORR_ERR_CNT5_COUNT_MASK) >> ERM_CORR_ERR_CNT5_COUNT_SHIFT;
            break;

        case kERM_MemoryChannelRAMF:
            count = (base->CORR_ERR_CNT6 & ERM_CORR_ERR_CNT6_COUNT_MASK) >> ERM_CORR_ERR_CNT6_COUNT_SHIFT;
            break;

        case kERM_MemoryChannelLPCACRAM:
            count = (base->CORR_ERR_CNT7 & ERM_CORR_ERR_CNT7_COUNT_MASK) >> ERM_CORR_ERR_CNT7_COUNT_SHIFT;
            break;

        case kERM_MemoryChannelPKCRAM:
            count = (base->CORR_ERR_CNT8 & ERM_CORR_ERR_CNT8_COUNT_MASK) >> ERM_CORR_ERR_CNT8_COUNT_SHIFT;
            break;

        case kERM_MemoryChannelFLASH:
            count = (base->CORR_ERR_CNT9 & ERM_CORR_ERR_CNT9_COUNT_MASK) >> ERM_CORR_ERR_CNT9_COUNT_SHIFT;
            break;

        default:
            assert(NULL);
            break;
    }

    return count;
}

void ERM_ResetErrorCount(ERM_Type *base, erm_memory_channel_t channel)
{
    switch (channel)
    {
        case kERM_MemoryChannelRAMX:
            base->CORR_ERR_CNT0 = 0x00U;
            break;

        case kERM_MemoryChannelRAMA:
            base->CORR_ERR_CNT1 = 0x00U;
            break;

        case kERM_MemoryChannelRAMB:
            base->CORR_ERR_CNT2 = 0x00U;
            break;

        case kERM_MemoryChannelRAMC:
            base->CORR_ERR_CNT3 = 0x00U;
            break;

        case kERM_MemoryChannelRAMD:
            base->CORR_ERR_CNT4 = 0x00U;
            break;

        case kERM_MemoryChannelRAME:
            base->CORR_ERR_CNT5 = 0x00U;
            break;

        case kERM_MemoryChannelRAMF:
            base->CORR_ERR_CNT6 = 0x00U;
            break;

        case kERM_MemoryChannelLPCACRAM:
            base->CORR_ERR_CNT7 = 0x00U;
            break;

        case kERM_MemoryChannelPKCRAM:
            base->CORR_ERR_CNT8 = 0x00U;
            break;

        case kERM_MemoryChannelFLASH:
            base->CORR_ERR_CNT9 = 0x00U;
            break;

        default:
            assert(NULL);
            break;
    }
}
