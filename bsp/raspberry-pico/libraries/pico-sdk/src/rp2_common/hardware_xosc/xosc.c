/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico.h"

// For frequency related definitions etc
#include "hardware/clocks.h"

#include "hardware/platform_defs.h"
#include "hardware/regs/xosc.h"
#include "hardware/xosc.h"

#if XOSC_KHZ < (1 * KHZ) || XOSC_KHZ > (50 * KHZ)
// Note: Although an external clock can be supplied up to 50 MHz, the maximum frequency the
// XOSC cell is specified to work with a crystal is less, please see the RP2040 Datasheet.
#error XOSC_KHZ must be in the range 1,000-50,000KHz i.e. 1-50MHz XOSC frequency
#endif

#define STARTUP_DELAY (((XOSC_KHZ + 128) / 256) * PICO_XOSC_STARTUP_DELAY_MULTIPLIER)

// The DELAY field in xosc_hw->startup is 14 bits wide.
#if STARTUP_DELAY >= (1 << 13)
#error PICO_XOSC_STARTUP_DELAY_MULTIPLIER is too large: XOSC STARTUP.DELAY must be < 8192
#endif

void xosc_init(void) {
    // Assumes 1-15 MHz input, checked above.
    xosc_hw->ctrl = XOSC_CTRL_FREQ_RANGE_VALUE_1_15MHZ;

    // Set xosc startup delay
    xosc_hw->startup = STARTUP_DELAY;

    // Set the enable bit now that we have set freq range and startup delay
    hw_set_bits(&xosc_hw->ctrl, XOSC_CTRL_ENABLE_VALUE_ENABLE << XOSC_CTRL_ENABLE_LSB);

    // Wait for XOSC to be stable
    while(!(xosc_hw->status & XOSC_STATUS_STABLE_BITS));
}

void xosc_disable(void) {
    uint32_t tmp = xosc_hw->ctrl;
    tmp &= (~XOSC_CTRL_ENABLE_BITS);
    tmp |= (XOSC_CTRL_ENABLE_VALUE_DISABLE << XOSC_CTRL_ENABLE_LSB);
    xosc_hw->ctrl = tmp;
    // Wait for stable to go away
    while(xosc_hw->status & XOSC_STATUS_STABLE_BITS);
}

void xosc_dormant(void) {
    // WARNING: This stops the xosc until woken up by an irq
    xosc_hw->dormant = XOSC_DORMANT_VALUE_DORMANT;
    // Wait for it to become stable once woken up
    while(!(xosc_hw->status & XOSC_STATUS_STABLE_BITS));
}
