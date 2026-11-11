/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-27     RTT          first version
 * 2026-09-04     CYFS         clock EXMC from PLL1R for faster SDRAM
 */

#include <board.h>

#ifdef BSP_USING_SDRAM
#include <sdram_port.h>

static void _sdram_gpio_config(uint32_t gpio_periph, uint32_t gpio_af, uint32_t pins)
{
    gpio_af_set(gpio_periph, gpio_af, pins);
    gpio_mode_set(gpio_periph, GPIO_MODE_AF, GPIO_PUPD_PULLUP, pins);
    gpio_output_options_set(gpio_periph, GPIO_OTYPE_PP, GPIO_OSPEED_85MHZ, pins);
}

void rt_hw_sdram_gpio_init(void)
{
#if defined(SDRAM_USE_PLL1R_EXMC) && SDRAM_USE_PLL1R_EXMC
    if (RESET == rcu_flag_get(RCU_FLAG_PLL1STB))
    {
        rcu_pll_input_output_clock_range_config(IDX_PLL1,
                                                RCU_PLL1RNG_4M_8M,
                                                RCU_PLL1VCO_150M_420M);
        if (rcu_pll1_config(SDRAM_PLL1_PSC,
                            SDRAM_PLL1_N,
                            SDRAM_PLL1_P,
                            SDRAM_PLL1_Q,
                            SDRAM_PLL1_R) == SUCCESS)
        {
            rcu_pll_clock_output_enable(RCU_PLL1R);
            rcu_osci_on(RCU_PLL1_CK);
            if (rcu_osci_stab_wait(RCU_PLL1_CK) == SUCCESS)
            {
                rcu_exmc_clock_config(RCU_EXMCSRC_PLL1R);
            }
            else
            {
                rcu_exmc_clock_config(RCU_EXMCSRC_AHB);
            }
        }
        else
        {
            rcu_exmc_clock_config(RCU_EXMCSRC_AHB);
        }
    }
    else
    {
        rcu_pll_clock_output_enable(RCU_PLL1R);
        rcu_exmc_clock_config(RCU_EXMCSRC_PLL1R);
    }
#else
    rcu_exmc_clock_config(RCU_EXMCSRC_AHB);
#endif
    rcu_periph_clock_enable(RCU_EXMC);
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_GPIOE);
    rcu_periph_clock_enable(RCU_GPIOF);
    rcu_periph_clock_enable(RCU_GPIOG);
    rcu_periph_clock_enable(RCU_GPIOH);

    /* D13-D15: PA4-PA6. */
    _sdram_gpio_config(GPIOA, GPIO_AF_4, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6);

    /* A0-A1, D10-D11, A12, SDNE0 and SDNWE0. */
    _sdram_gpio_config(GPIOB, GPIO_AF_5, GPIO_PIN_0 | GPIO_PIN_1);
    _sdram_gpio_config(GPIOB, GPIO_AF_3, GPIO_PIN_2 | GPIO_PIN_6);
    _sdram_gpio_config(GPIOB, GPIO_AF_7, GPIO_PIN_3);
    _sdram_gpio_config(GPIOB, GPIO_AF_10, GPIO_PIN_7);
    _sdram_gpio_config(GPIOB, GPIO_AF_0, GPIO_PIN_10);

    /* D12 and D9. */
    _sdram_gpio_config(GPIOC, GPIO_AF_1, GPIO_PIN_0);
    _sdram_gpio_config(GPIOC, GPIO_AF_8, GPIO_PIN_2);

    /* D2-D3 and D0-D1. */
    _sdram_gpio_config(GPIOD, GPIO_AF_12,
                       GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_14 | GPIO_PIN_15);

    /* NBL0, A2, A4, D4-D5 and D8. */
    _sdram_gpio_config(GPIOE, GPIO_AF_12,
                       GPIO_PIN_0 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_11);
    _sdram_gpio_config(GPIOE, GPIO_AF_4, GPIO_PIN_2);
    _sdram_gpio_config(GPIOE, GPIO_AF_11, GPIO_PIN_4);

    /* A3, A5, NRAS and A6-A9. */
    _sdram_gpio_config(GPIOF, GPIO_AF_12,
                       GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_11 | GPIO_PIN_12 |
                       GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);

    /* A10-A11, D6-D7, BA0-BA1, CLK and NCAS. */
    _sdram_gpio_config(GPIOG, GPIO_AF_12,
                       GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 |
                       GPIO_PIN_8 | GPIO_PIN_15);
    _sdram_gpio_config(GPIOG, GPIO_AF_0, GPIO_PIN_2 | GPIO_PIN_3);

    /* SDCKE0 and NBL1. */
    _sdram_gpio_config(GPIOH, GPIO_AF_12, GPIO_PIN_2 | GPIO_PIN_7);
}

#endif /* BSP_USING_SDRAM */
