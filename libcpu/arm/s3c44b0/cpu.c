/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-09-06     XuXinming    first version
 */

#include <rtthread.h>
#include "s3c44b0.h"

/**
 * @addtogroup S3C44B0
 */
/*@{*/

/**
 * This function will enable I-Cache of CPU
 *
 */
void rt_hw_cpu_icache_enable()
{
	rt_base_t reg;

	volatile int i;
	/* flush cycle */
	for(i = 0x10002000; i < 0x10004800; i+=16)
	{
		*((int *)i)=0x0;
	}

	/*
	 *	Init cache
	 *	Non-cacheable area (everything outside RAM)
	 *	0x0000:0000 - 0x0C00:0000
	 */
	NCACHBE0 = 0xC0000000;
	NCACHBE1 = 0x00000000;

	/*
		Enable chache
	*/
	reg = SYSCFG;
	reg |= 0x00000006; /* 8kB */
	SYSCFG = reg;
}

/**
 * This function will disable I-Cache of CPU
 *
 */
void rt_hw_cpu_icache_disable()
{
	rt_base_t reg;

	reg = SYSCFG;
	reg &= ~0x00000006; /* 8kB */
	SYSCFG = reg;
}

/**
 * this function will get the status of I-Cache
 *
 */
rt_base_t rt_hw_cpu_icache_status()
{
	return 0;
}

/**
 * this function will enable D-Cache of CPU
 *
 */
void rt_hw_cpu_dcache_enable()
{
	rt_hw_cpu_icache_enable();
}

/**
 * this function will disable D-Cache of CPU
 *
 */
void rt_hw_cpu_dcache_disable()
{
	rt_hw_cpu_icache_disable();
}

/**
 * this function will get the status of D-Cache
 *
 */
rt_base_t rt_hw_cpu_dcache_status()
{
	return rt_hw_cpu_icache_status();
}

/**
 * this function will reset CPU
 *
 */
void rt_hw_cpu_reset()
{
}

/**
 * this function will shutdown CPU
 *
 */
void rt_hw_cpu_shutdown()
{
	rt_kprintf("shutdown...\n");

	while (1);
}

/*@}*/
