#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <hal_clk.h>
#include "platform_resource.h"

u32 g_irq_no[] = {
    106,/*tcon-lcd0*/
    107,/*tcon-tv*/
    108/*dsi*/
};

u32 g_reg_base[] = {
    0x05000000,/*de0*/
    0x05460000,/*disp_if_top*/
    0x05461000,/*tcon_lcd0*/
    0x05470000,/*tcon_tv*/
    0x05450000,/*dsi0*/
};

struct clk_info_t g_clk_no[] = {
    {
        "clk_de0",
        CLK_DE0,
        CLK_PLL_PERIPH0_2X,
        RST_BUS_DE0,
        NULL,
        NULL,
        NULL,
    },
    {
        "clk_bus_de0",
        CLK_BUS_DE0,
        (hal_clk_id_t)-1,
        (hal_reset_id_t)-1,
        NULL,
        NULL,
        NULL,
    },
    {
        "clk_de1",
        CLK_DE0,
        CLK_PLL_PERIPH0_2X,
        RST_BUS_DE0,
        NULL,
        NULL,
        NULL,
    },
    {
        "clk_bus_de1",
        CLK_BUS_DE0,
        (hal_clk_id_t)-1,
        (hal_reset_id_t)-1,
        NULL,
        NULL,
        NULL,
    },
    {
        "clk_bus_dpss_top0",
        CLK_BUS_DPSS_TOP0,
        (hal_clk_id_t)(-1),/*NULL for clk_parent*/
        RST_BUS_DPSS_TOP0,
        NULL,
        NULL,
        NULL,
    },
    {
        "clk_bus_dpss_top1",
        CLK_BUS_DPSS_TOP0,
        (hal_clk_id_t)(-1),/*NULL for clk_parent*/
        RST_BUS_DPSS_TOP0,
        NULL,
        NULL,
        NULL,
    },
    {
        "clk_tcon0",
        CLK_TCON_LCD0,
        CLK_PLL_VIDEO0_4X,
        RST_BUS_TCON_LCD0,
        NULL,
        NULL,
        NULL,
    },
    {
        "clk_tcon1",
        CLK_TCON_TV,
        CLK_PLL_VIDEO0_4X,
        RST_BUS_TCON_TV,
        NULL,
        NULL,
        NULL,
    },
    {
        "clk_bus_tcon0",
        CLK_BUS_TCON_LCD0,
        (hal_clk_id_t)-1,
        (hal_reset_id_t)-1,
        NULL,
        NULL,
        NULL,
    },
    {
        "clk_bus_tcon1",
        CLK_BUS_TCON_TV,
        (hal_clk_id_t)-1,
        (hal_reset_id_t)-1,
        NULL,
        NULL,
        NULL,
    },
    {
        "clk_mipi_dsi0",
        CLK_MIPI_DSI,
        CLK_PLL_PERIPH0,
        RST_BUS_MIPI_DSI,
        NULL,
        NULL,
        NULL,
    },
    {
        "clk_bus_mipi_dsi0",
        CLK_BUS_MIPI_DSI,
        (hal_clk_id_t)-1,
        (hal_reset_id_t)-1,
        NULL,
        NULL,
        NULL,
    },
    {
        "rst_bus_lvds0",
        (hal_clk_id_t)-1,
        (hal_clk_id_t)-1,
        RST_BUS_LVDS0,
        NULL,
        NULL,
        NULL,
    },
};

u32 g_irq_no_len = sizeof(g_irq_no) / sizeof(u32);
u32 g_reg_base_len = sizeof(g_reg_base) / sizeof(u32);
u32 g_clk_no_len = sizeof(g_clk_no) / sizeof(struct clk_info_t);
