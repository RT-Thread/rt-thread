/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-02     aozima       the first version.
 * 2011-03-17     aozima       fix some bug.
 * 2011-03-18     aozima       to dynamic thread.
 */

#include <rtthread.h>
#include <dfs_file.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/statfs.h>

static rt_uint32_t stop_flag = 0;
static rt_thread_t fsrw1_thread = RT_NULL;
static rt_thread_t fsrw2_thread = RT_NULL;

#define fsrw1_fn                   "/test1.dat"
#define fsrw1_data_len             120               /* Less than 256 */
static void fsrw1_thread_entry(void* parameter)
{
    int fd;
    int index,length;
    rt_uint32_t round;
    rt_uint32_t tick_start,tick_end,read_speed,write_speed;

    static rt_uint8_t write_data1[fsrw1_data_len];
    static rt_uint8_t read_data1[fsrw1_data_len];

    round = 1;

    while(1)
    {
        if( stop_flag )
        {
            rt_kprintf("thread fsrw2 error,thread fsrw1 quit!\r\n");
            fsrw1_thread = RT_NULL;
            stop_flag = 0;
            return;
        }

        /* creat file */
        fd = open(fsrw1_fn, O_WRONLY | O_CREAT | O_TRUNC, 0);
        if (fd < 0)
        {
            rt_kprintf("fsrw1 open file for write failed\n");
            stop_flag = 1;
            fsrw1_thread = RT_NULL;
            return;
        }

        /* plan write data */
        for (index = 0; index < fsrw1_data_len; index ++)
        {
            write_data1[index] = index;
        }

        /* write 8000 times */
        tick_start = rt_tick_get();
        for(index=0; index<8000; index++)
        {
            length = write(fd, write_data1, fsrw1_data_len);
            if (length != fsrw1_data_len)
            {
                rt_kprintf("fsrw1 write data failed\n");
                close(fd);
                fsrw1_thread = RT_NULL;
                stop_flag = 1;
                return;
            }
        }
        tick_end = rt_tick_get();
        write_speed = fsrw1_data_len*8000UL*RT_TICK_PER_SECOND/(tick_end-tick_start);

        /* close file */
        close(fd);

        /* open file read only */
        fd = open(fsrw1_fn, O_RDONLY, 0);
        if (fd < 0)
        {
            rt_kprintf("fsrw1 open file for read failed\n");
            stop_flag = 1;
            fsrw1_thread = RT_NULL;
            return;
        }

        /* verify data */
        tick_start = rt_tick_get();
        for(index=0; index<8000; index++)
        {
            rt_uint32_t i;

            length = read(fd, read_data1, fsrw1_data_len);
            if (length != fsrw1_data_len)
            {
                rt_kprintf("fsrw1 read file failed\r\n");
                close(fd);
                stop_flag = 1;
                fsrw1_thread = RT_NULL;
                return;
            }
            for(i=0; i<fsrw1_data_len; i++)
            {
                if( read_data1[i] != write_data1[i] )
                {
                    rt_kprintf("fsrw1 data error!\r\n");
                    close(fd);
                    stop_flag = 1;
                    fsrw1_thread = RT_NULL;
                    return;
                }
            }
        }
        tick_end = rt_tick_get();
        read_speed = fsrw1_data_len*8000UL*RT_TICK_PER_SECOND/(tick_end-tick_start);

        rt_kprintf("thread fsrw1 round %d ",round++);
        rt_kprintf("rd:%dbyte/s,wr:%dbyte/s\r\n",read_speed,write_speed);

        /* close file */
        close(fd);
    }
}

