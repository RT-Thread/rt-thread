/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_gpc.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.gpc_1"
#endif

/*!
 * brief Enable the IRQ.
 *
 * param base GPC peripheral base address.
 * param irqId ID number of IRQ to be enabled, available range is 32-159. 0-31 is available in some platforms.
 */
void GPC_EnableIRQ(GPC_Type *base, uint32_t irqId)
{
    uint32_t irqRegNum      = irqId / 32U;
    uint32_t irqRegShiftNum = irqId % 32U;

    assert(irqRegNum <= GPC_IMR_COUNT);

#if ((defined FSL_FEATURE_GPC_HAS_IRQ_0_31) && FSL_FEATURE_GPC_HAS_IRQ_0_31)
    if (irqRegNum == GPC_IMR_COUNT)
    {
        base->IMR5 &= ~(1UL << irqRegShiftNum);
    }
    else
    {
        base->IMR[irqRegNum] &= ~(1UL << irqRegShiftNum);
    }
#else
    assert(irqRegNum > 0U);
    base->IMR[irqRegNum - 1UL] &= ~(1UL << irqRegShiftNum);
#endif /* FSL_FEATURE_GPC_HAS_IRQ_0_31 */
}

/*!
 * brief Disable the IRQ.
 *
 * param base GPC peripheral base address.
 * param irqId ID number of IRQ to be disabled, available range is 32-159. 0-31 is available in some platforms.
 */
void GPC_DisableIRQ(GPC_Type *base, uint32_t irqId)
{
    uint32_t irqRegNum      = irqId / 32U;
    uint32_t irqRegShiftNum = irqId % 32U;

    assert(irqRegNum <= GPC_IMR_COUNT);

#if ((defined FSL_FEATURE_GPC_HAS_IRQ_0_31) && FSL_FEATURE_GPC_HAS_IRQ_0_31)
    if (irqRegNum == GPC_IMR_COUNT)
    {
        base->IMR5 |= (1UL << irqRegShiftNum);
    }
    else
    {
        base->IMR[irqRegNum] |= (1UL << irqRegShiftNum);
    }
#else
    assert(irqRegNum > 0U);
    base->IMR[irqRegNum - 1UL] |= (1UL << irqRegShiftNum);
#endif /* FSL_FEATURE_GPC_HAS_IRQ_0_31 */
}

/*!
 * brief Get the IRQ/Event flag.
 *
 * param base GPC peripheral base address.
 * param irqId ID number of IRQ to be enabled, available range is 32-159. 0-31 is available in some platforms.
 * return Indicated IRQ/Event is asserted or not.
 */
bool GPC_GetIRQStatusFlag(GPC_Type *base, uint32_t irqId)
{
    uint32_t irqRegNum      = irqId / 32U;
    uint32_t irqRegShiftNum = irqId % 32U;
    uint32_t ret;

    assert(irqRegNum <= GPC_IMR_COUNT);

#if ((defined FSL_FEATURE_GPC_HAS_IRQ_0_31) && FSL_FEATURE_GPC_HAS_IRQ_0_31)
    if (irqRegNum == GPC_IMR_COUNT)
    {
        ret = base->ISR5 & (1UL << irqRegShiftNum);
    }
    else
    {
        ret = base->ISR[irqRegNum] & (1UL << irqRegShiftNum);
    }
#else
    assert(irqRegNum > 0U);
    ret = base->ISR[irqRegNum - 1UL] & (1UL << irqRegShiftNum);
#endif /* FSL_FEATURE_GPC_HAS_IRQ_0_31 */

    return (1UL << irqRegShiftNum) == ret;
}
