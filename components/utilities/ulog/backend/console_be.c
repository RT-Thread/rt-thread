/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-09-04     armink       the first version
 * 2025-10-30     wdfk-prog    add emergency log flush mechanism
 */

#include <rthw.h>
#include <ulog.h>

#ifdef ULOG_BACKEND_USING_CONSOLE

#if defined(ULOG_ASYNC_OUTPUT_BY_THREAD) && ULOG_ASYNC_OUTPUT_THREAD_STACK < 384
#error "The thread stack size must more than 384 when using async output by thread (ULOG_ASYNC_OUTPUT_BY_THREAD)"
#endif

static struct ulog_backend console = { 0 };

void ulog_console_backend_output(struct ulog_backend *backend, rt_uint32_t level, const char *tag, rt_bool_t is_raw,
        const char *log, rt_size_t len)
{
    rt_kputs(log);

}

int ulog_console_backend_init(void)
{
    ulog_init();
    console.output = ulog_console_backend_output;

    ulog_backend_register(&console, "console", RT_TRUE);
    console.output = ulog_console_backend_output;
    console.is_emergency_backend = RT_TRUE;

    return 0;
}
INIT_PREV_EXPORT(ulog_console_backend_init);

#endif /* ULOG_BACKEND_USING_CONSOLE */
