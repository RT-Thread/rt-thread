/*
 * File      : clock.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include <rthw.h>
#include <dfs_posix.h>

#ifdef RT_USING_FINSH
    #include <finsh.h>
#endif

#ifndef RT_USING_DFS
    #error  "lwp need file system(RT_USING_DFS)"
#endif

#include "lwp.h"

#define DBG_ENABLE
#define DBG_SECTION_NAME    "[LWP]"
#define DBG_COLOR
#define DBG_LEVEL           DBG_LOG
#include <rtdbg.h>

extern rt_thread_t rt_current_thread;
extern void lwp_user_entry(const void *text, void *data);

/**
 * RT-Thread light-weight process
 */
void lwp_set_kernel_sp(uint32_t *sp)
{
    struct rt_lwp *user_data;
    user_data = (struct rt_lwp *)rt_current_thread->user_data;
    user_data->kernel_sp = sp;
}

uint32_t *lwp_get_kernel_sp(void)
{
    struct rt_lwp *user_data;
    user_data = (struct rt_lwp *)rt_current_thread->user_data;

    return user_data->kernel_sp;
}

static int lwp_load(const char *filename, struct rt_lwp *lwp, uint8_t *load_addr, size_t addr_size)
{
    int fd;
    uint8_t *ptr;
    int result = RT_EOK;
    int nbytes;
    struct lwp_header header;
    struct lwp_chunk  chunk;

    /* check file name */
    RT_ASSERT(filename != RT_NULL);
    /* check lwp control block */
    RT_ASSERT(lwp != RT_NULL);

    memset(lwp, 0x00, sizeof(struct rt_lwp));

    if (load_addr != RT_NULL)
    {
        lwp->lwp_type = LWP_TYPE_FIX_ADDR;
        ptr = load_addr;
    }
    else
    {
        lwp->lwp_type = LWP_TYPE_DYN_ADDR;
        ptr = RT_NULL;
    }

    /* open lwp */
    fd = open(filename, 0, O_RDONLY);
    if (fd < 0)
    {
        dbg_log(DBG_ERROR, "open file:%s failed!\n", filename);
        result = -RT_ENOSYS;
        goto _exit;
    }

    /* read lwp header */
    nbytes = read(fd, &header, sizeof(struct lwp_header));
    if (nbytes != sizeof(struct lwp_header))
    {
        dbg_log(DBG_ERROR, "read lwp header return error size: %d!\n", nbytes);
        result = -RT_EIO;
        goto _exit;
    }

    /* check file header */
    if (header.magic != LWP_MAGIC)
    {
        dbg_log(DBG_ERROR, "erro header magic number: 0x%02X\n", header.magic);
        result = -RT_EINVAL;
        goto _exit;
    }

    /* read text chunk info */
    nbytes = read(fd, &chunk, sizeof(struct lwp_chunk));
    if (nbytes != sizeof(struct lwp_chunk))
    {
        dbg_log(DBG_ERROR, "read text chunk info failed!\n");
        result = -RT_EIO;
        goto _exit;
    }

    dbg_log(DBG_LOG, "chunk name: %s, total len %d, data %d, need space %d!\n",
            "text", /*chunk.name*/ chunk.total_len, chunk.data_len, chunk.data_len_space);

    /* load text */
    {
        lwp->text_size = RT_ALIGN(chunk.data_len_space, 4);
        if (load_addr)
            lwp->text_entry = ptr;
        else
        {
#ifdef RT_USING_CACHE
            lwp->text_entry = (rt_uint8_t *)rt_malloc_align(lwp->text_size, RT_CPU_CACHE_LINE_SZ);
#else
            lwp->text_entry = (rt_uint8_t *)rt_malloc(lwp->text_size);
#endif

            if (lwp->text_entry == RT_NULL)
            {
                dbg_log(DBG_ERROR, "alloc text memory faild!\n");
                result = -RT_ENOMEM;
                goto _exit;
            }
            else
            {
                dbg_log(DBG_LOG, "lwp text malloc : %p, size: %d!\n", lwp->text_entry, lwp->text_size);
            }
        }
        dbg_log(DBG_INFO, "load text %d  => (0x%08x, 0x%08x)\n", lwp->text_size, (uint32_t)lwp->text_entry, (uint32_t)lwp->text_entry + lwp->text_size);

        nbytes = read(fd, lwp->text_entry, chunk.data_len);
        if (nbytes != chunk.data_len)
        {
            dbg_log(DBG_ERROR, "read text region from file failed!\n");
            result = -RT_EIO;
            goto _exit;
        }
#ifdef RT_USING_CACHE
        else
        {
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, lwp->text_entry, lwp->text_size);
            rt_hw_cpu_icache_ops(RT_HW_CACHE_INVALIDATE, lwp->text_entry, lwp->text_size);
        }
#endif

        if (ptr != RT_NULL) ptr += nbytes;

        /* skip text hole */
        if ((chunk.total_len - sizeof(struct lwp_chunk) - chunk.data_len))
        {
            dbg_log(DBG_LOG, "skip text hole %d!\n", (chunk.total_len - sizeof(struct lwp_chunk) - chunk.data_len));
            lseek(fd, (chunk.total_len - sizeof(struct lwp_chunk) - chunk.data_len), SEEK_CUR);
        }
    }

    /* load data */
    nbytes = read(fd, &chunk, sizeof(struct lwp_chunk));
    if (nbytes != sizeof(struct lwp_chunk))
    {
        dbg_log(DBG_ERROR, "read data chunk info failed!\n");
        result = -RT_EIO;
        goto _exit;
    }

    dbg_log(DBG_LOG, "chunk name: %s, total len %d, data %d, need space %d!\n",
            chunk.name, chunk.total_len, chunk.data_len, chunk.data_len_space);

    {
        lwp->data_size = RT_ALIGN(chunk.data_len_space, 4);
        if (load_addr)
            lwp->data = ptr;
        else
        {
            lwp->data = rt_malloc(lwp->data_size);
            if (lwp->data == RT_NULL)
            {
                dbg_log(DBG_ERROR, "alloc data memory faild!\n");
                result = -RT_ENOMEM;
                goto _exit;
            }
            else
            {
                dbg_log(DBG_LOG, "lwp data malloc : %p, size: %d!\n", lwp->data, lwp->data_size);
                rt_memset(lwp->data, 0, lwp->data_size);
            }
        }

        dbg_log(DBG_INFO, "load data %d => (0x%08x, 0x%08x)\n", lwp->data_size, (uint32_t)lwp->data, (uint32_t)lwp->data + lwp->data_size);
        nbytes = read(fd, lwp->data, chunk.data_len);
        if (nbytes != chunk.data_len)
        {
            dbg_log(DBG_ERROR, "read data region from file failed!\n");
            result = -RT_ERROR;
            goto _exit;
        }
    }

