/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <stdlib.h>
#include <assert.h>

#include "FreeRTOS.h"
#include "utils_list.h"
#include "utils_ringblk.h"

/**
 * ring block buffer object initialization
 *
 * @param rbb ring block buffer object
 * @param buf buffer
 * @param buf_size buffer size
 * @param block_set block set
 * @param blk_max_num max block number
 *
 * @note When your application need align access, please make the buffer address is aligned.
 */
void utils_rbb_init(utils_rbb_t rbb, uint8_t *buf, uint32_t buf_size, utils_rbb_blk_t block_set, uint32_t blk_max_num)
{
    uint32_t i;

    assert(rbb);
    assert(buf);
    assert(block_set);

    rbb->buf = buf;
    rbb->buf_size = buf_size;
    rbb->blk_set = block_set;
    rbb->blk_max_num = blk_max_num;
    utils_slist_init(&rbb->blk_list);
    /* initialize block status */
    for (i = 0; i < blk_max_num; i++)
    {
        block_set[i].status = RBB_BLK_UNUSED;
    }
}


/**
 * ring block buffer object create
 *
 * @param buf_size buffer size
 * @param blk_max_num max block number
 *
 * @return != NULL: ring block buffer object
 *            NULL: create failed
 */
utils_rbb_t utils_rbb_create(uint32_t buf_size, uint32_t blk_max_num)
{
    utils_rbb_t rbb = NULL;
    uint8_t *buf;
    utils_rbb_blk_t blk_set;

    rbb = (utils_rbb_t)pvPortMalloc(sizeof(struct utils_rbb));
    if (!rbb)
    {
        return NULL;
    }

    buf = (uint8_t *)pvPortMalloc(buf_size);
    if (!buf)
    {
        vPortFree(rbb);
        return NULL;
    }

    blk_set = (utils_rbb_blk_t)pvPortMalloc(sizeof(struct utils_rbb_blk) * blk_max_num);
    if (!blk_set)
    {
        vPortFree(buf);
        vPortFree(rbb);
        return NULL;
    }

    utils_rbb_init(rbb, buf, buf_size, blk_set, blk_max_num);

    return rbb;
}

/**
 * ring block buffer object destroy
 *
 * @param rbb ring block buffer object
 */
void utils_rbb_destroy(utils_rbb_t rbb)
{
    assert(rbb);

    vPortFree(rbb->buf);
    vPortFree(rbb->blk_set);
    vPortFree(rbb);

}

utils_rbb_blk_t utils_rbb_find_used_blk(utils_rbb_t rbb)
{
    uint32_t i;

    assert(rbb);

    for (i = 0; i < rbb->blk_max_num; i ++)
    {
        if (rbb->blk_set[i].status != RBB_BLK_UNUSED)
        {
            return &rbb->blk_set[i];
        }
    }

    return NULL;
}

utils_rbb_blk_t utils_rbb_find_empty_blk(utils_rbb_t rbb)
{
    uint32_t i;

    assert(rbb);

    for (i = 0; i < rbb->blk_max_num; i ++)
    {
        if (rbb->blk_set[i].status == RBB_BLK_UNUSED)
        {
            return &rbb->blk_set[i];
        }
    }

    return NULL;
}

/**
 * Allocate a block by given size. The block will add to blk_list when allocate success.
 *
 * @param rbb ring block buffer object
 * @param blk_size block size
 *
 * @note When your application need align access, please make the blk_szie is aligned.
 *
 * @return != NULL: allocated block
 *            NULL: allocate failed
 */
