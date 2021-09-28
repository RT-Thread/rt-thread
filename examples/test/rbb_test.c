/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-31     armink       the first version
 */

#include <string.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <stdlib.h>

static rt_bool_t put_finish = RT_FALSE;

static void put_thread(void *param)
{
    rt_rbb_t rbb = (rt_rbb_t)param;
    rt_rbb_blk_t block;
    rt_uint8_t put_count = 0;

    put_finish = RT_FALSE;

    while (put_count < 255)
    {
        if (put_count == 10)
        {
            put_count = 10;
        }
        block = rt_rbb_blk_alloc(rbb, rand() % 10 + 1);
        if (block)
        {
            block->buf[0] = put_count++;
            rt_rbb_blk_put(block);
        }
        rt_thread_mdelay(rand() % 10);
    }
    rt_kprintf("Put block data finish.\n");

    put_finish = RT_TRUE;
}

static void get_thread(void *param)
{
    rt_rbb_t rbb = (rt_rbb_t)param;
    rt_rbb_blk_t block;
    rt_uint8_t get_count = 0;

    while (get_count < 255)
    {
        if (get_count == 10)
        {
            get_count = 10;
        }
        block = rt_rbb_blk_get(rbb);
        if (block)
        {
            if (block->buf[0] != get_count++)
            {
                rt_kprintf("Error: get data (times %d) has an error!\n", get_count);
            }
            rt_rbb_blk_free(rbb, block);
        }
        else if (put_finish)
        {
            break;
        }
        rt_thread_mdelay(rand() % 10);
    }
    rt_kprintf("Get block data finish.\n");
    rt_kprintf("\n====================== rbb dynamic test finish =====================\n");
}

