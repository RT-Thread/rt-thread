/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.common_dsp"
#endif

extern uint32_t xthal_get_ccount(void);

void SDK_DelayAtLeastUs(uint32_t delayTime_us, uint32_t coreClock_Hz)
{
    uint64_t count;

    if (delayTime_us > 0U)
    {
        count = USEC_TO_COUNT(delayTime_us, coreClock_Hz);

        assert(count <= UINT32_MAX);

        /* Calculate the count ticks. */
        count += xthal_get_ccount();

        if (count > UINT32_MAX)
        {
            count -= UINT32_MAX;
            /* Wait for cyccnt overflow. */
            while (count < xthal_get_ccount())
            {
            }
        }

        /* Wait for cyccnt reach count value. */
        while (count > xthal_get_ccount())
        {
        }
    }
}
