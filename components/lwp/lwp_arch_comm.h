/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __LWP_ARCH_COMM__
#define __LWP_ARCH_COMM__

#include <mm_aspace.h>
#include <rtthread.h>
#include <mmu.h>

/**
 * APIs that must port to all architectures
 */

/* syscall handlers */
void arch_clone_exit(void);
void arch_fork_exit(void);
void arch_syscall_exit();
void arch_ret_to_user();

/* ELF relocation */
#ifdef ARCH_MM_MMU

struct rt_lwp;
void arch_elf_reloc(rt_aspace_t aspace, void *text_start, void *rel_dyn_start, size_t rel_dyn_size, void *got_start, size_t got_size, void *dynsym);
#else
void arch_elf_reloc(void *text_start, void *rel_dyn_start, size_t rel_dyn_size, void *got_start, size_t got_size, void *dynsym);
#endif

/* User entry. enter user program code for the first time */
void arch_crt_start_umode(void *args, const void *text, void *ustack, void *user_stack);
void arch_start_umode(void *args, const void *text, void *ustack, void *k_stack);

/* lwp create and setup */
int arch_set_thread_context(void (*exit)(void), void *new_thread_stack,
                            void *user_stack, void **thread_sp);
void *arch_get_user_sp(void);

/* user space setup and control */
int arch_user_space_init(struct rt_lwp *lwp);
void arch_user_space_free(struct rt_lwp *lwp);
void *arch_kernel_mmu_table_get(void);
void arch_kuser_init(rt_aspace_t aspace, void *vectors);
int arch_expand_user_stack(void *addr);

/* thread id register */
void arch_set_thread_area(void *p);
void* arch_get_tidr(void);
void arch_set_tidr(void *p);

#endif /* __LWP_ARCH_COMM__ */
