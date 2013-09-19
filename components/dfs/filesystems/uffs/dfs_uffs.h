/*
 * File      : dfs_uffs.h
 * This file is part of Device File System in RT-Thread RTOS
 * COPYRIGHT (C) 2004-2012, RT-Thread Development Team
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
 * 2012-03-30     prife        the first version
 */

#ifndef DFS_UFFS_H_
#define DFS_UFFS_H_

#include "uffs_config.h"
#include "uffs/uffs_public.h"

/* the UFFS ECC mode opitons  */
/* #define RT_CONFIG_UFFS_ECC_MODE  UFFS_ECC_HW_AUTO */
/* #define RT_CONFIG_UFFS_ECC_MODE  UFFS_ECC_SOFT */
/* #define RT_CONFIG_UFFS_ECC_MODE  UFFS_ECC_NONE */

/* enable this ,you need provide a mark_badblock/check_block funciton */
/* #define RT_UFFS_USE_CHECK_MARK_FUNCITON */

#if RT_CONFIG_UFFS_ECC_MODE == UFFS_ECC_SOFT      /* let uffs do soft ecc */
#define RT_CONFIG_UFFS_LAYOUT    UFFS_LAYOUT_UFFS /* UFFS_LAYOUT_FLASH */

#elif RT_CONFIG_UFFS_ECC_MODE == UFFS_ECC_HW_AUTO /* nand driver make ecc and do ecc correct */
#define RT_CONFIG_UFFS_LAYOUT    UFFS_LAYOUT_FLASH

#elif RT_CONFIG_UFFS_ECC_MODE == UFFS_ECC_NONE
#define RT_CONFIG_UFFS_LAYOUT    UFFS_LAYOUT_UFFS /* UFFS_LAYOUT_FLASH */

#else
#error "uffs under rt-thread do not support this ECC mode"
#endif /* RT_CONFIG_UFFS_ECC_MODE */

#if (!CONFIG_USE_STATIC_MEMORY_ALLOCATOR)  && (CONFIG_USE_SYSTEM_MEMORY_ALLOCATOR)
#define RT_UFFS_MEMORY_ALLOCATOR  1  /* use system memory allocator */
#elif (CONFIG_USE_STATIC_MEMORY_ALLOCATOR) && (!CONFIG_USE_SYSTEM_MEMORY_ALLOCATOR)
#define RT_UFFS_MEMORY_ALLOCATOR  0  /* use static memory allocator */
#else
#error "UFFS: CONFIG_USE_STATIC_MEMORY_ALLOCATOR ,CONFIG_USE_SYSTEM_MEMORY_ALLOCATOR are invalid!"
#endif

#if CONFIG_USE_STATIC_MEMORY_ALLOCATOR > 0
#error "dfs_uffs only support CONFIG_USE_SYSTEM_MEMORY_ALLOCATOR"
#endif

#if defined(CONFIG_UFFS_AUTO_LAYOUT_USE_MTD_SCHEME)
#error "dfs_uffs not support CONFIG_UFFS_AUTO_LAYOUT_USE_MTD_SCHEME"
#endif

#if (RT_CONFIG_UFFS_ECC_MODE == UFFS_ECC_HW_AUTO) && (RT_CONFIG_UFFS_LAYOUT != UFFS_LAYOUT_FLASH)
#error "when use UFFS_ECC_HW_AUTO, you must use UFFS_LAYOUT_FLASH"

#elif (RT_CONFIG_UFFS_ECC_MODE == UFFS_ECC_SOFT) && (RT_CONFIG_UFFS_LAYOUT != UFFS_LAYOUT_UFFS)
#warning "when use UFFS_ECC_SOFT, it is recommended to use UFFS_LAYOUT_UFFS"
#endif

extern const uffs_FlashOps nand_ops;

extern void uffs_setup_storage(
    struct uffs_StorageAttrSt *attr,
    struct rt_mtd_nand_device * nand);

extern int dfs_uffs_init(void);
#endif /* DFS_UFFS_H_ */
