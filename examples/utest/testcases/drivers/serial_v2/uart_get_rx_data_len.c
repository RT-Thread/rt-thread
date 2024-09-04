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
static rt_uint8_t               uart_over_flag = RT_FALSE;

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
    config.rx_bufsz                = BSP_UART2_RX_BUFSIZE;
    config.tx_bufsz                = BSP_UART2_TX_BUFSIZE;
    rt_device_control(&serial->parent, RT_DEVICE_CTRL_CONFIG, &config);

    result = rt_device_open(&serial->parent, RT_DEVICE_FLAG_RX_NON_BLOCKING | RT_DEVICE_FLAG_TX_BLOCKING);
    if (result != RT_EOK)
    {
        LOG_E("Open uart device failed.");
        return RT_FALSE;
    }

    rt_uint8_t *ch;
    rt_uint32_t old_tick;
    rt_ssize_t  send_len;
    rt_ssize_t  buf_data_len;
    ch = (rt_uint8_t *)rt_malloc(sizeof(rt_uint8_t) * (BSP_UART2_TX_BUFSIZE * 2 + 1));

    rt_device_control(&serial->parent, RT_SERIAL_CTRL_GET_RX_DATA_LEN, (void *)&buf_data_len);
    if (0 != buf_data_len)
    {
        result = -RT_ERROR;
        goto __exit;
    }

    send_len = rt_device_write(&serial->parent, 0, ch, 30);
    rt_thread_delay(100);
    rt_device_control(&serial->parent, RT_SERIAL_CTRL_GET_RX_DATA_LEN, (void *)&buf_data_len);
    if (30 != buf_data_len)
    {
        result = -RT_ERROR;
        goto __exit;
    }

    if (30 != rt_device_read(&serial->parent, 0, ch, 30))
    {
        result = -RT_ERROR;
        goto __exit;
    }

    rt_device_control(&serial->parent, RT_SERIAL_CTRL_GET_RX_DATA_LEN, (void *)&buf_data_len);
    if (0 != buf_data_len)
    {
        result = -RT_ERROR;
        goto __exit;
    }

    send_len = rt_device_write(&serial->parent, 0, ch, BSP_UART2_RX_BUFSIZE * 2);
    rt_thread_delay(100);
    rt_device_control(&serial->parent, RT_SERIAL_CTRL_GET_RX_DATA_LEN, (void *)&buf_data_len);
    if (BSP_UART2_RX_BUFSIZE != buf_data_len)
    {
        result = -RT_ERROR;
        goto __exit;
    }

    if (BSP_UART2_RX_BUFSIZE != rt_device_read(&serial->parent, 0, ch, BSP_UART2_RX_BUFSIZE))
    {
        result = -RT_ERROR;
        goto __exit;
    }

    rt_device_control(&serial->parent, RT_SERIAL_CTRL_GET_RX_DATA_LEN, (void *)&buf_data_len);
    if (0 != buf_data_len)
    {
        result = -RT_ERROR;
        goto __exit;
    }

    send_len = rt_device_write(&serial->parent, 0, ch, BSP_UART2_RX_BUFSIZE + 20);
    rt_thread_delay(100);
    rt_device_control(&serial->parent, RT_SERIAL_CTRL_GET_RX_DATA_LEN, (void *)&buf_data_len);
    if (BSP_UART2_RX_BUFSIZE != buf_data_len)
    {
        result = -RT_ERROR;
        goto __exit;
    }

    if (BSP_UART2_RX_BUFSIZE != rt_device_read(&serial->parent, 0, ch, BSP_UART2_RX_BUFSIZE))
    {
        result = -RT_ERROR;
        goto __exit;
    }

    rt_device_control(&serial->parent, RT_SERIAL_CTRL_GET_RX_DATA_LEN, (void *)&buf_data_len);
    if (0 != buf_data_len)
    {
        result = -RT_ERROR;
        goto __exit;
    }

__exit:
    rt_free(ch);
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
    rt_device_t uart_dev = rt_device_find(TC_UART_DEVICE_NAME);
    while (rt_device_close(uart_dev) != -RT_ERROR);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(tc_uart_api);
}

UTEST_TC_EXPORT(testcase, "testcases.drivers.uart_get_rx_data_len", utest_tc_init, utest_tc_cleanup, 30);

#endif /* TC_UART_USING_TC */
