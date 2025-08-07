/* Copyright (c) 2023, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"
#include <mmu.h>
#include "board.h"
#include "drv_pdma.h"

#define UART_IRQ 0x10

typedef enum
{
    PDMA_EVENT_NONE,
    PDMA_EVENT_COMPLETE,
    PDMA_EVENT_TIMEOUT
} pdma_event_t;

static rt_event_t pdma_event = RT_NULL;

void pdma_call_back(rt_uint8_t ch, rt_bool_t is_done)
{
    /* Send completion or timeout event based on callback status */
    pdma_event_t event_type = is_done ? PDMA_EVENT_COMPLETE : PDMA_EVENT_TIMEOUT;
    rt_event_send(pdma_event, event_type);
}

void test_pdma_request()
{
    rt_uint8_t ch;
    rt_err_t err;

    /* Test channel allocation for all available channels */
    for (rt_uint8_t i = 0; i < PDMA_CH_MAX; i++)
    {
        err = k230_pdma_request_channel(&ch);
        uassert_int_equal(err, RT_EOK);
    }

    /* Should fail when all channels are allocated */
    err = k230_pdma_request_channel(&ch);
    uassert_int_equal(err, -RT_EBUSY);

    /* Release channel 0 and test re-allocation */
    err = k230_pdma_release_channel(0);
    uassert_int_equal(err, RT_EOK);

    err = k230_pdma_request_channel(&ch);
    uassert_int_equal(err, RT_EOK);

    /* Cleanup: release all channels */
    for (rt_uint8_t i = 0; i < PDMA_CH_MAX; i++)
    {
        err = k230_pdma_release_channel(i);
        uassert_int_equal(err, RT_EOK);
    }
}

/* Test DMA transfer from DDR to UART output */
void test_pdma_tx()
{
    rt_uint8_t ch;
    rt_err_t err;
    rt_uint32_t recv_event;
    rt_uint32_t len = 192;

    /* Allocate aligned buffer and prepare test pattern */
    uint8_t *buf = rt_malloc_align(len, 64);
    void *buf_pa = rt_kmem_v2p(buf);

    for (int i = 0; i < 192; i++)
    {
        if ((i + 2) % 64 == 0)
        {
            buf[i] = '\r';
        }
        else if ((i + 1) % 64 == 0)
        {
            buf[i] = '\n';
        }
        else
        {
            buf[i] = 'x';
        }
    }

    rt_event_control(pdma_event, RT_IPC_CMD_RESET, NULL);

    /* Configure DMA transfer */
    err = k230_pdma_request_channel(&ch);
    uassert_int_equal(err, RT_EOK);

    usr_pdma_cfg_t pdma_cfg;
    /* Configure DMA parameters */
    pdma_cfg.device = UART0_TX;
    pdma_cfg.src_addr = buf_pa;
    pdma_cfg.dst_addr = UART0_BASE_ADDR;
    pdma_cfg.line_size = len;

    /* Set channel configuration */
    pdma_cfg.pdma_ch_cfg.ch_src_type = CONTINUE;
    pdma_cfg.pdma_ch_cfg.ch_dev_hsize = PSBYTE1;
    pdma_cfg.pdma_ch_cfg.ch_dat_endian = PDEFAULT;
    pdma_cfg.pdma_ch_cfg.ch_dev_blen = PBURST_LEN_16;
    pdma_cfg.pdma_ch_cfg.ch_priority = 7;
    pdma_cfg.pdma_ch_cfg.ch_dev_tout = 0xFFF;

    err = k230_pdma_set_callback(ch, pdma_call_back);
    uassert_int_equal(err, RT_EOK);

    err = k230_pdma_config(ch, &pdma_cfg);
    uassert_int_equal(err, RT_EOK);

    /* Start transfer and wait for completion */
    err = k230_pdma_start(ch);
    uassert_int_equal(err, RT_EOK);

    err = rt_event_recv(pdma_event,
                       PDMA_EVENT_COMPLETE | PDMA_EVENT_TIMEOUT,
                       RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                       RT_WAITING_FOREVER,
                       &recv_event);
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(recv_event, PDMA_EVENT_COMPLETE);

    /* Cleanup */
    err = k230_pdma_stop(ch);
    uassert_int_equal(err, RT_EOK);

    err = k230_pdma_release_channel(ch);
    uassert_int_equal(err, RT_EOK);

    rt_free_align(buf);
    LOG_I("PDMA TX test completed successfully");
}

