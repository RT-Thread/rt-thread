/*
 * Copyright (c) 2021 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-12     Steven Liu   first implementation
 */

#include "rtdef.h"
#include "iomux.h"
#include "hal_base.h"

/**
 * @brief  Config iomux for M4 JTAG
 */
rt_weak void m4_jtag_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_C7 |  // M4_JTAG_TCK
                         GPIO_PIN_D0,   // M4_JTAG_TMS
                         PIN_CONFIG_MUX_FUNC2);
}

/**
 * @brief  Config iomux for UART0
 */
rt_weak void uart0_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_C7 |  // UART0_RX
                         GPIO_PIN_D0,   // UART0_TX
                         PIN_CONFIG_MUX_FUNC1);
}

/**
 * @brief  Config iomux for UART1
 */
rt_weak void uart1_m0_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_D1 |  // UART1_RX_M0
                         GPIO_PIN_D2,   // UART1_TX_M0
                         PIN_CONFIG_MUX_FUNC2);

    WRITE_REG_MASK_WE(GRF->SOC_CON5,
                      GRF_SOC_CON5_GRF_CON_UART1_IOMUX_SEL_MASK,
                      (0 << GRF_SOC_CON5_GRF_CON_UART1_IOMUX_SEL_SHIFT));
}

rt_weak void uart1_m1_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_A5 |  // UART1_RX_M1
                         GPIO_PIN_A4,   // UART1_TX_M1
                         PIN_CONFIG_MUX_FUNC2);

    WRITE_REG_MASK_WE(GRF->SOC_CON5,
                      GRF_SOC_CON5_GRF_CON_UART1_IOMUX_SEL_MASK,
                      (1 << GRF_SOC_CON5_GRF_CON_UART1_IOMUX_SEL_SHIFT));
}

rt_weak void uart1_m2_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK1,
                         GPIO_PIN_B1 |  // UART1_RX_M2
                         GPIO_PIN_B0,   // UART1_TX_M2
                         PIN_CONFIG_MUX_FUNC3);

    WRITE_REG_MASK_WE(GRF->SOC_CON5,
                      GRF_SOC_CON5_GRF_CON_UART1_IOMUX_SEL_MASK,
                      (2 << GRF_SOC_CON5_GRF_CON_UART1_IOMUX_SEL_SHIFT));
}

rt_weak void uart1_m3_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_A5,   // UART1_RX_M3
                         PIN_CONFIG_MUX_FUNC2);

    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_B1,   // UART1_TX_M3
                         PIN_CONFIG_MUX_FUNC4);

    WRITE_REG_MASK_WE(GRF->SOC_CON5,
                      GRF_SOC_CON5_GRF_CON_UART1_IOMUX_SEL_MASK,
                      (3 << GRF_SOC_CON5_GRF_CON_UART1_IOMUX_SEL_SHIFT));
}

/**
 * @brief  Config iomux for UART2
 */
rt_weak void uart2_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK1,
                         GPIO_PIN_A0 |  // UART2_RX
                         GPIO_PIN_A1 |  // UART2_TX
                         GPIO_PIN_A2 |  // UART2_CTS
                         GPIO_PIN_A3,   // UART2_RTS
                         PIN_CONFIG_MUX_FUNC4);
}

/**
 * @brief  Config iomux for RK2108
 */
rt_weak void rt_hw_iomux_config(void)
{
    uart2_iomux_config();

#ifdef M4_JTAG_ENABLE
    m4_jtag_iomux_config();
#else
    uart0_iomux_config();
#endif
}
