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
 * Test Case Name: UART Unread Bytes Count Test
 *
 * Test Objectives:
 * - Validate query of unread RX bytes and flush interaction in non-blocking receive mode
 * - Verify APIs: rt_device_find, rt_device_control(RT_DEVICE_CTRL_CONFIG / RT_SERIAL_CTRL_GET_UNREAD_BYTES_COUNT / RT_SERIAL_CTRL_RX_FLUSH),
 *   rt_device_open with RT_DEVICE_FLAG_RX_NON_BLOCKING | RT_DEVICE_FLAG_TX_BLOCKING,
 *   rt_device_write
 *
 * Test Scenarios:
 * - **Scenario 1 (Unread Count Verification / tc_uart_api):**
 *   1. Configure UART buffers and send varying payload lengths, some exceeding RX buffer capacity.
 *   2. After each transfer, query unread byte count and ensure it saturates at `min(send_size, RT_SERIAL_TC_RXBUF_SIZE)`.
 *   3. Flush RX buffer and verify unread count resets to zero before next iteration.
 *
 * Verification Metrics:
 * - `RT_SERIAL_CTRL_GET_UNREAD_BYTES_COUNT` returns expected length; subsequent flush yields zero.
 * - All iterations covering large and random payloads complete with RT_EOK.
 *
 * Dependencies:
 * - Requires `RT_UTEST_SERIAL_V2`, RX count control support, and loopback wiring on `RT_SERIAL_TC_DEVICE_NAME`.
 * - Optional DMA ping buffer configuration honored.
 *
 * Expected Results:
 * - Test ends without assertions; logs may remain silent unless failures occur.
 * - Utest harness prints `[  PASSED  ] [ result   ] testcase (components.drivers.serial.v2.uart_get_unread_bytes_count)`.
 */

#include <rtthread.h>
#include "utest.h"
#include <rtdevice.h>
#include <stdlib.h>

/* */

#ifdef RT_UTEST_SERIAL_V2

static struct rt_serial_device *serial;
static rt_uint8_t               uart_over_flag = RT_FALSE;

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

static rt_err_t test_item(rt_uint8_t *uart_write_buffer, rt_uint32_t size)
{
    rt_uint32_t old_tick;
    rt_ssize_t  send_len;
    rt_ssize_t  buf_data_len;

    send_len = rt_device_write(&serial->parent, 0, uart_write_buffer, size);
    if (size > RT_SERIAL_TC_RXBUF_SIZE)
    {
        size = RT_SERIAL_TC_RXBUF_SIZE;
    }

    rt_thread_delay(5);
    rt_device_control(&serial->parent, RT_SERIAL_CTRL_GET_UNREAD_BYTES_COUNT, (void *)&buf_data_len);
    if (size != buf_data_len)
    {
        return -RT_ERROR;
    }

    rt_device_control(&serial->parent, RT_SERIAL_CTRL_RX_FLUSH, RT_NULL);

    rt_device_control(&serial->parent, RT_SERIAL_CTRL_GET_UNREAD_BYTES_COUNT, (void *)&buf_data_len);
    if (0 != buf_data_len)
    {
        return -RT_ERROR;
    }

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
#ifdef RT_SERIAL_USING_DMA
    config.dma_ping_bufsz = RT_SERIAL_TC_RXBUF_SIZE / 2;
#endif
    rt_device_control(&serial->parent, RT_DEVICE_CTRL_CONFIG, &config);

    result = rt_device_open(&serial->parent, RT_DEVICE_FLAG_RX_NON_BLOCKING | RT_DEVICE_FLAG_TX_BLOCKING);
    if (result != RT_EOK)
    {
        LOG_E("Open uart device failed.");
        return RT_FALSE;
    }

    rt_uint8_t *uart_write_buffer;
    rt_uint32_t i;
    uart_write_buffer = (rt_uint8_t *)rt_malloc(RT_SERIAL_TC_TXBUF_SIZE * 5 + 1);

    srand(rt_tick_get());
    for (i = 0; i < RT_SERIAL_TC_SEND_ITERATIONS; i++)
    {
        if (RT_EOK != test_item(uart_write_buffer, RT_SERIAL_TC_RXBUF_SIZE + RT_SERIAL_TC_RXBUF_SIZE * (rand() % 5)))
        {
            result = -RT_ERROR;
            goto __exit;
        }

        if (RT_EOK != test_item(uart_write_buffer, rand() % (RT_SERIAL_TC_RXBUF_SIZE * 5)))
        {
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

UTEST_TC_EXPORT(testcase, "components.drivers.serial.v2.uart_get_unread_bytes_count", utest_tc_init, utest_tc_cleanup, 30);

#endif /* TC_UART_USING_TC */
