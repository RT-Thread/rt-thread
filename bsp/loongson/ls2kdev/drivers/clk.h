/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-06     勤为本       first version
 *
 * Copyright (c) 2020, Du Huanpeng <548708880@qq.com>
 * base on bsp/ls1cdev/libraries/ls1c_clock.h
 */

#ifndef __LOONGSON_CLK_H__
#define __LOONGSON_CLK_H__

unsigned long clk_get_pll_rate(void);
unsigned long clk_get_cpu_rate(void);
unsigned long clk_get_ddr_rate(void);
unsigned long clk_get_apb_rate(void);
unsigned long clk_get_dc_rate(void);

#endif
