/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

#include <rtthread.h>
#include <stdio.h>
#include <board.h>

/* fix the compile errors for redefiniton of lwip_htonl in win socket */
#ifdef _WIN32
#undef RT_USING_LWIP
#include <components.h>
#endif

void rt_init_thread_entry(void *parameter)
{
#ifdef RT_USING_LWIP
    extern void pcap_netif_hw_init(void);
    pcap_netif_hw_init();
#endif

    /* initialization RT-Thread Components */
    rt_components_init();

    rt_platform_init();

    /* Filesystem Initialization */
#ifdef RT_USING_DFS
    {
#ifdef RT_USING_DFS_WINSHAREDIR
        {
            extern rt_err_t rt_win_sharedir_init(const char *name);
            extern int dfs_win32_init(void);

            rt_win_sharedir_init("wdd");
            dfs_win32_init();

            if (dfs_mount("wdd", "/", "wdir", 0, 0) == 0)
                rt_kprintf("win32 share directory initialized!\n");
            else
                rt_kprintf("win32 share directory initialized failed!\n");
        }
#endif

#ifdef RT_USING_DFS_ELMFAT
        /* mount sd card fat partition 1 as root directory */
        if (dfs_mount("sd0", "/disk/sd", "elm", 0, 0) == 0)
        {
            rt_kprintf("fatfs initialized!\n");
        }
        else
            rt_kprintf("fatfs initialzation failed!\n");
#endif

#ifdef RT_USING_DFS_UFFS
        /* mount sd card fat partition 1 as root directory */
        if (dfs_mount("nand0", "/disk/nand", "uffs", 0, 0) == 0)
        {
            rt_kprintf("uffs initialized!\n");
        }
        else
            rt_kprintf("uffs initialzation failed!\n");
#endif

#ifdef RT_USING_DFS_JFFS2
        /* mount sd card fat partition 1 as root directory */
        if (dfs_mount("nor", "/disk/nor", "jffs2", 0, 0) == 0)
        {
            rt_kprintf("jffs2 initialized!\n");
        }
        else
            rt_kprintf("jffs2 initialzation failed!\n");
#endif


    }
#endif
#ifdef WIN32
    {
        extern void low_cpu(void);
        rt_thread_idle_sethook(low_cpu);
    }
#endif

#if 0
    {
        extern void application_init(void);
        rt_thread_delay(RT_TICK_PER_SECOND);
        application_init();
    }
#endif

#if defined(RT_USING_RTGUI)
    rt_thread_delay(3000);
    realtouch_ui_init();
#endif
}

void rt_test_thread_entry(void *parameter)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        rt_kprintf("hello, world\n");
        rt_thread_delay(100);
    }
}

int rt_application_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("init",
                           rt_init_thread_entry, RT_NULL,
                           2048, RT_THREAD_PRIORITY_MAX / 3, 20);

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    tid = rt_thread_create("test",
                           rt_test_thread_entry, RT_NULL,
                           2048, RT_THREAD_PRIORITY_MAX * 3 / 4, 20);
    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}
#ifdef WIN32
#include <windows.h>
void low_cpu(void)
{
    Sleep(1000);
}

#ifndef _CRT_TERMINATE_DEFINED
#define _CRT_TERMINATE_DEFINED
_CRTIMP __declspec(noreturn) void __cdecl exit(__in int _Code);
_CRTIMP __declspec(noreturn) void __cdecl _exit(__in int _Code);
_CRTIMP void __cdecl abort(void);
#endif
void rt_hw_exit(void)
{
    rt_kprintf("RT-Thread, bye\n");
    exit(0);
}
FINSH_FUNCTION_EXPORT_ALIAS(rt_hw_exit, exit, exit rt-thread);

#endif

#include <dfs_posix.h>
void test_fs(void)
{
    int fd;
    DIR *dir;
    struct dirent *dirp;
    off_t off[6];
    int i;
    mkdir("/testdir", 0777);
    fd = open("/testdir/file1", O_CREAT | O_RDWR, 0777);
    close(fd);
    fd = open("/testdir/file2", O_CREAT | O_RDWR, 0777);
    close(fd);
    fd = open("/testdir/file3", O_CREAT | O_RDWR, 0777);
    close(fd);
    fd = open("/testdir/file4", O_CREAT | O_RDWR, 0777);
    close(fd);
    fd = open("/testdir/file5", O_CREAT | O_RDWR, 0777);
    close(fd);
    fd = open("/testdir/file6", O_CREAT | O_RDWR, 0777);
    close(fd);

    dir = opendir("/testdir");
    for (i = 0; i < 6; i++)
    {
        off[i] = telldir(dir);
        dirp = readdir(dir);
        if (dirp)
            rt_kprintf("#%d NAME:%s\n", i, dirp->d_name);
        else break;
    }
    for (i = 0; i < 6; i++)
    {
        seekdir(dir, off[i]);
        dirp = readdir(dir);
        if (dirp)
            rt_kprintf("#%d NAME:%s\n", i, dirp->d_name);
        else break;
    }

    rt_kprintf("unlink file2\n");
    unlink("/testdir/file2");
    rewinddir(dir);
    for (i = 0; i < 6; i++)
    {
        off[i] = telldir(dir);
        dirp = readdir(dir);
        if (dirp)
            rt_kprintf("#%d NAME:%s\n", i, dirp->d_name);
        else break;
    }
    for (i = 0; i < 6; i++)
    {
        seekdir(dir, off[i]);
        dirp = readdir(dir);
        if (dirp)
            rt_kprintf("#%d NAME:%s\n", i, dirp->d_name);
        else break;
    }

    rt_kprintf("unlink file4\n");
    unlink("/testdir/file4");
    rewinddir(dir);
    for (i = 0; i < 6; i++)
    {
        off[i] = telldir(dir);
        dirp = readdir(dir);
        if (dirp)
            rt_kprintf("#%d NAME:%s\n", i, dirp->d_name);
        else break;
    }
    for (i = 0; i < 6; i++)
    {
        seekdir(dir, off[i]);
        dirp = readdir(dir);
        if (dirp)
            rt_kprintf("#%d NAME:%s\n", i, dirp->d_name);
        else break;
    }

    unlink("/testdir/file1");
    unlink("/testdir/file3");
    unlink("/testdir/file5");
    unlink("/testdir/file6");

    closedir(dir);
}
FINSH_FUNCTION_EXPORT(test_fs, test fs);

/*@}*/
