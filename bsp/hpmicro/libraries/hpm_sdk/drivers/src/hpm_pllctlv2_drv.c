/*
 * Copyright (c) 2022-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_pllctlv2_drv.h"


#define PLLCTLV2_PLL_MFN_FACTOR (10U)                       /*!< PLLCTLV2 PLL MFN Factor */
#define PLLCTLV2_PLL_MFD_DEFAULT (240UL * 1000000UL)        /*!< PLLCTLV2 PLL Default MFD value */

#define PLLCTLV2_PLL_MFI_MIN (16U)
#define PLLCTLV2_PLL_MFI_MAX (42U)
#define PLLCTLV2_PLL_XTAL_FREQ (24000000UL)

#define PLLCTLV2_PLL_FREQ_MIN (PLLCTLV2_PLL_MFI_MIN * PLLCTLV2_PLL_XTAL_FREQ)
#define PLLCTLV2_PLL_FREQ_MAX ((PLLCTLV2_PLL_MFI_MAX + 1U) * PLLCTLV2_PLL_XTAL_FREQ)

hpm_stat_t pllctlv2_init_pll_with_freq(PLLCTLV2_Type *ptr, uint8_t pll, uint32_t freq_in_hz)
{
    hpm_stat_t status;
    if ((ptr == NULL) || (freq_in_hz < PLLCTLV2_PLL_FREQ_MIN) || (freq_in_hz > PLLCTLV2_PLL_FREQ_MAX) ||
        (pll >= PLLCTL_SOC_PLL_MAX_COUNT)) {
        status = status_invalid_argument;
    } else {
        uint32_t mfn = freq_in_hz % PLLCTLV2_PLL_XTAL_FREQ;
        uint32_t mfi = freq_in_hz / PLLCTLV2_PLL_XTAL_FREQ;

        if (PLLCTLV2_PLL_MFI_MFI_GET(ptr->PLL[pll].MFI) == mfi) {
            ptr->PLL[pll].MFI = mfi - 1U;
        }

        ptr->PLL[pll].MFI = mfi;
        /*
         * NOTE: Default MFD value is 240M
         */
        ptr->PLL[pll].MFN = mfn * PLLCTLV2_PLL_MFN_FACTOR;

        status = status_success;
    }
    return status;
}

void pllctlv2_enable_spread_spectrum(PLLCTLV2_Type *ptr, uint8_t pll, uint32_t step, uint32_t stop)
{
    /*
     * NOTE: The spread spectrum related registers cannot be configured under below conditions:
     *       1. PLL is enabled
     *       2. spread spectrum is enabled
     */
    if ((ptr != NULL) && (pll < PLLCTL_SOC_PLL_MAX_COUNT)) {

        ptr->PLL[pll].CONFIG &= ~PLLCTLV2_PLL_CONFIG_SPREAD_MASK;

        ptr->PLL[pll].SS_STEP = step;
        ptr->PLL[pll].SS_STOP = stop;

        ptr->PLL[pll].CONFIG |= PLLCTLV2_PLL_CONFIG_SPREAD_MASK;
    }
}

void pllctlv2_set_postdiv(PLLCTLV2_Type *ptr, uint8_t pll, uint8_t div_index, uint8_t div_value)
{
    if ((ptr != NULL) && (pll < PLLCTL_SOC_PLL_MAX_COUNT)) {
        ptr->PLL[pll].DIV[div_index] =
            (ptr->PLL[pll].DIV[div_index] & ~PLLCTLV2_PLL_DIV_DIV_MASK) | PLLCTLV2_PLL_DIV_DIV_SET(div_value) |
                PLLCTLV2_PLL_DIV_ENABLE_MASK;
    }
}

uint32_t pllctlv2_get_pll_freq_in_hz(PLLCTLV2_Type *ptr, uint8_t pll)
{
    uint32_t freq = 0;
    if ((ptr != NULL) && (pll < PLLCTL_SOC_PLL_MAX_COUNT)) {
        uint32_t mfi = PLLCTLV2_PLL_MFI_MFI_GET(ptr->PLL[pll].MFI);
        uint32_t mfn = PLLCTLV2_PLL_MFN_MFN_GET(ptr->PLL[pll].MFN);
        uint32_t mfd = PLLCTLV2_PLL_MFD_MFD_GET(ptr->PLL[pll].MFD);
        freq = (uint32_t) (PLLCTLV2_PLL_XTAL_FREQ * (mfi + 1.0 * mfn / mfd));
    }
    return freq;
}

uint32_t pllctlv2_get_pll_postdiv_freq_in_hz(PLLCTLV2_Type *ptr, uint8_t pll, uint8_t div_index)
{
    uint32_t postdiv_freq = 0;
    if ((ptr != NULL) && (pll < PLLCTL_SOC_PLL_MAX_COUNT)) {
        uint32_t postdiv = PLLCTLV2_PLL_DIV_DIV_GET(ptr->PLL[pll].DIV[div_index]);
        uint32_t pll_freq = pllctlv2_get_pll_freq_in_hz(ptr, pll);
        postdiv_freq = (uint32_t) (pll_freq / (1U + postdiv * 1.0 / 5U));
    }

    return postdiv_freq;
}
