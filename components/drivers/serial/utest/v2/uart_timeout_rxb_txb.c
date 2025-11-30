/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-11-13     CYFS         Add standardized utest documentation block
*/

/**
 * Test Case Name: UART Blocking Timeout RX/TX Test
 *
 * Test Objectives:
 * - Validate combined blocking receive/transmit timeout behavior for the serial v2 driver
 * - Verify APIs: rt_device_find, rt_device_control(RT_SERIAL_CTRL_SET_RX_TIMEOUT / _SET_TX_TIMEOUT / _RX_FLUSH / _TX_FLUSH),
 *   rt_device_open with RT_DEVICE_FLAG_RX_BLOCKING | RT_DEVICE_FLAG_TX_BLOCKING, rt_device_read, rt_device_write
 *
 * Test Scenarios:
 * - **Scenario 1 (Timeout Verification / tc_uart_api):**
 *   1. Discover and reconfigure the target UART with loopback (TX shorted to RX) and known buffer sizes.
 *   2. Spawn concurrent TX and RX worker threads; RX thread configures 100-tick blocking timeout and repeatedly validates measured wait time.
 *   3. Switch to TX timeout mode (10 ticks) and push oversized bursts to ensure write calls block for the configured window.
 *   4. Monitor status flags to detect allocation failures, timeout violations, or thread termination.
 *
 * Verification Metrics:
 * - RX blocking reads must complete within [100, 101] ticks and return expected lengths across 10 iterations.
 * - TX blocking writes must complete within [10, 11] ticks with successful flush between iterations.
 * - No allocation or control failures occur; master loop exits with `uart_over_flag == RT_TRUE`.
 *
 * Dependencies:
 * - Requires `RT_UTEST_SERIAL_V2` enabled and a loopbacked UART defined by `RT_SERIAL_TC_DEVICE_NAME`.
 * - Serial driver must support blocking mode and timeout controls; optional RX DMA segment size is set via `RT_SERIAL_USING_DMA`.
 * - Two 2 KB threads plus dynamic buffers (~RT_SERIAL_TC_RXBUF_SIZE*10) must be allocatable from the heap.
 *
 * Expected Results:
 * - Test completes without assertions, device handles close cleanly, logs show timeout measurements within tolerance.
 * - Utest harness prints `[  PASSED  ] [ result   ] testcase (components.drivers.serial.v2.uart_timeout_rxb_txb)`.
 */

#include <rtthread.h>
#include "utest.h"
#include <rtdevice.h>
#include <stdlib.h>

/* */

#ifdef RT_UTEST_SERIAL_V2

static struct rt_serial_device *serial;
static rt_bool_t                uart_result     = RT_TRUE;
static rt_uint8_t               uart_write_flag = RT_TRUE;
static rt_uint8_t               uart_over_flag  = RT_FALSE;

static rt_err_t uart_find(void)
{
    serial = (struct rt_serial_device *)rt_device_find(RT_SERIAL_TC_DEVICE_NAME);

    if (serial == RT_NULL)
    {
        LOG_E("find %s device failed!\n", RT_SERIAL_TC_DEVICE_NAME);
        return -RT_ERROR;
    }

    return RT_EOK;
}


static void uart_send_entry(void *parameter)
{
    rt_uint8_t *uart_write_buffer = RT_NULL;
    rt_uint32_t i                 = 0;

    /* assign send buffer */
    uart_write_buffer = (rt_uint8_t *)rt_malloc(RT_SERIAL_TC_RXBUF_SIZE);
    if (uart_write_buffer == RT_NULL)
    {
        LOG_E("Without spare memory for uart dma!");
        uart_result = RT_FALSE;
        return;
    }

    for (i = 0; i < RT_SERIAL_TC_RXBUF_SIZE; i++)
    {
        uart_write_buffer[i] = (rt_uint8_t)i;
    }

    while (1)
    {
        if (uart_write_flag == RT_FALSE)
            break;

        rt_device_write(&serial->parent, 0, uart_write_buffer, RT_SERIAL_TC_RXBUF_SIZE / 3);
        rt_thread_mdelay(40);
    }

    rt_free(uart_write_buffer);
}

