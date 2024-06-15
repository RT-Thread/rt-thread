/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PLLCTL_DRV_H
#define HPM_PLLCTL_DRV_H
#include "hpm_common.h"
#include "hpm_soc_feature.h"
#include "hpm_pllctl_regs.h"

/**
 *
 * @brief PLLCTL driver APIs
 * @defgroup pllctl_interface PLLCTL driver APIs
 * @{
 */

#define PLLCTL_PLL_VCO_FREQ_MIN (375000000U)
#define PLLCTL_PLL_VCO_FREQ_MAX (2200000000U)

/*
 * @brief PLL parts with lock
 */
#define PLLCTL_PLL_LOCK_SS_RESET PLLCTL_PLL_LOCK_LOCK_SS_RSTPTR_MASK
#define PLLCTL_PLL_LOCK_REFDIV PLLCTL_PLL_LOCK_LOCK_REFDIV_MASK
#define PLLCTL_PLL_LOCK_POSTDIV1 PLLCTL_PLL_LOCK_LOCK_POSTDIV1_MASK
#define PLLCTL_PLL_LOCK_SS_SPREAD PLLCTL_PLL_LOCK_LOCK_SS_SPREAD_MASK
#define PLLCTL_PLL_LOCK_SS_DIVVAL PLLCTL_PLL_LOCK_LOCK_SS_DIVVAL_MASK
#define PLLCTL_PLL_LOCK_ALL (PLLCTL_PLL_LOCK_LOCK_SS_RSTPTR_MASK \
                            | PLLCTL_PLL_LOCK_LOCK_REFDIV_MASK \
                            | PLLCTL_PLL_LOCK_LOCK_POSTDIV1_MASK \
                            | PLLCTL_PLL_LOCK_LOCK_SS_SPREAD_MASK \
                            | PLLCTL_PLL_LOCK_LOCK_SS_DIVVAL_MASK \
                            | PLLCTL_PLL_LOCK_LOCK_SS_DIVVAL_MASK)

/*
 * @brief PLLCTL specific status
 */
