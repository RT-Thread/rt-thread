/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023.08.03     xqyjlj       first version
 */
#include <interrupt.h>
#include <rtthread.h>
#include <sysrq.h>

#define _SYSRQ_SIZE 62

typedef rt_err_t (*sysrq_callback_fn)(const char key);

static struct rt_spinlock _spinlock = RT_SPINLOCK_INIT;

static int sysrq_log_list_thread(const char key)
{
#if defined(RT_USING_FINSH)
    extern long list_thread(void);
    list_thread();
#else
    rt_kprintf("finsh is not enable\n");
#endif

    return 0;
}

static int sysrq_log_list_isr(const char key)
{
#if defined(RT_USING_INTERRUPT_INFO) && defined(RT_USING_FINSH)
    extern long list_isr(void);
    list_isr();
#else
    rt_kprintf("interrupt info is not enable\n");
#endif
    return 0;
}

static int (*_sysrq_log_fun_array[10])(const char key) = {
    sysrq_log_list_thread, /* 0 */
    RT_NULL,               /* 1 reserved list_cpu*/
    sysrq_log_list_isr,    /* 2 */
    RT_NULL,               /* 3 */
    RT_NULL,               /* 4 */
    RT_NULL,               /* 5 */
    RT_NULL,               /* 6 */
    RT_NULL,               /* 7 */
    RT_NULL,               /* 8 */
    RT_NULL,               /* 9 */
};

static int sysrq_log_list(const char key)
{
    rt_base_t level;
    level = rt_spin_lock_irqsave(&_spinlock);

    int (*const _fun)(const char) = _sysrq_log_fun_array[(uint8_t)(key - '0')];

    rt_spin_unlock_irqrestore(&_spinlock, level);
    if (_fun)
    {
        _fun(key);
    }

    return 0;
}

void sysrq_num_register(char key, int (*const fun)(const char))
{
    uint8_t   id = 255;
    rt_base_t level;

    if ((key >= '0') && (key <= '9'))
        id = key - '0';
    else
        id = 255;

    if (id < 10)
    {
        level = rt_spin_lock_irqsave(&_spinlock);

        _sysrq_log_fun_array[id] = fun;

        rt_spin_unlock_irqrestore(&_spinlock, level);
    }
}

static const struct sysrq_opt _log_list = {.handler    = sysrq_log_list,
                                           .help_str   = "Sys List (0-9)",
                                           .action_str = "Log System List"};

static int sysrq_reboot(const char key)
{
    RT_UNUSED(key);

    rt_hw_cpu_reset();
    return 0;
}

static const struct sysrq_opt _reboot = {.handler = sysrq_reboot, .help_str = "Reboot (b)", .action_str = "Reboot"};

static int sysrq_show_alllock(const char key)
{
    RT_UNUSED(key);

#if defined(RT_USING_FINSH) && defined(RT_USING_MUTEX)
    extern long list_mutex(void);
    list_mutex();
#endif
    return 0;
}

static const struct sysrq_opt _show_alllock = {.handler    = sysrq_show_alllock,
                                               .help_str   = "Show All Lock (d)",
                                               .action_str = "Show All Lock"};

static int sysrq_help(const char key);

static const struct sysrq_opt _help = {.handler = sysrq_help, .help_str = "Help (h)", .action_str = "Help"};

static int sysrq_show_meminfo(const char key)
{
    RT_UNUSED(key);
#if defined(RT_USING_FINSH) && defined(RT_USING_MEMHEAP)
    extern long list_memheap(void);
    list_memheap();
#endif
    return 0;
}
static const struct sysrq_opt _show_meminfo = {.handler    = sysrq_show_meminfo,
                                               .help_str   = "Show Memory Information (m)",
                                               .action_str = "Show Memory Information"};

static int sysrq_shutdown(const char key)
{
    RT_UNUSED(key);

    rt_hw_cpu_shutdown();
    return 0;
}
static const struct sysrq_opt _shutdown = {.handler    = sysrq_shutdown,
                                           .help_str   = "Shutdown (o)",
                                           .action_str = "Shutdown"};

static int sysrq_show_allthread(const char key)
{
    RT_UNUSED(key);

#ifdef RT_USING_FINSH
    extern long list_thread(void);
    list_thread();
#endif
    return 0;
}

static const struct sysrq_opt _show_allthread = {.handler    = sysrq_show_allthread,
                                                 .help_str   = "Show All Thread (t)",
                                                 .action_str = "Show All Thread"};

// TODO: when has nmi irq, shuould show cpu backtrace
static int sysrq_show_allthread_backtrace(const char key)
{
    RT_UNUSED(key);

    struct rt_object_information *info;
    struct rt_object             *obj;
    struct rt_thread             *thread;
    rt_base_t                     level;

    info  = rt_object_get_information(RT_Object_Class_Thread);
    level = rt_spin_lock_irqsave(&info->spinlock);
    rt_list_for_each_entry (obj, &info->object_list, list)
    {
        rt_spin_unlock_irqrestore(&info->spinlock, level);
        thread = (struct rt_thread *)obj;
        rt_kprintf("backtrace for thread: <%s>\n", thread->parent.name);
        rt_backtrace_thread(thread);
        rt_kprintf("\n");
    }
    return 0;
}

