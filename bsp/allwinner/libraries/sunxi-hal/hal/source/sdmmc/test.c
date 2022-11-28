/*
 * Copyright (C) 2017 ALLWINNERTECH TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of ALLWINNERTECH TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <string.h>
#include <stdio.h>


#include "sys/sys_debug.h"

#include "os_time.h"
//#include "FreeRTOS.h"
#include "os_semaphore.h"

#include "hal_def.h"
#include "hal_ccm.h"
#include "hal_sdhost.h"
#include "sdmmc.h"
#include "sdio.h"

#include "_sd_define.h"
#include "_sdhost.h"


#define TEST_SD
#define TEST_SD_WRITE

#ifdef TEST_SD

#define SIZE_1K     (1024)
#define SIZE_1M         (SIZE_1K*SIZE_1K)

#define READ_WRITE_SINGLE_SIZE  (16*SIZE_1K)
#define READ_WRITE_TOTAL_SIZE   (8*SIZE_1M)

struct sdmmc_tester {
    struct mmc_card *card;
    SDCard_InitTypeDef card_param;
    SDC_InitTypeDef sdc_param;
    uint16_t sdc_id;
    uint16_t card_id;
    uint8_t wbuf[READ_WRITE_SINGLE_SIZE];
    uint8_t rbuf[READ_WRITE_SINGLE_SIZE];
#ifdef CONFIG_DETECT_CARD
    OS_Semaphore_t card_present_sem;
#endif
};

static struct sdmmc_tester *sdmmc_test = NULL;

#ifdef CONFIG_DETECT_CARD
static int detect_status = -1;
void card_detect(uint32_t present)
{
    if (present) {
        detect_status = 0;
        rt_kprintf("%s insert\n", __func__);
        if (mmc_card_create(sdmmc_test->card_id, &sdmmc_test->card_param) != 0) {
            rt_kprintf("mmc create fail\n");
            return ;
        }
        sdmmc_test->card = mmc_card_open(sdmmc_test->card_id);
        if (sdmmc_test->card == NULL) {
            rt_kprintf("mmc open fail\n");
            return ;
        }
        /* scan card for detect card is exist? */
        if (!mmc_card_present(sdmmc_test->card)) {
        //  if (mmc_rescan(sdmmc_test->card, sdmmc_test->card->id)) {
            sdmmc_test->card->type = MMC_TYPE_SD;
            if (mmc_rescan(sdmmc_test->card, sdmmc_test->sdc_id)) {
                rt_kprintf("Initial card failed!!\n");
                mmc_card_close(sdmmc_test->card_id);
                detect_status = -1;
                return ;
            } else {
                rt_kprintf("Initial card success. capacity :%dMB\n", sdmmc_test->card->csd.capacity / 1024);
                mmc_card_close(sdmmc_test->card_id);
#ifndef CONFIG_KERNEL_FREERTOS
                // void mount_sdmmc_filesystem(int card_id);
                // mount_sdmmc_filesystem((int)sdmmc_test->card_id);
#endif
                SDC_SemPost(&sdmmc_test->card_present_sem);
            }
        } else {
            rt_kprintf("%s not eixst\n", __func__);
            mmc_card_close(sdmmc_test->card_id);
            return ;
        }
    } else {
        struct mmc_card *card;

        rt_kprintf("%s removed\n", __func__);
        card = mmc_card_open(sdmmc_test->card_id);
        if (card == NULL) {
            rt_kprintf("card open fail\n");
        } else {
            if (mmc_card_present(card)) {
                mmc_card_deinit(card);
            }
            mmc_card_close(sdmmc_test->card_id);
#ifndef CONFIG_KERNEL_FREERTOS
            // void unmount_sdmmc_filesystem(void);
            // unmount_sdmmc_filesystem();
#endif
            mmc_card_delete(sdmmc_test->card_id);
        }
    }
}
#endif
//#define WIFI_DEBUG 0
// #define DETECT_BY_GPIO 1
int32_t mmc_test_init(uint32_t host_id, SDC_InitTypeDef *sdc_param, uint32_t scan)
{
    struct mmc_host *host;

    if (!sdmmc_test) {
        sdmmc_test = malloc(sizeof(struct sdmmc_tester));
        if (!sdmmc_test) {
            rt_kprintf("malloc faild!\n");
            return -1;
        }
        memset(sdmmc_test, 0, sizeof(struct sdmmc_tester));
    }

    if (sdc_param)
        memcpy(&sdmmc_test->sdc_param, sdc_param, sizeof(SDC_InitTypeDef));

#ifdef CONFIG_DETECT_CARD
    OS_SemaphoreCreate(&sdmmc_test->card_present_sem, 0, OS_SEMAPHORE_MAX_COUNT);

    if (!sdc_param) {
#ifndef DETECT_BY_GPIO
        sdmmc_test->sdc_param.cd_mode = CARD_ALWAYS_PRESENT;
#else
        sdmmc_test->sdc_param.cd_mode = CARD_DETECT_BY_GPIO_IRQ;
#endif
        sdmmc_test->sdc_param.cd_cb = &card_detect;
#ifndef WIFI_DEBUG
        sdmmc_test->sdc_param.debug_mask = (ROM_INF_MASK | \
                ROM_WRN_MASK | ROM_ERR_MASK | ROM_ANY_MASK);
#else
        sdmmc_test->sdc_param.debug_mask = (ROM_DUMP_MASK | ROM_DBG_MASK | ROM_INF_MASK | \
                ROM_WRN_MASK | ROM_ERR_MASK | ROM_ANY_MASK);
#endif
        sdmmc_test->sdc_param.dma_use = 1;
    }
#endif
    if (!sdc_param)
        sdc_param = &sdmmc_test->sdc_param;
#ifdef WIFI_DEBUG
    sdmmc_test->card_param.debug_mask = (ROM_DUMP_MASK | ROM_DBG_MASK | ROM_INF_MASK | \
                         ROM_WRN_MASK | ROM_ERR_MASK | ROM_ANY_MASK);
#else
    sdmmc_test->card_param.debug_mask = (ROM_INF_MASK | \
                         ROM_WRN_MASK | ROM_ERR_MASK | ROM_ANY_MASK);
#endif
    host = hal_sdc_create(host_id, sdc_param);
    host->State = SDC_STATE_RESET;
    hal_sdc_init(host);
    //HAL_SDC_SetHighSpeed(host);
    sdmmc_test->sdc_id = host_id;
    sdmmc_test->card_id = host_id;

    if (scan && sdmmc_test->sdc_param.cd_mode == CARD_ALWAYS_PRESENT) {
        card_detect(1);
        return detect_status;
    }

    return 0;
}

