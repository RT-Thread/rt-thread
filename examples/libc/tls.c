/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-12-19     iDings      first version
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <finsh.h>
#include <rtthread.h>

static __thread int i;

static void child_routine(void *param)
{
    printf("child_thread: i:%d\n", i);
    i = 300;
    printf("child_thread: i:%d\n", i);
}

static int tls_test(void)
{
    rt_thread_t child;

    char name[RT_NAME_MAX];
    rt_thread_get_name(rt_thread_self(), name, sizeof(name));

    printf("i:%d\n", i);
    i = 200;
    printf("main_thread: i:%d\n", i);

    child = rt_thread_create("tls_thread", child_routine, NULL, 4096, 10, 20);
    rt_thread_startup(child);

    sleep(1);
    printf("main_thread: i:%d\n", i);

    return 0;
}
MSH_CMD_EXPORT(tls_test, thread local storage example);
