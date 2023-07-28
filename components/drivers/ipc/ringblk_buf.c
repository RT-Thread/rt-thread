/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-25     armink       the first version
 */

#include <rthw.h>
#include <rtdevice.h>

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
void rt_rbb_init(rt_rbb_t rbb, rt_uint8_t *buf, rt_size_t buf_size, rt_rbb_blk_t block_set, rt_size_t blk_max_num)
{
    rt_size_t i;

    RT_ASSERT(rbb);
    RT_ASSERT(buf);
    RT_ASSERT(block_set);

    rbb->buf = buf;
    rbb->buf_size = buf_size;
    rbb->blk_set = block_set;
    rbb->blk_max_num = blk_max_num;
    rbb->tail = &rbb->blk_list;
    rt_slist_init(&rbb->blk_list);
    rt_slist_init(&rbb->free_list);
    /* initialize block status */
    for (i = 0; i < blk_max_num; i++)
    {
        block_set[i].status = RT_RBB_BLK_UNUSED;
        rt_slist_init(&block_set[i].list);
        rt_slist_insert(&rbb->free_list, &block_set[i].list);
    }
}
RTM_EXPORT(rt_rbb_init);

#ifdef RT_USING_HEAP

/**
 * ring block buffer object create
 *
 * @param buf_size buffer size
 * @param blk_max_num max block number
 *
 * @return != RT_NULL: ring block buffer object
 *            RT_NULL: create failed
 */
rt_rbb_t rt_rbb_create(rt_size_t buf_size, rt_size_t blk_max_num)
{
    rt_rbb_t rbb = RT_NULL;
    rt_uint8_t *buf;
    rt_rbb_blk_t blk_set;

    rbb = (rt_rbb_t)rt_malloc(sizeof(struct rt_rbb));
    if (!rbb)
    {
        return RT_NULL;
    }

    buf = (rt_uint8_t *)rt_malloc(buf_size);
    if (!buf)
    {
        rt_free(rbb);
        return RT_NULL;
    }

    blk_set = (rt_rbb_blk_t)rt_malloc(sizeof(struct rt_rbb_blk) * blk_max_num);
    if (!blk_set)
    {
        rt_free(buf);
        rt_free(rbb);
        return RT_NULL;
    }

    rt_rbb_init(rbb, buf, buf_size, blk_set, blk_max_num);

    return rbb;
}
RTM_EXPORT(rt_rbb_create);

/**
 * ring block buffer object destroy
 *
 * @param rbb ring block buffer object
 */
void rt_rbb_destroy(rt_rbb_t rbb)
{
    RT_ASSERT(rbb);

    rt_free(rbb->buf);
    rt_free(rbb->blk_set);
    rt_free(rbb);

}
RTM_EXPORT(rt_rbb_destroy);

#endif

static rt_rbb_blk_t find_empty_blk_in_set(rt_rbb_t rbb)
{
    struct rt_rbb_blk *blk;

    RT_ASSERT(rbb);

    if (rt_slist_isempty(&rbb->free_list))
    {
        return RT_NULL;
    }
    blk = rt_slist_first_entry(&rbb->free_list, struct rt_rbb_blk, list);
    rt_slist_remove(&rbb->free_list, &blk->list);
    RT_ASSERT(blk->status == RT_RBB_BLK_UNUSED);
    return blk;
}

rt_inline void list_append(rt_rbb_t rbb, rt_slist_t *n)
{
    /* append the node to the tail */
    rbb->tail->next = n;
    n->next = RT_NULL;
    /* save tail node */
    rbb->tail = n;
}

rt_inline rt_slist_t *list_remove(rt_rbb_t rbb, rt_slist_t *n)
{
    rt_slist_t *l = &rbb->blk_list;
    struct rt_slist_node *node = l;

    /* remove slist head */
    while (node->next && node->next != n) node = node->next;
    /* remove node */
    if (node->next != (rt_slist_t *)0)
    {
        node->next = node->next->next;
        n->next = RT_NULL;
        /* update tail node */
        if (rbb->tail == n)
            rbb->tail = node;
    }
    return l;
}

/**
 * Allocate a block by given size. The block will add to blk_list when allocate success.
 *
 * @param rbb ring block buffer object
 * @param blk_size block size
 *
 * @note When your application need align access, please make the blk_szie is aligned.
 *
 * @return != RT_NULL: allocated block
 *            RT_NULL: allocate failed
 */
