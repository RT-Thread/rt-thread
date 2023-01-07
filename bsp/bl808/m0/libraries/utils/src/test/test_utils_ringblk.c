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

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>

#include <FreeRTOS.h>
#include <task.h>

#ifdef CONFIG_CLI_CMD_ENABLE
#include <cli.h>
#endif
#include "utils_ringblk.h"

#ifdef UTILS_RINGBLK_TEST


static void cmd_ringblk_test(char *buf, int len, int argc, char **argv)
{
    utils_rbb_t rbb;
    utils_rbb_blk_t blk1, blk2, blk3, blk4, blk5, blk6, _blk1, _blk2;
    uint32_t i, j, k, req_size, size;
    struct utils_rbb_blk_queue blk_queue1;

    /* create ring block buffer */
    printf("\n====================== rbb create test =====================\r\n");
    rbb = utils_rbb_create(52, 6);
    if (rbb)
    {
        printf("6 blocks in 52 bytes ring block buffer object create success.\r\n");
    }
    else
    {
        printf("Test error: 6 blocks in 52 bytes ring block buffer object create failed.\r\n");
    }
    /* allocate block */
    printf("\n====================== rbb alloc test =====================\r\n");
    blk1 = utils_rbb_blk_alloc(rbb, 2);
    if (blk1 && blk1->size == 2)
    {
        memset(blk1->buf, 1, blk1->size);
        printf("Block1 (2 bytes) allocate success.\r\n");
    }
    else
    {
        printf("Test error: block1 (2 bytes) allocate failed.\r\n");
        goto __exit;
    }
    blk2 = utils_rbb_blk_alloc(rbb, 4);
    if (blk2 && blk2->size == 4)
    {
        memset(blk2->buf, 2, blk2->size);
        printf("Block2 (4 bytes) allocate success.\r\n");
    }
    else
    {
        printf("Test error: block2 (4 bytes) allocate failed.\r\n");
        goto __exit;
    }
    blk3 = utils_rbb_blk_alloc(rbb, 8);
    if (blk3 && blk3->size == 8)
    {
        memset(blk3->buf, 3, blk3->size);
        printf("Block3 (8 bytes) allocate success.\r\n");
    }
    else
    {
        printf("Test error: block3 (8 bytes) allocate failed.\r\n");
        goto __exit;
    }
    blk4 = utils_rbb_blk_alloc(rbb, 16);
    if (blk4 && blk4->size == 16)
    {
        memset(blk4->buf, 4, blk4->size);
        printf("Block4 (16 bytes) allocate success.\r\n");
    }
    else
    {
        printf("Test error: block4 (16 bytes) allocate failed.\r\n");
        goto __exit;
    }
    blk5 = utils_rbb_blk_alloc(rbb, 32);
    if (blk5 && blk5->size == 32)
    {
        memset(blk5->buf, 5, blk5->size);
        printf("Block5 (32 bytes) allocate success.\r\n");
    }
    else
    {
        printf("Block5 (32 bytes) allocate failed.\r\n");
    }
    blk5 = utils_rbb_blk_alloc(rbb, 18);
    if (blk5 && blk5->size == 18)
    {
        memset(blk5->buf, 5, blk5->size);
        printf("Block5 (18 bytes) allocate success.\r\n");
    }
    else
    {
        printf("Test error: block5 (18 bytes) allocate failed.\r\n");
        goto __exit;
    }
    printf("Ring block buffer current status:\r\n");
    printf("next block queue length: %"PRIu32"\r\n", utils_rbb_next_blk_queue_len(rbb));
    printf("block list length: %d\r\n", utils_slist_entry_number(&rbb->blk_list));
    printf("|<- 2 -->|<-- 4 -->|<---- 8 ----->|<------- 16 -------->|<------ 18 ------>|<---- 4 ---->|\r\n");
    printf("+--------+---------+--------------+---------------------+------------------+-------------+\r\n");
    printf("| blcok1 | block2  |    block3    |       block4        |       block5     |    empty    |\r\n");
    printf("+--------+---------+--------------+---------------------+------------------+-------------+\r\n");
    printf("| inited | inited  |    inited    |       inited        |       inited     |             |\r\n");
    //
    /* put block */
    printf("\n====================== rbb put test =====================\r\n");
    utils_rbb_blk_put(blk1);
    utils_rbb_blk_put(blk2);
    utils_rbb_blk_put(blk3);
    utils_rbb_blk_put(blk4);
    utils_rbb_blk_put(blk5);
    printf("Block1 to block5 put success.\r\n");
    printf("Ring block buffer current status:\r\n");
    printf("next block queue length: %"PRIu32"\r\n", utils_rbb_next_blk_queue_len(rbb));
    printf("block list length: %d\r\n", utils_slist_entry_number(&rbb->blk_list));
    printf("|<- 2 -->|<-- 4 -->|<---- 8 ----->|<------- 16 -------->|<------ 18 ------>|<---- 4 ---->|\r\n");
    printf("+--------+---------+--------------+---------------------+------------------+-------------+\r\n");
    printf("| blcok1 | block2  |    block3    |       block4        |       block5     |    empty    |\r\n");
    printf("+--------+---------+--------------+---------------------+------------------+-------------+\r\n");
    printf("|  put   |  put    |     put      |        put          |        put       |             |\r\n");
    //
    /* get block */
    printf("\n====================== rbb get test =====================\r\n");
    _blk1 = utils_rbb_blk_get(rbb);
    _blk2 = utils_rbb_blk_get(rbb);
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
        printf("Block1 and block2 get success.\r\n");
    }
    else
    {
        printf("Test error: block1 and block2 get failed.\r\n");
        goto __exit;
    }
    printf("Ring block buffer current status:\r\n");
    printf("next block queue length: %"PRIu32"\r\n", utils_rbb_next_blk_queue_len(rbb));
    printf("block list length: %d\r\n", utils_slist_entry_number(&rbb->blk_list));
    printf("|<- 2 -->|<-- 4 -->|<---- 8 ----->|<------- 16 -------->|<------ 18 ------>|<---- 4 ---->|\r\n");
    printf("+--------+---------+--------------+---------------------+------------------+-------------+\r\n");
    printf("| blcok1 | block2  |    block3    |       block4        |       block5     |    empty    |\r\n");
    printf("+--------+---------+--------------+---------------------+------------------+-------------+\r\n");
    printf("|  get   |   get   |     put      |        put          |        put       |             |\r\n");
    //
    /* free block */
    printf("\n====================== rbb free test =====================\r\n");
    utils_rbb_blk_free(rbb, blk2);
    printf("Block2 free success.\r\n");
    utils_rbb_blk_free(rbb, blk1);
    printf("Block1 free success.\r\n");
    printf("Ring block buffer current status:\r\n");
    printf("next block queue length: %"PRIu32"\r\n", utils_rbb_next_blk_queue_len(rbb));
    printf("block list length: %d\r\n", utils_slist_entry_number(&rbb->blk_list));
    printf("|<------- 6 ------>|<---- 8 ----->|<------- 16 -------->|<------ 18 ------>|<---- 4 ---->|\r\n");
    printf("+------------------+--------------+---------------------+------------------+-------------+\r\n");
    printf("|      empty2      |    block3    |       block4        |       block5     |    empty1   |\r\n");
    printf("+------------------+--------------+---------------------+------------------+-------------+\r\n");
    printf("|                  |     put      |        put          |        put       |             |\r\n");

    blk6 = utils_rbb_blk_alloc(rbb, 5);
    if (blk6)
    {
        printf("Block6 (5 bytes) allocate success.\r\n");
    }
    else
    {
        printf("Test error: block6 (5 bytes) allocate failed.\r\n");
        goto __exit;
    }

    utils_rbb_blk_put(blk6);
    printf("Block6 put success.\r\n");
    printf("Ring block buffer current status:\r\n");
    printf("next block queue length: %"PRIu32"\r\n", utils_rbb_next_blk_queue_len(rbb));
    printf("block list length: %d\r\n", utils_slist_entry_number(&rbb->blk_list));
    printf("|<--- 5 ---->|< 1 >|<---- 8 ----->|<------- 16 -------->|<------ 18 ------>|<---- 4 ---->|\r\n");
    printf("+------------+-----+--------------+---------------------+------------------+-------------+\r\n");
    printf("|   block6   |empty|    block3    |       block4        |       block5     |   fragment  |\r\n");
    printf("+------------+-----+--------------+---------------------+------------------+-------------+\r\n");
    printf("|     put    |     |     put      |        put          |        put       |             |\r\n");

    /* get block queue */
    printf("\n====================== rbb block queue get test =====================\r\n");
    req_size = utils_rbb_next_blk_queue_len(rbb) + 5;
    size = utils_rbb_blk_queue_get(rbb, req_size, &blk_queue1);
    i = j = k = 0;
    for (; i < blk3->size; i++)
    {
        if (utils_rbb_blk_queue_buf(&blk_queue1)[i] != 3) break;
    }
    for (; j < blk4->size; j++)
    {
        if (utils_rbb_blk_queue_buf(&blk_queue1)[i + j] != 4) break;
    }
    for (; k < blk5->size; k++)
    {
        if (utils_rbb_blk_queue_buf(&blk_queue1)[i + j + k] != 5) break;
    }
    if (size && size == 42 && utils_rbb_blk_queue_len(&blk_queue1) == 42 && k == blk5->size)
    {
        printf("Block queue (request %"PRIu32" bytes, actual %"PRIu32") get success.\r\n", req_size, size);
    }
    else
    {
        printf("Test error: Block queue (request %"PRIu32" bytes, actual %"PRIu32") get failed.\r\n", req_size, size);
        goto __exit;
    }
    printf("Ring block buffer current status:\r\n");
    printf("next block queue length: %"PRIu32"\r\n", utils_rbb_next_blk_queue_len(rbb));
    printf("block list length: %d\r\n", utils_slist_entry_number(&rbb->blk_list));
    printf("|            |     |<----- block queue1 (42 bytes continuous buffer) ----->|             |\r\n");
    printf("|<--- 5 ---->|< 1 >|<---- 8 ----->|<------- 16 -------->|<------ 18 ------>|<---- 4 ---->|\r\n");
    printf("+------------+-----+--------------+---------------------+------------------+-------------+\r\n");
    printf("|   block6   |empty|    block3    |       block4        |       block5     |   fragment  |\r\n");
    printf("+------------+-----+--------------+---------------------+------------------+-------------+\r\n");
    printf("|     put    |     |     get      |        get          |        get       |             |\r\n");

    /* free block queue */
    printf("\n====================== rbb block queue free test =====================\r\n");
    utils_rbb_blk_queue_free(rbb, &blk_queue1);
    printf("Block queue1 free success.\r\n");
    printf("Ring block buffer current status:\r\n");
    printf("next block queue length: %"PRIu32"\r\n", utils_rbb_next_blk_queue_len(rbb));
    printf("block list length: %d\r\n", utils_slist_entry_number(&rbb->blk_list));
    printf("|<--- 5 ---->|<--------------------------------- 47 ------------------------------------>|\r\n");
    printf("+------------+---------------------------------------------------------------------------+\r\n");
    printf("|   block6   |                                 empty                                     |\r\n");
    printf("+------------+---------------------------------------------------------------------------+\r\n");
    printf("|     put    |                                                                           |\r\n");
    utils_rbb_blk_free(rbb, blk6);

    printf("\n====================== rbb static test SUCCESS =====================\r\n");

    printf("\n====================== rbb dynamic test =====================\r\n");

