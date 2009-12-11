/*
 * File      : clock.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-04-25     Yi.qiu       first version
 */

#include <rtthread.h>
#include "s3c24x0.h"

#define CONFIG_SYS_CLK_FREQ	12000000	// Fin = 12.00MHz

rt_uint32_t PCLK;
rt_uint32_t FCLK;
rt_uint32_t HCLK;
rt_uint32_t UCLK;

void rt_hw_get_clock(void)
{
	rt_uint32_t val;
	rt_uint8_t m, p, s;

	val = MPLLCON;
	m = (val>>12)&0xff;
	p = (val>>4)&0x3f;
	s = val&3;

	FCLK = ((m+8)*(CONFIG_SYS_CLK_FREQ/100)*2)/((p+2)*(1<<s))*100;

	val = CLKDIVN;
	m = (val>>1)&3;
	p = val&1;

	switch (m) {
	case 0:
		HCLK = FCLK;
		break;
	case 1:
		HCLK = FCLK>>1;
		break;
	case 2:
		if(s&2)
			HCLK = FCLK>>3;
		else
			HCLK = FCLK>>2;
		break;
	case 3:
		if(s&1)
			HCLK = FCLK/6;
		else
			HCLK = FCLK/3;
		break;
}

	if(p)
		PCLK = HCLK>>1;
	else
		PCLK = HCLK;
}

void rt_hw_set_clock(rt_uint8_t sdiv, rt_uint8_t pdiv, rt_uint8_t mdiv)
{
	MPLLCON = sdiv | pdiv<<4 | mdiv<<12;
}

void rt_hw_set_dividor(rt_uint8_t hdivn, rt_uint8_t pdivn)
{
	CLKDIVN = (hdivn<<1) | pdivn;
}

