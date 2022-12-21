/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-06-05     Bernard      the first version
 */

#include <rtthread.h>

/**
 * @addtogroup LPC2148
 */
/*@{*/

#ifdef RT_USING_FINSH
#include <shell.h>
#include <finsh.h>
#endif

#ifdef RT_USING_DFS
/* dfs init */
#include <dfs.h>
/* dfs filesystem:FAT filesystem init */
#include <dfs_fat.h>
/* dfs filesystem:EFS filesystem init */
#include <dfs_efs.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#endif

#ifdef RT_USING_RTGUI
#include <rtgui/rtgui.h>
#endif

/* thread phase init */
void rt_init_thread_entry(void *parameter)
{
#ifdef RT_USING_DEVICE
#ifdef RT_USING_DFS
    /* init sd card */
    rt_hw_sdcard_init();
#endif

#ifdef RT_USING_LWIP
    eth_system_device_init();
    /* init ethernetif device */
    rt_hw_dm9000_init();
#endif

    /* init hardware serial device */
    rt_hw_serial_init();
#endif

    /* Filesystem Initialization */
#ifdef RT_USING_DFS
    {
        /* init the device filesystem */
        dfs_init();
        elm_init();

        /* mount sd card fat partition 1 as root directory */
        if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
            rt_kprintf("File System initialized!\n");
        else
            rt_kprintf("File System init failed!\n");
    }
#endif

    /* LwIP Initialization */
#ifdef RT_USING_LWIP
    {
        extern void lwip_sys_init(void);

        /* init lwip system */
        lwip_sys_init();
        rt_kprintf("TCP/IP initialized!\n");
    }
#endif

#ifdef RT_USING_FINSH
    finsh_system_init();
#endif
}

/************** LED BLINK *******************/
#include "lpc214x.h"
#define LED1     (1<<16) //P1
#define LED2     (1<<17) //P1
#define LED3     (1<<18) //P1
#define LED4     (1<<19) //P1

rt_align(4) char thread_led1_stack[512];
struct rt_thread thread_led1;
void thread_led1_entry(void *parameter)
{
    unsigned int count = 0;

    IO1DIR |= LED1;
    while (1)
    {
        /* led1 on */
        IO1CLR = LED1;
#ifndef RT_USING_FINSH
        rt_kprintf("led1 on, count : %d\r\n", count);
#endif
        count++;
        rt_thread_delay(RT_TICK_PER_SECOND / 3); /* delay 0.3s */

        /* led1 off */
        IO1SET = LED1;
#ifndef RT_USING_FINSH
        rt_kprintf("led1 off\r\n");
#endif
        rt_thread_delay(RT_TICK_PER_SECOND / 3);
    }
}

rt_align(4) char thread_led2_stack[512];
struct rt_thread thread_led2;
void thread_led2_entry(void *parameter)
{
    unsigned int count = 0;

    IO1DIR |= LED2;
    while (1)
    {
        /* led2 on */
        IO1CLR = LED2;
#ifndef RT_USING_FINSH
        rt_kprintf("led2 on, count : %d\r\n", count);
#endif
        count++;
        rt_thread_delay(RT_TICK_PER_SECOND / 2); /* delay 0.5s */

        /* led2 off */
        IO1SET = LED2;
#ifndef RT_USING_FINSH
        rt_kprintf("led1 off\r\n");
#endif
        rt_thread_delay(RT_TICK_PER_SECOND / 2);
    }
}
/************** LED BLINK *******************/

int rt_application_init()
{
    rt_thread_init(&thread_led1,
                   "led1",
                   thread_led1_entry, RT_NULL,
                   &thread_led1_stack[0], sizeof(thread_led1_stack),
                   20, 10);

    rt_thread_init(&thread_led2,
                   "led2",
                   thread_led2_entry, RT_NULL,
                   &thread_led2_stack[0], sizeof(thread_led2_stack),
                   25, 8);
    rt_thread_startup(&thread_led1);
    rt_thread_startup(&thread_led2);

    /* inint SD-crad and dm9000 */
    {
        rt_thread_t init_thread;

        init_thread = rt_thread_create("init",
                                       rt_init_thread_entry, RT_NULL,
                                       1024, 8, 5);
        rt_thread_startup(init_thread);
    }

    return 0;
}

/*@}*/