#define fsrw2_fn                   "/test2.dat"
#define fsrw2_data_len             180              /* Less than 256 */
static void fsrw2_thread_entry(void* parameter)
{
    int fd;
    int index,length;
    rt_uint32_t round;
    rt_uint32_t tick_start,tick_end,read_speed,write_speed;

    static rt_uint8_t write_data2[fsrw2_data_len];
    static rt_uint8_t read_data2[fsrw2_data_len];

    round = 1;

    while(1)
    {
        if( stop_flag )
        {
            rt_kprintf("thread fsrw1 error,thread fsrw2 quit!\r\n");
            fsrw2_thread = RT_NULL;
            stop_flag = 0;
            return;
        }

        /* creat file */
        fd = open(fsrw2_fn, O_WRONLY | O_CREAT | O_TRUNC, 0);
        if (fd < 0)
        {
            rt_kprintf("fsrw2 open file for write failed\n");
            stop_flag = 1;
            fsrw2_thread = RT_NULL;
            return;
        }

        /* plan write data */
        for (index = 0; index < fsrw2_data_len; index ++)
        {
            write_data2[index] = index;
        }

        /* write 5000 times */
        tick_start = rt_tick_get();
        for(index=0; index<5000; index++)
        {
            length = write(fd, write_data2, fsrw2_data_len);
            if (length != fsrw2_data_len)
            {
                rt_kprintf("fsrw2 write data failed\n");
                close(fd);
                stop_flag = 1;
                fsrw2_thread = RT_NULL;
                return;
            }
        }
        tick_end = rt_tick_get();
        write_speed = fsrw2_data_len*5000UL*RT_TICK_PER_SECOND/(tick_end-tick_start);

        /* close file */
        close(fd);

        /* open file read only */
        fd = open(fsrw2_fn, O_RDONLY, 0);
        if (fd < 0)
        {
            rt_kprintf("fsrw2 open file for read failed\n");
            stop_flag = 1;
            fsrw2_thread = RT_NULL;
            return;
        }

        /* verify data */
        tick_start = rt_tick_get();
        for(index=0; index<5000; index++)
        {
            rt_uint32_t i;

            length = read(fd, read_data2, fsrw2_data_len);
            if (length != fsrw2_data_len)
            {
                rt_kprintf("fsrw2 read file failed\r\n");
                close(fd);
                stop_flag = 1;
                fsrw2_thread = RT_NULL;
                return;
            }
            for(i=0; i<fsrw2_data_len; i++)
            {
                if( read_data2[i] != write_data2[i] )
                {
                    rt_kprintf("fsrw2 data error!\r\n");
                    close(fd);
                    stop_flag = 1;
                    fsrw2_thread = RT_NULL;
                    return;
                }
            }
        }
        tick_end = rt_tick_get();
        read_speed = fsrw2_data_len*5000UL*RT_TICK_PER_SECOND/(tick_end-tick_start);

        rt_kprintf("thread fsrw2 round %d ",round++);
        rt_kprintf("rd:%dbyte/s,wr:%dbyte/s\r\n",read_speed,write_speed);

        /* close file */
        close(fd);
    }
}


/** \brief startup filesystem read/write test(multi thread).
 *
 * \param arg rt_uint32_t [0]startup thread1,[1]startup thread2.
 * \return void
 *
 */
void fs_test(rt_uint32_t arg)
{
    rt_kprintf("arg is : 0x%02X ",arg);

    if(arg & 0x01)
    {
        if( fsrw1_thread != RT_NULL )
        {
            rt_kprintf("fsrw1_thread already exists!\r\n");
        }
        else
        {
            fsrw1_thread = rt_thread_create( "fsrw1",
                                             fsrw1_thread_entry,
                                             RT_NULL,
                                             2048,
                                             RT_THREAD_PRIORITY_MAX-2,
                                             1);
            if ( fsrw1_thread != RT_NULL)
            {
                rt_thread_startup(fsrw1_thread);
            }
        }
    }

    if( arg & 0x02)
    {
        if( fsrw2_thread != RT_NULL )
        {
            rt_kprintf("fsrw2_thread already exists!\r\n");
        }
        else
        {
            fsrw2_thread = rt_thread_create( "fsrw2",
                                             fsrw2_thread_entry,
                                             RT_NULL,
                                             2048,
                                             RT_THREAD_PRIORITY_MAX-2,
                                             1);
            if ( fsrw2_thread != RT_NULL)
            {
                rt_thread_startup(fsrw2_thread);
            }
        }
    }
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(fs_test, file system R/W test. e.g: fs_test(3));
#endif