/* Test DMA transfer from UART RX FIFO to memory */
void test_pdma_rx()
{
    rt_uint8_t ch;
    rt_err_t err;
    rt_uint32_t recv_event;
    rt_uint32_t len = 16;

    /* Allocate aligned buffer for DMA transfer */
    uint8_t *buf = rt_malloc_align(len, 64);
    void *buf_pa = rt_kmem_v2p(buf);

    /* Reset event before starting test */
    rt_event_control(pdma_event, RT_IPC_CMD_RESET, NULL);

    /* Request DMA channel */
    err = k230_pdma_request_channel(&ch);
    uassert_int_equal(err, RT_EOK);

    /* Configure DMA parameters */
    usr_pdma_cfg_t pdma_cfg;
    pdma_cfg.device = UART0_RX;
    pdma_cfg.src_addr = UART0_BASE_ADDR;
    pdma_cfg.dst_addr = buf_pa;
    pdma_cfg.line_size = len;

    /* Set channel configuration */
    pdma_cfg.pdma_ch_cfg.ch_src_type = FIXED;
    pdma_cfg.pdma_ch_cfg.ch_dev_hsize = PSBYTE1;
    pdma_cfg.pdma_ch_cfg.ch_dat_endian = PDEFAULT;
    pdma_cfg.pdma_ch_cfg.ch_dev_blen = PBURST_LEN_16;
    pdma_cfg.pdma_ch_cfg.ch_priority = 7;
    pdma_cfg.pdma_ch_cfg.ch_dev_tout = 0xFFF;

    /* Set callback and configure DMA */
    err = k230_pdma_set_callback(ch, pdma_call_back);
    uassert_int_equal(err, RT_EOK);

    err = k230_pdma_config(ch, &pdma_cfg);
    uassert_int_equal(err, RT_EOK);

    LOG_I("Send test data by keyboard input within 2 seconds (to UART receive buffer)");

    /* Setup 2 second timeout */
    rt_tick_t timeout = RT_TICK_PER_SECOND * 2;
    rt_tick_t start_tick = rt_tick_get();

    /* Mask UART interrupt to prevent FIFO access by ISR */
    rt_hw_interrupt_mask(UART_IRQ);

    /* Wait for timeout period */
    while (RT_TRUE)
    {
        if (rt_tick_get_delta(start_tick) >= timeout)
        {
            break;
        }
    }

    /* Start DMA transfer */
    k230_pdma_start(ch);

    /* Wait for transfer completion event */
    err = rt_event_recv(pdma_event,
                       PDMA_EVENT_COMPLETE | PDMA_EVENT_TIMEOUT,
                       RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                       RT_WAITING_FOREVER,
                       &recv_event);
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(recv_event, PDMA_EVENT_COMPLETE);

    rt_hw_interrupt_umask(UART_IRQ);

    err = k230_pdma_stop(ch);
    uassert_int_equal(err, RT_EOK);

    err = k230_pdma_release_channel(ch);
    uassert_int_equal(err, RT_EOK);

    LOG_I("Got: %.*s", len, buf);

    rt_free_align(buf);
}

static rt_err_t utest_tc_init(void)
{
    pdma_event = (rt_event_t)rt_malloc(sizeof(struct rt_event));
    if (pdma_event == RT_NULL)
    {
        LOG_E("Failed to allocate memory for pdma_event!");
        return -RT_ENOMEM;
    }

    if (rt_event_init(pdma_event, "pdma_event", RT_IPC_FLAG_FIFO) != RT_EOK)
    {
        LOG_E("Failed to init pdma_event!");
        rt_free(pdma_event);
        return -RT_ERROR;
    }

    LOG_I("PDMA event initialized successfully!");
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_free(pdma_event);
    LOG_I("Thanks for feeding me, I'm still alive!");
    return RT_EOK;
}

void test_pdma()
{
    UTEST_UNIT_RUN(test_pdma_request);
    UTEST_UNIT_RUN(test_pdma_tx);
    UTEST_UNIT_RUN(test_pdma_rx);
}

UTEST_TC_EXPORT(test_pdma, "pdma", utest_tc_init, utest_tc_cleanup, 10);
