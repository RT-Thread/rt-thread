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

#ifndef _UTILS_RINGBLK_H_
#define _UTILS_RINGBLK_H_


#include "stddef.h"
#include <stdint.h>
#include "utils_list.h"


#define UTILS_RINGBLK_TEST

/*
 * Introduction:
 * The rbb is the ring buffer which is composed with many blocks. It is different from the ring buffer.
 * The ring buffer is only composed with chars. The rbb put and get supported zero copies. So the rbb
 * is very suitable for put block and get block by a certain order. Such as DMA block transmit,
 * communicate frame send/recv, and so on.
 */

#ifdef __cplusplus
extern "C" {
#endif

enum utils_rbb_status
{
    /* unused status when first initialize or after blk_free() */
    RBB_BLK_UNUSED,
    /* initialized status after blk_alloc() */
    RBB_BLK_INITED,
    /* put status after blk_put() */
    RBB_BLK_PUT,
    /* get status after blk_get() */
    RBB_BLK_GET,
};
typedef enum utils_rbb_status utils_rbb_status_t;

/**
 * the block of rbb
 */
struct utils_rbb_blk
{
    utils_rbb_status_t status :8;
    /* less then 2^24 */
    uint32_t size :24;
    uint8_t *buf;
    utils_slist_t list;
};
typedef struct utils_rbb_blk *utils_rbb_blk_t;

/**
 * Rbb block queue: the blocks (from block1->buf to blockn->buf) memory which on this queue is continuous.
 */
struct utils_rbb_blk_queue
{
    utils_rbb_blk_t blocks;
    uint32_t blk_num;
};
typedef struct utils_rbb_blk_queue *utils_rbb_blk_queue_t;

/**
 * ring block buffer
 */
struct utils_rbb
{
    uint8_t *buf;
    uint32_t buf_size;
    /* all of blocks */
    utils_rbb_blk_t blk_set;
    uint32_t blk_max_num;
    /* saved the initialized and put status blocks */
    utils_slist_t blk_list;
};
typedef struct utils_rbb *utils_rbb_t;

/* rbb (ring block buffer) API */
void utils_rbb_init(utils_rbb_t rbb, uint8_t *buf, uint32_t buf_size, utils_rbb_blk_t block_set, uint32_t blk_max_num);
uint32_t utils_rbb_get_buf_size(utils_rbb_t rbb);

utils_rbb_t utils_rbb_create(uint32_t buf_size, uint32_t blk_max_num);
void utils_rbb_destroy(utils_rbb_t rbb);

/* rbb block API */
utils_rbb_blk_t utils_rbb_blk_alloc(utils_rbb_t rbb, uint32_t blk_size);
void utils_rbb_blk_put(utils_rbb_blk_t block);
utils_rbb_blk_t utils_rbb_blk_get(utils_rbb_t rbb);
uint32_t utils_rbb_blk_size(utils_rbb_blk_t block);
uint8_t *utils_rbb_blk_buf(utils_rbb_blk_t block);
void utils_rbb_blk_free(utils_rbb_t rbb, utils_rbb_blk_t block);
utils_rbb_blk_t utils_rbb_find_empty_blk(utils_rbb_t rbb);
utils_rbb_blk_t utils_rbb_find_used_blk(utils_rbb_t rbb);

/* rbb block queue API */
uint32_t utils_rbb_blk_queue_get(utils_rbb_t rbb, uint32_t queue_data_len, utils_rbb_blk_queue_t blk_queue);
uint32_t utils_rbb_blk_queue_len(utils_rbb_blk_queue_t blk_queue);
uint8_t *utils_rbb_blk_queue_buf(utils_rbb_blk_queue_t blk_queue);
void utils_rbb_blk_queue_free(utils_rbb_t rbb, utils_rbb_blk_queue_t blk_queue);
uint32_t utils_rbb_next_blk_queue_len(utils_rbb_t rbb);


int utils_rbb_cli_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _UTILS_RINGBLK_H_ */
