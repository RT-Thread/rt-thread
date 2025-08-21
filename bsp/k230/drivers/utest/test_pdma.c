/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * Refer to PDMA driver implementation and hardware specifications
 * This is a PDMA (Peripheral DMA) device test routine. The program tests:
 * - Channel allocation/release functionality
 * - DMA transfer from DDR to UART (TX)
 * - DMA transfer from UART to DDR (RX)
 *
 * "test_pdma_tx" tests DDR-to-UART transmission:
 * - Should display 3 identical rows of data on screen
 * - Each row consists of 62 'x' characters
 * - Total output should contain exactly 186 'x' characters
 * - Data is transferred from DDR to UART0 TX FIFO via PDMA
 *
 * "test_pdma_rx" tests UART-to-DDR reception:
 * - After "Send test data by keyboard input within 2 seconds" prompt appears:
 *   - User has 2 seconds to input data via keyboard
 *   - Input will be captured via UART0 RX FIFO to DDR through PDMA
 * - Test will display first 16 bytes of received DDR data
 * - Verify output matches partial input data
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"
#include <mmu.h>
#include "board.h"
#include "drv_pdma.h"

#define UART0_IRQ K230_IRQ_UART0

#define CACHE_LINE_SIZE 64

typedef enum
{
    TEST_PDMA_EVENT_NONE,
    TEST_PDMA_EVENT_COMPLETE,
    TEST_PDMA_EVENT_TIMEOUT
} test_pdma_event_t;

static rt_event_t test_pdma_event = RT_NULL;

void test_pdma_call_back(rt_uint8_t ch, rt_bool_t is_done)
{
    /* Send completion or timeout event based on callback status */
    test_pdma_event_t event_type = is_done ? TEST_PDMA_EVENT_COMPLETE : TEST_PDMA_EVENT_TIMEOUT;
    rt_event_send(test_pdma_event, event_type);
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

    /* For software-managed DMA cache coherency, ensure buffer start address and size are cache-line aligned */
    uint8_t *buf = rt_malloc_align(len, CACHE_LINE_SIZE);
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

    rt_event_control(test_pdma_event, RT_IPC_CMD_RESET, NULL);

    /* Configure DMA transfer */
    err = k230_pdma_request_channel(&ch);
    uassert_int_equal(err, RT_EOK);

    usr_pdma_cfg_t pdma_cfg;
    /* Configure DMA parameters */
    pdma_cfg.device = UART0_TX;
    pdma_cfg.src_addr = buf_pa;
    pdma_cfg.dst_addr = (rt_uint8_t *)UART0_BASE_ADDR;
    pdma_cfg.line_size = len;

    /* Set channel configuration */
    pdma_cfg.pdma_ch_cfg.ch_src_type = CONTINUE;
    pdma_cfg.pdma_ch_cfg.ch_dev_hsize = PSBYTE1;
    pdma_cfg.pdma_ch_cfg.ch_dat_endian = PDEFAULT;
    pdma_cfg.pdma_ch_cfg.ch_dev_blen = PBURST_LEN_16;
    pdma_cfg.pdma_ch_cfg.ch_priority = 7;
    pdma_cfg.pdma_ch_cfg.ch_dev_tout = 0xFFF;

    err = k230_pdma_set_callback(ch, test_pdma_call_back);
    uassert_int_equal(err, RT_EOK);

    err = k230_pdma_config(ch, &pdma_cfg);
    uassert_int_equal(err, RT_EOK);

    /* Start transfer and wait for completion */
    err = k230_pdma_start(ch);
    uassert_int_equal(err, RT_EOK);

    err = rt_event_recv(test_pdma_event,
                       TEST_PDMA_EVENT_COMPLETE | TEST_PDMA_EVENT_TIMEOUT,
                       RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                       RT_WAITING_FOREVER,
                       &recv_event);
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(recv_event, TEST_PDMA_EVENT_COMPLETE);

    /* Cleanup */
    err = k230_pdma_stop(ch);
    uassert_int_equal(err, RT_EOK);

    err = k230_pdma_release_channel(ch);
    uassert_int_equal(err, RT_EOK);

    rt_free_align(buf);
    LOG_I("PDMA TX test completed successfully");
}

