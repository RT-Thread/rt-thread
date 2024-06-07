/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-06     WangXiaoyao  the first version
 */
#ifndef __MM_FAULT_H__
#define __MM_FAULT_H__

#include <rtthread.h>
#include <stddef.h>
#include <stdint.h>

/* fast path fault handler, a page frame on kernel space is returned */
#define MM_FAULT_STATUS_OK              0
/* customized fault handler, done by using rt_varea_map_* */
#define MM_FAULT_STATUS_OK_MAPPED       1
#define MM_FAULT_STATUS_UNRECOVERABLE   4

#define MM_FAULT_FIXABLE_FALSE  0
#define MM_FAULT_FIXABLE_TRUE   1

enum rt_mm_fault_op
{
    MM_FAULT_OP_READ = 1,
    MM_FAULT_OP_WRITE,
    MM_FAULT_OP_EXECUTE,
};

enum rt_mm_fault_type
{
    /**
     * Occurs when an instruction attempts to access a memory address that it
     * does not have R/W/X permission to access
     */
    MM_FAULT_TYPE_RWX_PERM,

    /* Without privileges to access (e.g. user accessing kernel) */
    MM_FAULT_TYPE_NO_PRIVILEGES,

    /**
     * Occurs when a load or store instruction accesses a virtual memory
     * address that is not currently mapped to a physical memory page
     */
    MM_FAULT_TYPE_PAGE_FAULT,

    /**
     * Occurs like a SIGBUS
     */
    MM_FAULT_TYPE_BUS_ERROR,

    /**
     * Occurs when page table walk failed, permission failed, writings on
     * non-dirty page.
     */
    MM_FAULT_TYPE_GENERIC_MMU,

    MM_FAULT_TYPE_GENERIC,
    __PRIVATE_PAGE_INSERT,
};

enum rt_mm_hint_prefetch
{
    MM_FAULT_HINT_PREFETCH_NONE,
    MM_FAULT_HINT_PREFETCH_READY,
};

struct rt_mm_fault_res
{
    void *vaddr;
    rt_size_t size;
    int status;

    /* hint for prefetch strategy */
    enum rt_mm_hint_prefetch hint;
};

struct rt_aspace_fault_msg
{
    enum rt_mm_fault_op fault_op;
    enum rt_mm_fault_type fault_type;
    rt_size_t off;
    void *fault_vaddr;

    struct rt_mm_fault_res response;
};

struct rt_aspace_io_msg
{
    /* offset in varea */
    rt_size_t off;
    /* fault address in target address space */
    void *fault_vaddr;
    /* read/write buffer in kernel space */
    void *buffer_vaddr;

    struct rt_mm_fault_res response;
};

rt_inline void rt_mm_fault_res_init(struct rt_mm_fault_res *res)
{
    res->vaddr = RT_NULL;
    res->size = 0;
    res->hint = MM_FAULT_HINT_PREFETCH_NONE;
    res->status = MM_FAULT_STATUS_UNRECOVERABLE;
}

rt_inline void rt_mm_io_msg_init(struct rt_aspace_io_msg *io, rt_size_t off, void *fault_vaddr, void *buffer_vaddr)
{
    io->off = off;
    io->fault_vaddr = fault_vaddr;
    io->buffer_vaddr = buffer_vaddr;
    rt_mm_fault_res_init(&io->response);
}

struct rt_aspace;
/* MMU base page fault handler, MM_FAULT_FIXABLE_TRUE/MM_FAULT_FIXABLE_FALSE will be returned */
int rt_aspace_fault_try_fix(struct rt_aspace *aspace, struct rt_aspace_fault_msg *msg);

#endif /* __MM_FAULT_H__ */
