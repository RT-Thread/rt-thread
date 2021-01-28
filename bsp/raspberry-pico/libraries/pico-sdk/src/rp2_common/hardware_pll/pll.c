/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// For MHZ definitions etc
#include "hardware/clocks.h"
#include "hardware/pll.h"

/// \tag::pll_init_calculations[]
void pll_init(PLL pll, uint32_t refdiv, uint32_t vco_freq, uint32_t post_div1, uint8_t post_div2) {
    // Turn off PLL in case it is already running
    pll->pwr = 0xffffffff;
    pll->fbdiv_int = 0;

    uint32_t ref_mhz = XOSC_MHZ / refdiv;
    pll->cs = refdiv;

    // What are we multiplying the reference clock by to get the vco freq
    // (The regs are called div, because you divide the vco output and compare it to the refclk)
    uint32_t fbdiv = vco_freq / (ref_mhz * MHZ);
/// \end::pll_init_calculations[]

    // fbdiv
    assert(fbdiv >= 16 && fbdiv <= 320);

    // Check divider ranges
    assert((post_div1 >= 1 && post_div1 <= 7) && (post_div2 >= 1 && post_div2 <= 7));

    // post_div1 should be >= post_div2
    // from appnote page 11
    // postdiv1 is designed to operate with a higher input frequency
    // than postdiv2
    assert(post_div2 <= post_div1);

/// \tag::pll_init_finish[]
    // Check that reference frequency is no greater than vco / 16
    assert(ref_mhz <= (vco_freq / 16));

    // Put calculated value into feedback divider
    pll->fbdiv_int = fbdiv;

    // Turn on PLL
    uint32_t power = PLL_PWR_PD_BITS | // Main power
                     PLL_PWR_VCOPD_BITS; // VCO Power

    hw_clear_bits(&pll->pwr, power);

    // Wait for PLL to lock
    while (!(pll->cs & PLL_CS_LOCK_BITS)) tight_loop_contents();

    // Set up post dividers - div1 feeds into div2 so if div1 is 5 and div2 is 2 then you get a divide by 10
    uint32_t pdiv = (post_div1 << PLL_PRIM_POSTDIV1_LSB) |
                    (post_div2 << PLL_PRIM_POSTDIV2_LSB);
    pll->prim = pdiv;

    // Turn on post divider
    hw_clear_bits(&pll->pwr, PLL_PWR_POSTDIVPD_BITS);
/// \end::pll_init_finish[]
}

void pll_deinit(PLL pll) {
    // todo: Make sure there are no sources running from this pll?
    pll->pwr = PLL_PWR_BITS;
}