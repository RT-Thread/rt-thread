/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-06     勤为本       first version
 * 2021-02-02     michael5hzg@gmail.com       adapt to ls1b
 */


#include "rtconfig.h"
#include "ls1b_regs.h"
#include "ls1b_public.h"


// 晶振的频率
#define AHB_CLK                 (RT_OSC_CLK)
#define APB_CLK                 (AHB_CLK)

#define DIV_DC_EN			(0x1 << 31)
#define DIV_DC				(0x1f << 26)
#define DIV_CPU_EN			(0x1 << 25)
#define DIV_CPU				(0x1f << 20)
#define DIV_DDR_EN			(0x1 << 19)
#define DIV_DDR				(0x1f << 14)

#define DIV_DC_SHIFT			26
#define DIV_CPU_SHIFT			20
#define DIV_DDR_SHIFT			14


/*
 * 获取PLL频率
 * @ret PLL频率
 */
unsigned long clk_get_pll_rate(void)
{
    unsigned int ctrl;
    unsigned long pll_rate = 0;

    ctrl = reg_read_32((volatile unsigned int *)LS1B_START_FREQ);
	pll_rate = (12 + (ctrl & 0x3f)) * APB_CLK / 2
		+ ((ctrl >> 8) & 0x3ff) * APB_CLK / 1024 / 2;

    return pll_rate;
}


/*
 * 获取CPU频率
 * @ret CPU频率
 */
unsigned long clk_get_cpu_rate(void)
{
    unsigned long pll_rate, cpu_rate;
    unsigned int ctrl;

    pll_rate = clk_get_pll_rate();
    ctrl = reg_read_32((volatile unsigned int *)LS1B_CLK_DIV_PARAM);
	cpu_rate = pll_rate / ((ctrl & DIV_CPU) >> DIV_CPU_SHIFT);

    return cpu_rate;
}


/*
 * 获取DDR频率
 * @ret DDR频率
 */
unsigned long clk_get_ddr_rate(void)
{
    unsigned long pll_rate, ddr_rate;
	unsigned int ctrl;

	pll_rate = clk_get_pll_rate();
	ctrl = reg_read_32((volatile unsigned int *)LS1B_CLK_DIV_PARAM);

	ddr_rate = pll_rate / ((ctrl & DIV_DDR) >> DIV_DDR_SHIFT);

    return ddr_rate;
}


/*
 * 获取APB频率
 * @ret APB频率
 */
unsigned long clk_get_apb_rate(void)
{
    return clk_get_ddr_rate() / 2;
}


/*
 * 获取DC频率
 * @ret DC频率
 */
unsigned long clk_get_dc_rate(void)
{
    unsigned long pll_rate, dc_rate;
    unsigned int ctrl;

    pll_rate = clk_get_pll_rate();
    ctrl = reg_read_32((volatile unsigned int *)LS1B_CLK_DIV_PARAM);

    dc_rate = pll_rate ;

    return dc_rate;
}



