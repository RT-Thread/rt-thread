/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.common_riscv"
#endif

static void DelayLoop(uint32_t count)
{
    __ASM volatile(
        "    mv     a0, %0              \n"
        "loop%=:                        \n"
        "    addi   a0, a0, -1          \n"
        "    bgtz   a0, loop%=          \n"
        :
        : "r"(count)
        :);
}

void SDK_DelayAtLeastUs(uint32_t delayTime_us, uint32_t coreClock_Hz)
{
    uint64_t count;

    if (delayTime_us > 0U)
    {
        count = USEC_TO_COUNT(delayTime_us, coreClock_Hz);

        assert(count <= UINT32_MAX);

        /*
         * Add is 1 cycle.
         * Branch is 2 cycle.
         */
        count = count / 3U;

        DelayLoop((uint32_t)count);
    }
}
