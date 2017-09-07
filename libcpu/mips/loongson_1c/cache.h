/*
 * File      : cache.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-07-09     Bernard      first version
 * 2011-08-08     lgnq         modified for LS1B
 */
#ifndef	__CACHE_H__
#define	__CACHE_H__

/*
 * Cache Operations
 */
#define Index_Invalidate_I      0x00
#define Index_Writeback_Inv_D   0x01
#define Index_Invalidate_SI     0x02
#define Index_Writeback_Inv_SD  0x03
#define Index_Load_Tag_I		0x04
#define Index_Load_Tag_D		0x05
#define Index_Load_Tag_SI		0x06
#define Index_Load_Tag_SD		0x07
#define Index_Store_Tag_I		0x08
#define Index_Store_Tag_D		0x09
#define Index_Store_Tag_SI		0x0A
#define Index_Store_Tag_SD		0x0B
#define Create_Dirty_Excl_D		0x0d
#define Create_Dirty_Excl_SD	0x0f
#define Hit_Invalidate_I		0x10
#define Hit_Invalidate_D		0x11
#define Hit_Invalidate_SI		0x12
#define Hit_Invalidate_SD		0x13
#define Fill					0x14
#define Hit_Writeback_Inv_D		0x15
/* 0x16 is unused */
#define Hit_Writeback_Inv_SD	0x17
#define Hit_Writeback_I			0x18
#define Hit_Writeback_D			0x19
/* 0x1a is unused */
#define Hit_Writeback_SD		0x1b
/* 0x1c is unused */
/* 0x1e is unused */
#define Hit_Set_Virtual_SI		0x1e
#define Hit_Set_Virtual_SD		0x1f

#endif
