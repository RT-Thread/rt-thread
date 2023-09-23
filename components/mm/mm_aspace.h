/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-14     WangXiaoyao  the first version
 */
#ifndef __MM_ASPACE_H__
#define __MM_ASPACE_H__

#include <rthw.h>
#include <rtthread.h>
#include <stddef.h>

#include "avl_adpt.h"
#include "mm_fault.h"
#include "mm_flag.h"

#define MM_PAGE_SHIFT    12
#define MM_PA_TO_OFF(pa) ((uintptr_t)(pa) >> MM_PAGE_SHIFT)
#define PV_OFFSET        (rt_kmem_pvoff())

#ifndef RT_USING_SMP
typedef rt_spinlock_t mm_spinlock;

#define MM_PGTBL_LOCK_INIT(aspace)
#define MM_PGTBL_LOCK(aspace)      (rt_hw_spin_lock(&((aspace)->pgtbl_lock)))
#define MM_PGTBL_UNLOCK(aspace)    (rt_hw_spin_unlock(&((aspace)->pgtbl_lock)))

#else
typedef struct rt_spinlock mm_spinlock;

#define MM_PGTBL_LOCK_INIT(aspace) (rt_spin_lock_init(&((aspace)->pgtbl_lock)))
#define MM_PGTBL_LOCK(aspace)      (rt_spin_lock(&((aspace)->pgtbl_lock)))
#define MM_PGTBL_UNLOCK(aspace)    (rt_spin_unlock(&((aspace)->pgtbl_lock)))

#endif /* RT_USING_SMP */

struct rt_aspace;
struct rt_varea;
struct rt_mem_obj;

extern struct rt_aspace rt_kernel_space;

typedef struct rt_aspace
{
    void *start;
    rt_size_t size;

    void *page_table;
    mm_spinlock pgtbl_lock;

    struct _aspace_tree tree;
    struct rt_mutex bst_lock;

    rt_uint64_t asid;
} *rt_aspace_t;

typedef struct rt_varea
{
    void *start;
    rt_size_t size;
    rt_size_t offset;

    rt_size_t attr;
    rt_size_t flag;

    struct rt_aspace *aspace;
    struct rt_mem_obj *mem_obj;

    struct _aspace_node node;

    struct rt_page *frames;
    void *data;
} *rt_varea_t;

typedef struct rt_mm_va_hint
{
    void *limit_start;
    rt_size_t limit_range_size;

    void *prefer;
    const rt_size_t map_size;

    mm_flag_t flags;
} *rt_mm_va_hint_t;

typedef struct rt_mem_obj
{
    void (*hint_free)(rt_mm_va_hint_t hint);
    void (*on_page_fault)(struct rt_varea *varea, struct rt_aspace_fault_msg *msg);

    /* do pre open bushiness like inc a ref */
    void (*on_varea_open)(struct rt_varea *varea);
    /* do post close bushiness like def a ref */
    void (*on_varea_close)(struct rt_varea *varea);

    void (*on_page_offload)(struct rt_varea *varea, void *vaddr, rt_size_t size);

    const char *(*get_name)(rt_varea_t varea);
} *rt_mem_obj_t;

extern struct rt_mem_obj rt_mm_dummy_mapper;

enum rt_mmu_cntl
{
    MMU_CNTL_NONCACHE,
    MMU_CNTL_CACHE,
    MMU_CNTL_READONLY,
    MMU_CNTL_READWRITE,
    MMU_CNTL_DUMMY_END,
};

/**
 * @brief Lock to access page table of address space
 */
#define WR_LOCK(aspace)                                                        \
    rt_thread_self() ? rt_mutex_take(&(aspace)->bst_lock, RT_WAITING_FOREVER)  \
                     : 0
#define WR_UNLOCK(aspace)                                                      \
    rt_thread_self() ? rt_mutex_release(&(aspace)->bst_lock) : 0

#define RD_LOCK(aspace)   WR_LOCK(aspace)
#define RD_UNLOCK(aspace) WR_UNLOCK(aspace)

rt_aspace_t rt_aspace_create(void *start, rt_size_t length, void *pgtbl);

rt_err_t rt_aspace_init(rt_aspace_t aspace, void *start, rt_size_t length, void *pgtbl);

void rt_aspace_delete(rt_aspace_t aspace);

void rt_aspace_detach(rt_aspace_t aspace);

