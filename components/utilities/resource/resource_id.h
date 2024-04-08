/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-25     RT-Thread    First version
 * 2023-09-15     xqyjlj       perf rt_hw_interrupt_disable/enable
 */

#ifndef  RESOURCE_ID_H__
#define  RESOURCE_ID_H__

#include <rthw.h>
#include <rtthread.h>

#define RESOURCE_ID_INIT(size, pool)  {size, pool, 0, RT_NULL, RT_SPINLOCK_INIT}

typedef struct
{
    int size;
    void **_res;
    int noused;
    void **_free;
    struct rt_spinlock spinlock;
} resource_id_t;

void resource_id_init(resource_id_t *mgr, int size, void **res);
int resource_id_get(resource_id_t *mgr);
void resource_id_put(resource_id_t *mgr, int no);

#endif  /*RESOURCE_ID_H__*/
