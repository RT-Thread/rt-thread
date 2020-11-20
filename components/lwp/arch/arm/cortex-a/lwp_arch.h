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

#define USER_HEAP_VADDR   0x80000000
#define USER_STACK_VSTART 0x70000000
#define USER_STACK_VEND   USER_HEAP_VADDR
#define USER_VADDR_START  0x00100000

#ifdef __cplusplus
extern "C" {
#endif

int arch_user_space_init(struct rt_lwp *lwp);
void *arch_kernel_mmu_table_get(void);
void arch_kuser_init(rt_mmu_info *mmu_info, void *vectors);
int arch_expand_user_stack(void *addr);

#ifdef __cplusplus
}
#endif

#endif

#endif  /*LWP_ARCH_H__*/
