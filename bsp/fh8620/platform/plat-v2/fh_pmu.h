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
 
#ifndef FH_PMU_H_
#define FH_PMU_H_

#include <rtdef.h>

#define     REG_PMU_CHIP_ID             (0x000)
#define     REG_PMU_IP_VER              (0x004)
#define     REG_PMU_FW_VER              (0x008)
#define     REG_PMU_SYS_CTRL            (0x00c)
#define     REG_PMU_PLL0_CTRL           (0x010)
#define     REG_PMU_PLL1_CTRL           (0x014)
#define     REG_PMU_ARC_CLK_GATE        (0x018)
#define     REG_PMU_CLK_GATE        	(0x01c)
#define     REG_PMU_CLK_SEL             (0x020)
#define     REG_PMU_CLK_DIV0            (0x024)
#define     REG_PMU_CLK_DIV1            (0x028)
#define     REG_PMU_CLK_DIV2            (0x02c)
#define     REG_PMU_CLK_DIV3            (0x030)
#define     REG_PMU_CLK_DIV4            (0x034)
#define     REG_PMU_CLK_DIV5            (0x038)
#define     REG_PMU_CLK_DIV6            (0x03c)
#define     REG_PMU_SWRST_MAIN_CTRL     (0x040)
#define     REG_PMU_SWRST_AXI_CTRL      (0x044)
#define     REG_PMU_SWRST_AHB_CTRL      (0x048)
#define     REG_PMU_SWRST_APB_CTRL      (0x04c)
#define     REG_PMU_VDAC_CTRL           (0x050)
#define     REG_PMU_MAC_REF_CLK_CFG     (0x0a4)

int fh_pmu_read(rt_uint32_t offset,rt_uint32_t *value);
int fh_pmu_write(rt_uint32_t offset, const rt_uint32_t value);
int fh_pmu_write_mask(rt_uint32_t offset,const rt_uint32_t value, const rt_uint32_t mask);

#endif /* FH_PMU_H_ */
