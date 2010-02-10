/*
 * File      : writespeed.c
 * This file is part of RT-TestCase in RT-Thread RTOS
 * COPYRIGHT (C) 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-02-10     Bernard      first version
 */
#include <rtthread.h>
#include <dfs_posix.h>

void writespeed(const char* filename, int total_length, int block_size)
{
    int fd;
    char *buff_ptr;
    rt_tick_t tick;

    fd = open(filename, 0, O_WRONLY);
    if (fd < 0)
    {
        rt_kprintf("open file:%s failed\n", filename);
        return;
    }

    buff_ptr = rt_malloc(block_size);
    if (buff_ptr == RT_NULL)
    {
        rt_kprintf("no memory\n");
        close(fd);

        return;
    }

	/* prepare write data */

    tick = rt_tick_get();

    tick = rt_tick_get() - tick;

	/* close file and release memory */
    close(fd);
	rt_free(buff_ptr);

    /* calculate write speed */
    rt_kprintf("File write speed: %d byte/s\n", total_length/ (tick/RT_TICK_PER_SECOND));
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(writespeed, perform file write test);
#endif
