/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __DE_CLOCK_H__
#define __DE_CLOCK_H__

#include "../include.h"
#include "de_feat.h"

enum de_clk_id {
    DE_CLK_NONE = 0,

    DE_CLK_CORE0 = 1,
    DE_CLK_CORE1 = 2,
    DE_CLK_WB = 3,
};

struct de_clk_para {
    enum de_clk_id clk_no;
    u32 div;
    u32 ahb_gate_adr;
    u32 ahb_gate_shift;
    u32 ahb_reset_adr;
    u32 ahb_reset_shift;
    u32 dram_gate_adr;
    u32 dram_gate_shift;
    u32 mod_adr;
    u32 mod_enable_shift;
    u32 mod_div_adr;
    u32 mod_div_shift;
    u32 mod_div_width;
};

extern s32 de_clk_enable(u32 clk_no);
extern s32 de_clk_disable(u32 clk_no);
extern s32 de_clk_set_reg_base(uintptr_t reg_base);
#if defined(CONFIG_ARCH_SUN50IW10)
extern s32 de1_clk_set_reg_base(uintptr_t reg_base);
#endif
#endif
