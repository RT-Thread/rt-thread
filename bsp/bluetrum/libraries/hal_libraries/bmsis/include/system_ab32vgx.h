/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef SYSTEM_PROUGENGX_H__
#define SYSTEM_PROUGENGX_H__

//sys_clk configure list
enum {
    //select pll0out, PLL0 240M
    PLL0DIV_12M,
    PLL0DIV_24M,
    PLL0DIV_30M,
    PLL0DIV_48M,
    PLL0DIV_60M,
    PLL0DIV_80M,
    PLL0DIV_120M,

    //select osc26m
    OSCDIV_2M,
    OSCDIV_13M,
    OSCDIV_26M,

    //select adpll
};

//需要与sysclk_sel_tbl对应, 按时钟频率升序
enum {
    SYSCLK_2M,
    SYSCLK_12M,
    SYSCLK_13M,
    SYSCLK_24M,
    SYSCLK_26M,
    SYSCLK_30M,
    SYSCLK_48M,
    SYSCLK_60M,
    SYSCLK_80M,
    SYSCLK_120M,
};

extern uint32_t get_sysclk_nhz(void);
extern void system_init(void);
extern void set_sysclk(uint32_t sys_clk);

#endif
