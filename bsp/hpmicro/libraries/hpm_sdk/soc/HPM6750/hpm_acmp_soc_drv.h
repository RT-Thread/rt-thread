/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef HPM_ACMP_SOC_DRV_H
#define HPM_ACMP_SOC_DRV_H

#include "hpm_soc.h"

static inline void acmp_enable_bandgap(void)
{
    uint32_t clk_div_temp;

    clk_div_temp = ADC16_CONV_CFG1_CLOCK_DIVIDER_GET(HPM_ADC3->CONV_CFG1);

    /* Set input clock divider temporarily */
    HPM_ADC3->CONV_CFG1 = (HPM_ADC3->CONV_CFG1 & ~ADC16_CONV_CFG1_CLOCK_DIVIDER_MASK)
                   | ADC16_CONV_CFG1_CLOCK_DIVIDER_SET(1);

    /* Enable ADC config clock */
    HPM_ADC3->ANA_CTRL0 |= ADC16_ANA_CTRL0_ADC_CLK_ON_MASK;

    /* Enable bandgap_en */
    HPM_ADC3->ADC16_CONFIG0 |= ADC16_ADC16_CONFIG0_BANDGAP_EN_MASK;

    /* Recover input clock divider */
    HPM_ADC3->CONV_CFG1 = (HPM_ADC3->CONV_CFG1 & ~ADC16_CONV_CFG1_CLOCK_DIVIDER_MASK)
                   | ADC16_CONV_CFG1_CLOCK_DIVIDER_SET(clk_div_temp);

    /* Disable ADC config clock */
    HPM_ADC3->ANA_CTRL0 &= ~ADC16_ANA_CTRL0_ADC_CLK_ON_MASK;
}

#endif /* HPM_ACMP_SOC_DRV_H */