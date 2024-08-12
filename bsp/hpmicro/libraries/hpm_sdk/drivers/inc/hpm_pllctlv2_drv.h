/*
 * Copyright (c) 2022-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PLLCTLV2_DRV_H
#define HPM_PLLCTLV2_DRV_H


#include "hpm_common.h"
#include "hpm_soc_feature.h"
#include "hpm_pllctlv2_regs.h"

#define PLLCTLV2_CLK_SRC_XTAL24M (0U)
#define PLLCTLV2_CLK_SRC_IRC24M (1U)

/**
 * @brief PLLCTLV2 driver APIs
 * @defgroup pllctlv2_interface PLLCTLV2 driver APIs
 * @{
 */

/**
 * @brief Check if external crystal is stable
 * @param [in] ptr PLLCTLV2 base address
 * @return true if external crystal is stable
 */
static inline bool pllctlv2_xtal_is_stable(PLLCTLV2_Type *ptr)
{
    return IS_HPM_BITMASK_SET(ptr->XTAL, PLLCTLV2_XTAL_RESPONSE_MASK);
}

/**
 * @brief Check if external crystal is enabled
 * @param [in] ptr PLLCTLV2 base address
 * @return true if external crystal is enabled
 */
static inline bool pllctlv2_xtal_is_enabled(PLLCTLV2_Type *ptr)
{
    return IS_HPM_BITMASK_SET(ptr->XTAL, PLLCTLV2_XTAL_ENABLE_MASK);
}

/**
 * @brief Set external crystal ramp-up time
 * @param [in] ptr PLLCTLV2 base address
 * @param [in] rc24m_cycles Cycles of RC24M clock
 */
static inline void pllctlv2_xtal_set_rampup_time(PLLCTLV2_Type *ptr, uint32_t rc24m_cycles)
{
    ptr->XTAL = (ptr->XTAL & ~PLLCTLV2_XTAL_RAMP_TIME_MASK) | PLLCTLV2_XTAL_RAMP_TIME_SET(rc24m_cycles);
}

/**
 * @brief Check is PLL is stable
 * @param [in] ptr PLLCTLv2 base address
 * @param [in] pll PLL index
 * @return true if PLL is stable
 */
static inline bool pllctlv2_pll_is_stable(PLLCTLV2_Type *ptr, uint8_t pll)
{
    return IS_HPM_BITMASK_SET(ptr->PLL[pll].MFI, PLLCTLV2_PLL_MFI_RESPONSE_MASK);
}

/**
 * @brief Check if PLL is enabled
 * @param [in] ptr PLLCTLV2 base address
 * @param [in] pll PLL index
 * @return true if PLL is enabled
 */
static inline bool pllctlv2_pll_is_enabled(PLLCTLV2_Type *ptr, uint8_t pll)
{
    return IS_HPM_BITMASK_SET(ptr->PLL[pll].MFI, PLLCTLV2_PLL_MFI_ENABLE_MASK);
}

/**
 * @brief Select the PLL reference clock
 * @param [in] ptr PLLCTLV2 base address
 * @param [in] pll PLL index
 * @param [in] src PLL reference lcock source
 * @arg 0 - XTAL24M
 * @arg 1 - IRC24M
 */
static inline void pllctlv2_select_reference_clock(PLLCTLV2_Type *ptr, uint8_t pll, uint8_t src)
{
    ptr->PLL[pll].CONFIG = (ptr->PLL[pll].CONFIG & PLLCTLV2_PLL_CONFIG_REFSEL_MASK) | PLLCTLV2_PLL_CONFIG_REFSEL_SET(src);
}

/**
 * @brief Enable PLL Spread Spectrum feature
 * @param [in] ptr PLLCTLV2 base address
 * @param [in] pll PLL index
 * @param [in] step Step of spread spectrum modulator
 * @param [in] stop Stop point of spread spectrum modulator
 */
