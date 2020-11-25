/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-18     Jesven       first version
 */

#include <rtthread.h>
#include <rthw.h>

#ifdef RT_USING_USERSPACE

#include <mmu.h>
#include <page.h>
#include <lwp_mm_area.h>
#include <lwp_user_mm.h>
#include <lwp_arch.h>

int arch_expand_user_stack(void *addr)
{
    int ret = 0;
    size_t stack_addr = (size_t)addr;

    stack_addr &= ~ARCH_PAGE_MASK;
    if ((stack_addr >= (size_t)USER_STACK_VSTART) && (stack_addr < (size_t)USER_STACK_VEND))
    {
        void *map = lwp_map_user(lwp_self(), (void*)stack_addr, ARCH_PAGE_SIZE);

        if (map || lwp_data_access_ok(&lwp_self()->mmu_info, addr, 1))
        {
            ret = 1;
        }
    }
    return ret;
}
#endif
