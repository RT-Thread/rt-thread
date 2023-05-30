/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-08     Yang        the first version
 */

#include <rtthread.h>
#ifdef RT_USING_FINSH
#include <shell.h>
#include <finsh.h>
#endif

/* thread phase init */
void rt_init_thread_entry(void *parameter)
{
    /* Initialization RT-Thread Components */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_init();
#elif defined(RT_USING_FINSH)
    finsh_system_init();
#endif
}

void build_dump(void)
{
#if    defined(__CC_ARM)
    rt_kprintf("using MDK\n");
#elif  defined(__IAR_SYSTEMS_ICC__)
    rt_kprintf("using IAR\n");
#elif  defined(__GNUC__)
    rt_kprintf("using GCC\n");
#else
    rt_kprintf("unkown Compiler\n");
#endif
}

void link_dump(void)
{
#ifdef __GNUC__
    extern unsigned int _sdata;
    extern unsigned int _edata;
    extern unsigned int _sidata;

    extern unsigned int _sbss;
    extern unsigned int _ebss;

    #define DUMP_VAR(__VAR) \
        rt_kprintf("%-20s %p\n", #__VAR, &__VAR)

    DUMP_VAR(_sdata);
    DUMP_VAR(_edata);
    DUMP_VAR(_sidata);
    DUMP_VAR(_sbss);
    DUMP_VAR(_ebss);
#endif
}

int rt_application_init(void)
{
    rt_thread_t tid;

    build_dump();
    link_dump();

    tid = rt_thread_create("init",
                           rt_init_thread_entry, RT_NULL,
                           2048, RT_THREAD_PRIORITY_MAX / 3, 20);
    if (tid != RT_NULL) rt_thread_startup(tid);

    return 0;
}
