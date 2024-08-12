/*
 * Copyright (c) 2021-2024 HPMicro
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
 * @brief Enable TMCLK (for Data timeout detection)
*/
static inline void sdxc_enable_tm_clock(SDXC_Type *base)
{
    volatile uint32_t *reg = (base == HPM_SDXC0) ? &HPM_CONCTL->CTRL4 : &HPM_CONCTL->CTRL5;
    (*reg) |= (1UL << 10);
}

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
    (void) base;
    (void) delay_from_pad;
}

static inline void sdxc_set_cardclk_delay_chain(SDXC_Type *base, uint32_t delay_chain)
{
    (void) base;
    volatile uint32_t *reg = (base == HPM_SDXC0) ? &HPM_CONCTL->CTRL4 : &HPM_CONCTL->CTRL5;
    *reg = (*reg & ~CONCTL_CTRL4_SDXC0_GPR_TUNING_CARD_CLK_SEL_MASK) |
           CONCTL_CTRL4_SDXC0_GPR_TUNING_CARD_CLK_SEL_SET(delay_chain);
}

static inline void sdxc_set_data_strobe_delay(SDXC_Type *base, uint32_t num_delaycells)
{
    (void) base;
    volatile uint32_t *reg = (base == HPM_SDXC0) ? &HPM_CONCTL->CTRL4 : &HPM_CONCTL->CTRL5;
    *reg = (*reg & ~CONCTL_CTRL4_SDXC0_GPR_TUNING_STROBE_SEL_MASK) |
           CONCTL_CTRL4_SDXC0_GPR_TUNING_STROBE_SEL_SET(num_delaycells);
    *reg |= CONCTL_CTRL4_SDXC0_GPR_STROBE_IN_ENABLE_MASK;
}


static inline uint32_t sdxc_get_default_strobe_delay(SDXC_Type *base)
{
    (void) base;
    return 0;
}

static inline void sdxc_set_rxclk_delay_chain(SDXC_Type *base, uint32_t num_delaycells)
{
    volatile uint32_t *reg = (base == HPM_SDXC0) ? &HPM_CONCTL->CTRL4 : &HPM_CONCTL->CTRL5;
    *reg = (*reg & ~CONCTL_CTRL4_SDXC0_GPR_CCLK_RX_DLY_SW_SEL_MASK) |
           CONCTL_CTRL4_SDXC0_GPR_CCLK_RX_DLY_SW_SEL_SET(num_delaycells);

    *reg |= CONCTL_CTRL4_SDXC0_GPR_CCLK_RX_DLY_SW_FORCE_MASK;
}

static inline uint32_t sdxc_get_default_cardclk_delay_chain(SDXC_Type *base, uint32_t clock_freq)
{
    (void) base;
    uint32_t num_delaycells = 1;
    if (clock_freq <= 52000000) {
        num_delaycells = 13;
    }
    return num_delaycells;
}

static inline bool sdxc_is_ddr50_supported(SDXC_Type *base)
{
    (void) base;
    return false;
}

#if defined(__cplusplus)
}
#endif


#endif /* HPM_SDXC_SOC_DRV_H  */
