/*
 * File      : lwp.h
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

#ifndef __LWP_H__
#define __LWP_H__

#define LWP_MAGIC           0x5A

#define LWP_TYPE_FIX_ADDR   0x01
#define LWP_TYPE_DYN_ADDR   0x02

#define LWP_ARG_MAX         8

#include <stdint.h>
#include <rtthread.h>
#include <dfs.h>
#include <lwp_memheap.h>

struct rt_lwp
{
    uint8_t lwp_type;
    uint8_t heap_cnt;
    uint8_t reserv[2];

    rt_list_t hlist;                                    /**< headp list */

    uint8_t *text_entry;
    uint32_t text_size;

    uint8_t *data;
    uint32_t data_size;

    uint32_t *kernel_sp;                                /**< kernel stack point */
    struct dfs_fdtable fdt;
};

struct lwp_header
{
    uint8_t magic;
    uint8_t compress_encrypt_algo;
    uint16_t reserved;

    uint32_t crc32;
};

struct lwp_chunk
{
    uint32_t total_len;

    char name[4];
    uint32_t data_len;
    uint32_t data_len_space;
};

extern struct rt_lwp *rt_lwp_self(void);

extern void rt_lwp_mem_init(struct rt_lwp *lwp);
extern void rt_lwp_mem_deinit(struct rt_lwp *lwp);
extern void *rt_lwp_mem_malloc(rt_uint32_t size);
extern void rt_lwp_mem_free(void *addr);
extern void *rt_lwp_mem_realloc(void *rmem, rt_size_t newsize);

#endif
