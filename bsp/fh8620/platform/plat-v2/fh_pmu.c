/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#include "rtdebug.h"
#include "arch.h"
#include "fh_pmu.h"
#include "fh_def.h"

#define FH_PMU_WRITEL(offset,value)		SET_REG((PMU_REG_BASE + offset),value)
#define FH_PMU_WRITEL_MASK(offset,value, mask)	SET_REG_M((PMU_REG_BASE + offset), value, mask)
#define FH_PMU_READL(offset)			GET_REG((PMU_REG_BASE + offset))

#define PMU_OFFSET_MAX		0x1d0

int fh_pmu_read(rt_uint32_t offset, rt_uint32_t *value)
{
	RT_ASSERT(offset < PMU_OFFSET_MAX);

	*value = FH_PMU_READL(offset);
	return 0;
}

int  fh_pmu_write(rt_uint32_t offset, const rt_uint32_t value)
{
	RT_ASSERT(offset < PMU_OFFSET_MAX);

	FH_PMU_WRITEL(offset, value);
	return 0;
}

int fh_pmu_write_mask(rt_uint32_t offset, const rt_uint32_t value,
		      const rt_uint32_t mask)
{
	RT_ASSERT(offset < PMU_OFFSET_MAX);

	FH_PMU_WRITEL_MASK(offset, value, mask);
	return 0;

}
