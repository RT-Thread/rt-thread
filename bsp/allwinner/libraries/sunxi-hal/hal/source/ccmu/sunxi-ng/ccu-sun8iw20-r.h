/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2020 frank@allwinnertech.com
 */

#ifndef _CCU_SUN8IW20_R_H
#define _CCU_SUN8IW20_R_H

#define SUNXI_R_CCU_BASE    0x07010000
#define CLK_R_AHB       0
#define CLK_R_APB0      1
#define CLK_R_APB0_TIMER    2
#define CLK_R_APB0_TWD      3
#define CLK_R_PPU       4
#define CLK_R_APB0_IRRX     5
#define CLK_R_APB0_BUS_IRRX 6
#define CLK_R_AHB_BUS_RTC   7
#define CLK_R_APB0_CPUCFG   8

#define CLK_R_MAX_NO        CLK_R_APB0_CPUCFG
#define CLK_R_NUMBER    (CLK_R_MAX_NO + 1)

#endif /* _CCU_SUN8IW20_R_H */
