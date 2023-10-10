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

#include <errno.h>
#include <stdlib.h>

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

rt_inline sysret_t lwp_errno_to_posix(rt_err_t error)
{
    sysret_t posix_rc;

    switch (labs(error))
    {
        case RT_EOK:
            posix_rc = 0;
            break;
        case RT_ETIMEOUT:
            posix_rc = -ETIMEDOUT;
            break;
        case RT_EINVAL:
            posix_rc = -EINVAL;
            break;
        case RT_ENOENT:
            posix_rc = -ENOENT;
            break;
        case RT_ENOSPC:
            posix_rc = -ENOSPC;
            break;
        case RT_EPERM:
            posix_rc = -EPERM;
            break;
        default:
            posix_rc = -1;
            break;
    }

    return posix_rc;
}

#endif /* __SYSCALL_DATA_H__ */
