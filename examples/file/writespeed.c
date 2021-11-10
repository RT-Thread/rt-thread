/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-02-10     Bernard      first version
 * 2020-04-12     Jianjia Ma   add msh cmd
 */
#include <rtthread.h>
#include <dfs_posix.h>

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
    rt_kprintf("File write speed: %d byte/s\n", total_length / tick * RT_TICK_PER_SECOND);
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(writespeed, perform file write test);

static void cmd_writespeed(int argc, char *argv[])
{
    char* filename;
    int length;
    int block_size;

    if(argc == 4)
    {
        filename = argv[1];
        length = atoi(argv[2]);
        block_size = atoi(argv[3]);
    }
    else if(argc == 2)
    {
        filename = argv[1];
        block_size = 512;
        length = 1024*1024;
    }
    else
    {
       rt_kprintf("Usage:\nwritespeed [file_path] [length] [block_size]\n");
       rt_kprintf("writespeed [file_path] with default length 1MB and block size 512\n");
       return;
    }
    writespeed(filename, length, block_size);
}
MSH_CMD_EXPORT_ALIAS(cmd_writespeed, writespeed, test file system write speed);
#endif /* RT_USING_FINSH */
