/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef  LWP_ARCH_H__
#define  LWP_ARCH_H__

#include <lwp.h>

#ifdef RT_USING_USERSPACE

#define USER_HEAP_VEND    0xB0000000UL
#define USER_HEAP_VADDR   0x80000000UL
#define USER_STACK_VSTART 0x70000000UL
#define USER_STACK_VEND   USER_HEAP_VADDR
#define LDSO_LOAD_VADDR   0x60000000UL
#define USER_VADDR_START  0x00100000UL
#define USER_LOAD_VADDR   USER_VADDR_START

#ifdef __cplusplus
extern "C" {
#endif

int arch_user_space_init(struct rt_lwp *lwp);
void arch_user_space_vtable_free(struct rt_lwp *lwp);
void *arch_kernel_mmu_table_get(void);
void arch_kuser_init(rt_mmu_info *mmu_info, void *vectors);
int arch_expand_user_stack(void *addr);

rt_inline unsigned long ffz(unsigned long x)
{
    return __builtin_ffs(~x) - 1;
}

#ifdef __cplusplus
}
#endif

#endif

#endif  /*LWP_ARCH_H__*/
