/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-10     RT-Thread    The first version
 * 2023-03-13     WangXiaoyao  syscall metadata as structure
 */
#ifndef __SYSCALL_DATA_H__
#define __SYSCALL_DATA_H__

#include <rtthread.h>

typedef long sysret_t;

struct rt_syscall_def
{
    void *func;
    char *name;
};

/**
 * @brief signature for syscall, used to locate syscall metadata.
 *
 * We don't allocate an exclusive section in ELF like Linux do
 * to avoid initializing necessary data by iterating that section,
 * which increases system booting time. We signature a pointer
 * just below each syscall entry in syscall table to make it
 * easy to locate every syscall's metadata by using syscall id.
 */
#define SYSCALL_SIGN(func) {    \
    (void *)(func),             \
    &RT_STRINGIFY(func)[4],     \
}

#define SET_ERRNO(no) rt_set_errno(-(no))
#define GET_ERRNO() ({int _errno = rt_get_errno(); _errno > 0 ? -_errno : _errno;})

#define _SYS_WRAP(func) ({int _ret = func; _ret < 0 ? GET_ERRNO() : _ret;})

#endif /* __SYSCALL_DATA_H__ */
