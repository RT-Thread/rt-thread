/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-06-26     Grissiom     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <log_trace.h>

#define PIPE_SZ    2048
#define PIPE_NAME  "memlog"

static rt_pipe_t *_log_pipe = NULL;
static rt_uint8_t outbuf[1024];
void memlog_flush(void)
{
    rt_size_t readsz;
    rt_device_t console;

    console = rt_console_get_device();
    if (!console) return;

    readsz = rt_device_read((rt_device_t)&(_log_pipe->parent), 0, outbuf, sizeof(outbuf));
    if (readsz)
        rt_device_write(console, 0, outbuf, readsz);
}

int memlog_init(void)
{
    _log_pipe = rt_pipe_create(PIPE_NAME, PIPE_SZ);
    if (_log_pipe == RT_NULL)
    {
        rt_kprintf("init pipe device failed.\n");
        return -1;
    }

    log_trace_set_device(PIPE_NAME);
    rt_thread_idle_sethook(memlog_flush);
    
    return 0;
}
INIT_APP_EXPORT(memlog_init);