/* Test DMA transfer from UART RX FIFO to DDR */
void test_pdma_rx()
{
    rt_uint8_t ch;
    rt_err_t err;
    rt_uint32_t recv_event;
    rt_uint32_t len = 16;

    uint8_t *buf = rt_malloc_align(64, CACHE_LINE_SIZE);
    void *buf_pa = rt_kmem_v2p(buf);

    /* Reset event before starting test */
    rt_event_control(test_pdma_event, RT_IPC_CMD_RESET, NULL);

    /* Request DMA channel */
    err = k230_pdma_request_channel(&ch);
    uassert_int_equal(err, RT_EOK);

    /* Configure DMA parameters */
    usr_pdma_cfg_t pdma_cfg;
    pdma_cfg.device = UART0_RX;
    pdma_cfg.src_addr = (rt_uint8_t *)UART0_BASE_ADDR;
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
    err = k230_pdma_set_callback(ch, test_pdma_call_back);
    uassert_int_equal(err, RT_EOK);

    err = k230_pdma_config(ch, &pdma_cfg);
    uassert_int_equal(err, RT_EOK);

    LOG_I("Send test data by keyboard input within 2 seconds (to UART receive buffer)");

    /* Setup 2 second timeout */
    rt_tick_t timeout = RT_TICK_PER_SECOND * 2;
    rt_tick_t start_tick = rt_tick_get();

    /* Mask UART0 interrupt to prevent FIFO access by ISR */
    rt_hw_interrupt_mask(UART0_IRQ);

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
    err = rt_event_recv(test_pdma_event,
                       TEST_PDMA_EVENT_COMPLETE | TEST_PDMA_EVENT_TIMEOUT,
                       RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                       RT_WAITING_FOREVER,
                       &recv_event);
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(recv_event, TEST_PDMA_EVENT_COMPLETE);

    rt_hw_interrupt_umask(UART0_IRQ);

    err = k230_pdma_stop(ch);
    uassert_int_equal(err, RT_EOK);

    err = k230_pdma_release_channel(ch);
    uassert_int_equal(err, RT_EOK);

    LOG_I("Got: %.*s", len, buf);

    rt_free_align(buf);
}

static rt_err_t utest_tc_init(void)
{
    test_pdma_event = (rt_event_t)rt_malloc(sizeof(struct rt_event));
    if (test_pdma_event == RT_NULL)
    {
        LOG_E("Failed to allocate memory for pdma_event!");
        return -RT_ENOMEM;
    }

    if (rt_event_init(test_pdma_event, "pdma_event", RT_IPC_FLAG_FIFO) != RT_EOK)
    {
        LOG_E("Failed to init pdma_event!");
        rt_free(test_pdma_event);
        return -RT_ERROR;
    }

    LOG_I("PDMA event initialized successfully!");
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_free(test_pdma_event);

    /* Check and release all DMA channels */
    for (rt_uint8_t ch = 0; ch < PDMA_CH_MAX; ch++)
    {
        rt_err_t err = k230_pdma_release_channel(ch);

        /* Channel was successfully released now - means it wasn't properly released in test case */
        if (err == RT_EOK)
        {
            LOG_W("PDMA channel %d was not released in test case!", ch);
        }
        /* Channel release failed with error other than -RT_EINVAL (unexpected error) */
        else if (err != -RT_EINVAL)
        {
            LOG_I("PDMA channel %d release failed: %d", ch, err);
        }
        /* -RT_EINVAL means channel was already released (normal case) - no action needed */
    }

    return RT_EOK;
}

void test_pdma()
{
    UTEST_UNIT_RUN(test_pdma_request);
    UTEST_UNIT_RUN(test_pdma_tx);
    UTEST_UNIT_RUN(test_pdma_rx);
}

UTEST_TC_EXPORT(test_pdma, "pdma", utest_tc_init, utest_tc_cleanup, 10);
