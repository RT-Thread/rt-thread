/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#include <rthw.h>
#include <rtthread.h>
#include "fh_pmu.h"
#include "fh_def.h"
#include "fh_arch.h"

void machine_reset(void)
{
	fh_pmu_write(REG_PMU_SWRST_MAIN_CTRL, 0x7fffffff);
}

void machine_shutdown(void)
{
	while(1)
		;

}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT_ALIAS(rt_hw_cpu_reset, reset, system reset);
#endif

/*@}*/
