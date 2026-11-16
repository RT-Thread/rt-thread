/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <dt-bindings/reset/sun252i-f101-ccu.h>
#include <sunxi_reset.h>

/* A set reset bit releases the corresponding peripheral from reset. */
static const struct sunxi_reset_line sun252i_f101_reset_lines[] =
{
    [SUN252I_F101_RST_BUS_PLL_SSC] = { 0x0200, RT_BIT(30) },
    [SUN252I_F101_RST_MBUS] = { 0x0540, RT_BIT(30) },
    [SUN252I_F101_RST_BUS_DE] = { 0x060c, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_DI] = { 0x062c, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_G2D] = { 0x063c, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_CE] = { 0x068c, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_VE] = { 0x069c, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_DMA] = { 0x070c, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_HSTIMER] = { 0x073c, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_DBGSYS] = { 0x078c, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_PWM_BL] = { 0x0794, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_PWM] = { 0x07ac, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_DRAM_MOD] = { 0x0800, RT_BIT(30) },
    [SUN252I_F101_RST_BUS_LPSRAM] = { 0x0808, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_DRAM] = { 0x080c, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_SMHC2] = { 0x084c, RT_BIT(18) },
    [SUN252I_F101_RST_BUS_SMHC0] = { 0x084c, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_UART5] = { 0x090c, RT_BIT(21) },
    [SUN252I_F101_RST_BUS_UART4] = { 0x090c, RT_BIT(20) },
    [SUN252I_F101_RST_BUS_UART3] = { 0x090c, RT_BIT(19) },
    [SUN252I_F101_RST_BUS_UART2] = { 0x090c, RT_BIT(18) },
    [SUN252I_F101_RST_BUS_UART1] = { 0x090c, RT_BIT(17) },
    [SUN252I_F101_RST_BUS_UART0] = { 0x090c, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_TWI2] = { 0x091c, RT_BIT(18) },
    [SUN252I_F101_RST_BUS_TWI1] = { 0x091c, RT_BIT(17) },
    [SUN252I_F101_RST_BUS_TWI0] = { 0x091c, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_SPI1] = { 0x096c, RT_BIT(17) },
    [SUN252I_F101_RST_BUS_SPI0] = { 0x096c, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_SPIF] = { 0x0984, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_IRRX] = { 0x09cc, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_CAN0] = { 0x092c, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_CAN1] = { 0x092c, RT_BIT(17) },
    [SUN252I_F101_RST_BUS_GPADC] = { 0x09ec, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_THS] = { 0x09fc, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_I2S0] = { 0x0a20, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_OWA] = { 0x0a2c, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_AUDIO] = { 0x0a5c, RT_BIT(16) },
    [SUN252I_F101_RST_USB_PHY0] = { 0x0a70, RT_BIT(30) },
    [SUN252I_F101_RST_USB_OTG0] = { 0x0a8c, RT_BIT(24) },
    [SUN252I_F101_RST_USB_EHCI0] = { 0x0a8c, RT_BIT(20) },
    [SUN252I_F101_RST_USB_OHCI0] = { 0x0a8c, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_DPSS] = { 0x0abc, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_DSI] = { 0x0b4c, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_TCONLCD] = { 0x0b7c, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_LVDS0] = { 0x0bac, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_CSI] = { 0x0c1c, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_TVIN] = { 0x0c24, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_TVIN_TOP] = { 0x0c28, RT_BIT(16) },
    [SUN252I_F101_RST_BUS_TPADC] = { 0x0c5c, RT_BIT(16) },
};

const struct sunxi_reset_data sun252i_f101_reset_data =
{
    .lines = sun252i_f101_reset_lines,
    .lines_nr = RT_ARRAY_SIZE(sun252i_f101_reset_lines),
    .assert_delay_us = 2,
};
