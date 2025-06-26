/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 *
 */

#include <rtthread.h>
#include "utest.h"
#include <rtdevice.h>
#include <stdlib.h>


#ifdef UTEST_SERIAL_TC

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

static rt_err_t test_item(rt_uint8_t *uart_write_buffer, rt_uint32_t size)
{
    rt_device_write(&serial->parent, 0, uart_write_buffer, size);
    rt_thread_mdelay(size * 0.0868 + 5);
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
    uart_write_buffer = (rt_uint8_t *)rt_malloc(sizeof(rt_uint8_t) * (RT_SERIAL_TC_TXBUF_SIZE * 5 + 1));

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

UTEST_TC_EXPORT(testcase, "testcases.drivers.uart_flush_rx", utest_tc_init, utest_tc_cleanup, 30);

#endif /* TC_UART_USING_TC */
