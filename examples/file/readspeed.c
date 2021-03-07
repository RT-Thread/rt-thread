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

void readspeed(const char* filename, int block_size)
{
    int fd;
    char *buff_ptr;
    rt_size_t total_length;
    rt_tick_t tick;

    fd = open(filename, 0, O_RDONLY);
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

    tick = rt_tick_get();
    total_length = 0;
    while (1)
    {
        int length;
        length = read(fd, buff_ptr, block_size);

        if (length <= 0) break;
        total_length += length;
    }
    tick = rt_tick_get() - tick;

    /* close file and release memory */
    close(fd);
    rt_free(buff_ptr);

    /* calculate read speed */
    rt_kprintf("File read speed: %d byte/s\n", total_length /tick * RT_TICK_PER_SECOND);
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(readspeed, perform file read test);

#ifdef FINSH_USING_MSH
static void cmd_readspeed(int argc, char *argv[])
{
    char* filename;
    int block_size;

    if(argc == 3)
    {
        filename = argv[1];
        block_size = atoi(argv[2]);
    }
    else if(argc == 2)
    {
        filename = argv[1];
        block_size = 512;
    }
    else
    {
       rt_kprintf("Usage:\nreadspeed [file_path] [block_size]\n");
       rt_kprintf("readspeed [file_path] with default block size 512\n");
       return;
    }
    readspeed(filename, block_size);
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_readspeed, __cmd_readspeed, test file system read speed);
#endif /* FINSH_USING_MSH */
#endif /* RT_USING_FINSH */
