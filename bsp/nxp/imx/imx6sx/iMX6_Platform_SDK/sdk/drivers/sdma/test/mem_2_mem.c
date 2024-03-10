/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <string.h>
#include <stdio.h>

#include "sdma/sdma.h"
#include "sdma_test.h"
#include "sdk.h"
#include "profile/profile.h"

#define DDR_2_DDR	1

#define MEM2MEM_TEST_BUF_SZ 		1024*8

#if DDR_2_DDR
/* Uncacheable & unbufferable area startes */
static uint32_t src_buf[2][MEM2MEM_TEST_BUF_SZ];
static uint32_t dst_buf[2][MEM2MEM_TEST_BUF_SZ];
#endif

static sdma_bd_t bd[2];
static char env_buffer[SDMA_ENV_BUF_SIZE];
/* Uncacheable & unbufferable area endes */

int mem_2_mem_test(void)
{
    int idx, channel;
    sdma_chan_desc_t chan_desc;
    uint32_t *src_buf_p[2], *dst_buf_p[2];

    printf("Memory to memory test starts.\n");

#if DDR_2_DDR
    src_buf_p[0] = (uint32_t *) & src_buf[0][0];
    src_buf_p[1] = (uint32_t *) & src_buf[1][0];
    dst_buf_p[0] = (uint32_t *) & dst_buf[0][0];
    dst_buf_p[1] = (uint32_t *) & dst_buf[1][0];
#else
    src_buf_p[0] = (uint32_t *) IRAM_BASE_ADDR;
    src_buf_p[1] = (uint32_t *) (IRAM_BASE_ADDR + MEM2MEM_TEST_BUF_SZ * 4);
    dst_buf_p[0] = (uint32_t *) (IRAM_BASE_ADDR + MEM2MEM_TEST_BUF_SZ * 4 * 2);
    dst_buf_p[1] = (uint32_t *) (IRAM_BASE_ADDR + MEM2MEM_TEST_BUF_SZ * 4 * 3);
#endif

    MEM_VIRTUAL_2_PHYSICAL(src_buf_p[0], sizeof(MEM2MEM_TEST_BUF_SZ * 4),
                           MEM_PRO_UNCACHEABLE | MEM_PRO_UNBUFFERABEL);
    MEM_VIRTUAL_2_PHYSICAL(src_buf_p[1], sizeof(MEM2MEM_TEST_BUF_SZ * 4),
                           MEM_PRO_UNCACHEABLE | MEM_PRO_UNBUFFERABEL);
    MEM_VIRTUAL_2_PHYSICAL(dst_buf_p[0], sizeof(MEM2MEM_TEST_BUF_SZ * 4),
                           MEM_PRO_UNCACHEABLE | MEM_PRO_UNBUFFERABEL);
    MEM_VIRTUAL_2_PHYSICAL(dst_buf_p[1], sizeof(MEM2MEM_TEST_BUF_SZ * 4),
                           MEM_PRO_UNCACHEABLE | MEM_PRO_UNBUFFERABEL);
    MEM_VIRTUAL_2_PHYSICAL(env_buf, sizeof(env_buffer), MEM_PRO_UNCACHEABLE | MEM_PRO_UNBUFFERABEL);
    MEM_VIRTUAL_2_PHYSICAL(bd, sizeof(bd), MEM_PRO_UNCACHEABLE | MEM_PRO_UNBUFFERABEL);

    /* Initialize buffer for testing */
    memset(src_buf_p[0], 0x5A, MEM2MEM_TEST_BUF_SZ * 4);
    memset(src_buf_p[1], 0xA5, MEM2MEM_TEST_BUF_SZ * 4);

    memset(dst_buf_p[0], 0x00, MEM2MEM_TEST_BUF_SZ * 4);
    memset(dst_buf_p[1], 0x00, MEM2MEM_TEST_BUF_SZ * 4);

    /* Initialize SDMA */
    printf("Initialize SDMA environment.\n");
    if (SDMA_RETV_SUCCESS != sdma_init((uint32_t *) env_buffer, SDMA_IPS_HOST_BASE_ADDR)) {
        printf("SDMA initialization failed.\n");
        return FALSE;
    }

    uint32_t script_addr;
    if (SDMA_RETV_SUCCESS != sdma_lookup_script(SDMA_AP_2_AP, &script_addr)) {
        printf("Invalid script.\n");
        return FALSE;
    }
    chan_desc.script_addr = script_addr;
    chan_desc.dma_mask[0] = chan_desc.dma_mask[1] = 0;
    chan_desc.priority = SDMA_CHANNEL_PRIORITY_LOW;
    for (idx = 0; idx < 8; idx++) {
        chan_desc.gpr[idx] = 0;
    }

    /* Setup buffer descriptors */
    bd[0].mode = SDMA_FLAGS_BUSY | SDMA_FLAGS_CONT | (MEM2MEM_TEST_BUF_SZ << 2);
    bd[0].buf_addr = (uint32_t) src_buf_p[0];
    bd[0].ext_buf_addr = (uint32_t) dst_buf_p[0];

    bd[1].mode = SDMA_FLAGS_BUSY | SDMA_FLAGS_WRAP | (MEM2MEM_TEST_BUF_SZ << 2);
    bd[1].buf_addr = (uint32_t) src_buf_p[1];
    bd[1].ext_buf_addr = (uint32_t) dst_buf_p[1];

    /* Open channel */
    printf("Open SDMA channel for transfer.\n");
    channel = sdma_channel_request(&chan_desc, (sdma_bd_p) bd);
    if (channel < 0) {
        printf("Channel open failed.\n");
        return FALSE;
    }

    /* Start channel */
    printf("Channel %d opened, starting transfer...\n", channel);
    sdma_channel_start(channel);

    uint32_t perf_cnt = 0;

    StartPerfCounter();
    /* Wait channel stop */
    uint32_t status;
    do {
        sdma_channel_status(channel, &status);
    } while (!(status & SDMA_CHANNEL_STATUS_DONE));
    perf_cnt = StopPerfCounter();

    float interval = ((float)(perf_cnt)) / ((float)get_main_clock(CPU_CLK));
    float speed = (float)(MEM2MEM_TEST_BUF_SZ * 2 * 4) / 1024.0f / interval;
    printf("mem-2-mem speed: %d KB/s\n", (int)speed);

    /* Stop channel */
    printf("Transfer completed. Stop channel.\n");
    sdma_channel_stop(channel);
    sdma_channel_release(channel);
    sdma_deinit();

    /* Check data transfered */
    printf("Verify data transfered.\n");
    for (idx = 0; idx < MEM2MEM_TEST_BUF_SZ; idx++) {
        if (*src_buf_p[0]++ != *dst_buf_p[0]++) {
            printf("Word %d mismatch: 0x%x, 0x%x\n", idx + 1, *src_buf_p[0], *dst_buf_p[0]);
            return FALSE;
        }

        if (*src_buf_p[1]++ != *dst_buf_p[1]++) {
            printf("Word %d mismatch: 0x%x, 0x%x\n", idx + 1, *src_buf_p[1], *dst_buf_p[1]);
            return FALSE;
        }
    }

    return TRUE;
}
