/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-06     勤为本       first version
 */


#ifndef __LOONGSON_CLOCK_H
#define __LOONGSON_CLOCK_H



/*
 * 获取PLL频率
 * @ret PLL频率
 */
unsigned long clk_get_pll_rate(void);


/*
 * 获取CPU频率
 * @ret CPU频率
 */
unsigned long clk_get_cpu_rate(void);



/*
 * 获取DDR频率
 * @ret DDR频率
 */
unsigned long clk_get_ddr_rate(void);


/*
 * 获取APB频率
 * @ret APB频率
 */
unsigned long clk_get_apb_rate(void);


/*
 * 获取DC频率
 * @ret DC频率
 */
unsigned long clk_get_dc_rate(void);



#endif

