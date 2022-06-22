/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef AB32VG1_HAL_RCU_H__
#define AB32VG1_HAL_RCU_H__

#include "ab32vg1_hal_def.h"

enum rcu_periph_type {
    RCU_ROM0 = 0,
    RCU_ROM1,
    RCU_RAM0,
    RCU_RAM1,
    RCU_RAM2,
    RCU_RAM3,
    RCU_RSV0,   /*!< reserve */
    RCU_RSV1,   /*!< reserve */
    RCU_TMR0 = 8,
    RCU_SD0,
    RCU_UART0,
    RCU_HSUT0,
    RCU_DAC,
    RCU_SARADC,
    RCU_USB,
    RCU_FMRX,
    RCU_AUDEC,
    RCU_PORT,
    RCU_MBIST,
    RCU_SPI0,
    RCU_UART1 = 21,
    RCU_TMR1 = 24,
    RCU_TMR2 = 25,
    RCU_FMAMFDT = 26,
    RCU_FMTX,
    RCU_IRRX = 29,
    RCU_IIS,
    RCU_TMR3 = 34,
    RCU_TMR4,
    RCU_TMR5,
    RCU_UART2,
    RCU_SPI1,
};

void hal_rcu_periph_clk_enable(uint32_t periph);
void hal_rcu_periph_clk_disable(uint32_t periph);

#endif
