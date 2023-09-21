/*
 * Copyright (c) 2021-2023 HPMicro
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


static inline void sdxc_enable_tm_clock(SDXC_Type *base)
{
    base->MISC_CTRL0 |= SDXC_MISC_CTRL0_TMCLK_EN_MASK;
}

static inline void sdxc_enable_freq_selection(SDXC_Type *base)
{
    base->MISC_CTRL0 |= SDXC_MISC_CTRL0_FREQ_SEL_SW_EN_MASK;
}

static inline void sdxc_disable_freq_selection(SDXC_Type *base)
{
    base->MISC_CTRL0 &= ~SDXC_MISC_CTRL0_FREQ_SEL_SW_EN_MASK;
}

static inline void sdxc_set_clock_divider(SDXC_Type *base, uint32_t div)
{
    base->MISC_CTRL0 = (base->MISC_CTRL0 & ~SDXC_MISC_CTRL0_FREQ_SEL_SW_MASK) | SDXC_MISC_CTRL0_FREQ_SEL_SW_SET(div - 1U) |
                       SDXC_MISC_CTRL0_FREQ_SEL_SW_EN_MASK;
}

static inline uint32_t sdxc_get_clock_divider(SDXC_Type *base)
{
    return (1U + SDXC_MISC_CTRL0_FREQ_SEL_SW_GET(base->MISC_CTRL0));
}

/**
 * @brief Wait at least 74 clocks until card is ready to receive the first command
 */
static inline void sdxc_wait_card_active(SDXC_Type *base)
{
    base->SYS_CTRL |= SDXC_SYS_CTRL_SD_CLK_EN_MASK;

    base->MISC_CTRL1 |= SDXC_MISC_CTRL1_CARD_ACTIVE_MASK;

    while (!IS_HPM_BITMASK_SET(base->MISC_CTRL1, SDXC_MISC_CTRL1_CARD_ACTIVE_MASK)) {
    }
}

static inline void sdxc_enable_inverse_clock(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->MISC_CTRL0 |= SDXC_MISC_CTRL0_CARDCLK_INV_EN_MASK;
    } else {
        base->MISC_CTRL0 &= ~SDXC_MISC_CTRL0_CARDCLK_INV_EN_MASK;
    }
}

static inline bool sdxc_is_inverse_clock_enabled(SDXC_Type *base)
{
    return ((base->MISC_CTRL0 & SDXC_MISC_CTRL0_CARDCLK_INV_EN_MASK) != 0U);
}

static inline void sdxc_select_cardclk_delay_source(SDXC_Type *base, bool loopback_from_pad)
{
    if (!loopback_from_pad) {
        base->MISC_CTRL0 &= ~SDXC_MISC_CTRL0_PAD_CLK_SEL_B_MASK;
    } else {
        base->MISC_CTRL0 |= SDXC_MISC_CTRL0_PAD_CLK_SEL_B_MASK;
    }
}

static inline void sdxc_set_cardclk_delay_chain(SDXC_Type *base, uint32_t number_of_delaycells)
{
    base->MISC_CTRL1 = (base->MISC_CTRL1 & ~SDXC_MISC_CTRL1_CARDCLK_DLYSEL_MASK) |
                       SDXC_MISC_CTRL1_CARDCLK_DLYSEL_SET(number_of_delaycells);
}


#if defined(__cplusplus)
}
#endif


#endif /* HPM_SDXC_SOC_DRV_H  */
