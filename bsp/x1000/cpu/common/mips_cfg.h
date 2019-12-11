/*
 * File      : mips_cfg.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
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
 * Change Logs:
 * Date           Author       Notes
 * 2016Äê9ÔÂ10ÈÕ     Urey         the first version
 */

#ifndef _MIPS_CFG_H_
#define _MIPS_CFG_H_

#ifndef __ASSEMBLY__
#include <stdint.h>
typedef struct mips32_core_cfg
{
    uint16_t icache_line_size;
//    uint16_t icache_lines_per_way;
//    uint16_t icache_ways;
    uint16_t icache_size;
    uint16_t dcache_line_size;
//    uint16_t dcache_lines_per_way;
//    uint16_t dcache_ways;
    uint16_t dcache_size;

    uint16_t max_tlb_entries;	/* number of tlb entry */
} mips32_core_cfg_t;

extern mips32_core_cfg_t g_mips_core;

#endif /* __ASSEMBLY__ */

#endif /* _MIPS_CFG_H_ */