enum {
    status_pllctl_not_enabled = MAKE_STATUS(status_group_pllctl, 1),
    status_pllctl_out_of_range = MAKE_STATUS(status_group_pllctl, 2),
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Unlock pll
 *
 * @param[in] ptr PLLCTL base address
 * @param[in] pll Target PLL index
 * @param[in] lock_mask Mask of PLL parts to be unlocked
 */
static inline void pllctl_pll_unlock(PLLCTL_Type *ptr, uint8_t pll, uint32_t lock_mask)
{
    ptr->PLL[pll].LOCK &= ~lock_mask;
}

/**
 * @brief   Lock pll
 *
 * @param[in] ptr PLLCTL base address
 * @param[in] pll Target PLL index
 * @param[in] lock_mask Mask of PLL parts to be locked
 */

static inline void pllctl_pll_lock(PLLCTL_Type *ptr, uint8_t pll, uint32_t lock_mask)
{
    ptr->PLL[pll].LOCK = lock_mask;
}

/**
 * @brief   Disable spread spectrum
 *
 * @param[in] ptr PLLCTL base address
 * @param[in] pll Target PLL index
 *
 * @return status_success if everything is okay
 */
static inline hpm_stat_t pllctl_pll_ss_disable(PLLCTL_Type *ptr, uint8_t pll)
{
    if (pll > (PLLCTL_SOC_PLL_MAX_COUNT - 1)) {
        return status_invalid_argument;
    }

    ptr->PLL[pll].CFG0 |= (PLLCTL_PLL_CFG0_SS_RSTPTR_MASK
                            | PLLCTL_PLL_CFG0_SS_RESET_MASK);
    ptr->PLL[pll].CFG0 |= PLLCTL_PLL_CFG0_SS_DISABLE_SSCG_MASK;
    return status_success;
}

/**
 * @brief   Power down target PLL
 *
 * @param[in] ptr PLLCTL base address
 * @param[in] pll Target PLL index
 *
 * @return status_success if everything is okay
 */
static inline hpm_stat_t pllctl_pll_powerdown(PLLCTL_Type *ptr, uint8_t pll)
{
    if (pll > (PLLCTL_SOC_PLL_MAX_COUNT - 1)) {
        return status_invalid_argument;
    }

    ptr->PLL[pll].CFG1 = (ptr->PLL[pll].CFG1 &
            ~(PLLCTL_PLL_CFG1_PLLCTRL_HW_EN_MASK | PLLCTL_PLL_CFG1_CLKEN_SW_MASK))
            | PLLCTL_PLL_CFG1_PLLPD_SW_MASK;
    return status_success;
}

/**
 * @brief   Power on target PLL
 *
 * @param[in] ptr PLLCTL base address
 * @param[in] pll Target PLL index
 *
 * @return status_success if everything is okay
 */
static inline hpm_stat_t pllctl_pll_poweron(PLLCTL_Type *ptr, uint8_t pll)
{
    uint32_t cfg;
    if (pll > (PLLCTL_SOC_PLL_MAX_COUNT - 1)) {
        return status_invalid_argument;
    }

    cfg = ptr->PLL[pll].CFG1;
    if (!(cfg & PLLCTL_PLL_CFG1_PLLPD_SW_MASK)) {
        return status_success;
    }

    if (cfg & PLLCTL_PLL_CFG1_PLLCTRL_HW_EN_MASK) {
        ptr->PLL[pll].CFG1 &= ~PLLCTL_PLL_CFG1_PLLCTRL_HW_EN_MASK;
    }

    ptr->PLL[pll].CFG1 &= ~PLLCTL_PLL_CFG1_PLLPD_SW_MASK;

    /*
     * put back to hardware mode
     */
    ptr->PLL[pll].CFG1 |= PLLCTL_PLL_CFG1_PLLCTRL_HW_EN_MASK;
    return status_success;
}

/**
 * @brief   Enable spread spectrum mode
 *
 * @param[in] ptr PLLCTL base address
 * @param[in] pll Target PLL index
 * @param[in] spread Spread spectrum depth (1-31, from 0.1% to 3.1%)
 * @param[in] div Spread spectrum divider (1-63, divide by 1 to 63)
 * @param[in] down_spread Set true if need down-spread, otherwise center-spread
 *
 * @return status_success if everything is okay
 */
static inline hpm_stat_t pllctl_pll_ss_enable(PLLCTL_Type *ptr, uint8_t pll,
                                                uint8_t spread, uint8_t div,
                                                bool down_spread)
{
    if ((pll > (PLLCTL_SOC_PLL_MAX_COUNT - 1))
            || (spread > (PLLCTL_PLL_CFG0_SS_SPREAD_MASK >> PLLCTL_PLL_CFG0_SS_SPREAD_SHIFT))
            || (div > (PLLCTL_PLL_CFG0_SS_DIVVAL_MASK >> PLLCTL_PLL_CFG0_SS_DIVVAL_SHIFT))) {
        return status_invalid_argument;
    }
    if (!(ptr->PLL[pll].CFG1 & PLLCTL_PLL_CFG1_PLLPD_SW_MASK)) {
        pllctl_pll_powerdown(ptr, pll);
    }

    ptr->PLL[pll].CFG0 &= ~(PLLCTL_PLL_CFG0_SS_RSTPTR_MASK
                            | PLLCTL_PLL_CFG0_SS_RESET_MASK);
    ptr->PLL[pll].CFG0 &= ~PLLCTL_PLL_CFG0_SS_DISABLE_SSCG_MASK;
    ptr->PLL[pll].CFG0 = (ptr->PLL[pll].CFG0
        & ~(PLLCTL_PLL_CFG0_SS_SPREAD_MASK | PLLCTL_PLL_CFG0_SS_DIVVAL_MASK))
        | PLLCTL_PLL_CFG0_SS_SPREAD_SET(spread)
        | PLLCTL_PLL_CFG0_SS_DIVVAL_SET(div)
        | PLLCTL_PLL_CFG0_SS_DOWNSPREAD_SET(down_spread);

    pllctl_pll_poweron(ptr, pll);
    return status_success;
}

/**
 * @brief   Set postdiv1 for PLL
 *
 * @param[in] ptr PLLCTL base address
 * @param[in] pll Target PLL index
 * @param[in] div Postdiv1 value (0x1~0x7)
 *
 * @return status_success if everything is okay
 */
static inline hpm_stat_t pllctl_set_postdiv1(PLLCTL_Type *ptr, uint8_t pll, uint8_t div)
{
    if ((pll > (PLLCTL_SOC_PLL_MAX_COUNT - 1))
            || (!div)
            || ((div) > (PLLCTL_PLL_CFG0_POSTDIV1_MASK >> PLLCTL_PLL_CFG0_POSTDIV1_SHIFT))) {
        return status_invalid_argument;
    }

    ptr->PLL[pll].CFG0 = ((ptr->PLL[pll].CFG0 & ~(PLLCTL_PLL_CFG0_POSTDIV1_MASK))) | PLLCTL_PLL_CFG0_POSTDIV1_SET(div);
    return status_success;
}

/**
 * @brief   Set fbdiv for PLL integer mode
 *
 * Fout = Fref/refdiv * fbdiv / postdiv1
 *
 * @param[in] ptr PLLCTL base address
 * @param[in] pll Target PLL index
 * @param[in] fbdiv Fbdiv value (0x1~0x1000)
 * @note fbdiv value can not set too large, if Fref/refdiv * fbdiv > 2GHz, it might cause irrecoverable damage to that PLL
 *
 * @return status_success if everything is okay
 */
static inline hpm_stat_t pllctl_set_fbdiv_int(PLLCTL_Type *ptr, uint8_t pll, uint16_t fbdiv)
{
    if ((pll > (PLLCTL_SOC_PLL_MAX_COUNT - 1))
            || ((fbdiv - 1) > (uint16_t)(PLLCTL_PLL_CFG2_FBDIV_INT_MASK >> PLLCTL_PLL_CFG2_FBDIV_INT_SHIFT))) {
        return status_invalid_argument;
    }

    ptr->PLL[pll].CFG2 = ((ptr->PLL[pll].CFG2 & ~(PLLCTL_PLL_CFG2_FBDIV_INT_MASK))) | PLLCTL_PLL_CFG2_FBDIV_INT_SET(fbdiv - 1);
    return status_success;
}

/**
 * @brief   Set fbdiv for PLL fraction mode
 *
 * Fout = Fref/refdive * (fbdiv + frac/2^24)/postdiv1
 *
 * @param[in] ptr PLLCTL base address
 * @param[in] pll Target PLL index
 * @param[in] fbdiv Fbdiv value (0x1~0x1000)
 * @note fbdiv value can not set too large, if Fref/refdiv * fbdiv > 2GHz, it might cause irrecoverable damage to that PLL
 *
 * @return status_success if everything is okay
 */
static inline hpm_stat_t pllctl_set_fbdiv_frac(PLLCTL_Type *ptr, uint8_t pll, uint16_t fbdiv)
{
    if ((pll > (PLLCTL_SOC_PLL_MAX_COUNT - 1))
            || ((fbdiv - 1) > (uint16_t) (PLLCTL_PLL_FREQ_FBDIV_FRAC_MASK >> PLLCTL_PLL_FREQ_FBDIV_FRAC_SHIFT))) {
        return status_invalid_argument;
    }

    ptr->PLL[pll].FREQ = (ptr->PLL[pll].FREQ & ~(PLLCTL_PLL_FREQ_FBDIV_FRAC_MASK))
                        | PLLCTL_PLL_FREQ_FBDIV_FRAC_SET(fbdiv - 1);
    return status_success;
}

/**
 * @brief   Set fraction for PLL fraction mode
 *
 * @param[in] ptr PLLCTL base address
 * @param[in] pll Target PLL index
 * @param[in] frac 24-bit fixed float point value
 *
 * @return
 */
static inline hpm_stat_t pllctl_set_frac(PLLCTL_Type *ptr, uint8_t pll, uint32_t frac)
{
    if ((pll > (PLLCTL_SOC_PLL_MAX_COUNT - 1))
            || (frac > (PLLCTL_PLL_FREQ_FRAC_MASK >> PLLCTL_PLL_FREQ_FRAC_SHIFT))) {
        return status_invalid_argument;
    }
    ptr->PLL[pll].FREQ = (ptr->PLL[pll].FREQ & ~(PLLCTL_PLL_FREQ_FRAC_MASK))
                        | PLLCTL_PLL_FREQ_FRAC_SET(frac);
    return status_success;
}

/**
 * @brief   Get PLL divx value
 *
 * @param[in] ptr PLLCTL base address
 * @param[in] pll Target PLL index
 * @param[in] div_index Target DIV to query
 *
 * @return Divider value of target DIV
 */
static inline hpm_stat_t pllctl_get_div(PLLCTL_Type *ptr, uint8_t pll, uint8_t div_index)
{
    if ((pll > (PLLCTL_SOC_PLL_MAX_COUNT - 1))
            || !(PLLCTL_SOC_PLL_HAS_DIV0(pll))) {
        return status_invalid_argument;
    }
    if (div_index) {
        return PLLCTL_PLL_DIV0_DIV_GET(ptr->PLL[pll].DIV1) + 1;
    } else {
        return PLLCTL_PLL_DIV0_DIV_GET(ptr->PLL[pll].DIV0) + 1;
    }
}

/**
 * @brief   Set divider
 *
 * @param[in] ptr PLLCTL base address
 * @param[in] pll Target PLL index
 * @param[in] div_index DIV index
 * @param[in] div Divider value (starting from 1)
 *
 * @return status_success if everything is okay
 */
static inline hpm_stat_t pllctl_set_div(PLLCTL_Type *ptr, uint8_t pll, uint8_t div_index, uint16_t div)
{
    if ((pll > (PLLCTL_SOC_PLL_MAX_COUNT - 1))
            || !(PLLCTL_SOC_PLL_HAS_DIV0(pll))
            || ((div - 1) > (uint16_t) (PLLCTL_PLL_DIV0_DIV_MASK >> PLLCTL_PLL_DIV0_DIV_SHIFT))) {
        return status_invalid_argument;
    }

    if (div_index) {
        ptr->PLL[pll].DIV1 = (ptr->PLL[pll].DIV1 & ~(PLLCTL_PLL_DIV1_DIV_MASK))
                            | PLLCTL_PLL_DIV1_DIV_SET(div - 1);
    } else {
        ptr->PLL[pll].DIV0 = (ptr->PLL[pll].DIV0 & ~(PLLCTL_PLL_DIV0_DIV_MASK))
                            | PLLCTL_PLL_DIV0_DIV_SET(div - 1);
    }
    return status_success;
}

/**
 * @brief   Check if specific PLL DIV is stable
 *
 * @param[in] ptr PLLCTL base address
 * @param[in] pll Target PLL index
 * @param[in] div_index Target DIV to check
 *
 * @return true if target PLL DIV is stable
 */
static inline bool pllctl_div_is_stable(PLLCTL_Type *ptr, uint8_t pll, uint8_t div_index)
{
    if ((pll > (PLLCTL_SOC_PLL_MAX_COUNT - 1)) || !(PLLCTL_SOC_PLL_HAS_DIV0(pll))) {
        return false;
    }
    if (div_index) {
        return ptr->PLL[pll].DIV1 & PLLCTL_PLL_DIV0_RESPONSE_MASK;
    } else {
        return ptr->PLL[pll].DIV0 & PLLCTL_PLL_DIV0_RESPONSE_MASK;
    }
}

/**
 * @brief   Check if target PLL is enabled
 *
 * @param[in] ptr PLLCTL base address
 * @param[in] pll Target PLL index
 *
 * @return true if target PLL is enabled
 */
static inline bool pllctl_pll_is_enabled(PLLCTL_Type *ptr, uint8_t pll)
{
    return (ptr->PLL[pll].STATUS & PLLCTL_PLL_STATUS_ENABLE_MASK);
}

/**
 * @brief   Check if XTAL is stable
 *
 * @param[in] ptr PLLCTL base address
 *
 * @return true if XTAL is stable
 */
static inline bool pllctl_xtal_is_stable(PLLCTL_Type *ptr)
{
    return ptr->XTAL & PLLCTL_XTAL_RESPONSE_MASK;
}

/**
 * @brief   Check if XTAL is enabled
 *
 * @param[in] ptr PLLCTL base address
 *
 * @return true if XTAL is enabled
 */
static inline bool pllctl_xtal_is_enabled(PLLCTL_Type *ptr)
{
    return ptr->XTAL & PLLCTL_XTAL_ENABLE_MASK;
}

/*
 * @brief set XTAL rampup time in cycles of IRC24M
 *
 * @param[in] ptr PLLCTL base address
 */
static inline void pllctl_xtal_set_rampup_time(PLLCTL_Type *ptr, uint32_t cycles)
{
    ptr->XTAL = (ptr->XTAL & ~PLLCTL_XTAL_RAMP_TIME_MASK) | PLLCTL_XTAL_RAMP_TIME_SET(cycles);
}

/**
 * @brief   Set pll work mode
 *
 * @param[in] ptr PLLCTL base address
 * @param[in] pll Target PLL index
 * @param[in] int_mode true: integer mode, false - fraction mode
 *
 * @return status_success if everything is okay
 */
hpm_stat_t pllctl_set_pll_work_mode(PLLCTL_Type *ptr, uint8_t pll, bool int_mode);

/**
 * @brief   Set refdiv
 *
 * @param[in] ptr PLLCTL base address
 * @param[in] pll Target PLL index
 * @param[in] div Divider value (0x1-0x3F)
 *
 * @return status_success if everything is okay
 */
hpm_stat_t pllctl_set_refdiv(PLLCTL_Type *ptr, uint8_t pll, uint8_t div);

/**
 * @brief   Initialize PLL working at integer mode with specific frequency
 *
 * @param[in] ptr PLLCTL base address
 * @param[in] pll Target PLL index
 * @param[in] freq_in_hz Target frequency, expected >= 375000000Hz
 *
 * @return status_success if everything is okay
 *
 * @note The actual frequency might be slightly different from freq_in_hz due to calculation.
 */
hpm_stat_t pllctl_init_int_pll_with_freq(PLLCTL_Type *ptr, uint8_t pll,
                                    uint32_t freq_in_hz);

/**
 * @brief   Initialize PLL working at franction mode with specific frequency
 *
 * @param[in] ptr PLLCTL base address
 * @param[in] pll Target PLL index
 * @param[in] freq_in_hz Target frequency, expected >= 375000000Hz
 *
 * @return status_success if everything is okay
 * @note The actual frequency might be slightly different from freq_in_hz due to calculation.
 */
hpm_stat_t pllctl_init_frac_pll_with_freq(PLLCTL_Type *ptr, uint8_t pll,
                                    uint32_t freq_in_hz);

/**
 * @brief   Get frequency of target PLL
 *
 * @param[in] ptr PLLCTL base address
 * @param[in] pll Target PLL index
 *
 * @return current frequency of target PLL in Hz
 */
uint32_t pllctl_get_pll_freq_in_hz(PLLCTL_Type *ptr, uint8_t pll);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_PLLCTL_DRV_H */

