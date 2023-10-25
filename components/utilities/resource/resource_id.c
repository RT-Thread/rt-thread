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
#include <rthw.h>
#include <rtthread.h>
#include <resource_id.h>

void resource_id_init(resource_id_t *mgr, int size, void **res)
{
    if (mgr)
    {
        mgr->size = size;
        mgr->_res = res;
        mgr->noused = 0;
        mgr->_free = RT_NULL;
        rt_spin_lock_init(&(mgr->spinlock));
    }
}

int resource_id_get(resource_id_t *mgr)
{
    rt_base_t level;
    void **cur;

    level = rt_spin_lock_irqsave(&(mgr->spinlock));
    if (mgr->_free)
    {
        cur = mgr->_free;
        mgr->_free = (void **)*mgr->_free;
        rt_spin_unlock_irqrestore(&(mgr->spinlock), level);
        return cur - mgr->_res;
    }
    else if (mgr->noused < mgr->size)
    {
        cur = &mgr->_res[mgr->noused++];
        rt_spin_unlock_irqrestore(&(mgr->spinlock), level);
        return cur - mgr->_res;
    }

    return -1;
}

void resource_id_put(resource_id_t *mgr, int no)
{
    rt_base_t level;
    void **cur;

    if (no >= 0 && no < mgr->size)
    {
        level = rt_spin_lock_irqsave(&(mgr->spinlock));
        cur = &mgr->_res[no];
        *cur = (void *)mgr->_free;
        mgr->_free = cur;
        rt_spin_unlock_irqrestore(&(mgr->spinlock), level);
    }
}
