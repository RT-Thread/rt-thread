/*
 * dfs_uffs.h
 *
 *  Created on: 2012-3-30
 *      Author: prife
 */

#ifndef DFS_UFFS_H_
#define DFS_UFFS_H_

#include "uffs_config.h"
#include "uffs/uffs_public.h"

#define UFFS_BLOCK_MARK_SPARE_OFFSET  4    /* indicate block bad or good, offset in spare */

//#define RT_CONFIG_UFFS_ECC_MODE  UFFS_ECC_SOFT
//#define RT_CONFIG_UFFS_ECC_MODE  UFFS_ECC_NONE

/* enable this ,you need provide a mark_badblock/check_block funciton */
//#define RT_UFFS_USE_CHECK_MARK_FUNCITON

#if RT_CONFIG_UFFS_ECC_MODE == UFFS_ECC_SOFT      /* let uffs do soft ecc */

#define RT_CONFIG_UFFS_LAYOUT    UFFS_LAYOUT_UFFS /* UFFS_LAYOUT_FLASH */
#define RT_CONFIG_UFFS_ECC_SIZE  0                /* if 0, then uffs will caculate a proper ecc size */

#elif RT_CONFIG_UFFS_ECC_MODE == UFFS_ECC_HW_AUTO /* nand driver make ecc and do ecc correct */

#define RT_CONFIG_UFFS_LAYOUT    UFFS_LAYOUT_FLASH
#define RT_CONFIG_UFFS_ECC_SIZE  4                /* if 0, then uffs will caculate a proper ecc size */

#elif RT_CONFIG_UFFS_ECC_MODE == UFFS_ECC_NONE

#define RT_CONFIG_UFFS_LAYOUT    UFFS_LAYOUT_UFFS /* UFFS_LAYOUT_FLASH */
#define RT_CONFIG_UFFS_ECC_SIZE  0                /* if 0, then uffs will caculate a proper ecc size */

#else
#error "uffs under rt-thread do not support this ECC mode"
#endif

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

#endif /* DFS_UFFS_H_ */
