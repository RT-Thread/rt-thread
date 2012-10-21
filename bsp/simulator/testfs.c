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

#ifdef RT_USING_DFS
/* dfs init */
#include <dfs_init.h>
/* dfs filesystem:ELM filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

#include <dfs_posix.h>

int testfat(void) 
{
    int Fd,i;
	int res;

    Fd = open("/nor/test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0);    //打开文件 
    if (Fd>=0)
    {
        rt_kprintf("begin\n");
        for (i = 0; i < 94520 ; i++)
        //for (i = 0; i < 512 ; i++)
        {
           res = write(Fd, &i, 1);
		   if (res < 0)
		   {
				rt_kprintf("write %d bytes, then meet a error, break\n", i);
				break;
		   }
        }
        close(Fd);
        rt_kprintf("over\n");
    }
    else
    {
        rt_kprintf("failed\n");
    }
    return 0;
}

static char buf[94520];
int testfat2(void) 
{
    int Fd,i;

    Fd = open("/nor/test2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0);    //打开文件 
    if (Fd>=0)
    {
        rt_kprintf("begin\n");
        for (i = 0; i < 94520 ; i++)
        {
            write(Fd, buf, 1);
        }
        close(Fd);
        rt_kprintf("over\n");
    }
    else
    {
        rt_kprintf("failed\n");
    }
    return 0;
}


int testfat3(void) 
{
    int Fd,i;

    Fd = open("/nor/test3.txt", O_WRONLY | O_CREAT | O_TRUNC, 0);    //打开文件 
    if (Fd>=0)
    {
        rt_kprintf("begin\n");
        {
            write(Fd, buf, 94520);
        }
        close(Fd);
        rt_kprintf("over\n");
    }
    else
    {
        rt_kprintf("failed\n");
    }
    return 0;
}

#include <finsh.h>
FINSH_FUNCTION_EXPORT(testfat, test fs);
FINSH_FUNCTION_EXPORT(testfat2, test fs);
FINSH_FUNCTION_EXPORT(testfat3, test fs);