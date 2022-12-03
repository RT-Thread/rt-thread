#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <hal_clk.h>
#include "platform_resource.h"

u32 g_irq_no[] = {
    94,
    95,
    77
};

u32 g_reg_base[] = {
    0x01000000,
    0x06510000,
    0x06511000,
    0x06504000,
};

struct clk_info_t g_clk_no[] = {
    {
        "clk_de0",
        HAL_CLK_PERIPH_DE,
        HAL_CLK_PLL_PERI1,
        (hal_reset_id_t)0,
        0,
        0,
        0,
    },
    {
        "clk_display_top",
        HAL_CLK_PERIPH_DISPLAY_TOP,
        HAL_CLK_SRC_HOSC24M,
        (hal_reset_id_t)0,
        0,
        0,
        0,
    },
    {
        "clk_tcon0",
        HAL_CLK_PERIPH_TCON_LCD0,
        HAL_CLK_PLL_VIDEO,
        (hal_reset_id_t)0,
        0,
        0,
        0,
    },
    {
        "clk_mipi_dsi0",
        HAL_CLK_PERIPH_MIPI_DPHY0,
        HAL_CLK_PLL_VIDEO,
        (hal_reset_id_t)0,
        0,
        0,
        0,
    },
    {
        "clk_mipi_dsi1",
        HAL_CLK_PERIPH_MIPI_HOST0,
        HAL_CLK_SRC_HOSC24M,
        (hal_reset_id_t)0,
        0,
        0,
        0,
    },
};

u32 g_irq_no_len = sizeof(g_irq_no) / sizeof(u32);
u32 g_reg_base_len = sizeof(g_reg_base) / sizeof(u32);
u32 g_clk_no_len = sizeof(g_clk_no) / sizeof(struct clk_info_t);
