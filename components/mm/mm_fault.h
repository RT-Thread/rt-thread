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

struct rt_mm_fault_res
{
    void *vaddr;
    rt_size_t size;
    int status;
};

enum rt_mm_fault_op
{
    MM_FAULT_OP_READ = 1,
    MM_FAULT_OP_WRITE,
    MM_FAULT_OP_EXECUTE,
};

enum rt_mm_fault_type
{
    MM_FAULT_TYPE_ACCESS_FAULT,
    MM_FAULT_TYPE_PAGE_FAULT,
    MM_FAULT_TYPE_BUS_ERROR,
    MM_FAULT_TYPE_GENERIC,
};

struct rt_aspace_fault_msg
{
    enum rt_mm_fault_op fault_op;
    enum rt_mm_fault_type fault_type;
    rt_size_t off;
    void *fault_vaddr;

    struct rt_mm_fault_res response;
};

struct rt_aspace;
/* MMU base page fault handler, return 1 is fixable */
int rt_aspace_fault_try_fix(struct rt_aspace *aspace, struct rt_aspace_fault_msg *msg);

#endif /* __MM_FAULT_H__ */
