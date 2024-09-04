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

/* #define DBG_LVL DBG_LOG*/

#define TC_UART_DEVICE_NAME "uart2"

#ifdef UTEST_SERIAL_TC

static struct rt_serial_device *serial;
static rt_bool_t                uart_result     = RT_TRUE;
static rt_uint8_t               uart_write_flag = RT_TRUE;
static rt_uint8_t               uart_over_flag  = RT_FALSE;


static rt_err_t uart_find(void)
{
    serial = (struct rt_serial_device *)rt_device_find(TC_UART_DEVICE_NAME);

    if (serial == RT_NULL)
    {
        LOG_E("find %s device failed!\n", TC_UART_DEVICE_NAME);
        return -RT_ERROR;
    }

    return RT_EOK;
}


static void uart_send_entry(void *parameter)
{
    rt_uint8_t *uart_write_buffer = RT_NULL;
    rt_uint32_t i                 = 0;

    /* assign send buffer */
    uart_write_buffer = (rt_uint8_t *)rt_malloc(BSP_UART2_RX_BUFSIZE);
    if (uart_write_buffer == RT_NULL)
    {
        LOG_E("Without spare memory for uart dma!");
        uart_result = RT_FALSE;
        return;
    }

    for (i = 0; i < BSP_UART2_RX_BUFSIZE; i++)
    {
        uart_write_buffer[i] = (rt_uint8_t)i;
    }

    while (1)
    {
        if (uart_write_flag == RT_FALSE)
            break;

        rt_device_write(&serial->parent, 0, uart_write_buffer, BSP_UART2_RX_BUFSIZE / 3);
        rt_thread_mdelay(40);
    }

    rt_free(uart_write_buffer);
}

static void uart_rec_entry(void *parameter)
{
    rt_uint8_t *ch;
    rt_uint32_t old_tick;
    rt_uint32_t i;
    ch = (rt_uint8_t *)rt_malloc(sizeof(rt_uint8_t) * (BSP_UART2_RX_BUFSIZE * 10 + 1));

    rt_device_control(&serial->parent, RT_SERIAL_CTRL_RX_TIMEOUT, (void *)100);

    uart_write_flag = RT_TRUE;
    for (i = 0; i < 10; i++)
    {
        rt_device_control(&serial->parent, RT_SERIAL_CTRL_RX_FLUSH, RT_NULL);
        old_tick          = rt_tick_get();
        uint32_t recv_len = rt_device_read(&serial->parent, 0, (void *)ch, BSP_UART2_RX_BUFSIZE);
        if (rt_tick_get() - old_tick > 100 + 2 || rt_tick_get() - old_tick < 100 - 2)
        {
            rt_kprintf("%d recv_len: %d\r\n", rt_tick_get() - old_tick, recv_len);
            uart_write_flag = RT_FALSE;
            uart_result     = RT_FALSE;
            rt_free(ch);
            return;
        }
    }
    uart_write_flag = RT_FALSE;

    rt_thread_mdelay(60);

    rt_device_control(&serial->parent, RT_SERIAL_CTRL_TX_TIMEOUT, (void *)10);
    for (i = 0; i < 10; i++)
    {
        old_tick = rt_tick_get();
        rt_device_write(&serial->parent, 0, ch, BSP_UART2_RX_BUFSIZE * 10);
        if (rt_tick_get() - old_tick > 10 + 2 || rt_tick_get() - old_tick < 10 - 2)
        {
            uart_result = RT_FALSE;
            rt_free(ch);
            return;
        }

        rt_device_control(&serial->parent, RT_SERIAL_CTRL_TX_FLUSH, RT_NULL);
    }

    rt_free(ch);
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
    config.rx_bufsz                = BSP_UART2_RX_BUFSIZE;
    config.tx_bufsz                = 64;
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
    rt_device_t uart_dev = rt_device_find(TC_UART_DEVICE_NAME);
    while (rt_device_close(uart_dev) != -RT_ERROR);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(tc_uart_api);
}

UTEST_TC_EXPORT(testcase, "testcases.drivers.uart_timeout_rxb_txb", utest_tc_init, utest_tc_cleanup, 30);

#endif /* TC_UART_USING_TC */