void pllctlv2_enable_spread_spectrum(PLLCTLV2_Type *ptr, uint8_t pll, uint32_t step, uint32_t stop);

/**
 * @brief Disable PLL Spread spectrum
 * @param [in] ptr PLLCTLV2 base address
 * @param [in] pll PLL index
 */
static inline void pllctlv2_disable_spread_spectrum(PLLCTLV2_Type *ptr, uint8_t pll)
{
    ptr->PLL[pll].CONFIG &= ~PLLCTLV2_PLL_CONFIG_SPREAD_MASK;
}

/**
 * @brief Set PLL lock time
 * @param [in] ptr PLLCTLV2 base address
 * @param [in] pll PLL index
 * @param [in] xtal_cycles external Crystal cycles
 */
static inline void pllctlv2_set_pll_lock_time(PLLCTLV2_Type *ptr, uint8_t pll, uint32_t xtal_cycles)
{
    ptr->PLL[pll].LOCKTIME = PLLCTLV2_PLL_LOCKTIME_LOCKTIME_SET(xtal_cycles);
}

/**
 * @brief Set PLL step time
 * @param [in] ptr PLLCTLV2 base address
 * @param [in] pll PLL index
 * @param [in] xtal_cycles external Crystal cycles
 */
static inline void pllctlv2_set_pll_step_time(PLLCTLV2_Type *ptr, uint8_t pll, uint32_t xtal_cycles)
{
    ptr->PLL[pll].STEPTIME = PLLCTLV2_PLL_STEPTIME_STEPTIME_SET(xtal_cycles);
}

/**
 * @brief Set PLL Post divider
 * @param [in] ptr PLLCTLV2 base
 * @param [in] pll PLL index
 * @param [in] div_index Divider index
 * @param [in] div_value divider value, divider factor is 1 + div_value / 5
 */
void pllctlv2_set_postdiv(PLLCTLV2_Type *ptr, uint8_t pll,  uint8_t div_index, uint8_t div_value);

/**
 * @brief Set the PLL via the low-level MFI, MFD and MFN
 *        PLL frequency = REF CLOCK * (mfi + 1.0 * mfn / mfd)
 * @param [in] ptr  PLLCTLV2 base
 * @param [in] pll  PLL index
 * @param [in] mfi  MFI value
 * @param [in] mfn  MFN value
 * @retval status_invalid_argument some parameters are invalid
 * @retval status_success operation is successful
 */
hpm_stat_t pllctlv2_set_pll_with_mfi_mfn(PLLCTLV2_Type *ptr, uint8_t pll,  uint32_t mfi, uint32_t mfn);

/**
 * @brief Initialize PLL to specified frequency
 *        Note: the specified PLL clock needs to be enabled before being configured
 * @param [in] ptr PLLCTLV2 base
 * @param [in] pll PLL index
 * @param [in] freq_in_hz expected PLL frequency
 * @retval status_invalid_argument some parameters are invalid
 * @retval status_success operation is successful
 */
hpm_stat_t pllctlv2_init_pll_with_freq(PLLCTLV2_Type *ptr, uint8_t pll, uint32_t freq_in_hz);

/**
 * @brief Get the specified PLl clock frequency
 * @param [in] ptr PLLCTLV2 base
 * @param [in] pll PLL index
 * @return PLL frequency in Hz
 */
uint32_t pllctlv2_get_pll_freq_in_hz(PLLCTLV2_Type *ptr, uint8_t pll);

/**
 * @brief Get the selected PLL post divider frequency
 * @param [in] ptr PLLCTLV2 base
 * @param [in] pll PLL index
 * @param [in] div_index Post divider index
 * @return PLL frequency in Hz
 */
uint32_t pllctlv2_get_pll_postdiv_freq_in_hz(PLLCTLV2_Type *ptr, uint8_t pll, uint8_t div_index);


/**
 * @}
 */
#endif /* HPM_PLLCTLV2_DRV_H */