__exit :

    utils_rbb_destroy(rbb);
}


static uint8_t put_finish = 0;

static void put_thread(void *param)
{
  utils_rbb_t rbb = (utils_rbb_t)param;
  utils_rbb_blk_t block;
  uint32_t put_count = 0;

  put_finish = 0;

  while (put_count < 10000)
  {
    block = utils_rbb_blk_alloc(rbb, rand() % 10 + 4);
    if (block)
    {
      memcpy(&block->buf[0], (void *)&put_count, 4);
      utils_rbb_blk_put(block);
      printf("put block size %d count %" PRId32 "\r\n", block->size, put_count++);
    }
    else
    {
      printf("block alloc failed\r\n");
    }
    vTaskDelay(rand() % 10);
  }
  printf("Put block data finish.\r\n");

  put_finish = 1;

  vTaskDelete(NULL);
}

static void get_thread(void *param)
{
  utils_rbb_t rbb = (utils_rbb_t)param;
  utils_rbb_blk_t block;
  uint32_t get_count = 0;

  while (get_count < 10000)
  {
    block = utils_rbb_blk_get(rbb);

    if (block)
    {
      if (memcmp(&block->buf[0], (void *)&get_count, 4) != 0)
      {
        printf("Error: get data (times %" PRId32 ") has an error!\r\n", get_count);
        goto exit_;
      }
      utils_rbb_blk_free(rbb, block);
      printf("free block size %d count %" PRId32 "\r\n", block->size, get_count++);
    }
    else if (put_finish)
    {
      break;
    }
    vTaskDelay(rand() % 10);
  }
  printf("Get block data finish.\r\n");

  utils_rbb_blk_t new_rbb = utils_rbb_find_used_blk(rbb);
  if (new_rbb != NULL)
  {
    printf("\n====================== rbb blk not free =====================\r\n");
  }

exit_:
  printf("\n====================== rbb dynamic test finish =====================\r\n");

  utils_rbb_destroy(rbb);

  vTaskDelete(NULL);
}

static void cmd_ringblk_through_test(char *buf, int len, int argc, char **argv)
{
  utils_rbb_t rbb;

  rbb = utils_rbb_create(100, 10);

  xTaskCreate(put_thread, "rbb_put", 1024, rbb, 10, NULL);

  xTaskCreate(get_thread, "rbb_get", 1024, rbb, 10, NULL);
}

#ifdef CONFIG_CLI_CMD_ENABLE
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
  {"rbb_static_test", "ringblk static test", cmd_ringblk_test},
  {"rbb_through_test", "ringblk dynamic test", cmd_ringblk_through_test},
};
#endif

int utils_rbb_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}

#endif
