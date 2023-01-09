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

#define MM_FAULT_STATUS_OK            0
#define MM_FAULT_STATUS_UNRECOVERABLE 1

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

struct rt_mm_fault_msg
{
    enum rt_mm_fault_op fault_op;
    enum rt_mm_fault_type fault_type;
    rt_size_t off;
    void *vaddr;

    struct rt_mm_fault_res response;
};

/* MMU base page fault handler, return 1 is */
int rt_mm_fault_try_fix(struct rt_mm_fault_msg *msg);

#endif /* __MM_FAULT_H__ */
