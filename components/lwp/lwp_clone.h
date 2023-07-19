/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-06     RT-Thread    the first version
 */
#ifndef __LWP_CLONE_H__
#define __LWP_CLONE_H__

#define CLONE_VM    0x00000100
#define CLONE_FS    0x00000200
#define CLONE_FILES 0x00000400
#define CLONE_SIGHAND   0x00000800
#define CLONE_PTRACE    0x00002000
#define CLONE_VFORK 0x00004000
#define CLONE_PARENT    0x00008000
#define CLONE_THREAD    0x00010000
#define CLONE_NEWNS 0x00020000
#define CLONE_SYSVSEM   0x00040000
#define CLONE_SETTLS    0x00080000
#define CLONE_PARENT_SETTID 0x00100000
#define CLONE_CHILD_CLEARTID    0x00200000
#define CLONE_DETACHED  0x00400000
#define CLONE_UNTRACED  0x00800000
#define CLONE_CHILD_SETTID  0x01000000
#define CLONE_NEWCGROUP 0x02000000
#define CLONE_NEWUTS    0x04000000
#define CLONE_NEWIPC    0x08000000
#define CLONE_NEWUSER   0x10000000
#define CLONE_NEWPID    0x20000000
#define CLONE_NEWNET    0x40000000
#define CLONE_IO    0x80000000

/* arg[] -> flags
 *          stack
 *          new_tid
 *          tls
 *          set_clear_tid_address
 *          quit_func
 *          start_args
 *          */
#define SYS_CLONE_ARGS_NR 7

#endif /* __LWP_CLONE_H__ */
