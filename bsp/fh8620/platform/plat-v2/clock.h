/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#ifndef TIMER_H_
#define TIMER_H_


#include <rtdef.h>


void rt_hw_clock_init(void);
void rt_hw_get_clock(void);
void rt_hw_set_dividor(rt_uint8_t hdivn, rt_uint8_t pdivn);
void rt_hw_set_clock(rt_uint8_t sdiv, rt_uint8_t pdiv, rt_uint8_t mdiv);


struct fh_clk;
/*
void fh_pmu_open(void);
void fh_pmu_close(void);
*/

#define DIFF_SDC_REFCLK_0			(0)
#define DIFF_SDC_REFCLK_90			(1)
#define DIFF_SDC_REFCLK_180			(2)
#define DIFF_SDC_REFCLK_270			(3)
#define SDC_CLK_PARA_ERROR		(0xffff0000)
#define SDC_CLK_PARA_OK			(0)


void clk_gate(struct fh_clk *p_clk);
void clk_ungate(struct fh_clk *p_clk);
struct fh_clk *clk_get(const char *name);
rt_uint32_t clk_get_rate(struct fh_clk *p_clk);
void clk_set_rate(struct fh_clk *p_clk,rt_uint32_t rate_value);
rt_uint32_t sdc_get_phase(struct fh_clk *p_clk);
rt_uint32_t sdc_set_phase(struct fh_clk *p_clk,rt_uint32_t phase);

#endif
