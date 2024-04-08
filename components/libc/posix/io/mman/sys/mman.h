/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017/11/30     Bernard           The first version.
 * 2024/03/29     TroyMitchelle     Add comments for all macros
 */

#ifndef __SYS_MMAN_H__
#define __SYS_MMAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#define MAP_FAILED     ((void *) -1)

/* mmap flags */
#define MAP_SHARED     0x01      /**< Share the mapping with other processes. */
#define MAP_PRIVATE    0x02      /**< Create a private copy-on-write mapping. */
#define MAP_TYPE       0x0f      /**< Mask for type of mapping. */
#define MAP_FIXED      0x10      /**< Interpret addr exactly. */
#define MAP_ANON       0x20      /**< Anonymous mapping. */
#define MAP_ANONYMOUS  MAP_ANON  /**< Synonym for MAP_ANON. */
#define MAP_NORESERVE  0x4000    /**< Don't reserve swap space for this mapping. */
#define MAP_GROWSDOWN  0x0100    /**< Stack-like segment. */
#define MAP_DENYWRITE  0x0800    /**< ETXTBSY. */
#define MAP_EXECUTABLE 0x1000    /**< Mark it as an executable. */
#define MAP_LOCKED     0x2000    /**< Lock the mapping's pages. */
#define MAP_POPULATE   0x8000    /**< Populate (prefault) pagetables. */
#define MAP_NONBLOCK   0x10000   /**< Do not block on IO. */
#define MAP_STACK      0x20000   /**< Allocation is a stack segment. */
#define MAP_HUGETLB    0x40000   /**< Create a huge page mapping. */
#define MAP_FILE       0         /**< Compatibility */

/* mmap protections */
#define PROT_NONE      0         /**< No access. */
#define PROT_READ      1         /**< Page can be read. */
#define PROT_WRITE     2         /**< Page can be written. */
#define PROT_EXEC      4         /**< Page can be executed. */
#define PROT_GROWSDOWN 0x01000000/**< Extend change to start of growsdown vma (mprotect only). */
#define PROT_GROWSUP   0x02000000/**< Extend change to start of growsup vma (mprotect only). */

/* msync flags */
#define MS_ASYNC       1         /**< Perform asynchronous writes. */
#define MS_INVALIDATE  2         /**< Invalidate mappings after writing. */
#define MS_SYNC        4         /**< Perform synchronous writes. */

/* mlockall flags */
#define MCL_CURRENT    1         /**< Lock all pages which are currently mapped into the address space of the process. */
#define MCL_FUTURE     2         /**< Lock all pages which will become mapped into the address space of the process in the future. */
#define MCL_ONFAULT    4         /**< Lock all pages which are currently mapped into the address space of the process on access. */


void *mmap (void *start, size_t len, int prot, int flags, int fd, off_t off);
int munmap (void *start, size_t len);

#ifdef __cplusplus
}
#endif
#endif