utils_rbb_blk_t utils_rbb_blk_alloc(utils_rbb_t rbb, uint32_t blk_size)
{
    uint32_t empty1 = 0, empty2 = 0;
    utils_rbb_blk_t head, tail, new_rbb = NULL;
    int list_num = 0;

    assert(rbb);
    assert(blk_size < (1L << 24));

    portENTER_CRITICAL();

    new_rbb = utils_rbb_find_empty_blk(rbb);

    list_num = utils_slist_entry_number(&rbb->blk_list);

    if (list_num < rbb->blk_max_num && new_rbb)
    {
        if (list_num > 0)
        {
            head = utils_slist_first_entry(&rbb->blk_list, struct utils_rbb_blk, list);
            tail = utils_slist_tail_entry(&rbb->blk_list, struct utils_rbb_blk, list);
            if (head->buf <= tail->buf)
            {
                /**
                 *                      head                     tail
                 * +--------------------------------------+-----------------+------------------+
                 * |      empty2     | block1 |   block2  |      block3     |       empty1     |
                 * +--------------------------------------+-----------------+------------------+
                 *                            rbb->buf
                 */
                empty1 = (rbb->buf + rbb->buf_size) - (tail->buf + tail->size);
                empty2 = head->buf - rbb->buf;

                if (empty1 >= blk_size)
                {
                    utils_slist_append(&rbb->blk_list, &new_rbb->list);
                    new_rbb->status = RBB_BLK_INITED;
                    new_rbb->buf = tail->buf + tail->size;
                    new_rbb->size = blk_size;
                }
                else if (empty2 >= blk_size)
                {
                    utils_slist_append(&rbb->blk_list, &new_rbb->list);
                    new_rbb->status = RBB_BLK_INITED;
                    new_rbb->buf = rbb->buf;
                    new_rbb->size = blk_size;
                }
                else
                {
                    /* no space */
                    new_rbb = NULL;
                }
            }
            else
            {
                /**
                 *        tail                                              head
                 * +----------------+-------------------------------------+--------+-----------+
                 * |     block3     |                empty1               | block1 |  block2   |
                 * +----------------+-------------------------------------+--------+-----------+
                 *                            rbb->buf
                 */
                empty1 = head->buf - (tail->buf + tail->size);

                if (empty1 >= blk_size)
                {
                    utils_slist_append(&rbb->blk_list, &new_rbb->list);
                    new_rbb->status = RBB_BLK_INITED;
                    new_rbb->buf = tail->buf + tail->size;
                    new_rbb->size = blk_size;
                }
                else
                {
                    /* no space */
                    new_rbb = NULL;
                }
            }
        }
        else
        {
            /* the list is empty */
            utils_slist_append(&rbb->blk_list, &new_rbb->list);
            new_rbb->status = RBB_BLK_INITED;
            new_rbb->buf = rbb->buf;
            new_rbb->size = blk_size;
        }
    }
    else
    {
        new_rbb = NULL;
    }

    portEXIT_CRITICAL();

    return new_rbb;
}

/**
 * put a block to ring block buffer object
 *
 * @param block the block
 */
void utils_rbb_blk_put(utils_rbb_blk_t block)
{
    assert(block);
    assert(block->status == RBB_BLK_INITED);

    block->status = RBB_BLK_PUT;
}

/**
 * get a block from the ring block buffer object
 *
 * @param rbb ring block buffer object
 *
 * @return != NULL: block
 *            NULL: get failed
 */
utils_rbb_blk_t utils_rbb_blk_get(utils_rbb_t rbb)
{
    utils_rbb_blk_t block = NULL;
    utils_slist_t *node;

    assert(rbb);

    if (utils_slist_empty(&rbb->blk_list))
        return 0;

    portENTER_CRITICAL();

    for (node = utils_slist_first(&rbb->blk_list); node; node = utils_slist_next(node))
    {
        block = utils_slist_entry(node, struct utils_rbb_blk, list);
        if (block->status == RBB_BLK_PUT)
        {
            block->status = RBB_BLK_GET;
            goto __exit;
        }
    }
    /* not found */
    block = NULL;

__exit:

    portEXIT_CRITICAL();

    return block;
}

/**
 * return the block size
 *
 * @param block the block
 *
 * @return block size
 */
uint32_t utils_rbb_blk_size(utils_rbb_blk_t block)
{
    assert(block);

    return block->size;
}

/**
 * return the block buffer
 *
 * @param block the block
 *
 * @return block buffer
 */
uint8_t *utils_rbb_blk_buf(utils_rbb_blk_t block)
{
    assert(block);

    return block->buf;
}

/**
 * free the block
 *
 * @param rbb ring block buffer object
 * @param block the block
 */
void utils_rbb_blk_free(utils_rbb_t rbb, utils_rbb_blk_t block)
{
    assert(rbb);
    assert(block);
    assert(block->status != RBB_BLK_UNUSED);

    portENTER_CRITICAL();

    /* remove it on rbb block list */
    utils_slist_del(&block->list, &rbb->blk_list);

    block->status = RBB_BLK_UNUSED;

    portEXIT_CRITICAL();
}

/**
 * get a continuous block to queue by given size
 *
 *          tail                         head
 * +------------------+---------------+--------+----------+--------+
 * |      block3      |  empty1       | block1 |  block2  |fragment|
 * +------------------+------------------------+----------+--------+
 *                                    |<-- return_size -->|    |
 *                                    |<--- queue_data_len --->|
 *
 *         tail                          head
 * +------------------+---------------+--------+----------+--------+
 * |      block3      |  empty1       | block1 |  block2  |fragment|
 * +------------------+------------------------+----------+--------+
 *                                    |<-- return_size -->|              out of len(b1+b2+b3)    |
 *                                    |<-------------------- queue_data_len -------------------->|
 *
 * @param rbb ring block buffer object
 * @param queue_data_len The max queue data size, and the return size must less then it.
 * @param queue continuous block queue
 *
 * @return the block queue data total size
 */