int32_t mmc_test_exit(uint16_t sd_id, uint16_t host_id)
{
    struct mmc_card *card;
    struct mmc_host *host;

    if (!sdmmc_test->card || !sdmmc_test->card->host ||
        sdmmc_test->card->id != sd_id || sdmmc_test->sdc_id != host_id) {
        if (!sdmmc_test->card || !sdmmc_test->card->host)
            rt_kprintf("no card found\n");
        else
            rt_kprintf("wrong card id:%d<->%d host id:%ld<->%d\n", sd_id, host_id,
                   HAL_PR_SZ_L(sdmmc_test->card->id), sdmmc_test->sdc_id);
        return 0;
    }

    card = mmc_card_open(sdmmc_test->card_id);
    if (card == NULL) {
        rt_kprintf("card open fail\n");
    } else {
        if (mmc_card_present(card)) {
            mmc_card_deinit(card);
        }
        mmc_card_close(sdmmc_test->card_id);
        mmc_card_delete(sdmmc_test->card_id);
    }

#if 0
    host = HAL_SDC_Open(host_id);
    HAL_SDC_Close(host_id);
#endif
    hal_sdc_deinit(sd_id);
#if 0
    HAL_SDC_Destory(host);
#endif

#ifdef CONFIG_DETECT_CARD
    OS_SemaphoreDelete(&sdmmc_test->card_present_sem);
#endif

    if (sdmmc_test) {
        free(sdmmc_test);
        sdmmc_test = NULL;
    }


    return 0;
}

struct mmc_card *mmc_scan_init(uint16_t sd_id, uint16_t sdc_id, SDCard_InitTypeDef *card_param)
{
    struct mmc_card *card;

