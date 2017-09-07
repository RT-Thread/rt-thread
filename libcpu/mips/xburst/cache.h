/*
 * File      : cache.h
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
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
*/

#ifndef __CACHE_H__
#define __CACHE_H__

/*
 * Cache Operations
 */
#define Index_Invalidate_I          0x00
#define Index_Writeback_Inv_D    0x01
#define Index_Invalidate_SI         0x02
#define Index_Writeback_Inv_SD  0x03
#define Index_Load_Tag_I        0x04
#define Index_Load_Tag_D        0x05
#define Index_Load_Tag_SI       0x06
#define Index_Load_Tag_SD       0x07
#define Index_Store_Tag_I       0x08
#define Index_Store_Tag_D       0x09
#define Index_Store_Tag_SI      0x0A
#define Index_Store_Tag_SD      0x0B
#define Create_Dirty_Excl_D     0x0d
#define Create_Dirty_Excl_SD        0x0f
#define Hit_Invalidate_I            0x10
#define Hit_Invalidate_D            0x11
#define Hit_Invalidate_SI           0x12
#define Hit_Invalidate_SD           0x13
#define Fill                        0x14
#define Hit_Writeback_Inv_D     0x15
/* 0x16 is unused */
#define Hit_Writeback_Inv_SD        0x17
#define Hit_Writeback_I         0x18
#define Hit_Writeback_D         0x19
/* 0x1a is unused */
#define Hit_Writeback_SD            0x1b
/* 0x1c is unused */
/* 0x1e is unused */
#define Hit_Set_Virtual_SI      0x1e
#define Hit_Set_Virtual_SD      0x1f

void rt_hw_cache_init(void);

#endif