uint32_t utils_rbb_blk_queue_get(utils_rbb_t rbb, uint32_t queue_data_len, utils_rbb_blk_queue_t blk_queue)
{
    uint32_t data_total_size = 0;
    utils_slist_t *node;
    utils_rbb_blk_t last_block = NULL, block;

    assert(rbb);
    assert(blk_queue);

    if (utils_slist_empty(&rbb->blk_list))
        return 0;

    portENTER_CRITICAL();

    for (node = utils_slist_first(&rbb->blk_list); node; node = utils_slist_next(node))
    {
        if (!last_block)
        {
            last_block = utils_slist_entry(node, struct utils_rbb_blk, list);
            if (last_block->status == RBB_BLK_PUT)
            {
                /* save the first put status block to queue */
                blk_queue->blocks = last_block;
                blk_queue->blk_num = 0;
            }
            else
            {
                /* the first block must be put status */
                last_block = NULL;
                continue;
            }
        }
        else
        {
            block = utils_slist_entry(node, struct utils_rbb_blk, list);
            /*
             * these following conditions will break the loop:
             * 1. the current block is not put status
             * 2. the last block and current block is not continuous
             * 3. the data_total_size will out of range
             */
            if (block->status != RBB_BLK_PUT ||
                last_block->buf > block->buf ||
                data_total_size + block->size > queue_data_len)
            {
                break;
            }
            /* backup last block */
            last_block = block;
        }
        /* remove current block */
        utils_slist_del(&last_block->list, &rbb->blk_list);
        data_total_size += last_block->size;
        last_block->status = RBB_BLK_GET;
        blk_queue->blk_num++;
    }

    portEXIT_CRITICAL();

    return data_total_size;
}

/**
 * get all block length on block queue
 *
 * @param blk_queue the block queue
 *
 * @return total length
 */
uint32_t utils_rbb_blk_queue_len(utils_rbb_blk_queue_t blk_queue)
{
    uint32_t i, data_total_size = 0;

    assert(blk_queue);

    for (i = 0; i < blk_queue->blk_num; i++)
    {
        data_total_size += blk_queue->blocks[i].size;
    }

    return data_total_size;
}

/**
 * return the block queue buffer
 *
 * @param blk_queue the block queue
 *
 * @return block queue buffer
 */
uint8_t *utils_rbb_blk_queue_buf(utils_rbb_blk_queue_t blk_queue)
{
    assert(blk_queue);

    return blk_queue->blocks[0].buf;
}

/**
 * free the block queue
 *
 * @param rbb ring block buffer object
 * @param blk_queue the block queue
 */
void utils_rbb_blk_queue_free(utils_rbb_t rbb, utils_rbb_blk_queue_t blk_queue)
{
    uint32_t i;

    assert(rbb);
    assert(blk_queue);

    for (i = 0; i < blk_queue->blk_num; i++)
    {
        utils_rbb_blk_free(rbb, &blk_queue->blocks[i]);
    }
}

/**
 * The put status and buffer continuous blocks can be make a block queue.
 * This function will return the length which from next can be make block queue.
 *
 * @param rbb ring block buffer object
 *
 * @return the next can be make block queue's length
 */
uint32_t utils_rbb_next_blk_queue_len(utils_rbb_t rbb)
{
    uint32_t data_len = 0;
    utils_slist_t *node;
    utils_rbb_blk_t last_block = NULL, block;

    assert(rbb);

    if (utils_slist_empty(&rbb->blk_list))
        return 0;

    portENTER_CRITICAL();

    for (node = utils_slist_first(&rbb->blk_list); node; node = utils_slist_next(node))
    {
        if (!last_block)
        {
            last_block = utils_slist_entry(node, struct utils_rbb_blk, list);
            if (last_block->status != RBB_BLK_PUT)
            {
                /* the first block must be put status */
                last_block = NULL;
                continue;
            }
        }
        else
        {
            block = utils_slist_entry(node, struct utils_rbb_blk, list);
            /*
             * these following conditions will break the loop:
             * 1. the current block is not put status
             * 2. the last block and current block is not continuous
             */
            if (block->status != RBB_BLK_PUT || last_block->buf > block->buf)
            {
                break;
            }
            /* backup last block */
            last_block = block;
        }
        data_len += last_block->size;
    }

    portEXIT_CRITICAL();

    return data_len;
}

/**
 * get the ring block buffer object buffer size
 *
 * @param rbb ring block buffer object
 *
 * @return buffer size
 */
uint32_t utils_rbb_get_buf_size(utils_rbb_t rbb)
{
    assert(rbb);

    return rbb->buf_size;
}
