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
 * Test Case Name: UART Blocking TX Timeout Test
 *
 * Test Objectives:
 * - Validate blocking transmit timeout handling when RX operates non-blocking
 * - Verify APIs: rt_device_find, rt_device_control(RT_SERIAL_CTRL_SET_TX_TIMEOUT / _TX_FLUSH),
 *   rt_device_open with RT_DEVICE_FLAG_RX_NON_BLOCKING | RT_DEVICE_FLAG_TX_BLOCKING, rt_device_write
 *
 * Test Scenarios:
 * - **Scenario 1 (TX Timeout Sweep / tc_uart_api):**
 *   1. Configure UART buffers and open the device in RX non-blocking / TX blocking mode.
 *   2. Allocate a reusable TX buffer and iterate `RT_SERIAL_TC_SEND_ITERATIONS` times.
 *   3. For each iteration, randomize burst length (1024~2047 bytes), set expected TX timeout,
 *      issue write, and ensure returned write size falls into tolerated range.
 *   4. Flush TX FIFO and delay to allow loopback RX to complete reception.
 *
 * Verification Metrics:
 * - Each write returns size within `[tx_timeout_send_size - 70, send_size - 80]`.
 * - No allocation failures; all iterations exit via RT_EOK and device closes cleanly.
 *
 * Dependencies:
 * - Requires `RT_UTEST_SERIAL_V2` enabled and loopback wiring of `RT_SERIAL_TC_DEVICE_NAME`.
 * - Excludes configurations with `BSP_UART2_TX_USING_DMA` (DMA write timeout unsupported).
 * - Needs random number generator and system tick for duration calculations.
 *
 * Expected Results:
 * - Test completes without assertion failures; logs show sequence of timeout send sizes.
 * - Utest framework prints `[  PASSED  ] [ result   ] testcase (components.drivers.serial.v2.uart_timeout_txb)`.
 */

#include <rtthread.h>
#include "utest.h"
#include <rtdevice.h>
#include <stdlib.h>

#ifdef RT_UTEST_SERIAL_V2
#ifndef BSP_UART2_TX_USING_DMA

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

static rt_err_t tx_timeout_test_item(rt_uint8_t *uart_write_buffer, rt_uint32_t send_size)
{
    rt_uint32_t readSize             = 0;
    rt_int32_t  tx_timeout_send_size = send_size - send_size / 3;
    rt_int32_t  tx_timeout           = rt_tick_from_millisecond(0.0868 * tx_timeout_send_size + 1);
    rt_device_control(&serial->parent, RT_SERIAL_CTRL_SET_TX_TIMEOUT, (void *)&tx_timeout);

    rt_ssize_t size = rt_device_write(&serial->parent, 0, uart_write_buffer, send_size);
    if (size < (tx_timeout_send_size - 70) || size > (send_size - 80))
    {
        LOG_E("size [%4d], send_size [%4d]", size, tx_timeout_send_size);
        return -RT_ERROR;
    }

    rt_device_control(&serial->parent, RT_SERIAL_CTRL_TX_FLUSH, RT_NULL);
    /* Waiting for rx to complete reception */
    rt_thread_mdelay(0.0868 * (send_size / 3));

    LOG_I("tx timeout send_size [%4d]", send_size);

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
    config.tx_bufsz                = RT_SERIAL_TC_TXBUF_SIZE;

    rt_device_control(&serial->parent, RT_DEVICE_CTRL_CONFIG, &config);

    result = rt_device_open(&serial->parent, RT_DEVICE_FLAG_RX_NON_BLOCKING | RT_DEVICE_FLAG_TX_BLOCKING);
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
        if (RT_EOK != tx_timeout_test_item(uart_write_buffer, 1024 + (rand() % 1024)))
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

UTEST_TC_EXPORT(testcase, "components.drivers.serial.v2.uart_timeout_txb", utest_tc_init, utest_tc_cleanup, 30);

#endif /* BSP_UART2_TX_USING_DMA */
#endif /* TC_UART_USING_TC */
