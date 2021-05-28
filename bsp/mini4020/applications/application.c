/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2007-11-20     Yi.Qiu        add rtgui application
 * 2008-6-28      Bernard       no rtgui init
 */

/**
 * @addtogroup mini4020
 */

/*@{*/

#include <board.h>
#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs.h>
#include <dfs_elm.h>
#include <dfs_fs.h>
#include <dfs_posix.h>
#endif

#ifdef RT_USING_RTGUI
#include <rtgui/rtgui.h>
extern void radio_rtgui_init(void);
#endif

#define RT_INIT_THREAD_STACK_SIZE (2*1024)

void rt_init_thread_entry(void *parameter)
{
    int fd;
    rt_uint32_t sz;
    char buffer[20];
#ifdef RT_USING_DFS
    dfs_init();
#ifdef RT_USING_DFS_ELMFAT
    elm_init();
    /* mount sd card fat partition 1 as root directory */
    if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("File System initialized!\n");

        /*Open a file*/
        fd = open("/fattest.txt", O_RDWR|O_CREAT, 0);
        if (fd < 0)
        {
            rt_kprintf("open file for write failed\n");
            return;
        }

        sz = write(fd,"Hello RT-Thread!",sizeof("Hello RT-Thread!"));

        if (sz != 0)
        {
            rt_kprintf("written %d\n",sz);
        }
        else
            rt_kprintf("haven't written\n");

        lseek(fd, 0, SEEK_SET);

        sz = read(fd, buffer, sizeof(buffer));

        if (sz != 0)
        {
            rt_kprintf("READ %d:",sz);
            while (sz--)
                rt_kprintf("%c",buffer[sz]);//opposite
            rt_kprintf("\n");
        }
        else
            rt_kprintf("haven't read\n");

        close(fd);
    }
    else
        rt_kprintf("File System initialzation failed!\n");
#endif
#endif
}

void rt_led_thread_entry(void *parameter)
{
/*
    while (1)
    {
        count++;
        *(RP)GPIO_PORTE_DATA |= 0x1<<4;
        rt_thread_delay(RT_TICK_PER_SECOND*2);

        *(RP)GPIO_PORTE_DATA &= ~(0x1<<4);
        rt_thread_delay(RT_TICK_PER_SECOND*2);

    }
*/
}


int rt_application_init(void)
{
    rt_thread_t init_thread;
    rt_thread_t led_thread;

    init_thread = rt_thread_create("init",
                                rt_init_thread_entry, RT_NULL,
                                RT_INIT_THREAD_STACK_SIZE, 8, 20);
    led_thread = rt_thread_create("led",
                                rt_led_thread_entry, RT_NULL,
                                512, 200, 20);

    if (init_thread != RT_NULL)
        rt_thread_startup(init_thread);

    if (led_thread != RT_NULL)
        rt_thread_startup(led_thread);

    return 0;
}

/*@}*/