rt_rbb_blk_t rt_rbb_blk_alloc(rt_rbb_t rbb, rt_size_t blk_size)
{
    rt_base_t level;
    rt_size_t empty1 = 0, empty2 = 0;
    rt_rbb_blk_t head, tail, new_rbb = RT_NULL;

    RT_ASSERT(rbb);
    RT_ASSERT(blk_size < (1L << 24));

    level = rt_hw_interrupt_disable();

    new_rbb = find_empty_blk_in_set(rbb);

    if (new_rbb)
    {
        if (rt_slist_isempty(&rbb->blk_list) == 0)
        {
            head = rt_slist_first_entry(&rbb->blk_list, struct rt_rbb_blk, list);
            /* get tail rbb blk object */
            tail = rt_slist_entry(rbb->tail, struct rt_rbb_blk, list);
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
                    list_append(rbb, &new_rbb->list);
                    new_rbb->status = RT_RBB_BLK_INITED;
                    new_rbb->buf = tail->buf + tail->size;
                    new_rbb->size = blk_size;
                }
                else if (empty2 >= blk_size)
                {
                    list_append(rbb, &new_rbb->list);
                    new_rbb->status = RT_RBB_BLK_INITED;
                    new_rbb->buf = rbb->buf;
                    new_rbb->size = blk_size;
                }
                else
                {
                    /* no space */
                    new_rbb = RT_NULL;
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
                    list_append(rbb, &new_rbb->list);
                    new_rbb->status = RT_RBB_BLK_INITED;
                    new_rbb->buf = tail->buf + tail->size;
                    new_rbb->size = blk_size;
                }
                else
                {
                    /* no space */
                    new_rbb = RT_NULL;
                }
            }
        }
        else
        {
            /* the list is empty */
            list_append(rbb, &new_rbb->list);
            new_rbb->status = RT_RBB_BLK_INITED;
            new_rbb->buf = rbb->buf;
            new_rbb->size = blk_size;
        }
    }
    else
    {
        new_rbb = RT_NULL;
    }

    rt_hw_interrupt_enable(level);

    return new_rbb;
}
RTM_EXPORT(rt_rbb_blk_alloc);

/**
 * put a block to ring block buffer object
 *
 * @param block the block
 */
void rt_rbb_blk_put(rt_rbb_blk_t block)
{
    RT_ASSERT(block);
    RT_ASSERT(block->status == RT_RBB_BLK_INITED);

    block->status = RT_RBB_BLK_PUT;
}
RTM_EXPORT(rt_rbb_blk_put);

/**
 * get a block from the ring block buffer object
 *
 * @param rbb ring block buffer object
 *
 * @return != RT_NULL: block
 *            RT_NULL: get failed
 */
rt_rbb_blk_t rt_rbb_blk_get(rt_rbb_t rbb)
{
    rt_base_t level;
    rt_rbb_blk_t block = RT_NULL;
    rt_slist_t *node;

    RT_ASSERT(rbb);

    if (rt_slist_isempty(&rbb->blk_list))
        return 0;

    level = rt_hw_interrupt_disable();

    for (node = rt_slist_first(&rbb->blk_list); node; node = rt_slist_next(node))
    {
        block = rt_slist_entry(node, struct rt_rbb_blk, list);
        if (block->status == RT_RBB_BLK_PUT)
        {
            block->status = RT_RBB_BLK_GET;
            goto __exit;
        }
    }
    /* not found */
    block = RT_NULL;

__exit:

    rt_hw_interrupt_enable(level);

    return block;
}
RTM_EXPORT(rt_rbb_blk_get);

/**
 * return the block size
 *
 * @param block the block
 *
 * @return block size
 */
rt_size_t rt_rbb_blk_size(rt_rbb_blk_t block)
{
    RT_ASSERT(block);

    return block->size;
}
RTM_EXPORT(rt_rbb_blk_size);

/**
 * return the block buffer
 *
 * @param block the block
 *
 * @return block buffer
 */
rt_uint8_t *rt_rbb_blk_buf(rt_rbb_blk_t block)
{
    RT_ASSERT(block);

    return block->buf;
}
RTM_EXPORT(rt_rbb_blk_buf);

/**
 * free the block
 *
 * @param rbb ring block buffer object
 * @param block the block
 */
void rt_rbb_blk_free(rt_rbb_t rbb, rt_rbb_blk_t block)
{
    rt_base_t level;

    RT_ASSERT(rbb);
    RT_ASSERT(block);
    RT_ASSERT(block->status != RT_RBB_BLK_UNUSED);

    level = rt_hw_interrupt_disable();
    /* remove it on rbb block list */
    list_remove(rbb, &block->list);
    block->status = RT_RBB_BLK_UNUSED;
    rt_slist_insert(&rbb->free_list, &block->list);
    rt_hw_interrupt_enable(level);
}
RTM_EXPORT(rt_rbb_blk_free);

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
rt_size_t rt_rbb_blk_queue_get(rt_rbb_t rbb, rt_size_t queue_data_len, rt_rbb_blk_queue_t blk_queue)
{
    rt_base_t level;
    rt_size_t data_total_size = 0;
    rt_slist_t *node, *tmp = RT_NULL;
    rt_rbb_blk_t last_block = RT_NULL, block;

    RT_ASSERT(rbb);
    RT_ASSERT(blk_queue);

    if (rt_slist_isempty(&rbb->blk_list))
        return 0;

    level = rt_hw_interrupt_disable();

    node = rt_slist_first(&rbb->blk_list);
    if (node != RT_NULL)
    {
        tmp = rt_slist_next(node);
    }
    for (; node; node = tmp, tmp = rt_slist_next(node))
    {
        if (!last_block)
        {
            last_block = rt_slist_entry(node, struct rt_rbb_blk, list);
            if (last_block->status == RT_RBB_BLK_PUT)
            {
                /* save the first put status block to queue */
                blk_queue->blocks = last_block;
                blk_queue->blk_num = 0;
            }
            else
            {
                /* the first block must be put status */
                last_block = RT_NULL;
                continue;
            }
        }
        else
        {
            block = rt_slist_entry(node, struct rt_rbb_blk, list);
            /*
             * these following conditions will break the loop:
             * 1. the current block is not put status
             * 2. the last block and current block is not continuous
             * 3. the data_total_size will out of range
             */
            if (block->status != RT_RBB_BLK_PUT ||
                    last_block->buf > block->buf ||
                    data_total_size + block->size > queue_data_len)
            {
                break;
            }
            /* backup last block */
            last_block = block;
        }
        /* remove current block */
        data_total_size += last_block->size;
        last_block->status = RT_RBB_BLK_GET;
        blk_queue->blk_num++;
    }

    rt_hw_interrupt_enable(level);

    return data_total_size;
}
RTM_EXPORT(rt_rbb_blk_queue_get);