static const struct sysrq_opt _show_allthread_backtrace = {.handler    = sysrq_show_allthread_backtrace,
                                                           .help_str   = "Show All Thread Backtrace (l)",
                                                           .action_str = "Show All Thread Backtrace"};

static const struct sysrq_opt *sysrq_key_table[_SYSRQ_SIZE] = {
    &_log_list,                 /* 0 */
    &_log_list,                 /* 1 */
    &_log_list,                 /* 2 */
    &_log_list,                 /* 3 */
    &_log_list,                 /* 4 */
    &_log_list,                 /* 5 */
    &_log_list,                 /* 6 */
    &_log_list,                 /* 7 */
    &_log_list,                 /* 8 */
    &_log_list,                 /* 9 */
    RT_NULL,                    /* a */
    &_reboot,                   /* b - reboot */
    RT_NULL,                    /* c - reserved crashdump */
    &_show_alllock,             /* d - show alllock */
    RT_NULL,                    /* e */
    RT_NULL,                    /* f */
    RT_NULL,                    /* g */
    &_help,                     /* h - for help */
    RT_NULL,                    /* i */
    RT_NULL,                    /* j */
    RT_NULL,                    /* k */
    &_show_allthread_backtrace, /* l - show all cpu backtrace */
    &_show_meminfo,             /* m - show mem info */
    RT_NULL,                    /* n */
    &_shutdown,                 /* o - shutdown*/
    RT_NULL,                    /* p - reserved for show cpu reg */
    RT_NULL,                    /* q */
    RT_NULL,                    /* r */
    RT_NULL,                    /* s */
    &_show_allthread,           /* t - show all cpu thread */
    RT_NULL,                    /* u */
    RT_NULL,                    /* v */
    RT_NULL,                    /* w */
    RT_NULL,                    /* x */
    RT_NULL,                    /* y */
    RT_NULL,                    /* z */
    RT_NULL,                    /* A */
    RT_NULL,                    /* B */
    RT_NULL,                    /* C */
    RT_NULL,                    /* D */
    RT_NULL,                    /* E */
    RT_NULL,                    /* F */
    RT_NULL,                    /* G */
    RT_NULL,                    /* H */
    RT_NULL,                    /* I */
    RT_NULL,                    /* J */
    RT_NULL,                    /* K */
    RT_NULL,                    /* L */
    RT_NULL,                    /* M */
    RT_NULL,                    /* N */
    RT_NULL,                    /* O */
    RT_NULL,                    /* P */
    RT_NULL,                    /* Q */
    RT_NULL,                    /* R */
    RT_NULL,                    /* S */
    RT_NULL,                    /* T */
    RT_NULL,                    /* U */
    RT_NULL,                    /* V */
    RT_NULL,                    /* W */
    RT_NULL,                    /* X */
    RT_NULL,                    /* Y */
    RT_NULL,                    /* Z */
};

static int sysrq_help(const char key)
{
    RT_UNUSED(key);

    for (int i = 9; i < _SYSRQ_SIZE; i++)
    {
        const struct sysrq_opt *opt = sysrq_key_table[i];
        if (opt)
        {
            rt_kprintf("%s.\n", opt->help_str);
        }
    }
    return 0;
}

rt_err_t sysrq_trigger(char key)
{
    uint8_t          id    = 255;
    rt_err_t         err   = -RT_ERROR;
    static rt_bool_t sysrq = RT_FALSE;
    rt_base_t        level;
    if (sysrq)
    {
        if ((key >= '0') && (key <= '9'))
            id = key - '0';
        else if ((key >= 'a') && (key <= 'z'))
            id = key + 10 - 'a';
        else if ((key >= 'A') && (key <= 'Z'))
            id = key + 36 - 'A';
        else
            id = 255;

        if (id < _SYSRQ_SIZE)
        {
            level = rt_spin_lock_irqsave(&_spinlock);

            const struct sysrq_opt *opt = sysrq_key_table[id];

            rt_spin_unlock_irqrestore(&_spinlock, level);
            if (opt)
            {
                rt_kprintf("sysrq: %s.\n", opt->action_str);
                opt->handler(key);
                err = RT_EOK;
            }
        }
    }
    sysrq = (key == 27);
    return err;
}

void sysrq_register(char key, const struct sysrq_opt *opt)
{
    uint8_t   id = 255;
    rt_base_t level;

    if ((key >= '0') && (key <= '9'))
        id = key - '0';
    else if ((key >= 'a') && (key <= 'z'))
        id = key + 10 - 'a';
    else if ((key >= 'A') && (key <= 'Z'))
        id = key + 36 - 'A';
    else
        id = 255;

    if (id < _SYSRQ_SIZE)
    {
        level = rt_spin_lock_irqsave(&_spinlock);

        sysrq_key_table[id] = opt;

        rt_spin_unlock_irqrestore(&_spinlock, level);
    }
}
