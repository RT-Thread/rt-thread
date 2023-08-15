/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_SDXC_SOC_DRV_H
#define HPM_SDXC_SOC_DRV_H

#include "hpm_soc.h"
#include "hpm_sdxc_regs.h"

#if defined(__cplusplus)
extern "C" {
#endif


/**
 * @brief Wait at least 74 clocks until card is ready to receive the first command
 */
static inline void sdxc_wait_card_active(SDXC_Type *base)
{
    base->SYS_CTRL |= SDXC_SYS_CTRL_SD_CLK_EN_MASK;

    while (!IS_HPM_BITMASK_SET(base->SYS_CTRL, SDXC_SYS_CTRL_SD_CLK_EN_MASK)) {
    }
    /*
     * Assume that the BUS clock is 200MHz, while in the identification state, the SD clock is 400KHz.
     *  - Reading the register costs about 5ns in best case, hence the loop should be (74 / 400KHz) * 1000000000 / 5
     *  - For robustness, use 50000 here
     */
    for (volatile uint32_t i = 0; i < 50000U; i++) {
        (void) base->CAPABILITIES1;
    }
}

static inline void sdxc_enable_inverse_clock(SDXC_Type *base, bool enable)
{
    volatile uint32_t *reg = (base == HPM_SDXC0) ? &HPM_CONCTL->CTRL4 : &HPM_CONCTL->CTRL5;
    if (enable) {
        *reg |= (1UL << 28);
    } else {
        *reg &= ~(1UL << 28);
    }
}

static inline bool sdxc_is_inverse_clock_enabled(SDXC_Type *base)
{
    volatile uint32_t *reg = (base == HPM_SDXC0) ? &HPM_CONCTL->CTRL4 : &HPM_CONCTL->CTRL5;
    return ((*reg) & (1UL << 28)) != 0U;
}

static inline void sdxc_select_cardclk_delay_source(SDXC_Type *base, bool delay_from_pad)
{

}

static inline void sdxc_set_cardclk_delay_chain(SDXC_Type *base, uint32_t delay_chain)
{

}


#if defined(__cplusplus)
}
#endif


#endif /* HPM_SDXC_SOC_DRV_H  */
