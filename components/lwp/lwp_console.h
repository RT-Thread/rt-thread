/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-02-23     Jesven         first version.
 */
#ifndef  LWP_CONSOLE_H__
#define  LWP_CONSOLE_H__

#include <lwp.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <dfs_posix.h>
#include <dfs_poll.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RT_PROCESS_KERNEL RT_NULL

struct rt_console_device
{
    struct rt_device parent;
    int    init_flag;
    struct rt_device *iodev;
    struct rt_lwp *foreground;
    struct rt_wqueue wait_queue; /* for kernel when current == 0 */
    struct rt_ringbuffer input_rb;
    rt_uint8_t input_buf[LWP_CONSOLE_INPUT_BUFFER_SIZE];
};

rt_err_t rt_console_register(const char *name, struct rt_device *iodev);

struct rt_device *rt_console_set_iodev(struct rt_device *iodev);
struct rt_device *rt_console_get_iodev(void);

void rt_console_set_foreground(struct rt_lwp *lwp);
struct rt_lwp* rt_console_get_foreground(void);

#ifdef __cplusplus
}
#endif

#endif  /* LWP_CONSOLE_H__*/
