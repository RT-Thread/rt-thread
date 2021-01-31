/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 *  Visit http://www.goke.com to get contact with Goke.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef GK7101_H
#define GK7101_H

#ifdef __cplusplus
extern "C" {
#endif

#include <rtthread.h>



/*****************************/
/* CPU Mode                  */
/*****************************/
#define USERMODE		0x10
#define FIQMODE			0x11
#define IRQMODE			0x12
#define SVCMODE			0x13
#define ABORTMODE		0x17
#define UNDEFMODE		0x1b
#define MODEMASK		0x1f
#define NOINT			0xc0

struct rt_hw_register
{
	rt_uint32_t r0;
	rt_uint32_t r1;
	rt_uint32_t r2;
	rt_uint32_t r3;
	rt_uint32_t r4;
	rt_uint32_t r5;
	rt_uint32_t r6;
	rt_uint32_t r7;
	rt_uint32_t r8;
	rt_uint32_t r9;
	rt_uint32_t r10;
	rt_uint32_t fp;
	rt_uint32_t ip;
	rt_uint32_t sp;
	rt_uint32_t lr;
	rt_uint32_t pc;
	rt_uint32_t cpsr;
	rt_uint32_t ORIG_r0;
};

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern struct clk *clk_get(const char *id);
extern rt_uint32_t clk_get_rate(struct clk *clk);
extern void rt_hw_clock_init(void);

#ifdef __cplusplus
}
#endif

#endif

