/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-16     Bernard      the first version
 * 2006-05-25     Bernard      rewrite vsprintf
 * 2006-08-10     Bernard      add rt_show_version
 * 2010-03-17     Bernard      remove rt_strlcpy function
 *                             fix gcc compiling issue.
 * 2010-04-15     Bernard      remove weak definition on ICCM16C compiler
 * 2012-07-18     Arda         add the alignment display for signed integer
 * 2012-11-23     Bernard      fix IAR compiler error.
 * 2012-12-22     Bernard      fix rt_kprintf issue, which found by Grissiom.
 * 2013-06-24     Bernard      remove rt_kprintf if RT_USING_CONSOLE is not defined.
 * 2013-09-24     aozima       make sure the device is in STREAM mode when used by rt_kprintf.
 * 2015-07-06     Bernard      Add rt_assert_handler routine.
 * 2021-02-28     Meco Man     add RT_KSERVICE_USING_STDLIB
 * 2021-12-20     Meco Man     implement rt_strcpy()
 * 2022-01-07     Gabriel      add __on_rt_assert_hook
 * 2022-06-04     Meco Man     remove strnlen
 * 2022-08-24     Yunjie       make rt_memset word-independent to adapt to ti c28x (16bit word)
 * 2022-08-30     Yunjie       make rt_vsnprintf adapt to ti c28x (16bit int)
 * 2022-11-14     Meco Man     move libc functions to the klibc.c file
 * 2022-11-14     Meco Man     move __rt_ffs functions to the scheduler.c file
 */

#include <rtthread.h>

#ifdef RT_USING_MODULE
#include <dlmodule.h>
#endif /* RT_USING_MODULE */

/**
 * @addtogroup KernelService
 */

/**@{*/

/**
 * This function will show the version of rt-thread rtos
 */
void rt_show_version(void)
{
    rt_kprintf("\n \\ | /\n");
    rt_kprintf("- RT -     Thread Operating System\n");
    rt_kprintf(" / | \\     %d.%d.%d build %s %s\n",
               (rt_int32_t)RT_VERSION_MAJOR, (rt_int32_t)RT_VERSION_MINOR, (rt_int32_t)RT_VERSION_PATCH, __DATE__, __TIME__);
    rt_kprintf(" 2006 - 2022 Copyright by RT-Thread team\n");
}
RTM_EXPORT(rt_show_version);

RT_WEAK void rt_hw_us_delay(rt_uint32_t us)
{
    (void) us;
    RT_DEBUG_LOG(RT_DEBUG_DEVICE, ("rt_hw_us_delay() doesn't support for this board."
        "Please consider implementing rt_hw_us_delay() in another file.\n"));
}

#ifdef RT_USING_CONSOLE
#ifdef RT_USING_DEVICE
static rt_device_t _console_device = RT_NULL;

/**
 * This function returns the device using in console.
 *
 * @return Returns the console device pointer or RT_NULL.
 */
rt_device_t rt_console_get_device(void)
{
    return _console_device;
}
RTM_EXPORT(rt_console_get_device);

/**
 * This function will set a device as console device.
 * After set a device to console, all output of rt_kprintf will be
 * redirected to this new device.
 *
 * @param  name is the name of new console device.
 *
 * @return the old console device handler on successful, or RT_NULL on failure.
 */
rt_device_t rt_console_set_device(const char *name)
{
    rt_device_t new_device, old_device;

    /* save old device */
    old_device = _console_device;

    /* find new console device */
    new_device = rt_device_find(name);

    /* check whether it's a same device */
    if (new_device == old_device) return RT_NULL;

    if (new_device != RT_NULL)
    {
        if (_console_device != RT_NULL)
        {
            /* close old console device */
            rt_device_close(_console_device);
        }

        /* set new console device */
        rt_device_open(new_device, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_STREAM);
        _console_device = new_device;
    }

    return old_device;
}
RTM_EXPORT(rt_console_set_device);
#endif /* RT_USING_DEVICE */

RT_WEAK void rt_hw_console_output(const char *str)
{
    /* empty console output */
}
RTM_EXPORT(rt_hw_console_output);
#endif /* RT_USING_CONSOLE */

#ifndef __on_rt_assert_hook
    #define __on_rt_assert_hook(ex, func, line)         __ON_HOOK_ARGS(rt_assert_hook, (ex, func, line))
#endif

#ifdef RT_DEBUG
/* RT_ASSERT(EX)'s hook */

void (*rt_assert_hook)(const char *ex, const char *func, rt_size_t line);

/**
 * This function will set a hook function to RT_ASSERT(EX). It will run when the expression is false.
 *
 * @param hook is the hook function.
 */
void rt_assert_set_hook(void (*hook)(const char *ex, const char *func, rt_size_t line))
{
    rt_assert_hook = hook;
}

/**
 * The RT_ASSERT function.
 *
 * @param ex_string is the assertion condition string.
 *
 * @param func is the function name when assertion.
 *
 * @param line is the file line number when assertion.
 */
void rt_assert_handler(const char *ex_string, const char *func, rt_size_t line)
{
    volatile char dummy = 0;

    if (rt_assert_hook == RT_NULL)
    {
#ifdef RT_USING_MODULE
        if (dlmodule_self())
        {
            /* close assertion module */
            dlmodule_exit(-1);
        }
        else
#endif /*RT_USING_MODULE*/
        {
            rt_kprintf("(%s) assertion failed at function:%s, line number:%d \n", ex_string, func, line);
            while (dummy == 0);
        }
    }
    else
    {
        rt_assert_hook(ex_string, func, line);
    }
}
RTM_EXPORT(rt_assert_handler);
#endif /* RT_DEBUG */

/**@}*/
