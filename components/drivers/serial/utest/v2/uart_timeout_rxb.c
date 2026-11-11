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
 * Test Case Name: UART Blocking RX Timeout Test
 *
 * Test Objectives:
 * - Validate blocking receive timeout behavior while TX operates non-blocking
 * - Verify APIs: rt_device_find, rt_device_control(RT_SERIAL_CTRL_SET_RX_TIMEOUT / _TX_FLUSH),
 *   rt_device_open with RT_DEVICE_FLAG_RX_BLOCKING | RT_DEVICE_FLAG_TX_NON_BLOCKING,
 *   rt_device_write, rt_device_read
 *
 * Test Scenarios:
 * - **Scenario 1 (RX Timeout Sweep / tc_uart_api):**
 *   1. Reconfigure UART buffers (optional DMA ping buffer) and open in RX blocking / TX non-blocking mode.
 *   2. Allocate reusable TX buffer and iterate `RT_SERIAL_TC_SEND_ITERATIONS` times.
 *   3. For each iteration, randomize burst length (1024~2047 bytes), program RX timeout, transmit payload,
 *      then read back and ensure received size reflects timeout truncation.
 *   4. Flush TX FIFO and delay to allow residual bytes to drain before next iteration.
 *
 * Verification Metrics:
 * - Each receive length lies within `[rx_timeout_send_size - 70, send_size - 80]`.
 * - Transmission always completes full burst; overall loop exits with RT_EOK and device closes successfully.
 *
 * Dependencies:
 * - Requires `RT_UTEST_SERIAL_V2` with UART loopback (`RT_SERIAL_TC_DEVICE_NAME` TX shorted to RX).
 * - Serial driver must support RX timeout control and optional DMA ping buffer configuration.
 * - Random number generator and system tick used for timeout computation.
 *
 * Expected Results:
 * - No assertions triggered; log traces show per-iteration timeout measurements.
 * - Utest framework prints `[  PASSED  ] [ result   ] testcase (components.drivers.serial.v2.uart_timeout_rxb)`.
 */

#include <rtthread.h>
#include "utest.h"
#include <rtdevice.h>
#include <stdlib.h>


#ifdef RT_UTEST_SERIAL_V2

static struct rt_serial_device *serial;

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

static rt_err_t rx_timeout_test_item(rt_uint8_t *uart_write_buffer, rt_uint32_t send_size)
{
    rt_uint32_t readSize             = 0;
    rt_int32_t  rx_timeout_send_size = send_size - send_size / 3;
    rt_int32_t  rx_timeout           = rt_tick_from_millisecond(0.0868 * rx_timeout_send_size + 1);

    rt_device_control(&serial->parent, RT_SERIAL_CTRL_SET_RX_TIMEOUT, (void *)&rx_timeout);

    rt_ssize_t size = rt_device_write(&serial->parent, 0, uart_write_buffer, send_size);
    if (size != send_size)
    {
        LOG_E("size [%4d], send_size [%4d]", size, send_size);
        return -RT_ERROR;
    }

    readSize = rt_device_read(&serial->parent, 0, uart_write_buffer, size);
    if (readSize < (rx_timeout_send_size - 70) || readSize > (send_size - 80))
    {
        LOG_E("readSize [%4d], rx_timeout_send_size [%4d]", readSize, rx_timeout_send_size);
        return -RT_ERROR;
    }

    rt_device_control(&serial->parent, RT_SERIAL_CTRL_TX_FLUSH, RT_NULL);
    /* Waiting for rx to complete reception */
    rt_thread_mdelay(0.0868 * (send_size / 3));

    LOG_I("rx timeout send_size [%4d]", send_size);
    return RT_EOK;
}

static rt_bool_t uart_api()
{
    rt_err_t result = RT_EOK;

    result = uart_find();
    if (result != RT_EOK)
    {
        return RT_FALSE;
    }

    /* Reinitialize */
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    config.baud_rate               = BAUD_RATE_115200;
    config.rx_bufsz                = RT_SERIAL_TC_RXBUF_SIZE;
    config.tx_bufsz                = 2048;
#ifdef RT_SERIAL_USING_DMA
    config.dma_ping_bufsz = RT_SERIAL_TC_RXBUF_SIZE / 2;
#endif
    rt_device_control(&serial->parent, RT_DEVICE_CTRL_CONFIG, &config);

    result = rt_device_open(&serial->parent, RT_DEVICE_FLAG_RX_BLOCKING | RT_DEVICE_FLAG_TX_NON_BLOCKING);
    if (result != RT_EOK)
    {
        LOG_E("Open uart device failed.");
        return RT_FALSE;
    }

    rt_uint8_t *uart_write_buffer;
    rt_uint32_t i;
    uart_write_buffer = (rt_uint8_t *)rt_malloc(2048);


    for (i = 0; i < RT_SERIAL_TC_SEND_ITERATIONS; i++)
    {
        srand(rt_tick_get());
        if (RT_EOK != rx_timeout_test_item(uart_write_buffer, 1024 + (rand() % 1024)))
        {
            LOG_E("test_item failed.");
            result = -RT_ERROR;
            goto __exit;
        }
    }

__exit:
    rt_free(uart_write_buffer);
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
    LOG_I("UART TEST: Please connect Tx and Rx directly for self testing.");
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_device_t uart_dev = rt_device_find(RT_SERIAL_TC_DEVICE_NAME);
    while (rt_device_close(uart_dev) != -RT_ERROR);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(tc_uart_api);
}

UTEST_TC_EXPORT(testcase, "components.drivers.serial.v2.uart_timeout_rxb", utest_tc_init, utest_tc_cleanup, 30);

#endif /* TC_UART_USING_TC */
