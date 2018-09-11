/*
 * File      : ringblk_buf.h
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
 * 2018-08-25     armink       the first version
 */

#ifndef _RINGBLK_BUF_H_
#define _RINGBLK_BUF_H_

/*
 * Introduction:
 * The rbb is the ring buffer which is composed with many blocks. It is different from the ring buffer.
 * The ring buffer is only composed with chars. The rbb put and get supported zero copies. So the rbb
 * is very suitable for put block and get block by a certain order. Such as DMA block transmit,
 * communicate frame send/recv, and so on.
 */

#ifdef __cplusplus
extern "C" {
#endif

enum rt_rbb_status
{
    /* unused status when first initialize or after blk_free() */
    RT_RBB_BLK_UNUSED,
    /* initialized status after blk_alloc() */
    RT_RBB_BLK_INITED,
    /* put status after blk_put() */
    RT_RBB_BLK_PUT,
    /* get status after blk_get() */
    RT_RBB_BLK_GET,
};
typedef enum rt_rbb_status rt_rbb_status_t;

/**
 * the block of rbb
 */
struct rt_rbb_blk
{
    rt_rbb_status_t status :8;
    /* less then 2^24 */
    rt_size_t size :24;
    rt_uint8_t *buf;
    rt_slist_t list;
};
typedef struct rt_rbb_blk *rt_rbb_blk_t;

/**
 * Rbb block queue: the blocks (from block1->buf to blockn->buf) memory which on this queue is continuous.
 */
struct rt_rbb_blk_queue
{
    rt_rbb_blk_t blocks;
    rt_size_t blk_num;
};
typedef struct rt_rbb_blk_queue *rt_rbb_blk_queue_t;

/**
 * ring block buffer
 */
struct rt_rbb
{
    rt_uint8_t *buf;
    rt_size_t buf_size;
    /* all of blocks */
    rt_rbb_blk_t blk_set;
    rt_size_t blk_max_num;
    /* saved the initialized and put status blocks */
    rt_slist_t blk_list;
};
typedef struct rt_rbb *rt_rbb_t;

/* rbb (ring block buffer) API */
void rt_rbb_init(rt_rbb_t rbb, rt_uint8_t *buf, rt_size_t buf_size, rt_rbb_blk_t block_set, rt_size_t blk_max_num);
rt_rbb_t rt_rbb_create(rt_size_t buf_size, rt_size_t blk_max_num);
void rt_rbb_destroy(rt_rbb_t rbb);
rt_size_t rt_rbb_get_buf_size(rt_rbb_t rbb);

/* rbb block API */
rt_rbb_blk_t rt_rbb_blk_alloc(rt_rbb_t rbb, rt_size_t blk_size);
void rt_rbb_blk_put(rt_rbb_blk_t block);
rt_rbb_blk_t rt_rbb_blk_get(rt_rbb_t rbb);
void rt_rbb_blk_free(rt_rbb_t rbb, rt_rbb_blk_t block);

/* rbb block queue API */
rt_size_t rt_rbb_blk_queue_get(rt_rbb_t rbb, rt_size_t queue_data_len, rt_rbb_blk_queue_t blk_queue);
rt_size_t rt_rbb_blk_queue_len(rt_rbb_blk_queue_t blk_queue);
rt_uint8_t *rt_rbb_blk_queue_buf(rt_rbb_blk_queue_t blk_queue);
void rt_rbb_blk_queue_free(rt_rbb_t rbb, rt_rbb_blk_queue_t blk_queue);
rt_size_t rt_rbb_next_blk_queue_len(rt_rbb_t rbb);


#ifdef __cplusplus
}
#endif

#endif /* _RINGBLK_BUF_H_ */