/**
 * @brief Memory Map on Virtual Address Space to Mappable Object
 * *INFO There is no restriction to use NULL address(physical/virtual).
 * Vaddr passing in addr must be page aligned. If vaddr is RT_NULL,
 * a suitable address will be chose automatically.
 *
 * @param aspace target virtual address space
 * @param addr virtual address of the mapping
 * @param length length of mapping region
 * @param attr MMU attribution
 * @param flags desired memory protection and behaviour of the mapping
 * @param mem_obj memory map backing store object
 * @param offset offset of mapping in 4KB page for mem_obj
 * @return int E_OK on success, with addr set to vaddr of mapping
 *             E_INVAL
 */
int rt_aspace_map(rt_aspace_t aspace, void **addr, rt_size_t length, rt_size_t attr,
                  mm_flag_t flags, rt_mem_obj_t mem_obj, rt_size_t offset);

/** no malloc routines call */
int rt_aspace_map_static(rt_aspace_t aspace, rt_varea_t varea, void **addr,
                         rt_size_t length, rt_size_t attr, mm_flag_t flags,
                         rt_mem_obj_t mem_obj, rt_size_t offset);

/**
 * @brief Memory Map on Virtual Address Space to Physical Memory
 *
 * @param aspace target virtual address space
 * @param hint hint of mapping va
 * @param attr MMU attribution
 * @param pa_off (physical address >> 12)
 * @param ret_va pointer to the location to store va
 * @return int E_OK on success, with ret_va set to vaddr of mapping
 *             E_INVAL
 */
int rt_aspace_map_phy(rt_aspace_t aspace, rt_mm_va_hint_t hint, rt_size_t attr,
                      rt_size_t pa_off, void **ret_va);

/** no malloc routines call */
int rt_aspace_map_phy_static(rt_aspace_t aspace, rt_varea_t varea,
                             rt_mm_va_hint_t hint, rt_size_t attr, rt_size_t pa_off,
                             void **ret_va);

/**
 * @brief Remove any mappings overlap the range [addr, addr + bytes)
 *
 * @param aspace
 * @param addr
 * @return int
 */
int rt_aspace_unmap(rt_aspace_t aspace, void *addr);

int rt_aspace_control(rt_aspace_t aspace, void *addr, enum rt_mmu_cntl cmd);

int rt_aspace_load_page(rt_aspace_t aspace, void *addr, rt_size_t npage);

int rt_aspace_offload_page(rt_aspace_t aspace, void *addr, rt_size_t npage);

int rt_aspace_traversal(rt_aspace_t aspace,
                        int (*fn)(rt_varea_t varea, void *arg), void *arg);

void rt_aspace_print_all(rt_aspace_t aspace);

/**
 * @brief Map one page to varea
 *
 * @param varea target varea
 * @param addr user address
 * @param page the page frame to be mapped
 * @return int
 */
int rt_varea_map_page(rt_varea_t varea, void *vaddr, void *page);

/**
 * @brief Unmap one page in varea
 *
 * @param varea target varea
 * @param addr user address
 * @param page the page frame to be mapped
 * @return int
 */
int rt_varea_unmap_page(rt_varea_t varea, void *vaddr);

/**
 * @brief Map a range of physical address to varea
 *
 * @warning Caller should take care of synchronization of its varea among all
 *          the map/unmap operation
 *
 * @param varea target varea
 * @param vaddr user address
 * @param paddr physical address
 * @param length map range
 * @return int
 */
int rt_varea_map_range(rt_varea_t varea, void *vaddr, void *paddr, rt_size_t length);

/**
 * @brief Unmap a range of physical address in varea
 *
 * @warning Caller should take care of synchronization of its varea among all
 *          the map/unmap operation
 *
 * @param varea target varea
 * @param vaddr user address
 * @param length map range
 * @return int
 */
int rt_varea_unmap_range(rt_varea_t varea, void *vaddr, rt_size_t length);

/**
 * @brief Insert page to page manager of varea
 * The page will be freed by varea on uninstall automatically
 *
 * @param varea target varea
 * @param page_addr the page frame to be added
 */
void rt_varea_pgmgr_insert(rt_varea_t varea, void *page_addr);

rt_ubase_t rt_kmem_pvoff(void);

void rt_kmem_pvoff_set(rt_ubase_t pvoff);

int rt_kmem_map_phy(void *va, void *pa, rt_size_t length, rt_size_t attr);

void *rt_kmem_v2p(void *vaddr);

void rt_kmem_list(void);

#endif /* __MM_ASPACE_H__ */
