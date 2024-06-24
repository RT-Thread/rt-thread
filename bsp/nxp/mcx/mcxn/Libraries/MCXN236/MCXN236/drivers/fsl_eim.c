/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_eim.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.eim"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to EIM bases for each instance. */
static EIM_Type *const s_eimBases[] = EIM_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to EIM clocks for each instance. */
static const clock_ip_name_t s_eimClocks[] = EIM_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t EIM_GetInstance(EIM_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_eimBases); instance++)
    {
        if (s_eimBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_eimBases));

    return instance;
}

/*!
 * brief EIM module initialization function.
 *
 * param base EIM base address.
 */
void EIM_Init(EIM_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate EIM clock. */
    CLOCK_EnableClock(s_eimClocks[EIM_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    base->EIMCR  = 0x00U;
    base->EICHEN = 0x00U;
}

/*!
 * brief Deinitializes the EIM.
 *
 */
void EIM_Deinit(EIM_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate EIM clock. */
    CLOCK_DisableClock(s_eimClocks[EIM_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

void EIM_InjectCheckBitError(EIM_Type *base, eim_memory_channel_t channel, uint8_t mask)
{
    switch ((uint8_t)channel)
    {
        case 0U:
            base->EICHD0_WORD0 = EIM_EICHD0_WORD0_CHKBIT_MASK(mask);
            break;
#ifdef EIM_EICHEN_EICH1EN_MASK
        case 1U:
            base->EICHD1_WORD0 = EIM_EICHD1_WORD0_CHKBIT_MASK(mask);
            break;
#endif

#ifdef EIM_EICHEN_EICH2EN_MASK
        case 2U:
            base->EICHD2_WORD0 = EIM_EICHD2_WORD0_CHKBIT_MASK(mask);
            break;
#endif
#ifdef EIM_EICHEN_EICH3EN_MASK
        case 3U:
            base->EICHD3_WORD0 = EIM_EICHD3_WORD0_CHKBIT_MASK(mask);
            break;
#endif
#ifdef EIM_EICHEN_EICH4EN_MASK
        case 4U:
            base->EICHD4_WORD0 = EIM_EICHD4_WORD0_CHKBIT_MASK(mask);
            break;
#endif
#ifdef EIM_EICHEN_EICH5EN_MASK
        case 5U:
            base->EICHD5_WORD0 = EIM_EICHD5_WORD0_CHKBIT_MASK(mask);
            break;
#endif
#ifdef EIM_EICHEN_EICH6EN_MASK
        case 6U:
            base->EICHD6_WORD0 = EIM_EICHD6_WORD0_CHKBIT_MASK(mask);
            break;
#endif
#ifdef EIM_EICHEN_EICH7EN_MASK
        case 7U:
            base->EICHD7_WORD0 = EIM_EICHD7_WORD0_CHKBIT_MASK(mask);
            break;
#endif
#ifdef EIM_EICHEN_EICH8EN_MASK
        case 8U:
            base->EICHD8_WORD0 = EIM_EICHD8_WORD0_CHKBIT_MASK(mask);
            break;
#endif
        default:
            assert(NULL);
            break;
    }
}

uint8_t EIM_GetCheckBitMask(EIM_Type *base, eim_memory_channel_t channel)
{
    uint8_t mask = 0x00U;

    switch ((uint8_t)channel)
    {
        case 0U:
            mask = (uint8_t)((base->EICHD0_WORD0 & EIM_EICHD0_WORD0_CHKBIT_MASK_MASK) >>
                             EIM_EICHD0_WORD0_CHKBIT_MASK_SHIFT);
            break;
#ifdef EIM_EICHEN_EICH1EN_MASK
        case 1U:
            mask = (uint8_t)((base->EICHD1_WORD0 & EIM_EICHD1_WORD0_CHKBIT_MASK_MASK) >>
                             EIM_EICHD1_WORD0_CHKBIT_MASK_SHIFT);
            break;
#endif
#ifdef EIM_EICHEN_EICH2EN_MASK
        case 2U:
            mask = (uint8_t)((base->EICHD2_WORD0 & EIM_EICHD2_WORD0_CHKBIT_MASK_MASK) >>
                             EIM_EICHD2_WORD0_CHKBIT_MASK_SHIFT);
            break;
#endif
#ifdef EIM_EICHEN_EICH3EN_MASK
        case 3U:
            mask = (uint8_t)((base->EICHD3_WORD0 & EIM_EICHD3_WORD0_CHKBIT_MASK_MASK) >>
                             EIM_EICHD3_WORD0_CHKBIT_MASK_SHIFT);
            break;
#endif
#ifdef EIM_EICHEN_EICH4EN_MASK
        case 4U:
            mask = (uint8_t)((base->EICHD4_WORD0 & EIM_EICHD4_WORD0_CHKBIT_MASK_MASK) >>
                             EIM_EICHD4_WORD0_CHKBIT_MASK_SHIFT);
            break;
#endif
#ifdef EIM_EICHEN_EICH5EN_MASK
        case 5U:
            mask = (uint8_t)((base->EICHD5_WORD0 & EIM_EICHD5_WORD0_CHKBIT_MASK_MASK) >>
                             EIM_EICHD5_WORD0_CHKBIT_MASK_SHIFT);
            break;
#endif
#ifdef EIM_EICHEN_EICH6EN_MASK
        case 6U:
            mask = (uint8_t)((base->EICHD6_WORD0 & EIM_EICHD6_WORD0_CHKBIT_MASK_MASK) >>
                             EIM_EICHD6_WORD0_CHKBIT_MASK_SHIFT);
            break;
#endif
#ifdef EIM_EICHEN_EICH7EN_MASK
        case 7U:
            mask = (uint8_t)((base->EICHD7_WORD0 & EIM_EICHD7_WORD0_CHKBIT_MASK_MASK) >>
                             EIM_EICHD7_WORD0_CHKBIT_MASK_SHIFT);
            break;
#endif
#ifdef EIM_EICHEN_EICH8EN_MASK
        case 8U:
            mask = (uint8_t)((base->EICHD8_WORD0 & EIM_EICHD8_WORD0_CHKBIT_MASK_MASK) >>
                             EIM_EICHD8_WORD0_CHKBIT_MASK_SHIFT);
            break;
#endif
        default:
            assert(NULL);
            break;
    }

    return mask;
}

void EIM_InjectDataBitError(EIM_Type *base, eim_memory_channel_t channel, uint8_t mask)
{
    switch ((uint8_t)channel)
    {
        case 0U:
            base->EICHD0_WORD1 = mask;
            break;
#ifdef EIM_EICHEN_EICH1EN_MASK
        case 1U:
            base->EICHD1_WORD1 = mask;
            break;
#endif
#ifdef EIM_EICHEN_EICH2EN_MASK
        case 2U:
            base->EICHD2_WORD1 = mask;
            break;
#endif
#ifdef EIM_EICHEN_EICH3EN_MASK
        case kEIM_MemoryChannelRAMC:
            base->EICHD3_WORD1 = mask;
            break;
#endif
#ifdef EIM_EICHEN_EICH4EN_MASK
        case kEIM_MemoryChannelRAMD:
            base->EICHD4_WORD1 = mask;
            break;
#endif
#ifdef EIM_EICHEN_EICH5EN_MASK
        case kEIM_MemoryChannelRAME:
            base->EICHD5_WORD1 = mask;
            break;
#endif
#ifdef EIM_EICHEN_EICH6EN_MASK
        case kEIM_MemoryChannelRAMF:
            base->EICHD6_WORD1 = mask;
            break;
#endif
#ifdef EIM_EICHEN_EICH7EN_MASK
        case kEIM_MemoryChannelLPCACRAM:
            base->EICHD7_WORD1 = mask;
            break;
#endif
#ifdef EIM_EICHEN_EICH8EN_MASK
        case kEIM_MemoryChannelPKCRAM:
            base->EICHD8_WORD1 = mask;
            break;
#endif
        default:
            assert(NULL);
            break;
    }
}

uint32_t EIM_GetDataBitMask(EIM_Type *base, eim_memory_channel_t channel)
{
    uint32_t mask = 0x00U;

    switch ((uint8_t)channel)
    {
        case 0U:
            mask = (base->EICHD0_WORD0 & EIM_EICHD0_WORD1_B0_3DATA_MASK_MASK) >> EIM_EICHD0_WORD1_B0_3DATA_MASK_SHIFT;
            break;

#ifdef EIM_EICHEN_EICH1EN_MASK
        case 1U:
            mask = (base->EICHD1_WORD0 & EIM_EICHD1_WORD1_B0_3DATA_MASK_MASK) >> EIM_EICHD1_WORD1_B0_3DATA_MASK_SHIFT;
            break;
#endif
#ifdef EIM_EICHEN_EICH2EN_MASK
        case 2U:
            mask = (base->EICHD2_WORD0 & EIM_EICHD2_WORD1_B0_3DATA_MASK_MASK) >> EIM_EICHD2_WORD1_B0_3DATA_MASK_SHIFT;
            break;
#endif
#ifdef EIM_EICHEN_EICH3EN_MASK
        case 3U:
            mask = (base->EICHD3_WORD0 & EIM_EICHD3_WORD1_B0_3DATA_MASK_MASK) >> EIM_EICHD3_WORD1_B0_3DATA_MASK_SHIFT;
            break;
#endif
#ifdef EIM_EICHEN_EICH4EN_MASK
        case 4U:
            mask = (base->EICHD4_WORD0 & EIM_EICHD4_WORD1_B0_3DATA_MASK_MASK) >> EIM_EICHD4_WORD1_B0_3DATA_MASK_SHIFT;
            break;
#endif
#ifdef EIM_EICHEN_EICH5EN_MASK
        case 5U:
            mask = (base->EICHD5_WORD0 & EIM_EICHD5_WORD1_B0_3DATA_MASK_MASK) >> EIM_EICHD5_WORD1_B0_3DATA_MASK_SHIFT;
            break;
#endif
#ifdef EIM_EICHEN_EICH6EN_MASK
        case 6U:
            mask = (base->EICHD6_WORD0 & EIM_EICHD6_WORD1_B0_3DATA_MASK_MASK) >> EIM_EICHD6_WORD1_B0_3DATA_MASK_SHIFT;
            break;
#endif
#ifdef EIM_EICHEN_EICH7EN_MASK
        case 7U:
            mask = (base->EICHD7_WORD0 & EIM_EICHD7_WORD1_B0_3DATA_MASK_MASK) >> EIM_EICHD7_WORD1_B0_3DATA_MASK_SHIFT;
            break;
#endif
#ifdef EIM_EICHEN_EICH8EN_MASK
        case 8U:
            mask = (base->EICHD8_WORD1 & EIM_EICHD8_WORD1_B0_3DATA_MASK_MASK) >> EIM_EICHD8_WORD1_B0_3DATA_MASK_SHIFT;
            break;
#endif
        default:
            assert(NULL);
            break;
    }

    return mask;
}