    if (!card_param) {
        card_param = &sdmmc_test->card_param;
        sdmmc_test->card_param.debug_mask = ROM_WRN_MASK | ROM_ERR_MASK | ROM_ANY_MASK;
    }
    if (mmc_card_create(sd_id, card_param) != 0) {
        rt_kprintf("mmc create fail\n");
        return NULL;
    }
    card = mmc_card_open(sd_id);
    if (card == NULL) {
        rt_kprintf("mmc open fail\n");
        return NULL;
    }
    if (!mmc_card_present(card)) {
        int mmc_ret = mmc_rescan(card, sdc_id);
        if (mmc_ret != 0) {
            rt_kprintf("mmc scan fail\n");
            mmc_card_close(sd_id);
            return NULL;
        } else {
            rt_kprintf("mmc init\n");
        }
    }
    mmc_card_close(sd_id);
    sdmmc_test->card = card;

    return card;
}

int32_t mmc_test(uint32_t host_id, uint32_t cd_mode, uint32_t sdc_degmask, uint32_t card_dbgmask)
{
    int32_t err;
    uint32_t i, cnt = 0;
    SDC_InitTypeDef sdc_param = { 0 };

    sdc_param.cd_mode = cd_mode;
    sdc_param.cd_cb = &card_detect;
    sdc_param.debug_mask = sdc_degmask;
    sdc_param.dma_use = 1;

    //if (mmc_test_init(host_id, &sdc_param, 1)) {
    if (mmc_test_init(host_id, &sdc_param, 1)) {
        return -1;
    }

    memset((void *)sdmmc_test->wbuf, 0x55, 128);
    memset((void *)&sdmmc_test->wbuf[128], 0xaa, 128);

    for (i = 0; i < 256; i ++)
        sdmmc_test->wbuf[256 + i] = i;

    memcpy((void *)&sdmmc_test->wbuf[512], (void *)sdmmc_test->wbuf, 512);

    sdmmc_test->card_param.debug_mask = card_dbgmask;


//  if (mmc_test_init(host_id, &sdc_param, 1)) {
//      return -1;
//  }


    sdmmc_test->card_param.type = MMC_TYPE_SD;

    while (cnt++ < 1) {
        uint32_t throuth_mb, throuth_kb;
        OS_Time_t tick_use;

        rt_kprintf("%s,%d count:%lu\n", __func__, __LINE__, HAL_PR_SZ_L(cnt));

#ifdef CONFIG_DETECT_CARD
        if (!mmc_card_present(sdmmc_test->card) || (cd_mode != CARD_ALWAYS_PRESENT))
            OS_SemaphoreWait(&sdmmc_test->card_present_sem, OS_WAIT_FOREVER);
#endif

        struct mmc_card *card = mmc_card_open(sdmmc_test->card_id);
        card->debug_mask = card_dbgmask;
        if (card == NULL) {
            rt_kprintf("mmc open fail\n");
            goto err_out;
        }

#ifdef TEST_SD_WRITE
        tick_use = OS_GetTicks();
        err = mmc_block_write(sdmmc_test->card, sdmmc_test->wbuf, 0, 1);
        tick_use = OS_GetTicks() - tick_use;
        if (err) {
            goto err_out;
        } else {
            rt_kprintf("%s 1 block write ok, 512B use:%lu ms\n", __func__,
                  HAL_PR_SZ_L((uint32_t)OS_TicksToMSecs(tick_use)));
        }
#endif
        memset((void *)sdmmc_test->rbuf, 0, 512);
        tick_use = OS_GetTicks();
        err = mmc_block_read(sdmmc_test->card, sdmmc_test->rbuf, 0, 1);
        tick_use = OS_GetTicks() - tick_use;
        if (err) {
            goto err_out;
        } else {
            rt_kprintf("%s 1 block read ok, 512B use:%lu ms\n", __func__,
                   HAL_PR_SZ_L((uint32_t)OS_TicksToMSecs(tick_use)));
#ifndef TEST_SD_WRITE
            print_hex_dump_words(sdmmc_test->rbuf, 512);
#endif
        }
#ifdef TEST_SD_WRITE
        if (memcmp((void *)sdmmc_test->wbuf, (void *)sdmmc_test->rbuf, 512)) {
            goto err_out;
        } else
            rt_kprintf("%s,%d mmc 1 block rw ok\n", __func__, __LINE__);

        tick_use = OS_GetTicks();
        for (i = 0; i < READ_WRITE_TOTAL_SIZE/READ_WRITE_SINGLE_SIZE; i++) {
            err = mmc_block_write(sdmmc_test->card, sdmmc_test->wbuf, 3 + i * (READ_WRITE_SINGLE_SIZE/512),
                                  READ_WRITE_SINGLE_SIZE/512);
            if (err)
                break;
            if (i % 50 == 0)
                rt_kprintf("%s, wirite cnt:%lu\n", __func__, HAL_PR_SZ_L(i));
        }
        tick_use = OS_GetTicks() - tick_use;
        if (err) {
            rt_kprintf("%s,%d mmc mult blocks write err!\n", __func__, __LINE__);
            goto err_out;
        } else {
            throuth_kb = READ_WRITE_TOTAL_SIZE/SIZE_1K*1000/(uint32_t)OS_TicksToMSecs(tick_use);
            throuth_mb = throuth_kb/1000;
            rt_kprintf("%s mult blocks write ok, %d MB use:%lu ms, throughput:%lu.%lu MB/S\n",
                   __func__, READ_WRITE_TOTAL_SIZE/SIZE_1M, HAL_PR_SZ_L((uint32_t)OS_TicksToMSecs(tick_use)),
                   HAL_PR_SZ_L(throuth_mb), HAL_PR_SZ_L(throuth_kb - throuth_mb));
        }
#endif

        tick_use = OS_GetTicks();
        for (i = 0; i < READ_WRITE_TOTAL_SIZE/READ_WRITE_SINGLE_SIZE; i++) {
            err = mmc_block_read(sdmmc_test->card, sdmmc_test->rbuf, 3 + i * (READ_WRITE_SINGLE_SIZE/512),
                                 READ_WRITE_SINGLE_SIZE/512);
            if (err)
                break;
        }
        tick_use = OS_GetTicks() - tick_use;
        if (err) {
            rt_kprintf("%s,%d mmc mult blocks read err!\n", __func__, __LINE__);
            goto err_out;
        } else {
            throuth_kb = READ_WRITE_TOTAL_SIZE/SIZE_1K*1000/(uint32_t)OS_TicksToMSecs(tick_use);
            throuth_mb = throuth_kb/1000;
            rt_kprintf("%s mult blocks read ok, %d MB use:%lu ms, throughput:%lu.%lu MB/S\n",
                   __func__, READ_WRITE_TOTAL_SIZE/SIZE_1M, HAL_PR_SZ_L((uint32_t)OS_TicksToMSecs(tick_use)),
                   HAL_PR_SZ_L(throuth_mb), HAL_PR_SZ_L(throuth_kb - throuth_mb));
        }

        memset((void *)sdmmc_test->rbuf, 0, READ_WRITE_SINGLE_SIZE);
        err = mmc_block_read(sdmmc_test->card, sdmmc_test->rbuf, 3, READ_WRITE_SINGLE_SIZE/512);
        if (err) {
            goto err_out;
        } else
            rt_kprintf("%s %d blocks read ok\n", __func__, READ_WRITE_SINGLE_SIZE/512);

#ifdef TEST_SD_WRITE
        if (memcmp((void *)sdmmc_test->wbuf, (void *)sdmmc_test->rbuf, 1024)) { /* check 1024B */
            rt_kprintf("%s %d mmc blocks rw failed\n", __func__, READ_WRITE_SINGLE_SIZE/512);
            goto err_out;
        } else
            rt_kprintf("%s %d mmc blocks rw ok\n", __func__, READ_WRITE_SINGLE_SIZE/512);
#endif
        mmc_card_close(sdmmc_test->card_id);

        OS_MSleep(1000);
    }

    mmc_test_exit(host_id, sdmmc_test->card_id);

    return 0;

err_out:
#ifdef TEST_SD_WRITE
    rt_kprintf("%s,%d mmc block rw failed\n", __func__, __LINE__);
    rt_kprintf("rbuf:\n");
    print_hex_dump_words(sdmmc_test->rbuf, SIZE_1K);
    rt_kprintf("wbuf:\n");
    print_hex_dump_words(sdmmc_test->wbuf, 512);
#endif
#ifndef CONFIG_DETECT_CARD
out:
#endif
    mmc_test_exit(host_id, sdmmc_test->card_id);
    return -1;
}
#endif /* TEST_SD */
