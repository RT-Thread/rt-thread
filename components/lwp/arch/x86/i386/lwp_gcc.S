/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-7-14      JasonHu      first version
 */

#include "rtconfig.h"

.section      .text.lwp

/*
 * void lwp_switch_to_user(frame);
 */
.global lwp_switch_to_user
lwp_switch_to_user:
    movl 0x4(%esp), %esp
    addl $4,%esp    // skip intr no
    popal
    popl %gs
    popl %fs
    popl %es
    popl %ds
    addl $4, %esp   // skip error_code
    iret    // enter to user mode

.extern arch_syscall_exit
.global sys_fork
.global sys_vfork
.global arch_fork_exit
sys_fork:
sys_vfork:
    jmp _sys_fork
arch_fork_exit:
    jmp arch_syscall_exit

.global sys_clone
.global arch_clone_exit
sys_clone:
    jmp _sys_clone
arch_clone_exit:
    jmp arch_syscall_exit

/**
 * rt thread return code
 */
.align 4
.global lwp_thread_return
lwp_thread_return:
    movl $1, %eax   // eax = 1, sys_exit
    movl $0, %ebx
    int $0x80
.align 4
.global lwp_thread_return_end
lwp_thread_return_end:

#ifdef RT_USING_SIGNALS
/**
 * signal return code
 */
.align 4
.global lwp_signal_return
lwp_signal_return:
    movl $0xe000, %eax // special syscall id for return code
    int $0x80
.align 4
.global lwp_signal_return_end
lwp_signal_return_end:

#endif /* RT_USING_SIGNALS */
