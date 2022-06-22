/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ab32vg1_hal.h"

#ifdef HAL_RCU_MODULE_ENABLED

void hal_rcu_periph_clk_enable(uint32_t periph)
{
    if (periph <= RCU_TMR2) {
        CLKGAT0 |= BIT(periph);
    } else if (periph <= RCU_SPI1) {
        CLKGAT1 |= BIT(periph - RCU_FMAMFDT);
    }
}

void hal_rcu_periph_clk_disable(uint32_t periph)
{
    if (periph <= RCU_TMR2) {
        CLKGAT0 &= ~BIT(periph);
    } else if (periph <= RCU_SPI1) {
        CLKGAT1 &= ~BIT(periph - RCU_FMAMFDT);
    }
}

#endif