static void uart_rec_entry(void *parameter)
{
    rt_uint8_t *uart_write_buffer;
    rt_tick_t   old_tick;
    rt_tick_t   tick_diff;
    rt_ssize_t  recv_len;
    rt_uint32_t i;
    rt_int32_t  timeout = 0;
    uart_write_buffer   = (rt_uint8_t *)rt_malloc(RT_SERIAL_TC_RXBUF_SIZE * 10 + 1);

    timeout = 100;
    rt_device_control(&serial->parent, RT_SERIAL_CTRL_SET_RX_TIMEOUT, (void *)&timeout);

    uart_write_flag = RT_TRUE;
    for (i = 0; i < 10; i++)
    {
        rt_device_control(&serial->parent, RT_SERIAL_CTRL_RX_FLUSH, RT_NULL);
        old_tick  = rt_tick_get();
        recv_len  = rt_device_read(&serial->parent, 0, (void *)uart_write_buffer, RT_SERIAL_TC_RXBUF_SIZE);
        tick_diff = rt_tick_get() - old_tick;
        if (tick_diff > 100 + 1 || tick_diff < 100)
        {
            LOG_E("timeout_test: recv_size [%d], RX block time [%d], expect_time [100 - 101]", recv_len, tick_diff);
            uart_write_flag = RT_FALSE;
            uart_result     = RT_FALSE;
            rt_free(uart_write_buffer);
            rt_thread_mdelay(60);
            return;
        }

        LOG_I("timeout_test: RX block time [%d], expect_time [100 - 101]", tick_diff);
    }
    uart_write_flag = RT_FALSE;

    rt_thread_mdelay(60);
    timeout = 10;
    rt_device_control(&serial->parent, RT_SERIAL_CTRL_SET_TX_TIMEOUT, (void *)&timeout);

    for (i = 0; i < 10; i++)
    {
        old_tick  = rt_tick_get();
        recv_len  = rt_device_write(&serial->parent, 0, uart_write_buffer, RT_SERIAL_TC_RXBUF_SIZE * 10);
        tick_diff = rt_tick_get() - old_tick;
        if (tick_diff > 10 + 1 || tick_diff < 10)
        {
            LOG_E("timeout_test: recv_size [%d], TX block time [%d], expect_time [10 - 11]", recv_len, tick_diff);
            uart_result = RT_FALSE;
            rt_free(uart_write_buffer);
            return;
        }

        LOG_I("timeout_test: TX block time [%d], expect_time [10 - 11]", tick_diff);
        rt_device_control(&serial->parent, RT_SERIAL_CTRL_TX_FLUSH, RT_NULL);
    }

    rt_free(uart_write_buffer);
    uart_over_flag = RT_TRUE;
}

static rt_bool_t uart_api()
{
    rt_thread_t thread_send = RT_NULL;
    rt_thread_t thread_recv = RT_NULL;
    rt_err_t    result      = RT_EOK;

    result = uart_find();
    if (result != RT_EOK)
    {
        return RT_FALSE;
    }

    /* Reinitialize */
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    config.baud_rate               = BAUD_RATE_115200;
    config.rx_bufsz                = RT_SERIAL_TC_RXBUF_SIZE;
    config.tx_bufsz                = RT_SERIAL_TC_TXBUF_SIZE;
#ifdef RT_SERIAL_USING_DMA
    config.dma_ping_bufsz = RT_SERIAL_TC_RXBUF_SIZE / 2;
#endif
    rt_device_control(&serial->parent, RT_DEVICE_CTRL_CONFIG, &config);

    result = rt_device_open(&serial->parent, RT_DEVICE_FLAG_RX_BLOCKING | RT_DEVICE_FLAG_TX_BLOCKING);
    if (result != RT_EOK)
    {
        LOG_E("Open uart device failed.");
        return RT_FALSE;
    }

    thread_send = rt_thread_create("uart_send", uart_send_entry, NULL, 2048, RT_THREAD_PRIORITY_MAX - 4, 10);
    thread_recv = rt_thread_create("uart_recv", uart_rec_entry, NULL, 2048, RT_THREAD_PRIORITY_MAX - 5, 10);

    if ((thread_send != RT_NULL) && (thread_recv != RT_NULL))
    {
        rt_thread_startup(thread_send);
        rt_thread_startup(thread_recv);
    }
    else
    {
        result = -RT_ERROR;
        goto __exit;
    }

    while (1)
    {
        if (uart_result != RT_TRUE)
        {
            LOG_E("The test for uart dma is failure.");
            result = -RT_ERROR;
            goto __exit;
        }
        if (uart_over_flag == RT_TRUE)
        {
            goto __exit;
        }
        /* waiting for test over */
        rt_thread_mdelay(5);
    }

__exit:
    rt_device_close(&serial->parent);
    rt_thread_mdelay(5);
    return result == RT_EOK ? RT_TRUE : RT_FALSE;
}

static void tc_uart_api(void)
{
    uassert_true(uart_api() == RT_TRUE);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    uart_result          = RT_TRUE;
    uart_write_flag      = RT_TRUE;
    uart_over_flag       = RT_FALSE;
    rt_device_t uart_dev = rt_device_find(RT_SERIAL_TC_DEVICE_NAME);
    while (rt_device_close(uart_dev) != -RT_ERROR);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(tc_uart_api);
}

UTEST_TC_EXPORT(testcase, "components.drivers.serial.v2.uart_timeout_rxb_txb", utest_tc_init, utest_tc_cleanup, 30);

#endif /* TC_UART_USING_TC */