/**
 * get all block length on block queue
 *
 * @param blk_queue the block queue
 *
 * @return total length
 */
rt_size_t rt_rbb_blk_queue_len(rt_rbb_blk_queue_t blk_queue)
{
    rt_size_t i = 0, data_total_size = 0;
    rt_rbb_blk_t blk;

    RT_ASSERT(blk_queue);

    for (blk = blk_queue->blocks; i < blk_queue->blk_num; i++)
    {
        data_total_size += blk->size;
        blk = rt_slist_entry(blk->list.next, struct rt_rbb_blk, list);
    }
    return data_total_size;
}
RTM_EXPORT(rt_rbb_blk_queue_len);

/**
 * return the block queue buffer
 *
 * @param blk_queue the block queue
 *
 * @return block queue buffer
 */
rt_uint8_t *rt_rbb_blk_queue_buf(rt_rbb_blk_queue_t blk_queue)
{
    RT_ASSERT(blk_queue);

    return blk_queue->blocks[0].buf;
}
RTM_EXPORT(rt_rbb_blk_queue_buf);

/**
 * free the block queue
 *
 * @param rbb ring block buffer object
 * @param blk_queue the block queue
 */
void rt_rbb_blk_queue_free(rt_rbb_t rbb, rt_rbb_blk_queue_t blk_queue)
{
    rt_size_t i = 0;
    rt_rbb_blk_t blk, next_blk;

    RT_ASSERT(rbb);
    RT_ASSERT(blk_queue);

    for (blk = blk_queue->blocks; i < blk_queue->blk_num; i++)
    {
        next_blk = rt_slist_entry(blk->list.next, struct rt_rbb_blk, list);
        rt_rbb_blk_free(rbb, blk);
        blk = next_blk;
    }
}
RTM_EXPORT(rt_rbb_blk_queue_free);

/**
 * The put status and buffer continuous blocks can be make a block queue.
 * This function will return the length which from next can be make block queue.
 *
 * @param rbb ring block buffer object
 *
 * @return the next can be make block queue's length
 */
rt_size_t rt_rbb_next_blk_queue_len(rt_rbb_t rbb)
{
    rt_base_t level;
    rt_size_t data_len = 0;
    rt_slist_t *node;
    rt_rbb_blk_t last_block = RT_NULL, block;

    RT_ASSERT(rbb);

    if (rt_slist_isempty(&rbb->blk_list))
        return 0;

    level = rt_hw_interrupt_disable();

    for (node = rt_slist_first(&rbb->blk_list); node; node = rt_slist_next(node))
    {
        if (!last_block)
        {
            last_block = rt_slist_entry(node, struct rt_rbb_blk, list);
            if (last_block->status != RT_RBB_BLK_PUT)
            {
                /* the first block must be put status */
                last_block = RT_NULL;
                continue;
            }
        }
        else
        {
            block = rt_slist_entry(node, struct rt_rbb_blk, list);
            /*
             * these following conditions will break the loop:
             * 1. the current block is not put status
             * 2. the last block and current block is not continuous
             */
            if (block->status != RT_RBB_BLK_PUT || last_block->buf > block->buf)
            {
                break;
            }
            /* backup last block */
            last_block = block;
        }
        data_len += last_block->size;
    }

    rt_hw_interrupt_enable(level);

    return data_len;
}
RTM_EXPORT(rt_rbb_next_blk_queue_len);

/**
 * get the ring block buffer object buffer size
 *
 * @param rbb ring block buffer object
 *
 * @return buffer size
 */
rt_size_t rt_rbb_get_buf_size(rt_rbb_t rbb)
{
    RT_ASSERT(rbb);

    return rbb->buf_size;
}
RTM_EXPORT(rt_rbb_get_buf_size);