void rbb_test(void)
{
    rt_rbb_t rbb;
    rt_rbb_blk_t blk1, blk2, blk3, blk4, blk5, blk6, _blk1, _blk2;
    rt_size_t i, j, k, req_size, size;
    struct rt_rbb_blk_queue blk_queue1;
    rt_thread_t thread;

    /* create ring block buffer */
    rt_kprintf("\n====================== rbb create test =====================\n");
    rbb = rt_rbb_create(52, 6);
    if (rbb)
    {
        rt_kprintf("6 blocks in 52 bytes ring block buffer object create success.\n");
    }
    else
    {
        rt_kprintf("Test error: 6 blocks in 52 bytes ring block buffer object create failed.\n");
    }
    /* allocate block */
    rt_kprintf("\n====================== rbb alloc test =====================\n");
    blk1 = rt_rbb_blk_alloc(rbb, 2);
    if (blk1 && blk1->size == 2)
    {
        memset(blk1->buf, 1, blk1->size);
        rt_kprintf("Block1 (2 bytes) allocate success.\n");
    }
    else
    {
        rt_kprintf("Test error: block1 (2 bytes) allocate failed.\n");
        goto __exit;
    }
    blk2 = rt_rbb_blk_alloc(rbb, 4);
    if (blk2 && blk2->size == 4)
    {
        memset(blk2->buf, 2, blk2->size);
        rt_kprintf("Block2 (4 bytes) allocate success.\n");
    }
    else
    {
        rt_kprintf("Test error: block2 (4 bytes) allocate failed.\n");
        goto __exit;
    }
    blk3 = rt_rbb_blk_alloc(rbb, 8);
    if (blk3 && blk3->size == 8)
    {
        memset(blk3->buf, 3, blk3->size);
        rt_kprintf("Block3 (8 bytes) allocate success.\n");
    }
    else
    {
        rt_kprintf("Test error: block3 (8 bytes) allocate failed.\n");
        goto __exit;
    }
    blk4 = rt_rbb_blk_alloc(rbb, 16);
    if (blk4 && blk4->size == 16)
    {
        memset(blk4->buf, 4, blk4->size);
        rt_kprintf("Block4 (16 bytes) allocate success.\n");
    }
    else
    {
        rt_kprintf("Test error: block4 (16 bytes) allocate failed.\n");
        goto __exit;
    }
    blk5 = rt_rbb_blk_alloc(rbb, 32);
    if (blk5 && blk5->size == 32)
    {
        memset(blk5->buf, 5, blk5->size);
        rt_kprintf("Block5 (32 bytes) allocate success.\n");
    }
    else
    {
        rt_kprintf("Block5 (32 bytes) allocate failed.\n");
    }
    blk5 = rt_rbb_blk_alloc(rbb, 18);
    if (blk5 && blk5->size == 18)
    {
        memset(blk5->buf, 5, blk5->size);
        rt_kprintf("Block5 (18 bytes) allocate success.\n");
    }
    else
    {
        rt_kprintf("Test error: block5 (18 bytes) allocate failed.\n");
        goto __exit;
    }
    rt_kprintf("Ring block buffer current status:\n");
    rt_kprintf("next block queue length: %d\n", rt_rbb_next_blk_queue_len(rbb));
    rt_kprintf("block list length: %d\n", rt_slist_len(&rbb->blk_list));
    rt_kprintf("|<- 2 -->|<-- 4 -->|<---- 8 ----->|<------- 16 -------->|<------ 18 ------>|<---- 4 ---->|\n");
    rt_kprintf("+--------+---------+--------------+---------------------+------------------+-------------+\n");
    rt_kprintf("| blcok1 | block2  |    block3    |       block4        |       block5     |    empty    |\n");
    rt_kprintf("+--------+---------+--------------+---------------------+------------------+-------------+\n");
    rt_kprintf("| inited | inited  |    inited    |       inited        |       inited     |             |\n");

    /* put block */
    rt_kprintf("\n====================== rbb put test =====================\n");
    rt_rbb_blk_put(blk1);
    rt_rbb_blk_put(blk2);
    rt_rbb_blk_put(blk3);
    rt_rbb_blk_put(blk4);
    rt_rbb_blk_put(blk5);
    rt_kprintf("Block1 to block5 put success.\n");
    rt_kprintf("Ring block buffer current status:\n");
    rt_kprintf("next block queue length: %d\n", rt_rbb_next_blk_queue_len(rbb));
    rt_kprintf("block list length: %d\n", rt_slist_len(&rbb->blk_list));
    rt_kprintf("|<- 2 -->|<-- 4 -->|<---- 8 ----->|<------- 16 -------->|<------ 18 ------>|<---- 4 ---->|\n");
    rt_kprintf("+--------+---------+--------------+---------------------+------------------+-------------+\n");
    rt_kprintf("| blcok1 | block2  |    block3    |       block4        |       block5     |    empty    |\n");
    rt_kprintf("+--------+---------+--------------+---------------------+------------------+-------------+\n");
    rt_kprintf("|  put   |  put    |     put      |        put          |        put       |             |\n");

    /* get block */
    rt_kprintf("\n====================== rbb get test =====================\n");
    _blk1 = rt_rbb_blk_get(rbb);
    _blk2 = rt_rbb_blk_get(rbb);
    for (i = 0; i < _blk1->size; i++)
    {
        if (_blk1->buf[i] != 1) break;
    }
    for (j = 0; j < _blk2->size; j++)
    {
        if (_blk2->buf[j] != 2) break;
    }
    if (blk1 == _blk1 && blk2 == _blk2 && i == _blk1->size && j == _blk2->size)
    {
        rt_kprintf("Block1 and block2 get success.\n");
    }
    else
    {
        rt_kprintf("Test error: block1 and block2 get failed.\n");
        goto __exit;
    }
    rt_kprintf("Ring block buffer current status:\n");
    rt_kprintf("next block queue length: %d\n", rt_rbb_next_blk_queue_len(rbb));
    rt_kprintf("block list length: %d\n", rt_slist_len(&rbb->blk_list));
    rt_kprintf("|<- 2 -->|<-- 4 -->|<---- 8 ----->|<------- 16 -------->|<------ 18 ------>|<---- 4 ---->|\n");
    rt_kprintf("+--------+---------+--------------+---------------------+------------------+-------------+\n");
    rt_kprintf("| blcok1 | block2  |    block3    |       block4        |       block5     |    empty    |\n");
    rt_kprintf("+--------+---------+--------------+---------------------+------------------+-------------+\n");
    rt_kprintf("|  get   |   get   |     put      |        put          |        put       |             |\n");

    /* free block */
    rt_kprintf("\n====================== rbb free test =====================\n");
    rt_rbb_blk_free(rbb, blk2);
    rt_kprintf("Block2 free success.\n");
    rt_rbb_blk_free(rbb, blk1);
    rt_kprintf("Block1 free success.\n");
    rt_kprintf("Ring block buffer current status:\n");
    rt_kprintf("next block queue length: %d\n", rt_rbb_next_blk_queue_len(rbb));
    rt_kprintf("block list length: %d\n", rt_slist_len(&rbb->blk_list));
    rt_kprintf("|<------- 6 ------>|<---- 8 ----->|<------- 16 -------->|<------ 18 ------>|<---- 4 ---->|\n");
    rt_kprintf("+------------------+--------------+---------------------+------------------+-------------+\n");
    rt_kprintf("|      empty2      |    block3    |       block4        |       block5     |    empty1   |\n");
    rt_kprintf("+------------------+--------------+---------------------+------------------+-------------+\n");
    rt_kprintf("|                  |     put      |        put          |        put       |             |\n");

    blk6 = rt_rbb_blk_alloc(rbb, 5);
    if (blk6)
    {
        rt_kprintf("Block6 (5 bytes) allocate success.\n");
    }
    else
    {
        rt_kprintf("Test error: block6 (5 bytes) allocate failed.\n");
        goto __exit;
    }

    rt_rbb_blk_put(blk6);
    rt_kprintf("Block6 put success.\n");
    rt_kprintf("Ring block buffer current status:\n");
    rt_kprintf("next block queue length: %d\n", rt_rbb_next_blk_queue_len(rbb));
    rt_kprintf("block list length: %d\n", rt_slist_len(&rbb->blk_list));
    rt_kprintf("|<--- 5 ---->|< 1 >|<---- 8 ----->|<------- 16 -------->|<------ 18 ------>|<---- 4 ---->|\n");
    rt_kprintf("+------------+-----+--------------+---------------------+------------------+-------------+\n");
    rt_kprintf("|   block6   |empty|    block3    |       block4        |       block5     |   fragment  |\n");
    rt_kprintf("+------------+-----+--------------+---------------------+------------------+-------------+\n");
    rt_kprintf("|     put    |     |     put      |        put          |        put       |             |\n");

    /* get block queue */
    rt_kprintf("\n====================== rbb block queue get test =====================\n");
    req_size = rt_rbb_next_blk_queue_len(rbb) + 5;
    size = rt_rbb_blk_queue_get(rbb, req_size, &blk_queue1);
    i = j = k = 0;
    for (; i < blk3->size; i++)
    {
        if (rt_rbb_blk_queue_buf(&blk_queue1)[i] != 3) break;
    }
    for (; j < blk4->size; j++)
    {
        if (rt_rbb_blk_queue_buf(&blk_queue1)[i + j] != 4) break;
    }
    for (; k < blk5->size; k++)
    {
        if (rt_rbb_blk_queue_buf(&blk_queue1)[i + j + k] != 5) break;
    }
    if (size && size == 42 && rt_rbb_blk_queue_len(&blk_queue1) == 42 && k == blk5->size)
    {
        rt_kprintf("Block queue (request %d bytes, actual %d) get success.\n", req_size, size);
    }
    else
    {
        rt_kprintf("Test error: Block queue (request %d bytes, actual %d) get failed.\n", req_size, size);
        goto __exit;
    }
    rt_kprintf("Ring block buffer current status:\n");
    rt_kprintf("next block queue length: %d\n", rt_rbb_next_blk_queue_len(rbb));
    rt_kprintf("block list length: %d\n", rt_slist_len(&rbb->blk_list));
    rt_kprintf("|            |     |<----- block queue1 (42 bytes continuous buffer) ----->|             |\n");
    rt_kprintf("|<--- 5 ---->|< 1 >|<---- 8 ----->|<------- 16 -------->|<------ 18 ------>|<---- 4 ---->|\n");
    rt_kprintf("+------------+-----+--------------+---------------------+------------------+-------------+\n");
    rt_kprintf("|   block6   |empty|    block3    |       block4        |       block5     |   fragment  |\n");
    rt_kprintf("+------------+-----+--------------+---------------------+------------------+-------------+\n");
    rt_kprintf("|     put    |     |     get      |        get          |        get       |             |\n");

    /* free block queue */
    rt_kprintf("\n====================== rbb block queue free test =====================\n");
    rt_rbb_blk_queue_free(rbb, &blk_queue1);
    rt_kprintf("Block queue1 free success.\n");
    rt_kprintf("Ring block buffer current status:\n");
    rt_kprintf("next block queue length: %d\n", rt_rbb_next_blk_queue_len(rbb));
    rt_kprintf("block list length: %d\n", rt_slist_len(&rbb->blk_list));
    rt_kprintf("|<--- 5 ---->|<--------------------------------- 47 ------------------------------------>|\n");
    rt_kprintf("+------------+---------------------------------------------------------------------------+\n");
    rt_kprintf("|   block6   |                                 empty                                     |\n");
    rt_kprintf("+------------+---------------------------------------------------------------------------+\n");
    rt_kprintf("|     put    |                                                                           |\n");
    rt_rbb_blk_free(rbb, blk6);

    rt_kprintf("\n====================== rbb static test SUCCESS =====================\n");

    rt_kprintf("\n====================== rbb dynamic test =====================\n");

    thread = rt_thread_create("rbb_put", put_thread, rbb, 1024, 10, 25);
    if (thread)
    {
        rt_thread_startup(thread);
    }

    thread = rt_thread_create("rbb_get", get_thread, rbb, 1024, 10, 25);
    if (thread)
    {
        rt_thread_startup(thread);
    }

__exit :

    rt_rbb_destroy(rbb);
}

MSH_CMD_EXPORT(rbb_test, run ring block buffer testcase)