_exit:
    if (fd >= 0)
        close(fd);

    if (result != RT_EOK)
    {
        if (lwp->lwp_type == LWP_TYPE_DYN_ADDR)
        {
            dbg_log(DBG_ERROR, "lwp dynamic load faild, %d\n", result);
            if (lwp->text_entry)
            {
                dbg_log(DBG_LOG, "lwp text free: %p\n", lwp->text_entry);
#ifdef RT_USING_CACHE
                rt_free_align(lwp->text_entry);
#else
                rt_free(lwp->text_entry);
#endif
            }
            if (lwp->data)
            {
                dbg_log(DBG_LOG, "lwp data free: %p\n", lwp->data);
                rt_free(lwp->data);
            }
        }
    }

    return result;
}

static void lwp_cleanup(struct rt_thread *tid)
{
    struct rt_lwp *lwp;

    dbg_log(DBG_INFO, "thread: %s, stack_addr: %08X\n", tid->name, tid->stack_addr);

    lwp = (struct rt_lwp *)tid->user_data;

    if (lwp->lwp_type == LWP_TYPE_DYN_ADDR)
    {
        dbg_log(DBG_INFO, "dynamic lwp\n");
        if (lwp->text_entry)
        {
            dbg_log(DBG_LOG, "lwp text free: %p\n", lwp->text_entry);
#ifdef RT_USING_CACHE
            rt_free_align(lwp->text_entry);
#else
            rt_free(lwp->text_entry);
#endif
        }
        if (lwp->data)
        {
            dbg_log(DBG_LOG, "lwp data free: %p\n", lwp->data);
            rt_free(lwp->data);
        }
    }

    dbg_log(DBG_LOG, "lwp free memory pages\n");
    rt_lwp_mem_deinit(lwp);

    dbg_log(DBG_LOG, "lwp free: %p\n", lwp);
    rt_free(lwp);

    /* TODO: cleanup fd table */
}

static void lwp_thread(void *parameter)
{
    volatile uint32_t tmp;
    rt_thread_t tid;
    struct rt_lwp *lwp;

    rt_kprintf("%08x %08x\n", &tmp, tmp);

    lwp = (struct rt_lwp *)parameter;
    rt_lwp_mem_init(lwp);
    tid = rt_thread_self();
    tid->user_data = (rt_uint32_t)lwp;
    tid->cleanup = lwp_cleanup;

    lwp_user_entry(lwp->text_entry, lwp->data);
}

struct rt_lwp *rt_lwp_self(void)
{
    return (struct rt_lwp *)rt_thread_self()->user_data;
}

int exec(char *filename)
{
    struct rt_lwp *lwp;
    int result;

    if (filename == RT_NULL)
        return -RT_ERROR;

    lwp = (struct rt_lwp *)rt_malloc(sizeof(struct rt_lwp));
    if (lwp == RT_NULL)
    {
        dbg_log(DBG_ERROR, "lwp struct out of memory!\n");
        return -RT_ENOMEM;
    }
    dbg_log(DBG_INFO, "lwp malloc : %p, size: %d!\n", lwp, sizeof(struct rt_lwp));

    rt_memset(lwp, 0, sizeof(*lwp));
    result = lwp_load(filename, lwp, RT_NULL, 0);
    if (result == RT_EOK)
    {
        rt_thread_t tid;

        tid = rt_thread_create("user", lwp_thread, (void *)lwp,
                               1024 * 4, 2, 200);
        if (tid != RT_NULL)
        {
            dbg_log(DBG_LOG, "lwp kernel => (0x%08x, 0x%08x)\n", (rt_uint32_t)tid->stack_addr, (rt_uint32_t)tid->stack_addr + tid->stack_size);
            rt_thread_startup(tid);
            return RT_EOK;
        }
        else
        {
#ifdef RT_USING_CACHE
            rt_free_align(lwp->text_entry);
#else
            rt_free(lwp->text_entry);
#endif
            rt_free(lwp->data);
        }
    }

    rt_free(lwp);

    return -RT_ERROR;
}
