/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-09-04     armink       the first version
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
#ifdef RT_USING_DEVICE
    rt_device_t dev = rt_console_get_device();

    if (dev == RT_NULL)
    {
        rt_hw_console_output(log);
    }
    else
    {
        rt_device_write(dev, 0, log, len);
    }
#else
    rt_hw_console_output(log);
#endif

}

RT_WEAK rt_bool_t ulog_console_backend_filter(struct ulog_backend *backend, rt_uint32_t level, const char *tag, 
                                             rt_bool_t is_raw,const char *log, rt_size_t len)
{
  return RT_TRUE;
}

int ulog_console_backend_init(void)
{
    ulog_init();
    console.output = ulog_console_backend_output;

    ulog_backend_register(&console, "console", RT_TRUE);
    ulog_backend_set_filter(&console,ulog_console_backend_filter);
    return 0;
}
INIT_PREV_EXPORT(ulog_console_backend_init);

#ifdef RT_USING_MSH
static void ulog_console_backend_filter_set(uint8_t argc, char **argv)
{
    if (argc < 2)
    {
        rt_kprintf("Usage:\n");
        rt_kprintf("console filter [option] optino:enable or disable\n");
        return;
    }
    else
    {
        const char *operator = argv[1];
        if (!rt_strcmp(operator, "enable"))
        {
            ulog_backend_set_filter(&console,ulog_console_backend_filter);
        }
        else if (!rt_strcmp(operator, "disable"))
        {
            ulog_backend_set_filter(&console,RT_NULL);
        }
        else
        {
            rt_kprintf("Usage:\n");
            rt_kprintf("console filter [option] optino:enable or disable\n");
        }
    }
}
MSH_CMD_EXPORT_ALIAS(ulog_console_backend_filter_set,console_filter,console filter [option] optino:enable or disable);
#endif /* ULOG_BACKEND_USING_CONSOLE */
