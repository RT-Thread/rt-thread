/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
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
