/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-10     RT-Thread    The first version
 */
#ifndef __SYSCALL_DATA_H__
#define __SYSCALL_DATA_H__

#include <rtthread.h>

/**
 * @brief signature for syscall, used to locate syscall metadata.
 *
 * We don't allocate an exclusive section in ELF like Linux do
 * to avoid initializing necessary data by iterating that section,
 * which increases system booting time. We signature a pointer
 * just below each syscall entry in syscall table to make it
 * easy to locate every syscall's metadata by using syscall id.
 *
 * TODO Currently this adds a dummy pointer to syscall name.
 * After adding metadata of every syscalls in front of their definition,
 * this should be replaced by a pointer to that structure
 */
#define SYSCALL_SIGN(func) \
    (void *)func,          \
        RT_STRINGIFY(func)

#endif /* __SYSCALL_DATA_H__ */