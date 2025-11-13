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
 * Test Case Name: UART RX Buffer Flush Test
 *
 * Test Objectives:
 * - Verify RX flush control clears buffered data and preserves integrity of subsequent transfers
 * - Confirm APIs: rt_device_find, rt_device_control(RT_DEVICE_CTRL_CONFIG / RT_SERIAL_CTRL_RX_FLUSH),
 *   rt_device_open with RT_DEVICE_FLAG_RX_NON_BLOCKING | RT_DEVICE_FLAG_TX_BLOCKING,
 *   rt_device_read, rt_device_write
 *
 * Test Scenarios:
 * - **Scenario 1 (Flush Validation / tc_uart_api):**
 *   1. Configure UART buffers and allocate test pattern spanning multiple RX buffer lengths.
 *   2. Send payload, consume a single byte, invoke RX flush, and ensure next read returns no residual data.
 *   3. Resend partial payloads of varying sizes to confirm data after flush matches original pattern.
 *
 * Verification Metrics:
 * - Initial read after flush returns zero bytes; subsequent reads match transmitted data byte-for-byte.
 * - All iterations across deterministic and random lengths complete with RT_EOK.
 *
 * Dependencies:
 * - Requires `RT_UTEST_SERIAL_V2`, loopback wiring, and RX flush support on `RT_SERIAL_TC_DEVICE_NAME`.
 * - Optional DMA ping buffer configuration honored when `RT_SERIAL_USING_DMA` enabled.
 *
 * Expected Results:
 * - No assertions triggered; logs show flush operations with payload sizes.
 * - Utest harness prints `[  PASSED  ] [ result   ] testcase (components.drivers.serial.v2.uart_flush_rx)`.
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

static rt_err_t test_item(rt_uint8_t *uart_write_buffer, rt_uint32_t send_size)
{
    rt_uint8_t  readBuf[16] = {0};
    rt_uint32_t readSize    = 0;
    if (send_size >= sizeof(readBuf))
    {
        readSize = sizeof(readBuf);
    }
    else
    {
        readSize = send_size;
    }

    rt_ssize_t size = rt_device_write(&serial->parent, 0, uart_write_buffer, send_size);
    if (size != send_size)
    {
        LOG_E("size [%4d], send_size [%4d]", size, send_size);
        return -RT_ERROR;
    }
    rt_thread_mdelay(send_size * 0.0868 + 5);
    if (1 != rt_device_read(&serial->parent, 0, uart_write_buffer, 1))
    {
        LOG_E("read failed.");
        return -RT_ERROR;
    }

    rt_device_control(&serial->parent, RT_SERIAL_CTRL_RX_FLUSH, RT_NULL);
    if (0 != rt_device_read(&serial->parent, 0, uart_write_buffer, 1))
    {
        LOG_E("read failed.");
        return -RT_ERROR;
    }

    /* Resend the data and check for any discrepancies upon reception */
    if (readSize > 0)
    {
        rt_device_write(&serial->parent, 0, uart_write_buffer, readSize);
        rt_thread_mdelay(readSize * 0.0868 + 5);
        rt_device_read(&serial->parent, 0, readBuf, readSize);

        for (rt_uint32_t i = 0; i < readSize; i++)
        {
            if (readBuf[i] != uart_write_buffer[i])
            {
                LOG_E("index: %d, Read Different data -> former data: %x, current data: %x.", i, uart_write_buffer[i], readBuf[i]);
                return -RT_ERROR;
            }
        }
    }

    LOG_I("flush rx send_size [%4d]", send_size);

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
    uart_write_buffer = (rt_uint8_t *)rt_malloc(RT_SERIAL_TC_RXBUF_SIZE * 5 + 1);
    for (rt_uint32_t count = 0; count < (RT_SERIAL_TC_RXBUF_SIZE * 5 + 1); count++)
    {
        uart_write_buffer[count] = count;
    }

    srand(rt_tick_get());
    for (i = 0; i < RT_SERIAL_TC_SEND_ITERATIONS; i++)
    {
        if (RT_EOK != test_item(uart_write_buffer, RT_SERIAL_TC_RXBUF_SIZE + RT_SERIAL_TC_RXBUF_SIZE * (rand() % 5)))
        {
            LOG_E("test_item failed.");
            result = -RT_ERROR;
            goto __exit;
        }

        if (RT_EOK != test_item(uart_write_buffer, rand() % (RT_SERIAL_TC_RXBUF_SIZE * 5)))
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

UTEST_TC_EXPORT(testcase, "components.drivers.serial.v2.uart_flush_rx", utest_tc_init, utest_tc_cleanup, 30);

#endif /* TC_UART_USING_TC */
