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
#include <stdlib.h>

void writespeed(const char* filename, int total_length, int block_size)
{
    int fd, index, length;
    char *buff_ptr;
    rt_tick_t tick;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0);
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
    for (index = 0; index < block_size; index++)
    {
        buff_ptr[index] = index;
    }
    index = 0;

    /* get the beginning tick */
    tick = rt_tick_get();
    while (index < total_length / block_size)
    {
        length = write(fd, buff_ptr, block_size);
        if (length != block_size)
        {
            rt_kprintf("write failed\n");
            break;
        }

        index ++;
    }
    tick = rt_tick_get() - tick;

    /* close file and release memory */
    close(fd);
    rt_free(buff_ptr);

    /* calculate write speed */
    if (tick)
        rt_kprintf("File write speed: %d byte/s\n", total_length / tick * RT_TICK_PER_SECOND);
    else
        rt_kprintf("time is not long enough\n");
}

static void cmd_writespeed(int argc, char **argv)
{
    int ts = 1024*1024*10;
    int bs = 512;
    char *name = "/_tws.dat";

    while (argc)
    {
        switch (argc)
        {
        case 2:
            name = argv[1];
            break;  
        case 3:
            ts = atoi(argv[2]);
            break;
        case 4:
            bs = atoi(argv[3]);
            break;
        }

        argc --;
    }
    rt_kprintf("name: %s, size: %d, blksize: %d\n", name, ts, bs);

    writespeed(name, ts, bs);
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(writespeed, perform file write test);
MSH_CMD_EXPORT_ALIAS(cmd_writespeed, writespeed, writespeed [name] [size] [blksize]);
#endif
