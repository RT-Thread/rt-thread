/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-28     Jesven       first version
 * 2021-02-12     lizhirui     add 64-bit support for lwp_brk
 */
#ifndef  __LWP_USER_MM_H__
#define  __LWP_USER_MM_H__

#include <rthw.h>
#include <rtthread.h>

#ifdef ARCH_MM_MMU
#include <lwp.h>
#include <mmu.h>
#include <mm_aspace.h>
#include <mm_fault.h>
#include <mm_page.h>

#ifdef __cplusplus
extern "C" {
#endif

int lwp_user_space_init(struct rt_lwp *lwp, rt_bool_t is_fork);
void lwp_unmap_user_space(struct rt_lwp *lwp);

int lwp_unmap_user(struct rt_lwp *lwp, void *va);
void *lwp_map_user(struct rt_lwp *lwp, void *map_va, size_t map_size, rt_bool_t text);

void *lwp_map_user_phy(struct rt_lwp *lwp, void *map_va, void *map_pa, size_t map_size, rt_bool_t cached);
int lwp_unmap_user_phy(struct rt_lwp *lwp, void *va);

rt_base_t lwp_brk(void *addr);
void* lwp_mmap2(void *addr, size_t length, int prot, int flags, int fd, off_t pgoffset);
int lwp_munmap(void *addr);

size_t lwp_get_from_user(void *dst, void *src, size_t size);
size_t lwp_put_to_user(void *dst, void *src, size_t size);
int lwp_user_accessable(void *addr, size_t size);

size_t lwp_data_get(struct rt_lwp *lwp, void *dst, void *src, size_t size);
size_t lwp_data_put(struct rt_lwp *lwp, void *dst, void *src, size_t size);
void lwp_data_cache_flush(struct rt_lwp *lwp, void *vaddr, size_t size);

static inline void *_lwp_v2p(struct rt_lwp *lwp, void *vaddr)
{
    return rt_hw_mmu_v2p(lwp->aspace, vaddr);
}

static inline void *lwp_v2p(struct rt_lwp *lwp, void *vaddr)
{
    RD_LOCK(lwp->aspace);
    void *paddr = _lwp_v2p(lwp, vaddr);
    RD_UNLOCK(lwp->aspace);
    return paddr;
}

#ifdef __cplusplus
}
#endif

#endif

#endif  /*__LWP_USER_MM_H__*/
